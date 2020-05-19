//
// Created by Ciaran on 4/17/2020.
//

#ifndef LIBSEMGEN_RDFNODE_H
#define LIBSEMGEN_RDFNODE_H

#include <string>
#include <librdf.h>
#include <memory>

#include "semsim/RedlandAPIWrappers/LibrdfNode.h"

namespace semsim {

    class RDFNode {
    protected:
        LibrdfNode node_;

    public:
        const LibrdfNode &getNode() const;

        explicit RDFNode(LibrdfNode node);

        virtual std::string str();

        ~RDFNode();

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

#endif //LIBSEMGEN_RDFNODE_H
