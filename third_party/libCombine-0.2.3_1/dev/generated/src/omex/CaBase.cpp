/**
 * @file CaBase.cpp
 * @brief Implementation of the CaBase class.
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


#include <sstream>
#include <vector>

#include <sbml/xml/XMLError.h>
#include <sbml/xml/XMLErrorLog.h>
#include <sbml/xml/XMLOutputStream.h>
#include <sbml/xml/XMLInputStream.h>
#include <sbml/xml/XMLToken.h>
#include <sbml/xml/XMLNode.h>

#include <sbml/util/util.h>

#include <omex/CaError.h>
#include <omex/CaErrorLog.h>
#include <omex/CaOmexManifest.h>
#include <omex/CaListOf.h>
#include <omex/CaBase.h>


/** @cond doxygenIgnored */
using namespace std;
/** @endcond */

LIBCOMBINE_CPP_NAMESPACE_BEGIN

#ifdef __cplusplus

CaBase*
CaBase::getElementBySId(const std::string& id)
{
  if (id.empty()) return NULL;

  return NULL;
}


const CaBase*
CaBase::getElementBySId(const std::string& id) const 
{
  if (id.empty()) return NULL;

  return NULL;
}


CaBase*
CaBase::getElementByMetaId(const std::string& metaid)
{
  if (metaid.empty()) return NULL;

  return NULL;
}

const CaBase*
CaBase::getElementByMetaId(const std::string& metaid) const 
{
  if (metaid.empty()) return NULL;

  return NULL;
}


List*
CaBase::getAllElements()
{
  return NULL;
}

/** @cond doxygenLibomexInternal */
/*
 * Creates a new CaBase object with the given level and version.
 * Only subclasses may create CaBase objects.
 */
CaBase::CaBase (unsigned int level, unsigned int version) 
 : mMetaId ("")
 , mId ("")
 , mNotes(NULL)
 , mAnnotation( NULL )
 , mCa      ( NULL )
 , mCaNamespaces (NULL)
 , mUserData(NULL)
 , mLine      ( 0 )
 , mColumn    ( 0 )
 , mParentCaObject (NULL)
  , mHasBeenDeleted(false)
  , mEmptyString("")
 , mURI("")
{
  mCaNamespaces = new CaNamespaces(level, version);

  //
  // Sets the XMLNS URI of corresponding OMEX Level/Version to
  // the element namespace (mURI) of this object.
  //
  //
  setElementNamespace(mCaNamespaces->getURI());
}



/*
 * Creates a new CaBase object with the given CaNamespaces.
 * Only subclasses may create CaBase objects.
 */
CaBase::CaBase (CaNamespaces *omexns) 
 : mMetaId("")
 , mId("")
 , mNotes(NULL)
 , mAnnotation( NULL )
 , mCa      ( NULL )
 , mCaNamespaces (NULL)
 , mUserData(NULL)
 , mLine      ( 0 )
 , mColumn    ( 0 )
 , mParentCaObject (NULL)
  , mHasBeenDeleted(false)
  , mEmptyString("")
 , mURI("")
{
  if (!omexns)
  {
    std::string err("CaBase::CaBase(CaNamespaces*) : CaNamespaces is null");
    throw CaConstructorException(err);
  }
  mCaNamespaces = omexns->clone();

  setElementNamespace(static_cast<CaNamespaces>(*mCaNamespaces).getURI());
}
/** @endcond */


/** @cond doxygenLibomexInternal */
/*
 * Copy constructor. Creates a copy of this CaBase object.
 */
CaBase::CaBase(const CaBase& orig)
  : mMetaId (orig.mMetaId)
  , mId (orig.mId)
  , mNotes (NULL)
  , mAnnotation (NULL)
  , mCa (NULL)
  , mCaNamespaces(NULL)
  , mUserData(orig.mUserData)
  , mLine(orig.mLine)
  , mColumn(orig.mColumn)
  , mParentCaObject(NULL)
  , mURI(orig.mURI)
{
  if(orig.mNotes != NULL)
    this->mNotes = new LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode(*const_cast<CaBase&>(orig).getNotes());
  else
    this->mNotes = NULL;

  if(orig.mAnnotation != NULL)
    this->mAnnotation = new LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode(*const_cast<CaBase&>(orig).mAnnotation);
  else
    this->mAnnotation = NULL;

  if(orig.getCaNamespaces() != NULL)
    this->mCaNamespaces =
    new CaNamespaces(*const_cast<CaBase&>(orig).getCaNamespaces());
  else
    this->mCaNamespaces = NULL;

  this->mHasBeenDeleted = false;
}
/** @endcond */


/*
 * Destroy this CaBase object.
 */
CaBase::~CaBase ()
{
  if (mNotes != NULL)       delete mNotes;
  if (mAnnotation != NULL)  delete mAnnotation;
  if (mCaNamespaces != NULL)  delete mCaNamespaces;
}

/*
 * Assignment operator
 */
CaBase& CaBase::operator=(const CaBase& rhs)
{
  if(&rhs!=this)
  {
    this->mMetaId = rhs.mMetaId;
    this->mId = rhs.mId;

    delete this->mNotes;

    if(rhs.mNotes != NULL)
      this->mNotes = new LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode(*const_cast<CaBase&>(rhs).getNotes());
    else
      this->mNotes = NULL;

    delete this->mAnnotation;

    if(rhs.mAnnotation != NULL)
      this->mAnnotation = new LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode(*const_cast<CaBase&>(rhs).mAnnotation);
    else
      this->mAnnotation = NULL;

    this->mCa       = rhs.mCa;
    this->mLine       = rhs.mLine;
    this->mColumn     = rhs.mColumn;
    this->mParentCaObject = rhs.mParentCaObject;
    this->mUserData   = rhs.mUserData;

    delete this->mCaNamespaces;

    if(rhs.mCaNamespaces != NULL)
      this->mCaNamespaces =
      new CaNamespaces(*const_cast<CaBase&>(rhs).mCaNamespaces);
    else
      this->mCaNamespaces = NULL;


    this->mURI = rhs.mURI;
  }

  return *this;
}


/*
 * @return the metaid of this OMEX object.
 */
const string&
CaBase::getMetaId () const
{
  return mMetaId;
}


/*
 * @return the metaid of this OMEX object.
 */
string&
CaBase::getMetaId ()
{
  return mMetaId;
}


const string&
CaBase::getId() const
{
  return mId;
}


/*
 * @return the notes of this OMEX object.
 */
LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode*
CaBase::getNotes()
{
  return mNotes;
}


const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode*
CaBase::getNotes() const
{
  return mNotes;
}


/*
 * @return the notes of this OMEX object by string.
 */
std::string
CaBase::getNotesString()
{
  return LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode::convertXMLNodeToString(mNotes);
}


std::string
CaBase::getNotesString() const
{
  return LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode::convertXMLNodeToString(mNotes);
}


/*
 * @return the annotation of this OMEX object.
 */
LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode*
CaBase::getAnnotation ()
{
  return mAnnotation;
}


const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode*
CaBase::getAnnotation () const
{
  return const_cast<CaBase *>(this)->getAnnotation();
}


/*
 * @return the annotation of this OMEX object by string.
 */
std::string
CaBase::getAnnotationString ()
{
  return LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode::convertXMLNodeToString(getAnnotation());
}


std::string
CaBase::getAnnotationString () const
{
  return LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode::convertXMLNodeToString(getAnnotation());
}


/** @cond doxygenLibomexInternal */
std::string
CaBase::getURI() const
{
  const CaOmexManifest* doc = getCaOmexManifest();

  if (doc == NULL)
    return getElementNamespace();

  CaNamespaces* omexns = doc->getCaNamespaces();

  if (omexns == NULL)
    return getElementNamespace();

  return getElementNamespace();
}
/** @endcond */


void *
CaBase::getUserData() const
{
  return this->mUserData;
}


int
CaBase::setUserData(void *userData)
{
  this->mUserData = userData;
  if (userData == NULL && mUserData == NULL)
  {
    return LIBCOMBINE_OPERATION_SUCCESS;
  }
  else if (mUserData != NULL)
  {
    return LIBCOMBINE_OPERATION_SUCCESS;
  }
  else
  {
    return LIBCOMBINE_OPERATION_FAILED;
  }
}

bool
CaBase::isSetUserData() const
{
  if (mUserData != NULL)
  {
    return true;
  }
  else
  {
    return false;
  }
}

int
CaBase::unsetUserData()
{
  this->mUserData = NULL;
  if (mUserData == NULL)
  {
    return LIBCOMBINE_OPERATION_SUCCESS;
  }
  else
  {
    return LIBCOMBINE_OPERATION_FAILED;
  }
}

/*
 * @return the Namespaces associated with this OMEX object
 */
LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces*
CaBase::getNamespaces()
{
  if (mCa != NULL)
    return mCa->getCaNamespaces()->getNamespaces();
  else
    return mCaNamespaces->getNamespaces();
}


const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces*
CaBase::getNamespaces() const
{
  if (mCa != NULL)
    return mCa->getCaNamespaces()->getNamespaces();
  else
    return mCaNamespaces->getNamespaces();
}


/*
 * @return the parent CaOmexManifest of this OMEX object.
 */
const CaOmexManifest*
CaBase::getCaOmexManifest () const
{
  if (mCa != NULL)
  {
    // if the doc object has been deleted the pointer is
    // still valid but points to nothing
    try
    {
      if (mCa->getHasBeenDeleted())
      {
        return NULL;
      }
      else
      {
        return mCa;
      }
    }
    catch ( ... )
    {
      return NULL;
    }
  }

  return mCa;
}

/*
 * @return the parent CaOmexManifest of this OMEX object.
 */
CaOmexManifest*
CaBase::getCaOmexManifest ()
{
  if (mCa != NULL)
  {
    // if the doc object has been deleted the pointer is
    // still valid but points to nothing
    try
    {
      if (mCa->getHasBeenDeleted())
      {
        return NULL;
      }
      else
      {
        return mCa;
      }
    }
    catch ( ... )
    {
      return NULL;
    }
  }
  return mCa;
}
CaBase*
CaBase::getParentCaObject ()
{
  if (mParentCaObject != NULL)
  {
    // if the parent object has been deleted the pointer is
    // still valid but points to nothing
    try
    {
      if (mParentCaObject->getHasBeenDeleted())
      {
        return NULL;
      }
      else
      {
        return mParentCaObject;
      }
    }
    catch ( ... )
    {
      return NULL;
    }
  }

  return mParentCaObject;
}

const CaBase*
CaBase::getParentCaObject () const
{
  if (mParentCaObject != NULL)
  {
    // if the parent object has been deleted the pointer is
    // still valid but points to nothing
    try
    {
      if (mParentCaObject->getHasBeenDeleted())
      {
        return NULL;
      }
      else
      {
        return mParentCaObject;
      }
    }
    catch ( ... )
    {
      return NULL;
    }
  }

  return mParentCaObject;
}


