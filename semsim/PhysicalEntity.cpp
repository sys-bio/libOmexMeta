//
// Created by Ciaran on 4/22/2020.
//

#include "semsim/PhysicalEntity.h"
#include "semsim/Triple.h"

// todo perhaps the observer pattern for metaid's:
//  the observed is a class storing all metaids in use.
//  The observers are objects that need to know the metaids.
//  Could have a superclass of all observers for implementing the method
//  that receives observations???

semsim::PhysicalEntity::PhysicalEntity(
        librdf_world *world,
        Subject metaid,
        semsim::PhysicalPropertyResource physicalProperty,
        semsim::Resource is,
        semsim::Resources is_part_of)
        : PhysicalPhenomenon(world, metaid, physicalProperty, PHYSICAL_ENTITY),
          is_(is), isPartOf_(is_part_of) {

}

/*
 * The problem: We need to ensure these identifiers are unique.
 * Get xmlassistnat classes to store the located
 * metaids in a variable that can be passed to the editor.
 * We'll need to do something special for finding the metaid of existing
 * physicalXX elements since they are burried
 *    ... what if we just add them to the addepted terms in xml assistant?
 */
std::string semsim::PhysicalEntity::createMetaId(librdf_model *model, std::string base_metaid) const {
    return "entityMetaidPlaceholder";
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
    RDFURINode entity_metaid_node = RDFURINode(world_, createMetaId(nullptr, "entity"));
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
