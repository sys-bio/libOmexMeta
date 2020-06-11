//
// Created by Ciaran on 4/22/2020.
//

#include "PhysicalPropertyResource.h"


namespace semsim {

    PhysicalPropertyResource::PhysicalPropertyResource(std::string physical_property_string)
            : Resource(Resource::fromRawPtr(LibrdfNode::fromUriString(physical_property_string).get())) {
        validate();
    }

    void PhysicalPropertyResource::validate() {
        std::string expected_prefix1 = "https://identifiers.org/OPB";
        std::string expected_prefix2 = "https://identifiers.org/opb";
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
                LibrdfNode::fromUriString(subject_metaid).get(),
                BiomodelsBiologyQualifier("isVersionOf").getNode(),
                Resource::fromRawPtr(node_).getNode()
        );
    }

    Triple PhysicalPropertyResource::isPropertyOfTriple(std::string subject_metaid, std::string property_metaid) const {
        return Triple(
                LibrdfNode::fromUriString(subject_metaid).get(),
                BiomodelsBiologyQualifier("isPropertyOf").getNode(),
                LibrdfNode::fromUriString(property_metaid).get()
        );
    }

    Triples PhysicalPropertyResource::toTriples(std::string subject_metaid, std::string property_metaid) const {
        
        Triple v = isVersionOfTriple(subject_metaid);
        
        Triple p = isPropertyOfTriple(subject_metaid, property_metaid);
        
        return Triples({v, p});
    }


    bool PhysicalPropertyResource::isSet() const {
        return node_ != nullptr;
    }


}