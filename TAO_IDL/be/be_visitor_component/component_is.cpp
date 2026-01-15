// component_is.cpp,v 1.2 2003/03/12 16:50:33 parsons Exp

// ============================================================================
//
// = LIBRARY
//    TAO IDL
//
// = FILENAME
//    component_is.cpp
//
// = DESCRIPTION
//    Visitor generating code for Components 
//    in the implementation skeletons file.
//
// = AUTHOR
//   Jeff Parsons
//
// ============================================================================

// ************************************************************
// Component visitor for implementation skeletons.
// ************************************************************

ACE_RCSID (be_visitor_component, 
           component_is, 
           "component_is.cpp,v 1.2 2003/03/12 16:50:33 parsons Exp")

be_visitor_component_is::be_visitor_component_is (be_visitor_context *ctx)
  : be_visitor_component (ctx)
{
}

be_visitor_component_is::~be_visitor_component_is (void)
{
}

int
be_visitor_component_is::visit_component (be_component *node)
{
  be_visitor_context ctx (*this->ctx_);
  be_visitor_interface_is visitor (&ctx);
  return visitor.visit_interface (node);
}
