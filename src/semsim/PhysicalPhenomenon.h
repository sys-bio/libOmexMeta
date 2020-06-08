//
// Created by Ciaran on 4/22/2020.
//

#ifndef LIBSEMSIM_PhysicalPhenomenon_H
#define LIBSEMSIM_PhysicalPhenomenon_H

#include "semsim/Subject.h"
#include "semsim/PhysicalPropertyResource.h"
#include "semsim/AnnotationType.h"
#include "semsim/Triple.h"
#include "semsim/Triples.h"
#include "semsim/MetaID.h"
#include "semsim/Error.h"
#include "semsim/Query.h"
#include "RedlandAPIWrapper.h"
#include "HERE.h"

using namespace redland;

namespace semsim {
    class PhysicalPhenomenon {
    protected:

        librdf_model *model_ = nullptr; // should be cleaned up by the LibrdfModel inside RDF.
        Subject about;
        PhysicalPropertyResource physical_property_;
        AnnotationType type_ = AnnotationType::UNKNOWN;

        [[nodiscard]] std::string generateMetaId(std::string id_base) const;

    public:
        PhysicalPhenomenon() = default;

        ~PhysicalPhenomenon();

        /*
         * @brief Copy constructor for PhysicalPhenomenon
         */
        PhysicalPhenomenon(const PhysicalPhenomenon &phenomenon);

        /*
         * @brief Move constructor for PhysicalPhenomenon
         */
        PhysicalPhenomenon(PhysicalPhenomenon &&phenomenon) noexcept;

        /*
         * @brief assignment operator for PhysicalPhenomenon
         */
        PhysicalPhenomenon &operator=(const PhysicalPhenomenon &phenomenon);

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
        [[maybe_unused]] explicit PhysicalPhenomenon(librdf_model* model);

        /*
         * @brief constructor for PhysicalPhenomenon object.
         * @param model a librdf_model object assicated with RDF graph.
         * @param about The subject for the PhysicalPhenomenon. This is the metaid.
         * @param propertyResource The PhysicalPropertyResource assocaited with a composite annotation
         * @param type An AnnotationType to distinguish composite annotations.
         */
        PhysicalPhenomenon(librdf_model* model, Subject about,
                           PhysicalPropertyResource propertyResource,
                           AnnotationType type);

        /*
         * @brief get the subject portion of the PhysicalPhenomenon
         */
        [[nodiscard]] Subject getAbout() const;

        /*
         * @brief get the subject portion of the PhysicalPhenomenon
         *
         * This is the same as getAbout method.
         */
        [[nodiscard]] Subject getSubject() const;

        /*
         * @brief getter for Type argument
         */
        [[nodiscard]] AnnotationType getType() const;

        /*
         * @brief getter for PhysicalProperty argument
         */
        [[nodiscard]] PhysicalPropertyResource getPhysicalProperty() const;

        /*
         * @brief create a Triples object using the information
         * contained in the PhysicalPhenomenon. Overridden by subclasses.
         * Refer to subclasses for more documentation.
         */
        [[nodiscard]] virtual Triples toTriples();

        virtual void free();
    };

    typedef std::shared_ptr<PhysicalPhenomenon> PhysicalPhenomenonPtr;


}

#endif //LIBSEMSIM_PhysicalPhenomenon_H
