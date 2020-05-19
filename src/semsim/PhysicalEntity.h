//
// Created by Ciaran on 4/22/2020.
//

#ifndef LIBSEMGEN_PHYSICALENTITY_H
#define LIBSEMGEN_PHYSICALENTITY_H

#include <semsim/PhysicalPropertyResource.h>
#include "Resource.h"
#include "Subject.h"
#include "PhysicalPhenomenon.h"
#include "MetaID.h"
#include "semsim/RelandAPIWrappers/RedlandAPIWrapper.h"

namespace semsim {
    class PhysicalEntity : public PhysicalPhenomenon {
    private:
        Resource identity_resource_;
        Resources location_resources;
        std::string resource;

    public:

        PhysicalEntity() = default;

        PhysicalEntity(LibrdfWorld world, LibrdfModel model, Subject metaid,
                       PhysicalPropertyResource physicalProperty, Resource is,
                       Resources is_part_of);


        PhysicalEntity(LibrdfWorld world, LibrdfModel model);

        Triples toTriples() const override;

        const Resource &getIdentityResource() const;

        const Resources &getLocationResources() const;

        PhysicalEntity &setAbout(std::string metaid);

        PhysicalEntity &setPhysicalProperty(PhysicalPropertyResource physicalProperty);

        PhysicalEntity &setIdentity(std::string resource);

        PhysicalEntity &addLocation(std::string where);

        PhysicalEntity &setPhysicalProperty(const std::string &physicalProperty);

        int getNumLocations();
    };
}

#endif //LIBSEMGEN_PHYSICALENTITY_H
