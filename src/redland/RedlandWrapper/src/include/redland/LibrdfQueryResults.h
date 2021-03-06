//
// Created by Ciaran on 5/20/2020.
//

#ifndef LIBOMEXMETA_LIBRDFQuery_results_H
#define LIBOMEXMETA_LIBRDFQuery_results_H


#include "librdf.h"
#include <memory>

#include "World.h"

namespace redland {

    class LibrdfQueryResults {
        librdf_query_results * query_results_ = nullptr;

    public:
        LibrdfQueryResults() = default;

        explicit LibrdfQueryResults(librdf_query_results *queryResults);

        /**
         * Copy constructor
         */
        LibrdfQueryResults(const LibrdfQueryResults &queryResults) = delete;

        /**
         * move constructor
         */
        LibrdfQueryResults(LibrdfQueryResults &&queryResults) noexcept;

        /**
         * Copy assignment constructor
         */
        LibrdfQueryResults &operator=(const LibrdfQueryResults &queryResults) = delete;

        /**
         * move assignment constructor
         */
        LibrdfQueryResults &operator=(LibrdfQueryResults &&queryResults) noexcept;

        [[nodiscard]] librdf_query_results *get() const;

        std::string str(std::string format);

        void freeQueryResults();
    };
}// namespace redland

#endif//LIBOMEXMETA_LIBRDFQuery_results_H
