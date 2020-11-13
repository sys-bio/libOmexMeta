//
// Created by Ciaran on 4/22/2020.
//

#include "omexmeta/PhysicalProcess.h"

namespace omexmeta {

    PhysicalProcess::PhysicalProcess(librdf_model *model, std::string model_uri, std::string local_uri,
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
        subject_metaid = OmexMetaUtils::concatMetaIdAndUri(subject_metaid, getModelUri());
        physical_property_ = PhysicalProperty(subject_metaid, physicalProperty, getModelUri());
        return (*this);
    }

    PhysicalProcess &PhysicalProcess::addSource(std::string physical_entity_reference, int multiplier) {
        sources_.push_back(
                std::move(SourceParticipant(model_,
                                            multiplier,
                                            std::move(physical_entity_reference),
                                            getModelUri(), getLocalUri())));
        return (*this);
    }

    PhysicalProcess &PhysicalProcess::addSink(std::string physical_entity_reference, int multiplier) {
        sinks_.push_back(
                std::move(SinkParticipant(
                        model_,
                        multiplier, std::move(physical_entity_reference),
                        getModelUri(), getLocalUri())));

        return (*this);
    }

    PhysicalProcess &PhysicalProcess::addMediator(std::string physical_entity_reference) {
        mediators_.push_back(
                std::move(MediatorParticipant(
                        model_,
                        std::move(physical_entity_reference),
                        getModelUri(), getLocalUri())));

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
        std::cout<<"prop about:"  << physical_property_.getAbout() << std::endl;

        // check PhysicalProcess::getAbout for being empty. Autogenerate id if true.
        if (OmexMetaUtils::isStringEmpty<PhysicalProcess>(*this, getAbout())) {
            std::cout << "autogenerating about for physical process property" << std::endl;
            std::string new_process_about_value = generateMetaId("Process");
            about(new_process_about_value, LOCAL_URI);


        }

        if (OmexMetaUtils::isStringEmpty<PhysicalProcess>(*this, physical_property_.getAbout())) {
            // the PhysicalProperty will autogenerate its own about metaid. We set this base to something more approprioate for a PhysicalProcess
            physical_property_.setPropertyMetaidBase("ProcessProperty");
        }

        // We also have to update the
        // isPropertyOf field of the physical_property
        physical_property_.isPropertyOf(getAbout(), LOCAL_URI);
        Triples triples = physical_property_.toTriples();

        if (!is_version_of_.empty()) {
            SingularAnnotation singularAnnotation(
                    LibrdfNode::fromUriString(getAbout()).get(),
                    PredicateFactory("bqbiol", "isVersionOf")->getNode(),
                    LibrdfNode::fromUriString(is_version_of_).get());
            triples.move_back(singularAnnotation);
        }
        for (auto &source : sources_) {
            for (auto &triple : source.toTriples(getAbout(), new_metaid_exclusion_list_)) {
                triples.move_back(triple);
            }
        }
        for (auto &sink : sinks_) {
            for (auto &triple : sink.toTriples(getAbout(), new_metaid_exclusion_list_)) {
                triples.move_back(triple);
            }
        }
        for (auto &mediator : mediators_) {
            for (auto &triple : mediator.toTriples(getAbout(), new_metaid_exclusion_list_)) {
                triples.move_back(triple);
            }
        }
        return triples;
    }


//    PhysicalProcess &PhysicalProcess::isVersionOf(const std::string &property) {
//        physical_property_.isVersionOf(property);
//        return *this;
//    }

    PhysicalProcess &PhysicalProcess::about(const std::string &about, eUriType type) {
        std::cout<<"about " << about << std::endl;
        about_value_ = UriHandler::uriModifier<PhysicalProcess>(*this, about, type);
        std::cout<<"about_value_:"  << about_value_ << std::endl;
//        if (!OmexMetaUtils::startsWith(about, "http"))
//            physical_property_.about(OmexMetaUtils::concatMetaIdAndUri(about, model_uri_));
//        else
//            physical_property_.about(about, type);
        return *this;
    }

//    PhysicalProcess &PhysicalProcess::variableMetaId(const std::string &metaid) {
//        physical_process_property_id_ = metaid;
//        return *this;
//    }

    PhysicalProperty &PhysicalProcess::hasProperty(const PhysicalProperty &property) {
        physical_property_ = property;
        if (OmexMetaUtils::isStringEmpty<PhysicalProcess>(*this, physical_property_.getIsPropertyOfValue())){
            // physical property takes care of generating ids
            physical_property_.setPropertyMetaidBase(getPropertyMetaidBase());
        }
        return physical_property_;
    }

    PhysicalProperty &PhysicalProcess::hasProperty(const std::string &property_about, eUriType about_uri_type) {
        /*
         * Two scenarios:
         *  1) User wants to provide their own strings to use for the property about section.
         *  2) the user wants the library to autogenerate a property metaid, which will be local to rdf document
         */
                std::cout<<"prop about:2"  << physical_property_.getAbout() << std::endl;

        if (property_about.empty()){
            // option 2
            physical_property_ = PhysicalProperty(model_, model_uri_, local_uri_);
            physical_property_.setPropertyMetaidBase("ProcessProperty");

        } else {
            // option 1
            physical_property_ = PhysicalProperty(model_, model_uri_, local_uri_).about(property_about, about_uri_type);
        }
                std::cout<<"prop about:3"  << physical_property_.getAbout() << std::endl;
        return physical_property_;
    }
}// namespace omexmeta