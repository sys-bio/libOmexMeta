//
// Created by Ciaran on 11/08/2020.
//

#ifndef LIBOMEXMETA_SBMLSEMANTICEXTRACTION_H
#define LIBOMEXMETA_SBMLSEMANTICEXTRACTION_H

#include "omexmeta/Editor.h"
#include "omexmeta/ElementExtractor.h"

#include <iostream>

/**
 * Here's the basic logic that we use in SemGen to determine which OPB physical property is represented by a <species> in an SBML model:
 *
 * Using libSBML, we first look up the substance base units for the model and also whether the species's "hasOnlySubstanceUnits" attribute is true...
 *
 * if the substance base unit is mole
 *      if hasOnlySubstanceUnits for species is TRUE, then use OPB:Chemical_molar_amount (OPB_00425)
 *      else use OPB:Chemical_concentration (OPB_00340)
 *
 * else if the substance base unit is item
 *      if hasOnlySubstanceUnits for species is TRUE, then use OPB:Particle_count (OPB_01001)
 *      else use OPB:Particle_concentration (OPB_01000)
 *
 * else if the base unit is kilogram or gram
 *      if hasOnlySubstanceUnits is TRUE, then use OPB:Mass_of_solid_entity (OPB_01226)
 *      else
 *           if the spatial dimensions of the compartment containing the species = 1, use OPB:Mass_lineal_density (OPB_00190)
 *           else, if the spatial dimensions of the compartment containing the species = 2, use OPB:Mass_areal_density (OPB_00258)
 *           else, if the spatial dimensions of the compartment containing the species = 3, use OPB:Mass_volumetric_density (OPB_00101)
 *
 * Hope that's helpful for determining which OPB property to use in composite annotations for SBML <species>.
 *
 * Any questions, just lemme know.
 */


namespace omexmeta {

    class Editor;

    class SBMLSemanticExtraction {

        Editor* editor_ = nullptr;

        std::string sbml_string_;

    public:
        /**
         * @brief Construct an SBMLSemanticExtraction object
         * with an @brief Editor.
         */
        explicit SBMLSemanticExtraction(Editor *editor);

        /**
         * @brief Parses SBML and creates triples from
         * the location of species.
         * @details Takes a species and creates a single
         * triple with the following information:
         *  - subject node is species metaid
         *  - predicate is always bqbiol::isPartOf
         *  - resource is the metaid of the compartment the species belongs to
         */
        void extractSpeciesCompartmentSemantics();

        /**
         * @brief Parses the sbml and automatically
         * creates PhysicalProcess annotations for
         * each reaction.
         */
        void extractProcessesFromReactions();

    };
}












#endif //LIBOMEXMETA_SBMLSEMANTICEXTRACTION_H
