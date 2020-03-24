/**
 * @file CaConstructorException.cpp
 * @brief Implementation of the CaConstructorException class.
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


#include <omex/CaConstructorException.h>

#include <omex/CaNamespaces.h>
#include <sbml/xml/XMLNamespaces.h>
#include <sbml/xml/XMLOutputStream.h>

#include <string>
#include <sstream>

LIBCOMBINE_CPP_NAMESPACE_BEGIN


/** @cond doxygenLibomexInternal */

CaConstructorException::CaConstructorException(std::string errmsg) :
      std::invalid_argument("Level/version/namespaces combination is invalid")
    , mCaErrMsg(errmsg)
{
}


CaConstructorException::CaConstructorException (std::string errmsg, std::string omexErrMsg) :
    std::invalid_argument(errmsg)
  , mCaErrMsg(omexErrMsg)
{
}


CaConstructorException::CaConstructorException (std::string elementName, CaNamespaces* omexns) :
    std::invalid_argument("Level/version/namespaces combination is invalid")
  , mCaErrMsg(elementName)
{
  if (omexns == NULL) return;
  
  XMLNamespaces* xmlns = omexns->getNamespaces();
  
  if (xmlns == NULL) return;
    
  std::ostringstream oss;
  XMLOutputStream xos(oss);
  xos << *xmlns;
  mCaErrMsg.append(oss.str());
  
}


CaConstructorException::~CaConstructorException() throw()
{
}

/** @endcond */

LIBCOMBINE_CPP_NAMESPACE_END

