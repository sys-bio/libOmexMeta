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
        std::string process_metaid = SemsimUtils::generateUniqueMetaid(world_, model_, "PhysicalProcess");

        Subject process_metaid_subject(world_, RDFURINode(world_, process_metaid));

        Triples triples = physical_property_.toTriples(subject_metaid_.str(), process_metaid);

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

    Triples toTriples();


}