//
// Created by Ciaran on 4/4/2020.
//

#include <utility>
#include "raptor2.h"
#include "Triple.h"
#include "semsim/RaptorUtils.h"

//'todo Conceptually, could we use an isa relationshop between singular annotation and Triple?

namespace semsim {

    Triple::Triple(Subject subject, Predicate predicate, Resource resource) : subject(std::move(subject)),
                                                                              predicate(std::move(predicate)),
                                                                              resource(std::move(resource)) {}


    Triple::Triple(const Triple &triple) {
        if (*this != triple) {
            this->subject = triple.subject;
            this->predicate = triple.predicate;
            this->resource = triple.resource;
        }
    }

    Triple::Triple(Triple &&triple) noexcept {
        if (this != &triple) {
            this->subject = std::move(triple.subject);
            this->predicate = std::move(triple.predicate);
            this->resource = std::move(triple.resource);
        }
    }

    Triple &Triple::operator=(const Triple &triple) {
        if (this != &triple) {
            this->subject = triple.subject;
            this->predicate = triple.predicate;
            this->resource = triple.resource;
        }
        return *this;
    }

    Triple &Triple::operator=(Triple &&triple) noexcept {
        if (this != &triple) {
            this->subject = std::move(triple.subject);
            this->predicate = std::move(triple.predicate);
            this->resource = std::move(triple.resource);
        }
        return *this;
    }

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
           << triple.getSubject().getMetaId()
           << ", predicate="
           << triple.getPredicate().getUri().str()
           << ", resource="
           << triple.getResource().build();
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

    void Triple::from_xml2(std::string xml) {
        // create raptor world object
        raptor_world *world = raptor_new_world();

        // create a raptor parser object
        raptor_parser *rdf_parser = raptor_new_parser(world, "rdfxml");

//        // create a raptor parser statement handler
//        raptor_parser_set_statement_handler(rdf_parser, nullptr, print_triple);
//        size_t size = 0;
//        raptor_iostream *iostream = raptor_new_iostream_from_string(world, (void *) xml.c_str(), size);
//        if (!(iostream)) {
//            throw std::logic_error("iostream not created");
//        }
//        const unsigned char *uri_string = raptor_uri_filename_to_uri_string("./MyModel");
//        raptor_uri *uri = raptor_new_uri(world, uri_string);
//
//        raptor_parser_parse_iostream(rdf_parser, iostream, uri);
//
//        void *sp;
//        raptor_iostream_string_write(sp, iostream);
//
//        const auto *s = static_cast<const char *>(sp);
//
//        printf(s);

        raptor_free_parser(rdf_parser);

//        raptor_free_uri(uri);

        raptor_free_world(world);
    }

    Triple Triple::from_xml(std::string xml) {

        raptor_world *world = raptor_new_world();

        raptor_parser *rdf_parser = raptor_new_parser(world, "rdfxml");

        raptor_parser_set_statement_handler(rdf_parser, nullptr, RaptorStatementHandler::printStatementNTriples);

        unsigned char *uri_string = raptor_uri_filename_to_uri_string(R"(/mnt/d/libsemsim/tests/Teusink2000.xml)");
        raptor_uri *uri = raptor_new_uri(world, uri_string);
        raptor_uri *base_uri = raptor_uri_copy(uri);

        raptor_parser_parse_file(rdf_parser, uri, base_uri);

        raptor_free_parser(rdf_parser);

        raptor_free_uri(base_uri);
        raptor_free_uri(uri);
        raptor_free_memory(uri_string);

        raptor_free_world(world);

    }

    /*
     * Use kyles raptor utils class for putting things
     * like UriToString.
     */

    void Triple::parseTriple(void *user_data, raptor_statement *triple) {
//        triple->subject->
        auto &x = triple->subject->value.uri;
        const unsigned char *y = raptor_uri_to_string(x);
        std::string subject_result((const char *) y);
        this->subject = Subject(subject_result);
//        std::string x = static_cast<std::string>(triple->subject->value.uri)
//        raptor_statement_print(triple, stdout);
//        fputc('\n\n', stdout);
    }

}


/*
 * I wonder whether its possible to wrap the serialisation
 * up in a builder pattern. So users would do somethinglike:
 *
 *      statement.serialise().with_format('format').to_output(output)
 */