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
#include "semsim/RedlandAPIWrappers/RedlandAPIWrapper.h"

namespace semsim {
    class PhysicalPhenomenon {
    protected:
        LibrdfWorld world_;
        LibrdfModel model_;
        Subject about;
        PhysicalPropertyResource physical_property_;
        AnnotationType type_;

        std::string generateMetaId(std::string id_base) const;

    public:
        PhysicalPhenomenon();

        PhysicalPhenomenon(LibrdfWorld world, LibrdfModel model, Subject metaid,
                           PhysicalPropertyResource propertyResource, AnnotationType type);

        PhysicalPhenomenon(LibrdfWorld world, LibrdfModel model);

        Subject getAbout() const;

        Subject getSubject() const;

        AnnotationType getType() const;

        PhysicalPropertyResource getPhysicalProperty() const;

        virtual Triples toTriples() const;


    };

    typedef std::shared_ptr<PhysicalPhenomenon> PhysicalPhenomenonPtr;


}

#endif //LIBSEMGEN_PhysicalPhenomenon_H
