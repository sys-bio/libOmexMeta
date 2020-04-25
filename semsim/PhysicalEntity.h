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

        PhysicalEntity(librdf_world *world, Subject metaid, PhysicalPropertyResource physicalProperty, Resource is,
                       Resources is_part_of);

        std::string createMetaId(std::string base_metaid) override;

        const Resource &getIdentityResource() const;

        const Resources &getLocationResources() const;

        std::vector<Triple> toTriples();

        Triple whatTriple();

        semsim::Triples whereTriple();


    };
}

#endif //LIBSEMGEN_PHYSICALENTITY_H
