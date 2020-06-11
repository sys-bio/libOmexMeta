//
// Created by Ciaran on 4/22/2020.
//

#include "PhysicalProcess.h"

#include <utility>

#include <utility>


namespace semsim {

    PhysicalProcess::PhysicalProcess(librdf_model *model, Subject metaid,
                                     PhysicalPropertyResource physicalProperty, Sources sources, Sinks sinks,
                                     Mediators mediators)
            : PhysicalPhenomenon(model, metaid, std::move(physicalProperty), PHYSICAL_PROCESS),
              sources_(std::move(sources)), sinks_(std::move(sinks)), mediators_(std::move(std::move(mediators))) {

    }

    PhysicalProcess::PhysicalProcess(librdf_model *model) : PhysicalPhenomenon(model) {

    }

    const std::vector<SourceParticipant> &PhysicalProcess::getSources() const {
        return sources_;
    }

    const std::vector<SinkParticipant> &PhysicalProcess::getSinks() const {
        return sinks_;
    }

    const std::vector<MediatorParticipant> &PhysicalProcess::getMediators() const {
        return mediators_;
    }

    Triples PhysicalProcess::toTriples() {
        if (!getAbout().isSet()) {
            throw AnnotationBuilderException(
                    "PhysicalProcess::toTriples(): Cannot create"
                    " triples because the \"about\" information is not set. "
                    "Use the setAbout() method."
            );
        }
        if (!getPhysicalProperty().isSet()) {
            throw AnnotationBuilderException(
                    "PhysicalProcess::toTriples(): Cannot create"
                    " triples because the \"physical_property\" information is not set. "
                    "Use the setPhysicalProperty() method."
            );
        }


        std::string process_metaid = SemsimUtils::generateUniqueMetaid(model_, "PhysicalProcess",
                                                                       std::vector<std::string>());

        Triples triples = physical_property_.toTriples(about.str(), process_metaid);
        // todo see note on physical entity::toTriples
        about.free();

        for (auto &source: sources_) {
            for (auto &triple: source.toTriples(process_metaid)) {
                triples.move_back(triple);
            }
        }
        for (auto &sink: sinks_) {
            for (auto &triple: sink.toTriples(process_metaid)) {
                triples.move_back(triple);
            }
        }
        for (auto &mediator: mediators_) {
            for (auto &triple: mediator.toTriples(process_metaid)) {
                triples.move_back(triple);
            }
        }
        return triples;
    }

    PhysicalProcess &PhysicalProcess::setAbout(std::string metaid) {
        about = Subject::fromRawPtr(LibrdfNode::fromUriString(metaid).get());
        return (*this);
    }

    PhysicalProcess &PhysicalProcess::setPhysicalProperty(PhysicalPropertyResource physicalProperty) {
        physical_property_ = std::move(physicalProperty);
        return (*this);
    }

//todo turn this into a factory whereby user enters string of PhysicalProperty
//  and we automatically pick out the correct OPB identifier
    PhysicalProcess &PhysicalProcess::setPhysicalProperty(const std::string &physicalProperty) {
        physical_property_ = PhysicalPropertyResource(physicalProperty);
        return (*this);
    }

    PhysicalProcess &PhysicalProcess::addSource(std::string source_metaid, double multiplier,
                                                std::string physical_entity_reference) {
        sources_.push_back(
                std::move(SourceParticipant(model_,
                                            std::move(source_metaid),
                                            multiplier,
                                            std::move(physical_entity_reference)
                          )
                )
        );
        return (*this);
    }

    PhysicalProcess &PhysicalProcess::addSink(std::string sink_metaid, double multiplier,
                                              std::string physical_entity_reference) {
        sinks_.push_back(
                std::move(SinkParticipant(
                        model_,
                        std::move(sink_metaid),
                        multiplier, std::move(physical_entity_reference)
                ))
        );

        return (*this);
    }

    PhysicalProcess &PhysicalProcess::addMediator(std::string mediator_metaid, double multiplier,
                                                  std::string physical_entity_reference) {
        mediators_.push_back(
                std::move(MediatorParticipant(
                        model_,
                        std::move(mediator_metaid),
                        std::move(physical_entity_reference)
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


}