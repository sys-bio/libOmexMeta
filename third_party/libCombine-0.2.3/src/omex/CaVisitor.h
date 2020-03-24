/**
 * @file CaVisitor.h
 * @brief Definition of the CaVisitor class.
 * @author DEVISER
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
 * @class 
 * @sbmlbrief{} TODO:Definition of the CaVisitor class.
 */



#ifndef CaVisitor_h
#define CaVisitor_h


#ifdef __cplusplus


#include <omex/CaTypeCodes.h>


LIBCOMBINE_CPP_NAMESPACE_BEGIN

/**
 * Forward class name declarations avoid cyclic dependencies.
 */

class CaBase;

class CaOmexManifest;
class CaListOf;

class CaContent;
class CaOmexManifest;


class CaVisitor
{
public:

  /**
   * Destructor method.
   */
  virtual ~CaVisitor ();

  /**
   * Interface method for using the <a target="_blank" 
   * href="http://en.wikipedia.org/wiki/Design_pattern_(computer_science)"><i>Visitor
   * Pattern</i></a> to perform operations on CaOmexManifest objects.
   *
   * @param x the CaOmexManifest object to visit.
   */
  virtual void visit (const CaOmexManifest &x);


  /**
   * Interface method for using the <a target="_blank" 
   * href="http://en.wikipedia.org/wiki/Design_pattern_(computer_science)"><i>Visitor
   * Pattern</i></a> to perform operations on CaListOf objects.
   *
   * @param x the CaListOf object to visit.
   *
   * @param type the object type code.
   */
  virtual void visit (const CaListOf       &x, int type);


  /**
   * Interface method for using the <a target="_blank" 
   * href="http://en.wikipedia.org/wiki/Design_pattern_(computer_science)"><i>Visitor
   * Pattern</i></a> to perform operations on CaBase objects.
   *
   * @param x the CaBase object to visit.
   */
  virtual bool visit (const CaBase                    &x);



/**
 * Interface method for using the <a target="_blank"
 * href="http://en.wikipedia.org/wiki/Design_pattern_(computer_science)"><i>Visitor
 * Pattern</i></a> to perform operations on CaBase objects.
 *
 * @param x the CaBase object to visit.
 */
virtual bool visit (const CaContent &x);


  /**
   * Interface method for using the <a target="_blank" 
   * href="http://en.wikipedia.org/wiki/Design_pattern_(computer_science)"><i>Visitor
   * Pattern</i></a> to perform operations on CaOmexManifest objects.
   *
   * @param x the CaOmexManifest object to visit.
   */
  virtual void leave (const CaOmexManifest &x);


  /**
   * Interface method for using the <a target="_blank" 
   * href="http://en.wikipedia.org/wiki/Design_pattern_(computer_science)"><i>Visitor
   * Pattern</i></a> to perform operations on Reaction objects.
   *
   * @param x the Reaction object to visit.
   */
  virtual void leave (const CaBase     &x);


  /**
   * Interface method for using the <a target="_blank" 
   * href="http://en.wikipedia.org/wiki/Design_pattern_(computer_science)"><i>Visitor
   * Pattern</i></a> to perform operations on CaListOf objects.
   *
   * @param x the CaListOf object to visit.
   *
   * @param type the object type code.
   *
   */
  virtual void leave (const CaListOf &x, int type);


/**
 * Interface method for using the <a target="_blank"
 * href="http://en.wikipedia.org/wiki/Design_pattern_(computer_science)"><i>Visitor
 * Pattern</i></a> to perform operations on CaBase objects.
 *
 * @param x the CaBase object to leave.
 */
virtual void leave (const CaContent &x);
};

LIBCOMBINE_CPP_NAMESPACE_END

#endif  /* __cplusplus */
#endif  /* CaVisitor_h */

