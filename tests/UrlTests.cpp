#include <iostream>
#include <iterator>
#include <ctime>
#include <cassert>
#include <sstream>
#include "semsim/url.h"
#include "gtest/gtest.h"

using namespace std;
using namespace semsim;

class UrlTests : public ::testing::Test {
public:
    string url_str1;
    string url_str2;
    string url_str3;
    string url_str4;
    string url_str5;
    void SetUp() override {
        url_str1 = "http://www.example.com/";
        url_str2 = "https://github.com/sys-bio/sbnw/blob/master/CMakeLists.txt";
        url_str3 = "http://192.168.1.102:95";
        url_str4 = "www.yoursite.com?myparam1=id1&myparam2=id2";
        url_str5 = "http://example.com/?color=#ffff&amp;shape=circle";
    }

};

TEST_F(UrlTests, TestCopy) {
    Url u1;
    Url u2(url_str1);
    u1 = u2;
    ASSERT_STREQ(url_str1.c_str(), u1.str().c_str());
}

TEST_F(UrlTests, TestHost) {
    Url u1(url_str1);
    const string& actual = u1.host();
    string expected = "www.example.com";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(UrlTests, TestHost2) {
    Url u3(url_str3);
    const string& actual = u3.host();
    string expected = "192.168.1.102";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(UrlTests, TestPath) {
    Url u2(url_str2);
    const string& actual = u2.path();
    string expected = "/sys-bio/sbnw/blob/master/CMakeLists.txt";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(UrlTests, TestPath2) {
    Url u3(url_str3);
    const string& actual = u3.path();
    string expected;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(UrlTests, TestPort) {
    Url u1(url_str2);
    string actual = u1.port();
    string expected;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(UrlTests, TestQuery) {
    Url u4(url_str4);
    auto actual = u4.query();
    ostringstream ss;
    for (const auto& it : actual){
        ss << it.key() << ": " << it.val();
    }
    string expected = "myparam1: id1myparam2: id2";
    ASSERT_STREQ(expected.c_str(), ss.str().c_str());
}

TEST_F(UrlTests, TestFragment) {
    Url u5(url_str5);
    const string& actual = u5.fragment();
    string expected = "ffff&amp;shape=circle";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}
TEST_F(UrlTests, TestScheme) {
    Url u5(url_str5);
    const string& actual = u5.scheme();
    string expected = "http";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(UrlTests, TestEquality) {
    Url u1(url_str5);
    Url u2(url_str5);
    ASSERT_EQ(u1, u2);
}
TEST_F(UrlTests, TestInequality) {
    Url u1(url_str5);
    Url u2(url_str4);
    ASSERT_NE(u1, u2);
}


