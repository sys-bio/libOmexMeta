//
// Created by Ciaran on 4/24/2020.
//

#include "Query.h"
#include <string>
#include <sstream>
#include <iostream>
#include <utility>
#include "librdf.h"
#include "semsim/Error.h"
#include "semsim/Error.h"
#include "semsim/SemsimUtils.h"

namespace semsim {

    Query::Query(librdf_world *world, librdf_model *model, std::string query)
            : world_(world), model_(model), query_(query) {

        if (!world_) {
            throw LibRDFException("World is null");
        }
        if (!model_) {
            throw LibRDFException("Model is null");
        }
        librdf_query *q = librdf_new_query(
                world_, (const char *) "sparql",
                nullptr, (const unsigned char *) query_.c_str(), nullptr
        );
        if (!q) {
            std::ostringstream qerr;
            qerr << __FILE__ << ":" << __LINE__ << ": librdf_query object was not created";
            throw LibRDFException(qerr.str());
        }

        query_results_ = librdf_query_execute(q, model_);
        if (!query_results_) {
            std::ostringstream qerr2;
            qerr2 << __FILE__ << ":" << __LINE__ << ": librdf_query_results object was not created";
            throw LibRDFException(qerr2.str());
        }

    }

    bool Query::isBoolean() {
        return librdf_query_results_is_boolean(query_results_);
    }

    bool Query::isBindings() {
        return librdf_query_results_is_bindings(query_results_);
    }

    int Query::getBoolean() {
        return librdf_query_results_get_boolean(query_results_);
    }

    librdf_stream *Query::resultsAsLibRdfStream() {
        return librdf_query_results_as_stream(query_results_);
    }

    RDF Query::resultsAsRDF() {
        return RDF();
    }

    int Query::getCount() {
        return librdf_query_results_get_count(query_results_);
    }

    std::string Query::getBindingValueByName(const std::string &name) {
        librdf_node *node = librdf_query_results_get_binding_value_by_name(query_results_, (const char *) name.c_str());
        std::string value;
        switch (node->type) {
            case RAPTOR_TERM_TYPE_URI: {
                value = (const char *) librdf_uri_as_string(librdf_node_get_uri(node));
                break;
            }
            case RAPTOR_TERM_TYPE_LITERAL: {
                value = (const char *) librdf_node_get_literal_value(node);
                break;
            }
            case RAPTOR_TERM_TYPE_BLANK: {
                value = (const char *) librdf_node_get_blank_identifier(node);
                break;
            }
            default:
                throw LibRDFException("Unrecognized term type");
        }
        return value;
    }

    int Query::getBindingsCount() {
        return librdf_query_results_get_bindings_count(query_results_);
    }

    std::string Query::resultAsStr(const std::string &output_format) {
        if (std::find(valid_output_formats_.begin(), valid_output_formats_.end(), output_format) ==
            valid_output_formats_.end()) {
            std::ostringstream err;
            err << __FILE__ << ":" << __LINE__ << ": requested output format \"" << output_format << "\"";
            err << "is not valid. These formats are valid: ";
            for (auto &it : valid_output_formats_) {
                err << it << ", ";
            }
            err << std::endl;
            throw std::invalid_argument(err.str());
        }
        return (const char *) librdf_query_results_to_string2(query_results_, output_format.c_str(), nullptr, nullptr,
                                                              nullptr);
    }

    Query::~Query() {
        librdf_free_query_results(query_results_);

    }

    int Query::next() {
        return librdf_query_results_next(query_results_);
    }

    ResultsMap Query::resultsAsMap() {
        librdf_query_results* results_copy = nullptr;
        results_copy = query_results_;
        ResultsMap map;
        for (int i = 0; i < getBindingsCount(); i++) {
            std::string binding_name = getBindingsName(i);
            map[getBindingsName(i)] = std::vector<std::string>();
        }
        bool done = false;
        while (!done) {
            for (auto &key : map) {
                map[key.first].push_back(getBindingValueByName(key.first));
            }
            int failed = next();
            if (failed) {
                done = true;
            }
        }

        librdf_query_results_finished(query_results_);
        return map;
    }

    ResultsMap Query::resultsAsMap2() {
        librdf_stream* stream = resultsAsLibRdfStream();
        bool done= false;
        while (!done){
            librdf_statement* stmt = librdf_stream_get_object(stream);
            Triple triple::from_librdf_statement(stmt);
            librdf_stream_next(stream);
        }




        librdf_query_results* results_copy = nullptr;
        results_copy = query_results_;
        ResultsMap map;
        for (int i = 0; i < getBindingsCount(); i++) {
            std::string binding_name = getBindingsName(i);
            map[getBindingsName(i)] = std::vector<std::string>();
        }
        bool done = false;
        while (!done) {
            for (auto &key : map) {
                map[key.first].push_back(getBindingValueByName(key.first));
            }
            int failed = next();
            if (failed) {
                done = true;
            }
        }

        librdf_query_results_finished(query_results_);
        return map;
    }


    std::string Query::getBindingsName(int index) {
        return librdf_query_results_get_binding_name(query_results_, index);
    }

}

//todo information like MIME types etc for each syntax are
// queryable using featuers similar to librdf_query_language_get_description