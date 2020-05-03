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

        PhysicalProcess(librdf_world *world, librdf_model *model);

        const Sources &getSources() const;

        const Sinks &getSinks() const;

        const Mediators &getMediators() const;

        Triples toTriples() const override;

        PhysicalProcess &setAbout(std::string metaid);

        PhysicalProcess &setPhysicalProperty(PhysicalPropertyResource physicalProperty);

        PhysicalProcess &addSource(std::string source_metaid, std::string source_identity, double multiplier,
                                   std::string physical_entity_reference);

        PhysicalProcess &addSink(std::string source_metaid, std::string sink_resource, double multiplier,
                                 std::string physical_entity_reference);

        PhysicalProcess &addMediator(std::string mediator_metaid, std::string mediator_resource, double multiplier,
                                     std::string physical_entity_reference);


        PhysicalProcess &setPhysicalProperty(const std::string &physicalProperty);
    };
}

#endif //LIBSEMGEN_PHYSICALPROCESS_H
