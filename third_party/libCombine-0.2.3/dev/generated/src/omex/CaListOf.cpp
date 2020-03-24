/**
 * @file CaListOf.cpp
 * @brief Implementation of the CaListOf class.
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


#include <algorithm>
#include <functional>

#include <omex/CaVisitor.h>
#include <omex/CaListOf.h>
#include <omex/common/common.h>

/** @cond doxygenIgnored */

using namespace std;

/** @endcond */

LIBCOMBINE_CPP_NAMESPACE_BEGIN
#ifdef __cplusplus

/*
 * Creates a new CaListOf items.
 */
CaListOf::CaListOf (unsigned int level, unsigned int version)
: CaBase(level,version)
{
    if (!hasValidLevelVersionNamespaceCombination())
    throw CaConstructorException();
}


/*
 * Creates a new CaListOf items.
 */
CaListOf::CaListOf (CaNamespaces* omexns)
: CaBase(omexns)
{
    if (!hasValidLevelVersionNamespaceCombination())
    throw CaConstructorException();
}


/**
 * Used by the Destructor to delete each item in mItems.
 */
struct Delete : public unary_function<CaBase*, void>
{
  void operator() (CaBase* sb) { delete sb; }
};


/*
 * Destroys the given CaListOf and its constituent items.
 */
CaListOf::~CaListOf ()
{
  for_each( mItems.begin(), mItems.end(), Delete() );
}


/**
 * Used by the Copy Constructor to clone each item in mItems.
 */
struct Clone : public unary_function<CaBase*, CaBase*>
{
  CaBase* operator() (CaBase* sb) { return sb->clone(); }
};


/*
 * Copy constructor. Creates a copy of this CaListOf items.
 */
CaListOf::CaListOf (const CaListOf& orig) : CaBase(orig), mItems()
{
  mItems.resize( orig.size() );
  transform( orig.mItems.begin(), orig.mItems.end(), mItems.begin(), Clone() );
  connectToChild();
}


/*
 * Assignment operator
 */
CaListOf& CaListOf::operator=(const CaListOf& rhs)
{
  if(&rhs!=this)
  {
    this->CaBase::operator =(rhs);
    // Deletes existing items
    for_each( mItems.begin(), mItems.end(), Delete() );
    mItems.resize( rhs.size() );
    transform( rhs.mItems.begin(), rhs.mItems.end(), mItems.begin(), Clone() );
    connectToChild();
  }

  return *this;
}

/** @cond doxygenLibomexInternal */
bool
CaListOf::accept (CaVisitor& v) const
{
  v.visit(*this, getItemTypeCode() );
  for (unsigned int n = 0 ; n < mItems.size() && mItems[n]->accept(v); ++n) ;
  v.leave(*this, getItemTypeCode() );

  return true;
}
/** @endcond */


/*
 * @return a (deep) copy of this CaListOf items.
 */
CaListOf*
CaListOf::clone () const
{
  return new CaListOf(*this);
}


/*
 * Inserts the item at the given location.  This CaListOf items assumes
 * no ownership of item and will not delete it.
 */
int 
CaListOf::insert(int location, const CaBase* item)
{
  return insertAndOwn(location, item->clone());
}


/*
 * Inserts the item at the given location.  This CaListOf items assumes
 * ownership of item and will delete it.
 */
int 
CaListOf::insertAndOwn(int location, CaBase* item)
{
  /* no list elements yet */
  if (this->getItemTypeCode() == OMEX_UNKNOWN )
  {
    mItems.insert( mItems.begin() + location, item );
    item->connectToParent(this);
    return LIBCOMBINE_OPERATION_SUCCESS;
  }
  else if (!isValidTypeForList(item))
  {
    return LIBCOMBINE_INVALID_OBJECT;
  }
  else
  {
    mItems.insert( mItems.begin() + location, item );
    item->connectToParent(this);
    return LIBCOMBINE_OPERATION_SUCCESS;
  }
}


/*
 * Adds item to the end of this CaListOf items.  This CaListOf items assumes
 * no ownership of item and will not delete it.
 */
int
CaListOf::append (const CaBase* item)
{
  CaBase* clone = item->clone();
  int ret = appendAndOwn( clone );
  if (ret != LIBCOMBINE_OPERATION_SUCCESS) 
  {
    delete clone;
  }
  return ret;
}


/*
 * Adds item to the end of this CaListOf items.  This CaListOf items assumes
 * ownership of item and will delete it.
 */
int
CaListOf::appendAndOwn (CaBase* item)
{
  /* no list elements yet */
  if (this->getItemTypeCode() == OMEX_UNKNOWN )
  {
    mItems.push_back( item );
    item->connectToParent(this);
    return LIBCOMBINE_OPERATION_SUCCESS;
  }
  else if (!isValidTypeForList(item))
  {
    return LIBCOMBINE_INVALID_OBJECT;
  }
  else
  {
    mItems.push_back( item );
    item->connectToParent(this);
    return LIBCOMBINE_OPERATION_SUCCESS;
  }
}

