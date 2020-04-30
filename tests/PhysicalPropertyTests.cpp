//
// Created by Ciaran on 4/22/2020.
//


#include <semsim/Triple.h>
#include "gtest/gtest.h"
#include "librdf.h"
#include "semsim/PhysicalPropertyResource.h"


class PhysicalPropertyTests : public ::testing::Test {
public:
    librdf_world *world;
    librdf_storage *storage;
    librdf_model *model;

    PhysicalPropertyTests() {
        world = librdf_new_world();
    }
};


TEST_F(PhysicalPropertyTests, TestPhysicalPropertyResource) {
    semsim::PhysicalPropertyResource property = semsim::PhysicalPropertyResource(
            world,
            semsim::RDFURINode(world, "OPB:OPB_00154")
    );
    std::string expected = "https://identifiers.org/OPB/OPB_00154";
    std::string actual = property.str();
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(PhysicalPropertyTests, TestFailureOnNonOPBResource) {
    ASSERT_THROW(semsim::PhysicalPropertyResource(
            world,
            semsim::RDFURINode(world, "other/identifier72652")
    ), semsim::InappropriateResourceException);
}


TEST_F(PhysicalPropertyTests, TestToTriple1) {
    semsim::Triple triple = semsim::PhysicalPropertyResource(
            world,
            semsim::RDFURINode(world, "OPB/OPB_1234")
    ).isVersionOfTriple("Entity0");

    std::string actual = (const char *) librdf_uri_as_string(
            librdf_node_get_uri(
                    triple.getSubject().toRdfNode()
            )
    );
    std::string expected = "Entity0";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(PhysicalPropertyTests, TestToTriple2) {
    semsim::Triple triple = semsim::PhysicalPropertyResource(
            world,
            semsim::RDFURINode(world, "OPB/OPB_1234")
    ).isVersionOfTriple("Entity0");

    std::string actual = (const char *) librdf_uri_as_string(
            librdf_node_get_uri(
                    triple.getResource().toRdfNode()
            )
    );
    std::string expected = "https://identifiers.org/OPB/OPB_1234";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PhysicalPropertyTests, TestToTriple3) {
    semsim::Triple triple = semsim::PhysicalPropertyResource(
            world,
            semsim::RDFURINode(world, "OPB/OPB_1234")
    ).isVersionOfTriple("Entity0");


    std::string actual = triple.str();
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"Entity0\">\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/OPB/OPB_1234\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

















