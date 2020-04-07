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


//todo get some real singular annotations and parse into a Triple. Does it work?
namespace semsim {
    class Triple : private IRDF {
        Subject subject;
        Predicate predicate;
        Resource resource;
    public:
        Triple(Subject subject, Predicate predicate, Resource resource);

        Triple() = default;

        ~Triple() = default;

        Triple(const Triple &triple);

        Triple(Triple &&triple) noexcept;

        Triple &operator=(const Triple &triple);

        Triple &operator=(Triple &&triple) noexcept;

        const Subject &getSubject() const;

        const Predicate &getPredicate() const;

        const Resource &getResource() const;

        bool operator==(const Triple &rhs) const;

        bool operator!=(const Triple &rhs) const;

        friend std::ostream &operator<<(std::ostream &os, const Triple &triple);

        std::string serialize(std::string format) override;

        static void from_xml2(std::string xml);

        static Triple from_xml(std::string xml);

    private:
        void parseTriple(void *user_data, raptor_statement *triple);
    };
}

#endif //LIBSEMGEN_TRIPLE_H
