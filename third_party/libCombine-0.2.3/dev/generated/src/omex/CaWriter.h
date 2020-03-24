/**
 * @file CaWriter.h
 * @brief Definition of the CaWriter class.
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
 * @class CaWriter
 * @sbmlbrief{} TODO:Definition of the CaWriter class.
 */


#ifndef CaWriter_h
#define CaWriter_h


#include <omex/common/extern.h>
#include <omex/common/combinefwd.h>


#ifdef __cplusplus


#include <iosfwd>
#include <string>

LIBCOMBINE_CPP_NAMESPACE_BEGIN

class CaOmexManifest;


class LIBCOMBINE_EXTERN CaWriter
{
public:

  /**
   * Creates a new CaWriter.
   *
   * The libCombine CaWriter objects offer methods for writing OMEX in
   * XML form to files and text strings.
   */
  CaWriter  ();


  /**
   * Destroys this CaWriter.
   */
  ~CaWriter ();


  /**
   * Sets the name of this program, i.e., the program that is about to
   * write out the CaOmexManifest.
   *
   * If the program name and version are set (see
   * CaWriter::setProgramVersion(@if java String@endif)), the
   * following XML comment, intended for human consumption, will be written
   * at the beginning of the XML document:
   * @verbatim
 <!-- Created by <program name> version <program version>
 on yyyy-MM-dd HH:mm with libCombine version <libcombine version>. -->
 @endverbatim
   *
   * If the program name and version are not set at some point before
   * calling the writeOMEX() methods, no such comment is written out.
   *
   * @param name the name of this program (where "this program" refers to
   * program in which libCombine is embedded, not libCombine itself!)
   *
   * @copydetails doc_returns_success_code
   * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
   * 
   * @see setProgramVersion(const std::string& version)
   */
  int setProgramName (const std::string& name);


  /**
   * Sets the version of this program, i.e., the program that is about to
   * write out the CaOmexManifest.
   *
   * If the program version and name are set (see
   * CaWriter::setProgramName(@if java String@endif)), the
   * following XML comment, intended for human consumption, will be written
   * at the beginning of the document:
   * @verbatim
 <!-- Created by <program name> version <program version>
 on yyyy-MM-dd HH:mm with libCombine version <libcombine version>. -->
 @endverbatim
   *
   * If the program version and name are not set at some point before
   * calling the writeOMEX() methods, no such comment is written out.
   *
   * @param version the version of this program (where "this program"
   * refers to program in which libCombine is embedded, not libCombine itself!)
   *
   * @copydetails doc_returns_success_code
   * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
   *
   * @see setProgramName(const std::string& name)
   */
  int setProgramVersion (const std::string& version);


  /**
   * Writes the given CaOmexManifest to filename.
   *
   * @htmlinclude assuming-compressed-file.html
   *
   * @param d the CaOmexManifest to be written
   *
   * @param filename the name or full pathname of the file where the OMEX
   * is to be written. 
   *
   * @return @c true on success and @c false if the filename could not be
   * opened for writing.
   *
   * @note @htmlinclude note-writing-zipped-files.html
   * 
   * @see setProgramVersion(const std::string& version)
   * @see setProgramName(const std::string& name)
   */
  bool writeOMEX (const CaOmexManifest* d, const std::string& filename);


  /**
   * Writes the given CaOmexManifest to the output stream.
   *
   * @param d the CaOmexManifest to be written
   *
   * @param stream the stream object where the OMEX is to be written.
   *
   * @return @c true on success and @c false if one of the underlying
   * parser components fail (rare).
   * 
   * @see setProgramVersion(const std::string& version)
   * @see setProgramName(const std::string& name)
   */
  bool writeOMEX (const CaOmexManifest* d, std::ostream& stream);


  /** @cond doxygenLibomexInternal */

  /**
   * Writes the given CaOmexManifest to an in-memory string and returns a
   * pointer to it.
   *
   * The string is owned by the caller and should be freed (with @c free())
   * when no longer needed.
   *
   * @param d the CaOmexManifest to be written
   *
   * @return the string on success and @c 0 if one of the underlying parser
   * components fail.
   * 
   * @see setProgramVersion(const std::string& version)
   * @see setProgramName(const std::string& name)
   */
  char* writeToString (const CaOmexManifest* d);

