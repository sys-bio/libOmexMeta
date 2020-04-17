//
// Created by Ciaran on 4/4/2020.
//

#ifndef LIBSEMGEN_RESOURCE_H
#define LIBSEMGEN_RESOURCE_H

#include <iostream>
#include "semsim/Resource.h"
#include "semsim/uri.h"
#include "sstream"
#include "semsim/RDFTerm.h"

namespace semsim {
    class Resource {
        RDFTerm *rdf_term_ptr_;

    public:
        Resource(RDFTerm *rdf_term_ptr);

        Resource(const RDFTerm *rdf_term_ptr);

        ~Resource();

        Resource(const Resource &resource);

        Resource(const Resource &&resource) noexcept;

        Resource &operator=(const Resource &resource);

        Resource &operator=(Resource &&resource) noexcept;

        std::string str();

    };

}

#endif //LIBSEMGEN_RESOURCE_H

