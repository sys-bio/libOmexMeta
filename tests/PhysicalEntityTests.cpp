//
// Created by Ciaran on 4/22/2020.
//

#include <semsim/RDF.h>
#include <vector>
#include "gtest/gtest.h"
#include "librdf.h"
#include "semsim/PhysicalEntity.h"

class PhysicalEntityTests : public ::testing::Test {

public:

    librdf_world *world;
    raptor_world *raptorWorld;
    librdf_storage *storage;
    librdf_model *model;

    semsim::PhysicalPropertyResource physical_property;

    PhysicalEntityTests() {
        auto initializer = semsim::RDF::init();
        world = std::get<0>(initializer);
        raptorWorld = std::get<1>(initializer);
        storage = std::get<2>(initializer);
        model = std::get<3>(initializer);

        physical_property = semsim::PhysicalPropertyResource(
                // chemical concentration
                world, semsim::RDFURINode(world, "OPB:OPB_00340")
        );
    };
};


TEST_F(PhysicalEntityTests, TestGetSubjectMetaidStr) {
    semsim::RDF rdf;
    semsim::PhysicalEntity physicalEntity(
            world,
            model,
            semsim::Subject(world, semsim::RDFURINode(world, "Metaid0034")),
            physical_property,
            semsim::Resource(world, semsim::RDFURINode(world, "obo/PR_000000365")), // is smad3
            std::vector<semsim::Resource>(
                    {semsim::Resource(world, semsim::RDFURINode(world, "https://identifiers.org/fma/FMA:72564")),
                     semsim::Resource(world, semsim::RDFURINode(world, "https://identifiers.org/fma/FMA:63877"))
                    })
    );
    std::string actual = physicalEntity.getSubject().str();
    std::string expected = "Metaid0034";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PhysicalEntityTests, TestGetSubjectMetaidFromNode) {
    semsim::RDF rdf;
    semsim::PhysicalEntity physicalEntity(
            world,
            model,
            semsim::Subject(world, semsim::RDFURINode(world, "Metaid0034")),
            physical_property,
            semsim::Resource(world, semsim::RDFURINode(world, "obo/PR_000000365")), // is smad3
            std::vector<semsim::Resource>(
                    {semsim::Resource(world, semsim::RDFURINode(world, "https://identifiers.org/fma/FMA:72564")),
                     semsim::Resource(world, semsim::RDFURINode(world, "https://identifiers.org/fma/FMA:63877"))
                    })
    );
    std::string actual = (const char *) librdf_uri_as_string(
            librdf_node_get_uri(physicalEntity.getSubject().toRdfNode()));
    std::string expected = "Metaid0034";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PhysicalEntityTests, TestGetPhysicalPropertyNode) {
    semsim::RDF rdf;
    semsim::PhysicalEntity physicalEntity(
            world,
            model,
            semsim::Subject(world, semsim::RDFURINode(world, "Metaid0034")),
            physical_property,
            semsim::Resource(world, semsim::RDFURINode(world, "obo/PR_000000365")), // is smad3
            std::vector<semsim::Resource>(
                    {semsim::Resource(world, semsim::RDFURINode(world, "https://identifiers.org/fma/FMA:72564")),
                     semsim::Resource(world, semsim::RDFURINode(world, "https://identifiers.org/fma/FMA:63877"))
                    })
    );
    std::string actual = (const char *) librdf_uri_as_string(
            librdf_node_get_uri(physicalEntity.getPhysicalProperty().toRdfNode()));
    std::string expected = "https://identifiers.org/OPB/OPB_00340";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PhysicalEntityTests, TestGetPhysicalPropertyStr) {
    semsim::RDF rdf;
    semsim::PhysicalEntity physicalEntity(
            world,
            model,
            semsim::Subject(world, semsim::RDFURINode(world, "Metaid0034")),
            physical_property,
            semsim::Resource(world, semsim::RDFURINode(world, "obo/PR_000000365")), // is smad3
            std::vector<semsim::Resource>(
                    {semsim::Resource(world, semsim::RDFURINode(world, "https://identifiers.org/fma/FMA:72564")),
                     semsim::Resource(world, semsim::RDFURINode(world, "https://identifiers.org/fma/FMA:63877"))
                    })
    );
    std::string actual = physicalEntity.getPhysicalProperty().str();
    std::string expected = "https://identifiers.org/OPB/OPB_00340";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(PhysicalEntityTests, TestIdentityResourceStr) {
    semsim::RDF rdf;
    semsim::PhysicalEntity physicalEntity(
            world,
            model,
            semsim::Subject(world, semsim::RDFURINode(world, "Metaid0034")),
            physical_property,
            semsim::Resource(world, semsim::RDFURINode(world, "obo/PR_000000365")), // is smad3
            std::vector<semsim::Resource>(
                    {semsim::Resource(world, semsim::RDFURINode(world, "https://identifiers.org/fma/FMA:72564")),
                     semsim::Resource(world, semsim::RDFURINode(world, "fma:FMA:63877"))
                    })
    );
    std::string actual = physicalEntity.getIdentityResource().str();
    std::string expected = "https://identifiers.org/obo/PR_000000365";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(PhysicalEntityTests, TestIdentityResourceNode) {
    semsim::RDF rdf;
    semsim::PhysicalEntity physicalEntity(
            world,
            model,
            semsim::Subject(world, semsim::RDFURINode(world, "Metaid0034")),
            physical_property,
            semsim::Resource(world, semsim::RDFURINode(world, "obo/PR_000000365")), // is smad3
            std::vector<semsim::Resource>(
                    {semsim::Resource(world, semsim::RDFURINode(world, "https://identifiers.org/fma/FMA:72564")),
                     semsim::Resource(world, semsim::RDFURINode(world, "fma:FMA:63877"))
                    })
    );
    std::string actual = (const char *) librdf_uri_as_string(
            librdf_node_get_uri(physicalEntity.getIdentityResource().toRdfNode()));
    std::string expected = "https://identifiers.org/obo/PR_000000365";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PhysicalEntityTests, TestLocationResourceStr) {
    semsim::RDF rdf;
    semsim::PhysicalEntity physicalEntity(
            world,
            model,
            semsim::Subject(world, semsim::RDFURINode(world, "Metaid0034")),
            physical_property,
            semsim::Resource(world, semsim::RDFURINode(world, "obo/PR_000000365")), // is smad3
            std::vector<semsim::Resource>(
                    {semsim::Resource(world, semsim::RDFURINode(world, "https://identifiers.org/fma/FMA:72564")),
                     semsim::Resource(world, semsim::RDFURINode(world, "fma:FMA:63877"))
                    })
    );
    std::ostringstream actual;
    for (auto &it: physicalEntity.getLocationResources()) {
        actual << it.str() << std::endl;
    }
    std::string expected = "https://identifiers.org/fma/FMA:72564\n"
                           "https://identifiers.org/fma/FMA:63877\n";
    ASSERT_STREQ(expected.c_str(), actual.str().c_str());
}

TEST_F(PhysicalEntityTests, TestLocationResourceNode) {
    semsim::RDF rdf;
    semsim::PhysicalEntity physicalEntity(
            world,
            model,
            semsim::Subject(world, semsim::RDFURINode(world, "Metaid0034")),
            physical_property,
            semsim::Resource(world, semsim::RDFURINode(world, "obo/PR_000000365")), // is smad3
            std::vector<semsim::Resource>(
                    {semsim::Resource(world, semsim::RDFURINode(world, "https://identifiers.org/fma/FMA:72564")),
                     semsim::Resource(world, semsim::RDFURINode(world, "fma:FMA:63877"))
                    })
    );
    std::ostringstream actual;
    for (auto &it: physicalEntity.getLocationResources()) {
        actual << librdf_uri_as_string(librdf_node_get_uri(it.toRdfNode())) << std::endl;
    }
    std::string expected = "https://identifiers.org/fma/FMA:72564\n"
                           "https://identifiers.org/fma/FMA:63877\n";
    ASSERT_STREQ(expected.c_str(), actual.str().c_str());
}

TEST_F(PhysicalEntityTests, TestToTripleSize) {
    semsim::RDF rdf;
    semsim::PhysicalEntity physicalEntity(
            world,
            model,
            semsim::Subject(world, semsim::RDFURINode(world, "Metaid0034")),
            physical_property,
            semsim::Resource(world, semsim::RDFURINode(world, "obo/PR_000000365")), // is smad3
            std::vector<semsim::Resource>(
                    {semsim::Resource(world, semsim::RDFURINode(world, "https://identifiers.org/fma/FMA:72564")),
                     semsim::Resource(world, semsim::RDFURINode(world, "fma:FMA:63877"))
                    })
    );

    semsim::Triples triples = physicalEntity.toTriples();
    int expected = 4;
    int actual = triples.size();
    ASSERT_EQ(expected, actual);
}


TEST_F(PhysicalEntityTests, TestToTriple) {
    semsim::RDF rdf;
    semsim::PhysicalEntity physicalEntity(
            world,
            model,
            semsim::Subject(world, semsim::RDFURINode(world, "Metaid0034")),
            physical_property,
            semsim::Resource(world, semsim::RDFURINode(world, "obo/PR_000000365")), // is smad3
            std::vector<semsim::Resource>(
                    {semsim::Resource(world, semsim::RDFURINode(world, "https://identifiers.org/fma/FMA:72564")),
                     semsim::Resource(world, semsim::RDFURINode(world, "fma:FMA:63877"))
                    })
    );
    semsim::Triples triples = physicalEntity.toTriples();
    std::ostringstream actual;

    for (auto &triple : triples) {
        actual << triple.getResource().str() << std::endl;
    }
    std::string expected = "https://identifiers.org/OPB/OPB_00340\n"
                           "https://identifiers.org/obo/PR_000000365\n"
                           "https://identifiers.org/fma/FMA:72564\n"
                           "https://identifiers.org/fma/FMA:63877\n";

    ASSERT_STREQ(actual.str().c_str(), expected.c_str());

}

TEST_F(PhysicalEntityTests, TestWhereTriple) {
    semsim::RDF rdf;
    semsim::PhysicalEntity physicalEntity(
            world,
            model,
            semsim::Subject(world, semsim::RDFURINode(world, "Metaid0034")),
            physical_property,
            semsim::Resource(world, semsim::RDFURINode(world, "obo/PR_000000365")), // is smad3
            std::vector<semsim::Resource>(
                    {semsim::Resource(world, semsim::RDFURINode(world, "https://identifiers.org/fma/FMA:72564")),
                     semsim::Resource(world, semsim::RDFURINode(world, "fma:FMA:63877"))
                    })
    );
    semsim::Triples triples = physicalEntity.where();


//    semsim::Triples triples = physicalEntity.toTriples();
//    std::ostringstream actual;
//
//    for (auto &triple : triples) {
//        actual << triple.getResource().str() << std::endl;
//    }
//    std::string expected = "https://identifiers.org/OPB/OPB_00340\n"
//                           "https://identifiers.org/obo/PR_000000365\n"
//                           "https://identifiers.org/fma/FMA:72564\n"
//                           "https://identifiers.org/fma/FMA:63877\n";
//
//    ASSERT_STREQ(actual.str().c_str(), expected.c_str());

}









