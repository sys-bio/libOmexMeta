//
// Created by Ciaran on 4/4/2020.
//

#include "Triple.h"


namespace semsim {

    Triple::Triple(LibrdfWorld world)
            : world_(world) {

    }

    Triple::Triple(LibrdfWorld world, Subject subject, PredicatePtr predicate_ptr, Resource resource) :
            world_(world),
            subject_(std::move(subject)),
            predicate_ptr_(std::move(predicate_ptr)),
            resource_(std::move(resource)) {}


    Triple::Triple(LibrdfWorld world, Subject subject, const Predicate &predicate, Resource resource) :
            world_(world),
            subject_(std::move(subject)),
            predicate_ptr_(std::make_shared<Predicate>(predicate)),
            resource_(std::move(resource)) {}

    Subject Triple::getSubject() const {
        return subject_;
    }

    PredicatePtr Triple::getPredicatePtr() const {
        return predicate_ptr_;
    }

    Resource Triple::getResource() const {
        return resource_;
    }

    LibrdfStatement Triple::toStatement() {

        librdf_statement *stmt = librdf_new_statement_from_nodes(
                *world_.getWorld(),
                *subject_.getNode().getNode(),
                *predicate_ptr_->getNode().getNode(),
                *resource_.getNode().getNode()
        );
        return LibrdfStatement(stmt);
    }

    Triple Triple::fromStatement(LibrdfWorld world, LibrdfStatement statement) {
        librdf_statement *&statement_raw = *statement.getStatement();
        Subject subject(world, RDFURINode(world.newNodeUriString((const char *) statement_raw->subject)));
        PredicatePtr predicatePtr = std::make_shared<Predicate>(
                Predicate(world, world.newNodeUriString((const char *) statement_raw->predicate))
        );
        Resource resource(world, RDFURINode(world.newNodeUriString((const char *) statement_raw->object)));
        return Triple(world, subject, predicatePtr, resource);
    }

    std::string Triple::str(std::string format, std::string base) {
        return TripleWriter(*this, base, format).toString();
    }

    void Triple::setSubject(const Subject &subject) {
        subject_ = subject;
    }

    void Triple::setPredicatePtr(const PredicatePtr &predicatePtr) {
        predicate_ptr_ = predicatePtr;
    }

    void Triple::setResource(const Resource &resource) {
        resource_ = resource;
    }

    semsim::Triple &semsim::Triple::setAbout(const std::string &about) {
        subject_ = Subject(world_, RDFURINode(world_.newNodeUriString(about)));
        return (*this);
    }

    std::string semsim::Triple::getAbout() const {
        return getSubject().str();
    }

    semsim::Triple &
    semsim::Triple::setPredicate(const std::string &namespace_, const std::string &term) {
        predicate_ptr_ = semsim::PredicateFactory(world_, namespace_, term);
        return *this;
    }


    semsim::Triple &
    semsim::Triple::setPredicateNew(const std::string &namespace_, const std::string &term, const std::string &prefix) {
        setPredicatePtr(std::make_shared<Predicate>(semsim::Predicate(world_, namespace_, term, prefix)));
        return *this;
    }

    semsim::Triple &semsim::Triple::setResourceLiteral(const std::string &literal) {
        resource_ = Resource(world_, RDFLiteralNode(world_.newNodeLiteral(literal)));
        return *this;
    }

    semsim::Triple &semsim::Triple::setResourceUri(const std::string &identifiers_uri) {
        resource_ = Resource(world_, RDFURINode(world_.newNodeUriString(identifiers_uri)));
        return *this;
    }

    semsim::Triple &semsim::Triple::setResourceBlank(const std::string &blank_id) {
        resource_ = Resource(world_, RDFBlankNode(world_.newNodeBlank(blank_id)));
        return *this;
    }

}

