//
// Created by Ciaran on 5/20/2020.
//

#ifndef LIBSEMSIM_LIBRDFQUERY_H
#define LIBSEMSIM_LIBRDFQUERY_H


#include <librdf.h>
#include <memory>
#include "semsim/Error.h"
#include "semsim/RedlandAPIWrapper/World.h"

namespace semsim {

    class LibrdfQuery {

        struct deleter {
            void operator()(librdf_query *query);
        };

        std::unique_ptr<librdf_query, deleter> query_;
    public:
        LibrdfQuery() = default;

        explicit LibrdfQuery(librdf_query *query);

        explicit LibrdfQuery(const std::string &query,
                             const std::string &name = "sparql",
                             const unsigned char *uri = nullptr,
                             const char *base_uri = nullptr);

        [[nodiscard]] librdf_query *get() const;

    };
}

#endif //LIBSEMSIM_LIBRDFQUERY_H
