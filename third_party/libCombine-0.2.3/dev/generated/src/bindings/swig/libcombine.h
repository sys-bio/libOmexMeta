/**
 * @file libcombine.h
 * @brief Definition of the libcombine class.
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



#include <omex/common/libcombine-version.h>
#include <omex/common/CaOperationReturnValues.h>

#include <omex/CaTypes.h>

#include "ListWrapper.h"

#include <sbml/SyntaxChecker.h>
#include <sbml/ExpectedAttributes.h>
#include <sbml/SBase.h>

#include <sbml/math/MathML.h>
#include <sbml/math/ASTNode.h>
#include <sbml/math/FormulaParser.h>
#include <sbml/math/FormulaFormatter.h>
#include <sbml/math/L3Parser.h>
#include <sbml/math/L3ParserSettings.h>

#include <sbml/xml/XMLAttributes.h>
#include <sbml/xml/XMLNamespaces.h>
#include <sbml/xml/XMLConstructorException.h>
#include <sbml/xml/XMLToken.h>
#include <sbml/xml/XMLNode.h>
#include <sbml/xml/XMLTriple.h>
#include <sbml/xml/XMLInputStream.h>
#include <sbml/xml/XMLOutputStream.h>
#include <sbml/xml/XMLError.h>
#include <sbml/xml/XMLErrorLog.h>


