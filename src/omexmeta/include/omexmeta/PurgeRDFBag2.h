//
// Created by Ciaran on 21/04/2021.
//

#ifndef LIBOMEXMETA_PURGERDFBAG2_H
#define LIBOMEXMETA_PURGERDFBAG2_H

#include "omexmeta/IRDF.h"

namespace omexmeta {

    class IRDF;

    class PurgeRDFBag {
    public:
        /**
         * @brief constructor for PurgeRDFBag
         * @param rdf* non owning pointer to RDF object.
         * @details Since this class is designed to be used
         * by the rdf*, the private member variables rdf_ will
         * always live for longer than the lifetime of this class
         */
        explicit PurgeRDFBag(IRDF *rdf);

        void purge();


    private:
        IRDF* rdf_;
        unsigned int currentBlankId_ = 0;
    };
}// namespace omexmeta

#endif//LIBOMEXMETA_PURGERDFBAG_H
