//
// Created by Ciaran on 4/22/2020.
//

#include "PhysicalProcess.h"

#include <utility>

#include <utility>


namespace omexmeta {

    PhysicalProcess::PhysicalProcess(librdf_model *model, std::string model_uri,std::string local_uri,
                                     const PhysicalProperty &physicalProperty,
                                     Sources sources, Sinks sinks, Mediators mediators)
            : PhysicalPhenomenon(model, model_uri, local_uri, physicalProperty, PHYSICAL_PROCESS),
              sources_(std::move(sources)), sinks_(std::move(sinks)), mediators_(std::move(mediators)) {
    }

    PhysicalProcess::PhysicalProcess(librdf_model *model) : PhysicalPhenomenon(model) {}

    PhysicalProcess::PhysicalProcess(librdf_model *model, std::string model_uri, std::string local_uri)
        : PhysicalPhenomenon(model, model_uri, local_uri) {}

    const std::vector<SourceParticipant> &PhysicalProcess::getSources() const {
        return sources_;
    }

    const std::vector<SinkParticipant> &PhysicalProcess::getSinks() const {
        return sinks_;
    }

    const std::vector<MediatorParticipant> &PhysicalProcess::getMediators() const {
        return mediators_;
    }

    PhysicalProcess &PhysicalProcess::setPhysicalProperty(PhysicalProperty physicalProperty) {
        physical_property_ = std::move(physicalProperty);
        return (*this);
    }

//todo turn this into a factory whereby user enters string of PhysicalProperty
//  and we automatically pick out the correct OPB identifier
    PhysicalProcess &
    PhysicalProcess::setPhysicalProperty(std::string subject_metaid, const std::string &physicalProperty) {
        LOG_DEBUG("subject_metaid: %s, getModelUri(): %s", subject_metaid.c_str(), getModelUri().c_str());
        subject_metaid = OmexMetaUtils::concatMetaIdAndUri(subject_metaid, getModelUri());
        LOG_DEBUG("subject_metaid2: %s", subject_metaid.c_str());
        physical_property_ = PhysicalProperty(subject_metaid, physicalProperty, getModelUri());
        return (*this);
    }

    PhysicalProcess &PhysicalProcess::addSource(double multiplier, std::string physical_entity_reference) {
        sources_.push_back(
                std::move(SourceParticipant(model_,
                                            multiplier,
                                            std::move(physical_entity_reference),
                                            getModelUri()
                          )
                )
        );
        return (*this);
    }

    PhysicalProcess &PhysicalProcess::addSink(double multiplier, std::string physical_entity_reference) {
        sinks_.push_back(
                std::move(SinkParticipant(
                        model_,
                        multiplier, std::move(physical_entity_reference),
                        getModelUri()
                ))
        );

        return (*this);
    }

    PhysicalProcess &PhysicalProcess::addMediator(std::string physical_entity_reference) {
        mediators_.push_back(
                std::move(MediatorParticipant(
                        model_,
                        std::move(physical_entity_reference),
                        getModelUri()
                ))
        );

        return (*this);
    }

    int PhysicalProcess::getNumSources() {
        return sources_.size();
    }

    int PhysicalProcess::getNumSinks() {
        return sinks_.size();
    }

    int PhysicalProcess::getNumMediators() {
        return mediators_.size();
    }

    void PhysicalProcess::free() {
        for (auto &i : sources_) {
            i.free();
        }
        for (auto &i : sinks_) {
            i.free();
        }
        for (auto &i : mediators_) {
            i.free();
        }
    }

    bool PhysicalProcess::operator==(const PhysicalProcess &rhs) const {
        return static_cast<const omexmeta::PhysicalPhenomenon &>(*this) ==
               static_cast<const omexmeta::PhysicalPhenomenon &>(rhs) &&
               sources_ == rhs.sources_ &&
               sinks_ == rhs.sinks_ &&
               mediators_ == rhs.mediators_;
    }

    bool PhysicalProcess::operator!=(const PhysicalProcess &rhs) const {
        return !(rhs == *this);
    }


    Triples PhysicalProcess::toTriples() {
        if (getAbout().empty()) {
            throw AnnotationBuilderException(
                    "PhysicalProcess::toTriples(): Cannot create"
                    " triples because the \"about\" information is not set. "
                    "Use the setAbout() method."
            );
        }
        if (getPhysicalProperty().getResourceStr().empty()) {
            throw AnnotationBuilderException(
                    "PhysicalProcess::toTriples(): Cannot create"
                    " triples because the \"physical_property\" information is not set. "
                    "Use the setPhysicalProperty() method."
            );
        }
        std::string process_id = generateMetaId("PhysicalProcess");
        process_id = OmexMetaUtils::concatMetaIdAndUri(process_id, getLocalUri());

        LOG_DEBUG("getAbout: %s", getAbout().c_str());

        Triples triples = physical_property_.toTriples(getAbout());


        for (auto &source: sources_) {
            for (auto &triple: source.toTriples(process_id)) {
                triples.move_back(triple);
            }
        }
        for (auto &sink: sinks_) {
            for (auto &triple: sink.toTriples(process_id)) {
                triples.move_back(triple);
            }
        }
        for (auto &mediator: mediators_) {
            for (auto &triple: mediator.toTriples(process_id)) {
                triples.move_back(triple);
            }
        }
        return triples;
    }

}