/*
 * @return the line number of this OMEX object.
 */
unsigned int
CaBase::getLine () const
{
  return mLine;
}


/*
 * @return the column number of this OMEX object.
 */
unsigned int
CaBase::getColumn () const
{
  return mColumn;
}


/*
 * @return true if the metaid of this OMEX object is set, false
 * otherwise.
 */
bool
CaBase::isSetMetaId () const
{
  return (mMetaId.empty() == false);
}


bool
CaBase::isSetId() const
{
  return (getId().empty() == false);
}


/*
 * @return true if the notes of this OMEX object is set, false
 * otherwise.
 */
bool
CaBase::isSetNotes () const
{
  return (mNotes != NULL);
}


/*
 * @return true if the annotation of this OMEX object is set,
 * false otherwise.
 */
bool
CaBase::isSetAnnotation () const
{
  return (mAnnotation != NULL);
}


/*
 * Sets the metaid field of the given OMEX object to a copy of metaid.
 */
int
CaBase::setMetaId (const std::string& metaid)
{
  if (metaid.empty())
  {
    mMetaId.erase();
    return LIBCOMBINE_OPERATION_SUCCESS;
  }
  else if (!(SyntaxChecker::isValidXMLID(metaid)))
  {
    return LIBCOMBINE_INVALID_ATTRIBUTE_VALUE;
  }
  else
  {
    mMetaId = metaid;
    return LIBCOMBINE_OPERATION_SUCCESS;
  }
}

/*
 * Sets the id field of the given OMEX object to a copy of sid.
 */
int
CaBase::setId (const std::string& sid)
{
  if (sid.empty())
  {
    mId.erase();
    return LIBCOMBINE_OPERATION_SUCCESS;
  }
  else if (!(SyntaxChecker::isValidXMLID(sid)))
  {
    return LIBCOMBINE_INVALID_ATTRIBUTE_VALUE;
  }
  else
  {
    mId = sid;
    return LIBCOMBINE_OPERATION_SUCCESS;
  }
}


/*
 * Sets the annotation of this OMEX object to a copy of annotation.
 */
int
CaBase::setAnnotation (LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode* annotation)
{
  if (annotation == NULL)
  {
    delete mAnnotation;
    mAnnotation = NULL;
  }

  if (mAnnotation != annotation)
  {
    delete mAnnotation;

    mAnnotation = annotation->clone();
  }

  return LIBCOMBINE_OPERATION_SUCCESS;
}

/*
 * Sets the annotation (by string) of this OMEX object to a copy of annotation.
 */
int
CaBase::setAnnotation (const std::string& annotation)
{
  
  int success = LIBCOMBINE_OPERATION_FAILED;
  
  if(annotation.empty())
  {
    unsetAnnotation();
    return LIBCOMBINE_OPERATION_SUCCESS;
  }
  
  LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode* annt_xmln;
  
  // you might not have a document !!
  if (getCaOmexManifest() != NULL)
  {
    LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces* xmlns = getCaOmexManifest()->getNamespaces();
    annt_xmln = LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode::convertStringToXMLNode(annotation,xmlns);
  }
  else
  {
    annt_xmln = LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode::convertStringToXMLNode(annotation);
  }
  
  if(annt_xmln != NULL)
  {
    success = setAnnotation(annt_xmln);
    delete annt_xmln;
  }
  return success;  
}


/*
 * Appends annotation to the existing annotations.
 * This allows other annotations to be preserved whilst
 * adding additional information.
 */
int
CaBase::appendAnnotation (const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode* annotation)
{
  int success = LIBCOMBINE_OPERATION_FAILED;
  unsigned int duplicates = 0;

  if(annotation == NULL)
    return LIBCOMBINE_OPERATION_SUCCESS;

  LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode* new_annotation = NULL;
  const string&  name = annotation->getName();

  // check for annotation tags and add if necessary
  if (name != "annotation")
  {
    LIBSBML_CPP_NAMESPACE_QUALIFIER XMLToken ann_t = LIBSBML_CPP_NAMESPACE_QUALIFIER XMLToken(LIBSBML_CPP_NAMESPACE_QUALIFIER XMLTriple("annotation", "", ""), LIBSBML_CPP_NAMESPACE_QUALIFIER XMLAttributes());
    new_annotation = new LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode(ann_t);
    new_annotation->addChild(*annotation);
  }
  else
  {
    new_annotation = annotation->clone();
  }


  if (mAnnotation != NULL)
  {
    // if mAnnotation is just <annotation/> need to tell
    // it to no longer be an end
    if (mAnnotation->isEnd())
    {
      mAnnotation->unsetEnd();
    }


    // create a list of existing top level ns
      vector<string> topLevelNs;
    unsigned int i = 0;
    for(i = 0; i < mAnnotation->getNumChildren(); i++)
    {
          topLevelNs.push_back(mAnnotation->getChild(i).getName());
    }



    for(i = 0; i < new_annotation->getNumChildren(); i++)
    {
          if (find(topLevelNs.begin(), topLevelNs.end(), (new_annotation->getChild(i).getName())) != topLevelNs.end())
      {
        mAnnotation->addChild(new_annotation->getChild(i));
      }
      else
      {
        duplicates++;
      }
    }

    delete new_annotation;

    if (duplicates > 0)
    {
      success = LIBCOMBINE_DUPLICATE_ANNOTATION_NS;
    }
    else
    {
      LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode *copy = mAnnotation->clone();
      success = setAnnotation(copy);
      delete copy;
    }


  }
  else
  {
    success = setAnnotation(new_annotation);

    delete new_annotation;
  }

  return success;
}

/*
 * Appends annotation (by string) to the existing annotations.
 * This allows other annotations to be preserved whilst
 * adding additional information.
 */
int
CaBase::appendAnnotation (const std::string& annotation)
{
  int success = LIBCOMBINE_OPERATION_FAILED;
  LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode* annt_xmln;
  if (getCaOmexManifest() != NULL)
  {
    LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces* xmlns = getCaOmexManifest()->getNamespaces();
    annt_xmln = LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode::convertStringToXMLNode(annotation,xmlns);
  }
  else
  {
    annt_xmln = LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode::convertStringToXMLNode(annotation);
  }

  if(annt_xmln != NULL)
  {
    success = appendAnnotation(annt_xmln);
    delete annt_xmln;
  }

  return success;
}


int
CaBase::removeTopLevelAnnotationElement(const std::string elementName,
    const std::string elementURI)
{

  int success = LIBCOMBINE_OPERATION_FAILED;
  if (mAnnotation == NULL)
  {
    success = LIBCOMBINE_OPERATION_SUCCESS;
    return success;
  }

  int index = mAnnotation->getIndex(elementName);
  if (index < 0)
  {
    // the annotation does not have a child of this name
    success = LIBCOMBINE_ANNOTATION_NAME_NOT_FOUND;
    return success;
  }
  else
  {
    // check uri matches
    if (elementURI.empty() == false)
    {
      LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode child = mAnnotation->getChild(index);
      std::string prefix = child.getPrefix();

      if (prefix.empty() == false
        && elementURI != child.getNamespaceURI(prefix))
      {
        success = LIBCOMBINE_ANNOTATION_NS_NOT_FOUND;
        return success;
      }
      else
      {
        bool match = false;
        int n = 0;

        while (match == false && n < child.getNamespacesLength())
        {
          if (elementURI == child.getNamespaceURI(n))
          {
            match = true;
          }
          n++;
        }

        if (match == false)
        {
          success = LIBCOMBINE_ANNOTATION_NS_NOT_FOUND;
          return success;
        }
      }
    }

    // remove the annotation at the index corresponding to the name
    delete mAnnotation->removeChild(index);

      if (mAnnotation->getNumChildren() == 0)
        {
          delete mAnnotation;
          mAnnotation = NULL;
        }

    // check success
    if (mAnnotation == NULL || mAnnotation->getIndex(elementName) < 0)
    {
      success = LIBCOMBINE_OPERATION_SUCCESS;
    }
  }

  return success;
}


int
CaBase::replaceTopLevelAnnotationElement(const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode* annotation)
{
  int success = LIBCOMBINE_OPERATION_FAILED;
  LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode * replacement = NULL;
  if (annotation->getName() == "annotation")
  {
    if (annotation->getNumChildren() != 1)
    {
      success = LIBCOMBINE_INVALID_OBJECT;
      return success;
    }
    else
    {
      replacement = annotation->getChild(0).clone();
    }
  }
  else
  {
    replacement = annotation->clone();
  }

  success = removeTopLevelAnnotationElement(replacement->getName());
  if (success == LIBCOMBINE_OPERATION_SUCCESS)
  {
    success = appendAnnotation(annotation);
  }

  delete (replacement);

  return success;
}


int
CaBase::replaceTopLevelAnnotationElement(const std::string& annotation)
{
  int success = LIBCOMBINE_OPERATION_FAILED;
  LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode* annt_xmln;
  if (getCaOmexManifest() != NULL)
  {
    LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces* xmlns = getCaOmexManifest()->getNamespaces();
    annt_xmln = LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode::convertStringToXMLNode(annotation,xmlns);
  }
  else
  {
    annt_xmln = LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode::convertStringToXMLNode(annotation);
  }

  if(annt_xmln != NULL)
  {
    success = replaceTopLevelAnnotationElement(annt_xmln);
  }

  delete annt_xmln;

  return success;
}


/*
 * Sets the notes of this OMEX object to a copy of notes.
 */
int
CaBase::setNotes(const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode* notes)
{
  if (mNotes == notes)
  {
    return LIBCOMBINE_OPERATION_SUCCESS;
  }
  else if (notes == NULL)
  {
    delete mNotes;
    mNotes = NULL;
    return LIBCOMBINE_OPERATION_SUCCESS;
  }

  delete mNotes;
  const string&  name = notes->getName();

  /* check for notes tags and add if necessary */

  if (name == "notes")
  {
    mNotes = static_cast<LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode*>( notes->clone() );
  }
  else
  {
    LIBSBML_CPP_NAMESPACE_QUALIFIER XMLToken notes_t = LIBSBML_CPP_NAMESPACE_QUALIFIER XMLToken(LIBSBML_CPP_NAMESPACE_QUALIFIER XMLTriple("notes", "", ""),
                                LIBSBML_CPP_NAMESPACE_QUALIFIER XMLAttributes());
    mNotes = new LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode(notes_t);

    // The root node of the given XMLNode tree can be an empty XMLNode
    // (i.e. neither start, end, nor text XMLNode) if the given notes was
    // converted from an XML string whose top level elements are neither
    // "html" nor "body" and not enclosed with <notes>..</notes> tag
    // (e.g. <p ...>..</p><br/>).
    if (!notes->isStart() && !notes->isEnd() && !notes->isText() )
    {
      for (unsigned int i=0; i < notes->getNumChildren(); i++)
      {
        if (mNotes->addChild(notes->getChild(i)) < 0)
        {
          return LIBCOMBINE_OPERATION_FAILED;
        }
      }
    }
    else
    {
      if (mNotes->addChild(*notes) < 0)
        return LIBCOMBINE_OPERATION_FAILED;
    }
  }

    if (!SyntaxChecker::hasExpectedXHTMLSyntax(mNotes, NULL))
    {
      delete mNotes;
      mNotes = NULL;
      return LIBCOMBINE_INVALID_OBJECT;
    }

  return LIBCOMBINE_OPERATION_SUCCESS;

}

