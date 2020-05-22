//
// Created by Ciaran on 5/17/2020.
//
#include "gtest/gtest.h"
#include "semsim/RedlandAPIWrappers/LibrdfWorld.h"
#include "semsim/RedlandAPIWrappers/LibrdfParser.h"
#include "iostream"

class LibrdfParserTests : public ::testing::Test {

public:

    LibrdfParserTests() = default;

};

TEST_F(LibrdfParserTests, TestInstantiateParser) {
    semsim::LibrdfWorld world;
    semsim::LibrdfParser parser1 = world.newParser("rdfxml");
    ASSERT_NE(parser1.get(), nullptr);
}

TEST_F(LibrdfParserTests, TestCopyConstructor) {
    semsim::LibrdfWorld world;
    semsim::LibrdfParser parser1 = world.newParser("rdfxml");
    semsim::LibrdfParser parser2 = parser1;
    ASSERT_EQ(parser1, parser2);
}

TEST_F(LibrdfParserTests, TestCopyAssignment) {
    semsim::LibrdfWorld world;
    semsim::LibrdfParser parser1 = world.newParser("rdfxml");
    semsim::LibrdfParser parser2 = world.newParser("rdfxml");
    parser2 = parser1;
    ASSERT_EQ(parser1, parser2);
}


TEST_F(LibrdfParserTests, TestMoveConstructor) {
    semsim::LibrdfWorld world;
    semsim::LibrdfParser parser1 = world.newParser("rdfxml");
    auto parser1_int_ptr = reinterpret_cast<std::uintptr_t>(parser1.get());
    semsim::LibrdfParser parser2 = std::move(parser1);
    auto parser2_int_ptr = reinterpret_cast<std::uintptr_t>(parser2.get());
    ASSERT_EQ(parser1.getParser(), nullptr);
    ASSERT_EQ(parser1_int_ptr, parser2_int_ptr);
}

TEST_F(LibrdfParserTests, TestMoveAssignment) {
    semsim::LibrdfWorld world;
    semsim::LibrdfParser parser1 = world.newParser("rdfxml");
    auto parser1_int_ptr = reinterpret_cast<std::uintptr_t>(parser1.get());
    semsim::LibrdfParser parser2 = world.newParser("rdfxml");
    auto parser2_int_ptr = reinterpret_cast<std::uintptr_t>(parser2.get());
    parser1 = std::move(parser2);
    ASSERT_NE(parser1_int_ptr, parser2_int_ptr);
    ASSERT_EQ(parser2.getParser(), nullptr);
}















