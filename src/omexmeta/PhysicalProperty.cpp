//
// Created by Ciaran on 4/22/2020.
//

#include "PhysicalProperty.h"

#include <utility>


namespace semsim {

    PhysicalProperty::PhysicalProperty(std::string subject_str, std::string resource_str)
            : subject_(std::move(subject_str)),
              resource_(std::move(resource_str)) {
        validate();
    }

    void PhysicalProperty::validate() {
        std::string expected_prefix1 = "https://identifiers.org/OPB";
        std::string expected_prefix2 = "https://identifiers.org/opb";

        // create a temporary resource obj for checking only.
        Resource r(LibrdfNode::fromUriString(resource_));
        std::string uri = r.str();
        r.free();
        if ((uri.rfind(expected_prefix1, 0) != 0) && (uri.rfind(expected_prefix2, 0) != 0)) {
            std::ostringstream err;
            err << __FILE__ << ":" << __LINE__ << ": The uri generated (";
            err << uri << ") is not a OPB resource. Physical properties "
                          "must be OPB resources.";
            throw semsim::InappropriateResourceException(err.str());
        }
    }


    Triples PhysicalProperty::toTriples(const std::string &property_metaid) const {
        Triple is_version_of_triple(
                LibrdfNode::fromUriString(subject_).get(),
                BiomodelsBiologyQualifier("isVersionOf").getNode(),
                Resource(LibrdfNode::fromUriString(resource_)).getNode()
        );
        Triple is_property_of_triple(
                LibrdfNode::fromUriString(subject_).get(),
                BiomodelsBiologyQualifier("isPropertyOf").getNode(),
                LibrdfNode::fromUriString(property_metaid).get()
        );
        Triples triples;
        triples.move_back(is_version_of_triple);
        triples.move_back(is_property_of_triple);
        return triples;
    }

    const std::string &PhysicalProperty::getSubjectStr() const {
        return subject_;
    }

    void PhysicalProperty::setSubject(const std::string &subject) {
        subject_ = subject;
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



}