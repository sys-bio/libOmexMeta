#include "LibrdfQueryResults.h"

namespace semsim {

    LibrdfQueryResults::LibrdfQueryResults(librdf_query_results *query_results) :
            query_results_(std::make_shared<librdf_query_results *>(query_results)) {

    }

    LibrdfQueryResults::~LibrdfQueryResults() {
        if (query_results_.use_count() == 1) {
            librdf_free_query_results(*query_results_);
        }
    }

    LibrdfQueryResults::LibrdfQueryResults(const LibrdfQueryResults &LibrdfQueryResults) {
        if (query_results_)
            librdf_free_query_results(*query_results_); // Remove prexisting query_results before copy
        query_results_ = LibrdfQueryResults.query_results_;
    }

    LibrdfQueryResults::LibrdfQueryResults(LibrdfQueryResults &&LibrdfQueryResults) noexcept {
        if (query_results_) {
            librdf_free_query_results(*query_results_);
        }
        query_results_ = std::move(LibrdfQueryResults.query_results_);
    }

    LibrdfQueryResults &LibrdfQueryResults::operator=(const LibrdfQueryResults &LibrdfQueryResults) {
        if (this != &LibrdfQueryResults) {
            if (query_results_) {
                librdf_free_query_results(*query_results_);
            }
            query_results_ = LibrdfQueryResults.query_results_;
        }
        return *this;
    }

    LibrdfQueryResults &LibrdfQueryResults::operator=(LibrdfQueryResults &&LibrdfQueryResults) noexcept {
        if (this != &LibrdfQueryResults) {
            if (query_results_) {
                librdf_free_query_results(*query_results_);
            }
            query_results_ = std::move(LibrdfQueryResults.query_results_);
        }
        return *this;
    }

    const std::shared_ptr<librdf_query_results *> &LibrdfQueryResults::getQueryResults() const {
        return query_results_;
    }

    bool LibrdfQueryResults::operator!() const {
        return !getQueryResults();
    }

}
