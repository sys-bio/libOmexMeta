#include "LibrdfQueryResults.h"

namespace redland {

    LibrdfQueryResults::LibrdfQueryResults(librdf_query_results *query_results) :
            query_results_(query_results) {}

    void LibrdfQueryResults::deleter::operator()(librdf_query_results *query_results) {
        if (query_results)
            librdf_free_query_results(query_results);
    }

    librdf_query_results *LibrdfQueryResults::get() const {
        return query_results_.get();
    }

    std::string LibrdfQueryResults::str(std::string format) {
        return std::__cxx11::string();
    }


}

/*
 * Todo implement librdf_query_results_get_binding_value_by_name(
                query_results_, (const char *) name.c_str());
                for use in Query.cpp
 */
