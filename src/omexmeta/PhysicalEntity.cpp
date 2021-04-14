//
// Created by Ciaran on 4/22/2020.
//

#include "omexmeta/PhysicalEntity.h"
#include "omexmeta/UriHandler.h"

namespace omexmeta {

    PhysicalEntity::PhysicalEntity(librdf_model *model, UriHandler &uriHandler, PhysicalProperty physicalProperty,
                                   Resource is, Resources is_part_of)
        : PropertyBearer(model, uriHandler, std::move(physicalProperty), PHYSICAL_ENTITY),
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

    PhysicalEntity::PhysicalEntity(librdf_model *model, UriHandler &uriHandler)
        : PropertyBearer(model, uriHandler) {}

    PhysicalEntity &PhysicalEntity::setPhysicalProperty(PhysicalProperty physicalProperty) {
        physical_property_ = std::move(physicalProperty);
        return *this;
    }

    PhysicalEntity &
    PhysicalEntity::setPhysicalProperty(std::string subject_metaid, const std::string &physicalProperty) {
        subject_metaid = OmexMetaUtils::concatMetaIdAndUri(subject_metaid, uriHandler_.getModelUri());
        physical_property_ = PhysicalProperty(model_, uriHandler_);
        physical_property_.about(subject_metaid)
                .isVersionOf(physicalProperty);
        return *this;
    }


    PhysicalEntity &PhysicalEntity::setIdentity(const std::string &resource) {
        // todo implement second argument which defaults to RDFUriNode
        //  and controls whether we use literal/blank/uri node
        identity_resource_ = Resource(LibrdfNode::fromUriString(resource));
        return *this;
    }

    PhysicalEntity &PhysicalEntity::identity(const std::string &resource) {
        return setIdentity(resource);
    }

    PhysicalEntity &PhysicalEntity::addLocation(const std::string &where) {
        location_resources_.push_back(std::move(
                Resource(LibrdfNode::fromUriString(where))));
        return *this;
    }

    PhysicalEntity &PhysicalEntity::hasPart(const std::string &where) {
        part_resources_.push_back(std::move(
                Resource(LibrdfNode::fromUriString(where))));
        return *this;
    }

    const Resource &PhysicalEntity::getIdentityResource() const {
        return identity_resource_;
    }

    const Resources &PhysicalEntity::getLocationResources() const {
        return location_resources_;
    }

    Triples PhysicalEntity::toTriples() {

        // when physical_property_id_ is empty it means we have not
        // called the toTriples() method before and an ID needs to be generated.
        // When it is not empty - we have called toTriples before and we can skip ID generation
        //
        // To further clarify, the entity_id_ needs to be a class level attribute
        // and initialized as an empty string. When its empty we need to generate a
        // new id but if its filled then we can generate Triples an arbitrary number
        // of times from the same PhysicalEntity instance and still get the same
        // Triples object. Note, this is important for deleting composites from the rdf model.
        if (physical_property_.getIsPropertyOfValue().empty() || physical_property_.getPropertyMetaidBase() == "Property") {
            // we do not set the value of the PhysicalProperty objects subject portion of Triple
            // but instead change the base name for the PhysicalProperty and it'll generate
            // an appropriate id itself.
            physical_property_.setPropertyMetaidBase("EntityProperty");
        }

        if (OmexMetaUtils::isStringEmpty<PhysicalEntity>(*this, about_value_)) {
            about(OmexMetaUtils::generateUniqueMetaid(model_, "Entity", new_metaid_exclusion_list_), LOCAL_URI);
            physical_property_.isPropertyOf(about_value_, LOCAL_URI);
        }


        // preallocate for efficiency
        Triples triples((int) getLocationResources().size() + (int) part_resources_.size() + 3);

        /**
         * Patch around physical property triples generation.
         * This can be made more concise but for now we just use patch.
         * When there is no physical property we do not add property related
         * triples
         */
        if (physical_property_.isSet()) {
            Triples physical_property_triples = physical_property_.toTriples();

            for (auto &it : physical_property_triples) {
                triples.moveBack(it);// moves the statement
            }
            // we do not need to freeTriples here
            // since the move gives ownership to triples object
            //
            // physical_property_triples.freeTriples();
        }

        // the "what" part of physical entity triple
        if (identity_resource_.isSet()) {
            triples.emplace_back(
                    uriHandler_,
                    LibrdfNode::fromUriString(physical_property_.getIsPropertyOfValue()).get(),
                    BiomodelsBiologyQualifier("is").getNode(),
                    identity_resource_.getNode()
                    );
        }

        // make it explicit that location resources is optional
        if (!location_resources_.empty()) {
            // the "where" part of the physical entity
            for (auto &locationResource : location_resources_) {
                triples.emplace_back(
                        uriHandler_,
                        LibrdfNode::fromUriString(physical_property_.getIsPropertyOfValue()).get(),
                        BiomodelsBiologyQualifier("isPartOf").getNode(),
                        locationResource.getNode());
            }
        }
        // make it explicit that hasPart resources is optional
        if (!part_resources_.empty()) {
            // the "where" part of the physical entity
            for (auto &locationResource : part_resources_) {
                triples.emplace_back(
                        uriHandler_,
                        LibrdfNode::fromUriString(physical_property_.getIsPropertyOfValue()).get(),
                        BiomodelsBiologyQualifier("hasPart").getNode(),
                        locationResource.getNode());
            }
        }
        return std::move(triples);
    }

