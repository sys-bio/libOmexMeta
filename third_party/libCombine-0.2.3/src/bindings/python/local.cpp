/**
* @file    local.cpp
* @brief   Python-specific SWIG support code for wrapping libSBML API
* @author  Ben Bornstein
* @author  Ben Kovitz
*
* <!--------------------------------------------------------------------------
* This file is part of libSBML.  Please visit http://sbml.org for more
* information about SBML, and the latest version of libSBML.
*
* Copyright (C) 2009-2013 jointly by the following organizations: 
*     1. California Institute of Technology, Pasadena, CA, USA
*     2. EMBL European Bioinformatics Institute (EBML-EBI), Hinxton, UK
*  
* Copyright (C) 2006-2008 by the California Institute of Technology,
*     Pasadena, CA, USA 
*  
* Copyright (C) 2002-2005 jointly by the following organizations: 
*     1. California Institute of Technology, Pasadena, CA, USA
*     2. Japan Science and Technology Agency, Japan
* 
* This library is free software; you can redistribute it and/or modify it
* under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation.  A copy of the license agreement is provided
* in the file named "LICENSE.txt" included with this software distribution
* and also available online as http://sbml.org/software/libsbml/license.html
* ---------------------------------------------------------------------- -->*/

#include <cstddef>
#include "omex/CaBase.h"

/**
* @return the most specific Swig type for the given SedBase object.
*/
struct swig_type_info*
GetDowncastSwigType (CaBase* sb)
{
  if (sb == 0) return SWIGTYPE_p_CaBase;

  std::string name;
  switch( sb->getTypeCode() )
    {
    case LIB_COMBINE_OMEXMANIFEST:
      return SWIGTYPE_p_CaOmexManifest;
      
    case LIB_COMBINE_CONTENT:
      return SWIGTYPE_p_CaContent;

    case OMEX_LIST_OF:
      name = sb->getElementName();
      if(name == "listOf")
      {
        return SWIGTYPE_p_CaListOf;
      }
      else if (name == "listOfContents")
      {
        return SWIGTYPE_p_CaListOfContents;
      }
      
        return SWIGTYPE_p_CaListOf;
      
    default:
      return SWIGTYPE_p_CaBase;
    } 
}

/* Compatibility bug fix for swig 2.0.7 and Python 3. 
* See http://patch-tracker.debian.org/patch/series/view/swig2.0/2.0.7-3/pyint_fromsize_t.diff
*/
#if (PY_MAJOR_VERSION >= 3)
#define PyInt_FromSize_t(x) PyLong_FromSize_t(x)
#endif
