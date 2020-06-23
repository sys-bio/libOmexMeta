//
// Created by Ciaran on 4/22/2020.
//

#include "omexmeta/PhysicalEntity.h"

#include <utility>

namespace semsim {

    PhysicalEntity::PhysicalEntity(librdf_model *model,
                                   PhysicalProperty physicalProperty,
                                   Resource is,
                                   Resources is_part_of)
            : PhysicalPhenomenon(model, std::move(physicalProperty), PHYSICAL_ENTITY),
              identity_resource_(std::move(is)), location_resources_(std::move(is_part_of)) {}


    void PhysicalEntity::free() {
        if (identity_resource_.getNode() != nullptr) {
            identity_resource_.free();
            identity_resource_.setNode(nullptr);
        }

        for (auto &i : location_resources_) {
            if (i.getNode() != nullptr) {
                i.free();
                i.setNode(nullptr);
            }
        }
    }

    PhysicalEntity::PhysicalEntity(librdf_model *model) : PhysicalPhenomenon(model) {
    }


    PhysicalEntity &PhysicalEntity::setAbout(const std::string& metaid) {
        physical_property_.setSubject(metaid);
        return *this;
    }

    PhysicalEntity &PhysicalEntity::setPhysicalProperty(PhysicalProperty physicalProperty) {
        physical_property_ = std::move(physicalProperty);
        return *this;
    }

    PhysicalEntity &PhysicalEntity::setPhysicalProperty(const std::string &subject_metaid, const std::string &physicalProperty) {
        physical_property_ = PhysicalProperty(subject_metaid, physicalProperty);
        return *this;
    }


    PhysicalEntity &PhysicalEntity::setIdentity(const std::string& resource) {
        // todo implement second argument which defaults to RDFUriNode
        //  and controls whether we use literal/blank/uri node
        identity_resource_ = Resource(LibrdfNode::fromUriString(resource));
        return *this;
    }

    PhysicalEntity &PhysicalEntity::addLocation(const std::string& where) {
        location_resources_.push_back(std::move(
                Resource(LibrdfNode::fromUriString(where))
                )
        );
        return *this;
    }

    const Resource &PhysicalEntity::getIdentityResource() const {
        return identity_resource_;
    }

    const Resources &PhysicalEntity::getLocationResources() const {
        return location_resources_;
    }

    Triples PhysicalEntity::toTriples() {
        if (getAbout().empty()) {
            throw AnnotationBuilderException(
                    "PhysicalEntity::toTriples(): Cannot create"
                    " triples because the \"about\" information is not set. "
                    "Use the setAbout() method."
            );
        }

        if (getPhysicalProperty().getResourceStr().empty()) {
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

        // preallocate for efficiency
        Triples triples(getLocationResources().size() + 3);

        for (auto &it : physical_property_.toTriples(property_metaid)){
            triples.move_back(it);
        }

        // the "what" part of physical entity triple
        triples.emplace_back(
                LibrdfNode::fromUriString(property_metaid).get(),
                BiomodelsBiologyQualifier("is").getNode(),
                identity_resource_.getNode()
        );

        // the "where" part of the physical entity
        for (auto &locationResource : location_resources_) {
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

    bool PhysicalEntity::operator==(const PhysicalEntity &rhs) const {
        return static_cast<const semsim::PhysicalPhenomenon &>(*this) ==
               static_cast<const semsim::PhysicalPhenomenon &>(rhs) &&
               identity_resource_ == rhs.identity_resource_ &&
               location_resources_ == rhs.location_resources_;
    }

    bool PhysicalEntity::operator!=(const PhysicalEntity &rhs) const {
        return !(rhs == *this);
    }

}
















