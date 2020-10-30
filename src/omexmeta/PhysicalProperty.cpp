//
// Created by Ciaran on 4/22/2020.
//

#include "omexmeta/PhysicalProperty.h"

#include <utility>

namespace omexmeta {

    PhysicalProperty::PhysicalProperty(std::string subject_str, std::string resource_str, std::string model_uri)
        : isPropertyOfValue(std::move(subject_str)),
          isVersionOfValue(std::move(resource_str)),
          model_uri_(std::move(model_uri)) {
        validate();
    }
    PhysicalProperty::PhysicalProperty(std::string subject_str, std::string model_uri)
        : isPropertyOfValue(std::move(subject_str)),
          model_uri_(std::move(model_uri)) {
        validate();
    }

    void PhysicalProperty::validate() {
        std::string expected_prefix1 = "https://identifiers.org/OPB";
        std::string expected_prefix2 = "https://identifiers.org/opb";

        // create a temporary resource obj for checking only.
        if (!isVersionOfValue.empty()) {
            Resource r(LibrdfNode::fromUriString(isVersionOfValue));
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
        if (OmexMetaUtils::startsWith(isPropertyOfValue, "http")) {
            if (!OmexMetaUtils::startsWith(isPropertyOfValue, getModelUri())) {
                throw std::invalid_argument("std::invalid_argument: PhysicalProperty::validate() "
                                            "The subject argument to PhysicalProperty is already a URI"
                                            "but is it not the uri associated with the model you are annotating "
                                            "(" +
                                            getModelUri() + ") but instead \"" + isPropertyOfValue + "\"");
            }
        } else {
            isPropertyOfValue = OmexMetaUtils::concatMetaIdAndUri(isPropertyOfValue, getModelUri());
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
                LibrdfNode::fromUriString(isPropertyOfValue).get());
        triples.move_back(is_property_of_triple);

        if (!isVersionOfValue.empty()) {
            Triple is_version_of_triple(
                    LibrdfNode::fromUriString(property_metaid).get(),
                    BiomodelsBiologyQualifier("isVersionOf").getNode(),
                    Resource(LibrdfNode::fromUriString(isVersionOfValue)).getNode());
            triples.move_back(is_version_of_triple);
        }

        return triples;
    }

    const std::string &PhysicalProperty::getSubjectStr() const {
        return isPropertyOfValue;
    }

    void PhysicalProperty::setSubject(const std::string &subject) {
        if (OmexMetaUtils::startsWith(subject, "http")) {
            isPropertyOfValue = subject;
        } else {
            isPropertyOfValue = OmexMetaUtils::concatMetaIdAndUri(subject, getModelUri());
        }
    }

    const std::string &PhysicalProperty::getResourceStr() const {
        return isVersionOfValue;
    }

    void PhysicalProperty::setResource(const std::string &resource) {
        isVersionOfValue = resource;
    }

    bool PhysicalProperty::operator==(const PhysicalProperty &rhs) const {
        return isPropertyOfValue == rhs.isPropertyOfValue &&
               isVersionOfValue == rhs.isVersionOfValue;
    }

    bool PhysicalProperty::operator!=(const PhysicalProperty &rhs) const {
        return !(rhs == *this);
    }

    const std::string &PhysicalProperty::getSubject() const {
        return isPropertyOfValue;
    }

    const std::string &PhysicalProperty::getResource() const {
        return isVersionOfValue;
    }

    const std::string &PhysicalProperty::getModelUri() const {
        return model_uri_;
    }

    void PhysicalProperty::setModelUri(const std::string &model_uri) {
        model_uri_ = model_uri;
    }


}// namespace omexmeta