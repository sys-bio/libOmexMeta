#include <combine/combinearchive.h>
#include <combine/knownformats.h>
#include <combine/util.h>

#include <omex/CaOmexManifest.h>
#include <omex/CaContent.h>
#include <omex/CaReader.h>
#include <omex/CaWriter.h>

#include <zipper/zipper.h>
#include <zipper/tools.h>
#include <zipper/unzipper.h>

#include <fstream>
#include <sstream>
#include <cstdio>

using namespace zipper;
LIBCOMBINE_CPP_NAMESPACE_USE

CombineArchive::CombineArchive()
  : mpManifest(NULL)
  , mMap()
  , mMetadataMap()
  , mpUnzipper(NULL)
  , mTempFiles()
{
}

CombineArchive::~CombineArchive()
{
  cleanUp();
  // TODO: delete files if we extracted things somewhere
}

bool
CombineArchive::extractTo(const std::string &directory)
{
  if (mpUnzipper != NULL)
  {
    return mpUnzipper->extract(directory);
  }

  return true;
}

bool
CombineArchive::initializeFromDirectory(const std::string &directory)
{
  return true;
}

bool
CombineArchive::initializeFromArchive(
    const std::string &archiveFile)
{
  cleanUp();

  try 
  {
    mpUnzipper = new Unzipper(archiveFile);
  }
  catch (const std::exception&)
  {
    // invalid COMBINE archive, it should always have a manifest
    cleanUp();
    return false;
  }

  // now build the map of all files in the archive
  std::vector<zipper::ZipEntry> entries = mpUnzipper->entries();
  for (std::vector<zipper::ZipEntry>::iterator it = entries.begin(); 
       it != entries.end(); ++it)
  {
    mMap[(*it).name] = "unzipper://" + (*it).name;
  }

  if (mMap.find("manifest.xml") == mMap.end())
  {
    // invalid COMBINE archive, it should always have a manifest
    cleanUp();
    return false;
  }

  // read manifest
  std::ostringstream manifest;
  mpUnzipper->extractEntryToStream("manifest.xml", manifest);
  mpManifest = readOMEXFromString(manifest.str().c_str());

  if (mpManifest == NULL)
  {
    // invalid COMBINE archive, it should always have a valid manifest
    cleanUp();
    return false;
  }

  // remove the actual manifest entry from the manifest
  for (unsigned int i = 0; i < mpManifest->getNumContents(); ++i)
  {
    CaContent* current = mpManifest->getContent(i);
    if (current->getLocation() != ".")
      continue;

    mpManifest->removeContent(i);
    break;
  }
  mMap.erase("manifest.xml");

  // now go through the list again and extract all metadata
  // elements from the content list, leaving only those that
  // do not conform to the OmexMetadata
  unsigned int numContents = mpManifest->getNumContents();
  for (unsigned int i = numContents; i >= 1; --i)
  {
    CaContent* current = mpManifest->getContent(i-1);
    if ( current == NULL || !current->isFormat("omex"))
      continue;

    std::vector<OmexDescription> descriptions =
        OmexDescription::parseString(extractEntryToString(current->getLocation()));

    if (descriptions.empty())
      continue;

    bool added = false;
    std::vector<OmexDescription>::iterator it = descriptions.begin();
    for (; it != descriptions.end(); ++it)
    {
      if (!it->isEmpty())
      {
        mMetadataMap[it->getAbout()]  = *it;
        added = true;
      }
    }

    if (added)
    {
      delete mpManifest->removeContent(i-1);
    }

  }

  return true;
}

bool CombineArchive::cleanUp()
{
  mMap.clear();
  mMetadataMap.clear();

  if (mpUnzipper != NULL)
  {
    delete mpUnzipper;
    mpUnzipper = NULL;
  }

  if (mpManifest != NULL)
  {
    delete mpManifest;
    mpManifest = NULL;
  }

  for(std::vector<std::string>::iterator it = mTempFiles.begin(); 
      it != mTempFiles.end(); ++it)
  {
    std::remove((*it).c_str());
  }

  mTempFiles.clear();

  return true;
}

std::string CombineArchive::getNextFilename(const std::string& prefix,
                                            const std::string& suffix)
{
  std::string fileName = prefix + suffix;
  int count = 0;
  while (getEntryByLocation(fileName) != NULL)
  {
    std::stringstream nameStream;
    nameStream << prefix << "_" << ++count << suffix;
    fileName = nameStream.str();
  }

  return fileName;
}