/*
 * Sets the notes (by std::string) of this OMEX object to a copy of notes.
 */
int
CaBase::setNotes(const std::string& notes, bool addXHTMLMarkup)
{
  int success = LIBCOMBINE_OPERATION_FAILED;
  
  if (notes.empty())
  {
    success = unsetNotes();
  }
  else
  {
    LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode* notes_xmln;

    // you might not have a document !!
    if (getCaOmexManifest() != NULL)
    {
      LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces* xmlns = getCaOmexManifest()->getNamespaces();
      notes_xmln = LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode::convertStringToXMLNode(notes,xmlns);
    }
    else
    {
      notes_xmln = LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode::convertStringToXMLNode(notes);
    }

    if (notes_xmln != NULL)
    {
      if (addXHTMLMarkup == true)
      {
        if (notes_xmln->getNumChildren() == 0
            && notes_xmln->isStart() == false
            && notes_xmln->isEnd() == false
            && notes_xmln->isText() == true)
        {
          //create a parent node of xhtml type p
          LIBSBML_CPP_NAMESPACE_QUALIFIER XMLAttributes blank_att = LIBSBML_CPP_NAMESPACE_QUALIFIER XMLAttributes();
          LIBSBML_CPP_NAMESPACE_QUALIFIER XMLTriple triple = LIBSBML_CPP_NAMESPACE_QUALIFIER XMLTriple("p", "http://www.w3.org/1999/xhtml", "");
          LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces xmlns = LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces();
          xmlns.add("http://www.w3.org/1999/xhtml", "");
          LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode *xmlnode = new LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode(LIBSBML_CPP_NAMESPACE_QUALIFIER XMLToken(triple, blank_att, xmlns));

          // create a text node from the text given
          xmlnode->addChild(*notes_xmln);
          success = setNotes(xmlnode);
          delete xmlnode;
        }
        else
        {
          success = setNotes(notes_xmln);
        }
      }
      else
      {
        success = setNotes(notes_xmln);
      }

      delete notes_xmln;
    }
  }
  return success;
}


/*
 * Appends notes to the existing notes.
 * This allows other notes to be preserved whilst
 * adding additional information.
 */
int
CaBase::appendNotes(const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode* notes)
{
  int success = LIBCOMBINE_OPERATION_FAILED;
  if(notes == NULL)
  {
    return LIBCOMBINE_OPERATION_SUCCESS;
  }

  const string&  name = notes->getName();

  // The content of notes in OMEX can consist only of the following
  // possibilities:
  //
  //  1. A complete XHTML document (minus the XML and DOCTYPE
  //     declarations), that is, XHTML content beginning with the
  //     html tag.
  //     (_NotesType is _ANotesHTML.)
  //
  //  2. The body element from an XHTML document.
  //     (_NotesType is _ANotesBody.)
  //
  //  3. Any XHTML content that would be permitted within a body
  //     element, each one must declare the XML namespace separately.
  //     (_NotesType is _ANotesAny.)
  //

  typedef enum { _ANotesHTML, _ANotesBody, _ANotesAny } _NotesType;

  _NotesType addedNotesType = _ANotesAny;
  LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode   addedNotes;

  //------------------------------------------------------------
  //
  // STEP1 : identifies the type of the given notes
  //
  //------------------------------------------------------------

  if (name == "notes")
  {
    /* check for notes tags on the added notes and strip if present and
       the notes tag has "html" or "body" element */

    if (notes->getNumChildren() > 0)
    {
      // notes->getChild(0) must be "html", "body", or any XHTML
      // element that would be permitted within a "body" element
      // (e.g. <p>..</p>,  <br>..</br> and so forth).

      const string& cname = notes->getChild(0).getName();

      if (cname == "html")
      {
        addedNotes = notes->getChild(0);
        addedNotesType = _ANotesHTML;
      }
      else if (cname == "body")
      {
        addedNotes = notes->getChild(0);
        addedNotesType = _ANotesBody;
      }
      else
      {
        // the notes tag must NOT be stripped if notes->getChild(0) node
        // is neither "html" nor "body" element because the children of
        // the addedNotes will be added to the curNotes later if the node
        // is neither "html" nor "body".
        addedNotes = *notes;
        addedNotesType = _ANotesAny;
      }
    }
    else
    {
      // the given notes is empty
      return LIBCOMBINE_OPERATION_SUCCESS;
    }
  }
  else
  {
    // if the XMLNode argument notes has been created from a string and
    // it is a set of subelements there may be a single empty node
    // as parent - leaving this in doesnt affect the writing out of notes
    // but messes up the check for correct syntax
    if (!notes->isStart() && !notes->isEnd() && !notes->isText() )
    {
      if (notes->getNumChildren() > 0)
      {
        addedNotes = *notes;
        addedNotesType = _ANotesAny;
      }
      else
      {
        // the given notes is empty
        return LIBCOMBINE_OPERATION_SUCCESS;
      }
    }
    else
    {
      if (name == "html")
      {
        addedNotes = *notes;
        addedNotesType = _ANotesHTML;
      }
      else if (name == "body")
      {
        addedNotes = *notes;
        addedNotesType = _ANotesBody;
      }
      else
      {
        // The given notes node needs to be added to a parent node
        // if the node is neither "html" nor "body" element because the
        // children of addedNotes will be added to the curNotes later if the
        // node is neither "html" nor "body" (i.e. any XHTML element that
        // would be permitted within a "body" element)
        addedNotes.addChild(*notes);
        addedNotesType = _ANotesAny;
      }
    }
  }

  //
  // checks the addedNotes of "html" if the html tag contains "head" and
  // "body" tags which must be located in this order.
  //
  if (addedNotesType == _ANotesHTML)
  {
    if ((addedNotes.getNumChildren() != 2) ||
        ( (addedNotes.getChild(0).getName() != "head") ||
          (addedNotes.getChild(1).getName() != "body")
        )
       )
    {
      return LIBCOMBINE_INVALID_OBJECT;
    }
  }

  // check whether notes is valid xhtml
  if (getLevel() > 2
    || (getLevel() == 2 && getVersion() > 1))
  {
    LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode tmpNotes(LIBSBML_CPP_NAMESPACE_QUALIFIER XMLTriple("notes","",""), LIBSBML_CPP_NAMESPACE_QUALIFIER XMLAttributes());

    if (addedNotesType == _ANotesAny)
    {
      for (unsigned int i=0; i < addedNotes.getNumChildren(); i++)
      {
        tmpNotes.addChild(addedNotes.getChild(i));
      }
    }
    else
    {
      tmpNotes.addChild(addedNotes);
    }

    if (!SyntaxChecker::hasExpectedXHTMLSyntax(&tmpNotes, NULL))
    {
      return LIBCOMBINE_INVALID_OBJECT;
    }
  }


  if ( mNotes != NULL )
  {
    //------------------------------------------------------------
    //
    //  STEP2: identifies the type of the existing notes
    //
    //------------------------------------------------------------

    _NotesType curNotesType   = _ANotesAny;
    LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode&  curNotes = *mNotes;

    // curNotes.getChild(0) must be "html", "body", or any XHTML
    // element that would be permitted within a "body" element .

    const string& cname = curNotes.getChild(0).getName();

    if (cname == "html")
    {
      LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode& curHTML = curNotes.getChild(0);
      //
      // checks the curHTML if the html tag contains "head" and "body" tags
      // which must be located in this order, otherwise nothing will be done.
      //
      if ((curHTML.getNumChildren() != 2) ||
          ( (curHTML.getChild(0).getName() != "head") ||
            (curHTML.getChild(1).getName() != "body")
          )
         )
      {
        return LIBCOMBINE_INVALID_OBJECT;
      }
      curNotesType = _ANotesHTML;
    }
    else if (cname == "body")
    {
      curNotesType = _ANotesBody;
    }
    else
    {
      curNotesType = _ANotesAny;
    }

    /*
     * BUT we also have the issue of the rules relating to notes
     * contents and where to add them ie we cannot add a second body element
     * etc...
     */

    //------------------------------------------------------------
    //
    //  STEP3: appends the given notes to the current notes
    //
    //------------------------------------------------------------

    unsigned int i;

    if (curNotesType == _ANotesHTML)
    {
      LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode& curHTML = curNotes.getChild(0);
      LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode& curBody = curHTML.getChild(1);

      if (addedNotesType == _ANotesHTML)
      {
        // adds the given html tag to the current html tag

        LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode& addedBody = addedNotes.getChild(1);

        for (i=0; i < addedBody.getNumChildren(); i++)
        {
          if (curBody.addChild(addedBody.getChild(i)) < 0 )
            return LIBCOMBINE_OPERATION_FAILED;
        }
      }
      else if ((addedNotesType == _ANotesBody)
             || (addedNotesType == _ANotesAny))
      {
        // adds the given body or other tag (permitted in the body) to the current
        // html tag

        for (i=0; i < addedNotes.getNumChildren(); i++)
        {
          if (curBody.addChild(addedNotes.getChild(i)) < 0 )
            return LIBCOMBINE_OPERATION_FAILED;
        }
      }
      success = LIBCOMBINE_OPERATION_SUCCESS;
    }
    else if (curNotesType == _ANotesBody)
    {
      if (addedNotesType == _ANotesHTML)
      {
        // adds the given html tag to the current body tag

        LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode  addedHTML(addedNotes);
        LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode& addedBody = addedHTML.getChild(1);
        LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode& curBody   = curNotes.getChild(0);

        for (i=0; i < curBody.getNumChildren(); i++)
        {
          addedBody.insertChild(i,curBody.getChild(i));
        }

        curNotes.removeChildren();
        if (curNotes.addChild(addedHTML) < 0)
          return LIBCOMBINE_OPERATION_FAILED;
      }
      else if ((addedNotesType == _ANotesBody) || (addedNotesType == _ANotesAny))
      {
        // adds the given body or other tag (permitted in the body) to the current
        // body tag

        LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode& curBody = curNotes.getChild(0);

        for (i=0; i < addedNotes.getNumChildren(); i++)
        {
          if (curBody.addChild(addedNotes.getChild(i)) < 0)
            return LIBCOMBINE_OPERATION_FAILED;
        }
      }
      success = LIBCOMBINE_OPERATION_SUCCESS;
    }
    else if (curNotesType == _ANotesAny)
    {
      if (addedNotesType == _ANotesHTML)
      {
        // adds the given html tag to the current any tag permitted in the body.

        LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode  addedHTML(addedNotes);
        LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode& addedBody = addedHTML.getChild(1);

        for (i=0; i < curNotes.getNumChildren(); i++)
        {
          addedBody.insertChild(i,curNotes.getChild(i));
        }

        curNotes.removeChildren();
        if (curNotes.addChild(addedHTML) < 0)
          return LIBCOMBINE_OPERATION_FAILED;
      }
      else if (addedNotesType == _ANotesBody)
      {
        // adds the given body tag to the current any tag permitted in the body.

        LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode addedBody(addedNotes);

        for (i=0; i < curNotes.getNumChildren(); i++)
        {
          addedBody.insertChild(i,curNotes.getChild(i));
        }

        curNotes.removeChildren();
        if (curNotes.addChild(addedBody) < 0)
          return LIBCOMBINE_OPERATION_FAILED;
      }
      else if (addedNotesType == _ANotesAny)
      {
        // adds the given any tag permitted in the boy to that of the current
        // any tag.

        for (i=0; i < addedNotes.getNumChildren(); i++)
        {
          if (curNotes.addChild(addedNotes.getChild(i)) < 0)
            return LIBCOMBINE_OPERATION_FAILED;
        }
      }
      success = LIBCOMBINE_OPERATION_SUCCESS;
    }
  }
  else // if (mNotes == NULL)
  {
    // setNotes accepts XMLNode with/without top level notes tags.
    success = setNotes(notes);
  }

  return success;
}

