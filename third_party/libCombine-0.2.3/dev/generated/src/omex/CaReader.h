/**
 * @file CaReader.h
 * @brief Definition of the CaReader class.
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
 * @class CaReader
 * @sbmlbrief{} TODO:Definition of the CaReader class.
 */


#ifndef CaReader_h
#define CaReader_h


#include <omex/common/extern.h>
#include <omex/common/combinefwd.h>
#include <sbml/util/util.h>

#ifdef __cplusplus


#include <string>

LIBCOMBINE_CPP_NAMESPACE_BEGIN

class CaOmexManifest;


class LIBCOMBINE_EXTERN CaReader
{
public:

  /**
   * Creates a new CaReader object and returns it.
   *
   * The libCombine CaReader object offers methods for reading OMEX in
   * XML form from files and text strings.
   */
  CaReader ();


  /**
   * Destroys this CaReader.
   */
  virtual ~CaReader ();


  /**
   * This method is identical to
   * @if python @link CaReader::readOMEXFromFile() CaReader.readOMEXFromFile()@endlink@endif@if java @link CaReader::readOMEXFromFile(String) CaReader.readOMEXFromFile(String)@endlink@endif@if cpp CaReader::readOMEXFromFile()@endif@if csharp CaReader.readOMEXFromFile()@endif.
   *
   * @param filename the name or full pathname of the file to be read.
   *
   * @return a pointer to the CaOmexManifest object created from the OMEX
   * content in @p filename.
   *
   * @see readOMEXFromString(@if java String@endif)
   * @see CaError
   * @see CaOmexManifest
   */
  CaOmexManifest* readOMEX (const std::string& filename);


  /**
   * This method is identical to
   * @if python @link CaReader::readOMEX() CaReader.readOMEX()@endlink@endif@if java @link CaReader::readOMEX(String) CaReader.readOMEX(String)@endlink@endif@if cpp CaReader::readOMEX()@endif@if csharp CaReader.readOMEX()@endif.
   *
   * @param filename the name or full pathname of the file to be read.
   *
   * @return a pointer to the CaOmexManifest object created from the Ca
   * content in @p filename.
   *
   * @see readOMEXFromString(@if java String@endif)
   * @see CaError
   * @see CaOmexManifest
   */
  CaOmexManifest* readOMEXFromFile (const std::string& filename);


  /**
   * @param xml a string containing a full Ca model
   *
   * @return a pointer to the CaOmexManifest created from the Ca content,
   * or a null pointer if @p xml is null.
   *
   * @see CaReader::readOMEX(@if java String@endif)
   */
  CaOmexManifest* readOMEXFromString (const std::string& xml);


  /**
   * Static method; returns @c true if this copy of libCombine supports
   * <i>gzip</I> and <i>zip</i> format compression.
   *
   * @return @c true if libCombine has been linked with the <i>zlib</i>
   * library, @c false otherwise.
   *
   * @see @if clike hasBzip2() @else CaReader::hasBzip2()@endif@~
   */
  static bool hasZlib();


  /**
   * Static method; returns @c true if this copy of libCombine supports
   * <i>bzip2</i> format compression.
   *
   * @return @c true if libCombine is linked with the <i>bzip2</i>
   * libraries, @c false otherwise.
   *
   * @see @if clike hasZlib() @else CaReader::hasZlib()@endif@~
   */
  static bool hasBzip2();


protected:
  /** @cond doxygenLibomexInternal */
  /**
   * Used by readOMEX() and readOMEXFromString().
   */
  CaOmexManifest* readInternal (const char* content, bool isFile = true);

  /** @endcond */
};

LIBCOMBINE_CPP_NAMESPACE_END

#endif /* __cplusplus */


LIBCOMBINE_CPP_NAMESPACE_BEGIN
BEGIN_C_DECLS


#ifndef SWIG


