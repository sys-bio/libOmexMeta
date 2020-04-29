//
// Created by Ciaran on 4/4/2020.
//

#include "semsim/Resource.h"
#include "SemsimUtils.h"

namespace semsim {

    Resource::Resource(librdf_world *world, const RDFLiteralNode& node) :
        world_(world){
        this->rdf_node_ptr_ = std::make_shared<RDFLiteralNode>(node);
    }

    Resource::Resource(librdf_world *world, const RDFURINode &node) :
            world_(world) {
        this->rdf_node_ptr_ = std::make_shared<RDFURINode>(node);
    }

    Resource::Resource(librdf_world *world, const RDFBlankNode &node) :
            world_(world) {
        this->rdf_node_ptr_ = std::make_shared<RDFBlankNode>(node);
    }

    librdf_node *Resource::toRdfNode() const {
        return rdf_node_ptr_->toRdfNode();
    }

    std::string Resource::str() const {
        return rdf_node_ptr_->str();
    }

    Resource::Resource(librdf_world *world, librdf_node *node)
        : world_(world), rdf_node_ptr_(RDFNode::fromRDFNode(world, node)){

    }

}






