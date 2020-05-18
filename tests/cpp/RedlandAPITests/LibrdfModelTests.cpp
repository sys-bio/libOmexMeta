//
// Created by Ciaran on 5/17/2020.
//

#include "gtest/gtest.h"
#include "semsim/RelandAPIWrappers/LibrdfWorld.h"
#include "semsim/RelandAPIWrappers/LibrdfModel.h"
#include "semsim/SemsimUtils.h"

class LibrdfModelTests : public ::testing::Test {

public:

    LibrdfModelTests() = default;

};

TEST_F(LibrdfModelTests, TestNew) {
    HERE();
    semsim::LibrdfWorld world;
    HERE();
    semsim::LibrdfStorage storage1 = world.newStorage("memory", "semsim_store1");
    HERE();
    semsim::LibrdfModel model1 = world.newModel(storage1);
}

TEST_F(LibrdfModelTests, TestCopyConstructor) {
    HERE();
    semsim::LibrdfWorld world;
    HERE();
    semsim::LibrdfStorage storage1 = world.newStorage("memory", "semsim_store1");
    HERE();
    semsim::LibrdfModel model1 = world.newModel(storage1);
    HERE();
    semsim::LibrdfStorage storage2 = storage1;
    HERE();
    ASSERT_EQ(storage1, storage2);
}

TEST_F(LibrdfModelTests, TestCopyAssignment) {
    semsim::LibrdfWorld world;
    semsim::LibrdfStorage storage1 = world.newStorage("memory", "semsim_store1");
    semsim::LibrdfStorage storage2 = world.newStorage("memory", "semsim_store2");
    storage2 = storage1;
    ASSERT_EQ(storage1, storage2);
    ASSERT_STREQ("semsim_store1", storage2.getName().c_str());
}


TEST_F(LibrdfModelTests, TestMoveConstructor) {
    semsim::LibrdfWorld world;
    semsim::LibrdfStorage storage1 = world.newStorage("memory", "semsim_store1");
    semsim::LibrdfStorage storage2 = std::move(storage1);
    ASSERT_NE(storage1, storage2);
}

TEST_F(LibrdfModelTests, TestMoveAssignment) {
    semsim::LibrdfWorld world;
    semsim::LibrdfStorage storage1 = world.newStorage("memory", "semsim_store1");
    semsim::LibrdfStorage storage2 = world.newStorage("memory", "semsim_store2");
    storage1 = std::move(storage2);
    ASSERT_NE(storage1, storage2);
}



