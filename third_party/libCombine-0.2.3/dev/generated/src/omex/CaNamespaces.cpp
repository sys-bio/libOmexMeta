/**
 * @file CaNamespaces.cpp
 * @brief Implementation of the CaNamespaces class.
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


#include <omex/CaNamespaces.h>
#include <sstream>
#include <omex/common/common.h>
#include <iostream>

/** @cond doxygenIgnored */

using namespace std;

/** @endcond */


LIBCOMBINE_CPP_NAMESPACE_BEGIN

#ifdef __cplusplus

/** @cond doxygenLibomexInternal */
void 
CaNamespaces::initCaNamespace()
{
  mNamespaces = new XMLNamespaces();

  switch (mLevel)
  {
  case 0:
  default:
    switch (mVersion)
    {
    case 0:
    default:
      mNamespaces->add(OMEX_XMLNS_L1V1);
      break;
    }
    break;
  }

  if (mNamespaces->getLength() == 0)
  {
    mLevel = OMEX_INT_MAX;
    mVersion = OMEX_INT_MAX;
    delete mNamespaces;
    mNamespaces = NULL;
  }
}
/** @endcond */


CaNamespaces::CaNamespaces(unsigned int level, unsigned int version)
 : mLevel(level)
  ,mVersion(version)
{
  initCaNamespace();
}


CaNamespaces::~CaNamespaces()
{
  if (mNamespaces != NULL)
    delete mNamespaces;
}


/*
 * Copy constructor; creates a copy of a CaNamespaces.
 */
CaNamespaces::CaNamespaces(const CaNamespaces& orig)
 : mLevel(orig.mLevel)
 , mVersion(orig.mVersion)
 , mNamespaces(NULL)
{
  if(orig.mNamespaces != NULL)
    this->mNamespaces = 
          new XMLNamespaces(*const_cast<CaNamespaces&>(orig).mNamespaces);
}


const List * 
CaNamespaces::getSupportedNamespaces()
{
  List *result = new List();
  result->add(new CaNamespaces(0,0));
  return result;
}


void 
CaNamespaces::freeCaNamespaces(List * supportedNS)
{
  if (supportedNS == NULL) return;
  for (unsigned int i = 0; i < supportedNS->getSize(); i++)
  {
    delete (CaNamespaces*)supportedNS->get(i);
  }
  delete supportedNS;
}

/*
 * Assignment operator for CaNamespaces.
 */
CaNamespaces&
CaNamespaces::operator=(const CaNamespaces& rhs)
{
  if (&rhs != this)
  {
    mLevel   = rhs.mLevel;
    mVersion = rhs.mVersion;
    delete this->mNamespaces;
    if(rhs.mNamespaces != NULL)
      this->mNamespaces = 
            new XMLNamespaces(*const_cast<CaNamespaces&>(rhs).mNamespaces);
    else
      this->mNamespaces = NULL;
  }

  return *this;
}



/*
 * Creates and returns a deep copy of this CaNamespaces.
 */
CaNamespaces *
CaNamespaces::clone () const
{
  return new CaNamespaces(*this);
}


std::string 
CaNamespaces::getCaNamespaceURI(unsigned int level,
                                 unsigned int version)
{
  std::string uri = "";
  switch (level)
  {
  case 0:
  default:
    switch (version)
    {
    case 0:
    default:
      uri = OMEX_XMLNS_L1V1;
      break;
    }
    break;
  }
  return uri;
}


std::string
CaNamespaces::getURI() const
{
  return getCaNamespaceURI(mLevel,mVersion);
}


unsigned int 
CaNamespaces::getLevel()
{
  return mLevel;
}


unsigned int 
CaNamespaces::getLevel() const
{
  return mLevel;
}


unsigned int 
CaNamespaces::getVersion()
{
  return mVersion;
}


unsigned int 
CaNamespaces::getVersion() const
{
  return mVersion;
}


XMLNamespaces * 
CaNamespaces::getNamespaces()
{
  return mNamespaces;
}


const XMLNamespaces * 
CaNamespaces::getNamespaces() const
{
  return mNamespaces;
}


int
CaNamespaces::addNamespaces(const XMLNamespaces * xmlns)
{
  int success = LIBCOMBINE_OPERATION_SUCCESS;

  if (xmlns == NULL)
    return LIBCOMBINE_INVALID_OBJECT;

  if (!mNamespaces) 
  {
    initCaNamespace();
  }

  /* check whether the namespace already exists
   * add if it does not
   */
  for (int i = 0; i < xmlns->getLength(); i++)
  {
    if (mNamespaces != NULL && !(mNamespaces->hasNS(xmlns->getURI(i), xmlns->getPrefix(i))))
    {
      success = mNamespaces->add(xmlns->getURI(i), xmlns->getPrefix(i));
    }
  }

  return success;
}


int
CaNamespaces::addNamespace(const std::string &uri, const std::string &prefix)
{
  if (!mNamespaces) 
  {
    initCaNamespace();
  }

  return mNamespaces != NULL ? mNamespaces->add(uri, prefix) : LIBCOMBINE_INVALID_OBJECT;
}


