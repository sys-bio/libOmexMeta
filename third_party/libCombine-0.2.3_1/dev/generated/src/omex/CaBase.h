/**
 * @file CaBase.h
 * @brief Definition of the CaBase class.
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
 * @class CaBase
 * @sbmlbrief{} TODO:Definition of the CaBase class.
 */


#ifndef CaBase_h
#define CaBase_h


#include <omex/common/extern.h>
#include <omex/common/libcombine-namespace.h>
#include <sbml/common/libsbml-namespace.h>
#include <omex/common/combinefwd.h>
#include <omex/CaTypeCodes.h>
#include <omex/CaNamespaces.h>
#include <omex/CaConstructorException.h>
#include <sbml/util/List.h>
#include <sbml/SyntaxChecker.h>
#include <sbml/ExpectedAttributes.h>
#include <sbml/xml/XMLNode.h>

#ifdef __cplusplus


#include <string>
#include <stdexcept>
#include <algorithm>

#include <omex/CaErrorLog.h>
#include <omex/CaVisitor.h>

LIBSBML_CPP_NAMESPACE_BEGIN

class Model;

class List;

class XMLAttributes;
class XMLInputStream;
class XMLNamespaces;
class XMLOutputStream;
class XMLToken;

LIBSBML_CPP_NAMESPACE_END

LIBCOMBINE_CPP_NAMESPACE_BEGIN

class CaOmexManifest;


class LIBCOMBINE_EXTERN CaBase
{
public:

  /**
   * Destroys this object.
   */
  virtual ~CaBase ();


  /**
   * Assignment operator for CaBase.
   *
   * @param rhs The object whose values are used as the basis of the
   * assignment.
   */
  CaBase& operator=(const CaBase& rhs);


  /** @cond doxygenLibomexInternal */
  /**
   * Accepts the given CaVisitor for this CaBase object.
   *
   * @param v the CaVisitor instance to be used
   *
   * @return the result of calling <code>v.visit()</code>.
   */
  virtual bool accept (CaVisitor& v) const = 0;
  /** @endcond */


  /**
   * Creates and returns a deep copy of this CaBase object.
   *
   * @return the (deep) copy of this CaBase object.
   */
  virtual CaBase* clone () const = 0;


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
   * Returns the first child element it can find with a specific "id"
   * attribute value, or @c NULL if no such object is found.
   *
   * @param id string representing the "id" attribute value of the
   * object to find.
   *
   * @return pointer to the first element found with the given identifier.
   */
  virtual const CaBase* getElementBySId(const std::string& metaid) const;


  /**
   * Returns the first child element it can find with a specific "metaid"
   * attribute value, or @c NULL if no such object is found.
   *
   * @param metaid string representing the "metaid" attribute value of the
   * object to find.
   *
   * @return pointer to the first element found with the given meta-identifier.
   */
  virtual CaBase* getElementByMetaId(const std::string& metaid);

  /**
   * Returns the first child element it can find with a specific "metaid"
   * attribute value, or @c NULL if no such object is found.
   *
   * @param metaid string representing the "metaid" attribute value of the
   * object to find.
   *
   * @return pointer to the first element found with the given meta-identifier.
   */
  virtual const CaBase* getElementByMetaId(const std::string& metaid) const;

  /**
   * Returns a List of all child CaBase objects, including those nested to
   * an arbitrary depth.
   *
   * @return a pointer to a List of pointers to all children objects.
   */
  virtual List* getAllElements();


  /**
   * Returns the value of the "metaid" attribute of this object.
   *
   * @copydetails doc_what_is_metaid
   *  
   * @return the meta-identifier of this OMEX object.
   *
   * @see isSetMetaId()
   * @see setMetaId(const std::string& metaid)
   */
  const std::string& getMetaId () const;


  /**
   * Returns the value of the "metaid" attribute of this object.
   *
   * @copydetails doc_what_is_metaid
   *  
   * @return the meta-identifier of this OMEX object, as a string.
   *
   * @see isSetMetaId()
   * @see setMetaId(const std::string& metaid)
   */
  std::string& getMetaId ();

  
  /*
   * @return the id of this OMEX object.
   *
   * @note The fact that the value of attribute "id" is defined on the
   * CaBase parent class object is a convenience provided by libCombine, and
   * <b>does not strictly follow OMEX specifications</b>.  This libCombine
   * implementation of CaBase allows client applications to use more
   * generalized code in some situations (for instance, when manipulating
   * objects that are all known to have identifiers), but beware that not
   * all OMEX object classes provide an "id" attribute.  LibCombine will allow
   * the identifier to be set, but it will not read nor write "id"
   * attributes for objects that do not possess them according to the OMEX
   * specification for the Level and Version in use.
   *
   */
  virtual const std::string& getId() const;

  /**
   * Returns the content of the "notes" subelement of this object as
   * a tree of XMLNode objects.
   *
   * The "notes" element content returned by this method will be in XML
   * form, but libCombine does not provide an object model specifically for
   * the content of notes.  Callers will need to traverse the XML tree
   * structure using the facilities available on XMLNode and related
   * objects.  For an alternative method of accessing the notes, see
   * getNotesString().
   *
   * @return the content of the "notes" subelement of this OMEX object as a
   * tree structure composed of XMLNode objects.
   *
   * @see getNotesString()
   * @see isSetNotes()
   * @see setNotes(const XMLNode* notes)
   * @see setNotes(const std::string& notes)
   * @see appendNotes(const XMLNode* notes)
   * @see appendNotes(const std::string& notes)
   * @see unsetNotes()
   * @see SyntaxChecker::hasExpectedXHTMLSyntax(@if java XMLNode@endif)
   */
  LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode* getNotes();


  /**
   * Returns the content of the "notes" subelement of this object as
   * a tree of XMLNode objects.
   *
   * The "notes" element content returned by this method will be in XML
   * form, but libCombine does not provide an object model specifically for
   * the content of notes.  Callers will need to traverse the XML tree
   * structure using the facilities available on XMLNode and related
   * objects.  For an alternative method of accessing the notes, see
   * getNotesString().
   *
   * @return the content of the "notes" subelement of this OMEX object as a
   * tree structure composed of XMLNode objects.
   *
   * @see getNotesString()
   * @see isSetNotes()
   * @see setNotes(const XMLNode* notes)
   * @see setNotes(const std::string& notes)
   * @see appendNotes(const XMLNode* notes)
   * @see appendNotes(const std::string& notes)
   * @see unsetNotes()
   * @see SyntaxChecker::hasExpectedXHTMLSyntax(@if java XMLNode@endif)
   */
  const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode* getNotes() const;


  /**
   * Returns the content of the "notes" subelement of this object as a
   * string.
   *
   * For an alternative method of accessing the notes, see getNotes(),
   * which returns the content as an XMLNode tree structure.  Depending on
   * an application's needs, one or the other method may be more
   * convenient.
   *
   * @return the content of the "notes" subelement of this OMEX object as a
   * string.
   *
   * @see getNotes()
   * @see isSetNotes()
   * @see setNotes(const XMLNode* notes)
   * @see setNotes(const std::string& notes)
   * @see appendNotes(const XMLNode* notes)
   * @see appendNotes(const std::string& notes)
   * @see unsetNotes()
   * @see SyntaxChecker::hasExpectedXHTMLSyntax(@if java XMLNode@endif)
   */
  std::string getNotesString ();


  /**
   * Returns the content of the "notes" subelement of this object as a
   * string.
   *
   * For an alternative method of accessing the notes, see getNotes(),
   * which returns the content as an XMLNode tree structure.  Depending on
   * an application's needs, one or the other method may be more
   * convenient.
   *
   * @return the content of the "notes" subelement of this OMEX object as a
   * string.
   *
   * @see getNotes()
   * @see isSetNotes()
   * @see setNotes(const XMLNode* notes)
   * @see setNotes(const std::string& notes)
   * @see appendNotes(const XMLNode* notes)
   * @see appendNotes(const std::string& notes)
   * @see unsetNotes()
   * @see SyntaxChecker::hasExpectedXHTMLSyntax(@if java XMLNode@endif)
   */
  std::string getNotesString () const;


  /**
   * Returns the content of the "annotation" subelement of this object as
   * a tree of XMLNode objects.
   *
   * The annotations returned by this method will be in XML form.  LibCombine
   * provides an object model and related interfaces for certain specific
   * kinds of annotations, namely model history information and RDF
   * content.  See the ModelHistory, CVTerm and RDFAnnotationParser classes
   * for more information about the facilities available.
   *
   * @return the annotation of this OMEX object as a tree of XMLNode objects.
   *
   * @see getAnnotationString()
   * @see isSetAnnotation()
   * @see setAnnotation(const XMLNode* annotation)
   * @see setAnnotation(const std::string& annotation)
   * @see appendAnnotation(const XMLNode* annotation)
   * @see appendAnnotation(const std::string& annotation)
   * @see unsetAnnotation()
   */
  LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode* getAnnotation ();


  /**
   * Returns the content of the "annotation" subelement of this object as
   * a tree of XMLNode objects.
   *
   * The annotations returned by this method will be in XML form.  LibCombine
   * provides an object model and related interfaces for certain specific
   * kinds of annotations, namely model history information and RDF
   * content.  See the ModelHistory, CVTerm and RDFAnnotationParser classes
   * for more information about the facilities available.
   *
   * @return the annotation of this OMEX object as a tree of XMLNode objects.
   *
   * @see getAnnotationString()
   * @see isSetAnnotation()
   * @see setAnnotation(const XMLNode* annotation)
   * @see setAnnotation(const std::string& annotation)
   * @see appendAnnotation(const XMLNode* annotation)
   * @see appendAnnotation(const std::string& annotation)
   * @see unsetAnnotation()
   */
  const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode* getAnnotation () const;


  /**
   * Returns the content of the "annotation" subelement of this object as a
   * character string.
   *
   * The annotations returned by this method will be in string form.  See the
   * method getAnnotation() for a version that returns annotations in XML form.
   *
   * @return the annotation of this OMEX object as a character string.
   *
   * @see getAnnotation()
   * @see isSetAnnotation()
   * @see setAnnotation(const XMLNode* annotation)
   * @see setAnnotation(const std::string& annotation)
   * @see appendAnnotation(const XMLNode* annotation)
   * @see appendAnnotation(const std::string& annotation)
   * @see unsetAnnotation()
   */
  std::string getAnnotationString ();


  /**
   * Returns the content of the "annotation" subelement of this object as a
   * character string.
   *
   * The annotations returned by this method will be in string form.  See the
   * method getAnnotation() for a version that returns annotations in XML form.
   *
   * @return the annotation of this OMEX object as a character string.
   *
   * @see getAnnotation()
   * @see isSetAnnotation()
   * @see setAnnotation(const XMLNode* annotation)
   * @see setAnnotation(const std::string& annotation)
   * @see appendAnnotation(const XMLNode* annotation)
   * @see appendAnnotation(const std::string& annotation)
   * @see unsetAnnotation()
   */
  std::string getAnnotationString () const;


