//
// Created by Ciaran on 10/08/2020.
//

#include "omexmeta/MarkupIdentifier.h"
#include "omexmeta/logger.h"

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
        bool is_sbml = true;
        // if all sbml_hallmarks in element_names_ we have sbml.
        for (auto &hallmark: sbml_hallmarks) {
            if (!OmexMetaUtils::stringInVector(getElementNames(), hallmark)){
                is_sbml = false;
            }
        }
        return is_sbml;
    }

    bool MarkupIdentifier::isCellML() {
        std::vector<std::string> cellml_hallmarks = {
                "component",
                "variable"
        };
        bool is_cellml = true;
        // if all cellml_hallmarks in element_names_ we have sbml.
        for (auto &hallmark: cellml_hallmarks) {
            if (!OmexMetaUtils::stringInVector(getElementNames(), hallmark)){
                is_cellml = false;
            }
        }
        return is_cellml;
    }


    const std::vector<std::string> &MarkupIdentifier::getElementNames() const {
        return element_names_;
    }


}