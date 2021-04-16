#include "redland/LibrdfQueryResults.h"

namespace redland {

    LibrdfQueryResults::LibrdfQueryResults(librdf_query_results *query_results) : query_results_(query_results) {}

    LibrdfQueryResults::~LibrdfQueryResults(){
        if (!query_results_)
            return;
        librdf_free_query_results(query_results_);
        query_results_ = nullptr;
    }


    librdf_query_results *LibrdfQueryResults::get() const {
        return query_results_;
    }

    std::string LibrdfQueryResults::str(std::string format) {
        return std::string();
    }

    LibrdfQueryResults::LibrdfQueryResults(LibrdfQueryResults &&queryResults) noexcept {
        if (queryResults.query_results_ != nullptr) {
            if (query_results_ != nullptr) {
                librdf_free_query_results(query_results_);
                query_results_ = nullptr;
            }
            query_results_ = queryResults.query_results_;
            queryResults.query_results_ = nullptr;
        }
    }

    LibrdfQueryResults &LibrdfQueryResults::operator=(LibrdfQueryResults &&queryResults) noexcept {
        if (this != &queryResults) {
            if (queryResults.query_results_ != nullptr) {
                if (query_results_ != nullptr) {
                    librdf_free_query_results(query_results_);
                    query_results_ = nullptr;
                }
                query_results_ = queryResults.query_results_;
                queryResults.query_results_ = nullptr;
            }
        }
        return *this;
    }


}// namespace redland

/*
 * Todo implement librdf_query_results_get_binding_value_by_name(
                query_results_, (const char *) name.c_str());
                for use in Query.cpp
 */
