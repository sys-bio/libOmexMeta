#include "redland/LibrdfQuery.h"

namespace redland {

    LibrdfQuery::~LibrdfQuery() {
        if (!query_)
            return;
        int usage = getUsage();
        librdf_free_query(query_);
        if ((usage - 1) == 0) {
            query_ = nullptr;
        }
    }

    LibrdfQuery::LibrdfQuery(const LibrdfQuery &query) {
        if (query_) {
            librdf_free_query(query_);
            query_ = nullptr;
        }
        query_ = query.get();// automatically increments the reference count
    };

    LibrdfQuery::LibrdfQuery(LibrdfQuery &query) noexcept {
        if (query_) {
            librdf_free_query(query_);
            query_ = nullptr;
        }
        query_ = query.get();
        query.query_ = nullptr;
    };

    LibrdfQuery &LibrdfQuery::operator=(const LibrdfQuery &query) {
        // note: equality operators only test for equality between
        // the query pointers because librdf does not support equality operators
        // for queries
        if (query_) {
            librdf_free_query(query_);
            query_ = nullptr;
        }
        query_ = query.get(); // increments the internal ref counter for us
        return *this;
    }

    LibrdfQuery &LibrdfQuery::operator=(LibrdfQuery &&query) noexcept {
        if (*this != query) {
            if (query_) {
                librdf_free_query(query_);
                query_ = nullptr;
            }
            query_ = query.getWithoutIncrement();
            query.query_ = nullptr;
        }
        return *this;
    }

    bool LibrdfQuery::operator==(const LibrdfQuery &rhs) const {
        return query_ == rhs.query_;
    }

    bool LibrdfQuery::operator!=(const LibrdfQuery &rhs) const {
        return !(rhs == *this);
    };

    int LibrdfQuery::getUsage() {
        return query_->usage;
    }

    LibrdfQuery::LibrdfQuery(librdf_query *query) : query_(query) {}

    LibrdfQuery::LibrdfQuery(const std::string &query, const std::string &name, const unsigned char *uri,
                             const char *base_uri) {
        librdf_uri *uri_ = nullptr;
        if (!uri)
            uri_ = librdf_new_uri(World::getWorld(), uri);

        librdf_uri *base_uri_ = nullptr;
        if (!base_uri)
            base_uri_ = librdf_new_uri(World::getWorld(), uri);
        query_ = librdf_new_query(
                World::getWorld(), name.c_str(), uri_, (const unsigned char *) query.c_str(), base_uri_);
    }


    librdf_query *LibrdfQuery::get() const {
        query_->usage++;
        return query_;
    }

    librdf_query *LibrdfQuery::getWithoutIncrement() const {
        return query_;
    }

}// namespace redland
