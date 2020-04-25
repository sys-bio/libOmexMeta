//
// Created by Ciaran on 4/22/2020.
//

#ifndef LIBSEMGEN_PHYSICALFORCE_H
#define LIBSEMGEN_PHYSICALFORCE_H


#include "semsim/PhysicalPhenomenon.h"
#include "semsim/Participant.h"
#include "librdf.h"


#include "semsim/PhysicalPhenomenon.h"
#include "semsim/Participant.h"

namespace semsim {
    class PhysicalForce : public PhysicalPhenomenon {

        Sources sources_;
        Sinks sinks_;

    public:

        PhysicalForce() = default;

        PhysicalForce(librdf_world *world, Subject metaid, PhysicalPropertyResource physicalProperty,
                      Sources sources, Sinks sinks);

        std::string createMetaId(std::string base_metaid) override;

        const Sources &getSources() const;

        const Sinks &getSinks() const;

        Triples toTriples() const override;
    };
}

#endif //LIBSEMGEN_PHYSICALFORCE_H
