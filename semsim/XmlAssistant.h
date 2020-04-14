//
// Created by Ciaran on 4/14/2020.
//

#ifndef LIBSEMGEN_XMLASSISTANT_H
#define LIBSEMGEN_XMLASSISTANT_H


#include <vector>
#include "iostream"
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "semsim/SemSim.h"

namespace semsim {

    class XmlAssistant {
        std::vector<std::string> valid_elements_{"Any"};
        std::string xml_;
        std::string metaid_base;
        int metaid_num_digits_;

        const std::vector<std::string> &getValidElements() const;

    public:
        static void addMetaIdsRecursion(xmlNode *a_node, std::vector<std::string> &seen_metaids);

        static void
        generateMetaId(std::vector<std::string> &seen_metaids, long count, MetaID metaid_gen, std::string &id);

        explicit XmlAssistant(std::string xml, std::string base = "MetaID", int metaid_num_digits = 4);

        std::string addMetaIds();
    };


}
#endif //LIBSEMGEN_XMLASSISTANT_H
