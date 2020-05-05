/**
 * @file CaListOf.h
 * @brief Definition of the CaListOf class.
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
 *
 * @class CaListOf
 * @sbmlbrief{} TODO:Definition of the CaListOf class.
 */


#ifndef CaListOf_h
#define CaListOf_h


#include <omex/common/extern.h>
#include <omex/common/combinefwd.h>
#include <omex/CaTypeCodes.h>


#ifdef __cplusplus


#include <vector>
#include <algorithm>
#include <functional>

#include <omex/CaBase.h>

LIBCOMBINE_CPP_NAMESPACE_BEGIN

class CaVisitor;


/** @cond doxygenLibomexInternal */
/**
 * Used by CaListOf::get() to lookup an CaBase based by its id.
 */
#ifndef SWIG
template<class CNAME>
struct CaIdEq : public std::unary_function<CaBase*, bool>
{
  const std::string& id;

  CaIdEq (const std::string& id) : id(id) { }
  bool operator() (CaBase* sb) 
       { return static_cast <CNAME*> (sb)->getId() == id; }
};
#endif /* SWIG */
/** @endcond */


class LIBCOMBINE_EXTERN CaListOf : public CaBase
{
public:

  /**
   * Creates a new CaListOf object.
   *
   * @param level the OMEX Level; if not assigned, defaults to the
   * value of OMEX_DEFAULT_LEVEL.
   *
   * @param version the Version within the OMEX Level; if not assigned,
   * defaults to the value of OMEX_DEFAULT_VERSION.
   */
  CaListOf (unsigned int level   = OMEX_DEFAULT_LEVEL,
          unsigned int version = OMEX_DEFAULT_VERSION);


  /**
   * Creates a new CaListOf with a given CaNamespaces object.
   *
   * @param omexns the set of OMEX namespaces that this CaListOf should
   * contain.
   */
  CaListOf (CaNamespaces* omexns);


  /**
   * Destroys this CaListOf and the items inside it.
   */
  virtual ~CaListOf ();


  /**
   * Copy constructor; creates a copy of this CaListOf.
   *
   * @param orig the CaListOf instance to copy.
   */
  CaListOf (const CaListOf& orig);


  /**
   * Assignment operator for CaListOf.
   */
  CaListOf& operator=(const CaListOf& rhs);



  /** @cond doxygenLibomexInternal */
  /**
   * Accepts the given CaVisitor.
   *
   * @param v the CaVisitor instance to be used.
   *
   * @return the result of calling <code>v.visit()</code>, which indicates
   * whether the Visitor would like to visit the next item in the
   * list.
   */
  virtual bool accept (CaVisitor& v) const;
  /** @endcond */


  /**
   * Creates and returns a deep copy of this CaListOf object.
   *
   * @return the (deep) copy of this CaListOf object.
   */
  virtual CaListOf* clone () const;


  /**
   * Adds an item to the end of this CaListOf's list of items.
   *
   * This method makes a clone of the @p item handed to it.  This means that
   * when the CaListOf object is destroyed, the original items will not be
   * destroyed.  For a method with an alternative ownership behavior, see the
   * CaListOf::appendAndOwn(@if java CaBase@endif) method.
   *
   * @param item the item to be added to the list.
   *
   * @copydetails doc_returns_success_code
   * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
   * @li @omexconstant{LIBCOMBINE_INVALID_OBJECT, OperationReturnValues_t}
   *
   * @see appendAndOwn(CaBase* disownedItem)
   * @see appendFrom(const CaListOf* list)
   */
  int append (const CaBase* item);


  /**
   * Adds an item to the end of this CaListOf's list of items.
   *
   * This method does not clone the @p disownedItem handed to it; instead, it assumes
   * ownership of it.  This means that when the CaListOf is destroyed, the item
   * will be destroyed along with it.  For a method with an alternative
   * ownership behavior, see the CaListOf::append(CaBase* item) method.
   *
   * @param disownedItem the item to be added to the list.
   *
   * @copydetails doc_returns_success_code
   * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
   * @li @omexconstant{LIBCOMBINE_INVALID_OBJECT, OperationReturnValues_t}
   *
   * @see append(const CaBase* item)
   * @see appendFrom(const CaListOf* list)
   */
  int appendAndOwn (CaBase* disownedItem);


