//
// Created by Ciaran on 4/4/2020.
//

#include "semsim/Subject.h"


namespace semsim {

    Subject::Subject(librdf_node* node)
            : node_(node) {
    }

    Subject Subject::fromUri(const std::string &uri) {
        return Subject(LibrdfNode::fromUriString(uri));
    }

    Subject Subject::fromBlank(const std::string &blank) {
        return Subject(LibrdfNode::fromBlank(blank));
    }

    std::string Subject::str() const {
        return LibrdfNode::str(node_);
    }

    bool Subject::isSet() const {
        return node_ != nullptr;
    }

    librdf_node* Subject::getNode() const {
        return node_;
    }

    Subject Subject::fromRawPtr(librdf_node* node) {
        return Subject(node);
    }

    void Subject::free() {
        if (node_){
            LibrdfNode::freeNode(node_);
            setNode(nullptr);
        }
        this->~Subject();
    }

    void Subject::setNode(librdf_node *node) {
        node_ = node;
    }

}