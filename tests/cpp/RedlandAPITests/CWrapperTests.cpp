//
// Created by Ciaran on 5/17/2020.
//

#include "gtest/gtest.h"

#include "semsim/RelandAPIWrappers/CWrapper.h"


TEST(CWapperTests, TestRefCount) {
    semsim::CWrapper wrapper = semsim::CWrapper();
    int actual = wrapper.getRefCount();
    int expected = 0;
    ASSERT_EQ(expected, actual);
}

TEST(CWapperTests, TestIncrementRefCount) {
    semsim::CWrapper wrapper = semsim::CWrapper();
    wrapper.increment_ref_count();
    int actual = wrapper.getRefCount();
    int expected = 1;
    ASSERT_EQ(expected, actual);
}

TEST(CWapperTests, TestDecrementRefCount) {
    semsim::CWrapper wrapper = semsim::CWrapper();
    wrapper.increment_ref_count();
    wrapper.increment_ref_count();
    wrapper.decrement_ref_count();
    int actual = wrapper.getRefCount();
    int expected = 1;
    ASSERT_EQ(expected, actual);
}

TEST(CWapperTests, TestFailOnNegative) {
    semsim::CWrapper wrapper = semsim::CWrapper();
    ASSERT_THROW(wrapper.decrement_ref_count(), std::logic_error);
}










