//
// Created by Ciaran on 4/17/2020.
//

#ifndef LIBSEMSIM__RDFNODE_H
#define LIBSEMSIM__RDFNODE_H

#include <string>
#include <librdf.h>
#include <memory>
#include "librdf.h"
#include <regex>
#include <utility>

#include "LibrdfNode.h"
#include "World.h"

/*
 * This file is no longer in use as it has been replaced by
 * LibrdfNode
 */
using namespace redland;

namespace semsim {

    class _RDFNode {
    protected:
        LibrdfNode node_;

    public:
        [[nodiscard]] const LibrdfNode &getNode() const;

        explicit _RDFNode(LibrdfNode node);

        virtual std::string str();

        ~_RDFNode();

        static std::unique_ptr<_RDFNode> fromRDFNode(LibrdfNode node);
    };

    class RDFLiteralNode : public _RDFNode {

    public:

        explicit RDFLiteralNode(const LibrdfNode &node);

        std::string str() override;
    };

    class RDFTypedLiteralNode : public _RDFNode {

    public:

        explicit RDFTypedLiteralNode(LibrdfNode node);

        std::string getType();

        [[maybe_unused]] std::string getLanguage();

        std::string str() override;
    };

    class RDFURINode : public _RDFNode {
    public:

        explicit RDFURINode(LibrdfNode node);

        std::string str() override;

        [[nodiscard]] LibrdfUri getUri() const;
    };

    class RDFBlankNode : public _RDFNode {
    public:

        explicit RDFBlankNode(LibrdfNode node);

        std::string str() override;

        [[nodiscard]] std::string getBlankIdentifier() const;
    };

}

#endif //LIBSEMSIM__RDFNODE_H
