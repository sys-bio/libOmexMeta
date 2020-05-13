//
// Created by Ciaran on 5/8/2020.
//

#include "SemsimCApi.h"
#include <iostream>
#include <cstring>
#include "semsim/SemsimUtils.h"

namespace semsim {
    semsim::RDF *RDF_new_ptr() {
        return new semsim::RDF();
    }

    void RDF_free(semsim::RDF *rdf_ptr) {
        free(rdf_ptr);
    }

    void RDF_fromString(semsim::RDF *rdf_ptr, const char *str, const char *format) {
        semsim::RDF rdf = semsim::RDF::fromString(str, format);
        *rdf_ptr = rdf;
    }

    const char *RDF_toString(semsim::RDF *rdf_ptr, const char *format, const char *base_uri) {
        // do not return a temporary object:
        static std::string s = rdf_ptr->toString(format, base_uri);
        const char *output_str = (const char *) s.c_str();
        return output_str;
    }

    char *RDF_getBaseUri(semsim::RDF *rdf_ptr) {
        std::string str = rdf_ptr->getBaseUriAsString();
        char *cstr = (char *) malloc(str.size());
        strcpy(cstr, str.c_str());
        return cstr;
    }

    void RDF_setBaseUri(semsim::RDF *rdf_ptr, const char *uri) {
        rdf_ptr->setBaseUri(uri);
    }

    const char *RDF_queryResultsAsStr(semsim::RDF *rdf_ptr, const char *query_str, const char *results_format) {
        static std::string query_results = rdf_ptr->queryResultsAsStr(query_str, results_format);
        return query_results.c_str();
    }

    int RDF_size(semsim::RDF *rdf_ptr) {
        return rdf_ptr->size();
    }

}































