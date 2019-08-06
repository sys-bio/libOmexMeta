# ifndef SEMSIM_SBML_OMEX_H_
# define SEMSIM_SBML_OMEX_H_

# include "semsim/Preproc.h"
# include "semsim/Model.h"
# include "semsim/sbml/SBMLModel.h"

namespace semsim {
    /**
     * Read a Combine archive and return a @ref Model with annotation information.
     * @param archive_path    The path for the Combine archive.
     * @param sbml_entry_path The path to the SBML file within the archive.
     * @param rdf_entry_path  The path to the annotation RDF metadata within the archive.
     */
    SBMLModel importSBMLOmex(
      const std::string& archive_path,
      const std::string& sbml_entry_path,
      const std::string& rdf_entry_path);
}
# endif
