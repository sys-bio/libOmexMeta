//
// Created by Ciaran on 5/17/2020.
//

#include "gtest/gtest.h"
#include "World.h"
#include "LibrdfUri.h"
//#include "redland/SemsimUtils.h"
#include "raptor2.h"

using namespace redland;

class LibrdfUriTests : public ::testing::Test {

public:

    LibrdfUriTests() = default;

};

TEST_F(LibrdfUriTests, TestCreate) {
    LibrdfUri uri("http://uri.com");
    std::string expected = "http://uri.com";
    std::string actual = uri.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(LibrdfUriTests, TestGet) {
    LibrdfUri uri("http://uri.com");
    librdf_uri *curi = uri.get();
    std::string expected = "http://uri.com";
    auto cstr = (unsigned char *) librdf_uri_as_string(curi);
    ASSERT_STREQ(expected.c_str(), (const char *) cstr);
}

TEST_F(LibrdfUriTests, TestStr) {
    LibrdfUri uri("http://uri.com");
    std::string expected = "http://uri.com";
    std::string actual = uri.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(LibrdfUriTests, TestIsNullFalse) {
    LibrdfUri uri("http://uri.com");
    ASSERT_FALSE(uri.isNull());
}

TEST_F(LibrdfUriTests, TestIsNull) {
    LibrdfUri uri{};
    ASSERT_TRUE(uri.isNull());
}

TEST_F(LibrdfUriTests, TestIsEmpty1) {
    LibrdfUri uri("");
    ASSERT_TRUE(uri.isNull());
}

TEST_F(LibrdfUriTests, TestIsEmpty2) {
    LibrdfUri uri((std::string()));
    ASSERT_TRUE(uri.isNull());
}


