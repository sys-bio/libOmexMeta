//
// Created by ciaran on 16/08/2021.
//

#include "omexmeta/Query.h"
#include "redland/RedlandAPI.h"

namespace omexmeta {

    Query::Query(const std::string& query, const LibrdfModel& model)
        : query_(LibrdfQuery(query, model)), model_(model){
        results_ = query_.execute();
    }

    ResultsMap Query::asMap(){
        ResultsMap results =  results_.map();
        results_ = query_.execute();
        return results;
    }

    std::string Query::asString(const std::string& format){
        std::string resultsString = results_.toString(format);
        results_ = query_.execute();
        return resultsString;
    }

}