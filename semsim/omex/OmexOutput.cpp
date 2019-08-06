# include "semsim/omex/OmexOutput.h"

# include "combine/combinearchive.h"
# include "combine/knownformats.h"
# include "combine/omexdescription.h"

namespace semsim {
    void exportToOmex(const Model& model, const std::string& archive_path, const std::string& model_entry_path, const std::string& rdf_entry_path) {
      LIBCOMBINE_CPP_NAMESPACE_QUALIFIER CombineArchive archive;

      {
        std::stringstream s;
        s << model.encodeXML(), // get model xml
        archive.addFile(
              s, // buffer with xml contents
              model_entry_path, // entry path in the archive
              LIBCOMBINE_CPP_NAMESPACE_QUALIFIER KnownFormats::lookupFormat(model.getFormat()), // look up the format for xml files
              true // master attribute - mark this file as the default to be opened
              );
      }

      {
        std::stringstream s;
        s << model.getRDF(model_entry_path), // get model annotation rdf
        archive.addFile(
              s, // buffer with rdf/xml contents
              rdf_entry_path, // entry path in the archive
              "application/rdf+xml", // TODO: check correct format
              false // master attribute
              );
      }

      LIBCOMBINE_CPP_NAMESPACE_QUALIFIER OmexDescription description;
      description.setAbout("."); // about the archive itself
      description.setDescription("libSemSim ");
      description.setCreated(LIBCOMBINE_CPP_NAMESPACE_QUALIFIER OmexDescription::getCurrentDateAndTime());

      archive.writeToFile(archive_path);

      archive.cleanUp();
    }
}
