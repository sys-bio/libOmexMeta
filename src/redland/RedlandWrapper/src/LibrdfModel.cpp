//
// Created by Ciaran on 5/17/2020.
//

#include "redland/LibrdfModel.h"


namespace redland {

    void LibrdfModel::freeModel() {
        if (model_ != nullptr) {
            librdf_free_model(model_);
        }
    }

    LibrdfModel::LibrdfModel(librdf_model *model)
        : model_(model) {
    }

    LibrdfModel::LibrdfModel(LibrdfModel &&model) noexcept {
        if (model.model_ != nullptr) {
            if (model_ != nullptr)
                freeModel();
            model_ = std::move(model.model_);
            model.model_ = nullptr;
        }
    }

    LibrdfModel &LibrdfModel::operator=(LibrdfModel &&model) noexcept {
        if (this != &model) {
            if (model.model_ != nullptr) {
                if (model_ != nullptr)
                    freeModel();
                model_ = std::move(model.model_);
                model.model_ = nullptr;
            }
        }
        return *this;
    }


    /*
     *
     *
     * For developers: passing a raw pointer to librdf_storage* helps prevent memory leaks.
     */
    LibrdfModel::LibrdfModel(librdf_storage *storage, const char *options)
        : model_(librdf_new_model(World::getWorld(), storage, options)) {}


    void LibrdfModel::addStatement(librdf_statement *statement) const {
        librdf_model_add_statement(get(), statement);
    }

    void LibrdfModel::addStatement(const LibrdfStatement &statement) const {
        librdf_model_add_statement(get(), statement.get());
    }

    librdf_model *LibrdfModel::get() const {
        return model_;
    }

    LibrdfQueryResults LibrdfModel::query(const LibrdfQuery &query) const {
        librdf_query_results *results = librdf_query_execute(query.get(), model_);
        return LibrdfQueryResults(results);
    }

    int LibrdfModel::size() const {
        return librdf_model_size(model_);
    }

    librdf_stream* LibrdfModel::toStream() {
        return librdf_model_as_stream(model_);
    }

    /*
     * @breif remove statement from the model
     * @param statement a LibrdfStatement to remove from the movel
     * @return void
     */
    void LibrdfModel::removeStatement(const LibrdfStatement &statement) const {
        librdf_model_remove_statement(model_, statement.get());
    }

    /*
     * @breif remove statement from the model
     * @param statement a librdf_statement* to remove from the model
     * @return void
     */
    void LibrdfModel::removeStatement(librdf_statement *statement) const {
        librdf_model_remove_statement(model_, statement);
    }


    bool LibrdfModel::operator==(const LibrdfModel &rhs) const {
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
        librdf_stream *this_stream = librdf_model_as_stream(model_);
        if (!this_stream) {
            std::cerr << "LibrdfModel::operator== Cannot create stream from model" << std::endl;
        } else {
            int count = 0;
            while (!librdf_stream_end(this_stream)) {
                librdf_statement *statement = librdf_stream_get_object(this_stream);
                if (!statement) {
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
        librdf_stream *rhs_stream = librdf_model_as_stream(rhs.model_);
        if (!rhs_stream) {
            std::cerr << "LibrdfModel::operator== Cannot create stream from model" << std::endl;
        } else {
            int count = 0;
            while (!librdf_stream_end(rhs_stream)) {
                librdf_statement *statement = librdf_stream_get_object(rhs_stream);
                if (!statement) {
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

    bool LibrdfModel::operator!=(const LibrdfModel &rhs) const {
        return !(rhs == *this);
    }

    librdf_storage *LibrdfModel::getStorage() const {
        return librdf_model_get_storage(get());
    }

    int LibrdfModel::commitTransaction() const {
        return librdf_model_transaction_commit(get());
    }

    int LibrdfModel::startTransaction() const {
        return librdf_model_transaction_start(get());
    }

    void *LibrdfModel::getTransactionHandle() const {
        return librdf_model_transaction_get_handle(get());
    }

    int LibrdfModel::startTransactionWithHandle(void *handle) const {
        return librdf_model_transaction_start_with_handle(get(), handle);
    }

    int LibrdfModel::getTransactionRollback() const {
        return librdf_model_transaction_rollback(get());
    }

    int LibrdfModel::supportsContexts() const {
        return librdf_model_supports_contexts(get());
    }
    bool LibrdfModel::containsStatement(librdf_statement *statement) const {
        bool contains_statement = false;
        librdf_stream *stream = librdf_model_as_stream(model_);
        if (!stream) {
            throw std::logic_error("LibrdfModel::containsStatement stream is nullptr");
        }

        // non-owning
        while (!librdf_stream_end(stream)) {
            // this is a non-owning pointer that apparently doesn't add to the ref count.
            // so don't free it.
            librdf_statement *proposal_statement = librdf_stream_get_object(stream);
            if (!proposal_statement) {
                throw std::logic_error("LibrdfModel::containsStatement proposal statement is nullptr");
            }

            if (LibrdfStatement::equals(statement, proposal_statement)) {
                contains_statement = true;
                break;
            }
            librdf_stream_next(stream);
        }
        librdf_free_stream(stream);
        return contains_statement;
    }

}// namespace redland
