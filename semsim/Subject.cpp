//
// Created by Ciaran on 4/4/2020.
//

#include "semsim/Subject.h"

namespace semsim {

    Subject::Subject(librdf_world *world, const RDFURINode &node)
            : world_(world) {
        this->rdfNodePtr_ = std::make_shared<RDFURINode>(node);
    }

    Subject::Subject(librdf_world *world, const RDFBlankNode &node)
            : world_(world) {
        this->rdfNodePtr_ = std::make_shared<RDFBlankNode>(node);
    }

    librdf_node *Subject::toRdfNode() {
        return rdfNodePtr_->toRdfNode();
    }

    std::string Subject::str() {
        return rdfNodePtr_->str();
    }


}