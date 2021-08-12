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
        : uriHandler_(triple.uriHandler_),
          LibrdfStatement(std::move(triple)){}

    Triple &Triple::operator=(Triple &&triple) noexcept {
        if (*this != triple) {
            uriHandler_ = triple.uriHandler_;
            LibrdfStatement::operator=(std::move(triple));
        }
        return *this;
    };

    Triple::Triple(const Triple &triple)
        : uriHandler_(triple.uriHandler_),
        LibrdfStatement(triple){}

    Triple & Triple::operator=(const Triple &triple) {
        if (*this != triple) {
            uriHandler_ = triple.uriHandler_;
            LibrdfStatement::operator=(triple);
        }
        return *this;
    }

//    Triple::Triple(UriHandler &uriHandler, const LibrdfNode &subject, const PredicatePtr &predicate_ptr, const LibrdfNode &resource)
//        : uriHandler_(uriHandler), LibrdfStatement(subject, *predicate_ptr, resource) {}

    Triple::Triple(UriHandler &uriHandler, const LibrdfNode &subject, const LibrdfNode &predicate, const LibrdfNode &resource)
        : uriHandler_(uriHandler), LibrdfStatement(subject, predicate, resource) {}

    Triple::Triple(UriHandler &uriHandler, librdf_statement *statement)
        : uriHandler_(uriHandler), LibrdfStatement(statement) {}

    Triple &Triple::about(std::string omex_name, const std::string &model_name, std::string metaid) {
//        if (!getSubjectNode().isNull())
//            getSubjectNode().freeObj();
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
                           omex_name + model_name + "#" + metaid));
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

        setSubject(LibrdfNode::fromUriString(metaid));

        return *this;
    }

    Triple &Triple::about(std::string metaid, eUriType uri_type) {
        metaid = UriHandler::uriModifier<Triple>(*this, metaid, uri_type);
        setSubject(LibrdfNode::fromUriString(metaid));
        return *this;
    }

    Triple &Triple::setPredicate(const std::string &namespace_, const std::string &term) {
        // ive implemented the logic here rather then using LibrdfStatement::setPredicate
        //  because I want them both to be called setPredicate.
        LibrdfNode node = PredicateFactory(namespace_, term)->getNode();
        LibrdfStatement::setPredicate(node);
        return *this;
    }

    Triple &Triple::predicate(const std::string &namespace_, const std::string &term) {
        return setPredicate(namespace_, term);
    }


    Triple &
    Triple::predicate(const std::string &uri) {
        LibrdfNode node = LibrdfNode::fromUriString(uri);
        LibrdfStatement::setPredicate(node);
        return *this;
    }

    Triple &Triple::setResourceLiteral(const std::string &literal) {
        setResource(LibrdfNode::fromLiteral(literal));
        return *this;
    }

    Triple &Triple::setResourceUri(const std::string &identifiers_uri) {
        setResource(LibrdfNode::fromUriString(identifiers_uri));
        return *this;
    }

    Triple &Triple::setResourceBlank(const std::string &blank_id) {
        setResource(LibrdfNode::fromBlank(blank_id));
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
        setResource(LibrdfNode::fromUriString(OmexMetaUtils::concatMetaIdAndUri(metaid, getModelUri())));
        return *this;
    }

    Triple &Triple::resourceWithModelUri(const std::string &metaid) {
        return setResourceWithModelUri(metaid);
    }

    std::string Triple::getAbout() const {
        return getSubjectNode().str();
    }

    bool Triple::isEmpty() {
        return getSubjectNode().isNull() && getPredicateNode().isNull() && getResourceNode().isNull();
    }

    LibrdfStatement Triple::getStatement() const {
        LibrdfStatement stmt(obj_);
        stmt.incrementUsage();
        return stmt ;
    }

    void Triple::freeTriple() {
        freeFunc_(obj_);
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
