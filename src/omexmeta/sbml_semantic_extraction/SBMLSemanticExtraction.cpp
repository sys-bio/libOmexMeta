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



    void SBMLSemanticExtraction::extractProcessesFromReactions() {
        ElementExtractor reaction_extraction(sbml_string_, "reaction");
        std::vector<xmlNode *> reactions = reaction_extraction.getElements();

        if (reactions.empty()) {
            return; // this is not needed when model has no reactions.
        }
        // we also need the listOfSpecies element and its children
        ElementExtractor species_extraction(sbml_string_, "listOfSpecies");
        std::vector<xmlNode *> list_of_species = species_extraction.getElements();
        assert(list_of_species.size() == 1);
        std::vector<xmlNode *> species_elements = OmexMetaUtils::getAllChildElements(list_of_species[0]);

        // we iterate over all reaction elements
        for (auto &reaction_node: reactions) {
            // collect some of the reaction attributes
            std::string reaction_id = OmexMetaUtils::getXmlNodeProperty(reaction_node, "id");
            std::string reaction_metaid = OmexMetaUtils::getXmlNodeProperty(reaction_node, "metaid");

            // begin the annotation
            PhysicalProcess process = editor_.newPhysicalProcess();
            process.setPhysicalProperty(reaction_metaid, "opb::opb_1234");

            // and pull out the listOf* elements for the reaction
            xmlNode* reactants_node = OmexMetaUtils::getChildElementCalled(reaction_node, "listOfReactants");
            xmlNode* products_node = OmexMetaUtils::getChildElementCalled(reaction_node, "listOfProducts");
            xmlNode* modifiers_node = OmexMetaUtils::getChildElementCalled(reaction_node, "listOfModifiers");

            // we collect the speciesReference elements which are children of listOf* elements in a reaction
            // note, these will be empty if listOf* is empty and we won't enter the next loop.
            std::vector<xmlNode*> reactants_species_references = OmexMetaUtils::getAllChildElements(reactants_node);
            std::vector<xmlNode*> products_species_references = OmexMetaUtils::getAllChildElements(products_node);
            std::vector<xmlNode*> modifiers_species_references = OmexMetaUtils::getAllChildElements(modifiers_node);

            // Now we iterate over the collected species references
            // note: there is some code duplication here but since we need to use a different
            // end method (addSource here) it'll take some thinking.
            for (auto &reactant_node: reactants_species_references){
                // collect some information from the participant node attributes
                std::string reactant_node_stoic = OmexMetaUtils::getXmlNodeProperty(reactant_node, "stoichiometry");
                std::string reactant_node_species_ref = OmexMetaUtils::getXmlNodeProperty(reactant_node, "species");


                // and begin looking for the species that has the reactant_node_species_ref
                for (auto &species_node : species_elements){
                    // collect the id from the species node and compare against reactant_node_species_ref
                    std::string species_node_id = OmexMetaUtils::getXmlNodeProperty(species_node, "id");
                    if (reactant_node_species_ref == species_node_id){
                        // if we have a match, then species_node contains our metaid that will be species ref.
                        std::string species_node_metaid = OmexMetaUtils::getXmlNodeProperty(species_node, "metaid");
                        process.addSource(std::stod(reactant_node_stoic), reactant_node_species_ref);
                    }
                }
            }

            // Similarly for products.
            for (auto &product_node: products_species_references){
                // collect some information from the participant node attributes
                std::string product_node_stoic = OmexMetaUtils::getXmlNodeProperty(product_node, "stoichiometry");
                std::string product_node_species_ref = OmexMetaUtils::getXmlNodeProperty(product_node, "species");

                // and begin looking for the species that has the reactant_node_species_ref
                for (auto &species_node : species_elements){
                    // collect the id from the species node and compare against reactant_node_species_ref
                    std::string species_node_id = OmexMetaUtils::getXmlNodeProperty(species_node, "id");
                    if (product_node_species_ref == species_node_id){
                        // if we have a match, then species_node contains our metaid that will be species ref.
                        std::string species_node_metaid = OmexMetaUtils::getXmlNodeProperty(species_node, "metaid");
                        process.addSink(std::stod(product_node_stoic), product_node_species_ref);
                    }
                }
            }
            // modifiers
            for (auto &modifier_node: modifiers_species_references){
                // collect some information from the participant node attributes
                std::string modifier_node_species_ref = OmexMetaUtils::getXmlNodeProperty(modifier_node, "species");

                // and begin looking for the species that has the reactant_node_species_ref
                for (auto &species_node : species_elements){
                    // collect the id from the species node and compare against reactant_node_species_ref
                    std::string species_node_id = OmexMetaUtils::getXmlNodeProperty(species_node, "id");
                    if (modifier_node_species_ref == species_node_id){
                        // if we have a match, then species_node contains our metaid that will be species ref.
                        std::string species_node_metaid = OmexMetaUtils::getXmlNodeProperty(species_node, "metaid");
                        process.addMediator(modifier_node_species_ref);
                    }
                }
            }
            editor_.addPhysicalProcess(process);
        }
    }
}






