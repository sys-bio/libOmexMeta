/**
 * @file CaContent.cpp
 * @brief Implementation of the CaContent class.
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
#include <omex/CaContent.h>
#include <omex/CaListOfContents.h>
#include <sbml/xml/XMLInputStream.h>


using namespace std;



LIBCOMBINE_CPP_NAMESPACE_BEGIN




#ifdef __cplusplus


/*
 * Creates a new CaContent instance.
 */
CaContent::CaContent()
  : CaBase(1, 1)
  , mLocation ("")
  , mFormat ("")
  , mMaster (false)
  , mIsSetMaster (false)
  , mCrossRefs ()
{
  connectToChild();
}


/*
 * Creates a new CaContent using the given CaNamespaces object @p omexns.
 */
CaContent::CaContent(CaNamespaces *omexns)
  : CaBase(omexns)
  , mLocation ("")
  , mFormat ("")
  , mMaster (false)
  , mIsSetMaster (false)
  , mCrossRefs (omexns)
{
  setElementNamespace(omexns->getURI());
  connectToChild();
}


/*
 * Copy constructor for CaContent.
 */
CaContent::CaContent(const CaContent& orig)
  : CaBase( orig )
  , mLocation ( orig.mLocation )
  , mFormat ( orig.mFormat )
  , mMaster ( orig.mMaster )
  , mIsSetMaster ( orig.mIsSetMaster )
  , mCrossRefs ( orig.mCrossRefs )
{
  connectToChild();
}


/*
 * Assignment operator for CaContent.
 */
CaContent&
CaContent::operator=(const CaContent& rhs)
{
  if (&rhs != this)
  {
    CaBase::operator=(rhs);
    mLocation = rhs.mLocation;
    mFormat = rhs.mFormat;
    mMaster = rhs.mMaster;
    mIsSetMaster = rhs.mIsSetMaster;
    mCrossRefs = rhs.mCrossRefs;
    connectToChild();
  }

  return *this;
}


/*
 * Creates and returns a deep copy of this CaContent object.
 */
CaContent*
CaContent::clone() const
{
  return new CaContent(*this);
}


/*
 * Destructor for CaContent.
 */
CaContent::~CaContent()
{
}


/*
 * Returns the value of the "location" attribute of this CaContent.
 */
const std::string&
CaContent::getLocation() const
{
  return mLocation;
}


/*
 * Returns the value of the "format" attribute of this CaContent.
 */
const std::string&
CaContent::getFormat() const
{
  return mFormat;
}


/*
 * Returns the value of the "master" attribute of this CaContent.
 */
bool
CaContent::getMaster() const
{
  return mMaster;
}


/*
 * Predicate returning @c true if this CaContent's "location" attribute is set.
 */
bool
CaContent::isSetLocation() const
{
  return (mLocation.empty() == false);
}


/*
 * Predicate returning @c true if this CaContent's "format" attribute is set.
 */
bool
CaContent::isSetFormat() const
{
  return (mFormat.empty() == false);
}


/*
 * Predicate returning @c true if this CaContent's "master" attribute is set.
 */
bool
CaContent::isSetMaster() const
{
  return mIsSetMaster;
}


/*
 * Sets the value of the "location" attribute of this CaContent.
 */
int
CaContent::setLocation(const std::string& location)
{
  mLocation = location;
  return LIBCOMBINE_OPERATION_SUCCESS;
}


/*
 * Sets the value of the "format" attribute of this CaContent.
 */
int
CaContent::setFormat(const std::string& format)
{
  mFormat = format;
  return LIBCOMBINE_OPERATION_SUCCESS;
}


/*
 * Sets the value of the "master" attribute of this CaContent.
 */
int
CaContent::setMaster(bool master)
{
  mMaster = master;
  mIsSetMaster = true;
  return LIBCOMBINE_OPERATION_SUCCESS;
}


/*
 * Unsets the value of the "location" attribute of this CaContent.
 */