  /**
   * Returns a list of the XML Namespaces declared on the OMEX document
   * owning this object.
   *
   * The CaNamespaces object encapsulates OMEX Level/Version/namespaces
   * information.  It is used to communicate the OMEX Level, Version, and (in
   * Level&nbsp;3) packages used in addition to OMEX Level&nbsp;3 Core.
   *
   * @return the XML Namespaces associated with this OMEX object, or @c NULL
   * in certain very usual circumstances where a namespace is not set.
   *
   * @see getLevel()
   * @see getVersion()
   */
  virtual const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces* getNamespaces() const ;


  /**
   * Returns a list of the XML Namespaces declared on the OMEX document
   * owning this object.
   *
   * The CaNamespaces object encapsulates OMEX Level/Version/namespaces
   * information.  It is used to communicate the OMEX Level, Version, and (in
   * Level&nbsp;3) packages used in addition to OMEX Level&nbsp;3 Core.
   *
   * @return the XML Namespaces associated with this OMEX object, or @c NULL
   * in certain very usual circumstances where a namespace is not set.
   *
   * @see getLevel()
   * @see getVersion()
   */
  virtual LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces* getNamespaces();


  /**
   * Returns the CaOmexManifest object containing this object instance.
   *
   * This method allows the caller to obtain the CaOmexManifest for the
   * current object.
   * 
   * @return the parent CaOmexManifest object of this OMEX object.
   *
   * @see getParentCaObject()
   * @see getModel()
   */
  const CaOmexManifest* getCaOmexManifest () const;


  /**
   * Returns the CaOmexManifest object containing this object instance.
   *
   * This method allows the caller to obtain the CaOmexManifest for the
   * current object.
   * 
   * @return the parent CaOmexManifest object of this OMEX object.
   *
   * @see getParentCaObject()
   * @see getModel()
   */
  CaOmexManifest* getCaOmexManifest ();


  /**
   * Returns the parent OMEX object containing this object.
   *
   * This returns the immediately-containing object.  This method is
   * convenient when holding an object nested inside other objects in an
   * OMEX model.  
   * 
   * @return the parent OMEX object of this OMEX object.
   *
   * @see getCaOmexManifest()
   * @see getModel()
   */
  CaBase* getParentCaObject();


  /**
   * Returns the parent OMEX object containing this object.
   *
   * This returns the immediately-containing object.  This method is
   * convenient when holding an object nested inside other objects in an
   * OMEX model.  
   * 
   * @return the parent OMEX object of this OMEX object.
   *
   * @see getCaOmexManifest()
   * @see getModel()
   */
  const CaBase* getParentCaObject() const;


  /**
   * Returns the first ancestor object that has the given OMEX type code.
   *
   * @if clike LibCombine attaches an identifying code to every kind of OMEX
   * object.  These are known as <em>OMEX type codes</em>.  The set of
   * possible type codes is defined in the enumeration #CaTypeCode_t.
   * The names of the type codes all begin with the characters @c
   * OMEX_. @endif@if java LibCombine attaches an identifying code to every
   * kind of OMEX object.  These are known as <em>OMEX type codes</em>.  In
   * other languages, the set of type codes is stored in an enumeration; in
   * the Java language interface for libCombine, the type codes are defined as
   * static integer constants in the interface class {@link
   * libcombineConstants}.  The names of the type codes all begin with the
   * characters @c OMEX_. @endif@if python LibCombine attaches an identifying
   * code to every kind of OMEX object.  These are known as <em>OMEX type
   * codes</em>.  In the Python language interface for libCombine, the type
   * codes are defined as static integer constants in the interface class
   * @link libcombine@endlink.  The names of the type codes all begin with the
   * characters @c OMEX_. @endif@if csharp LibCombine attaches an identifying
   * code to every kind of OMEX object.  These are known as <em>OMEX type
   * codes</em>.  In the C# language interface for libCombine, the type codes
   * are defined as static integer constants in the interface class @link
   * libcombinecs.libcombine libcombine@endlink.  The names of the type codes all begin with
   * the characters @c OMEX_. @endif@~
   *
   * This method searches the tree of objects that are parents of this
   * object, and returns the first one that has the given OMEX type code from 
   * the given @p pkgName.
   *
   * @param type the OMEX type code of the object sought
   *
   * @return the ancestor OMEX object of this OMEX object that corresponds
   * to the given @if clike #CaTypeCode_t value@else OMEX object type
   * code@endif, or @c NULL if no ancestor exists.
   */
  CaBase* getAncestorOfType(int type);


  /**
   * Returns the first ancestor object that has the given OMEX type code.
   *
   * @if clike LibCombine attaches an identifying code to every kind of OMEX
   * object.  These are known as <em>OMEX type codes</em>.  The set of
   * possible type codes is defined in the enumeration #CaTypeCode_t.
   * The names of the type codes all begin with the characters @c
   * OMEX_. @endif@if java LibCombine attaches an identifying code to every
   * kind of OMEX object.  These are known as <em>OMEX type codes</em>.  In
   * other languages, the set of type codes is stored in an enumeration; in
   * the Java language interface for libCombine, the type codes are defined as
   * static integer constants in the interface class {@link
   * libcombineConstants}.  The names of the type codes all begin with the
   * characters @c OMEX_. @endif@if python LibCombine attaches an identifying
   * code to every kind of OMEX object.  These are known as <em>OMEX type
   * codes</em>.  In the Python language interface for libCombine, the type
   * codes are defined as static integer constants in the interface class
   * @link libcombine@endlink.  The names of the type codes all begin with the
   * characters @c OMEX_. @endif@if csharp LibCombine attaches an identifying
   * code to every kind of OMEX object.  These are known as <em>OMEX type
   * codes</em>.  In the C# language interface for libCombine, the type codes
   * are defined as static integer constants in the interface class @link
   * libcombinecs.libcombine libcombine@endlink.  The names of the type codes all begin with
   * the characters @c OMEX_. @endif@~
   *
   * This method searches the tree of objects that are parents of this
   * object, and returns the first one that has the given OMEX type code from 
   * the given @p pkgName.
   *
   * @param type the OMEX type code of the object sought
   *
   * @return the ancestor OMEX object of this OMEX object that corresponds
   * to the given @if clike #CaTypeCode_t value@else OMEX object type
   * code@endif, or @c NULL if no ancestor exists.
   *
   */
  const CaBase* getAncestorOfType(int type) const;


  /**
   * Returns the line number on which this object first appears in the XML
   * representation of the OMEX document, or '0' if the object was created,
   * not read from a file.
   *
   * @return the line number of this OMEX object, or '0' if no such value.
   *
   * @note The line number for each construct in an OMEX model is set upon
   * reading the model.  The accuracy of the line number depends on the
   * correctness of the XML representation of the model, and on the
   * particular XML parser library being used.  The former limitation
   * relates to the following problem: if the model is actually invalid
   * XML, then the parser may not be able to interpret the data correctly
   * and consequently may not be able to establish the real line number.
   * The latter limitation is simply that different parsers seem to have
   * their own accuracy limitations, and out of all the parsers supported
   * by libCombine, none have been 100% accurate in all situations. (At this
   * time, libCombine supports the use of <a target="_blank"
   * href="http://xmlsoft.org">libxml2</a>, <a target="_blank"
   * href="http://expat.sourceforge.net/">Expat</a> and <a target="_blank"
   * href="http://xerces.apache.org/xerces-c/">Xerces</a>.)
   *
   * @see getColumn()
   */
  unsigned int getLine () const;


  /**
   * Returns the column number on which this object first appears in the XML
   * representation of the OMEX document, or '0' if the object was created,
   * not read from a file.
   * 
   * @return the column number of this OMEX object, or '0' if no such value.
   * 
   * @note The column number for each construct in an OMEX model is set
   * upon reading the model.  The accuracy of the column number depends on
   * the correctness of the XML representation of the model, and on the
   * particular XML parser library being used.  The former limitation
   * relates to the following problem: if the model is actually invalid
   * XML, then the parser may not be able to interpret the data correctly
   * and consequently may not be able to establish the real column number.
   * The latter limitation is simply that different parsers seem to have
   * their own accuracy limitations, and out of all the parsers supported
   * by libCombine, none have been 100% accurate in all situations. (At this
   * time, libCombine supports the use of <a target="_blank"
   * href="http://xmlsoft.org">libxml2</a>, <a target="_blank"
   * href="http://expat.sourceforge.net/">Expat</a> and <a target="_blank"
   * href="http://xerces.apache.org/xerces-c/">Xerces</a>.)
   * 
   * @see getLine()
   */
  unsigned int getColumn () const;


  /**
   * Predicate returning @c true if this object's "metaid" attribute is set.
   *
   * @return @c true if the "metaid" attribute of this OMEX object is
   * set, @c false otherwise.
   *
   * @see getMetaId()
   * @see setMetaId(const std::string& metaid)
   */
  bool isSetMetaId () const;


  /**
   * Predicate returning @c true if this object's "id" attribute is set.
   *
   * @return @c true if the "id" attribute of this OMEX object is
   * set, @c false otherwise.
   *
   * @see getId()
   */
  virtual bool isSetId() const;

  /**
   * Predicate returning @c true if this
   * object's "notes" subelement exists and has content.
   *
   * The optional OMEX element named "notes", present on every major OMEX
   * component type, is intended as a place for storing optional
   * information intended to be seen by humans.  An example use of the
   * "notes" element would be to contain formatted user comments about the
   * model element in which the "notes" element is enclosed.  Every object
   * derived directly or indirectly from type CaBase can have a separate
   * value for "notes", allowing users considerable freedom when adding
   * comments to their models.
   *
   * The format of "notes" elements must be <a target="_blank"
   * href="http://www.w3.org/TR/xhtml1/">XHTML&nbsp;1.0</a>.  To help
   * verify the formatting of "notes" content, libCombine provides the static
   * utility method SyntaxChecker::hasExpectedXHTMLSyntax(@if java XMLNode xhtml@endif); however,
   * readers are urged to consult the appropriate <a target="_blank"
   * href="http://omex.org/Documents/Specifications">OMEX specification
   * document</a> for the Level and Version of their model for more
   * in-depth explanations.  The OMEX Level&nbsp;2 and &nbsp;3
   * specifications have considerable detail about how "notes" element
   * content must be structured.
   *
   * @return @c true if a "notes" subelement exists, @c false otherwise.
   * 
   * @see getNotes()
   * @see getNotesString()
   * @see setNotes(const XMLNode* notes)
   * @see setNotes(const std::string& notes)
   * @see appendNotes(const XMLNode* notes)
   * @see appendNotes(const std::string& notes)
   * @see unsetNotes()
   * @see SyntaxChecker::hasExpectedXHTMLSyntax(@if java XMLNode@endif)
   */
  bool isSetNotes () const;


  /**
   * Predicate returning @c true if this
   * object's "annotation" subelement exists and has content.
   *
   * Whereas the CaBase "notes" subelement is a container for content to be
   * shown directly to humans, the "annotation" element is a container for
   * optional software-generated content @em not meant to be shown to
   * humans.  Every object derived from CaBase can have its own value for
   * "annotation".  The element's content type is <a target="_blank"
   * href="http://www.w3.org/TR/2004/REC-xml-20040204/#elemdecls">XML type
   * "any"</a>, allowing essentially arbitrary well-formed XML data
   * content.
   *
   * OMEX places a few restrictions on the organization of the content of
   * annotations; these are intended to help software tools read and write
   * the data as well as help reduce conflicts between annotations added by
   * different tools.  Please see the OMEX specifications for more details.
   *
   * @return @c true if a "annotation" subelement exists, @c false
   * otherwise.
   * 
   * @see getAnnotation()
   * @see getAnnotationString()
   * @see setAnnotation(const XMLNode* annotation)
   * @see setAnnotation(const std::string& annotation)
   * @see appendAnnotation(const XMLNode* annotation)
   * @see appendAnnotation(const std::string& annotation)
   * @see unsetAnnotation()
   */
  bool isSetAnnotation () const;


