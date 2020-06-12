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
#include "PhysicalProperty.h"
#include "PhysicalPhenomenon.h"
#include "SemsimUtils.h"

using namespace redland;

namespace semsim {
    class PhysicalForce : public PhysicalPhenomenon {

        Sources sources_;
        Sinks sinks_;

    public:

        /*
         * @brief default constructor for PhysicalForce
         * @details deliberately deleted. If you try using the
         * builder interface (chaining setter methods) from a default
         * instantiated PhysicalForce you will get an error, because there
         * will be no model assicated with PhysicalForce. Instead, always
         * instantiate a PhysicalForce from the Editor::addPhysicalForce() method.
         */
        PhysicalForce() = delete;

        ~PhysicalForce() = default;


        PhysicalForce(librdf_model *model, PhysicalProperty physicalProperty,
                      Sources sources, Sinks sinks);

        /*
         * @brief Free nodes associated with PhysicalForce.
         *
         * The PhysicalForce is
         * owned by the caller if the PhysicalForce::toTriples method is NOT used.
         * When toTriples() is used, the nodes that create the PhysicalForce are "given"
         * to the Triples object, which automatically destroys them at the right time.
         *
         * Most of the time, users will not have to remember to free the PhysicalForce themselves
         * as the toTriples method is always used.
         *
         */
        void free();

        /*
         * @brief constructor for instantiating a PhysicalForce type composite annotation
         * @param model. A librdf_model pass down by Editor.
         *
         * Users do not need to instantiate PhysicalForce manually, since it is done
         * by Editor. This constructor instantiates an empty PhysicalForce
         * object which is filled by
         *
         */
        explicit PhysicalForce(librdf_model *model);

        /*
         * @brief create a metaid for the physical force annotation
         * @brief a new metaid for PhysicalForce
         */
        [[maybe_unused]] [[nodiscard]] std::string createMetaId() const;

        /*
         * @brief return vector of Source objects assocated with PhysicalForce
         * @return a vector of SourceParticipants
         */
        [[nodiscard]] const Sources &getSources() const;

        /*
         * @brief return vector of Sink objects assocated with PhysicalForce
         * @return a vector of SinkParticipants
         */
        [[nodiscard]] const Sinks &getSinks() const;

        /*
         * @brief converts the PhyicalForce object into a Triples object.
         * @return a Triples object containing the individual Triple objects of a PhysicalForce.
         *
         * When this method is called ownership of all RDF nodes gets transferred from
         * the caller to the returned Triples object.
         */
        [[nodiscard]] Triples toTriples() override;

        /*
         * @brief sets the about field of the PhysicalForce
         * @param metaid id for the physical force. Result is relative to base_uri.
         * @return a reference to this PhysicalForce to enable the builder interface.
         *
         * A Resource object with a URI node is instantiated using the
         * the @param metaid.
         *
         * See Resource for more information about input format for @param metaid
         */
        PhysicalForce &setAbout(const std::string &metaid);

        /*
         * @brief sets the physical property of the PhysicalForce
         * @parameter physicalProperty An instance of PhysicalProperty representing the
         * physical property term for the PhysicalForce.
         * @return a reference to this PhysicalForce to enable the builder interface.
         *
         * Prefer the other setPhysicalProperty method since it only requires a
         * string input and instantiates the PhysicalProperty for you.
         *
         * For developers. Consider removing.
         */
        [[maybe_unused]] PhysicalForce &setPhysicalProperty(PhysicalProperty physicalProperty);

        /*
         * @brief sets the physical property of the PhysicalForce
         * @param subject_metaid. The subject portion of the two triples produced by PhysicalProperty. Metaid of a model element.
         * @param A string representing the OPB term to use as the physical property. Like "OPB:OPB_1234"
         * @return a reference to this PhysicalForce to enable the builder interface.
         */
        PhysicalForce &setPhysicalProperty(const std::string &subject_metaid, const std::string &physicalProperty);

        /*
         * @brief add a SourceParticipant to the PhysicalForce.
         * @param metaid the ID for the SourceParticipant.
         * @param multiplier The multiplier argument for SourceParticipant
         * @param physical_entity_reference The physicalEntityReference argument for
         * the SourceParticipant.
         * @return a reference to this PhysicalForce to enable the builder interface.
         *
         * See SourceParticipant documentation for more details on arguments.
         */
        PhysicalForce &addSource(std::string source_metaid, double multiplier,
                                 std::string physical_entity_reference);

        /*
         * @brief add a SinkParticipant to the PhysicalForce.
         * @param sink_metaid the ID for the SinkParticipant.
         * @param multiplier The multiplier argument for SinkParticipant
         * @param physical_entity_reference The physicalEntityReference argument for
         * the SinkParticipant.
         * @return a reference to this PhysicalForce to enable the builder interface.
         *
         * See SinkParticipant documentation for more details on arguments.
         */
        PhysicalForce &
        addSink(std::string sink_metaid, double multiplier,
                std::string physical_entity_reference);

        bool operator==(const PhysicalForce &rhs) const;

        bool operator!=(const PhysicalForce &rhs) const;

        /*
         * @brief returns the number of sources associated with the
         * PhysicalForce
         * @return the integer number of sources
         */
        int getNumSources();

        /*
         * @brief returns the number of sinks associated with the
         * PhysicalForce
         * @return the integer number of sinks
         */
        int getNumSinks();
    };
}

#endif //LIBSEMSIM_PHYSICALFORCE_H
