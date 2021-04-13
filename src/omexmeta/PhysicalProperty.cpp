//
// Created by Ciaran on 4/22/2020.
//

#include "omexmeta/PhysicalProperty.h"

#include "omexmeta/UriHandler.h"
#include <utility>

namespace omexmeta {

    const std::string &PhysicalProperty::getLocalUri() const {
        return uriHandler_.getLocal();
    }

    PhysicalProperty::PhysicalProperty(librdf_model *model, UriHandler& uriHandler)
        : model_(model), uriHandler_(uriHandler){}


    Triples PhysicalProperty::toTriples() {
        // in sbml the metaid for property needs to be generated
        if (OmexMetaUtils::isStringEmpty<PhysicalProperty>(*this, about_value_)) {
            std::string new_about = OmexMetaUtils::generateUniqueMetaid(model_, property_metaid_base_, new_metaid_exclusion_list_);
            new_metaid_exclusion_list_.push_back(new_about);
            about(new_about, LOCAL_URI);
        }

        if (!OmexMetaUtils::startsWith(about_value_, "http")) {
            throw std::invalid_argument("std::invalid_argument: PhysicalProperty::toTriples: "
                                        "Expected a full uri (i.e. begins with http) for property_metaid "
                                        "argument but instead recieved \"" +
                                        about_value_ + "\"");
        }

        Triples triples;

        if (is_property_of_value_.empty()) {
            is_property_of_value_ = OmexMetaUtils::generateUniqueMetaid(model_, property_metaid_base_, new_metaid_exclusion_list_);
        }

        Triple is_property_of_triple(
                LibrdfNode::fromUriString(about_value_).get(),
                BiomodelsBiologyQualifier("isPropertyOf").getNode(),
                LibrdfNode::fromUriString(is_property_of_value_).get());
        triples.move_back(is_property_of_triple);

        if (!is_version_of_value_.empty()) {
            Triple is_version_of_triple(
                    LibrdfNode::fromUriString(about_value_).get(),
                    BiomodelsBiologyQualifier("isVersionOf").getNode(),
                    Resource(LibrdfNode::fromUriString(is_version_of_value_)).getNode());
            triples.move_back(is_version_of_triple);
        }
        return triples;
    }
    const std::string &PhysicalProperty::getIsPropertyOfValue() const {
        return is_property_of_value_;
    }
    const std::string &PhysicalProperty::getPropertyMetaidBase() const {
        return property_metaid_base_;
    }

    const std::string &PhysicalProperty::getAbout() const {
        return about_value_;
    }

    PhysicalProperty &PhysicalProperty::about(const std::string &about, eUriType type) {
        if (OmexMetaUtils::startsWith(about, "http")){
            about_value_ = about;
        } else {
            about_value_ = UriHandler::uriModifier<PhysicalProperty>(*this, about, type);
        }
        return *this;
    }

    const std::string &PhysicalProperty::getIsVersionOfValue() const {
        return is_version_of_value_;
    }

    bool PhysicalProperty::operator==(const PhysicalProperty &rhs) const {
        return is_property_of_value_ == rhs.is_property_of_value_ &&
               is_version_of_value_ == rhs.is_version_of_value_ &&
               about_value_ == rhs.about_value_;
    }

    bool PhysicalProperty::operator!=(const PhysicalProperty &rhs) const {
        return !(rhs == *this);
    }

    const std::string &PhysicalProperty::getModelUri() const {
        return uriHandler_.getModel();
    }

    PhysicalProperty &PhysicalProperty::isVersionOf(const std::string &is_version_of) {
        is_version_of_value_ = is_version_of;
        return *this;
    }

    PhysicalProperty &PhysicalProperty::isPropertyOf(const std::string &is_property_of, eUriType type) {
        is_property_of_value_ = UriHandler::uriModifier<PhysicalProperty>(*this, is_property_of, type);
        return *this;
    }

    void PhysicalProperty::setPropertyMetaidBase(const std::string &propertyMetaidBase) {
        property_metaid_base_ = propertyMetaidBase;
    }

    const std::string &PhysicalProperty::getPropertyBearerBase() const {
        return property_bearer_base_;
    }

    void PhysicalProperty::setPropertyBearerBase(const std::string &propertyBearerBase) {
        property_bearer_base_ = propertyBearerBase;
    }
    bool PhysicalProperty::isSet() const {
        return is_set_;
    }
    void PhysicalProperty::setIsSet(bool isSet) {
        is_set_ = isSet;
    }


}// namespace omexmeta