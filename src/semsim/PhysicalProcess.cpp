//
// Created by Ciaran on 4/22/2020.
//

#include <vector>
#include "PhysicalProcess.h"
#include "Participant.h"
#include "PhysicalPropertyResource.h"
#include "PhysicalPhenomenon.h"
#include "SemsimUtils.h"

namespace semsim {

    PhysicalProcess::PhysicalProcess(LibrdfWorld world, LibrdfModel model, Subject metaid,
                                     PhysicalPropertyResource physicalProperty, Sources sources, Sinks sinks,
                                     Mediators mediators)
            : PhysicalPhenomenon(world, model, metaid, physicalProperty, PHYSICAL_PROCESS),
              sources_(sources), sinks_(sinks), mediators_(mediators) {

    }

    PhysicalProcess::PhysicalProcess(LibrdfWorld world, LibrdfModel model) : PhysicalPhenomenon(world, model) {

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

    Triples PhysicalProcess::toTriples() const {
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


        std::string process_metaid = SemsimUtils::generateUniqueMetaid(world_, model_, "PhysicalProcess",
                                                                       std::vector<std::string>());

        Subject process_metaid_subject(world_, RDFURINode(world_, process_metaid));

        Triples triples = physical_property_.toTriples(about.str(), process_metaid);

        for (auto &source : sources_) {
            for (auto &triple : source.toTriples(process_metaid)) {
                triples.push_back(triple);
            }
        }
        for (auto &sink : sinks_) {
            for (auto &triple : sink.toTriples(process_metaid)) {
                triples.push_back(triple);
            }
        }
        for (auto &mediator: mediators_) {
            for (auto &triple : mediator.toTriples(process_metaid)) {
                triples.push_back(triple);
            }
        }
        return triples;
    }

    PhysicalProcess &PhysicalProcess::setAbout(std::string metaid) {
        about = Subject(world_, RDFURINode(world_, metaid));
        return (*this);
    }

    PhysicalProcess &PhysicalProcess::setPhysicalProperty(PhysicalPropertyResource physicalProperty) {
        physical_property_ = std::move(physicalProperty);
        return (*this);
    }

    //todo turn this into a factory whereby user enters string of PhysicalProperty
    //  and we automatically pick out the correct OPB identifier
    PhysicalProcess &PhysicalProcess::setPhysicalProperty(const std::string &physicalProperty) {
        physical_property_ = PhysicalPropertyResource(world_, RDFURINode(world_, physicalProperty));
        return (*this);
    }

    PhysicalProcess &PhysicalProcess::addSource(std::string source_metaid, double multiplier,
                                                std::string physical_entity_reference) {
        sources_.push_back(
                SourceParticipant(
                        world_,
                        model_,
                        std::move(source_metaid),
                        multiplier,
                        std::move(physical_entity_reference)
                )
        );
        return (*this);
    }

    PhysicalProcess &PhysicalProcess::addSink(std::string sink_metaid, double multiplier,
                                              std::string physical_entity_reference) {
        sinks_.push_back(
                SinkParticipant(
                        world_,
                        model_,
                        std::move(sink_metaid),
                        multiplier, std::move(physical_entity_reference)
                )
        );

        return (*this);
    }

    PhysicalProcess &PhysicalProcess::addMediator(std::string mediator_metaid, double multiplier,
                                                  std::string physical_entity_reference) {
        mediators_.push_back(
                MediatorParticipant(
                        world_,
                        model_,
                        std::move(mediator_metaid),
                        std::move(physical_entity_reference)
                )
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


}