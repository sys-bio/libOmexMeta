//
// Created by Ciaran on 4/4/2020.
//

#include <utility>
#include <algorithm>
#include <cstring>
#include "raptor2.h"
#include "librdf.h"
#include "Triple.h"
#include "semsim/RaptorUtils.h"
#include "semsim/uri.h"

//'todo Conceptually, could we use an isa relationshop between singular annotation and Triple?

namespace semsim {

    Triple::Triple(Subject subject, PredicatePtr predicate_ptr, Resource resource) :
            subject_(std::move(subject)),
            predicate_ptr_(std::move(predicate_ptr)),
            resource_(std::move(resource)) {}

    Triple::Triple(Subject subject, const Predicate &predicate, Resource resource) :
            subject_(std::move(subject)),
            predicate_ptr_(std::make_unique<Predicate>(predicate)),
            resource_(std::move(resource)) {}

    Triple::Triple(std::string subject, const Predicate &predicate, const std::string& resource) :
            subject_(Subject(std::move(subject))),
            predicate_ptr_(std::make_unique<Predicate>(predicate)),
            resource_(Resource(resource)) {}

    Triple::Triple(const Triple &other) :
            subject_(other.subject_),
            predicate_ptr_(std::make_unique<Predicate>(*other.predicate_ptr_)),
            resource_(other.resource_) {}

    Triple::Triple(const Triple &&other) noexcept :
            subject_(other.subject_),
            predicate_ptr_(std::make_unique<Predicate>(*other.predicate_ptr_)),
            resource_(other.resource_) {}


    Triple &Triple::operator=(const Triple &triple) {
        if (this != &triple) {
            this->subject_ = triple.subject_;
            this->predicate_ptr_ = std::make_unique<Predicate>(*triple.predicate_ptr_);
            this->resource_ = triple.resource_;
        }
        return *this;
    }

    Triple &Triple::operator=(Triple &&triple) noexcept {
        if (this != &triple) {
            this->subject_ = triple.subject_;
            this->predicate_ptr_ = std::make_unique<Predicate>(*triple.predicate_ptr_);
            this->resource_ = triple.resource_;
        }
        return *this;
    }

    const Subject &Triple::getSubject() const {
        return subject_;
    }

    const PredicatePtr &Triple::getPredicate() const {
        return predicate_ptr_;
    }

    const Resource &Triple::getResource() const {
        return resource_;
    }

    bool Triple::operator==(const Triple &rhs) const {
        return subject_ == rhs.subject_ &&
               predicate_ptr_ == rhs.predicate_ptr_ &&
               resource_ == rhs.resource_;
    }

    bool Triple::operator!=(const Triple &rhs) const {
        return !(rhs == *this);
    }

    std::ostream &operator<<(std::ostream &os, const Triple &triple) {
        os << "Triple(subject_="
           << triple.getSubject().getMetaId()
           << ", predicate_="
           << triple.getPredicate()->getUri().str()
           << ", resource_="
           << triple.getResource().str();
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
                (const unsigned char *) subject_.getMetaId().c_str()
        );

        triple->predicate = raptor_new_term_from_uri_string(
                world,
                (const unsigned char *) predicate_ptr_->getUri().str().c_str()
        );
        triple->object = raptor_new_term_from_uri_string(world, (const unsigned char *) resource_.str().c_str());

        // make a raptor serializer
        raptor_serializer *rdf_serializer = nullptr;
        rdf_serializer = raptor_new_serializer(world, format.c_str());
        if (!rdf_serializer)
            throw std::runtime_error("Could not create Raptor serializer for format " + format);

        // add a namespace for the predicate_ uri
        raptor_uri *predicate_uri = raptor_new_uri(
                world,
                (const unsigned char *) predicate_ptr_->getNamespace().c_str());
        raptor_serializer_set_namespace(
                rdf_serializer,
                predicate_uri,
                (const unsigned char *) predicate_ptr_->getPrefix().c_str());
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

