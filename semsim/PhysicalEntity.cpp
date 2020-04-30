//
// Created by Ciaran on 4/22/2020.
//

#include "semsim/PhysicalEntity.h"
#include "semsim/Triple.h"
#include "Query.h"

semsim::PhysicalEntity::PhysicalEntity(
        librdf_world *world,
        librdf_model *model,
        Subject metaid,
        semsim::PhysicalPropertyResource physicalProperty,
        semsim::Resource is,
        semsim::Resources is_part_of)
        : PhysicalPhenomenon(world, model, metaid, physicalProperty, PHYSICAL_ENTITY),
          is_(is), isPartOf_(is_part_of) {

}

std::string semsim::PhysicalEntity::createMetaId() const {
    return generateMetaId("PhysicalEntity");
}

const semsim::Resources &semsim::PhysicalEntity::getLocationResources() const {
    return isPartOf_;
}

const semsim::Resource &semsim::PhysicalEntity::getIdentityResource() const {
    return is_;
}


semsim::Triple semsim::PhysicalEntity::what() const {
    // the "what" part of the physical entity:
    return Triple(
            world_,
            subject_metaid_,
            std::make_shared<Predicate>(BiomodelsBiologyQualifier(world_, "is")),
            getIdentityResource()
    );
}

semsim::Triples semsim::PhysicalEntity::where() const {
    Triples triples;
    // the "where" part of the physical entity
    for (auto &locationResource : getLocationResources()) {
        triples.emplace_back(
                world_,
                Subject(world_, RDFURINode(world_, createMetaId())),
                std::make_shared<Predicate>(BiomodelsBiologyQualifier(world_, "isPartOf")),
                locationResource
        );
    }
    return triples;
}

semsim::Triples semsim::PhysicalEntity::toTriples() const {
    Triples triples = {
            physical_property_.toIsVersionOfTriple(subject_metaid_),
            what()
    };
    for (auto &trip : where()) {
        triples.push_back(trip);
    }
    return triples;
}

















