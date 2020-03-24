/**
 * @file CaErrorLog.cpp
 * @brief Implementation of the CaErrorLog class.
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
#include <string>
#include <list>

#include <sbml/xml/XMLToken.h>
#include <sbml/xml/XMLParser.h>

#include <omex/CaError.h>
#include <omex/CaErrorLog.h>

/** @cond doxygenIgnored */

using namespace std;

/** @endcond */

LIBCOMBINE_CPP_NAMESPACE_BEGIN

#ifdef __cplusplus

/** @cond doxygenLibomexInternal */

/*
 * Creates a new empty CaErrorLog.
 */
CaErrorLog::CaErrorLog ()
{
}

/*
* Copy Constructor
*/
CaErrorLog::CaErrorLog (const CaErrorLog& other)
  : XMLErrorLog(other)
{
}

/*
* Assignment operator
*/
CaErrorLog& CaErrorLog::operator=(const CaErrorLog& other)
{
  XMLErrorLog::operator=(other);
  return *this;
}



/*
 * Used by the Destructor to delete each item in mErrors.
 */
struct Delete : public unary_function<XMLError*, void>
{
  void operator() (XMLError* error) { delete error; }
};


/*
 * Destroys this CaErrorLog.
 */
CaErrorLog::~CaErrorLog ()
{
}


/*
 * See CaError for a list of OMEX error codes and XMLError
 * for a list of system and XML-level error codes.
 */
void
CaErrorLog::logError ( const unsigned int errorId
                       , const unsigned int level
                       , const unsigned int version
                       , const std::string& details
                       , const unsigned int line
                       , const unsigned int column
                       , const unsigned int severity
                       , const unsigned int category )
{
  add( CaError( errorId, level, version, details, line, column,
                  severity, category ));
}


/*
 * Adds the given CaError to the log.
 *
 * @param error CaError, the error to be logged.
 */
void
CaErrorLog::add (const CaError& error)
{
  if (error.getSeverity() != LIBCOMBINE_SEV_NOT_APPLICABLE)
    XMLErrorLog::add(error);
}


/*
 * Logs (copies) the CaErrors in the given CaError list to this
 * CaErrorLog.
 *
 * @param errors list, a list of CaError to be added to the log.
 */
void
CaErrorLog::add (const std::list<CaError>& errors)
{
  list<CaError>::const_iterator end = errors.end();
  list<CaError>::const_iterator iter;

  for (iter = errors.begin(); iter != end; ++iter)
    XMLErrorLog::add( *iter );
}

/*
 * Logs (copies) the CaErrors in the given CaError vector to this
 * CaErrorLog.
 *
 * @param errors vector, a vector of CaError to be added to the log.
 */
void
CaErrorLog::add (const std::vector<CaError>& errors)
{
  vector<CaError>::const_iterator end = errors.end();
  vector<CaError>::const_iterator iter;

  for (iter = errors.begin(); iter != end; ++iter)
    XMLErrorLog::add( *iter );
}

/*
 * Helper class used by CaErrorLog::remove.
 */
class MatchErrorId
{
public:
  MatchErrorId(const unsigned int theId) : idToFind(theId) {};

  bool operator() (XMLError* e) const
  {
    return e->getErrorId() == idToFind;
  };

private:
  unsigned int idToFind;
};


/*
 * Removes an error having errorId from the CaError list.
 *
 * Only the first item will be removed if there are multiple errors
 * with the given errorId.
 *
 * @param errorId the error identifier of the error to be removed.
 */
void
CaErrorLog::remove (const unsigned int errorId)
{
  vector<XMLError*>::iterator delIter;

  // finds an item with the given errorId (the first item will be found if
  // there are two or more items with the same Id)
  delIter = find_if(mErrors.begin(), mErrors.end(), MatchErrorId(errorId));

  if ( delIter != mErrors.end() )
  {
    // deletes (invoke delete operator for the matched item) and erases (removes
    // the pointer from mErrors) the matched item (if any)
    delete *delIter;
    mErrors.erase(delIter);
  }
}

void
CaErrorLog::removeAll (const unsigned int errorId)
{
  vector<XMLError*>::iterator delIter;

  // finds an item with the given errorId (the first item will be found if
  // there are two or more items with the same Id)
  delIter = find_if(mErrors.begin(), mErrors.end(), MatchErrorId(errorId));

  while ( delIter != mErrors.end() )
  {
    // deletes (invoke delete operator for the matched item) and erases (removes
    // the pointer from mErrors) the matched item (if any)
    delete *delIter;
    mErrors.erase(delIter);

    delIter = find_if(mErrors.begin(), mErrors.end(), MatchErrorId(errorId));
  }
}


bool
CaErrorLog::contains (const unsigned int errorId) const
{
  vector<XMLError*>::const_iterator iter;

  // finds an item with the given errorId (the first item will be found if
  // there are two or more items with the same Id)
  iter = find_if(mErrors.begin(), mErrors.end(), MatchErrorId(errorId));

  if ( iter != mErrors.end() )
  {
    return true;
  }
  else
  {
    return false;
  }
}


/*
 * Helper class used by
 * CaErrorLog::getNumFailsWithSeverity(CaErrorSeverity_t).
 */
class MatchSeverity
{
public:
  MatchSeverity(const unsigned int s) : severity(s) {};

  bool operator() (XMLError* e) const
  {
    return e->getSeverity() == severity;
  };

private:
  unsigned int severity;
};

/** @endcond */


unsigned int 
CaErrorLog::getNumFailsWithSeverity(unsigned int severity) const
{
  unsigned int n = 0;

#if defined(__SUNPRO_CC)
  // Workaround for Sun cc which is missing:
  count_if(mErrors.begin(), mErrors.end(), MatchSeverity(severity), n);
#else
  n = (unsigned int)count_if(mErrors.begin(), mErrors.end(), MatchSeverity(severity));
#endif

  return n;
}


/*
 * Returns number of errors that are logged with severity Error
 */
unsigned int
CaErrorLog::getNumFailsWithSeverity(unsigned int severity)
{
  unsigned int n = 0;

#if defined(__SUNPRO_CC)
  // Workaround for Sun cc which is missing:
  count_if(mErrors.begin(), mErrors.end(), MatchSeverity(severity), n);
#else
  n = (unsigned int)count_if(mErrors.begin(), mErrors.end(), MatchSeverity(severity));
#endif

  return n;
}


/*
 * Returns the nth CaError in this log.
 *
 * @param n unsigned int number of the error to retrieve.
 *
 * @return the nth CaError in this log.
 */
const CaError*
CaErrorLog::getError (unsigned int n) const
{
  return static_cast<const CaError*>(XMLErrorLog::getError(n));
}


/*
 * Returns the nth CaError with severity in this log.
 *
 * @param n unsigned int number of the error to retrieve.
 * @param severity the severity sought
 *
 * @return the nth CaError in this log.
 */
const CaError*
CaErrorLog::getErrorWithSeverity(unsigned int n, unsigned int severity) const
{
  unsigned int count = 0;
  MatchSeverity matcher(severity);
  std::vector<XMLError*>::const_iterator it = mErrors.begin();
  for (; it != mErrors.end(); ++it)
  {
    if (matcher(*it))
    {
      if (count == n) return dynamic_cast<const CaError*>(*it);
      ++count;
    }
  }
  return NULL;
}

#endif /* __cplusplus */


/** @cond doxygenIgnored */
/** @endcond */
LIBCOMBINE_CPP_NAMESPACE_END