  /**
   * Sets the value of the meta-identifier attribute of this object.
   *
   * @copydetails doc_what_is_metaid 
   *
   * The string @p metaid is copied.  
   *
   * @param metaid the identifier string to use as the value of the
   * "metaid" attribute
   *
   * @copydetails doc_returns_success_code
   * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
   * @li @omexconstant{LIBCOMBINE_INVALID_ATTRIBUTE_VALUE, OperationReturnValues_t}
   * @li @omexconstant{LIBCOMBINE_UNEXPECTED_ATTRIBUTE, OperationReturnValues_t}
   * 
   * @see getMetaId()
   * @see isSetMetaId()
   */
  int setMetaId (const std::string& metaid);


  /**
  /**
   * Sets the value of the "id" attribute of this OMEX object.
   *
   * @copydetails doc_set_id
   */
  virtual int setId(const std::string& sid);


  /**
   * Sets the value of the "annotation" subelement of this OMEX object.
   *
   * The content of @p annotation is copied, and any previous content of
   * this object's "annotation" subelement is deleted.
   * 
   * Whereas the CaBase "notes" subelement is a container for content to be
   * shown directly to humans, the "annotation" element is a container for
   * optional software-generated content @em not meant to be shown to
   * humans.  Every object derived from CaBase can have its own value for
   * "annotation".  The element's content type is <a target="_blank"
   * href="http://www.w3.org/TR/2004/REC-xml-20040204/#elemdecls">XML type
   * "any"</a>, allowing essentially arbitrary well-formed XML data
   * content.
   *
   * OMEX places a few restrictions on the organization of the content of
   * annotations; these are intended to help software tools read and write
   * the data as well as help reduce conflicts between annotations added by
   * different tools.  Please see the OMEX specifications for more details.
   *
   * Call this method will result in any existing content of the
   * "annotation" subelement to be discarded.  Unless you have taken steps
   * to first copy and reconstitute any existing annotations into the @p
   * annotation that is about to be assigned, it is likely that performing
   * such wholesale replacement is unfriendly towards other software
   * applications whose annotations are discarded.  An alternative may be
   * to use CaBase::appendAnnotation(const XMLNode* annotation) or
   * CaBase::appendAnnotation(const std::string& annotation).
   *
   * @param annotation an XML structure that is to be used as the new content
   * of the "annotation" subelement of this object
   *
   * @return integer value indicating success/failure of the
   * function.  The possible values returned by this function are:
   * @li @link OperationReturnValues_t#LIBCOMBINE_OPERATION_SUCCESS LIBCOMBINE_OPERATION_SUCCESS @endlink
   *
   * @see getAnnotationString()
   * @see isSetAnnotation()
   * @see setAnnotation(const std::string& annotation)
   * @see appendAnnotation(const XMLNode* annotation)
   * @see appendAnnotation(const std::string& annotation)
   * @see unsetAnnotation()
   */
  virtual int setAnnotation (LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode* annotation);


  /**
   * Sets the value of the "annotation" subelement of this OMEX object.
   *
   * The content of @p annotation is copied, and any previous content of
   * this object's "annotation" subelement is deleted.
   * 
   * Whereas the CaBase "notes" subelement is a container for content to be
   * shown directly to humans, the "annotation" element is a container for
   * optional software-generated content @em not meant to be shown to
   * humans.  Every object derived from CaBase can have its own value for
   * "annotation".  The element's content type is <a target="_blank"
   * href="http://www.w3.org/TR/2004/REC-xml-20040204/#elemdecls">XML type
   * "any"</a>, allowing essentially arbitrary well-formed XML data
   * content.
   *
   * OMEX places a few restrictions on the organization of the content of
   * annotations; these are intended to help software tools read and write
   * the data as well as help reduce conflicts between annotations added by
   * different tools.  Please see the OMEX specifications for more details.
   *
   * Call this method will result in any existing content of the
   * "annotation" subelement to be discarded.  Unless you have taken steps
   * to first copy and reconstitute any existing annotations into the @p
   * annotation that is about to be assigned, it is likely that performing
   * such wholesale replacement is unfriendly towards other software
   * applications whose annotations are discarded.  An alternative may be
   * to use CaBase::appendAnnotation(const XMLNode* annotation) or
   * CaBase::appendAnnotation(const std::string& annotation).
   *
   * @param annotation an XML string that is to be used as the content
   * of the "annotation" subelement of this object
   *
   * @return integer value indicating success/failure of the
   * function.  The possible values returned by this function are:
   * @li @link OperationReturnValues_t#LIBCOMBINE_OPERATION_SUCCESS LIBCOMBINE_OPERATION_SUCCESS @endlink
   * @li @link OperationReturnValues_t#LIBCOMBINE_OPERATION_FAILED LIBCOMBINE_OPERATION_FAILED @endlink
   *
   * @see getAnnotationString()
   * @see isSetAnnotation()
   * @see setAnnotation(const XMLNode* annotation)
   * @see appendAnnotation(const XMLNode* annotation)
   * @see appendAnnotation(const std::string& annotation)
   * @see unsetAnnotation()
   */
  virtual int setAnnotation (const std::string& annotation);


  /**
   * Appends the given @p annotation to the "annotation" subelement of this
   * object.
   * 
   * Whereas the CaBase "notes" subelement is a container for content to be
   * shown directly to humans, the "annotation" element is a container for
   * optional software-generated content @em not meant to be shown to
   * humans.  Every object derived from CaBase can have its own value for
   * "annotation".  The element's content type is <a
   * target="_blank"
   * href="http://www.w3.org/TR/2004/REC-xml-20040204/#elemdecls">XML type "any"</a>,
   * allowing essentially arbitrary well-formed XML data content.
   *
   * OMEX places a few restrictions on the organization of the content of
   * annotations; these are intended to help software tools read and write
   * the data as well as help reduce conflicts between annotations added by
   * different tools.  Please see the OMEX specifications for more details.
   *
   * Unlike CaBase::setAnnotation(const XMLNode* annotation) or
   * CaBase::setAnnotation(const std::string& annotation), this method
   * allows other annotations to be preserved when an application adds its
   * own data.
   *
   * @param annotation an XML structure that is to be copied and appended
   * to the content of the "annotation" subelement of this object
   *
   * @return integer value indicating success/failure of the
   * function.  The possible values returned by this function are:
   * @li @link OperationReturnValues_t#LIBCOMBINE_OPERATION_SUCCESS LIBCOMBINE_OPERATION_SUCCESS @endlink
   * @li @link OperationReturnValues_t#LIBCOMBINE_OPERATION_FAILED LIBCOMBINE_OPERATION_FAILED @endlink
   *
   * @see getAnnotationString()
   * @see isSetAnnotation()
   * @see setAnnotation(const XMLNode* annotation)
   * @see setAnnotation(const std::string& annotation)
   * @see appendAnnotation(const std::string& annotation)
   * @see unsetAnnotation()
   */
  virtual int appendAnnotation (const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode* annotation);


  /**
   * Appends the given @p annotation to the "annotation" subelement of this
   * object.
   *
   * Whereas the CaBase "notes" subelement is a container for content to be
   * shown directly to humans, the "annotation" element is a container for
   * optional software-generated content @em not meant to be shown to
   * humans.  Every object derived from CaBase can have its own value for
   * "annotation".  The element's content type is <a
   * target="_blank"
   * href="http://www.w3.org/TR/2004/REC-xml-20040204/#elemdecls">XML type "any"</a>,
   * allowing essentially arbitrary well-formed XML data content.
   *
   * OMEX places a few restrictions on the organization of the content of
   * annotations; these are intended to help software tools read and write
   * the data as well as help reduce conflicts between annotations added by
   * different tools.  Please see the OMEX specifications for more details.
   *
   * Unlike CaBase::setAnnotation(const XMLNode* annotation) or
   * CaBase::setAnnotation(const std::string& annotation), this method
   * allows other annotations to be preserved when an application adds its
   * own data.
   *
   * @param annotation an XML string that is to be copied and appended
   * to the content of the "annotation" subelement of this object
   *
   * @return integer value indicating success/failure of the
   * function.  The possible values returned by this function are:
   * @li @link OperationReturnValues_t#LIBCOMBINE_OPERATION_SUCCESS LIBCOMBINE_OPERATION_SUCCESS @endlink
   * @li @link OperationReturnValues_t#LIBCOMBINE_OPERATION_FAILED LIBCOMBINE_OPERATION_FAILED @endlink
   *
   * @see getAnnotationString()
   * @see isSetAnnotation()
   * @see setAnnotation(const XMLNode* annotation)
   * @see setAnnotation(const std::string& annotation)
   * @see appendAnnotation(const XMLNode* annotation)
   * @see unsetAnnotation()
   */
  virtual int appendAnnotation (const std::string& annotation);


  /**
   * Removes the top-level element within the "annotation" subelement of this
   * OMEX object with the given name and optional URI.
   *
   * OMEX places a few restrictions on the organization of the content of
   * annotations; these are intended to help software tools read and write
   * the data as well as help reduce conflicts between annotations added by
   * different tools.  Please see the OMEX specifications for more details.
   *
   * Calling this method allows a particular annotation element to be removed
   * whilst the remaining annotations remain intact.
   *
   * @param elementName a string representing the name of the top level
   * annotation element that is to be removed
   * @param elementURI an optional string that is used to check both the name
   * and URI of the top level element to be removed
   *
   * @return integer value indicating success/failure of the
   * function.  The possible values returned by this function are:
   * @li @link OperationReturnValues_t#LIBCOMBINE_OPERATION_SUCCESS LIBCOMBINE_OPERATION_SUCCESS @endlink
   * @li @link OperationReturnValues_t#LIBCOMBINE_OPERATION_FAILED LIBCOMBINE_OPERATION_FAILED @endlink
   * @li @link OperationReturnValues_t#LIBCOMBINE_ANNOTATION_NAME_NOT_FOUND LIBCOMBINE_ANNOTATION_NAME_NOT_FOUND @endlink
   * @li @link OperationReturnValues_t#LIBCOMBINE_ANNOTATION_NS_NOT_FOUND LIBCOMBINE_ANNOTATION_NS_NOT_FOUND @endlink
   *
   * @see replaceTopLevelAnnotationElement(const XMLNode *)
   * @see replaceTopLevelAnnotationElement(const std::string&)
   */
  int removeTopLevelAnnotationElement(const std::string elementName,
                                      const std::string elementURI = "");


