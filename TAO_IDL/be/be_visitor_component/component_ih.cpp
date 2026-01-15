// component_ih.cpp,v 1.2 2003/03/12 16:50:33 parsons Exp

// ============================================================================
//
// = LIBRARY
//    TAO IDL
//
// = FILENAME
//    component_ih.cpp
//
// = DESCRIPTION
//    Visitor generating code for Interfaces in the implementation header
//
// = AUTHOR
//   Jeff Parsons
//
// ============================================================================

ACE_RCSID (be_visitor_component, 
           component_ih, 
           "component_ih.cpp,v 1.2 2003/03/12 16:50:33 parsons Exp")

// ************************************************************
// Interface visitor for implementation header.
// ************************************************************

be_visitor_component_ih::be_visitor_component_ih (be_visitor_context *ctx)
  : be_visitor_component (ctx)
{
}

be_visitor_component_ih::~be_visitor_component_ih (void)
{
}

int
be_visitor_component_ih::visit_component (be_component *node)
{
  be_visitor_context ctx (*this->ctx_);
  be_visitor_interface_ih visitor (&ctx);
  return visitor.visit_interface (node);
}
