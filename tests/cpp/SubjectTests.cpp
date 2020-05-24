//
// Created by Ciaran on 4/4/2020.
//

#include <semsim/Subject.h>
#include "gtest/gtest.h"

#include "semsim/RedlandAPIWrapper/World.h"

using namespace semsim;

class SubjectTests : public ::testing::Test {
public:
    SubjectTests() = default;

    ~SubjectTests() override = default;
};

TEST_F(SubjectTests, TestDefaultConstructor) {
    Subject subject;
    ASSERT_TRUE(true); // if you get this far the test passes
}

TEST_F(SubjectTests, TestSubjectFromUri) {
    Subject subject(LibrdfNode::fromUriString("meta754"));
    std::string expected = subject.str();
    ASSERT_STREQ(expected.c_str(), "meta754");
}

TEST_F(SubjectTests, TestStringUri) {
    std::string url_str = "https://www.notarealaddress.com";
    Subject subject(LibrdfNode::fromUriString(url_str));
    const std::string &expected = subject.str();
    ASSERT_STREQ(url_str.c_str(), expected.c_str());
}

TEST_F(SubjectTests, TestGetNodeUri) {
    std::string url_str = "https://www.notarealaddress.com";
    Subject subject(LibrdfNode::fromUriString(url_str));
    ASSERT_STREQ(url_str.c_str(), subject.getNode().str().c_str());
}

TEST_F(SubjectTests, TestGetNodeBlank) {
    std::string string = "blank";
    Subject subject(LibrdfNode::fromUriString(string));
    ASSERT_STREQ(string.c_str(), subject.getNode().str().c_str());
}

















