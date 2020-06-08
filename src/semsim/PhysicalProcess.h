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


        /*
         * @brief Constructor for PhysicalProcess object. Subclass of PhysicalPhenomenon.
         * @param model a librdf_model pointer for current rdf graph.
         * @param physicalProperty the physical property for the PhysicalProcess
         * @param sources a vector of Source objects representing the energetic sources for the PhysicalProcess
         * @param sinks a vector of Sink objects representing the energetic sinks for the PhysicalProcess
         * @param mediator a vector of Sink objects representing the energetic modulators for the PhysicalProcess
         */
        PhysicalProcess(librdf_model* model, Subject metaid,
                        PhysicalPropertyResource physicalProperty, Sources sources, Sinks sinks,
                        Mediators mediators);

        /*
         * @brief free the node resources used by PhysicalProcess.
         *
         * When the toTriples() method is used, ownership of the nodes associated with
         * PhysicalProcess are transferred to the resulting Triples object, which
         * destroys them automatically at the right time. If user does not use the
         * toTriples method, then resources used by PhysicalProcess must be freed manually
         * with this method.
         */
        void free();

        /*
         * @brief constructor for the builder interface of PhysicalProcess instantiation
         * @param model the currently active RDF model.
         */
        PhysicalProcess(librdf_model* model);

        /*
         * @brief getter for sources
         */
        const Sources &getSources() const;

        /*
         * @brief getter for sinks
         */
        const Sinks &getSinks() const;

        /*
         * @brief getter for mediators
         */
        const Mediators &getMediators() const;

        /*
         * @brief convert a PhysicalProcess into a set of Triples
         *
         * When used, the ownership of nodes in PhysicalProcess are pass
         * to the Triples object, which automatically destroys them when appropriate.
         * Otherwise the caller is responsible for freeing resources.
         */
        Triples toTriples();

        /*
         * @brief setter for the about portion of the PhysicalProcess.
         */
        PhysicalProcess &setAbout(std::string metaid);

        /*
         * @brief setter for the physical property portion of the PhysicalProcess.
         */
        PhysicalProcess &setPhysicalProperty(const std::string &physicalProperty);

        /*
         * @brief setter for the physical property portion of the PhysicalProcess.
         *
         * Developers. Consider removing this method in favour of the
         * setPhysicalProperty version that only takes a string as argument
         */
        PhysicalProcess &setPhysicalProperty(PhysicalPropertyResource physicalProperty);

        /*
         * @brief add a source to the list of Source object associated with a PhysicalProcess
         */
        PhysicalProcess &addSource(std::string source_metaid, double multiplier, std::string physical_entity_reference);

        /*
         * @brief add a sink to the list of Source object associated with a PhysicalProcess
         */
        PhysicalProcess &addSink(std::string sink_metaid, double multiplier, std::string physical_entity_reference);

        /*
         * @brief add a mediator to the list of Source object associated with a PhysicalProcess
         */
        PhysicalProcess &addMediator(
                std::string mediator_metaid, double multiplier, std::string physical_entity_reference);

        /*
         * @brief returns the number of sources assocaited with the PhysicalProcess
         */
        int getNumSources();

        /*
         * @brief returns the number of sinks assocaited with the PhysicalProcess
         */
        int getNumSinks();

        /*
         * @brief returns the number of mediators assocaited with the PhysicalProcess
         */
        int getNumMediators();
    };
}

#endif //LIBSEMSIM_PHYSICALPROCESS_H
