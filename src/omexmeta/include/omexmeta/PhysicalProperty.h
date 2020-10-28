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

#include <regex>
#include <utility>

using namespace redland;

namespace omexmeta {

    class PhysicalProperty {

        std::string subject_;
        std::string resource_;
        std::string model_uri_;
        void validate();

    public:
        bool operator==(const PhysicalProperty &rhs) const;

        bool operator!=(const PhysicalProperty &rhs) const;

        PhysicalProperty() = default;

        /**
         * @brief constructor for PhysicalProperty
         * @param physical_property_string is used to create a URI node representing the physical property
         */
        PhysicalProperty(std::string subject_str, std::string resource_str, std::string model_uri);

        /**
         * @brief constructor for PhysicalProperty
         * @param physical_property_string is used to create a URI node representing the physical property
         */
        PhysicalProperty(std::string subject_str, std::string model_uri);

        [[nodiscard]] const std::string &getSubject() const;

        [[nodiscard]] const std::string &getResource() const;

        [[nodiscard]] const std::string &getModelUri() const;

        void setModelUri(const std::string &model_uri);

        [[nodiscard]] const std::string &getSubjectStr() const;

        void setSubject(const std::string &subject);

        [[nodiscard]] const std::string &getResourceStr() const;

        void setResource(const std::string &resource);

        /**
         * @brief creates a Triples object using the information in the PhysicalProperty
         * @return a Triples object containing the set of Triple object used to represent this PhysicalProperty
         */
        [[nodiscard]] Triples toTriples(const std::string& property_metaid) const;

    };
}

#endif //LIBOMEXMETA_PHYSICALPROPERTY_H