  /** @endcond */

  /**
   * Writes the given CaOmexManifest to filename.
   *
   * @htmlinclude assuming-compressed-file.html
   *
   * @param d the CaOmexManifest to be written
   *
   * @param filename the name or full pathname of the file where the OMEX
   * is to be written. 
   *
   * @return @c true on success and @c false if the filename could not be
   * opened for writing.
   *
   * @note @htmlinclude note-writing-zipped-files.html
   * 
   * @see setProgramVersion(const std::string& version)
   * @see setProgramName(const std::string& name)
   */
  bool writeOMEXToFile (const CaOmexManifest* d, const std::string& filename);


  /**
   * Writes the given CaOmexManifest to an in-memory string and returns a
   * pointer to it.
   *
   * The string is owned by the caller and should be freed (with @c free())
   * when no longer needed.
   *
   * @param d the CaOmexManifest to be written
   *
   * @return the string on success and @c 0 if one of the underlying parser
   * components fail.
   * 
   * @see setProgramVersion(const std::string& version)
   * @see setProgramName(const std::string& name)
   */
  char* writeOMEXToString (const CaOmexManifest* d);

#ifndef SWIG
  /**
   * Writes the given CaOmexManifest to an in-memory string and returns it.
   *
   * @param d the CaOmexManifest to be written
   *
   * @return the string on success or an empty string, 
   *         if one of the underlying parser
   *         components fail.
   * 
   * @see setProgramVersion(const std::string& version)
   * @see setProgramName(const std::string& name)
   */
  std::string writeOMEXToStdString(const CaOmexManifest* d);
#endif
  

  /**
   * Predicate returning @c true if this copy of libCombine has been linked
   * with the <em>zlib</em> library.
   *
   * LibCombine supports reading and writing files compressed with either
   * bzip2 or zip/gzip compression.  The facility depends on libCombine having
   * been compiled with the necessary support libraries.  This method
   * allows a calling program to inquire whether that is the case for the
   * copy of libCombine it is using.
   *
   * @return @c true if libCombine is linked with zlib, @c false otherwise.
   *
   * @copydetails doc_note_static_methods
   *
   * @see @if clike hasBzip2() @else CaWriter::hasBzip2() @endif@~
   */
  static bool hasZlib();


  /**
   * Predicate returning @c true if this copy of libCombine has been linked
   * with the <em>bzip2</em> library.
   *
   * LibCombine supports reading and writing files compressed with either
   * bzip2 or zip/gzip compression.  The facility depends on libCombine having
   * been compiled with the necessary support libraries.  This method
   * allows a calling program to inquire whether that is the case for the
   * copy of libCombine it is using.
   *
   * @return @c true if libCombine is linked with bzip2, @c false otherwise.
   *
   * @copydetails doc_note_static_methods
   *
   * @see @if clike hasZlib() @else CaWriter::hasZlib() @endif@~
   */
  static bool hasBzip2();


 protected:
  /** @cond doxygenLibomexInternal */
  std::string mProgramName;
  std::string mProgramVersion;

  /** @endcond */
};

#ifndef SWIG

/**
 * Writes the given CaOmexManifest to an in-memory string that is returned.
 *
 * @param d the CaOmexManifest to be written
 *
 * @return the string on success or an empty string, 
 *         if one of the underlying parser
 *         components fail.
 * 
 */
LIBCOMBINE_EXTERN
std::string writeOMEXToStdString(const CaOmexManifest* d);

#endif

LIBCOMBINE_CPP_NAMESPACE_END

#endif  /* __cplusplus */


LIBCOMBINE_CPP_NAMESPACE_BEGIN
BEGIN_C_DECLS


#ifndef SWIG


/**
 * Creates a new CaWriter and returns a pointer to it.
 *
 * @memberof CaWriter_t
 */
LIBCOMBINE_EXTERN
CaWriter_t *
CaWriter_create (void);

/**
 * Frees the given CaWriter.
 *
 * @memberof CaWriter_t
 */
LIBCOMBINE_EXTERN
void
CaWriter_free (CaWriter_t *sw);