  /**
   * Replaces the given top-level element within the "annotation"
   * subelement of this OMEX object and with the annotation element supplied.
   *
   * OMEX places a few restrictions on the organization of the content of
   * annotations; these are intended to help software tools read and write
   * the data as well as help reduce conflicts between annotations added by
   * different tools.  Please see the OMEX specifications for more details.
   *
   * This method determines the name of the element to be replaced from the
   * annotation argument. Functionally it is equivalent to calling
   * <code> removeTopLevelAnnotationElement(name); appendAnnotation(annotation_with_name);
   * </code> with the exception that the placement of the annotation element remains
   * the same.
   *
   * @param annotation XMLNode representing the replacement top level annotation
   *
   * @return integer value indicating success/failure of the
   * function.  The possible values returned by this function are:
   * @li @link OperationReturnValues_t#LIBCOMBINE_OPERATION_SUCCESS LIBCOMBINE_OPERATION_SUCCESS @endlink
   * @li @link OperationReturnValues_t#LIBCOMBINE_OPERATION_FAILED LIBCOMBINE_OPERATION_FAILED @endlink
   * @li @link OperationReturnValues_t#LIBCOMBINE_INVALID_OBJECT LIBCOMBINE_INVALID_OBJECT @endlink
   *
   * @see removeTopLevelAnnotationElement(const std::string elementName, const std::string elementURI)
   * @see replaceTopLevelAnnotationElement(const std::string&)
   */
  int replaceTopLevelAnnotationElement(const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode* annotation);


  /**
   * Replaces the given top-level element within the "annotation"
   * subelement of this OMEX object and with the annotation element supplied.
   *
   * OMEX places a few restrictions on the organization of the content of
   * annotations; these are intended to help software tools read and write
   * the data as well as help reduce conflicts between annotations added by
   * different tools.  Please see the OMEX specifications for more details.
   *
   * This method determines the name of the element to be replaced from the
   * annotation argument. Functionally it is equivalent to calling
   * <code> removeTopLevelAnnotationElement(name); appendAnnotation(annotation_with_name);
   * </code> with the exception that the placement of the annotation element remains
   * the same.
   *
   * @param annotation string representing the replacement top level annotation
   *
   * @return integer value indicating success/failure of the
   * function.  The possible values returned by this function are:
   * @li @link OperationReturnValues_t#LIBCOMBINE_OPERATION_SUCCESS LIBCOMBINE_OPERATION_SUCCESS @endlink
   * @li @link OperationReturnValues_t#LIBCOMBINE_OPERATION_FAILED LIBCOMBINE_OPERATION_FAILED @endlink
   * @li @link OperationReturnValues_t#LIBCOMBINE_INVALID_OBJECT LIBCOMBINE_INVALID_OBJECT @endlink
   *
   * @see removeTopLevelAnnotationElement(const std::string elementName, const std::string elementURI)
   * @see replaceTopLevelAnnotationElement(const XMLNode*)
   */
  int replaceTopLevelAnnotationElement(const std::string& annotation);


  /**
   * Sets the value of the "notes" subelement of this OMEX object.
   *
   * The content of @p notes is copied, and any existing content of this
   * object's "notes" subelement is deleted.
   *
   * The optional OMEX element named "notes", present on every major OMEX
   * component type, is intended as a place for storing optional
   * information intended to be seen by humans.  An example use of the
   * "notes" element would be to contain formatted user comments about the
   * model element in which the "notes" element is enclosed.  Every object
   * derived directly or indirectly from type CaBase can have a separate
   * value for "notes", allowing users considerable freedom when adding
   * comments to their models.
   *
   * The format of "notes" elements must be <a target="_blank"
   * href="http://www.w3.org/TR/xhtml1/">XHTML&nbsp;1.0</a>.  To help
   * verify the formatting of "notes" content, libCombine provides the static
   * utility method SyntaxChecker::hasExpectedXHTMLSyntax(@if java XMLNode xhtml@endif); however,
   * readers are urged to consult the appropriate <a target="_blank"
   * href="http://omex.org/Documents/Specifications">OMEX specification
   * document</a> for the Level and Version of their model for more
   * in-depth explanations.  The OMEX Level&nbsp;2 and &nbsp;3
   * specifications have considerable detail about how "notes" element
   * content must be structured.
   *
   * @param notes an XML structure that is to be used as the content of the
   * "notes" subelement of this object
   *
   * @return integer value indicating success/failure of the
   * function.  The possible values returned by this function are:
   * @li @link OperationReturnValues_t#LIBCOMBINE_OPERATION_SUCCESS LIBCOMBINE_OPERATION_SUCCESS @endlink
   * @li @link OperationReturnValues_t#LIBCOMBINE_INVALID_OBJECT LIBCOMBINE_INVALID_OBJECT @endlink
   *
   * @see getNotesString()
   * @see isSetNotes()
   * @see setNotes(const std::string& notes, bool addXHTMLMarkup)
   * @see appendNotes(const XMLNode* notes)
   * @see appendNotes(const std::string& notes)
   * @see unsetNotes()
   * @see SyntaxChecker::hasExpectedXHTMLSyntax(@if java XMLNode@endif)
   */
  int setNotes(const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode* notes);


  /**
   * Sets the value of the "notes" subelement of this OMEX object to a copy
   * of the string @p notes.
   *
   * The content of @p notes is copied, and any existing content of this
   * object's "notes" subelement is deleted.
   *
   * The optional OMEX element named "notes", present on every major OMEX
   * component type, is intended as a place for storing optional
   * information intended to be seen by humans.  An example use of the
   * "notes" element would be to contain formatted user comments about the
   * model element in which the "notes" element is enclosed.  Every object
   * derived directly or indirectly from type CaBase can have a separate
   * value for "notes", allowing users considerable freedom when adding
   * comments to their models.
   *
   * The format of "notes" elements must be <a target="_blank"
   * href="http://www.w3.org/TR/xhtml1/">XHTML&nbsp;1.0</a>.  To help
   * verify the formatting of "notes" content, libCombine provides the static
   * utility method SyntaxChecker::hasExpectedXHTMLSyntax(@if java XMLNode@endif); however,
   * readers are urged to consult the appropriate <a target="_blank"
   * href="http://omex.org/Documents/Specifications">OMEX specification
   * document</a> for the Level and Version of their model for more
   * in-depth explanations.  The OMEX Level&nbsp;2 and &nbsp;3
   * specifications have considerable detail about how "notes" element
   * content must be structured.
   *
   * @param notes an XML string that is to be used as the content of the
   * "notes" subelement of this object
   *
   * @param addXHTMLMarkup a boolean indicating whether to wrap the contents
   * of the @p notes argument with XHTML paragraph (<code>&lt;p&gt;</code>)
   * tags.  This is appropriate when the string in @p notes does not already
   * containg the appropriate XHTML markup.
   *
   * @return integer value indicating success/failure of the
   * function.  The possible values returned by this function are:
   * @li @link OperationReturnValues_t#LIBCOMBINE_OPERATION_SUCCESS LIBCOMBINE_OPERATION_SUCCESS @endlink
   * @li @link OperationReturnValues_t#LIBCOMBINE_INVALID_OBJECT LIBCOMBINE_INVALID_OBJECT @endlink
   * @li @link OperationReturnValues_t#LIBCOMBINE_OPERATION_FAILED LIBCOMBINE_OPERATION_FAILED @endlink
   *
   * @see getNotesString()
   * @see isSetNotes()
   * @see setNotes(const XMLNode* notes)
   * @see appendNotes(const XMLNode* notes)
   * @see appendNotes(const std::string& notes)
   * @see unsetNotes()
   * @see SyntaxChecker::hasExpectedXHTMLSyntax(@if java XMLNode@endif)
   */
  int setNotes(const std::string& notes, bool addXHTMLMarkup = false);


  /**
   * Appends the given @p notes to the "notes" subelement of this object.
   *
   * The content of @p notes is copied.
   *
   * The optional OMEX element named "notes", present on every major OMEX
   * component type, is intended as a place for storing optional
   * information intended to be seen by humans.  An example use of the
   * "notes" element would be to contain formatted user comments about the
   * model element in which the "notes" element is enclosed.  Every object
   * derived directly or indirectly from type CaBase can have a separate
   * value for "notes", allowing users considerable freedom when adding
   * comments to their models.
   *
   * The format of "notes" elements must be <a target="_blank"
   * href="http://www.w3.org/TR/xhtml1/">XHTML&nbsp;1.0</a>.  To help
   * verify the formatting of "notes" content, libCombine provides the static
   * utility method SyntaxChecker::hasExpectedXHTMLSyntax(@if java XMLNode@endif); however,
   * readers are urged to consult the appropriate <a target="_blank"
   * href="http://omex.org/Documents/Specifications">OMEX specification
   * document</a> for the Level and Version of their model for more
   * in-depth explanations.  The OMEX Level&nbsp;2 and &nbsp;3
   * specifications have considerable detail about how "notes" element
   * content must be structured.
   * 
   * @param notes an XML node structure that is to appended to the content
   * of the "notes" subelement of this object
   *
   * @return integer value indicating success/failure of the
   * function.  The possible values returned by this function are:
   * @li @link OperationReturnValues_t#LIBCOMBINE_OPERATION_SUCCESS LIBCOMBINE_OPERATION_SUCCESS @endlink
   * @li @link OperationReturnValues_t#LIBCOMBINE_INVALID_OBJECT LIBCOMBINE_INVALID_OBJECT @endlink
   * @li @link OperationReturnValues_t#LIBCOMBINE_OPERATION_FAILED LIBCOMBINE_OPERATION_FAILED @endlink
   *
   * @see getNotesString()
   * @see isSetNotes()
   * @see setNotes(const XMLNode* notes)
   * @see setNotes(const std::string& notes, bool addXHTMLMarkup)
   * @see appendNotes(const std::string& notes)
   * @see unsetNotes()
   * @see SyntaxChecker::hasExpectedXHTMLSyntax(@if java XMLNode@endif)
   */
  int appendNotes(const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode* notes);


  /**
   * Appends the given @p notes to the "notes" subelement of this object.
   *
   * The content of the parameter @p notes is copied.
   *
   * The optional OMEX element named "notes", present on every major OMEX
   * component type, is intended as a place for storing optional
   * information intended to be seen by humans.  An example use of the
   * "notes" element would be to contain formatted user comments about the
   * model element in which the "notes" element is enclosed.  Every object
   * derived directly or indirectly from type CaBase can have a separate
   * value for "notes", allowing users considerable freedom when adding
   * comments to their models.
   *
   * The format of "notes" elements must be <a target="_blank"
   * href="http://www.w3.org/TR/xhtml1/">XHTML&nbsp;1.0</a>.  To help
   * verify the formatting of "notes" content, libCombine provides the static
   * utility method SyntaxChecker::hasExpectedXHTMLSyntax(@if java XMLNode@endif); however,
   * readers are urged to consult the appropriate <a target="_blank"
   * href="http://omex.org/Documents/Specifications">OMEX specification
   * document</a> for the Level and Version of their model for more
   * in-depth explanations.  The OMEX Level&nbsp;2 and &nbsp;3
   * specifications have considerable detail about how "notes" element
   * content must be structured.
   *
   * @param notes an XML string that is to appended to the content of
   * the "notes" subelement of this object
   *
   * @return integer value indicating success/failure of the
   * function.  The possible values returned by this function are:
   * @li @link OperationReturnValues_t#LIBCOMBINE_OPERATION_SUCCESS LIBCOMBINE_OPERATION_SUCCESS @endlink
   * @li @link OperationReturnValues_t#LIBCOMBINE_INVALID_OBJECT LIBCOMBINE_INVALID_OBJECT @endlink
   * @li @link OperationReturnValues_t#LIBCOMBINE_OPERATION_FAILED LIBCOMBINE_OPERATION_FAILED @endlink
   *
   * @see getNotesString()
   * @see isSetNotes()
   * @see setNotes(const XMLNode* notes)
   * @see setNotes(const std::string& notes, bool addXHTMLMarkup)
   * @see appendNotes(const XMLNode* notes)
   * @see unsetNotes()
   * @see SyntaxChecker::hasExpectedXHTMLSyntax(@if java XMLNode@endif)
   */
  int appendNotes(const std::string& notes);


