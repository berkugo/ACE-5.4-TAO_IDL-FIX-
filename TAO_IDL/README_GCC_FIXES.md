# TAO_IDL GCC Uyumluluk

## Genel Bakış

ACE 5.4 ile birlikte gelen TAO_IDL derleyicisi orijinal olarak Solaris üzerinde Sun Studio (Sun CC) derleyicisi ile geliştirilmiş ve test edilmiştir. Bu derleyici ile sorunsuz çalışan kod, GCC/G++ ile derlendiğinde çeşitli runtime hataları üretmektedir.

Bu dokümanda, TAO_IDL'in modern GCC sürümleri ile uyumlu hale getirilmesi için yapılan değişiklikler detaylı olarak açıklanmaktadır.

## Değişikliklerin Kapsamı

Yapılan tüm değişiklikler yalnızca `TAO/TAO_IDL` dizini içerisinde yer almaktadır. ACE framework'ünün temel sınıfları (`ace/` dizini), TAO ORB implementasyonu (`TAO/tao/` dizini) ve diğer TAO bileşenleri bu yamalardan etkilenmemektedir.

Değişiklikler şu bileşenlerle sınırlıdır:
- IDL parser (frontend): Lexer ve parser kaynak dosyaları
- IDL code generator (backend): Kod üretim ve dosya yazım modülleri  
- Driver: Preprocessor entegrasyonu

Bu sayede mevcut ACE/TAO uygulamaları ve kütüphaneleri herhangi bir değişiklik gerektirmeden çalışmaya devam edecektir. Yamalar sadece IDL derleyicisinin GCC ile uyumlu şekilde çalışmasını sağlamaktadır.

## Problem Tanımı

TAO_IDL, GCC ile derlenip çalıştırıldığında aşağıdaki hatalar gözlemlenmektedir:

1. IDL dosyaları parse edilirken segmentation fault
2. Hata mesajları yazdırılırken NULL pointer erişimi
3. Program sonlandırılırken double free hatası

Bu hataların hiçbiri Sun CC ile derlenen versiyonda görülmemektedir.

## Analiz

### 1. Stack vs Heap Allocation Davranış Farkı

GCC, Sun CC'ye kıyasla daha agresif stack optimizasyonları uygulamaktadır. Parser kodunda (`y.tab.cpp`) bazı nesneler stack üzerinde oluşturulup pointer olarak başka nesnelere geçirilmektedir:

```cpp
// Orijinal kod - stack allocation
UTL_ScopedName n (identifier, 0);
FE_InterfaceHeader *header = new FE_InterfaceHeader(&n, ...);
```

Bu pattern'de `n` nesnesi stack frame'de yaşamakta ve `FE_InterfaceHeader` constructor'ına pointer olarak geçirilmektedir. `FE_InterfaceHeader` bu pointer'ı internal olarak saklamaktadır. Ancak constructor çağrısı tamamlandıktan sonra stack frame değişebilir ve `n`'in bulunduğu bellek alanı geçersiz hale gelebilir.

Sun CC bu durumda stack'i korurken, GCC stack frame'i daha erken geri dönüştürebilmektedir. Bu durum dangling pointer oluşmasına ve sonrasında segmentation fault'a yol açmaktadır.

### 2. GCC Preprocessor Çıktı Formatı

GCC preprocessor, Sun CC preprocessor'dan farklı bir çıktı formatı üretmektedir:

```
# 0 "dosya.idl"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "dosya.idl"
```

TAO_IDL lexer'ı bu formattaki direktifleri tanıyamamaktadır:
- `# 0 "..."` formatı (satır numarası 0)
- `<built-in>` ve `<command-line>` pseudo dosya isimleri
- Satır sonundaki ekstra flag'ler (`1 3 4`)

### 3. FILE* Pointer Reuse

GCC runtime'ı, kapatılan dosya handle'larını daha agresif bir şekilde yeniden kullanmaktadır. Bir `FILE*` pointer kapatıldıktan sonra, aynı değer yeni açılan bir dosya için tekrar kullanılabilir. Eğer eski pointer hala bir yerde saklanıyorsa ve tekrar kapatılmaya çalışılırsa double free hatası oluşur.

## Uygulanan Düzeltmeler

### Dosya 1: `fe/y.tab.cpp`

**Etkilenen bölümler:** case 36, 42, 43, 44

Stack allocation yerine heap allocation kullanılacak şekilde değiştirildi:

```cpp
// Değişiklik öncesi
UTL_ScopedName n (tao_yyvsp[-1].idval, 0);
ACE_NEW_RETURN (tao_yyval.ihval,
                FE_InterfaceHeader (&n, tao_yyvsp[0].nlval, ...),
                1);

// Değişiklik sonrası
UTL_ScopedName *n = 0;
ACE_NEW_RETURN (n,
                UTL_ScopedName (tao_yyvsp[-1].idval, 0),
                1);
ACE_NEW_RETURN (tao_yyval.ihval,
                FE_InterfaceHeader (n, tao_yyvsp[0].nlval, ...),
                1);
```

Ayrıca case 36'daki cleanup kodu güncellendi. Artık heap'te yaşayan `UTL_ScopedName` nesnesi `FE_InterfaceHeader` tarafından yönetildiği için ayrıca destroy edilmesine gerek kalmadı.

