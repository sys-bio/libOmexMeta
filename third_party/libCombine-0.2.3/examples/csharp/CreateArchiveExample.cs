using System;
using libcombinecs;

namespace CreateArchiveExample
{
  class Program
  {
    static void Main(string[] args)
    {
      if (args.Length < 1)
      {
        Console.WriteLine("usage: CreateArchiveExample sbml-file");
        return;
      }
      var archive = new CombineArchive();
      archive.addFile(
            args[0], // filename
            "./models/model.xml", // target file name
            KnownFormats.lookupFormat("sbml"), // look up identifier for SBML models
            true // mark file as master
            );

      var description = new OmexDescription();
      description.setAbout("."); // about the archive itself
      description.setDescription("Simple test archive including one SBML model");
      description.setCreated(OmexDescription.getCurrentDateAndTime());

      var creator = new VCard();
      creator.setFamilyName("Bergmann");
      creator.setGivenName("Frank");
      creator.setEmail("fbergman@caltech.edu");
      creator.setOrganization("Caltech");

      description.addCreator(creator);

      archive.addMetadata(".", description);

      archive.writeToFile("out.omex");
    }
  }
}
