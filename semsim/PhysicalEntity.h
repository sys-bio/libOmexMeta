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
        Resource identity_resource_;
        Resources location_resources;
        std::string resource;

    public:

        PhysicalEntity() = default;

        PhysicalEntity(librdf_world *world, librdf_model *model, Subject metaid,
                       PhysicalPropertyResource physicalProperty, Resource is,
                       Resources is_part_of);


        PhysicalEntity(librdf_world *world, librdf_model *model);

        Triples toTriples() const override;

        const Resource &getIdentityResource() const;

        const Resources &getLocationResources() const;

        PhysicalEntity &setAbout(std::string metaid);

        PhysicalEntity & setPhysicalProperty(PhysicalPropertyResource physicalProperty);

        PhysicalEntity & setIdentity(std::string resource);

        PhysicalEntity & addLocation(std::string where);

    };
}

#endif //LIBSEMGEN_PHYSICALENTITY_H