  /**
   * Adds a clone of a list of items to this CaListOf's list.
   *
   * Note that because this clones the objects handed to it, the original
   * items will not be destroyed when this CaListOf object is destroyed.
   *
   * @param list a list of items to be added.
   *
   * @copydetails doc_returns_success_code
   * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
   * @li @omexconstant{LIBCOMBINE_INVALID_OBJECT, OperationReturnValues_t}
   *
   * @see append(const CaBase* item)
   * @see appendAndOwn(CaBase* disownedItem)
   */
  virtual int appendFrom (const CaListOf* list);


  /**
   * Inserts an item at a given position in this CaListOf's list of items.
   *
   * This variant of the method makes a clone of the @p item handed to it.
   * This means that when the CaListOf is destroyed, the original @p item will
   * <em>not</em> be destroyed.
   *
   * @param location the location in the list where to insert the item.
   * @param item the item to be inserted to the list.
   *
   * @copydetails doc_returns_success_code
   * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
   * @li @omexconstant{LIBCOMBINE_INVALID_OBJECT, OperationReturnValues_t}
   *
   * @see insertAndOwn(int location, CaBase* item)
   */
  int insert (int location, const CaBase* item);


  /**
   * Inserts an item at a given position in this CaListOf's list of items.
   *
   * This variant of the method does not make a clone of the @p disownedItem handed to it.
   * This means that when the CaListOf is destroyed, the original @p item
   * <em>will</em> be destroyed.
   *
   * @param location the location where to insert the item
   * @param disownedItem the item to be inserted to the list
   *
   * @copydetails doc_returns_success_code
   * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
   * @li @omexconstant{LIBCOMBINE_INVALID_OBJECT, OperationReturnValues_t}
   *
   * @see insert(int location, const CaBase* item)
   */
  int insertAndOwn(int location, CaBase* disownedItem);


  /**
   * Get an item from the list.
   *
   * @param n the index number of the item to get.
   *
   * @return the <em>n</em>th item in this CaListOf items, or a null pointer if
   * the index number @p n refers to a nonexistent position in this list.
   *
   * @see size()
   */
  virtual const CaBase* get (unsigned int n) const;


  /**
   * Get an item from the list.
   *
   * @param n the index number of the item to get.
   * 
   * @return the <em>n</em>th item in this CaListOf items, or a null pointer if
   * the index number @p n refers to a nonexistent position in this list.
   *
   * @see size()
   */
  virtual CaBase* get (unsigned int n);


  /**
   * Returns the first child element it can find with a specific "id"
   * attribute value, or @c NULL if no such object is found.
   *
   * @param id string representing the "id" attribute value of the
   * object to find.
   *
   * @return pointer to the first element found with the given identifier.
   */
  virtual CaBase* getElementBySId(const std::string& id);


  /**
   * Returns the first child element found with the given meta-identifier.
   *
   * @param metaid string representing the "metaid" attribute of the object
   * to find.
   *
   * @return the first element found with the given @p metaid, or @c NULL if
   * no such object is found.
   */
  virtual CaBase* getElementByMetaId(const std::string& metaid);


  /**
   * Returns a List of all child CaBase objects.
   *
   * The values returned include all children of the objects in this CaListOf
   * list, nested to an arbitrary depth.
   *
   * @return a List of pointers to all child objects.
   */
  virtual List* getAllElements();


  /**
   * Removes all items in this CaListOf object.
   *
   * If parameter @p doDelete is @c true (default), all items in this CaListOf
   * object are deleted and cleared, and thus the caller doesn't have to
   * delete those items.  Otherwise, all items are cleared only from this
   * CaListOf object; the caller is still responsible for deleting the actual
   * items.  (In the latter case, callers are advised to store pointers to
   * all items elsewhere before calling this function.)
   *
   * @param doDelete if @c true (default), all items are deleted and cleared.
   * Otherwise, all items are just cleared and not deleted.
   *
   * @ifnot hasDefaultArgs @htmlinclude warn-default-args-in-docs.html @endif@~
   */
  void clear (bool doDelete = true);


