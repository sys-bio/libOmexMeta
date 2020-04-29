//
// Created by Ciaran on 4/4/2020.
//

#ifndef LIBSEMGEN_TRIPLE_H
#define LIBSEMGEN_TRIPLE_H

#include <ostream>
#include "librdf.h"
#include "semsim/Subject.h"
#include "semsim/Predicate.h"
#include "semsim/Resource.h"


namespace semsim {
    class Triple {
    protected:
        librdf_world *world_;
    private:
        Subject subject_;
        PredicatePtr predicate_ptr_;
        Resource resource_;
    public:

        Triple(librdf_world *world, Subject subject, PredicatePtr predicate_ptr, Resource resource);

        Triple(librdf_world *world, Subject subject, const Predicate& predicate, Resource resource);

        Subject getSubject() const;

        PredicatePtr getPredicatePtr() const;

        Resource getResource() const;

        librdf_statement *toStatement();

        static Triple fromStatement(librdf_world *world, librdf_statement* statement);

    };

}

#endif //LIBSEMGEN_TRIPLE_H
