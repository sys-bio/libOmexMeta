#include "redland/LibrdfQuery.h"
#include "redland/LibrdfQueryResults.h"
#include <redland/LibrdfException.h>
#include <redland/LibrdfModel.h>

#include <utility>
#include "redland/Logger.h"

namespace redland {

    bool LibrdfQuery::operator==(const LibrdfQuery &rhs) const {
        return obj_ == rhs.obj_;
    }

    bool LibrdfQuery::operator!=(const LibrdfQuery &rhs) const {
        return !(rhs == *this);
    };

//    LibrdfQuery::LibrdfQuery(librdf_query *query, const LibrdfModel &model)
//        : RedlandType_librdf_query(query, librdf_free_query), model_(const_cast<LibrdfModel &>(model)) {
//        REDLAND_DEBUG("Instantiated a LibrdfQuery instance");
//    }

    LibrdfQuery::LibrdfQuery(const std::string& query, const LibrdfModel &model)
        : query_(query), model_(const_cast<LibrdfModel &>(model)) {
        obj_ = newQuery();
        freeFunc_ = librdf_free_query;
    }

    librdf_query *LibrdfQuery::newQuery() {
        return librdf_new_query(
                LibrdfWorld::getWorld(),
                "sparql",
                nullptr,
                (const unsigned char *) query_.c_str(),
                nullptr);
    }

    LibrdfQueryResults LibrdfQuery::execute() {
        librdf_query_results* q = librdf_query_execute(obj_, model_.getWithoutIncrement());
        LibrdfQueryResults qr(q, this);
        // return by value uses copy constructor
        return qr;
    }

    LibrdfModel &LibrdfQuery::getModel() const {
        return model_;
    }


}// namespace redland
