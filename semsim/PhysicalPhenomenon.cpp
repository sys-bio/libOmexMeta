//
// Created by Ciaran on 4/22/2020.
//

#include "semsim/PhysicalPhenomenon.h"
#include "semsim/MetaID.h"
#include "semsim/Error.h"

namespace semsim {

    PhysicalPhenomenon::PhysicalPhenomenon(
            librdf_world *world, Subject metaid,
            PhysicalPropertyResource propertyResource, AnnotationType type)
            : world_(world), subject_metaid_(metaid), physical_property_(propertyResource), type_(type) {

    }

    Subject PhysicalPhenomenon::getSubject() const {
        return subject_metaid_;
    }

    AnnotationType PhysicalPhenomenon::getType() const {
        return type_;
    }

    std::string PhysicalPhenomenon::createMetaId(std::string id_base) {
        return "emptyplaceholder";
    }

    const PhysicalPropertyResource PhysicalPhenomenon::getPhysicalProperty() const {
        return physical_property_;
    }

    std::vector<Triple> PhysicalPhenomenon::toTriples() const {
        throw NotImplementedException("Base class PhysicalPhenomenon "
                                      "does cannot produce triples.");
    }

    PhysicalPhenomenon::PhysicalPhenomenon() = default;


}