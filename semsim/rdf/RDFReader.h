# ifndef SEMSIM_RDF_RDFREADER_H_
# define SEMSIM_RDF_RDFREADER_H_

# include "semsim/Preproc.h"
# include "semsim/Model.h"
# include "semsim/sbml/SBMLModel.h"

namespace semsim {

    class RDFReader {
    public:
        static std::string RaptorURIToString(raptor_uri *u);


        static URI RaptorTermToURI(raptor_term *t);

        static std::string RaptorTermToRepr(raptor_term *t);

        static bool isMetaId(const std::string &uri);

        static bool isMetaId(raptor_term *t);

        static std::string extractMetaId(const std::string &uri);

        static std::string extractMetaId(raptor_term *t);

        static void addTermToEntity(EntityBase &entity, const Relation &relation, const Resource &resource);

        static void
        addTermToCompositeAnnotation(CompositeAnnotation &annotation, const Relation &relation,
                                     const Resource &resource);

        static void
        addTermToSingularAnnotation(SingularAnnotation &annotation, const Relation &relation, const Resource &resource);

        static void addTermToAnnotation(AnnotationBase &annotation, const Relation &relation, const Resource &resource);

        static void process_triple(void *user_data, raptor_statement *triple);

        /**
         * Applies RDF metadata annotations to a libSemSim model.
         * @param model      The libSemSim model.
         * @param rdf        The RDF annotations to apply.
         * @param rdf_format The format of the RDF annotations. Choices include "rdfxml", "ntriples", "turtle", "trig", "rss-tag-soup", "grddl", "rdfa", "json", and "nquads".
         */
        void applyRDFAnnotationsToModel(
                Model &model,
                const std::string &rdf,
                const std::string &rdf_format = "rdfxml");
    };
}
# endif