  /** @cond doxygenLibomexInternal */
  /**
   * Sets the parent CaOmexManifest of this OMEX object.
   *
   * @param d the CaOmexManifest object to use
   *
   * @see connectToChild()
   * @if clike
   * @see enablePackageInternal()
   * @endif@~
   */
  virtual void setCaOmexManifest (CaOmexManifest* d);
  /** @endcond */


  /** @cond doxygenLibomexInternal */
  /**
   * Sets the parent OMEX object of this OMEX object.
   * (Creates a child-parent relationship by the child)
   * This function is called when a child element is
   * set/added/created by its parent element (e.g. by setXXX,
   * addXXX, createXXX, and connectToChild functions of the
   * parent element).
   *
   * @param parent the OMEX object to use
   */
  virtual void connectToParent (CaBase* parent);


  /**
   * Sets this OMEX object to child OMEX objects (if any).
   * (Creates a child-parent relationship by the parent)
   *
   * Subclasses must override this function if they define
   * one ore more child elements.
   * Basically, this function needs to be called in
   * constructor, copy constructor, assignment operator.
   *
   * @if clike
   * @see setCaOmexManifest()
   * @see enablePackageInternal()
   * @endif@~
   */
  virtual void connectToChild ();

  /** @endcond */


  /**
   * Sets the namespaces relevant of this OMEX object.
   *
   * The content of @p xmlns is copied, and this object's existing
   * namespace content is deleted.
   *
   * The CaNamespaces object encapsulates OMEX Level/Version/namespaces
   * information.  It is used to communicate the OMEX Level, Version, and
   * (in Level&nbsp;3) packages used in addition to OMEX Level&nbsp;3 Core.
   * 
   * @param xmlns the namespaces to set
   *
   * @copydetails doc_returns_success_code
   * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
   */
  int setNamespaces(LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces* xmlns);


  /**
   * Unsets the value of the "metaid" attribute of this OMEX object.
   *
   */
  int unsetMetaId ();


  /**
   * Unsets the value of the "id" attribute of this OMEX object.
   *
   * @copydetails doc_unset_id
   */
  virtual int unsetId ();


  /**
   * Unsets the value of the "notes" subelement of this OMEX object.
   *
   * The optional OMEX element named "notes", present on every major OMEX
   * component type, is intended as a place for storing optional
   * information intended to be seen by humans.  An example use of the
   * "notes" element would be to contain formatted user comments about the
   * model element in which the "notes" element is enclosed.  Every object
   * derived directly or indirectly from type CaBase can have a separate
   * value for "notes", allowing users considerable freedom when adding
   * comments to their models.
   *
   * The format of "notes" elements must be <a target="_blank"
   * href="http://www.w3.org/TR/xhtml1/">XHTML&nbsp;1.0</a>.  To help
   * verify the formatting of "notes" content, libCombine provides the static
   * utility method SyntaxChecker::hasExpectedXHTMLSyntax(@if java XMLNode@endif); however,
   * readers are urged to consult the appropriate <a target="_blank"
   * href="http://omex.org/Documents/Specifications">OMEX specification
   * document</a> for the Level and Version of their model for more
   * in-depth explanations.  The OMEX Level&nbsp;2 and &nbsp;3
   * specifications have considerable detail about how "notes" element
   * content must be structured.
   *
   * @return integer value indicating success/failure of the
   * function.  The possible values returned by this function are:
   * @li @link OperationReturnValues_t#LIBCOMBINE_OPERATION_SUCCESS LIBCOMBINE_OPERATION_SUCCESS @endlink
   *
   * @see getNotesString()
   * @see isSetNotes()
   * @see setNotes(const XMLNode* notes)
   * @see setNotes(const std::string& notes, bool addXHTMLMarkup)
   * @see appendNotes(const XMLNode* notes)
   * @see appendNotes(const std::string& notes)
   * @see SyntaxChecker::hasExpectedXHTMLSyntax(@if java XMLNode@endif)
   */
  int unsetNotes ();


  /**
   * Unsets the value of the "annotation" subelement of this OMEX object.
   *
   * Whereas the CaBase "notes" subelement is a container for content to be
   * shown directly to humans, the "annotation" element is a container for
   * optional software-generated content @em not meant to be shown to
   * humans.  Every object derived from CaBase can have its own value for
   * "annotation".  The element's content type is <a target="_blank"
   * href="http://www.w3.org/TR/2004/REC-xml-20040204/#elemdecls">XML type
   * "any"</a>, allowing essentially arbitrary well-formed XML data
   * content.
   *
   * OMEX places a few restrictions on the organization of the content of
   * annotations; these are intended to help software tools read and write
   * the data as well as help reduce conflicts between annotations added by
   * different tools.  Please see the OMEX specifications for more details.
   *
   * @return integer value indicating success/failure of the
   * function.  The possible values returned by this function are:
   * @li @link OperationReturnValues_t#LIBCOMBINE_OPERATION_SUCCESS LIBCOMBINE_OPERATION_SUCCESS @endlink
   *
   * @see getAnnotation()
   * @see getAnnotationString()
   * @see isSetAnnotation()
   * @see setAnnotation(const XMLNode* annotation)
   * @see setAnnotation(const std::string& annotation)
   * @see appendAnnotation(const XMLNode* annotation)
   * @see appendAnnotation(const std::string& annotation)
   */
  int unsetAnnotation ();


  /**
   * Returns the OMEX Level of the CaOmexManifest object containing @em this
   * object.
   * 
   * @return the OMEX level of this OMEX object.
   * 
   * @see getVersion()
   * @see getNamespaces()
   * @see getPackageVersion()
   */
  unsigned int getLevel () const;


  /**
   * Returns the Version within the OMEX Level of the CaOmexManifest object
   * containing @em this object.
   * 
   * @return the OMEX version of this OMEX object.
   *
   * @see getLevel()
   * @see getNamespaces()
   */
  unsigned int getVersion () const;


  /**
   * Returns the libCombine type code for this object.
   *
   * @copydetails doc_what_are_typecodes
   *
   * @copydetails doc_additional_typecode_details
   *
   * @return the @if clike #CaTypeCode_t value@else OMEX object type
   * code@endif@~ of this OMEX object, or @omexconstant{OMEX_UNKNOWN,
   * CaTypeCode_t} (the default).  The latter is possible because
   * subclasses of CaBase are not required to implement this method to return
   * a type code.
   *
   * @copydetails doc_warning_typecodes_not_unique
   *
   * @see getPackageName()
   * @see getElementName()
   */
  virtual int getTypeCode () const;


  /**
   * Predicate returning @c true if this object's level/version and namespace
   * values correspond to a valid OMEX specification.
   *
   * @return @c true if the level, version and namespace values of this 
   * OMEX object correspond to a valid set of values, @c false otherwise.
   */
  bool hasValidLevelVersionNamespaceCombination();

  
  /**
   * Returns the XML element name of this object.
   *
   * This is overridden by subclasses to return a string appropriate to the
   * OMEX component.  For example, Model defines it as returning @c
   * "model", CompartmentType defines it as returning @c "compartmentType",
   * and so on.
   */
  virtual const std::string& getElementName () const = 0;


  /**
   * Returns a string consisting of a partial OMEX corresponding to just
   * this object.
   * 
   * @return the partial OMEX that describes this OMEX object.
   *
   * @warning <span class="warning">This is primarily provided for testing
   * and debugging purposes.  It may be removed in a future version of
   * libCombine.</span>
   */
  char* toCa();


  // ------------------------------------------------------------------

  #ifndef SWIG
   /** @cond doxygenLibomexInternal */


   virtual int getAttribute(const std::string& attributeName, double& value) const;

  /** @endcond */

  /** @cond doxygenLibomexInternal */

   virtual int getAttribute(const std::string& attributeName, bool& value) const;

  /** @endcond */

  /** @cond doxygenLibomexInternal */

   virtual int getAttribute(const std::string& attributeName, int& value) const;

  /** @endcond */

  /** @cond doxygenLibomexInternal */

   virtual int getAttribute(const std::string& attributeName, unsigned int& value) const;

  /** @endcond */

  /** @cond doxygenLibomexInternal */

   virtual int getAttribute(const std::string& attributeName, std::string& value) const;

  /** @endcond */

//   virtual int getAttribute(const std::string& attributeName, const char * value) const;


   virtual bool isSetAttribute(const std::string& attributeName) const;

  /** @endcond */

  /** @cond doxygenLibomexInternal */

   virtual int setAttribute(const std::string& attributeName, double value);

  /** @endcond */

  /** @cond doxygenLibomexInternal */

   virtual int setAttribute(const std::string& attributeName, bool value);

  /** @endcond */

  /** @cond doxygenLibomexInternal */

   virtual int setAttribute(const std::string& attributeName, int value);

  /** @endcond */

  /** @cond doxygenLibomexInternal */

   virtual int setAttribute(const std::string& attributeName, unsigned int value);

  /** @endcond */

  /** @cond doxygenLibomexInternal */

   virtual int setAttribute(const std::string& attributeName, const std::string& value);

  /** @endcond */

  /** @cond doxygenLibomexInternal */

//   virtual int setAttribute(const std::string& attributeName, const char* value);

  /** @endcond */

  /** @cond doxygenLibomexInternal */

   virtual int unsetAttribute(const std::string& attributeName);

  /** @endcond */

  /** @cond doxygenLibomexInternal */

   virtual CaBase* createChildObject(const std::string& elementName);

  /** @endcond */

  /** @cond doxygenLibomexInternal */

   virtual int addChildObject(const std::string& elementName, const CaBase* element);

   /** @endcond */

   /** @cond doxygenLibomexInternal */

   virtual CaBase* removeChildObject(const std::string& elementName, const std::string& id);

   /** @endcond */

   /** @cond doxygenLibomexInternal */

   virtual unsigned int getNumObjects(const std::string& objectName);

  /** @endcond */

  /** @cond doxygenLibomexInternal */

   virtual CaBase* getObject(const std::string& objectName, unsigned int index);

  /** @endcond */

  /** @cond doxygenLibomexInternal */

  template<typename T> T getAttribute(const std::string& attributeName)
  {
    T result;
    getAttribute(attributeName, result);
    return result;
  }
  /** @endcond */

#endif /* SWIG */



  /** @cond doxygenLibomexInternal */
  /**
   * Reads (initializes) this OMEX object by reading from XMLInputStream.
   */
  void read (LIBSBML_CPP_NAMESPACE_QUALIFIER XMLInputStream& stream);
  /** @endcond */