int
CaContent::unsetLocation()
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
 * Unsets the value of the "format" attribute of this CaContent.
 */
int
CaContent::unsetFormat()
{
  mFormat.erase();

  if (mFormat.empty() == true)
  {
    return LIBCOMBINE_OPERATION_SUCCESS;
  }
  else
  {
    return LIBCOMBINE_OPERATION_FAILED;
  }
}


/*
 * Unsets the value of the "master" attribute of this CaContent.
 */
int
CaContent::unsetMaster()
{
  mMaster = false;
  mIsSetMaster = false;

  if (isSetMaster() == false)
  {
    return LIBCOMBINE_OPERATION_SUCCESS;
  }
  else
  {
    return LIBCOMBINE_OPERATION_FAILED;
  }
}


/*
 * Returns the CaListOfCrossRefs from this CaContent.
 */
const CaListOfCrossRefs*
CaContent::getListOfCrossRefs() const
{
  return &mCrossRefs;
}


/*
 * Returns the CaListOfCrossRefs from this CaContent.
 */
CaListOfCrossRefs*
CaContent::getListOfCrossRefs()
{
  return &mCrossRefs;
}


/*
 * Get a CaCrossRef from the CaContent.
 */
CaCrossRef*
CaContent::getCrossRef(unsigned int n)
{
  return mCrossRefs.get(n);
}


/*
 * Get a CaCrossRef from the CaContent.
 */
const CaCrossRef*
CaContent::getCrossRef(unsigned int n) const
{
  return mCrossRefs.get(n);
}


/*
 * Adds a copy of the given CaCrossRef to this CaContent.
 */
int
CaContent::addCrossRef(const CaCrossRef* ccr)
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
    return mCrossRefs.append(ccr);
  }
}


/*
 * Get the number of CaCrossRef objects in this CaContent.
 */
unsigned int
CaContent::getNumCrossRefs() const
{
  return mCrossRefs.size();
}


/*
 * Creates a new CaCrossRef object, adds it to this CaContent object and
 * returns the CaCrossRef object created.
 */
CaCrossRef*
CaContent::createCrossRef()
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
    mCrossRefs.appendAndOwn(ccr);
  }

  return ccr;
}


/*
 * Removes the nth CaCrossRef from this CaContent and returns a pointer to it.
 */
CaCrossRef*
CaContent::removeCrossRef(unsigned int n)
{
  return mCrossRefs.remove(n);
}


/*
 * Returns the XML element name of this CaContent object.
 */
const std::string&
CaContent::getElementName() const
{
  static const string name = "content";
  return name;
}


/*
 * Returns the libCombine type code for this CaContent object.
 */
int
CaContent::getTypeCode() const
{
  return LIB_COMBINE_CONTENT;
}


/*
 * Predicate returning @c true if all the required attributes for this
 * CaContent object have been set.
 */
