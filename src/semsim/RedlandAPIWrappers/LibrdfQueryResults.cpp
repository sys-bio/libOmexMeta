#include "LibrdfQueryResults.h"

namespace semsim {

    LibrdfQueryResults::LibrdfQueryResults(librdf_query_results *query_results) :
            query_results_(query_results_ptr(query_results, librdf_free_query_results)) {

    }

    const query_results_ptr &LibrdfQueryResults::getQueryResults() const {
        return query_results_;
    }

    bool LibrdfQueryResults::operator!() const {
        return !getQueryResults();
    }

    bool LibrdfQueryResults::operator==(const LibrdfQueryResults &rhs) const {
        return query_results_.get() == rhs.query_results_.get();
    }

    bool LibrdfQueryResults::operator!=(const LibrdfQueryResults &rhs) const {
        return !(rhs == *this);
    }

    librdf_query_results *LibrdfQueryResults::get() {
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
