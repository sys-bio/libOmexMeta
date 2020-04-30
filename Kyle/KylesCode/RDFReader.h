# ifndef SEMSIM_RDF_RDFREADER_H_
# define SEMSIM_RDF_RDFREADER_H_

# include "semsim/uri.h"
# include "semsim/SemsimModel.h"
# include "SemSimSBMLModel.h"

namespace semsim {

    class RDFReader {
    public:
        static std::string RaptorURIToString(raptor_uri *u);

        static Url RaptorTermToURI(raptor_term *t);

        static std::string RaptorTermToRepr(raptor_term *t);

        static bool isMetaId(std::string &uri);

        static bool isMetaId(raptor_term *t);

        static std::string extractMetaId(std::string &uri);

        static std::string extractMetaId(raptor_term *t);

        static void addTermToEntity(EntityBase &entity, Relation &relation, Resource &resource);

        static void addTermToCompositeAnnotation(
                CompositeAnnotation &annotation,
                Relation &relation,
                Resource &resource);

        static void addTermToSingularAnnotation(
                SingularAnnotation &annotation,
                Relation &relation,
                Resource &resource);

        static void addTermToAnnotation(AnnotationBase &annotation, Relation &relation, Resource &resource);

        static void process_triple(void *user_data, raptor_statement *triple);

        /**
         * Applies RDF metadata annotations to a libSemSim model.
         * @param model      The libSemSim model.
         * @param rdf        The RDF annotations to apply.
         * @param rdf_format The format of the RDF annotations. Choices include "rdfxml", "ntriples", "turtle", "trig", "rss-tag-soup", "grddl", "rdfa", "json", and "nquads".
         */
        static void applyRDFAnnotationsToModel(
                SemsimModel &model,
                std::string &rdf,
                std::string &rdf_format = "rdfxml");
    };
}
# endif
