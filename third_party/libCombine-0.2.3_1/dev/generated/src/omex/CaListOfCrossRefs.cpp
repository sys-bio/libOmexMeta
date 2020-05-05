/**
 * @file CaListOfCrossRefs.cpp
 * @brief Implementation of the CaListOfCrossRefs class.
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
#include <omex/CaListOfCrossRefs.h>
#include <sbml/xml/XMLInputStream.h>


using namespace std;



LIBCOMBINE_CPP_NAMESPACE_BEGIN




#ifdef __cplusplus


/*
 * Creates a new CaListOfCrossRefs instance.
 */
CaListOfCrossRefs::CaListOfCrossRefs()
  : CaListOf(1, 1)
{
}


/*
 * Creates a new CaListOfCrossRefs using the given CaNamespaces object @p
 * omexns.
 */
CaListOfCrossRefs::CaListOfCrossRefs(CaNamespaces *omexns)
  : CaListOf(omexns)
{
  setElementNamespace(omexns->getURI());
}


/*
 * Copy constructor for CaListOfCrossRefs.
 */
CaListOfCrossRefs::CaListOfCrossRefs(const CaListOfCrossRefs& orig)
  : CaListOf( orig )
{
}


/*
 * Assignment operator for CaListOfCrossRefs.
 */
CaListOfCrossRefs&
CaListOfCrossRefs::operator=(const CaListOfCrossRefs& rhs)
{
  if (&rhs != this)
  {
    CaListOf::operator=(rhs);
  }

  return *this;
}


/*
 * Creates and returns a deep copy of this CaListOfCrossRefs object.
 */
CaListOfCrossRefs*
CaListOfCrossRefs::clone() const
{
  return new CaListOfCrossRefs(*this);
}


/*
 * Destructor for CaListOfCrossRefs.
 */
CaListOfCrossRefs::~CaListOfCrossRefs()
{
}


/*
 * Get a CaCrossRef from the CaListOfCrossRefs.
 */
CaCrossRef*
CaListOfCrossRefs::get(unsigned int n)
{
  return static_cast<CaCrossRef*>(CaListOf::get(n));
}


/*
 * Get a CaCrossRef from the CaListOfCrossRefs.
 */
const CaCrossRef*
CaListOfCrossRefs::get(unsigned int n) const
{
  return static_cast<const CaCrossRef*>(CaListOf::get(n));
}


/*
 * Get a CaCrossRef from the CaListOfCrossRefs based on its identifier.
 */
CaCrossRef*
CaListOfCrossRefs::get(const std::string& sid)
{
  return const_cast<CaCrossRef*>(static_cast<const
    CaListOfCrossRefs&>(*this).get(sid));
}


/*
 * Get a CaCrossRef from the CaListOfCrossRefs based on its identifier.
 */
const CaCrossRef*
CaListOfCrossRefs::get(const std::string& sid) const
{
  vector<CaBase*>::const_iterator result;
  result = find_if(mItems.begin(), mItems.end(), CaIdEq<CaCrossRef>(sid));
  return (result == mItems.end()) ? 0 : static_cast <const CaCrossRef*>
    (*result);
}


/*
 * Removes the nth CaCrossRef from this CaListOfCrossRefs and returns a pointer
 * to it.
 */
CaCrossRef*
CaListOfCrossRefs::remove(unsigned int n)
{
  return static_cast<CaCrossRef*>(CaListOf::remove(n));
}


/*
 * Removes the CaCrossRef from this CaListOfCrossRefs based on its identifier
 * and returns a pointer to it.
 */
CaCrossRef*
CaListOfCrossRefs::remove(const std::string& sid)
{
  CaBase* item = NULL;
  vector<CaBase*>::iterator result;

  result = find_if(mItems.begin(), mItems.end(), CaIdEq<CaCrossRef>(sid));

  if (result != mItems.end())
  {
    item = *result;
    mItems.erase(result);
  }

  return static_cast <CaCrossRef*> (item);
}


/*
 * Adds a copy of the given CaCrossRef to this CaListOfCrossRefs.
 */
int
CaListOfCrossRefs::addCrossRef(const CaCrossRef* ccr)
{
  if (ccr == NULL)
  {
    return LIBCOMBINE_OPERATION_FAILED;
  }
  else if (ccr->hasRequiredAttributes() == false)
  {
    return LIBCOMBINE_INVALID_OBJECT;
  }
  else if (getLevel() != ccr->getLevel())
  {
    return LIBCOMBINE_LEVEL_MISMATCH;
  }
  else if (getVersion() != ccr->getVersion())
  {
    return LIBCOMBINE_VERSION_MISMATCH;
  }
  else if (matchesRequiredCaNamespacesForAddition(static_cast<const
    CaBase*>(ccr)) == false)
  {
    return LIBCOMBINE_NAMESPACES_MISMATCH;
  }
  else
  {
    return append(ccr);
  }
}


