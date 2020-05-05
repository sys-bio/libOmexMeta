/**
 * @file vcard.h
 * @brief Definition of the VCard class.
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
 * @class VCard
 */

#ifndef LIBCOMBINE_VCARD_H
#define LIBCOMBINE_VCARD_H

#include <string>
#include <sstream>

#include <omex/common/extern.h>

#include <sbml/xml/XMLNode.h>

#ifdef __cplusplus

LIBCOMBINE_CPP_NAMESPACE_BEGIN

class LIBCOMBINE_EXTERN VCard
{
public:

  /**
   * @brief VCard
   */
  VCard();

  /**
   * @brief VCard
   * @param other
   */
  VCard(const VCard& other);

  /**
   * @brief VCard
   * @param stream
   */
  VCard(XMLInputStream& stream, const XMLToken& current);

  /**
   * @return true if empty(no names specified)
   */
  bool isEmpty() const;

  /**
   * @return an xml representation of this class
   */
  std::string toXML() const;

  /**
   * @return the family name
   */
  std::string getFamilyName() const;

  /**
   * sets the family name
   *
   * @param familyName the name
   */
  void setFamilyName(const std::string &familyName);

  /**
   * @return the first name
   */
  std::string getGivenName() const;

  /**
   * sets the first name
   *
   * @param givenName the name
   */
  void setGivenName(const std::string &givenName);

  /**
   * @return the email
   */
  std::string getEmail() const;

  /**
   * sets the email address
   *
   * @param email the email address
   */
  void setEmail(const std::string &email);

  /**
   * @return the organization
   */
  std::string getOrganization() const;

  /**
   * sets the organization
   *
   * @param organization the organization
   */
  void setOrganization(const std::string &organization);

private:
  std::string mFamilyName;
  std::string mGivenName;
  std::string mEmail;
  std::string mOrganization;

};


LIBCOMBINE_CPP_NAMESPACE_END

#endif  /* __cplusplus */
#endif  /* LIBCOMBINE_VCARD_H */
