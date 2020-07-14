//
// Created by Ciaran on 4/4/2020.
//

#include "Triple.h"


namespace omexmeta {

    Triple::Triple(const Subject &subject, const PredicatePtr &predicate_ptr, const Resource &resource)
            : LibrdfStatement(subject.getNode(),
                              predicate_ptr->getNode(),
                              resource.getNode()) {
    }

    Triple::Triple(librdf_node *subject, librdf_node *predicate, librdf_node *resource) :
            LibrdfStatement(subject, predicate, resource) {}

    Triple Triple::fromRawStatementPtr(librdf_statement *statement) {
        return Triple(statement);
    }

    Triple::Triple(librdf_statement *statement) : LibrdfStatement(statement) {}

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

        std::vector<std::string> nsvec = OmexMetaUtils::configureSelfStrings("http://omex-library.org/", omex_name,
                                                                             model_name);

        // make uri's for the namespaces
        librdf_uri *myomexlib = librdf_new_uri(World::getWorld(), (const unsigned char *) nsvec[0].c_str());
        librdf_uri *myomex = librdf_new_uri(World::getWorld(), (const unsigned char *) nsvec[1].c_str());
        librdf_uri *local = librdf_new_uri(World::getWorld(), (const unsigned char *) nsvec[2].c_str());

        librdf_serializer_set_namespace(serializer, myomexlib, "myOMEXlib");
        librdf_serializer_set_namespace(serializer, myomex, "myOMEX");
        librdf_serializer_set_namespace(serializer, local, "local");

        // free the uri's now that we're done with them.
        librdf_free_uri(myomexlib);
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

    Triple &Triple::setAbout(std::string omex_name, const std::string &model_name, std::string metaid) {
        if (getSubject() != nullptr)
            LibrdfNode::freeNode(getSubject());
        if (omex_name.rfind("http", 0) != 0) {
            throw std::invalid_argument("std::invalid_argument Triple::setAbout: metaid does not "
                                        "begin with \"http\" which suggests that it is not properly "
                                        "formatted. Metaid's should look like: "
                                        "\"http://omex-library.org/myomex.omex/mymodel.rdf#MetaId0000\" but yours "
                                        "is: " + omex_name);
        }
        if (!OmexMetaUtils::endsWith(omex_name, "/")) {
            omex_name = omex_name + "/";
        }

        if (OmexMetaUtils::startsWith(metaid, "#"))
            metaid.erase(metaid.begin());

        setSubject(LibrdfNode::fromUriString(
                omex_name + model_name + "#" + metaid
        ).get());
        return *this;
    }

    Triple &Triple::setAbout(std::string metaid) {
        // get rid of starting "#" characters in metaid.
        if (OmexMetaUtils::startsWith(metaid, "#")) {
            metaid.erase(metaid.begin());
        }
        // if not start with http, assume local_uri not included and add it on
        if (!OmexMetaUtils::startsWith(metaid, "http")) {
            if (getLocalUri().empty()) {
                throw std::logic_error("std::logic_error: Triple::setAbout: Trying to "
                                       "setAbout(), i.e. the subject portion of a singular annotation. Either "
                                       "give a full uri (i.e. starts with http) or set the local_uri attribute"
                                       "using setLocalUri() before calling setAbout().");
            }
            metaid = getLocalUri() + metaid;
        }


        setSubject(LibrdfNode::fromUriString(metaid).get());

        return *this;
    }

//    Triple &Triple::setAbout(const std::string &metaid) {
//        if (metaid.rfind("http", 0) != 0){
//            throw std::invalid_argument("std::invalid_argument Triple::setAbout: metaid does not "
//                                        "begin with \"http\" which suggests that it is not properly"
//                                        "formatted. Metaid's should look like: "
//                                        "\"http://omex-library.org/myomex.omex/mymodel.rdf#MetaId0000\"");
//        }
//        setSubject(LibrdfNode::fromUriString(metaid).get());
//
//        return *this;
//    }

    Triple &
    Triple::setPredicate(const std::string &namespace_, const std::string &term) {
        if (getPredicate() != nullptr)
            LibrdfNode::freeNode(getPredicate());
        // ive implemented the logic here rather then using LibrdfStatement::setPredicate
        //  because I want them both to be called setPredicate.
        librdf_node *node = PredicateFactory(namespace_, term)->getNode();
        librdf_statement_set_predicate(statement_, node);
        return *this;
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
        return local_uri_;
    }

    void Triple::setLocalUri(std::string localUri) {
        if (!OmexMetaUtils::endsWith(localUri, "#"))
            localUri += "#";
        local_uri_ = localUri;
    }

}

