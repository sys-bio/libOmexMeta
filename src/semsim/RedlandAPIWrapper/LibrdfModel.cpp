//
// Created by Ciaran on 5/17/2020.
//

#include "LibrdfModel.h"


namespace semsim {


    void LibrdfModel::deleter::operator()(librdf_model *model) {
        librdf_free_model(model);
    }

    LibrdfModel::LibrdfModel(librdf_model *model)
            : model_(model) {
    }

    LibrdfModel::LibrdfModel(LibrdfStorage storage, const char *options)
            : model_(librdf_new_model(World::getWorld(), std::move(storage).get(), options)) {}

    void LibrdfModel::addStatement(const LibrdfStatement &statement) const {
        librdf_model_add_statement(get(), statement.get());
    }

    librdf_model *LibrdfModel::get() const {
        return model_.get();
    }

    LibrdfQueryResults LibrdfModel::query(LibrdfQuery query) {
        librdf_query_results *results = librdf_query_execute(query.get(), model_.get());
        return LibrdfQueryResults(results);
    }


    // todo add wrapper around librdf_model_add_statement

}

