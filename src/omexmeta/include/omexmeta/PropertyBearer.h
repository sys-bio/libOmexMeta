//
// Created by Ciaran on 4/22/2020.
//

#ifndef LIBOMEXMETA_PropertyBearer_H
#define LIBOMEXMETA_PropertyBearer_H

#include "include/redland/Query.h"
#include "omexmeta/AnnotationType.h"
#include "omexmeta/Error.h"
#include "omexmeta/MetaID.h"
#include "omexmeta/PhysicalProperty.h"
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
         * @brief Copy constructor for PropertyBearer
         */
        PropertyBearer(const PropertyBearer &propertyBearer) = delete;

        /**
         * @brief Move constructor for PropertyBearer
         */
        PropertyBearer(PropertyBearer &&propertyBearer) noexcept;

        /**
         * @brief assignment operator for PropertyBearer
         */
        PropertyBearer &operator=(const PropertyBearer &propertyBearer) = delete;

        /**
         * @brief move assignment operator for PropertyBearer
         */
        PropertyBearer &operator=(PropertyBearer &&propertyBearer) noexcept;

        /**
         * @brief Constructor for builder interface.
         *
         * Shouldn't be needed by users directly.
         */
        PropertyBearer(librdf_model *model, UriHandler& uriHandler);

        /**
         * @brief constructor for PropertyBearer object.
         * @param model a librdf_model object assicated with RDF graph.
         * @param about The subject for the PropertyBearer. This is the metaid.
         * @param propertyResource The PhysicalProperty assocaited with a composite annotation
         * @param type An AnnotationType to distinguish composite annotations.
         */
        PropertyBearer(librdf_model *model, UriHandler& uriHandler,
                       PhysicalProperty propertyResource, AnnotationType type);

        [[nodiscard]] const std::string &getModelUri() const;

        /**
         * @brief get the subject portion of the PropertyBearer
         * @return the string associated with the subject node
         */
        [[nodiscard]] const std::string &getPropertyAbout() const;

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
         * contained in the PropertyBearer. Overridden by subclasses.
         * @return Triples object containing the individual Triple objects representing the PropertyBearer
         *
         * Refer to subclasses for more documentation.
         *
         */
        [[nodiscard]] virtual Triples toTriples();

        OMEXMETA_DEPRECATED void setPhysicalProperty(const PhysicalProperty &physicalProperty);

        OMEXMETA_DEPRECATED void setType(AnnotationType type);

        [[nodiscard]] librdf_model *getModel() const;

        virtual PropertyBearer &hasProperty(const PhysicalProperty &property);

        OMEXMETA_DEPRECATED virtual PropertyBearer &hasProperty(const std::string &property_about, eUriType about_uri_type, const std::string &is_version_of, const std::string &is_property_of, eUriType is_property_of_uri_type);

        virtual PropertyBearer &hasProperty(const std::string &is_version_of);

        virtual PropertyBearer &hasProperty(const std::string &property_about, eUriType about_uri_type, const std::string &is_version_of);

        virtual PropertyBearer &about(const std::string &about, eUriType type);

        virtual PropertyBearer &about(const std::string &about);

        const std::string &getAbout() const;


    protected:
        /**
         * @brief getter for a vector of strings that keeps track of used metaids.
         * @details this mechanism is necessary in order to ensure unique metaids in
         * the case of adding multiple instances of a type to the PropertyBearer
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
        std::string property_metaid_base_;// Empty for PropertyBearer but overridden by subclasses with values such as "EntityProperty"
        std::string about_value_;
        eUriType about_uri_type_ = NONE;
        UriHandler& uriHandler_;
    };

    typedef std::shared_ptr<PropertyBearer> PropertyBearerPtr;


}// namespace omexmeta

#endif//LIBOMEXMETA_PropertyBearer_H
