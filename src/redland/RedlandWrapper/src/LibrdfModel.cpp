//
// Created by Ciaran on 5/17/2020.
//

#include "redland/LibrdfModel.h"
#include "redland/LibrdfStream.h"
#include "redland/Logger.h"

namespace redland {

    LibrdfModel::LibrdfModel(librdf_model *model)
        : RefCounted_librdf_model(model, librdf_free_model) {
        REDLAND_DEBUG("Instantiated a LibrdfModel instance");
    }

    LibrdfModel::LibrdfModel(LibrdfStorage &storage, const char *options)
        : RefCounted_librdf_model(
                  librdf_new_model(LibrdfWorld::getWorld(),
                                   // note that we do not increment the storage usage count
                                   // since this already happens inside librdf (valgrind validated)
                                   storage.getWithoutIncrement(),
                                   options),
                  librdf_free_model) {
        REDLAND_DEBUG("Instantiated a LibrdfModel instance");
    }

    void LibrdfModel::addStatement(const LibrdfStatement &statement) const {
        // librdf takes care of ref counting in this instance
        librdf_model_add_statement(obj_, statement.getWithoutIncrement());
    }

    LibrdfQueryResults LibrdfModel::query(const std::string &query) {
        LibrdfQuery q(query, *this);
        return q.execute();
    }

    int LibrdfModel::size() const {
        return librdf_model_size(obj_);
    }

    LibrdfStream LibrdfModel::toStream() const {
        LibrdfStream s(librdf_model_as_stream(obj_));
        if (s.isNull()) {
            std::cerr << "LibrdfModel::operator== Cannot create stream from model" << std::endl;
        }
        return s;
    }

    /*
     * @breif remove statement from the model
     * @param statement a LibrdfStatement to remove from the movel
     * @return void
     */
    void LibrdfModel::removeStatement(const LibrdfStatement &statement) const {
        librdf_model_remove_statement(obj_, statement.getWithoutIncrement());
    }

    bool LibrdfModel::operator==(const LibrdfModel &rhs) const {
        /**
         * Note on complexity - this algorithm is quite expensive.
         * First, if not same size, then return false. So the rest is assuming the size of lhs and rhs are equal.
         * iterate over lhs. For each of the n elements element we search through n rhs --> n^2
         * Then we iterate over rhs. For each of the n elements we search through n lhs elements --> n^2
         * So we have O(2n^2), but since we ignore multiplicitive and additive constants, its just O(n^2)
         */

        // we first try comparing size. If they are not equal, then the models are not equal
        if (size() != rhs.size())
            return false;

        // if they are the same size, we need a more expensive operation to compare the models
        // No equals operator exists for a model so we use this strategy:
        // Convert this and that to a stream. Iterate over each stream
        // checking if all statements in this are in that and all
        // statements in that are in this. Then this == that.
        bool all_this_in_rhs = true;
        bool all_rhs_in_this = true;
        LibrdfStream this_stream = toStream();
        {
            int count = 0;

            while (!this_stream.end()) {
                LibrdfStatement statement = this_stream.getStatement();
                // check statement is in other model
                bool contains_statement = rhs.containsStatement(statement);
                if (!contains_statement) {
                    all_this_in_rhs = false;
                    return all_this_in_rhs;
                }
                this_stream.next();
                count++;
            }
        }

        LibrdfStream rhs_stream = rhs.toStream();
        {
            int count = 0;
            while (!rhs_stream.end()) {
                LibrdfStatement statement = rhs_stream.getStatement();
                // check statement is in other model
                bool contains_statement = containsStatement(statement);
                if (!contains_statement) {
                    all_rhs_in_this = false;
                    break;
                }
                rhs_stream.next();
                count++;
            }
        }
        // remember that all_this_in_rhs is already true, if the algorithm has got this far.
        return all_rhs_in_this;
    }

    bool LibrdfModel::operator!=(const LibrdfModel &rhs) const {
        return !(rhs == *this);
    }

    LibrdfStorage LibrdfModel::getStorage() const {
        return LibrdfStorage(librdf_model_get_storage(obj_));
    }

    int LibrdfModel::commitTransaction() const {
        return librdf_model_transaction_commit(obj_);
    }

    int LibrdfModel::startTransaction() const {
        return librdf_model_transaction_start(obj_);
    }

    void *LibrdfModel::getTransactionHandle() const {
        return librdf_model_transaction_get_handle(obj_);
    }

    int LibrdfModel::startTransactionWithHandle(void *handle) const {
        return librdf_model_transaction_start_with_handle(obj_, handle);
    }

    int LibrdfModel::getTransactionRollback() const {
        return librdf_model_transaction_rollback(obj_);
    }

    int LibrdfModel::supportsContexts() const {
        return librdf_model_supports_contexts(obj_);
    }

    bool LibrdfModel::containsStatement(LibrdfStatement &statement) const {
        LibrdfStream stream = toStream();

        // non-owning
        while (!stream.end()) {
            // this is a non-owning pointer that apparently doesn't add to the ref count.
            // so don't free it.
            LibrdfStatement proposal_statement = stream.getStatement();
            if (statement == proposal_statement) {
                return true;
            }
            stream.next();
        }
        return false;
    }


}// namespace redland
