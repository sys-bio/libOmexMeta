//
// Created by Ciaran on 4/22/2020.
//

#include "PhysicalForce.h"

#include <vector>
#include "semsim/Participant.h"
#include "semsim/PhysicalPropertyResource.h"
#include "semsim/PhysicalPhenomenon.h"

namespace semsim {

    PhysicalForce::PhysicalForce(librdf_world *world,librdf_model *model,  Subject metaid, PhysicalPropertyResource physicalProperty,
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
        return triples;
    }

    Triples toTriples();


}