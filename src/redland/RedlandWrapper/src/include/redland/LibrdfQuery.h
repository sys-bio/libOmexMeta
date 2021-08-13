//
// Created by Ciaran on 5/20/2020.
//

#ifndef LIBOMEXMETA_LIBRDFQUERY_H
#define LIBOMEXMETA_LIBRDFQUERY_H


#include "librdf.h"
#include <memory>

#include "LibrdfWorld.h"
#include "RefCountedRedlandType.h"
#include "redland/LibrdfQueryResults.h"
#include "redland/LibrdfModel.h"

namespace redland {

    class LibrdfModel;

    /**
     * @brief std::function signature of librdf_free_parser
     */
    using query_free_func = std::function<void(librdf_query *)>;

    /**
     * Instantiation of templated superclass
     */
    using RedlandType_librdf_query = RefCountedRedlandType<librdf_query, query_free_func>;

    using ResultsMap = std::unordered_map<std::string, std::vector<std::string>>;

    class LibrdfQueryResults;

    /**
     * @brief interface for querying an rdf graph
     * @class This class is basically a wrapper around both librdf_query and
     * librdf_query_results. Query is not used by users directly but
     * accessed indurectly without the users knowledge via the RDF::query method.
     * Query results can be returned in 1 of 9 formats:
     *  - xml
     *  - json
     *  - table
     *  - csv
     *  - mrk
     *  - tsv
     *  - html
     *  - turtle
     *  - rdfxml
     */
    class LibrdfQuery : public RedlandType_librdf_query {

    public:
//        explicit LibrdfQuery(librdf_query *query, const LibrdfModel& model);

        explicit LibrdfQuery(const std::string& query, const LibrdfModel& model);

        bool operator==(const LibrdfQuery &rhs) const;

        bool operator!=(const LibrdfQuery &rhs) const;

        LibrdfQueryResults execute();

        LibrdfModel &getModel() const;

    private:
        /**
         * @brief construct a new query
         */
        librdf_query* newQuery();

    private:
        LibrdfModel& model_;
        std::string query_;




    };
}// namespace redland

#endif//LIBOMEXMETA_LIBRDFQUERY_H
