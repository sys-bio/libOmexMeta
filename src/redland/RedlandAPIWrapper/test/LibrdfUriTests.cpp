//
// Created by Ciaran on 5/17/2020.
//

#include "gtest/gtest.h"
#include "World.h"
#include "LibrdfUri.h"
//#include "redland/SemsimUtils.h"
#include "raptor2.h"
#include <filesystem>

using namespace redland;

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

TEST_F(LibrdfUriTests, TestIsNullFalse) {
    LibrdfUri uri("http://uri.com");
    ASSERT_FALSE(uri.isNull());
}

TEST_F(LibrdfUriTests, TestIsNull) {
    LibrdfUri uri{};
    ASSERT_TRUE(uri.isNull());
}

TEST_F(LibrdfUriTests, TestIsEmpty1) {
    LibrdfUri uri("");
    ASSERT_TRUE(uri.isNull());
}

TEST_F(LibrdfUriTests, TestIsEmpty2) {
    LibrdfUri uri((std::string()));
    ASSERT_TRUE(uri.isNull());
}

#ifdef __linux__
TEST_F(LibrdfUriTests, TestFromFilenameLinux) {
    LibrdfUri uri = LibrdfUri::fromFilename("./local_filename");
    bool contains_file_prefix = false;
    bool contains_local_filename = false;
    if (uri.str().find("file://") != std::string::npos) {
        contains_file_prefix = true;
    }
    if (uri.str().find("local_filename") != std::string::npos) {
        contains_local_filename = true;
    }
    ASSERT_TRUE((contains_local_filename && contains_file_prefix));
    uri.freeUri();
}
#endif
#ifdef WIN32
TEST_F(LibrdfUriTests, TestFromFilenameWithWindowsFormattedFile) {
    LibrdfUri uri = LibrdfUri::fromFilename("D:\\libOmexMeta\\tests\\cpp");
    std::cout << uri.str() << std::endl;
    bool contains_file_prefix = false;
    bool contains_local_filename = false;
    if (uri.str().find("file://") != std::string::npos) {
        contains_file_prefix = true;
    }
    if (uri.str().find("libOmexMeta/tests/cpp") != std::string::npos) {
        contains_local_filename = true;
    }
    ASSERT_TRUE((contains_local_filename && contains_file_prefix));
    uri.freeUri();
}
#endif
TEST_F(LibrdfUriTests, TestConcatonate) {
    LibrdfUri uri = LibrdfUri("./local_filename");
    LibrdfUri uri2 = uri.concatonate("new_uri");
    std::string expected = "./local_filenamenew_uri";
    std::string actual = uri2.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    uri.freeUri();
    uri2.freeUri();
}

TEST_F(LibrdfUriTests, TestIsFileUri) {
    LibrdfUri uri = LibrdfUri::fromFilename("./local_filename");
    ASSERT_TRUE(uri.isFileUri());
    uri.freeUri();
}

TEST_F(LibrdfUriTests, TestEqualityOperator) {
    LibrdfUri uri1 = LibrdfUri::fromFilename("./local_filename");
    LibrdfUri uri2 = LibrdfUri::fromFilename("./local_filename");
    ASSERT_TRUE(uri1 == uri2);
    uri1.freeUri();
    uri2.freeUri();
}


/*
 * Both uri's refer to the same block of memory.
 * librdf_uri has an internal ref counter that
 * increases when you create another uri with the
 * same string.
 * The uri is deleted when the ref count gets to 1 and free is called.
 */
TEST_F(LibrdfUriTests, TestEquality) {
    LibrdfUri uri1 = LibrdfUri::fromFilename("./local_filename.rdf");
    LibrdfUri uri2 = LibrdfUri::fromFilename("./local_filename.rdf");
    ASSERT_EQ(uri1, uri2);
    uri1.freeUri();
    uri2.freeUri();
}

TEST_F(LibrdfUriTests, TestInequality) {
    LibrdfUri uri1 = LibrdfUri::fromFilename("./local_filename1.rdf");
    LibrdfUri uri2 = LibrdfUri::fromFilename("./local_filename2.rdf");
    ASSERT_NE(uri1, uri2);
    uri1.freeUri();
    uri2.freeUri();
}

TEST_F(LibrdfUriTests, TestUriTwice) {
    LibrdfUri uri1 = LibrdfUri("https://uri.com");
    LibrdfUri uri2 = LibrdfUri("https://uri.com");

    ASSERT_EQ(2, uri1.getUsage());
    ASSERT_EQ(2, uri2.getUsage());

    uri1.freeUri();
    uri2.freeUri();
}




