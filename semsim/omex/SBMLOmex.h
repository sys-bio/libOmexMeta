# ifndef SEMSIM_SBML_OMEX_H_
# define SEMSIM_SBML_OMEX_H_


# include "semsim/SemsimModel.h"
# include "semsim/SemSimSBMLModel.h"

namespace semsim {
    /**
     * Read an SBML file and annotation metadata from a Combine archive and
     * return a @ref SemsimModel with annotation information.
     * @param archive_path    The path for the Combine archive.
     * @param sbml_entry_path The path to the SBML file within the archive.
     * @param rdf_entry_path  The path to the annotation RDF metadata within the archive.
     */
    SemSimSBMLModel importSBMLOmex(
             std::string &archive_path,
             std::string &sbml_entry_path,
             std::string &rdf_entry_path);
}
# endif
