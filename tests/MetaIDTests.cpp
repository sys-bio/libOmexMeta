//
// Created by Ciaran on 4/14/2020.
//

#include "gtest/gtest.h"
#include "semsim/MetaID.h"

class MetaIDTests : public ::testing::Test {
public:

    MetaIDTests() {

    }
};

TEST_F(MetaIDTests, TestCountDigits1) {
    int actual = semsim::MetaID::countDigits(5032);
    int expected = 4;
    ASSERT_EQ(actual, expected);
}

TEST_F(MetaIDTests, TestCountDigits2) {
    long actual = semsim::MetaID::countDigits(50365363456);
    long expected = 11;
    ASSERT_EQ(actual, expected);
}

TEST_F(MetaIDTests, TestMaxNumber1) {
    semsim::MetaID metaId("metaId", 4, 3);
    int actual = metaId.maxNumber();
    int expected = 999;
    ASSERT_EQ(actual, expected);
}


TEST_F(MetaIDTests, TestMaxNumber2) {
    semsim::MetaID metaId("metaId", 4, 6);
    int actual = metaId.maxNumber();
    int expected = 999999;
    ASSERT_EQ(actual, expected);
}

TEST_F(MetaIDTests, TestMaxNumberFail) {
    ASSERT_THROW(semsim::MetaID metaId("metaId", 106, 2), std::invalid_argument);
}

TEST_F(MetaIDTests, TestGenerate) {
    semsim::MetaID metaId("metaId", 4, 3);
    std::string actual = metaId.generate();
    std::string expected = "metaId004";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(MetaIDTests, TestGenerate2) {
    semsim::MetaID metaId("SemsimID", 1453, 6);
    std::string actual = metaId.generate();
    std::string expected = "SemsimID001453";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(MetaIDTests, TestEquality1) {
    semsim::MetaID metaId1("SemsimID", 1453, 6);
    semsim::MetaID metaId2("SemsimID", 1453, 6);
    ASSERT_STREQ(metaId1.generate().c_str(), metaId2.generate().c_str());
}


TEST_F(MetaIDTests, TestInequality1) {
    semsim::MetaID metaId1("SemsimID", 55, 6);
    semsim::MetaID metaId2("SemsimID", 1453, 6);
    ASSERT_STRNE(metaId1.generate().c_str(), metaId2.generate().c_str());
}













