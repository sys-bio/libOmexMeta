//
// Created by Ciaran on 4/4/2020.
//

#include "omexmeta/Triple.h"
#include "omexmeta_export.h"
#include <omexmeta/UriHandler.h>

namespace omexmeta {
    Triple::Triple(UriHandler &uriHandler)
        : uriHandler_(uriHandler) {}

    Triple::Triple(Triple &&triple) noexcept
        : uriHandler_(triple.uriHandler_) {
        if (triple.statement_ != nullptr) {
            if (statement_ != nullptr) {
                librdf_free_statement(statement_);
                statement_ = nullptr;
            }
            statement_ = triple.statement_;
            triple.statement_ = nullptr;
        }
    }

    Triple &Triple::operator=(Triple &&triple) noexcept {
        if (*this != triple) {
            uriHandler_ = triple.uriHandler_;
            LibrdfStatement::operator=(std::move(triple));
        }
        return *this;
    };

    Triple::Triple(UriHandler &uriHandler, const LibrdfNode &subject, const PredicatePtr &predicate_ptr, const LibrdfNode &resource)
        : uriHandler_(uriHandler), LibrdfStatement(subject.get(), predicate_ptr->get(), resource.get()) {}

    Triple::Triple(UriHandler &uriHandler, librdf_node *subject, librdf_node *predicate, librdf_node *resource)
        : uriHandler_(uriHandler), LibrdfStatement(subject, predicate, resource) {}

    Triple Triple::fromRawStatementPtr(UriHandler &uriHandler, librdf_statement *statement) {
        return Triple(uriHandler, statement);
    }

    Triple::Triple(UriHandler &uriHandler, librdf_statement *statement)
        : uriHandler_(uriHandler), LibrdfStatement(statement) {}

    std::string Triple::str(const std::string &format, const std::string &base, std::string omex_name,
                            std::string model_name) const {
        // ensure we have three nodes and a statement
        if (!getSubject()) {
            throw RedlandNullPointerException("RedlandNullPointerException: Triple::str: subject is null");
        }
        if (!getPredicate()) {
            throw RedlandNullPointerException("RedlandNullPointerException: Triple::str: predicate is null");
        }
        if (!getResource()) {
            throw RedlandNullPointerException("RedlandNullPointerException: Triple::str: resource is null");
        }
        if (!statement_) {
            throw RedlandNullPointerException("RedlandNullPointerException: Triple::str: statement is null");
        }

        librdf_world *world = librdf_new_world();
        librdf_storage *storage = librdf_new_storage(world, "memory", "SemsimMemoryStore", nullptr);
        librdf_model *model = librdf_new_model(world, storage, nullptr);

        librdf_model_add_statement(model, statement_);
        librdf_serializer *serializer = librdf_new_serializer(world, format.c_str(), nullptr, nullptr);

        // turn off base uri
        LibrdfUri write_base_uri_uri = LibrdfUri("http://feature.librdf.org/raptor-writeBaseURI");
        LibrdfNode write_base_uri_node = LibrdfNode::fromLiteral("0");
        librdf_serializer_set_feature(serializer, write_base_uri_uri.get(), write_base_uri_node.get());
        write_base_uri_uri.freeUri();
        write_base_uri_node.freeNode();

        // deal with namespaces
        Predicate::addSeenNamespaceToSerializer(world, serializer, getPredicate());

        std::vector<std::string> nsvec = OmexMetaUtils::configurePrefixStrings(
                "http://omex-library.org/", std::move(omex_name), std::move(model_name));

        // make uri's for the namespaces
        librdf_uri *OMEXlib = librdf_new_uri(World::getWorld(), (const unsigned char *) nsvec[0].c_str());
        librdf_uri *myomex = librdf_new_uri(World::getWorld(), (const unsigned char *) nsvec[1].c_str());
        librdf_uri *local = librdf_new_uri(World::getWorld(), (const unsigned char *) nsvec[2].c_str());

        librdf_serializer_set_namespace(serializer, OMEXlib, "OMEXlib");
        librdf_serializer_set_namespace(serializer, myomex, "myOMEX");
        librdf_serializer_set_namespace(serializer, local, "local");

        // free the uri's now that we're done with them.
        librdf_free_uri(OMEXlib);
        librdf_free_uri(myomex);
        librdf_free_uri(local);

        // run the base uri through func that adds file:// if it needs to
        librdf_uri *base_uri = librdf_new_uri(world,
                                              (const unsigned char *) OmexMetaUtils::prepareBaseUri(base).c_str());
        // do the serializing
        unsigned char *string = librdf_serializer_serialize_model_to_string(serializer, base_uri, model);
        std::string str = (const char *) string;

        // free up resources
        free(string);
        librdf_free_serializer(serializer);
        librdf_free_uri(base_uri);
        librdf_free_model(model);
        librdf_free_storage(storage);
        librdf_free_world(world);
        return str;
    }

