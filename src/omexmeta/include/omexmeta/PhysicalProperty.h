//
// Created by Ciaran on 4/22/2020.
//

#ifndef LIBOMEXMETA_PHYSICALPROPERTY_H
#define LIBOMEXMETA_PHYSICALPROPERTY_H

#include "redland/RedlandAPI.h"

#include "omexmeta/Resource.h"
#include "omexmeta/Error.h"
#include "omexmeta/Triple.h"
#include "omexmeta/Triples.h"
#include "omexmeta/Triple.h"
#include "omexmeta/Triples.h"
#include "omexmeta_export.h"

#include <regex>
#include <utility>

using namespace redland;

namespace omexmeta {

    class PhysicalProperty {

        std::string is_property_of_value_;
        std::string is_version_of_value_;
        std::string metaid_;

        std::string model_uri_;
        std::string local_uri_;
        librdf_model* model_ = nullptr;

        OMEXMETA_DEPRECATED void validate();

    public:
        bool operator==(const PhysicalProperty &rhs) const;

        bool operator!=(const PhysicalProperty &rhs) const;

        PhysicalProperty() = default;

        /**
         * @brief constructor for PhysicalProperty
         * @param physical_property_string is used to create a URI node representing the physical property
         */
        OMEXMETA_DEPRECATED PhysicalProperty(std::string is_version_of, std::string is_version_of_value, std::string model_uri);

        OMEXMETA_DEPRECATED PhysicalProperty(std::string is_version_of, std::string is_version_of_value, std::string model_uri, librdf_model* model);

        PhysicalProperty(librdf_model *model, const std::string &model_uri, const std::string &local_uri);

        /**
         * @brief constructor for PhysicalProperty
         * @param physical_property_string is used to create a URI node representing the physical property
         */
        PhysicalProperty(std::string subject_str, std::string model_uri);

        [[nodiscard]] const std::string &getModelUri() const;

        [[nodiscard]] const std::string &getAbout() const;

        PhysicalProperty& about(const std::string &about);

        [[nodiscard]] const std::string &getIsVersionOfValue() const;

        /**
         * @brief creates a Triples object using the information in the PhysicalProperty
         * @return a Triples object containing the set of Triple object used to represent this PhysicalProperty
         */
        [[nodiscard]] Triples toTriples(const std::string& property_metaid) const;

        [[nodiscard]] Triples toTriples() const;

        PhysicalProperty &isPropertyOf(const std::string &is_property_of);

        PhysicalProperty &isVersionOf(const std::string &resource);

//        PhysicalProperty &propertyMetaId(const std::string &property_metaid);

    };


}

#endif //LIBOMEXMETA_PHYSICALPROPERTY_H