### Dosya 2: `driver/drv_preproc.cpp`

GCC preprocessor çıktısını TAO_IDL lexer'ının anlayabileceği formata dönüştüren bir filtre fonksiyonu eklendi:

```cpp
static void DRV_filter_gcc_output (const char *filename);
```

Bu fonksiyon:
- `<built-in>` ve `<command-line>` içeren satırları kaldırır
- `# 0 "..."` formatındaki satırları kaldırır (geçersiz satır numarası)
- `stdc-predef.h` referanslarını kaldırır
- `# 1 "dosya" 1 3 4` formatındaki satırlardaki ekstra flag'leri temizler

Fonksiyon, preprocessor çıktısı oluşturulduktan hemen sonra ve lexer'a verilmeden önce çağrılmaktadır.

### Dosya 3: `util/utl_err.cpp`

`idl_error_header` fonksiyonunda NULL pointer kontrolü eklendi. Bazı hata durumlarında dosya adı bilgisi NULL olabilmektedir:

```cpp
// Değişiklik öncesi
s->get_string()  // s NULL olabilir

// Değişiklik sonrası  
const char *filename = "unknown";
if (s != 0)
    filename = s->get_string();
```

### Dosya 4: `fe/lex.yy.cpp`

`idl_parse_line_and_file` fonksiyonu GCC'nin ürettiği özel direktifleri handle edecek şekilde güncellendi. Satır numarası 0 olan direktifler satır 1 olarak yorumlanmakta, özel dosya isimleri ise yok sayılmaktadır.

### Dosya 5: `be/be_codegen.cpp`

`TAO_CodeGen` destructor'ında tüm stream pointer'ları için NULL kontrolü eklendi:

```cpp
// Değişiklik öncesi
delete this->client_header_;

// Değişiklik sonrası
if (this->client_header_) {
    delete this->client_header_;
    this->client_header_ = 0;
}
```

### Dosya 6: `be/be_helper.cpp` ve `be_include/be_helper.h`

`TAO_OutStream` sınıfına `close()` metodu eklendi:

```cpp
void TAO_OutStream::close (void)
{
    if (this->fp_ != 0) {
        ACE_OS::fclose (this->fp_);
        this->fp_ = 0;
    }
}
```

Bu metot dosyayı kapatır ve internal pointer'ı NULL yapar. Böylece destructor'da tekrar kapatma girişimi yapılmaz.

### Dosya 7: `be/be_interface.cpp`

gperf geçici dosyasının kapatılması sırasında doğrudan `fclose()` yerine yeni eklenen `close()` metodu kullanılacak şekilde değiştirildi:

```cpp
// Değişiklik öncesi
ACE_OS::fclose (tao_cg->gperf_input_stream ()->file ());

// Değişiklik sonrası
tao_cg->gperf_input_stream ()->close ();
```

Eski kod dosyayı kapatıyor ancak stream nesnesinin internal `fp_` pointer'ını NULL yapmıyordu. Daha sonra aynı `FILE*` değeri başka bir dosya için yeniden kullanıldığında ve stream destructor'ı çağrıldığında double free hatası oluşuyordu.

## Derleme Talimatları

```bash
export ACE_ROOT=/path/to/ACE_wrappers
export TAO_ROOT=$ACE_ROOT/TAO
cd $TAO_ROOT/TAO_IDL

# Frontend kütüphanesi
make -f Makefile.FE clean
make -f Makefile.FE

# Backend kütüphanesi
make -f Makefile.BE clean
make -f Makefile.BE

# Çalıştırılabilir dosya
make -f Makefile.EXE clean
make -f Makefile.EXE
```

## Kullanım

```bash
export LD_LIBRARY_PATH=$ACE_ROOT/ace:$TAO_ROOT/TAO_IDL:$LD_LIBRARY_PATH
$TAO_ROOT/TAO_IDL/tao_idl dosya.idl
```

## Test

```bash
# Basit test
cat > test.idl << 'EOF'
module Test {
    interface Hello {
        void say_hello();
    };
};
EOF

$TAO_ROOT/TAO_IDL/tao_idl test.idl
ls -la test*.cpp test*.h
```

## Notlar

- Bu değişiklikler ACE 5.4 sürümü için hazırlanmıştır
- GCC 14.3.1 ile test edilmiştir
- Değişiklikler geriye dönük uyumludur; Sun CC ile derleme etkilenmez
- `y.tab.cpp` dosyası Bison/Yacc tarafından `idl.yy`'den üretilmektedir; kalıcı değişiklik için `idl.yy` dosyası da güncellenmelidir
- `lex.yy.cpp` dosyası Flex tarafından `idl.ll`'den üretilmektedir; ancak modern Flex sürümleri uyumsuz kod ürettiğinden doğrudan `lex.yy.cpp` üzerinde değişiklik yapılmıştır

## Referanslar

- ACE/TAO Documentation: http://www.dre.vanderbilt.edu/~schmidt/ACE.html
- GCC Preprocessor Output: https://gcc.gnu.org/onlinedocs/cpp/Preprocessor-Output.html
