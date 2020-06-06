//
// Created by Ciaran on 4/24/2020.
//

#include "Query.h"


// todo: Is laqrs a valid query language?

namespace semsim {

    Query::Query(librdf_model *model, std::string query)
            : model_(model), query_(std::move(query)) {
        q_ = librdf_new_query(
                World::getWorld(), (const char *) "sparql",
                nullptr, (const unsigned char *) query_.c_str(),
                nullptr);
        if (!q_) {
            std::ostringstream qerr;
            throw NullPointerException("NullPointerException: Query::runQuery(): q_");
        }
        runQuery();
    }

//    Query::~Query() {
//        librdf_free_query_results(query_results_);
//    }

    Query::Query(Query &&query) noexcept {
        if (query.query_results_ != nullptr) {
            if (query_results_ == nullptr) {
                librdf_free_query_results(query_results_);
                query_results_ = nullptr;
            }
            query_results_ = query.query_results_;
        }
        if (query.q_ != nullptr) {
            if (q_ == nullptr) {
                librdf_free_query(q_);
                q_ = nullptr;
            }
            q_ = query.q_;
        }
    }

    Query &Query::operator=(Query &&query) noexcept {
        if (this != &query) {
            if (query.query_results_ != nullptr) {
                if (query_results_ == nullptr) {
                    librdf_free_query_results(query_results_);
                    query_results_ = nullptr;
                }
                query_results_ = query.query_results_;
            }
            if (query.q_ != nullptr) {
                if (q_ == nullptr) {
                    librdf_free_query(q_);
                    q_ = nullptr;
                }
                q_ = query.q_;
            }
        }
        return *this;
    }

    void Query::freeQuery() {
        if (query_results_ != nullptr) {
            librdf_free_query_results(query_results_);
            query_results_ = nullptr;
        }
        if (q_ != nullptr) {
            librdf_free_query(q_);
            q_ = nullptr;
        }
    }

    void Query::runQuery() {
        // When we runQuery twice, we have memory leak if we do
        //  not free previous query results.
        if (query_results_ != nullptr) {
            librdf_free_query_results(query_results_);
            query_results_ = nullptr;
        }

        query_results_ = librdf_query_execute(q_, model_);
        if (!query_results_) {
            throw NullPointerException("NullPointerException: Query::runQuery(): query_results_");
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

//    RDF Query::resultsAsRDF() {
//        RDF rdf = RDF::fromString(resultsAsStr("rdfxml"), "rdfxml");
//        return rdf;
//    }

    int Query::getCount() {
        return librdf_query_results_get_count(query_results_);
    }

    std::string Query::getBindingValueByName(const std::string &name) {
        LibrdfNode node(librdf_query_results_get_binding_value_by_name(
                query_results_, (const char *) name.c_str()));
        std::string s = node.str();
        node.freeNode();
        return s;
    }

    int Query::getBindingsCount() {
        return librdf_query_results_get_bindings_count(query_results_);
    }

    std::string Query::resultsAsStr(const std::string &output_format) {
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
        unsigned char *s = librdf_query_results_to_string2(
                query_results_, output_format.c_str(),
                nullptr, nullptr,
                nullptr);
        std::string res = (const char *) s; // makes a copy
        free(s);
        return res;
    }


    int Query::next() {
        return librdf_query_results_next(query_results_);
    }

    ResultsMap Query::resultsAsMap() {
        ResultsMap map;
        // configure a data structure for storing the results
        // binding name is x, y, z of sparql query for example.
        for (int i = 0; i < getBindingsCount(); i++) {
            std::string binding_name = getBindingsName(i);
            map[binding_name] = std::vector<std::string>();
        }

        // iterate over bindings until no more left
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

        // we rerun the query to overwrite the serializer_
        // variable with a fresh object (since once you've
        // hit the end you can't seem to go back).
        // todo look more into this.
        runQuery();
        return map;
    }

//    Triples Query::resultsAsTriples() {
//        return resultsAsRDF().toTriples();
//    }


    std::string Query::getBindingsName(int index) {
        return librdf_query_results_get_binding_name(query_results_, index);
    }


}

//todo information like MIME types etc for each syntax are
// queryable using featuers similar to librdf_query_language_get_description