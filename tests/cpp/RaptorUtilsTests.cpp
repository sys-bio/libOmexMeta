//
// Created by Ciaran on 4/7/2020.
//

#include "gtest/gtest.h"
#include "raptor2.h"
#include "semsim/RaptorUtils.h"


class RaptorUtilsTests : public ::testing::Test {
public:
    std::string str ;
    const unsigned char* cstr;
    raptor_uri *uri;
    raptor_term *term;
    raptor_world* world;

    RaptorUtilsTests() {
        str = "https://stackoverflow.com";
        cstr = (const unsigned char *)str.c_str();
        world = raptor_new_world();
        uri = raptor_new_uri(world, cstr);
        term = raptor_new_term_from_uri(world, uri);
    }

    ~RaptorUtilsTests() override{
        raptor_free_world(world);
        raptor_free_uri(uri);
        raptor_free_term(term);
    }
};


TEST_F(RaptorUtilsTests, TestRaptorStringToUri) {
    raptor_uri* uri2 = semsim::RaptorUtils::raptorStringToUri(world, cstr);
    const unsigned char* str2 = raptor_uri_to_string(uri2);
    ASSERT_STREQ((const char*)cstr, (const char*) str2);
}

TEST_F(RaptorUtilsTests, TestRaptorUriToString) {
    std::string str2 = semsim::RaptorUtils::raptorUriToString(uri);
    ASSERT_STREQ((const char*)cstr, str.c_str());
}

TEST_F(RaptorUtilsTests, TestRaptorUriToTerm) {
    raptor_term* term2 = semsim::RaptorUtils::raptorUriToTerm(world,uri);
    raptor_uri* uri2 = term2->value.uri;
    ASSERT_EQ(uri, uri2);
}

TEST_F(RaptorUtilsTests, TestRaptorTermToString) {
    const unsigned char* cstr2 = semsim::RaptorUtils::raptorTermToString(term);
    const char* expected = "<https://stackoverflow.com>";
    ASSERT_STREQ(expected, (const char*)cstr2);
}

//TEST_F(RaptorUtilsTests, TestRaptorUriToTerm) {
//    raptor_term* term2 = semsim::RaptorUtils::raptorUriToTerm(world,uri);
//    ASSERT_EQ(term, term2);
//}
