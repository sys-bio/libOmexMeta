//
// Created by Ciaran on 11/08/2020.
//

#ifndef LIBOMEXMETA_ELEMENTEXTRACTOR_H
#define LIBOMEXMETA_ELEMENTEXTRACTOR_H

#include <iostream>
#include <vector>
#include <algorithm>

#include "libxml/tree.h"
#include "libxml/parser.h"

#include "omexmeta/Error.h"
#include "omexmeta/OmexMetaUtils.h"

namespace omexmeta {
    /*
     * @brief extract all elements from a document with name and put into a list
     */
    class ElementExtractor {
    private:
        xmlDocPtr doc_; /* the resulting document tree */

        std::string markup_; /* store the input string */
        std::string element_; /* element you want to extract from markup_ */

        std::vector<xmlNode*> elements_; /*vector of xmlNodes containing element your interested in */

        void collectElements(xmlNode *a_node);

    public:
        /*
         * @brief constructor for ElementExtractor
         * @param markup the string containing the sbml document string
         * @param element a string with the sbml element you want to extract
         */
        explicit ElementExtractor(const std::string &markup, const std::string &element);

        ~ElementExtractor();

        /*
         * @brief get xml elements called element_
         */
        [[nodiscard]] const std::vector<xmlNode *> &getElements() const;
    };
}

#endif //LIBOMEXMETA_ELEMENTEXTRACTOR_H
