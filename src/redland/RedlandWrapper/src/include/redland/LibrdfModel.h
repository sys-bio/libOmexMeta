//
// Created by Ciaran on 5/17/2020.
//

#ifndef LIBOMEXMETA_LIBRDFMODEL_H
#define LIBOMEXMETA_LIBRDFMODEL_H

#include "LibrdfQuery.h"
#include "LibrdfQueryResults.h"
#include "LibrdfStatement.h"
#include "LibrdfStorage.h"
#include "LibrdfStream.h"
#include "LibrdfWorld.h"
#include "librdf.h"
#include <iostream>
#include <memory>
#include <string>


namespace redland {

    /**
     * @brief std::function signature of librdf_free_model
     */
    using model_free_func = std::function<void(librdf_model *)>;

    /**
     * Instantiation of templated superclass
     */
    using RefCounted_librdf_model = RefCountedRedlandType<librdf_model, model_free_func>;

    class LibrdfQuery;
    class LibrdfQueryResults;

    /**
     * @brief RAII abstraction around librdf_model
     */
    class LibrdfModel : public RefCounted_librdf_model {

    public:
        using RefCounted_librdf_model::RefCounted_librdf_model;

        explicit LibrdfModel(librdf_model *model);

        explicit LibrdfModel(LibrdfStorage& storage, const char *options = nullptr);

        /**
         * @brief equality operator.
         * @details iterates over this stream and looks for containment in rhs stream, and then does the same in reverse.
         * @details Maximum complexity: O(n^2). Minimum complexity O(1), when lhs and rhs are different sizes.
         */
        bool operator==(const LibrdfModel &rhs) const ;

        bool operator!=(const LibrdfModel &rhs) const ;

        [[nodiscard]] LibrdfQueryResults query(const std::string& query) const;

        LibrdfStream toStream() const;

        int size() const;

        void addStatement(const LibrdfStatement& statement) const;

        void removeStatement(const LibrdfStatement &statement) const;

        LibrdfStorage getStorage() const;

        int commitTransaction() const;

        int startTransaction() const;

        void *getTransactionHandle() const;

        int startTransactionWithHandle(void *handle) const;

        int getTransactionRollback() const;

        int supportsContexts() const;

        bool containsStatement( LibrdfStatement &statement) const ;
    };
}

#endif //LIBOMEXMETA_LIBRDFMODEL_H
