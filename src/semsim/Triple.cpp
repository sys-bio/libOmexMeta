//
// Created by Ciaran on 4/4/2020.
//

#include <utility>
#include <algorithm>
#include <cstring>
#include "raptor2.h"
#include "librdf.h"
#include "Triple.h"
#include "Writer.h"


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

    librdf_statement *Triple::toStatement() {
        return librdf_new_statement_from_nodes(
                world_,
                subject_.toRdfNode(),
                predicate_ptr_->toRdfNode(),
                resource_.toRdfNode()
        );
    }

    Triple Triple::fromStatement(librdf_world* world, librdf_statement *statement) {
        Subject subject(world, statement->subject);
        PredicatePtr predicatePtr = std::make_shared<Predicate>(
                Predicate(world, statement->predicate)
                );
        Resource resource(world, statement->object);

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
        subject_ = Subject(world_, RDFURINode(world_, about));
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
        resource_ = Resource(world_, RDFLiteralNode(world_, literal));
        return *this;
    }

    semsim::Triple &semsim::Triple::setResourceUri(const std::string &identifiers_uri) {
        resource_ = Resource(world_, RDFURINode(world_, identifiers_uri));
        return *this;
    }

    semsim::Triple &semsim::Triple::setResourceBlank(const std::string &blank_id) {
        resource_ = Resource(world_, RDFBlankNode(world_, blank_id));
        return *this;
    }

}

