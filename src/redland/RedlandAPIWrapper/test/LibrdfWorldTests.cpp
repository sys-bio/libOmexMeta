#include "gtest/gtest.h"
#include "World.h"
#include <cstdint>

using namespace redland;

class LibrdfWorldTests : public ::testing::Test {

public:

    LibrdfWorldTests() = default;

};


//TEST_F(LibrdfWorldTests, TestSingleton) {
//    std::cout<< "jbiyb" << std::endl;
//}
TEST_F(LibrdfWorldTests, TestSingleton) {
    librdf_world *world1 = World::getWorld();
    librdf_world *world2 = World::getWorld();
    ASSERT_EQ(world1, world2);
}

//TEST_F(LibrdfWorldTests, TestFreeWorld) {
//    librdf_world *world1 = World::getWorld();
//    auto world1_int_ptr = reinterpret_cast<uintptr_t>(world1);
//    World::free(world1);
//    librdf_world *world2 = World::getWorld();
//    auto world2_int_ptr = reinterpret_cast<uintptr_t>(world2);
//    ASSERT_NE(world1_int_ptr, world2_int_ptr);
//}









































