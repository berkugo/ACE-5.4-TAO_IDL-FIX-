//
// valuetype_si.cpp,v 1.3 2002/07/01 15:54:11 coryan Exp
//

// ============================================================================
//
// = LIBRARY
//    TAO IDL
//
// = FILENAME
//    valuetype_si.cpp
//
// = DESCRIPTION
//    Visitor generating code for Interfaces in the server inline file
//
// = AUTHOR
//    Jeff Parsons
//
// ============================================================================

ACE_RCSID (be_visitor_valuetype,
           valuetype_si,
           "valuetype_si.cpp,v 1.3 2002/07/01 15:54:11 coryan Exp")


// ************************************************************************
// Valuetype visitor for server inline
// ************************************************************************

be_visitor_valuetype_si::be_visitor_valuetype_si (be_visitor_context *ctx)
  : be_visitor_valuetype (ctx)
{
}

be_visitor_valuetype_si::~be_visitor_valuetype_si (void)
{
}

int
be_visitor_valuetype_si::visit_valuetype (be_valuetype *)
{
  // Nothing needed for now, but the visitor is here just in case.
  return 0;
}
