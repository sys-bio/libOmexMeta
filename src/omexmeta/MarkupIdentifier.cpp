//
// Created by Ciaran on 10/08/2020.
//

#include "MarkupIdentifier.h"

#include <utility>

namespace omexmeta {

    MarkupIdentifier::MarkupIdentifier(std::string markup) : markup_(std::move(markup)) {
        doc_ = parseML();

    }

    MarkupIdentifier::~MarkupIdentifier() {
        xmlFreeDoc(doc_);
    }


    /*
     * @brief utility to check whether a string is in the elements_names_ vector
     * @param element_name the string to check for existence in element_names_
     */
    bool MarkupIdentifier::checkStringInElementVec(const std::string &element_name) {
        bool in_vec = false;
        if (std::find(element_names_.begin(), element_names_.end(), element_name) != element_names_.end()) {
            // Element in vector.
            in_vec = true;
        }
        return in_vec;
    }

    /*
     * @brief read an xml document using libxml2.
     */
    xmlDoc *MarkupIdentifier::parseML() {
        /*
         * The document being in memory, it have no base per RFC 2396,
         * and the "noname.xml" argument will serve as its base.
         */
        doc_ = xmlReadMemory(markup_.c_str(), (int) markup_.length() + 1, "noname.xml", NULL, 0);
        if (doc_ == nullptr) {
            throw NullPointerException("Could not read xml into document. nullptr");
        }

        // also populate elements vector
        xmlNode *root_element = xmlDocGetRootElement(doc_);
        collectElementNames(root_element);

        return doc_;
    }

    /*
     * @brief collect the name of the element pointed to by a_node
     * @brief *a_node pointer to an xmlNode
     */
    void MarkupIdentifier::collectElementNames(xmlNode *a_node) {
        for (xmlNode *cur_node = a_node; cur_node; cur_node = cur_node->next) {
            if (cur_node->type == XML_ELEMENT_NODE) {
                // we only add to the list of elements if we haven't seen it before
                const char *element_name = (const char *) cur_node->name;
                if (!checkStringInElementVec(element_name)) {
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
        for (auto &it: getElementNames()){
            std::cout<< it << std::endl;
        }
        for (auto &hallmark: sbml_hallmarks) {
            if (!checkStringInElementVec(hallmark)){
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
            if (!checkStringInElementVec(hallmark)){
                is_cellml = false;
            }
        }
        return is_cellml;
    }


    const std::vector<std::string> &MarkupIdentifier::getElementNames() const {
        return element_names_;
    }


}