#include <iostream>

#include <omex/common/libcombine-namespace.h>

#include <combine/combinearchive.h>
#include <combine/knownformats.h>
#include <combine/omexdescription.h>
#include <combine/vcard.h>

using namespace std;
LIBCOMBINE_CPP_NAMESPACE_USE


int main(int argc, const char* argv[])
{
  if (argc < 2)
  {
    cout << "usage: create_archive sbml-file" << endl;
    return 1;
  }
  
  CombineArchive archive;

  archive.addFile(
        argv[1], // existing filename
        "./models/model.xml", // filename in the archive
        KnownFormats::lookupFormat("sbml"), // look up the format for sbml files
        true // mark this file as the default to be opened
        );

  OmexDescription description;
  description.setAbout("."); // about the archive itself
  description.setDescription("Simple test archive including one SBML model");
  description.setCreated(OmexDescription::getCurrentDateAndTime());

  VCard creator;
  creator.setFamilyName("Bergmann");
  creator.setGivenName("Frank");
  creator.setEmail("fbergman@caltech.edu");
  creator.setOrganization("Caltech");

  description.addCreator(creator);

  archive.addMetadata(".", description);

  archive.writeToFile("out.omex");

  archive.cleanUp();

}
