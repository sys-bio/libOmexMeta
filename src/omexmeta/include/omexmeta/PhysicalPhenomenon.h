//
// Created by Ciaran on 4/22/2020.
//

#ifndef LIBOMEXMETA_PhysicalPhenomenon_H
#define LIBOMEXMETA_PhysicalPhenomenon_H

#include "omexmeta/Subject.h"
#include "omexmeta/PhysicalProperty.h"
#include "omexmeta/AnnotationType.h"
#include "omexmeta/Triple.h"
#include "omexmeta/Triples.h"
#include "omexmeta/MetaID.h"
#include "omexmeta/Error.h"
#include "omexmeta/Query.h"
#include "redland/RedlandAPI.h"

#include <utility>

using namespace redland;

namespace omexmeta {
    class PhysicalPhenomenon {

    protected:

        librdf_model *model_ = nullptr; // should be cleaned up by the LibrdfModel inside RDF.
        PhysicalProperty physical_property_;
        AnnotationType type_ = AnnotationType::UNKNOWN;
        std::string model_uri_;
        std::string local_uri_;
        std::vector<std::string> new_metaid_exclusion_list_;
        std::string property_metaid_base_; // Empty for PhysicalPhenomenon but overridden by subclasses with values such as "EntityProperty"
        std::string about_value_;

        /**
         * @brief getter for a vector of strings that keeps track of used metaids.
         * @details this mechanism is necessary in order to ensure unique metaids in
         * the case of adding multiple instances of a type to the PhysicalPhenomenon
         * before commiting to the model. For instance, you can have arbitrary
         * sink participants, which would all be given the SinkParticipant0000 metaid
         * if not for this mechanism.
         */
        [[nodiscard]] std::vector<std::string> getNewMetaidExclusionList();


        [[nodiscard]] std::string generateMetaId(const std::string& id_base);

    public:
        [[nodiscard]] virtual const std::string &getPropertyMetaidBase() const;
        PhysicalPhenomenon() = default;

        bool operator==(const PhysicalPhenomenon &rhs) const;

        bool operator!=(const PhysicalPhenomenon &rhs) const;

        ~PhysicalPhenomenon();

        [[nodiscard]] const std::string &getLocalUri() const;

        void setLocalUri(const std::string &localUri);

        /**
         * @brief Copy constructor for PhysicalPhenomenon
         */
        PhysicalPhenomenon(const PhysicalPhenomenon &phenomenon) = delete;

        /**
         * @brief Move constructor for PhysicalPhenomenon
         */
        PhysicalPhenomenon(PhysicalPhenomenon &&phenomenon) noexcept;

        /**
         * @brief assignment operator for PhysicalPhenomenon
         */
        PhysicalPhenomenon &operator=(const PhysicalPhenomenon &phenomenon) = delete;

        /**
         * @brief move assignment operator for PhysicalPhenomenon
         */
        PhysicalPhenomenon &operator=(PhysicalPhenomenon &&phenomenon) noexcept;

        /**
         * @brief Constructor for builder interface.
         *
         * Shouldn't be needed by users.
         */
        [[maybe_unused]] explicit PhysicalPhenomenon(librdf_model *model);

        /**
         * @brief Constructor for builder interface.
         *
         * Shouldn't be needed by users directly.
         */
        [[maybe_unused]] explicit PhysicalPhenomenon(librdf_model *model, std::string model_uri, std::string local_uri);

        /**
         * @brief constructor for PhysicalPhenomenon object.
         * @param model a librdf_model object assicated with RDF graph.
         * @param about The subject for the PhysicalPhenomenon. This is the metaid.
         * @param propertyResource The PhysicalProperty assocaited with a composite annotation
         * @param type An AnnotationType to distinguish composite annotations.
         */
        PhysicalPhenomenon(librdf_model *model, std::string model_uri, std::string local_uri,
                           PhysicalProperty propertyResource, AnnotationType type);

        [[nodiscard]] const std::string &getModelUri() const;

        void setModelUri(const std::string &modelUri);

        /**
         * @brief get the subject portion of the PhysicalPhenomenon
         * @return the string associated with the subject node
         */
        [[nodiscard]] const std::string& getAbout() const;

        /**
         * @brief getter for Type argument
         * @return the AnnotationType currently used (PhysicalEntity, PhysicalForce or PhysicalProcess)
         */
        [[nodiscard]] AnnotationType getType() const;

        /**
         * @brief getter for PhysicalProperty argument
         * @return the resource representing the physical property being annotated
         */
        [[nodiscard]] PhysicalProperty getPhysicalProperty() const;

        /**
         * @brief create a Triples object using the information
         * contained in the PhysicalPhenomenon. Overridden by subclasses.
         * @return Triples object containing the individual Triple objects representing the PhysicalPhenomenon
         *
         * Refer to subclasses for more documentation.
         *
         */
        [[nodiscard]] virtual Triples toTriples();

        [[nodiscard]] const std::string &getSubjectStr() const;

        void setPhysicalProperty(const PhysicalProperty &physicalProperty);

        void setType(AnnotationType type);

        [[nodiscard]] librdf_model *getModel() const;


//        PhysicalPhenomenon &hasProperty(const PhysicalProperty &property);

//        PhysicalProperty& hasProperty(const std::string &property_about = "", eUriType about_uri_type = NONE);

    };

    typedef std::shared_ptr<PhysicalPhenomenon> PhysicalPhenomenonPtr;


}

#endif //LIBOMEXMETA_PhysicalPhenomenon_H
