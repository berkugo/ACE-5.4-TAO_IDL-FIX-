//
// be_union_label.cpp,v 1.9 2003/06/17 15:09:23 parsons Exp
//

#include "be_union_label.h"
#include "be_visitor.h"

ACE_RCSID (be, 
           be_union_label, 
           "be_union_label.cpp,v 1.9 2003/06/17 15:09:23 parsons Exp")

be_union_label::be_union_label (void)
  : AST_UnionLabel ()
{
}

be_union_label::be_union_label (AST_UnionLabel::UnionLabel ul,
			                          AST_Expression *v)
  : AST_UnionLabel (ul,
                    v)
{
}

int
be_union_label::accept (be_visitor *visitor)
{
  return visitor->visit_union_label (this);
}
