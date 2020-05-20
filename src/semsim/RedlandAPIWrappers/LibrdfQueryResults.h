//
// Created by Ciaran on 5/20/2020.
//

#ifndef LIBSEMSIM_LIBRDFQUERYRESULTS_H
#define LIBSEMSIM_LIBRDFQUERYRESULTS_H

#include <librdf.h>
#include <memory>
#include "semsim/Error.h"

namespace semsim {
    class LibrdfQueryResults {
        std::shared_ptr<librdf_query_results *> query_results_;
    public:
        const std::shared_ptr<librdf_query_results *> &getQueryResults() const;

        LibrdfQueryResults() = default;

        explicit LibrdfQueryResults(librdf_query_results *query_results);

        ~LibrdfQueryResults();

        LibrdfQueryResults(const LibrdfQueryResults &LibrdfQueryResults);

        LibrdfQueryResults(LibrdfQueryResults &&LibrdfQueryResults) noexcept;

        LibrdfQueryResults &operator=(const LibrdfQueryResults &LibrdfQueryResults);

        LibrdfQueryResults &operator=(LibrdfQueryResults &&LibrdfQueryResults) noexcept;

        bool operator!() const;


    };
}


#endif //LIBSEMSIM_LIBRDFQUERYRESULTS_H
