//
// Created by Ciaran on 5/17/2020.
//

#include "gtest/gtest.h"

#include "semsim/RelandAPIWrappers/RaptorWorld.h"
#include "semsim/RelandAPIWrappers/LibrdfWorld.h"

class RaptorUriTests : public ::testing::Test {

public:

    RaptorUriTests() = default;

};

TEST_F(RaptorUriTests, TestCreate) {
    semsim::LibrdfWorld librdfWorld;
    semsim::RaptorWorld raptorWorld1 = librdfWorld.getRaptor();
    std::string expected = "https://notarealaddress.com";
    semsim::RaptorUri raptorUri = raptorWorld1.newRaptorUri(expected);
    std::string actual = raptorUri.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(RaptorUriTests, TestCopyConstructor) {
    semsim::LibrdfWorld librdfWorld;
    semsim::RaptorWorld raptorWorld1 = librdfWorld.getRaptor();
    std::string expected = "https://notarealaddress.com";
    semsim::RaptorUri raptorUri1 = raptorWorld1.newRaptorUri(expected);
    semsim::RaptorUri raptorUri2 = raptorUri1;
    ASSERT_STREQ(expected.c_str(), raptorUri1.str().c_str());
    ASSERT_STREQ(expected.c_str(), raptorUri2.str().c_str());
}

TEST_F(RaptorUriTests, TestMoveConstructor) {
    std::string expected = "https://notarealaddress.com";
    semsim::LibrdfWorld librdfWorld;
    semsim::RaptorWorld raptorWorld1 = librdfWorld.getRaptor();
    semsim::RaptorUri raptorUri1 = raptorWorld1.newRaptorUri(expected);
    semsim::RaptorUri raptorUri2 = std::move(raptorUri1);
    ASSERT_STREQ(raptorUri2.str().c_str(), expected.c_str());
}

TEST_F(RaptorUriTests, TestMobvrAssignment) {
    std::string expected = "https://notarealaddress1.com";
    std::string expected2 = "https://notarealaddress2.com";
    semsim::LibrdfWorld librdfWorld;
    semsim::RaptorWorld raptorWorld1 = librdfWorld.getRaptor();
    semsim::RaptorUri raptorUri1 = raptorWorld1.newRaptorUri(expected);
    semsim::RaptorUri raptorUri2 = raptorWorld1.newRaptorUri(expected2);
    raptorUri1 = std::move(raptorUri2);
    ASSERT_STREQ(raptorUri1.str().c_str(), expected2.c_str());
}

TEST_F(RaptorUriTests, TestCopyAssignment) {
    std::string expected = "https://notarealaddress1.com";
    std::string expected2 = "https://notarealaddress2.com";
    semsim::LibrdfWorld librdfWorld;
    semsim::RaptorWorld raptorWorld1 = librdfWorld.getRaptor();
    semsim::RaptorUri raptorUri1 = raptorWorld1.newRaptorUri(expected);
    semsim::RaptorUri raptorUri2 = raptorWorld1.newRaptorUri(expected2);
    raptorUri1 = raptorUri2;
    ASSERT_STREQ(raptorUri1.str().c_str(), expected2.c_str());
    ASSERT_STREQ(raptorUri2.str().c_str(), expected2.c_str());
}



