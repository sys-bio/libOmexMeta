/**
 * @file combinearchive.h
 * @brief Definition of the CombineArchive class.
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
 * @class CombineArchive
 */

#ifndef LIBCOMBINE_COMBINEARCHIVE_H
#define LIBCOMBINE_COMBINEARCHIVE_H

#include <string>
#include <list>
#include <map>
#include <fstream>

#include <omex/common/extern.h>

#include <combine/omexdescription.h>

#ifdef __cplusplus

namespace  zipper {
  class Zipper;
  class Unzipper;
}

LIBCOMBINE_CPP_NAMESPACE_BEGIN

class CaOmexManifest;
class CaContent;

class LIBCOMBINE_EXTERN CombineArchive
{
public:

  /**
   * Constructs a new COMBINE archive.
   */
  CombineArchive();

  /**
   * Desctructor, also clears all variables by calling cleanUp()
   */
  ~CombineArchive();

  /**
   * Adds a new file to the archive.
   *
   * @param fileName the file to be added
   * @param targetName the target name of the file in the archive
   * @param format the format that this file has
   * @param isMaster boolean indicating whether the file should be
   *        opened first if there are multiple ones.
   *
   * @return boolean indicating success or failure
   */
  bool addFile(const std::string& fileName,
               const std::string& targetName,
               const std::string& format,
               bool isMaster = false);

  /**
   * Adds the contents of the stream to the archive.
   *
   * @param stream input stream with the data.
   * @param targetName the target name of the file in the archive
   * @param format the format that this file has
   * @param isMaster boolean indicating whether the file should be
   *        opened first if there are multiple ones.
   *
   * @return boolean indicating success or failure
   */
  bool addFile(std::istream& stream,
               const std::string& targetName,
               const std::string& format,
               bool isMaster = false);

  /**
   * Adds the given string to the archive.
   *
   * @param content the content of the file to be added to the archive.
   * @param targetName the target name of the file in the archive
   * @param format the format that this file has
   * @param isMaster boolean indicating whether the file should be
   *        opened first if there are multiple ones.
   *
   * @return boolean indicating success or failure
   */
  bool addFileFromString(const std::string& content,
               const std::string& targetName,
               const std::string& format,
               bool isMaster = false);
  /**
   * Adds the given metadata to the list.
   *
   * @param targetName the name of the entry that the metadata is about
   * @param description the metadata description
   */
  void addMetadata(const std::string& targetName,
                   const OmexDescription& description);

  /**
   * extracts the content from the entry with the given name
   *
   * @param name the entry to be extracted
   * @param destination optional filename or folder to save the entry under.
   *        If a folder is given, the file will be saved as folder + "/" + name.
   *        If the argument is left blank the file will be written into
   *        "./" + name.
   *
   * @return boolean indicating success or failure.
   */
  bool extractEntry(const std::string& name,
                    const std::string& destination = std::string());

  /**
   * extracts the entry into the given outptu stream.
   *
   * @param name of the entry to be extracted
   * @param stream the stream into which to write the contents of the file
   *
   * @return boolean indicating success or failure.
   */
  bool extractEntryToStream(const std::string& name,
                            std::ostream& stream);

  /**
   * extracts the given entry and returns the contents as string.
   *
   * @param name the entry to be extracted
   *
   * @return the content of the entry, or empty if not found.
   */
  std::string extractEntryToString(const std::string& name);

  /**
   * extracts all entries in this archive into the given directory.
   *
   * @param directory the directory into which to extract the archive.
   *
   * @return boolean indicating success or failure.
   */
  bool extractTo(const std::string& directory);

  /**
   * initializes this archive with all the content from the given directory
   *
   * @param directory the directory, from which all files will be added
   *        recursively to this archive. (excluding a file called "manifest.xml").
   *
   * @return boolean indicating success or failure
   */
  bool initializeFromDirectory(const std::string& directory);

