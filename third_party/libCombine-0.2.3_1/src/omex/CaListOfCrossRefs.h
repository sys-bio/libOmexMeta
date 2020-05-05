/**
 * @file CaListOfCrossRefs.h
 * @brief Definition of the CaListOfCrossRefs class.
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
 * @class CaListOfCrossRefs
 * @sbmlbrief{combine} TODO:Definition of the CaListOfCrossRefs class.
 */


#ifndef CaListOfCrossRefs_H__
#define CaListOfCrossRefs_H__


#include <omex/common/extern.h>
#include <omex/common/combinefwd.h>


#ifdef __cplusplus


#include <string>


#include <omex/CaListOf.h>
#include <omex/CaCrossRef.h>
#include <sbml/common/libsbml-namespace.h>


LIBCOMBINE_CPP_NAMESPACE_BEGIN


class LIBCOMBINE_EXTERN CaListOfCrossRefs : public CaListOf
{

public:

  /**
   * Creates a new CaListOfCrossRefs instance.
   */
  CaListOfCrossRefs();


  /**
   * Creates a new CaListOfCrossRefs using the given CaNamespaces object @p
   * omexns.
   *
   * @param omexns the CaNamespaces object.
   *
   * @copydetails doc_note_setting_lv_pkg
   */
  CaListOfCrossRefs(CaNamespaces *omexns);


  /**
   * Copy constructor for CaListOfCrossRefs.
   *
   * @param orig the CaListOfCrossRefs instance to copy.
   */
  CaListOfCrossRefs(const CaListOfCrossRefs& orig);


  /**
   * Assignment operator for CaListOfCrossRefs.
   *
   * @param rhs the CaListOfCrossRefs object whose values are to be used as the
   * basis of the assignment.
   */
  CaListOfCrossRefs& operator=(const CaListOfCrossRefs& rhs);


  /**
   * Creates and returns a deep copy of this CaListOfCrossRefs object.
   *
   * @return a (deep) copy of this CaListOfCrossRefs object.
   */
  virtual CaListOfCrossRefs* clone() const;


  /**
   * Destructor for CaListOfCrossRefs.
   */
  virtual ~CaListOfCrossRefs();


  /**
   * Get a CaCrossRef from the CaListOfCrossRefs.
   *
   * @param n an unsigned int representing the index of the CaCrossRef to
   * retrieve.
   *
   * @return the nth CaCrossRef in this CaListOfCrossRefs.
   *
   * @copydetails doc_returned_unowned_pointer
   *
   * @see addCrossRef(const CaCrossRef* object)
   * @see createCrossRef()
   * @see get(const std::string& sid)
   * @see getNumCrossRefs()
   * @see remove(const std::string& sid)
   * @see remove(unsigned int n)
   */
  virtual CaCrossRef* get(unsigned int n);


  /**
   * Get a CaCrossRef from the CaListOfCrossRefs.
   *
   * @param n an unsigned int representing the index of the CaCrossRef to
   * retrieve.
   *
   * @return the nth CaCrossRef in this CaListOfCrossRefs.
   *
   * @copydetails doc_returned_unowned_pointer
   *
   * @see addCrossRef(const CaCrossRef* object)
   * @see createCrossRef()
   * @see get(const std::string& sid)
   * @see getNumCrossRefs()
   * @see remove(const std::string& sid)
   * @see remove(unsigned int n)
   */
  virtual const CaCrossRef* get(unsigned int n) const;


  /**
   * Get a CaCrossRef from the CaListOfCrossRefs based on its identifier.
   *
   * @param sid a string representing the identifier of the CaCrossRef to
   * retrieve.
   *
   * @return the CaCrossRef in this CaListOfCrossRefs with the given @p sid or
   * @c NULL if no such CaCrossRef exists.
   *
   * @copydetails doc_returned_unowned_pointer
   *
   * @see addCrossRef(const CaCrossRef* object)
   * @see createCrossRef()
   * @see get(unsigned int n)
   * @see getNumCrossRefs()
   * @see remove(const std::string& sid)
   * @see remove(unsigned int n)
   */
  virtual CaCrossRef* get(const std::string& sid);


