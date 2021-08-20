//
// Created by Ciaran on 10/08/2020.
//

#include "omexmeta/MarkupIdentifier.h"

namespace omexmeta {

    MarkupIdentifier::MarkupIdentifier(std::string markup) : markup_(std::move(markup)) {
        doc_ = parseML();
    }

    MarkupIdentifier::~MarkupIdentifier() {
        xmlFreeDoc(doc_);
    }

    /**
     * @brief read an xml document using libxml2.
     */
    xmlDoc *MarkupIdentifier::parseML() {
        doc_ = OmexMetaUtils::parseXmlDocument(markup_);

        // also populate elements vector
        xmlNode *root_element = xmlDocGetRootElement(doc_);
        collectElementNames(root_element);

        return doc_;
    }

    /**
     * @brief collect the name of the element pointed to by a_node
     * @brief *a_node pointer to an xmlNode
     */
    void MarkupIdentifier::collectElementNames(xmlNode *a_node) {
        for (xmlNode *cur_node = a_node; cur_node; cur_node = cur_node->next) {
            if (cur_node->type == XML_ELEMENT_NODE) {
                // we only add to the list of elements if we haven't seen it before
                const char *element_name = (const char *) cur_node->name;
                if (!OmexMetaUtils::stringInVector(getElementNames(), element_name)) {
                    element_names_.emplace_back(element_name);
                }
            }
            collectElementNames(cur_node->children);
        }
    }


    bool MarkupIdentifier::isSBML() {
        std::vector<std::string> sbml_hallmarks = {
                "listOfCompartments",
                "listOfSpecies",
                "listOfReactions",
                "listOfProducts",
                "sbml",
        };
        bool is_sbml = false;
        // Note: previously this was configured so that if *all* sbml_hallmarks in element_names_ we have sbml.
        // This doesn't work because you can have valid sbml without all these elements.
        // Therefore, if any sbml_hallmarks in element_names_ we have sbml.
        for (const auto& element : getElementNames()){
            is_sbml = std::any_of(sbml_hallmarks.begin(), sbml_hallmarks.end(),
                                  [element](const std::string & s) {return s == element;});
            // if we find 1 match, we do not continue
            if (is_sbml)
                break;
        }
        return is_sbml;
    }

    bool MarkupIdentifier::isCellML() {
        // note: do not include "model" in this list as it causes sbml and cellml to not
        // be distinguished correctly (its compensated by the other hallmarks anyway).
        std::vector<std::string> cellml_hallmarks = {
                "component",
                "variable",
        };
        bool is_cellml = false;

        for (const auto& element : getElementNames()){
            is_cellml = std::any_of(cellml_hallmarks.begin(), cellml_hallmarks.end(),
                                  [element](const std::string & s) {return s == element;});
            // if we find 1 match, we do not continue
            if (is_cellml)
                break;
        }
        return is_cellml;
    }


    const std::vector<std::string> &MarkupIdentifier::getElementNames() const {
        return element_names_;
    }


}