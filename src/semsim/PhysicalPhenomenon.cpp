//
// Created by Ciaran on 4/22/2020.
//

#include "PhysicalPhenomenon.h"

#include <utility>


namespace semsim {

    PhysicalPhenomenon::PhysicalPhenomenon(librdf_model *model, Subject metaid,
                                           PhysicalPropertyResource propertyResource, AnnotationType type)
            : model_(model), about(metaid), physical_property_(std::move(propertyResource)), type_(type) {}

    PhysicalPhenomenon::~PhysicalPhenomenon() = default;

    void PhysicalPhenomenon::free() {
        if (about.getNode())
            about.free();
        if (physical_property_.getNode())
            physical_property_.free();
    }

    PhysicalPhenomenon::PhysicalPhenomenon(librdf_model* model)
            : model_(model) {}

    Subject PhysicalPhenomenon::getSubject() const {
        return about;
    }

    AnnotationType PhysicalPhenomenon::getType() const {
        return type_;
    }

    std::string PhysicalPhenomenon::generateMetaId(std::string id_base) const {
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


    PhysicalPropertyResource PhysicalPhenomenon::getPhysicalProperty() const {
        return physical_property_;
    }

    Triples PhysicalPhenomenon::toTriples() const {
        throw NotImplementedException("Base class PhysicalPhenomenon "
                                      "does cannot produce triples.");
    }


    Subject PhysicalPhenomenon::getAbout() const {
        return about;
    }

    PhysicalPhenomenon::PhysicalPhenomenon(const PhysicalPhenomenon &phenomenon) {
        model_ = phenomenon.model_;
        about = phenomenon.about;
        physical_property_ = phenomenon.physical_property_;
        type_ = phenomenon.type_;
    }

    PhysicalPhenomenon::PhysicalPhenomenon(PhysicalPhenomenon &&phenomenon) noexcept {
        model_ = phenomenon.model_;
        phenomenon.model_ = nullptr; // not sure if this is right.
        about = std::move(phenomenon.about);
        physical_property_ = std::move(phenomenon.physical_property_);
        type_ = std::move(phenomenon.type_);
    }

    PhysicalPhenomenon &PhysicalPhenomenon::operator=(const PhysicalPhenomenon &phenomenon) {
        if (this != &phenomenon) {
            model_ = phenomenon.model_;
            about = std::move(phenomenon.about);
            physical_property_ = std::move(phenomenon.physical_property_);
            type_ = std::move(phenomenon.type_);
        }
        return *this;
    }
    
    PhysicalPhenomenon &PhysicalPhenomenon::operator=(PhysicalPhenomenon &&phenomenon) noexcept {
        if (this != &phenomenon) {
            model_ = phenomenon.model_;
            phenomenon.model_ = nullptr; // not sure if this is right.
            about = std::move(phenomenon.about);
            physical_property_ = std::move(phenomenon.physical_property_);
            type_ = std::move(phenomenon.type_);
        }
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






