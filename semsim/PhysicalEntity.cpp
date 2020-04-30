//
// Created by Ciaran on 4/22/2020.
//

#include "semsim/PhysicalEntity.h"

#include <utility>
#include "semsim/Triple.h"
#include "Query.h"
#include "SemsimUtils.h"

semsim::PhysicalEntity::PhysicalEntity(
        librdf_world *world,
        librdf_model *model,
        Subject metaid,
        semsim::PhysicalPropertyResource physicalProperty,
        semsim::Resource is,
        semsim::Resources is_part_of)
        : PhysicalPhenomenon(world, model, std::move(metaid), std::move(physicalProperty), PHYSICAL_ENTITY),
          is_(std::move(is)), isPartOf_(std::move(is_part_of)) {

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



semsim::Triples semsim::PhysicalEntity::toTriples() const {
    std::string property_metaid = SemsimUtils::generateUniqueMetaid(world_, model_, "PhysicalEntity");
    Triples triples = physical_property_.toTriples(subject_metaid_.str(), property_metaid);

    // what part of physical entity triple
    triples.emplace_back(
            world_,
            Subject(world_, RDFURINode(world_, property_metaid)),
            std::make_shared<Predicate>(BiomodelsBiologyQualifier(world_, "is")),
            getIdentityResource()
    );

    // the "where" part of the physical entity
    for (auto &locationResource : getLocationResources()) {
        triples.emplace_back(
                world_,
                Subject(world_, RDFURINode(world_, property_metaid)),
                std::make_shared<Predicate>(BiomodelsBiologyQualifier(world_, "isPartOf")),
                locationResource
        );
    }
    return triples;
}

