void CombineArchive::addMetadataToArchive(OmexDescription& desc, Zipper *zipper)
{
  if (desc.isEmpty() || zipper == NULL || mpManifest == NULL)
    return;

  std::string fileName = getNextFilename("metadata", ".rdf");
  std::stringstream content; content << desc.toXML();
  zipper->add(content, fileName);

  CaContent* entry = mpManifest->createContent();
  entry->setLocation(fileName);
  entry->setFormat(KnownFormats::lookupFormat("omex"));
  entry->setMaster(false);

}

bool CombineArchive::writeToFile(const std::string &fileName)
{
  if (mpManifest == NULL)
    return false;

  Zipper zipper(fileName);
  zipper.open();

  bool foundIdentity = false;

  // add all files
  for(unsigned int i = 0; i < mpManifest->getNumContents(); ++i)
  {
    const CaContent* entry = mpManifest->getContent(i);
    std::string targetName = entry->getLocation();
    if (targetName == ".")
    {
      // skip manifest for now (will be generated below)
      foundIdentity = true;
      continue;
    }

    const std::string& sourceFile = mMap[targetName];

    if (targetName.find("./") == 0)
      targetName = targetName.substr(2);

    if (targetName.find("/") == 0)
      targetName = targetName.substr(1);

    std::ifstream in(sourceFile.c_str(), std::ios::binary);
    zipper.add(in, targetName);
    in.close();
  }

  // add an entry for the manifest
  if (!foundIdentity)
  {
    CaContent* manifest = mpManifest->createContent();
    manifest->setLocation(".");
    manifest->setFormat("http://identifiers.org/combine.specifications/omex");
  }

  // add metadata elements

  // add the main metadata information first if existing.
  std::map<std::string, OmexDescription>::iterator it = mMetadataMap.find(".");
  if (it != mMetadataMap.end())
  {
    addMetadataToArchive(it->second, &zipper);
  }

  it = mMetadataMap.begin();
  for (; it != mMetadataMap.end(); ++it)
  {
    if (it->first == ".")
      continue;

    addMetadataToArchive(it->second, &zipper);
  }

  // add manifest
  std::stringstream str; str << writeOMEXToStdString(mpManifest);
  zipper.add(str, "manifest.xml");

  zipper.close();
  return true;
}

bool
CombineArchive::getStream(const std::string &name,
                          std::ifstream &stream)
{
  std::map<std::string, std::string>::iterator it = mMap.find(name);
  if (it == mMap.end()) 
  {
    if (name.find("./") == 0)
      it = mMap.find(name.substr(2));
    if (it == mMap.end())
    {
      if (name.find("/") == 0)
        it = mMap.find(name.substr(1));
      if (it == mMap.end())
        return false;
    }
  }

  std::string filename = (*it).second;
  if (filename.find("unzipper://") == 0)
  {
    filename = filename.substr(std::string("unzipper://").length());
    if (mpUnzipper == NULL) return false;
    std::string tempFile = Util::getTempFilename();
    std::ofstream tempStream(tempFile.c_str(), std::ios::out | std::ios::binary);
    bool result = mpUnzipper->extractEntryToStream(filename, tempStream);
    tempStream.close();
    if (!result)
    {
      std::remove(tempFile.c_str());
      return false;
    }

    mTempFiles.push_back(tempFile);
    filename = tempFile;
  }
  
  stream.open(filename.c_str(), std::ios::binary);
   
  return true;
}

const CaOmexManifest *
CombineArchive::getManifest() const
{
  return mpManifest;
}

CaOmexManifest *
CombineArchive::getManifest()
{
  return mpManifest;
}

const CaContent *
CombineArchive::getMasterFile() const
{
  if (mpManifest == NULL) return NULL;

  for (unsigned int i = 0;i < mpManifest->getNumContents(); ++i)
  {
    const CaContent* current = mpManifest->getContent(i);
    if (current->isSetMaster() && current->getMaster())
      return current;
  }

  return NULL;
}

