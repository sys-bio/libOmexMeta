/**
 * @file CaListOfContents.cpp
 * @brief Implementation of the CaListOfContents class.
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
#include <omex/CaListOfContents.h>
#include <sbml/xml/XMLInputStream.h>


using namespace std;



LIBCOMBINE_CPP_NAMESPACE_BEGIN




#ifdef __cplusplus


/*
 * Creates a new CaListOfContents instance.
 */
CaListOfContents::CaListOfContents()
  : CaListOf(1, 1)
{
}


/*
 * Creates a new CaListOfContents using the given CaNamespaces object @p
 * omexns.
 */
CaListOfContents::CaListOfContents(CaNamespaces *omexns)
  : CaListOf(omexns)
{
  setElementNamespace(omexns->getURI());
}


/*
 * Copy constructor for CaListOfContents.
 */
CaListOfContents::CaListOfContents(const CaListOfContents& orig)
  : CaListOf( orig )
{
}


/*
 * Assignment operator for CaListOfContents.
 */
CaListOfContents&
CaListOfContents::operator=(const CaListOfContents& rhs)
{
  if (&rhs != this)
  {
    CaListOf::operator=(rhs);
  }

  return *this;
}


/*
 * Creates and returns a deep copy of this CaListOfContents object.
 */
CaListOfContents*
CaListOfContents::clone() const
{
  return new CaListOfContents(*this);
}


/*
 * Destructor for CaListOfContents.
 */
CaListOfContents::~CaListOfContents()
{
}


/*
 * Get a CaContent from the CaListOfContents.
 */
CaContent*
CaListOfContents::get(unsigned int n)
{
  return static_cast<CaContent*>(CaListOf::get(n));
}


/*
 * Get a CaContent from the CaListOfContents.
 */
const CaContent*
CaListOfContents::get(unsigned int n) const
{
  return static_cast<const CaContent*>(CaListOf::get(n));
}


/*
 * Get a CaContent from the CaListOfContents based on its identifier.
 */
CaContent*
CaListOfContents::get(const std::string& sid)
{
  return const_cast<CaContent*>(static_cast<const
    CaListOfContents&>(*this).get(sid));
}


/*
 * Get a CaContent from the CaListOfContents based on its identifier.
 */
const CaContent*
CaListOfContents::get(const std::string& sid) const
{
  vector<CaBase*>::const_iterator result;
  result = find_if(mItems.begin(), mItems.end(), CaIdEq<CaContent>(sid));
  return (result == mItems.end()) ? 0 : static_cast <const CaContent*>
    (*result);
}


/*
 * Removes the nth CaContent from this CaListOfContents and returns a pointer
 * to it.
 */
CaContent*
CaListOfContents::remove(unsigned int n)
{
  return static_cast<CaContent*>(CaListOf::remove(n));
}


/*
 * Removes the CaContent from this CaListOfContents based on its identifier and
 * returns a pointer to it.
 */
CaContent*
CaListOfContents::remove(const std::string& sid)
{
  CaBase* item = NULL;
  vector<CaBase*>::iterator result;

  result = find_if(mItems.begin(), mItems.end(), CaIdEq<CaContent>(sid));

  if (result != mItems.end())
  {
    item = *result;
    mItems.erase(result);
  }

  return static_cast <CaContent*> (item);
}


/*
 * Adds a copy of the given CaContent to this CaListOfContents.
 */
int
CaListOfContents::addContent(const CaContent* cc)
{
  if (cc == NULL)
  {
    return LIBCOMBINE_OPERATION_FAILED;
  }
  else if (cc->hasRequiredAttributes() == false)
  {
    return LIBCOMBINE_INVALID_OBJECT;
  }
  else if (getLevel() != cc->getLevel())
  {
    return LIBCOMBINE_LEVEL_MISMATCH;
  }
  else if (getVersion() != cc->getVersion())
  {
    return LIBCOMBINE_VERSION_MISMATCH;
  }
  else if (matchesRequiredCaNamespacesForAddition(static_cast<const
    CaBase*>(cc)) == false)
  {
    return LIBCOMBINE_NAMESPACES_MISMATCH;
  }
  else
  {
    return append(cc);
  }
}


