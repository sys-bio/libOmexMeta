//
// Created by Ciaran on 5/17/2020.
//

#include "gtest/gtest.h"
#include "semsim/RedlandAPIWrapper/World.h"
#include "semsim/RedlandAPIWrapper/LibrdfUri.h"
#include "semsim/SemsimUtils.h"

using namespace semsim;

class LibrdfUriTests : public ::testing::Test {

public:

    LibrdfUriTests() = default;

};

TEST_F(LibrdfUriTests, TestCreate) {
    LibrdfUri uri("http://uri.com");
    std::string expected = "http://uri.com";
    std::string actual = uri.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(LibrdfUriTests, TestGet) {
    LibrdfUri uri("http://uri.com");
    librdf_uri *curi = uri.get();
    std::string expected = "http://uri.com";
    auto cstr = (unsigned char *) librdf_uri_as_string(curi);
    ASSERT_STREQ(expected.c_str(), (const char *) cstr);
}

TEST_F(LibrdfUriTests, TestStr) {
    LibrdfUri uri("http://uri.com");
    std::string expected = "http://uri.com";
    std::string actual = uri.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(LibrdfUriTests, TestClone) {
//    LibrdfUri uri("http://uri.com");
//    LibrdfUri uri_clone = uri.clone();
//    std::cout << &uri << ", " << &uri_clone << std::endl;
//    std::cout << uri.get() << ", " << uri_clone.get() << std::endl;
    LibrdfUri uri1("http://uri.com");
    LibrdfUri uri2("http://uri.com");
    std::cout << &uri1 << ", " << &uri2 << std::endl;
    std::cout << uri1.get() << ", " << uri2.get() << std::endl;

//    ASSERT_STREQ( uri.str().c_str(),
//                  uri_clone.str().c_str());
//    ASSERT_NE(&uri, &uri_clone);
//    ASSERT_NE(uri.get(), uri_clone.get());
//    ASSERT_NE(&uri.get()->value.literal.string,
//              &uri_clone.get()->value.literal.string);
}


