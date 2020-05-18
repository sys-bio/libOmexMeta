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

TEST_F(RaptorUriTests, TestCreation) {
    semsim::LibrdfWorld librdfWorld;
    semsim::RaptorWorld raptorWorld = librdfWorld.getRaptor();
    int actual = raptorWorld.getRefCount();
    int expected = 1;
    ASSERT_EQ(actual, expected);
}

TEST_F(RaptorUriTests, TestCopyConstructor) {
    semsim::LibrdfWorld librdfWorld;
    semsim::RaptorWorld raptorWorld1 = librdfWorld.getRaptor();
    semsim::RaptorWorld raptorWorld2 = raptorWorld1;
    ASSERT_EQ(2, raptorWorld1.getRefCount());
    ASSERT_EQ(2, raptorWorld2.getRefCount());
    ASSERT_EQ(raptorWorld1, raptorWorld2);
}

TEST_F(RaptorUriTests, TestMoveConstructor) {
    semsim::LibrdfWorld librdfWorld;
    semsim::RaptorWorld raptorWorld1 = librdfWorld.getRaptor();
    semsim::RaptorWorld raptorWorld2 = std::move(raptorWorld1);
    ASSERT_EQ(1, raptorWorld1.getRefCount());
    ASSERT_EQ(1, raptorWorld2.getRefCount());
    ASSERT_NE(raptorWorld1, raptorWorld2);
}

TEST_F(RaptorUriTests, TestCopyAssignment) {
    semsim::LibrdfWorld librdfWorld;
    semsim::RaptorWorld raptorWorld1 = librdfWorld.getRaptor();
    semsim::RaptorWorld raptorWorld2 = librdfWorld.getRaptor();
    raptorWorld2 = raptorWorld1;
    ASSERT_EQ(2, raptorWorld1.getRefCount());
    ASSERT_EQ(2, raptorWorld2.getRefCount());
    ASSERT_EQ(raptorWorld1.getRaptorWorld(), raptorWorld2.getRaptorWorld());
    ASSERT_EQ(raptorWorld1, raptorWorld2);
}

TEST_F(RaptorUriTests, TestMoveAssignment) {
    semsim::LibrdfWorld librdfWorld;
    semsim::RaptorWorld raptorWorld1 = librdfWorld.getRaptor();
    semsim::RaptorWorld raptorWorld2 = librdfWorld.getRaptor();
    raptorWorld2 = std::move(raptorWorld1);
    ASSERT_EQ(1, raptorWorld1.getRefCount());
    ASSERT_EQ(1, raptorWorld2.getRefCount());
    ASSERT_NE(raptorWorld1, raptorWorld2);
}



