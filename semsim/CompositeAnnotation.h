//
// Created by Ciaran on 4/22/2020.
//

#ifndef LIBSEMGEN_COMPOSITEANNOTATION_H
#define LIBSEMGEN_COMPOSITEANNOTATION_H

#include "semsim/PhysicalPropertyResource.h"
#include "semsim/PhysicalPhenomenon.h"
#include "semsim/AnnotationType.h"

namespace semsim {


    class CompositeAnnotation {
    private:
        AnnotationType type;
        PhysicalPropertyResource physicalProperty_;
        PhysicalPhenomenon propertyBearer_;

    public:
        CompositeAnnotation(PhysicalPropertyResource physicalProperty, PhysicalPhenomenon propertyBearer);

        const PhysicalPropertyResource &getPhysicalProperty() const;

        void setPhysicalProperty(const PhysicalPropertyResource &physicalProperty);

        const PhysicalPhenomenon &getPhysicalPhenomenon() const;

        void setPhysicalPhenomenon(const PhysicalPhenomenon &propertyBearer);
    };
}

#endif //LIBSEMGEN_COMPOSITEANNOTATION_H
