//
// Created by Ciaran on 5/17/2020.
//


#include <utility>

#include "gtest/gtest.h"
#include "semsim/RDF.h"
#include "semsim/SemSim.h"
#include "tests/cpp/AnnotationSamples.h"

# include "combine/combinearchive.h"
# include "combine/knownformats.h"
# include "combine/omexdescription.h"

#include "curl/curl.h"
#include "tests/cpp/SBMLFactory.h"
#include "semsim/RelandAPIWrappers/LibrdfWorld.h"

class LibrdfWorldTests : public ::testing::Test {

public:

    LibrdfWorldTests() = default;

};

TEST_F(LibrdfWorldTests, Test) {
    semsim::LibrdfWorld world;
    int actual = world.getRefCount();
    int expected = 1;
    ASSERT_EQ(actual, expected);
}

TEST_F(LibrdfWorldTests, TestCopyConstructor) {
    semsim::LibrdfWorld world1;
    semsim::LibrdfWorld world2 = world1;
    ASSERT_EQ(2, world1.getRefCount());
    ASSERT_EQ(2, world2.getRefCount());
}

TEST_F(LibrdfWorldTests, TestCopyAssignment) {
    semsim::LibrdfWorld world1;
    semsim::LibrdfWorld world2;
    world2 = world1;
    ASSERT_EQ(2, world1.getRefCount());
    ASSERT_EQ(2, world2.getRefCount());
}


TEST_F(LibrdfWorldTests, TestTwoDifferentWorlds) {
    semsim::LibrdfWorld world1;
    semsim::LibrdfWorld world2 = std::move(world1);


//    world2 = world1;
//    ASSERT_EQ(2, world1.getRefCount());
//    ASSERT_EQ(2, world2.getRefCount());
}







































