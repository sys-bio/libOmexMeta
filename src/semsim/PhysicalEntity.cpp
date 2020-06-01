//
// Created by Ciaran on 4/22/2020.
//

#include "semsim/PhysicalEntity.h"

namespace semsim {
    PhysicalEntity::PhysicalEntity( const LibrdfModel& model,
            Subject metaid,
            PhysicalPropertyResource physicalProperty,
            Resource is,
            Resources is_part_of)
            : PhysicalPhenomenon(model, std::move(metaid), std::move(physicalProperty), PHYSICAL_ENTITY),
              identity_resource_(std::move(is)), location_resources(std::move(is_part_of)) {

    }


    PhysicalEntity::PhysicalEntity( LibrdfModel model) : PhysicalPhenomenon(model) {
    }


    PhysicalEntity &PhysicalEntity::setAbout(std::string metaid) {
        this->about = Subject::fromRawPtr( LibrdfNode::fromUriString(std::move(metaid)));
        return *this;

    }

    PhysicalEntity &PhysicalEntity::setPhysicalProperty(PhysicalPropertyResource physicalProperty) {
        PhysicalPhenomenon::physical_property_ = physicalProperty;
        return *this;
    }

    PhysicalEntity &PhysicalEntity::setPhysicalProperty(const std::string &physicalProperty) {
        physical_property_ = PhysicalPropertyResource( physicalProperty);
        return *this;
    }


    PhysicalEntity &PhysicalEntity::setIdentity(std::string resource) {
        // todo implement second argument which defaults to RDFUriNode
        //  and controls whether we use literal/blank/uri node
        identity_resource_ = Resource::fromRawPtr( LibrdfNode::fromUriString(std::move(resource)));
        return *this;
    }

    PhysicalEntity &PhysicalEntity::addLocation(std::string where) {
        location_resources.push_back(
                Resource::fromRawPtr( LibrdfNode::fromUriString(where))
        );
        return *this;
    }

    const Resource &PhysicalEntity::getIdentityResource() const {
        return identity_resource_;
    }

    const Resources &PhysicalEntity::getLocationResources() const {
        return location_resources;
    }

    Triples PhysicalEntity::toTriples() const {
//    if (!getAbout().isSet()) {
//        throw AnnotationBuilderException(
//                "PhysicalEntity::toTriples(): Cannot create"
//                " triples because the \"about\" information is not set. "
//                "Use the setAbout() method."
//        );
//    }
//    if (!getPhysicalProperty().isSet()) {
//        throw AnnotationBuilderException(
//                "PhysicalEntity::toTriples(): Cannot create"
//                " triples because the \"physical_property\" information is not set. "
//                "Use the setPhysicalProperty() method."
//        );
//    }
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
        std::string property_metaid = SemsimUtils::generateUniqueMetaid( model_, "PhysicalEntity",
                                                                        std::vector<std::string>());
        Triples triples = physical_property_.toTriples(about.str(), property_metaid);

        // what part of physical entity triple
        triples.emplace_back(
                Subject::fromRawPtr( LibrdfNode::fromUriString(property_metaid)),
                std::make_shared<Predicate>(BiomodelsBiologyQualifier( "is")),
                getIdentityResource()
        );

        // the "where" part of the physical entity
        for (auto &locationResource : getLocationResources()) {
            triples.emplace_back(
                    Subject::fromRawPtr( LibrdfNode::fromUriString(property_metaid)),
                    std::make_shared<Predicate>(BiomodelsBiologyQualifier( "isPartOf")),
                    locationResource
            );
        }
        return triples;
    }

    int PhysicalEntity::getNumLocations() {
        return getLocationResources().size();
    }

    PhysicalEntity::~PhysicalEntity() {

    }


}
















