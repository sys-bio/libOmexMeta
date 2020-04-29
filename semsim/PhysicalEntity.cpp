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


semsim::Triple semsim::PhysicalEntity::whatTriple() const {
    // the "what" part of the physical entity:
    return Triple(
            world_,
            subject_metaid_,
            std::make_shared<Predicate>(BiomodelsBiologyQualifier(world_, "is")),
            getIdentityResource()
    );
}

semsim::Triples semsim::PhysicalEntity::whereTriple() const {
    RDFURINode entity_metaid_node = RDFURINode(world_, generateMetaId(createMetaId()));
    Triples triples;
    // the "where" part of the physical entity
    for (auto &locationResource : getLocationResources()) {
        triples.emplace_back(
                world_,
                Subject(world_, entity_metaid_node),
                std::make_shared<Predicate>(BiomodelsBiologyQualifier(world_, "isPartOf")),
                locationResource
        );
    }
    return triples;
}

semsim::Triples semsim::PhysicalEntity::toTriples() const {
    Triples triples = {
            physical_property_.toIsVersionOfTriple(subject_metaid_),
            whatTriple()
    };
    for (auto &trip : whereTriple()) {
        triples.push_back(trip);
    }
    return triples;
}
