/**
 * @file CaTypeCodes.h
 * @brief Definition of the CaTypeCodes class.
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
 * @class CaTypeCodes
 * @sbmlbrief{} TODO:Definition of the CaTypeCodes class.
 */



#ifndef CaTypeCodes_h
#define CaTypeCodes_h


#include <omex/common/libcombine-config.h>
#include <omex/common/extern.h>

LIBCOMBINE_CPP_NAMESPACE_BEGIN
BEGIN_C_DECLS


/**
 * @enum  CaTypeCode_t
 * @brief The enumeration of possible OMEX core object types.
 *
 * @copydetails doc_what_are_typecodes
 *
 * @copydetails doc_additional_typecode_details
 *
 */
typedef enum
{
    OMEX_UNKNOWN                    =  0
  , LIB_COMBINE_CONTENT
  , LIB_COMBINE_OMEXMANIFEST
  , LIB_COMBINE_CROSSREF
  , OMEX_LIST_OF
} CaTypeCode_t;



/**
 * This method takes an OMEX type code and returns a string representing
 * the code.
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
 * libcombine@endlink.  The names of the type codes all begin with
 * the characters @c OMEX_. @endif@~
 *
 * @return a human readable name for the given
 * @if clike #CaTypeCode_t value@else OMEX type code@endif.
 *
 * @note The caller does not own the returned string and is therefore not
 * allowed to modify it.
 */
LIBCOMBINE_EXTERN
const char *
CaTypeCode_toString (int tc);


END_C_DECLS
LIBCOMBINE_CPP_NAMESPACE_END

#endif  /* CaTypeCodes_h */
