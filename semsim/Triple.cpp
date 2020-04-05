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

    // todo i suspect you'll have to move some of this code into a higher level object
    //  so that we can call down and seralize several rdf statements at once
    //  via the iostream feature. For now, keep itlke this.
    std::string Triple::serialize(std::string format) {
        raptor_world *world = raptor_new_world();
        // todo work out whether base uri should be a file name of the model.

        // create raptor triple
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

        // make a raptor serializer
        raptor_serializer *rdf_serializer = nullptr;
        rdf_serializer = raptor_new_serializer(world, format.c_str());
        if (!rdf_serializer)
            throw std::runtime_error("Could not create Raptor serializer for format " + format);

        // add a namespace for the predicate uri
        raptor_uri *predicate_uri = raptor_new_uri(
                world,
                (const unsigned char *) predicate.getTerm()->getRoot().c_str());
        raptor_serializer_set_namespace(
                rdf_serializer,
                predicate_uri,
                (const unsigned char *) predicate.getTerm()->getCvNamespace().c_str());
        void *string;  /* destination for string */
        size_t length; /* length of constructed string */
        raptor_serializer_start_to_string(rdf_serializer, nullptr, &string, &length);
//        const char *filename = "./raptor.rdf";
//        raptor_serializer_start_to_filename(rdf_serializer, filename);
        raptor_serializer_serialize_statement(rdf_serializer, triple);
        /* Delete the triple */
        raptor_free_statement(triple);

        raptor_serializer_serialize_end(rdf_serializer);
        auto *pstr = static_cast<const char *>(string);

        // free memory
        raptor_free_serializer(rdf_serializer);
        raptor_free_world(world);

        return static_cast<std::string>(pstr);
    }


}


/*
 * I wonder whether its possible to wrap the serialisation
 * up in a builder pattern. So users would do somethinglike:
 *
 *      statement.serialise().with_format('format').to_output(output)
 */