//
// Created by Ciaran on 5/17/2020.
//

#include "gtest/gtest.h"
#include "semsim/RedlandAPIWrappers/LibrdfWorld.h"
#include "semsim/RedlandAPIWrappers/LibrdfModel.h"
#include "semsim/SemsimUtils.h"

class LibrdfModelTests : public ::testing::Test {

public:

    LibrdfModelTests() = default;

};

TEST_F(LibrdfModelTests, TestNew) {
    semsim::LibrdfWorld world;
    auto world_ptr_int = reinterpret_cast<std::uintptr_t>(world.get());
    semsim::LibrdfStorage storage1 = world.newStorage("memory", "semsim_store1");
    semsim::LibrdfModel model1 = world.newModel(storage1);
    ASSERT_TRUE(true);
}

TEST_F(LibrdfModelTests, TestCopyConstructor) {
    semsim::LibrdfWorld world;
    semsim::LibrdfStorage storage1 = world.newStorage("memory", "semsim_store1");
    semsim::LibrdfModel model1 = world.newModel(storage1);
    semsim::LibrdfModel model2 = model1;
    ASSERT_EQ(model1, model2);
}

TEST_F(LibrdfModelTests, TestCopyAssignment) {
    semsim::LibrdfWorld world;
    semsim::LibrdfStorage storage1 = world.newStorage("memory", "semsim_store1");
    semsim::LibrdfModel model1 = world.newModel(storage1);
    auto model1_ptr_int = reinterpret_cast<std::uintptr_t>(model1.get());
    semsim::LibrdfStorage storage2 = world.newStorage("memory", "semsim_store2");
    semsim::LibrdfModel model2 = world.newModel(storage2);
    auto model2_ptr_int_before = reinterpret_cast<std::uintptr_t>(model2.get());
    ASSERT_NE(model1_ptr_int, model2_ptr_int_before);
    model2 = model1;
    auto model2_ptr_int_after = reinterpret_cast<std::uintptr_t>(model2.get());
    ASSERT_EQ(model1_ptr_int, model2_ptr_int_after);
}


TEST_F(LibrdfModelTests, TestMoveConstructor) {
    semsim::LibrdfWorld world;
    semsim::LibrdfStorage storage1 = world.newStorage("memory", "semsim_store1");
    semsim::LibrdfModel model1 = world.newModel(storage1);
    auto model1_int_ptr = reinterpret_cast<std::uintptr_t>(model1.get());
    semsim::LibrdfModel model2 = std::move(model1);
    auto model2_int_ptr = reinterpret_cast<std::uintptr_t>(model2.get());
    ASSERT_EQ(model1_int_ptr, model2_int_ptr);
}

TEST_F(LibrdfModelTests, TestMoveAssignment) {
    semsim::LibrdfWorld world;
    // storage to model is 1:1
    semsim::LibrdfStorage storage1 = world.newStorage("memory", "semsim_store1");
    semsim::LibrdfStorage storage2 = world.newStorage("memory", "semsim_store2");
    semsim::LibrdfModel model1 = world.newModel(storage1);
    auto model1_int_ptr = reinterpret_cast<std::uintptr_t>(model1.get());
    semsim::LibrdfModel model2 = world.newModel(storage2);
    model2 = std::move(model1);
    auto model2_int_ptr = reinterpret_cast<std::uintptr_t>(model2.get());
    ASSERT_EQ(model1_int_ptr, model2_int_ptr);
}