int CaListOf::appendFrom(const CaListOf* list)
{
  if (list==NULL) return LIBCOMBINE_INVALID_OBJECT;
  
  if (getItemTypeCode() != list->getItemTypeCode()) 
  {
    return LIBCOMBINE_INVALID_OBJECT;
  }
  
  int ret = LIBCOMBINE_OPERATION_SUCCESS;
  
  for (unsigned int item=0; item<list->size(); item++) 
  {
    ret = appendAndOwn(list->get(item)->clone());
    if (ret != LIBCOMBINE_OPERATION_SUCCESS) return ret;
  }
  return ret;
}

/*
 * @return the nth item in this CaListOf items.
 */
const CaBase*
CaListOf::get (unsigned int n) const
{
  return (n < mItems.size()) ? mItems[n] : NULL;
}


/*
 * @return the nth item in this CaListOf items.
 */
CaBase*
CaListOf::get (unsigned int n)
{
  return const_cast<CaBase*>( static_cast<const CaListOf&>(*this).get(n) );
}


CaBase*
CaListOf::getElementBySId(const std::string& id)
{
  if (id.empty()) return NULL;
  
  for (unsigned int i = 0; i < size(); i++)
  {
    CaBase* obj = get(i);
    if (obj->getId() == id)
    {
      return obj;
    }
    
    obj = obj->getElementBySId(id);
    
    if (obj != NULL) return obj;
  }

  return NULL;
}


CaBase*
CaListOf::getElementByMetaId(const std::string& metaid)
{
  if (metaid.empty()) return NULL;
  
  for (unsigned int i = 0; i < size(); i++)
  {
    CaBase* obj = get(i);
    if (obj->getMetaId() == metaid)
    {
      return obj;
    }
    
    obj = obj->getElementByMetaId(metaid);
    
    if (obj != NULL) return obj;
  }

  return NULL;
}


List*
CaListOf::getAllElements()
{
  List* ret = new List();
  List* sublist = NULL;
  
  for (unsigned int i = 0; i < size(); i++) 
  {
    CaBase* obj = get(i);
    ret->add(obj);
    sublist = obj->getAllElements();
    ret->transferFrom(sublist);
    delete sublist;
  }

  return ret;
}


/*
 * Removes all items in this CaListOf object.
 *
 * If doDelete is true (default), all items in this CaListOf object are deleted
 * and cleared, and thus the caller doesn't have to delete those items.
 * Otherwise, all items are just cleared from this CaListOf object and the caller
 * is responsible for deleting all items (In this case, pointers to all items
 * should be stored elsewhere before calling this function by the caller).
 */
void
CaListOf::clear (bool doDelete)
{
  if (doDelete)
    for_each( mItems.begin(), mItems.end(), Delete() );
  
  mItems.clear();
}


int CaListOf::removeFromParentAndDelete()
{
  clear(true);
  unsetAnnotation();
  unsetMetaId();
  unsetNotes();
  return LIBCOMBINE_OPERATION_SUCCESS;
}

/*
 * Removes the nth item from this CaListOf items and returns a pointer to
 * it.  The caller owns the returned item and is responsible for deleting
 * it.
 */
CaBase*
CaListOf::remove (unsigned int n)
{
  CaBase* item = get(n);
  
  if (item != NULL) mItems.erase( mItems.begin() + n );
  
  return item;
}


/*
 * @return the number of items in this CaListOf items.
 */
unsigned int
CaListOf::size () const
{
  return (unsigned int)mItems.size();
}


/**
 * Used by CaListOf::setCaOmexManifest().
 */
struct SetCaOmexManifest : public unary_function<CaBase*, void>
{
  CaOmexManifest* d;

  SetCaOmexManifest (CaOmexManifest* d) : d(d) { }
  void operator() (CaBase* sbase) { sbase->setCaOmexManifest(d); }
};


/**
 * Used by CaListOf::setParentCaObject().
 */
struct SetParentCaObject : public unary_function<CaBase*, void>
{
  CaBase* sb;

  SetParentCaObject (CaBase *sb) : sb(sb) { }
  void operator() (CaBase* sbase) { sbase->connectToParent(sb); }
};

/** @cond doxygenLibomexInternal */

/*
 * Sets the parent CaOmexManifest of this OMEX object.
 */
void
CaListOf::setCaOmexManifest (CaOmexManifest* d)
{
  CaBase::setCaOmexManifest(d);
  for_each( mItems.begin(), mItems.end(), SetCaOmexManifest(d) );
}


/*
 * Sets this OMEX object to child OMEX objects (if any).
 * (Creates a child-parent relationship by the parent)
  */
void
CaListOf::connectToChild()
{
  CaBase::connectToChild();
  for_each( mItems.begin(), mItems.end(), SetParentCaObject(this) );
}

/** @endcond */


/*
 * @return the typecode (int) of this OMEX object or OMEX_UNKNOWN
 * (default).
 */
int
CaListOf::getTypeCode () const
{
  return OMEX_LIST_OF;
}


