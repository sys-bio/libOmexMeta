//
// Created by Ciaran on 4/22/2020.
//

#include "semsim/PhysicalEntity.h"

#include <utility>

namespace semsim {

    PhysicalEntity::PhysicalEntity(librdf_model *model,
                                   Subject about,
                                   PhysicalPropertyResource physicalProperty,
                                   Resource is,
                                   Resources is_part_of)
            : PhysicalPhenomenon(model, about, std::move(physicalProperty), PHYSICAL_ENTITY),
              identity_resource_(std::move(is)), location_resources(std::move(is_part_of)) {}


    void PhysicalEntity::free() {
        if (about.getNode() != nullptr) {
            about.free();
            about.setNode(nullptr);
        }

        if (physical_property_.getNode() != nullptr) {
            physical_property_.free();
            physical_property_.setNode(nullptr);
        }
        if (identity_resource_.getNode() != nullptr) {
            identity_resource_.free();
            identity_resource_.setNode(nullptr);
        }

        for (auto &i : location_resources) {
            if (i.getNode() != nullptr) {
                i.free();
                i.setNode(nullptr);
            }
        }
    }

    PhysicalEntity::PhysicalEntity(librdf_model *model) : PhysicalPhenomenon(model) {
    }


    PhysicalEntity &PhysicalEntity::setAbout(std::string metaid) {
        this->about = Subject::fromRawPtr(LibrdfNode::fromUriString(metaid).get());
        return *this;

    }

    PhysicalEntity &PhysicalEntity::setPhysicalProperty(PhysicalPropertyResource physicalProperty) {
        PhysicalPhenomenon::physical_property_ = physicalProperty;
        return *this;
    }

    PhysicalEntity &PhysicalEntity::setPhysicalProperty(const std::string &physicalProperty) {
        physical_property_ = PhysicalPropertyResource(physicalProperty);
        return *this;
    }


    PhysicalEntity &PhysicalEntity::setIdentity(std::string resource) {
        // todo implement second argument which defaults to RDFUriNode
        //  and controls whether we use literal/blank/uri node
        identity_resource_ = Resource::fromRawPtr(LibrdfNode::fromUriString(std::move(resource)).get());
        return *this;
    }

    PhysicalEntity &PhysicalEntity::addLocation(std::string where) {
        location_resources.push_back(
                Resource::fromRawPtr(LibrdfNode::fromUriString(where).get())
        );
        return *this;
    }

    const Resource &PhysicalEntity::getIdentityResource() const {
        return identity_resource_;
    }

    const Resources &PhysicalEntity::getLocationResources() const {
        return location_resources;
    }

    Triples PhysicalEntity::toTriples() {
        
        if (getAbout().getNode() == nullptr) {
            throw AnnotationBuilderException(
                    "PhysicalEntity::toTriples(): Cannot create"
                    " triples because the \"about\" information is not set. "
                    "Use the setAbout() method."
            );
        }
        
        if (getPhysicalProperty().getNode() == nullptr) {
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
            
            if (i.getNode() == nullptr) {
                
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
        // no exclusions needed here - we only generate 1 process metaid before comiting the triples
        // to the model.
        std::string property_metaid = SemsimUtils::generateUniqueMetaid(
                model_, "PhysicalEntity",
                std::vector<std::string>());

        
        Triples triples = physical_property_.toTriples(about.str(), property_metaid);


        
        std::cout << "about to free about" << std::endl;
//        about.free();

        
        // the "what" part of physical entity triple
        triples.emplace_back(
                LibrdfNode::fromUriString(property_metaid).get(),
                BiomodelsBiologyQualifier("is").getNode(),
                getIdentityResource().getNode()
        );
        
        // the "where" part of the physical entity
        for (auto &locationResource : getLocationResources()) {
            triples.emplace_back(
                    LibrdfNode::fromUriString(property_metaid).get(),
                    BiomodelsBiologyQualifier("isPartOf").getNode(),
                    locationResource.getNode()
            );
        }
        

        return triples;
    }

    [[maybe_unused]] int PhysicalEntity::getNumLocations() const {
        return getLocationResources().size();
    }


}
















