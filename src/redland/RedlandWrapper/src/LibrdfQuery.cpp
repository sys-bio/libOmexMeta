#include "LibrdfQuery.h"

namespace redland {

    void LibrdfQuery::deleter::operator()(librdf_query *query) {
        if (query)
            librdf_free_query(query);
    }

    LibrdfQuery::LibrdfQuery(librdf_query *query) :
            query_(query) {}

    LibrdfQuery::LibrdfQuery(const std::string &query, const std::string &name, const unsigned char *uri,
                             const char *base_uri) {
        librdf_uri *uri_ = nullptr;
        if (!uri)
            uri_ = librdf_new_uri(World::getWorld(), uri);

        librdf_uri *base_uri_ = nullptr;
        if (!base_uri)
            base_uri_ = librdf_new_uri(World::getWorld(), uri);
        librdf_query *q = librdf_new_query(
                World::getWorld(), name.c_str(), uri_, (const unsigned char *) query.c_str(), base_uri_);
        query_ = std::unique_ptr<librdf_query, deleter>(q);

    }

    librdf_query *LibrdfQuery::get() const {
        return query_.get();
    }

}
