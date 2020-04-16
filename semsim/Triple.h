//
// Created by Ciaran on 4/4/2020.
//

#ifndef LIBSEMGEN_TRIPLE_H
#define LIBSEMGEN_TRIPLE_H

#include "raptor2.h"
#include <ostream>
#include "Subject.h"
#include "Predicate.h"
#include "Resource.h"
#include "IRDF.h"


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

        Subject subject_;
        PredicatePtr predicate_ptr_;
        Resource resource_;
    public:
        Triple(Subject subject, PredicatePtr predicate_ptr_, Resource resource);

        Triple(Subject subject, const Predicate &predicate, Resource resource);

        Triple() = default;

        Triple(const Triple &other);

        Triple(const Triple &&other) noexcept;

        Triple &operator=(const Triple &triple);

        Triple &operator=(Triple &&triple) noexcept;

        const Subject &getSubject() const;

        const PredicatePtr &getPredicate() const;

        const Resource &getResource() const;

        bool operator==(const Triple &rhs) const;

        bool operator!=(const Triple &rhs) const;

        friend std::ostream &operator<<(std::ostream &os, const Triple &triple);

        std::string serialize(std::string format);

        static void from_xml(std::string xml);

    private:
        static void parseTriple(void *user_data, raptor_statement *raptor_triple);
    };
}

#endif //LIBSEMGEN_TRIPLE_H
