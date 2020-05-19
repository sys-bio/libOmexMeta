//
// Created by Ciaran on 4/17/2020.
//

#ifndef LIBSEMGEN_RDFNODE_H
#define LIBSEMGEN_RDFNODE_H

#include <string>
#include <librdf.h>
#include <memory>

#include "semsim/RelandAPIWrappers/RedlandAPIWrapper.h"

namespace semsim {

    class RDFNode {
    protected:
        LibrdfWorld world_;
        std::string value_;
        const char *xml_language_;
        bool is_wf_xml_ = false;

    public:

        RDFNode(LibrdfWorld world, std::string value, const char *xml_language, bool is_wf_xml);

        virtual std::string str() = 0;

        virtual LibrdfNode toRdfNode() = 0;

        static std::string getValue(LibrdfNode node);

        static std::shared_ptr<RDFNode> fromRDFNode(LibrdfWorld world, LibrdfNode node);

        ~RDFNode();

    };

    class RDFLiteralNode : public RDFNode {
        bool is_typed_literal = false;
        std::string data_type_uri;

    public:

        RDFLiteralNode(LibrdfWorld world, std::string value,
                       std::string data_type = "http://www.w3.org/2001/XMLSchema#string",
                       const char *xml_language = nullptr, bool is_wf_xml = false);

        RDFLiteralNode(LibrdfWorld world, librdf_node *node,
                       std::string data_type = "http://www.w3.org/2001/XMLSchema#string",
                       const char *xml_language = nullptr, bool is_wf_xml = false);

        std::string str() override;

        LibrdfNode toRdfNode() override;

    };

    class RDFURINode : public RDFNode {
    public:

        explicit RDFURINode(LibrdfWorld world, std::string value, const char *xmlLanguage = nullptr,
                            bool isWfXml = false);

        RDFURINode(LibrdfWorld world, LibrdfNode node, const char *xmlLanguage = nullptr, bool isWfXml = false);

        std::string str() override;

        LibrdfNode toRdfNode() override;

    };

    class RDFBlankNode : public RDFNode {
    public:

        explicit RDFBlankNode(LibrdfWorld world, std::string value, const char *xml_language = nullptr,
                              bool is_wf_xml = false);

        RDFBlankNode(LibrdfWorld world, LibrdfNode node, const char *xmlLanguage = nullptr, bool isWfXml = false);

        std::string str() override;

        LibrdfNode toRdfNode() override;


    };

    typedef std::shared_ptr<RDFNode> RDFNodePtr;

}

#endif //LIBSEMGEN_RDFNODE_H
