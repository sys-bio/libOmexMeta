//
// Created by Ciaran on 4/22/2020.
//

#include "PhysicalPropertyResource.h"
#include "Triple.h"
#include "Triples.h"
#include <regex>

namespace semsim {

    PhysicalPropertyResource::PhysicalPropertyResource(librdf_world *world, RDFURINode node)
            : Resource(world, node) {
        validate();
    }


    PhysicalPropertyResource::PhysicalPropertyResource(librdf_world *world, std::string node)
            : Resource(world, RDFURINode(world, node)) {
        validate();
    }

    void PhysicalPropertyResource::validate() {
        std::string expected_prefix = "https://identifiers.org/OPB"; //todo case speific?
        std::string uri = str();
        if (uri.rfind(expected_prefix, 0) != 0) {
            std::ostringstream err;
            err << __FILE__ << ":" << __LINE__ << ": The uri generated (";
            err << uri << ") is not a OPB resource. Physical properties "
                          "must be OPB resources.";
            throw semsim::InappropriateResourceException(err.str());
        }
    }
//
//    Triple PhysicalPropertyResource::isVersionOf(Subject subject_metaid) const {
//        return Triple(
//                world_,
//                subject_metaid,
//                BiomodelsBiologyQualifier(world_, "isVersionOf"),
//                Resource(world_, RDFURINode(world_, rdf_node_ptr_->str()))
//        );
//    }

    Triple PhysicalPropertyResource::isVersionOfTriple(std::string subject_metaid) const {
        return Triple(
                world_,
                Subject(world_, RDFURINode(world_, subject_metaid)),
                BiomodelsBiologyQualifier(world_, "isVersionOf"),
                Resource(world_, RDFURINode(world_, rdf_node_ptr_->str()))
        );
    }

    Triple PhysicalPropertyResource::isPropertyOfTriple(std::string subject_metaid, std::string property_metaid) const {
        return Triple(
                world_,
                Subject(world_, RDFURINode(world_, subject_metaid)),
                BiomodelsBiologyQualifier(world_, "isPropertyOf"),
                Resource(world_, RDFURINode(world_, property_metaid))
        );
    }

    Triples PhysicalPropertyResource::toTriples(std::string subject_metaid, std::string property_metaid) const {
        return Triples({
            isVersionOfTriple(subject_metaid),
            isPropertyOfTriple(subject_metaid, property_metaid),
        });
    }


}