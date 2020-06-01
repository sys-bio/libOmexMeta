//
// Created by Ciaran on 4/8/2020.
//
#include "semsim/RDF.h"

namespace semsim {


/*******************************************************
 * Constructors
 */

    RDF::RDF(const std::string &base_uri, const std::string &storage_type, const std::string &storage_name,
             const char *storage_options,
             const char *model_options) {
        storage_ = LibrdfStorage(storage_type, storage_name, storage_options);
        model_ = LibrdfModel(storage_, model_options);
        setBaseUri(base_uri);
    }


/***************************************************************
 *  getters and setters
 */

    std::vector<std::string> RDF::getValidParserNames() {
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

/*************************************************
 * to/from operations
 */

//    RDF RDF::fromUrl(std::string url, std::string filename, std::string format) {
//        SemsimUtils::download(url, filename);
//        return RDF::fromFile(filename, std::__cxx11::string());
//    }
//    RDF RDF::fromFile(std::string filename, std::string format) {
//        return RDF();
//    }

    RDF RDF::fromString(const std::string &str, const std::string &format) {
        if (std::find(RDF::getValidParserNames().begin(), RDF::getValidParserNames().end(), format) ==
            RDF::getValidParserNames().end()) {
            std::ostringstream os;
            os << "Invalid Argument Exception: RDF::fromString: Format \"" << format
               << "\" is not a valid option. These are your options: ";
            for (auto &it : RDF::getValidParserNames()) {
                os << it << ", ";
            }
            throw std::invalid_argument(os.str());
        }

        RDF rdf;
        Reader reader(rdf.getModel(), format, "file://./annotations.rdf");
        reader.fromString(str);

        // pull "seen" namespaces out of the parser and pass them to RDF class
        rdf.seen_namespaces_ = reader.getSeenNamespaces();

        // Compare against predefined set of namespaces: keep ones we've seen
        rdf.namespaces_ = rdf.propagateNamespacesFromParser(rdf.seen_namespaces_);

        return rdf;
    }

    const LibrdfModel &RDF::getModel() const {
        return model_;
    }


    std::ostringstream RDF::listOptions() {
        raptor_world *raptor_world_ptr = raptor_new_world();
        int num_raptor_options = (int) raptor_option_get_count() - 1;
        std::ostringstream os;
        os << "option, name, label, domain, value type, url" << std::endl;
        int i = 0;
        while (i != num_raptor_options) {
            raptor_option_description *parser_opt = raptor_world_get_option_description(
                    raptor_world_ptr,
                    RAPTOR_DOMAIN_PARSER,
                    (raptor_option) i
            );
            if (parser_opt) {
                unsigned char *s = raptor_uri_to_string(parser_opt->uri);
                os << parser_opt->option << "," << parser_opt->name << "," << parser_opt->label << ","
                   << parser_opt->domain
                   << "," << parser_opt->value_type << "," << s << std::endl;
                free(s);
                raptor_free_option_description(parser_opt);
            } else {
                raptor_option_description *serializer_opt = raptor_world_get_option_description(
                        raptor_world_ptr,

                        RAPTOR_DOMAIN_SERIALIZER,
                        (raptor_option) i
                );
                if (serializer_opt) {
                    unsigned char *s = raptor_uri_to_string(serializer_opt->uri);
                    os << serializer_opt->option << "," << serializer_opt->name << "," << serializer_opt->label
                       << ","
                       << serializer_opt->domain
                       << "," << serializer_opt->value_type << "," << s
                       << std::endl;
                    free(s);
                }
                raptor_free_option_description(serializer_opt);
            }
            i++;
        };
        return os;
    }

    int RDF::size() const {
        return model_.size();
    }

    std::string RDF::toString(const std::string &format, const std::string &base_uri) {
        if (!base_uri.empty())
            setBaseUri(base_uri);
        Writer writer(model_, getBaseUri(), format);
        writer.registerNamespace(namespaces_);
        return writer.toString();
    }

    const std::string &RDF::getBaseUri() const {
        return base_uri_;
    }

    void RDF::setBaseUri(std::string baseUri) {
        base_uri_ = SemsimUtils::addFilePrefixToString(baseUri);
    }

    const NamespaceMap &RDF::getNamespaces() const {
        return namespaces_;
    }

    void RDF::setNamespaces(const NamespaceMap &namespaces) {
        namespaces_ = namespaces;
    }

    std::unordered_map<std::string, std::string>
    RDF::propagateNamespacesFromParser(std::vector<std::string> seen_namespaces) {
        std::unordered_map<std::string, std::string> keep_map;
        for (auto &seen_namespace : seen_namespaces) {
            auto iter = default_namespaces_.find(seen_namespace);
            if (iter != default_namespaces_.end()) {
                keep_map[seen_namespace] = default_namespaces_[seen_namespace];
            }
        }
        return keep_map;
    }

//    RDF RDF::fromXML(const std::string &filename, std::string format) {
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
//        RDF rdf(world, raptor_world_ptr, storage, model);
//
//        // pull "seen" namespaces out of the parser and pass them to RDF class
//        rdf.seen_namespaces_ = reader.getSeenNamespaces();
//
//        // Compare against predefined set of namespaces: keep ones we've seen
//        rdf.namespaces_ = rdf.propagateNamespacesFromParser(rdf.seen_namespaces_);
//
//        return rdf;
//    }

//    RDF RDF::fromOmex(const std::string &filename_or_url, std::string format) {
//        return RDF();
//    }


//    void RDF::toFile(std::string format) {
//
//    }


/********************************************************************
 * Other methods
 */



//    Editor RDF::toEditor(std::string xml, SemsimXmlType type) {
//        return Editor(xml, type, world_, model_, namespaces_);
//    }
//
//    Editor *RDF::toEditorPtr(std::string xml, SemsimXmlType type) {
//        return new Editor(xml, type, world_, model_, namespaces_);
//    }
//
//    LibrdfUri RDF::getBaseUri() const {
//        return base_uri_;
//    }
//
//    std::string RDF::getBaseUriAsString() const {
//        return base_uri_.str(); //std::string((const char *) librdf_uri_as_string(base_uri_));
//    }

//    void RDF::setBaseUri(std::string baseUri) {
//        baseUri = SemsimUtils::addFilePrefixToString(baseUri);
//        LibrdfUri uri = world_.newUri(baseUri);
//        if (!uri) {
//            throw LibRDFException("RDF::setBaseUri: Unable to create a new librdf_uri instance. ");
//        }
//        base_uri_ = uri;
//    }
//
//    void RDF::setBaseUri(LibrdfUri baseUri) {
//        if (!baseUri) {
//            throw LibRDFException("RDF::setBaseUri: Unable to create a new librdf_uri instance. ");
//        }
//        // check if file:// prepended to baseUri and if not add it.
//        base_uri_ = world_.newUri(
//                SemsimUtils::addFilePrefixToString(baseUri.str())
//        );
//    }
//
//    int RDF::size() const {
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
    Triples RDF::toTriples() {
//        LibrdfStream stream = model_.toStream();
        librdf_stream *stream = librdf_model_as_stream(model_.get());

        Triples triples;
        // todo turn this into method of LibrdfStream
        while (!librdf_stream_end(stream)) {
            librdf_statement* statement = librdf_stream_get_object(stream);

            std::cout << librdf_statement_get_subject(statement) << std::endl;
            triples.push_back(Triple::fromRawStatementPtr(statement));
            librdf_stream_next(stream);
        }
        librdf_free_stream(stream);
        return triples;
    }

//    std::string RDF::queryResultsAsStr(const std::string &query_str, const std::string &results_format) {
//        return Query(world_, model_, query_str).resultsAsStr(results_format);
//    }
//
//    ResultsMap RDF::queryResultsAsMap(const std::string &query_str) {
//        return Query(world_, model_, query_str).resultsAsMap();
//    }
//
//    Triples RDF::queryResultsAsTriples(const std::string &query_str) {
//        return queryResultsAsRDF(query_str).toTriples();
//    }
//
//    RDF RDF::queryResultsAsRDF(const std::string &query_str) {
//        return RDF::fromString(queryResultsAsStr(query_str, "rdfxml"), "rdfxml");
//    }
//

}


















