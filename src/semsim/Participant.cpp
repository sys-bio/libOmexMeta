//
// Created by Ciaran on 4/20/2020.
//

#include "Participant.h"



/*
 * todo work on participant classes, are they doing what they should?
 *  Does the resource argument need to be there? ? ?
 */
namespace semsim {


    Participant::Participant(LibrdfWorld world, LibrdfModel model, std::string subject, PredicatePtr predicate,
                             double multiplier, std::string physicalEntityReference)
            : world_(world), subject_(std::move(subject)),
              predicate_ptr_(predicate),
              multiplier_(multiplier), physicalEntityReference_(std::move(physicalEntityReference)) {
    }

    Triples Participant::toTriples(std::string process_metaid) const {
        Triples triples;

        // have source participant triple
        triples.emplace_back(
                world_,
                Subject(world_, RDFURINode(world_, process_metaid)),
                predicate_ptr_, //term is hasSourceParticipant etc.
                Resource(world_, RDFURINode(world_, subject_))
        );
        Subject participant_subject(world_, RDFURINode(world_, subject_));

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
                    Resource(world_, RDFLiteralNode(world_, multiplier_os.str(),
                            "http://www.w3.org/2001/XMLSchema#double"))
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

    LibrdfWorld Participant::getWorld() const {
        if (!world_) {
            throw NullPointerException("Participant::getWorld(): world_");
        }
        return world_;
    }

    const std::string &Participant::getSubject() const {
        return subject_;
    }

    double Participant::getMultiplier() const {
        return multiplier_;
    }

    const std::string &Participant::getPhysicalEntityReference() const {
        return physicalEntityReference_;
    }

    SourceParticipant::SourceParticipant(LibrdfWorld world, LibrdfModel model, std::string subject,
                                         double multiplier,
                                         std::string physicalEntityReference)
            : Participant(world, model, subject,
                          std::make_shared<SemSim>(SemSim(world, "hasSourceParticipant")), multiplier,
                          physicalEntityReference) {
    }

    SinkParticipant::SinkParticipant(LibrdfWorld world, LibrdfModel model, std::string subject, double multiplier,
                                     std::string physicalEntityReference)
            : Participant(world, model, subject,
                          std::make_shared<SemSim>(SemSim(world, "hasSinkParticipant")), multiplier,
                          physicalEntityReference) {
    }

    MediatorParticipant::MediatorParticipant(LibrdfWorld world, LibrdfModel model, std::string subject,
                                             std::string physicalEntityReference)
            : Participant(world, model, subject,
                          std::make_shared<SemSim>(SemSim(world, "hasMediatorParticipant")), 0.0,
                          physicalEntityReference) {
    }

}