//
// Created by Ciaran on 4/8/2020.
//
#include "semsim/RDF.h"

namespace semsim {


/*******************************************************
 * Constructors
 */

    RDF::RDF(const std::string &storage_type, const std::string &storage_name, const char *storage_options,
             const char *model_options) {
        storage_ = LibrdfStorage(storage_type, storage_name, storage_options);
        model_ = LibrdfModel(std::move(storage_), model_options);
    }

    std::vector<std::string> getValidParserNames() {
        return std::vector<std::string>(
                {"rdfxml",
                 "ntriples",
                 "turtle",
                 "trig",
                 "rss-tag-soup",
                 "grddl",
                 "guess",
                 "rdfa",
                 "nquads",
                });
    }
/***************************************************************
 *  getters and setters
 */
//
//    const std::unordered_map<std::string, std::string> &semsim::RDF::getNamespaces() const {
//        return namespaces_;
//    }
//
//    void semsim::RDF::setNamespaces(const std::unordered_map<std::string, std::string> &namespaces) {
//        namespaces_ = namespaces;
//    }




/*************************************************
 * to/from operations
 */
//
//    semsim::RDF semsim::RDF::fromUrl(std::string url, std::string filename, std::string format) {
//        SemsimUtils::download(url, filename);
//        return semsim::RDF::fromFile(filename, std::__cxx11::string());
//    }
//    semsim::RDF semsim::RDF::fromFile(std::string filename, std::string format) {
//        return semsim::RDF();
//    }

