//
// Created by Ciaran on 4/22/2020.
//

#include "PhysicalPhenomenon.h"

#include <utility>


namespace semsim {

    PhysicalPhenomenon::PhysicalPhenomenon(librdf_model *model, PhysicalProperty propertyResource, AnnotationType type)
            : model_(model), physical_property_(std::move(propertyResource)), type_(type) {}

    PhysicalPhenomenon::~PhysicalPhenomenon() = default;


    PhysicalPhenomenon::PhysicalPhenomenon(librdf_model *model)
            : model_(model) {}

    const std::string & PhysicalPhenomenon::getSubjectStr() const {
        return physical_property_.getSubjectStr();
    }

    AnnotationType PhysicalPhenomenon::getType() const {
        return type_;
    }

    std::string PhysicalPhenomenon::generateMetaId(const std::string& id_base) const {
        std::string q = "SELECT ?subject ?predicate ?object\n"
                        "WHERE {?subject ?predicate ?object}";
        Query query(model_, q);
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


    PhysicalProperty PhysicalPhenomenon::getPhysicalProperty() const {
        return physical_property_;
    }

    Triples PhysicalPhenomenon::toTriples() {
        throw NotImplementedException("Base class PhysicalPhenomenon "
                                      "does cannot produce triples.");
    }


    const std::string & PhysicalPhenomenon::getAbout() const {
        return physical_property_.getSubjectStr();
    }

//    PhysicalPhenomenon::PhysicalPhenomenon(const PhysicalPhenomenon &phenomenon) {
//        model_ = phenomenon.model_;
//        about = std::move(phenomenon.about);
//        physical_property_ = phenomenon.physical_property_;
//        type_ = phenomenon.type_;
//    }

    PhysicalPhenomenon::PhysicalPhenomenon(PhysicalPhenomenon &&phenomenon) noexcept {
        model_ = phenomenon.model_;
        phenomenon.model_ = nullptr; // not sure if this is right.
        physical_property_ = std::move(phenomenon.physical_property_);
        type_ = std::move(phenomenon.type_);
    }

    PhysicalPhenomenon &PhysicalPhenomenon::operator=(PhysicalPhenomenon &&phenomenon) noexcept {
        if (this != &phenomenon) {
            model_ = phenomenon.model_;
            phenomenon.model_ = nullptr; // not sure if this is right.
            physical_property_ = std::move(phenomenon.physical_property_);
            type_ = phenomenon.type_;
        }
    }

    bool PhysicalPhenomenon::operator==(const PhysicalPhenomenon &rhs) const {
        return physical_property_ == rhs.physical_property_;
    }

    bool PhysicalPhenomenon::operator!=(const PhysicalPhenomenon &rhs) const {
        return !(rhs == *this);
    }

}




/*
 * todo
 *  How would we parse rdf back into a composite annotation
 *  structure? It might be possible if composite annotations
 *  themselves had an flag attribute which tells software which type of
 *  annotation were dealing with. This would simplify the ascertaining of all
 *  (say) physical process triples and enable us think about
 *  reassembling them again
 */






