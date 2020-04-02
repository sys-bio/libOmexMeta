


#include "gtest/gtest.h"
#include "semsim/Resource.h"

using namespace semsim;
using namespace std;


class ResourceTest : public ::testing::Test {
public:
    std::string url_str1;

    void SetUp() override {
        url_str1 = "http://www.example.com/";
    }

};

TEST_F(ResourceTest, TestConstructFromString){
    Resource resource(url_str1);
    ASSERT_STREQ(resource.url_.str().c_str(), url_str1.c_str());
}

TEST_F(ResourceTest, TestConstructFromUrl){
    Url url(url_str1);
    Resource resource(url);
    ASSERT_STREQ(resource.url_.str().c_str(), url_str1.c_str());
}

// todo workout how to use google mock to make a Component












































