//
// Created by ciaran on 16/08/2021.
//

#ifndef LIBOMEXMETA_QUERY_H
#define LIBOMEXMETA_QUERY_H

#include "redland/RedlandAPI.h"

using namespace redland;

namespace omexmeta {

    /**
     * @brief make a Sparql @param query on the rdf graph represented by
     * @param model.
     */
    class Query {
    public:
        Query(const std::string& query, const LibrdfModel& model);

        /**
         * @brief return query results as a ResultsMap, where sparql
         * variables are bound as keys in a map and values are vectors
         * containing nodes associated with the ith position in the query results.
         */
        ResultsMap asMap();

        /**
         * @brief return query results as a string in the format of your
         * choosing.
         * @details valid formats are "xml", "json", "table", "csv",
         * "mkr", "tsv", "html","turtle", "rdfxml",
         */
        std::string asString(const std::string& format);

    private:
        LibrdfQuery query_;
        const LibrdfModel& model_;
        LibrdfQueryResults results_;
    };
}// namespace omex

#endif//LIBOMEXMETA_QUERY_H
