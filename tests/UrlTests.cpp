#include <iostream>
#include <iterator>
#include <ctime>
#include <cassert>
#include <sstream>
#include "url.hpp"
#include "gtest/gtest.h"

using namespace std;

class UrlTests : public ::testing::Test {
public:
    std::string url_str1;
    std::string url_str2;
    std::string url_str3;
    std::string url_str4;
    std::string url_str5;
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
    const std::string& actual = u1.host();
    std::string expected = "www.example.com";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(UrlTests, TestHost2) {
    Url u3(url_str3);
    const std::string& actual = u3.host();
    std::string expected = "192.168.1.102";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(UrlTests, TestPath) {
    Url u2(url_str2);
    const std::string& actual = u2.path();
    std::string expected = "/sys-bio/sbnw/blob/master/CMakeLists.txt";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(UrlTests, TestPath2) {
    Url u3(url_str3);
    const std::string& actual = u3.path();
    std::string expected;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(UrlTests, TestPort) {
    Url u1(url_str2);
    std::string actual = u1.port();
    std::string expected;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(UrlTests, TestQuery) {
    Url u4(url_str4);
    auto actual = u4.query();
    std::ostringstream ss;
    for (const auto& it : actual){
        ss << it.key() << ": " << it.val();
    }
    std::string expected = "myparam1: id1myparam2: id2";
    ASSERT_STREQ(expected.c_str(), ss.str().c_str());
}

TEST_F(UrlTests, TestFragment) {
    Url u5(url_str5);
    const std::string& actual = u5.fragment();
    std::string expected = "ffff&amp;shape=circle";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}
TEST_F(UrlTests, TestScheme) {
    Url u5(url_str5);
    const std::string& actual = u5.scheme();
    std::string expected = "http";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


