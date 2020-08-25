//
// Created by Ciaran on 4/22/2020.
//

#ifndef LIBOMEXMETA_PHYSICALPROPERTY_H
#define LIBOMEXMETA_PHYSICALPROPERTY_H

#include "omexmeta/Resource.h"
#include "omexmeta/Error.h"
#include "omexmeta/Triple.h"
#include "omexmeta/Triples.h"
#include "RedlandWrapper.h"
#include "Triple.h"
#include "Triples.h"
#include <regex>
#include "omexmeta/HERE.h"

using namespace redland;

namespace omexmeta {

    /*
     * PhysicalProperty is a subclass of the Resource
     * object. It is a special type of Resource that is restricted
     * to terms from the ontology of physics for biology.
     *
     * Usage:
     *  PhysicalProperty r("http://identifiers.org/opb:opb12345");
     * is equilavent to:
     *  PhysicalProperty r("opb:opb12345");
     * is equilavent to:
     *  PhysicalProperty r("opb/opb12345");
     *
     */
    class PhysicalProperty {

        std::string subject_;
        std::string resource_;
        std::string model_uri_;
        void validate();

    public:
        bool operator==(const PhysicalProperty &rhs) const;

        bool operator!=(const PhysicalProperty &rhs) const;

        PhysicalProperty() = default;

        /*
         * @brief constructor for PhysicalProperty
         * @param physical_property_string is used to create a URI node representing the physical property
         */
        explicit PhysicalProperty(std::string subject_str, std::string resource_str, std::string model_uri);

        const std::string &getSubject() const;

        const std::string &getResource() const;

        const std::string &getModelUri() const;

        void setModelUri(const std::string &model_uri);

        [[nodiscard]] const std::string &getSubjectStr() const;

        void setSubject(const std::string &subject);

        [[nodiscard]] const std::string &getResourceStr() const;

        void setResource(const std::string &resource);

        /*
         * @brief creates a Triples object using the information in the PhysicalProperty
         * @return a Triples object containing the set of Triple object used to represent this PhysicalProperty
         */
        [[nodiscard]] Triples toTriples(const std::string& property_metaid) const;

    };
}

#endif //LIBOMEXMETA_PHYSICALPROPERTY_H