/*
 * Get the number of CaCrossRef objects in this CaListOfCrossRefs.
 */
unsigned int
CaListOfCrossRefs::getNumCrossRefs() const
{
  return size();
}


/*
 * Creates a new CaCrossRef object, adds it to this CaListOfCrossRefs object
 * and returns the CaCrossRef object created.
 */
CaCrossRef*
CaListOfCrossRefs::createCrossRef()
{
  CaCrossRef* ccr = NULL;

  try
  {
    ccr = new CaCrossRef(getCaNamespaces());
  }
  catch (...)
  {
  }

  if (ccr != NULL)
  {
    appendAndOwn(ccr);
  }

  return ccr;
}


/*
 * Returns the XML element name of this CaListOfCrossRefs object.
 */
const std::string&
CaListOfCrossRefs::getElementName() const
{
  static const string name = "listOfCrossRefs";
  return name;
}


/*
 * Returns the libCombine type code for this CaListOfCrossRefs object.
 */
int
CaListOfCrossRefs::getTypeCode() const
{
  return OMEX_LIST_OF;
}


/*
 * Returns the libOMEX type code for the OMEX objects contained in this
 * CaListOfCrossRefs object.
 */
int
CaListOfCrossRefs::getItemTypeCode() const
{
  return LIB_COMBINE_CROSSREF;
}



/** @cond doxygenlibCombineInternal */

/*
 * Creates a new CaCrossRef in this CaListOfCrossRefs
 */
CaBase*
CaListOfCrossRefs::createObject(LIBSBML_CPP_NAMESPACE_QUALIFIER XMLInputStream&
  stream)
{
  const std::string& name = stream.peek().getName();
  CaBase* object = NULL;

  if (name == "crossRef")
  {
    object = new CaCrossRef(getCaNamespaces());
    appendAndOwn(object);
  }

  return object;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Writes the namespace for the Combine package
 */
void
CaListOfCrossRefs::writeXMLNS(LIBSBML_CPP_NAMESPACE_QUALIFIER XMLOutputStream&
  stream) const
{
  LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces xmlns;
  std::string prefix = getPrefix();

  if (prefix.empty())
  {
    const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces* thisxmlns =
      getNamespaces();
    if (thisxmlns && thisxmlns->hasURI(OMEX_XMLNS_L3V1))
    {
      xmlns.add(OMEX_XMLNS_L3V1, prefix);
    }
  }

  stream << xmlns;
}

/** @endcond */




#endif /* __cplusplus */


/*
 * Get a CaCrossRef_t from the CaListOf_t.
 */
LIBCOMBINE_EXTERN
CaCrossRef_t*
CaListOfCrossRefs_getCrossRef(CaListOf_t* clo, unsigned int n)
{
  if (clo == NULL)
  {
    return NULL;
  }

  return static_cast <CaListOfCrossRefs*>(clo)->get(n);
}


/*
 * Get a CaCrossRef_t from the CaListOf_t based on its identifier.
 */
LIBCOMBINE_EXTERN
CaCrossRef_t*
CaListOfCrossRefs_getById(CaListOf_t* clo, const char *sid)
{
  if (clo == NULL)
  {
    return NULL;
  }

  return (sid != NULL) ? static_cast <CaListOfCrossRefs*>(clo)->get(sid) :
    NULL;
}


/*
 * Removes the nth CaCrossRef_t from this CaListOf_t and returns a pointer to
 * it.
 */
LIBCOMBINE_EXTERN
CaCrossRef_t*
CaListOfCrossRefs_remove(CaListOf_t* clo, unsigned int n)
{
  if (clo == NULL)
  {
    return NULL;
  }

  return static_cast <CaListOfCrossRefs*>(clo)->remove(n);
}


/*
 * Removes the CaCrossRef_t from this CaListOf_t based on its identifier and
 * returns a pointer to it.
 */
LIBCOMBINE_EXTERN
CaCrossRef_t*
CaListOfCrossRefs_removeById(CaListOf_t* clo, const char* sid)
{
  if (clo == NULL)
  {
    return NULL;
  }

  return (sid != NULL) ? static_cast <CaListOfCrossRefs*>(clo)->remove(sid) :
    NULL;
}




LIBCOMBINE_CPP_NAMESPACE_END


