//
// Created by Ciaran on 4/4/2020.
//

#include <utility>
#include "raptor2.h"
#include "Triple.h"

namespace semsim {

    Triple::Triple(Subject subject, Predicate predicate, Resource resource) : subject(std::move(subject)),
                                                                              predicate(std::move(predicate)),
                                                                              resource(std::move(resource)) {}

    const Subject &Triple::getSubject() const {
        return subject;
    }

    const Predicate &Triple::getPredicate() const {
        return predicate;
    }

    const Resource &Triple::getResource() const {
        return resource;
    }

    bool Triple::operator==(const Triple &rhs) const {
        return subject == rhs.subject &&
               predicate == rhs.predicate &&
               resource == rhs.resource;
    }

    bool Triple::operator!=(const Triple &rhs) const {
        return !(rhs == *this);
    }

    std::ostream &operator<<(std::ostream &os, const Triple &triple) {
        os << "Triple(subject="
           << triple.getSubject()
           << ", predicate="
           << triple.predicate
           << ", resource="
           << triple.resource;
        return os;
    }

    Triple::Triple(std::string subject, std::string predicate, std::string resource) :
            subject(
                    Subject(std::move(subject))
            ),
            predicate(
                    Predicate(std::make_unique<ControlledVocabulary>(predicate))
            ),
            resource(
                    Resource(std::move(resource))
            ) {}


    std::string Triple::serialize(std::string format) {
        raptor_world *world = raptor_new_world();
//        unsigned char *uri_string = raptor_uri_filename_to_uri_string("./MyModel.xml");
        raptor_uri *base_uri = raptor_new_uri(world, (const unsigned char *) "");


        /* Make a triple with URI subject, URI predicate, literal object */
        raptor_statement *triple = raptor_new_statement(world);
        triple->subject = raptor_new_term_from_uri_string(
                world,
                (const unsigned char *) subject.getMetaId().c_str()
        );

        triple->predicate = raptor_new_term_from_uri_string(
                world,
                (const unsigned char *) predicate.getUri().str().c_str()
        );
        triple->object = raptor_new_term_from_uri_string(world, (const unsigned char *) resource.build().c_str());

        /* Write the triple */
        raptor_serializer *rdf_serializer = nullptr;
        rdf_serializer = raptor_new_serializer(world, format.c_str());
        if (!rdf_serializer)
            throw std::runtime_error("Could not create Raptor serializer for format " + format);
        std::string prefix = "bqb";
        raptor_uri *u;

//        raptor_uri_to_relative_uri_string()
        std::string x = "http://biomodels.net/biology-qualifiers";

        u = raptor_new_uri(world, (const unsigned char *) x.c_str());
//        raptor_uri_filename_to_uri_string(u);

        raptor_serializer_set_namespace(rdf_serializer, u, (const unsigned char *) prefix.c_str());
//        raptor_serializer_set_namespace_from_namespace()

        raptor_serializer_start_to_file_handle(rdf_serializer, base_uri, stdout);
        raptor_serializer_serialize_statement(rdf_serializer, triple);

        /* Delete the triple */
        raptor_free_statement(triple);

        raptor_serializer_serialize_end(rdf_serializer);
        raptor_free_serializer(rdf_serializer);

        raptor_free_uri(base_uri);

        raptor_free_world(world);


        return "not yet implemented";
    }
//            SemsimModel &model = *(SemsimModel *) user_data;
//        if (isMetaId(triple->subject)) {
//            std::string metaid = extractMetaId(triple->subject);
//            if (model.hasComponentWithMetaId(metaid)) {
//                Component &component = model.findComponentWithMetaId(metaid);
//                if (!component.hasAnnotation()) {
//                    component.setAnnotation(SingularAnnotation(metaid));
//                }
//                addTermToAnnotation(component.getAnnotation(), Relation(RaptorTermToURI(triple->predicate)),
//                                    Resource(RaptorTermToURI(triple->object)));
//                // std::cerr << metaid << " " << RaptorTermToRepr(triple->predicate) << " " << RaptorTermToRepr(triple->object) << "\n";
//            }
//        }
}
/*
 * Does it make sense to set a namespace on the triple itself? Probably not.
 * However, surely the namespaces can be extracted directly from the urls?
 * but then what about the prefixes? These should be stndardized - ie.e bqb,
 * Perhaps I could just include logic for the common ones and an interace to users to
 * specify their own?
 *
 * Also, the subject url is absolute, where we want to keep it relative.
 *
 * A triple in raptor is a statement - possibly. So a Triple should
 * also have a statement.
 */

//        std::string getRDF(Url &sbml_base_uri,  std::string &format)  override {
//            raptor_world *world = raptor_new_world();
//            raptor_serializer *serializer = raptor_new_serializer(world, format.c_str());
//            if (!serializer)
//                throw std::runtime_error("Could not create Raptor serializer for format " + format);
//
//            raptor_uri *base_uri = raptor_new_uri(world, ( unsigned char *) "");
//
//            raptor_serializer_set_namespace(serializer,
//                                            raptor_new_uri(world, ( unsigned char *) bqb::root.c_str()),
//                                            ( unsigned char *) "bqb");
//            raptor_serializer_set_namespace(serializer,
//                                            raptor_new_uri(world, ( unsigned char *) semsim::root.c_str()),
//                                            ( unsigned char *) "semsim");
//
//            void *output;
//            size_t length;
//            raptor_serializer_start_to_string(serializer, base_uri, &output, &length);
//
//            serializeToRDF(sbml_base_uri, world, serializer);
//
//            raptor_serializer_serialize_end(serializer);
//
//            raptor_free_serializer(serializer);
//            raptor_free_world(world);
//
//            std::string result((char *) output);
//            free(output);
//            return result;
//        }
