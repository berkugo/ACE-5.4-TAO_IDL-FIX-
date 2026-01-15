//
// interceptors_exceptlist.h,v 1.4 2002/09/25 16:25:38 parsons Exp
//

// ============================================================================
//
// = LIBRARY
//    TAO IDL
//
// = FILENAME
//    operation_interceptors_exceptlist.h
//
// = DESCRIPTION
//    Visitor for generating code for exceptionlist for interceptors
//
// = AUTHOR
//    Kirthika Parameswaran  <kirthika@cs.wustl.edu>
//
// ============================================================================

#ifndef _BE_VISITOR_OPERATION_OPERATION_INTERCEPTORS_EXCEPTLIST_H_
#define _BE_VISITOR_OPERATION_OPERATION_INTERCEPTORS_EXCEPTLIST_H_


class be_visitor_operation_interceptors_exceptlist : public be_visitor_operation
{
  //
  // = TITLE
  //   be_visitor_operation_interceptors_exceptlist
  //
  // = DESCRIPTION
  //   This is a concrete visitor to generate exceptionlist for interceptors
  //
  //
public:
  be_visitor_operation_interceptors_exceptlist (be_visitor_context *ctx);
  // constructor

  ~be_visitor_operation_interceptors_exceptlist (void);
  // destructor

  virtual int visit_operation (be_operation *node);
  // visit operation.
 protected:
  virtual int gen_exceptlist (be_operation *node);
};



#endif /* _BE_VISITOR_OPERATION_OPERATION_INTERCEPTORS_EXCEPTLIST_H_ */
