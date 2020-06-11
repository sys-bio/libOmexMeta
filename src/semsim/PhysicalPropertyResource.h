//
// Created by Ciaran on 4/22/2020.
//

#ifndef LIBSEMSIM_PHYSICALPROPERTYRESOURCE_H
#define LIBSEMSIM_PHYSICALPROPERTYRESOURCE_H

#include "semsim/Resource.h"
#include "semsim/Error.h"
#include "semsim/Triple.h"
#include "semsim/Triples.h"
#include "RedlandAPIWrapper.h"
#include "Triple.h"
#include "Triples.h"
#include <regex>
#include "semsim/HERE.h"

using namespace redland;

namespace semsim {

    /*
     * PhysicalPropertyResource is a subclass of the Resource
     * object. It is a special type of Resource that is restricted
     * to terms from the ontology of physics for biology.
     *
     * Usage:
     *  PhysicalPropertyResource r("http://identifiers.org/opb:opb12345");
     * is equilavent to:
     *  PhysicalPropertyResource r("opb:opb12345");
     * is equilavent to:
     *  PhysicalPropertyResource r("opb/opb12345");
     *
     */
    class PhysicalPropertyResource : public Resource {

        void validate();

    public:

        PhysicalPropertyResource() = default;

        /*
         * @brief constructor for PhysicalPropertyResource
         * @param physical_property_string is used to create a URI node representing the physical property
         */
        explicit PhysicalPropertyResource(std::string physical_property_string);

        /*
         * @brief make the triple that has the "isVersionOf" predicate
         * @param subject_metaid The metaid for the subject portion of the triple.
         * @return a Triple with the isVersionOf predicate for this PhysicalPropertyResource
         *
         * The metaid will be coverted into a RDF URI node
         */
        [[nodiscard]] Triple isVersionOfTriple(std::string subject_metaid) const;

        /*
         * @brief make the triple that has the "isPropertyOf" predicate
         * @param subject_metaid The metaid for the subject portion of the triple.
         * @param property_metaid The metaid for the property portion of the triple.
         * @return a Triple with the isPropertyOf predicate for this PhysicalPropertyResource
         *
         */
        [[nodiscard]] Triple isPropertyOfTriple(std::string subject_metaid, std::string property_metaid) const;

        /*
         * @brief creates a Triples object using the information in the PhysicalPropertyResource
         * @return a Triples object containing the set of Triple object used to represent this PhysicalPropertyResource
         */
        [[nodiscard]] Triples toTriples(std::string subject_metaid, std::string property_metaid) const;

        /*
         * @brief indicator for whether the PhysicalPropertyResource node is empty.
         * @return false when node is empty
         */
        [[nodiscard]] bool isSet() const override;

        Triples toTriples(Triple subject_metaid, Triple property_metaid) const;
    };
}

#endif //LIBSEMSIM_PHYSICALPROPERTYRESOURCE_H