  /**
   * Removes all items in this CaListOf object and deletes its properties too.
   *
   * This performs a call to clear() with an argument of @c true (thus removing
   * all the child objects in the list), followed by calls to various libCombine
   * <code>unset<em>Foo</em></code> methods to delete everything else: CVTerm
   * objects, model history objects, etc.
   *
   * @if cpp Implementations of subclasses of CaListOf may need to override
   * this method if different handling of child objects is needed.@endif@~
   *
   * @copydetails doc_returns_success_code
   * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
   */
  virtual int removeFromParentAndDelete();


  /**
   * Removes the <em>n</em>th item from this CaListOf list of items and returns
   * it.
   *
   * The caller owns the returned item and is responsible for deleting it.
   *
   * @param n the index of the item to remove
   *
   * @see size()
   */
  virtual CaBase* remove (unsigned int n);


  /**
   * Returns number of items in this CaListOf list.
   *
   * @return the number of items in this CaListOf items.
   */
  unsigned int size () const;


  /** @cond doxygenLibomexInternal */
  /**
   * Sets the parent CaOmexManifest of this OMEX object.
   *
   * @param d the CaOmexManifest that should become the parent of this
   * CaListOf.
   */
  virtual void setCaOmexManifest (CaOmexManifest* d);
  /** @endcond */


  /** @cond doxygenLibomexInternal */
  /**
   * Sets this OMEX object to child OMEX objects (if any).
   * (Creates a child-parent relationship by the parent)
   *
   * Subclasses must override this function if they define
   * one ore more child elements.
   * Basically, this function needs to be called in
   * constructor, copy constructor and assignment operator.
   *
   * @if cpp
   * @see setCaOmexManifest()
   * @see enablePackageInternal()
   * @endif
   */
  virtual void connectToChild ();
  /** @endcond */


  /**
   * Returns the libCombine type code for this object, namely,
   * @omexconstant{OMEX_LIST_OF, CaTypeCode_t}.
   * 
   * @copydetails doc_what_are_typecodes
   *
   * @return the OMEX type code for this object:
   * @omexconstant{OMEX_LIST_OF, CaTypeCode_t} (default).
   *
   * @note The various CaListOf classes mostly differ from each other in what they
   * contain.  Hence, one must call getItemTypeCode() to fully determine the
   * class of this OMEX object.
   *
   * @see getItemTypeCode()
   * @see getElementName()
   */
  virtual int getTypeCode () const;


  /**
   * Get the type code of the objects contained in this CaListOf.
   *
   * Classes that inherit from the CaListOf class should override this method
   * to return the OMEX type code for the objects contained in this CaListOf.
   * If they do not, this method will return
   * @omexconstant{OMEX_UNKNOWN, CaTypeCode_t}
   *
   * @return The CaListOf base class contains no OMEX objects, and therefore
   * this method returns @omexconstant{OMEX_UNKNOWN, CaTypeCode_t}.
   *
   * @see getElementName()
   * @see getPackageName()
   */
  virtual int getItemTypeCode () const;


  /**
   * Returns the XML element name of this object, which for CaListOf, is
   * always @c "listOf".
   *
   * @return the XML name of this element.
   */
  virtual const std::string& getElementName () const;


  /** @cond doxygenLibomexInternal */
  /**
   * Subclasses should override this method to write out their contained
   * OMEX objects as XML elements.  Be sure to call your parents
   * implementation of this method as well.
   */
  virtual void writeElements (XMLOutputStream& stream) const;
  /** @endcond */


protected:
  /** @cond doxygenLibomexInternal */
  typedef std::vector<CaBase*>           ListItem;
  typedef std::vector<CaBase*>::iterator ListItemIter;

  /**
   * Subclasses should override this method to get the list of
   * expected attributes.
   * This function is invoked from corresponding readAttributes()
   * function.
   */
  virtual void addExpectedAttributes(ExpectedAttributes& attributes);

  
  /**
   * Subclasses should override this method to read values from the given
   * XMLAttributes set into their specific fields.  Be sure to call your
   * parents implementation of this method as well.
   */
  virtual void readAttributes (const XMLAttributes& attributes,
                               const ExpectedAttributes& expectedAttributes);

