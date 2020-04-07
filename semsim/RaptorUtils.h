//
// Created by Ciaran on 4/6/2020.
//

#ifndef LIBSEMGEN_RAPTORUTILS_H
#define LIBSEMGEN_RAPTORUTILS_H

#include <string>
#include <raptor2.h>
#include "uri.h"

namespace semsim {
    class RaptorUtils {
    public:
        static std::string RaptorURIToString(raptor_uri *u);

        static Uri RaptorTermToURI(raptor_term *t);

        static raptor_uri* raptorStringToUri();

    };


    class RaptorStatementHandler {
    public:
        static void raptorStatementPrintAsNTriples(void *user_data, raptor_statement *triple);

        static void raptorStatementPrintStatement(void *user_data, raptor_statement *triple);

    };

}

#endif //LIBSEMGEN_RAPTORUTILS_H
