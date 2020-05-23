//
// Created by Ciaran on 5/17/2020.
//

#include "gtest/gtest.h"
#include "semsim/RedlandAPIWrapper/World.h"
#include "semsim/RedlandAPIWrapper/LibrdfUri.h"
#include "semsim/SemsimUtils.h"

using namespace semsim;

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

//TEST_F(LibrdfUriTests, TestCopyConstruct) {
//    semsim::World world;
//    semsim::LibrdfUri uri1 = world.newUri("http://uri.com");
//    semsim::LibrdfUri uri2 = uri1;
//    std::string expected = "http://uri.com";
//    std::string actual = uri2.str();
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}
//
//TEST_F(LibrdfUriTests, TestMoveConstruct) {
//    semsim::World world;
//    semsim::LibrdfUri uri1 = world.newUri("http://uri1.com");
//    semsim::LibrdfUri uri2 = std::move(uri1);
//    std::string expected = "http://uri1.com";
//    std::string actual = uri2.str();
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}
//
//TEST_F(LibrdfUriTests, TestMoveAssign) {
//    semsim::World world;
//    semsim::LibrdfUri uri1 = world.newUri("http://uri1.com");
//    semsim::LibrdfUri uri2 = world.newUri("http://uri2.com");
//    uri1 = std::move(uri2);
//    std::string expected = "http://uri2.com";
//    std::string actual = uri1.str();
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}
//
//TEST_F(LibrdfUriTests, TestCopyAssign) {
//    semsim::World world;
//    semsim::LibrdfUri uri1 = world.newUri("http://uri1.com");
//    semsim::LibrdfUri uri2 = world.newUri("http://uri2.com");
//    uri1 = uri2;
//    std::string expected = "http://uri2.com";
//    std::string actual = uri2.str();
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}



