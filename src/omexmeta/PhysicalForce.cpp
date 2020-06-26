//
// Created by Ciaran on 4/22/2020.
//

#include "omexmeta/PhysicalForce.h"

#include <utility>

#include <utility>


namespace semsim {

    PhysicalForce::PhysicalForce(librdf_model *model,
                                 PhysicalProperty physicalProperty,
                                 Sources sources, Sinks sinks)
            : PhysicalPhenomenon(model, std::move(physicalProperty), PHYSICAL_PROCESS),
              sources_(std::move(sources)), sinks_(std::move(sinks)) {

    }

    const std::vector<SourceParticipant> &PhysicalForce::getSources() const {
        return sources_;
    }

    const std::vector<SinkParticipant> &PhysicalForce::getSinks() const {
        return sinks_;
    }

    std::string PhysicalForce::createMetaId() const {
        return generateMetaId("PhysicalForce");
    }

    Triples PhysicalForce::toTriples() {
        if (getAbout().empty()) {
            throw AnnotationBuilderException(
                    "PhysicalForce::toTriples(): Cannot create"
                    " triples because the \"about\" information is not set. "
                    "Use the setAbout() method."
            );
        }
        if (getPhysicalProperty().getResourceStr().empty()) {
            throw AnnotationBuilderException(
                    "PhysicalForce::toTriples(): Cannot create"
                    " triples because the \"physical_property resource\" information is not set. "
                    "Use the setPhysicalProperty() method."
            );
        }

        std::string force_metaid = SemsimUtils::generateUniqueMetaid(
                model_, "PhysicalForce",
                std::vector<std::string>());

        Triples triples = physical_property_.toTriples(force_metaid);

        for (auto &source : sources_) {
            for (auto &triple : source.toTriples(force_metaid)) {
                triples.move_back(triple);
            }
        }
        for (auto &sink : sinks_) {
            for (auto &triple : sink.toTriples(force_metaid)) {
                triples.move_back(triple);
            }
        }
        return triples;
    }

    PhysicalForce &PhysicalForce::setAbout(const std::string &metaid) {
        physical_property_.setSubject(metaid);
        return (*this);
    }

    PhysicalForce &PhysicalForce::setPhysicalProperty(PhysicalProperty physicalProperty) {
        physical_property_ = std::move(physicalProperty);
        return (*this);
    }

    PhysicalForce &PhysicalForce::setPhysicalProperty(std::string subject_metaid, std::string physical_property) {
        physical_property_ = PhysicalProperty(std::move(subject_metaid), std::move(physical_property));
        return *this;
    }

    PhysicalForce &PhysicalForce::addSource(double multiplier,const std::string& physical_entity_reference) {
        sources_.push_back(
                std::move(SourceParticipant(
                        model_,
                        multiplier, physical_entity_reference
                ))
        );
        return (*this);
    }

    PhysicalForce &PhysicalForce::addSink(double multiplier, const std::string& physical_entity_reference) {
        sinks_.push_back(
                SinkParticipant(model_, multiplier, physical_entity_reference)
        );

        return (*this);
    }

    PhysicalForce::PhysicalForce(librdf_model *model)
            : PhysicalPhenomenon(model) {}

    int PhysicalForce::getNumSources() {
        return sources_.size();
    }

    int PhysicalForce::getNumSinks() {
        return sinks_.size();
    }

    void PhysicalForce::free() {

        for (auto &i : sources_) {
            i.free();
        }
        for (auto &i : sinks_) {
            i.free();
        }
    }

    bool PhysicalForce::operator==(const PhysicalForce &rhs) const {
        return static_cast<const semsim::PhysicalPhenomenon &>(*this) ==
               static_cast<const semsim::PhysicalPhenomenon &>(rhs) &&
               sources_ == rhs.sources_ &&
               sinks_ == rhs.sinks_;
    }

    bool PhysicalForce::operator!=(const PhysicalForce &rhs) const {
        return !(rhs == *this);
    }

}