#include <iostream>

#include <omex/common/libcombine-namespace.h>

#include <combine/combinearchive.h>
#include <combine/knownformats.h>
#include <combine/omexdescription.h>
#include <combine/vcard.h>

#include <omex/CaContent.h>


using namespace std;
LIBCOMBINE_CPP_NAMESPACE_USE


void printMetaDataFor(const CombineArchive& archive, const std::string& location)
{
  OmexDescription desc = archive.getMetadataForLocation(location);
  if (desc.isEmpty())
  {
    cout << "  no metadata for '" << location << "'" << endl;
    return;
  }
  cout << "  metadata for '" << location << "':" << endl;
  cout << "     Created : " << desc.getCreated().getDateAsString() <<endl;
  for (unsigned int i = 0; i < desc.getNumModified(); ++i)
  {
    cout << "     Modified : " <<  desc.getModified(i).getDateAsString() << endl;
  }

  cout << "     # Creators: " << desc.getNumCreators() << endl;
  for (unsigned int i = 0; i < desc.getNumCreators(); ++i)
  {
    VCard creator = desc.getCreator(i);
    cout << "       " << creator.getGivenName() << " " << creator.getFamilyName() << endl;
  }

}

int main(int argc, const char* argv[])
{
  if (argc < 2)
  {
    cout << "usage: print_archive archive-file" << endl;
    return 1;
  }

  CombineArchive archive;

  if (!archive.initializeFromArchive(argv[1]))
  {
    cerr << "Invalid Combine Archive" << endl;
    return 1;
  }

  printMetaDataFor(archive, ".");

  cout << "Num Entries: " << archive.getNumEntries();

  for (int i = 0; i < archive.getNumEntries(); ++i)
  {
    const CaContent* entry = archive.getEntry(i);
    cout << " " << i << ": location: " << entry->getLocation() << " format: " << entry->getFormat() << endl;
    printMetaDataFor(archive, entry->getLocation());

    // the entry could now be extracted via 
    // archive.extractEntry(entry->getLocation(), <filename or folder>)

    // or used as string
    // std::string content = archive.extractEntryToString(entry->getLocation());

  }

  archive.cleanUp();

}
