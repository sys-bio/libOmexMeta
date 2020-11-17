//
// Created by Ciaran on 4/22/2020.
//

#include "omexmeta/PhysicalForce.h"


namespace omexmeta {

    PhysicalForce::PhysicalForce(librdf_model *model, std::string model_uri, std::string local_uri,
                                 PhysicalProperty physicalProperty,
                                 Sources sources,
                                 Sinks sinks)
        : PhysicalPhenomenon(model, model_uri, local_uri, std::move(physicalProperty), PHYSICAL_PROCESS),
          sources_(std::move(sources)), sinks_(std::move(sinks)) {
    }

    const std::vector<SourceParticipant> &PhysicalForce::getSources() const {
        return sources_;
    }

    const std::vector<SinkParticipant> &PhysicalForce::getSinks() const {
        return sinks_;
    }

    std::string PhysicalForce::createMetaId() {
        return generateMetaId("PhysicalForce");
    }

    Triples PhysicalForce::toTriples() {
        //        if (getAbout().empty() || getAbout() == model_uri_ + "#") {
        //            std::string new_about = generateMetaId("Force");
        //            about(OmexMetaUtils::concatMetaIdAndUri(new_about, local_uri_));
        //        }
        //        if (physical_force_property_id_.empty()) {
        //            physical_force_property_id_ = generateMetaId("ForceProperty");
        //            physical_property_.about(physical_force_property_id_, LOCAL_URI);
        //        }
        // check PhysicalForce::getAbout for being empty. Autogenerate id if true.

        std::cout << "getAbout(): " << getAbout() << std::endl;
        if (OmexMetaUtils::isStringEmpty<PhysicalForce>(*this, getAbout())) {
            std::cout << "getAbout(): " << getAbout() << std::endl;
            std::string new_force_about_value = generateMetaId("Force");
            std::cout << "getAbout(): " << getAbout() << std::endl;
            about(new_force_about_value, LOCAL_URI);
            std::cout << "getAbout(): " << getAbout() << std::endl;
        }
        std::cout << "getAbout(): " << getAbout() << std::endl;

        if (OmexMetaUtils::isStringEmpty<PhysicalForce>(*this, physical_property_.getAbout())) {
            // the PhysicalProperty will autogenerate its own about metaid. We set this base to something more approprioate for a PhysicalProcess
            physical_property_.setPropertyMetaidBase("ForceProperty");
        }

        // We also have to update the
        // isPropertyOf field of the physical_property
        physical_property_.isPropertyOf(getAbout(), LOCAL_URI);


        Triples triples = physical_property_.toTriples();
        for (auto &source : sources_) {
            for (auto &triple : source.toTriples(getAbout(), new_metaid_exclusion_list_)) {
                triples.move_back(triple);
            }
        }
        for (auto &sink : sinks_) {
            for (auto &triple : sink.toTriples(getAbout(), new_metaid_exclusion_list_)) {
                triples.move_back(triple);
            }
        }
        return triples;
    }

    PhysicalForce &PhysicalForce::setPhysicalProperty(PhysicalProperty physicalProperty) {
        physical_property_ = std::move(physicalProperty);
        return (*this);
    }

    PhysicalForce &PhysicalForce::setPhysicalProperty(std::string subject_metaid, std::string physical_property) {
        if (!OmexMetaUtils::startsWith(subject_metaid, "http")) {
            subject_metaid = OmexMetaUtils::concatMetaIdAndUri(subject_metaid, getModelUri());
        }
        physical_property_ = PhysicalProperty(std::move(subject_metaid), std::move(physical_property), getModelUri());
        return *this;
    }

    PhysicalForce &PhysicalForce::addSource(const std::string &physical_entity_reference, eUriType type, int multiplier) {
        sources_.push_back(
                std::move(SourceParticipant(
                        model_, multiplier, physical_entity_reference, type, getModelUri(), getLocalUri())));
        return (*this);
    }

    PhysicalForce &PhysicalForce::addSink(const std::string &physical_entity_reference, eUriType type, int multiplier) {
        sinks_.push_back(
                SinkParticipant(model_, multiplier, physical_entity_reference, type, getModelUri(), getLocalUri()));
        return (*this);
    }

    PhysicalForce::PhysicalForce(librdf_model *model)
        : PhysicalPhenomenon(model) {}

    PhysicalForce::PhysicalForce(librdf_model *model, const std::string &model_uri, const std::string &local_uri)
        : PhysicalPhenomenon(model, model_uri, local_uri) {}

