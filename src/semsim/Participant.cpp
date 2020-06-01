//
// Created by Ciaran on 4/20/2020.
//

#include "Participant.h"


namespace semsim {


    Participant::Participant(const LibrdfModel& model, std::string subject, PredicatePtr predicate, double multiplier,
            std::string physicalEntityReference)
    : model_(model), subject_(std::move(subject)),
    predicate_ptr_(predicate), multiplier_(multiplier),
    physicalEntityReference_(std::move(physicalEntityReference)) {}

    Triples Participant::toTriples(std::string process_metaid) const {
        Triples triples;

        // have source participant triple
        triples.emplace_back(
                Subject::fromRawPtr(LibrdfNode::fromUriString(process_metaid)),
                predicate_ptr_, //term is hasSourceParticipant etc.
                Resource::fromRawPtr(LibrdfNode::fromUriString(subject_))
        );
        Subject participant_subject = Subject::fromRawPtr(LibrdfNode::fromUriString(subject_));

        triples.emplace_back(
                participant_subject,
                std::make_shared<SemSim>(SemSim("hasPhysicalEntityReference")),
                Resource::fromRawPtr(LibrdfNode::fromUriString(physicalEntityReference_))
        );
        if (multiplier_ > 0.0) {
            std::ostringstream multiplier_os;
            multiplier_os << multiplier_;
            triples.emplace_back(
                    participant_subject,
                    std::make_shared<SemSim>(SemSim("hasMultiplier")),
                    Resource::fromRawPtr(LibrdfNode::fromLiteral(
                            multiplier_os.str(),
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


    const std::string &Participant::getSubject() const {
        return subject_;
    }

    double Participant::getMultiplier() const {
        return multiplier_;
    }

    const std::string &Participant::getPhysicalEntityReference() const {
        return physicalEntityReference_;
    }

    SourceParticipant::SourceParticipant(const LibrdfModel &model, std::string subject,
                                         double multiplier, std::string physicalEntityReference)
            : Participant(model, subject,
                          std::make_shared<SemSim>(SemSim("hasSourceParticipant")), multiplier,
                          physicalEntityReference) {}

    SinkParticipant::SinkParticipant(const LibrdfModel &model, std::string subject, double multiplier,
                                     std::string physicalEntityReference)
            : Participant(model, subject,
                          std::make_shared<SemSim>(SemSim("hasSinkParticipant")), multiplier,
                          physicalEntityReference) {}

    MediatorParticipant::MediatorParticipant(
            const LibrdfModel &model, std::string subject,
            std::string physicalEntityReference)
            : Participant(model, subject,
                          std::make_shared<SemSim>(SemSim("hasMediatorParticipant")),
                          0.0, physicalEntityReference) {
    }

}