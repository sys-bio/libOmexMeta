//
// Created by Ciaran on 4/22/2020.
//

#ifndef LIBOMEXMETA_PHYSICALPROCESS_H
#define LIBOMEXMETA_PHYSICALPROCESS_H

#include "redland/RedlandAPI.h"

#include "omexmeta/OmexMetaUtils.h"
#include "omexmeta/Participant.h"
#include "omexmeta/PhysicalProperty.h"
#include "omexmeta/PropertyBearer.h"
#include "omexmeta_export.h"

#include <utility>
#include <vector>

using namespace redland;

namespace omexmeta {
    class OMEXMETA_EXPORT PhysicalProcess : public PropertyBearer {
    private:
        Sources sources_;
        Sinks sinks_;
        Mediators mediators_;
        std::string is_version_of_;// optional class level attribute to store the isVErsionOf under the process ID.
        std::string property_metaid_base_ = "ProcessProperty";

    public:
        /**
         * @brief default constructor for PhysicalProcess
         * @details deliberately deleted. If you try using the
         * builder interface (chaining setter methods) from a default
         * instantiated PhysicalProcess you will get an error, because there
         * will be no model associated with PhysicalProcess. Instead, always
         * instantiate a PhysicalProcess from the Editor::addPhysicalProcess() method.
         */
        PhysicalProcess() = delete;

        ~PhysicalProcess() = default;


        /**
         * @brief Constructor for PhysicalProcess object. Subclass of PhysicalPhenomenon.
         * @param model a librdf_model pointer for current rdf graph.
         * @param physicalProperty the physical property for the PhysicalProcess
         * @param sources a vector of Source objects representing the energetic sources for the PhysicalProcess
         * @param sinks a vector of Sink objects representing the energetic sinks for the PhysicalProcess
         * @param mediator a vector of Sink objects representing the energetic modulators for the PhysicalProcess
         *
         */
        PhysicalProcess(librdf_model *model, std::string model_uri, std::string local_uri, const PhysicalProperty &physicalProperty,
                        Sources sources, Sinks sinks, Mediators mediators);

        /**
         * @brief free the node resources used by PhysicalProcess.
         *
         * When the toTriples() method is used, ownership of the nodes associated with
         * PhysicalProcess are transferred to the resulting Triples object, which
         * destroys them automatically at the right time. If user does not use the
         * toTriples method, then resources used by PhysicalProcess must be freed manually
         * with this method.
         */
        void free();

        /**
         * @brief constructor for the builder interface of PhysicalProcess instantiation
         * @param model the currently active RDF model.
         */
        OMEXMETA_DEPRECATED explicit PhysicalProcess(librdf_model *model);

        /**
         * @brief constructor for the builder interface of PhysicalProcess instantiation
         * @param model the currently active RDF model.
         * @param model_uri the local uri in current use.
         */
        explicit PhysicalProcess(librdf_model *model, std::string model_uri, std::string local_uri);

        /**
         * @brief getter for sources
         * @return a vector of SourceParticipant objects
         */
        [[nodiscard]] const Sources &getSources() const;

        /**
         * @brief getter for sinks
         * @return a vector of SinkParticipant objects
         */
        [[nodiscard]] const Sinks &getSinks() const;

        /**
         * @brief getter for mediators
         * @return a vector of MediatorParticipant objects
         */
        [[nodiscard]] const Mediators &getMediators() const;

        /**
         * @brief convert a PhysicalProcess into a set of Triples
         * @return A Triples object containing the set of Triple objects that represent this PhysicalProcess
         *
         * When used, the ownership of nodes in PhysicalProcess are pass
         * to the Triples object, which automatically destroys them when appropriate.
         * Otherwise the caller is responsible for freeing resources.
         */
        Triples toTriples() override;

        /**
         * @brief setter for the physical property portion of the PhysicalProcess.
         * @return a reference to this PhysicalProcess to enable chaining setter commands
         */
        OMEXMETA_DEPRECATED PhysicalProcess &setPhysicalProperty(std::string subject_metaid, const std::string &physicalProperty);

        /**
         * @brief setter for the physical property portion of the PhysicalProcess.
         * @return a reference to this PhysicalProcess to enable chaining setter commands
         *
         * Developers. Consider removing this method in favour of the
         * setPhysicalProperty version that only takes a string as argument
         */
        OMEXMETA_DEPRECATED PhysicalProcess &setPhysicalProperty(PhysicalProperty physicalProperty);

        /**
         * @brief add a source to the list of Source object associated with a PhysicalProcess
         * @return a reference to this PhysicalProcess to enable chaining setter commands
         */
        PhysicalProcess &addSource(std::string physical_entity_reference, eUriType type, double multiplier = 1.0);

        /**
         * @brief add a sink to the list of Source object associated with a PhysicalProcess
         * @return a reference to this PhysicalProcess to enable chaining setter commands
         */
        PhysicalProcess &addSink(std::string physical_entity_reference, eUriType type, double multiplier = 1.0);

        /**
         * @brief add a mediator to the list of Source object associated with a PhysicalProcess
         * @return a reference to this PhysicalProcess to enable chaining setter commands
         */
        PhysicalProcess &addMediator(std::string physical_entity_reference, eUriType type);

        /**
         * @brief returns the number of sources assocaited with the PhysicalProcess
         * @return the number of Source objects associated with this PhysicalProcess
         */
        int getNumSources();

        /**
         * @brief returns the number of sinks assocaited with the PhysicalProcess
         * @return the number of Sink objects associated with this PhysicalProcess
         */
        int getNumSinks();

        /**
         * @brief returns the number of mediators assocaited with the PhysicalProcess
         * @return the number of Mediator objects associated with this PhysicalProcess
         */
        int getNumMediators();

        bool operator==(const PhysicalProcess &rhs) const;

        bool operator!=(const PhysicalProcess &rhs) const;

        /**
         * @brief set the subject (rdf:about) portion of the PhysicalProcess composite annotation
         * @param about the string to be used as the Subject portion of the isVersionOf Triple. This
         * should be an existing metaid on the model you are annotating. Will error when metaid does not exist.
         * @details This method will set the Subject subject_ attribute of the PhysicalProperty
         * associated with the PhysicalProcess.
         */
        PhysicalProcess &about(const std::string &about, eUriType type) override;

        PhysicalProcess &about(const std::string &about) override;


        [[nodiscard]] const std::string &getPropertyMetaidBase() const override;

        PhysicalProcess& isVersionOf(const std::string & is_version_of, eUriType type = NONE);

        PhysicalProcess &hasProperty(const PhysicalProperty &property) override;

        PhysicalProcess &hasProperty(const std::string &property_about, eUriType about_uri_type, const std::string& is_version_of, const std::string& is_property_of, eUriType is_property_of_uri_type) override;

        PhysicalProcess &hasProperty(const std::string &is_version_of) override;

        PhysicalProcess &hasProperty(const std::string &property_about, eUriType about_uri_type, const std::string &is_version_of) override;

    };
}// namespace omexmeta

#endif//LIBOMEXMETA_PHYSICALPROCESS_H