const CaContent *
CombineArchive::getMasterFile(const std::string &formatKey) const
{
  if (mpManifest == NULL) return NULL;

  for (unsigned int i = 0;i < mpManifest->getNumContents(); ++i)
  {
    const CaContent* current = mpManifest->getContent(i);
    if (current->isSetMaster() && current->getMaster() &&
        KnownFormats::isFormat(formatKey, current->getFormat()))
      return current;
  }

  return NULL;
}

const CaContent *
CombineArchive::getEntryByFormat(const std::string &formatKey) const
{
  if (mpManifest == NULL) return NULL;

  for (unsigned int i = 0;i < mpManifest->getNumContents(); ++i)
  {
    const CaContent* current = mpManifest->getContent(i);
    if (KnownFormats::isFormat(formatKey, current->getFormat()))
      return current;
  }

  return NULL;
}

const CaContent *
CombineArchive::getEntryByLocation(const std::string &location) const
{
  if (mpManifest == NULL) return NULL;

  for (unsigned int i = 0;i < mpManifest->getNumContents(); ++i)
  {
    const CaContent* current = mpManifest->getContent(i);
    if (current->getLocation() == location ||
        current->getLocation() == "./" + location ||
        (location.find("./") == 0 && current->getLocation() == location.substr(2)) ||
        (location.find("/") == 0 && current->getLocation() == location.substr(1)) )
      return current;
  }

  return NULL;
}

std::vector<std::string>
CombineArchive::getAllLocations() const
{
  std::vector<std::string> result;

  if (mpManifest == NULL)
    return result;

  for (unsigned int i = 0; i < mpManifest->getNumContents(); ++i)
    result.push_back(mpManifest->getContent(i)->getLocation());

  return result;
}

int 
CombineArchive::getNumEntries() const
{
  if (mpManifest == NULL) return 0;
  return mpManifest->getNumContents();
}

const CaContent * 
CombineArchive::getEntry(int index) const
{
  if (mpManifest == NULL) return NULL;
  return mpManifest->getContent(index);
}

OmexDescription
CombineArchive::getMetadataForLocation(const std::string &location) const
{
  std::map<std::string, OmexDescription>::const_iterator it = mMetadataMap.find(location);
  if (it != mMetadataMap.end())
    return it->second;

  return OmexDescription();
}

void
CombineArchive::setManifest(CaOmexManifest *value)
{
  cleanUp();

  mpManifest = value;
}

bool
CombineArchive::addFile(const std::string &fileName,
                        const std::string &targetName,
                        const std::string &format,
                        bool isMaster)
{
  if (mpManifest == NULL)
  {
    mpManifest = new CaOmexManifest();
  }

  CaContent* content = mpManifest->createContent();
  content->setLocation(targetName);
  content->setFormat(format);
  content->setMaster(isMaster);

  mMap[targetName] = fileName;

  return true;
}

bool 
CombineArchive::addFileFromString(const std::string& content,
                                  const std::string& targetName,
                                  const std::string& format,
                                  bool isMaster)
{
   std::stringstream str; str << content;
   return addFile(str, targetName, format, isMaster);
}

bool
CombineArchive::addFile(std::istream &stream,
                        const std::string &targetName,
                        const std::string &format,
                        bool isMaster)
{
  std::string tempFilename = Util::getTempFilename();
  mTempFiles.push_back(tempFilename);

  std::ofstream out(tempFilename.c_str(), std::ios::out | std::ios::binary);
  Util::copyStream(stream, out);

  return addFile(tempFilename, targetName, format, isMaster);
}

void
CombineArchive::addMetadata(const std::string &targetName,
                            const OmexDescription &description)
{
  mMetadataMap[targetName] = description;
}

bool
CombineArchive::extractEntry(const std::string &name,
                             const std::string &destination)
{
  std::string target(destination);
  if (target.empty())
    target = "./" + name;
  if (isDirectory(target))
    target += "/" + name;

  std::ofstream stream(target.c_str(), std::ios::out | std::ios::binary);
  bool result = extractEntryToStream(name, stream);
  stream.close();
  return result;
}

bool
CombineArchive::extractEntryToStream(const std::string& name,
                                     std::ostream& stream)
{
  std::ifstream in;
  if (!getStream(name, in))
    return false;

  Util::copyStream(in, stream);
  in.close();

  return true;
}

std::string
CombineArchive::extractEntryToString(const std::string& name)
{
  std::ostringstream stream;
  extractEntryToStream(name, stream);
  return stream.str();
}
