//
// Created by Ciaran on 4/5/2020.
//

#include "gtest/gtest.h"
#include "semsim/Predicate.h"


class PredicateTests : public ::testing::Test {
public:
    std::string bqb_ns;
    PredicateTests() : bqb_ns("http://biomodels.net/biology-qualifiers/") {}
};

TEST_F(PredicateTests, TestUri) {
    semsim::BiomodelsQualifier bqb_is("is");
    std::string expected = bqb_ns + "is";
    ASSERT_STREQ(expected.c_str(), bqb_is.getUri().str().c_str());
}


TEST_F(PredicateTests, TestFailure) {
    ASSERT_THROW(semsim::BiomodelsQualifier bqb_is("isa"), std::invalid_argument);
}


TEST_F(PredicateTests, TestNamespace) {
    semsim::BiomodelsQualifier bqb_is("is");
    std::string expected = "http://biomodels.net/biology-qualifiers/";
    ASSERT_STREQ(expected.c_str(), bqb_is.getNamespace().c_str());
}


TEST_F(PredicateTests, TestStr) {
    semsim::BiomodelsQualifier bqb_is("is");
    std::string expected = "http://biomodels.net/biology-qualifiers/is";
    ASSERT_STREQ(expected.c_str(), bqb_is.str().c_str());
}

TEST_F(PredicateTests, TestPrefix) {
    semsim::BiomodelsQualifier bqb_is("is");
    std::string expected = "bqbiol";
    ASSERT_STREQ(expected.c_str(), bqb_is.getPrefix().c_str());
}

TEST_F(PredicateTests, TestTerm) {
    semsim::BiomodelsQualifier bqb_is("is");
    std::string expected = "is";
    ASSERT_STREQ(expected.c_str(), bqb_is.getTerm().c_str());
}

TEST_F(PredicateTests, TestNamespaceDCTerms) {
    semsim::DCTerms description("Description");
    std::string expected = "http://purl.org/dc/terms/";
    ASSERT_STREQ(expected.c_str(), description.getNamespace().c_str());
}


TEST_F(PredicateTests, TestStrDCTerms) {
    semsim::DCTerms description("Description");
    std::string expected = "http://purl.org/dc/terms/Description";
    ASSERT_STREQ(expected.c_str(), description.str().c_str());
}

TEST_F(PredicateTests, TestPrefixDCTerms) {
    semsim::DCTerms description("Description");
    std::string expected = "dc";
    ASSERT_STREQ(expected.c_str(), description.getPrefix().c_str());
}

TEST_F(PredicateTests, TestTermDCTerms) {
    semsim::DCTerms description("Description");
    std::string expected = "Description";
    ASSERT_STREQ(expected.c_str(), description.getTerm().c_str());
}











