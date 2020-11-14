//
// Created by Ciaran on 4/14/2020.
//

#include "gtest/gtest.h"
#include "omexmeta/MetaID.h"

class MetaIDTests : public ::testing::Test {
public:

    MetaIDTests() {

    }
};

TEST_F(MetaIDTests, TestCountDigits1) {
    int actual = omexmeta::MetaID::countDigits(5032);
    int expected = 4;
    ASSERT_EQ(actual, expected);
}

TEST_F(MetaIDTests, TestCountDigits2) {
    long actual = omexmeta::MetaID::countDigits(50365363456);
    long expected = 11;
    ASSERT_EQ(actual, expected);
}

TEST_F(MetaIDTests, TestCountDigits3) {
    int actual = omexmeta::MetaID::countDigits(0);
    int expected = 1;
    ASSERT_EQ(actual, expected);
}

TEST_F(MetaIDTests, TestCountDigits4) {
    int actual = omexmeta::MetaID::countDigits(7);
    int expected = 1;
    ASSERT_EQ(actual, expected);
}

TEST_F(MetaIDTests, TestCountDigits5) {
    int actual = omexmeta::MetaID::countDigits(1);
    int expected = 1;
    ASSERT_EQ(actual, expected);
}


TEST_F(MetaIDTests, TestMaxNumber1) {
    omexmeta::MetaID metaId("metaId", 4, 3);
    int actual = metaId.maxNumber();
    int expected = 999;
    ASSERT_EQ(actual, expected);
}


TEST_F(MetaIDTests, TestMaxNumber2) {
    omexmeta::MetaID metaId("metaId", 4, 6);
    int actual = metaId.maxNumber();
    int expected = 999999;
    ASSERT_EQ(actual, expected);
}

TEST_F(MetaIDTests, TestMaxNumberFail) {
    ASSERT_THROW(omexmeta::MetaID
                         metaId("metaId", 106, 2), std::invalid_argument);
}

TEST_F(MetaIDTests, TestGenerate) {
    omexmeta::MetaID metaId("metaId", 4, 3);
    std::string actual = metaId.generate();
    std::string expected = "metaId004";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(MetaIDTests, TestGenerate5) {
    omexmeta::MetaID metaId("metaId", 4, 3);
    std::string actual = metaId.generate();
    std::string expected = "metaId004";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(MetaIDTests, TestGenerate2) {
    omexmeta::MetaID metaId("SemsimID", 1453, 6);
    std::string actual = metaId.generate();
    std::string expected = "SemsimID001453";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(MetaIDTests, TestGenerate3) {
    omexmeta::MetaID metaId("SemsimID", 1453, 6);
    std::string actual = metaId.generate(9);
    std::string expected = "SemsimID000009";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(MetaIDTests, TestGenerate4) {
    omexmeta::MetaID metaId("SemsimID", 0, 4);
    std::string actual = metaId.generate();
    std::string expected = "SemsimID0000";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(MetaIDTests, TestEquality1) {
    omexmeta::MetaID metaId1("SemsimID", 1453, 6);
    omexmeta::MetaID metaId2("SemsimID", 1453, 6);
    ASSERT_STREQ(metaId1.generate().c_str(), metaId2.generate().c_str());
}

TEST_F(MetaIDTests, TestInequality1) {
    omexmeta::MetaID metaId1("SemsimID", 55, 6);
    omexmeta::MetaID metaId2("SemsimID", 1453, 6);
    ASSERT_STRNE(metaId1.generate().c_str(), metaId2.generate().c_str());
}

TEST_F(MetaIDTests, AnotherTest) {
    omexmeta::MetaID metaId1("EntityProperty", 0, 4);
    std::string expected = "EntityProperty0000";
    std::string actual = metaId1.generate();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}













