//
// Created by Ciaran on 5/17/2020.
//

#include "gtest/gtest.h"
#include "semsim/RedlandAPIWrapper/LibrdfWorld.h"
#include "semsim/RedlandAPIWrapper/LibrdfUri.h"
#include "semsim/SemsimUtils.h"

class LibrdfUriTests : public ::testing::Test {

public:

    LibrdfUriTests() = default;

};

TEST_F(LibrdfUriTests, TestCreate) {
    semsim::LibrdfWorld world;
    semsim::LibrdfUri uri = world.newUri("http://uri.com");
    std::string expected = "http://uri.com";
    std::string actual = uri.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(LibrdfUriTests, TestCopyConstruct) {
    semsim::LibrdfWorld world;
    semsim::LibrdfUri uri1 = world.newUri("http://uri.com");
    semsim::LibrdfUri uri2 = uri1;
    std::string expected = "http://uri.com";
    std::string actual = uri2.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(LibrdfUriTests, TestMoveConstruct) {
    semsim::LibrdfWorld world;
    semsim::LibrdfUri uri1 = world.newUri("http://uri1.com");
    semsim::LibrdfUri uri2 = std::move(uri1);
    std::string expected = "http://uri1.com";
    std::string actual = uri2.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(LibrdfUriTests, TestMoveAssign) {
    semsim::LibrdfWorld world;
    semsim::LibrdfUri uri1 = world.newUri("http://uri1.com");
    semsim::LibrdfUri uri2 = world.newUri("http://uri2.com");
    uri1 = std::move(uri2);
    std::string expected = "http://uri2.com";
    std::string actual = uri1.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(LibrdfUriTests, TestCopyAssign) {
    semsim::LibrdfWorld world;
    semsim::LibrdfUri uri1 = world.newUri("http://uri1.com");
    semsim::LibrdfUri uri2 = world.newUri("http://uri2.com");
    uri1 = uri2;
    std::string expected = "http://uri2.com";
    std::string actual = uri2.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}



