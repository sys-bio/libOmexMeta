//
// Created by Ciaran on 10/07/2020.
//

#include "PersonalInformation.h"


namespace omexmeta {

    PersonalInformation::PersonalInformation(librdf_model *model, std::string local_uri)
            : model_(model), local_uri_(local_uri) {
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
        model_name = information.model_name;
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
            model_name = information.model_name;
        }
    }

    bool PersonalInformation::operator==(const PersonalInformation &rhs) const {
        return model_ == rhs.model_ &&
               triples_ == rhs.triples_;
    }

    bool PersonalInformation::operator!=(const PersonalInformation &rhs) const {
        return !(rhs == *this);
    }

    std::string PersonalInformation::generateMetaId() const {
        std::string metaid = SemsimUtils::generateUniqueMetaid(model_, "PersonalInfo");
        return SemsimUtils::addLocalPrefixToMetaid(metaid, local_uri_);
    }

    PersonalInformation &
    PersonalInformation::addFoaf(const std::string &predicate, LibrdfNode value_node) {
        LibrdfNode subject = LibrdfNode::fromUriString(metaid_);
        Foaf foaf(predicate);
        Triple triple(subject.get(), foaf.getNode(), value_node.get());
        triples_.move_back(triple);
        // todo throw error if foaf already present in list
        return *this;
    }


    PersonalInformation &
    PersonalInformation::addFoafBlank(const std::string &predicate, const std::string &blank_value) {
        LibrdfNode blank_node = LibrdfNode::fromBlank(blank_value);
        addFoaf(predicate, std::move(blank_node));
        return *this;
    }

    PersonalInformation &
    PersonalInformation::addFoafUri(const std::string &predicate, const std::string &uri_value) {
        Foaf foaf(predicate);
        LibrdfNode uri_node = LibrdfNode::fromBlank(uri_value);
        addFoaf(predicate, std::move(uri_node));
        return *this;
    }

    PersonalInformation &
    PersonalInformation::addFoafLiteral(const std::string &predicate, const std::string &literal_value) {
        Foaf foaf(predicate);
        LibrdfNode literal_node = LibrdfNode::fromLiteral(literal_value);
        addFoaf(predicate, std::move(literal_node));
        return *this;
    }

    PersonalInformation &PersonalInformation::addCreator(std::string value) {
        addFoafLiteral("creator", value);
        return *this;
    }

    PersonalInformation &PersonalInformation::addCurator(std::string value) {
        addFoafLiteral("curator", value);
        return *this;
    }

    PersonalInformation &PersonalInformation::addName(std::string value) {
        addFoafLiteral("name", value);
        return *this;
    }

    PersonalInformation &PersonalInformation::addMbox(std::string value) {
        addFoafLiteral("mbox", value);
        return *this;
    }

    PersonalInformation &PersonalInformation::addAccountName(std::string value) {
        addFoafUri("accountName", value); // orchid id
        return *this;
    }

    PersonalInformation &PersonalInformation::addAccountServiceHomepage(std::string value) {
        addFoafUri("accountServiceHomepage", value);
        return *this;
    }

    const std::string &PersonalInformation::getLocalUri() const {
        return local_uri_;
    }

    void PersonalInformation::setLocalUri(const std::string &localUri) {
        local_uri_ = localUri;
    }

    void PersonalInformation::createSubject() {
        LibrdfNode n = LibrdfNode::fromUriString(model_name);
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

    const std::string &PersonalInformation::getModelName() const {
        return model_name;
    }

    void PersonalInformation::setModelName(const std::string &modelName) {
        model_name = modelName;
    }

    void PersonalInformation::freeTriples(){
        triples_.freeTriples();
    }

}