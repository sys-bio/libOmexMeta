//
// Created by Ciaran on 4/22/2020.
//

#include "PhysicalEntity.h"

#include <utility>
#include "Triple.h"
#include "Query.h"
#include "SemsimUtils.h"
#include "memory"

semsim::PhysicalEntity::PhysicalEntity(
        LibrdfWorld world,
        LibrdfModel model,
        Subject metaid,
        semsim::PhysicalPropertyResource physicalProperty,
        semsim::Resource is,
        semsim::Resources is_part_of)
        : PhysicalPhenomenon(world, model, std::move(metaid), std::move(physicalProperty), PHYSICAL_ENTITY),
          identity_resource_(std::move(is)), location_resources(std::move(is_part_of)) {

}


semsim::PhysicalEntity::PhysicalEntity(LibrdfWorld world, LibrdfModel model) : PhysicalPhenomenon(world, model) {
}


semsim::PhysicalEntity &semsim::PhysicalEntity::setAbout(std::string metaid) {
    this->about = Subject(world_, RDFURINode(world_, std::move(metaid)));
    return *this;

}

semsim::PhysicalEntity &semsim::PhysicalEntity::setPhysicalProperty(PhysicalPropertyResource physicalProperty) {
    PhysicalPhenomenon::physical_property_ = physicalProperty;
    return *this;
}

semsim::PhysicalEntity &semsim::PhysicalEntity::setPhysicalProperty(const std::string &physicalProperty) {
    physical_property_ = PhysicalPropertyResource(world_, RDFURINode(world_, physicalProperty));
    return *this;
}


semsim::PhysicalEntity &semsim::PhysicalEntity::setIdentity(std::string resource) {
    // todo implement second argument which defaults to RDFUriNode
    //  and controls whether we use literal/blank/uri node
    identity_resource_ = Resource(world_, RDFURINode(world_, std::move(resource)));
    return *this;
}

semsim::PhysicalEntity &semsim::PhysicalEntity::addLocation(std::string where) {
    location_resources.push_back(
            Resource(world_, RDFURINode(world_, where))
    );
    return *this;
}

const semsim::Resource &semsim::PhysicalEntity::getIdentityResource() const {
    return identity_resource_;
}

const semsim::Resources &semsim::PhysicalEntity::getLocationResources() const {
    return location_resources;
}

semsim::Triples semsim::PhysicalEntity::toTriples() const {
    if (!getAbout().isSet()) {
        throw AnnotationBuilderException(
                "PhysicalEntity::toTriples(): Cannot create"
                " triples because the \"about\" information is not set. "
                "Use the setAbout() method."
        );
    }
    if (!getPhysicalProperty().isSet()) {
        throw AnnotationBuilderException(
                "PhysicalEntity::toTriples(): Cannot create"
                " triples because the \"physical_property\" information is not set. "
                "Use the setPhysicalProperty() method."
        );
    }
    if (getLocationResources().empty()) {
        throw AnnotationBuilderException(
                "PhysicalEntity::toTriples(): cannot create "
                "triples object because the\"location\" information "
                "is empty. Use the addLocation() method."
        );
    }
    int count = 0;
    for (auto &i : getLocationResources()) {
        if (!i.isSet()) {
            std::ostringstream err;
            err << "PhysicalEntity::toTriples(): Cannot create"
                   " triples because item ";
            err << count << "of the \"location\" information is not set. ";
            err << "Use the addLocation() method.";
            throw AnnotationBuilderException(
                    err.str()
            );
        }
    }
    // no exclusions needed here - we only generate 1 process metaid before commiting the triples
    // to the model.
    std::string property_metaid = SemsimUtils::generateUniqueMetaid(world_, model_, "PhysicalEntity", std::vector<std::string>());
    Triples triples = physical_property_.toTriples(about.str(), property_metaid);

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

int semsim::PhysicalEntity::getNumLocations() {
    return getLocationResources().size();
}

















