//
// Created by Ciaran on 5/31/2020.
//

#include "omexmeta/RDF.h"
#include "omexmeta/Options.h"
#include "omexmeta/PurgeRDFBag.h"
#include "redland/RedlandAPI.h"

namespace omexmeta {


    RDF::RDF(const std::string &storage_type, const std::string &storage_name,
             const char *storage_options, const char *model_options) {
        storage_ = LibrdfStorage(storage_type, storage_name, storage_options);
        // model_ now owns storage_
        model_ = LibrdfModel(storage_, model_options);

        // initialises the logger ;-)
        Logger::getLogger();
        REDLAND_DEBUG("Created an empty RDF graph");
    }


    RDF::RDF(RDF &&rdf) noexcept {
        REDLAND_DEBUG("Moved an RDF graph");
        namespaces_ = std::move(rdf.namespaces_);
        seen_namespaces_ = std::move(rdf.seen_namespaces_);
        storage_ = std::move(rdf.storage_);
        model_ = std::move(rdf.model_);
    }

    RDF &RDF::operator=(RDF &&rdf) noexcept {
        if (this != &rdf) {
            REDLAND_DEBUG("Move assigned an RDF graph");
            namespaces_ = std::move(rdf.namespaces_);
            seen_namespaces_ = std::move(rdf.seen_namespaces_);
            storage_ = std::move(rdf.storage_);
            model_ = std::move(rdf.model_);
        }
        return *this;
    }

    int RDF::size() const {
        return model_.size();
    }

    bool RDF::empty() const {
        return size() == 0;
    }

    RDF RDF::fromString(const std::string &str, const std::string &syntax) {
        RDF rdf;
        LibrdfParser parser(syntax);
        LibrdfUri u(rdf.getModelUri());
        parser.parseString(str, rdf.model_, u);

        // update the list of "seen" namespaces
        rdf.seen_namespaces_ = parser.getSeenNamespaces(std::vector<std::string>());

        // Compare against predefined set of namespaces: bqbiol etc.
        // This allows us to only use the ones that are needed
        rdf.namespaces_ = rdf.propagateNamespacesFromParser(rdf.seen_namespaces_);

        // when reading xml types, we try to classify the string as sbml or cellml.
        // other syntaxs ignored.
        // this will set the xmlType variable if sbml or cellml
        rdf.classifyXmlType(str, syntax);
        // Here we use the semantic extraction tool to collect
        // information if were using sbml
        rdf.extractSemanticInformationFromSBML(str);

        if (Options::translateVCard_)
            rdf.translateVcard();

        if (Options::removeRDFBag_)
            rdf.purgeRDFBag();
        return rdf;
    }

    void RDF::purgeRDFBag() {
        // remove rdf bag constructs
        PurgeRDFBag purger(this);
        purger.purge();
    }

    void RDF::translateVcard() {
        // remove rdf bag constructs
        VCardTranslator translator(this);
        translator.translate();
    }

    void RDF::addFromString(const std::string &str,
                            const std::string &syntax) {

        LibrdfParser parser(syntax);

        LibrdfUri u = LibrdfUri::fromFilename(getModelUri());
        parser.parseString(str, model_, u);

        // update the list of "seen" namespaces
        seen_namespaces_ = parser.getSeenNamespaces(seen_namespaces_);

        // Compare against predefined set of namespaces: bqbiol etc.
        // This allows us to only use the ones that are needed
        namespaces_ = propagateNamespacesFromParser(seen_namespaces_);

        // this will set the xmlType variable if sbml or cellml
        classifyXmlType(str, syntax);

        extractSemanticInformationFromSBML(str);

        if (Options::translateVCard_)
            translateVcard();

        if (Options::removeRDFBag_)
            purgeRDFBag();
    }

