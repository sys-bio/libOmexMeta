/**
 * @file CaReader.cpp
 * @brief Implementation of the CaReader class.
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


#include <sbml/xml/XMLError.h>
#include <sbml/xml/XMLErrorLog.h>
#include <sbml/xml/XMLInputStream.h>

#include <omex/CaErrorLog.h>
#include <omex/CaVisitor.h>
#include <omex/CaOmexManifest.h>
#include <omex/CaError.h>
#include <omex/CaReader.h>

#include <sbml/compress/CompressCommon.h>
#include <sbml/compress/InputDecompressor.h>

/** @cond doxygenIgnored */

using namespace std;

/** @endcond */

LIBCOMBINE_CPP_NAMESPACE_BEGIN

#ifdef __cplusplus

/*
 * Creates a new CaReader and returns it. 
 */
CaReader::CaReader ()
{
}


/*
 * Destorys this CaReader.
 */
CaReader::~CaReader ()
{
}


/*
 * Reads an Ca document from the given file.  If filename does not exist
 * or is not an Ca file, an error will be logged.  Errors can be
 * identified by their unique ids, e.g.:
 *
 * If the filename ends with @em .gz, the file will be read as a @em gzip file.
 * Similary, if the filename ends with @em .zip or @em .bz2, the file will be
 * read as a @em zip or @em bzip2 file, respectively. Otherwise, the fill will be
 * read as an uncompressed file.
 * If the filename ends with @em .zip, only the first file in the archive will
 * be read if the zip archive contains two or more files.
 *
 * To read a gzip/zip file, underlying libCombine needs to be linked with zlib
 * at compile time. Also, underlying libCombine needs to be linked with bzip2 
 * to read a bzip2 file. File unreadable error will be logged if a compressed 
 * file name is given and underlying libCombine is not linked with the corresponding 
 * required library.
 * CaReader::hasZlib() and CaReader::hasBzip2() can be used to check 
 * whether libCombine is linked with each library.
 * 
 * @return a pointer to the CaOmexManifest read.
 */
CaOmexManifest*
CaReader::readOMEX (const std::string& filename)
{
  return readInternal(filename.c_str(), true);
}


/*
 * Reads an Ca document from the given filename.
 */
CaOmexManifest*
CaReader::readOMEXFromFile (const std::string& filename)
{
  return readInternal(filename.c_str(), true);
}


/*
 * Reads an Ca document from the given XML string.
 *
 * If the string does not begin with XML declaration:
 *
 *   <?xml version='1.0' encoding='UTF-8'?>
 *
 * it will be prepended.
 *
 * This method will log a fatal error if the XML string is not Ca.  See
 * the method documentation for readOMEX(filename) for example error
 * checking code.
 *
 * @return a pointer to the CaOmexManifest read.
 */
CaOmexManifest*
CaReader::readOMEXFromString (const std::string& xml)
{
  const static string dummy_xml ("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");  
  
  if (!strncmp(xml.c_str(), dummy_xml.c_str(), 14))
  {
    return readInternal(xml.c_str(), false);
  }
  else
  {
    const std::string temp = (dummy_xml + xml);
    return readInternal(temp.c_str(), false);
  }
}


/*
 * Predicate returning @c true if
 * libCombine is linked with zlib.
 *
 * @return @c true if libCombine is linked with zlib, @c false otherwise.
 */
bool 
CaReader::hasZlib() 
{
  return LIBCOMBINE_CPP_NAMESPACE ::hasZlib();
}


/*
 * Predicate returning @c true if
 * libCombine is linked with bzip2.
 *
 * @return @c true if libCombine is linked with bzip2, @c false otherwise.
 */
bool 
CaReader::hasBzip2() 
{
  return LIBCOMBINE_CPP_NAMESPACE ::hasBzip2();
}


/** @cond doxygenLibomexInternal */
static bool
isCriticalError(const unsigned int errorId)
{
  switch (errorId)
  {
  case InternalXMLParserError:
  case UnrecognizedXMLParserCode:
  case XMLTranscoderError:
  case BadlyFormedXML:
  case InvalidXMLConstruct:
  case UnclosedXMLToken:
  case XMLTagMismatch:
  case BadXMLPrefix:
  case MissingXMLAttributeValue:
  case BadXMLComment:
  case XMLUnexpectedEOF:
  case UninterpretableXMLContent:
  case BadXMLDocumentStructure:
  case InvalidAfterXMLContent:
  case XMLExpectedQuotedString:
  case XMLEmptyValueNotPermitted:
  case MissingXMLElements:
  case BadXMLDeclLocation:
    return true;

  default:
    return false;
  }
}
/** @endcond */


