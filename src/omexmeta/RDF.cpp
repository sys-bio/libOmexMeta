//
// Created by Ciaran on 5/31/2020.
//

#include "omexmeta/RDF.h"


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
        default_namespaces_ = std::move(rdf.default_namespaces_);
        storage_ = std::move(rdf.storage_);
        model_ = std::move(rdf.model_);
    }

    RDF &RDF::operator=(RDF &&rdf) noexcept {
        if (this != &rdf) {
            namespaces_ = std::move(rdf.namespaces_);
            seen_namespaces_ = std::move(rdf.seen_namespaces_);
            default_namespaces_ = std::move(rdf.default_namespaces_);
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
        rdf.seen_namespaces_ = parser.getSeenNamespaces();

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
        rdf->seen_namespaces_ = parser.getSeenNamespaces();

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
        seen_namespaces_ = parser.getSeenNamespaces();

        // Compare against predefined set of namespaces: bqbiol etc.
        // This allows us to only use the ones that are needed
        namespaces_ = propagateNamespacesFromParser(seen_namespaces_);

        // this will set the xmlType variable if sbml or cellml
        classifyXmlType(str, format);

        extractSemanticInformationFromSBML(str);


    }

    /*
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
        rdf.seen_namespaces_ = parser.getSeenNamespaces();

        // Compare against predefined set of namespaces: bqbiol etc.
        // This allows us to only use the ones that are needed
        rdf.namespaces_ = rdf.propagateNamespacesFromParser(rdf.seen_namespaces_);
        rdf.extractSemanticInformationFromSBML(uri_string);
        return rdf;
    }

    /*
     * @brief non-static counterpart of RDF::fromUri. Downloads and
     * parses rdf from a URI.
     *
     * @details See RDF::fromUri for details.
     */
    void RDF::addFromUri(const std::string &uri_string, const std::string &format) {
        LibrdfParser parser(format);
        parser.parseUri(uri_string, model_);

        // update the list of "seen" namespaces
        seen_namespaces_ = parser.getSeenNamespaces();

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
        rdf.seen_namespaces_ = parser.getSeenNamespaces();

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
        seen_namespaces_ = parser.getSeenNamespaces();

        // Compare against predefined set of namespaces: bqbiol etc.
        // This allows us to only use the ones that are needed
        namespaces_ = propagateNamespacesFromParser(seen_namespaces_);

        extractSemanticInformationFromSBML(filename);
    }

    /*
     * @brief compared namespaces seen with namespaces
     * known and ensures models that use a known namespace
     * use that namespace.
     * @param seen_namespaces a vector of strings of namespaces the parser has seen before.
     *
     */
    std::unordered_map<std::string, std::string>
    RDF::propagateNamespacesFromParser(const std::vector<std::string> &seen_namespaces) {
        std::unordered_map<std::string, std::string> keep_map;
        for (auto &seen_namespace : seen_namespaces) {
            auto iter = default_namespaces_.find(seen_namespace);
            if (iter != default_namespaces_.end()) {
                keep_map[seen_namespace] = default_namespaces_[seen_namespace];
            }
        }
        return keep_map;
    }

    std::string RDF::toString(const std::string &format,
                              const char *mime_type,
                              const char *type_uri) {
        LibrdfSerializer serializer(format.c_str(), mime_type, type_uri);
        // remember to add namespaces taken from parser
        for (auto &it: namespaces_) {
            serializer.setNamespace(it.first, it.second);
        }
        //todo play around with myOMEX
        serializer.setNamespace(getRepositoryUri(), "OMEXlib");
        serializer.setNamespace(getArchiveUri(), "myOMEX");
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
                    (raptor_option) i
            );
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
                        (raptor_option) i
                );
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
        return repository_uri_;
    }

    void RDF::setRepositoryUri(std::string repositoryName) {
        if (!OmexMetaUtils::startsWith(repositoryName, "http")) {
            throw std::invalid_argument("std::invalid_argument: RDF::setRepositoryUri: "
                                        "Specified \"repositoryName\" argument \"" + repositoryName
                                        + "\" does not begin with \"http\". Example: \"http://MyOmexRepository.org\"");
        }
        if (!OmexMetaUtils::endsWith(repositoryName, "/")) {
            repositoryName += "/";
        }
        repository_uri_ = repositoryName;
    }

    const std::string &RDF::getArchiveUri() const {
        return archive_uri_;
    }

    void RDF::setArchiveUri(std::string archiveName) {
        if (OmexMetaUtils::startsWith(archiveName, "http")) {
            throw std::invalid_argument("std::invalid_argument: RDF::setArchiveUri: "
                                        "Specified \"archiveName\" argument \"" + archiveName
                                        + "\" begins with \"http\". Since the archive url is built "
                                          "using the repositoryName argument, please only specify "
                                          "the name of the omex archive. Like \"myOmexFile.omex\"");
        }
        if (!OmexMetaUtils::endsWith(archiveName, ".omex")) {
            archiveName = archiveName + ".omex";
        }
        archive_uri_ = getRepositoryUri() + archiveName;
    }

    const std::string &RDF::getModelUri() const {
        return model_uri_;
    }

    void RDF::setModelUri(std::string modelName) {
        if (OmexMetaUtils::startsWith(modelName, "http")) {
            throw std::invalid_argument("std::invalid_argument: RDF::setModelUri: "
                                        "Specified \"modelName\" argument \"" + modelName
                                        + "\" begins with \"http\". Since the model url is built "
                                          "using the repositoryName argument, please only specify "
                                          "the name of the model. Like \"NewModel.sbml\"");
        }
        // first we make sure the suffix ends with a "#"
        if (!OmexMetaUtils::endsWith(modelName, "#")) {
            modelName += "#";
        }

        // Now we check for file extension
        std::vector<std::string> suffexes = {".xml#", ".sbml#", ".cellml#"};
        bool good = false;
        for (auto &it : suffexes) {
            if (OmexMetaUtils::endsWith(modelName, it)) {
                good = true;
            }
        }
        // automaticall add .xml if one of the above suffixes was not detected
        if (!good) {
            // remember to remove the trailing "#"
            modelName.pop_back();
            modelName += ".xml#";
        }

        // concatonate archive and model, being sensitive to ending "/"
        if (OmexMetaUtils::endsWith(getArchiveUri(), "/")) {
            model_uri_ = getArchiveUri() + modelName;
        } else {
            model_uri_ = getArchiveUri() + "/" + modelName;
        }

        // Since the model name is also used for the local name we
        // figure that out here. We know modelName definitely contains
        // a suffux like .xml.
        // we need to remove it so we can add .rdf.
        // We do this in a way that enables multiple "." in a model_name
        std::vector<std::string> split = OmexMetaUtils::splitStringBy(modelName, '.');
        if (split.size() <= 1) {
            throw std::logic_error("std::logic_error: RDF::setModelUri: You should never get a "
                                   "a value less than 2 here because you are splitting a string. "
                                   "If you are seeing this message this is a bug. Please report "
                                   "it as a github issue (https://github.com/sys-bio/libOmexMeta/issues)");
        }
        // remove the last element which should contain the extension.
        split.pop_back();

        // docs-build up the string again with any dots that appeared before the final
        std::ostringstream os;
        for (auto &it : split) {
            os << it << ".";
        }
        // Now we can docs-build up the local string
        if (OmexMetaUtils::endsWith(getArchiveUri(), "/")) {
            local_uri_ = getArchiveUri() + os.str() + "rdf#";
        } else {
            local_uri_ = getArchiveUri() + "/" + os.str() + "rdf#";
        }
    }


    const std::string &RDF::getLocalUri() const {
        return local_uri_;
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
        std::cout << "RDF::extractSemanticInformationFromSBML" << std::endl;
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
}
