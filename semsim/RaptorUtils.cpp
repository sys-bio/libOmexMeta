//
// Created by Ciaran on 4/6/2020.
//

#include "RaptorUtils.h"

namespace semsim {
    Uri RaptorUtils::RaptorTermToURI(raptor_term *t) {
        if (!t)
            throw std::runtime_error("Raptor term is null");
        switch (t->type) {
            case RAPTOR_TERM_TYPE_URI:
                return Uri(RaptorURIToString(t->value.uri));
            default:
                throw std::runtime_error("Raptor term is wrong type - not a URI");
        }
    };

    std::string RaptorUtils::RaptorURIToString(raptor_uri *u) {
        unsigned char *c = raptor_uri_to_string(u);
        std::string result((const char *) c);
        raptor_free_memory(c);
        return result;
    }

     void RaptorStatementHandler::raptorStatementPrintAsNTriples(void *user_data, raptor_statement *triple) {
         raptor_statement_print_as_ntriples(triple, stdout);
         fputc('\n', stdout);
     }


    void RaptorStatementHandler::raptorStatementPrintStatement(void *user_data, raptor_statement *triple) {
        raptor_statement_print(triple, stdout);
        fputc('\n\n', stdout);
    }

}