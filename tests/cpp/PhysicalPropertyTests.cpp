//
// Created by Ciaran on 4/22/2020.
//


#include "gtest/gtest.h"
#include "omexmeta/Triple.h"
#include "omexmeta/PhysicalProperty.h"

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


TEST_F(PhysicalPropertyTests, TestToTriples) {
    PhysicalProperty resource = PhysicalProperty("sub", "OPB/OPB_1234");
    Triples triples = resource.toTriples("prop");
    auto r = triples.getResources();
    std::string expeted = "<sub> <http://biomodels.net/biology-qualifiers/isPropertyOf> <prop> .\n"
                          "<sub> <http://biomodels.net/biology-qualifiers/isVersionOf> <https://identifiers.org/OPB/OPB_1234> .\n";
    std::string actual = triples.str("ntriples", "PhysicalPropertyTests_TestToTriples");
    std::cout << actual << std::endl;
    ASSERT_STREQ(expeted.c_str(), actual.c_str());
    triples.freeTriples();
}

TEST_F(PhysicalPropertyTests, TestToTriplesLowerCaseOPB) {
    PhysicalProperty resource = PhysicalProperty("sub", "opb/opb_1234");
    Triples triples = resource.toTriples("prop");
    auto r = triples.getResources();
    std::string expeted = "<sub> <http://biomodels.net/biology-qualifiers/isPropertyOf> <prop> .\n"
                          "<sub> <http://biomodels.net/biology-qualifiers/isVersionOf> <https://identifiers.org/opb/opb_1234> .\n";
    std::string actual = triples.str("ntriples", "PhysicalPropertyTests_TestToTriplesLowerCaseOPB");
    ASSERT_STREQ(expeted.c_str(), actual.c_str());
    triples.freeTriples();
}

TEST_F(PhysicalPropertyTests, TestToTriplesUsingColonNotSlash) {
    PhysicalProperty resource = PhysicalProperty("sub", "opb:opb_1234");
    Triples triples = resource.toTriples("prop");
    auto r = triples.getResources();
    std::string expeted = "<sub> <http://biomodels.net/biology-qualifiers/isPropertyOf> <prop> .\n"
                          "<sub> <http://biomodels.net/biology-qualifiers/isVersionOf> <https://identifiers.org/opb/opb_1234> .\n";
    std::string actual = triples.str("ntriples", "PhysicalPropertyTests_TestToTriplesUsingColonNotSlash");
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




