    int PhysicalForce::getNumSources() {
        return sources_.size();
    }

    int PhysicalForce::getNumSinks() {
        return sinks_.size();
    }

    void PhysicalForce::free() {

        for (auto &i : sources_) {
            i.free();
        }
        for (auto &i : sinks_) {
            i.free();
        }
    }

    bool PhysicalForce::operator==(const PhysicalForce &rhs) const {
        return static_cast<const omexmeta::PhysicalPhenomenon &>(*this) ==
                       static_cast<const omexmeta::PhysicalPhenomenon &>(rhs) &&
               sources_ == rhs.sources_ &&
               sinks_ == rhs.sinks_;
    }

    bool PhysicalForce::operator!=(const PhysicalForce &rhs) const {
        return !(rhs == *this);
    }

    PhysicalForce &PhysicalForce::isVersionOf(const std::string &property) {
        physical_property_.isVersionOf(property);
        return *this;
    }


//    PhysicalForce &PhysicalForce::about(const std::string &about, eUriType type) {
//        if (OmexMetaUtils::startsWith(about, "http")) {
//            about_value_ = UriHandler::uriModifier<PhysicalForce>(*this, about, NONE);
//        } else {
//            about_value_ = UriHandler::uriModifier<PhysicalForce>(*this, about, type);
//        }
//        if (physical_property_.getIsPropertyOfValue().empty()) {
//            physical_property_.isPropertyOf(about_value_, LOCAL_URI);
//        }
//        return *this;
//    }

//
//    PhysicalForce &PhysicalForce::hasProperty(const PhysicalProperty &property) {
//        physical_property_ = property;
//        if (OmexMetaUtils::isStringEmpty<PhysicalForce>(*this, physical_property_.getIsPropertyOfValue())) {
//            // physical property takes care of generating ids
//            physical_property_.setPropertyMetaidBase(getPropertyMetaidBase());
//        }
//        return *this;
//    }
//
//    PhysicalForce &PhysicalForce::hasProperty(const std::string &property_about, eUriType about_uri_type) {
//        /*
//         * Two scenarios:
//         *  1) User wants to provide their own strings to use for the property about section.
//         *  2) the user wants the library to autogenerate a property metaid, which will be local to rdf document
//         */
//        if (property_about.empty()) {
//            // option 2
//            physical_property_ = PhysicalProperty(model_, model_uri_, local_uri_);
//            physical_property_.setPropertyMetaidBase("ForceProperty");
//
//        } else {
//            // option 1
//            physical_property_ = PhysicalProperty(model_, model_uri_, local_uri_).about(property_about, about_uri_type);
//        }
//        return *this;
//    }

    PhysicalForce &PhysicalForce::isPropertyOf(const std::string &is_property_of, eUriType type) {
        physical_property_.isPropertyOf(is_property_of, type);
        return *this;
    }

    PhysicalForce &PhysicalForce::propertyIsVersionOf(const std::string &is_version_of) {
        physical_property_.isVersionOf(is_version_of);
        return *this;
    }

    const std::string &PhysicalForce::getPropertyMetaidBase() const {
        return property_metaid_base_;
    }
    PhysicalForce &PhysicalForce::hasProperty(const PhysicalProperty &property) {
        PhysicalPhenomenon::hasProperty(property);
        return *this;
    }
    PhysicalForce &PhysicalForce::hasProperty(const std::string &property_about, eUriType about_uri_type, const std::string &is_version_of, const std::string &is_property_of, eUriType is_property_of_uri_type) {
        PhysicalPhenomenon::hasProperty(property_about, about_uri_type, is_version_of, is_property_of, is_property_of_uri_type);
        return *this;
    }
    PhysicalForce &PhysicalForce::hasProperty(const std::string &is_version_of) {
        PhysicalPhenomenon::hasProperty(is_version_of);
        return *this;
    }
    PhysicalForce &PhysicalForce::hasProperty(const std::string &property_about, eUriType about_uri_type, const std::string &is_version_of) {
        PhysicalPhenomenon::hasProperty(property_about, about_uri_type, is_version_of);
        return *this;
    }

    PhysicalForce &PhysicalForce::about(const std::string &about, eUriType type) {
        PhysicalPhenomenon::about(about, type);
        return *this;
    }

    PhysicalForce &PhysicalForce::about(const std::string &about) {
        PhysicalPhenomenon::about(about);
        return *this;
    }


}// namespace omexmeta