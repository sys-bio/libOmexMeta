//
// Created by Ciaran on 5/17/2020.
//
#include "gtest/gtest.h"
#include "World.h"
#include "LibrdfStorage.h"
#include "iostream"

using namespace semsim;

class LibrdfStorageTests : public ::testing::Test {

public:

    LibrdfStorageTests() = default;

};

TEST_F(LibrdfStorageTests, TestInstantiateStorage) {
    semsim::LibrdfStorage storage1 = LibrdfStorage("memory", "Storage1");
    ASSERT_NE(storage1.get(), nullptr);
}

//TEST_F(LibrdfStorageTests, TestCopyConstructor) {
//
//    semsim::LibrdfStorage storage1 = LibrdfStorage("memory", "semsim_store1");
//    semsim::LibrdfStorage storage2 = storage1;
//    ASSERT_EQ(storage1, storage2);
//}

//TEST_F(LibrdfStorageTests, TestCopyAssignment) {
//
//    semsim::LibrdfStorage storage1 = LibrdfStorage("memory", "semsim_store1");
//    semsim::LibrdfStorage storage2 = LibrdfStorage("memory", "semsim_store2");
//    storage2 = storage1;
//    ASSERT_EQ(storage1, storage2);
//}


TEST_F(LibrdfStorageTests, TestMoveConstructor) {

    semsim::LibrdfStorage storage1 = LibrdfStorage();
    // get ptr as int before we move it to compare with storage 2
    auto storage1_int_ptr = reinterpret_cast<std::uintptr_t>(storage1.get());
    semsim::LibrdfStorage storage2 = std::move(storage1);
    auto storage2_int_ptr = reinterpret_cast<std::uintptr_t>(storage2.get());
    ASSERT_EQ(storage1_int_ptr, storage2_int_ptr);
}

TEST_F(LibrdfStorageTests, TestMoveAssignment) {

    semsim::LibrdfStorage storage1 = LibrdfStorage();
    auto storage1_int_ptr = reinterpret_cast<std::uintptr_t>(storage1.get());
    semsim::LibrdfStorage storage2 = LibrdfStorage();
    auto storage2_int_ptr = reinterpret_cast<std::uintptr_t>(storage2.get());
    storage1 = std::move(storage2);
    ASSERT_NE(storage1_int_ptr, storage2_int_ptr);
}















