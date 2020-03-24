/**
 * @file CaOmexManifest.cpp
 * @brief Implementation of the CaOmexManifest class.
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
#include <omex/CaOmexManifest.h>
#include <sbml/xml/XMLInputStream.h>


using namespace std;



LIBCOMBINE_CPP_NAMESPACE_BEGIN




#ifdef __cplusplus


/*
 * Creates a new CaOmexManifest instance.
 */
CaOmexManifest::CaOmexManifest()
  : CaBase(1, 1)
  , mContents ()
{
  setCaOmexManifest(this);
  connectToChild();
}


/*
 * Creates a new CaOmexManifest using the given CaNamespaces object @p omexns.
 */
CaOmexManifest::CaOmexManifest(CaNamespaces *omexns)
  : CaBase(omexns)
  , mContents (omexns)
{
  setElementNamespace(omexns->getURI());
  setCaOmexManifest(this);
  connectToChild();
}


/*
 * Copy constructor for CaOmexManifest.
 */
CaOmexManifest::CaOmexManifest(const CaOmexManifest& orig)
  : CaBase( orig )
  , mContents ( orig.mContents )
{
  setCaOmexManifest(this);

  connectToChild();
}


/*
 * Assignment operator for CaOmexManifest.
 */
CaOmexManifest&
CaOmexManifest::operator=(const CaOmexManifest& rhs)
{
  if (&rhs != this)
  {
    CaBase::operator=(rhs);
    mContents = rhs.mContents;
    connectToChild();
    setCaOmexManifest(this);
  }

  return *this;
}


/*
 * Creates and returns a deep copy of this CaOmexManifest object.
 */
CaOmexManifest*
CaOmexManifest::clone() const
{
  return new CaOmexManifest(*this);
}


/*
 * Destructor for CaOmexManifest.
 */
CaOmexManifest::~CaOmexManifest()
{
}


/*
 * Returns the CaListOfContents from this CaOmexManifest.
 */
const CaListOfContents*
CaOmexManifest::getListOfContents() const
{
  return &mContents;
}


/*
 * Returns the CaListOfContents from this CaOmexManifest.
 */
CaListOfContents*
CaOmexManifest::getListOfContents()
{
  return &mContents;
}


/*
 * Get a CaContent from the CaOmexManifest.
 */
CaContent*
CaOmexManifest::getContent(unsigned int n)
{
  return mContents.get(n);
}


/*
 * Get a CaContent from the CaOmexManifest.
 */
const CaContent*
CaOmexManifest::getContent(unsigned int n) const
{
  return mContents.get(n);
}


/*
 * Adds a copy of the given CaContent to this CaOmexManifest.
 */
int
CaOmexManifest::addContent(const CaContent* cc)
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
    return mContents.append(cc);
  }
}


/*
 * Get the number of CaContent objects in this CaOmexManifest.
 */
unsigned int
CaOmexManifest::getNumContents() const
{
  return mContents.size();
}


/*
 * Creates a new CaContent object, adds it to this CaOmexManifest object and
 * returns the CaContent object created.
 */
CaContent*
CaOmexManifest::createContent()
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
    mContents.appendAndOwn(cc);
  }

  return cc;
}


/*
 * Removes the nth CaContent from this CaOmexManifest and returns a pointer to
 * it.
 */
CaContent*
CaOmexManifest::removeContent(unsigned int n)
{
  return mContents.remove(n);
}


/*
 * Returns the XML element name of this CaOmexManifest object.
 */
const std::string&
CaOmexManifest::getElementName() const
{
  static const string name = "omexManifest";
  return name;
}


/*
 * Returns the libCombine type code for this CaOmexManifest object.
 */
int
CaOmexManifest::getTypeCode() const
{
  return LIB_COMBINE_OMEXMANIFEST;
}



/** @cond doxygenlibCombineInternal */

/*
 * Write any contained elements
 */
