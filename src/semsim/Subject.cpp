//
// Created by Ciaran on 4/4/2020.
//

#include "semsim/Subject.h"
#include "semsim/Error.h"

namespace semsim {

    Subject::Subject(LibrdfWorld world, const RDFURINode &node)
            : world_(world) {
        this->rdf_node_ptr_ = std::make_shared<RDFURINode>(node);

    }

    Subject::Subject(LibrdfWorld world, const RDFBlankNode &node)
            : world_(world) {
        this->rdf_node_ptr_ = std::make_shared<RDFBlankNode>(node);
    }

    LibrdfNode Subject::toRdfNode() const {
        LibrdfNode node = rdf_node_ptr_->toRdfNode();
        if (!node) {
            throw NullPointerException("Subject::ToRdfNode(): node object nullptr");
        }
    }

    std::string Subject::str() const {
        return rdf_node_ptr_->str();
    }

    Subject::Subject(LibrdfWorld world, LibrdfNode node)
            : world_(world), rdf_node_ptr_(RDFNode::fromRDFNode(world, node)) {
    }

    Subject::~Subject() = default;

    bool Subject::isSet() const {
        if (rdf_node_ptr_) {
            return true;
        }
        return false;
    }


}