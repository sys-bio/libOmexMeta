//
// Created by Ciaran on 5/17/2020.
//

#include "gtest/gtest.h"

#include "semsim/RedlandAPIWrappers/RaptorWorld.h"
#include "semsim/RedlandAPIWrappers/LibrdfWorld.h"

class LibrdfUriTests : public ::testing::Test {

public:
    semsim::LibrdfWorld librdfWorld;

    LibrdfUriTests() = default;

};

TEST_F(LibrdfUriTests, TestCreate) {
    std::string expected = "https://notarealaddress.com";
    semsim::LibrdfUri librdfUri = librdfWorld.newUri(expected);
    std::string actual = librdfUri.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(LibrdfUriTests, TestCopyConstructor) {
    semsim::LibrdfWorld librdfWorld;
    std::string expected = "https://notarealaddress.com";
    semsim::LibrdfUri librdfUri1 = librdfWorld.newUri(expected);
    semsim::LibrdfUri librdfUri2 = librdfUri1;
    ASSERT_STREQ(expected.c_str(), librdfUri1.str().c_str());
    ASSERT_STREQ(expected.c_str(), librdfUri2.str().c_str());
}

TEST_F(LibrdfUriTests, TestMoveConstructor) {
    std::string expected = "https://notarealaddress.com";
    semsim::LibrdfUri librdfUri1 = librdfWorld.newUri(expected);
    semsim::LibrdfUri librdfUri2 = std::move(librdfUri1);
    ASSERT_STREQ(librdfUri2.str().c_str(), expected.c_str());
}

TEST_F(LibrdfUriTests, TestMobvrAssignment) {
    std::string expected = "https://notarealaddress1.com";
    std::string expected2 = "https://notarealaddress2.com";
    semsim::LibrdfUri librdfUri1 = librdfWorld.newUri(expected);
    semsim::LibrdfUri librdfUri2 = librdfWorld.newUri(expected2);
    librdfUri1 = std::move(librdfUri2);
    ASSERT_STREQ(librdfUri1.str().c_str(), expected2.c_str());
}

TEST_F(LibrdfUriTests, TestCopyAssignment) {
    std::string expected = "https://notarealaddress1.com";
    std::string expected2 = "https://notarealaddress2.com";
    semsim::LibrdfUri librdfUri1 = librdfWorld.newUri(expected);
    semsim::LibrdfUri librdfUri2 = librdfWorld.newUri(expected2);
    librdfUri1 = librdfUri2;
    ASSERT_STREQ(librdfUri1.str().c_str(), expected2.c_str());
    ASSERT_STREQ(librdfUri2.str().c_str(), expected2.c_str());
}



