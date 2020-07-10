//
// Created by Ciaran on 4/22/2020.
//


#include "gtest/gtest.h"
#include "omexmeta/Triple.h"
#include "omexmeta/PhysicalProperty.h"

using namespace omexmeta;


class PhysicalPropertyTests : public ::testing::Test {
public:

    LibrdfStorage storage;
    LibrdfModel model;

    std::string local_uri = "http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#";

    PhysicalPropertyTests() {
        model = LibrdfModel(storage.get());
    }

    ~PhysicalPropertyTests() {
        model.freeModel();
        storage.freeStorage();
    }
};


TEST_F(PhysicalPropertyTests, TestPhysicalPropertySubjectStr) {
    PhysicalProperty property = PhysicalProperty("subject", "OPB:OPB_00154", local_uri);
    std::string expected = "http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#subject";
    std::string actual = property.getSubjectStr();
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PhysicalPropertyTests, TestPhysicalPropertyResourceStr) {
    PhysicalProperty property = PhysicalProperty("subject", "OPB:OPB_00154", local_uri);
    std::string expected = "OPB:OPB_00154";
    std::string actual = property.getResourceStr();
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PhysicalPropertyTests, TestPhysicalPropertyGetItWrong) {
    ASSERT_THROW(PhysicalProperty("subject", "not_obp:OPB_00154", local_uri),
            InappropriateResourceException);
}


TEST_F(PhysicalPropertyTests, TestToTriples) {
    PhysicalProperty resource = PhysicalProperty("sub", "OPB/OPB_1234", local_uri);
    Triples triples = resource.toTriples("prop");
    auto r = triples.getResources();
    std::string expeted = "<http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#sub> <http://biomodels.net/biology-qualifiers/isPropertyOf> <http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#prop> .\n"
                          "<http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#sub> <http://biomodels.net/biology-qualifiers/isVersionOf> <https://identifiers.org/OPB/OPB_1234> .\n";
    std::string actual = triples.str("ntriples", "PhysicalPropertyTests_TestToTriples");
    std::cout << actual << std::endl;
    ASSERT_STREQ(expeted.c_str(), actual.c_str());
    triples.freeTriples();
}

TEST_F(PhysicalPropertyTests, TestToTriplesLowerCaseOPB) {
    PhysicalProperty resource = PhysicalProperty("sub", "opb/opb_1234", local_uri);
    Triples triples = resource.toTriples("prop");
    auto r = triples.getResources();
    std::string expeted = "<http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#sub> <http://biomodels.net/biology-qualifiers/isPropertyOf> <http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#prop> .\n"
                          "<http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#sub> <http://biomodels.net/biology-qualifiers/isVersionOf> <https://identifiers.org/opb/opb_1234> .\n";
    std::string actual = triples.str("ntriples", "PhysicalPropertyTests_TestToTriplesLowerCaseOPB");
    std::cout << actual << std::endl;
    ASSERT_STREQ(expeted.c_str(), actual.c_str());
    triples.freeTriples();
}

TEST_F(PhysicalPropertyTests, TestToTriplesUsingColonNotSlash) {
    PhysicalProperty resource = PhysicalProperty("sub", "opb:opb_1234", local_uri);
    Triples triples = resource.toTriples("prop");
    auto r = triples.getResources();
    std::string expeted = "<http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#sub> <http://biomodels.net/biology-qualifiers/isPropertyOf> <http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#prop> .\n"
                          "<http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#sub> <http://biomodels.net/biology-qualifiers/isVersionOf> <https://identifiers.org/opb/opb_1234> .\n";
    std::string actual = triples.str("ntriples", "PhysicalPropertyTests_TestToTriplesUsingColonNotSlash");
    std::cout << actual << std::endl;
    ASSERT_STREQ(expeted.c_str(), actual.c_str());
    triples.freeTriples();
}

TEST_F(PhysicalPropertyTests, TestEquality) {
    PhysicalProperty resource1 = PhysicalProperty("sub", "OPB/OPB_1234", local_uri);
    PhysicalProperty resource2 = PhysicalProperty("sub", "OPB/OPB_1234", local_uri);
    ASSERT_EQ(resource1, resource2);
}

TEST_F(PhysicalPropertyTests, TestInequality) {
    PhysicalProperty resource1 = PhysicalProperty("sub1", "OPB/OPB_1234", local_uri);
    PhysicalProperty resource2 = PhysicalProperty("sub2", "OPB/OPB_1234", local_uri);
    ASSERT_NE(resource1, resource2);
}

TEST_F(PhysicalPropertyTests, TestInequality2) {
    PhysicalProperty resource1 = PhysicalProperty("property_metaid_0", "opb/OPB_00592", local_uri);
    PhysicalProperty resource2 = PhysicalProperty("property_metaid_1", "opb/OPB_00592", local_uri);
    ASSERT_NE(resource1, resource2);
}




















