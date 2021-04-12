//
// Created by Ciaran on 4/22/2020.
//

#ifndef LIBOMEXMETA_PhysicalPhenomenon_H
#define LIBOMEXMETA_PhysicalPhenomenon_H

#include "omexmeta/AnnotationType.h"
#include "omexmeta/Error.h"
#include "omexmeta/MetaID.h"
#include "omexmeta/PhysicalProperty.h"
#include "omexmeta/Query.h"
#include "omexmeta/Subject.h"
#include "omexmeta/Triple.h"
#include "omexmeta/Triples.h"
#include "redland/RedlandAPI.h"

#include <utility>

using namespace redland;

namespace omexmeta {
    class PropertyBearer {

    public:
        eUriType getAboutUriType() const;

        void setAboutUriType(eUriType aboutUriType);

        [[nodiscard]] virtual const std::string &getPropertyMetaidBase() const;

        PropertyBearer() = default;

        bool operator==(const PropertyBearer &rhs) const;

        bool operator!=(const PropertyBearer &rhs) const;

        ~PropertyBearer();

        [[nodiscard]] const std::string &getLocalUri() const;

        /**
         * @brief Copy constructor for PhysicalPhenomenon
         */
        PropertyBearer(const PropertyBearer &phenomenon) = delete;

        /**
         * @brief Move constructor for PhysicalPhenomenon
         */
        PropertyBearer(PropertyBearer &&propertyBearer) noexcept;

        /**
         * @brief assignment operator for PhysicalPhenomenon
         */
        PropertyBearer &operator=(const PropertyBearer &phenomenon) = delete;

        /**
         * @brief move assignment operator for PhysicalPhenomenon
         */
        PropertyBearer &operator=(PropertyBearer &&propertyBearer) noexcept;

        /**
         * @brief Constructor for builder interface.
         *
         * Shouldn't be needed by users directly.
         */
        PropertyBearer(librdf_model *model, UriHandler uriHandler);

        /**
         * @brief constructor for PhysicalPhenomenon object.
         * @param model a librdf_model object assicated with RDF graph.
         * @param about The subject for the PhysicalPhenomenon. This is the metaid.
         * @param propertyResource The PhysicalProperty assocaited with a composite annotation
         * @param type An AnnotationType to distinguish composite annotations.
         */
        PropertyBearer(librdf_model *model, UriHandler uriHandler,
                       PhysicalProperty propertyResource, AnnotationType type);

        [[nodiscard]] const std::string &getModelUri() const;

        /**
         * @brief get the subject portion of the PhysicalPhenomenon
         * @return the string associated with the subject node
         */
        [[nodiscard]] const std::string &getAbout() const;

        /**
         * @brief getter for Type argument
         * @return the AnnotationType currently used (PhysicalEntity, EnergyDiff or PhysicalProcess)
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

        [[nodiscard]] OMEXMETA_DEPRECATED const std::string &getSubjectStr() const;

        OMEXMETA_DEPRECATED void setPhysicalProperty(const PhysicalProperty &physicalProperty);

        OMEXMETA_DEPRECATED void setType(AnnotationType type);

        [[nodiscard]] librdf_model *getModel() const;

        virtual PropertyBearer &hasProperty(const PhysicalProperty &property);

        OMEXMETA_DEPRECATED virtual PropertyBearer &hasProperty(const std::string &property_about, eUriType about_uri_type, const std::string &is_version_of, const std::string &is_property_of, eUriType is_property_of_uri_type);

        virtual PropertyBearer &hasProperty(const std::string &is_version_of);

        virtual PropertyBearer &hasProperty(const std::string &property_about, eUriType about_uri_type, const std::string &is_version_of);

        virtual PropertyBearer &about(const std::string &about, eUriType type);

        virtual PropertyBearer &about(const std::string &about);

    protected:
        /**
         * @brief getter for a vector of strings that keeps track of used metaids.
         * @details this mechanism is necessary in order to ensure unique metaids in
         * the case of adding multiple instances of a type to the PhysicalPhenomenon
         * before commiting to the model. For instance, you can have arbitrary
         * sink participants, which would all be given the SinkParticipant0000 metaid
         * if not for this mechanism.
         */
        [[nodiscard]] std::vector<std::string> getNewMetaidExclusionList();

        [[nodiscard]] std::string generateMetaId(const std::string &id_base);

        librdf_model *model_ = nullptr;// should be cleaned up by the LibrdfModel inside RDF.
        PhysicalProperty physical_property_;
        AnnotationType type_ = AnnotationType::UNKNOWN;

        // todo replace model_uri_ and local_uri_ with instnce if UriHandler
        std::vector<std::string> new_metaid_exclusion_list_;
        std::string property_metaid_base_;// Empty for PhysicalPhenomenon but overridden by subclasses with values such as "EntityProperty"
        std::string about_value_;
        eUriType about_uri_type_ = NONE;
        UriHandler uriHandler_;
    };

    typedef std::shared_ptr<PropertyBearer> PhysicalPhenomenonPtr;


}// namespace omexmeta

#endif//LIBOMEXMETA_PhysicalPhenomenon_H
