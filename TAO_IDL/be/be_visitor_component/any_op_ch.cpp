//
// any_op_ch.cpp,v 1.2 2003/03/12 16:50:33 parsons Exp
//

// ============================================================================
//
// = LIBRARY
//    TAO IDL
//
// = FILENAME
//    any_op_ch.cpp
//
// = DESCRIPTION
//    Visitor generating code for Any operators for an Component in the client
//    header.
//
// = AUTHOR
//    Jeff Parsons
//
// ============================================================================

ACE_RCSID (be_visitor_component, 
           any_op_ch, 
           "any_op_ch.cpp,v 1.2 2003/03/12 16:50:33 parsons Exp")

// ***************************************************************************
// Interface visitor for generating Any operator declarations in the client header
// ***************************************************************************

be_visitor_component_any_op_ch::be_visitor_component_any_op_ch
(be_visitor_context *ctx)
  : be_visitor_component (ctx)
{
}

be_visitor_component_any_op_ch::~be_visitor_component_any_op_ch (void)
{
}

int
be_visitor_component_any_op_ch::visit_component (be_component *node)
{
  be_visitor_context ctx (*this->ctx_);
  be_visitor_interface_any_op_ch visitor (&ctx);
  return visitor.visit_interface (node);
}
