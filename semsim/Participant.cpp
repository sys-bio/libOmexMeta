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

    std::vector<Triple> Participant::toTriples() const {

        std::vector<Triple> triples;
        triples.emplace_back(
                world_,
                Subject(world_, RDFURINode(world_, subject_)),
                predicate_ptr_, //term is hasSourceParticipant etc.
                resource_
        );

        triples.emplace_back(
                world_,
                Subject(world_, RDFURINode(world_, resource_.str())),
                std::make_shared<SemSim>(SemSim(world_, "hasPhysicalEntityReference")),
                Resource(world_, RDFURINode(world_, physicalEntityReference_))
        );
        if (multiplier_ != 0.0) {
            std::ostringstream multiplier_os;
            multiplier_os << multiplier_;
            triples.emplace_back(
                    world_,
                    Subject(world_, RDFURINode(world_, resource_.str())),
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

    }

    SinkParticipant::SinkParticipant(
            librdf_world *world, std::string subject, Resource resource,
            double multiplier, std::string physicalEntityReference)
            : Participant(world, subject,
                          std::make_shared<SemSim>(SemSim(world, "hasSinkParticipant")),
                          resource, multiplier, physicalEntityReference) {

    }

    MediatorParticipant::MediatorParticipant(
            librdf_world *world, std::string subject, Resource resource,
            std::string physicalEntityReference)
            : Participant(world, subject,
                          std::make_shared<SemSim>(SemSim(world, "hasMediatorParticipant")),
                          resource, 0.0, physicalEntityReference) {

    }
//
//
//    SinkParticipant::SinkParticipant(
//            librdf_world *world, Subject subject, Resource resource,
//            double multiplier, std::string physicalEntityReference)
//            : Participant(world, std::move(subject), std::__cxx11::string(),
//                          std::make_shared<SemSim>(SemSim(world, "hasSourceParticipant")),
//                          std::move(resource), std::__cxx11::string()),
//              multiplier_(multiplier), physicalEntityReference_(std::move(physicalEntityReference)) {}
//
//    std::vector<Triple> SinkParticipant::toTriples() {
//        return Participant::toTriples_(world_, getSubject(), "hasParticipantSink", getResource(),
//                                       multiplier_, physicalEntityReference_);
//    };
//
//
//    MediatorParticipant::MediatorParticipant(
//            librdf_world *world, Subject subject, Resource resource,
//            std::string physicalEntityReference)
//            : Participant(world, std::move(subject), std::__cxx11::string(),
//                          std::make_shared<SemSim>(SemSim(world, "hasMediatorParticipant")),
//                          std::move(resource), std::__cxx11::string()),
//              physicalEntityReference_(std::move(physicalEntityReference)) {}
//
//    std::vector<Triple> MediatorParticipant::toTriples() {
//        return Participant::toTriples_(world_, getSubject(), "SourceParticipant", getResource(),
//                                       0.0, physicalEntityReference_);
//    };


}