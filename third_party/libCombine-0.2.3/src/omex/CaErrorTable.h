/**
 * @file CaErrorTable.h
 * @brief Definition of the CaErrorTable class.
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


#ifndef CaErrorTable_H__
#define CaErrorTable_H__

#include <omex/CaError.h>


LIBCOMBINE_CPP_NAMESPACE_BEGIN

/** @cond doxygenLibomexInternal */
typedef struct {
  const char * ref_l1v1;
} referenceEntry;


typedef struct {
  unsigned int code;
  const char * shortMessage;
  unsigned int category;
  unsigned int l1v1_severity;
  const char * message;
  referenceEntry reference;
} omexErrorTableEntry;


static const omexErrorTableEntry omexErrorTable[] =
{
  // 10000
  { CaUnknown,
    "Encountered unknown internal libCombine error",
    LIBCOMBINE_CAT_INTERNAL, 
    LIBCOMBINE_SEV_FATAL,
    "Unrecognized error encountered by libCombine",
    {"",
    }
  },

  //10001
  {
    CaNotUTF8,
    "File does not use UTF-8 encoding",
    LIBCOMBINE_CAT_OMEX,
    LIBCOMBINE_SEV_ERROR,
    "An OMEX XML file must use UTF-8 as the character encoding. More "
    "precisely, the 'encoding' attribute of the XML declaration at the "
    "beginning of the XML data stream cannot have a value other than "
    "'UTF-8'. An example valid declaration is "
    "'<?xml version=\"1.0\" encoding=\"UTF-8\"?>'.",
    {""
    }
  },

  //10002
  {
    CaUnrecognizedElement,
    "Encountered unrecognized element",
    LIBCOMBINE_CAT_OMEX,
    LIBCOMBINE_SEV_ERROR,
    "An OMEX XML document must not contain undefined elements or attributes "
    "in the OMEX namespace. Documents containing unknown elements or "
    "attributes placed in the OMEX namespace do not conform to the OMEX "
    "specification.",  
    {""
    }
  },

  //10003
  {
    CaNotSchemaConformant,
    "Document does not conform to the OMEX XML schema",
    LIBCOMBINE_CAT_OMEX,
    LIBCOMBINE_SEV_ERROR,
    "An OMEX XML document must conform to the XML Schema for the corresponding "
    "OMEX Level, Version and Release. The XML Schema for OMEX defines the "
    "basic OMEX object structure, the data types used by those objects, and the "
    "order in which the objects may appear in an OMEX document.",
    {""
    }
  },

  //10201
  {
    CaInvalidMathElement,
    "Invalid MathML",
    LIBCOMBINE_CAT_MATHML_CONSISTENCY,
    LIBCOMBINE_SEV_ERROR,
    "All MathML content in OMEX must appear within a <math> element, and the "
    "<math> element must be either explicitly or implicitly in the XML "
    "namespace \"http://www.w3.org/1998/Math/MathML\".",
    {""
    }
  },

  //10401
  {
    CaMissingAnnotationNamespace,
    "Missing declaration of the XML namespace for the annotation",
    LIBCOMBINE_CAT_OMEX,
    LIBCOMBINE_SEV_ERROR,
    "Every top-level element within an annotation element must "
    "have a namespace declared.",
    {""
    }
  },

  //10402
  {
    CaDuplicateAnnotationNamespaces,
    "Multiple annotations using the same XML namespace",
    LIBCOMBINE_CAT_OMEX,
    LIBCOMBINE_SEV_ERROR,
    "There cannot be more than one top-level element using a "
    "given namespace inside a given annotation element. ", 
    {""
    }
  },

  //10403
  {
    CaNamespaceInAnnotation,
    "The OMEX XML namespace cannot be used in an Annotation object",
    LIBCOMBINE_CAT_OMEX,
    LIBCOMBINE_SEV_ERROR,
    "Top-level elements within an annotation element cannot use any OMEX "
    "namespace, whether explicitly or implicitly (by failing "
    "to declare any namespace).",
    {""
    }
  },

  //10404
  {
    CaMultipleAnnotations,
    "Only one Annotation object is permitted under a given OMEX object",
    LIBCOMBINE_CAT_OMEX,
    LIBCOMBINE_SEV_ERROR,
    "A given OMEX object may contain at most one <annotation> element.",
    {""
    }
  },

  //10801
  {
    CaNotesNotInXHTMLNamespace,
    "Notes must be placed in the XHTML XML namespace",
    LIBCOMBINE_CAT_OMEX,
    LIBCOMBINE_SEV_ERROR,
    "The contents of the <notes> element must be explicitly placed in the "
    "XHTML XML namespace.", 
    {""
    }
  },

  //10802
  {
    CaNotesContainsXMLDecl,
    "XML declarations are not permitted in Notes objects",
    LIBCOMBINE_CAT_OMEX,
    LIBCOMBINE_SEV_ERROR,
    "The contents of the <notes> element must not contain an XML declaration "
    "(i.e., a string of the form \"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\" "
    "or similar).",
    {""
    }
  },

  //10803
  {
    CaNotesContainsDOCTYPE,
    "XML DOCTYPE elements are not permitted in Notes objects",
    LIBCOMBINE_CAT_OMEX,
    LIBCOMBINE_SEV_ERROR,
    "The contents of the <notes> element must not contain an XML DOCTYPE "
    "declaration (i.e., a string beginning with the characters \"<!DOCTYPE\". ",
    {""
    }
  },

  //10804
  {
    CaInvalidNotesContent,
    "Invalid notes content",
    LIBCOMBINE_CAT_OMEX,
    LIBCOMBINE_SEV_ERROR,
    "Invalid contents in a <notes> element. ",
    {""
    }
  },

  //10805
  {
    CaOnlyOneNotesElementAllowed,
    "Only one Notes subobject is permitted on a given OMEX object",
    LIBCOMBINE_CAT_OMEX,
    LIBCOMBINE_SEV_ERROR,
    "A given OMEX object may contain at most one <notes> element. ",
    {""
    }
  },

  /* --------------------------------------------------------------------------
   * Boundary marker.  OMEX specific errors.
   * ----------------------------------------------------------------------- */

  // 10101
  { CombineNSUndeclared,
    "The Combine namespace is not correctly declared.",
    LIBCOMBINE_CAT_GENERAL_CONSISTENCY,
    LIBCOMBINE_SEV_ERROR,
    "To conform to the Package specification for SBML Level 3 Version 1, an "
    "SBML document must declare "
    "'http://www.sbml.org/sbml/level3/version1/combine/version1' as the "
    "XMLNamespace to use for elements of this package.",
    { "L3V1 Combine V1 Section 3.1"
    }
  },

  // 10102
  { CombineElementNotInNs,
    "Element not in Combine namespace",
    LIBCOMBINE_CAT_GENERAL_CONSISTENCY,
    LIBCOMBINE_SEV_ERROR,
    "Wherever they appear in an SBML document, elements and attributes from the "
    "Package must use the "
    "'http://www.sbml.org/sbml/level3/version1/combine/version1' namespace, "
    "declaring so either explicitly or implicitly.",
    { "L3V1 Combine V1 Section 3.1"
    }
  },

  // 10301
  { CombineDuplicateComponentId,
    "Duplicate 'id' attribute value",
    LIBCOMBINE_CAT_GENERAL_CONSISTENCY,
    LIBCOMBINE_SEV_ERROR,
    "(Extends validation rule #10301 in the SBML Level 3 Core specification. TO "
    "DO list scope of ids)",
    { "L3V1 Combine V1 Section"
    }
  },

  // 10302
  { CombineIdSyntaxRule,
    "Invalid SId syntax",
    LIBCOMBINE_CAT_GENERAL_CONSISTENCY,
    LIBCOMBINE_SEV_ERROR,
    "The value of a 'combine:id' must conform to the syntax of the <sbml> data "
    "type 'SId'",
    { "L3V1 Combine V1 Section"
    }
  },

  // 10303
  { CaInvalidMetaidSyntax,
    "Invalid SId syntax",
    LIBCOMBINE_CAT_GENERAL_CONSISTENCY,
    LIBCOMBINE_SEV_ERROR,
    "The value of a 'combine:metaid' must conform to the syntax of the XML Type "
    "ID",
    { "L3V1 Combine V1 Section"
    }
  },

  // 20101
  { InvalidNamespaceOnCa,
    "Invalid namespace",
    LIBCOMBINE_CAT_GENERAL_CONSISTENCY,
    LIBCOMBINE_SEV_ERROR,
    "Invalid namespace declared.",
    { "L3V1 Combine V1 Section"
    }
  },

  // 20102
  { AllowedAttributes,
    "Allowed attributes",
    LIBCOMBINE_CAT_GENERAL_CONSISTENCY,
    LIBCOMBINE_SEV_ERROR,
    "Allowed attributes",
    { "L3V1 Combine V1 Section"
    }
  },

  // 20103
  { CaEmptyListElement,
    "No empty listOf",
    LIBCOMBINE_CAT_GENERAL_CONSISTENCY,
    LIBCOMBINE_SEV_ERROR,
    "No empty lists",
    { "L3V1 Combine V1 Section"
    }
  },

  // 20201
  { CombineContentAllowedCoreAttributes,
    "Core attributes allowed on <content>.",
    LIBCOMBINE_CAT_GENERAL_CONSISTENCY,
    LIBCOMBINE_SEV_ERROR,
    "A <content> object may have the optional SBML Level 3 Core attributes "
    "'metaid' and 'sboTerm'. No other attributes from the SBML Level 3 Core "
    "namespaces are permitted on a <content>.",
    { "L3V1 Combine V1 Section"
    }
  },

  // 20202
  { CombineContentAllowedCoreElements,
    "Core elements allowed on <content>.",
    LIBCOMBINE_CAT_GENERAL_CONSISTENCY,
    LIBCOMBINE_SEV_ERROR,
    "A <content> object may have the optional SBML Level 3 Core subobjects for "
    "notes and annotations. No other elements from the SBML Level 3 Core "
    "namespaces are permitted on a <content>.",
    { "L3V1 Combine V1 Section"
    }
  },

  // 20203
  { CombineContentAllowedAttributes,
    "Attributes allowed on <content>.",
    LIBCOMBINE_CAT_GENERAL_CONSISTENCY,
    LIBCOMBINE_SEV_ERROR,
    "A <content> object must have the required attributes 'combine:location' "
    "and 'combine:format', and may have the optional attribute "
    "'combine:master'. No other attributes from the SBML Level 3 Combine "
    "Archive namespaces are permitted on a <content> object. ",
    { "L3V1 Combine V1 Section"
    }
  },

  // 20204
  { CombineContentAllowedElements,
    "Elements allowed on <content>.",
    LIBCOMBINE_CAT_GENERAL_CONSISTENCY,
    LIBCOMBINE_SEV_ERROR,
    "A <content> object may contain one and only one instance of the "
    "<listOfCrossRefs> element. No other elements from the SBML Level 3 Combine "
    "Archive namespaces are permitted on a <content> object. ",
    { "L3V1 Combine V1 Section"
    }
  },

  // 20205
  { CombineContentLocationMustBeString,
    "The 'location' attribute must be String.",
    LIBCOMBINE_CAT_GENERAL_CONSISTENCY,
    LIBCOMBINE_SEV_ERROR,
    "The attribute 'combine:location' on a <content> must have a value of data "
    "type 'string'.",
    { "L3V1 Combine V1 Section"
    }
  },

  // 20206
  { CombineContentFormatMustBeString,
    "The 'format' attribute must be String.",
    LIBCOMBINE_CAT_GENERAL_CONSISTENCY,
    LIBCOMBINE_SEV_ERROR,
    "The attribute 'combine:format' on a <content> must have a value of data "
    "type 'string'.",
    { "L3V1 Combine V1 Section"
    }
  },

  // 20207
  { CombineContentMasterMustBeBoolean,
    "The 'master' attribute must be Boolean.",
    LIBCOMBINE_CAT_GENERAL_CONSISTENCY,
    LIBCOMBINE_SEV_ERROR,
    "The attribute 'combine:master' on a <content> must have a value of data "
    "type 'boolean'.",
    { "L3V1 Combine V1 Section"
    }
  },

  // 20301
  { CombineOmexManifestAllowedCoreAttributes,
    "Core attributes allowed on <omexManifest>.",
    LIBCOMBINE_CAT_GENERAL_CONSISTENCY,
    LIBCOMBINE_SEV_ERROR,
    "An <omexManifest> object may have the optional SBML Level 3 Core "
    "attributes 'metaid' and 'sboTerm'. No other attributes from the SBML Level "
    "3 Core namespaces are permitted on an <omexManifest>.",
    { "L3V1 Combine V1 Section"
    }
  },

  // 20302
  { CombineOmexManifestAllowedCoreElements,
    "Core elements allowed on <omexManifest>.",
    LIBCOMBINE_CAT_GENERAL_CONSISTENCY,
    LIBCOMBINE_SEV_ERROR,
    "An <omexManifest> object may have the optional SBML Level 3 Core "
    "subobjects for notes and annotations. No other elements from the SBML "
    "Level 3 Core namespaces are permitted on an <omexManifest>.",
    { "L3V1 Combine V1 Section"
    }
  },

  // 20303
  { CombineOmexManifestAllowedElements,
    "Elements allowed on <omexManifest>.",
    LIBCOMBINE_CAT_GENERAL_CONSISTENCY,
    LIBCOMBINE_SEV_ERROR,
    "An <omexManifest> object may contain one and only one instance of the "
    "<listOfContents> element. No other elements from the SBML Level 3 Combine "
    "Archive namespaces are permitted on an <omexManifest> object. ",
    { "L3V1 Combine V1 Section"
    }
  },

  // 20401
  { CombineCrossRefAllowedCoreAttributes,
    "Core attributes allowed on <crossRef>.",
    LIBCOMBINE_CAT_GENERAL_CONSISTENCY,
    LIBCOMBINE_SEV_ERROR,
    "A <crossRef> object may have the optional SBML Level 3 Core attributes "
    "'metaid' and 'sboTerm'. No other attributes from the SBML Level 3 Core "
    "namespaces are permitted on a <crossRef>.",
    { "L3V1 Combine V1 Section"
    }
  },

  // 20402
  { CombineCrossRefAllowedCoreElements,
    "Core elements allowed on <crossRef>.",
    LIBCOMBINE_CAT_GENERAL_CONSISTENCY,
    LIBCOMBINE_SEV_ERROR,
    "A <crossRef> object may have the optional SBML Level 3 Core subobjects for "
    "notes and annotations. No other elements from the SBML Level 3 Core "
    "namespaces are permitted on a <crossRef>.",
    { "L3V1 Combine V1 Section"
    }
  },

  // 20403
  { CombineCrossRefAllowedAttributes,
    "Attributes allowed on <crossRef>.",
    LIBCOMBINE_CAT_GENERAL_CONSISTENCY,
    LIBCOMBINE_SEV_ERROR,
    "A <crossRef> object may have the optional attribute 'combine:location'. No "
    "other attributes from the SBML Level 3 Combine Archive namespaces are "
    "permitted on a <crossRef> object. ",
    { "L3V1 Combine V1 Section"
    }
  },

  // 20404
  { CombineCrossRefLocationMustBeString,
    "The 'location' attribute must be String.",
    LIBCOMBINE_CAT_GENERAL_CONSISTENCY,
    LIBCOMBINE_SEV_ERROR,
    "The attribute 'combine:location' on a <crossRef> must have a value of data "
    "type 'string'.",
    { "L3V1 Combine V1 Section"
    }
  },

  /* --------------------------------------------------------------------------
   * Boundary marker.  Application-specific codes should begin at 100000.
   * ----------------------------------------------------------------------- */

  //99994
  {
    CaUnknownCoreAttribute,
    "Unknown attribute",
    LIBCOMBINE_CAT_INTERNAL,
    LIBCOMBINE_SEV_ERROR,
    "An unknown attribute has been found.", 
    {""
    }
   },

  //99999
  {
    CaCodesUpperBound,
    "Upper boundary of libCombine-specific diagnostic codes",
    LIBCOMBINE_CAT_INTERNAL,
    LIBCOMBINE_SEV_NOT_APPLICABLE,
    "Application-specific codes should begin at 100000.", 
    {""
    }
   }
};

LIBCOMBINE_CPP_NAMESPACE_END
/** @endcond */



#endif /* !CaErrorTable_H__ */

