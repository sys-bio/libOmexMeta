//
// Created by Ciaran on 4/22/2020.
//

#include <vector>
#include "semsim/PhysicalProcess.h"
#include "semsim/Participant.h"
#include "semsim/PhysicalPropertyResource.h"
#include "semsim/PhysicalPhenomenon.h"

namespace semsim {

    PhysicalProcess::PhysicalProcess(librdf_world *world, librdf_model *model, Subject metaid,
                                     PhysicalPropertyResource physicalProperty, Sources sources, Sinks sinks,
                                     Mediators mediators)
            : PhysicalPhenomenon(world, model, metaid, physicalProperty, PHYSICAL_PROCESS),
              sources_(sources), sinks_(sinks), mediators_(mediators) {

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

    std::string PhysicalProcess::createMetaId() const {
        return generateMetaId("PhysicalProcess");
    }

    Triples PhysicalProcess::toTriples() const {
        Triples triples = {
                physical_property_.toIsVersionOfTriple(createMetaId())
        };

        for (auto &source : sources_) {
            for (auto &triple : source.toTriples()) {
                triples.push_back(triple);
            }
        }
        for (auto &sink : sinks_) {
            for (auto &triple : sink.toTriples()) {
                triples.push_back(triple);
            }
        }
        for (auto &mediator: mediators_) {
            for (auto &triple : mediator.toTriples()) {
                triples.push_back(triple);
            }
        }
        return triples;
    }

    Triples toTriples();


}