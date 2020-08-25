//
// Created by Ciaran on 4/20/2020.
//

#include "Participant.h"

#include <utility>


namespace omexmeta {


    Participant::Participant(librdf_model *model, std::string base_metaid,
                             const std::string &model_uri, const std::string &local_uri,
                             std::string semsim_predicate_term,
                             double multiplier,
                             std::string physicalEntityReference)
            : model_(model),
              metaid_template_str_(std::move(base_metaid)),
              model_uri_(model_uri),
              local_uri_(local_uri),
              semsim_predicate_term_(std::move(semsim_predicate_term)),
              multiplier_(multiplier),
              physicalEntityReference_(std::move(physicalEntityReference)){}

    void Participant::free() {}; // this was needed but no longer, because Triple objects do the cleaning

    std::string Participant::createMetaid(const std::string &base, std::vector<std::string>& metaid_exclusions) const {
        return OmexMetaUtils::generateUniqueMetaid(model_, base, metaid_exclusions);
    }

    Triples Participant::toTriples(const std::string &subject_metaid, std::vector<std::string>& metaid_exclusions) {

        for (auto &it: metaid_exclusions) {
            
        }

        if (local_participant_metaid_.empty()) {
            local_participant_metaid_ = OmexMetaUtils::generateUniqueMetaid(
                    model_, metaid_template_str_, metaid_exclusions);
        }
        if (!OmexMetaUtils::startsWith(subject_metaid, "http")) {
            throw std::invalid_argument("std::invalid_argument: Participant::toTriples(): "
                                        "Expected a full uri (i.e. starts with http) for subject_metaid argument "
                                        "but received \"" + subject_metaid + "\" instead");
        }
        
        
        
//        

        /*
         * Since Triple's are added to the model as a unit, we need a way of keeping track of which metaids
         * have been used in order to ensure unique metaid's when we have more than one Sink/Source/Mediate Participant.
         * For this we add the generated metaid to a vector. Note, we do this before concat with local uri because of the way
         * local_uri's were added after the original design was in place. Future developers might want to look at this.
         */

        metaid_exclusions.push_back(local_participant_metaid_);
        
        for (auto &it: metaid_exclusions) {
            
        }
        


        local_participant_metaid_ = OmexMetaUtils::concatMetaIdAndUri(local_participant_metaid_, getLocalUri());
        

        Triples triples;
        // have source participant triple
        librdf_node *sub1 = LibrdfNode::fromUriString(subject_metaid).get();
        if (sub1 == nullptr) {
            throw NullPointerException("NullPointerException: Participant::toTriples: sub1");
        }

        librdf_node *pred1 = SemSim(semsim_predicate_term_).getNode(); //term is hasSourceParticipant etc.
        if (pred1 == nullptr) {
            throw NullPointerException("NullPointerException: Participant::toTriples: pred1");
        }

        librdf_node *res1 = LibrdfNode::fromUriString(local_participant_metaid_).get();
        if (res1 == nullptr) {
            throw NullPointerException("NullPointerException: Participant::toTriples: res1");
        }
        triples.emplace_back(sub1, pred1, res1);
        librdf_node *sub2 = LibrdfNode::fromUriString(local_participant_metaid_).get();
        if (sub2 == nullptr) {
            throw NullPointerException("NullPointerException: Participant::toTriples: sub2");
        }
        librdf_node *pred2 = SemSim("hasPhysicalEntityReference").getNode();
        if (pred2 == nullptr) {
            throw NullPointerException("NullPointerException: Participant::toTriples: pred2");
        }
        librdf_node *res2 = LibrdfNode::fromUriString(
                OmexMetaUtils::concatMetaIdAndUri(physicalEntityReference_, getModelUri())
        ).get();
        if (res2 == nullptr) {
            throw NullPointerException("NullPointerException: Participant::toTriples: res2");
        }
        triples.emplace_back(sub2, pred2, res2);
        if (multiplier_ != 0.0) {
            std::ostringstream multiplier_os;
            multiplier_os << multiplier_;
            librdf_node *sub3 = LibrdfNode::fromUriString(local_participant_metaid_).get();
            if (sub3 == nullptr) {
                throw NullPointerException("NullPointerException: Participant::toTriples: sub3");
            }
            librdf_node *pred3 = SemSim("hasMultiplier").getNode();
            if (pred3 == nullptr) {
                throw NullPointerException("NullPointerException: Participant::toTriples: pred3");
            }
            librdf_node *res3 = LibrdfNode::fromLiteral(
                    multiplier_os.str(),
                    "double").get();
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

    bool Participant::operator==(const Participant &rhs) const {
        return metaid_template_str_ == rhs.metaid_template_str_ &&
               semsim_predicate_term_ == rhs.semsim_predicate_term_ &&
               multiplier_ == rhs.multiplier_ &&
               physicalEntityReference_ == rhs.physicalEntityReference_ &&
               local_participant_metaid_ == rhs.local_participant_metaid_ &&
               local_uri_ == rhs.local_uri_ &&
               model_uri_ == rhs.model_uri_;
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

    const std::string &Participant::getLocalParticipantMetaid() const {
        return local_participant_metaid_;
    }

    void Participant::setUniqueParticipantMetaid(const std::string &uniqueParticipantMetaid) {
        local_participant_metaid_ = uniqueParticipantMetaid;
    }

    const std::string &Participant::getLocalUri() const {
        return local_uri_;
    }

    void Participant::setLocalUri(const std::string &localUri) {
        local_uri_ = localUri;
    }

    const std::string &Participant::getModelUri() const {
        return model_uri_;
    }

    void Participant::setModelUri(const std::string &model_uri) {
        model_uri_ = model_uri;
    }

    SourceParticipant::SourceParticipant(librdf_model *model, double multiplier, std::string physicalEntityReference,
                                         const std::string &model_uri, const std::string &local_uri)
            : Participant(model, "SourceParticipant", model_uri, local_uri, "hasSourceParticipant",
                          multiplier, std::move(physicalEntityReference)) {}

    SinkParticipant::SinkParticipant(librdf_model *model, double multiplier,
                                     std::string physicalEntityReference, const std::string &model_uri,
                                     const std::string &local_uri)
            : Participant(model, "SinkParticipant", model_uri, local_uri,
                          "hasSinkParticipant",
                          multiplier,
                          std::move(physicalEntityReference)) {}

    MediatorParticipant::MediatorParticipant(
            librdf_model *model, std::string physicalEntityReference, const std::string &model_uri,
            const std::string &local_uri)
            : Participant(model, "MediatorParticipant", model_uri, local_uri,
                          "hasMediatorParticipant",
                          0.0, std::move(physicalEntityReference)) {}


}