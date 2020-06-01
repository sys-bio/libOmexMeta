//
// Created by Ciaran on 4/22/2020.
//

#ifndef LIBSEMSIM_PHYSICALFORCE_H
#define LIBSEMSIM_PHYSICALFORCE_H


#include "PhysicalPhenomenon.h"
#include "Participant.h"
#include "librdf.h"


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
    class PhysicalForce : public PhysicalPhenomenon {

        Sources sources_;
        Sinks sinks_;

    public:

        PhysicalForce() = delete;

        PhysicalForce(const LibrdfModel& model, Subject metaid, PhysicalPropertyResource physicalProperty,
                      Sources sources, Sinks sinks);

        PhysicalForce(const LibrdfModel& model);

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

#endif //LIBSEMSIM_PHYSICALFORCE_H
