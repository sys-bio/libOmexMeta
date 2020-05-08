//
// Created by Ciaran on 4/22/2020.
//

#ifndef LIBSEMGEN_PhysicalPhenomenon_H
#define LIBSEMGEN_PhysicalPhenomenon_H

#include "Subject.h"
#include "PhysicalPropertyResource.h"
#include "AnnotationType.h"
#include "Triple.h"
#include "Triples.h"

namespace semsim {
    class PhysicalPhenomenon {
    protected:
        librdf_world *world_;
        librdf_model *model_;
        Subject about;
        PhysicalPropertyResource physical_property_;
        AnnotationType type_;

        std::string generateMetaId(std::string id_base) const;

    public:
        PhysicalPhenomenon();

        PhysicalPhenomenon(librdf_world *world, librdf_model *model, Subject metaid,
                           PhysicalPropertyResource propertyResource, AnnotationType type);

        PhysicalPhenomenon(librdf_world *world, librdf_model *model);

        Subject getAbout() const;

        Subject getSubject() const;

        AnnotationType getType() const;

        PhysicalPropertyResource getPhysicalProperty() const;

        virtual Triples toTriples() const;


    };

    typedef std::shared_ptr<PhysicalPhenomenon> PhysicalPhenomenonPtr;


}

#endif //LIBSEMGEN_PhysicalPhenomenon_H
