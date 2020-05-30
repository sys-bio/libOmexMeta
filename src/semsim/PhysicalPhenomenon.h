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

using namespace redland;

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

#endif //LIBSEMSIM_PhysicalPhenomenon_H
