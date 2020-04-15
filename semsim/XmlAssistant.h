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
        std::string xml_;
        std::string metaid_base;
        int metaid_num_digits_;

        void addMetaIdsRecursion(xmlNode *a_node, std::vector<std::string> &seen_metaids);

        void generateMetaId(std::vector<std::string> &seen_metaids, long count, MetaID metaid_gen, std::string &id);

        std::vector<std::string> valid_elements_{"Any"};

    public:

        explicit XmlAssistant(std::string xml, std::string base = "MetaID", int metaid_num_digits = 4);

        std::string addMetaIds();

        virtual const std::vector<std::string> &getValidElements() const;
    };


    class SBMLAssistant : public XmlAssistant {
    protected:
        std::vector<std::string> valid_elements_ = {
                "model",
                "unit",
                "compartment",
                "species",
                "reaction",
                "kineticLaw",
                "localParameter",
        };
    public:
        using XmlAssistant::XmlAssistant;

        const std::vector<std::string> &getValidElements() const override;


    };


    class CellMLAssistant : public XmlAssistant {
        std::vector<std::string> valid_elements_ = {
                "model",
                "unit",
                "compartment",
                "species",
                "reaction",
                "kineticLaw",
                "localParameter",
        };
    public:
        using XmlAssistant::XmlAssistant;

        const std::vector<std::string> &getValidElements() const override;

    };

    typedef std::unique_ptr<XmlAssistant> XmlAssistantPtr;


}
#endif //LIBSEMGEN_XMLASSISTANT_H
