//
// Created by Ciaran on 4/4/2020.
//

#include <semsim/Subject.h>
#include "gtest/gtest.h"


class SubjectTests : public ::testing::Test {
public:

    std::string uri_str1;
    semsim::Uri uri;

    void SetUp() override {
        uri_str1 = "http://www.example.com/";
        uri = semsim::Uri(uri_str1);
    }
};

TEST_F(SubjectTests, TestGetMetaId) {
    semsim::Subject subject("x");
    std::string expected = subject.getMetaId();
    ASSERT_STREQ(expected.c_str(), "x");
}

TEST_F(SubjectTests, TestStringUri) {
    std::string url_str = "www.notarealaddress.com";
    semsim::Subject subject(url_str);
    const std::string& expected = subject.getMetaId();
    ASSERT_STREQ(url_str.c_str(), expected.c_str());
}

TEST_F(SubjectTests, TestGetUri) {
    semsim::Subject subject(uri_str1);
    std::string expected = subject.getMetaId();
    ASSERT_STREQ(expected.c_str(), uri_str1.c_str());
}

TEST_F(SubjectTests, TestEqualityOperator) {
    semsim::Subject subject1(uri_str1);
    semsim::Subject subject2(uri_str1);
    ASSERT_EQ(subject1, subject2);
}

TEST_F(SubjectTests, TestInequalityOperator) {
    semsim::Subject subject1(uri_str1 + "x");
    semsim::Subject subject2(uri_str1);
    ASSERT_NE(subject1, subject2);
}

TEST_F(SubjectTests, TestStreamOperator) {
    semsim::Subject subject1(uri_str1);
    std::ostringstream os;
    os << subject1;
    std::string expected = "Subject(metaId=http://www.example.com/)";
    ASSERT_STREQ(expected.c_str(), os.str().c_str());
}














