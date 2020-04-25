//
// Created by Ciaran on 4/22/2020.
//

#ifndef LIBSEMGEN_PhysicalPhenomenon_H
#define LIBSEMGEN_PhysicalPhenomenon_H

#include "semsim/Subject.h"
#include "semsim/PhysicalPropertyResource.h"
#include "semsim/AnnotationType.h"
#include "semsim/Triple.h"

// todo rename physical phenomenon to physical world/universe ?
namespace semsim {
    class PhysicalPhenomenon {
    protected:
        librdf_world *world_;
        Subject subject_metaid_;
        PhysicalPropertyResource physical_property_;
        AnnotationType type_;

        virtual std::string createMetaId(std::string id_base);

    public:
        PhysicalPhenomenon(librdf_world *world, Subject metaid, PhysicalPropertyResource propertyResource,
                           AnnotationType type);

        PhysicalPhenomenon();

        Subject getSubject() const;

        AnnotationType getType() const;

        const PhysicalPropertyResource getPhysicalProperty() const;

        virtual std::vector<Triple> toTriples() const;

    };

    typedef std::shared_ptr<PhysicalPhenomenon> PhysicalPhenomenonPtr;


}

#endif //LIBSEMGEN_PhysicalPhenomenon_H
