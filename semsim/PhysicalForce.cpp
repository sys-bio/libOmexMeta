//
// Created by Ciaran on 4/22/2020.
//

#include "PhysicalForce.h"

#include <vector>
#include "semsim/Participant.h"
#include "semsim/PhysicalPropertyResource.h"
#include "semsim/PhysicalPhenomenon.h"
#include "semsim/SemsimUtils.h"

namespace semsim {

    PhysicalForce::PhysicalForce(librdf_world *world, librdf_model *model, Subject metaid,
                                 PhysicalPropertyResource physicalProperty,
                                 Sources sources, Sinks sinks)
            : PhysicalPhenomenon(world, model, metaid, physicalProperty, PHYSICAL_PROCESS),
              sources_(sources), sinks_(sinks) {

    }

    const std::vector<SourceParticipant> &PhysicalForce::getSources() const {
        return sources_;
    }

    const std::vector<SinkParticipant> &PhysicalForce::getSinks() const {
        return sinks_;
    }

    std::string PhysicalForce::createMetaId() const {
        return generateMetaId("PhysicalForce");
    }

    Triples PhysicalForce::toTriples() const {
        std::string force_metaid = SemsimUtils::generateUniqueMetaid(world_, model_, "PhysicalForce",
                                                                     std::vector<std::string>());

        Subject force_metaid_subject(world_, RDFURINode(world_, force_metaid));

        Triples triples = physical_property_.toTriples(about.str(), force_metaid);

        for (auto &source : sources_) {
            for (auto &triple : source.toTriples(force_metaid)) {
                triples.push_back(triple);
            }
        }
        for (auto &sink : sinks_) {
            for (auto &triple : sink.toTriples(force_metaid)) {
                triples.push_back(triple);
            }
        }
        return triples;
    }

    PhysicalForce &PhysicalForce::setAbout(std::string metaid) {
        about = Subject(world_, RDFURINode(world_, metaid));
        return (*this);
    }

    PhysicalForce &PhysicalForce::setPhysicalProperty(PhysicalPropertyResource physicalProperty) {
        physical_property_ = std::move(physicalProperty);
        return (*this);
    }

    PhysicalForce &PhysicalForce::addSource(
            std::string source_metaid, std::string source_resource, double multiplier,
            std::string physical_entity_reference) {
        sources_.push_back(
                SourceParticipant(
                        world_,
                        model_,
                        std::move(source_metaid),
                        Resource(world_, RDFURINode(world_, std::move(source_resource))),
                        multiplier, std::move(physical_entity_reference)
                )
        );
        return (*this);
    }

    PhysicalForce &PhysicalForce::addSink(std::string sink_metaid, std::string sink_resource, double multiplier,
                                          std::string physical_entity_reference) {
        sinks_.push_back(
                SinkParticipant(
                        world_,
                        model_,
                        std::move(sink_metaid),
                        Resource(world_, RDFURINode(world_, std::move(sink_resource))),
                        multiplier, std::move(physical_entity_reference)
                )
        );

        return (*this);
    }

    PhysicalForce::PhysicalForce(librdf_world *world, librdf_model *model)
            : PhysicalPhenomenon(world, model) {

    }

}