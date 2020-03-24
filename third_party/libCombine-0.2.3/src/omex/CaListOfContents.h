/**
 * @file CaListOfContents.h
 * @brief Definition of the CaListOfContents class.
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
 * @class CaListOfContents
 * @sbmlbrief{combine} TODO:Definition of the CaListOfContents class.
 */


#ifndef CaListOfContents_H__
#define CaListOfContents_H__


#include <omex/common/extern.h>
#include <omex/common/combinefwd.h>


#ifdef __cplusplus


#include <string>


#include <omex/CaListOf.h>
#include <omex/CaContent.h>
#include <sbml/common/libsbml-namespace.h>


LIBCOMBINE_CPP_NAMESPACE_BEGIN


class LIBCOMBINE_EXTERN CaListOfContents : public CaListOf
{

public:

  /**
   * Creates a new CaListOfContents instance.
   */
  CaListOfContents();


  /**
   * Creates a new CaListOfContents using the given CaNamespaces object @p
   * omexns.
   *
   * @param omexns the CaNamespaces object.
   *
   * @copydetails doc_note_setting_lv_pkg
   */
  CaListOfContents(CaNamespaces *omexns);


  /**
   * Copy constructor for CaListOfContents.
   *
   * @param orig the CaListOfContents instance to copy.
   */
  CaListOfContents(const CaListOfContents& orig);


  /**
   * Assignment operator for CaListOfContents.
   *
   * @param rhs the CaListOfContents object whose values are to be used as the
   * basis of the assignment.
   */
  CaListOfContents& operator=(const CaListOfContents& rhs);


  /**
   * Creates and returns a deep copy of this CaListOfContents object.
   *
   * @return a (deep) copy of this CaListOfContents object.
   */
  virtual CaListOfContents* clone() const;


  /**
   * Destructor for CaListOfContents.
   */
  virtual ~CaListOfContents();


  /**
   * Get a CaContent from the CaListOfContents.
   *
   * @param n an unsigned int representing the index of the CaContent to
   * retrieve.
   *
   * @return the nth CaContent in this CaListOfContents.
   *
   * @copydetails doc_returned_unowned_pointer
   *
   * @see addContent(const CaContent* object)
   * @see createContent()
   * @see get(const std::string& sid)
   * @see getNumContents()
   * @see remove(const std::string& sid)
   * @see remove(unsigned int n)
   */
  virtual CaContent* get(unsigned int n);


  /**
   * Get a CaContent from the CaListOfContents.
   *
   * @param n an unsigned int representing the index of the CaContent to
   * retrieve.
   *
   * @return the nth CaContent in this CaListOfContents.
   *
   * @copydetails doc_returned_unowned_pointer
   *
   * @see addContent(const CaContent* object)
   * @see createContent()
   * @see get(const std::string& sid)
   * @see getNumContents()
   * @see remove(const std::string& sid)
   * @see remove(unsigned int n)
   */
  virtual const CaContent* get(unsigned int n) const;


  /**
   * Get a CaContent from the CaListOfContents based on its identifier.
   *
   * @param sid a string representing the identifier of the CaContent to
   * retrieve.
   *
   * @return the CaContent in this CaListOfContents with the given @p sid or
   * @c NULL if no such CaContent exists.
   *
   * @copydetails doc_returned_unowned_pointer
   *
   * @see addContent(const CaContent* object)
   * @see createContent()
   * @see get(unsigned int n)
   * @see getNumContents()
   * @see remove(const std::string& sid)
   * @see remove(unsigned int n)
   */
  virtual CaContent* get(const std::string& sid);


  /**
   * Get a CaContent from the CaListOfContents based on its identifier.
   *
   * @param sid a string representing the identifier of the CaContent to
   * retrieve.
   *
   * @return the CaContent in this CaListOfContents with the given @p sid or
   * @c NULL if no such CaContent exists.
   *
   * @copydetails doc_returned_unowned_pointer
   *
   * @see addContent(const CaContent* object)
   * @see createContent()
   * @see get(unsigned int n)
   * @see getNumContents()
   * @see remove(const std::string& sid)
   * @see remove(unsigned int n)
   */
  virtual const CaContent* get(const std::string& sid) const;


  /**
   * Removes the nth CaContent from this CaListOfContents and returns a pointer
   * to it.
   *
   * @param n an unsigned int representing the index of the CaContent to
   * remove.
   *
   * @return a pointer to the nth CaContent in this CaListOfContents.
   *
   * @copydetails doc_returned_owned_pointer
   *
   * @see addContent(const CaContent* object)
   * @see createContent()
   * @see get(const std::string& sid)
   * @see get(unsigned int n)
   * @see getNumContents()
   * @see remove(const std::string& sid)
   */
  virtual CaContent* remove(unsigned int n);


