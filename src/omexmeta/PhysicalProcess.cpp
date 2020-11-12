//
// Created by Ciaran on 4/22/2020.
//

#include "omexmeta/PhysicalProcess.h"

namespace omexmeta {

    PhysicalProcess::PhysicalProcess(librdf_model *model, std::string model_uri,std::string local_uri,
                                     const PhysicalProperty &physicalProperty,
                                     Sources sources, Sinks sinks, Mediators mediators)
            : PhysicalPhenomenon(model, model_uri, local_uri, physicalProperty, PHYSICAL_PROCESS),
              sources_(std::move(sources)), sinks_(std::move(sinks)), mediators_(std::move(mediators)) {
    }

    PhysicalProcess::PhysicalProcess(librdf_model *model) : PhysicalPhenomenon(model) {}

    PhysicalProcess::PhysicalProcess(librdf_model *model, std::string model_uri, std::string local_uri)
        : PhysicalPhenomenon(model, model_uri, local_uri) {}

    const std::vector<SourceParticipant> &PhysicalProcess::getSources() const {
        return sources_;
    }

    const std::vector<SinkParticipant> &PhysicalProcess::getSinks() const {
        return sinks_;
    }

    const std::vector<MediatorParticipant> &PhysicalProcess::getMediators() const {
        return mediators_;
    }

    PhysicalProcess &PhysicalProcess::setPhysicalProperty(PhysicalProperty physicalProperty) {
        physical_property_ = std::move(physicalProperty);
        return (*this);
    }

//todo turn this into a factory whereby user enters string of PhysicalProperty
//  and we automatically pick out the correct OPB identifier
    PhysicalProcess &
    PhysicalProcess::setPhysicalProperty(std::string subject_metaid, const std::string &physicalProperty) {
        subject_metaid = OmexMetaUtils::concatMetaIdAndUri(subject_metaid, getModelUri());
        physical_property_ = PhysicalProperty(subject_metaid, physicalProperty, getModelUri());
        return (*this);
    }

    PhysicalProcess &PhysicalProcess::addSource(int multiplier, std::string physical_entity_reference) {
        sources_.push_back(
                std::move(SourceParticipant(model_,
                                            multiplier,
                                            std::move(physical_entity_reference),
                                            getModelUri(), getLocalUri()
                          )
                )
        );
        return (*this);
    }

    PhysicalProcess &PhysicalProcess::addSink(int multiplier, std::string physical_entity_reference) {
        sinks_.push_back(
                std::move(SinkParticipant(
                        model_,
                        multiplier, std::move(physical_entity_reference),
                        getModelUri(), getLocalUri()
                ))
        );

        return (*this);
    }

    PhysicalProcess &PhysicalProcess::addMediator(std::string physical_entity_reference) {
        mediators_.push_back(
                std::move(MediatorParticipant(
                        model_,
                        std::move(physical_entity_reference),
                        getModelUri(), getLocalUri()
                ))
        );

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
        return static_cast<const omexmeta::PhysicalPhenomenon &>(*this) ==
               static_cast<const omexmeta::PhysicalPhenomenon &>(rhs) &&
               sources_ == rhs.sources_ &&
               sinks_ == rhs.sinks_ &&
               mediators_ == rhs.mediators_;
    }

    bool PhysicalProcess::operator!=(const PhysicalProcess &rhs) const {
        return !(rhs == *this);
    }


    Triples PhysicalProcess::toTriples() {
        if (getAbout().empty() || getAbout() == model_uri_ + "#") {
            std::string new_about = generateMetaId("Process");
            about(OmexMetaUtils::concatMetaIdAndUri(new_about, local_uri_));
        }
        if (physical_process_property_id_.empty()) {
            physical_process_property_id_ = generateMetaId("ProcessProperty");
            physical_property_.about(physical_process_property_id_, LOCAL_URI);
        }


        Triples triples = physical_property_.toTriples();

        if (!is_version_of_.empty()) {
            SingularAnnotation singularAnnotation(
                    LibrdfNode::fromUriString(getAbout()).get(),
                    PredicateFactory("bqbiol", "isVersionOf")->getNode(),
                    LibrdfNode::fromUriString(is_version_of_).get());
            triples.move_back(singularAnnotation);
        }
        for (auto &source: sources_) {
            for (auto &triple: source.toTriples(getAbout(), new_metaid_exclusion_list_)) {
                triples.move_back(triple);
            }
        }
        for (auto &sink: sinks_) {
            for (auto &triple: sink.toTriples(getAbout(), new_metaid_exclusion_list_)) {
                triples.move_back(triple);
            }
        }
        for (auto &mediator: mediators_) {
            for (auto &triple: mediator.toTriples(getAbout(), new_metaid_exclusion_list_)) {
                triples.move_back(triple);
            }
        }
        return triples;
    }


    PhysicalProcess &PhysicalProcess::isVersionOf(const std::string &property) {
        physical_property_.isVersionOf(property);
        return *this;
    }

    PhysicalProcess &PhysicalProcess::about(const std::string &about, eUriType type) {
        if (!OmexMetaUtils::startsWith(about, "http"))
            physical_property_.about(OmexMetaUtils::concatMetaIdAndUri(about, model_uri_));
        else
            physical_property_.about(about, type);
        return *this;
    }

    PhysicalProcess &PhysicalProcess::variableMetaId(const std::string& metaid) {
        physical_process_property_id_ = metaid;
        return *this;
    }


}