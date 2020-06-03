//
// Created by Ciaran on 4/22/2020.
//

#ifndef LIBSEMSIM_PHYSICALENTITY_H
#define LIBSEMSIM_PHYSICALENTITY_H

#include <semsim/PhysicalPropertyResource.h>
#include "semsim/Resource.h"
#include "semsim/Subject.h"
#include "semsim/PhysicalPhenomenon.h"
#include "semsim/MetaID.h"
#include "RedlandAPIWrapper.h"
#include <utility>
#include "semsim/Triple.h"
#include "semsim/Query.h"
#include "semsim/SemsimUtils.h"
#include "memory"

using namespace redland;

namespace semsim {
    class PhysicalEntity : public PhysicalPhenomenon {
    private:
        Resource identity_resource_;
        Resources location_resources;
        std::string resource;

    public:

        PhysicalEntity() = default;

        ~PhysicalEntity() = default;

        void free() override ;

        PhysicalEntity(librdf_model* model, Subject about,
                       PhysicalPropertyResource physicalProperty, Resource is,
                       Resources is_part_of);


        explicit PhysicalEntity(librdf_model* model);

        [[nodiscard]] Triples toTriples() override;

        [[nodiscard]] const Resource &getIdentityResource() const;

        [[nodiscard]] const Resources &getLocationResources() const;

        PhysicalEntity &setAbout(std::string metaid);

        PhysicalEntity &setPhysicalProperty(PhysicalPropertyResource physicalProperty);

        PhysicalEntity &setIdentity(std::string resource);

        PhysicalEntity &addLocation(std::string where);

        PhysicalEntity &setPhysicalProperty(const std::string &physicalProperty);

        [[maybe_unused]] int getNumLocations() const;
    };
}

#endif //LIBSEMSIM_PHYSICALENTITY_H
