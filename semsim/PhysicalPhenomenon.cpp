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

    std::string PhysicalPhenomenon::createMetaId(librdf_model *model, std::string id_base) const {
        bool unique_id_found = false;
        int count = 0;
        MetaID id(std::move(id_base), count, 4);
        std::string id_str = id.generate();
        std::ostringstream q;

        q << "BASE <https://base-uri.rdf> \n"
             "SELECT ?y ?z\n"
             "WHERE {\n"
             "  <metaid_1> ?y ?z\n"
             "}\n";
//        std::cout << "id " << id_str <<std::endl;
//        q << "SELECT " << id_str << " ?pred ?res\n"
//                                    "WHERE {\n"
//                                    "  " << id_str << " ?pred ?res\n"
//                                                      "}";
        librdf_query *query = librdf_new_query(
                world_, "sparql", nullptr, (const unsigned char *) q.str().c_str(), nullptr
        );
        librdf_query_results *results = librdf_model_query_execute(model, query);

        if (!results) {
            throw LibRDFException("No results");
        }

        int boolean_query_results = librdf_query_results_get_boolean(results);
        int binding_query_results = librdf_query_results_is_bindings(results);
        std::cout << "boolean_query_results: " << boolean_query_results << std::endl;
        std::cout << "binding_query_results: " << binding_query_results << std::endl;
        unsigned char *string = librdf_query_results_to_string2(
                results, "turtle", nullptr, nullptr, nullptr);
        if (!string) {
            throw LibRDFException("No workey");
        }
        std::cout << string << std::endl;
        return id_str;

    }

    const PhysicalPropertyResource PhysicalPhenomenon::getPhysicalProperty() const {
        return physical_property_;
    }

    Triples PhysicalPhenomenon::toTriples() const {
        throw NotImplementedException("Base class PhysicalPhenomenon "
                                      "does cannot produce triples.");
    }

    PhysicalPhenomenon::PhysicalPhenomenon() = default;

}