    semsim::RDF semsim::RDF::fromString(const std::string &str, const std::string &format) {
        if (std::find(RDF::getValidParserNames().begin(), RDF::getValidParserNames().end(), format) ==
            RDF::getValidParserNames().end()) {
            std::ostringstream os;
            os << __FILE__ << ":" << __LINE__ << ": Format \"" << format
               << "\" is not a valid option. These are your options: ";
            for (auto &it : RDF::getValidParserNames()) {
                os << it << ", ";
            }
            throw std::invalid_argument(os.str());
        }
        RDF rdf;
        Reader reader(rdf.getWorld(), rdf.getModel(), std::move(format), "file://./annotations.rdf");
        reader.fromString(str);

        // pull "seen" namespaces out of the parser and pass them to RDF class
        rdf.seen_namespaces_ = reader.getSeenNamespaces();

        // Compare against predefined set of namespaces: keep ones we've seen
        rdf.namespaces_ = rdf.propagateNamespacesFromParser(rdf.seen_namespaces_);

        return rdf;
    }

//    semsim::RDF semsim::RDF::fromXML(const std::string &filename, std::string format) {
//        LibRDFObjectsTuple objectsTuple = RDF::init();
//
//        // unpack redland library objects
//        LibrdfWorld world = std::get<0>(objectsTuple);
//        RaptorWorld raptor_world_ptr = std::get<1>(objectsTuple);
//        LibrdfStorage storage = std::get<2>(objectsTuple);
//        LibrdfModel model = std::get<3>(objectsTuple);
//
//        // Read the xml
//        Reader reader(world, model, std::move(format), "file://./annotations.rdf");
//        reader.fromFile(filename);
//
//        // construct an RDF object
//        semsim::RDF rdf(world, raptor_world_ptr, storage, model);
//
//        // pull "seen" namespaces out of the parser and pass them to RDF class
//        rdf.seen_namespaces_ = reader.getSeenNamespaces();
//
//        // Compare against predefined set of namespaces: keep ones we've seen
//        rdf.namespaces_ = rdf.propagateNamespacesFromParser(rdf.seen_namespaces_);
//
//        return rdf;
//    }

//    semsim::RDF semsim::RDF::fromOmex(const std::string &filename_or_url, std::string format) {
//        return semsim::RDF();
//    }

//    std::string semsim::RDF::toString(const std::string &format = "rdfxml-abbrev",
//                                      const std::string &base_uri = "file://./annotations.rdf") {
//        setBaseUri(base_uri);
//        Writer writer = makeWriter(format);
//        return writer.toString();
//    }

//    void semsim::RDF::toFile(std::string format) {
//
//    }


/********************************************************************
 * Other methods
 */

//    std::unordered_map<std::string, std::string>
//    semsim::RDF::propagateNamespacesFromParser(std::vector<std::string> seen_namespaces) {
//        std::unordered_map<std::string, std::string> keep_map;
//        for (auto &seen_namespace : seen_namespaces) {
//            auto iter = default_namespaces_.find(seen_namespace);
//            if (iter != default_namespaces_.end()) {
//                keep_map[seen_namespace] = default_namespaces_[seen_namespace];
//            }
//        }
//        return keep_map;
//    }


//    semsim::Writer semsim::RDF::makeWriter(const std::string &format) {
//        Writer writer(world_, model_, getBaseUriAsString(), format);
//        writer.registerNamespace(namespaces_);
//        return writer;
//    }

//    std::ostringstream semsim::RDF::listOptions() {
//        raptor_world *raptor_world_ptr = raptor_new_world();
//        int num_raptor_options = (int) raptor_option_get_count() - 1;
//        std::ostringstream os;
//        os << "option, name, label, domain, value type, url" << std::endl;
//        int i = 0;
//        while (i != num_raptor_options) {
//            raptor_option_description *parser_opt = raptor_world_get_option_description(
//                    raptor_world_ptr,
//                    RAPTOR_DOMAIN_PARSER,
//                    (raptor_option) i
//            );
//            if (parser_opt) {
//                os << parser_opt->option << "," << parser_opt->name << "," << parser_opt->label << ","
//                   << parser_opt->domain
//                   << "," << parser_opt->value_type << "," << raptor_uri_to_string(parser_opt->uri) << std::endl;
//            } else {
//                raptor_option_description *serializer_opt = raptor_world_get_option_description(
//                        raptor_world_ptr,
//
//                        RAPTOR_DOMAIN_SERIALIZER,
//                        (raptor_option) i
//                );
//                if (serializer_opt) {
//                    os << serializer_opt->option << "," << serializer_opt->name << "," << serializer_opt->label
//                       << ","
//                       << serializer_opt->domain
//                       << "," << serializer_opt->value_type << "," << raptor_uri_to_string(serializer_opt->uri)
//                       << std::endl;
//                }
//            }
//            i++;
//        };
//        return os;
//    }

//    semsim::Editor semsim::RDF::toEditor(std::string xml, semsim::XmlAssistantType type) {
//        return Editor(xml, type, world_, model_, namespaces_);
//    }
//
//    semsim::Editor *semsim::RDF::toEditorPtr(std::string xml, semsim::XmlAssistantType type) {
//        return new Editor(xml, type, world_, model_, namespaces_);
//    }
//
//    semsim::LibrdfUri semsim::RDF::getBaseUri() const {
//        return base_uri_;
//    }
//
//    std::string semsim::RDF::getBaseUriAsString() const {
//        return base_uri_.str(); //std::string((const char *) librdf_uri_as_string(base_uri_));
//    }

//    void semsim::RDF::setBaseUri(std::string baseUri) {
//        baseUri = semsim::SemsimUtils::addFilePrefixToString(baseUri);
//        LibrdfUri uri = world_.newUri(baseUri);
//        if (!uri) {
//            throw semsim::LibRDFException("semsim::RDF::setBaseUri: Unable to create a new librdf_uri instance. ");
//        }
//        base_uri_ = uri;
//    }
//
//    void semsim::RDF::setBaseUri(LibrdfUri baseUri) {
//        if (!baseUri) {
//            throw semsim::LibRDFException("semsim::RDF::setBaseUri: Unable to create a new librdf_uri instance. ");
//        }
//        // check if file:// prepended to baseUri and if not add it.
//        base_uri_ = world_.newUri(
//                semsim::SemsimUtils::addFilePrefixToString(baseUri.str())
//        );
//    }
//
//    int semsim::RDF::size() const {
//        librdf_stream *stream = librdf_model_as_stream(*getModel().getModel());
//        if (!stream) {
//            throw LibRDFException("Query::resultsAsTriples: stream object null");
//        }
//        int count = 0;
//        while (!librdf_stream_end(stream)) {
//            count++;
//            librdf_stream_next(stream);
//        }
//        librdf_free_stream(stream);
//        return count;
//    }
//
//    semsim::Triples semsim::RDF::toTriples() {
//        LibrdfStream stream(librdf_model_as_stream(*getModel().getModel()));
//        if (!stream) {
//            throw LibRDFException("RDF::toTriples: stream object null");
//        }
//        Triples triples;
//        // todo turn this into method of LibrdfStream
//        while (!librdf_stream_end(*stream.getStream())) {
//            LibrdfStatement statement(
//                    librdf_stream_get_object(*stream.getStream())
//            );
//            if (!statement) {
//                throw LibRDFException("RDF::toTriples(): statement is null");
//            }
//            triples.emplace_back(world_, statement);
//            librdf_stream_next(*stream.getStream());
//        }
//        return triples;
//    }
//
//    std::string semsim::RDF::queryResultsAsStr(const std::string &query_str, const std::string &results_format) {
//        return semsim::Query(world_, model_, query_str).resultsAsStr(results_format);
//    }
//
//    semsim::ResultsMap semsim::RDF::queryResultsAsMap(const std::string &query_str) {
//        return semsim::Query(world_, model_, query_str).resultsAsMap();
//    }
//
//    semsim::Triples semsim::RDF::queryResultsAsTriples(const std::string &query_str) {
//        return queryResultsAsRDF(query_str).toTriples();
//    }
//
//    semsim::RDF semsim::RDF::queryResultsAsRDF(const std::string &query_str) {
//        return RDF::fromString(queryResultsAsStr(query_str, "rdfxml"), "rdfxml");
//    }
//

}


















