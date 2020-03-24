/**
 * @file CaCrossRef.h
 * @brief Definition of the CaCrossRef class.
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
 * @class CaCrossRef
 * @sbmlbrief{combine} TODO:Definition of the CaCrossRef class.
 */


#ifndef CaCrossRef_H__
#define CaCrossRef_H__


#include <omex/common/extern.h>
#include <omex/common/combinefwd.h>


#ifdef __cplusplus


#include <string>


#include <omex/CaBase.h>
#include <sbml/common/libsbml-namespace.h>


LIBCOMBINE_CPP_NAMESPACE_BEGIN


class LIBCOMBINE_EXTERN CaCrossRef : public CaBase
{
protected:

  /** @cond doxygenlibCombineInternal */

  std::string mLocation;

  /** @endcond */

public:

  /**
   * Creates a new CaCrossRef instance.
   */
  CaCrossRef();


  /**
   * Creates a new CaCrossRef using the given CaNamespaces object @p omexns.
   *
   * @param omexns the CaNamespaces object.
   *
   * @copydetails doc_note_setting_lv_pkg
   */
  CaCrossRef(CaNamespaces *omexns);


  /**
   * Copy constructor for CaCrossRef.
   *
   * @param orig the CaCrossRef instance to copy.
   */
  CaCrossRef(const CaCrossRef& orig);


  /**
   * Assignment operator for CaCrossRef.
   *
   * @param rhs the CaCrossRef object whose values are to be used as the basis
   * of the assignment.
   */
  CaCrossRef& operator=(const CaCrossRef& rhs);


  /**
   * Creates and returns a deep copy of this CaCrossRef object.
   *
   * @return a (deep) copy of this CaCrossRef object.
   */
  virtual CaCrossRef* clone() const;


  /**
   * Destructor for CaCrossRef.
   */
  virtual ~CaCrossRef();


  /**
   * Returns the value of the "location" attribute of this CaCrossRef.
   *
   * @return the value of the "location" attribute of this CaCrossRef as a
   * string.
   */
  const std::string& getLocation() const;


  /**
   * Predicate returning @c true if this CaCrossRef's "location" attribute is
   * set.
   *
   * @return @c true if this CaCrossRef's "location" attribute has been set,
   * otherwise @c false is returned.
   */
  bool isSetLocation() const;


  /**
   * Sets the value of the "location" attribute of this CaCrossRef.
   *
   * @param location std::string& value of the "location" attribute to be set.
   *
   * @copydetails doc_returns_one_success_code
   * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
   *
   * Calling this function with @p location = @c NULL or an empty string is
   * equivalent to calling unsetLocation().
   */
  int setLocation(const std::string& location);


  /**
   * Unsets the value of the "location" attribute of this CaCrossRef.
   *
   * @copydetails doc_returns_success_code
   * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
   * @li @omexconstant{LIBCOMBINE_OPERATION_FAILED, OperationReturnValues_t}
   */
  int unsetLocation();


  /**
   * Returns the XML element name of this CaCrossRef object.
   *
   * For CaCrossRef, the XML element name is always @c "crossRef".
   *
   * @return the name of this element, i.e. @c "crossRef".
   */
  virtual const std::string& getElementName() const;


  /**
   * Returns the libCombine type code for this CaCrossRef object.
   *
   * @copydetails doc_what_are_typecodes
   *
   * @return the OMEX type code for this object:
   * @omexconstant{LIB_COMBINE_CROSSREF, CaTypeCode_t}.
   *
   * @copydetails doc_warning_typecodes_not_unique
   *
   * @see getElementName()
   */
  virtual int getTypeCode() const;


  /**
   * Predicate returning @c true if all the required attributes for this
   * CaCrossRef object have been set.
   *
   * @return @c true to indicate that all the required attributes of this
   * CaCrossRef have been set, otherwise @c false is returned.
   *
   *
   * @note The required attributes for the CaCrossRef object are:
   * @li "location"
   */
  virtual bool hasRequiredAttributes() const;



