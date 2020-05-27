//
// Created by Ciaran on 5/17/2020.
//

#include "gtest/gtest.h"
#include "semsim/RedlandAPIWrapper/World.h"
#include "semsim/RedlandAPIWrapper/LibrdfUri.h"
#include "semsim/SemsimUtils.h"
#include "raptor2.h"

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

TEST_F(LibrdfUriTests, TestCopy) {
    /*
     * There is *no* copying of uri's because the constructor
     * will store a uri on creation. If the same string
     * used again for the uri, it is searched and returned.
     */
    librdf_uri *uri1 = librdf_new_uri(World::getWorld(), (const unsigned char *) "uri");
    librdf_uri *uri2 = librdf_new_uri(World::getWorld(), (const unsigned char *) "uri");
    librdf_uri *uri3 = librdf_new_uri_from_uri(uri1);

//    LibrdfUri uri1("http://uri.com");
//    ASSERT_STREQ(uri1.str().c_str(), uri2.str().c_str());

}