bool
CaContent::hasRequiredAttributes() const
{
  bool allPresent = true;

  if (isSetLocation() == false)
  {
    allPresent = false;
  }

  if (isSetFormat() == false)
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
CaContent::writeElements(LIBSBML_CPP_NAMESPACE_QUALIFIER XMLOutputStream&
  stream) const
{
  CaBase::writeElements(stream);

  for (unsigned int i = 0; i < getNumCrossRefs(); i++)
  {
    getCrossRef(i)->write(stream);
  }
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Accepts the given CaVisitor
 */
bool
CaContent::accept(CaVisitor& v) const
{
  return false;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Sets the parent CaOmexManifest
 */
void
CaContent::setCaOmexManifest(CaOmexManifest* d)
{
  CaBase::setCaOmexManifest(d);

  mCrossRefs.setCaOmexManifest(d);
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Connects to child elements
 */
void
CaContent::connectToChild()
{
  CaBase::connectToChild();

  mCrossRefs.connectToParent(this);
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Gets the value of the "attributeName" attribute of this CaContent.
 */
int
CaContent::getAttribute(const std::string& attributeName, bool& value) const
{
  int return_value = CaBase::getAttribute(attributeName, value);

  if (return_value == LIBCOMBINE_OPERATION_SUCCESS)
  {
    return return_value;
  }

  if (attributeName == "master")
  {
    value = getMaster();
    return_value = LIBCOMBINE_OPERATION_SUCCESS;
  }

  return return_value;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Gets the value of the "attributeName" attribute of this CaContent.
 */
int
CaContent::getAttribute(const std::string& attributeName, int& value) const
{
  int return_value = CaBase::getAttribute(attributeName, value);

  return return_value;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Gets the value of the "attributeName" attribute of this CaContent.
 */
int
CaContent::getAttribute(const std::string& attributeName, double& value) const
{
  int return_value = CaBase::getAttribute(attributeName, value);

  return return_value;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Gets the value of the "attributeName" attribute of this CaContent.
 */
int
CaContent::getAttribute(const std::string& attributeName,
                        unsigned int& value) const
{
  int return_value = CaBase::getAttribute(attributeName, value);

  return return_value;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Gets the value of the "attributeName" attribute of this CaContent.
 */
int
CaContent::getAttribute(const std::string& attributeName,
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
  else if (attributeName == "format")
  {
    value = getFormat();
    return_value = LIBCOMBINE_OPERATION_SUCCESS;
  }

  return return_value;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Predicate returning @c true if this CaContent's attribute "attributeName" is
 * set.
 */
bool
CaContent::isSetAttribute(const std::string& attributeName) const
{
  bool value = CaBase::isSetAttribute(attributeName);

  if (attributeName == "location")
  {
    value = isSetLocation();
  }
  else if (attributeName == "format")
  {
    value = isSetFormat();
  }
  else if (attributeName == "master")
  {
    value = isSetMaster();
  }

  return value;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Sets the value of the "attributeName" attribute of this CaContent.
 */
int
CaContent::setAttribute(const std::string& attributeName, bool value)
{
  int return_value = CaBase::setAttribute(attributeName, value);

  if (attributeName == "master")
  {
    return_value = setMaster(value);
  }

  return return_value;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Sets the value of the "attributeName" attribute of this CaContent.
 */
int
CaContent::setAttribute(const std::string& attributeName, int value)
{
  int return_value = CaBase::setAttribute(attributeName, value);

  return return_value;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Sets the value of the "attributeName" attribute of this CaContent.
 */
int
CaContent::setAttribute(const std::string& attributeName, double value)
{
  int return_value = CaBase::setAttribute(attributeName, value);

  return return_value;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Sets the value of the "attributeName" attribute of this CaContent.
 */
int
CaContent::setAttribute(const std::string& attributeName, unsigned int value)
{
  int return_value = CaBase::setAttribute(attributeName, value);

  return return_value;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Sets the value of the "attributeName" attribute of this CaContent.
 */
int
CaContent::setAttribute(const std::string& attributeName,
                        const std::string& value)
{
  int return_value = CaBase::setAttribute(attributeName, value);

  if (attributeName == "location")
  {
    return_value = setLocation(value);
  }
  else if (attributeName == "format")
  {
    return_value = setFormat(value);
  }

  return return_value;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Unsets the value of the "attributeName" attribute of this CaContent.
 */
int
CaContent::unsetAttribute(const std::string& attributeName)
{
  int value = CaBase::unsetAttribute(attributeName);

  if (attributeName == "location")
  {
    value = unsetLocation();
  }
  else if (attributeName == "format")
  {
    value = unsetFormat();
  }
  else if (attributeName == "master")
  {
    value = unsetMaster();
  }

  return value;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Creates and returns an new "elementName" object in this CaContent.
 */
CaBase*
CaContent::createChildObject(const std::string& elementName)
{
  CaBase* obj = NULL;

  if (elementName == "crossRef")
  {
    return createCrossRef();
  }

  return obj;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Adds a new "elementName" object to this CaContent.
 */
int
CaContent::addChildObject(const std::string& elementName,
                          const CaBase* element)
{
  if (elementName == "crossRef" && element->getTypeCode() ==
    LIB_COMBINE_CROSSREF)
  {
    return addCrossRef((const CaCrossRef*)(element));
  }

  return LIBSBML_OPERATION_FAILED;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Removes and returns the new "elementName" object with the given id in this
 * CaContent.
 */
CaBase*
CaContent::removeChildObject(const std::string& elementName,
                             const std::string& id)
{
  if (elementName == "crossRef")
  {
    for (unsigned int i = 0; i < getNumCrossRefs(); i++)
    {
      if (getCrossRef(i)->getId() == id)
      {
        return removeCrossRef(i);
      }
    }
  }

  return NULL;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Returns the number of "elementName" in this CaContent.
 */
unsigned int
CaContent::getNumObjects(const std::string& elementName)
{
  unsigned int n = 0;

  if (elementName == "crossRef")
  {
    return getNumCrossRefs();
  }

  return n;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Returns the nth object of "objectName" in this CaContent.
 */
CaBase*
CaContent::getObject(const std::string& elementName, unsigned int index)
{
  CaBase* obj = NULL;

  if (elementName == "crossRef")
  {
    return getCrossRef(index);
  }

  return obj;
}

/** @endcond */


/*
 * Returns the first child element that has the given @p id in the model-wide
 * SId namespace, or @c NULL if no such object is found.
 */
CaBase*
CaContent::getElementBySId(const std::string& id)
{
  if (id.empty())
  {
    return NULL;
  }

  CaBase* obj = NULL;

  obj = mCrossRefs.getElementBySId(id);

  if (obj != NULL)
  {
    return obj;
  }

  return obj;
}



/** @cond doxygenlibCombineInternal */

/*
 * Creates a new object from the next XMLToken on the XMLInputStream
 */
CaBase*
CaContent::createObject(LIBSBML_CPP_NAMESPACE_QUALIFIER XMLInputStream& stream)
{
  CaBase* obj = NULL;

  const std::string& name = stream.peek().getName();

  if (name == "crossRef")
  {
    obj = mCrossRefs.createObject(stream);
  }

  connectToChild();

  return obj;
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Adds the expected attributes for this element
 */
void
CaContent::addExpectedAttributes(LIBSBML_CPP_NAMESPACE_QUALIFIER
  ExpectedAttributes& attributes)
{
  CaBase::addExpectedAttributes(attributes);

  attributes.add("location");

  attributes.add("format");

  attributes.add("master");
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Reads the expected attributes into the member data variables
 */
void
CaContent::readAttributes(
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
    static_cast<CaListOfContents*>(getParentCaObject())->size() < 2)
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
        log->logError(CombineContentAllowedAttributes, level, version, details,
          getLine(), getColumn());
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
      logEmptyString(mLocation, level, version, "<CaContent>");
    }
  }
  else
  {
    std::string message = "Combine attribute 'location' is missing from the "
      "<CaContent> element.";
    log->logError(CombineContentAllowedAttributes, level, version, message);
  }

  // 
  // format string (use = "required" )
  // 

  assigned = attributes.readInto("format", mFormat);

  if (assigned == true)
  {
    if (mFormat.empty() == true)
    {
      logEmptyString(mFormat, level, version, "<CaContent>");
    }
  }
  else
  {
    std::string message = "Combine attribute 'format' is missing from the "
      "<CaContent> element.";
    log->logError(CombineContentAllowedAttributes, level, version, message);
  }

  // 
  // master bool (use = "optional" )
  // 

  numErrs = log->getNumErrors();
  mIsSetMaster = attributes.readInto("master", mMaster);

  if (mIsSetMaster == false)
  {
    if (log->getNumErrors() == numErrs + 1 &&
      log->contains(XMLAttributeTypeMismatch))
    {
      log->remove(XMLAttributeTypeMismatch);
      log->logError(CombineContentMasterMustBeBoolean, level, version);
    }
  }
}

/** @endcond */



/** @cond doxygenlibCombineInternal */

/*
 * Writes the attributes to the stream
 */
void
CaContent::writeAttributes(LIBSBML_CPP_NAMESPACE_QUALIFIER XMLOutputStream&
  stream) const
{
  CaBase::writeAttributes(stream);

  if (isSetLocation() == true)
  {
    stream.writeAttribute("location", getPrefix(), mLocation);
  }

  if (isSetFormat() == true)
  {
    stream.writeAttribute("format", getPrefix(), mFormat);
  }

  if (isSetMaster() == true)
  {
    stream.writeAttribute("master", getPrefix(), mMaster);
  }
}

/** @endcond */




#endif /* __cplusplus */


/*
 * Creates a new CaContent_t instance.
 */
LIBCOMBINE_EXTERN
CaContent_t *
CaContent_create()
{
  return new CaContent();
}


/*
 * Creates and returns a deep copy of this CaContent_t object.
 */
LIBCOMBINE_EXTERN
CaContent_t*
CaContent_clone(const CaContent_t* cc)
{
  if (cc != NULL)
  {
    return static_cast<CaContent_t*>(cc->clone());
  }
  else
  {
    return NULL;
  }
}


/*
 * Frees this CaContent_t object.
 */
LIBCOMBINE_EXTERN
void
CaContent_free(CaContent_t* cc)
{
  if (cc != NULL)
  {
    delete cc;
  }
}


/*
 * Returns the value of the "location" attribute of this CaContent_t.
 */
LIBCOMBINE_EXTERN
char *
CaContent_getLocation(const CaContent_t * cc)
{
  if (cc == NULL)
  {
    return NULL;
  }

  return cc->getLocation().empty() ? NULL :
    safe_strdup(cc->getLocation().c_str());
}


/*
 * Returns the value of the "format" attribute of this CaContent_t.
 */
LIBCOMBINE_EXTERN
char *
CaContent_getFormat(const CaContent_t * cc)
{
  if (cc == NULL)
  {
    return NULL;
  }

  return cc->getFormat().empty() ? NULL : safe_strdup(cc->getFormat().c_str());
}


/*
 * Returns the value of the "master" attribute of this CaContent_t.
 */
LIBCOMBINE_EXTERN
int
CaContent_getMaster(const CaContent_t * cc)
{
  return (cc != NULL) ? static_cast<int>(cc->getMaster()) : 0;
}


/*
 * Predicate returning @c 1 (true) if this CaContent_t's "location" attribute
 * is set.
 */
LIBCOMBINE_EXTERN
int
CaContent_isSetLocation(const CaContent_t * cc)
{
  return (cc != NULL) ? static_cast<int>(cc->isSetLocation()) : 0;
}


/*
 * Predicate returning @c 1 (true) if this CaContent_t's "format" attribute is
 * set.
 */
LIBCOMBINE_EXTERN
int
CaContent_isSetFormat(const CaContent_t * cc)
{
  return (cc != NULL) ? static_cast<int>(cc->isSetFormat()) : 0;
}


/*
 * Predicate returning @c 1 (true) if this CaContent_t's "master" attribute is
 * set.
 */
LIBCOMBINE_EXTERN
int
CaContent_isSetMaster(const CaContent_t * cc)
{
  return (cc != NULL) ? static_cast<int>(cc->isSetMaster()) : 0;
}


/*
 * Sets the value of the "location" attribute of this CaContent_t.
 */
LIBCOMBINE_EXTERN
int
CaContent_setLocation(CaContent_t * cc, const char * location)
{
  return (cc != NULL) ? cc->setLocation(location) : LIBCOMBINE_INVALID_OBJECT;
}


/*
 * Sets the value of the "format" attribute of this CaContent_t.
 */
LIBCOMBINE_EXTERN
int
CaContent_setFormat(CaContent_t * cc, const char * format)
{
  return (cc != NULL) ? cc->setFormat(format) : LIBCOMBINE_INVALID_OBJECT;
}


/*
 * Sets the value of the "master" attribute of this CaContent_t.
 */
LIBCOMBINE_EXTERN
int
CaContent_setMaster(CaContent_t * cc, int master)
{
  return (cc != NULL) ? cc->setMaster(master) : LIBCOMBINE_INVALID_OBJECT;
}


/*
 * Unsets the value of the "location" attribute of this CaContent_t.
 */
LIBCOMBINE_EXTERN
int
CaContent_unsetLocation(CaContent_t * cc)
{
  return (cc != NULL) ? cc->unsetLocation() : LIBCOMBINE_INVALID_OBJECT;
}


/*
 * Unsets the value of the "format" attribute of this CaContent_t.
 */
LIBCOMBINE_EXTERN
int
CaContent_unsetFormat(CaContent_t * cc)
{
  return (cc != NULL) ? cc->unsetFormat() : LIBCOMBINE_INVALID_OBJECT;
}


/*
 * Unsets the value of the "master" attribute of this CaContent_t.
 */
LIBCOMBINE_EXTERN
int
CaContent_unsetMaster(CaContent_t * cc)
{
  return (cc != NULL) ? cc->unsetMaster() : LIBCOMBINE_INVALID_OBJECT;
}


/*
 * Returns a ListOf_t * containing CaCrossRef_t objects from this CaContent_t.
 */
LIBCOMBINE_EXTERN
CaListOf_t*
CaContent_getListOfCrossRefs(CaContent_t* cc)
{
  return (cc != NULL) ? cc->getListOfCrossRefs() : NULL;
}


/*
 * Get a CaCrossRef_t from the CaContent_t.
 */
LIBCOMBINE_EXTERN
CaCrossRef_t*
CaContent_getCrossRef(CaContent_t* cc, unsigned int n)
{
  return (cc != NULL) ? cc->getCrossRef(n) : NULL;
}


/*
 * Adds a copy of the given CaCrossRef_t to this CaContent_t.
 */
LIBCOMBINE_EXTERN
int
CaContent_addCrossRef(CaContent_t* cc, const CaCrossRef_t* ccr)
{
  return (cc != NULL) ? cc->addCrossRef(ccr) : LIBCOMBINE_INVALID_OBJECT;
}


/*
 * Get the number of CaCrossRef_t objects in this CaContent_t.
 */
LIBCOMBINE_EXTERN
unsigned int
CaContent_getNumCrossRefs(CaContent_t* cc)
{
  return (cc != NULL) ? cc->getNumCrossRefs() : OMEX_INT_MAX;
}


/*
 * Creates a new CaCrossRef_t object, adds it to this CaContent_t object and
 * returns the CaCrossRef_t object created.
 */
LIBCOMBINE_EXTERN
CaCrossRef_t*
CaContent_createCrossRef(CaContent_t* cc)
{
  return (cc != NULL) ? cc->createCrossRef() : NULL;
}


/*
 * Removes the nth CaCrossRef_t from this CaContent_t and returns a pointer to
 * it.
 */
LIBCOMBINE_EXTERN
CaCrossRef_t*
CaContent_removeCrossRef(CaContent_t* cc, unsigned int n)
{
  return (cc != NULL) ? cc->removeCrossRef(n) : NULL;
}


/*
 * Predicate returning @c 1 (true) if all the required attributes for this
 * CaContent_t object have been set.
 */
LIBCOMBINE_EXTERN
int
CaContent_hasRequiredAttributes(const CaContent_t * cc)
{
  return (cc != NULL) ? static_cast<int>(cc->hasRequiredAttributes()) : 0;
}




LIBCOMBINE_CPP_NAMESPACE_END


