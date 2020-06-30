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
#include "RedlandAPIWrapper.h"
#include "HERE.h"

using namespace redland;

namespace semsim {
    class PhysicalPhenomenon {
    protected:

        librdf_model *model_ = nullptr; // should be cleaned up by the LibrdfModel inside RDF.
        PhysicalProperty physical_property_;
        AnnotationType type_ = AnnotationType::UNKNOWN;

        std::string physical_property_id_;

        [[nodiscard]] std::string generateMetaId(const std::string& id_base) const;

    public:
        PhysicalPhenomenon() = default;

        bool operator==(const PhysicalPhenomenon &rhs) const;

        bool operator!=(const PhysicalPhenomenon &rhs) const;

        ~PhysicalPhenomenon();

        /*
         * @brief Copy constructor for PhysicalPhenomenon
         */
        PhysicalPhenomenon(const PhysicalPhenomenon &phenomenon) = delete;

        /*
         * @brief Move constructor for PhysicalPhenomenon
         */
        PhysicalPhenomenon(PhysicalPhenomenon &&phenomenon) noexcept;

        /*
         * @brief assignment operator for PhysicalPhenomenon
         */
        PhysicalPhenomenon &operator=(const PhysicalPhenomenon &phenomenon) = delete;

        /*
         * @brief move assignment operator for PhysicalPhenomenon
         */
        PhysicalPhenomenon &operator=(PhysicalPhenomenon &&phenomenon) noexcept;

        /*
         * @brief Constructor for builder interface.
         *
         * Shouldn't be needed by users.
         *
         * Developers. Re-evaluate requirement for this constructor and remove if unnecessary
         */
        [[maybe_unused]] explicit PhysicalPhenomenon(librdf_model *model);

        /*
         * @brief constructor for PhysicalPhenomenon object.
         * @param model a librdf_model object assicated with RDF graph.
         * @param about The subject for the PhysicalPhenomenon. This is the metaid.
         * @param propertyResource The PhysicalProperty assocaited with a composite annotation
         * @param type An AnnotationType to distinguish composite annotations.
         */
        PhysicalPhenomenon(librdf_model *model,
                           PhysicalProperty propertyResource,
                           AnnotationType type);

        /*
         * @brief get the subject portion of the PhysicalPhenomenon
         * @return the string associated with the subject node
         */
        [[nodiscard]] const std::string& getAbout() const;

//        /*
//         * @brief get the subject portion of the PhysicalPhenomenon
//         * @return the string associated with the subject node
//         *
//         * This is the same as getAbout method.
//         */
//        [[nodiscard]] const Subject & getSubject() const;

        /*
         * @brief getter for Type argument
         * @return the AnnotationType currently used (PhysicalEntity, PhysicalForce or PhysicalProcess)
         */
        [[nodiscard]] AnnotationType getType() const;

        /*
         * @brief getter for PhysicalProperty argument
         * @return the resource representing the physical property being annotated
         */
        [[nodiscard]] PhysicalProperty getPhysicalProperty() const;

        /*
         * @brief create a Triples object using the information
         * contained in the PhysicalPhenomenon. Overridden by subclasses.
         * @return Triples object containing the individual Triple objects representing the PhysicalPhenomenon
         *
         * Refer to subclasses for more documentation.
         *
         */
        [[nodiscard]] virtual Triples toTriples();

//        virtual void free();

        const std::string &getSubjectStr() const;
    };

    typedef std::shared_ptr<PhysicalPhenomenon> PhysicalPhenomenonPtr;


}

#endif //LIBOMEXMETA_PhysicalPhenomenon_H