  /**
   * Removes the CaContent from this CaListOfContents based on its identifier
   * and returns a pointer to it.
   *
   * @param sid a string representing the identifier of the CaContent to
   * remove.
   *
   * @return the CaContent in this CaListOfContents based on the identifier or
   * NULL if no such CaContent exists.
   *
   * @copydetails doc_returned_owned_pointer
   *
   * @see addContent(const CaContent* object)
   * @see createContent()
   * @see get(const std::string& sid)
   * @see get(unsigned int n)
   * @see getNumContents()
   * @see remove(unsigned int n)
   */
  virtual CaContent* remove(const std::string& sid);


  /**
   * Adds a copy of the given CaContent to this CaListOfContents.
   *
   * @param cc the CaContent object to add.
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
   * @see createContent()
   * @see get(const std::string& sid)
   * @see get(unsigned int n)
   * @see getNumContents()
   * @see remove(const std::string& sid)
   * @see remove(unsigned int n)
   */
  int addContent(const CaContent* cc);


  /**
   * Get the number of CaContent objects in this CaListOfContents.
   *
   * @return the number of CaContent objects in this CaListOfContents.
   *
   * @see addContent(const CaContent* object)
   * @see createContent()
   * @see get(const std::string& sid)
   * @see get(unsigned int n)
   * @see remove(const std::string& sid)
   * @see remove(unsigned int n)
   */
  unsigned int getNumContents() const;


  /**
   * Creates a new CaContent object, adds it to this CaListOfContents object
   * and returns the CaContent object created.
   *
   * @return a new CaContent object instance.
   *
   * @copydetails doc_returned_unowned_pointer
   *
   * @see addContent(const CaContent* object)
   * @see get(const std::string& sid)
   * @see get(unsigned int n)
   * @see getNumContents()
   * @see remove(const std::string& sid)
   * @see remove(unsigned int n)
   */
  CaContent* createContent();


  /**
   * Returns the XML element name of this CaListOfContents object.
   *
   * For CaListOfContents, the XML element name is always @c "listOfContents".
   *
   * @return the name of this element, i.e. @c "listOfContents".
   */
  virtual const std::string& getElementName() const;


  /**
   * Returns the libCombine type code for this CaListOfContents object.
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
   * CaListOfContents object.
   *
   * @copydetails doc_what_are_typecodes
   *
   * @return the OMEX typecode for the objects contained in this
   * CaListOfContents:
   * @omexconstant{LIB_COMBINE_CONTENT, CaTypeCode_t}.
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
   * Creates a new CaContent in this CaListOfContents
   */
  virtual CaBase* createObject(LIBSBML_CPP_NAMESPACE_QUALIFIER XMLInputStream&
    stream);

  /** @endcond */


  friend class CaOmexManifest;

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
 * Get a CaContent_t from the CaListOf_t.
 *
 * @param clo the CaListOf_t structure to search.
 *
 * @param n an unsigned int representing the index of the CaContent_t to
 * retrieve.
 *
 * @return the nth CaContent_t in this CaListOf_t.
 *
 * @copydetails doc_returned_unowned_pointer
 *
 * @memberof CaListOfContents_t
 */
LIBCOMBINE_EXTERN
CaContent_t*
CaListOfContents_getContent(CaListOf_t* clo, unsigned int n);


/**
 * Get a CaContent_t from the CaListOf_t based on its identifier.
 *
 * @param clo the CaListOf_t structure to search.
 *
 * @param sid a string representing the identifier of the CaContent_t to
 * retrieve.
 *
 * @return the CaContent_t in this CaListOf_t with the given @p sid or @c NULL
 * if no such CaContent_t exists.
 *
 * @copydetails doc_returned_unowned_pointer
 *
 * @memberof CaListOfContents_t
 */
LIBCOMBINE_EXTERN
CaContent_t*
CaListOfContents_getById(CaListOf_t* clo, const char *sid);


/**
 * Removes the nth CaContent_t from this CaListOf_t and returns a pointer to
 * it.
 *
 * @param clo the CaListOf_t structure to search.
 *
 * @param n an unsigned int representing the index of the CaContent_t to
 * remove.
 *
 * @return a pointer to the nth CaContent_t in this CaListOf_t.
 *
 * @copydetails doc_returned_owned_pointer
 *
 * @memberof CaListOfContents_t
 */
LIBCOMBINE_EXTERN
CaContent_t*
CaListOfContents_remove(CaListOf_t* clo, unsigned int n);


/**
 * Removes the CaContent_t from this CaListOf_t based on its identifier and
 * returns a pointer to it.
 *
 * @param clo the CaListOf_t structure to search.
 *
 * @param sid a string representing the identifier of the CaContent_t to
 * remove.
 *
 * @return the CaContent_t in this CaListOf_t based on the identifier or NULL
 * if no such CaContent_t exists.
 *
 * @copydetails doc_returned_owned_pointer
 *
 * @memberof CaListOfContents_t
 */
LIBCOMBINE_EXTERN
CaContent_t*
CaListOfContents_removeById(CaListOf_t* clo, const char* sid);




END_C_DECLS




LIBCOMBINE_CPP_NAMESPACE_END




#endif /* !SWIG */




#endif /* !CaListOfContents_H__ */


