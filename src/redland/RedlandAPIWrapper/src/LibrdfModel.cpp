//
// Created by Ciaran on 5/17/2020.
//

#include "LibrdfModel.h"


namespace redland {

    void LibrdfModel::freeModel() {
        if (model_ != nullptr) {
            librdf_free_model(model_);
        }
    }

    LibrdfModel::LibrdfModel(librdf_model *model)
            : model_(model) {
    }

//    LibrdfModel::~LibrdfModel() {
//        freeModel();
//    }

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


    void LibrdfModel::addStatement(const LibrdfStatement &statement) const {
//        std::cout << "Experimental free statement here2" << std::endl;
        librdf_model_add_statement(get(), statement.get());
//        librdf_free_statement(statement.get());
    }

    void LibrdfModel::addStatement(librdf_statement *statement) const {
        librdf_model_add_statement(get(), statement);
    }

    librdf_model *LibrdfModel::get() const {
        return model_;
    }

    LibrdfQueryResults LibrdfModel::query(const LibrdfQuery& query) const {
        librdf_query_results *results = librdf_query_execute(query.get(), model_);
        return LibrdfQueryResults(results);
    }

    int LibrdfModel::size() const {
        return librdf_model_size(model_);
    }

    LibrdfStream LibrdfModel::toStream() {
        LibrdfStream stream(librdf_model_as_stream(model_));
        if (!stream.get()) {
            throw RedlandNullPointerException("NullPointerException: LibrdfModel::toStream(): stream object null");
        }
        return stream;
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
        return model_ == rhs.model_;
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

    void* LibrdfModel::getTransactionHandle() const {
        return librdf_model_transaction_get_handle(get());
    }

    int LibrdfModel::startTransactionWithHandle(void* handle) const {
        return librdf_model_transaction_start_with_handle(get(), handle);
    }

    int LibrdfModel::getTransactionRollback() const {
        return librdf_model_transaction_rollback(get());
    }

}

