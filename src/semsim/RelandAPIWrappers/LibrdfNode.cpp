//
// Created by Ciaran on 5/17/2020.
//

#include "LibrdfNode.h"

namespace semsim {

    LibrdfNode::LibrdfNode(librdf_node *node) :
            node_(std::make_shared<librdf_node *>(node)) {

    }
}