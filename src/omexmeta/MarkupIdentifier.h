//
// Created by Ciaran on 10/08/2020.
//

#ifndef LIBOMEXMETA_MARKUPIDENTIFIER_H
#define LIBOMEXMETA_MARKUPIDENTIFIER_H

#include <iostream>
#include <vector>
#include <algorithm>

#include "libxml/tree.h"
#include "libxml/parser.h"

#include "omexmeta/Error.h"

namespace omexmeta {
    /*
     * @brief determines whether input language is sbml, cellml or unknown
     */
    class MarkupIdentifier {
    private:
        xmlDocPtr doc_; /* the resulting document tree */

        std::string markup_; /* store the input string */
    public:
        const std::vector<std::string> &getElementNames() const;

    private:
        std::vector<std::string> element_names_;

        bool checkStringInElementVec(const std::string& element_name);

        xmlDoc * parseML();


        void collectElementNames(xmlNode *a_node);

    public:
        explicit MarkupIdentifier(std::string markup);

        ~MarkupIdentifier();

        bool isSBML();

        bool isCellML();

    };
}

#endif //LIBOMEXMETA_MARKUPIDENTIFIER_H
