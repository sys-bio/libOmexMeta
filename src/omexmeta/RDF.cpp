//
// Created by Ciaran on 5/31/2020.
//

#include "omexmeta/RDF.h"

#include <utility>


namespace omexmeta {

    RDF::RDF(const std::string &storage_type, const std::string &storage_name,
             const char *storage_options, const char *model_options) {
        storage_ = LibrdfStorage(storage_type, storage_name, storage_options);
        // model_ now owns storage_
        model_ = LibrdfModel(storage_.get(), model_options);
    }

    void RDF::freeRDF() {
        model_.freeModel();
        storage_.freeStorage();
    }

    RDF::~RDF() {
        freeRDF();
    }

    RDF::RDF(RDF &&rdf) noexcept {
        namespaces_ = std::move(rdf.namespaces_);
        seen_namespaces_ = std::move(rdf.seen_namespaces_);
        storage_ = std::move(rdf.storage_);
        model_ = std::move(rdf.model_);
    }

    RDF &RDF::operator=(RDF &&rdf) noexcept {
        if (this != &rdf) {
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

    RDF RDF::fromString(const std::string &str, const std::string &format) {
        RDF rdf;
        LibrdfParser parser(format);
        LibrdfUri u(rdf.getLocalUri());
        parser.parseString(str, rdf.model_, u);
        u.freeUri();

        // update the list of "seen" namespaces
        rdf.seen_namespaces_ = parser.getSeenNamespaces(std::vector<std::string>());

        // Compare against predefined set of namespaces: bqbiol etc.
        // This allows us to only use the ones that are needed
        rdf.namespaces_ = rdf.propagateNamespacesFromParser(rdf.seen_namespaces_);

        // when reading xml types, we try to classify the string as sbml or cellml.
        // other formats ignored.
        // this will set the xmlType variable if sbml or cellml
        rdf.classifyXmlType(str, format);
        // Here we use the semantic extraction tool to collect
        // information if were using sbml
        rdf.extractSemanticInformationFromSBML(str);

        return rdf;
    }

    [[maybe_unused]] void
    RDF::fromString(RDF *rdf, const std::string &str, const std::string &format, std::string base_uri) {
        // if the base_uri is a web uri we leave it alone
        base_uri = OmexMetaUtils::prepareBaseUri(base_uri);

        LibrdfParser parser(format);
        parser.parseString(str, rdf->model_, LibrdfUri(base_uri));

        // update the list of "seen" namespaces
        rdf->seen_namespaces_ = parser.getSeenNamespaces(std::vector<std::string>());

        // Compare against predefined set of namespaces: bqbiol etc.
        // This allows us to only use the ones that are needed
        rdf->namespaces_ = rdf->propagateNamespacesFromParser(rdf->seen_namespaces_);

        // this will set the xmlType variable if sbml or cellml
        rdf->classifyXmlType(str, format);
        rdf->extractSemanticInformationFromSBML(str);
    }

    void RDF::addFromString(const std::string &str,
                            const std::string &format) {

        LibrdfParser parser(format);

        LibrdfUri u = LibrdfUri::fromFilename(getLocalUri());
        parser.parseString(str, model_, u);
        u.freeUri();

        // update the list of "seen" namespaces
        seen_namespaces_ = parser.getSeenNamespaces(seen_namespaces_);

        // Compare against predefined set of namespaces: bqbiol etc.
        // This allows us to only use the ones that are needed
        namespaces_ = propagateNamespacesFromParser(seen_namespaces_);

        // this will set the xmlType variable if sbml or cellml
        classifyXmlType(str, format);

        extractSemanticInformationFromSBML(str);
    }

    /**
     * @brief parse RDF directly from a uri
     * @param uri_string the uri to download containing RDF
     * @param format the format that the RDF is in
     * @return RDF an instantiated RDF object.
     *
     * @details downloads uri from the internet and creates an RDF graph.
     * See Librdf::parseUri() for more details.
     */
    RDF RDF::fromUri(const std::string &uri_string, const std::string &format) {
        RDF rdf;
        LibrdfParser parser(format);
        parser.parseUri(uri_string, rdf.model_);

        // update the list of "seen" namespaces
        rdf.seen_namespaces_ = parser.getSeenNamespaces(rdf.seen_namespaces_);

        // Compare against predefined set of namespaces: bqbiol etc.
        // This allows us to only use the ones that are needed
        rdf.namespaces_ = rdf.propagateNamespacesFromParser(rdf.seen_namespaces_);
        rdf.extractSemanticInformationFromSBML(uri_string);
        return rdf;
    }

    /**
     * @brief non-static counterpart of RDF::fromUri. Downloads and
     * parses rdf from a URI.
     *
     * @details See RDF::fromUri for details.
     */
    void RDF::addFromUri(const std::string &uri_string, const std::string &format) {
        LibrdfParser parser(format);
        parser.parseUri(uri_string, model_);

        // update the list of "seen" namespaces
        seen_namespaces_ = parser.getSeenNamespaces(seen_namespaces_);

        // Compare against predefined set of namespaces: bqbiol etc.
        // This allows us to only use the ones that are needed
        namespaces_ = propagateNamespacesFromParser(seen_namespaces_);
        extractSemanticInformationFromSBML(uri_string);
    }

    RDF RDF::fromFile(const std::string &filename, const std::string &format) {
        RDF rdf;
        LibrdfParser parser(format);
        parser.parseFile(filename, rdf.model_, rdf.getLocalUri());
        rdf.classifyXmlTypeFromFile(filename, format);
        // update the list of "seen" namespaces
        rdf.seen_namespaces_ = parser.getSeenNamespaces(rdf.seen_namespaces_);
        // Compare against predefined set of namespaces: bqbiol etc.
        // This allows us to only use the ones that are needed
        rdf.namespaces_ = rdf.propagateNamespacesFromParser(rdf.seen_namespaces_);
        // Here we use the semantic extraction tool to collect
        // information if were using sbml
        rdf.extractSemanticInformationFromSBML(filename);
        return rdf;
    }

    void RDF::addFromFile(const std::string &filename, const std::string &format) {
        LibrdfParser parser(format);
        parser.parseFile(filename, model_, getLocalUri());
        classifyXmlTypeFromFile(filename, format);
        // update the list of "seen" namespaces
        seen_namespaces_ = parser.getSeenNamespaces(seen_namespaces_);

        // Compare against predefined set of namespaces: bqbiol etc.
        // This allows us to only use the ones that are needed
        namespaces_ = propagateNamespacesFromParser(seen_namespaces_);

        extractSemanticInformationFromSBML(filename);
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

    std::string RDF::toString(const std::string &format,
                              const char *mime_type,
                              const char *type_uri) {
        LibrdfSerializer serializer(format.c_str(), mime_type, type_uri);
        // remember to add namespaces taken from parser
        for (auto &it : namespaces_) {
            serializer.setNamespace(it.first, it.second);
        }
        serializer.setNamespace(getRepositoryUri(), "OMEXlib");
        serializer.setNamespace(getLocalUri(), "local");
        return serializer.toString("base", model_);
    }

    std::string RDF::query(const std::string &query_str, const std::string &results_format) const {
        Query query(getModel(), query_str);
        std::string results = query.resultsAsStr(results_format);
        query.freeQuery();
        return results;
    }

    void
    RDF::toFile(const std::string &filename, const std::string &format, const char *mime_type, const char *type_uri) {
        std::string syntax = toString(format, mime_type, type_uri);
        std::ofstream f(filename);
        if (f.is_open()) {
            f << syntax << std::endl;
            f.flush();
            f.close();
        } else {
            throw std::logic_error("std::logic_error: RDF::toFile: Could not open file for writing. ");
        }
    }

    librdf_model *RDF::getModel() const {
        return model_.get();
    }

    Editor RDF::toEditor(const std::string &xml, bool generate_new_metaids, bool sbml_semantic_extraction) {
        return Editor(xml, false, model_, namespaces_, generate_new_metaids, sbml_semantic_extraction,
                      getRepositoryUri(), getArchiveUri(), getModelUri(), getLocalUri());
    }

    Editor *RDF::toEditorPtr(const std::string &xml, bool generate_new_metaids, bool sbml_semantic_extraction) {
        auto *editor = new Editor(xml, false, model_, namespaces_, generate_new_metaids, sbml_semantic_extraction,
                                  getRepositoryUri(), getArchiveUri(), getModelUri(), getLocalUri());
        return editor;
    }

    librdf_storage *RDF::getStorage() const {
        return storage_.get();
    }

    int RDF::commitTransaction() const {
        return librdf_model_transaction_commit(getModel());
    }

    int RDF::startTransaction() const {
        return librdf_model_transaction_start(getModel());
    }

    void *RDF::getTransactionHandle() const {
        return librdf_model_transaction_get_handle(getModel());
    }

    int RDF::startTransactionWithHandle(void *handle) const {
        return librdf_model_transaction_start_with_handle(getModel(), handle);
    }

    int RDF::getTransactionRollback() const {
        return librdf_model_transaction_rollback(getModel());
    }

    std::ostringstream RDF::listOptions() {
        raptor_world *raptor_world_ptr = World::getRaptor();
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
        return uriHandler_.getRepository();
    }

    void RDF::setRepositoryUri(const std::string& repositoryName) {
        uriHandler_.setRepository(repositoryName);
    }

    const std::string &RDF::getArchiveUri() const {
        return uriHandler_.getArchive();
    }

    void RDF::setArchiveUri(const std::string& archiveName) {
        uriHandler_.setArchive(archiveName);
    }

    const std::string &RDF::getModelUri() const {
        return uriHandler_.getModel();
    }

    void RDF::setModelUri(std::string modelName){
        uriHandler_.setModel(std::move(modelName));
    }

    const std::string &RDF::getLocalUri() const {
        return uriHandler_.getLocal();
    }

    OmexMetaXmlType RDF::getXmlType() const {
        return xmlType;
    }

    void RDF::setXmlType(OmexMetaXmlType xmlType) {
        RDF::xmlType = xmlType;
    }

    void RDF::classifyXmlType(const std::string &xml, const std::string &input_format) {
        // when reading xml types, we try to classify the string
        if (input_format == "rdfxml" || input_format == "rdfxml-abbrev" || input_format == "rdfxml-xmp") {
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

    void RDF::classifyXmlTypeFromFile(const std::string &xml_file, const std::string &input_format) {
        if (!OmexMetaUtils::exists(xml_file)) {
            std::ostringstream os;
            os << "File called \"" + xml_file + "\" does not exist.";
            throw std::logic_error(os.str());
        }
        std::ifstream t(xml_file);
        std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
        classifyXmlType(str, input_format);
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
        model_.addStatement(triple.getStatement());
        // after adding content to the model we need to
        // update namespace information
        seen_namespaces_.push_back(triple.getPredicateStr());
        namespaces_ = propagateNamespacesFromParser(seen_namespaces_);
    }

    void RDF::addTriples(const Triples &triples) {
        for (int i = 0; i < triples.size(); i++) {
            const Triple &triple = triples[i];
            model_.addStatement(triple.getStatement());
            const std::string &ns = LibrdfNode(triple.getPredicate()).getNamespace();
            seen_namespaces_.push_back(triple.getPredicateNamespaceStr());
            namespaces_ = propagateNamespacesFromParser(seen_namespaces_);
        }
    }


    bool RDF::equals(RDF *actual, RDF *expected, const std::string &format) {
        bool equal = *expected == *actual;
        if (!equal) {
            std::cout << "Expected does not equal actual: " << std::endl;
            std::cout << "Expected:" << std::endl;
            std::cout << expected->toString(format) << std::endl;
            std::cout << "Actual : " << std::endl;
            std::cout << actual->toString(format) << std::endl;
        }
        return equal;
    }
    bool RDF::equals(RDF *actual, const std::string &expected_string, const std::string &format) {
        RDF expected = RDF::fromString(expected_string, format);
        bool equal = expected == *actual;
        if (!equal) {
            std::cout << "Expected does not equal actual: " << std::endl;
            std::cout << "Expected:" << std::endl;
            std::cout << expected.toString(format) << std::endl;
            std::cout << "Actual : " << std::endl;
            std::cout << actual->toString(format) << std::endl;
        }
        return equal;
    }

    bool RDF::equals(const Triple &actual, const std::string &expected_string, const std::string &format) {
        RDF actual_rdf;
        actual_rdf.addTriple(actual);

        RDF expected_rdf = RDF::fromString(expected_string);
        bool equal = expected_rdf == actual_rdf;
        if (!equal) {
            std::cout << "Expected does not equal actual: " << std::endl;
            std::cout << "Expected:" << std::endl;
            std::cout << expected_rdf.toString(format) << std::endl;
            std::cout << "Actual : " << std::endl;
            std::cout << actual_rdf.toString(format) << std::endl;
        }
        return equal;
    }

    bool RDF::equals(const Triples &actual, const std::string &expected_string, const std::string &format) {
        RDF actual_rdf;
        actual_rdf.addTriples(actual);

        RDF expected_rdf = RDF::fromString(expected_string);
        bool equal = expected_rdf == actual_rdf;
        if (!equal) {
            std::cout << "Expected does not equal actual: " << std::endl;
            std::cout << "Expected:" << std::endl;
            std::cout << expected_rdf.toString(format) << std::endl;
            std::cout << "Actual : " << std::endl;
            std::cout << actual_rdf.toString(format) << std::endl;
        }
        return equal;
    }

    bool RDF::equals(const std::string &first, const std::string &second, const std::string &first_format, const std::string &second_format) {
        RDF first_rdf = RDF::fromString(first, first_format);
        RDF second_rdf = RDF::fromString(second, second_format);
        bool equal = first_format == second_format;
        if (!equal) {
            std::cout << "First rdf string does not equal second rdf string: " << std::endl;
            std::cout << "first:" << std::endl;
            std::cout << first_rdf.toString("turtle") << std::endl;
            std::cout << "Actual : " << std::endl;
            std::cout << second_rdf.toString("turtle") << std::endl;
        }
        return equal;
    }


}// namespace omexmeta
