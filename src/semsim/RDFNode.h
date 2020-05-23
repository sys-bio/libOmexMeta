//
// Created by Ciaran on 4/17/2020.
//

#ifndef LIBSEMSIM_RDFNODE_H
#define LIBSEMSIM_RDFNODE_H

#include <string>
#include <librdf.h>
#include <memory>
#include "librdf.h"
#include <regex>
#include <utility>

#include "semsim/RedlandAPIWrapper/LibrdfNode.h"
#include "semsim/RedlandAPIWrapper/LibrdfWorld.h"

namespace semsim {

    class RDFNode {
    protected:
        LibrdfNode node_;

    public:
        const LibrdfNode &getNode() const;

        explicit RDFNode(LibrdfNode node);

        virtual std::string str();

        ~RDFNode();

        static std::shared_ptr<RDFNode> fromRDFNode(LibrdfWorld world, LibrdfNode node);
    };

    class RDFLiteralNode : public RDFNode {

    public:

        explicit RDFLiteralNode(const LibrdfNode &node);

        std::string str() override;
    };

    class RDFTypedLiteralNode : public RDFNode {

    public:

        explicit RDFTypedLiteralNode(LibrdfNode node);

        std::string getType();

        std::string str() override;
    };

    class RDFURINode : public RDFNode {
    public:

        explicit RDFURINode(LibrdfNode node);

        std::string str() override;
    };

    class RDFBlankNode : public RDFNode {
    public:

        explicit RDFBlankNode(LibrdfNode node);

        std::string str() override;
    };

    typedef std::shared_ptr<RDFNode> RDFNodePtr;

}

#endif //LIBSEMSIM_RDFNODE_H
