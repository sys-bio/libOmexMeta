//
// Created by Ciaran on 4/22/2020.
//

#ifndef LIBSEMSIM_PHYSICALPROPERTYRESOURCE_H
#define LIBSEMSIM_PHYSICALPROPERTYRESOURCE_H

#include "semsim/Resource.h"
#include "semsim/RDFNode.h"
#include "semsim/Error.h"
#include "semsim/Triple.h"
#include "semsim/Triples.h"
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

#endif //LIBSEMSIM_PHYSICALPROPERTYRESOURCE_H
