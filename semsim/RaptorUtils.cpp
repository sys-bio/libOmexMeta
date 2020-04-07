//
// Created by Ciaran on 4/6/2020.
//

#include "RaptorUtils.h"

namespace semsim {

    raptor_uri *RaptorUtils::raptorStringToUri(raptor_world *world, const unsigned char *str) {
        return raptor_new_uri(world, str);
    }

    std::string RaptorUtils::raptorUriToString(raptor_uri *u) {
        unsigned char *c = raptor_uri_to_string(u);
        std::string result((const char *) c);
        raptor_free_memory(c);
        return result;
    }

    raptor_term *RaptorUtils::raptorUriToTerm(raptor_world *world, raptor_uri *uri) {
        return raptor_new_term_from_uri(world, uri);
    }

    const unsigned char *RaptorUtils::raptorTermToString(raptor_term *term) {
        return raptor_term_to_string(term);
    }


    void RaptorStatementHandler::raptorStatementPrintAsNTriples(void *user_data, raptor_statement *triple) {
        raptor_statement_print_as_ntriples(triple, stdout);
        fputc('\n', stdout);
    }


    void RaptorStatementHandler::raptorStatementPrintStatement(void *user_data, raptor_statement *triple) {
        raptor_statement_print(triple, stdout);
        fputc('\n', stdout);
    }

}