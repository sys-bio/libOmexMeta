# ifndef SEMSIM_RDF_RDFREADER_H_
# define SEMSIM_RDF_RDFREADER_H_

# include "semsim/Preproc.h"
# include "semsim/Model.h"
# include "semsim/sbml/SBMLModel.h"

namespace semsim {
    /**
     * Applies RDF metadata annotations to a libSemSim model.
     * @param model      The libSemSim model.
     * @param rdf        The RDF annotations to apply.
     * @param rdf_format The format of the RDF annotations. Choices include "rdfxml", "ntriples", "turtle", "trig", "rss-tag-soup", "grddl", "rdfa", "json", and "nquads".
     */
    void applyRDFAnnotationsToModel(
      const Model& model,
      const std::string& rdf,
      const std::string& rdf_format="rdfxml");
}
# endif
