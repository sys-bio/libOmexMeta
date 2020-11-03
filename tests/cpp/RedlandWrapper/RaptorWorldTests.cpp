#include "gtest/gtest.h"
#include "redland/SemsimUtils.h"
#include "RaptorWorld.h"
#include "World.h"

class RaptorWorldTests : public ::testing::Test {

public:

    RaptorWorldTests() = default;

};
//
//TEST_F(RaptorWorldTests, TestCopyConstructor) {
//    redland::LibrdfWorld librdfWorld;
//    redland::RaptorWorld raptorWorld1 = librdfWorld.getRaptor();
//    redland::RaptorWorld raptorWorld2 = raptorWorld1;
//    ASSERT_EQ(raptorWorld1, raptorWorld2);
//}
//
//TEST_F(RaptorWorldTests, TestMoveConstructor) {
//    redland::LibrdfWorld librdfWorld;
//    redland::RaptorWorld raptorWorld1 = librdfWorld.getRaptor();
//    redland::RaptorWorld raptorWorld2 = std::move(raptorWorld1);
//    ASSERT_NE(raptorWorld1, raptorWorld2);
//}
//
//TEST_F(RaptorWorldTests, TestCopyAssignment) {
//    redland::LibrdfWorld librdfWorld;
//    redland::RaptorWorld raptorWorld1 = librdfWorld.getRaptor();
//    redland::RaptorWorld raptorWorld2 = librdfWorld.getRaptor();
//    raptorWorld2 = raptorWorld1;
//    ASSERT_EQ(raptorWorld1.getRaptorWorld(), raptorWorld2.getRaptorWorld());
//    ASSERT_EQ(raptorWorld1, raptorWorld2);
//}
//
//TEST_F(RaptorWorldTests, TestMoveAssignment) {
//    redland::LibrdfWorld librdfWorld;
//    redland::RaptorWorld raptorWorld1 = librdfWorld.getRaptor();
//    redland::RaptorWorld raptorWorld2 = librdfWorld.getRaptor();
//    raptorWorld2 = std::move(raptorWorld1);
//    ASSERT_NE(raptorWorld1, raptorWorld2);
//}



