//
// Created by Ciaran on 4/4/2020.
//

#include <semsim/Subject.h>
#include "gtest/gtest.h"

#include "World.h"

using namespace semsim;

class SubjectTests : public ::testing::Test {
public:
    SubjectTests() = default;

    ~SubjectTests() override = default;
};

TEST_F(SubjectTests, TestSubjectFromUri) {
    Subject subject = Subject::fromRawPtr(LibrdfNode::fromUriString("meta754"));
    std::string expected = subject.str();
    ASSERT_STREQ(expected.c_str(), "meta754");
}

TEST_F(SubjectTests, TestStringUri) {
    std::string url_str = "https://www.notarealaddress.com";
    Subject subject = Subject::fromRawPtr(LibrdfNode::fromUriString(url_str));
    const std::string &expected = subject.str();
    ASSERT_STREQ(url_str.c_str(), expected.c_str());
}

TEST_F(SubjectTests, TestGetNodeUri) {
    std::string url_str = "https://www.notarealaddress.com";
    Subject subject = Subject::fromRawPtr(LibrdfNode::fromUriString(url_str));
    ASSERT_STREQ(url_str.c_str(), subject.str().c_str());
}

TEST_F(SubjectTests, TestGetNodeBlank) {
    std::string string = "blank";
    Subject subject = Subject::fromRawPtr(LibrdfNode::fromUriString(string));
    ASSERT_STREQ(string.c_str(), subject.str().c_str());
}

TEST_F(SubjectTests, TestGetNodeAsConstRef) {
    std::string string = "blank";
    Subject subject = Subject::fromRawPtr(LibrdfNode::fromUriString("blank"));
    ASSERT_STREQ(string.c_str(), subject.str().c_str());
}

















