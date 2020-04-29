//
// Created by Ciaran on 4/24/2020.
//

#ifndef LIBSEMGEN_QUERY_H
#define LIBSEMGEN_QUERY_H

#include <librdf.h>
#include <string>
#include <unordered_map>
#include <vector>
#include "semsim/Triples.h"

namespace semsim {

    typedef std::unordered_map<std::string, std::vector<std::string>> ResultsMap;

    class Query {
        librdf_world *world_;
        librdf_model *model_;
        std::string query_;
        librdf_query_results *query_results_;
        librdf_query_results *query_results_copy_;

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

        Query(librdf_world *world, librdf_model *model, std::string query);

        ~Query();

        librdf_stream *resultsAsLibRdfStream();

//        RDF resultsAsRDF();

        ResultsMap resultsAsMap();

        std::string resultsAsStr(const std::string &output_format);

        Triples resultsAsTriples();
    };
}

#endif //LIBSEMGEN_QUERY_H