    /**
     * @brief parse RDF directly from a uri
     * @param uri_string the uri to download containing RDF
     * @param syntax the syntax that the RDF is in
     * @return RDF an instantiated RDF object.
     *
     * @details downloads uri from the internet and creates an RDF graph.
     * See Librdf::parseUri() for more details.
     */
    RDF RDF::fromUri(const std::string &uri_string, const std::string &syntax) {
        RDF rdf;
        LibrdfParser parser(syntax);
        parser.parseUri(uri_string, rdf.model_);

        // update the list of "seen" namespaces
        rdf.seen_namespaces_ = parser.getSeenNamespaces(rdf.seen_namespaces_);

        // Compare against predefined set of namespaces: bqbiol etc.
        // This allows us to only use the ones that are needed
        rdf.namespaces_ = rdf.propagateNamespacesFromParser(rdf.seen_namespaces_);
        rdf.extractSemanticInformationFromSBML(uri_string);


        if (Options::translateVCard_)
            rdf.translateVcard();

        if (Options::removeRDFBag_)
            rdf.purgeRDFBag();

        return rdf;
    }

    /**
     * @brief non-static counterpart of RDF::fromUri. Downloads and
     * parses rdf from a URI.
     *
     * @details See RDF::fromUri for details.
     */
    void RDF::addFromUri(const std::string &uri_string, const std::string &syntax) {
        LibrdfParser parser(syntax);
        parser.parseUri(uri_string, model_);

        // update the list of "seen" namespaces
        seen_namespaces_ = parser.getSeenNamespaces(seen_namespaces_);

        // Compare against predefined set of namespaces: bqbiol etc.
        // This allows us to only use the ones that are needed
        namespaces_ = propagateNamespacesFromParser(seen_namespaces_);
        extractSemanticInformationFromSBML(uri_string);

        if (Options::translateVCard_)
            translateVcard();

        if (Options::removeRDFBag_)
            purgeRDFBag();
    }

    RDF RDF::fromFile(const std::string &filename, const std::string &syntax) {
        RDF rdf;
        LibrdfParser parser(syntax);
        parser.parseFile(filename, rdf.model_, rdf.getModelUri());

        std::cout << "ttle:" << rdf.toString("turtle") << std::endl;
        rdf.classifyXmlTypeFromFile(filename, syntax);
        // update the list of "seen" namespaces
        rdf.seen_namespaces_ = parser.getSeenNamespaces(rdf.seen_namespaces_);
        // Compare against predefined set of namespaces: bqbiol etc.
        // This allows us to only use the ones that are needed
        rdf.namespaces_ = rdf.propagateNamespacesFromParser(rdf.seen_namespaces_);
        // Here we use the semantic extraction tool to collect
        // information if were using sbml
        rdf.extractSemanticInformationFromSBML(filename);

        if (Options::translateVCard_)
            rdf.translateVcard();

        if (Options::removeRDFBag_)
            rdf.purgeRDFBag();

        return rdf;
    }

    void RDF::addFromFile(const std::string &filename, const std::string &syntax) {
        LibrdfParser parser(syntax);
        parser.parseFile(filename, model_, getModelUri());
        classifyXmlTypeFromFile(filename, syntax);
        // update the list of "seen" namespaces
        seen_namespaces_ = parser.getSeenNamespaces(seen_namespaces_);

        // Compare against predefined set of namespaces: bqbiol etc.
        // This allows us to only use the ones that are needed
        namespaces_ = propagateNamespacesFromParser(seen_namespaces_);

        extractSemanticInformationFromSBML(filename);

        if (Options::translateVCard_)
            translateVcard();

        if (Options::removeRDFBag_)
            purgeRDFBag();
    }

    /**
     * @brief compared namespaces seen with namespaces
     * known and ensures models that use a known namespace
     * use that namespace.
     * @param seen_namespaces a vector of strings of namespaces the parser has seen before.
     *
     */
    std::unordered_map<std::string, std::string>
    RDF::propagateNamespacesFromParser(const std::vector<std::string> &seen_namespaces) {
        std::unordered_map<std::string, std::string> keep_map;

        // flip the namespace map for this method:
        NamespaceMap flippedNSMap;
        for (auto &it : Predicate::namespaceMap()) {
            flippedNSMap[it.second] = it.first;
        }

        for (auto &seen_namespace : seen_namespaces) {
            auto iter = flippedNSMap.find(seen_namespace);
            if (iter != flippedNSMap.end()) {
                keep_map[seen_namespace] = flippedNSMap[seen_namespace];
            }
        }
        return keep_map;
    }

