//
// Created by Ciaran on 11/08/2020.
//

#include "omexmeta/SBMLSemanticExtraction.h"

namespace omexmeta {

    SBMLSemanticExtraction::SBMLSemanticExtraction(Editor *editor)
        : editor_(editor), sbml_string_(editor->getXml()) {
    }

    void SBMLSemanticExtraction::extractSpeciesCompartmentSemantics() {
        ElementExtractor compartment_extraction(sbml_string_, "compartment");
        std::vector<xmlNode *> compartments = compartment_extraction.getElements();
        if (compartments.size() == 1) {
            return;// this is not needed when we only have one compartment.
        }
        ElementExtractor species_extraction(sbml_string_, "species");
        std::vector<xmlNode *> species = species_extraction.getElements();
        // this logic would be easier with objects, but I don't want to rewrite
        // libsbml or use it as a dependency so here I'll do it the hard way.
        // to help with readability, I'm using very descriptive names.
        for (auto &species_node : species) {
            // get name
            std::string species_id = OmexMetaUtils::getXmlNodeProperty(species_node, "id");
            std::string species_metaid = OmexMetaUtils::getXmlNodeProperty(species_node, "metaid");
            // get the compartment id for which the species belongs to. Remember to free this char* later
            std::string compartment_id_that_species_node_belongs_to = OmexMetaUtils::getXmlNodeProperty(species_node, "compartment");

            // compartment metaid.
            for (auto &compartment_node : compartments) {
                // if the compartment matches the species_compartment_metaid
                std::string compartment_id = OmexMetaUtils::getXmlNodeProperty(compartment_node, "id");
                if (compartment_id_that_species_node_belongs_to == compartment_id) {
                    // collect the compartments metaid
                    std::string compartment_metaid_that_species_node_belongs_to = OmexMetaUtils::getXmlNodeProperty(compartment_node, "metaid");

                    // and use the information to construct a singular annotation and add it to the model
                    SingularAnnotation singularAnnotation = editor_->newSingularAnnotation();
                    singularAnnotation
                            .about(species_metaid)
                            .setPredicate("bqbiol", "isPartOf")
                            .setResourceWithModelUri(compartment_id_that_species_node_belongs_to);
                    editor_->addSingleAnnotation(singularAnnotation);
                    singularAnnotation.freeTriple();
                }
            }
        }
    }


