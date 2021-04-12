//
// Created by Ciaran on 4/22/2020.
//

#ifndef LIBOMEXMETA_ENERGYDIFF_H
#define LIBOMEXMETA_ENERGYDIFF_H


#include "redland/librdf.h"
#include "redland/RedlandAPI.h"

#include "omexmeta/OmexMetaUtils.h"
#include "omexmeta/Participant.h"
#include "omexmeta/PhysicalProperty.h"
#include "omexmeta/PropertyBearer.h"
#include "omexmeta_export.h"

#include <vector>
#include <utility>

using namespace redland;

namespace omexmeta {
    class OMEXMETA_EXPORT EnergyDiff : public PropertyBearer {

        Sources sources_;
        Sinks sinks_;
        std::string property_metaid_base_ = "EnergyDiffProperty"; // Empty for PhysicalPhenomenon but overridden by subclasses with values such as "EntityProperty"

    public:

        /**
         * @brief default constructor for EnergyDiff
         * @details deliberately deleted. If you try using the
         * builder interface (chaining setter methods) from a default
         * instantiated EnergyDiff you will get an error, because there
         * will be no model assicated with EnergyDiff. Instead, always
         * instantiate a EnergyDiff from the Editor::addEnergyDiff() method.
         */
        EnergyDiff() = delete;

        ~EnergyDiff() = default;


        [[deprecated("EnergyDiff(librdf_model *model, UriHandler uriHandler, PhysicalProperty physicalProperty, Sources sources,\n"
                     "                      Sinks sinks);")]] EnergyDiff(librdf_model *model, std::string model_uri, std::string local_uri, PhysicalProperty physicalProperty, Sources sources,
                      Sinks sinks);

        EnergyDiff(librdf_model *model, UriHandler uriHandler, PhysicalProperty physicalProperty, Sources sources,
                      Sinks sinks);

        /**
         * @brief Free nodes associated with EnergyDiff.
         *
         * The EnergyDiff is
         * owned by the caller if the EnergyDiff::toTriples method is NOT used.
         * When toTriples() is used, the nodes that create the EnergyDiff are "given"
         * to the Triples object, which automatically destroys them at the right time.
         *
         * Most of the time, users will not have to remember to free the EnergyDiff themselves
         * as the toTriples method is always used.
         *
         */
        void free();

        /**
         * @brief constructor for instantiating a EnergyDiff type composite annotation
         * @param model. A librdf_model pass down by Editor.
         *
         * Users do not need to instantiate EnergyDiff manually, since it is done
         * by Editor. This constructor instantiates an empty EnergyDiff
         * object which is filled by
         *
         */
        OMEXMETA_DEPRECATED explicit EnergyDiff(librdf_model *model);

        /**
         * @brief constructor for instantiating a EnergyDiff type composite annotation
         * @param model. A librdf_model pass down by Editor.
         * @param model_uri. String passed down by Editor. The local uri to use for metaids
         *
         * Users do not need to instantiate EnergyDiff manually, since it is done
         * by Editor. This constructor instantiates an empty EnergyDiff
         * object which is filled by
         *
         */
        [[deprecated("EnergyDiff::EnergyDiff(librdf_model *model, UriHandler uriHandler")]] explicit EnergyDiff(librdf_model *model, const std::string& model_uri, const std::string& local_uri);

        explicit EnergyDiff(librdf_model *model, UriHandler uriHandler);

        /**
         * @brief create a metaid for the energy differential annotation
         * @brief a new metaid for EnergyDiff
         */
        [[maybe_unused]] [[nodiscard]] std::string createMetaId();

        /**
         * @brief return vector of Source objects assocated with EnergyDiff
         * @return a vector of SourceParticipants
         */
        [[nodiscard]] const Sources &getSources() const;

        /**
         * @brief return vector of Sink objects assocated with EnergyDiff
         * @return a vector of SinkParticipants
         */
        [[nodiscard]] const Sinks &getSinks() const;

        /**
         * @brief converts the PhyicalForce object into a Triples object.
         * @return a Triples object containing the individual Triple objects of a EnergyDiff.
         *
         * When this method is called ownership of all RDF nodes gets transferred from
         * the caller to the returned Triples object.
         */
        [[nodiscard]] Triples toTriples() override;

