//
// Created by Ciaran on 4/22/2020.
//

#ifndef LIBSEMGEN_PHYSICALPROCESS_H
#define LIBSEMGEN_PHYSICALPROCESS_H

#include "semsim/PhysicalPhenomenon.h"
#include "semsim/Participant.h"

namespace semsim {
    class PhysicalProcess : public PhysicalPhenomenon {
    private:
        Sources sources_;
        Sinks sinks_;
        Mediators mediators_;

    public:

        PhysicalProcess() = default;

        PhysicalProcess(librdf_world *world, librdf_model *model, Subject metaid,
                        PhysicalPropertyResource physicalProperty, Sources sources, Sinks sinks,
                        Mediators mediators);

        const Sources &getSources() const;

        const Sinks &getSinks() const;

        const Mediators &getMediators() const;

        Triples toTriples() const override;

        std::string createMetaId() const;
    };
}

#endif //LIBSEMGEN_PHYSICALPROCESS_H
