//
// Created by Ciaran on 4/22/2020.
//

#ifndef LIBSEMGEN_PHYSICALPROPERTYRESOURCE_H
#define LIBSEMGEN_PHYSICALPROPERTYRESOURCE_H

#include "Resource.h"
#include "RDFNode.h"
#include "Error.h"
#include "Triple.h"
#include "Triples.h"
#include "semsim/RedlandAPIWrappers/RedlandAPIWrapper.h"
#include "Triple.h"
#include "Triples.h"
#include <regex>

namespace semsim {
    class PhysicalPropertyResource : public Resource {

        void validate();

    public:

        PhysicalPropertyResource() = default;

        explicit PhysicalPropertyResource(LibrdfWorld world, RDFURINode node);

        explicit PhysicalPropertyResource(LibrdfWorld world, std::string node);

        Triple isVersionOfTriple(std::string subject_metaid) const;

        Triple isPropertyOfTriple(std::string subject_metaid, std::string property_metaid) const;

        Triples toTriples(std::string subject_metaid, std::string property_metaid) const;

        bool isSet() const override ;
    };
}

#endif //LIBSEMGEN_PHYSICALPROPERTYRESOURCE_H