/*
 * Appends notes (by string) to the existing notes.
 * This allows other notes to be preserved whilst
 * adding additional information.
 */
int
CaBase::appendNotes(const std::string& notes)
{
  int success = LIBCOMBINE_OPERATION_FAILED;
  if (notes.empty())
  {
    return LIBCOMBINE_OPERATION_SUCCESS;
  }

  LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode* notes_xmln;
  // you might not have a document !!
  if (getCaOmexManifest() != NULL)
  {
      LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces* xmlns = getCaOmexManifest()->getNamespaces();
      notes_xmln = LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode::convertStringToXMLNode(notes,xmlns);
  }
  else
  {
      notes_xmln = LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode::convertStringToXMLNode(notes);
  }

  if(notes_xmln != NULL)
  {
    success = appendNotes(notes_xmln);
    delete notes_xmln;
  }
  return success;
}


/** @cond doxygenLibomexInternal */
/*
 * Sets the parent CaOmexManifest of this OMEX object.
 */
void
CaBase::setCaOmexManifest (CaOmexManifest* d)
{
  mCa = d;
}


/*
  * Sets the parent OMEX object of this OMEX object.
  *
  * @param sb the OMEX object to use
  */
void
CaBase::connectToParent (CaBase* parent)
{
  mParentCaObject = parent;
  if (mParentCaObject)
  {
#if 0
    cout << "[DEBUG] connectToParent " << this << " (parent) " << CaTypeCode_toString(parent->getTypeCode(),"core")
         << " " << parent->getCaOmexManifest() << endl;
#endif
    setCaOmexManifest(mParentCaObject->getCaOmexManifest());
  }
  else
  {
    setCaOmexManifest(NULL);
  }
}


/*
 * Sets this OMEX object to child OMEX objects (if any).
 * (Creates a child-parent relationship by the parent)
 *
 * Subclasses must override this function if they define
 * one ore more child elements.
 * Basically, this function needs to be called in
 * constructors, copy constructors and assignment operators.
 */
void
CaBase::connectToChild()
{
}
/** @endcond */

CaBase*
CaBase::getAncestorOfType(int type)
{
  if (type == LIB_COMBINE_OMEXMANIFEST)
    return getCaOmexManifest();

  CaBase *child;
  CaBase *parent = getParentCaObject();

  while ( parent != NULL &&
          !( parent->getTypeCode() == LIB_COMBINE_OMEXMANIFEST )
        )
  {
    if (parent->getTypeCode() == type)
      return parent;
    else
    {
      child = parent;
      parent = child->getParentCaObject();
    }
  }

  // if we get here we havent found an ancestor of this type
  return NULL;

}


const CaBase*
CaBase::getAncestorOfType(int type) const
{
  if (type == LIB_COMBINE_OMEXMANIFEST)
    return getCaOmexManifest();

  const CaBase *child;
  const CaBase *parent = getParentCaObject();

  while ( parent != NULL &&
          !( parent->getTypeCode() == LIB_COMBINE_OMEXMANIFEST )
        )
  {
    if (parent->getTypeCode() == type)
      return parent;
    else
    {
      child = parent;
      parent = child->getParentCaObject();
    }
  }

  // if we get here we havent found an ancestor of this type
  return NULL;

}


/*
 * Sets the namespaces relevant of this OMEX object.
 *
 * @param xmlns the namespaces to set
 */
int
CaBase::setNamespaces(LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces* xmlns)
{
  if (xmlns == NULL)
  {
    mCaNamespaces->setNamespaces(NULL);
    return LIBCOMBINE_OPERATION_SUCCESS;
  }
  else
  {
    mCaNamespaces->setNamespaces(xmlns);
    return LIBCOMBINE_OPERATION_SUCCESS;
  }
}



/*
 * Unsets the metaid of this OMEX object.
 */
int
CaBase::unsetMetaId ()
{
  mMetaId.erase();

  if (mMetaId.empty())
  {
    return LIBCOMBINE_OPERATION_SUCCESS;
  }
  else
  {
    return LIBCOMBINE_OPERATION_FAILED;
  }
}


/*
 * Unsets the id of this OMEX object.
 */
int
CaBase::unsetId ()
{
  mId.erase();

  if (mId.empty())
  {
    return LIBCOMBINE_OPERATION_SUCCESS;
  }
  else
  {
    return LIBCOMBINE_OPERATION_FAILED;
  }
}


/*
 * Unsets the notes of this OMEX object.
 */
int
CaBase::unsetNotes ()
{
  delete mNotes;
  mNotes = NULL;
  return LIBCOMBINE_OPERATION_SUCCESS;
}


/*
 * Unsets the annotation of this OMEX object.
 */
int
CaBase::unsetAnnotation ()
{
  LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode* empty = NULL;
  return setAnnotation(empty);
}


/*
 * @return the OMEX level of this OMEX object.
 */
unsigned int
CaBase::getLevel () const
{
  if (mCaNamespaces != NULL)
    return mCaNamespaces->getLevel();
  else
    return OMEX_DEFAULT_LEVEL;
}


/*
 * @return the OMEX version of this OMEX object.
 */
unsigned int
CaBase::getVersion () const
{
  if (mCaNamespaces != NULL)
    return mCaNamespaces->getVersion();
  else
    return OMEX_DEFAULT_VERSION;
}


/*
 * @return the typecode (int) of this OMEX object or OMEX_UNKNOWN
 * (default).
 *
 * This method MAY return the typecode of this OMEX object or it MAY
 * return OMEX_UNKNOWN.  That is, subclasses of CaBase are not required to
 * implement this method to return a typecode.  This method is meant
 * primarily for the LibCombine C interface where class and subclass
 * information is not readily available.
 *
 * @see getElementName()
 */
int
CaBase::getTypeCode () const
{
  return OMEX_UNKNOWN;
}


bool
CaBase::hasValidLevelVersionNamespaceCombination()
{
  int typecode = getTypeCode();
  LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces *xmlns = getNamespaces();

  return hasValidLevelVersionNamespaceCombination(typecode, xmlns);
}

/** @cond doxygenLibomexInternal */
bool
CaBase::matchesCaNamespaces(const CaBase * sb)
{
  bool match = matchesCoreCaNamespace(sb);

  return match;
}

bool
CaBase::matchesCaNamespaces(const CaBase * sb) const
{
  bool match = matchesCoreCaNamespace(sb);

  return match;
}


bool
CaBase::matchesRequiredCaNamespacesForAddition(const CaBase * sb)
{
  // if core does not match forget it
  bool match = matchesCoreCaNamespace(sb);

  return match;
}


bool
CaBase::matchesRequiredCaNamespacesForAddition(const CaBase * sb) const
{
  // if core does not match forget it
  bool match = matchesCoreCaNamespace(sb);

  return match;
}


bool
CaBase::matchesCoreCaNamespace(const CaBase * sb)
{
  bool match = false;

  CaNamespaces *omexns = getCaNamespaces();
  CaNamespaces *omexns_rhs = sb->getCaNamespaces();

  if (omexns->getLevel() != omexns_rhs->getLevel())
    return match;

  if (omexns->getVersion() != omexns_rhs->getVersion())
    return match;

  std::string coreNs = CaNamespaces::getCaNamespaceURI(
                       omexns->getLevel(), omexns->getVersion());

  if (omexns->getNamespaces()->containsUri(coreNs)
    && omexns_rhs->getNamespaces()->containsUri(coreNs))
  {
    match = true;
  }

  return match;
}


bool
CaBase::matchesCoreCaNamespace(const CaBase * sb) const
{
  bool match = false;

  CaNamespaces *omexns = getCaNamespaces();
  CaNamespaces *omexns_rhs = sb->getCaNamespaces();

  if (omexns->getLevel() != omexns_rhs->getLevel())
    return match;

  if (omexns->getVersion() != omexns_rhs->getVersion())
    return match;

  std::string coreNs = CaNamespaces::getCaNamespaceURI(
                       omexns->getLevel(), omexns->getVersion());

  if (omexns->getNamespaces()->containsUri(coreNs)
    && omexns_rhs->getNamespaces()->containsUri(coreNs))
  {
    match = true;
  }

  return match;
}


