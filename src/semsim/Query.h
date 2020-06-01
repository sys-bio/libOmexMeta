//
// Created by Ciaran on 4/24/2020.
//

#ifndef LIBSEMSIM_QUERY_H
#define LIBSEMSIM_QUERY_H

#include "RedlandAPIWrapper.h"
#include "semsim/Error.h"
#include "semsim/SemsimUtils.h"
//#include "semsim/Triple.h"
//#include "semsim/Triples.h"

#include "librdf.h"

#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <utility>

using namespace redland;

namespace semsim {

    typedef std::unordered_map<std::string, std::vector<std::string>> ResultsMap;

    class Query {
        const LibrdfModel& model_;
        std::string query_;
        LibrdfQueryResults query_results_;

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

        void runQuery();

    public:

        Query(const LibrdfModel& model, std::string query);

        ~Query();

        librdf_stream *resultsAsLibRdfStream();

//        RDF resultsAsRDF();

        ResultsMap resultsAsMap();

        std::string resultsAsStr(const std::string &output_format);

//        Triples resultsAsTriples();
    };
}

#endif //LIBSEMSIM_QUERY_H