    std::string RDF::toString(const std::string &syntax,
                              const char *mime_type,
                              const char *type_uri) {
        LibrdfSerializer serializer(syntax.c_str(), mime_type, type_uri);
        // remember to add namespaces taken from parser
        for (auto &it : namespaces_) {
            serializer.setNamespace(it.first, it.second);
        }
        serializer.setNamespace(getRepositoryUri(), "OMEXlib");
        serializer.setNamespace(getLocalUri(), "local");
        return serializer.toString("base", model_);
    }

    std::string RDF::queryResultsAsString(const std::string &query_str, const std::string &results_syntax) const {
        // create query object
        LibrdfQuery query(query_str, getModel());
        LibrdfQueryResults results = query.execute();
        return results.toString(results_syntax);
    }

    ResultsMap RDF::queryResultsAsMap(const std::string &query_str) const {
        LibrdfQuery query(query_str, getModel());
        LibrdfQueryResults results = query.execute();
        return results.map();
    }

    void RDF::toFile(const std::string &filename, const std::string &syntax, const char *mime_type, const char *type_uri) {
        std::string string_syntax = toString(syntax, mime_type, type_uri);
        std::ofstream f(filename);
        if (f.is_open()) {
            f << string_syntax << std::endl;
            f.flush();
            f.close();
        } else {
            throw std::logic_error("std::logic_error: RDF::toFile: Could not open file for writing. ");
        }
    }

    LibrdfModel RDF::getModel() const {
        // do not increment usage here, causes memory leaks
        return model_;
    }

    Editor RDF::toEditor(const std::string &xml, bool generate_new_metaids, bool sbml_semantic_extraction) {
        return Editor(xml, false, model_, namespaces_, uriHandler_, generate_new_metaids, sbml_semantic_extraction);
    }

    Editor *RDF::toEditorPtr(const std::string &xml, bool generate_new_metaids, bool sbml_semantic_extraction) {
        auto *editor = new Editor(xml, false, model_, namespaces_, uriHandler_, generate_new_metaids, sbml_semantic_extraction);
        return editor;
    }

    LibrdfStorage RDF::getStorage() const {
        return storage_;
    }

    int RDF::commitTransaction() const {
        return getModel().commitTransaction();
    }

    int RDF::startTransaction() const {
        return getModel().startTransaction();
    }

    void *RDF::getTransactionHandle() const {
        return getModel().getTransactionHandle();
    }

    int RDF::startTransactionWithHandle(void *handle) const {
         return getModel().startTransactionWithHandle(handle);
    }

    int RDF::getTransactionRollback() const {
        return getModel().getTransactionRollback();
    }

    std::ostringstream RDF::listOptions() {
        raptor_world *raptor_world_ptr = LibrdfWorld::getRaptor();
        int num_raptor_options = (int) raptor_option_get_count() - 1;
        std::ostringstream os;
        os << "option, name, label, domain, value type, uri" << std::endl;
        int i = 0;
        while (i != num_raptor_options) {
            raptor_option_description *parser_opt = raptor_world_get_option_description(
                    raptor_world_ptr,
                    RAPTOR_DOMAIN_PARSER,
                    (raptor_option) i);
            if (parser_opt) {
                unsigned char *uri_string1 = raptor_uri_to_string(parser_opt->uri);
                os << parser_opt->option << "," << parser_opt->name << "," << parser_opt->label << ","
                   << parser_opt->domain
                   << "," << parser_opt->value_type << "," << uri_string1 << std::endl;
                raptor_free_option_description(parser_opt);
                free(uri_string1);
            } else {
                raptor_option_description *serializer_opt = raptor_world_get_option_description(
                        raptor_world_ptr,
                        RAPTOR_DOMAIN_SERIALIZER,
                        (raptor_option) i);
                if (serializer_opt) {
                    unsigned char *uri_string2 = raptor_uri_to_string(serializer_opt->uri);
                    os << serializer_opt->option << "," << serializer_opt->name << "," << serializer_opt->label
                       << ","
                       << serializer_opt->domain
                       << "," << serializer_opt->value_type << "," << uri_string2
                       << std::endl;
                    raptor_free_option_description(serializer_opt);
                    free(uri_string2);
                }
            }
            i++;
        };

        return os;
    }

