//
// Created by Ciaran on 4/22/2020.
//

#ifndef LIBSEMGEN_PhysicalPhenomenon_H
#define LIBSEMGEN_PhysicalPhenomenon_H

#include "semsim/Subject.h"
#include "semsim/PhysicalPropertyResource.h"
#include "semsim/AnnotationType.h"
#include "semsim/Triple.h"
#include "semsim/Triples.h"

namespace semsim {
    class PhysicalPhenomenon {
    protected:
        librdf_world *world_;
        Subject subject_metaid_;
        PhysicalPropertyResource physical_property_;
        AnnotationType type_;

    public:
        PhysicalPhenomenon(librdf_world *world, Subject metaid, PhysicalPropertyResource propertyResource,
                           AnnotationType type);

        PhysicalPhenomenon();

        Subject getSubject() const;

        AnnotationType getType() const;

        const PhysicalPropertyResource getPhysicalProperty() const;

        virtual Triples toTriples() const;

        virtual std::string createMetaId(librdf_model *model, std::string id_base) const;
    };

    typedef std::shared_ptr<PhysicalPhenomenon> PhysicalPhenomenonPtr;


}

#endif //LIBSEMGEN_PhysicalPhenomenon_H
