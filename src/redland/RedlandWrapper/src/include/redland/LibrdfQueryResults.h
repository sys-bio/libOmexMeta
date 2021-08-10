//
// Created by Ciaran on 5/20/2020.
//

#ifndef LIBOMEXMETA_LIBRDFQuery_results_H
#define LIBOMEXMETA_LIBRDFQuery_results_H


#include "librdf.h"
#include <memory>

#include "LibrdfWorld.h"
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

    class LibrdfQueryResults : public RedlandType_query_results {

    public:
        using RedlandType_query_results::RedlandType_query_results;

        explicit LibrdfQueryResults(librdf_query_results *queryResults);

        std::string str(std::string format);

        bool isBoolean();

        bool isBindings();

        int getBoolean();

        librdf_stream *resultsAsLibRdfStream();

        int getCount();

        std::string getBindingValueByName(const std::string &name);

        int getBindingsCount();

        static std::string stringReplace(std::string str, const std::string &string_to_replace, const std::string &replacement);

        std::string toString(const std::string &output_format) const;

        int next();

        ResultsMap resultsAsMap();

        std::string getBindingsName(int index);

        void printQueryResults();

        std::vector<std::string> getValidOutputFormats() const;

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
    };
}// namespace redland

#endif//LIBOMEXMETA_LIBRDFQuery_results_H
