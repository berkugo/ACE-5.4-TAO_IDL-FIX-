//
// component_ss.cpp,v 1.3 2003/03/12 16:50:33 parsons Exp
//

// ============================================================================
//
// = LIBRARY
//    TAO IDL
//
// = FILENAME
//    component_si.cpp
//
// = DESCRIPTION
//    Visitor generating code for Components in the server skeleton.
//
// = AUTHOR
//    Jeff Parsons
//
// ============================================================================

ACE_RCSID (be_visitor_component,
           component_ss,
           "component_ss.cpp,v 1.3 2003/03/12 16:50:33 parsons Exp")

// ******************************************************
// Component visitor for server skeleton
// ******************************************************

be_visitor_component_ss::be_visitor_component_ss (be_visitor_context *ctx)
  : be_visitor_component (ctx)
{
}

be_visitor_component_ss::~be_visitor_component_ss (void)
{
}

int
be_visitor_component_ss::visit_component (be_component *node)
{
  be_visitor_context ctx (*this->ctx_);
  be_visitor_interface_ss visitor (&ctx);
  return visitor.visit_interface (node);
}
