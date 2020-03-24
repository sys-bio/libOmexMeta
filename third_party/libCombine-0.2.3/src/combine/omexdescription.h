/**
 * @file omexdescription.h
 * @brief Definition of the OmexDescription class.
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
 * @class OmexDescription
 */

#ifndef LIBCOMBINE_OMEXDESCRIPTION_H
#define LIBCOMBINE_OMEXDESCRIPTION_H

#include <omex/common/extern.h>
#include <omex/common/libcombine-namespace.h>

#include <combine/vcard.h>

#include <sbml/common/libsbml-namespace.h>
#include <sbml/annotation/Date.h>

#ifdef __cplusplus

#include <vector>
#include <string>

LIBCOMBINE_CPP_NAMESPACE_BEGIN

class LIBCOMBINE_EXTERN OmexDescription
{

public:

  /**
   * constructs a new omex description
   */
  OmexDescription();

  /**
   * constructs a new omex description document
   * from XML stream
   *
   * @param stream the xml stream
   */
  OmexDescription(XMLInputStream& stream);

  /**
   * @return RDF namespace
   */
  static const std::string& getRdfNS();

  /**
   * @return dublin core namespace
   */
  static const std::string& getDcNS();

  /**
   * parses the given filename returning all description documents found
   *
   * @param fileName the file to read from
   *
   * @return std::vector of all descriptions in the file
   */
  static std::vector<OmexDescription> parseFile(const std::string& fileName);

  /**
   * parses the given filename returning all description documents found
   *
   * @param xml a string containing one or more omex descriptions
   *
   * @return std::vector of all descriptions in the string
   */
  static std::vector<OmexDescription> parseString(const std::string& xml);

  /**
   * reads all the omes descriptions from the xml input stream
   *
   * @param stream the xml input stream
   *
   * @return
   */
  static std::vector<OmexDescription> readFrom(XMLInputStream& stream);

  /**
   * @return an indication whether this description is empty
   */
  bool isEmpty() const;

  /**
   * @return the description
   */
  std::string getDescription() const;

  /**
   * sets the description
   *
   * @param description the description element (without any xml tags)
   */
  void setDescription(const std::string &description);

  /**
   * @return the about element
   */
  std::string getAbout() const;

  /**
   * Sets the about element of the description
   *
   * @param about the value to set
   */
  void setAbout(const std::string &about);

  /**
   * @return a reference to all creators
   */
  const std::vector<VCard> &getCreators() const;

  /**
   * @return a reference to all creators
   */
  std::vector<VCard> &getCreators();

  /**
   * @return the number of creators
   */
  size_t getNumCreators() const;

  /**
   * sets the creators
   *
   * @param creators the vector of elements to set
   */
  void setCreators(const std::vector<VCard> &creators);

  /**
   * adds another creator to the list
   *
   * @param creator the creator to add
   */
  void addCreator(const VCard& creator);

  /**
   * @return the creation date
   */
  const LIBSBML_CPP_NAMESPACE_QUALIFIER Date &getCreated() const;

  /**
   * @return the creation date
   */
  LIBSBML_CPP_NAMESPACE_QUALIFIER Date &getCreated();

  /**
   * returns the creator for the given index, if not found an
   * empty vcard will be returned.
   *
   * @param index the index for the creator
   *
   * @return the creator if found, will be empty otherwise
   */
  VCard getCreator(unsigned int index) const;

  /**
   * Sets the creation date
   * @param created the date to set
   */
  void setCreated(const LIBSBML_CPP_NAMESPACE_QUALIFIER Date &created);

  /**
   * @return the current date and time as Date object (in UTC)
   */
  static LIBSBML_CPP_NAMESPACE_QUALIFIER Date getCurrentDateAndTime();

  /**
   * @return the vector of all modification dates
   */
  const std::vector<LIBSBML_CPP_NAMESPACE_QUALIFIER Date>& getModified() const;

  /**
   * @return the vector of all modification dates
   */
  std::vector<LIBSBML_CPP_NAMESPACE_QUALIFIER Date>& getModified();

  /**
  * @return the modification date with the given index
  */
  LIBSBML_CPP_NAMESPACE_QUALIFIER Date getModified(int index) const;

  /**
   * @return number of modification dates
   */
  size_t getNumModified() const;

  /**
   * sets the modification dates to the given vector
   *
   * @param modified the modification dates to set
   */
  void setModified(const std::vector<LIBSBML_CPP_NAMESPACE_QUALIFIER Date> &modified);

  /**
   * Adds the given modification date to the vector
   *
   * @param date the date to add
   */
  void addModification(const LIBSBML_CPP_NAMESPACE_QUALIFIER Date& date);

  /**
   * writes this description to the given filename
   *
   * @param fileName the file name to write to
   */
  void writeToFile(const std::string& fileName);

  /**
   * returns this omex description as a string
   *
   * @param omitDeclaration optional boolean flag indicating
   *        that the xml declaration should be omitted (false
   *        if omitted)
   *
   * @return xml string representation of this description
   */
  std::string toXML(bool omitDeclaration = false);

protected:
  /**
   * reads the text node from the next element and returns it
   *
   * @param stream the stream to read from
   *
   * @return the contents of the next text node
   */
  static std::string readString(XMLInputStream &stream);

  /**
   * reads a date from the stream
   *
   * @param stream the stream to read from, a date will only be found
   *        if the next element is a start element with name "W3CDTF"
   *
   * @return the date found (or a default date)
   */
  static LIBSBML_CPP_NAMESPACE_QUALIFIER Date readDate(XMLInputStream &stream);


  /**
  * the about element indicating for which element this description is
  */
  std::string mAbout;

  /**
   * a text description element, that contains a description for the element
   * referenced in the 'about' field. This description is expected to be in
   * xhtml or plain text.
   */
  std::string mDescription;

  /**
   * a vector of creators
   */
  std::vector<VCard> mCreators;

  /**
   * creation date
   */
  LIBSBML_CPP_NAMESPACE_QUALIFIER Date mCreated;

  /**
   * a vector of modification dates
   */
  std::vector<LIBSBML_CPP_NAMESPACE_QUALIFIER Date> mModified;
};

LIBCOMBINE_CPP_NAMESPACE_END

#endif  /* __cplusplus */

#endif /* LIBCOMBINE_OMEXDESCRIPTION_H */
