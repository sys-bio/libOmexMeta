//
// Created by Ciaran on 4/4/2020.
//

#include "Resource.h"

namespace semsim {

    Resource::Resource(LibrdfWorld world, const RDFLiteralNode &node) :
            world_(world){
        this->rdf_node_ptr_ = std::make_shared<RDFLiteralNode>(node);
    }

    Resource::Resource(LibrdfWorld world, const RDFURINode &node) :
            world_(world) {
        this->rdf_node_ptr_ = std::make_shared<RDFURINode>(node);
    }

    Resource::Resource(LibrdfWorld world, const RDFBlankNode &node) :
            world_(world) {
        this->rdf_node_ptr_ = std::make_shared<RDFBlankNode>(node);
    }

    LibrdfNode Resource::getNode() const {
        return rdf_node_ptr_->getNode();
    }

    std::string Resource::str() const {
        return rdf_node_ptr_->str();
    }

    Resource::Resource(LibrdfWorld world, LibrdfNode node)
            : world_(world),
              rdf_node_ptr_(RDFNode::fromRDFNode(world, node)) {
    }

    bool Resource::isSet() const {
        if (rdf_node_ptr_) {
            return true;
        }
        return false;
    }

}