  /** @cond doxygenlibCombineInternal */

  /**
   * Write any contained elements
   */
  virtual void writeElements(LIBSBML_CPP_NAMESPACE_QUALIFIER XMLOutputStream&
    stream) const;

  /** @endcond */



  /** @cond doxygenlibCombineInternal */

  /**
   * Accepts the given CaVisitor
   */
  virtual bool accept(CaVisitor& v) const;

  /** @endcond */



  /** @cond doxygenlibCombineInternal */

  /**
   * Sets the parent CaOmexManifest
   */
  virtual void setCaOmexManifest(CaOmexManifest* d);

  /** @endcond */




  #ifndef SWIG



  /** @cond doxygenlibCombineInternal */

  /**
   * Gets the value of the "attributeName" attribute of this CaCrossRef.
   *
   * @param attributeName, the name of the attribute to retrieve.
   *
   * @param value, the address of the value to record.
   *
   * @copydetails doc_returns_success_code
   * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
   * @li @omexconstant{LIBCOMBINE_OPERATION_FAILED, OperationReturnValues_t}
   */
  virtual int getAttribute(const std::string& attributeName, bool& value)
    const;

  /** @endcond */



  /** @cond doxygenlibCombineInternal */

  /**
   * Gets the value of the "attributeName" attribute of this CaCrossRef.
   *
   * @param attributeName, the name of the attribute to retrieve.
   *
   * @param value, the address of the value to record.
   *
   * @copydetails doc_returns_success_code
   * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
   * @li @omexconstant{LIBCOMBINE_OPERATION_FAILED, OperationReturnValues_t}
   */
  virtual int getAttribute(const std::string& attributeName, int& value) const;

  /** @endcond */



  /** @cond doxygenlibCombineInternal */

  /**
   * Gets the value of the "attributeName" attribute of this CaCrossRef.
   *
   * @param attributeName, the name of the attribute to retrieve.
   *
   * @param value, the address of the value to record.
   *
   * @copydetails doc_returns_success_code
   * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
   * @li @omexconstant{LIBCOMBINE_OPERATION_FAILED, OperationReturnValues_t}
   */
  virtual int getAttribute(const std::string& attributeName,
                           double& value) const;

  /** @endcond */



  /** @cond doxygenlibCombineInternal */

  /**
   * Gets the value of the "attributeName" attribute of this CaCrossRef.
   *
   * @param attributeName, the name of the attribute to retrieve.
   *
   * @param value, the address of the value to record.
   *
   * @copydetails doc_returns_success_code
   * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
   * @li @omexconstant{LIBCOMBINE_OPERATION_FAILED, OperationReturnValues_t}
   */
  virtual int getAttribute(const std::string& attributeName,
                           unsigned int& value) const;

  /** @endcond */



  /** @cond doxygenlibCombineInternal */

  /**
   * Gets the value of the "attributeName" attribute of this CaCrossRef.
   *
   * @param attributeName, the name of the attribute to retrieve.
   *
   * @param value, the address of the value to record.
   *
   * @copydetails doc_returns_success_code
   * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
   * @li @omexconstant{LIBCOMBINE_OPERATION_FAILED, OperationReturnValues_t}
   */
  virtual int getAttribute(const std::string& attributeName,
                           std::string& value) const;

  /** @endcond */



  /** @cond doxygenlibCombineInternal */

  /**
   * Predicate returning @c true if this CaCrossRef's attribute "attributeName"
   * is set.
   *
   * @param attributeName, the name of the attribute to query.
   *
   * @return @c true if this CaCrossRef's attribute "attributeName" has been
   * set, otherwise @c false is returned.
   */
  virtual bool isSetAttribute(const std::string& attributeName) const;

  /** @endcond */



  /** @cond doxygenlibCombineInternal */

