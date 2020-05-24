//
// Created by Ciaran on 4/4/2020.
//

#include "semsim/Subject.h"


namespace semsim {

    Subject::Subject(LibrdfNode node)
            : node_(std::move(node)) {
    }

    Subject Subject::fromUri(const std::string &uri) {
        return Subject(LibrdfNode::fromUriString(uri));
    }

    Subject Subject::fromBlank(const std::string &blank) {
        return Subject(LibrdfNode::fromBlank(blank));
    }

    std::string Subject::str() const {
        return node_.str();
    }

    bool Subject::isSet() const {
        return !node_.get();
    }

    const LibrdfNode &Subject::getNode() const {
        return node_;
    }

    semsim::Subject::~Subject() = default;


}