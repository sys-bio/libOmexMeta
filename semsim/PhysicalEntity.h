//
// Created by Ciaran on 4/22/2020.
//

#ifndef LIBSEMGEN_PHYSICALENTITY_H
#define LIBSEMGEN_PHYSICALENTITY_H

#include <semsim/PhysicalPropertyResource.h>
#include "semsim/Resource.h"
#include "semsim/Subject.h"
#include "semsim/PhysicalPhenomenon.h"
#include "semsim/MetaID.h"

namespace semsim {
    class PhysicalEntity : public PhysicalPhenomenon {
    private:
        Resource is_;
        Resources isPartOf_;

        static std::vector<MetaID> metaid_;

    public:

        PhysicalEntity() = default;

        PhysicalEntity(librdf_world *world, librdf_model *model, Subject metaid, PhysicalPropertyResource physicalProperty, Resource is,
                       Resources is_part_of);

        std::string createMetaId() const;

        const Resource &getIdentityResource() const;

        const Resources &getLocationResources() const;

        Triples toTriples() const override ;

        Triple whatTriple() const;

        semsim::Triples whereTriple() const;

    };
}

#endif //LIBSEMGEN_PHYSICALENTITY_H
