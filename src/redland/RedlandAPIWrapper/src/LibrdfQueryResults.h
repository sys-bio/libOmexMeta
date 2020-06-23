//
// Created by Ciaran on 5/20/2020.
//

#ifndef LIBOMEXMETA_LIBRDFQuery_results_H
#define LIBOMEXMETA_LIBRDFQuery_results_H


#include <librdf.h>
#include <memory>

#include "World.h"

namespace redland {

    class LibrdfQueryResults {

        struct deleter {
            void operator()(librdf_query_results *query_results);
        };

        std::unique_ptr<librdf_query_results, deleter> query_results_;
    public:
        LibrdfQueryResults() = default;

        explicit LibrdfQueryResults(librdf_query_results *queryResults);

//        explicit LibrdfQueryResults();

        [[nodiscard]] librdf_query_results *get() const;

        std::string str(std::string format);
    };
}

#endif //LIBOMEXMETA_LIBRDFQuery_results_H
