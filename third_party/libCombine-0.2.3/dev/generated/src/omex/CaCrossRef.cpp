/**
 * @file CaCrossRef.cpp
 * @brief Implementation of the CaCrossRef class.
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
#include <omex/CaCrossRef.h>
#include <omex/CaListOfCrossRefs.h>
#include <sbml/xml/XMLInputStream.h>


using namespace std;



LIBCOMBINE_CPP_NAMESPACE_BEGIN




#ifdef __cplusplus


/*
 * Creates a new CaCrossRef instance.
 */
CaCrossRef::CaCrossRef()
  : CaBase(1, 1)
  , mLocation ("")
{
}


/*
 * Creates a new CaCrossRef using the given CaNamespaces object @p omexns.
 */
CaCrossRef::CaCrossRef(CaNamespaces *omexns)
  : CaBase(omexns)
  , mLocation ("")
{
  setElementNamespace(omexns->getURI());
}


/*
 * Copy constructor for CaCrossRef.
 */
CaCrossRef::CaCrossRef(const CaCrossRef& orig)
  : CaBase( orig )
  , mLocation ( orig.mLocation )
{
}


/*
 * Assignment operator for CaCrossRef.
 */
CaCrossRef&
CaCrossRef::operator=(const CaCrossRef& rhs)
{
  if (&rhs != this)
  {
    CaBase::operator=(rhs);
    mLocation = rhs.mLocation;
  }

  return *this;
}


/*
 * Creates and returns a deep copy of this CaCrossRef object.
 */
CaCrossRef*
CaCrossRef::clone() const
{
  return new CaCrossRef(*this);
}


/*
 * Destructor for CaCrossRef.
 */
CaCrossRef::~CaCrossRef()
{
}


/*
 * Returns the value of the "location" attribute of this CaCrossRef.
 */
const std::string&
CaCrossRef::getLocation() const
{
  return mLocation;
}


/*
 * Predicate returning @c true if this CaCrossRef's "location" attribute is
 * set.
 */
bool
CaCrossRef::isSetLocation() const
{
  return (mLocation.empty() == false);
}


/*
 * Sets the value of the "location" attribute of this CaCrossRef.
 */
int
CaCrossRef::setLocation(const std::string& location)
{
  mLocation = location;
  return LIBCOMBINE_OPERATION_SUCCESS;
}


/*
 * Unsets the value of the "location" attribute of this CaCrossRef.
 */
int
CaCrossRef::unsetLocation()
{
  mLocation.erase();

  if (mLocation.empty() == true)
  {
    return LIBCOMBINE_OPERATION_SUCCESS;
  }
  else
  {
    return LIBCOMBINE_OPERATION_FAILED;
  }
}


/*
 * Returns the XML element name of this CaCrossRef object.
 */
const std::string&
CaCrossRef::getElementName() const
{
  static const string name = "crossRef";
  return name;
}


/*
 * Returns the libCombine type code for this CaCrossRef object.
 */
int
CaCrossRef::getTypeCode() const
{
  return LIB_COMBINE_CROSSREF;
}


/*
 * Predicate returning @c true if all the required attributes for this
 * CaCrossRef object have been set.
 */
bool
CaCrossRef::hasRequiredAttributes() const
{
  bool allPresent = true;

  if (isSetLocation() == false)
  {
    allPresent = false;
  }

  return allPresent;
}



/** @cond doxygenlibCombineInternal */

/*
 * Write any contained elements
 */