  /**
   * initializes this instance from the given Combine archive
   *
   * @param archiveFile the combine archive file
   *
   * @return boolean indicating success or failure
   */
  bool initializeFromArchive(const std::string& archiveFile);

  /**
   * @return the manifest
   */
  const CaOmexManifest *getManifest() const;

  /**
   * @return the manifest
   */
  CaOmexManifest *getManifest();

  /**
   * @return returns the first master file or NULL
   */
  const CaContent *getMasterFile() const;

  /**
   * returns the first master file with given format key
   *
   * @param formatKey the format key
   *
   * @return returns the first master file with the key or NULL
   */
  const CaContent *getMasterFile(const std::string& formatKey) const;

  /**
   * returns the first entry with the given format key
   *
   * @param formatKey the key
   *
   * @return the entry with the given format, or NULL
   */
  const CaContent *getEntryByFormat(const std::string &formatKey) const;

  /**
   * returns the first entry with the location
   *
   * @param location the location
   *
   * @return the entry with the given location, or NULL
   */
  const CaContent *getEntryByLocation(const std::string &location) const;

  /**
   * @return a std::vector of all locations in this archive.
   */
  std::vector<std::string> getAllLocations() const;

  /**
   * @return number of entries in the archive
   */
  int getNumEntries() const;

  /**
  * returns the entry at the given index
  *
  * @param index the element to get
  *
  * @return the entry with the given index, or NULL
  */
  const CaContent *getEntry(int index) const;


  /**
   * returns the metadata for the given location if it does not exist
   * an empty description will be returned.
   *
   * @param location the location
   *
   * @return the metadata object if found (otherwise it will be empty)
   */
  OmexDescription getMetadataForLocation(const std::string& location) const;

  /**
   * Sets the manifest to the given value
   *
   * @param value the manifest
   */
  void setManifest(CaOmexManifest *value);

  /**
   * @brief cleanUp resets this class (removes tempfiles, clears map and metadata)
   * @return
   */
  bool cleanUp();

  /**
   * writes the archive to the file
   *
   * @param fileName the filename
   *
   * @return true, in case of success
   */
  bool writeToFile(const std::string& fileName);

  /**
   * returns the stream for the given name
   *
   * @param name the name that should be in the current map of files
   * @param stream the stream for the found entry
   *
   * @return true if the name is found, false otherwise
   */

  bool getStream(const  std::string& name,
                 std::ifstream& stream);

protected:
  /**
   * the manifest
   */
  CaOmexManifest* mpManifest;

  /**
   * a map between the names of the files in this archive and
   * the actual file names on the disc. In case a combine
   * archive was opened, this filename will be prefixed with
   * "unzipper://" to indicate that the file is to be read from
   * the unzipper pointer.
   */
  std::map<std::string, std::string> mMap;

  /**
   * a map between entries in this archive and metadata
   * descriptions for them.
   */
  std::map<std::string, OmexDescription> mMetadataMap;

  /**
   * an unzipper instance, that is used to extract data files.
   */
  zipper::Unzipper* mpUnzipper;

  /**
   * a vector of temporary files that have been created in
   * the process of working on the archive. They will be deleted
   * automatically upon destruction of the instance.
   */
  std::vector<std::string> mTempFiles;

  /**
   * returns the next filename that is not yet in the archive
   * with the given prefix and suffix (defaults to .xml)
   *
   * @param prefix the prefix for the file
   * @param suffix the suffix
   *
   * @return the next filename that is not yet in the archive
   */
  std::string getNextFilename(const std::string& prefix,
                              const std::string &suffix = ".xml");


  /**
   * adds the given description to the zip archive (and the manifest).
   * the entry will be skipped if it is empty.
   *
   * @param desc the description to be added
   * @param zipper the zipper to be used
   */
  void addMetadataToArchive(OmexDescription& desc, zipper::Zipper* zipper);
};

LIBCOMBINE_CPP_NAMESPACE_END

#endif  /* __cplusplus */

#endif  /* LIBCOMBINE_COMBINEARCHIVE_H */
