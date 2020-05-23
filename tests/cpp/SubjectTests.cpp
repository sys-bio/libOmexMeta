//
// Created by Ciaran on 4/4/2020.
//

#include <semsim/Subject.h>
#include "gtest/gtest.h"

#include "semsim/RedlandAPIWrapper/LibrdfWorld.h"


class SubjectTests : public ::testing::Test {
public:
    semsim::LibrdfWorld world_;

    SubjectTests() {

    }

    ~SubjectTests() override {
    }
};

TEST_F(SubjectTests, TestDefaultConstructor) {
    semsim::Subject subject;
    ASSERT_TRUE(true); // if you get this far the test passes
}

TEST_F(SubjectTests, TestSubjectFromUri) {
    semsim::Subject subject(world_, semsim::RDFURINode(world_.newNodeUriString("meta754")));
    std::string expected = subject.str();
    ASSERT_STREQ(expected.c_str(), "meta754");
}

TEST_F(SubjectTests, TestStringUri) {
    std::string url_str = "https://www.notarealaddress.com";
    semsim::Subject subject(world_, semsim::RDFURINode(world_.newNodeUriString(url_str)));
    const std::string &expected = subject.str();
    ASSERT_STREQ(url_str.c_str(), expected.c_str());
}

TEST_F(SubjectTests, TestGetNodeUri) {
    std::string url_str = "https://www.notarealaddress.com";
    semsim::Subject subject(world_, semsim::RDFURINode(world_.newNodeUriString(url_str)));
    semsim::LibrdfNode n = subject.getNode();
    std::string actual = n.str();
    ASSERT_STREQ(url_str.c_str(), actual.c_str());
}

TEST_F(SubjectTests, TestGetNodeBlank) {
    std::string string = "blank";
    semsim::Subject subject(world_, semsim::RDFURINode(world_.newNodeUriString(string)));
    semsim::LibrdfNode n = subject.getNode();
    std::string actual = n.str();
    ASSERT_STREQ(string.c_str(), actual.c_str());
}

















