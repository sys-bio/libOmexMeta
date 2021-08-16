//
// Created by Ciaran on 5/20/2020.
//

#ifndef LIBOMEXMETA_LIBRDFQuery_results_H
#define LIBOMEXMETA_LIBRDFQuery_results_H


#include "librdf.h"
#include <memory>

#include "redland/LibrdfQuery.h"
#include "redland/LibrdfWorld.h"
#include "redland/LibrdfStream.h"
#include "redland/RedlandType.h"

namespace redland {

    using ResultsMap = std::unordered_map<std::string, std::vector<std::string>>;

    /**
     * @brief std::function signature of librdf_free_parser
     */
    using query_results_free_func = std::function<void(librdf_query_results *)>;

    /**
     * Instantiation of templated superclass
     */
    using RedlandType_query_results = RedlandType<librdf_query_results, query_results_free_func>;

    class LibrdfModel;
    class LibrdfQuery;


    class LibrdfQueryResults : public RedlandType_query_results {

    public:
        using RedlandType_query_results::RedlandType_query_results;

        explicit LibrdfQueryResults(librdf_query_results *queryResults, LibrdfQuery* query);

//        void regenerateQueryResults();

        /**
         * @brief get the query results as a LibrdfStream
         * @details only meaningful if this is an RDF graph query result
         * @throws invalid_argument when toStream is called
         * and LibrdfQueryResult::isGraph() evaluates to false.
         */
        LibrdfStream toStream();

        /**
         * @brief Move to the next result
         */
        int next();

        /**
         * @brief true when binding results are exausted
         */
        bool isFinished();

        std::vector<LibrdfNode> getBindings();

        /**
         * @brief true when this LibrdfQueryResults is variable boolean format
         */
        bool isBoolean();

        /**
         * @brief true when this LibrdfQueryResults is variable bindings format
         */
        bool isBindings();

        int getBoolean();

        /**
         * @brief true when this LibrdfQueryResults is RDF graph format
         */
        bool isGraph();


        std::string getBindingValueByName(const std::string &name);

        /**
         * @brief returns the number of bindings in the sparql query.
         * @details i.e. the query
         *  SELECT ?x ?y ?z
         *  WHERE {
         *      ?x ?y ?z
         *  }
         *  has 3 bindings, x, y and z.
         */
        int getBindingsCount();

        static std::string stringReplace(std::string str, const std::string &string_to_replace, const std::string &replacement);

        std::string toString(const std::string &output_format);


        /**
         * @brief get the value of the bindings at @param index as a std::string
         */
        std::string getBindingsName(int index);

        /**
         * @brief get all bindings names as a vector of strings
         * @details the number of bindings is determined by getBindingsCount
         */
         std::vector<std::string> getBindingsNames();

        void printQueryResults();

        std::vector<std::string> getValidOutputFormats() const;

        /**
         * @brief create a map from the query results.
         */
        ResultsMap map();

    private:
        LibrdfQuery* query_;
        ResultsMap map_;
        bool mapExecuted = false;

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

        librdf_query_results* begin = nullptr;
    };
}// namespace redland

#endif//LIBOMEXMETA_LIBRDFQuery_results_H
