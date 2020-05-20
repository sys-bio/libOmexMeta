#include "LibrdfQuery.h"

namespace semsim {

    LibrdfQuery::LibrdfQuery(librdf_query *query_results) :
            query_(std::make_shared<librdf_query *>(query_results)) {

    }

    LibrdfQuery::~LibrdfQuery() {
        if (query_.use_count() == 1) {
            librdf_free_query(*query_);
        }
    }

    LibrdfQuery::LibrdfQuery(const LibrdfQuery &LibrdfQuery) {
        if (query_)
            librdf_free_query(*query_); // Remove prexisting query_results before copy
        query_ = LibrdfQuery.query_;
    }

    LibrdfQuery::LibrdfQuery(LibrdfQuery &&LibrdfQuery) noexcept {
        if (query_) {
            librdf_free_query(*query_);
        }
        query_ = std::move(LibrdfQuery.query_);
    }

    LibrdfQuery &LibrdfQuery::operator=(const LibrdfQuery &LibrdfQuery) {
        if (this != &LibrdfQuery) {
            if (query_) {
                librdf_free_query(*query_);
            }
            query_ = LibrdfQuery.query_;
        }
        return *this;
    }

    LibrdfQuery &LibrdfQuery::operator=(LibrdfQuery &&LibrdfQuery) noexcept {
        if (this != &LibrdfQuery) {
            if (query_) {
                librdf_free_query(*query_);
            }
            query_ = std::move(LibrdfQuery.query_);
        }
        return *this;
    }

    const std::shared_ptr<librdf_query *> &LibrdfQuery::getQueryResults() const {
        return query_;
    }

    bool LibrdfQuery::operator!() const {
        return !getQueryResults();
    }

}
