//
// Created by Ciaran on 4/22/2020.
//

#include "PhysicalPropertyResource.h"


namespace semsim {

    PhysicalPropertyResource::PhysicalPropertyResource(std::string physical_property_string)
            : Resource(Resource::fromRawPtr(LibrdfNode::fromUriString(physical_property_string))) {
        validate();
    }

    void PhysicalPropertyResource::validate() {
        std::string expected_prefix1 = "https://identifiers.org/OPB"; //todo case speific?
        std::string expected_prefix2 = "https://identifiers.org/opb"; //todo case speific?
        std::string uri = str();
        if ((uri.rfind(expected_prefix1, 0) != 0) && (uri.rfind(expected_prefix2, 0) != 0)) {
            std::ostringstream err;
            err << __FILE__ << ":" << __LINE__ << ": The uri generated (";
            err << uri << ") is not a OPB resource. Physical properties "
                          "must be OPB resources.";
            throw semsim::InappropriateResourceException(err.str());
        }
    }

    Triple PhysicalPropertyResource::isVersionOfTriple(std::string subject_metaid) const {
        return Triple(
                Subject::fromRawPtr(LibrdfNode::fromUriString(subject_metaid)).getNode(),
                BiomodelsBiologyQualifier("isVersionOf").getNode(),
                Resource::fromRawPtr(node_).getNode()
        );
    }

    Triple PhysicalPropertyResource::isPropertyOfTriple(std::string subject_metaid, std::string property_metaid) const {
        return Triple(
                Subject::fromRawPtr(LibrdfNode::fromUriString(subject_metaid)).getNode(),
                BiomodelsBiologyQualifier("isPropertyOf").getNode(),
                Resource::fromRawPtr(LibrdfNode::fromUriString(property_metaid)).getNode()
        );
    }

    Triples PhysicalPropertyResource::toTriples(std::string subject_metaid, std::string property_metaid) const {
        return Triples({
                               isVersionOfTriple(subject_metaid),
                               isPropertyOfTriple(subject_metaid, property_metaid),
                       });
    }


    bool PhysicalPropertyResource::isSet() const {
        return node_ != nullptr;
    }


}