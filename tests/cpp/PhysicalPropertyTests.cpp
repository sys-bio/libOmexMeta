//
// Created by Ciaran on 4/22/2020.
//


#include "gtest/gtest.h"
#include <semsim/Triple.h>
#include "semsim/PhysicalProperty.h"

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


TEST_F(PhysicalPropertyTests, TestPhysicalPropertySubjectStr) {
    PhysicalProperty property = PhysicalProperty("subject", "OPB:OPB_00154");
    std::string expected = "subject";
    std::string actual = property.getSubjectStr();
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PhysicalPropertyTests, TestPhysicalPropertyResourceStr) {
    PhysicalProperty property = PhysicalProperty("subject", "OPB:OPB_00154");
    std::string expected = "OPB:OPB_00154";
    std::string actual = property.getResourceStr();
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PhysicalPropertyTests, TestPhysicalPropertyGetItWrong) {
    ASSERT_THROW(PhysicalProperty("subject", "not_obp:OPB_00154"),
            InappropriateResourceException);
}

//TEST_F(PhysicalPropertyTests, TestToTriple1) {
//    PhysicalProperty p = PhysicalProperty("Entity0", "OPB/OPB_1234");
//    Triple triple = p.isVersionOfTriple();
//    std::string actual = triple.getSubjectStr();
//    std::string expected = "Entity0";
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//    triple.freeStatement();
//}
//
//
//TEST_F(PhysicalPropertyTests, TestToTriple2) {
//    PhysicalProperty p = PhysicalProperty("Entity0", "OPB/OPB_1234");
//    Triple triple = p.isVersionOfTriple();
//    std::string actual = triple.getResourceStr();
//    std::string expected = "https://identifiers.org/OPB/OPB_1234";
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//    triple.freeStatement();
//}

//TEST_F(PhysicalPropertyTests, TestToTriple3) {
//    Triple triple = PhysicalProperty("Entity0", "OPB/OPB_1234").isVersionOfTriple();
//
//    std::string actual = triple.str();
//    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
//                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
//                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
//                           "   xml:base=\"file://./annotations.rdf\">\n"
//                           "  <rdf:Description rdf:about=\"Entity0\">\n"
//                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/OPB/OPB_1234\"/>\n"
//                           "  </rdf:Description>\n"
//                           "</rdf:RDF>\n"
//                           "";
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//    triple.freeStatement();
//}


//TEST_F(PhysicalPropertyTests, TestFree) {
//    PhysicalProperty resource = PhysicalProperty("OPB/OPB_1234");
//    resource.free();
//    // run with valgrind: pass
//}

TEST_F(PhysicalPropertyTests, TestToTriples) {
    PhysicalProperty resource = PhysicalProperty("sub", "OPB/OPB_1234");
    Triples triples = resource.toTriples("prop");
    auto r = triples.getResources();
    std::string expeted = "https://identifiers.org/OPB/OPB_1234";
    std::string actual = r[0];
    ASSERT_STREQ(expeted.c_str(), actual.c_str());
    triples.freeTriples();
}

TEST_F(PhysicalPropertyTests, TestToTriplesLowerCaseOPB) {
    PhysicalProperty resource = PhysicalProperty("sub", "opb/opb_1234");
    Triples triples = resource.toTriples("prop");
    auto r = triples.getResources();
    std::string expeted = "https://identifiers.org/opb/opb_1234";
    std::string actual = r[0];
    ASSERT_STREQ(expeted.c_str(), actual.c_str());
    triples.freeTriples();
}

TEST_F(PhysicalPropertyTests, TestToTriplesUsingColonNotSlash) {
    PhysicalProperty resource = PhysicalProperty("sub", "opb:opb_1234");
    Triples triples = resource.toTriples("prop");
    auto r = triples.getResources();
    std::string expeted = "https://identifiers.org/opb/opb_1234";
    std::string actual = r[0];
    ASSERT_STREQ(expeted.c_str(), actual.c_str());
    triples.freeTriples();
}

TEST_F(PhysicalPropertyTests, TestEquality) {
    PhysicalProperty resource1 = PhysicalProperty("sub", "OPB/OPB_1234");
    PhysicalProperty resource2 = PhysicalProperty("sub", "OPB/OPB_1234");
    ASSERT_EQ(resource1, resource2);
}

TEST_F(PhysicalPropertyTests, TestInequality) {
    PhysicalProperty resource1 = PhysicalProperty("sub1", "OPB/OPB_1234");
    PhysicalProperty resource2 = PhysicalProperty("sub2", "OPB/OPB_1234");
    ASSERT_NE(resource1, resource2);
}

TEST_F(PhysicalPropertyTests, TestInequality2) {
    PhysicalProperty resource1 = PhysicalProperty("property_metaid_0", "opb/OPB_00592");
    PhysicalProperty resource2 = PhysicalProperty("property_metaid_1", "opb/OPB_00592");
    ASSERT_NE(resource1, resource2);
}

//TEST_F(PhysicalPropertyTests, TestToTriples2) {
//    Subject s(LibrdfNode::fromUriString("https://subject.com"));
//    PhysicalProperty resource = PhysicalProperty("sub", "OPB/OPB_1234");
//    Triples triples = resource.toTriples(s, "prop");
//    auto r = triples.getResources();
//    std::string expeted = "https://identifiers.org/OPB/OPB_1234";
//    std::string actual = r[0];
//    ASSERT_STREQ(expeted.c_str(), actual.c_str());
//    triples.freeTriples();
//}

/*********************************************************************
 * Test reference counts in the underlying redland library.
 * Helped me bore into a bug where resource node pointer created by PhysicalProperty
 * on instantiation was copied to Triple, not given, so that resources were not properly freed.
 * (run with valgrind or address sanitizer)
 */

class PhysicalPropertyTestsResourceCounts : public ::testing::Test {
public:
    PhysicalProperty resource = PhysicalProperty("metaid", "OPB/OPB_1234");
    PhysicalPropertyTestsResourceCounts() {}
};


TEST_F(PhysicalPropertyTestsResourceCounts, TestSubjectUsage) {
    Subject s(LibrdfNode::fromUriString("https://subject.com"));
    ASSERT_EQ(1, s.getNode()->usage);
    s.free();
}

//TEST_F(PhysicalPropertyTestsResourceCounts, TestIsPropertyOfTriple) {
//    Subject s(LibrdfNode::fromUriString("https://subject.com"));
//    Triple triple1 = resource.isPropertyOfTriple(s, "property");
//    ASSERT_EQ(1, triple1.getStatement()->usage);
//    ASSERT_EQ(1, triple1.getSubject()->usage);
//    ASSERT_EQ(1, triple1.getPredicate()->usage);
//    ASSERT_EQ(1, triple1.getResource()->usage);
//    triple1.freeStatement();
//
//    // The isPropertyOf triple doesn't use the resource node given as argument
//    //  to the constructor. So for this test, we need to free it manually.
//}

//TEST_F(PhysicalPropertyTestsResourceCounts, TestIsVersionOfTriple) {
//    Triple triple1 = resource.isVersionOfTriple();
//    ASSERT_EQ(1, triple1.getStatement()->usage);
//    ASSERT_EQ(1, triple1.getSubject()->usage);
//    ASSERT_EQ(1, triple1.getPredicate()->usage);
//    ASSERT_EQ(1, triple1.getResource()->usage);
//    triple1.freeStatement();
//}




















