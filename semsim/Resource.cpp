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
    Resource::Resource(librdf_world *world, const RDFURINode& node) :
        world_(world){
        this->rdf_node_ptr_ = std::make_shared<RDFURINode>(node);
    }
    Resource::Resource(librdf_world *world, const RDFBlankNode& node) :
        world_(world){
        this->rdf_node_ptr_ = std::make_shared<RDFBlankNode>(node);
    }

    std::string Resource::str() {
        return rdf_node_ptr_->str();
    }

    librdf_node *Resource::toRdfNode() {
        return rdf_node_ptr_->toRdfNode();
    }

}






