//
// Created by Ciaran on 5/17/2020.
//

#include "gtest/gtest.h"
#include "semsim/RelandAPIWrappers/LibrdfWorld.h"
#include "semsim/RelandAPIWrappers/LibrdfModel.h"

class LibrdfModelTests : public ::testing::Test {

public:

    LibrdfModelTests() = default;

};

TEST_F(LibrdfModelTests, Test) {
    you are herw
    semsim::LibrdfWorld world;
    int actual = world.getRefCount();
    int expected = 1;
    ASSERT_EQ(actual, expected);
}

TEST_F(LibrdfModelTests, TestCopyConstructor) {
    semsim::LibrdfWorld world1;
    semsim::LibrdfWorld world2 = world1;
    ASSERT_EQ(2, world1.getRefCount());
    ASSERT_EQ(2, world2.getRefCount());
    ASSERT_EQ(world1, world2);
}

TEST_F(LibrdfModelTests, TestCopyAssignment) {
    semsim::LibrdfWorld world1;
    semsim::LibrdfWorld world2;
    world2 = world1;
    ASSERT_EQ(2, world1.getRefCount());
    ASSERT_EQ(2, world2.getRefCount());
    ASSERT_EQ(world1, world2);
}


TEST_F(LibrdfModelTests, TestMoveConstructor) {
    semsim::LibrdfWorld world1;
    semsim::LibrdfWorld world2 = std::move(world1);
    ASSERT_EQ(1, world2.getRefCount());
    ASSERT_NE(world1, world2);
}

TEST_F(LibrdfModelTests, TestMoveAssignment) {
    semsim::LibrdfWorld world1;
    semsim::LibrdfWorld world2;
    world2 = std::move(world1);
    ASSERT_EQ(1, world2.getRefCount());
    ASSERT_NE(world1, world2);
}
