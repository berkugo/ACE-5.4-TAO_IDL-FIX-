
//
// eventtype_obv_ci.cpp,v 1.2 2003/03/12 16:50:33 parsons Exp
//

// ============================================================================
//
// = LIBRARY
//    TAO IDL
//
// = FILENAME
//    eventtype_obv_ci.cpp
//
// = DESCRIPTION
//    Visitor generating code for Eventtypes in the client inline
//    OBV_ class
//    (see C++ mapping OMG 20.17)
//
// = AUTHOR
//    Jeff Parsons
//
// ============================================================================

ACE_RCSID (be_visitor_eventtype, 
           eventtype_obv_ci, 
           "eventtype_obv_ci.cpp,v 1.2 2003/03/12 16:50:33 parsons Exp")

// ******************************************************
// Eventtype visitor for client inline
// ******************************************************

be_visitor_eventtype_obv_ci::be_visitor_eventtype_obv_ci (
    be_visitor_context *ctx
  )
  : be_visitor_valuetype (ctx)
{
}

be_visitor_eventtype_obv_ci::~be_visitor_eventtype_obv_ci (void)
{
}


// OBV_ class must be in OBV_ namespace.
int
be_visitor_eventtype_obv_ci::visit_eventtype (be_eventtype *node)
{
  be_visitor_context ctx (*this->ctx_);
  be_visitor_valuetype_obv_ci visitor (&ctx);
  return visitor.visit_valuetype (node);
}
