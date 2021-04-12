//
// Created by Ciaran on 4/22/2020.
//

#ifndef LIBOMEXMETA_PHYSICALPROPERTY_H
#define LIBOMEXMETA_PHYSICALPROPERTY_H

#include "redland/RedlandAPI.h"

#include "omexmeta/Error.h"
#include "omexmeta/Resource.h"
#include "omexmeta/Triple.h"
#include "omexmeta/Triples.h"
#include "omexmeta/UriHandler.h"
#include "omexmeta_export.h"

#include <regex>
#include <utility>

using namespace redland;

namespace omexmeta {

    class PhysicalProperty {

    public:
        bool isSet() const;

        void setIsSet(bool isSet);

        bool operator==(const PhysicalProperty &rhs) const;

        bool operator!=(const PhysicalProperty &rhs) const;

        PhysicalProperty() = default;

        /**
         * @brief constructor for PhysicalProperty
         * @param physical_property_string is used to create a URI node representing the physical property
         * @details overload deprecated use PhysicalProperty(model, model_uri, local_uri) instead
         */
        [[deprecated]] PhysicalProperty(std::string is_version_of, std::string is_version_of_value, std::string model_uri);

        void setPropertyMetaidBase(const std::string &propertyMetaidBase);

        [[nodiscard]] const std::string &getPropertyBearerBase() const;

        void setPropertyBearerBase(const std::string &propertyBearerBase);
        /**
         * @brief constructor for PhysicalProperty
         * @param physical_property_string is used to create a URI node representing the physical property
         * @details overload deprecated use PhysicalProperty(model, model_uri, local_uri) instead
         */
        [[deprecated]] PhysicalProperty(std::string is_version_of, std::string is_version_of_value, std::string model_uri, librdf_model *model);

        [[deprecated("PhysicalProperty(librdf_model *model, UriHandler uriHandler;")]]
        PhysicalProperty(librdf_model *model, const std::string &model_uri, const std::string &local_uri);

        PhysicalProperty(librdf_model *model, UriHandler uriHandler);

//        /**
//         * @brief constructor for PhysicalProperty
//         * @param physical_property_string is used to create a URI node representing the physical property
//         */
//        PhysicalProperty(std::string subject_str, std::string model_uri);

        [[nodiscard]] const std::string &getModelUri() const;

        [[nodiscard]] const std::string &getAbout() const;

        PhysicalProperty &about(const std::string &about, eUriType type = eUriType::NONE);

        [[nodiscard]] const std::string &getIsVersionOfValue() const;

        /**
         * @brief creates a Triples object using the information in the PhysicalProperty
         * @return a Triples object containing the set of Triple object used to represent this PhysicalProperty
         */
        [[nodiscard]] Triples toTriples();

        PhysicalProperty &isPropertyOf(const std::string &is_property_of, eUriType type);

        PhysicalProperty &isVersionOf(const std::string &resource);

        [[nodiscard]] const std::string &getLocalUri() const;

        [[nodiscard]] const std::string &getIsPropertyOfValue() const;

        [[nodiscard]] const std::string &getPropertyMetaidBase() const;

    private:
        std::vector<std::string> new_metaid_exclusion_list_;
        std::string is_property_of_value_;
        std::string is_version_of_value_;
        std::string property_metaid_base_ = "Property";// which string to use for the base uri. "Property" would use Property0000 as first metaid generated.
        std::string property_bearer_base_ = "Entity";  // which string to use for the thing that has the property.
        std::string about_value_;

        std::string model_uri_;
        std::string local_uri_;
        librdf_model *model_ = nullptr;

        UriHandler uriHandler_;

        /**
         * Indicator to let classes which use the PhysicalProperty
         * know whether a particular instance of physical property has been set
         * by calling the hasProperty() method.
         */
        bool is_set_ = false;

        OMEXMETA_DEPRECATED void validate();

    };


}// namespace omexmeta

#endif//LIBOMEXMETA_PHYSICALPROPERTY_H
