//
// Created by Ciaran on 4/22/2020.
//

#include "omexmeta/PropertyBearer.h"


namespace omexmeta {

    PropertyBearer::PropertyBearer(librdf_model *model, std::string model_uri, std::string local_uri,
                                           PhysicalProperty propertyResource, AnnotationType type)
        : model_(model), physical_property_(std::move(propertyResource)), type_(type),
          model_uri_(std::move(model_uri)), local_uri_(std::move(local_uri)) {}

    librdf_model *PropertyBearer::getModel() const {
        return model_;
    }

    PropertyBearer::~PropertyBearer() = default;


    PropertyBearer::PropertyBearer(librdf_model *model)
        : model_(model) {}

    PropertyBearer::PropertyBearer(librdf_model *model, std::string model_uri, std::string local_uri)
        : model_(model), model_uri_(std::move(model_uri)), local_uri_(std::move(local_uri)) {
        physical_property_ = PhysicalProperty(model_, model_uri_, local_uri_);
    }

    const std::string &PropertyBearer::getSubjectStr() const {
        return physical_property_.getAbout();
    }

    AnnotationType PropertyBearer::getType() const {
        return type_;
    }

    std::string PropertyBearer::generateMetaId(const std::string &id_base) {
        return OmexMetaUtils::generateUniqueMetaid(model_, id_base, new_metaid_exclusion_list_);
    }

    PhysicalProperty PropertyBearer::getPhysicalProperty() const {
        return physical_property_;
    }

    Triples PropertyBearer::toTriples() {
        throw NotImplementedException("Base class PhysicalPhenomenon "
                                      "does cannot produce triples.");
    }


    const std::string &PropertyBearer::getAbout() const {
        // if the about field is empty or equal to model or local uri only, then we generate an about
        return about_value_;
    }

    eUriType PropertyBearer::getAboutUriType() const {
        return about_uri_type_;
    }
    void PropertyBearer::setAboutUriType(eUriType aboutUriType) {
        about_uri_type_ = aboutUriType;
    }

    PropertyBearer::PropertyBearer(PropertyBearer &&phenomenon) noexcept {
        model_ = phenomenon.model_;
        phenomenon.model_ = nullptr;// not sure if this is right.
        physical_property_ = std::move(phenomenon.physical_property_);
        type_ = phenomenon.type_;
        model_uri_ = phenomenon.model_uri_;
    }

    PropertyBearer &PropertyBearer::operator=(PropertyBearer &&phenomenon) noexcept {
        if (this != &phenomenon) {
            model_ = phenomenon.model_;
            phenomenon.model_ = nullptr;// not sure if this is right.
            physical_property_ = std::move(phenomenon.physical_property_);
            type_ = phenomenon.type_;
            model_uri_ = phenomenon.model_uri_;
        }
        return *this;
    }

    bool PropertyBearer::operator==(const PropertyBearer &rhs) const {
        return physical_property_ == rhs.physical_property_;
    }

    bool PropertyBearer::operator!=(const PropertyBearer &rhs) const {
        return !(rhs == *this);
    }

    void PropertyBearer::setPhysicalProperty(const PhysicalProperty &physicalProperty) {
        physical_property_ = physicalProperty;
    }

    void PropertyBearer::setType(AnnotationType type) {
        type_ = type;
    }

    const std::string &PropertyBearer::getModelUri() const {
        if (model_uri_.empty()) {
            throw std::invalid_argument("std::invalid_argument: model_uri_ is empty. "
                                        "Please use setModelUri or pass to the constructor a "
                                        "model uri. ");
        }
        return model_uri_;
    }

    void PropertyBearer::setModelUri(const std::string &modelUri) {
        model_uri_ = modelUri;
    }

    const std::string &PropertyBearer::getLocalUri() const {
        if (local_uri_.empty()) {
            throw std::invalid_argument("std::invalid_argument: local_uri_ is empty. "
                                        "Please use setLocalUri or pass to the constructor a "
                                        "local uri. ");
        }
        return local_uri_;
    }