/**
 * Sets the name of this program. i.\ e.\ the one about to write out the
 * CaOmexManifest.  If the program name and version are set
 * (setProgramVersion()), the following XML comment, intended for human
 * consumption, will be written at the beginning of the document:
 *
 *   <!-- Created by <program name> version <program version>
 *   on yyyy-MM-dd HH:mm with libCombine version <libcombine version>. -->
 *
 * @copydetails doc_returns_success_code
 * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
 *
 * @memberof CaWriter_t
 */
LIBCOMBINE_EXTERN
int
CaWriter_setProgramName (CaWriter_t *sw, const char *name);

/**
 * Sets the version of this program. i.\ e.\ the one about to write out the
 * CaOmexManifest.  If the program version and name are set
 * (setProgramName()), the following XML comment, intended for human
 * consumption, will be written at the beginning of the document:
 *
 *   <!-- Created by <program name> version <program version>
 *   on yyyy-MM-dd HH:mm with libCombine version <libcombine version>. -->
 *
 * @copydetails doc_returns_success_code
 * @li @omexconstant{LIBCOMBINE_OPERATION_SUCCESS, OperationReturnValues_t}
 *
 * @memberof CaWriter_t
 */
LIBCOMBINE_EXTERN
int
CaWriter_setProgramVersion (CaWriter_t *sw, const char *version);

/**
 * Writes the given CaOmexManifest to filename.
 *
 * @htmlinclude assuming-compressed-file.html
 *
 * If the filename ends with @em .gz, the file will be compressed by @em gzip.
 * Similary, if the filename ends with @em .zip or @em .bz2, the file will be
 * compressed by @em zip or @em bzip2, respectively. Otherwise, the fill will be
 * uncompressed.
 * If the filename ends with @em .zip, a filename that will be added to the
 * zip archive file will end with @em .xml or @em .omex. For example, the filename
 * in the zip archive will be @em test.xml if the given filename is @em test.xml.zip
 * or @em test.zip. Also, the filename in the archive will be @em test.omex if the
 * given filename is @em test.omex.zip.
 *
 * @note To write a gzip/zip file, libCombine needs to be configured and
 * linked with the <a target="_blank" href="http://www.zlib.net/">zlib</a> library at
 * compile time.  It also needs to be linked with the <a target="_blank"
 * href="">bzip2</a> library to write files in @em bzip2 format.  (Both
 * of these are the default configurations for libCombine.)  Errors about
 * unreadable files will be logged and this method will return @c false
 * if a compressed filename is given and libCombine was @em not linked with
 * the corresponding required library.
 *
 * @note CaWriter_hasZlib() and CaWriter_hasBzip2() can be used to
 * check whether libCombine has been linked with each library.
 *
 * @return non-zero on success and zero if the filename could not be opened
 * for writing.
 *
 * @memberof CaWriter_t
 */
LIBCOMBINE_EXTERN
int
CaWriter_writeOMEX ( CaWriter_t         *sw,
                       const CaOmexManifest_t *d,
                       const char           *filename );

/**
 * Writes the given CaOmexManifest to filename.
 *
 * If the filename ends with @em .gz, the file will be compressed by @em gzip.
 * Similary, if the filename ends with @em .zip or @em .bz2, the file will be
 * compressed by @em zip or @em bzip2, respectively. Otherwise, the fill will be
 * uncompressed.
 *
 * @note To create a gzip/zip file, libCombine needs to be linked with zlib at 
 * compile time. Also, libCombine needs to be linked with bzip2 to create a bzip2 file.
 * File unwritable error will be logged and @c zero will be returned if a compressed 
 * file name is given and libCombine is not linked with the required library.
 * CaWriter_hasZlib() and CaWriter_hasBzip2() can be used to check whether
 * libCombine was linked with the library at compile time.
 *
 * @return non-zero on success and zero if the filename could not be opened
 * for writing.
 *
 * @memberof CaWriter_t
 */
LIBCOMBINE_EXTERN
int
CaWriter_writeOMEXToFile ( CaWriter_t         *sw,
                       const CaOmexManifest_t *d,
                       const char           *filename );


/**
 * Writes the given CaOmexManifest to an in-memory string and returns a
 * pointer to it.  The string is owned by the caller and should be freed
 * (with free()) when no longer needed.
 *
 * @return the string on success and @c NULL if one of the underlying parser
 * components fail (rare).
 *
 * @memberof CaWriter_t
 */
