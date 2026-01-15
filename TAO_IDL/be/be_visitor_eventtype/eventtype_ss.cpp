//
// eventtype_ss.cpp,v 1.2 2003/03/12 16:50:33 parsons Exp
//

// ============================================================================
//
// = LIBRARY
//    TAO IDL
//
// = FILENAME
//    eventtype_ss.cpp
//
// = DESCRIPTION
//    Visitor generating code for Eventtypes in the server source
//
// = AUTHOR
//    Jeff Parsons
//
// ============================================================================

ACE_RCSID (be_visitor_eventtype, 
           eventtype_ss, 
           "eventtype_ss.cpp,v 1.2 2003/03/12 16:50:33 parsons Exp")

// ******************************************************
// Eventtype visitor for server source
// ******************************************************

be_visitor_eventtype_ss::be_visitor_eventtype_ss (be_visitor_context *ctx)
  : be_visitor_valuetype (ctx)
{
}

be_visitor_eventtype_ss::~be_visitor_eventtype_ss (void)
{
}

int
be_visitor_eventtype_ss::visit_eventtype (be_eventtype *node)
{
  be_visitor_context ctx (*this->ctx_);
  be_visitor_valuetype_ss visitor (&ctx);
  return visitor.visit_valuetype (node);
}
