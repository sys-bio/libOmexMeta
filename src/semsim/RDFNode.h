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
        LibrdfNode node_;
//        LibrdfWorld world_;
//        std::string value_;
//        const char *xml_language_;
//        bool is_wf_xml_ = false;

    public:
        const LibrdfNode &getNode() const;

        explicit RDFNode(LibrdfNode node);

        virtual std::string str();

        ~RDFNode();

    };

    class RDFLiteralNode : public RDFNode {

    public:

        explicit RDFLiteralNode(const LibrdfNode &node);

    };

    class RDFTypedLiteralNode : public RDFNode {

    public:

        explicit RDFTypedLiteralNode(LibrdfNode node);

        std::string getType();

    };

    class RDFURINode : public RDFNode {
    public:

        explicit RDFURINode(LibrdfNode node);

    };

    class RDFBlankNode : public RDFNode {
    public:

        explicit RDFBlankNode(LibrdfNode node);

    };

    typedef std::shared_ptr<RDFNode> RDFNodePtr;

}

#endif //LIBSEMGEN_RDFNODE_H