bool
CaBase::hasValidLevelVersionNamespaceCombination(int typecode, LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces *xmlns)
{


  //
  // (TODO) Currently, the following check code works only for
  //        elements in OMEX core.
  //        This function may need to be extented for other elements
  //        defined in each package extension.
  //

  bool valid = true;
  bool omexDeclared = false;
  std::string declaredURI("");

  if (xmlns != NULL)
  {
    int numNS = 0;

    if (xmlns->hasURI(OMEX_XMLNS_L1V1))
    {
      // checks different OMEX XMLNamespaces
      if (numNS > 0) return false;
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

  return valid;
}

/* sets the Canamespaces - internal use only*/
int
CaBase::setCaNamespaces(CaNamespaces * omexns)
{
  if (omexns == NULL)
    return LIBCOMBINE_INVALID_OBJECT;

  CaNamespaces* omexnsClone = (omexns) ? omexns->clone() : 0;
  setCaNamespacesAndOwn(omexnsClone);

  return LIBCOMBINE_OPERATION_SUCCESS;
}

/*
 * sets the Canamespaces - only for internal use in the
 * constructors of CaBase subclasses in extension packages.
 */
void
CaBase::setCaNamespacesAndOwn(CaNamespaces * omexns)
{
  delete mCaNamespaces;
  mCaNamespaces = omexns;

  if(omexns != NULL)
    setElementNamespace(omexns->getURI());
}


/* gets the Canamespaces - internal use only*/
CaNamespaces *
CaBase::getCaNamespaces() const
{
  if (mCa != NULL)
    return mCa->mCaNamespaces;
  
  // initialize OMEX namespace if need be
  if (mCaNamespaces == NULL)
    const_cast<CaBase*>(this)->mCaNamespaces = new CaNamespaces(getLevel(), getVersion());
  return mCaNamespaces;  
}
/** @endcond */



/*
 * @return the partial OMEX that describes this OMEX object.
 */
char*
CaBase::toCa ()
{
  ostringstream    os;
  LIBSBML_CPP_NAMESPACE_QUALIFIER XMLOutputStream  stream(os, "UTF-8", false);

  write(stream);

  return safe_strdup( os.str().c_str() );
}


/** @cond doxygenLibomexInternal */
int 
CaBase::getAttribute(const std::string& attributeName, double& value) const
{
  return LIBCOMBINE_OPERATION_FAILED;
}
/** @endcond */


/** @cond doxygenLibomexInternal */
int 
CaBase::getAttribute(const std::string& attributeName, bool& value) const
{
  return LIBCOMBINE_OPERATION_FAILED;
}
/** @endcond */


/** @cond doxygenLibomexInternal */
int 
CaBase::getAttribute(const std::string& attributeName, int& value) const
{
  return LIBCOMBINE_OPERATION_FAILED;
}
/** @endcond */


/** @cond doxygenLibomexInternal */
int 
CaBase::getAttribute(const std::string& attributeName, unsigned int& value) const
{
  return LIBCOMBINE_OPERATION_FAILED;
}
/** @endcond */


/** @cond doxygenLibomexInternal */
int 
CaBase::getAttribute(const std::string& attributeName, std::string& value) const
{
  if (attributeName == "metaid")
  {
    value = getMetaId();
    return LIBCOMBINE_OPERATION_SUCCESS;
  }
  else if (attributeName == "id")
  {
    value = getId();
    return LIBCOMBINE_OPERATION_SUCCESS;
  }

  return LIBCOMBINE_OPERATION_FAILED;
}
/** @endcond */


/** @cond doxygenLibomexInternal */
bool 
CaBase::isSetAttribute(const std::string& attributeName) const
{
  bool value = false;
  if (attributeName == "metaid")
  {
    value = isSetMetaId();
  }
  else if (attributeName == "id")
  {
    value = isSetId();
  }

  return value;
}
/** @endcond */


/** @cond doxygenLibomexInternal */
int 
CaBase::setAttribute(const std::string& attributeName, double value)
{
  return LIBCOMBINE_OPERATION_FAILED;
}
/** @endcond */


/** @cond doxygenLibomexInternal */
int 
CaBase::setAttribute(const std::string& attributeName, bool value)
{
  return LIBCOMBINE_OPERATION_FAILED;
}
/** @endcond */


/** @cond doxygenLibomexInternal */
int 
CaBase::setAttribute(const std::string& attributeName, int value)
{
  return LIBCOMBINE_OPERATION_FAILED;
}
/** @endcond */


/** @cond doxygenLibomexInternal */
int 
CaBase::setAttribute(const std::string& attributeName, unsigned int value)
{
  return LIBCOMBINE_OPERATION_FAILED;
}
/** @endcond */


/** @cond doxygenLibomexInternal */
int 
CaBase::setAttribute(const std::string& attributeName, const std::string& value)
{
  int return_value = LIBCOMBINE_OPERATION_FAILED;
  if (attributeName == "metaid")
  {
    return_value = setMetaId(value);
  }
  else if (attributeName == "id")
  {
    return_value = setId(value);
  }

  return return_value;
}
/** @endcond */


/** @cond doxygenLibomexInternal */
int 
CaBase::unsetAttribute(const std::string& attributeName)
{
  int value = LIBCOMBINE_OPERATION_FAILED;
  if (attributeName == "metaid")
  {
    value = unsetMetaId();
  }
  else if (attributeName == "id")
  {
    value = unsetId();
  }

  return value;
}
/** @endcond */

/** @cond doxygenLibomexInternal */
CaBase* 
CaBase::createChildObject(const std::string& elementName)
{
  return NULL;
}
/** @endcond */

/** @cond doxygenLibomexInternal */
int
CaBase::addChildObject(const std::string& elementName, const CaBase* element)
{
  return LIBCOMBINE_OPERATION_FAILED;
}
/** @endcond */

/** @cond doxygenLibomexInternal */
CaBase*
CaBase::removeChildObject(const std::string& elementName, const std::string& id)
{
  return NULL;
}
/** @endcond */

/** @cond doxygenLibomexInternal */

unsigned int
  CaBase::getNumObjects(const std::string& objectName)
{
  return 0;
}

  /** @endcond */

  /** @cond doxygenLibomexInternal */

CaBase* 
CaBase::getObject(const std::string& objectName, unsigned int index)
{
  return NULL;
}

  /** @endcond */
/** @cond doxygenLibomexInternal */
/*
 * Reads (initializes) this OMEX object by reading from XMLInputStream.
 */
void
CaBase::read (LIBSBML_CPP_NAMESPACE_QUALIFIER XMLInputStream& stream)
{
  if ( !stream.peek().isStart() ) return;

  const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLToken  element  = stream.next();
  int             position =  0;

  setCaBaseFields( element );

  ExpectedAttributes expectedAttributes;
  addExpectedAttributes(expectedAttributes);
  readAttributes( element.getAttributes(), expectedAttributes );

  /* if we are reading a document pass the
   * OMEX Namespace information to the input stream object
   * thus the MathML reader can find out what level/version
   * of OMEX it is parsing
   */
  if (element.getName() == "OmexManifest")
  {
 //   stream.setCaNamespaces(this->getCaNamespaces());
    // need to check that any prefix on the omexns also occurs on element
    // remembering the horrible situation where the omexns might be declared
    // with more than one prefix
    LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces * xmlns = this->getCaNamespaces()->getNamespaces();
    if (xmlns != NULL)
    {
      int i = xmlns->getIndexByPrefix(element.getPrefix());
      if (i < xmlns->getNumNamespaces())
      {
        bool errorLoggedAlready = false;
        bool error = false;
        if (i > -1)
        {
          if (xmlns->getURI(i) != this->getCaNamespaces()->getURI())
          {
            error = true;
          }
        }
        else if ( i == -1)
        {
          error = true;
        }

        /* if there is a mismatch in level/version this will already
         * be logged; do not need another error
         */
        for (unsigned int n = 0; n < this->getErrorLog()->getNumErrors(); n++)
        {
          unsigned int errorId =
                             this->getErrorLog()->getError(n)->getErrorId();
          if ( errorId == CombineOmexManifestAllowedCoreAttributes
            || errorId == InvalidNamespaceOnCa)
          {
            errorLoggedAlready = true;
          }
        }

        if (error == true && errorLoggedAlready == false)
        {
          static ostringstream errMsg;
          errMsg.str("");
          errMsg << "The prefix for the <omex> element does not match "
            << "the prefix for the OMEX namespace.  This means that "
            << "the <omex> element in not in the CaNamespace."<< endl;

          logError(InvalidNamespaceOnCa,
                    getLevel(), getVersion(), errMsg.str());
        }
      }
    }

  }
  else
  {
    //
    // checks if the given default namespace (if any) is a valid
    // OMEX namespace
    //
    checkDefaultNamespace(mCaNamespaces->getNamespaces(), element.getName());
    if (!element.getPrefix().empty())
    {
      LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces * prefixedNS = new LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces();
      prefixedNS->add(element.getURI(), element.getPrefix());
      checkDefaultNamespace(prefixedNS, element.getName(), element.getPrefix());
      delete prefixedNS;
    }
  }

  if ( element.isEnd() ) return;

  while ( stream.isGood() )
  {
    // this used to skip the text
    //    stream.skipText();
    // instead, read text and store in variable
    std::string text;
    while(stream.isGood() && stream.peek().isText())
    {
      text += stream.next().getCharacters();
    }
    setElementText(text);

    const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLToken& next = stream.peek();

    // Re-check stream.isGood() because stream.peek() could hit something.
    if ( !stream.isGood() ) break;

    if ( next.isEndFor(element) )
    {
      stream.next();
      break;
    }
    else if ( next.isStart() )
    {
      const std::string nextName = next.getName();

      CaBase * object = createObject(stream);

      if (object != NULL)
      {
        position = object->getElementPosition();

        object->connectToParent(static_cast <CaBase*>(this));

        object->read(stream);

        if ( !stream.isGood() ) break;

        checkCaListOfPopulated(object);
      }
      else if ( !( readOtherXML(stream)
                   || readAnnotation(stream)
                   || readNotes(stream) ))
      {
        logUnknownElement(nextName, getLevel(), getVersion());
        stream.skipPastEnd( stream.next() );
      }
    }
    else
    {
      stream.skipPastEnd( stream.next() );
    }
  }
}
/** @endcond */


void
CaBase::setElementText(const std::string &text)
{
}

/** @cond doxygenLibomexInternal */
/*
 * Writes (serializes) this OMEX object by writing it to XMLOutputStream.
 */
void
CaBase::write (LIBSBML_CPP_NAMESPACE_QUALIFIER XMLOutputStream& stream) const
{
  stream.startElement( getElementName(), getPrefix() );

  writeXMLNS     ( stream );
  writeAttributes( stream );
  writeElements  ( stream );

  stream.endElement( getElementName(), getPrefix() );

}
/** @endcond */


/** @cond doxygenLibomexInternal */
/*
 * Subclasses should override this method to write out their contained
 * OMEX objects as XML elements.  Be sure to call your parents
 * implementation of this method as well.
 */
void
CaBase::writeElements (LIBSBML_CPP_NAMESPACE_QUALIFIER XMLOutputStream& stream) const
{
  if ( mNotes != NULL ) stream << *mNotes;

  if (mAnnotation != NULL) stream << *mAnnotation;
}


/** @cond doxygenLibomexInternal */
/*
 * Subclasses should override this method to create, store, and then
 * return an OMEX object corresponding to the next XMLToken in the
 * XMLInputStream.
 *
 * @return the OMEX object corresponding to next XMLToken in the
 * XMLInputStream or @c NULL if the token was not recognized.
 */
CaBase*
CaBase::createObject (LIBSBML_CPP_NAMESPACE_QUALIFIER XMLInputStream& stream)
{
  return NULL;
}


/** @endcond */


/** @cond doxygenLibomexInternal */
/*
 * Subclasses should override this method to read (and store) XHTML,
 * MathML, etc. directly from the XMLInputStream.
 *
 * @return true if the subclass read from the stream, false otherwise.
 */
bool
CaBase::readOtherXML (LIBSBML_CPP_NAMESPACE_QUALIFIER XMLInputStream& stream)
{
  bool read = false;
  return read;
}
/** @endcond */


/** @cond doxygenLibomexInternal */
/*
 * @return true if read an <annotation> element from the stream
 */
bool
CaBase::readAnnotation (LIBSBML_CPP_NAMESPACE_QUALIFIER XMLInputStream& stream)
{
  const string& name = stream.peek().getName();

  if (name == "annotation")
  {
    // If an annotation already exists, log it as an error and replace
    // the content of the existing annotation with the new one.

    if (mAnnotation != NULL)
    {
      string msg = "An OMEX <" + getElementName() + "> element ";
      msg += "has multiple <annotation> children.";
      logError(CaMultipleAnnotations, getLevel(), getVersion(), msg);
    }

    delete mAnnotation;
    mAnnotation = new LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode(stream);
    checkAnnotation();
    return true;
  }

  return false;
}
/** @endcond */


/** @cond doxygenLibomexInternal */
/*
 * @return true if read a <notes> element from the stream
 */
bool
CaBase::readNotes (LIBSBML_CPP_NAMESPACE_QUALIFIER XMLInputStream& stream)
{
  const string& name = stream.peek().getName();

  if (name == "notes")
  {
    // If a notes element already exists, then it is an error.
    // If an annotation element already exists, then the ordering is wrong.
    // In either case, replace existing content with the new notes read.

    if (mNotes != NULL)
    {
      logError(CaOnlyOneNotesElementAllowed, getLevel(), getVersion());
    }

    delete mNotes;
    mNotes = new LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode(stream);

    //
    // checks if the given default namespace (if any) is a valid
    // OMEX namespace
    //
    const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces &xmlns = mNotes->getNamespaces();
    checkDefaultNamespace(&xmlns,"notes");

    return true;
  }

  return false;
}

bool
CaBase::getHasBeenDeleted() const
{
  return mHasBeenDeleted;
}
/** @endcond */


/** @cond doxygenLibomexInternal */
/*
 * @return the ordinal position of the element with respect to its siblings
 * or -1 (default) to indicate the position is not significant.
 */
int
CaBase::getElementPosition () const
{
  return -1;
}
/** @endcond */


/** @cond doxygenLibomexInternal */
CaErrorLog*
CaBase::getErrorLog ()
{
  return (mCa != NULL) ? mCa->getErrorLog() : NULL;
}
/** @endcond */


/** @cond doxygenLibomexInternal */
/*
 * Helper to log a common type of error.
 */
void
CaBase::logUnknownAttribute( const string& attribute,
                            const unsigned int level,
                            const unsigned int version,
                            const string& element,
                            const string& prefix)
{
  ostringstream msg;

    msg << "Attribute '" << attribute << "' is not part of the "
        << "definition of an OMEX Level " << level
        << " Version " << version << " <" << element << "> element.";

  if (mCa)
  {
  //
  // (TODO) Needs to be fixed so that error can be added when
  // no CaOmexManifest attached.
  //
        getErrorLog()->logError(CaUnknownCoreAttribute, level,
          version, msg.str(), getLine(), getColumn());
  }
}
/** @endcond */


/** @cond doxygenLibomexInternal */
/*
 * Helper to log a common type of error.
 */
void
CaBase::logUnknownElement( const string& element,
        const unsigned int level,
        const unsigned int version )
{


    ostringstream msg;

    msg << "Element '" << element << "' is not part of the definition of "
        << "OMEX Level " << level << " Version " << version << ".";

    if (mCa != NULL)
    {
      getErrorLog()->logError(CaUnrecognizedElement,
            level, version, msg.str(), getLine(), getColumn());
    }
  

}
/** @endcond */


/** @cond doxygenLibomexInternal */
/*
 * Helper to log a common type of error.
 */
void
CaBase::logEmptyString( const string& attribute,
                       const unsigned int level,
                       const unsigned int version,
                       const string& element )

{
  ostringstream msg;

  msg << "Attribute '" << attribute << "' on an "
    << element << " must not be an empty string.";

  //
  // (TODO) Needs to be fixed so that error can be added when
  // no CaOmexManifest attached.
  //
  if (mCa != NULL)
    getErrorLog()->logError(CaNotSchemaConformant,
                            level, version, msg.str(), getLine(), getColumn());
}
/** @endcond */


/** @cond doxygenLibomexInternal */
/*
 * Convenience method for easily logging problems from within method
 * implementations.
 *
 * This is essentially a short form of getErrorLog()->logError(...)
 */
void
CaBase::logError (  unsigned int       id
                 , const unsigned int level
                 , const unsigned int version
                 , const std::string& details )
{
  //
  // (TODO) Needs to be fixed so that error can be added when
  // no CaOmexManifest attached.
  //
  if ( CaBase::getErrorLog() != NULL && mCa != NULL)
    getErrorLog()->logError(id, getLevel(), getVersion(), details, getLine(), getColumn());
}
/** @endcond */


/** @cond doxygenLibomexInternal */
/**
 * Subclasses should override this method to get the list of
 * expected attributes.
 * This function is invoked from corresponding readAttributes()
 * function.
 */
void
CaBase::addExpectedAttributes(ExpectedAttributes& attributes)
{
  //
  // metaid: ID { use="optional" }  (L2v1 ->)
  //
  attributes.add("metaid");
}


/*
 * Subclasses should override this method to read values from the given
 * XMLAttributes set into their specific fields.  Be sure to call your
 * parents implementation of this method as well.
 */
void
CaBase::readAttributes (const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLAttributes& attributes,
                       const LIBSBML_CPP_NAMESPACE_QUALIFIER ExpectedAttributes& expectedAttributes)
{
  const_cast<LIBSBML_CPP_NAMESPACE_QUALIFIER XMLAttributes&>(attributes).setErrorLog(getErrorLog());

  const unsigned int level   = getLevel  ();
  const unsigned int version = getVersion();

  //
  // check that all attributes are expected
  //
  for (int i = 0; i < attributes.getLength(); i++)
  {
    std::string name   = attributes.getName(i);
    std::string uri    = attributes.getURI(i);
    std::string prefix = attributes.getPrefix(i);

    //
    // To allow prefixed attribute whose namespace doesn't belong to
    // core or extension package.
    //
    // (e.g. xsi:type attribute in Curve element in layout extension)
    //
    if (!prefix.empty())
    {
      if ( expectedAttributes.hasAttribute(prefix + ":" + name) ) continue;
    }


    //
    // Checks if there are attributes of unknown package extensions
    //
    // if we happen to be on the omex element (document) then
    // getPrefix() and mURI have not been set and just return defaults
    // thus a prefix does not appear to come from the right place !!!
    if (!prefix.empty() && getElementName() == "OmexManifest")
    {
      if (!expectedAttributes.hasAttribute(name))
      {
        logUnknownAttribute(name, level, version, getElementName());
      }
    }
    else if (!expectedAttributes.hasAttribute(name))
    {
      logUnknownAttribute(name, level, version, getElementName(), prefix);
    }
  }

    bool assigned = attributes.readInto("metaid", mMetaId, getErrorLog(), false, getLine(), getColumn());

    if (assigned && mMetaId.empty())
    {
      logEmptyString("metaid", level, version,
                     CaTypeCode_toString(getTypeCode()));
    }

    if (isSetMetaId())
    {
      if (!SyntaxChecker::isValidXMLID(mMetaId))
      {
        logError(CaInvalidMetaidSyntax, getLevel(), getVersion(), "The metaid '" + mMetaId + "' does not conform to the syntax.");
      }
  }

}


/** @cond doxygenLibomexInternal */
/*
 * Returns the prefix of this element.
 */
std::string
CaBase::getPrefix() const
{
  std::string prefix = "";

  const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces *xmlns = getNamespaces();
  string uri = getURI();
  if(xmlns && mCa)
  {
    prefix = xmlns->getPrefix(uri);
  }

  return prefix;
}


/*
 * Returns the prefix of this element.
 */
std::string
CaBase::getCaPrefix() const
{
  std::string prefix = "";

  const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces *xmlns = getNamespaces();
  if (xmlns == NULL)
    return getPrefix();

  for (int i = 0; i < xmlns->getNumNamespaces(); i++)
  {
    string uri = xmlns->getURI(i);
    if (CaNamespaces::isCaNamespace(uri))
      return xmlns->getPrefix(i);
  }

  return getPrefix();
}

/*
 * Returns the root element of this element.
 *
 * @note The root element may not be an CaOmexManifest element. For example,
 * this element is the root element if this element doesn't have a parent
 * OMEX object (i.e. mParentCaObject is NULL)
 */
CaBase*
CaBase::getRootElement()
{
  if (mCa)
  {
    return mCa;
  }
  else if (mParentCaObject)
  {
    return mParentCaObject->getRootElement();
  }
  else
  {
    return this;
  }
}


/*
 * Subclasses should override this method to write their XML attributes
 * to the XMLOutputStream.  Be sure to call your parents implementation
 * of this method as well.
 */
void
CaBase::writeAttributes (LIBSBML_CPP_NAMESPACE_QUALIFIER XMLOutputStream& stream) const
{
  string omexPrefix    = getCaPrefix();
  if ( !mMetaId.empty() )
  {
    stream.writeAttribute("metaid", omexPrefix, mMetaId);
  }

}


/*
 *
 * Subclasses should override this method to write their xmlns attriubutes
 * (if any) to the XMLOutputStream.  Be sure to call your parents implementation
 * of this method as well.
 *
 */
void
CaBase::writeXMLNS (LIBSBML_CPP_NAMESPACE_QUALIFIER XMLOutputStream& stream) const
{
  // do nothing.
}
/** @endcond */



/** @cond doxygenLibomexInternal */
/*
  * Checks that an OMEX CaListOf element has been populated.
  * If a listOf element has been declared with no elements,
  * an error is logged.
  */
void
CaBase::checkCaListOfPopulated(CaBase* object)
{
    // for now log the empty list
  if (object->getTypeCode() == OMEX_LIST_OF)
  {
    if (static_cast <CaListOf*> (object)->size() == 0)
    {
      CaErrorCode_t error = CaEmptyListElement;
      ostringstream errMsg;
      errMsg << object->getElementName() << " cannot be empty.";

      logError(error, getLevel(), getVersion(), errMsg.str());
    }
  }
}
/** @endcond */

//This assumes that the parent of the object is of the type CaListOf.  If this is not the case, it will need to be overridden.
int CaBase::removeFromParentAndDelete()
{
  CaBase* parent = getParentCaObject();

  if (parent==NULL) return LIBCOMBINE_OPERATION_FAILED;
  
  CaListOf* parentList = static_cast<CaListOf*>(parent);
  
  if (parentList == NULL) return LIBCOMBINE_OPERATION_FAILED;
  
  for (unsigned int i=0; i<parentList->size(); i++) 
  {
    CaBase* sibling = parentList->get(i);
    if (sibling == this) 
    {
      parentList->remove(i);
      delete this;
      return LIBCOMBINE_OPERATION_SUCCESS;
    }
  }
  return LIBCOMBINE_OPERATION_FAILED;
}

/** @cond doxygenLibomexInternal */
const std::string
CaBase::checkMathMLNamespace(const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLToken elem)
{
  std::string prefix = "";
  unsigned int match = 0;
  int n;
  if (elem.getNamespaces().getLength() != 0)
  {
    for (n = 0; n < elem.getNamespaces().getLength(); n++)
    {
      if (!strcmp(elem.getNamespaces().getURI(n).c_str(),
                  "http://www.w3.org/1998/Math/MathML"))
      {
        match = 1;
        break;
      }
    }
  }
  if (match == 0)
  {
    if( mCa->getNamespaces() != NULL)
    /* check for implicit declaration */
    {
      for (n = 0; n < mCa->getNamespaces()->getLength(); n++)
      {
        if (!strcmp(mCa->getNamespaces()->getURI(n).c_str(),
                    "http://www.w3.org/1998/Math/MathML"))
        {
          match = 1;
          prefix = mCa->getNamespaces()->getPrefix(n);
          break;
        }
      }
    }
  }
  if (match == 0)
  {
    logError(CaInvalidMathElement, getLevel(), getVersion(), "The MathML namespace 'http://www.w3.org/1998/Math/MathML' was not found.");
  }

  return prefix;
}
/** @endcond */


/** @cond doxygenLibomexInternal */
void
CaBase::checkDefaultNamespace(const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces* xmlns,
                             const std::string& elementName,
                             const std::string& prefix)
{
  //
  // checks if the given default namespace (if any) is a valid
  // OMEX namespace
  //
  if (xmlns == NULL || xmlns->getLength() == 0)
    return;

  const std::string defaultURI = xmlns->getURI(prefix);
  if (defaultURI.empty() || mURI == defaultURI)
    return;

  // if this element (CaBase derived) has notes or annotation elements,
  // it is ok for them to be in the OMEX namespace!
  if ( CaNamespaces::isCaNamespace(defaultURI)
       && !CaNamespaces::isCaNamespace(mURI)
       && (elementName == "notes" || elementName == "annotation"))
    return;

  static ostringstream errMsg;
  errMsg.str("");
  errMsg << "xmlns=\"" << defaultURI << "\" in <" << elementName
         << "> element is an invalid namespace." << endl;

  logError(CaNotSchemaConformant, getLevel(), getVersion(), errMsg.str());

}

/*
  * Checks the annotation does not declare an omex namespace.
  * If the annotation declares an omex namespace an error is logged.
  */
void
CaBase::checkAnnotation()
{
  unsigned int nNodes = 0;
  unsigned int match = 0;
  int n = 0;
  std::vector<std::string> uri_list;
  uri_list.clear();

  if (mAnnotation == NULL) return;

  //
  // checks if the given default namespace (if any) is a valid
  // OMEX namespace
  //
  const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces &xmlns = mAnnotation->getNamespaces();
  checkDefaultNamespace(&xmlns,"annotation");

  while (nNodes < mAnnotation->getNumChildren())
  {
    LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode topLevel = mAnnotation->getChild(nNodes);

    // the top level must be an element (so it should be a start)
    if (topLevel.isStart() == false)
    {
      logError(CaAnnotationNotElement, getLevel(), getVersion());
      nNodes++;
      continue;
    }
    std::string uri = topLevel.getURI();
    std::string prefix = topLevel.getPrefix();

#ifdef USE_LIBXML
    // sometimes libxml does not catch an empty ns with a prefix
    if (uri.empty() && !prefix.empty())
    {
      logError(BadXMLPrefix);
      nNodes++;
      continue;
    }
#endif

    // cannot be other toplevel element with this uri
    if (!uri.empty())
    {
      if (find(uri_list.begin(), uri_list.end(), uri)
                                               != uri_list.end())
      {
        string msg = "An OMEX <" + getElementName() + "> element ";
        msg += "has an <annotation> child with multiple children with the same namespace.";
        logError(CaDuplicateAnnotationNamespaces, getLevel(), getVersion(), msg);
      }
      uri_list.push_back(uri);
    }

    match = 0;
    n = 0;

    bool implicitNSdecl = false;
   // must have a namespace
    if (topLevel.getNamespaces().getLength() == 0)
    {
      // not on actual element - is it explicit ??
      if(mCa != NULL && mCa->getNamespaces() != NULL)
      /* check for implicit declaration */
      {
        for (n = 0; n < mCa->getNamespaces()->getLength(); n++)
        {
          if (!strcmp(mCa->getNamespaces()->getPrefix(n).c_str(),
                        prefix.c_str()))
          {
            implicitNSdecl = true;
            break;
          }
        }
     }


      if (!implicitNSdecl)
      {
        logError(CaMissingAnnotationNamespace);
      }
    }
    // cannot declare omex namespace
    while(!match && n < topLevel.getNamespaces().getLength())
    {
      match += !strcmp(topLevel.getNamespaces().getURI(n).c_str(),
                                          "http://identifiers.org/combine.specifications/omex-manifest");
      n++;
    }
    string msg = "An OMEX <" + getElementName() + "> element ";
    if (match > 0)
    {
      msg += "uses a restricted namespace on an element in its child <annotation>.";
      logError(CaNamespaceInAnnotation, getLevel(), getVersion(), msg);
      break;
    }

    if (implicitNSdecl && prefix.empty())
    {
      msg += "assumes the omex namespace on an element in its child <annotation>.";
      logError(CaMissingAnnotationNamespace, getLevel(), getVersion(), msg);
    }
    nNodes++;
  }
}
/** @endcond */


/** @cond doxygenLibomexInternal */
/*
 * Checks that the XHTML is valid.
 * If the xhtml does not conform to the specification of valid xhtml within
 * an omex document, an error is logged.
 */
void
CaBase::checkXHTML(const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode * xhtml)
{
  if (xhtml == NULL) return;

  const string&  name = xhtml->getName();
  unsigned int i, errorNS, errorXML, errorDOC, errorELEM;

  if (name == "notes")
  {
    errorNS   = CaNotesNotInXHTMLNamespace;
    errorXML  = CaNotesContainsXMLDecl;
    errorDOC  = CaNotesContainsDOCTYPE;
    errorELEM = CaInvalidNotesContent;
  }
  else                                  // We shouldn't ever get to this point.
  {
    logError(CaUnknown);
    return;
  }

  /*
  * errors relating to a misplaced XML or DOCTYPE declaration
  * will also cause a parser error.
  * since parsing will terminate at this error, then if it has occurred
  * it will be in the XML currently being checked and so a more
  * informative message can be added
  */
  for (i = 0; i < getErrorLog()->getNumErrors(); i++)
  {
    if (getErrorLog()->getError(i)->getErrorId() == BadXMLDeclLocation)
    {
      logError(errorXML);
    }
    if (getErrorLog()->getError(i)->getErrorId() == BadlyFormedXML)
    {
      logError(errorDOC);
    }
  }

  LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces* toplevelNS = (mCa) ? mCa->getNamespaces() : NULL;

  /*
  * namespace declaration is variable
  * if a whole html tag has been used
  * or a whole body tag then namespace can be implicitly declared
  */
  unsigned int children = xhtml->getNumChildren();

  if (children > 1)
  {
    for (i=0; i < children; i++)
    {
      if (SyntaxChecker::isAllowedElement(xhtml->getChild(i)))
      {
        if (!SyntaxChecker::hasDeclaredNS(xhtml->getChild(i),
                                                  toplevelNS))
        {
          logError(errorNS);
        }
      }
      else
      {
        logError(errorELEM);
      }
    }
  }
  else
  {
    /* only one element which can be html or body with either implicit/explicit
    * namespace declaration
    * OR could be one of the listed elements.
    */

    const string& top_name = xhtml->getChild(0).getName();

    if (top_name != "html" && top_name != "body"
      && !SyntaxChecker::isAllowedElement(xhtml->getChild(0)))
    {
      logError(errorELEM);
    }
    else
    {
      if (!SyntaxChecker::hasDeclaredNS(xhtml->getChild(0), toplevelNS))
      {
        logError(errorNS);
      }
      if (top_name == "html"
        && !SyntaxChecker::isCorrectHTMLNode(xhtml->getChild(0)))
      {
        logError(errorELEM);
      }
    }
  }
}
/** @endcond */
/** @cond doxygenLibomexInternal */
/* default for components that have no required attributes */
bool
CaBase::hasRequiredAttributes() const
{
  return true;
}

/* default for components that have no required elements */
bool
CaBase::hasRequiredElements() const
{
  return true;
}

int
CaBase::checkCompatibility(const CaBase * object) const
{
  if (object == NULL)
  {
    return LIBCOMBINE_OPERATION_FAILED;
  }
  else if (!(object->hasRequiredAttributes()) || !(object->hasRequiredElements()))
  {
    return LIBCOMBINE_INVALID_OBJECT;
  }
  else if (getLevel() != object->getLevel())
  {
    return LIBCOMBINE_LEVEL_MISMATCH;
  }
  else if (getVersion() != object->getVersion())
  {
    return LIBCOMBINE_VERSION_MISMATCH;
  }
  else if (this->matchesRequiredCaNamespacesForAddition(object) == false)
  {
    return LIBCOMBINE_NAMESPACES_MISMATCH;
  }
  else
  {
    return LIBCOMBINE_OPERATION_SUCCESS;
  }
}

/** @endcond */

/** @cond doxygenLibomexInternal */
/*
 * Stores the location (line and column) and any XML namespaces (for
 * roundtripping) declared on this OMEX (XML) element.
 */
void
CaBase::setCaBaseFields (const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLToken& element)
{
  mLine   = element.getLine  ();
  mColumn = element.getColumn();

  if (element.getNamespaces().getLength() > 0)
  {
    LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces tmpxmlns(element.getNamespaces());
    setNamespaces(&tmpxmlns);
  }
  else
  {
    setNamespaces(NULL);
  }
}


/*
 * Sets the XML namespace to which this element belongs to.
 */
int
CaBase::setElementNamespace(const std::string &uri)
{
  mURI = uri;

  return LIBCOMBINE_OPERATION_SUCCESS;
}

/*
 * Gets the XML namespace to which this element belongs to.
 */
const std::string&
CaBase::getElementNamespace() const
{
  return mURI;
}
/** @endcond */

#endif /* __cplusplus */


LIBCOMBINE_EXTERN
int
CaBase_getTypeCode (const CaBase_t *sb)
{
  return (sb != NULL) ? sb->getTypeCode() : OMEX_UNKNOWN;
}


LIBCOMBINE_EXTERN
const char *
CaBase_getMetaId (CaBase_t *sb)
{
  return (sb != NULL && sb->isSetMetaId()) ? sb->getMetaId().c_str() : NULL;
}


LIBCOMBINE_EXTERN
const CaOmexManifest_t *
CaBase_getCaOmexManifest (CaBase_t *sb)
{
  return (sb != NULL) ? sb->getCaOmexManifest() : NULL;
}


LIBCOMBINE_EXTERN
const CaBase_t *
CaBase_getParentCaObject (CaBase_t *sb)
{
  return (sb != NULL) ? sb->getParentCaObject() : NULL;
}


LIBCOMBINE_EXTERN
const CaBase_t *
CaBase_getAncestorOfType (CaBase_t *sb, int type)
{
  return (sb != NULL) ? sb->getAncestorOfType(type) : NULL;
}


LIBCOMBINE_EXTERN
unsigned int
CaBase_getLevel (const CaBase_t *sb)
{
  return (sb != NULL) ? sb->getLevel() : OMEX_INT_MAX;
}


LIBCOMBINE_EXTERN
unsigned int
CaBase_getVersion (const CaBase_t *sb)
{
  return (sb != NULL) ? sb->getVersion() : OMEX_INT_MAX;
}


LIBCOMBINE_EXTERN
XMLNode_t *
CaBase_getNotes (CaBase_t *sb)
{
  return (sb != NULL) ? sb->getNotes() : NULL;
}


LIBCOMBINE_EXTERN
char*
CaBase_getNotesString (CaBase_t *sb)
{
  return (sb != NULL && sb->isSetNotes()) ?
    safe_strdup(sb->getNotesString().c_str()) : NULL;
}


LIBCOMBINE_EXTERN
XMLNode_t *
CaBase_getAnnotation (CaBase_t *sb)
{
  return (sb != NULL) ? sb->getAnnotation() : NULL;
}


LIBCOMBINE_EXTERN
char*
CaBase_getAnnotationString (CaBase_t *sb)
{
  return (sb != NULL && sb->isSetAnnotation()) ?
    safe_strdup(sb->getAnnotationString().c_str()) : NULL;
}


LIBCOMBINE_EXTERN
int
CaBase_isSetMetaId (const CaBase_t *sb)
{
  return (sb != NULL) ? static_cast<int>( sb->isSetMetaId() ) : 0;
}


LIBCOMBINE_EXTERN
int
CaBase_isSetNotes (const CaBase_t *sb)
{
  return (sb != NULL) ? static_cast<int>( sb->isSetNotes() ) : 0;
}


LIBCOMBINE_EXTERN
int
CaBase_isSetAnnotation (const CaBase_t *sb)
{
  return (sb != NULL) ? static_cast<int>( sb->isSetAnnotation() ) : 0;
}


LIBCOMBINE_EXTERN
int
CaBase_setMetaId (CaBase_t *sb, const char *metaid)
{
  if (sb != NULL)
    return (metaid == NULL) ? sb->unsetMetaId() : sb->setMetaId(metaid);
  else
    return LIBCOMBINE_INVALID_OBJECT;
}


LIBCOMBINE_EXTERN
int
CaBase_setNamespaces (CaBase_t *sb, XMLNamespaces_t *xmlns)
{
  if (sb != NULL)
    return sb->setNamespaces(xmlns);
  else
    return LIBCOMBINE_INVALID_OBJECT;
}


LIBCOMBINE_EXTERN
int
CaBase_setNotes (CaBase_t *sb, XMLNode_t *notes)
{
  if (sb != NULL)
    return sb->setNotes(notes);
  else
    return LIBCOMBINE_INVALID_OBJECT;
}


LIBCOMBINE_EXTERN
int
CaBase_setNotesString (CaBase_t *sb, const char *notes)
{
  if (sb != NULL)
  {
    if(notes == NULL)
    {
      return sb->unsetNotes();
    }
    else
    {
      return sb->setNotes(notes);
    }
  }
  else
    return LIBCOMBINE_INVALID_OBJECT;
}


LIBCOMBINE_EXTERN
int
CaBase_setNotesStringAddMarkup (CaBase_t *sb, const char *notes)
{
  if (sb != NULL)
  {
    if(notes == NULL)
    {
      return sb->unsetNotes();
    }
    else
    {
      return sb->setNotes(notes, true);
    }
  }
  else
    return LIBCOMBINE_INVALID_OBJECT;
}


LIBCOMBINE_EXTERN
int
CaBase_appendNotes (CaBase_t *sb, XMLNode_t *notes)
{
  if (sb != NULL)
    return sb->appendNotes(notes);
  else
    return LIBCOMBINE_INVALID_OBJECT;
}


LIBCOMBINE_EXTERN
int
CaBase_appendNotesString (CaBase_t *sb, const char *notes)
{
  if (sb != NULL)
  {
    if (notes != NULL)
      return sb->appendNotes(notes);
    else
      return LIBCOMBINE_INVALID_OBJECT;
  }
  else
    return LIBCOMBINE_INVALID_OBJECT;
}


LIBCOMBINE_EXTERN
int
CaBase_setAnnotation (CaBase_t *sb, XMLNode_t *annotation)
{
  if (sb != NULL)
    return sb->setAnnotation(annotation);
  else
    return LIBCOMBINE_INVALID_OBJECT;
}


LIBCOMBINE_EXTERN
int
CaBase_setAnnotationString (CaBase_t *sb, const char *annotation)
{
  if (sb != NULL)
  {
    if(annotation == NULL)
    {
      return sb->unsetAnnotation();
    }
    else
    {
      return sb->setAnnotation(annotation);
    }
  }
  else
    return LIBCOMBINE_INVALID_OBJECT;
}


LIBCOMBINE_EXTERN
int
CaBase_appendAnnotation (CaBase_t *sb, XMLNode_t *annotation)
{
  if (sb != NULL)
    return sb->appendAnnotation(annotation);
  else
    return LIBCOMBINE_INVALID_OBJECT;
}


LIBCOMBINE_EXTERN
int
CaBase_appendAnnotationString (CaBase_t *sb, const char *annotation)
{
  if (sb != NULL)
  {
    if (annotation != NULL)
      return sb->appendAnnotation(annotation);
    else
      return LIBCOMBINE_INVALID_OBJECT;
  }
  else
    return LIBCOMBINE_INVALID_OBJECT;
}

LIBCOMBINE_EXTERN
int
CaBase_removeTopLevelAnnotationElement (CaBase_t *sb, const char *name)
{
  if (sb != NULL)
  {
    if (name != NULL)
      return sb->removeTopLevelAnnotationElement(name);
    else
      return LIBCOMBINE_INVALID_OBJECT;
  }
  else
    return LIBCOMBINE_INVALID_OBJECT;
}


LIBCOMBINE_EXTERN
int
CaBase_removeTopLevelAnnotationElementWithURI (CaBase_t *sb, const char *name,
                                              const char *uri)
{
  if (sb != NULL)
  {
    if (name != NULL && uri != NULL)
      return sb->removeTopLevelAnnotationElement(name, uri);
    else
      return LIBCOMBINE_INVALID_OBJECT;
  }
  else
    return LIBCOMBINE_INVALID_OBJECT;
}


LIBCOMBINE_EXTERN
int
CaBase_replaceTopLevelAnnotationElement (CaBase_t *sb, XMLNode_t *annotation)
{
  if (sb != NULL)
  {
    if (annotation != NULL)
      return sb->replaceTopLevelAnnotationElement(annotation);
    else
      return LIBCOMBINE_INVALID_OBJECT;
  }
  else
    return LIBCOMBINE_INVALID_OBJECT;
}


LIBCOMBINE_EXTERN
int
CaBase_replaceTopLevelAnnotationElementString (CaBase_t *sb, const char *annotation)
{
  if (sb != NULL)
  {
    if (annotation != NULL)
      return sb->replaceTopLevelAnnotationElement(annotation);
    else
      return LIBCOMBINE_INVALID_OBJECT;
  }
  else
    return LIBCOMBINE_INVALID_OBJECT;
}


LIBCOMBINE_EXTERN
int
CaBase_unsetMetaId (CaBase_t *sb)
{
  if (sb != NULL)
    return sb->unsetMetaId();
  else
    return LIBCOMBINE_INVALID_OBJECT;
}


LIBCOMBINE_EXTERN
int
CaBase_unsetNotes (CaBase_t *sb)
{
  if (sb != NULL)
    return sb->unsetNotes();
  else
    return LIBCOMBINE_INVALID_OBJECT;
}


LIBCOMBINE_EXTERN
int
CaBase_unsetAnnotation (CaBase_t *sb)
{
  if (sb != NULL)
    return sb->unsetAnnotation();
  else
    return LIBCOMBINE_INVALID_OBJECT;
}


LIBCOMBINE_EXTERN
const char *
CaBase_getElementName (const CaBase_t *sb)
{
  return (sb != NULL && !(sb->getElementName().empty())) ?
    sb->getElementName().c_str() : NULL;
}


LIBCOMBINE_EXTERN
unsigned int
CaBase_getLine (const CaBase_t *sb)
{
  return (sb != NULL) ? sb->getLine() : 0;
}


LIBCOMBINE_EXTERN
unsigned int
CaBase_getColumn (const CaBase_t *sb)
{
  return (sb != NULL) ? sb->getColumn() : 0;
}


LIBCOMBINE_EXTERN
int
CaBase_hasValidLevelVersionNamespaceCombination(CaBase_t *sb)
{
  return (sb != NULL) ?
    static_cast <int> (sb->hasValidLevelVersionNamespaceCombination()) : 0;
}


LIBCOMBINE_EXTERN
int
CaBase_setUserData(CaBase_t* sb, void *userData)
{
  if (sb == NULL) return LIBCOMBINE_INVALID_OBJECT;
  return sb->setUserData(userData);
}


LIBCOMBINE_EXTERN
void *
CaBase_getUserData(const CaBase_t* sb)
{
  if (sb == NULL) return NULL;
  return sb->getUserData();
}

LIBCOMBINE_EXTERN
int
CaBase_isSetUserData(const CaBase_t* sb)
{
  if (sb == NULL) return 0;
  return static_cast <int>(sb->isSetUserData());
}

LIBCOMBINE_EXTERN
int
CaBase_unsetUserData(CaBase_t* sb)
{
  if (sb == NULL) return LIBCOMBINE_INVALID_OBJECT;
  return sb->unsetUserData();
}

LIBCOMBINE_EXTERN
CaBase_t*
CaBase_getElementByMetaId(CaBase_t* sb, const char* metaid)
{
  if (sb == NULL) return NULL;
  return sb->getElementByMetaId(metaid);
}

LIBCOMBINE_EXTERN
List_t*
CaBase_getAllElements(CaBase_t* sb)
{
  if (sb == NULL) return NULL;
  return sb->getAllElements();
}

/** @endcond */

LIBCOMBINE_CPP_NAMESPACE_END