  /** @cond doxygenLibomexInternal */
  /**
   * Writes (serializes) this OMEX object by writing it to XMLOutputStream.
   */
  virtual void write (LIBSBML_CPP_NAMESPACE_QUALIFIER XMLOutputStream& stream) const;
  /** @endcond */


  /** @cond doxygenLibomexInternal */
  /**
   * Subclasses should override this method to write out their contained
   * OMEX objects as XML elements.  Be sure to call your parents
   * implementation of this method as well.  For example:@if clike
   * <pre>
   *   CaBase::writeElements();
   *   mReactants.write(stream);
   *   mProducts.write(stream);
   *   ...
   * </pre>@endif@~
   */
  virtual void writeElements (LIBSBML_CPP_NAMESPACE_QUALIFIER XMLOutputStream& stream) const;
  /** @endcond */


  /** @cond doxygenLibomexInternal */
  /* function returns true if component has all the required
   * attributes
   * needs to be overloaded for each component
   */
  virtual bool hasRequiredAttributes() const ;
  /** @endcond */


  /** @cond doxygenLibomexInternal */
  /* function returns true if component has all the required
   * elements
   * needs to be overloaded for each component
   */
  virtual bool hasRequiredElements() const ;
  /** @endcond */


  /** @cond doxygenLibomexInternal */
  /* function returns value if the object matches level/version/namespace
   */
  int checkCompatibility(const CaBase * object) const ;
  /** @endcond */


  /** @cond doxygenLibomexInternal */
  /* sets the Canamespaces - internal use only*/
  int setCaNamespaces(CaNamespaces * omexns);

  /* sets the CaNamaepaces and owns the given object - internal use only */
  void setCaNamespacesAndOwn(CaNamespaces * disownedNs);
  /** @endcond */


  /** @cond doxygenLibomexInternal */
  /* gets the Canamespaces - internal use only*/
  virtual CaNamespaces * getCaNamespaces() const;
  /** @endcond */


  /**
   * Removes this object from its parent.
   *
   * If the parent was storing this object as a pointer, it is deleted.  If
   * not, it is simply cleared (as in CaListOf objects).  This is a pure
   * virtual method, as every CaBase element has different parents, and
   * therefore different methods of removing itself.  Will fail (and not
   * delete itself) if it has no parent object.  This function is designed to
   * be overridden, but for all objects whose parent is of the class CaListOf,
   * the default implementation will work.
   *
   * @copydetails doc_returns_success_code
   * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
   * @li @omexconstant{LIBCOMBINE_OPERATION_FAILED, OperationReturnValues_t}
   */
  virtual int removeFromParentAndDelete();


  /**
   * Returns @c true if this object's set of XML namespaces are the same
   * as the given object's XML namespaces.
   *
   * @param sb an object to compare with respect to namespaces
   *
   * @return boolean, @c true if this object's collection of namespaces is
   * the same as @p sb's, @c false otherwise.
   */
  bool matchesCaNamespaces(const CaBase * sb);


  /**
   * Returns @c true if this object's set of XML namespaces are the same
   * as the given object's XML namespaces.
   *
   * @param sb an object to compare with respect to namespaces
   *
   * @return boolean, @c true if this object's collection of namespaces is
   * the same as @p sb's, @c false otherwise.
   */
  bool matchesCaNamespaces(const CaBase * sb) const;


  /**
   * Returns @c true if this object's set of XML namespaces are a subset
   * of the given object's XML namespaces.
   *
   * @param sb an object to compare with respect to namespaces
   *
   * @return boolean, @c true if this object's collection of namespaces is
   * a subset of @p sb's, @c false otherwise.
   */
  bool matchesRequiredCaNamespacesForAddition(const CaBase * sb);
  
  
  /**
   * Returns @c true if this object's set of XML namespaces are a subset
   * of the given object's XML namespaces.
   *
   * @param sb an object to compare with respect to namespaces
   *
   * @return boolean, @c true if this object's collection of namespaces is
   * a subset of @p sb's, @c false otherwise.
   */
  bool matchesRequiredCaNamespacesForAddition(const CaBase * sb) const;


  /**
   * Sets the user data of this element.
   *
   * @copydetails doc_what_is_user_data
   *
   * @param userData specifies the new user data.
   *
   * @copydetails doc_returns_success_code
   * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
   * @li @omexconstant{LIBCOMBINE_OPERATION_FAILED, OperationReturnValues_t}
   */
  int setUserData(void *userData);


  /**
   * Returns the user data that has been previously set via setUserData().
   *
   * @copydetails doc_what_is_user_data
   *
   * @return the user data of this node, or @c NULL if no user data has been set.
   *
   * @if clike
   * @see ASTNode::setUserData(void *userData)
   * @endif@~
   */
  void *getUserData() const;

  /**
   * Predicate returning true or false depending on whether
   * the user data of this element has been set.
   *
   * @copydetails doc_what_is_user_data
   *
   * @return boolean, @c true if this object's user data has been set,
   * @c false otherwise.
   */
  bool isSetUserData() const;


  /**
   * Unsets the user data of this element.
   *
   * @copydetails doc_what_is_user_data
   *
   * @copydetails doc_returns_success_code
   * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
   * @li @omexconstant{LIBCOMBINE_OPERATION_FAILED, OperationReturnValues_t}
   */
  int unsetUserData();


  /**
   * Returns the CaErrorLog used to log errors while reading and
   * validating OMEX.
   *
   * @return the CaErrorLog used to log errors while reading and
   * validating OMEX.
   */
  CaErrorLog* getErrorLog ();

protected:

  bool getHasBeenDeleted() const;

  /** 
   * When overridden allows CaBase elements to use the text included in between
   * the elements tags. The default implementation does nothing.
   * 
   * @param text the text string found between the element tags.
   */ 
  virtual void setElementText(const std::string &text);


  /** @cond doxygenLibomexInternal */

  bool matchesCoreCaNamespace(const CaBase * sb);

  bool matchesCoreCaNamespace(const CaBase * sb) const;

  /**
   * Creates a new CaBase object with the given OMEX level, version.
   */
  CaBase (unsigned int level, unsigned int version);


  /**
   * Creates a new CaBase object with the given CaNamespaces.
   * Only subclasses may create CaBase objects.
   */
  CaBase (CaNamespaces* omexns);


  /**
  * Copy constructor. Creates a copy of this CaBase object.
   *
   * @param orig the object to copy.
  */
  CaBase(const CaBase& orig);


  /**
   * Subclasses should override this method to create, store, and then
   * return an OMEX object corresponding to the next XMLToken in the
   * XMLInputStream.
   *
   * @return the OMEX object corresponding to next XMLToken in the
   * XMLInputStream or @c NULL if the token was not recognized.
   */
  virtual CaBase* createObject (LIBSBML_CPP_NAMESPACE_QUALIFIER XMLInputStream& stream);


  /**
   * Predicate returning @c true if this
   * object's level/version and namespace values correspond to a valid
   * OMEX specification.
   *
   * @param typecode the typecode for this element
   * @param xmlns the namespaces used by this element.
   *
   * @note  This function is provided as convenience method to be called from constructors. This 
   *        allows to use it in scenarios where the namespaces or typecode have not yet been initialized. 
   * 
   * @return @c true if the level, version and namespace values of this 
   * OMEX object correspond to a valid set of values, @c false otherwise.
   */
  bool hasValidLevelVersionNamespaceCombination(int typecode, LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces *xmlns);


  /**
   * Subclasses should override this method to read (and store) XHTML,
   * MathML, etc. directly from the XMLInputStream.
   *
   * @return true if the subclass read from the stream, false otherwise.
   */
  virtual bool readOtherXML (LIBSBML_CPP_NAMESPACE_QUALIFIER XMLInputStream& stream);


  /**
   * The OMEX XML Schema is written such that the order of child elements
   * is significant.  LibCombine can read elements out of order.  If you
   * override this method to indicate the ordinal position of element with
   * respect to its siblings, libCombine will log an error if the element is
   * read out of order.
   *
   * @return the ordinal position of the element with respect to its
   * siblings or @c -1 (the default) to indicate the position is not
   * significant.
   */
  virtual int getElementPosition () const;


  /**
   * Convenience method for easily logging problems from within method
   * implementations.
   *
   * This is essentially a short form of getErrorLog()->logError(...)
   *
   * @ifnot hasDefaultArgs @htmlinclude warn-default-args-in-docs.html @endif@~
   */
  void logError (  unsigned int       id
                 , const unsigned int level   = 2
                 , const unsigned int version = 3
                 , const std::string& details = "" );


  /**
   * Helper to log a common type of error.
   */
  void logUnknownAttribute( const std::string& attribute,
          const unsigned int level,
          const unsigned int version,
          const std::string& element,
          const std::string& prefix="");


  /**
   * Helper to log a common type of error.
   */
  void logUnknownElement( const std::string& element,
        const unsigned int level,
        const unsigned int version );

 
  /**
   * Helper to log a common type of error.
   */
  void logEmptyString( const std::string& attribute,
                       const unsigned int level,
                       const unsigned int version,
                       const std::string& element);


  /**
   * Subclasses should override this method to add the list of
   * expected attributes. Be sure to call your parents implementation 
   * of this method as well.
   */
  virtual void addExpectedAttributes(ExpectedAttributes& attributes);

  /**
   * Subclasses should override this method to read values from the given
   * XMLAttributes set into their specific fields.  Be sure to call your
   * parents implementation of this method as well.
   */
  virtual void readAttributes (const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLAttributes& attributes, 
                               const LIBSBML_CPP_NAMESPACE_QUALIFIER ExpectedAttributes& expectedAttributes);


  /**
   * Subclasses should override this method to write their XML attributes
   * to the XMLOutputStream.  Be sure to call your parents implementation
   * of this method as well.  For example:
   *
   *   CaBase::writeAttributes(stream);
   *   stream.writeAttribute( "id"  , mId   );
   *   stream.writeAttribute( "name", mName );
   *   ...
   *
   * (NOTICE) this function doesn't write xmlns attributes.
   * Be sure to implement wirteXMLNS() function to write xmlns attributes.
   *
   */
  virtual void writeAttributes (LIBSBML_CPP_NAMESPACE_QUALIFIER XMLOutputStream& stream) const;


  /**
   *
   * Subclasses should override this method to write their xmlns attriubutes
   * (if any) to the XMLOutputStream. 
   *
   */
  virtual void writeXMLNS (LIBSBML_CPP_NAMESPACE_QUALIFIER XMLOutputStream& stream) const;


  /**
   * Checks that an OMEX CaListOf element is populated.  
   * If a listOf element has been declared with no elements, 
   * an error is logged.
   */
  void checkCaListOfPopulated(CaBase* object);

  /**
   * Checks that the given default namespace in the given element is valid.
   * If the given default namespace is not valid, an error is logged.
   */
  void checkDefaultNamespace(const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces* xmlns, 
    const std::string& elementName, const std::string& prefix = "");

  /**
   * Checks the annotation does not declare an omex namespace.
   * If the annotation declares an omex namespace an error is logged.
   */
  void checkAnnotation();


