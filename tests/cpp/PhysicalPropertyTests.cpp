//
// Created by Ciaran on 4/22/2020.
//


#include "gtest/gtest.h"
#include <semsim/Triple.h>
#include "semsim/PhysicalPropertyResource.h"

using namespace semsim;


class PhysicalPropertyTests : public ::testing::Test {
public:

    LibrdfStorage storage;
    LibrdfModel model;

    PhysicalPropertyTests() {
        model = LibrdfModel(storage.get());
    }

    ~PhysicalPropertyTests() {
        model.freeModel();
        storage.freeStorage();
    }
};


TEST_F(PhysicalPropertyTests, TestPhysicalPropertyResource) {
    PhysicalPropertyResource property = PhysicalPropertyResource("OPB:OPB_00154");
    std::string expected = "https://identifiers.org/OPB/OPB_00154";
    std::string actual = property.str();
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    property.free();
}

TEST_F(PhysicalPropertyTests, TestPhysicalPropertyResourceGetItWrong) {
    PhysicalPropertyResource property = PhysicalPropertyResource("OPB:OPB00154");
    std::string expected = "https://identifiers.org/OPB/OPB00154";
    std::string actual = property.str();
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    property.free();
}


// how to test without memory leak?
//TEST_F(PhysicalPropertyTests, TestFailureOnNonOPBResource) {
//    ASSERT_THROW({
//            PhysicalPropertyResource p("other/identifier72652");
//            p.free();}
//            , InappropriateResourceException);
//
//}


TEST_F(PhysicalPropertyTests, TestToTriple1) {
    Triple triple = PhysicalPropertyResource("OPB/OPB_1234").isVersionOfTriple("Entity0");
    std::string actual = triple.getSubjectStr();
    std::string expected = "Entity0";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(PhysicalPropertyTests, TestToTriple2) {
    Triple triple = PhysicalPropertyResource("OPB/OPB_1234").isVersionOfTriple("Entity0");
    std::string actual = triple.getResourceStr();
    std::string expected = "https://identifiers.org/OPB/OPB_1234";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PhysicalPropertyTests, TestToTriple3) {
    Triple triple = PhysicalPropertyResource(
            "OPB/OPB_1234"
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


TEST_F(PhysicalPropertyTests, TestIsSet) {
    PhysicalPropertyResource resource = PhysicalPropertyResource("OPB/OPB_1234");
    ASSERT_TRUE(resource.isSet());
    resource.free();
}

TEST_F(PhysicalPropertyTests, TestFree) {
    PhysicalPropertyResource resource = PhysicalPropertyResource("OPB/OPB_1234");
    resource.free();
    // run with valgrind: pass
}

TEST_F(PhysicalPropertyTests, TestToTriples) {
    PhysicalPropertyResource resource = PhysicalPropertyResource("OPB/OPB_1234");
    Triples triples = resource.toTriples("sub", "prop");
    auto r = triples.getResources();
    std::string expeted = "https://identifiers.org/OPB/OPB_1234";
    std::string actual = r[0];
    ASSERT_STREQ(expeted.c_str(), actual.c_str());
}

