int
CaNamespaces::removeNamespace(const std::string &uri)
{
  if (!mNamespaces) 
  {
    initCaNamespace();
  }

  return mNamespaces != NULL ? mNamespaces->remove(mNamespaces->getIndex(uri)) : LIBCOMBINE_INVALID_OBJECT;
}


/*
 * Predicate returning @c true if the given
 * URL is one of OMEX XML namespaces.
 */
bool 
CaNamespaces::isCaNamespace(const std::string& uri)
{
  if (uri == OMEX_XMLNS_L1V1)   return true;

  return false;
}

bool 
CaNamespaces::isValidCombination()
{
  bool valid = true;
  bool omexDeclared = false;
  std::string declaredURI("");
  unsigned int version = getVersion();
  XMLNamespaces *xmlns = getNamespaces();

  if (xmlns != NULL)
  {
    int numNS = 0;

    if (xmlns->hasURI(OMEX_XMLNS_L1V1))
    {
      ++numNS;
      declaredURI.assign(OMEX_XMLNS_L1V1);
    }

    // checks if the OMEX Namespace is explicitly defined.
    for (int i=0; i < xmlns->getLength(); i++)
    {
      if (!declaredURI.empty() && 
                      xmlns->getURI(i) == declaredURI)
      {
        omexDeclared = true;
        break;
      }
    }
  }


  switch (getLevel())
  {
    case 0:
     switch (version)
      {
        case 0:
          // the namespaces contains the omex namespaces
          // check it is the correct ns for the level/version
          if (omexDeclared)
          {
            if (declaredURI != string(OMEX_XMLNS_L1V1))
            {
              valid = false;
            }
          }
          break;
        default:
          valid = false;
          break;
        }
      break;
    default:
      valid = false;
      break;
  }

  return valid;
}


/** @cond doxygenLibomexInternal */
void 
CaNamespaces::setLevel(unsigned int level)
{
  mLevel = level;
}


void 
CaNamespaces::setVersion(unsigned int version)
{
  mVersion = version;
}


void 
CaNamespaces::setNamespaces(XMLNamespaces * xmlns)
{
  delete mNamespaces;
  if (xmlns != NULL)
    mNamespaces = xmlns->clone();
  else
    mNamespaces = NULL;
}
/** @endcond */

#endif /* __cplusplus */


/** @cond doxygenIgnored */

LIBCOMBINE_EXTERN
CaNamespaces_t *
CaNamespaces_create(unsigned int level, unsigned int version)
{
  return new CaNamespaces(level, version);
}


LIBCOMBINE_EXTERN
void
CaNamespaces_free(CaNamespaces_t* ns)
{
  if (ns == NULL) return;
  delete static_cast<CaNamespaces*>(ns);
}


LIBCOMBINE_EXTERN
unsigned int
CaNamespaces_getLevel(CaNamespaces_t *omexns)
{
  return (omexns != NULL) ? omexns->getLevel() : OMEX_INT_MAX;
}


LIBCOMBINE_EXTERN
unsigned int
CaNamespaces_getVersion(CaNamespaces_t *omexns)
{
  return (omexns != NULL) ? omexns->getVersion() : OMEX_INT_MAX;
}


LIBCOMBINE_EXTERN
XMLNamespaces_t *
CaNamespaces_getNamespaces(CaNamespaces_t *omexns)
{
  return (omexns != NULL) ? omexns->getNamespaces() : NULL;
}


LIBCOMBINE_EXTERN
char *
CaNamespaces_getCaNamespaceURI(unsigned int level, unsigned int version)
{
  return safe_strdup(CaNamespaces::getCaNamespaceURI(level, version).c_str());
}


LIBCOMBINE_EXTERN
int
CaNamespaces_addNamespaces(CaNamespaces_t *omexns,
                             const XMLNamespaces_t * xmlns)
{
  if (omexns != NULL)
    return omexns->addNamespaces(xmlns);
  else
    return LIBCOMBINE_INVALID_OBJECT;
}

LIBCOMBINE_EXTERN
CaNamespaces_t **
CaNamespaces_getSupportedNamespaces(int *length)
{
  if (length == NULL) return NULL;
   const List* supported = CaNamespaces::getSupportedNamespaces();
  
   *length = (int) supported->getSize();
  CaNamespaces_t ** result = (CaNamespaces_t**)malloc(sizeof(CaNamespaces_t*)*((unsigned long)*length));
  memset(result, 0, sizeof(CaNamespaces_t*)*((unsigned long)*length));
  for (int i = 0; i < *length; i++)
  {
    result[i] = ((CaNamespaces*)supported->get((unsigned int)i))->clone();
  }
  CaNamespaces::freeCaNamespaces(const_cast<List*>(supported));
  return result;
}
/** @endcond */

LIBCOMBINE_CPP_NAMESPACE_END

