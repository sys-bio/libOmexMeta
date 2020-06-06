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
    Subject subject = Subject::fromRawPtr(LibrdfNode::fromUriString("meta754").get());
    std::string expected = subject.str();
    ASSERT_STREQ(expected.c_str(), "meta754");
    subject.free();
}

TEST_F(SubjectTests, TestStringUri) {
    std::string url_str = "https://www.notarealaddress.com";
    Subject subject = Subject::fromRawPtr(LibrdfNode::fromUriString(url_str).get());
    const std::string &expected = subject.str();
    ASSERT_STREQ(url_str.c_str(), expected.c_str());
    subject.free();
}

TEST_F(SubjectTests, TestGetNodeUri) {
    std::string url_str = "https://www.notarealaddress.com";
    Subject subject = Subject::fromRawPtr(LibrdfNode::fromUriString(url_str).get());
    ASSERT_STREQ(url_str.c_str(), subject.str().c_str());
    subject.free();
}

TEST_F(SubjectTests, TestGetNodeBlank) {
    std::string string = "blank";
    Subject subject = Subject::fromRawPtr(LibrdfNode::fromUriString(string).get());
    ASSERT_STREQ(string.c_str(), subject.str().c_str());
    subject.free();
}

TEST_F(SubjectTests, TestGetNodeAsConstRef) {
    std::string string = "blank";
    Subject subject = Subject::fromRawPtr(LibrdfNode::fromUriString("blank").get());
    ASSERT_STREQ(string.c_str(), subject.str().c_str());
    subject.free();
}

