  /**
   * Checks that the XHTML is valid.
   * If the xhtml does not conform to the specification of valid xhtml within
   * an omex document, an error is logged.
   */
  void checkXHTML(const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode *);


  /**
   * Checks that the math ml ns has been declared
   */
  const std::string checkMathMLNamespace(const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLToken elem);

   /**
   * Sets the XML namespace to which this element belongs to.
   * For example, all elements that belong to OMEX Level 3 Version 1 Core
   * must set the namespace to <code>"http://www.omex.org/omex/level3/version1/core"</code>; 
   * all elements that belong to Layout Extension Version 1 for OMEX Level 3
   * Version 1 Core must set the namespace to 
   * <code>"http://www.omex.org/omex/level3/version1/layout/version1"</code>.
   *
   * @copydetails doc_returns_success_code
   * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
   * @li @omexconstant{LIBCOMBINE_INVALID_ATTRIBUTE_VALUE, OperationReturnValues_t}
   */
  int setElementNamespace(const std::string &uri);


  /**
   * Gets the XML namespace (URI) to which this element belongs to.
   */
  const std::string& getElementNamespace() const;

  std::string getURI() const;

  std::string getPrefix() const;

  /**
   * Return the OMEX XML namespace prefix of this element.
   *
   * This will be the same as getPrefix() unless the element in question is
   * an element of an OMEX extension class.
   *
   * @return the XML namespace prefix
   */
  std::string getCaPrefix() const;


  /**
   * Returns the root element of the node tree to which this element is connected.
   *
   * @note The root element may not be an CaOmexManifest element. For example,
   * this element is the root element if this element doesn't have a parent
   * OMEX object (i.e. mParentCaObject is NULL)
   *
   * @see enablePackageInternal
   */
  CaBase* getRootElement();


  // ------------------------------------------------------------------


  std::string     mMetaId;
  std::string     mId;
  LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode*        mNotes;
  LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode*        mAnnotation;
  CaOmexManifest*   mCa;
  CaNamespaces* mCaNamespaces;
  void*           mUserData;

  unsigned int mLine;
  unsigned int mColumn;

  /* store the parent OMEX object */
  CaBase* mParentCaObject;
  bool mHasBeenDeleted;

  std::string mEmptyString;

  //
  // namespace to which this CaBase object belongs.
  // This variable can be publicly accessible by getElementNamespace function.
  //
  // For example, mURI of elements defined in L3 Core (or defined in Level 2 
  // or before) will be the URI defined in the corresponding OMEX specification
  // (e.g. "http://www.omex.org/omex/level3/version1" for L3V1 Core); and mURI
  // will be "http://www.omex.org/omex/level3/version1/layout/version1" for 
  // elements defined in layout extension L3V1-V1.
  // The purpuse of this data member is to explicitly distinguish elements in core 
  // package and extension packages.
  // 
  // From the implementation point of view, this variable is needed to identify
  // if the prefix needs to be added when printing elements in some package extension.
  // (i.e. used in getPrefix function)
  //
  std::string mURI;

  
  /** @endcond */

private:
  /** @cond doxygenLibomexInternal */
  /**
   * Stores the location (line and column) and any XML namespaces (for
   * roundtripping) declared on this OMEX (XML) element.
   */
  void setCaBaseFields (const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLToken& element);


  /**
   * Reads an annotation from the stream and returns true if successful.
   *
   * @return true if read an <annotation> element from the stream
   */
  bool readAnnotation (LIBSBML_CPP_NAMESPACE_QUALIFIER XMLInputStream& stream);


  /**
   * Reads the notes from the stream and returns true if successful.
   *
   * @return true if read a <notes> element from the stream
   */
  bool readNotes (LIBSBML_CPP_NAMESPACE_QUALIFIER XMLInputStream& stream);


  /** @endcond */
};

LIBCOMBINE_CPP_NAMESPACE_END

#endif  /* __cplusplus */



#ifndef SWIG

LIBCOMBINE_CPP_NAMESPACE_BEGIN
BEGIN_C_DECLS

/**
 * Returns the value of the "metaid" attribute of the given CaBase_t
 * structure.
 *
 * @param sb the CaBase_t structure
 *
 * @return the value of the "metaid" attribute of @p sb
 *
 * @memberof CaBase_t
 */
LIBCOMBINE_EXTERN
const char *
CaBase_getMetaId (CaBase_t *sb);


/**
 * Returns the parent CaOmexManifest_t structure of the given CaBase_t
 * structure.
 *
 * @param sb the CaBase_t structure
 *
 * @return the parent CaOmexManifest of this OMEX structure.
 *
 * @memberof CaBase_t
 */
LIBCOMBINE_EXTERN
const CaOmexManifest_t *
CaBase_getCaOmexManifest (CaBase_t *sb);


/**
 * Returns the parent CaBase_t structure of the given CaBase_t
 * structure.
 *
 * @param sb the CaBase_t structure
 *
 * @return the parent CaBase  of this OMEX structure.
 *
 * @memberof CaBase_t
 */
LIBCOMBINE_EXTERN
const CaBase_t *
CaBase_getParentCaObject (CaBase_t *sb);


/**
 * Returns the ancestor CaBase_t structure of the given CaBase_t
 * structure that corresponds to the given type.
 *
 * This function allows any structure to determine its exact
 * location/function within a model. For example a
 * StoichiometryMath_t structure has ancestors of type SpeciesReference_t,
 * CaListOf_t(Products/Reactants), Reaction_t, CaListOfReactions_t and Model_t;
 * any of which can be accessed via this function.
 *
 * @param sb the CaBase_t structure
 * @param type the typecode (int) of the structure to be returned
 *
 * @return the ancestor CaBase_t structure of this OMEX structure with
 * the corresponding typecode (int), NULL if there is no ancestor of
 * this type.
 *
 * @memberof CaBase_t
 */
LIBCOMBINE_EXTERN
const CaBase_t *
CaBase_getAncestorOfType (CaBase_t *sb, int type);

/**
 * Returns the line number on which the given structure first appears in the
 * XML representation of the OMEX document, or '0' if the object was created,
 * not read from a file.
 *
 * @param sb the CaBase_t structure
 *
 * @return the line number of the given structure, or '0' if no such value.
 *
 * @see getColumn().
 *
 * @memberof CaBase_t
 */
LIBCOMBINE_EXTERN
unsigned int
CaBase_getLine (const CaBase_t *sb);


/**
 * Returns the column number on which the given structure first appears in the
 * XML representation of the OMEX document, or '0' if the object was created,
 * not read from a file.
 *
 * @param sb the CaBase_t structure
 *
 * @return the column number of this OMEX structure, or '0' if no such value.
 *
 * @see getLine().
 *
 * @memberof CaBase_t
 */
LIBCOMBINE_EXTERN
unsigned int
CaBase_getColumn (const CaBase_t *sb);


/**
 * Returns the notes from given OMEX structure.
 *
 * @param sb the given OMEX structure.
 *
 * @return the XMLNode_t structure representing the notes from this structure.
 *
 * @memberof CaBase_t
 */
LIBCOMBINE_EXTERN
XMLNode_t *
CaBase_getNotes (CaBase_t *sb);


/**
 * Returns the notes string from given OMEX structure.
 * The string is owned by the caller and should be freed
 * (with free()) when no longer needed.
 *
 * @param sb the given OMEX structure.
 *
 * @return the string (char*) representing the notes from this structure.
 *
 * @memberof CaBase_t
 */
LIBCOMBINE_EXTERN
char*
CaBase_getNotesString (CaBase_t *sb);


/**
 * Returns the annotation from given OMEX structure.
 *
 * @param sb the given OMEX structure.
 *
 * @return the XMLNode_t structure representing the annotation from this structure.
 *
 * @memberof CaBase_t
 */
LIBCOMBINE_EXTERN
XMLNode_t *
CaBase_getAnnotation (CaBase_t *sb);


/**
 * Returns the annotation string from given OMEX structure.
 * The string is owned by the caller and should be freed
 * (with free()) when no longer needed.
 *
 * @param sb the given OMEX structure.
 *
 * @return the string (char*) representing the annotation from this structure.
 *
 * @memberof CaBase_t
 */
LIBCOMBINE_EXTERN
char*
CaBase_getAnnotationString (CaBase_t *sb);


/**
 * Predicate returning nonzero true or false depending on whether the given
 * structure's "metaid" attribute is set.
 *
 * @param sb the CaBase_t structure to query
 *
 * @return nonzero (for true) if the "metaid" attribute of this OMEX structure
 * is set, zero (for false) otherwise.
 *
 * @memberof CaBase_t
 */
LIBCOMBINE_EXTERN
int
CaBase_isSetMetaId (const CaBase_t *sb);


/**
 * Predicate returning nonzero true or false depending on whether the given
 * structure's "notes" subelement is set.
 *
 * @param sb the CaBase_t structure to query
 *
 * @return nonzero (for true) if the "notes" subelement of this OMEX structure
 * is set, zero (for false) otherwise.
 *
 * @memberof CaBase_t
 */
LIBCOMBINE_EXTERN
int
CaBase_isSetNotes (const CaBase_t *sb);


/**
 * Predicate returning nonzero true or false depending on whether the given
 * structure's "annotation" subelement is set.
 *
 * @param sb the CaBase_t structure to query
 *
 * @return nonzero (for true) if the "annotation" subelement of this OMEX structure
 * is set, zero (for false) otherwise.
 *
 * @memberof CaBase_t
 */
LIBCOMBINE_EXTERN
int
CaBase_isSetAnnotation (const CaBase_t *sb);


/**
 * Sets the value of the "metaid" attribute of the given structure.
 *
 * The string @p metaid is copied.  The value of @p metaid must be an
 * identifier conforming to the syntax defined by the XML 1.0 data type
 * ID.  Among other things, this type requires that a value is unique
 * among all the values of type XML ID in an CaOmexManifest_t.  Although OMEX
 * only uses XML ID for the "metaid" attribute, callers should be careful
 * if they use XML ID's in XML portions of a model that are not defined
 * by OMEX, such as in the application-specific content of the
 * "annotation" subelement.
 *
 * @param sb the CaBase_t structure
 *
 * @param metaid the identifier string to use as the value of the
 * "metaid" attribute
 *
 * @copydetails doc_returns_success_code
 * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
 * @li @omexconstant{LIBCOMBINE_INVALID_ATTRIBUTE_VALUE, OperationReturnValues_t}
 * @li @omexconstant{LIBCOMBINE_UNEXPECTED_ATTRIBUTE, OperationReturnValues_t}
 *
 * @note Using this function with the metaid set to NULL is equivalent to
 * unsetting the "metaid" attribute.
 *
 * @memberof CaBase_t
 */
LIBCOMBINE_EXTERN
int
CaBase_setMetaId (CaBase_t *sb, const char *metaid);


/**
 * Sets the namespaces relevant of this OMEX structure.
 *
 * @param sb the CaBase_t structure
 *
 * @param xmlns the namespaces to set
 *
 * @copydetails doc_returns_success_code
 * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
 *
 * @memberof CaBase_t
 */
LIBCOMBINE_EXTERN
int
CaBase_setNamespaces (CaBase_t *sb, XMLNamespaces_t *xmlns);


