//
// Created by Ciaran on 5/17/2020.
//
#include "gtest/gtest.h"
#include "semsim/RelandAPIWrappers/LibrdfWorld.h"
#include "semsim/RelandAPIWrappers/LibrdfStorage.h"


class LibrdfStorageTests : public ::testing::Test {

public:

    LibrdfStorageTests() = default;

};

TEST_F(LibrdfStorageTests, Test) {
    semsim::LibrdfWorld world;
    semsim::LibrdfStorage storage = world.newStorage("memory", "semsim_store");
    int actual = storage.getRefCount();
    int expected = 1;
    ASSERT_EQ(actual, expected);
}

TEST_F(LibrdfStorageTests, TestCopyConstructor) {
    semsim::LibrdfWorld world;
    semsim::LibrdfStorage storage1 = world.newStorage("memory", "semsim_store1");
    semsim::LibrdfStorage storage2 = storage1;
    ASSERT_EQ(2, storage1.getRefCount());
    ASSERT_EQ(2, storage2.getRefCount());
    ASSERT_EQ(storage1, storage2);
}

TEST_F(LibrdfStorageTests, TestCopyAssignment) {
    semsim::LibrdfWorld world;
    semsim::LibrdfStorage storage1 = world.newStorage("memory", "semsim_store1");
    semsim::LibrdfStorage storage2 = world.newStorage("memory", "semsim_store2");
    storage2 = storage1;
    ASSERT_EQ(2, storage1.getRefCount());
    ASSERT_EQ(2, storage2.getRefCount());
    ASSERT_EQ(storage1, storage2);
    ASSERT_STREQ("semsim_store1", storage2.getName().c_str());
}


TEST_F(LibrdfStorageTests, TestMoveConstructor) {
    semsim::LibrdfWorld world;
    semsim::LibrdfStorage storage1 = world.newStorage("memory", "semsim_store1");
    semsim::LibrdfStorage storage2 = std::move(storage1);
    ASSERT_EQ(1, storage2.getRefCount());
    ASSERT_NE(storage1, storage2);
}

TEST_F(LibrdfStorageTests, TestMoveAssignment) {
    semsim::LibrdfWorld world;
    semsim::LibrdfStorage storage1 = world.newStorage("memory", "semsim_store1");
    semsim::LibrdfStorage storage2 = world.newStorage("memory", "semsim_store2");
    storage1 = std::move(storage2);
    ASSERT_EQ(1, storage2.getRefCount());
    ASSERT_NE(storage1, storage2);
}















