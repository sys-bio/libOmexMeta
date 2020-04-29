//
// Created by Ciaran on 4/4/2020.
//

#include <utility>
#include <algorithm>
#include <cstring>
#include "raptor2.h"
#include "librdf.h"
#include "Triple.h"

//'todo Conceptually, could we use an isa relationshop between singular annotation and Triple?

namespace semsim {

    Triple::Triple(librdf_world *world, Subject subject, PredicatePtr predicate_ptr, Resource resource) :
            world_(world),
            subject_(std::move(subject)),
            predicate_ptr_(std::move(predicate_ptr)),
            resource_(std::move(resource)) {}


    Triple::Triple(librdf_world *world, Subject subject, const Predicate& predicate, Resource resource) :
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


}

