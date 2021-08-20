//
// Created by Ciaran on 4/20/2020.
//

#include "omexmeta/Participant.h"

namespace omexmeta {


    Participant::Participant(LibrdfModel& model, std::string base_metaid,
                             UriHandler& uriHandler,
                             std::string semsim_predicate_term,
                             double multiplier,
                             std::string physicalEntityReference, eUriType type)
        : model_(model),
          metaid_template_str_(std::move(base_metaid)),
          uriHandler_(uriHandler),
          semsim_predicate_term_(std::move(semsim_predicate_term)),
          multiplier_(multiplier),
          physicalEntityReference_(std::move(physicalEntityReference)),
          type_(type) {}

    void Participant::free(){};// this was needed but no longer, because Triple objects do the cleaning

    std::string Participant::createMetaid(const std::string &base, std::vector<std::string> &metaid_exclusions) const {
        return OmexMetaUtils::generateUniqueMetaid(model_, base, metaid_exclusions);
    }


    Triples Participant::toTriples(std::string about, std::vector<std::string> &metaid_exclusions) {
        about = UriHandler::uriModifier<Participant>(*this, about, type_);
        if (local_participant_metaid_.empty()) {
            local_participant_metaid_ = OmexMetaUtils::generateUniqueMetaid(
                    model_, metaid_template_str_, metaid_exclusions);
        }

        if (!OmexMetaUtils::startsWith(about, "http")) {
            throw std::invalid_argument("std::invalid_argument: Participant::toTriples(): "
                                        "Expected a full uri (i.e. starts with http) for subject_metaid argument "
                                        "but received \"" +
                                        about + "\" instead");
        }
        /**
        * Since Triple's are added to the model as a unit, we need a way of keeping track of which metaids
         * have been used in order to ensure unique metaid's when we have more than one Sink/Source/Mediate Participant.
         * For this we add the generated metaid to a vector. Note, we do this before concat with local uri because of the way
         * local_uri's were added after the original design was in place. Future developers might want to look at this.
         */
        metaid_exclusions.push_back(local_participant_metaid_);

        local_participant_metaid_ = UriHandler::uriModifier<Participant>(*this, local_participant_metaid_, LOCAL_URI);

        Triples triples;
        // have source participant triple
        LibrdfNode sub1 = LibrdfNode::fromUriString(about);
        LibrdfNode pred1 = SemSim(semsim_predicate_term_).getNode();//term is hasSourceParticipant etc.
        LibrdfNode res1 = LibrdfNode::fromUriString(local_participant_metaid_);
        Triple triple1(uriHandler_, sub1, pred1, res1);
        triples.moveBack(triple1);

        LibrdfNode sub2 = LibrdfNode::fromUriString(local_participant_metaid_);
        LibrdfNode pred2 = SemSim("hasPhysicalEntityReference").getNode();
        LibrdfNode res2 = LibrdfNode::fromUriString(
                                    UriHandler::uriModifier<Participant>(*this, physicalEntityReference_, type_));
        Triple triple2(uriHandler_, sub2, pred2, res2);
        triples.moveBack(triple2);
        if (multiplier_ != 0.0) {
            std::ostringstream multiplier_os;
            multiplier_os << multiplier_;
            LibrdfNode sub3 = LibrdfNode::fromUriString(local_participant_metaid_);
            LibrdfNode pred3 = SemSim("hasMultiplier").getNode();
            LibrdfNode res3 = LibrdfNode::fromLiteral(
                                        multiplier_os.str(),
                                        "double");
            triples.emplace_back(uriHandler_, sub3, pred3, res3);
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
               getLocalUri() == rhs.getLocalUri() &&
               getModelUri() == rhs.getModelUri();
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
        return uriHandler_.getLocalUri();
    }

    const std::string &Participant::getModelUri() const {
        return uriHandler_.getModelUri();
    }

    SourceParticipant::SourceParticipant(LibrdfModel& model, double multiplier, std::string physicalEntityReference, eUriType type,
                                         UriHandler& uriHandler)
        : Participant(model, "SourceParticipant", uriHandler, "hasSourceParticipant",
                      multiplier, std::move(physicalEntityReference), type) {}

    SinkParticipant::SinkParticipant(LibrdfModel& model, double multiplier,
                                     std::string physicalEntityReference, eUriType type, UriHandler& uriHandler)
        : Participant(model, "SinkParticipant", uriHandler,
                      "hasSinkParticipant",
                      multiplier,
                      std::move(physicalEntityReference), type) {}

    MediatorParticipant::MediatorParticipant(
            LibrdfModel& model, std::string physicalEntityReference, eUriType type, UriHandler& uriHandler)
        : Participant(model, "MediatorParticipant", uriHandler,
                      "hasMediatorParticipant",
                      0, std::move(physicalEntityReference), type) {}


}// namespace omexmeta
