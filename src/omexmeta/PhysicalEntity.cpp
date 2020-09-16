//
// Created by Ciaran on 4/22/2020.
//

#include "omexmeta/PhysicalEntity.h"

namespace omexmeta {

    PhysicalEntity::PhysicalEntity(librdf_model *model, std::string model_uri, std::string local_uri, PhysicalProperty physicalProperty,
                                   Resource is, Resources is_part_of)
            : PhysicalPhenomenon(model, model_uri, local_uri, std::move(physicalProperty), PHYSICAL_ENTITY),
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

    PhysicalEntity::PhysicalEntity(librdf_model *model) : PhysicalPhenomenon(model) {}

    PhysicalEntity::PhysicalEntity(librdf_model *model, const std::string& model_uri, const std::string& local_uri)
        : PhysicalPhenomenon(model, model_uri, local_uri) {}

    PhysicalEntity &PhysicalEntity::setPhysicalProperty(PhysicalProperty physicalProperty) {
        physical_property_ = std::move(physicalProperty);
        return *this;
    }

    PhysicalEntity &
    PhysicalEntity::setPhysicalProperty(std::string subject_metaid, const std::string &physicalProperty) {
        subject_metaid = OmexMetaUtils::concatMetaIdAndUri(subject_metaid, getModelUri());
        physical_property_ = PhysicalProperty(subject_metaid, physicalProperty, getModelUri());
        return *this;
    }


    PhysicalEntity &PhysicalEntity::setIdentity(const std::string &resource) {
        // todo implement second argument which defaults to RDFUriNode
        //  and controls whether we use literal/blank/uri node
        identity_resource_ = Resource(LibrdfNode::fromUriString(resource));
        return *this;
    }

    PhysicalEntity &PhysicalEntity::addLocation(const std::string &where) {
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
                    "Use the isVersionOf() method."
            );
        }

        if (getLocationResources().empty()) {
            throw AnnotationBuilderException(
                    "PhysicalProcess::toTriples(): cannot create "
                    "triples object because the\"location\" information "
                    "is empty. Please use the \"isVersionOf()\"."
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
        // when physical_property_id_ is empty it means we have not
        // called the toTriples() method before and an ID needs to be generated.
        // When it is not empty - we have called toTriples before and we can skip ID generation
        //
        // To further clarify, the entity_id_ needs to be a class level attribute
        // and initialized as an empty string. When its empty we need to generate a
        // new id but if its filled then we can generate Triples an arbitrary number
        // of times from the same PhysicalEntity instance and still get the same
        // Triples object. Note, this is important for deleting composites from the rdf model.
        if (entity_id_.empty()) {
            // no exclusions needed here - we only generate 1 process metaid before comiting the triples
            // to the model.
            entity_id_ = generateMetaId("PhysicalEntity");
        }
        entity_id_ = OmexMetaUtils::concatMetaIdAndUri(entity_id_, getLocalUri());
        // preallocate for efficiency
        Triples triples((int)getLocationResources().size() + 3);
        Triples physical_property_triples = physical_property_.toTriples(entity_id_);
        for (auto &it : physical_property_triples) {
            triples.move_back(it); // moves the statement
        }
        physical_property_triples.freeTriples();
        assert(physical_property_triples.size() == 0);

        // the "what" part of physical entity triple
        triples.emplace_back(
                LibrdfNode::fromUriString(entity_id_).get(),
                BiomodelsBiologyQualifier("is").getNode(),
                identity_resource_.getNode()
        );

        // the "where" part of the physical entity
        for (auto &locationResource : location_resources_) {
            triples.emplace_back(
                    LibrdfNode::fromUriString(entity_id_).get(),
                    BiomodelsBiologyQualifier("isPartOf").getNode(),
                    locationResource.getNode()
            );
        }
        return std::move(triples);
    }

    [[maybe_unused]] int PhysicalEntity::getNumLocations() const {
        return getLocationResources().size();
    }


    bool PhysicalEntity::operator==(const PhysicalEntity &rhs) const {
        return static_cast<const omexmeta::PhysicalPhenomenon &>(*this) ==
               static_cast<const omexmeta::PhysicalPhenomenon &>(rhs) &&
               identity_resource_ == rhs.identity_resource_ &&
               location_resources_ == rhs.location_resources_;
    }

    bool PhysicalEntity::operator!=(const PhysicalEntity &rhs) const {
        return !(rhs == *this);
    }

    PhysicalEntity &PhysicalEntity::isVersionOf(const std::string &is_version_of) {
        physical_property_.setResource(is_version_of);
        return *this;
    }

    PhysicalEntity &PhysicalEntity::setAbout(const std::string &about) {
        physical_property_.setSubject(about);
        return *this;
    }

    PhysicalEntity &PhysicalEntity::is(const std::string &is) {
        return setIdentity(is);
    }

    PhysicalEntity &PhysicalEntity::isPartOf(const std::string &isPartOf) {
        return addLocation(isPartOf);
    }


}
















