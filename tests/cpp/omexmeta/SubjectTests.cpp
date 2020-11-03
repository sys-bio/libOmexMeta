//
// Created by Ciaran on 4/4/2020.
//

#include "omexmeta/Subject.h"
#include "gtest/gtest.h"

using namespace omexmeta;

class SubjectTests : public ::testing::Test {
public:
    SubjectTests() = default;

    ~SubjectTests() override = default;
};

TEST_F(SubjectTests, TestSubjectFromUri) {
    Subject subject = Subject(LibrdfNode::fromUriString("meta754"));
    std::string expected = subject.str();
    ASSERT_STREQ(expected.c_str(), "meta754");
    subject.free();
}

TEST_F(SubjectTests, TestStringUri) {
    std::string url_str = "https://www.notarealaddress.com";
    Subject subject = Subject(LibrdfNode::fromUriString(url_str));
    const std::string &expected = subject.str();
    ASSERT_STREQ(url_str.c_str(), expected.c_str());
    subject.free();
}

TEST_F(SubjectTests, TestGetNodeUri) {
    std::string url_str = "https://www.notarealaddress.com";
    Subject subject = Subject(LibrdfNode::fromUriString(url_str));
    ASSERT_STREQ(url_str.c_str(), subject.str().c_str());
    subject.free();
}

TEST_F(SubjectTests, TestGetNodeBlank) {
    std::string string = "blank";
    Subject subject = Subject(LibrdfNode::fromUriString(string));
    ASSERT_STREQ(string.c_str(), subject.str().c_str());
    subject.free();
}

TEST_F(SubjectTests, TestGetNodeAsConstRef) {
    std::string string = "blank";
    Subject subject = Subject(LibrdfNode::fromUriString("blank"));
    ASSERT_STREQ(string.c_str(), subject.str().c_str());
    subject.free();
}

TEST_F(SubjectTests, TestEquality) {
    Subject subject1 = Subject(LibrdfNode::fromUriString("blank"));
    Subject subject2 = Subject(LibrdfNode::fromUriString("blank"));
    ASSERT_EQ(subject1, subject2);
    subject2.free();
    subject1.free();
}

TEST_F(SubjectTests, TestInequality) {
    Subject subject1 = Subject(LibrdfNode::fromUriString("blank1"));
    Subject subject2 = Subject(LibrdfNode::fromUriString("blank2"));
    ASSERT_NE(subject1, subject2);
    subject2.free();
    subject1.free();
}

















