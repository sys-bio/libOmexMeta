//
// Created by Ciaran on 4/22/2020.
//

#include "omexmeta/PhysicalPhenomenon.h"


namespace omexmeta {

    PhysicalPhenomenon::PhysicalPhenomenon(librdf_model *model, std::string model_uri, std::string local_uri,
                                           PhysicalProperty propertyResource, AnnotationType type)
            : model_(model), physical_property_(std::move(propertyResource)), type_(type),
              model_uri_(std::move(model_uri)), local_uri_(std::move(local_uri)){}
    librdf_model *PhysicalPhenomenon::getModel() const {
        return model_;
    }
    PhysicalPhenomenon::~PhysicalPhenomenon() = default;


    PhysicalPhenomenon::PhysicalPhenomenon(librdf_model *model)
            : model_(model) {}

    PhysicalPhenomenon::PhysicalPhenomenon(librdf_model *model, std::string model_uri, std::string local_uri)
        : model_(model), model_uri_(std::move(model_uri)), local_uri_(std::move(local_uri)) {}

    const std::string & PhysicalPhenomenon::getSubjectStr() const {
        return physical_property_.getSubjectStr();
    }

    AnnotationType PhysicalPhenomenon::getType() const {
        return type_;
    }

    std::string PhysicalPhenomenon::generateMetaId(const std::string& id_base) {
        return OmexMetaUtils::generateUniqueMetaid(model_, id_base, new_metaid_exclusion_list_);
    }

    PhysicalProperty PhysicalPhenomenon::getPhysicalProperty() const {
        return physical_property_;
    }

    Triples PhysicalPhenomenon::toTriples() {
        throw NotImplementedException("Base class PhysicalPhenomenon "
                                      "does cannot produce triples.");
    }


    const std::string & PhysicalPhenomenon::getAbout() const {
        return physical_property_.getSubjectStr();
    }

    PhysicalPhenomenon& PhysicalPhenomenon::about(const std::string& about) {
        physical_property_.setSubject(about);
        return *this;
    }


    PhysicalPhenomenon::PhysicalPhenomenon(PhysicalPhenomenon &&phenomenon) noexcept {
        model_ = phenomenon.model_;
        phenomenon.model_ = nullptr; // not sure if this is right.
        physical_property_ = std::move(phenomenon.physical_property_);
        type_ = phenomenon.type_;
        model_uri_ = phenomenon.model_uri_;
    }

    PhysicalPhenomenon &PhysicalPhenomenon::operator=(PhysicalPhenomenon &&phenomenon) noexcept {
        if (this != &phenomenon) {
            model_ = phenomenon.model_;
            phenomenon.model_ = nullptr; // not sure if this is right.
            physical_property_ = std::move(phenomenon.physical_property_);
            type_ = phenomenon.type_;
            model_uri_ = phenomenon.model_uri_;
        }
        return *this;
    }

    bool PhysicalPhenomenon::operator==(const PhysicalPhenomenon &rhs) const {
        return physical_property_ == rhs.physical_property_;
    }

    bool PhysicalPhenomenon::operator!=(const PhysicalPhenomenon &rhs) const {
        return !(rhs == *this);
    }

    void PhysicalPhenomenon::setPhysicalProperty(const PhysicalProperty &physicalProperty) {
        physical_property_ = physicalProperty;
    }

    void PhysicalPhenomenon::setType(AnnotationType type) {
        type_ = type;
    }

    const std::string &PhysicalPhenomenon::getModelUri() const {
        if (model_uri_.empty()){
            throw std::invalid_argument("std::invalid_argument: model_uri_ is empty. "
                                        "Please use setModelUri or pass to the constructor a "
                                        "model uri. ");
        }
        return model_uri_;
    }

    void PhysicalPhenomenon::setModelUri(const std::string &modelUri) {
        model_uri_ = modelUri;
    }

    const std::string &PhysicalPhenomenon::getLocalUri() const {
        if (local_uri_.empty()){
            throw std::invalid_argument("std::invalid_argument: local_uri_ is empty. "
                                        "Please use setLocalUri or pass to the constructor a "
                                        "local uri. ");
        }
        return local_uri_;
    }

    void PhysicalPhenomenon::setLocalUri(const std::string &localUri) {
        local_uri_ = localUri;
    }

    std::vector<std::string> PhysicalPhenomenon::getNewMetaidExclusionList() {
        return new_metaid_exclusion_list_;
    }


}





