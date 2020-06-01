//
// Created by Ciaran on 4/24/2020.
//

#include "Query.h"


// todo: Is laqrs a valid query language?

namespace semsim {

    Query::Query( const LibrdfModel &model, std::string query)
            : model_(model), query_(query) {
        runQuery();

    }

    void Query::runQuery() {
        librdf_query *q = librdf_new_query(
                World::getWorld(), (const char *) "sparql",
                nullptr, (const unsigned char *) query_.c_str(), nullptr
        );
        if (!q) {
            std::ostringstream qerr;
            qerr << __FILE__ << ":" << __LINE__ << ": librdf_query object was not created";
            throw LibRDFException(qerr.str());
        }

        query_results_ = LibrdfQueryResults(
                librdf_query_execute(q, model_.get())
        );
        if (!query_results_.get()) {
            std::ostringstream qerr2;
            qerr2 << __FILE__ << ":" << __LINE__ << ": librdf_query_results object was not created";
            throw LibRDFException(qerr2.str());
        }
        librdf_free_query(q);
    }

    bool Query::isBoolean() {
        return librdf_query_results_is_boolean(query_results_.get());
    }

    bool Query::isBindings() {
        return librdf_query_results_is_bindings(query_results_.get());
    }

    int Query::getBoolean() {
        return librdf_query_results_get_boolean(query_results_.get());
    }

    librdf_stream *Query::resultsAsLibRdfStream() {
        return librdf_query_results_as_stream(query_results_.get());
    }

//    RDF Query::resultsAsRDF() {
//        RDF rdf = RDF::fromString(resultsAsStr("rdfxml"), "rdfxml");
//        return rdf;
//    }

    int Query::getCount() {
        return librdf_query_results_get_count(query_results_.get());
    }

    std::string Query::getBindingValueByName(const std::string &name) {
        LibrdfNode node(librdf_query_results_get_binding_value_by_name(
                query_results_.get(), (const char *) name.c_str()));
        return LibrdfNode::str(node.get());
    }

    int Query::getBindingsCount() {
        return librdf_query_results_get_bindings_count(query_results_.get());
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
        return (const char *) librdf_query_results_to_string2(query_results_.get(), output_format.c_str(),
                                                              nullptr, nullptr,
                                                              nullptr);
    }

    Query::~Query() {
        librdf_free_query_results(query_results_.get());

    }

    int Query::next() {
        return librdf_query_results_next(query_results_.get());
    }

    ResultsMap Query::resultsAsMap() {
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
        return librdf_query_results_get_binding_name(query_results_.get(), index);
    }

}

//todo information like MIME types etc for each syntax are
// queryable using featuers similar to librdf_query_language_get_description