//
// Created by Ciaran on 11/08/2020.
//

#include "omexmeta/ElementExtractor.h"

namespace omexmeta {

    ElementExtractor::ElementExtractor(const std::string &markup, const std::string &element)
            : markup_(markup), element_(element) {
        doc_ = OmexMetaUtils::parseXmlDocument(markup_);
        xmlNode *root = xmlDocGetRootElement(doc_);
        collectElements(root); /* populates elements */
    }

    ElementExtractor::~ElementExtractor() {
        xmlFreeDoc(doc_);
    }

    /*
     * @brief collect the name of the element pointed to by a_node
     * @brief *a_node pointer to an xmlNode
     */
    void ElementExtractor::collectElements(xmlNode *a_node) {
        for (xmlNode *cur_node = a_node; cur_node; cur_node = cur_node->next) {
            if (cur_node->type == XML_ELEMENT_NODE) {
                // we only add to the list of elements if we haven't seen it before
                std::string element_name = (const char *) cur_node->name;
                if (element_name == element_) {
                    elements_.push_back(cur_node);
                }
            }
            collectElements(cur_node->children);
        }
    }

    const std::vector<xmlNode *> &ElementExtractor::getElements() const {
        return elements_;
    }


}