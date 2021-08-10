//
// Created by Ciaran on 4/24/2020.
//

#ifndef LIBOMEXMETA_QUERY_H
#define LIBOMEXMETA_QUERY_H

//#include "omexmeta/include/omexmeta/Error.h"
//#include "omexmeta/include/omexmeta/OmexMetaUtils.h"
#include "redland/RedlandAPI.h"

#include "redland/librdf.h"

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace redland;

namespace omexmeta {

    typedef std::unordered_map<std::string, std::vector<std::string>> ResultsMap;

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
    class Query {


    public:
        /**
        * @brief constructor for Query object
         */
        Query(LibrdfModel &model, std::string query);

        /**
         * @brief destructor
         */
         ~Query();

        /**
         *
         * @brief copy constructor for Query object
         * @details deleted
         */
        Query(const Query &query);

        /**
         * @brief move constructor for Query object
         */
        Query(Query &&query) noexcept;

        /**
         *
         * @brief copy assignment constructor for Query object
         * @details deleted
         *
         * @class copy assignment constructor is deleted because it makes using
         * the underlying librdf_query and librdf_query_results pointers
         * safer from a memory management perspective.
         */
        Query &operator=(const Query &query);

        /**
        *
         * @brief move assignment constructor for Query object
         *
         */
        Query &operator=(Query &&query) noexcept;

        /**
         * @brief free resources associated with a query object.
         * @details it is the callers responsibility to ensure
         * resources used by Query are released after use.
         */
        void freeQuery();

        /**
         * @breif returns the results as a librdf_stream* object
         *
         * developers. Consider removing.
         */
        [[maybe_unused]] librdf_stream *resultsAsLibRdfStream();

        /**
         * @brief returns query results in a map where keys are
         * the variable names used in query and values are vectors
         * of values for results.
         *
         * @details This is the only supported mechanism for ascertaining
         * query results programatically, without needing to read/write to/from
         * file. This method uses an iterator from librdf. When it gets to the end
         * of the iterator, the iterator is "used up". Therefore at the end of
         * collecting the results as a map, the original query is re-run, so that
         * the presently instantiated Query object is not rendered useless.
         *
         * If the query looks like this:
         * @code
         * std::string query_string =   "SELECT ?x ?y ?z
         *                              "WHERE {"
         *                              "   ?x ?y ?z"
         *                              "}";
         * Query query(query_string);
         * @endcode
         * The column names will be x, y and z and the results
         * will be string representations of all subjects (?x),
         * predicates (?y) and resources (?z) in a vector of size `n`,
         * where n is the number of query results.
         */
        ResultsMap resultsAsMap();

        /**
         * @brief collect the result of the query as a string
         * @param output_format one of 9 strings used to choose how you
         * want the results to be presented.
         * Options are xml, json, table, csv, mkr, tsv, html, turtle and rdfxml.
         */
        [[nodiscard]] std::string resultsAsStr(const std::string &output_format, std::string baseuri = "query_results") const;

        /**
         * @brief Run a query.
         * @details Users do not need to manually execute a query using this method.
         * It is used automatically in the constructor for Query and again in Query::map.
         */
        void runQuery();

        /**
         * @brief Output query results to cout
         */
        void printQueryResults();

    private:

        std::vector<std::string> valid_output_formats_ = {
                "xml",
                "json",
                "table",
                "csv",
                "mkr",
                "tsv",
                "html",
                "turtle",
                "rdfxml",
                };

        int next();


        /**
         * librdf_query_results_is_bindings:
         * @query_results: #librdf_query_results object
         *
         * Test if librdf_query_results is variable bindings format.
         *
         * Return value: non-0 if true
         **/
        bool isBindings();

        /**
         * Test if librdf_query_results is boolean format.
         *
         * If this function returns true, the result can be retrieved by
         * librdf_query_results_get_boolean().
         *
         * Return value: non-0 if true
         **/
        bool isBoolean();

        /**
         * Get boolean query result.
         *
         * The return value is only meaningful if this is a boolean
         * query result - see librdf_query_results_is_boolean()
         *
         * Return value: boolean query result - >0 is true, 0 is false, <0 on error or finished
         */
        int getBoolean();

        /**
         * librdf_query_results_get_count:
         * @query_results: #librdf_query_results query results
         *
         * Get number of bindings so far.
         *
         * Return value: number of bindings found so far
         **/
        int getCount();


        /**
         * @query_results: #librdf_query_results query results
         * @offset: offset of binding name into array of known names
         *
         * Get binding name for the current result.
         *
         * Return value: a pointer to a shared copy of the binding name or NULL on failure
         **/
        std::string getBindingsName(int index);

        /**
         * librdf_query_results_get_binding_value_by_name:
         * @query_results: #librdf_query_results query results
         * @name: variable name
         *
         * Get one binding value for a given name in the current result.
         *
         * Return value: a new #librdf_node binding value or NULL on failure
         **/
        std::string getBindingValueByName(const std::string &name);

        /**
         * librdf_query_results_get_bindings_count:
         * @query_results: #librdf_query_results query results
         *
         * Get the number of bound variables in the result.
         *
         * Return value: <0 if failed or results exhausted
         **/
        int getBindingsCount();

        librdf_model *model_ = nullptr;// will be cleaned up by RDF class
        librdf_query_results *query_results_ = nullptr;
        librdf_query *q_ = nullptr;
        std::string query_;

    };
}// namespace omexmeta

#endif//LIBOMEXMETA_QUERY_H