  /**
   * Subclasses should override this method to write their XML attributes
   * to the XMLOutputStream.  Be sure to call your parents implementation
   * of this method as well.  For example:
   *
   *   CaBase::writeAttributes(stream);
   *   stream.writeAttribute( "id"  , mId   );
   *   stream.writeAttribute( "name", mName );
   *   ...
   */
  virtual void writeAttributes (XMLOutputStream& stream) const;

  virtual bool isValidTypeForList(CaBase * item);

  ListItem mItems;

  /** @endcond */
};

LIBCOMBINE_CPP_NAMESPACE_END

#endif  /* __cplusplus */


#ifndef SWIG

LIBCOMBINE_CPP_NAMESPACE_BEGIN
BEGIN_C_DECLS


/**
 * Creates a new instance of a CaListOf_t structure.
 *
 * @param level an unsigned int, the OMEX Level to assign to this
 * CaListOf_t structure.
 *
 * @param version an unsigned int, the OMEX Version to assign to this
 * CaListOf_t structure.
 *
 * @return a pointer to the newly-created CaListOf_t structure.
 *
 * @memberof CaListOf_t
 */
LIBCOMBINE_EXTERN
CaListOf_t *
CaListOf_create (unsigned int level, unsigned int version);


/**
 * Frees the given CaListOf_t structure.
 *
 * This function assumes each item in the list is derived from CaBase_t.
 *
 * @param lo the CaListOf_t structure to be freed.
 *
 * @memberof CaListOf_t
 */
LIBCOMBINE_EXTERN
void
CaListOf_free (CaListOf_t *lo);


/**
 * Creates a deep copy of the given CaListOf_t structure.
 *
 * @param lo the CaListOf_t structure to be copied.
 *
 * @return a (deep) copy of the given CaListOf_t structure, or a null
 * pointer if a failure occurred.
 *
 * @memberof CaListOf_t
 */
LIBCOMBINE_EXTERN
CaListOf_t *
CaListOf_clone (const CaListOf_t *lo);


/**
 * Adds a copy of a given item to the end of a CaListOf_t list.
 *
 * @param lo the CaListOf_t structure to which the @p item should be appended.
 * @param item the item to append to the list.
 *
 * @copydetails doc_returns_success_code
 * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
 * @li @omexconstant{LIBCOMBINE_INVALID_OBJECT, OperationReturnValues_t}
 *
 * @see CaListOf_appendAndOwn()
 *
 * @memberof CaListOf_t
 */
LIBCOMBINE_EXTERN
int
CaListOf_append (CaListOf_t *lo, const CaBase_t *item);


/**
 * Adds the given item to the end of a CaListOf_t list.
 *
 * @param lo the CaListOf_t structure to which the @p disownedItem should be appended.
 * @param disownedItem the item to append to the list.
 *
 * Unlike CaListOf_append(), this function does not copy the @p disownedItem.
 * The given @p lo list will contain the original item.
 *
 * @copydetails doc_returns_success_code
 * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
 * @li @omexconstant{LIBCOMBINE_INVALID_OBJECT, OperationReturnValues_t}
 *
 * @see CaListOf_append()
 *
 * @memberof CaListOf_t
 */
LIBCOMBINE_EXTERN
int
CaListOf_appendAndOwn (CaListOf_t *lo, CaBase_t *disownedItem);


/**
 * Adds clones a list of items from one list to another.
 *
 * @param lo the CaListOf_t list to which @p list will be appended.
 * @param list the list of items to append to @p lo.
 *
 * @copydetails doc_returns_success_code
 * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
 * @li @omexconstant{LIBCOMBINE_INVALID_OBJECT, OperationReturnValues_t}
 *
 * @memberof CaListOf_t
 */
LIBCOMBINE_EXTERN
int
CaListOf_appendFrom (CaListOf_t *lo, CaListOf_t *list);


