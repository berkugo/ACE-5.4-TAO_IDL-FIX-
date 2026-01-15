//
// cdr_op_ch.cpp,v 1.2 2003/03/12 16:50:33 parsons Exp
//

// ============================================================================
//
// = LIBRARY
//    TAO IDL
//
// = FILENAME
//    cdr_op_ch.cpp
//
// = DESCRIPTION
//    Visitor generating CDR operators for Eventtypes in the client header
//
// = AUTHOR
//    Jeff Parsons
//
// ============================================================================

ACE_RCSID (be_visitor_eventtype, 
           cdr_op_ch, 
           "cdr_op_ch.cpp,v 1.2 2003/03/12 16:50:33 parsons Exp")

// ******************************************************
// Eventtype visitor for CDR operators in the client header
// ******************************************************

be_visitor_eventtype_cdr_op_ch::be_visitor_eventtype_cdr_op_ch (
    be_visitor_context *ctx
  )
  : be_visitor_valuetype (ctx)
{
}

be_visitor_eventtype_cdr_op_ch::~be_visitor_eventtype_cdr_op_ch (void)
{
}

int
be_visitor_eventtype_cdr_op_ch::visit_eventtype (be_eventtype *node)
{
  be_visitor_context ctx (*this->ctx_);
  be_visitor_valuetype_cdr_op_ch visitor (&ctx);
  return visitor.visit_valuetype (node);
}
