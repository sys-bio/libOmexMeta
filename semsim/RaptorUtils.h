//
// Created by Ciaran on 4/6/2020.
//

#ifndef LIBSEMGEN_RAPTORUTILS_H
#define LIBSEMGEN_RAPTORUTILS_H

#include <string>
#include <raptor2.h>
#include "uri.h"

namespace semsim {
    /*
     * A set of static utility functions for interfacing with
     * raptor library. Mostly these are not stictly necessary
     * since it is possible to just use the raptor library directly.
     * However, havng these functions here is convenient for
     * remembering how to use the raptor library.
     */
    class RaptorUtils {
    public:
        static std::string raptorUriToString(raptor_uri *u);

        static raptor_uri *raptorStringToUri(raptor_world *world, const unsigned char *str);

        static raptor_term *raptorUriToTerm(raptor_world *world, raptor_uri *uri);

        static const unsigned char *raptorTermToString(raptor_term *term);

    };



}

#endif //LIBSEMGEN_RAPTORUTILS_H
