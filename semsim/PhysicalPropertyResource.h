//
// Created by Ciaran on 4/22/2020.
//

#ifndef LIBSEMGEN_PHYSICALPROPERTYRESOURCE_H
#define LIBSEMGEN_PHYSICALPROPERTYRESOURCE_H

#include "semsim/Resource.h"
#include "semsim/RDFNode.h"
#include "semsim/Error.h"
#include "semsim/Triple.h"

namespace semsim {
    class PhysicalPropertyResource : public Resource {

        void validate();

    public:

        PhysicalPropertyResource() = default;

        explicit PhysicalPropertyResource(librdf_world *world, RDFURINode node);

        explicit PhysicalPropertyResource(librdf_world *world, std::string node);

        Triple toIsVersionOfTriple(Subject subject_metaid) const;

        Triple toIsVersionOfTriple(std::string subject_metaid) const;
    };
}

#endif //LIBSEMGEN_PHYSICALPROPERTYRESOURCE_H
