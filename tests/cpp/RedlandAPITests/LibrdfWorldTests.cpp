#include <cstdint>
#include "gtest/gtest.h"
#include "semsim/RedlandAPIWrapper/World.h"

using namespace semsim;

class LibrdfWorldTests : public ::testing::Test {

public:

    LibrdfWorldTests() = default;

};


TEST_F(LibrdfWorldTests, TestSingleton) {
    librdf_world *world1 = World::getWorld();
    librdf_world *world2 = World::getWorld();
    ASSERT_EQ(world1, world2);
}









































