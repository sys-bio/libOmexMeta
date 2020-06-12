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

    Triple PhysicalPropertyResource::isVersionOfTriple(const Subject &subject_metaid) {
        Triple triple(
                subject_metaid.getNode(),
                BiomodelsBiologyQualifier("isVersionOf").getNode(),
                node_
        );
        // The node_ object is used up - ownership responsibility
        // is passed on to the Triple.
        node_ = nullptr;
        return triple;
    }

    Triple PhysicalPropertyResource::isPropertyOfTriple(std::string subject_metaid, std::string property_metaid) const {
        return Triple(
                LibrdfNode::fromUriString(subject_metaid).get(),
                BiomodelsBiologyQualifier("isPropertyOf").getNode(),
                LibrdfNode::fromUriString(property_metaid).get()
        );
    }

    Triple
    PhysicalPropertyResource::isPropertyOfTriple(const Subject &subject_metaid, std::string property_metaid) const {
        return Triple(
                subject_metaid.getNode(),
                BiomodelsBiologyQualifier("isPropertyOf").getNode(),
                LibrdfNode::fromUriString(property_metaid).get()
        );
    }

    Triples PhysicalPropertyResource::toTriples(std::string subject_metaid, std::string property_metaid) const {
        Triple v = isVersionOfTriple(subject_metaid);
        Triple p = isPropertyOfTriple(subject_metaid, property_metaid);
        Triples triples;
        triples.move_back(v);
        triples.move_back(p);
        return triples;
    }

    Triples PhysicalPropertyResource::toTriples(Subject subject_metaid, std::string property_metaid) {
        Triple v = isVersionOfTriple(subject_metaid);
        Triple p = isPropertyOfTriple(subject_metaid, property_metaid);

        /*
         * Here we have used subject_metaid twice. Both times
         * the same node is being used but this is happening
         * outside the scope of librdf functions (i.e. in this function)
         * The librdf functinos would add 1 to the internal reference
         * counter of the node.
         * While a bit of a hack, here we add 1 to the node usage
         * manually so that we do not get a access violation error
         * later.
         * todo: find a better solution to this problem.
         */
        subject_metaid.getNode()->usage++;

        Triples triples;
        triples.move_back(v);
        triples.move_back(p);
        return triples;
    }


    bool PhysicalPropertyResource::isSet() const {
        return node_ != nullptr;
    }


}