  /**
   * Sets the value of the "attributeName" attribute of this CaCrossRef.
   *
   * @param attributeName, the name of the attribute to set.
   *
   * @param value, the value of the attribute to set.
   *
   * @copydetails doc_returns_success_code
   * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
   * @li @omexconstant{LIBCOMBINE_OPERATION_FAILED, OperationReturnValues_t}
   */
  virtual int setAttribute(const std::string& attributeName, bool value);

  /** @endcond */



  /** @cond doxygenlibCombineInternal */

  /**
   * Sets the value of the "attributeName" attribute of this CaCrossRef.
   *
   * @param attributeName, the name of the attribute to set.
   *
   * @param value, the value of the attribute to set.
   *
   * @copydetails doc_returns_success_code
   * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
   * @li @omexconstant{LIBCOMBINE_OPERATION_FAILED, OperationReturnValues_t}
   */
  virtual int setAttribute(const std::string& attributeName, int value);

  /** @endcond */



  /** @cond doxygenlibCombineInternal */

  /**
   * Sets the value of the "attributeName" attribute of this CaCrossRef.
   *
   * @param attributeName, the name of the attribute to set.
   *
   * @param value, the value of the attribute to set.
   *
   * @copydetails doc_returns_success_code
   * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
   * @li @omexconstant{LIBCOMBINE_OPERATION_FAILED, OperationReturnValues_t}
   */
  virtual int setAttribute(const std::string& attributeName, double value);

  /** @endcond */



  /** @cond doxygenlibCombineInternal */

  /**
   * Sets the value of the "attributeName" attribute of this CaCrossRef.
   *
   * @param attributeName, the name of the attribute to set.
   *
   * @param value, the value of the attribute to set.
   *
   * @copydetails doc_returns_success_code
   * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
   * @li @omexconstant{LIBCOMBINE_OPERATION_FAILED, OperationReturnValues_t}
   */
  virtual int setAttribute(const std::string& attributeName,
                           unsigned int value);

  /** @endcond */



  /** @cond doxygenlibCombineInternal */

  /**
   * Sets the value of the "attributeName" attribute of this CaCrossRef.
   *
   * @param attributeName, the name of the attribute to set.
   *
   * @param value, the value of the attribute to set.
   *
   * @copydetails doc_returns_success_code
   * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
   * @li @omexconstant{LIBCOMBINE_OPERATION_FAILED, OperationReturnValues_t}
   */
  virtual int setAttribute(const std::string& attributeName,
                           const std::string& value);

  /** @endcond */



  /** @cond doxygenlibCombineInternal */

  /**
   * Unsets the value of the "attributeName" attribute of this CaCrossRef.
   *
   * @param attributeName, the name of the attribute to query.
   *
   * @copydetails doc_returns_success_code
   * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
   * @li @omexconstant{LIBCOMBINE_OPERATION_FAILED, OperationReturnValues_t}
   */
  virtual int unsetAttribute(const std::string& attributeName);

  /** @endcond */




  #endif /* !SWIG */


protected:


  /** @cond doxygenlibCombineInternal */

  /**
   * Adds the expected attributes for this element
   */
  virtual void addExpectedAttributes(LIBSBML_CPP_NAMESPACE_QUALIFIER
    ExpectedAttributes& attributes);

  /** @endcond */



  /** @cond doxygenlibCombineInternal */

  /**
   * Reads the expected attributes into the member data variables
   */
  virtual void readAttributes(
                              const LIBSBML_CPP_NAMESPACE_QUALIFIER
                                XMLAttributes& attributes,
                              const LIBSBML_CPP_NAMESPACE_QUALIFIER
                                ExpectedAttributes& expectedAttributes);

  /** @endcond */



  /** @cond doxygenlibCombineInternal */

  /**
   * Writes the attributes to the stream
   */
  virtual void writeAttributes(LIBSBML_CPP_NAMESPACE_QUALIFIER XMLOutputStream&
    stream) const;

  /** @endcond */


};



LIBCOMBINE_CPP_NAMESPACE_END




#endif /* __cplusplus */




#ifndef SWIG




LIBCOMBINE_CPP_NAMESPACE_BEGIN




BEGIN_C_DECLS


