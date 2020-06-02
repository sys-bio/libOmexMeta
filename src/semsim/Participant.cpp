//
// Created by Ciaran on 4/20/2020.
//

#include "Participant.h"

#include <utility>


namespace semsim {


    Participant::Participant(const LibrdfModel &model, std::string subject, PredicatePtr predicate, double multiplier,
                             std::string physicalEntityReference)
            : model_(model), subject_(std::move(subject)),
              predicate_ptr_(std::move(predicate)), multiplier_(multiplier),
              physicalEntityReference_(std::move(physicalEntityReference)) {}

    Triples Participant::toTriples(const std::string &process_metaid) const {
        Triples triples;

        // have source participant triple
        triples.emplace_back(
                Subject::fromRawPtr(LibrdfNode::fromUriString(process_metaid)).getNode(),
                predicate_ptr_->getNode(), //term is hasSourceParticipant etc.
                Resource::fromRawPtr(LibrdfNode::fromUriString(subject_)).getNode()
        );
        Subject participant_subject = Subject::fromRawPtr(LibrdfNode::fromUriString(subject_));

        triples.emplace_back(
                participant_subject.getNode(),
                std::make_shared<SemSim>(SemSim("hasPhysicalEntityReference"))->getNode(),
                Resource::fromRawPtr(LibrdfNode::fromUriString(physicalEntityReference_)).getNode()
        );
        if (multiplier_ > 0.0) {
            std::ostringstream multiplier_os;
            multiplier_os << multiplier_;
            triples.emplace_back(
                    participant_subject.getNode(),
                    std::make_shared<SemSim>(SemSim("hasMultiplier"))->getNode(),
                    Resource::fromRawPtr(LibrdfNode::fromLiteral(
                            multiplier_os.str(),
                            "http://www.w3.org/2001/XMLSchema#double")).getNode()
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

//    Participant::~Participant() {
//        if (predicate_ptr_->getNode()) {
//            LibrdfNode::freeNode(predicate_ptr_->getNode());
//            predicate_ptr_ = nullptr;
//        }
//    }

    SourceParticipant::SourceParticipant(const LibrdfModel &model, std::string subject,
                                         double multiplier, std::string physicalEntityReference)
            : Participant(model, std::move(subject),
                          std::make_shared<SemSim>(SemSim("hasSourceParticipant")), multiplier,
                          std::move(physicalEntityReference)) {}

    SinkParticipant::SinkParticipant(const LibrdfModel &model, std::string subject, double multiplier,
                                     std::string physicalEntityReference)
            : Participant(model, std::move(subject),
                          std::make_shared<SemSim>(SemSim("hasSinkParticipant")), multiplier,
                          std::move(physicalEntityReference)) {}

    MediatorParticipant::MediatorParticipant(
            const LibrdfModel &model, std::string subject,
            std::string physicalEntityReference)
            : Participant(model, std::move(subject),
                          std::make_shared<SemSim>(SemSim("hasMediatorParticipant")),
                          0.0, std::move(physicalEntityReference)) {
    }

}