    void Triple::from_xml(std::string xml) {
        librdf_world *world = librdf_new_world();
        librdf_world_open(world);
        raptor_world *raptor_world_ptr = librdf_world_get_raptor(world);


        librdf_storage *storage = librdf_new_storage(world, "memory", "test", nullptr);
        if (!storage) {
            fprintf(stderr, "Failed to create new storage\n");
        }

        librdf_model *model = librdf_new_model(world, storage, nullptr);
        if (!model) {
            fprintf(stderr, "Failed to create model\n");
        }

        librdf_parser *parser = librdf_new_parser(world, reinterpret_cast<const char *>("rdfxml"), nullptr, nullptr);
        if (!parser) {
            fprintf(stderr, "Failed to create new parser\n");
        }

//        std::cout << __FILE__ << ":" << __LINE__ << std::endl;
//        librdf_uri *uri = librdf_new_uri(world,
//                                         (const unsigned char *) "http://www.ebi.ac.uk/biomodels-main/download?mid=BIOMD0000000064");
//
        raptor_uri *uri = librdf_new_uri_from_filename(world, (const char *) "/mnt/d/libsemsim/tests/Teusink2000.xml");
        if (!uri) {
            fprintf(stderr, "Failed to create URI\n");
        }

        /* PARSE the URI as RDF/XML*/
        fprintf(stdout, "Parsing URI %s\n", librdf_uri_as_string(uri));
        librdf_parser_parse_into_model(parser, uri, uri, model);
//        librdf_parser_parse_string_into_model(parser, (const unsigned char *) xml.c_str(), uri, model);
        librdf_free_parser(parser);

//        /* Print out the model*/
        fprintf(stdout, "Resulting model is:\n");
        raptor_iostream *iostr = raptor_new_iostream_to_file_handle(raptor_world_ptr, stdout);
        librdf_model_write(model, iostr);
        raptor_free_iostream(iostr);


        librdf_statement *statement2 = librdf_new_statement_from_nodes(world, librdf_new_node_from_uri_string(world,
                                                                                                              (const unsigned char *) "http://www.dajobe.org/"),
                                                                       librdf_new_node_from_uri_string(world,
                                                                                                       (const unsigned char *) "http://purl.org/dc/elements/1.1/title"),
                                                                       librdf_new_node_from_literal(world,
                                                                                                    (const unsigned char *) "My Home Page",
                                                                                                    nullptr, 0)
        );
        librdf_model_add_statement(model, statement2);

        /* Free what we just used to add to the model - now it should be stored */
        librdf_free_statement(statement2);


//        /* Print out the model*/
//        fprintf(stdout, "\n\n\n\nResulting model is:\n");
//        raptor_iostream *iostr = raptor_new_iostream_to_file_handle(raptor_world_ptr, stdout);
//        librdf_model_write(model, iostr);
//        raptor_free_iostream(iostr);


        unsigned char *string = librdf_model_to_string(model, uri, "rdfxml", NULL, NULL);
        if (!string)
            printf("Failed to serialize model\n");
        else {
            printf("Made a %d byte string\n", (int) strlen((char *) string));
            free(string);
        }
        printf("%s", string);

        librdf_free_model(model);

        librdf_free_storage(storage);

        librdf_free_uri(uri);

        librdf_free_world(world);
        std::cout << __FILE__ << ":" << __LINE__ << std::endl;

    }

    void Triple::parseTriple(void *user_data, raptor_statement *raptor_triple) {
        auto *myTriple = (Triple *) user_data;

        // pull subject_ from raptor triple object
        myTriple->subject_ = Subject(RaptorUtils::raptorUriToString(raptor_triple->subject->value.uri));

        // pull the predicate_ from the triple obj
        semsim::Uri predicate_uri(RaptorUtils::raptorUriToString(raptor_triple->predicate->value.uri));

        // Look up namespace to see if we already have an acronym for it
        std::string root;
        std::string ns;
        for (auto &it: PredicateNamespaces::getNamespaces()) {
            if (predicate_uri.str().find(it.second) != std::string::npos) {
                ns = it.first;
                root = it.second;
                break;
            }
        }

        raptor_statement_print_as_ntriples(raptor_triple, stdout);
        fputc('\n', stdout);
    }


}


/*
 * I wonder whether its possible to wrap the serialisation
 * up in a strer pattern. So users would do somethinglike:
 *
 *      statement.serialise().with_format('format').to_output(output)
 */