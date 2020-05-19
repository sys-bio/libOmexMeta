//
// Created by Ciaran on 4/4/2020.
//

#include "semsim/Subject.h"

#include <utility>
#include "semsim/Error.h"

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