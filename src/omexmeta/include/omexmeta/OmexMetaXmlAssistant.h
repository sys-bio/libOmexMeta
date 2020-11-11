//
// Created by Ciaran on 4/14/2020.
//

#ifndef LIBOMEXMETA_OMEXMETAXMLASSISTANT_H
#define LIBOMEXMETA_OMEXMETAXMLASSISTANT_H


#include <libxml/parser.h>
#include <libxml/tree.h>

#include "omexmeta/MetaID.h"
#include "omexmeta/OmexMetaUtils.h"
#include "omexmeta/OmexMetaXmlType.h"

#include <iostream>
#include <memory>
#include <utility>
#include <vector>

namespace omexmeta {

    class OmexMetaXmlAssistant {
        std::string xml_;
        std::string metaid_base_;
        int metaid_num_digits_;
        bool generate_new_metaids_;

        void addMetaIdsRecursion(xmlDocPtr doc, xmlNode *a_node, std::vector<std::string> &seen_metaids);

        void generateMetaId(
                std::vector<std::string> &seen_metaids, long count,
                const MetaID &metaid_gen, std::string &id);

    public:

        /**
         * @brief get the base for the metaid used by the current xml type.
         * This base is used as a precursor string for generating new metaids
         * if requested by the user by setting generate_new_metaids=true.
         * @details the base is given as argument to the OmexMetaXmlAssistant on
         * instantiation. If base is "metaid" then ids generated will be metaid_0000
         */
        [[maybe_unused]] const std::string &getMetaidBase() const;

        int getMetaidNumDigits() const;

        [[nodiscard]] bool generateNewMetaids() const;

        explicit OmexMetaXmlAssistant(std::string xml, std::string metaid_base = "MetaID", int metaid_num_digits = 4, bool generate_new_metaids = false);

        std::pair<std::string, std::vector<std::string>> addMetaIds();

        [[nodiscard]] virtual std::vector<std::string> getValidElements() const;

        [[nodiscard]] virtual std::string metaIdTagName() const;

        [[nodiscard]] virtual std::string metaIdNamespace() const;
    };


    class SBMLAssistant : public OmexMetaXmlAssistant {

    public:
        std::vector<std::string> getValidElements() const override;

        using OmexMetaXmlAssistant::OmexMetaXmlAssistant;

        std::string metaIdTagName() const override;

        [[nodiscard]] std::string metaIdNamespace() const override;
    };


    class CellMLAssistant : public OmexMetaXmlAssistant {
    public:
        using OmexMetaXmlAssistant::OmexMetaXmlAssistant;

        std::vector<std::string> getValidElements() const override;

        std::string metaIdTagName() const override;

        [[nodiscard]] std::string metaIdNamespace() const override;
    };

    typedef std::unique_ptr<OmexMetaXmlAssistant> XmlAssistantPtr;

    class OmexMetaXmlAssistantFactory {
    public:
        static XmlAssistantPtr generate(const std::string &xml, OmexMetaXmlType type, bool generate_new_metaids = false, std::string metaid_base = "#OmexMetaId", int metaid_num_digits = 4);
    };
}// namespace omexmeta
#endif//LIBOMEXMETA_OMEXMETAXMLASSISTANT_H
