//
// Created by Ciaran on 4/4/2020.
//

#include "Triple.h"


namespace semsim {

    Triple::Triple(Subject subject, PredicatePtr predicate_ptr, Resource resource)
            : subject_(std::move(subject)),
              predicate_ptr_(std::move(predicate_ptr)),
              resource_(std::move(resource)) {
        checkForNull();
    }

    Triple::Triple(Subject subject, Predicate predicate, Resource resource)
            : subject_(std::move(subject)),
              predicate_ptr_(std::make_unique<Predicate>(std::move(predicate))),
              resource_(std::move(resource)) {
        checkForNull();
    }

    void Triple::checkForNull() {
        if (!subject_.getNode().get())
            throw NullPointerException("NullPointerException: Triple::Triple(): Subject node is null");

        if (!predicate_ptr_) //todo another check on underlying pointer if possible (so far checking for null causes seg fault)
            throw NullPointerException("NullPointerException: Triple::Triple(): Predicate node is null");

        if (!resource_.getNode().get())
            throw NullPointerException("NullPointerException: Triple::Triple(): Resource node is null");
    }

    LibrdfStatement Triple::toStatement() {
        librdf_node *s = subject_.getNode().get();
        if (!s)
            throw NullPointerException("NullPointerException: Triple::toStatement(): Subject node is null");
        librdf_node *p = predicate_ptr_->getNode().get();
        if (!p)
            throw NullPointerException("NullPointerException: Triple::toStatement(): Subject node is null");
        librdf_node *r = resource_.getNode().get();
        if (!r)
            throw NullPointerException("NullPointerException: Triple::toStatement(): Subject node is null");

        librdf_statement *stmt = librdf_new_statement_from_nodes(
                World::getWorld(), s, p, r
        );
        return LibrdfStatement(stmt);
    }

    Triple Triple::fromStatement(LibrdfStatement statement) {
        Subject subject(LibrdfNode::fromUriString((const char *) statement.get()->subject));
        PredicatePtr predicatePtr = std::make_unique<Predicate>(
                Predicate(LibrdfNode::fromUriString((const char *) statement.get()->predicate))
        );
        Resource resource(LibrdfNode::fromUriString((const char *) statement.get()->object));
        return Triple(std::move(subject), std::move(predicatePtr), std::move(resource));
    }

    std::string Triple::getSubjectStr() const {
        return subject_.str();
    }

    std::string Triple::getPredicateStr() const {
        return predicate_ptr_->str();
    }

    std::string Triple::getResourceStr() const {
        return resource_.str();
    }

//    std::string Triple::str(std::string format, std::string base) {
//        return TripleWriter(*this, base, format).toString();
//    }

//    void Triple::setSubject(const Subject &subject) {
//        subject_ = std::move(subject);
//    }
//
//    void Triple::setPredicatePtr(const PredicatePtr &predicatePtr) {
//        predicate_ptr_ = std::move(predicatePtr);
//    }
////
//    void Triple::setResource(const Resource &resource) {
//        resource_ = resource;
//    }

//    semsim::Triple &semsim::Triple::setAbout(const std::string &about) {
//        subject_ = std::move(Subject(LibrdfNode::fromUriString(about)));
//        return (*this);
//    }
//
//    std::string semsim::Triple::getAbout() const {
//        return getSubject().str();
//    }
//
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

}