/**
 * Inserts a copy of an item into a CaListOf_t list at a given position.
 *
 * @param lo the list into which @p item will be inserted.
 * @param location the starting index for the @p item in the @p lo list.
 * @param item the item to append to insert into @p lo.
 *
 * @copydetails doc_returns_success_code
 * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
 * @li @omexconstant{LIBCOMBINE_INVALID_OBJECT, OperationReturnValues_t}
 *
 * @memberof CaListOf_t
 */
LIBCOMBINE_EXTERN
int
CaListOf_insert (CaListOf_t *lo, int location, const CaBase_t *item);


/**
 * Inserts an item into a CaListOf_t list at a given position.
 *
 * Unlike CaListOf_insert(), this function does not clone @p disownedItem before
 * inserting it into @p lo, which means that @p lo becomes the owner.
 *
 * @param lo the list into which @p disownedItem will be inserted.
 * @param location the starting index for the @p disownedItem in the @p lo list.
 * @param disownedItem the item to append to insert into @p lo.
 *
 * @copydetails doc_returns_success_code
 * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
 * @li @omexconstant{LIBCOMBINE_INVALID_OBJECT, OperationReturnValues_t}
 *
 * @memberof CaListOf_t
 */
LIBCOMBINE_EXTERN
int
CaListOf_insertAndOwn (CaListOf_t *lo, int location, CaBase_t *disownedItem);


/**
 * Returns the <em>n</em>th item of a given list.
 *
 * @param lo the list from which to retrieve the item.
 * @param n the index of the item to retrieve.
 *
 * @return the <em>n</em>th item in this CaListOf items, or a null pointer if
 * the index number @p n refers to a nonexistent position in @p lo.
 *
 * @see CaListOf_size()
 *
 * @memberof CaListOf_t
 */
LIBCOMBINE_EXTERN
CaBase_t *
CaListOf_get (CaListOf_t *lo, unsigned int n);


/**
 * Removes all items in this CaListOf_t structure.
 *
 * If @p doDelete is true (non-zero), all items in this CaListOf_t structure
 * are both deleted and cleared, and thus the caller doesn't have to delete
 * those items.  Otherwise, if @p doDelete is false (zero), all items are
 * only cleared from this CaListOf_t structure and the caller is responsible
 * for deleting all items.  (In the latter case, callers are advised to store
 * pointers to all items elsewhere before calling this function.)
 *
 * @param lo the CaListOf_t structure to clear
 * @param doDelete whether to delete the items.
 *
 * @memberof CaListOf_t
 */
LIBCOMBINE_EXTERN
void
CaListOf_clear (CaListOf_t *lo, int doDelete);


/**
 * Removes the <em>n</em>th item from this CaListOf_t list and returns it.
 *
 * The caller owns the returned item and is responsible for deleting it.
 *
 * @param lo the list from which the item should be removed.
 * @param n the index number of the item to remove.
 *
 * @return the item removed, or a null pointer if no item existed at the
 * index @p n.
 *
 * @memberof CaListOf_t
 */
LIBCOMBINE_EXTERN
CaBase_t *
CaListOf_remove (CaListOf_t *lo, unsigned int n);


/**
 * Returns the number of items in this CaListOf_t items.
 *
 * @param lo the CaListOf_t structure to count.
 *
 * @return the number of items in @p lo.
 *
 * @memberof CaListOf_t
 */
LIBCOMBINE_EXTERN
unsigned int
CaListOf_size (const CaListOf_t *lo);


/**
 * Get the type code of the objects contained in the given CaListOf_t
 * structure.
 *
 * @copydetails doc_what_are_typecodes
 *
 * @param lo the CaListOf_t whose item type codes are sought.
 *
 * @return the type code corresponding to the objects in @p lo,
 * or @omexconstant{OMEX_UNKNOWN, CaTypeCode_t}.
 *
 * @memberof CaListOf_t
 */
LIBCOMBINE_EXTERN
int
CaListOf_getItemTypeCode (const CaListOf_t *lo);


END_C_DECLS
LIBCOMBINE_CPP_NAMESPACE_END

#endif  /* !SWIG */
#endif  /* CaListOf_h */

