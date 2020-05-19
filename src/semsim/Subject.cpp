//
// Created by Ciaran on 4/4/2020.
//

#include "semsim/Subject.h"


namespace semsim {

    Subject::Subject(const RDFURINode &node)
            : rdf_node_ptr_(std::make_shared<RDFURINode>(node)) {
    }

    Subject::Subject(const RDFBlankNode &node)
            : rdf_node_ptr_(std::make_shared<RDFBlankNode>(node)) {
    }

    Subject::Subject(const RDFNode &node)
            : rdf_node_ptr_(std::make_shared<RDFNode>(node)) {
    }

    Subject Subject::uri(LibrdfWorld world, const std::string &uri) {
        LibrdfNode node = world.newNodeUriString(uri);
        return Subject(RDFURINode(node));
    }

    Subject Subject::blank(LibrdfWorld world, const std::string &blank) {
        LibrdfNode node = world.newNodeBlank(blank);
        return Subject(RDFBlankNode(node));
    }


    LibrdfNode Subject::getNode() const {
        LibrdfNode node = rdf_node_ptr_->getNode();
        if (!node) {
            throw NullPointerException("Subject::ToRdfNode(): node object nullptr");
        }
        return node;
    }

    std::string Subject::str() const {
        return rdf_node_ptr_->str();
    }

    Subject::~Subject() = default;


}