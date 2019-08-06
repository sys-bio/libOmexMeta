# ifndef SEMSIM_OMEX_OUTPUT_H_
# define SEMSIM_OMEX_OUTPUT_H_

# include "semsim/Preproc.h"
# include "semsim/Model.h"


namespace semsim {
    /**
     * Write a @ref Model and associated annotation information to a
     * Combine archive.
     * @param model           The libSemSim @ref Model to write out.
     * @param archive_path    The path for the Combine archive.
     * @param sbml_entry_path The path to the SBML file within the archive.
     * @param rdf_entry_path  The path to the annotation RDF metadata within the archive.
     */
    void exportToOmex(const Model& model,
      const std::string& archive_path,
      const std::string& model_entry_path="./model.xml",
      const std::string& rdf_entry_path="./annotations.xml");
}
# endif
