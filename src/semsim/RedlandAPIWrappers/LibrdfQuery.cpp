#include "LibrdfQuery.h"

namespace semsim {

    LibrdfQuery::LibrdfQuery(librdf_query *query) :
            query_(query_ptr(query)) {

    }

    const query_ptr &LibrdfQuery::getQueryResults() const {
        return query_;
    }

    bool LibrdfQuery::operator!() const {
        return !getQueryResults();
    }

    bool LibrdfQuery::operator==(const LibrdfQuery &rhs) const {
        return query_.get() == rhs.query_.get();
    }

    bool LibrdfQuery::operator!=(const LibrdfQuery &rhs) const {
        return !(rhs == *this);
    }

    librdf_query *LibrdfQuery::get() {
        return query_.get();
    }

}
