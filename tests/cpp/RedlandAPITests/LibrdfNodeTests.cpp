//
// Created by Ciaran on 5/17/2020.
//
#include "gtest/gtest.h"
#include "semsim/RelandAPIWrappers/LibrdfWorld.h"


class LibrdfNodeTests : public ::testing::Test {

public:

    LibrdfNodeTests() = default;

};


TEST_F(LibrdfNodeTests, TestCopyCreate) {
    semsim::LibrdfWorld librdfWorld;
    std::string expected = "https://notarealaddress.com";
    semsim::LibrdfNode node = librdfWorld.newNodeUriString(expected);
    std::string actual = node.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(LibrdfNodeTests, TestCopyConstructor) {
    semsim::LibrdfWorld librdfWorld;
    std::string expected1 = "https://notarealaddress1.com";
    semsim::LibrdfNode node1 = librdfWorld.newNodeUriString(expected1);
    semsim::LibrdfNode node2 = node1;
    std::string actual = node2.str();
    ASSERT_STREQ(expected1.c_str(), actual.c_str());
}


TEST_F(LibrdfNodeTests, TestMoveConstructor) {
    semsim::LibrdfWorld librdfWorld;
    std::string expected1 = "https://notarealaddress1.com";
    semsim::LibrdfNode node1 = librdfWorld.newNodeUriString(expected1);
    semsim::LibrdfNode node2 = std::move(node1);
    std::string actual = node2.str();
    ASSERT_STREQ(expected1.c_str(), actual.c_str());
}

TEST_F(LibrdfNodeTests, TestAssignmentOperator) {
    semsim::LibrdfWorld librdfWorld;
    std::string expected1 = "https://notarealaddress1.com";
    std::string expected2 = "https://notarealaddress2.com";
    semsim::LibrdfNode node1 = librdfWorld.newNodeUriString(expected1);
    semsim::LibrdfNode node2 = librdfWorld.newNodeUriString(expected2);
    node2 = node1;
    std::string actual = node2.str();
    ASSERT_STREQ(expected1.c_str(), actual.c_str());
}

/*
 * todo put the use_count check in librdfWorld and Raptororld
 */

TEST_F(LibrdfNodeTests, TestMoveAssignmentOperator) {
    semsim::LibrdfWorld librdfWorld;
    std::string expected1 = "https://notarealaddress1.com";
    std::string expected2 = "https://notarealaddress2.com";
    semsim::LibrdfNode node1 = librdfWorld.newNodeUriString(expected1);
    semsim::LibrdfNode node2 = librdfWorld.newNodeUriString(expected2);
    node1 = std::move(node2);
    std::string actual = node1.str();
    ASSERT_STREQ(expected2.c_str(), actual.c_str());
}

//TEST_F(LibrdfNodeTests, Test) {
//    semsim::LibrdfWorld world;
//    int actual = world.getRefCount();
//    int expected = 1;
//    ASSERT_EQ(actual, expected);
//}
//
//TEST_F(LibrdfNodeTests, TestCopyConstructor) {
//    semsim::LibrdfWorld world1;
//    semsim::LibrdfWorld world2 = world1;
//    ASSERT_EQ(2, world1.getRefCount());
//    ASSERT_EQ(2, world2.getRefCount());
//    ASSERT_EQ(world1, world2);
//}
//
//TEST_F(LibrdfNodeTests, TestCopyAssignment) {
//    semsim::LibrdfWorld world1;
//    semsim::LibrdfWorld world2;
//    world2 = world1;
//    ASSERT_EQ(2, world1.getRefCount());
//    ASSERT_EQ(2, world2.getRefCount());
//    ASSERT_EQ(world1, world2);
//}
//
//
//TEST_F(LibrdfNodeTests, TestMoveConstructor) {
//    semsim::LibrdfWorld world1;
//    semsim::LibrdfWorld world2 = std::move(world1);
//    ASSERT_EQ(1, world2.getRefCount());
//    ASSERT_NE(world1, world2);
//}
//
//TEST_F(LibrdfNodeTests, TestMoveAssignment) {
//    semsim::LibrdfWorld world1;
//    semsim::LibrdfWorld world2;
//    world2 = std::move(world1);
//    ASSERT_EQ(1, world2.getRefCount());
//    ASSERT_NE(world1, world2);
//}
