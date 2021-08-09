//
// Created by Ciaran on 5/17/2020.
//

#include "redland/LibrdfModel.h"
#include "redland/LibrdfStream.h"

namespace redland {

    LibrdfModel::LibrdfModel(librdf_model * model)
            : RefCounted_librdf_model(model, librdf_free_model){}

    LibrdfModel::LibrdfModel(LibrdfStorage &storage, const char *options)
        : RefCounted_librdf_model(
                  librdf_new_model(LibrdfWorld::getWorld(),
                                   // note that we do not increment the storage usage count
                                   // since this already happens inside librdf (valgrind validated)
                                   storage.getWithoutIncrement(),
                                   options),
                  librdf_free_model) {}

    void LibrdfModel::addStatement(const LibrdfStatement& statement) const {
        // librdf takes care of ref counting in this instance
        librdf_model_add_statement(obj_, statement.getWithoutIncrement());
    }

    LibrdfQueryResults LibrdfModel::query(const LibrdfQuery &query) const {
        librdf_query_results *results = librdf_query_execute(query.getWithoutIncrement(), obj_);
        return LibrdfQueryResults(results);
    }

    int LibrdfModel::size() const {
        return librdf_model_size(obj_);
    }

    LibrdfStream LibrdfModel::toStream() {
        return LibrdfStream(librdf_model_as_stream(obj_));
    }

    /*
     * @breif remove statement from the model
     * @param statement a LibrdfStatement to remove from the movel
     * @return void
     */
    void LibrdfModel::removeStatement(const LibrdfStatement &statement) const {
        librdf_model_remove_statement(obj_, statement.getWithoutIncrement());
    }

    bool LibrdfModel::operator==( LibrdfModel &rhs)  {
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
        librdf_stream *this_stream = librdf_model_as_stream(obj_);
        if (!this_stream) {
            std::cerr << "LibrdfModel::operator== Cannot create stream from model" << std::endl;
        } else {
            int count = 0;
            while (!librdf_stream_end(this_stream)) {
                LibrdfStatement statement = LibrdfStatement(librdf_stream_get_object(this_stream));
                if (!statement.getWithoutIncrement()) {
                    std::cerr << "LibrdfModel::operator==  librdf_stream_next returned null" << std::endl;
                }
                // check statement is in other model
                bool contains_statement = rhs.containsStatement(statement);
                if (!contains_statement) {
                    all_this_in_rhs = false;
                    break;
                }
                librdf_stream_next(this_stream);
                count++;
            }
        }
        librdf_free_stream(this_stream);
        librdf_stream *rhs_stream = librdf_model_as_stream(rhs.obj_);
        if (!rhs_stream) {
            std::cerr << "LibrdfModel::operator== Cannot create stream from model" << std::endl;
        } else {
            int count = 0;
            while (!librdf_stream_end(rhs_stream)) {
                LibrdfStatement statement(librdf_stream_get_object(rhs_stream));
                if (!statement.getWithoutIncrement()) {
                    std::cerr << "LibrdfModel::operator==  librdf_stream_next returned null" << std::endl;
                }
                // check statement is in other model
                bool contains_statement = rhs.containsStatement(statement);
                if (!contains_statement) {
                    all_rhs_in_this = false;
                    break;
                }
                librdf_stream_next(rhs_stream);
                count++;
            }
        }
        librdf_free_stream(rhs_stream);
        return all_this_in_rhs && all_rhs_in_this;
    }

    bool LibrdfModel::operator!=(LibrdfModel &rhs)  {
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

    bool LibrdfModel::containsStatement( LibrdfStatement &statement)  {
        bool contains_statement = false;
        librdf_stream *stream = librdf_model_as_stream(obj_);
        if (!stream) {
            throw std::logic_error("LibrdfModel::containsStatement stream is nullptr");
        }

        // non-owning
        while (!librdf_stream_end(stream)) {
            // this is a non-owning pointer that apparently doesn't add to the ref count.
            // so don't free it.
            LibrdfStatement proposal_statement(librdf_stream_get_object(stream));
            if (!proposal_statement.getWithoutIncrement()) {
                throw std::logic_error("LibrdfModel::containsStatement proposal statement is nullptr");
            }

            if (LibrdfStatement::equals(&statement, &proposal_statement)) {
                contains_statement = true;
                break;
            }
            librdf_stream_next(stream);
        }
        librdf_free_stream(stream);
        return contains_statement;
    }

//    bool LibrdfModel::containsStatement( LibrdfStatement &statement)  {
//        return containsStatement(statement);
//    }

}// namespace redland
