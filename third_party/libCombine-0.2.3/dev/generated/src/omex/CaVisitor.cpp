/**
 * @file CaVisitor.cpp
 * @brief Implementation of the CaVisitor class.
 * @author DEVISER
 *
 * <!--------------------------------------------------------------------------
 * This file is part of libSBML. Please visit http://sbml.org for more
 * information about SBML, and the latest version of libSBML.
 *
 * Copyright (C) 2019 jointly by the following organizations:
 * 1. California Institute of Technology, Pasadena, CA, USA
 * 2. University of Heidelberg, Heidelberg, Germany
 *
 * Copyright (C) 2013-2018 jointly by the following organizations:
 * 1. California Institute of Technology, Pasadena, CA, USA
 * 2. EMBL European Bioinformatics Institute (EMBL-EBI), Hinxton, UK
 * 3. University of Heidelberg, Heidelberg, Germany
 *
 * Copyright (C) 2009-2013 jointly by the following organizations:
 * 1. California Institute of Technology, Pasadena, CA, USA
 * 2. EMBL European Bioinformatics Institute (EMBL-EBI), Hinxton, UK
 *
 * Copyright (C) 2006-2008 by the California Institute of Technology,
 * Pasadena, CA, USA
 *
 * Copyright (C) 2002-2005 jointly by the following organizations:
 * 1. California Institute of Technology, Pasadena, CA, USA
 * 2. Japan Science and Technology Agency, Japan
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation. A copy of the license agreement is provided in the
 * file named "LICENSE.txt" included with this software distribution and also
 * available online as http://sbml.org/software/libsbml/license.html
 * ------------------------------------------------------------------------ -->
 */



#include <omex/CaVisitor.h>
#include <omex/CaTypes.h>

LIBCOMBINE_CPP_NAMESPACE_BEGIN

#ifdef __cplusplus

CaVisitor::~CaVisitor ()
{
}


void
CaVisitor::visit (const CaOmexManifest& x)
{
  visit( static_cast<const CaBase&>(x) );
}


void
CaVisitor::visit (const CaListOf& x, int type)
{
  visit( static_cast<const CaBase&>(x) );
}


bool
CaVisitor::visit (const CaBase& sb)
{
  return false;
}


/*
 * Visit the CaContent
 */
bool
CaVisitor::visit(const CaContent& x)
{
  return visit(static_cast<const CaBase&>(x));
}


/*
 * Visit the CaCrossRef
 */
bool
CaVisitor::visit(const CaCrossRef& x)
{
  return visit(static_cast<const CaBase&>(x));
}


void
CaVisitor::leave (const CaOmexManifest& x)
{
}


void
CaVisitor::leave (const CaBase& sb)
{
}


void
CaVisitor::leave (const CaListOf& x, int type)
{
}


/*
 * Leave the CaContent
 */
void
CaVisitor::leave(const CaContent& x)
{
}


/*
 * Leave the CaCrossRef
 */
void
CaVisitor::leave(const CaCrossRef& x)
{
}



#endif /* __cplusplus */


LIBCOMBINE_CPP_NAMESPACE_END