    void PropertyBearer::setLocalUri(const std::string &localUri) {
        local_uri_ = localUri;
    }

    std::vector<std::string> PropertyBearer::getNewMetaidExclusionList() {
        return new_metaid_exclusion_list_;
    }

    const std::string &PropertyBearer::getPropertyMetaidBase() const {
        return property_metaid_base_;
    }

    PropertyBearer &PropertyBearer::hasProperty(const std::string &property_about, eUriType about_uri_type, const std::string &is_version_of, const std::string &is_property_of, eUriType is_property_of_uri_type) {
        /*
         * Two scenarios:
         *  1) User wants to provide their own strings to use for the property about section.
         *  2) the user wants the library to autogenerate a property metaid, which will be local to rdf document
         */
        // option 1
        physical_property_ = PhysicalProperty(model_, model_uri_, local_uri_)
                                     .about(property_about, about_uri_type)
                                     .isVersionOf(is_version_of)
                                     .isPropertyOf(is_property_of, is_property_of_uri_type);
        return *this;
    }

    PropertyBearer &PropertyBearer::hasProperty(const std::string &is_version_of) {
        /*
         * Two scenarios:
         *  1) User wants to provide their own strings to use for the property about section.
         *  2) the user wants the library to autogenerate a property metaid, which will be local to rdf document
         */
        // option 2
        physical_property_ = PhysicalProperty(model_, model_uri_, local_uri_)
            .isVersionOf(is_version_of)
            .isPropertyOf(getAbout(), getAboutUriType());
        physical_property_.setPropertyMetaidBase(getPropertyMetaidBase());

        return *this;
    }

    PropertyBearer &PropertyBearer::hasProperty(const PhysicalProperty &property) {
        physical_property_ = property;
        if (OmexMetaUtils::isStringEmpty<PropertyBearer>(*this, physical_property_.getIsPropertyOfValue())){
            // physical property takes care of generating ids, we just set the base polymorphically.
            // subclasses override the getPropertyMetaidBase method to return their own version of base.
            physical_property_.setPropertyMetaidBase(getPropertyMetaidBase());
        }
        return *this;
    }

    PropertyBearer &PropertyBearer::hasProperty(const std::string &property_about, eUriType about_uri_type, const std::string &is_version_of) {
        /*
         * Two scenarios:
         *  1) User wants to provide their own strings to use for the property about section.
         *  2) the user wants the library to autogenerate a property metaid, which will be local to rdf document
         */
        // option 1
        physical_property_ = PhysicalProperty(model_, model_uri_, local_uri_)
                                     .about(property_about, about_uri_type)
                                     .isVersionOf(is_version_of)
                                     .isPropertyOf(getAbout(), getAboutUriType());
        return *this;
    }

    PropertyBearer &PropertyBearer::about(const std::string &about, eUriType type) {
        setAboutUriType(type);
        if (OmexMetaUtils::startsWith(about, "http")) {
            about_value_ = UriHandler::uriModifier<PropertyBearer>(*this, about, NONE);
        } else {
            about_value_ = UriHandler::uriModifier<PropertyBearer>(*this, about, type);
        }
        if (physical_property_.getIsPropertyOfValue().empty()){
            physical_property_.isPropertyOf(about_value_, LOCAL_URI);
        }
        return *this;
    }

    /**
     * Since we can't have default arguments on a virutal member function we
     * instead have an overload where the absent eUriType parameter is
     * assumed to be the default value of NONE. Note, it may be prudent to figure out which
     * of LOCAL or MODEL uri would be a better default.
     */
    PropertyBearer &PropertyBearer::about(const std::string &about) {

        setAboutUriType(NONE);
        about_value_ = UriHandler::uriModifier<PropertyBearer>(*this, about, NONE);
        if (OmexMetaUtils::startsWith(about, "http")) {
        } else {
            about_value_ = UriHandler::uriModifier<PropertyBearer>(*this, about, NONE);
        }
        if (physical_property_.getIsPropertyOfValue().empty()){
            physical_property_.isPropertyOf(about_value_, LOCAL_URI);
        }
        return *this;
    }

}// namespace omexmeta
