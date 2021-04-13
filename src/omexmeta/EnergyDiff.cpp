//
// Created by Ciaran on 4/22/2020.
//

#include "omexmeta/EnergyDiff.h"


namespace omexmeta {

    EnergyDiff::EnergyDiff(librdf_model *model, UriHandler& uriHandler,
                                 PhysicalProperty physicalProperty,
                                 Sources sources,
                                 Sinks sinks)
        : PropertyBearer(model, uriHandler, std::move(physicalProperty), PHYSICAL_PROCESS),
          sources_(std::move(sources)), sinks_(std::move(sinks)) {
    }

    const std::vector<SourceParticipant> &EnergyDiff::getSources() const {
        return sources_;
    }

    const std::vector<SinkParticipant> &EnergyDiff::getSinks() const {
        return sinks_;
    }

    std::string EnergyDiff::createMetaId() {
        return generateMetaId("EnergyDiff");
    }

    Triples EnergyDiff::toTriples() {

        if (OmexMetaUtils::isStringEmpty<EnergyDiff>(*this, getAbout())) {
            std::string new_energy_diff_about_value = generateMetaId("EnergyDiff");
            about(new_energy_diff_about_value, LOCAL_URI);
        }

        if (OmexMetaUtils::isStringEmpty<EnergyDiff>(*this, physical_property_.getAbout())) {
            // When about field is empty, the PhysicalProperty will autogenerate its own about metaid.
            // We set this base to something more appropriate for a EnergyDiff
            physical_property_.setPropertyMetaidBase("EnergyDiffProperty");
        }

        // We also have to update the
        // isPropertyOf field of the physical_property
        physical_property_.isPropertyOf(getAbout(), LOCAL_URI);


        Triples triples = physical_property_.toTriples();
        for (auto &source : sources_) {
            for (auto &triple : source.toTriples(getAbout(), new_metaid_exclusion_list_)) {
                triples.moveBack(triple);
            }
        }
        for (auto &sink : sinks_) {
            for (auto &triple : sink.toTriples(getAbout(), new_metaid_exclusion_list_)) {
                triples.moveBack(triple);
            }
        }
        return triples;
    }

    EnergyDiff &EnergyDiff::setPhysicalProperty(PhysicalProperty physicalProperty) {
        physical_property_ = std::move(physicalProperty);
        return (*this);
    }

    EnergyDiff &EnergyDiff::setPhysicalProperty(std::string subject_metaid, const std::string& physical_property) {
        if (!OmexMetaUtils::startsWith(subject_metaid, "http")) {
            subject_metaid = OmexMetaUtils::concatMetaIdAndUri(subject_metaid, getModelUri());
        }
        physical_property_ = PhysicalProperty(model_, uriHandler_);
        physical_property_.about(subject_metaid)
                .isVersionOf(physical_property);
        return *this;
    }

    EnergyDiff &EnergyDiff::addSource(const std::string &physical_entity_reference, eUriType type) {
        sources_.push_back(
                std::move(SourceParticipant(
                        model_, 0.0, physical_entity_reference, type, uriHandler_)));
        return (*this);
    }

    EnergyDiff &EnergyDiff::addSink(const std::string &physical_entity_reference, eUriType type) {
        sinks_.push_back(
                SinkParticipant(model_, 0.0, physical_entity_reference, type, uriHandler_));
        return (*this);
    }

    EnergyDiff::EnergyDiff(librdf_model *model, UriHandler& uriHandler)
        : PropertyBearer(model, uriHandler) {}

    int EnergyDiff::getNumSources() {
        return sources_.size();
    }

    int EnergyDiff::getNumSinks() {
        return sinks_.size();
    }

    void EnergyDiff::free() {

        for (auto &i : sources_) {
            i.free();
        }
        for (auto &i : sinks_) {
            i.free();
        }
    }

    bool EnergyDiff::operator==(const EnergyDiff &rhs) const {
        return static_cast<const omexmeta::PropertyBearer &>(*this) ==
                       static_cast<const omexmeta::PropertyBearer &>(rhs) &&
               sources_ == rhs.sources_ &&
               sinks_ == rhs.sinks_;
    }

    bool EnergyDiff::operator!=(const EnergyDiff &rhs) const {
        return !(rhs == *this);
    }

    EnergyDiff &EnergyDiff::isVersionOf(const std::string &property) {
        physical_property_.isVersionOf(property);
        return *this;
    }

    EnergyDiff &EnergyDiff::isPropertyOf(const std::string &is_property_of, eUriType type) {
        physical_property_.isPropertyOf(is_property_of, type);
        return *this;
    }

    EnergyDiff &EnergyDiff::propertyIsVersionOf(const std::string &is_version_of) {
        physical_property_.isVersionOf(is_version_of);
        return *this;
    }

    const std::string &EnergyDiff::getPropertyMetaidBase() const {
        return property_metaid_base_;
    }
    EnergyDiff &EnergyDiff::hasProperty(const PhysicalProperty &property) {
        PropertyBearer::hasProperty(property);
        return *this;
    }
    EnergyDiff &EnergyDiff::hasProperty(const std::string &property_about, eUriType about_uri_type, const std::string &is_version_of, const std::string &is_property_of, eUriType is_property_of_uri_type) {
        PropertyBearer::hasProperty(property_about, about_uri_type, is_version_of, is_property_of, is_property_of_uri_type);
        return *this;
    }
    EnergyDiff &EnergyDiff::hasProperty(const std::string &is_version_of) {
        PropertyBearer::hasProperty(is_version_of);
        return *this;
    }
    EnergyDiff &EnergyDiff::hasProperty(const std::string &property_about, eUriType about_uri_type, const std::string &is_version_of) {
        PropertyBearer::hasProperty(property_about, about_uri_type, is_version_of);
        return *this;
    }

    EnergyDiff &EnergyDiff::about(const std::string &about, eUriType type) {
        PropertyBearer::about(about, type);
        return *this;
    }

    EnergyDiff &EnergyDiff::about(const std::string &about) {
        PropertyBearer::about(about);
        return *this;
    }


}// namespace omexmeta