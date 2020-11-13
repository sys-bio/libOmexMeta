//
// Created by Ciaran on 4/22/2020.
//

#include "omexmeta/PhysicalEntity.h"
#include "omexmeta/UriHandler.h"

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

    PhysicalEntity::PhysicalEntity(librdf_model *model, const std::string &model_uri, const std::string &local_uri)
        : PhysicalPhenomenon(model, model_uri, local_uri) {}

    PhysicalEntity &PhysicalEntity::setPhysicalProperty(PhysicalProperty physicalProperty) {
        physical_property_ = std::move(physicalProperty);
        return *this;
    }

    OMEXMETA_DEPRECATED PhysicalEntity &
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

    void PhysicalEntity::autoGenerateAbout(){
        if (getAbout().empty() ||
            getAbout() == local_uri_ ||
            getAbout() == local_uri_ + "#" ||
            getAbout() == model_uri_ ||
            getAbout() == model_uri_+ "#"
            ) {
            about(OmexMetaUtils::generateUniqueMetaid(model_, "Entity", new_metaid_exclusion_list_), LOCAL_URI);
        }
    }

    Triples PhysicalEntity::toTriples() {
        // conditionals included within autoGenerateAbout such that only generates when about is empty or local/model uri
//        autoGenerateAbout();

        std::cout << __FILE__ << ":" << __LINE__ << std::endl;

        // when physical_property_id_ is empty it means we have not
        // called the toTriples() method before and an ID needs to be generated.
        // When it is not empty - we have called toTriples before and we can skip ID generation
        //
        // To further clarify, the entity_id_ needs to be a class level attribute
        // and initialized as an empty string. When its empty we need to generate a
        // new id but if its filled then we can generate Triples an arbitrary number
        // of times from the same PhysicalEntity instance and still get the same
        // Triples object. Note, this is important for deleting composites from the rdf model.
        if (physical_property_.getIsPropertyOfValue().empty()) {
            // no exclusions needed here - we only generate 1 process metaid before comiting the triples
            // to the model.
            physical_property_.isPropertyOf(generateMetaId("EntityProperty"), LOCAL_URI);
        }

        std::cout << __FILE__ << ":" << __LINE__ << std::endl;

        // preallocate for efficiency
        std::cout << __FILE__ << ":" << __LINE__ << std::endl;
        Triples triples((int) getLocationResources().size() + (int) part_resources_.size() + 3);

        std::cout << __FILE__ << ":" << __LINE__ << std::endl;
        Triples physical_property_triples = physical_property_.toTriples();

        std::cout << __FILE__ << ":" << __LINE__ << std::endl;
        for (auto &it : physical_property_triples) {
            triples.move_back(it);// moves the statement
        }

        physical_property_triples.freeTriples();
        assert(physical_property_triples.size() == 0);


        // the "what" part of physical entity triple

        if (identity_resource_.isSet()) {
            triples.emplace_back(
                    LibrdfNode::fromUriString(physical_property_.getIsPropertyOfValue()).get(),
                    BiomodelsBiologyQualifier("is").getNode(),
                    identity_resource_.getNode());
        }

        // make it explicit that location resources is optional
        if (!location_resources_.empty()) {
            // the "where" part of the physical entity
            for (auto &locationResource : location_resources_) {
                triples.emplace_back(
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
        return static_cast<const omexmeta::PhysicalPhenomenon &>(*this) ==
                       static_cast<const omexmeta::PhysicalPhenomenon &>(rhs) &&
               identity_resource_ == rhs.identity_resource_ &&
               location_resources_ == rhs.location_resources_;
    }

    bool PhysicalEntity::operator!=(const PhysicalEntity &rhs) const {
        return !(rhs == *this);
    }

    PhysicalEntity &PhysicalEntity::isVersionOf(const std::string &version) {
        physical_property_.isVersionOf(version);
        return *this;
    }


    PhysicalEntity &PhysicalEntity::isPropertyOf(const std::string &is_property_of, eUriType type) {
        physical_property_.isPropertyOf(is_property_of, type);
        return *this;
    }

    PhysicalEntity &PhysicalEntity::about(const std::string &about, eUriType type) {
        if (!OmexMetaUtils::startsWith(about, "http"))
            physical_property_.about(OmexMetaUtils::concatMetaIdAndUri(about, model_uri_));
        else
            physical_property_.about(about, type);
        return *this;
    }

    PhysicalEntity &PhysicalEntity::is(const std::string &is) {
        return setIdentity(is);
    }

    PhysicalEntity &PhysicalEntity::isPartOf(const std::string &isPartOf) {
        return addLocation(isPartOf);
    }


    PhysicalEntity &PhysicalEntity::variableMetaId(const std::string &metaid) {
        physical_entity_property_id_ = OmexMetaUtils::concatMetaIdAndUri(metaid, model_uri_);
        return *this;
    }
    const std::string &PhysicalEntity::getPropertyMetaidBase() const {
        return property_metaid_base_;
    }

    PhysicalEntity &PhysicalEntity::hasProperty(const PhysicalProperty &property){
        physical_property_ = property;
        if (
                physical_property_.getIsPropertyOfValue().empty() ||
                physical_property_.getIsPropertyOfValue() == local_uri_ ||
                physical_property_.getIsPropertyOfValue() == local_uri_ + "#" ||
                physical_property_.getIsPropertyOfValue() == model_uri_ ||
                physical_property_.getIsPropertyOfValue() == model_uri_ + "#") {
            // physical property takes care of using EntityProperty for generating ids
            physical_property_.setPropertyMetaidBase(getPropertyMetaidBase());
        }

        return *this;
    }


    PhysicalEntity& PhysicalEntity::hasProperty(const std::string& property_about, eUriType about_uri_type){
        /*
         * Two scenarios:
         *  1) User wants to provide their own strings to use for the property about section.
         *  2) the user wants the library to autogenerate a property metaid, which will be local to rdf document
         */
        if (property_about.empty()){
            // option 2
            physical_property_ = PhysicalProperty(model_, model_uri_, local_uri_).about(getAbout(), MODEL_URI);
            physical_property_.setPropertyMetaidBase(getPropertyMetaidBase());

        } else {
            // option 1
            physical_property_ = PhysicalProperty(model_, model_uri_, local_uri_).about(property_about, about_uri_type);
        }
        return *this;
    }

    const std::string &PhysicalPhenomenon::getPropertyMetaidBase() const {
        return property_metaid_base_;
    }



}// namespace omexmeta
