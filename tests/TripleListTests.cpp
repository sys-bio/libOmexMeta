//
// Created by Ciaran on 4/15/2020.
//

#include <semsim/Triple.h>
#include <semsim/TripleList.h>
#include "gtest/gtest.h"

class TripleListTests : public ::testing::Test {

public:


    std::string subject_str1 = "./MyModel#metaid_0";
    std::string subject_str2 = "./MyModel#metaid_1";
    std::string subject_str3 = "./MyModel#metaid_2";
    std::string predicate_str = "http://biomodels.net/biology-qualifiers/is";
    std::string resource_str1 = "uniprot:P0DP23";
    std::string resource_str2 = "uniprot:P0DP24";
    std::string resource_str3 = "uniprot:P0DP25";

    semsim::Triple triple1;
    semsim::Triple triple2;
    semsim::Triple triple3;


    TripleListTests() {
        triple1 = semsim::Triple(
                semsim::Subject(subject_str1),
                semsim::BiomodelsQualifier("is"),
                semsim::Resource(resource_str1)
        );
        triple2 = semsim::Triple(
                semsim::Subject(subject_str2),
                semsim::BiomodelsQualifier("is"),
                semsim::Resource(resource_str2)
        );
        triple3 = semsim::Triple(
                semsim::Subject(subject_str3),
                semsim::BiomodelsQualifier("is"),
                semsim::Resource(resource_str3)
        );
    };
};

TEST_F(TripleListTests, TestDefaultConstruction) {
    semsim::TripleList tripleList;
    ASSERT_TRUE(true);
}

TEST_F(TripleListTests, TestAlternativeConstruction) {
    std::vector<semsim::Triple> triples = {triple2, triple2, triple3};
    semsim::TripleList tripleList(triples);
    ASSERT_TRUE(true);
}

TEST_F(TripleListTests, TestAlternativeConstruction2) {
    semsim::TripleList tripleList({triple2, triple2, triple3});
    ASSERT_TRUE(true);
}

TEST_F(TripleListTests, TestPushBack) {
    semsim::TripleList tripleList;
    tripleList.push_back(triple1);
    tripleList.push_back(triple2);
    tripleList.push_back(triple3);
    std::string expected("P0DP25");
    std::string actual = tripleList[2].getResource().getIdentifier();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(TripleListTests, TestEmplaceBack) {
    semsim::TripleList tripleList;
    tripleList.emplace_back(
            semsim::Subject(subject_str1),
            semsim::BiomodelsQualifier("is"),
            semsim::Resource(resource_str1)
    );
    std::string expected("P0DP23");
    std::string actual = tripleList[0].getResource().getIdentifier();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}












