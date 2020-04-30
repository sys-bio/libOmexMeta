//
// Created by Ciaran on 4/20/2020.
//

#include "Participant.h"

#include <utility>
#include "semsim/SemSim.h"


namespace semsim {


    Participant::Participant(librdf_world *world, std::string subject, PredicatePtr predicate, Resource resource,
                             double multiplier,
                             std::string physicalEntityReference)
            : world_(world), subject_(std::move(subject)),
              resource_(std::move(resource)), predicate_ptr_(predicate),
              multiplier_(multiplier), physicalEntityReference_(std::move(physicalEntityReference)) {

    }

    Triples Participant::toTriples(std::string process_metaid) const {
        if (participant_metaid_.empty()){
            throw NullPointerException("Participant::toTriples: For developers. "
                                       "participant_metaid_ variable is "
                                       "nullptr meaning the Participant class is directly"
                                       "being used - not one of its subclasses.");
        }
        Triples triples;

        // have source participant triple
        triples.emplace_back(
                world_,
                Subject(world_, RDFURINode(world_, process_metaid)),
                predicate_ptr_, //term is hasSourceParticipant etc.
                Resource(world_, RDFURINode(world_, participant_metaid_))
        );
        Subject participant_subject(world_, RDFURINode(world_, participant_metaid_));

        triples.emplace_back(
                world_,
                participant_subject,
                std::make_shared<SemSim>(SemSim(world_, "hasPhysicalEntityReference")),
                Resource(world_, RDFURINode(world_, physicalEntityReference_))
        );
        if (multiplier_ > 0.0) {
            std::ostringstream multiplier_os;
            multiplier_os << multiplier_;
            triples.emplace_back(
                    world_,
                    participant_subject,
          std::make_shared<SemSim>(SemSim(world_, "hasMultiplier")),
                    Resource(world_, RDFLiteralNode(world_, multiplier_os.str()))
            );
        }
        return triples;
    }

    PredicatePtr Participant::getPredicatePtr() {
        return predicate_ptr_;
    }

    void Participant::setPredicatePtr(PredicatePtr predicate_ptr) {
        predicate_ptr_ = std::move(predicate_ptr);
    }

    librdf_world *Participant::getWorld() const {
        return world_;
    }

    const std::string &Participant::getSubject() const {
        return subject_;
    }

    const Resource &Participant::getResource() const {
        return resource_;
    }

    double Participant::getMultiplier() const {
        return multiplier_;
    }

    const std::string &Participant::getPhysicalEntityReference() const {
        return physicalEntityReference_;
    }

    SourceParticipant::SourceParticipant(
            librdf_world *world, std::string subject, Resource resource,
            double multiplier, std::string physicalEntityReference)
            : Participant(world, subject,
                          std::make_shared<SemSim>(SemSim(world, "hasSourceParticipant")),
                          resource, multiplier, physicalEntityReference) {
            participant_metaid_ = "SourceID";
    }

    SinkParticipant::SinkParticipant(
            librdf_world *world, std::string subject, Resource resource,
            double multiplier, std::string physicalEntityReference)
            : Participant(world, subject,
                          std::make_shared<SemSim>(SemSim(world, "hasSinkParticipant")),
                          resource, multiplier, physicalEntityReference) {
            participant_metaid_ = "SinkID";
    }

    MediatorParticipant::MediatorParticipant(
            librdf_world *world, std::string subject, Resource resource,
            std::string physicalEntityReference)
            : Participant(world, subject,
                          std::make_shared<SemSim>(SemSim(world, "hasMediatorParticipant")),
                          resource, 0.0, physicalEntityReference) {
            participant_metaid_ = "MediatorID";
    }

}