  /**
   * Get a CaCrossRef from the CaListOfCrossRefs based on its identifier.
   *
   * @param sid a string representing the identifier of the CaCrossRef to
   * retrieve.
   *
   * @return the CaCrossRef in this CaListOfCrossRefs with the given @p sid or
   * @c NULL if no such CaCrossRef exists.
   *
   * @copydetails doc_returned_unowned_pointer
   *
   * @see addCrossRef(const CaCrossRef* object)
   * @see createCrossRef()
   * @see get(unsigned int n)
   * @see getNumCrossRefs()
   * @see remove(const std::string& sid)
   * @see remove(unsigned int n)
   */
  virtual const CaCrossRef* get(const std::string& sid) const;


  /**
   * Removes the nth CaCrossRef from this CaListOfCrossRefs and returns a
   * pointer to it.
   *
   * @param n an unsigned int representing the index of the CaCrossRef to
   * remove.
   *
   * @return a pointer to the nth CaCrossRef in this CaListOfCrossRefs.
   *
   * @copydetails doc_returned_owned_pointer
   *
   * @see addCrossRef(const CaCrossRef* object)
   * @see createCrossRef()
   * @see get(const std::string& sid)
   * @see get(unsigned int n)
   * @see getNumCrossRefs()
   * @see remove(const std::string& sid)
   */
  virtual CaCrossRef* remove(unsigned int n);


  /**
   * Removes the CaCrossRef from this CaListOfCrossRefs based on its identifier
   * and returns a pointer to it.
   *
   * @param sid a string representing the identifier of the CaCrossRef to
   * remove.
   *
   * @return the CaCrossRef in this CaListOfCrossRefs based on the identifier
   * or NULL if no such CaCrossRef exists.
   *
   * @copydetails doc_returned_owned_pointer
   *
   * @see addCrossRef(const CaCrossRef* object)
   * @see createCrossRef()
   * @see get(const std::string& sid)
   * @see get(unsigned int n)
   * @see getNumCrossRefs()
   * @see remove(unsigned int n)
   */
  virtual CaCrossRef* remove(const std::string& sid);


  /**
   * Adds a copy of the given CaCrossRef to this CaListOfCrossRefs.
   *
   * @param ccr the CaCrossRef object to add.
   *
   * @copydetails doc_returns_success_code
   * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
   * @li @omexconstant{LIBCOMBINE_OPERATION_FAILED, OperationReturnValues_t}
   * @li @omexconstant{LIBCOMBINE_INVALID_OBJECT, OperationReturnValues_t}
   * @li @omexconstant{LIBCOMBINE_LEVEL_MISMATCH, OperationReturnValues_t}
   * @li @omexconstant{LIBCOMBINE_VERSION_MISMATCH, OperationReturnValues_t}
   * @li @omexconstant{LIBCOMBINE_PKG_VERSION_MISMATCH,
   * OperationReturnValues_t}
   * @li @omexconstant{LIBCOMBINE_DUPLICATE_OBJECT_ID, OperationReturnValues_t}
   *
   * @copydetails doc_note_object_is_copied
   *
   * @see createCrossRef()
   * @see get(const std::string& sid)
   * @see get(unsigned int n)
   * @see getNumCrossRefs()
   * @see remove(const std::string& sid)
   * @see remove(unsigned int n)
   */
  int addCrossRef(const CaCrossRef* ccr);


  /**
   * Get the number of CaCrossRef objects in this CaListOfCrossRefs.
   *
   * @return the number of CaCrossRef objects in this CaListOfCrossRefs.
   *
   * @see addCrossRef(const CaCrossRef* object)
   * @see createCrossRef()
   * @see get(const std::string& sid)
   * @see get(unsigned int n)
   * @see remove(const std::string& sid)
   * @see remove(unsigned int n)
   */
  unsigned int getNumCrossRefs() const;


  /**
   * Creates a new CaCrossRef object, adds it to this CaListOfCrossRefs object
   * and returns the CaCrossRef object created.
   *
   * @return a new CaCrossRef object instance.
   *
   * @copydetails doc_returned_unowned_pointer
   *
   * @see addCrossRef(const CaCrossRef* object)
   * @see get(const std::string& sid)
   * @see get(unsigned int n)
   * @see getNumCrossRefs()
   * @see remove(const std::string& sid)
   * @see remove(unsigned int n)
   */
  CaCrossRef* createCrossRef();


  /**
   * Returns the XML element name of this CaListOfCrossRefs object.
   *
   * For CaListOfCrossRefs, the XML element name is always
   * @c "listOfCrossRefs".
   *
   * @return the name of this element, i.e. @c "listOfCrossRefs".
   */
  virtual const std::string& getElementName() const;