LIBCOMBINE_EXTERN
char *
CaWriter_writeOMEXToString (CaWriter_t *sw, const CaOmexManifest_t *d);


/**
 * Predicate returning @c non-zero or @c zero depending on whether
 * libCombine is linked with zlib at compile time.
 *
 * @return @c non-zero if zlib is linked, @c zero otherwise.
 *
 * @memberof CaWriter_t
 */
LIBCOMBINE_EXTERN
int
CaWriter_hasZlib ();


/**
 * Predicate returning @c non-zero or @c zero depending on whether
 * libCombine is linked with bzip2 at compile time.
 *
 * @return @c non-zero if bzip2 is linked, @c zero otherwise.
 *
 * @memberof CaWriter_t
 */
LIBCOMBINE_EXTERN
int
CaWriter_hasBzip2 ();

#endif  /* !SWIG */


/**
 * Writes the given CaOmexManifest @p d to the file named by @p filename.
 * This convenience function is functionally equivalent to:
 *
 *   CaWriter_writeOMEX(CaWriter_create(), d, filename);
 *
 * @htmlinclude assuming-compressed-file.html
 *
 * @param d the CaOmexManifest object to be written out in XML format
 * 
 * @param filename a string giving the path to a file where the XML
 * content is to be written.
 *
 * @return @c 1 on success and @c 0 (zero) if @p filename could not be
 * written.  Some possible reasons for failure include (a) being unable to
 * open the file, and (b) using a filename that indicates a compressed OMEX
 * file (i.e., a filename ending in <code>&quot;.zip&quot;</code> or
 * similar) when the compression functionality has not been enabled in
 * the underlying copy of libCombine.
 *
 * @see CaWriter::hasZlib()
 * @see CaWriter::hasBzip2()
 *
 * @if conly
 * @memberof CaWriter_t
 * @endif
 */
LIBCOMBINE_EXTERN
int
writeOMEX (const CaOmexManifest_t *d, const char *filename);


/**
 * Writes the given CaOmexManifest @p d to an in-memory string and returns a
 * pointer to it.  The string is owned by the caller and should be freed
 * (with free()) when no longer needed.  This convenience function is
 * functionally equivalent to:
 *
 *   CaWriter_writeOMEXToString(CaWriter_create(), d);
 *
 * but does not require the caller to create an CaWriter object first.
 *
 * @param d an CaOmexManifest object to be written out in XML format
 *
 * @return the string on success and @c NULL if one of the underlying parser
 * components fail.
 *
 * @if clike @warning Note that the string is owned by the caller and
 * should be freed after it is no longer needed.@endif@~
 *
 * @if conly
 * @memberof CaWriter_t
 * @endif
 */
LIBCOMBINE_EXTERN
char *
writeOMEXToString (const CaOmexManifest_t *d);


/**
 * Writes the given CaOmexManifest @p d to the file @p filename.
 * This convenience function is functionally equivalent to:
 *
 *   CaWriter_writeOMEXToFile(CaWriter_create(), d, filename);
 *
 * but that does not require the caller to create an CaWriter object first.
 *
 * @htmlinclude assuming-compressed-file.html
 * 
 * @param d an CaOmexManifest object to be written out in XML format
 *
 * @param filename a string giving the path to a file where the XML
 * content is to be written.
 *
 * @return @c 1 on success and @c 0 (zero) if @p filename could not be
 * written.  Some possible reasons for failure include (a) being unable to
 * open the file, and (b) using a filename that indicates a compressed Ca
 * file (i.e., a filename ending in <code>&quot;.zip&quot;</code> or
 * similar) when the compression functionality has not been enabled in
 * the underlying copy of libCombine.
 *
 * @if clike @warning Note that the string is owned by the caller and
 * should be freed (with the normal string <code>free()</code> C++
 * function) after it is no longer needed.@endif@~
 *
 * @see CaWriter::hasZlib()
 * @see CaWriter::hasBzip2()
 *
 * @if conly
 * @memberof CaWriter_t
 * @endif
 */
LIBCOMBINE_EXTERN
int
writeOMEXToFile (const CaOmexManifest_t *d, const char *filename);


END_C_DECLS
LIBCOMBINE_CPP_NAMESPACE_END

#endif  /* CaWriter_h */