/*
 * @return the typecode (int) of OMEX objects contained in this CaListOf or
 * OMEX_UNKNOWN (default).
 */
int
CaListOf::getItemTypeCode () const
{
  return OMEX_UNKNOWN;
}


/*
 * @return the name of this element ie "listOf".
 
 */
const string&
CaListOf::getElementName () const
{
  static const string name = "listOf";
  return name;
}


/**
 * Used by CaListOf::writeElements().
 */
struct Write : public unary_function<CaBase*, void>
{
  XMLOutputStream& stream;

  Write (XMLOutputStream& s) : stream(s) { }
  void operator() (CaBase* sbase) { sbase->write(stream); }
};


/** @cond doxygenLibomexInternal */
/*
 * Subclasses should override this method to write out their contained
 * OMEX objects as XML elements.  Be sure to call your parents
 * implementation of this method as well.
 */
void
CaListOf::writeElements (XMLOutputStream& stream) const
{
  CaBase::writeElements(stream);
  for_each( mItems.begin(), mItems.end(), Write(stream) );
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
CaListOf::addExpectedAttributes(ExpectedAttributes& attributes)
{
  CaBase::addExpectedAttributes(attributes);
}


/*
 * Subclasses should override this method to read values from the given
 * XMLAttributes set into their specific fields.  Be sure to call your
 * parents implementation of this method as well.
 */
void
CaListOf::readAttributes (const XMLAttributes& attributes,
                       const ExpectedAttributes& expectedAttributes)
{
  CaBase::readAttributes(attributes,expectedAttributes);

  //
  // sboTerm: SBOTerm { use="optional" }  (L2v3 ->)
  // is read in CaBase::readAttributes()
  //
}

void 
CaListOf::writeAttributes (XMLOutputStream& stream) const
{
  CaBase::writeAttributes(stream);
}


bool
CaListOf::isValidTypeForList(CaBase * item)
{
  bool match = false;

  match = (item->getTypeCode() == getItemTypeCode());

  return match;
}
/** @endcond */



#endif /* __cplusplus */
/** @cond doxygenIgnored */
LIBCOMBINE_EXTERN
CaListOf_t *
CaListOf_create (unsigned int level, unsigned int version)
{
  return new(nothrow) CaListOf(level,version);
}


LIBCOMBINE_EXTERN
void
CaListOf_free (CaListOf_t *lo)
{
  if (lo != NULL)
  delete lo;
}


LIBCOMBINE_EXTERN
CaListOf_t *
CaListOf_clone (const CaListOf_t *lo)
{
  return (lo != NULL) ? static_cast<CaListOf_t*>( lo->clone() ) : NULL;
}


LIBCOMBINE_EXTERN
int
CaListOf_append (CaListOf_t *lo, const CaBase *item)
{
  if (lo != NULL)
    return lo->append(item);
  else
    return LIBCOMBINE_INVALID_OBJECT;
}


LIBCOMBINE_EXTERN
int
CaListOf_appendAndOwn (CaListOf_t *lo, CaBase_t *item)
{
  if (lo != NULL)
    return lo->appendAndOwn(item);
  else
    return LIBCOMBINE_INVALID_OBJECT;
}


LIBCOMBINE_EXTERN
int
CaListOf_appendFrom (CaListOf_t *lo, CaListOf_t *list)
{
  if (lo != NULL)
    return lo->appendFrom(list);
  else
    return LIBCOMBINE_INVALID_OBJECT;
}


LIBCOMBINE_EXTERN
int
CaListOf_insert (CaListOf_t *lo, int location, const CaBase_t *item)
{
  if (lo != NULL)
    return lo->insert(location, item);
  else
    return LIBCOMBINE_INVALID_OBJECT;
}


LIBCOMBINE_EXTERN
int
CaListOf_insertAndOwn (CaListOf_t *lo, int location, CaBase_t *item)
{
  if (lo != NULL)
    return lo->insertAndOwn(location, item);
  else
    return LIBCOMBINE_INVALID_OBJECT;
}


LIBCOMBINE_EXTERN
CaBase *
CaListOf_get (CaListOf_t *lo, unsigned int n)
{
  return (lo != NULL) ? lo->get(n) : NULL;
}


LIBCOMBINE_EXTERN
void
CaListOf_clear (CaListOf_t *lo, int doDelete)
{
  if (lo != NULL)
  lo->clear(doDelete);
}


LIBCOMBINE_EXTERN
CaBase *
CaListOf_remove (CaListOf_t *lo, unsigned int n)
{
  return (lo != NULL) ? lo->remove(n) : NULL;
}


LIBCOMBINE_EXTERN
unsigned int
CaListOf_size (const CaListOf_t *lo)
{
  return (lo != NULL) ? lo->size() : OMEX_INT_MAX;
}


LIBCOMBINE_EXTERN
int
CaListOf_getItemTypeCode (const CaListOf_t *lo)
{
  return (lo != NULL) ? lo->getItemTypeCode() : OMEX_UNKNOWN;
}

/** @endcond */

LIBCOMBINE_CPP_NAMESPACE_END

