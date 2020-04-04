# ifndef SEMSIM_OMEX_OUTPUT_H_
# define SEMSIM_OMEX_OUTPUT_H_


# include "semsim/SemsimModel.h"


namespace semsim {
    /**
     * Write a @ref SemsimModel and associated annotation information to a
     * Combine archive.
     * @param model            The libSemSim @ref SemsimModel to write out.
     * @param archive_path     The path for the Combine archive.
     * @param model_entry_path The path to the model file (SBML or CellML) within the archive.
     * @param rdf_entry_path   The path to the annotation RDF metadata within the archive.
     */
    void exportToOmex( SemsimModel &model,
                       std::string &archive_path,
                       std::string &model_entry_path = "./model.xml",
                       std::string &rdf_entry_path = "./annotations.xml");
}
# endif
