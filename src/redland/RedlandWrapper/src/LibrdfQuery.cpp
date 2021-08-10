#include "redland/LibrdfQuery.h"
#include "redland/LibrdfQueryResults.h"
#include <redland/LibrdfException.h>
#include <redland/LibrdfModel.h>

namespace redland {

    bool LibrdfQuery::operator==(const LibrdfQuery &rhs) const {
        return obj_ == rhs.obj_;
    }

    bool LibrdfQuery::operator!=(const LibrdfQuery &rhs) const {
        return !(rhs == *this);
    };

    LibrdfQuery::LibrdfQuery(librdf_query *query, LibrdfModel& model)
        : RedlandType_librdf_query(query, librdf_free_query), model_(model) {}

    LibrdfQuery::LibrdfQuery(const std::string &query, LibrdfModel &model)
        : RedlandType_librdf_query(
                  librdf_new_query(
                          LibrdfWorld::getWorld(),
                          "sparql",
                          nullptr,
                          (const unsigned char *) query.c_str(),
                          nullptr),
                  librdf_free_query),
          query_(query), model_(model) {}

    LibrdfQueryResults LibrdfQuery::execute(){
        return LibrdfQueryResults(librdf_query_execute(obj_, model_.getWithoutIncrement()));
    }



    //
    //    ResultsMap LibrdfQuery::resultsAsMap() {
    //        ResultsMap map;
    //        // configure a data structure for storing the results
    //        // binding name is x, y, z of sparql query for example.
    //        for (int i = 0; i < queryResults_.getBindingsCount(); i++) {
    //            std::string binding_name = queryResults_.getBindingsName(i);
    //            map[binding_name] = std::vector<std::string>();
    //        }
    //
    //        // iterate over bindings until no more left
    //        bool done = false;
    //        while (!done) {
    //            for (auto &key : map) {
    //                map[key.first].push_back(queryResults_.getBindingValueByName(key.first));
    //            }
    //            int failed = queryResults_.next();
    //            if (failed) {
    //                done = true;
    //            }
    //        }
    //
    //        // we rerun the query to overwrite the serializer_
    //        // variable with a fresh object (since once you've
    //        // hit the end you can't seem to go back).
    //        // todo look more into this.
    //        runQuery();
    //        return map;
    //    }
    //
    //    void LibrdfQuery::runQuery() {
    //        // When we runQuery twice, we have memory leak if we do
    //        //  not free previous query results.
    ////        if (queryResults_.isNull() ) {
    ////            librdf_free_query_results(queryResults_.get());
    ////            queryResults_ = nullptr;
    ////        }
    //
    //        queryResults_ = LibrdfQueryResults(librdf_query_execute(q_, model_));
    //        if (queryResults_.isNull()) {
    //            throw NullPointerException("NullPointerException: LibrdfQuery::runQuery(): queryResults_");
    //        }
    //    }
    //
    //        ResultsMap resultsAsMap() ;{
    //            ResultsMap map;
    //            // configure a data structure for storing the results
    //            // binding name is x, y, z of sparql query for example.
    //            for (int i = 0; i < getBindingsCount(); i++) {
    //                std::string binding_name = getBindingsName(i);
    //                map[binding_name] = std::vector<std::string>();
    //            }
    //
    //            // iterate over bindings until no more left
    //            bool done = false;
    //            while (!done) {
    //                for (auto &key : map) {
    //                    map[key.first].push_back(getBindingValueByName(key.first));
    //                }
    //                int failed = next();
    //                if (failed) {
    //                    done = true;
    //                }
    //            }
    //
    //            // we rerun the query to overwrite the serializer_
    //            // variable with a fresh object (since once you've
    //            // hit the end you can't seem to go back).
    //            // todo look more into this.
    //            runQuery();
    //            return map;
    //        }
    //

}// namespace redland
