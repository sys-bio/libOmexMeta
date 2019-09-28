# include <semsim/SemSim.h>

# include "combine/combinearchive.h"
# include "combine/knownformats.h"
# include "combine/omexdescription.h"
# include "omex/CaContent.h"

# include <iostream>

using namespace semsim;

int main(int argc, char *argv[]) {
  if (argc < 1)
    throw std::runtime_error("Usage: list_omex filename");

  LIBCOMBINE_CPP_NAMESPACE_QUALIFIER CombineArchive archive;

  if (!archive.initializeFromArchive(argv[1]))
  {
    std::cerr << "Invalid Combine Archive" << "\n";
    return 1;
  }

  for (int i = 0; i < archive.getNumEntries(); ++i)
  {
    const LIBCOMBINE_CPP_NAMESPACE_QUALIFIER CaContent* entry = archive.getEntry(i);
    if (entry->getFormat().find( "http://identifiers.org/combine.specifications/sbml") == 0 ||
        entry->getFormat().find("https://identifiers.org/combine.specifications/sbml") == 0) {
      std::cout << "  " << entry->getLocation() << ": " << entry->getFormat() << "\n";
    }

    // the entry could now be extracted via
    // archive.extractEntry(entry->getLocation(), <filename or folder>)

    // or used as string
    // std::string content = archive.extractEntryToString(entry->getLocation());

  }

  archive.cleanUp();

  return 0;
}