/**
 * Creates a new CaReader_t and returns it.
 *
 * By default, XML Schema validation is off.
 *
 * @if conly
 * @memberof CaReader_t
 * @endif
 */
LIBCOMBINE_EXTERN
CaReader_t *
CaReader_create (void);


/**
 * Frees the given CaReader_t.
 *
 * @if conly
 * @memberof CaReader_t
 * @endif
 */
LIBCOMBINE_EXTERN
void
CaReader_free (CaReader_t *sr);


/**
 * This function is identical to CaReader_readOMEXFromFile().
 *
 * @param sr The CaReader_t structure to use.
 *
 * @param filename a string giving the path to a file where the XML
 * content is to be found.
 *
 * @return a pointer to the CaOmexManifest structure created from the Ca
 * content read from @p filename.
 *
 * @if conly
 * @memberof CaReader_t
 * @endif
 */
LIBCOMBINE_EXTERN
CaOmexManifest_t *
CaReader_readOMEX (CaReader_t *sr, const char *filename);


/**
 * This function is identical to CaReader_readOMEX().
 *
 * @param sr The CaReader_t structure to use.
 *
 * @param filename a string giving the path to a file where the XML
 * content is to be found.
 *
 * @return a pointer to the CaOmexManifest structure created from the Ca
 * content read from @p filename.
 *
 * @if conly
 * @memberof CaReader_t
 * @endif
 */
LIBCOMBINE_EXTERN
CaOmexManifest_t *
CaReader_readOMEXFromFile (CaReader_t *sr, const char *filename);


/**
 * @param sr the CaReader_t structure to use
 *
 * @param xml the input xml string.
 *
 * @return a pointer to the CaOmexManifest read.
 *
 * @if conly
 * @memberof CaReader_t
 * @endif
 */
LIBCOMBINE_EXTERN
CaOmexManifest_t *
CaReader_readOMEXFromString (CaReader_t *sr, const char *xml);


/**
 * Returns @c true if the underlying libCombine supports @em gzip and @em zlib
 * format compression.
 *
 * This predicate tests whether the underlying copy of the libCombine library
 * has been linked with the necessary libraries to support @em zlib
 * compression.
 *
 * @return @c non-zero if libCombine is linked with zlib, @c zero otherwise.
 *
 * @if conly
 * @memberof CaReader_t
 * @endif
 */
LIBCOMBINE_EXTERN
int
CaReader_hasZlib ();


/**
 * Returns @c true if the underlying libCombine supports @em bzip2 format
 * compression.
 *
 * This predicate tests whether the underlying copy of the libCombine library
 * has been linked with the necessary libraries to support @em bzip2
 * compression.
 *
 * @return @c non-zero if libCombine is linked with bzip2, @c zero otherwise.
 *
 * @if conly
 * @memberof CaReader_t
 * @endif
 */
LIBCOMBINE_EXTERN
int
CaReader_hasBzip2 ();

#endif  /* !SWIG */


/**
 * @if conly
 * @memberof CaReader_t
 * @endif
 */
LIBCOMBINE_EXTERN
CaOmexManifest_t *
readOMEX (const char *filename);


/**
 * @param filename the name or full pathname of the file to be read.
 *
 * @return a pointer to the CaOmexManifest structure created from the Ca
 * content in @p filename.
 *
 * @if conly
 * @memberof CaReader_t
 * @endif
 */
LIBCOMBINE_EXTERN
CaOmexManifest_t *
readOMEXFromFile (const char *filename);


/**
 * @param xml a string containing a full Ca model
 *
 * @return a pointer to the CaOmexManifest structure created from the Ca
 * content in @p xml.
 *
 * @if conly
 * @memberof CaReader_t
 * @endif
 */
LIBCOMBINE_EXTERN
CaOmexManifest_t *
readOMEXFromString (const char *xml);


END_C_DECLS
LIBCOMBINE_CPP_NAMESPACE_END

#endif  /* CaReader_h */
