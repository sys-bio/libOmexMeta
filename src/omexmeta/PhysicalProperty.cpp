//
// Created by Ciaran on 4/22/2020.
//

#include "omexmeta/PhysicalProperty.h"

#include <utility>

namespace omexmeta {

    PhysicalProperty::PhysicalProperty(std::string subject_str, std::string resource_str, std::string model_uri)
        : subject_(std::move(subject_str)),
          resource_(std::move(resource_str)),
          model_uri_(std::move(model_uri)) {
        validate();
    }
    PhysicalProperty::PhysicalProperty(std::string subject_str, std::string model_uri)
        : subject_(std::move(subject_str)),
          model_uri_(std::move(model_uri)) {
        validate();
    }

    void PhysicalProperty::validate() {
        std::string expected_prefix1 = "https://identifiers.org/OPB";
        std::string expected_prefix2 = "https://identifiers.org/opb";

        // create a temporary resource obj for checking only.
        if (!resource_.empty()) {
            Resource r(LibrdfNode::fromUriString(resource_));
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
        if (OmexMetaUtils::startsWith(subject_, "http")) {
            if (!OmexMetaUtils::startsWith(subject_, getModelUri())) {
                throw std::invalid_argument("std::invalid_argument: PhysicalProperty::validate() "
                                            "The subject argument to PhysicalProperty is already a URI"
                                            "but is it not the uri associated with the model you are annotating "
                                            "(" +
                                            getModelUri() + ") but instead \"" + subject_ + "\"");
            }
        } else {
            subject_ = OmexMetaUtils::concatMetaIdAndUri(subject_, getModelUri());
        }
    }


    Triples PhysicalProperty::toTriples(const std::string &property_metaid) const {

        if (!OmexMetaUtils::startsWith(property_metaid, "http")) {
            throw std::invalid_argument("std::invalid_argument: PhysicalProperty::toTriples: "
                                        "Expected a full uri (i.e. begins with http) for property_metaid "
                                        "argument but instead recieved \"" +
                                        property_metaid + "\"");
        }

        std::cout << "PhysicalProperty::toTriples subject: " << subject_ << std::endl;
        std::cout << "PhysicalProperty::toTriples property_metaid: " << property_metaid << std::endl;

        Triples triples;
        Triple is_property_of_triple(
                LibrdfNode::fromUriString(property_metaid).get(),
                BiomodelsBiologyQualifier("isPropertyOf").getNode(),
                LibrdfNode::fromUriString(subject_).get());
        triples.move_back(is_property_of_triple);

        if (!resource_.empty()) {
            Triple is_version_of_triple(
                    LibrdfNode::fromUriString(property_metaid).get(),
                    BiomodelsBiologyQualifier("isVersionOf").getNode(),
                    Resource(LibrdfNode::fromUriString(resource_)).getNode());
            triples.move_back(is_version_of_triple);
        }
        return triples;
    }

    const std::string &PhysicalProperty::getSubjectStr() const {
        return subject_;
    }

    void PhysicalProperty::setSubject(const std::string &subject) {
        if (OmexMetaUtils::startsWith(subject, "http")) {
            subject_ = subject;
        } else {
            subject_ = OmexMetaUtils::concatMetaIdAndUri(subject, getModelUri());
        }
    }

    const std::string &PhysicalProperty::getResourceStr() const {
        return resource_;
    }

    void PhysicalProperty::setResource(const std::string &resource) {
        resource_ = resource;
    }

    bool PhysicalProperty::operator==(const PhysicalProperty &rhs) const {
        return subject_ == rhs.subject_ &&
               resource_ == rhs.resource_;
    }

    bool PhysicalProperty::operator!=(const PhysicalProperty &rhs) const {
        return !(rhs == *this);
    }

    const std::string &PhysicalProperty::getSubject() const {
        return subject_;
    }

    const std::string &PhysicalProperty::getResource() const {
        return resource_;
    }

    const std::string &PhysicalProperty::getModelUri() const {
        return model_uri_;
    }

    void PhysicalProperty::setModelUri(const std::string &model_uri) {
        model_uri_ = model_uri;
    }


}// namespace omexmeta