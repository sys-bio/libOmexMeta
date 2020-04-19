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
    /*
     * In the current implementation, Triple objects
     * cannot be copied because of the use of unique_ptr
     * in Predicate. I'm following the best practices that I know
     * here, in using a unique_ptr over shared_ptr but the consequence
     * is that we cannot (For example) construct a std::vector using
     * initializer lists i.e.:
     *      std::vector<Triple> triple = {triple1, triple2}
     * but instead must do
     *      std::vector<Triple> triple = {std::move(triple1), std::move(triple2)}
     * or
     *      std::vector<Triple> triple;
     *      triple.emplace_back(<triple args>); //or
     *      triple.push_back(std::move(triple2));
     *
     * I wouldn't want users of this library to have to contend with this
     * but its okay if its only used internally. A decision for future.
     *
     */
    class Triple {
        librdf_world *world_;
        Subject subject_;
        PredicatePtr predicate_ptr_;
        Resource resource_;
    public:

        Triple(librdf_world *world, Subject subject, PredicatePtr predicate_ptr, Resource resource);

        Triple(librdf_world *world, Subject subject, Predicate predicate, Resource resource);

        Subject getSubject() const;

        PredicatePtr getPredicatePtr() const;

        Resource getResource() const;

        librdf_statement *toStatement();

        librdf_world *getWorld() const;

    };

    typedef std::vector<std::vector<Triple>> TripleList;
}

#endif //LIBSEMGEN_TRIPLE_H
