using System;
using libcombinecs;

namespace PrintExample
{
  class Program
  {
    
    
    static void PrintMetaDataFor(CombineArchive archive, string location)
    {
      OmexDescription desc = archive.getMetadataForLocation(location);
      if (desc.isEmpty())
      {
        Console.WriteLine("  no metadata for '{0}'",location);
        return;
      }
      Console.WriteLine("  metadata for '{0}':", location);
      Console.WriteLine("     Created : {0}", desc.getCreated().getDateAsString());
      for (int i = 0; i < desc.getNumModified(); ++i)
      {
        Console.WriteLine("     Modified : {0}", desc.getModified(i).getDateAsString());
      }
    
      Console.WriteLine("     # Creators: {0}", desc.getNumCreators());
      for (int i = 0; i < desc.getNumCreators(); ++i)
      {
        VCard creator = desc.getCreator(i);
        Console.WriteLine("       {0} {1}", creator.getGivenName(), creator.getFamilyName());
      }
    
    }
    
    static void Main(string[] args)
    {
      if (args.Length < 1)
      {
        Console.WriteLine("usage: PrintExample archive-file");
        return;
      }
      var archive = new CombineArchive();
      if (!archive.initializeFromArchive(args[0]))
      {
        Console.WriteLine("Invalid Combine Archive");
        return;
      }
      
      PrintMetaDataFor(archive, ".");
      
      Console.WriteLine("Num Entries: {0}", archive.getNumEntries());
      
      for (int i = 0; i < archive.getNumEntries(); ++i)
      {
        CaContent entry = archive.getEntry(i);
        
        Console.WriteLine(" {0}: location: {1} format: {2}", i, entry.getLocation(), entry.getFormat());
        PrintMetaDataFor(archive, entry.getLocation());
      
        // the entry could now be extracted via 
        // archive.extractEntry(entry.getLocation(), <filename or folder>)
      
        // or used as string
        // string content = archive.extractEntryToString(entry.getLocation());
      
      }
      
      archive.cleanUp();
    }
  }
}
