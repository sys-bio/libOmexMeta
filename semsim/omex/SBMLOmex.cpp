# include "semsim/omex/SBMLOmex.h"
# include "semsim/SBMLImporter.h"
# include "semsim/RDFReader.h"

# include "combine/combinearchive.h"
# include "combine/knownformats.h"
# include "combine/omexdescription.h"

namespace semsim {
    SemSimSBMLModel importSBMLOmex(const std::string &archive_path, const std::string &model_entry_path,
                                   const std::string &rdf_entry_path) {
        LIBCOMBINE_CPP_NAMESPACE_QUALIFIER CombineArchive archive;

        if (!archive.initializeFromArchive(archive_path))
            throw std::runtime_error("Unable to import Combine archive");

        libsbml::SBMLReader reader;
        libsbml::SBMLDocument *d = reader.readSBMLFromString(archive.extractEntryToString(model_entry_path));

        if (!d || d->getNumErrors())
            throw std::runtime_error("Errors reading SBML");

        std::string rdf = archive.extractEntryToString(rdf_entry_path);

        SBMLImporter importer(d);
        SemSimSBMLModel &result = importer.getSemSimSBMLModel();
        RDFReader::applyRDFAnnotationsToModel(result, rdf);
        return std::move(result);
    }
}
