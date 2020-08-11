//
// Created by Ciaran on 11/08/2020.
//

#include "SBMLSemanticExtraction.h"

#include <utility>

namespace omexmeta {

    SBMLSemanticExtraction::SBMLSemanticExtraction(RDF &rdf, std::string sbml_string)
            : rdf_(rdf), sbml_string_(std::move(sbml_string)),
              editor_(rdf_.toEditor(sbml_string, OMEXMETA_TYPE_SBML)) {}

    void SBMLSemanticExtraction::extractSpeciesCompartmentSemantics() {
        ElementExtractor compartment_extraction(sbml_string_, "compartment");
        std::vector<xmlNode *> compartments = compartment_extraction.getElements();
        if (compartments.size() == 1) {
            return; // this is not needed when we only have one compartment.
        }
        ElementExtractor species_extraction(sbml_string_, "species");
        std::vector<xmlNode *> species = species_extraction.getElements();
        // this logic would be easier with objects, but I don't want to rewrite
        // libsbml or use it as a dependency so here I'll do it the hard way.
        // to help with readability, I'm using very descriptive names.
        for (auto &species_node: species) {
            // get name

            std::string species_id = OmexMetaUtils::getXmlNodeProperty(species_node, "id");
            std::string species_metaid = OmexMetaUtils::getXmlNodeProperty(species_node, "metaid");
            // get the compartment id for which the species belongs to. Remember to free this char* later
            std::string compartment_id_that_species_node_belongs_to = OmexMetaUtils::getXmlNodeProperty(species_node, "compartment");

            // compartment metaid.
            for (auto & compartment_node: compartments){
                // if the compartment matches the species_compartment_metaid
                std::string compartment_id = OmexMetaUtils::getXmlNodeProperty(compartment_node, "id");

                if (compartment_id_that_species_node_belongs_to == compartment_id){
                    // collect the compartments metaid
                    std::string compartment_metaid_that_species_node_belongs_to = OmexMetaUtils::getXmlNodeProperty(compartment_node, "metaid");

                    // and use the information to construct a singular annotation and add it to the model
                    SingularAnnotation singularAnnotation = editor_.newSingularAnnotation();
                    singularAnnotation
                        .setAbout(species_metaid)
                        .setPredicate("bqbiol", "isPartOf")
                        .setResourceUri(compartment_id_that_species_node_belongs_to);
                    editor_.addSingleAnnotation(singularAnnotation);
                    singularAnnotation.freeTriple();
                }
            }
        }
    }
}