/**
 * Creates a new CaCrossRef_t instance.
 *
 * @memberof CaCrossRef_t
 */
LIBCOMBINE_EXTERN
CaCrossRef_t *
CaCrossRef_create();


/**
 * Creates and returns a deep copy of this CaCrossRef_t object.
 *
 * @param ccr the CaCrossRef_t structure.
 *
 * @return a (deep) copy of this CaCrossRef_t object.
 *
 * @copydetails doc_returned_owned_pointer
 *
 * @memberof CaCrossRef_t
 */
LIBCOMBINE_EXTERN
CaCrossRef_t*
CaCrossRef_clone(const CaCrossRef_t* ccr);


/**
 * Frees this CaCrossRef_t object.
 *
 * @param ccr the CaCrossRef_t structure.
 *
 * @memberof CaCrossRef_t
 */
LIBCOMBINE_EXTERN
void
CaCrossRef_free(CaCrossRef_t* ccr);


/**
 * Returns the value of the "location" attribute of this CaCrossRef_t.
 *
 * @param ccr the CaCrossRef_t structure whose location is sought.
 *
 * @return the value of the "location" attribute of this CaCrossRef_t as a
 * pointer to a string.
 *
 * @copydetails doc_returned_owned_char
 *
 * @memberof CaCrossRef_t
 */
LIBCOMBINE_EXTERN
char *
CaCrossRef_getLocation(const CaCrossRef_t * ccr);


/**
 * Predicate returning @c 1 (true) if this CaCrossRef_t's "location" attribute
 * is set.
 *
 * @param ccr the CaCrossRef_t structure.
 *
 * @return @c 1 (true) if this CaCrossRef_t's "location" attribute has been
 * set, otherwise @c 0 (false) is returned.
 *
 * @memberof CaCrossRef_t
 */
LIBCOMBINE_EXTERN
int
CaCrossRef_isSetLocation(const CaCrossRef_t * ccr);


/**
 * Sets the value of the "location" attribute of this CaCrossRef_t.
 *
 * @param ccr the CaCrossRef_t structure.
 *
 * @param location const char * value of the "location" attribute to be set.
 *
 * @copydetails doc_returns_success_code
 * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
 * @li @omexconstant{LIBCOMBINE_INVALID_OBJECT, OperationReturnValues_t}
 *
 * Calling this function with @p location = @c NULL or an empty string is
 * equivalent to calling CaCrossRef_unsetLocation().
 *
 * @memberof CaCrossRef_t
 */
LIBCOMBINE_EXTERN
int
CaCrossRef_setLocation(CaCrossRef_t * ccr, const char * location);


/**
 * Unsets the value of the "location" attribute of this CaCrossRef_t.
 *
 * @param ccr the CaCrossRef_t structure.
 *
 * @copydetails doc_returns_success_code
 * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
 * @li @omexconstant{LIBCOMBINE_OPERATION_FAILED, OperationReturnValues_t}
 * @li @omexconstant{LIBCOMBINE_INVALID_OBJECT, OperationReturnValues_t}
 *
 * @memberof CaCrossRef_t
 */
LIBCOMBINE_EXTERN
int
CaCrossRef_unsetLocation(CaCrossRef_t * ccr);


/**
 * Predicate returning @c 1 (true) if all the required attributes for this
 * CaCrossRef_t object have been set.
 *
 * @param ccr the CaCrossRef_t structure.
 *
 * @return @c 1 (true) to indicate that all the required attributes of this
 * CaCrossRef_t have been set, otherwise @c 0 (false) is returned.
 *
 *
 * @note The required attributes for the CaCrossRef_t object are:
 * @li "location"
 *
 * @memberof CaCrossRef_t
 */
LIBCOMBINE_EXTERN
int
CaCrossRef_hasRequiredAttributes(const CaCrossRef_t * ccr);




END_C_DECLS




LIBCOMBINE_CPP_NAMESPACE_END




#endif /* !SWIG */




#endif /* !CaCrossRef_H__ */