/*
 * Get the number of CaContent objects in this CaListOfContents.
 */
unsigned int
CaListOfContents::getNumContents() const
{
  return size();
}


/*
 * Creates a new CaContent object, adds it to this CaListOfContents object and
 * returns the CaContent object created.
 */
CaContent*
CaListOfContents::createContent()
{
  CaContent* cc = NULL;

  try
  {
    cc = new CaContent(getCaNamespaces());
  }
  catch (...)
  {
  }

  if (cc != NULL)
  {
    appendAndOwn(cc);
  }

  return cc;
}


/*
 * Returns the XML element name of this CaListOfContents object.
 */
const std::string&
CaListOfContents::getElementName() const
{
  static const string name = "listOfContents";
  return name;
}


/*
 * Returns the libCombine type code for this CaListOfContents object.
 */
int
CaListOfContents::getTypeCode() const
{
  return OMEX_LIST_OF;
}


/*
 * Returns the libOMEX type code for the OMEX objects contained in this
 * CaListOfContents object.
 */
int
CaListOfContents::getItemTypeCode() const
{
  return LIB_COMBINE_CONTENT;
}



/** @cond doxygenlibCombineInternal */

/*
 * Creates a new CaContent in this CaListOfContents
 */
CaBase*
CaListOfContents::createObject(LIBSBML_CPP_NAMESPACE_QUALIFIER XMLInputStream&
  stream)
{
  const std::string& name = stream.peek().getName();
  CaBase* object = NULL;

  if (name == "content")
  {
    object = new CaContent(getCaNamespaces());
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
CaListOfContents::writeXMLNS(LIBSBML_CPP_NAMESPACE_QUALIFIER XMLOutputStream&
  stream) const
{
  LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces xmlns;
  std::string prefix = getPrefix();

  if (prefix.empty())
  {
    const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces* thisxmlns =
      getNamespaces();
    if (thisxmlns && thisxmlns->hasURI(OMEX_XMLNS_L1V1))
    {
      xmlns.add(OMEX_XMLNS_L1V1, prefix);
    }
  }

  stream << xmlns;
}

/** @endcond */




#endif /* __cplusplus */


/*
 * Get a CaContent_t from the CaListOf_t.
 */
LIBCOMBINE_EXTERN
CaContent_t*
CaListOfContents_getContent(CaListOf_t* clo, unsigned int n)
{
  if (clo == NULL)
  {
    return NULL;
  }

  return static_cast <CaListOfContents*>(clo)->get(n);
}


/*
 * Get a CaContent_t from the CaListOf_t based on its identifier.
 */
LIBCOMBINE_EXTERN
CaContent_t*
CaListOfContents_getById(CaListOf_t* clo, const char *sid)
{
  if (clo == NULL)
  {
    return NULL;
  }

  return (sid != NULL) ? static_cast <CaListOfContents*>(clo)->get(sid) : NULL;
}


/*
 * Removes the nth CaContent_t from this CaListOf_t and returns a pointer to
 * it.
 */
LIBCOMBINE_EXTERN
CaContent_t*
CaListOfContents_remove(CaListOf_t* clo, unsigned int n)
{
  if (clo == NULL)
  {
    return NULL;
  }

  return static_cast <CaListOfContents*>(clo)->remove(n);
}


/*
 * Removes the CaContent_t from this CaListOf_t based on its identifier and
 * returns a pointer to it.
 */
LIBCOMBINE_EXTERN
CaContent_t*
CaListOfContents_removeById(CaListOf_t* clo, const char* sid)
{
  if (clo == NULL)
  {
    return NULL;
  }

  return (sid != NULL) ? static_cast <CaListOfContents*>(clo)->remove(sid) :
    NULL;
}




LIBCOMBINE_CPP_NAMESPACE_END


