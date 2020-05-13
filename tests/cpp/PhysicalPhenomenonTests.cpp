//
// Created by Ciaran on 4/22/2020.
//

//
// Created by Ciaran on 4/22/2020.
//

#include <semsim/RDF.h>
#include "gtest/gtest.h"
#include "librdf.h"
#include "AnnotationSamples.h"
#include "semsim/PhysicalEntity.h"
#include "semsim/AnnotationType.h"

// todo consider using the builder pattern on physical* classes

class PhysicalPhenomenonTests : public ::testing::Test {

public:

    AnnotationSamples samples;

    librdf_world *world;
    raptor_world *raptorWorld;
    librdf_storage *storage;
    librdf_model *model;

    PhysicalPhenomenonTests() {
        auto initializer = semsim::RDF::init();
        world = std::get<0>(initializer);
        raptorWorld = std::get<1>(initializer);
        storage = std::get<2>(initializer);
        model = std::get<3>(initializer);
    };
};


TEST_F(PhysicalPhenomenonTests, TestSubjectStr) {
    semsim::PhysicalPhenomenon phenomenon(
            world, nullptr,
            semsim::Subject(world, semsim::RDFURINode(world, "metaid004")),
            semsim::PhysicalPropertyResource(world, "OPB:OPB_12345"),
            semsim::PHYSICAL_ENTITY
    );
    std::string expected = "metaid004";
    std::string actual = phenomenon.getSubject().str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PhysicalPhenomenonTests, TestSubjectNodeToStr) {
    semsim::PhysicalPhenomenon phenomenon(
            world, nullptr,
            semsim::Subject(world, semsim::RDFURINode(world, "metaid004")),
            semsim::PhysicalPropertyResource(world, "OPB:OPB_12345"),
            semsim::PHYSICAL_ENTITY
    );
    std::string expected = "metaid004";
    std::string actual = (const char *) librdf_uri_as_string(
            librdf_node_get_uri(
                    phenomenon.getSubject().toRdfNode()
            )
    );
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PhysicalPhenomenonTests, TestPhysicalProperty) {
    semsim::PhysicalPhenomenon phenomenon(
            world, nullptr,
            semsim::Subject(world, semsim::RDFURINode(world, "metaid004")),
            semsim::PhysicalPropertyResource(world, "OPB:OPB_12345"),
            semsim::PHYSICAL_ENTITY
    );
    std::string expected = "https://identifiers.org/OPB/OPB_12345";
    std::string actual = phenomenon.getPhysicalProperty().str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(PhysicalPhenomenonTests, Test) {

    HERE();
    semsim::RDF rdf = semsim::RDF::fromString(
            samples.singular_annotation1, "guess"
    );
    HERE();

//    rdf.setBaseUri("/mnt/d/libsemsim/tests/base-uri.rdf");
//    std::cout << rdf.getBaseUriAsString() << std::endl;
//    std::cout << rdf.toString("rdfxml-abbrev", "/mnt/d/libsemsim/tests/base-uri.rdf") << std::endl;
    std::ostringstream q;



    // a way around the problem is to
    //  instead do a search for all metaids
    //  and filter them out

    q << "BASE <file://./base-uri.rdf>\n"
         "SELECT ?x ?y ?z\n"
         "WHERE {\n"
         "  <metaid_1> ?y ?z\n"
         "}\n";
//    librdf_uri* base = librdf_new_uri(world, (const unsigned char*)"/mnt/d/libsemsim/tests/base-uri.rdf");
    librdf_query *query = librdf_new_query(
            world, "sparql",
            nullptr,
            (const unsigned char *) q.str().c_str(),
            nullptr
    );
    librdf_query_results *results = librdf_model_query_execute(rdf.getModel(), query);
    if (!results) {
        throw semsim::LibRDFException("No results");
    }

    // is the problem because the base metaid is only set by the writer???
    int boolean_query_results = librdf_query_results_get_boolean(results);
    int binding_query_results = librdf_query_results_is_bindings(results);
    std::cout << "boolean_query_results: " << boolean_query_results << std::endl;
    std::cout << "binding_query_results: " << binding_query_results << std::endl;
    unsigned char *string = librdf_query_results_to_string2(
            results, "turtle", nullptr, nullptr, nullptr);
    if (!string) {
        throw semsim::LibRDFException("No workey");
    }
    std::cout << string << std::endl;

    //    std::cout << rdf.getBaseUriAsString() << std::endl;
//    rdf.setBaseUri("/mnt/d/libsemsim/tests/rdftests.rdf");
//    std::cout << rdf.getBaseUriAsString() << std::endl;
//    HERE();
//    semsim::PhysicalPhenomenon phenomenon(
//            rdf.getWorld(),
//            semsim::Subject(rdf.getWorld(), semsim::RDFURINode(rdf.getWorld(), "metaid004")),
//            semsim::PhysicalPropertyResource(rdf.getWorld(), "OPB:OPB_12345"),
//            semsim::PHYSICAL_ENTITY
//    );
//    HERE();
//    phenomenon.generateMetaId(rdf.getModel(), "Phenomenon");
//    HERE();
//
//    librdf_uri* base = librdf_new_uri(world, (const unsigned char*)"./baseuri.rdf");
//
//    librdf_uri* uri = librdf_new_uri_normalised_to_base((const unsigned char*) "id1",
//            librdf_new_uri(world, (const unsigned char*)"source"), base);
//
//    librdf_uri* uri2 = librdf_new_uri_relative_to_base(base, (const unsigned char*)"id1");
//    std::cout << librdf_uri_as_string(uri) << std::endl;
//    std::cout << librdf_uri_as_string(uri2) << std::endl;

}














