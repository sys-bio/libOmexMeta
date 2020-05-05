/**
 * @file knownformats.h
 * @brief Definition of the KnownFormats class.
 * @author Frank T. Bergmann
 *
 * <!--------------------------------------------------------------------------
 * This file is part of libSBML. Please visit http://sbml.org for more
 * information about SBML, and the latest version of libSBML.
 *
 * Copyright (C) 2013-2016 jointly by the following organizations:
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
 * @class KnownFormats
 */

#ifndef LIBCOMBINE_KNOWNFORMATS_H
#define LIBCOMBINE_KNOWNFORMATS_H

#include <omex/common/extern.h>

#ifdef __cplusplus

#include <map>
#include <vector>
#include <string>

LIBCOMBINE_CPP_NAMESPACE_BEGIN

class LIBCOMBINE_EXTERN KnownFormats
{
public:
  /**
   * this function tests whether the provided format matches
   * the given formatKey
   *
   * @param formatKey the key
   * @param format the full format string
   *
   * @return boolean indicating whether the format matches the
   *         key or not.
   */
  static bool isFormat(const std::string& formatKey,
                       const std::string& format);


  /**
   * returns the first format string for the given key
   *
   * @param formatKey the key
   *
   * @return the found format string or empty string if not found.
   */
  static std::string lookupFormat(const std::string &formatKey);

  /**
   * Guesses the format from the filename
   *
   * @param fileName the filename, if it is an xml file, the first 128
   *        characters will be looked through to find some of the known
   *        xml formats.
   *
   * @return the format if found, empty string otherwise
   */
  static std::string guessFormat(const std::string& fileName);


  /**
   * adds a new entry to the list of known formats
   *
   * @param formatKey the key for the new known format
   * @param format the format string (mime type or identifiers.org reference)
   *
   */
  static void addKnownFormat(const std::string& formatKey, const std::string& format);
  
  /**
   * @return a vector of all known format keys
   */
  static std::vector< std::string > getFormatKeys();

  /**
   * @return the map of known format 
   */
  static std::map<std::string, std::vector<std::string> >& getKnownFormats();


protected:
  static std::map<std::string, std::vector<std::string> > initializeMap();
  static std::map<std::string, std::vector<std::string> > mKnownFormats;
};

LIBCOMBINE_CPP_NAMESPACE_END

#endif  /* __cplusplus */

#endif  /* LIBCOMBINE_KNOWNFORMATS_H */