/** @cond doxygenLibomexInternal */
/*
 * Used by readOMEX() and readOMEXFromString().
 */
CaOmexManifest*
CaReader::readInternal (const char* content, bool isFile)
{
  CaOmexManifest* d = new CaOmexManifest();

  if (isFile && content != NULL && (util_file_exists(content) == false))
  {
    d->getErrorLog()->logError(XMLFileUnreadable);
  }
  else 
  {
    XMLInputStream stream(content, isFile, "", d->getErrorLog());

    if (stream.peek().isStart() && stream.peek().getName() != "OmexManifest")
    {
      // the root element ought to be an omex element. 
      d->getErrorLog()->logError(CaNotSchemaConformant);
	  return d;
    }
	
    d->read(stream);
    
    if (stream.isError())
    {
      // If we encountered an error, some parsers will report it sooner
      // than others.  Unfortunately, those that fail sooner do it in an
      // opaque call, so we can't change the behavior.  Since we don't want
      // different parsers to report different validation errors, we bring
      // all parsers back to the same point.

      for (unsigned int i = 0; i < d->getNumErrors(); ++i)      
      {
        if (isCriticalError(d->getError(i)->getErrorId()))
        {
          // If we find even one critical error, all other errors are
          // suspect and may be bogus.  Remove them.

          for (int n = (int)d->getNumErrors()-1; n >= 0; --n)
            if (!isCriticalError(d->getError((unsigned int)n)->getErrorId()))
            {
              d->getErrorLog()->remove(d->getError((unsigned int)n)->getErrorId());
            }

          break;
        }
      }
    }
    else
    {
      // Low-level XML errors will have been caught in the first read,
      // before we even attempt to interpret the content as Ca.  Here
      // we want to start checking some basic Ca-level errors.

      if (stream.getEncoding() == "")
      {
        d->getErrorLog()->logError(MissingXMLEncoding);
      }
      else if (strcmp_insensitive(stream.getEncoding().c_str(), "UTF-8") != 0)
      {
        d->getErrorLog()->logError(CaNotUTF8);
      }

      if (stream.getVersion() == "")
      {
        d->getErrorLog()->logError(BadXMLDecl);
      }
      else if (strcmp_insensitive(stream.getVersion().c_str(), "1.0") != 0)
      {
        d->getErrorLog()->logError(BadXMLDecl);
      }
    }
  }
  return d;
}
/** @endcond */


#endif /* __cplusplus */
/** @cond doxygenIgnored */
LIBCOMBINE_EXTERN
CaReader_t *
CaReader_create ()
{
  return new (nothrow) CaReader;
}


LIBCOMBINE_EXTERN
void
CaReader_free (CaReader_t *sr)
{
  delete sr;
}


LIBCOMBINE_EXTERN
CaOmexManifest_t *
CaReader_readOMEX (CaReader_t *sr, const char *filename)
{
  if (sr != NULL)
    return (filename != NULL) ? sr->readOMEX(filename) : sr->readOMEX("");
  else
    return NULL;
}


LIBCOMBINE_EXTERN
CaOmexManifest_t *
CaReader_readOMEXFromFile (CaReader_t *sr, const char *filename)
{
  if (sr != NULL)
    return (filename != NULL) ? sr->readOMEX(filename) : sr->readOMEX("");
  else
    return NULL;
}


LIBCOMBINE_EXTERN
CaOmexManifest_t *
CaReader_readOMEXFromString (CaReader_t *sr, const char *xml)
{
  if (sr != NULL)
    return (xml != NULL) ? sr->readOMEXFromString(xml) :
                         sr->readOMEXFromString("");
  else
    return NULL;
}


LIBCOMBINE_EXTERN
int
CaReader_hasZlib (void)
{
  return static_cast<int>( CaReader::hasZlib() );
}


LIBCOMBINE_EXTERN
int
CaReader_hasBzip2 (void)
{
  return static_cast<int>( CaReader::hasBzip2() );
}


LIBCOMBINE_EXTERN
CaOmexManifest_t *
readOMEX (const char *filename)
{
  CaReader sr;
  return (filename != NULL) ? sr.readOMEX(filename) : sr.readOMEX("");
}


LIBCOMBINE_EXTERN
CaOmexManifest_t *
readOMEXFromFile (const char *filename)
{
  CaReader sr;
  return (filename != NULL) ? sr.readOMEX(filename) : sr.readOMEX("");
}


LIBCOMBINE_EXTERN
CaOmexManifest_t *
readOMEXFromString (const char *xml)
{
  CaReader sr;
  return (xml != NULL) ? sr.readOMEXFromString(xml) : sr.readOMEXFromString("");
}

LIBCOMBINE_CPP_NAMESPACE_END
/** @endcond */

