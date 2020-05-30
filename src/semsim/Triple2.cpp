//
// Created by Ciaran on 4/4/2020.
//

#include "Triple2.h"


namespace semsim {

    Triple2::Triple2(const Subject& subject, const PredicatePtr& predicate_ptr, const Resource& resource)
            : LibrdfStatement(subject.getNode(),
                      predicate_ptr->getNode(),
                      resource.getNode()){
    }
    Triple2::Triple2(const Subject& subject, const Predicate& predicate,const Resource& resource)
            : LibrdfStatement(subject.getNode(),
                      predicate.getNode(),
                      resource.getNode()){

    }

//    std::string Triple2::str(std::string format, std::string base) {
//        return Triple2Writer(*this, base, format).toString();
//    }

//    semsim::Triple2 &semsim::Triple2::setAbout(const std::string &about) {
//        subject_ = subject_.
//                std::move(Subject(LibrdfNode::fromUriString(about)));
//        return (*this);
//    }
//
//    std::string semsim::Triple2::getAbout() const {
//        return getSubject().str();
//    }

//    semsim::Triple2 &
//    semsim::Triple2::setPredicate(const std::string &namespace_, const std::string &term) {
//        predicate_ptr_ = semsim::PredicateFactory(world_, namespace_, term);
//        return *this;
//    }
//
//
//    semsim::Triple2 &
//    semsim::Triple2::setPredicateNew(const std::string &namespace_, const std::string &term, const std::string &prefix) {
//        setPredicatePtr(std::make_unique<Predicate>(semsim::Predicate(world_, namespace_, term, prefix)));
//        return *this;
//    }
//
//    semsim::Triple2 &semsim::Triple2::setResourceLiteral(const std::string &literal) {
//        resource_ = Resource(world_, RDFLiteralNode(world_.newNodeLiteral(literal)));
//        return *this;
//    }
//
//    semsim::Triple2 &semsim::Triple2::setResourceUri(const std::string &identifiers_uri) {
//        resource_ = Resource(world_, RDFURINode(world_.newNodeUriString(identifiers_uri)));
//        return *this;
//    }
//
//    semsim::Triple2 &semsim::Triple2::setResourceBlank(const std::string &blank_id) {
//        resource_ = Resource(world_, RDFBlankNode(world_.newNodeBlank(blank_id)));
//        return *this;
//    }
//
//}
//
}