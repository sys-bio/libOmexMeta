/**
 * @file CaErrorLog.h
 * @brief Definition of the CaErrorLog class.
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
 * @class CaErrorLog
 * @sbmlbrief{} TODO:Definition of the CaErrorLog class.
 */


#ifndef CaErrorLog_h
#define CaErrorLog_h


#include <omex/common/extern.h>
#include <sbml/xml/XMLError.h>
#include <sbml/xml/XMLErrorLog.h>
#include <omex/CaError.h>


#ifdef __cplusplus

#include <vector>

LIBCOMBINE_CPP_NAMESPACE_BEGIN

class LIBCOMBINE_EXTERN CaErrorLog : public XMLErrorLog
{
public:

  /**
   * Returns the <i>n</i>th CaError object in this log.
   *
   * Index @p n is counted from 0.  Callers should first inquire about the
   * number of items in the log by using the
   * @if java XMLErrorLog::getNumErrors()@else getNumErrors()@endif@~ method.
   * Attempts to use an error index number that exceeds the actual number
   * of errors in the log will result in a @c NULL being returned.
   *
   * @param n the index number of the error to retrieve (with 0 being the
   * first error).
   *
   * @return the <i>n</i>th CaError in this log, or @c NULL if @p n is
   * greater than or equal to
   * @if java XMLErrorLog::getNumErrors()@else getNumErrors()@endif.
   *
   * @see getNumErrors()
   */
  const CaError* getError (unsigned int n) const;


  /**
   * Returns the <i>n</i>th CaError object with given severity in this log.
   *
   * Index @p n is counted from 0.  Callers should first inquire about the
   * number of items in the log by using the
   * @if java CaErrorLog::getNumFailsWithSeverity(long severity)@else getNumFailsWithSeverity()@endif@~ method.
   * Attempts to use an error index number that exceeds the actual number
   * of errors in the log will result in a @c NULL being returned.
   *
   * @param n the index number of the error to retrieve (with 0 being the
   * first error).
   * @param severity the severity of the error to retrieve 
   *
   * @return the <i>n</i>th CaError in this log, or @c NULL if @p n is
   * greater than or equal to
   * @if java CaErrorLog::getNumFailsWithSeverity(long severity)@else getNumFailsWithSeverity()@endif.
   *
   * @see getNumFailsWithSeverity(unsigned int severity)
   */
  const CaError* getErrorWithSeverity(unsigned int n, unsigned int severity) const;


  /**
   * Returns the number of errors that have been logged with the given
   * severity code.
   *
   * @if clike @param severity a value from
   * #CaErrorSeverity_t @endif@if java @param severity a
   * value from the set of <code>LIBCOMBINE_SEV_</code> constants defined by
   * the interface class <code><a
   * href="libcombineConstants.html">libcombineConstants</a></code> @endif@if python @param severity a
   * value from the set of <code>LIBCOMBINE_SEV_</code> constants defined by
   * the interface class @link libcombine libcombine@endlink. @endif@~
   *
   * @return a count of the number of errors with the given severity code.
   *
   * @see getNumErrors()
   */
  unsigned int getNumFailsWithSeverity(unsigned int severity);


   /**
   * Returns the number of errors that have been logged with the given
   * severity code.
   *
   * @if clike @param severity a value from
   * #CaErrorSeverity_t @endif@if java @param severity a
   * value from the set of <code>LIBCOMBINE_SEV_</code> constants defined by
   * the interface class <code><a
   * href="libcombineConstants.html">libcombineConstants</a></code> @endif@if python @param severity a
   * value from the set of <code>LIBCOMBINE_SEV_</code> constants defined by
   * the interface class @link libcombine libcombine@endlink. @endif@~
   *
   * @return a count of the number of errors with the given severity code.
   *
   * @see getNumErrors()
   */
  unsigned int getNumFailsWithSeverity(unsigned int severity) const;


  /** @cond doxygenLibomexInternal */
  
  /**
   * Creates a new, empty CaErrorLog.
   */
  CaErrorLog ();


  /**
   * Copy Constructor
   */
  CaErrorLog (const CaErrorLog& other);


  /**
   * Assignment operator for CaErrorLog
   */
  CaErrorLog& operator=(const CaErrorLog& other);


  /**
   * Destroys this CaErrorLog.
   */
  virtual ~CaErrorLog ();


  /**
   * Convenience function that combines creating an CaError object and
   * adding it to the log.
   *
   * @param errorId an unsigned int, the identification number of the error.
   *
   * @param level an unsigned int, the OMEX Level
   *
   * @param version an unsigned int, the OMEX Level's Version
   * 
   * @param details a string containing additional details about the error.
   * If the error code in @p errorId is one that is recognized by CaError,
   * the given message is @em appended to a predefined message associated
   * with the given code.  If the error code is not recognized, the message
   * is stored as-is as the text of the error.
   * 
   * @param line an unsigned int, the line number at which the error occured.
   * 
   * @param column an unsigned int, the column number at which the error occured.
   * 
   * @param severity an integer indicating severity of the error.
   * 
   * @param category an integer indicating the category to which the error
   * belongs.
   */
  void logError
  (
      const unsigned int errorId  = 0
    , const unsigned int level    = OMEX_DEFAULT_LEVEL
    , const unsigned int version  = OMEX_DEFAULT_VERSION
    , const std::string& details  = ""
    , const unsigned int line     = 0
    , const unsigned int column   = 0
    , const unsigned int severity = LIBCOMBINE_SEV_ERROR
    , const unsigned int category = LIBCOMBINE_CAT_OMEX
  );


  /**
   * Adds the given CaError to the log.
   *
   * @param error CaError, the error to be logged.
   */
  void add (const CaError& error);


  /** @cond doxygenCppOnly */

  /**
   * Adds (copies) the CaErrors in the given CaError list to this
   * CaErrorLog.
   *
   * @param errors list, a list of CaError to be added to the log.
   */
  void add (const std::list<CaError>& errors);


  /**
   * Adds (copies) the CaErrors in the given CaError vector to this
   * CaErrorLog.
   *
   * @param errors vector, a vector of CaError to be added to the log.
   */
  void add (const std::vector<CaError>& errors);

  /** @endcond */


  /**
   * Removes an error having errorId from the CaError list.
   *  
   * Only the first item will be removed if there are multiple errors
   * with the given errorId.
   *
   * @param errorId the error identifier of the error to be removed.
   */
  void remove (const unsigned int errorId);


  /**
   * Removes all errors having errorId from the CaError list.
   *
   * @param errorId the error identifier of the error to be removed.
   */
  void removeAll(const unsigned int errorId);

  /**
   * Returns true if CaErrorLog contains an errorId
   *
   * @param errorId the error identifier of the error to be found.
   */
  bool contains (const unsigned int errorId) const;


  /** @endcond */
};

LIBCOMBINE_CPP_NAMESPACE_END

#endif  /* __cplusplus */
#endif  /* CaErrorLog_h */
