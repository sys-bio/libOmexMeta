//
// Created by Ciaran on 4/22/2020.
//

#include "omexmeta/PhysicalProperty.h"

#include <utility>

namespace omexmeta {

    PhysicalProperty::PhysicalProperty(std::string is_version_of, std::string is_version_of_value, std::string model_uri)
        : is_property_of_value_(std::move(is_version_of)),
          is_version_of_value_(std::move(is_version_of_value)),
          model_uri_(std::move(model_uri)) {
        //        validate();
    }

    PhysicalProperty::PhysicalProperty(std::string is_version_of, std::string is_version_of_value, std::string model_uri, librdf_model *model)
        : is_property_of_value_(std::move(is_version_of)),
          is_version_of_value_(std::move(is_version_of_value)),
          model_uri_(std::move(model_uri)),
          model_(model) {
        //        validate();
    }

    PhysicalProperty::PhysicalProperty(std::string subject_str, std::string model_uri)
        : is_property_of_value_(std::move(subject_str)),
          model_uri_(std::move(model_uri)) {
        //        validate();
    }

    PhysicalProperty::PhysicalProperty(librdf_model *model, const std::string &model_uri, const std::string &local_uri)
        : model_(model), model_uri_(model_uri), local_uri_(local_uri){}

    void PhysicalProperty::validate() {
        std::string expected_prefix1 = "https://identifiers.org/OPB";
        std::string expected_prefix2 = "https://identifiers.org/opb";

        // create a temporary resource obj for checking only.
        if (!is_version_of_value_.empty()) {
            Resource r(LibrdfNode::fromUriString(is_version_of_value_));
            std::string uri = r.str();
            r.free();
            if ((uri.rfind(expected_prefix1, 0) != 0) && (uri.rfind(expected_prefix2, 0) != 0)) {
                std::ostringstream err;
                err << __FILE__ << ":" << __LINE__ << ": The uri generated (";
                err << uri << ") is not a OPB resource. Physical properties "
                              "must be OPB resources.";
                throw omexmeta::InappropriateResourceException(err.str());
            }
        }

        // ensure subject_uri_ has the model_uri associated with it
        if (OmexMetaUtils::startsWith(is_property_of_value_, "http")) {
            if (!OmexMetaUtils::startsWith(is_property_of_value_, getModelUri())) {
                throw std::invalid_argument("std::invalid_argument: PhysicalProperty::validate() "
                                            "The subject argument to PhysicalProperty is already a URI"
                                            "but is it not the uri associated with the model you are annotating "
                                            "(" +
                                            getModelUri() + ") but instead \"" + is_property_of_value_ + "\"");
            }
        } else {
            is_property_of_value_ = OmexMetaUtils::concatMetaIdAndUri(is_property_of_value_, getModelUri());
        }
    }


    Triples PhysicalProperty::toTriples(const std::string &property_metaid) const {
        if (!OmexMetaUtils::startsWith(property_metaid, "http")) {
            throw std::invalid_argument("std::invalid_argument: PhysicalProperty::toTriples: "
                                        "Expected a full uri (i.e. begins with http) for property_metaid "
                                        "argument but instead recieved \"" +
                                        property_metaid + "\"");
        }


        Triples triples;
        Triple is_property_of_triple(
                LibrdfNode::fromUriString(property_metaid).get(),
                BiomodelsBiologyQualifier("isPropertyOf").getNode(),
                LibrdfNode::fromUriString(is_property_of_value_).get());
        triples.move_back(is_property_of_triple);

        if (!is_version_of_value_.empty()) {
            Triple is_version_of_triple(
                    LibrdfNode::fromUriString(property_metaid).get(),
                    BiomodelsBiologyQualifier("isVersionOf").getNode(),
                    Resource(LibrdfNode::fromUriString(is_version_of_value_)).getNode());
            triples.move_back(is_version_of_triple);
        }
        return triples;
    }

    Triples PhysicalProperty::toTriples() const {
        return std::move(toTriples(getAbout()));
    }

    const std::string &PhysicalProperty::getAbout() const {
        return metaid_;
    }

    PhysicalProperty& PhysicalProperty::about(const std::string &about) {
        std::cout << "about: " << about << std::endl;
        if (OmexMetaUtils::startsWith(about, "http")) {
            metaid_ = about;
        } else {
            metaid_ = OmexMetaUtils::concatMetaIdAndUri(about, getModelUri());
        }
        std::cout << "about: " << about << std::endl;
        return *this;
    }

    const std::string &PhysicalProperty::getIsVersionOfValue() const {
        return is_version_of_value_;
    }

    bool PhysicalProperty::operator==(const PhysicalProperty &rhs) const {
        return is_property_of_value_ == rhs.is_property_of_value_ &&
               is_version_of_value_ == rhs.is_version_of_value_ &&
               metaid_ == rhs.metaid_;
    }

    bool PhysicalProperty::operator!=(const PhysicalProperty &rhs) const {
        return !(rhs == *this);
    }

//    const std::string &PhysicalProperty::getSubject() const {
//        return metaid_;
//    }
//
//    const std::string &PhysicalProperty::getResource() const {
//        return is_version_of_value_;
//    }

    const std::string &PhysicalProperty::getModelUri() const {
        return model_uri_;
    }
//
//    void PhysicalProperty::setModelUri(const std::string &model_uri) {
//        model_uri_ = model_uri;
//    }

    PhysicalProperty& PhysicalProperty::isVersionOf(const std::string& is_version_of){
        is_version_of_value_ = is_version_of;
        return *this;
    }

    PhysicalProperty& PhysicalProperty::isPropertyOf(const std::string& is_property_of){
        is_property_of_value_ = is_property_of;
        return *this;
    }

//    PhysicalProperty& PhysicalProperty::propertyMetaId(const std::string &property_metaid) {
//        metaid_ = property_metaid;
//        return *this;
//    }


}// namespace omexmeta