    const std::string &RDF::getRepositoryUri() const {
        return uriHandler_.getRepositoryUri();
    }

    void RDF::setRepositoryUri(const std::string &repositoryName) {
        uriHandler_.setRepositoryUri(repositoryName);
    }

    const std::string &RDF::getArchiveUri() const {
        return uriHandler_.getArchiveUri();
    }

    void RDF::setArchiveUri(const std::string &archiveName) {
        uriHandler_.setArchiveUri(archiveName);
    }

    const std::string &RDF::getModelUri() const {
        return uriHandler_.getModelUri();
    }

    void RDF::setModelUri(std::string modelName) {
        uriHandler_.setModelUri(std::move(modelName));
    }

    const std::string &RDF::getModelMetaid() {
        return uriHandler_.getModelMetaid();
    }

    void RDF::setModelMetaid(const std::string &modelMetaid) {
        uriHandler_.setModelMetaid(modelMetaid);
    }

    std::string RDF::getModelLevelAnnotationUri() {
        return uriHandler_.getModelLevelAnnotationUri();
    }

    const std::string &RDF::getLocalUri() const {
        return uriHandler_.getLocalUri();
    }

    OmexMetaXmlType RDF::getXmlType() const {
        return xmlType;
    }

    void RDF::setXmlType(OmexMetaXmlType xmlType) {
        RDF::xmlType = xmlType;
    }

    void RDF::classifyXmlType(const std::string &xml, const std::string &input_syntax) {
        // when reading xml types, we try to classify the string
        if (input_syntax == "rdfxml" || input_syntax == "rdfxml-abbrev" || input_syntax == "rdfxml-xmp") {
            MarkupIdentifier identifier(xml);
            if (getXmlType() == OMEXMETA_TYPE_NOTSET) {
                if (identifier.isSBML())
                    setXmlType(OMEXMETA_TYPE_SBML);
                else if (identifier.isCellML())
                    setXmlType(OMEXMETA_TYPE_CELLML);
                else if (identifier.isCellML() && identifier.isCellML())
                    setXmlType(OMEXMETA_TYPE_UNKNOWN);
            } else {
                // prevent crossing annotation types.
                if (getXmlType() == OMEXMETA_TYPE_SBML && !identifier.isSBML()) {
                    throw std::logic_error("Previously you read from sbml but input xml is not sbml");
                } else if (getXmlType() == OMEXMETA_TYPE_CELLML && !identifier.isCellML())
                    throw std::logic_error("Previously you read from sbml but input xml is not sbml");
            }
        } else {
            setXmlType(OMEXMETA_TYPE_UNKNOWN);
        }
    }

    void RDF::classifyXmlTypeFromFile(const std::string &xml_file, const std::string &input_syntax) {
        if (!OmexMetaUtils::exists(xml_file)) {
            std::ostringstream os;
            os << "File called \"" + xml_file + "\" does not exist.";
            throw std::logic_error(os.str());
        }
        std::ifstream t(xml_file);
        std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
        classifyXmlType(str, input_syntax);
    }

