//
// Created by Ciaran on 4/14/2020.
//

#ifndef LIBOMEXMETA_OMEXMETAXML_H
#define LIBOMEXMETA_OMEXMETAXML_H


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

    /**
     * @brief Construct for handling xml
     *
     * todo this design works but is a little clunky. A better design
     * would be literally have an XML class, with a type enum to determine
     * SBML, CellML or other and then the functions performed by this
     * class would just be methods of the xml.
     */
    class OmexMetaXml {
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

        explicit OmexMetaXml(std::string xml, std::string metaid_base = "MetaID", int metaid_num_digits = 4, bool generate_new_metaids = false);

        std::pair<std::string, std::vector<std::string>> addMetaIds();

        [[nodiscard]] virtual std::vector<std::string> getValidElements() const;

        [[nodiscard]] virtual std::string metaIdTagName() const;

        [[nodiscard]] virtual std::string metaIdNamespace() const;

        /**
         * @brief returns a copy of the xml with all elemenents
         * named @param elementName removed from the document.
         */
        std::string removeElement(const std::string &elementName);

        /**
         * @brief write the current document to string
         */
        std::string toString();

        /**
         * @brief get the model elements metaid
         * @details the model element is often a child of the sbml or cellml element
         */
         virtual std::string getDefaultModelMetaid() = 0;

    private:
        /**
         * xml document tree
         */
        xmlDocPtr doc;

        /**
         * Parse xml into libxml2. If @param xml provided,
         * use this xml, otherwise use private member variable xml_
         *
         */
        xmlDocPtr parseDoc(const std::string &xml = std::string());

        void addMetaIdsRecursion(xmlDocPtr doc, xmlNode *a_node, std::vector<std::string> &seen_metaids);

        void generateMetaId(
                std::vector<std::string> &seen_metaids, long count,
                const MetaID &metaid_gen, std::string &id);

        std::string xml_;
        std::string metaid_base_;
        int metaid_num_digits_;
        bool generate_new_metaids_;
    };


    class OmexMetaSBML : public OmexMetaXml {

    public:
        [[nodiscard]] std::vector<std::string> getValidElements() const override;

        using OmexMetaXml::OmexMetaXml;

        [[nodiscard]] std::string metaIdTagName() const override;

        [[nodiscard]] std::string metaIdNamespace() const override;

        std::string getDefaultModelMetaid() override;
    };


    class OmexMetaCellML : public OmexMetaXml {
    public:
        using OmexMetaXml::OmexMetaXml;

        std::vector<std::string> getValidElements() const override;

        std::string metaIdTagName() const override;

        [[nodiscard]] std::string metaIdNamespace() const override;

        std::string getDefaultModelMetaid() override;
    };

    typedef std::unique_ptr<OmexMetaXml> OmexMetaXmlPtr;

    class OmexMetaXmlAssistantFactory {
    public:
        static OmexMetaXmlPtr generate(const std::string &xml, OmexMetaXmlType type, bool generate_new_metaids = false, std::string metaid_base = "#OmexMetaId", int metaid_num_digits = 4);
    };
}// namespace omexmeta
#endif//LIBOMEXMETA_OMEXMETAXML_H
