//
// Created by Ciaran on 10/07/2020.
//

#include "omexmeta/PersonalInformation.h"


namespace omexmeta {

    PersonalInformation::PersonalInformation(LibrdfModel& model, UriHandler &uriHandler)
        : model_(model), uriHandler_(uriHandler) {
        metaid_ = generateMetaId();
        PersonalInformation::createSubject();
    }

    PersonalInformation::~PersonalInformation() {}

    /**
     * @brief move constructor
     */
    PersonalInformation::PersonalInformation(PersonalInformation &&information) noexcept
        : uriHandler_(information.uriHandler_), model_(information.model_) {
    }

    /**
     * @brief move assignment constructor
     */
    PersonalInformation &PersonalInformation::operator=(PersonalInformation &&information) noexcept {
        if (this != &information) {
            model_ = std::move(information.model_);
            triples_ = std::move(information.triples_);
            uriHandler_ = information.uriHandler_;
        }
        return *this;
    }

    bool PersonalInformation::operator==(const PersonalInformation &rhs) const {
        return model_ == rhs.model_ &&
               triples_ == rhs.triples_;
    }

    bool PersonalInformation::operator!=(const PersonalInformation &rhs) const {
        return !(rhs == *this);
    }

    std::string PersonalInformation::generateMetaId() const {
        std::vector<std::string> exclusions;// not really needed in this context, but signature requires the argument
        std::string metaid = OmexMetaUtils::generateUniqueMetaid(model_, "PersonalInfo", exclusions);
        return OmexMetaUtils::concatMetaIdAndUri(metaid, getModelUri());
    }

    PersonalInformation &
    PersonalInformation::addFoaf(const std::string &predicate, const LibrdfNode &value_node) {
        LibrdfNode subject = LibrdfNode::fromUriString(metaid_);
        Foaf foaf(predicate);
        Triple triple(uriHandler_, subject, foaf.getNode(), value_node);
        triples_.moveBack(triple);
        namespaces_.push_back(Predicate::namespaceMap()["foaf"]);
        return *this;
    }

    PersonalInformation &
    PersonalInformation::addDC(const std::string &predicate, const LibrdfNode &value_node) {
        LibrdfNode subject = LibrdfNode::fromUriString(metaid_);
        DCTerm dc(predicate);
        Triple triple(uriHandler_, subject, dc.getNode(), value_node);
        triples_.moveBack(triple);
        namespaces_.push_back(Predicate::namespaceMap()["dc"]);
        return *this;
    }

    PersonalInformation &
    PersonalInformation::addFoafBlank(const std::string &predicate, const std::string &blank_value) {
        LibrdfNode blank_node = LibrdfNode::fromBlank(blank_value);
        addFoaf(predicate, blank_node);
        namespaces_.push_back(Predicate::namespaceMap()["foaf"]);
        return *this;
    }

    PersonalInformation &
    PersonalInformation::addFoafUri(const std::string &predicate, const std::string &uri_value) {
        Foaf foaf(predicate);
        LibrdfNode uri_node = LibrdfNode::fromUriString(uri_value);
        addFoaf(predicate, uri_node);
        namespaces_.push_back(Predicate::namespaceMap()["foaf"]);
        return *this;
    }

    PersonalInformation &
    PersonalInformation::addFoafLiteral(const std::string &predicate, const std::string &literal_value) {
        Foaf foaf(predicate);
        LibrdfNode literal_node = LibrdfNode::fromLiteral(literal_value);
        addFoaf(predicate, literal_node);
        namespaces_.push_back(Predicate::namespaceMap()["foaf"]);
        return *this;
    }

    PersonalInformation &
    PersonalInformation::addDCBlank(const std::string &predicate, const std::string &blank_value) {
        LibrdfNode blank_node = LibrdfNode::fromBlank(blank_value);
        addDC(predicate, blank_node);
        namespaces_.push_back(Predicate::namespaceMap()["dc"]);
        return *this;
    }

    PersonalInformation &
    PersonalInformation::addDCUri(const std::string &predicate, const std::string &uri_value) {
        DCTerm dcTerm(predicate);
        LibrdfNode uri_node = LibrdfNode::fromUriString(uri_value);
        addDC(predicate, uri_node);
        namespaces_.push_back(Predicate::namespaceMap()["dc"]);
        return *this;
    }

    PersonalInformation &
    PersonalInformation::addDCLiteral(const std::string &predicate, const std::string &literal_value) {
        DCTerm dcTerm(predicate);
        LibrdfNode literal_node = LibrdfNode::fromLiteral(literal_value);
        addDC(predicate, literal_node);
        namespaces_.push_back(Predicate::namespaceMap()["dc"]);
        return *this;
    }

    PersonalInformation &PersonalInformation::addName(const std::string &value) {
        addFoafLiteral("name", value);
        return *this;
    }

    PersonalInformation &PersonalInformation::addMbox(const std::string &value) {
        addFoafLiteral("mbox", value);
        return *this;
    }

    PersonalInformation &PersonalInformation::addAccountName(const std::string &value) {
        addFoafUri("accountName", "https://orcid.org/" + value);// orcid id
        namespaces_.push_back(Predicate::namespaceMap()["orcid"]);
        return *this;
    }

    void PersonalInformation::setTriples(Triples triples) {
        triples_ = std::move(triples);
    }

    PersonalInformation &PersonalInformation::addAccountServiceHomepage(const std::string &value) {
        addFoafUri("accountServiceHomepage", value);
        return *this;
    }

    PersonalInformation &PersonalInformation::addCreator(const std::string &value) {
        addDCUri("creator", "orcid:" + value);
        return *this;
    }

    const std::string &PersonalInformation::getLocalUri() const {
        return uriHandler_.getLocalUri();
    }

    void PersonalInformation::createSubject() {
        if (uriHandler_.getModelUri().empty()) {
            throw std::invalid_argument("std::invalid_argument: PersonalInformation::createSubject:"
                                        "Trying to create a PersonalInformation composite annotation triples without"
                                        "a `model_uri`. Please use setModelUri() and try again.");
        }
        LibrdfNode n = LibrdfNode::fromUriString(uriHandler_.getModelLevelAnnotationUri());
        PredicatePtr creatorPtr = std::make_shared<DCTerm>("creator");
        LibrdfNode creatorNode = creatorPtr->getNode();
        LibrdfNode r = LibrdfNode::fromUriString(metaid_);
        Triple triple(uriHandler_, n,creatorNode, r);
        namespaces_.push_back(Predicate::namespaceMap()["orcid"]);
        triples_.moveBack(triple);
    }

    const std::string &PersonalInformation::getMetaid() const {
        return metaid_;
    }

    Triples PersonalInformation::getTriples() {
        return std::move(triples_);
    }

    void PersonalInformation::setMetaid(const std::string &metaid) {
        metaid_ = metaid;
    }

    const std::string &PersonalInformation::getModelUri() const {
        return uriHandler_.getModelUri();
    }

    void PersonalInformation::freeTriples() {
        triples_.freeTriples();
    }
    const std::vector<std::string> &PersonalInformation::getNamespaces() const {
        return namespaces_;
    }


}// namespace omexmeta