//
// Created by Ciaran on 4/22/2020.
//

#include <vector>
#include "semsim/PhysicalProcess.h"
#include "semsim/Participant.h"
#include "semsim/PhysicalPropertyResource.h"
#include "semsim/PhysicalPhenomenon.h"
#include "SemsimUtils.h"

namespace semsim {

    PhysicalProcess::PhysicalProcess(librdf_world *world, librdf_model *model, Subject metaid,
                                     PhysicalPropertyResource physicalProperty, Sources sources, Sinks sinks,
                                     Mediators mediators)
            : PhysicalPhenomenon(world, model, metaid, physicalProperty, PHYSICAL_PROCESS),
              sources_(sources), sinks_(sinks), mediators_(mediators) {

    }

    PhysicalProcess::PhysicalProcess(librdf_world *world, librdf_model *model) : PhysicalPhenomenon(world, model) {

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


        std::string process_metaid = SemsimUtils::generateUniqueMetaid(world_, model_, "PhysicalProcess", std::vector<std::string>());

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

    PhysicalProcess &PhysicalProcess::addSource(
            std::string source_metaid, std::string source_resource, double multiplier,
            std::string physical_entity_reference) {
        sources_.push_back(
                SourceParticipant(
                        world_,
                        std::move(source_metaid),
                        Resource(world_, RDFURINode(world_, std::move(source_resource))),
                        multiplier, std::move(physical_entity_reference)
                )
        );
        return (*this);
    }

    PhysicalProcess &PhysicalProcess::addSink(std::string sink_metaid, std::string sink_resource, double multiplier,
                                              std::string physical_entity_reference) {
        sinks_.push_back(
                SinkParticipant(
                        world_,
                        std::move(sink_metaid),
                        Resource(world_, RDFURINode(world_, std::move(sink_resource))),
                        multiplier, std::move(physical_entity_reference)
                )
        );

        return (*this);
    }

    PhysicalProcess &PhysicalProcess::addMediator(
            std::string mediator_metaid, std::string mediator_resource, double multiplier,
            std::string physical_entity_reference) {
        mediators_.push_back(
                MediatorParticipant(
                        world_,
                        std::move(mediator_metaid),
                        Resource(world_, RDFURINode(world_, std::move(mediator_resource))),
                        std::move(physical_entity_reference)
                )
        );

        return (*this);
    }


}