//
// sequence_ci.cpp,v 1.29 2003/04/22 20:50:06 bala Exp
//

// ============================================================================
//
// = LIBRARY
//    TAO IDL
//
// = FILENAME
//    sequence_ci.cpp
//
// = DESCRIPTION
//    Visitor generating code for Sequence in the client inline file
//
// = AUTHOR
//    Aniruddha Gokhale
//
// ============================================================================

ACE_RCSID (be_visitor_sequence,
           sequence_ci,
           "sequence_ci.cpp,v 1.29 2003/04/22 20:50:06 bala Exp")

// ***********************************************************
// Sequence visitor for inline generation.
// ***********************************************************


be_visitor_sequence_ci::be_visitor_sequence_ci (be_visitor_context *ctx)
  : be_visitor_decl (ctx)
{
}

be_visitor_sequence_ci::~be_visitor_sequence_ci (void)
{
}

int
be_visitor_sequence_ci::visit_sequence (be_sequence *node)
{
  if (node->cli_inline_gen () || node->imported ())
    {
      return 0;
    }

  node->cli_inline_gen (1);
  return 0;
}
