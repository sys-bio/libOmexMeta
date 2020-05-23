//
// Created by Ciaran on 5/17/2020.
//
#include "gtest/gtest.h"
#include "semsim/RedlandAPIWrapper/LibrdfWorld.h"
#include "semsim/RedlandAPIWrapper/LibrdfStream.h"
#include "iostream"

class LibrdfStreamTests : public ::testing::Test {

public:

    LibrdfStreamTests() = default;


};

//TEST_F(LibrdfStreamTests, TestInstantiateStream) {
//    semsim::LibrdfWorld world;
//    semsim::LibrdfStream stream1 = world.newStream("memory", "semsim_store1");
//    librdf_new_stream()
//    ASSERT_NE(stream1.get(), nullptr);
//}

//TEST_F(LibrdfStreamTests, TestCopyConstructor) {
//    semsim::LibrdfWorld world;
//    semsim::LibrdfStream stream1 = world.newStream("memory", "semsim_store1");
//    semsim::LibrdfStream stream2 = stream1;
//    ASSERT_EQ(stream1, stream2);
//}
//
//TEST_F(LibrdfStreamTests, TestCopyAssignment) {
//    semsim::LibrdfWorld world;
//    semsim::LibrdfStream stream1 = world.newStream("memory", "semsim_store1");
//    semsim::LibrdfStream stream2 = world.newStream("memory", "semsim_store2");
//    stream2 = stream1;
//    ASSERT_EQ(stream1, stream2);
//}
//
//
//TEST_F(LibrdfStreamTests, TestMoveConstructor) {
//    semsim::LibrdfWorld world;
//    semsim::LibrdfStream stream1 = world.newStream("memory", "semsim_store1");
//    auto stream1_int_ptr = reinterpret_cast<std::uintptr_t>(stream1.get());
//    semsim::LibrdfStream stream2 = std::move(stream1);
//    auto stream2_int_ptr = reinterpret_cast<std::uintptr_t>(stream2.get());
//    ASSERT_EQ(stream1.getStream(), nullptr);
//    ASSERT_EQ(stream1_int_ptr, stream2_int_ptr);
//}
//
//TEST_F(LibrdfStreamTests, TestMoveAssignment) {
//    semsim::LibrdfWorld world;
//    semsim::LibrdfStream stream1 = world.newStream("memory", "semsim_store1");
//    auto stream1_int_ptr = reinterpret_cast<std::uintptr_t>(stream1.get());
//    semsim::LibrdfStream stream2 = world.newStream("memory", "semsim_store2");
//    auto stream2_int_ptr = reinterpret_cast<std::uintptr_t>(stream2.get());
//    stream1 = std::move(stream2);
//    ASSERT_NE(stream1_int_ptr, stream2_int_ptr);
//    ASSERT_EQ(stream2.getStream(), nullptr);
//}
//
//TEST_F(LibrdfStreamTests, TestStreamInAFunctionAsArgument) {
//    semsim::LibrdfWorld world;
//    semsim::LibrdfStream stream1 = world.newStream("memory", "semsim_store1");
//    int actual = function_that_takes_a_stream(world, stream1);
//    int expected = 0;
//    ASSERT_EQ(actual, expected);
//}
//














