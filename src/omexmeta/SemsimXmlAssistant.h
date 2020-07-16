//
// Created by Ciaran on 4/14/2020.
//

#ifndef LIBOMEXMETA_SEMSIMXMLASSISTANT_H
#define LIBOMEXMETA_SEMSIMXMLASSISTANT_H


#include <vector>
#include "iostream"
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <memory>
#include "MetaID.h"
#include <utility>
#include "OmexMetaUtils.h"

namespace omexmeta {
    enum SemsimXmlType {
        SEMSIM_TYPE_SBML,
        SEMSIM_TYPE_CELLML,
        SEMSIM_TYPE_OTHER,
    };

    class SemsimXmlAssistant {
        std::string xml_;
        std::string metaid_base_;
        int metaid_num_digits_;
        bool generate_new_metaids_;

        void addMetaIdsRecursion(xmlNode *a_node, std::vector<std::string> &seen_metaids);

        void generateMetaId(
                std::vector<std::string> &seen_metaids, long count,
                const MetaID &metaid_gen, std::string &id);

    public:
        const std::string &getMetaidBase() const;

        int getMetaidNumDigits() const;

        [[nodiscard]] bool generateNewMetaids() const;

        explicit SemsimXmlAssistant(std::string xml, std::string metaid_base = "MetaID", int metaid_num_digits = 4, bool generate_new_metaids = false);

        std::pair<std::string, std::vector<std::string>> addMetaIds();

        [[nodiscard]] virtual std::vector<std::string> getValidElements() const;

        [[nodiscard]] virtual std::string metaIdTagName() const;
    };


    class SBMLAssistant : public SemsimXmlAssistant {

    public:
        std::vector<std::string> getValidElements() const override;

        using SemsimXmlAssistant::SemsimXmlAssistant;

        std::string metaIdTagName() const override;

    };


    class CellMLAssistant : public SemsimXmlAssistant {
    public:
        using SemsimXmlAssistant::SemsimXmlAssistant;

        std::vector<std::string> getValidElements() const override;

        std::string metaIdTagName() const override;

    };

    typedef std::unique_ptr<SemsimXmlAssistant> XmlAssistantPtr;

    class SemsimXmlAssistantFactory {
    public:

        static XmlAssistantPtr generate(const std::string &xml, SemsimXmlType type, bool generate_new_metaids = false, std::string metaid_base = "OmexMetaId", int metaid_num_digits = 4);
    };
}
#endif //LIBOMEXMETA_SEMSIMXMLASSISTANT_H
