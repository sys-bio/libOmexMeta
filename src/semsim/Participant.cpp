//
// Created by Ciaran on 4/20/2020.
//

#include "Participant.h"

#include <utility>


namespace semsim {


    Participant::Participant(librdf_model *model, std::string subject, std::string semsim_predicate_term,
                             double multiplier,
                             std::string physicalEntityReference)
            : model_(model), subject_(std::move(subject)),
              semsim_predicate_term_(SemSim(semsim_predicate_term)),
              multiplier_(multiplier),
              physicalEntityReference_(std::move(physicalEntityReference)) {}


    Triples Participant::toTriples(const std::string &process_metaid) const {
        Triples triples;

        // have source participant triple
        librdf_node *sub1 = LibrdfNode::fromUriString(process_metaid).get();
        if (sub1 == nullptr) {
            throw NullPointerException("NullPointerException: Participant::toTriples: sub1");
        }

        librdf_node *pred1 = semsim_predicate_term_.getNode(); //term is hasSourceParticipant etc.
        if (pred1 == nullptr) {
            throw NullPointerException("NullPointerException: Participant::toTriples: pred1");
        }

        librdf_node *res1 = LibrdfNode::fromUriString(subject_).get();
        if (res1 == nullptr) {
            throw NullPointerException("NullPointerException: Participant::toTriples: res1");
        }
        triples.emplace_back(sub1, pred1, res1);

        librdf_node *sub2 = LibrdfNode::fromUriString(subject_).get();

        if (sub2 == nullptr) {
            throw NullPointerException("NullPointerException: Participant::toTriples: sub2");
        }

        librdf_node *pred2 = SemSim("hasPhysicalEntityReference").getNode();
        if (pred2 == nullptr) {
            throw NullPointerException("NullPointerException: Participant::toTriples: pred2");
        }

        librdf_node *res2 = LibrdfNode::fromUriString(physicalEntityReference_).get();
        if (res2 == nullptr) {
            throw NullPointerException("NullPointerException: Participant::toTriples: res2");
        }
        triples.emplace_back(sub2, pred2, res2);

        if (multiplier_ > 0.0) {
            std::ostringstream multiplier_os;
            multiplier_os << multiplier_;

            librdf_node *sub3 = LibrdfNode::fromUriString(subject_).get();
            if (sub3 == nullptr) {
                throw NullPointerException("NullPointerException: Participant::toTriples: sub3");
            }

            librdf_node *pred3 = SemSim("hasMultiplier").getNode();
            if (pred3 == nullptr) {
                throw NullPointerException("NullPointerException: Participant::toTriples: pred3");
            }

            librdf_node *res3 = LibrdfNode::fromLiteral(
                    multiplier_os.str(),
                    "http://www.w3.org/2001/XMLSchema#double").get();
            if (res3 == nullptr) {
                throw NullPointerException("NullPointerException: Participant::toTriples: res3");
            }

            triples.emplace_back(sub3, pred3, res3);
        }
        return triples;
    }

    SemSim Participant::getPredicate() {
        return semsim_predicate_term_;
    }

    void Participant::setPredicate(const std::string &semsim_predicate_term) {
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

    bool Participant::operator==(const Participant &rhs) const {
        return model_ == rhs.model_ &&
               subject_ == rhs.subject_ &&
               semsim_predicate_term_ == rhs.semsim_predicate_term_ &&
               multiplier_ == rhs.multiplier_ &&
               physicalEntityReference_ == rhs.physicalEntityReference_;
    }

    bool Participant::operator!=(const Participant &rhs) const {
        return !(rhs == *this);
    }

//    Participant::~Participant() {
//        if (predicate_ptr_->getNode()) {
//            LibrdfNode::free(predicate_ptr_->getNode());
//            predicate_ptr_ = nullptr;
//        }
//    }

    SourceParticipant::SourceParticipant(librdf_model *model, std::string subject,
                                         double multiplier, std::string physicalEntityReference)
            : Participant(model, std::move(subject), "hasSourceParticipant",
                          multiplier, std::move(physicalEntityReference)) {}

    SinkParticipant::SinkParticipant(librdf_model *model, std::string subject, double multiplier,
                                     std::string physicalEntityReference)
            : Participant(model, std::move(subject),
                          "hasSinkParticipant",
                          multiplier,
                          std::move(physicalEntityReference)) {}

    MediatorParticipant::MediatorParticipant(
            librdf_model *model, std::string subject,
            std::string physicalEntityReference)
            : Participant(model, std::move(subject),
                          "hasMediatorParticipant",
                          0.0, std::move(physicalEntityReference)) {
    }

}