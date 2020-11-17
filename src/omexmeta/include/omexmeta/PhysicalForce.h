//
// Created by Ciaran on 4/22/2020.
//

#ifndef LIBOMEXMETA_PHYSICALFORCE_H
#define LIBOMEXMETA_PHYSICALFORCE_H


#include "redland/librdf.h"
#include "redland/RedlandAPI.h"

#include "omexmeta/PhysicalPhenomenon.h"
#include "omexmeta/Participant.h"
#include "omexmeta/PhysicalPhenomenon.h"
#include "omexmeta/Participant.h"
#include "omexmeta/Participant.h"
#include "omexmeta/PhysicalProperty.h"
#include "omexmeta/PhysicalPhenomenon.h"
#include "omexmeta/OmexMetaUtils.h"
#include "omexmeta_export.h"

#include <vector>
#include <utility>

using namespace redland;

namespace omexmeta {
    class OMEXMETA_EXPORT PhysicalForce : public PhysicalPhenomenon {

        Sources sources_;
        Sinks sinks_;
        std::string property_metaid_base_ = "ForceProperty"; // Empty for PhysicalPhenomenon but overridden by subclasses with values such as "EntityProperty"

    public:

        /**
         * @brief default constructor for PhysicalForce
         * @details deliberately deleted. If you try using the
         * builder interface (chaining setter methods) from a default
         * instantiated PhysicalForce you will get an error, because there
         * will be no model assicated with PhysicalForce. Instead, always
         * instantiate a PhysicalForce from the Editor::addPhysicalForce() method.
         */
        PhysicalForce() = delete;

        ~PhysicalForce() = default;


        PhysicalForce(librdf_model *model, std::string model_uri, std::string local_uri, PhysicalProperty physicalProperty, Sources sources,
                      Sinks sinks);

        /**
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

        /**
         * @brief constructor for instantiating a PhysicalForce type composite annotation
         * @param model. A librdf_model pass down by Editor.
         *
         * Users do not need to instantiate PhysicalForce manually, since it is done
         * by Editor. This constructor instantiates an empty PhysicalForce
         * object which is filled by
         *
         */
        OMEXMETA_DEPRECATED explicit PhysicalForce(librdf_model *model);

        /**
         * @brief constructor for instantiating a PhysicalForce type composite annotation
         * @param model. A librdf_model pass down by Editor.
         * @param model_uri. String passed down by Editor. The local uri to use for metaids
         *
         * Users do not need to instantiate PhysicalForce manually, since it is done
         * by Editor. This constructor instantiates an empty PhysicalForce
         * object which is filled by
         *
         */
        explicit PhysicalForce(librdf_model *model, const std::string& model_uri, const std::string& local_uri);

        /**
         * @brief create a metaid for the physical force annotation
         * @brief a new metaid for PhysicalForce
         */
        [[maybe_unused]] [[nodiscard]] std::string createMetaId();

        /**
         * @brief return vector of Source objects assocated with PhysicalForce
         * @return a vector of SourceParticipants
         */
        [[nodiscard]] const Sources &getSources() const;

        /**
         * @brief return vector of Sink objects assocated with PhysicalForce
         * @return a vector of SinkParticipants
         */
        [[nodiscard]] const Sinks &getSinks() const;

        /**
         * @brief converts the PhyicalForce object into a Triples object.
         * @return a Triples object containing the individual Triple objects of a PhysicalForce.
         *
         * When this method is called ownership of all RDF nodes gets transferred from
         * the caller to the returned Triples object.
         */
        [[nodiscard]] Triples toTriples() override;

        /**
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
        [[maybe_unused]] OMEXMETA_DEPRECATED PhysicalForce &setPhysicalProperty(PhysicalProperty physicalProperty);

        /**
         * @brief sets the physical property of the PhysicalForce
         * @param subject_metaid. The subject portion of the two triples produced by PhysicalProperty. Metaid of a model element.
         * @param A string representing the OPB term to use as the physical property. Like "OPB:OPB_1234"
         * @return a reference to this PhysicalForce to enable the builder interface.
         */
        OMEXMETA_DEPRECATED PhysicalForce &setPhysicalProperty(std::string subject_metaid, std::string physical_property);

        /**
         * @brief add a SourceParticipant to the PhysicalForce.
         * @param metaid the ID for the SourceParticipant.
         * @param multiplier The multiplier argument for SourceParticipant
         * @param physical_entity_reference The physicalEntityReference argument for
         * the SourceParticipant.
         * @return a reference to this PhysicalForce to enable the builder interface.
         *
         * See SourceParticipant documentation for more details on arguments.
         */
        PhysicalForce &addSource(const std::string &physical_entity_reference,  eUriType type,int multiplier);

        /**
         * @brief add a SinkParticipant to the PhysicalForce.
         * @param sink_metaid the ID for the SinkParticipant.
         * @param multiplier The multiplier argument for SinkParticipant
         * @param physical_entity_reference The physicalEntityReference argument for
         * the SinkParticipant.
         * @return a reference to this PhysicalForce to enable the builder interface.
         *
         * See SinkParticipant documentation for more details on arguments.
         */
        PhysicalForce &addSink(const std::string &physical_entity_reference,  eUriType type, int multiplier);

        /**
         * @brief returns the number of sources associated with the
         * PhysicalForce
         * @return the integer number of sources
         */
        int getNumSources();

        /**
         * @brief returns the number of sinks associated with the
         * PhysicalForce
         * @return the integer number of sinks
         */
        int getNumSinks();

        bool operator==(const PhysicalForce &rhs) const;

        bool operator!=(const PhysicalForce &rhs) const;

        /**
         * @brief set the isVersionOf portion of the PhysicalForce composite annotation
         * @param is_version_of the string to be used as the Resource portion of the isVersionOf Triple. This
         * should be of the form OPB:OPB_12345 or OPB/OPB_12345.
         * @details This method will set the Resource resource_ attribute of the PhysicalProperty
         * associated with the PhysicalProcess.
         */
        PhysicalForce &isVersionOf(const std::string &property);

        /**
         * @brief set the subject (rdf:about) portion of the PhysicalForce composite annotation
         * @param about the string to be used as the Subject portion of the isVersionOf Triple. This
         * should be an existing metaid on the model you are annotating. Will error when metaid does not exist.
         * @details This method will set the Subject subject_ attribute of the PhysicalProperty
         * associated with the PhysicalProcess.
         */
        PhysicalForce &about(const std::string &about, eUriType type = NONE);

//        PhysicalForce &hasProperty(const PhysicalProperty &property);
//
//        PhysicalForce &hasProperty(const std::string &property_about = "", eUriType about_uri_type = NONE);

        PhysicalForce &isPropertyOf(const std::string &is_property_of, eUriType type);

        PhysicalForce &propertyIsVersionOf(const std::string &is_version_of);

        [[nodiscard]] const std::string &getPropertyMetaidBase() const override;
    };
}

#endif //LIBOMEXMETA_PHYSICALFORCE_H