    Triple &Triple::about(std::string omex_name, const std::string &model_name, std::string metaid) {
        if (getSubject() != nullptr)
            LibrdfNode::freeNode(getSubject());
        if (omex_name.rfind("http", 0) != 0) {
            throw std::invalid_argument("std::invalid_argument Triple::about: metaid does not "
                                        "begin with \"http\" which suggests that it is not properly "
                                        "formatted. Metaid's should look like: "
                                        "\"http://omex-library.org/myomex.omex/mymodel.rdf#MetaId0000\" but yours "
                                        "is: " +
                                        omex_name);
        }
        if (!OmexMetaUtils::endsWith(omex_name, "/")) {
            omex_name = omex_name + "/";
        }

        if (OmexMetaUtils::startsWith(metaid, "#"))
            metaid.erase(metaid.begin());

        setSubject(LibrdfNode::fromUriString(
                           omex_name + model_name + "#" + metaid)
                           .get());
        return *this;
    }

    Triple &Triple::about(std::string metaid) {
        // get rid of starting "#" characters in metaid.
        if (OmexMetaUtils::startsWith(metaid, "#")) {
            metaid.erase(metaid.begin());
        }
        // if not start with http, assume local_uri not included and add it on
        if (!OmexMetaUtils::startsWith(metaid, "http")) {
            if (getModelUri().empty()) {
                throw std::logic_error("std::logic_error: Triple::about: Trying to "
                                       "about(), i.e. the subject portion of a singular annotation. Either "
                                       "give a full uri (i.e. starts with http) or set the local_uri_ attribute "
                                       "using setLocalUri() before calling about().");
            }
            std::string model_uri = getModelUri();
            if (OmexMetaUtils::endsWith(model_uri, "#")) {
                // has to be -1 from the end, otherwise we remove the string terminator
                model_uri.erase(model_uri.end() - 1);
            }
            metaid = model_uri + "#" + metaid;
        }

        setSubject(LibrdfNode::fromUriString(metaid).get());

        return *this;
    }

    Triple &Triple::about(std::string metaid, eUriType uri_type) {
        metaid = UriHandler::uriModifier<Triple>(*this, metaid, uri_type);
        setSubject(LibrdfNode::fromUriString(metaid).get());
        return *this;
    }

    Triple &Triple::setPredicate(const std::string &namespace_, const std::string &term) {
        if (getPredicate() != nullptr)
            LibrdfNode::freeNode(getPredicate());
        // ive implemented the logic here rather then using LibrdfStatement::setPredicate
        //  because I want them both to be called setPredicate.
        librdf_node *node = PredicateFactory(namespace_, term)->get();
        librdf_statement_set_predicate(statement_, node);
        return *this;
    }

    Triple &Triple::predicate(const std::string &namespace_, const std::string &term) {
        return setPredicate(namespace_, term);
    }


    Triple &
    Triple::setPredicate(const std::string &uri) {
        if (getPredicate() != nullptr)
            LibrdfNode::freeNode(getPredicate());
        LibrdfNode node = LibrdfNode::fromUriString(uri);
        // we pass ownership of node to the statement.
        librdf_statement_set_predicate(statement_, node.get());
        return *this;
    }

    Triple &
    Triple::predicate(const std::string &uri) {
        return setPredicate(uri);
    }

    Triple &Triple::setResourceLiteral(const std::string &literal) {
        // if getResource() node alredy exists, free before resetting
        if (getResource() != nullptr)
            LibrdfNode::freeNode(getResource());
        setResource(LibrdfNode::fromLiteral(literal).get());
        return *this;
    }

    Triple &Triple::setResourceUri(const std::string &identifiers_uri) {
        if (getResource() != nullptr)
            LibrdfNode::freeNode(getResource());
        setResource(LibrdfNode::fromUriString(identifiers_uri).get());
        return *this;
    }

    Triple &Triple::setResourceBlank(const std::string &blank_id) {
        if (getResource() != nullptr)
            LibrdfNode::freeNode(getResource());
        setResource(LibrdfNode::fromBlank(blank_id).get());
        return *this;
    }
    Triple &Triple::resourceLiteral(const std::string &literal) {
        return setResourceLiteral(literal);
    }

    Triple &Triple::resourceUri(const std::string &identifiers_uri) {
        return setResourceUri(identifiers_uri);
    }

    Triple &Triple::resourceBlank(const std::string &blank_id) {
        return setResourceBlank(blank_id);
    }

    Triple &Triple::setResourceWithModelUri(const std::string &metaid) {
        if (getResource() != nullptr)
            LibrdfNode::freeNode(getResource());
        setResource(LibrdfNode::fromUriString(OmexMetaUtils::concatMetaIdAndUri(metaid, getModelUri())).get());
        return *this;
    }

    Triple &Triple::resourceWithModelUri(const std::string &metaid) {
        return setResourceWithModelUri(metaid);
    }

    std::string Triple::getAbout() const {
        return LibrdfNode::str(getSubject());
    }

    bool Triple::isEmpty() {
        return !getSubject() && !getPredicate() && !getResource();
    }

    librdf_statement *Triple::getStatement() const {
        return statement_;
    }

    void Triple::freeTriple() {
        freeStatement();
    }

    void Triple::freeTripleAndUris() {
        freeStatementAndUris();
    }

    const std::string &Triple::getLocalUri() const {
        return uriHandler_.getLocalUri();
    }

    const std::string &Triple::getModelUri() const {
        return uriHandler_.getModelUri();
    }

    void Triple::setModelUri(const std::string &model_uri) {
        uriHandler_.setModelUri(model_uri);
    }


}// namespace omexmeta
