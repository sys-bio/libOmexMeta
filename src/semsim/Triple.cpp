//
// Created by Ciaran on 4/4/2020.
//

#include "Triple.h"


namespace semsim {

    Triple::Triple(const Subject& subject, const PredicatePtr& predicate_ptr, const Resource& resource)
            : LibrdfStatement(subject.getNode(),
                      predicate_ptr->getNode(),
                      resource.getNode()){
    }

    Triple::Triple(librdf_node* subject, librdf_node* predicate, librdf_node* resource):
        LibrdfStatement(subject, predicate, resource){}

    Triple Triple::fromRawStatementPtr(librdf_statement *statement) {
        return Triple(statement);
    }

    Triple::Triple(librdf_statement *statement) : LibrdfStatement(statement) {}

//    std::string Triple::str(std::string format, std::string base) {
//        return Triple2Writer(*this, base, format).toString();
//    }

//    semsim::Triple &semsim::Triple::setAbout(const std::string &about) {
//        subject_ = subject_.
//                std::move(Subject(LibrdfNode::fromUriString(about)));
//        return (*this);
//    }
//
//    std::string semsim::Triple::getAbout() const {
//        return getSubject().str();
//    }

//    semsim::Triple &
//    semsim::Triple::setPredicate(const std::string &namespace_, const std::string &term) {
//        predicate_ptr_ = semsim::PredicateFactory(world_, namespace_, term);
//        return *this;
//    }
//
//
//    semsim::Triple &
//    semsim::Triple::setPredicateNew(const std::string &namespace_, const std::string &term, const std::string &prefix) {
//        setPredicatePtr(std::make_unique<Predicate>(semsim::Predicate(world_, namespace_, term, prefix)));
//        return *this;
//    }
//
//    semsim::Triple &semsim::Triple::setResourceLiteral(const std::string &literal) {
//        resource_ = Resource(world_, RDFLiteralNode(world_.newNodeLiteral(literal)));
//        return *this;
//    }
//
//    semsim::Triple &semsim::Triple::setResourceUri(const std::string &identifiers_uri) {
//        resource_ = Resource(world_, RDFURINode(world_.newNodeUriString(identifiers_uri)));
//        return *this;
//    }
//
//    semsim::Triple &semsim::Triple::setResourceBlank(const std::string &blank_id) {
//        resource_ = Resource(world_, RDFBlankNode(world_.newNodeBlank(blank_id)));
//        return *this;
//    }
//
//}
//
}