  /**
   * Returns the libCombine type code for this CaListOfCrossRefs object.
   *
   * @copydetails doc_what_are_typecodes
   *
   * @return the OMEX type code for this object:
   * @omexconstant{OMEX_LIST_OF, CaTypeCode_t}.
   *
   * @copydetails doc_warning_typecodes_not_unique
   */
  virtual int getTypeCode() const;


  /**
   * Returns the libOMEX type code for the OMEX objects contained in this
   * CaListOfCrossRefs object.
   *
   * @copydetails doc_what_are_typecodes
   *
   * @return the OMEX typecode for the objects contained in this
   * CaListOfCrossRefs:
   * @omexconstant{LIB_COMBINE_CROSSREF, CaTypeCode_t}.
   *
   * @copydetails doc_warning_typecodes_not_unique
   *
   * @see getElementName()
   */
  virtual int getItemTypeCode() const;




  #ifndef SWIG




  #endif /* !SWIG */


protected:


  /** @cond doxygenlibCombineInternal */

  /**
   * Creates a new CaCrossRef in this CaListOfCrossRefs
   */
  virtual CaBase* createObject(LIBSBML_CPP_NAMESPACE_QUALIFIER XMLInputStream&
    stream);

  /** @endcond */


  friend class CaContent;

  /** @cond doxygenlibCombineInternal */

  /**
   * Writes the namespace for the Combine package
   */
  virtual void writeXMLNS(LIBSBML_CPP_NAMESPACE_QUALIFIER XMLOutputStream&
    stream) const;

  /** @endcond */


};



LIBCOMBINE_CPP_NAMESPACE_END




#endif /* __cplusplus */




#ifndef SWIG




LIBCOMBINE_CPP_NAMESPACE_BEGIN




BEGIN_C_DECLS


/**
 * Get a CaCrossRef_t from the CaListOf_t.
 *
 * @param clo the CaListOf_t structure to search.
 *
 * @param n an unsigned int representing the index of the CaCrossRef_t to
 * retrieve.
 *
 * @return the nth CaCrossRef_t in this CaListOf_t.
 *
 * @copydetails doc_returned_unowned_pointer
 *
 * @memberof CaListOfCrossRefs_t
 */
LIBCOMBINE_EXTERN
CaCrossRef_t*
CaListOfCrossRefs_getCrossRef(CaListOf_t* clo, unsigned int n);


/**
 * Get a CaCrossRef_t from the CaListOf_t based on its identifier.
 *
 * @param clo the CaListOf_t structure to search.
 *
 * @param sid a string representing the identifier of the CaCrossRef_t to
 * retrieve.
 *
 * @return the CaCrossRef_t in this CaListOf_t with the given @p sid or @c NULL
 * if no such CaCrossRef_t exists.
 *
 * @copydetails doc_returned_unowned_pointer
 *
 * @memberof CaListOfCrossRefs_t
 */
LIBCOMBINE_EXTERN
CaCrossRef_t*
CaListOfCrossRefs_getById(CaListOf_t* clo, const char *sid);


/**
 * Removes the nth CaCrossRef_t from this CaListOf_t and returns a pointer to
 * it.
 *
 * @param clo the CaListOf_t structure to search.
 *
 * @param n an unsigned int representing the index of the CaCrossRef_t to
 * remove.
 *
 * @return a pointer to the nth CaCrossRef_t in this CaListOf_t.
 *
 * @copydetails doc_returned_owned_pointer
 *
 * @memberof CaListOfCrossRefs_t
 */
LIBCOMBINE_EXTERN
CaCrossRef_t*
CaListOfCrossRefs_remove(CaListOf_t* clo, unsigned int n);


/**
 * Removes the CaCrossRef_t from this CaListOf_t based on its identifier and
 * returns a pointer to it.
 *
 * @param clo the CaListOf_t structure to search.
 *
 * @param sid a string representing the identifier of the CaCrossRef_t to
 * remove.
 *
 * @return the CaCrossRef_t in this CaListOf_t based on the identifier or NULL
 * if no such CaCrossRef_t exists.
 *
 * @copydetails doc_returned_owned_pointer
 *
 * @memberof CaListOfCrossRefs_t
 */
LIBCOMBINE_EXTERN
CaCrossRef_t*
CaListOfCrossRefs_removeById(CaListOf_t* clo, const char* sid);




END_C_DECLS




LIBCOMBINE_CPP_NAMESPACE_END




#endif /* !SWIG */




#endif /* !CaListOfCrossRefs_H__ */


