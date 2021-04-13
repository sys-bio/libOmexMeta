//
// Created by Ciaran on 4/22/2020.
//

#include "omexmeta/PhysicalProcess.h"

namespace omexmeta {

    PhysicalProcess::PhysicalProcess(librdf_model *model, UriHandler& uriHandler,
                                     const PhysicalProperty &physicalProperty,
                                     Sources sources, Sinks sinks, Mediators mediators)
        : PropertyBearer(model, uriHandler, physicalProperty, PHYSICAL_PROCESS),
          sources_(std::move(sources)), sinks_(std::move(sinks)), mediators_(std::move(mediators)) {
    }

    PhysicalProcess::PhysicalProcess(librdf_model *model, UriHandler& uriHandler)
        : PropertyBearer(model, uriHandler) {}

    const std::vector<SourceParticipant> &PhysicalProcess::getSources() const {
        return sources_;
    }

    const std::vector<SinkParticipant> &PhysicalProcess::getSinks() const {
        return sinks_;
    }

    const std::vector<MediatorParticipant> &PhysicalProcess::getMediators() const {
        return mediators_;
    }

    PhysicalProcess &PhysicalProcess::addSource(std::string physical_entity_reference, eUriType type, double multiplier) {
        sources_.push_back(
                std::move(SourceParticipant(model_,
                                            multiplier,
                                            std::move(physical_entity_reference), type,
                                            uriHandler_
                                            )));
        return *this;
    }

    PhysicalProcess &PhysicalProcess::addSink(std::string physical_entity_reference, eUriType type, double multiplier) {
        sinks_.push_back(
                std::move(SinkParticipant(
                        model_,
                        multiplier, std::move(physical_entity_reference),type, uriHandler_)));

        return (*this);
    }

    PhysicalProcess &PhysicalProcess::addMediator(std::string physical_entity_reference, eUriType type) {
        mediators_.push_back(
                std::move(MediatorParticipant(
                        model_,
                        std::move(physical_entity_reference),type, uriHandler_)));

        return (*this);
    }

    int PhysicalProcess::getNumSources() {
        return sources_.size();
    }

    int PhysicalProcess::getNumSinks() {
        return sinks_.size();
    }

    int PhysicalProcess::getNumMediators() {
        return mediators_.size();
    }

    void PhysicalProcess::free() {
        for (auto &i : sources_) {
            i.free();
        }
        for (auto &i : sinks_) {
            i.free();
        }
        for (auto &i : mediators_) {
            i.free();
        }
    }

    bool PhysicalProcess::operator==(const PhysicalProcess &rhs) const {
        return static_cast<const omexmeta::PropertyBearer &>(*this) ==
                       static_cast<const omexmeta::PropertyBearer &>(rhs) &&
               sources_ == rhs.sources_ &&
               sinks_ == rhs.sinks_ &&
               mediators_ == rhs.mediators_;
    }

    bool PhysicalProcess::operator!=(const PhysicalProcess &rhs) const {
        return !(rhs == *this);
    }


    Triples PhysicalProcess::toTriples() {
        // check PhysicalProcess::getAbout for being empty. Autogenerate id if true.
        if (OmexMetaUtils::isStringEmpty<PhysicalProcess>(*this, getAbout())) {
            std::string new_process_about_value = generateMetaId("Process");
            about(new_process_about_value, LOCAL_URI);
        }

        if (OmexMetaUtils::isStringEmpty<PhysicalProcess>(*this, physical_property_.getAbout())) {
            // the PhysicalProperty will autogenerate its own about metaid. We set this base to something more approprioate for a PhysicalProcess
            physical_property_.setPropertyMetaidBase("ProcessProperty");
        }

        // We also have to update the
        // isPropertyOf field of the physical_property
        physical_property_.isPropertyOf(getAbout(), LOCAL_URI);
        Triples triples = physical_property_.toTriples();

        if (!is_version_of_.empty()) {
            SingularAnnotation singularAnnotation(
                    uriHandler_,
                    LibrdfNode::fromUriString(getAbout()).get(),
                    PredicateFactory("bqbiol", "isVersionOf")->getNode(),
                    LibrdfNode::fromUriString(is_version_of_).get());
            triples.moveBack(singularAnnotation);
        }
        for (auto &source : sources_) {
            for (auto &triple : source.toTriples(getAbout(), new_metaid_exclusion_list_)) {
                triples.moveBack(triple);
            }
        }
        for (auto &sink : sinks_) {
            for (auto &triple : sink.toTriples(getAbout(), new_metaid_exclusion_list_)) {
                triples.moveBack(triple);
            }
        }
        for (auto &mediator : mediators_) {
            for (auto &triple : mediator.toTriples(getAbout(), new_metaid_exclusion_list_)) {
                triples.moveBack(triple);
            }
        }
        return triples;
    }

    PhysicalProcess &PhysicalProcess::about(const std::string &about, eUriType type) {
        PropertyBearer::about(about, type);
        return *this;
    }

    PhysicalProcess &PhysicalProcess::about(const std::string &about) {
        PropertyBearer::about(about);
        return *this;
    }

    const std::string &PhysicalProcess::getPropertyMetaidBase() const {
        return property_metaid_base_;
    }

    PhysicalProcess &PhysicalProcess::hasProperty(const PhysicalProperty &property) {
        PropertyBearer::hasProperty(property);
        return *this;
    }

    PhysicalProcess &PhysicalProcess::hasProperty(const std::string &property_about, eUriType about_uri_type, const std::string &is_version_of, const std::string &is_property_of, eUriType is_property_of_uri_type) {
        PropertyBearer::hasProperty(property_about, about_uri_type, is_version_of, is_property_of, is_property_of_uri_type);
        return *this;
    }

    PhysicalProcess &PhysicalProcess::hasProperty(const std::string &is_version_of) {
        PropertyBearer::hasProperty(is_version_of);
        return *this;
    }

    PhysicalProcess &PhysicalProcess::hasProperty(const std::string &property_about, eUriType about_uri_type, const std::string &is_version_of) {
        PropertyBearer::hasProperty(property_about, about_uri_type, is_version_of);
        return *this;
    }

    PhysicalProcess &PhysicalProcess::isVersionOf(const std::string &is_version_of, eUriType type) {
        is_version_of_ = UriHandler::uriModifier<PhysicalProcess>(*this, is_version_of, type);
        return *this;
    }

}// namespace omexmeta