#include <cstdint>
#include "gtest/gtest.h"
#include "semsim/RedlandAPIWrappers/LibrdfWorld.h"

class LibrdfWorldTests : public ::testing::Test {

public:

    LibrdfWorldTests() = default;

};


TEST_F(LibrdfWorldTests, TestCopyConstructor) {
    semsim::LibrdfWorld world1;
    semsim::LibrdfWorld world2 = world1;
    ASSERT_EQ(world1, world2);
}

TEST_F(LibrdfWorldTests, TestCopyAssignment) {
    semsim::LibrdfWorld world1;
    semsim::LibrdfWorld world2;
    world2 = world1;
    ASSERT_EQ(world1, world2);
}


TEST_F(LibrdfWorldTests, TestMoveConstructor) {
    semsim::LibrdfWorld world1;
    semsim::LibrdfWorld world2 = std::move(world1);
    ASSERT_EQ(world1.getWorld(), nullptr);
}

TEST_F(LibrdfWorldTests, TestMoveAssignment) {
    semsim::LibrdfWorld world1;
    auto world1_ptr_number = reinterpret_cast<std::uintptr_t>(world1.get());
    semsim::LibrdfWorld world2;
    world2 = std::move(world1);
    auto world2_ptr_number = reinterpret_cast<std::uintptr_t>(world2.get());
    ASSERT_EQ(world1.getWorld(), nullptr);
    ASSERT_EQ(world1_ptr_number, world2_ptr_number);
}


TEST_F(LibrdfWorldTests, TestThatICanDoSomethingWithLibrdfWorld) {
    semsim::LibrdfWorld world1;
    librdf_storage *storage = librdf_new_storage(world1.get(), "memory", "storagename", nullptr);
    librdf_free_storage(storage);
    ASSERT_TRUE(true); // if we get this far we've passed
}








































