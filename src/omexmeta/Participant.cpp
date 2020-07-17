//
// Created by Ciaran on 4/20/2020.
//

#include "Participant.h"

#include <utility>


namespace omexmeta {


    Participant::Participant(librdf_model *model, std::string base_metaid,
                             std::string local_uri, std::string semsim_predicate_term,
                             double multiplier,
                             std::string physicalEntityReference)

            : model_(model),
              // add the local uri prefix to the metaid here. This will also
              // work for Participant subclasses.
//              metaid_template_str_(OmexMetaUtils::addLocalPrefixToMetaid(std::move(base_metaid), local_uri)),
              metaid_template_str_(std::move(base_metaid)),
              local_uri_(std::move(local_uri)),
              semsim_predicate_term_(std::move(semsim_predicate_term)),
              multiplier_(multiplier),
              physicalEntityReference_(std::move(physicalEntityReference)) {}

    std::string Participant::createMetaid(const std::string &base) const {
        return OmexMetaUtils::generateUniqueMetaid(model_, base);
    }

    Triples Participant::toTriples(std::string process_metaid) {
        if (unique_participant_metaid_.empty()) {
            unique_participant_metaid_ = OmexMetaUtils::generateUniqueMetaid(model_, metaid_template_str_);
        }
        process_metaid = OmexMetaUtils::addLocalPrefixToMetaid(process_metaid, local_uri_);
        unique_participant_metaid_ = OmexMetaUtils::addLocalPrefixToMetaid(unique_participant_metaid_, local_uri_);

        // todo preallocate num triples needed
        Triples triples;

        // have source participant triple
        librdf_node *sub1 = LibrdfNode::fromUriString(process_metaid).get();
        if (sub1 == nullptr) {
            throw NullPointerException("NullPointerException: Participant::toTriples: sub1");
        }

        librdf_node *pred1 = SemSim(semsim_predicate_term_).getNode(); //term is hasSourceParticipant etc.
        if (pred1 == nullptr) {
            throw NullPointerException("NullPointerException: Participant::toTriples: pred1");
        }

        librdf_node *res1 = LibrdfNode::fromUriString(unique_participant_metaid_).get();
        if (res1 == nullptr) {
            throw NullPointerException("NullPointerException: Participant::toTriples: res1");
        }
        triples.emplace_back(sub1, pred1, res1);

        librdf_node *sub2 = LibrdfNode::fromUriString(unique_participant_metaid_).get();

        if (sub2 == nullptr) {
            throw NullPointerException("NullPointerException: Participant::toTriples: sub2");
        }

        librdf_node *pred2 = SemSim("hasPhysicalEntityReference").getNode();
        if (pred2 == nullptr) {
            throw NullPointerException("NullPointerException: Participant::toTriples: pred2");
        }

        librdf_node *res2 = LibrdfNode::fromUriString(
                OmexMetaUtils::addLocalPrefixToMetaid(physicalEntityReference_, getLocalUri())
        ).get();
        if (res2 == nullptr) {
            throw NullPointerException("NullPointerException: Participant::toTriples: res2");
        }
        triples.emplace_back(sub2, pred2, res2);

        if (multiplier_ != 0.0) {
            std::ostringstream multiplier_os;
            multiplier_os << multiplier_;

            librdf_node *sub3 = LibrdfNode::fromUriString(unique_participant_metaid_).get();
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

    std::basic_string<char> Participant::getPredicate() {
        return semsim_predicate_term_;
    }

    void Participant::setPredicate(const std::string &semsim_predicate_term) {
        semsim_predicate_term_ = semsim_predicate_term;
    }

    const std::string &Participant::getSubject() const {
        return metaid_template_str_;
    }

    double Participant::getMultiplier() const {
        return multiplier_;
    }

    const std::string &Participant::getPhysicalEntityReference() const {
        return physicalEntityReference_;
    }

    void Participant::free() {
//        if (semsim_predicate_term_.getNode()) {
//            semsim_predicate_term_.freeNode();
//            semsim_predicate_term_.setNode(nullptr);
//        }

    }

    bool Participant::operator==(const Participant &rhs) const {
        return metaid_template_str_ == rhs.metaid_template_str_ &&
               semsim_predicate_term_ == rhs.semsim_predicate_term_ &&
               multiplier_ == rhs.multiplier_ &&
               physicalEntityReference_ == rhs.physicalEntityReference_ &&
               unique_participant_metaid_ == rhs.unique_participant_metaid_;
    }

    bool Participant::operator!=(const Participant &rhs) const {
        return !(rhs == *this);
    }

    void Participant::setMultiplier(double multiplier) {
        multiplier_ = multiplier;
    }

    void Participant::setPhysicalEntityReference(const std::string &physicalEntityReference) {
        physicalEntityReference_ = physicalEntityReference;
    }

    const std::string &Participant::getUniqueParticipantMetaid() const {
        return unique_participant_metaid_;
    }

    void Participant::setUniqueParticipantMetaid(const std::string &uniqueParticipantMetaid) {
        unique_participant_metaid_ = uniqueParticipantMetaid;
    }

    const std::string &Participant::getLocalUri() const {
        return local_uri_;
    }

    void Participant::setLocalUri(const std::string &localUri) {
        local_uri_ = localUri;
    }

    SourceParticipant::SourceParticipant(librdf_model *model, double multiplier, std::string physicalEntityReference,
                                         std::string local_uri)
            : Participant(model, "SourceParticipant", std::move(local_uri), "hasSourceParticipant",
                          multiplier, std::move(physicalEntityReference)) {}

    SinkParticipant::SinkParticipant(librdf_model *model, double multiplier,
                                     std::string physicalEntityReference, std::string local_uri)
            : Participant(model, "SinkParticipant", std::move(local_uri),
                          "hasSinkParticipant",
                          multiplier,
                          std::move(physicalEntityReference)) {}

    MediatorParticipant::MediatorParticipant(
            librdf_model *model, std::string physicalEntityReference, std::string local_uri)
            : Participant(model, "MediatorParticipant", std::move(local_uri),
                          "hasMediatorParticipant",
                          0.0, std::move(physicalEntityReference)) {
    }

}