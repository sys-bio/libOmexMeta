//
// Created by Ciaran on 4/22/2020.
//

#ifndef LIBSEMSIM_PHYSICALPROCESS_H
#define LIBSEMSIM_PHYSICALPROCESS_H

#include "PhysicalPhenomenon.h"
#include "Participant.h"
#include "RedlandAPIWrapper.h"
#include <vector>
#include "Participant.h"
#include "PhysicalPropertyResource.h"
#include "PhysicalPhenomenon.h"
#include "SemsimUtils.h"

using namespace redland;

namespace semsim {
    class PhysicalProcess : public PhysicalPhenomenon {
    private:
        Sources sources_;
        Sinks sinks_;
        Mediators mediators_;


    public:

        PhysicalProcess() = delete;

        ~PhysicalProcess() = default;

        void free();

        PhysicalProcess(librdf_model* model, Subject metaid,
                        PhysicalPropertyResource physicalProperty, Sources sources, Sinks sinks,
                        Mediators mediators);

        PhysicalProcess(librdf_model* model);

        const Sources &getSources() const;

        const Sinks &getSinks() const;

        const Mediators &getMediators() const;

        Triples toTriples() const override;

        PhysicalProcess &setAbout(std::string metaid);

        PhysicalProcess &setPhysicalProperty(PhysicalPropertyResource physicalProperty);

        PhysicalProcess &addSource(std::string source_metaid, double multiplier, std::string physical_entity_reference);

        PhysicalProcess &addSink(std::string sink_metaid, double multiplier, std::string physical_entity_reference);

        PhysicalProcess &addMediator(
                std::string mediator_metaid, double multiplier, std::string physical_entity_reference);

        PhysicalProcess &setPhysicalProperty(const std::string &physicalProperty);

        int getNumSources();

        int getNumSinks();

        int getNumMediators();
    };
}

#endif //LIBSEMSIM_PHYSICALPROCESS_H
