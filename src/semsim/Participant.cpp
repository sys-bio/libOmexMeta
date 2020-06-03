//
// Created by Ciaran on 4/20/2020.
//

#include "Participant.h"

#include <utility>


namespace semsim {


    Participant::Participant(librdf_model* model, std::string subject, std::string semsim_predicate_term,
                             double multiplier,
                             std::string physicalEntityReference)
            : model_(model), subject_(std::move(subject)),
              semsim_predicate_term_(SemSim(semsim_predicate_term)),
              multiplier_(multiplier),
              physicalEntityReference_(std::move(physicalEntityReference)) {}


    Triples Participant::toTriples(const std::string &process_metaid) const {
        Triples triples;

        // have source participant triple
        triples.emplace_back(
                Subject::fromRawPtr(LibrdfNode::fromUriString(process_metaid)).getNode(),
                semsim_predicate_term_.getNode(), //term is hasSourceParticipant etc.
                Resource::fromRawPtr(LibrdfNode::fromUriString(subject_)).getNode()
        );

        triples.emplace_back(
                Subject::fromRawPtr(LibrdfNode::fromUriString(subject_)).getNode(),
                SemSim("hasPhysicalEntityReference").getNode(),
                Resource::fromRawPtr(LibrdfNode::fromUriString(physicalEntityReference_)).getNode()
        );
        if (multiplier_ > 0.0) {
            std::ostringstream multiplier_os;
            multiplier_os << multiplier_;
            triples.emplace_back(
                    Subject::fromRawPtr(LibrdfNode::fromUriString(subject_)).getNode(),
                    SemSim("hasMultiplier").getNode(),
                    Resource::fromRawPtr(LibrdfNode::fromLiteral(
                            multiplier_os.str(),
                            "http://www.w3.org/2001/XMLSchema#double")).getNode()
            );
        }
        return triples;
    }

    SemSim Participant::getPredicate() {
        return semsim_predicate_term_;
    }

    void Participant::setPredicate(std::string semsim_predicate_term) {
        semsim_predicate_term_ = SemSim(semsim_predicate_term);
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

    void Participant::free() {
        if (semsim_predicate_term_.getNode()) {
            semsim_predicate_term_.freeNode();
            semsim_predicate_term_.setNode(nullptr);
        }

    }

//    Participant::~Participant() {
//        if (predicate_ptr_->getNode()) {
//            LibrdfNode::free(predicate_ptr_->getNode());
//            predicate_ptr_ = nullptr;
//        }
//    }

    SourceParticipant::SourceParticipant(librdf_model* model, std::string subject,
                                         double multiplier, std::string physicalEntityReference)
            : Participant(model, std::move(subject), "hasSourceParticipant",
                          multiplier, std::move(physicalEntityReference)) {}

    SinkParticipant::SinkParticipant(librdf_model* model, std::string subject, double multiplier,
                                     std::string physicalEntityReference)
            : Participant(model, std::move(subject),
                          "hasSinkParticipant",
                          multiplier,
                          std::move(physicalEntityReference)) {}

    MediatorParticipant::MediatorParticipant(
            librdf_model* model, std::string subject,
            std::string physicalEntityReference)
            : Participant(model, std::move(subject),
                          "hasMediatorParticipant",
                          0.0, std::move(physicalEntityReference)) {
    }

}