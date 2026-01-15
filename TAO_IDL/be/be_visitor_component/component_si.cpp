//
// component_si.cpp,v 1.2 2003/03/12 16:50:33 parsons Exp
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
//    Visitor generating code for Components in the server inline.
//
// = AUTHOR
//    Jeff Parsons
//
// ============================================================================

ACE_RCSID (be_visitor_component,
           component_si,
           "component_si.cpp,v 1.2 2003/03/12 16:50:33 parsons Exp")

// ******************************************************
// Component visitor for server inline
// ******************************************************

be_visitor_component_si::be_visitor_component_si (be_visitor_context *ctx)
  : be_visitor_component (ctx)
{
}

be_visitor_component_si::~be_visitor_component_si (void)
{
}

int
be_visitor_component_si::visit_component (be_component *node)
{
  be_visitor_context ctx (*this->ctx_);
  be_visitor_interface_si visitor (&ctx);
  return visitor.visit_interface (node);
}
