//
// Created by Ciaran on 4/22/2020.
//

#include "semsim/PhysicalPhenomenon.h"
#include "semsim/MetaID.h"
#include "semsim/Error.h"
#include "Query.h"

namespace semsim {

    PhysicalPhenomenon::PhysicalPhenomenon(librdf_world *world, librdf_model *model, Subject metaid,
                                           PhysicalPropertyResource propertyResource, AnnotationType type)
            : world_(world), model_(model), subject_metaid_(metaid), physical_property_(propertyResource), type_(type) {
    }

    Subject PhysicalPhenomenon::getSubject() const {
        return subject_metaid_;
    }

    AnnotationType PhysicalPhenomenon::getType() const {
        return type_;
    }

    std::string PhysicalPhenomenon::generateMetaId(std::string id_base) const {
        std::string q = "SELECT ?subject ?predicate ?object"
                        "WHERE {?subject ?predicate ?object}";
        Query query(world_, model_, q);
        ResultsMap results_map = query.resultsAsMap();
        std::vector<std::string> subjects = results_map["subject"];
        int count = 0;
        std::string metaid;
        while (true) {
            MetaID metaId(id_base, count, 4);
            metaid = metaId.generate();
            if (std::find(subjects.begin(), subjects.end(), metaId.generate()) == subjects.end()) {
                break;
            }
            count++;
        }
        return metaid;
    }


    const PhysicalPropertyResource PhysicalPhenomenon::getPhysicalProperty() const {
        return physical_property_;
    }

    Triples PhysicalPhenomenon::toTriples() const {
        throw NotImplementedException("Base class PhysicalPhenomenon "
                                      "does cannot produce triples.");
    }

    PhysicalPhenomenon::PhysicalPhenomenon() =
    default;

}