        /**
         * @brief sets the physical property of the EnergyDiff
         * @parameter physicalProperty An instance of PhysicalProperty representing the
         * physical property term for the EnergyDiff.
         * @return a reference to this EnergyDiff to enable the builder interface.
         *
         * Prefer the other setPhysicalProperty method since it only requires a
         * string input and instantiates the PhysicalProperty for you.
         *
         * For developers. Consider removing.
         */
        [[maybe_unused]] OMEXMETA_DEPRECATED EnergyDiff &setPhysicalProperty(PhysicalProperty physicalProperty);

        /**
         * @brief sets the physical property of the EnergyDiff
         * @param subject_metaid. The subject portion of the two triples produced by PhysicalProperty. Metaid of a model element.
         * @param A string representing the OPB term to use as the physical property. Like "OPB:OPB_1234"
         * @return a reference to this EnergyDiff to enable the builder interface.
         */
        OMEXMETA_DEPRECATED EnergyDiff &setPhysicalProperty(std::string subject_metaid, std::string physical_property);

        /**
         * @brief add a SourceParticipant to the EnergyDiff.
         * @param metaid the ID for the SourceParticipant.
         * @param multiplier The multiplier argument for SourceParticipant
         * @param physical_entity_reference The physicalEntityReference argument for
         * the SourceParticipant.
         * @return a reference to this EnergyDiff to enable the builder interface.
         *
         * See SourceParticipant documentation for more details on arguments.
         */
        EnergyDiff &addSource(const std::string &physical_entity_reference,  eUriType type);

        /**
         * @brief add a SinkParticipant to the EnergyDiff.
         * @param sink_metaid the ID for the SinkParticipant.
         * @param multiplier The multiplier argument for SinkParticipant
         * @param physical_entity_reference The physicalEntityReference argument for
         * the SinkParticipant.
         * @return a reference to this EnergyDiff to enable the builder interface.
         *
         * See SinkParticipant documentation for more details on arguments.
         */
        EnergyDiff &addSink(const std::string &physical_entity_reference,  eUriType type);

        /**
         * @brief returns the number of sources associated with the
         * EnergyDiff
         * @return the integer number of sources
         */
        int getNumSources();

        /**
         * @brief returns the number of sinks associated with the
         * EnergyDiff
         * @return the integer number of sinks
         */
        int getNumSinks();

        bool operator==(const EnergyDiff &rhs) const;

        bool operator!=(const EnergyDiff &rhs) const;

        /**
         * @brief set the isVersionOf portion of the EnergyDiff composite annotation
         * @param is_version_of the string to be used as the Resource portion of the isVersionOf Triple. This
         * should be of the form OPB:OPB_12345 or OPB/OPB_12345.
         * @details This method will set the Resource resource_ attribute of the PhysicalProperty
         * associated with the PhysicalProcess.
         */
        EnergyDiff &isVersionOf(const std::string &property);

        /**
         * @brief set the subject (rdf:about) portion of the EnergyDiff composite annotation
         * @param about the string to be used as the Subject portion of the isVersionOf Triple. This
         * should be an existing metaid on the model you are annotating. Will error when metaid does not exist.
         * @details This method will set the Subject subject_ attribute of the PhysicalProperty
         * associated with the PhysicalProcess.
         */
        EnergyDiff &about(const std::string &about, eUriType type) override;

        EnergyDiff &about(const std::string &about) override;

        EnergyDiff &isPropertyOf(const std::string &is_property_of, eUriType type);

        EnergyDiff &propertyIsVersionOf(const std::string &is_version_of);

        [[nodiscard]] const std::string &getPropertyMetaidBase() const override;


        EnergyDiff &hasProperty(const PhysicalProperty &property) override;

        EnergyDiff &hasProperty(const std::string &property_about, eUriType about_uri_type, const std::string& is_version_of, const std::string& is_property_of, eUriType is_property_of_uri_type) override;

        EnergyDiff &hasProperty(const std::string &is_version_of) override;

        EnergyDiff &hasProperty(const std::string &property_about, eUriType about_uri_type, const std::string &is_version_of) override;

    };
}

#endif//LIBOMEXMETA_ENERGYDIFF_H
