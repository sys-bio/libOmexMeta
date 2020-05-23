//
// Created by Ciaran on 5/17/2020.
//
#include "gtest/gtest.h"
#include "semsim/RedlandAPIWrapper/LibrdfWorld.h"
#include "semsim/RedlandAPIWrapper/LibrdfSerializer.h"
#include "iostream"

class LibrdfSerializerTests : public ::testing::Test {

public:

    LibrdfSerializerTests() = default;

};

TEST_F(LibrdfSerializerTests, TestInstantiateSerializer) {
    semsim::LibrdfWorld world;
    semsim::LibrdfSerializer serializer1 = world.newSerializer("rdfxml");
    ASSERT_NE(serializer1.get(), nullptr);
}

TEST_F(LibrdfSerializerTests, TestCopyConstructor) {
    semsim::LibrdfWorld world;
    semsim::LibrdfSerializer serializer1 = world.newSerializer("rdfxml");
    semsim::LibrdfSerializer serializer2 = serializer1;
    ASSERT_EQ(serializer1, serializer2);
}

TEST_F(LibrdfSerializerTests, TestCopyAssignment) {
    semsim::LibrdfWorld world;
    semsim::LibrdfSerializer serializer1 = world.newSerializer("rdfxml");
    semsim::LibrdfSerializer serializer2 = world.newSerializer("rdfxml");
    serializer2 = serializer1;
    ASSERT_EQ(serializer1, serializer2);
}


TEST_F(LibrdfSerializerTests, TestMoveConstructor) {
    semsim::LibrdfWorld world;
    semsim::LibrdfSerializer serializer1 = world.newSerializer("rdfxml");
    auto serializer1_int_ptr = reinterpret_cast<std::uintptr_t>(serializer1.get());
    semsim::LibrdfSerializer serializer2 = std::move(serializer1);
    auto serializer2_int_ptr = reinterpret_cast<std::uintptr_t>(serializer2.get());
    ASSERT_EQ(serializer1.getSerializer(), nullptr);
    ASSERT_EQ(serializer1_int_ptr, serializer2_int_ptr);
}

TEST_F(LibrdfSerializerTests, TestMoveAssignment) {
    semsim::LibrdfWorld world;
    semsim::LibrdfSerializer serializer1 = world.newSerializer("rdfxml");
    auto serializer1_int_ptr = reinterpret_cast<std::uintptr_t>(serializer1.get());
    semsim::LibrdfSerializer serializer2 = world.newSerializer("rdfxml");
    auto serializer2_int_ptr = reinterpret_cast<std::uintptr_t>(serializer2.get());
    serializer1 = std::move(serializer2);
    ASSERT_NE(serializer1_int_ptr, serializer2_int_ptr);
    ASSERT_EQ(serializer2.getSerializer(), nullptr);
}















