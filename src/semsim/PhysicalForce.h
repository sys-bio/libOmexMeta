//
// Created by Ciaran on 4/22/2020.
//

#ifndef LIBSEMGEN_PHYSICALFORCE_H
#define LIBSEMGEN_PHYSICALFORCE_H


#include "PhysicalPhenomenon.h"
#include "Participant.h"
#include "librdf.h"


#include "PhysicalPhenomenon.h"
#include "Participant.h"

namespace semsim {
    class PhysicalForce : public PhysicalPhenomenon {

        Sources sources_;
        Sinks sinks_;

    public:

        PhysicalForce() = default;

        PhysicalForce(librdf_world *world, librdf_model *model, Subject metaid, PhysicalPropertyResource physicalProperty,
                      Sources sources, Sinks sinks);

        PhysicalForce(librdf_world *world, librdf_model *model);

        std::string createMetaId() const;

        const Sources &getSources() const;

        const Sinks &getSinks() const;

        Triples toTriples() const override;

        PhysicalForce &setAbout(std::string metaid);

        PhysicalForce &setPhysicalProperty(PhysicalPropertyResource physicalProperty);

        PhysicalForce &addSource(std::string source_metaid, double multiplier,
                                 std::string physical_entity_reference);

        PhysicalForce &
        addSink(std::string sink_metaid, double multiplier,
                std::string physical_entity_reference);

        PhysicalForce &setPhysicalProperty(const std::string &physicalProperty);

        int getNumSources();

        int getNumSinks();
    };
}

#endif //LIBSEMGEN_PHYSICALFORCE_H