    [[maybe_unused]] int PhysicalEntity::getNumLocations() const {
        return getLocationResources().size();
    }


    bool PhysicalEntity::operator==(const PhysicalEntity &rhs) const {
        return static_cast<const omexmeta::PropertyBearer &>(*this) ==
                       static_cast<const omexmeta::PropertyBearer &>(rhs) &&
               identity_resource_ == rhs.identity_resource_ &&
               location_resources_ == rhs.location_resources_;
    }

    bool PhysicalEntity::operator!=(const PhysicalEntity &rhs) const {
        return !(rhs == *this);
    }


    PhysicalEntity &PhysicalEntity::isPropertyOf(const std::string &is_property_of, eUriType type) {
        physical_property_.isPropertyOf(is_property_of, type);
        return *this;
    }

    PhysicalEntity &PhysicalEntity::propertyIsVersionOf(const std::string &is_version_of) {
        physical_property_.isVersionOf(is_version_of);
        return *this;
    }

    PhysicalEntity &PhysicalEntity::about(const std::string &about, eUriType type) {
        PropertyBearer::about(about, type);
        return *this;
    }

    PhysicalEntity &PhysicalEntity::about(const std::string &about) {
        PropertyBearer::about(about);
        return *this;
    }

    PhysicalEntity &PhysicalEntity::is(const std::string &is) {
        return setIdentity(is);
    }

    PhysicalEntity &PhysicalEntity::isPartOf(std::string isPartOf, eUriType type) {
        isPartOf = UriHandler::uriModifier<PhysicalEntity>(*this, isPartOf, type);
        location_resources_.push_back(std::move(
                Resource(LibrdfNode::fromUriString(isPartOf))));
        return *this;
    }

    PhysicalEntity &PhysicalEntity::variableMetaId(const std::string &metaid) {
        physical_entity_property_id_ = OmexMetaUtils::concatMetaIdAndUri(metaid, getModelUri());
        return *this;
    }

    const std::string &PhysicalEntity::getPropertyMetaidBase() const {
        return property_metaid_base_;
    }
    PhysicalEntity &PhysicalEntity::hasProperty(const PhysicalProperty &property) {
        PropertyBearer::hasProperty(property);
        return *this;
    }
    //    PhysicalEntity &PhysicalEntity::hasProperty(const std::string &property_about, eUriType about_uri_type, const std::string &is_version_of, const std::string &is_property_of, eUriType is_property_of_uri_type) {
    //        PropertyBearer::hasProperty(property_about, about_uri_type, is_version_of, is_property_of, is_property_of_uri_type);
    //        return *this;
    //    }
    PhysicalEntity &PhysicalEntity::hasProperty(const std::string &is_version_of) {
        PropertyBearer::hasProperty(is_version_of);
        return *this;
    }
    PhysicalEntity &PhysicalEntity::hasProperty(const std::string &property_about, eUriType about_uri_type, const std::string &is_version_of) {
        PropertyBearer::hasProperty(property_about, about_uri_type, is_version_of);
        return *this;
    }


}// namespace omexmeta