    void RDF::extractSemanticInformationFromSBML(const std::string &sbml) {
        std::string str;
        // if sbml is a filename on disk read it into a string
        if (OmexMetaUtils::exists(sbml)) {
            std::ifstream t(sbml);
            std::string x((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
            str = x;
        } else {
            str = sbml;
        }
        if (getXmlType() == OMEXMETA_TYPE_SBML) {
            // Opening an SBML model in the editor automatically uses
            // the SBMLSemanticExtraction class to get the information we want.
            // see constructor for Editor.
            Editor editor = toEditor(str, true);
        }
    }
    bool RDF::operator==(const RDF &rhs) const {
        return model_ == rhs.model_;
    }
    bool RDF::operator!=(const RDF &rhs) const {
        return !(rhs == *this);
    }

    void RDF::addTriple(const Triple &triple) {
        model_.addStatement(triple);
        // after adding content to the model we need to
        // update namespace information
        seen_namespaces_.push_back(triple.getPredicateNode().str());
        namespaces_ = propagateNamespacesFromParser(seen_namespaces_);
    }

    void RDF::addTriples(Triples &triples) {
        for (auto &triple : triples) {
            model_.addStatement(triple);
            seen_namespaces_.push_back(triple.getPredicateNode().getNamespace());
            namespaces_ = propagateNamespacesFromParser(seen_namespaces_);
        }
    }


    bool RDF::equals(RDF *actual, RDF *expected, const std::string &syntax, bool verbose) {
        bool equal = *expected == *actual;
        if (verbose && !equal) {
            std::cout << "Expected does not equal actual: " << std::endl;
            std::cout << "Expected:" << std::endl;
            std::cout << expected->toString(syntax) << std::endl;
            std::cout << "Actual : " << std::endl;
            std::cout << actual->toString(syntax) << std::endl;
        }
        return equal;
    }
    bool RDF::equals(RDF *actual, const std::string &expected_string, const std::string &syntax, bool verbose) {
        RDF expected = RDF::fromString(expected_string, syntax);
        bool equal = expected == *actual;
        if (verbose && !equal) {
            std::cout << "Expected does not equal actual: " << std::endl;
            std::cout << "Expected:" << std::endl;
            std::cout << expected.toString(syntax) << std::endl;
            std::cout << "Actual : " << std::endl;
            std::cout << actual->toString(syntax) << std::endl;
        }
        return equal;
    }

    bool RDF::equals(const Triple &actual, const std::string &expected_string, const std::string &syntax, bool verbose) {
        RDF actual_rdf;
        actual_rdf.addTriple(actual);

        RDF expected_rdf = RDF::fromString(expected_string);
        bool equal = expected_rdf == actual_rdf;
        if (verbose && !equal) {
            std::cout << "Expected does not equal actual: " << std::endl;
            std::cout << "Expected:" << std::endl;
            std::cout << expected_rdf.toString(syntax) << std::endl;
            std::cout << "Actual : " << std::endl;
            std::cout << actual_rdf.toString(syntax) << std::endl;
        }
        return equal;
    }

    bool RDF::equals(Triples &actual, const std::string &expected_string, const std::string &syntax, bool verbose) {
        RDF actual_rdf;
        actual_rdf.addTriples(actual);

        RDF expected_rdf = RDF::fromString(expected_string);
        bool equal = expected_rdf == actual_rdf;
        if (verbose && !equal) {
            std::cout << "Expected does not equal actual: " << std::endl;
            std::cout << "Expected:" << std::endl;
            std::cout << expected_rdf.toString(syntax) << std::endl;
            std::cout << "Actual : " << std::endl;
            std::cout << actual_rdf.toString(syntax) << std::endl;
        }
        return equal;
    }

    bool RDF::equals(const std::string &first, const std::string &second, const std::string &first_syntax, const std::string &second_syntax, bool verbose) {
        RDF first_rdf = RDF::fromString(first, first_syntax);
        RDF second_rdf = RDF::fromString(second, second_syntax);
        bool equal = first_syntax == second_syntax;
        if (verbose && !equal) {
            std::cout << "First rdf string does not equal second rdf string: " << std::endl;
            std::cout << "first:" << std::endl;
            std::cout << first_rdf.toString("turtle") << std::endl;
            std::cout << "Actual : " << std::endl;
            std::cout << second_rdf.toString("turtle") << std::endl;
        }
        return equal;
    }


    UriHandler &RDF::getUriHandler() {
        return uriHandler_;
    }


}// namespace omexmeta