void
CaOmexManifest::writeElements(LIBSBML_CPP_NAMESPACE_QUALIFIER XMLOutputStream&
  stream) const
{
  CaBase::writeElements(stream);

  for (unsigned int i = 0; i < getNumContents(); i++)
  {
    getContent(i)->write(stream);
  }
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Accepts the given CaVisitor
 */
bool
CaOmexManifest::accept(CaVisitor& v) const
{
  return false;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Sets the parent CaOmexManifest
 */
void
CaOmexManifest::setCaOmexManifest(CaOmexManifest* d)
{
  CaBase::setCaOmexManifest(d);

  mContents.setCaOmexManifest(d);
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Connects to child elements
 */
void
CaOmexManifest::connectToChild()
{
  CaBase::connectToChild();

  mContents.connectToParent(this);
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Gets the value of the "attributeName" attribute of this CaOmexManifest.
 */
int
CaOmexManifest::getAttribute(const std::string& attributeName,
                             bool& value) const
{
  int return_value = CaBase::getAttribute(attributeName, value);

  return return_value;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Gets the value of the "attributeName" attribute of this CaOmexManifest.
 */
int
CaOmexManifest::getAttribute(const std::string& attributeName,
                             int& value) const
{
  int return_value = CaBase::getAttribute(attributeName, value);

  return return_value;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Gets the value of the "attributeName" attribute of this CaOmexManifest.
 */
int
CaOmexManifest::getAttribute(const std::string& attributeName,
                             double& value) const
{
  int return_value = CaBase::getAttribute(attributeName, value);

  return return_value;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Gets the value of the "attributeName" attribute of this CaOmexManifest.
 */
int
CaOmexManifest::getAttribute(const std::string& attributeName,
                             unsigned int& value) const
{
  int return_value = CaBase::getAttribute(attributeName, value);

  return return_value;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Gets the value of the "attributeName" attribute of this CaOmexManifest.
 */
int
CaOmexManifest::getAttribute(const std::string& attributeName,
                             std::string& value) const
{
  int return_value = CaBase::getAttribute(attributeName, value);

  return return_value;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Predicate returning @c true if this CaOmexManifest's attribute
 * "attributeName" is set.
 */
bool
CaOmexManifest::isSetAttribute(const std::string& attributeName) const
{
  bool value = CaBase::isSetAttribute(attributeName);

  return value;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Sets the value of the "attributeName" attribute of this CaOmexManifest.
 */
int
CaOmexManifest::setAttribute(const std::string& attributeName, bool value)
{
  int return_value = CaBase::setAttribute(attributeName, value);

  return return_value;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Sets the value of the "attributeName" attribute of this CaOmexManifest.
 */
int
CaOmexManifest::setAttribute(const std::string& attributeName, int value)
{
  int return_value = CaBase::setAttribute(attributeName, value);

  return return_value;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Sets the value of the "attributeName" attribute of this CaOmexManifest.
 */
int
CaOmexManifest::setAttribute(const std::string& attributeName, double value)
{
  int return_value = CaBase::setAttribute(attributeName, value);

  return return_value;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Sets the value of the "attributeName" attribute of this CaOmexManifest.
 */
int
CaOmexManifest::setAttribute(const std::string& attributeName,
                             unsigned int value)
{
  int return_value = CaBase::setAttribute(attributeName, value);

  return return_value;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Sets the value of the "attributeName" attribute of this CaOmexManifest.
 */
int
CaOmexManifest::setAttribute(const std::string& attributeName,
                             const std::string& value)
{
  int return_value = CaBase::setAttribute(attributeName, value);

  return return_value;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Unsets the value of the "attributeName" attribute of this CaOmexManifest.
 */
int
CaOmexManifest::unsetAttribute(const std::string& attributeName)
{
  int value = CaBase::unsetAttribute(attributeName);

  return value;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Creates and returns an new "elementName" object in this CaOmexManifest.
 */
CaBase*
CaOmexManifest::createChildObject(const std::string& elementName)
{
  CaBase* obj = NULL;

  if (elementName == "content")
  {
    return createContent();
  }

  return obj;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Adds a new "elementName" object to this CaOmexManifest.
 */
int
CaOmexManifest::addChildObject(const std::string& elementName,
                               const CaBase* element)
{
  if (elementName == "content" && element->getTypeCode() ==
    LIB_COMBINE_CONTENT)
  {
    return addContent((const CaContent*)(element));
  }

  return LIBSBML_OPERATION_FAILED;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Removes and returns the new "elementName" object with the given id in this
 * CaOmexManifest.
 */
CaBase*
CaOmexManifest::removeChildObject(const std::string& elementName,
                                  const std::string& id)
{
  if (elementName == "content")
  {
    for (unsigned int i = 0; i < getNumContents(); i++)
    {
      if (getContent(i)->getId() == id)
      {
        return removeContent(i);
      }
    }
  }

  return NULL;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Returns the number of "elementName" in this CaOmexManifest.
 */
unsigned int
CaOmexManifest::getNumObjects(const std::string& elementName)
{
  unsigned int n = 0;

  if (elementName == "content")
  {
    return getNumContents();
  }

  return n;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Returns the nth object of "objectName" in this CaOmexManifest.
 */
CaBase*
CaOmexManifest::getObject(const std::string& elementName, unsigned int index)
{
  CaBase* obj = NULL;

  if (elementName == "content")
  {
    return getContent(index);
  }

  return obj;
}

/** @endcond */


/*
 * Returns the first child element that has the given @p id in the model-wide
 * SId namespace, or @c NULL if no such object is found.
 */
CaBase*
CaOmexManifest::getElementBySId(const std::string& id)
{
  if (id.empty())
  {
    return NULL;
  }

  CaBase* obj = NULL;

  obj = mContents.getElementBySId(id);

  if (obj != NULL)
  {
    return obj;
  }

  return obj;
}


/*
 * Returns the value of the "Namespaces" element of this CaOmexManifest.
 */
const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces*
CaOmexManifest::getNamespaces() const
{
  return mCaNamespaces->getNamespaces();
}


/*
 * Returns the value of the "Namespaces" element of this CaOmexManifest.
 */
LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces*
CaOmexManifest::getNamespaces()
{
  return mCaNamespaces->getNamespaces();
}


/*
 * Returns the value of the "CaErrorLog" element of this CaOmexManifest.
 */
const CaErrorLog*
CaOmexManifest::getErrorLog() const
{
  return &mErrorLog;
}


/*
 * Returns the value of the "CaErrorLog" element of this CaOmexManifest.
 */
CaErrorLog*
CaOmexManifest::getErrorLog()
{
  return &mErrorLog;
}


/*
 * Get a CaError from the CaOmexManifest.
 */
CaError*
CaOmexManifest::getError(unsigned int n)
{
  return const_cast<CaError*>(mErrorLog.getError(n));
}


/*
 * Get a CaError from the CaOmexManifest.
 */
const CaError*
CaOmexManifest::getError(unsigned int n) const
{
  return mErrorLog.getError(n);
}


/*
 * Get the number of CaError objects in this CaOmexManifest.
 */
unsigned int
CaOmexManifest::getNumErrors() const
{
  return mErrorLog.getNumErrors();
}


/*
 * Get the number of CaError objects in this CaOmexManifest with the given
 * severity.
 */
unsigned int
CaOmexManifest::getNumErrors(unsigned int severity) const
{
  return getErrorLog()->getNumFailsWithSeverity(severity);
}



/** @cond doxygenlibCombineInternal */

/*
 * Creates a new object from the next XMLToken on the XMLInputStream
 */
CaBase*
CaOmexManifest::createObject(LIBSBML_CPP_NAMESPACE_QUALIFIER XMLInputStream&
  stream)
{
  CaBase* obj = NULL;

  const std::string& name = stream.peek().getName();

  if (name == "content")
  {
    obj = mContents.createObject(stream);
  }

  connectToChild();

  return obj;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Writes the namespace for the Combine package
 */
void
CaOmexManifest::writeXMLNS(LIBSBML_CPP_NAMESPACE_QUALIFIER XMLOutputStream&
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
 * Creates a new CaOmexManifest_t instance.
 */
LIBCOMBINE_EXTERN
CaOmexManifest_t *
CaOmexManifest_create()
{
  return new CaOmexManifest();
}


/*
 * Creates and returns a deep copy of this CaOmexManifest_t object.
 */
LIBCOMBINE_EXTERN
CaOmexManifest_t*
CaOmexManifest_clone(const CaOmexManifest_t* com)
{
  if (com != NULL)
  {
    return static_cast<CaOmexManifest_t*>(com->clone());
  }
  else
  {
    return NULL;
  }
}


/*
 * Frees this CaOmexManifest_t object.
 */
LIBCOMBINE_EXTERN
void
CaOmexManifest_free(CaOmexManifest_t* com)
{
  if (com != NULL)
  {
    delete com;
  }
}


/*
 * Returns a ListOf_t * containing CaContent_t objects from this
 * CaOmexManifest_t.
 */
LIBCOMBINE_EXTERN
CaListOf_t*
CaOmexManifest_getListOfContents(CaOmexManifest_t* com)
{
  return (com != NULL) ? com->getListOfContents() : NULL;
}


/*
 * Get a CaContent_t from the CaOmexManifest_t.
 */
LIBCOMBINE_EXTERN
CaContent_t*
CaOmexManifest_getContent(CaOmexManifest_t* com, unsigned int n)
{
  return (com != NULL) ? com->getContent(n) : NULL;
}


/*
 * Adds a copy of the given CaContent_t to this CaOmexManifest_t.
 */
LIBCOMBINE_EXTERN
int
CaOmexManifest_addContent(CaOmexManifest_t* com, const CaContent_t* cc)
{
  return (com != NULL) ? com->addContent(cc) : LIBCOMBINE_INVALID_OBJECT;
}


/*
 * Get the number of CaContent_t objects in this CaOmexManifest_t.
 */
LIBCOMBINE_EXTERN
unsigned int
CaOmexManifest_getNumContents(CaOmexManifest_t* com)
{
  return (com != NULL) ? com->getNumContents() : OMEX_INT_MAX;
}


/*
 * Creates a new CaContent_t object, adds it to this CaOmexManifest_t object
 * and returns the CaContent_t object created.
 */
LIBCOMBINE_EXTERN
CaContent_t*
CaOmexManifest_createContent(CaOmexManifest_t* com)
{
  return (com != NULL) ? com->createContent() : NULL;
}


/*
 * Removes the nth CaContent_t from this CaOmexManifest_t and returns a pointer
 * to it.
 */
LIBCOMBINE_EXTERN
CaContent_t*
CaOmexManifest_removeContent(CaOmexManifest_t* com, unsigned int n)
{
  return (com != NULL) ? com->removeContent(n) : NULL;
}




LIBCOMBINE_CPP_NAMESPACE_END