void
CaCrossRef::writeElements(LIBSBML_CPP_NAMESPACE_QUALIFIER XMLOutputStream&
  stream) const
{
  CaBase::writeElements(stream);
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Accepts the given CaVisitor
 */
bool
CaCrossRef::accept(CaVisitor& v) const
{
  return false;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Sets the parent CaOmexManifest
 */
void
CaCrossRef::setCaOmexManifest(CaOmexManifest* d)
{
  CaBase::setCaOmexManifest(d);
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Gets the value of the "attributeName" attribute of this CaCrossRef.
 */
int
CaCrossRef::getAttribute(const std::string& attributeName, bool& value) const
{
  int return_value = CaBase::getAttribute(attributeName, value);

  return return_value;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Gets the value of the "attributeName" attribute of this CaCrossRef.
 */
int
CaCrossRef::getAttribute(const std::string& attributeName, int& value) const
{
  int return_value = CaBase::getAttribute(attributeName, value);

  return return_value;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Gets the value of the "attributeName" attribute of this CaCrossRef.
 */
int
CaCrossRef::getAttribute(const std::string& attributeName,
                         double& value) const
{
  int return_value = CaBase::getAttribute(attributeName, value);

  return return_value;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Gets the value of the "attributeName" attribute of this CaCrossRef.
 */
int
CaCrossRef::getAttribute(const std::string& attributeName,
                         unsigned int& value) const
{
  int return_value = CaBase::getAttribute(attributeName, value);

  return return_value;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Gets the value of the "attributeName" attribute of this CaCrossRef.
 */
int
CaCrossRef::getAttribute(const std::string& attributeName,
                         std::string& value) const
{
  int return_value = CaBase::getAttribute(attributeName, value);

  if (return_value == LIBCOMBINE_OPERATION_SUCCESS)
  {
    return return_value;
  }

  if (attributeName == "location")
  {
    value = getLocation();
    return_value = LIBCOMBINE_OPERATION_SUCCESS;
  }

  return return_value;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Predicate returning @c true if this CaCrossRef's attribute "attributeName"
 * is set.
 */
bool
CaCrossRef::isSetAttribute(const std::string& attributeName) const
{
  bool value = CaBase::isSetAttribute(attributeName);

  if (attributeName == "location")
  {
    value = isSetLocation();
  }

  return value;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Sets the value of the "attributeName" attribute of this CaCrossRef.
 */
int
CaCrossRef::setAttribute(const std::string& attributeName, bool value)
{
  int return_value = CaBase::setAttribute(attributeName, value);

  return return_value;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Sets the value of the "attributeName" attribute of this CaCrossRef.
 */
int
CaCrossRef::setAttribute(const std::string& attributeName, int value)
{
  int return_value = CaBase::setAttribute(attributeName, value);

  return return_value;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Sets the value of the "attributeName" attribute of this CaCrossRef.
 */
int
CaCrossRef::setAttribute(const std::string& attributeName, double value)
{
  int return_value = CaBase::setAttribute(attributeName, value);

  return return_value;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Sets the value of the "attributeName" attribute of this CaCrossRef.
 */
int
CaCrossRef::setAttribute(const std::string& attributeName, unsigned int value)
{
  int return_value = CaBase::setAttribute(attributeName, value);

  return return_value;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Sets the value of the "attributeName" attribute of this CaCrossRef.
 */
int
CaCrossRef::setAttribute(const std::string& attributeName,
                         const std::string& value)
{
  int return_value = CaBase::setAttribute(attributeName, value);

  if (attributeName == "location")
  {
    return_value = setLocation(value);
  }

  return return_value;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Unsets the value of the "attributeName" attribute of this CaCrossRef.
 */
int
CaCrossRef::unsetAttribute(const std::string& attributeName)
{
  int value = CaBase::unsetAttribute(attributeName);

  if (attributeName == "location")
  {
    value = unsetLocation();
  }

  return value;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Adds the expected attributes for this element
 */
void
CaCrossRef::addExpectedAttributes(LIBSBML_CPP_NAMESPACE_QUALIFIER
  ExpectedAttributes& attributes)
{
  CaBase::addExpectedAttributes(attributes);

  attributes.add("location");
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Reads the expected attributes into the member data variables
 */
void
CaCrossRef::readAttributes(
                           const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLAttributes&
                             attributes,
                           const LIBSBML_CPP_NAMESPACE_QUALIFIER
                             ExpectedAttributes& expectedAttributes)
{
  unsigned int level = getLevel();
  unsigned int version = getVersion();
  unsigned int numErrs;
  bool assigned = false;
  CaErrorLog* log = getErrorLog();

  if (log && getParentCaObject() &&
    static_cast<CaListOfCrossRefs*>(getParentCaObject())->size() < 2)
  {
    numErrs = log->getNumErrors();
    for (int n = numErrs-1; n >= 0; n--)
    {
      if (log->getError(n)->getErrorId() == CaUnknownCoreAttribute)
      {
        const std::string details = log->getError(n)->getMessage();
        log->remove(CaUnknownCoreAttribute);
        log->logError(CaUnknown, level, version, details);
      }
    }
  }

  CaBase::readAttributes(attributes, expectedAttributes);

  if (log)
  {
    numErrs = log->getNumErrors();

    for (int n = numErrs-1; n >= 0; n--)
    {
      if (log->getError(n)->getErrorId() == CaUnknownCoreAttribute)
      {
        const std::string details = log->getError(n)->getMessage();
        log->remove(CaUnknownCoreAttribute);
        log->logError(CombineCrossRefAllowedAttributes, level, version,
          details, getLine(), getColumn());
      }
    }
  }

  // 
  // location string (use = "required" )
  // 

  assigned = attributes.readInto("location", mLocation);

  if (assigned == true)
  {
    if (mLocation.empty() == true)
    {
      logEmptyString(mLocation, level, version, "<CaCrossRef>");
    }
  }
  else
  {
    std::string message = "Combine attribute 'location' is missing from the "
      "<CaCrossRef> element.";
    log->logError(CombineCrossRefAllowedAttributes, level, version, message);
  }
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Writes the attributes to the stream
 */
void
CaCrossRef::writeAttributes(LIBSBML_CPP_NAMESPACE_QUALIFIER XMLOutputStream&
  stream) const
{
  CaBase::writeAttributes(stream);

  if (isSetLocation() == true)
  {
    stream.writeAttribute("location", getPrefix(), mLocation);
  }
}

/** @endcond */




#endif /* __cplusplus */


/*
 * Creates a new CaCrossRef_t instance.
 */
LIBCOMBINE_EXTERN
CaCrossRef_t *
CaCrossRef_create()
{
  return new CaCrossRef();
}


/*
 * Creates and returns a deep copy of this CaCrossRef_t object.
 */
LIBCOMBINE_EXTERN
CaCrossRef_t*
CaCrossRef_clone(const CaCrossRef_t* ccr)
{
  if (ccr != NULL)
  {
    return static_cast<CaCrossRef_t*>(ccr->clone());
  }
  else
  {
    return NULL;
  }
}


/*
 * Frees this CaCrossRef_t object.
 */
LIBCOMBINE_EXTERN
void
CaCrossRef_free(CaCrossRef_t* ccr)
{
  if (ccr != NULL)
  {
    delete ccr;
  }
}


/*
 * Returns the value of the "location" attribute of this CaCrossRef_t.
 */
LIBCOMBINE_EXTERN
char *
CaCrossRef_getLocation(const CaCrossRef_t * ccr)
{
  if (ccr == NULL)
  {
    return NULL;
  }

  return ccr->getLocation().empty() ? NULL :
    safe_strdup(ccr->getLocation().c_str());
}


/*
 * Predicate returning @c 1 (true) if this CaCrossRef_t's "location" attribute
 * is set.
 */
LIBCOMBINE_EXTERN
int
CaCrossRef_isSetLocation(const CaCrossRef_t * ccr)
{
  return (ccr != NULL) ? static_cast<int>(ccr->isSetLocation()) : 0;
}


/*
 * Sets the value of the "location" attribute of this CaCrossRef_t.
 */
LIBCOMBINE_EXTERN
int
CaCrossRef_setLocation(CaCrossRef_t * ccr, const char * location)
{
  return (ccr != NULL) ? ccr->setLocation(location) :
    LIBCOMBINE_INVALID_OBJECT;
}


/*
 * Unsets the value of the "location" attribute of this CaCrossRef_t.
 */
LIBCOMBINE_EXTERN
int
CaCrossRef_unsetLocation(CaCrossRef_t * ccr)
{
  return (ccr != NULL) ? ccr->unsetLocation() : LIBCOMBINE_INVALID_OBJECT;
}


/*
 * Predicate returning @c 1 (true) if all the required attributes for this
 * CaCrossRef_t object have been set.
 */
LIBCOMBINE_EXTERN
int
CaCrossRef_hasRequiredAttributes(const CaCrossRef_t * ccr)
{
  return (ccr != NULL) ? static_cast<int>(ccr->hasRequiredAttributes()) : 0;
}




LIBCOMBINE_CPP_NAMESPACE_END


