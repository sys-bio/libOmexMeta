//
// Created by Ciaran on 10/07/2020.
//

#include "PersonalInformation.h"


namespace omexmeta {

    PersonalInformation::PersonalInformation(librdf_model *model, std::string local_uri, std::string model_uri)
            : model_(model), local_uri_(local_uri), model_uri_(model_uri) {
        metaid_ = generateMetaId();
        createSubject();
    }


    /*
     * @brief move constructor
     */
    PersonalInformation::PersonalInformation(PersonalInformation &&information) noexcept {
        model_ = information.model_;
        information.model_ = nullptr;
        local_uri_ = information.local_uri_;
        triples_ = std::move(information.triples_);
        model_uri_ = information.model_uri_;
    }

    /*
     * @brief move assignment constructor
     */
    PersonalInformation &PersonalInformation::operator=(PersonalInformation &&information) noexcept {
        if (this != &information) {
            model_ = information.model_;
            information.model_ = nullptr;
            local_uri_ = information.local_uri_;
            triples_ = std::move(information.triples_);
            model_uri_ = information.model_uri_;
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
        std::string metaid = OmexMetaUtils::generateUniqueMetaid(model_, "PersonalInfo");
        return OmexMetaUtils::addLocalPrefixToMetaid(metaid, getModelUri());
    }

    PersonalInformation &
    PersonalInformation::addFoaf(const std::string &predicate, const LibrdfNode& value_node) {
        LibrdfNode subject = LibrdfNode::fromUriString(metaid_);
        Foaf foaf(predicate);
        Triple triple(subject.get(), foaf.getNode(), value_node.get());
        triples_.move_back(triple);
        return *this;
    }

    PersonalInformation &
    PersonalInformation::addDC(const std::string &predicate, const LibrdfNode& value_node) {
        LibrdfNode subject = LibrdfNode::fromUriString(metaid_);
        DCTerm dc(predicate);
        Triple triple(subject.get(), dc.getNode(), value_node.get());
        triples_.move_back(triple);
        return *this;
    }

    PersonalInformation &
    PersonalInformation::addFoafBlank(const std::string &predicate, const std::string &blank_value) {
        LibrdfNode blank_node = LibrdfNode::fromBlank(blank_value);
        addFoaf(predicate, blank_node);
        return *this;
    }

    PersonalInformation &
    PersonalInformation::addFoafUri(const std::string &predicate, const std::string &uri_value) {
        Foaf foaf(predicate);
        LibrdfNode uri_node = LibrdfNode::fromUriString(uri_value);
        addFoaf(predicate, uri_node);
        foaf.freeNode();
        return *this;
    }

    PersonalInformation &
    PersonalInformation::addFoafLiteral(const std::string &predicate, const std::string &literal_value) {
        Foaf foaf(predicate);
        LibrdfNode literal_node = LibrdfNode::fromLiteral(literal_value);
        addFoaf(predicate, literal_node);
        foaf.freeNode();
        return *this;
    }

    PersonalInformation &
    PersonalInformation::addDCBlank(const std::string &predicate, const std::string &blank_value) {
        LibrdfNode blank_node = LibrdfNode::fromBlank(blank_value);
        addDC(predicate, blank_node);
        return *this;
    }

    PersonalInformation &
    PersonalInformation::addDCUri(const std::string &predicate, const std::string &uri_value) {
        DCTerm dcTerm(predicate);
        LibrdfNode uri_node = LibrdfNode::fromUriString(uri_value);
        addDC(predicate, uri_node);
        dcTerm.freeNode();
        return *this;
    }

    PersonalInformation &
    PersonalInformation::addDCLiteral(const std::string &predicate, const std::string &literal_value) {
        DCTerm dcTerm(predicate);
        LibrdfNode literal_node = LibrdfNode::fromLiteral(literal_value);
        addDC(predicate, literal_node);
        dcTerm.freeNode();
        return *this;
    }

    PersonalInformation &PersonalInformation::addName(const std::string& value) {
        addFoafLiteral("name", value);
        return *this;
    }

    PersonalInformation &PersonalInformation::addMbox(const std::string& value) {
        addFoafLiteral("mbox", value);
        return *this;
    }

    PersonalInformation &PersonalInformation::addAccountName(const std::string& value) {
        addFoafUri("accountName", "https://orcid.org/" + value); // orchid id
        return *this;
    }

    void PersonalInformation::setTriples(Triples triples) {
        triples_ = std::move(triples);
    }

    PersonalInformation &PersonalInformation::addAccountServiceHomepage(const std::string& value) {
        addFoafUri("accountServiceHomepage", value);
        return *this;
    }

    PersonalInformation &PersonalInformation::addCreator(const std::string &value) {
        addDCUri("creator", value);
        return *this;
    }

    const std::string &PersonalInformation::getLocalUri() const {
        return local_uri_;
    }

    void PersonalInformation::setLocalUri(const std::string &localUri) {
        local_uri_ = localUri;
    }

    void PersonalInformation::createSubject() {
        if (model_uri_.empty()) {
            throw std::invalid_argument("std::invalid_argument: PersonalInformation::createSubject:"
                                        "Trying to create a PersonalInformation composite annotation triples without"
                                        "a `model_uri`. Please use setModelUri() and try again.");
        }
        LibrdfNode n = LibrdfNode::fromUriString(model_uri_);
        DCTerm creator("creator");
        LibrdfNode r = LibrdfNode::fromUriString(metaid_);
        Triple triple(n.get(), creator.getNode(), r.get());
        triples_.move_back(triple);
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
        return model_uri_;
    }

    void PersonalInformation::setModelUri(const std::string &modelUri) {
        model_uri_ = modelUri;
    }

    void PersonalInformation::freeTriples() {
        triples_.freeTriples();
    }




}