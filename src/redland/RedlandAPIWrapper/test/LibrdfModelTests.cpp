//
// Created by Ciaran on 5/17/2020.
//

#include "gtest/gtest.h"
#include "redland/RedlandAPIWrapper/LibrdfModel.h"

using namespace semsim;

class LibrdfModelTests : public ::testing::Test {

public:
    LibrdfStorage storage1 = LibrdfStorage();
    LibrdfStorage storage2 = LibrdfStorage();

    LibrdfModelTests() = default;

};

TEST_F(LibrdfModelTests, TestNew) {
    LibrdfModel model1 = LibrdfModel(std::move(storage1));
    ASSERT_NE(model1.get(), nullptr);
}


TEST_F(LibrdfModelTests, TestMoveConstructor) {
    LibrdfModel model1 = LibrdfModel(std::move(storage1));
    auto model1_int_ptr = reinterpret_cast<std::uintptr_t>(model1.get());
    LibrdfModel model2 = std::move(model1);
    auto model2_int_ptr = reinterpret_cast<std::uintptr_t>(model2.get());
    ASSERT_EQ(model1_int_ptr, model2_int_ptr);
}

TEST_F(LibrdfModelTests, TestMoveAssignment) {
    LibrdfModel model1 = LibrdfModel(std::move(storage1));
    // get ptr as int to store for comparison later:
    auto model1_int_ptr = reinterpret_cast<std::uintptr_t>(model1.get());
    LibrdfModel model2 = LibrdfModel(std::move(storage2));
    model2 = std::move(model1);
    auto model2_int_ptr = reinterpret_cast<std::uintptr_t>(model2.get());
    ASSERT_EQ(model1_int_ptr, model2_int_ptr);
}




