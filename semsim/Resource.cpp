//
// Created by Ciaran on 4/4/2020.
//

#include "semsim/Resource.h"

#include <utility>
#include <regex>
#include "uri.h"
#include "sstream"
#include "iterator"
#include "SemsimUtils.h"

namespace semsim {

    Resource::Resource(librdf_world *world, const RDFLiteralNode& node) :
        world_(world){
        this->rdf_node_ptr_ = std::make_unique<RDFLiteralNode>(node);
    }
    Resource::Resource(librdf_world *world, const RDFURINode& node) :
        world_(world){
        this->rdf_node_ptr_ = std::make_unique<RDFURINode>(node);
    }
    Resource::Resource(librdf_world *world, const RDFBlankNode& node) :
        world_(world){
        this->rdf_node_ptr_ = std::make_unique<RDFBlankNode>(node);
    }

    std::string Resource::str() {
        return rdf_node_ptr_->str();
    }

    librdf_node *Resource::toRdfNode() {
        return rdf_node_ptr_->toRdfNode();
    }

}






