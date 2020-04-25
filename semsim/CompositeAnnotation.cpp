//
// Created by Ciaran on 4/22/2020.
//

#include "CompositeAnnotation.h"


namespace semsim {


    const PhysicalPropertyResource &CompositeAnnotation::getPhysicalProperty() const {
        return physicalProperty_;
    }

    void CompositeAnnotation::setPhysicalProperty(const PhysicalPropertyResource &physicalProperty) {
        physicalProperty_ = physicalProperty;
    }

    const PhysicalPhenomenon &CompositeAnnotation::getPhysicalPhenomenon() const {
        return propertyBearer_;
    }

    void CompositeAnnotation::setPhysicalPhenomenon(const PhysicalPhenomenon &propertyBearer) {
        propertyBearer_ = propertyBearer;
    }

    CompositeAnnotation::CompositeAnnotation(PhysicalPropertyResource physicalProperty,
                                             PhysicalPhenomenon propertyBearer) :
            physicalProperty_(physicalProperty), propertyBearer_(propertyBearer) {
//        type = propertyBearer.getType();
    }
}