/**
 * Sets the notes for the given OMEX structure.
 *
 * @param sb the given OMEX structure.
 * @param notes the XMLNode_t structure respresenting the notes.
 *
 * @copydetails doc_returns_success_code
 * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
 * @li @omexconstant{LIBCOMBINE_INVALID_OBJECT, OperationReturnValues_t}
 *
 * @memberof CaBase_t
 */
LIBCOMBINE_EXTERN
int
CaBase_setNotes (CaBase_t *sb, XMLNode_t *notes);


/**
 * Sets the notes for the given OMEX structure.
 *
 * @param sb the given OMEX structure.
 * @param notes the string (const char*) respresenting the notes.
 *
 * @copydetails doc_returns_success_code
 * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
 * @li @omexconstant{LIBCOMBINE_INVALID_OBJECT, OperationReturnValues_t}
 * @li @omexconstant{LIBCOMBINE_OPERATION_FAILED, OperationReturnValues_t}
 *
 * @memberof CaBase_t
 */
LIBCOMBINE_EXTERN
int
CaBase_setNotesString (CaBase_t *sb, const char *notes);


/**
 * Sets the notes for the given OMEX structure.
 *
 * @param sb the given OMEX structure.
 * @param notes the string (const char*) respresenting the notes.
 *
 * @copydetails doc_returns_success_code
 * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
 * @li @omexconstant{LIBCOMBINE_INVALID_OBJECT, OperationReturnValues_t}
 * @li @omexconstant{LIBCOMBINE_OPERATION_FAILED, OperationReturnValues_t}
 *
 * @memberof CaBase_t
 */
LIBCOMBINE_EXTERN
int
CaBase_setNotesStringAddMarkup (CaBase_t *sb, const char *notes);


/**
 * Appends the notes for the given OMEX structure.
 *
 * @param sb the given OMEX structure.
 * @param notes the XMLNode_t structure respresenting the notes.
 *
 * @copydetails doc_returns_success_code
 * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
 * @li @omexconstant{LIBCOMBINE_INVALID_OBJECT, OperationReturnValues_t}
 * @li @omexconstant{LIBCOMBINE_OPERATION_FAILED, OperationReturnValues_t}
 *
 * @memberof CaBase_t
 */
LIBCOMBINE_EXTERN
int
CaBase_appendNotes (CaBase_t *sb, XMLNode_t *notes);


/**
 * Appends the notes for the given OMEX structure.
 *
 * @param sb the given OMEX structure.
 * @param notes the string (const char*) respresenting the notes.
 *
 * @copydetails doc_returns_success_code
 * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
 * @li @omexconstant{LIBCOMBINE_INVALID_OBJECT, OperationReturnValues_t}
 * @li @omexconstant{LIBCOMBINE_OPERATION_FAILED, OperationReturnValues_t}
 *
 * @memberof CaBase_t
 */
LIBCOMBINE_EXTERN
int
CaBase_appendNotesString (CaBase_t *sb, const char *notes);


/**
 * Sets the annotation for the given OMEX structure.
 *
 * @param sb the given OMEX structure.
 * @param annotation the XMLNode_t structure respresenting the annotation.
 *
 * @copydetails doc_returns_success_code
 * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
 *
 * @memberof CaBase_t
 */
LIBCOMBINE_EXTERN
int
CaBase_setAnnotation (CaBase_t *sb, XMLNode_t *annotation);


/**
 * Sets the annotation for the given OMEX structure.
 *
 * @param sb the given OMEX structure.
 * @param annotation the string (const char*) respresenting the annotation.
 *
 * @copydetails doc_returns_success_code
 * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
 * @li @omexconstant{LIBCOMBINE_OPERATION_FAILED, OperationReturnValues_t}
 *
 * @memberof CaBase_t
 */
LIBCOMBINE_EXTERN
int
CaBase_setAnnotationString (CaBase_t *sb, const char *annotation);


/**
 * Appends the annotation for the given OMEX structure.
 *
 * @param sb the given OMEX structure.
 * @param annotation the XMLNode_t structure respresenting the annotation.
 *
 * @copydetails doc_returns_success_code
 * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
 * @li @omexconstant{LIBCOMBINE_OPERATION_FAILED, OperationReturnValues_t}
 *
 * @memberof CaBase_t
 */
LIBCOMBINE_EXTERN
int
CaBase_appendAnnotation (CaBase_t *sb, XMLNode_t *annotation);


/**
 * Appends the annotation for the given OMEX structure.
 *
 * @param sb the given OMEX structure.
 * @param annotation the string (const char*) respresenting the annotation.
 *
 * @copydetails doc_returns_success_code
 * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
 * @li @omexconstant{LIBCOMBINE_OPERATION_FAILED, OperationReturnValues_t}
 *
 * @memberof CaBase_t
 */
LIBCOMBINE_EXTERN
int
CaBase_appendAnnotationString (CaBase_t *sb, const char *annotation);


/**
 * Unsets the "metaid" attribute of the given structure.
 *
 * @param sb the CaBase_t structure
 *
 * @copydetails doc_returns_success_code
 * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
 * @li @omexconstant{LIBCOMBINE_OPERATION_FAILED, OperationReturnValues_t}
 *
 * @memberof CaBase_t
 */
LIBCOMBINE_EXTERN
int
CaBase_unsetMetaId (CaBase_t *sb);


/**
 * Unsets the "notes" subelement of the given structure.
 *
 * @param sb the CaBase_t structure
 *
 * @copydetails doc_returns_success_code
 * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
 *
 * @memberof CaBase_t
 */
LIBCOMBINE_EXTERN
int
CaBase_unsetNotes (CaBase_t *sb);


/**
 * Unsets the "annotation" subelement of the given structure.
 *
 * @param sb the CaBase_t structure
 *
 * @copydetails doc_returns_success_code
 * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
 *
 * @memberof CaBase_t
 */
LIBCOMBINE_EXTERN
int
CaBase_unsetAnnotation (CaBase_t *sb);


/**
 * Returns the Model_t structure in which the given instance is located.
 *
 * @param sb the CaBase_t structure
 *
 * @return the parent Model_t strucdture of the given structure.
 *
 * @memberof CaBase_t
 */
LIBCOMBINE_EXTERN
const Model_t *
CaBase_getModel (const CaBase_t *sb);


/**
 * Returns the OMEX Level of the overall OMEX document.
 *
 * @param sb the CaBase_t structure to query
 *
 * @return the OMEX level of the given structure.
 *
 * @see getVersion()
 *
 * @memberof CaBase_t
 */
LIBCOMBINE_EXTERN
unsigned int
CaBase_getLevel (const CaBase_t *sb);


/**
 * Returns the Version within the OMEX Level of the overall OMEX document.
 *
 * @param sb the CaBase_t structure to query
 *
 * @return the OMEX version of the given structure.
 *
 * @see getLevel()
 *
 * @memberof CaBase_t
 */
LIBCOMBINE_EXTERN
unsigned int
CaBase_getVersion (const CaBase_t *sb);


/**
 * Returns the libCombine type code for this structure.
 *
 * This method MAY return the typecode of this OMEX structure or it MAY
 * return OMEX_UNKNOWN.  That is, subclasses of CaBase are not required to
 * implement this method to return a typecode.  This method is meant
 * primarily for the LibCombine C interface where class and subclass
 * information is not readily available.
 *
 * @note In libCombine 5, the type of return value has been changed from
 * typecode (int) to int. The return value is one of enum values defined for
 * each package. For example, return values will be one of typecode (int) if
 * this structure is defined in OMEX core package, return values will be one of
 * CaLayoutTypeCode_t if this structure is defined in Layout extension
 * (i.e. similar enum types are defined in each package extension for each
 * CaBase subclass) The value of each typecode can be duplicated between those
 * of different packages. Thus, to distinguish the typecodes of different
 * packages, not only the return value of getTypeCode() but also that of
 * getPackageName() must be checked.
 *
 * @param sb the CaBase_t structure
 *
 * @return the typecode (int value) of this OMEX structure or OMEX_UNKNOWN
 * (default).
 *
 * @see getElementName()
 * @see getPackageName()
 *
 * @memberof CaBase_t
 */
LIBCOMBINE_EXTERN
int
CaBase_getTypeCode (const CaBase_t *sb);


/**
 * Returns the XML element name of the given structure.
 *
 * This is overridden by subclasses to return a string appropriate to the
 * OMEX component.  For example, Model defines it as returning "model",
 * CompartmentType defines it as returning "compartmentType", etc.
 *
 * @param sb the CaBase_t structure
 *
 * @memberof CaBase_t
 */
LIBCOMBINE_EXTERN
const char *
CaBase_getElementName (const CaBase_t *sb);


/**
 * Predicate returning nonzero true or false depending on whether the
 * structure's level/version and namespace values correspond to a valid
 * OMEX specification.
 *
 * @param sb the CaBase_t structure
 *
 * @return nonzero (true) if the level, version and namespace values of this
 * OMEX structure correspond to a valid set of values, zero (false) otherwise.
 *
 * @memberof CaBase_t
 */
LIBCOMBINE_EXTERN
int
CaBase_hasValidLevelVersionNamespaceCombination(CaBase_t *sb);


/**
 * Sets the user data of this node. This can be used by the application
 * developer to attach custom information to the node. In case of a deep
 * copy this attribute will passed as it is. The attribute will be never
 * interpreted by this class.
 *
 * @param sb defines the node of which the user data should be set.
 * @param userData specifies the new user data.
 *
 * @copydetails doc_returns_success_code
 * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
 * @li @omexconstant{LIBCOMBINE_OPERATION_FAILED, OperationReturnValues_t}
 * @li @omexconstant{LIBCOMBINE_INVALID_OBJECT, OperationReturnValues_t}
 *
 * @memberof CaBase_t
 */
LIBCOMBINE_EXTERN
int 
CaBase_setUserData(CaBase_t* sb, void *userData);

/**
 * Returns the user data that has been previously set by setUserData().
 *
 * @param sb the CaBase_t structure in question.
 * @return the user data of this node. NULL if no user data has been.
 * @see CaBase_setUserData
 *
 * @memberof CaBase_t
 */
LIBCOMBINE_EXTERN
void *
CaBase_getUserData(const CaBase_t* sb);

/**
 * Predicate returning nonzero true or false depending on whether the
 * structure's user data object has been set.
 *
 * @param sb defines the node of which the user data should be queried.
 *
 * @return nonzero (true) if the user data object of this
 * OMEX structure has been set, zero (false) otherwise.
 *
 * @memberof CaBase_t
 */
LIBCOMBINE_EXTERN
int 
CaBase_isSetUserData(const CaBase_t* sb);

/**
 * Unsets the user data of this node. 
 *
 * @param sb defines the node of which the user data should be unset.
 *
 * @copydetails doc_returns_success_code
 * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
 * @li @omexconstant{LIBCOMBINE_OPERATION_FAILED, OperationReturnValues_t}
 * @li @omexconstant{LIBCOMBINE_INVALID_OBJECT, OperationReturnValues_t}
 *
 * @memberof CaBase_t
 */
LIBCOMBINE_EXTERN
int 
CaBase_unsetUserData(CaBase_t* sb);

END_C_DECLS
LIBCOMBINE_CPP_NAMESPACE_END

#endif  /* !SWIG   */
#endif  /* CaBase_h */
