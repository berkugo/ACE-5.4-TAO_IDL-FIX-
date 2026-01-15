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
//    Visitor generating code for CDR operators for forward declared
//    components. This uses compiled marshaling.
//
// = AUTHOR
//    Jeff Parsons
//
// ============================================================================

ACE_RCSID (be_visitor_component_fwd, 
           cdr_op_ch, 
           "cdr_op_ch.cpp,v 1.2 2003/03/12 16:50:33 parsons Exp")

// ***************************************************************************
// Forward declared component visitor for generating CDR operator declarations
// in the client header. Called if this node is not later defined in the file.
// ***************************************************************************

be_visitor_component_fwd_cdr_op_ch::be_visitor_component_fwd_cdr_op_ch (
    be_visitor_context *ctx
  )
  : be_visitor_decl (ctx)
{
}

be_visitor_component_fwd_cdr_op_ch::~be_visitor_component_fwd_cdr_op_ch (void)
{
}

int
be_visitor_component_fwd_cdr_op_ch::visit_component_fwd (be_component_fwd *node)
{
  be_visitor_context ctx (*this->ctx_);
  be_visitor_interface_fwd_cdr_op_ch visitor (&ctx);
  return visitor.visit_interface_fwd (node);
}
