//
// Created by Ciaran on 4/17/2020.
//

#include "gtest/gtest.h"
#include "semsim/RDFTerm.h"

class TermTests : public ::testing::Test {
public:
    TermTests() {

    }

};


TEST_F(TermTests, TestURITerm) {
    std::string uri_str = "http://bioportal.bioontology.org/virtual/2006/FMA:9670";
    semsim::URITerm term(uri_str);
    ASSERT_STREQ(uri_str.c_str(), term.str().c_str());
}

TEST_F(TermTests, TestURITermWithFragment) {
    std::string uri_str = "http://bioportal.bioontology.org/virtual/2006/FMA:9670#here";
    semsim::URITerm term(uri_str);
    ASSERT_STREQ(uri_str.c_str(), term.str().c_str());
}


TEST_F(TermTests, TestURITermRelative) {
    std::string uri_base = "http://bioportal.bioontology.org/virtual/2006";
    std::string uri_rel = "FMA:9670";
    std::string expected = uri_rel;
//    semsim::RelativeURITerm term(uri_base, uri_rel);
//    ASSERT_STREQ(expected.c_str(), term.str().c_str());
}

TEST_F(TermTests, TestURITermRelative2Abs) {
    std::string uri_base = "http://bioportal.bioontology.org/virtual/2006";
    std::string uri_rel = "FMA:9670";
    std::string expected = uri_base + "/" + uri_rel;
    semsim::URITerm term(uri_base, uri_rel);
//    ASSERT_STREQ(expected.c_str(), term.absoluteStr().c_str());
}

TEST_F(TermTests, TestIdentifiersURITerm1) {
    std::string uri_base = "http://identifiers.org/fma/FMA:9696";
//    std::string uri_rel = "FMA:9670";
    semsim::URITerm term("fma", "FMA:9696");
    std::cout << term.str() << std::endl;
    std::string expected = uri_base;
//    std::string actual = term.absoluteStr();
//    ASSERT_STREQ(expected.c_str(), actual.c_str());

}




































