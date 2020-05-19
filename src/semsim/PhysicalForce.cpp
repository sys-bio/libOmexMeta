//
// Created by Ciaran on 4/22/2020.
//

#include "PhysicalForce.h"


namespace semsim {

    PhysicalForce::PhysicalForce(LibrdfWorld world, LibrdfModel model, Subject metaid,
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

    PhysicalForce &PhysicalForce::setPhysicalProperty(const std::string &physicalProperty) {
        physical_property_ = PhysicalPropertyResource(world_, RDFURINode(world_, physicalProperty));
        return (*this);
    }

    PhysicalForce &PhysicalForce::addSource(
            std::string source_metaid, double multiplier,
            std::string physical_entity_reference) {
        sources_.push_back(
                SourceParticipant(
                        world_,
                        model_,
                        std::move(source_metaid),
                        multiplier, std::move(physical_entity_reference)
                )
        );
        return (*this);
    }

    PhysicalForce &PhysicalForce::addSink(std::string sink_metaid, double multiplier,
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

    PhysicalForce::PhysicalForce(LibrdfWorld world, LibrdfModel model)
            : PhysicalPhenomenon(world, model) {

    }

    int PhysicalForce::getNumSources() {
        return sources_.size();
    }

    int PhysicalForce::getNumSinks() {
        return sinks_.size();
    }

}