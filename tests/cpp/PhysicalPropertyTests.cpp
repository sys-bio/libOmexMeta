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
    triple.freeStatement();
}


TEST_F(PhysicalPropertyTests, TestToTriple2) {
    Triple triple = PhysicalPropertyResource("OPB/OPB_1234").isVersionOfTriple("Entity0");
    std::string actual = triple.getResourceStr();
    std::string expected = "https://identifiers.org/OPB/OPB_1234";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    triple.freeStatement();
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
    triple.freeStatement();
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
    triples.freeTriples();
}

TEST_F(PhysicalPropertyTests, TestToTriples2) {
    PhysicalPropertyResource resource = PhysicalPropertyResource("OPB/OPB_1234");
    Subject s(LibrdfNode::fromUriString("https://subject.com"));
    Triples triples = resource.toTriples(s, "prop");
    auto r = triples.getResources();
    std::string expeted = "https://identifiers.org/OPB/OPB_1234";
    std::string actual = r[0];
    ASSERT_STREQ(expeted.c_str(), actual.c_str());
    triples.freeTriples();
}

/*********************************************************************
 * Test reference counts in the underlying redland library.
 * Helped me bore into a bug where resource node pointer created by PhysicalPropertyResource
 * on instantiation was copied to Triple, not given, so that resources were not properly freed.
 * (run with valgrind or address sanitizer)
 */

class PhysicalPropertyTestsResourceCounts : public ::testing::Test {
public:
    PhysicalPropertyResource resource = PhysicalPropertyResource("OPB/OPB_1234");
    PhysicalPropertyTestsResourceCounts() {}
};

TEST_F(PhysicalPropertyTestsResourceCounts, TestResourceUsage) {
    ASSERT_EQ(1, resource.getNode()->usage);
    resource.free();
}

TEST_F(PhysicalPropertyTestsResourceCounts, TestSubjectUsage) {
    Subject s(LibrdfNode::fromUriString("https://subject.com"));
    ASSERT_EQ(1, s.getNode()->usage);
    s.free();
    resource.free();
}

TEST_F(PhysicalPropertyTestsResourceCounts, TestIsPropertyOfTriple) {
    Subject s(LibrdfNode::fromUriString("https://subject.com"));
    Triple triple1 = resource.isPropertyOfTriple(s, "property");
    ASSERT_EQ(1, triple1.getStatement()->usage);
    ASSERT_EQ(1, triple1.getSubject()->usage);
    ASSERT_EQ(1, triple1.getPredicate()->usage);
    ASSERT_EQ(1, triple1.getResource()->usage);
    triple1.freeStatement();

    // The isPropertyOf triple doesn't use the resource node given as argument
    //  to the constructor. So for this test, we need to free it manually.
    resource.free();
}

TEST_F(PhysicalPropertyTestsResourceCounts, TestIsVersionOfTriple) {
    Triple triple1 = resource.isVersionOfTriple("property");
    ASSERT_EQ(1, triple1.getStatement()->usage);
    ASSERT_EQ(1, triple1.getSubject()->usage);
    ASSERT_EQ(1, triple1.getPredicate()->usage);
    ASSERT_EQ(1, triple1.getResource()->usage);
    triple1.freeStatement();
}




















