# include "semsim/omex/SBMLOmex.h"
# include "semsim/sbml/SBMLImporter.h"
# include "semsim/rdf/RDFReader.h"

# include "combine/combinearchive.h"
# include "combine/knownformats.h"
# include "combine/omexdescription.h"

namespace semsim {
    SBMLModel importSBMLOmex(const std::string& archive_path, const std::string& model_entry_path, const std::string& rdf_entry_path) {
      LIBCOMBINE_CPP_NAMESPACE_QUALIFIER CombineArchive archive;

      if (!archive.initializeFromArchive(archive_path))
        throw std::runtime_error("Unable to import Combine archive");

      LIBSBML_CPP_NAMESPACE_QUALIFIER SBMLReader reader;
      LIBSBML_CPP_NAMESPACE_QUALIFIER SBMLDocument* d = reader.readSBMLFromString(archive.extractEntryToString(model_entry_path));

      if (!d || d->getNumErrors())
        throw std::runtime_error("Errors reading SBML");

      std::string rdf = archive.extractEntryToString(rdf_entry_path);

      SBMLImporter importer(d);
      SBMLModel& result = importer.getSBMLModel();
      applyRDFAnnotationsToModel(result, rdf);
      return std::move(result);
    }
}
