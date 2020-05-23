//
// Created by Ciaran on 5/17/2020.
//
#include "gtest/gtest.h"
#include "semsim/RedlandAPIWrapper/World.h"
#include "semsim/RedlandAPIWrapper/LibrdfSerializer.h"
#include "iostream"

using namespace semsim;

class LibrdfSerializerTests : public ::testing::Test {

public:

    LibrdfSerializerTests() = default;

};

TEST_F(LibrdfSerializerTests, TestInstantiateSerializer) {
    LibrdfSerializer serializer1 = LibrdfSerializer("rdfxml");
    ASSERT_NE(serializer1.get(), nullptr);
}


TEST_F(LibrdfSerializerTests, TestMoveConstructor) {
    LibrdfSerializer serializer1 = LibrdfSerializer("rdfxml");
    auto serializer1_int_ptr = reinterpret_cast<std::uintptr_t>(serializer1.get());
    LibrdfSerializer serializer2 = std::move(serializer1);
    auto serializer2_int_ptr = reinterpret_cast<std::uintptr_t>(serializer2.get());
    ASSERT_EQ(serializer1.get(), nullptr);
    ASSERT_EQ(serializer1_int_ptr, serializer2_int_ptr);
}

TEST_F(LibrdfSerializerTests, TestMoveAssignment) {
    LibrdfSerializer serializer1 = LibrdfSerializer("rdfxml");
    auto serializer1_int_ptr = reinterpret_cast<std::uintptr_t>(serializer1.get());
    LibrdfSerializer serializer2 = LibrdfSerializer("rdfxml");
    auto serializer2_int_ptr = reinterpret_cast<std::uintptr_t>(serializer2.get());
    serializer1 = std::move(serializer2);
    ASSERT_NE(serializer1_int_ptr, serializer2_int_ptr);
    ASSERT_EQ(serializer2.get(), nullptr);
}















