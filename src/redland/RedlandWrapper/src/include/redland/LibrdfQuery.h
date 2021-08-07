//
// Created by Ciaran on 5/20/2020.
//

#ifndef LIBOMEXMETA_LIBRDFQUERY_H
#define LIBOMEXMETA_LIBRDFQUERY_H


#include "librdf.h"
#include <memory>

#include "LibrdfWorld.h"

namespace redland {

    class LibrdfQuery {

    public:
        LibrdfQuery() = default;

        ~LibrdfQuery();

        LibrdfQuery(const LibrdfQuery &query);

        LibrdfQuery(LibrdfQuery &query) noexcept;

        LibrdfQuery &operator=(const LibrdfQuery &query);

        LibrdfQuery &operator=(LibrdfQuery &&query) noexcept;

        explicit LibrdfQuery(librdf_query *query);

        explicit LibrdfQuery(const std::string &query,
                             const std::string &name = "sparql",
                             const unsigned char *uri = nullptr,
                             const char *base_uri = nullptr);

        [[nodiscard]] librdf_query *get() const;

        int getUsage();

        librdf_query *getWithoutIncrement() const;

        bool operator==(const LibrdfQuery &rhs) const;

        bool operator!=(const LibrdfQuery &rhs) const;

    private:
        librdf_query *query_ = nullptr;
    };
}// namespace redland

#endif//LIBOMEXMETA_LIBRDFQUERY_H