    void SBMLSemanticExtraction::extractProcessesFromReactions() {
        std::cout << __FILE__ << ":" << __LINE__ << std::endl;
        ElementExtractor reaction_extraction(sbml_string_, "reaction");
        std::cout << __FILE__ << ":" << __LINE__ << std::endl;
        std::vector<xmlNode *> reactions = reaction_extraction.getElements();

        std::cout << __FILE__ << ":" << __LINE__ << std::endl;
        if (reactions.empty()) {
            return;// this is not needed when model has no reactions.
        }
        std::cout << __FILE__ << ":" << __LINE__ << std::endl;
        // we also need the listOfSpecies element and its children
        ElementExtractor species_extraction(sbml_string_, "listOfSpecies");
        std::cout << __FILE__ << ":" << __LINE__ << std::endl;
        std::vector<xmlNode *> list_of_species = species_extraction.getElements();
        std::cout << __FILE__ << ":" << __LINE__ << std::endl;
        assert(list_of_species.size() == 1);
        std::cout << __FILE__ << ":" << __LINE__ << std::endl;
        std::vector<xmlNode *> species_elements = OmexMetaUtils::getAllChildElements(list_of_species[0]);
        std::cout << __FILE__ << ":" << __LINE__ << std::endl;

        // we iterate over all reaction elements
        std::cout << __FILE__ << ":" << __LINE__ << std::endl;
        for (auto &reaction_node : reactions) {
            // collect some of the reaction attributes
            std::string reaction_id = OmexMetaUtils::getXmlNodeProperty(reaction_node, "id");
            std::cout << __FILE__ << ":" << __LINE__ << std::endl;
            std::string reaction_metaid = OmexMetaUtils::getXmlNodeProperty(reaction_node, "metaid");
            std::cout << __FILE__ << ":" << __LINE__ << std::endl;

            // begin the annotation
            PhysicalProcess process = editor_->newPhysicalProcess();
            std::cout << __FILE__ << ":" << __LINE__ << std::endl;
            process.hasProperty(reaction_metaid, MODEL_URI ).isVersionOf("opb:OPB_00592");
            std::cout << __FILE__ << ":" << __LINE__ << std::endl;

            // and pull out the listOf* elements for the reaction
            xmlNode *reactants_node = OmexMetaUtils::getChildElementCalled(reaction_node, "listOfReactants");
            std::cout << __FILE__ << ":" << __LINE__ << std::endl;
            xmlNode *products_node = OmexMetaUtils::getChildElementCalled(reaction_node, "listOfProducts");
            std::cout << __FILE__ << ":" << __LINE__ << std::endl;
            xmlNode *modifiers_node = OmexMetaUtils::getChildElementCalled(reaction_node, "listOfModifiers");
            std::cout << __FILE__ << ":" << __LINE__ << std::endl;

            // we collect the speciesReference elements which are children of listOf* elements in a reaction
            // note, these will be empty if listOf* is empty and we won't enter the next loop.
            std::vector<xmlNode *> reactants_species_references = OmexMetaUtils::getAllChildElements(reactants_node);
            std::cout << __FILE__ << ":" << __LINE__ << std::endl;
            std::vector<xmlNode *> products_species_references = OmexMetaUtils::getAllChildElements(products_node);
            std::cout << __FILE__ << ":" << __LINE__ << std::endl;
            std::vector<xmlNode *> modifiers_species_references = OmexMetaUtils::getAllChildElements(modifiers_node);
            std::cout << __FILE__ << ":" << __LINE__ << std::endl;

            // Now we iterate over the collected species references
            // note: there is some code duplication here but since we need to use a different
            // end method (addSource here) it'll take some thinking.
            for (auto &reactant_node : reactants_species_references) {
                // collect some information from the participant node attributes
                std::cout << __FILE__ << ":" << __LINE__ << std::endl;

                // stoichiometry only exists in some models. So default to 1.0.
                std::string reactant_node_stoic = "1.0";
                std::cout << __FILE__ << ":" << __LINE__ << std::endl;
                if (xmlHasProp(reactant_node, (const xmlChar *) "stoichiometry"))
                    reactant_node_stoic = OmexMetaUtils::getXmlNodeProperty(reactant_node, "stoichiometry");
                std::string reactant_node_species_ref = OmexMetaUtils::getXmlNodeProperty(reactant_node, "species");
                std::cout << __FILE__ << ":" << __LINE__ << std::endl;

                // and begin looking for the species that has the reactant_node_species_ref
                for (auto &species_node : species_elements) {
                    // collect the id from the species node and compare against reactant_node_species_ref
                    std::string species_node_id = OmexMetaUtils::getXmlNodeProperty(species_node, "id");
                    if (reactant_node_species_ref == species_node_id) {
                        // if we have a match, then species_node contains our metaid that will be species ref.
                        std::string species_node_metaid = OmexMetaUtils::getXmlNodeProperty(species_node, "metaid");
                        std::cout << __FILE__ << ":" << __LINE__ << std::endl;
                        process.addSource(species_node_metaid, MODEL_URI, std::stoi(reactant_node_stoic));
                        std::cout << __FILE__ << ":" << __LINE__ << std::endl;
                    }
                }
                std::cout << __FILE__ << ":" << __LINE__ << std::endl;
            }
            std::cout << __FILE__ << ":" << __LINE__ << std::endl;

            // Similarly for products.
            for (auto &product_node : products_species_references) {
                // collect some information from the participant node attributes
                std::cout << __FILE__ << ":" << __LINE__ << std::endl;

                // stoichiometry only exists in some models. So default to 1.0.
                std::string product_node_stoic = "1.0";
                std::cout << __FILE__ << ":" << __LINE__ << std::endl;
                if (xmlHasProp(products_node, (const xmlChar *) "stoichiometry"))
                    product_node_stoic = OmexMetaUtils::getXmlNodeProperty(product_node, "stoichiometry");
                std::string product_node_species_ref = OmexMetaUtils::getXmlNodeProperty(product_node, "species");
                std::cout << __FILE__ << ":" << __LINE__ << std::endl;

                // and begin looking for the species that has the reactant_node_species_ref
                std::cout << __FILE__ << ":" << __LINE__ << std::endl;
                for (auto &species_node : species_elements) {
                    // collect the id from the species node and compare against reactant_node_species_ref
                    std::string species_node_id = OmexMetaUtils::getXmlNodeProperty(species_node, "id");
                    std::cout << __FILE__ << ":" << __LINE__ << std::endl;
                    std::cout << "product_node_species_ref: " << product_node_species_ref << std::endl;
                    std::cout << __FILE__ << ":" << __LINE__ << std::endl;
                    std::cout << "species_node_id: " << species_node_id << std::endl;
                    std::cout << __FILE__ << ":" << __LINE__ << std::endl;
                    if (product_node_species_ref == species_node_id) {
                        // if we have a match, then species_node contains our metaid that will be species ref.
                        std::cout << __FILE__ << ":" << __LINE__ << std::endl;
                        std::string species_node_metaid = OmexMetaUtils::getXmlNodeProperty(species_node, "metaid");
                        std::cout << __FILE__ << ":" << __LINE__ << std::endl;
                        process.addSink(species_node_metaid, MODEL_URI, std::stoi(product_node_stoic));
                        std::cout << __FILE__ << ":" << __LINE__ << std::endl;
                    }
                    std::cout << __FILE__ << ":" << __LINE__ << std::endl;
                }
                std::cout << __FILE__ << ":" << __LINE__ << std::endl;
            }
            std::cout << __FILE__ << ":" << __LINE__ << std::endl;
            // modifiers
            for (auto &modifier_node : modifiers_species_references) {
                // collect some information from the participant node attributes
                std::cout << __FILE__ << ":" << __LINE__ << std::endl;
                std::string modifier_node_species_ref = OmexMetaUtils::getXmlNodeProperty(modifier_node, "species");

                // and begin looking for the species that has the reactant_node_species_ref
                for (auto &species_node : species_elements) {
                    std::cout << __FILE__ << ":" << __LINE__ << std::endl;
                    // collect the id from the species node and compare against reactant_node_species_ref
                    std::cout << __FILE__ << ":" << __LINE__ << std::endl;
                    std::string species_node_id = OmexMetaUtils::getXmlNodeProperty(species_node, "id");
                    std::cout << __FILE__ << ":" << __LINE__ << std::endl;
                    if (modifier_node_species_ref == species_node_id) {
                        std::cout << __FILE__ << ":" << __LINE__ << std::endl;
                        // if we have a match, then species_node contains our metaid that will be species ref.
                        std::string species_node_metaid = OmexMetaUtils::getXmlNodeProperty(species_node, "metaid");
                        std::cout << __FILE__ << ":" << __LINE__ << std::endl;
                        process.addMediator(species_node_metaid, MODEL_URI);
                        std::cout << __FILE__ << ":" << __LINE__ << std::endl;
                    }
                }
            }
            editor_->addPhysicalProcess(process);
        }
    }

}// namespace omexmeta
