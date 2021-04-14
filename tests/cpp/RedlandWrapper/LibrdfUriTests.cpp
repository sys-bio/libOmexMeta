//
// Created by Ciaran on 5/17/2020.
//

#include "redland/LibrdfUri.h"
#include "redland/LibrdfNode.h"
#include "redland/World.h"
#include "gtest/gtest.h"
#include "raptor2.h"
#include <filesystem>

using namespace redland;

class LibrdfUriTests : public ::testing::Test {

public:
    LibrdfUriTests() = default;
};

TEST_F(LibrdfUriTests, TestCreate) {
    LibrdfUri uri("http://uri.com");
    ASSERT_EQ(1, uri.getUsage());
    std::string expected = "http://uri.com";
    std::string actual = uri.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(LibrdfUriTests, TestGet) {
    LibrdfUri uri("http://uri.com");
    ASSERT_EQ(1, uri.getUsage());

    /**
     * The .get() method increments uri usage count.
     * The destructor will decrement the usage count
     * but only once. So we must call free for every call to
     * uri.get()
     */
    librdf_uri *curi = uri.get();
    ASSERT_EQ(2, uri.getUsage());
    librdf_free_uri(curi);
    std::string expected = "http://uri.com";
    auto cstr = (unsigned char *) librdf_uri_as_string(curi);
    ASSERT_STREQ(expected.c_str(), (const char *) cstr);
}

TEST_F(LibrdfUriTests, TestStr) {
    LibrdfUri uri("http://uri.com");
    ASSERT_EQ(1, uri.getUsage());
    std::string expected = "http://uri.com";
    std::string actual = uri.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


#ifdef __linux__
TEST_F(LibrdfUriTests, TestFromFilenameLinux) {
    LibrdfUri uri = LibrdfUri::fromFilename("./local_filename");
    ASSERT_EQ(1, uri.getUsage());
    bool contains_file_prefix = false;
    bool contains_local_filename = false;
    if (uri.str().find("file://") != std::string::npos) {
        contains_file_prefix = true;
    }
    if (uri.str().find("local_filename") != std::string::npos) {
        contains_local_filename = true;
    }
    ASSERT_TRUE((contains_local_filename && contains_file_prefix));
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
}
#endif
TEST_F(LibrdfUriTests, TestConcatonate) {
    LibrdfUri uri = LibrdfUri("./local_filename");
    ASSERT_EQ(1, uri.getUsage());
    LibrdfUri uri2 = uri.concatonate("new_uri");
    ASSERT_EQ(1, uri2.getUsage());
    std::string expected = "./local_filenamenew_uri";
    std::string actual = uri2.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(LibrdfUriTests, TestIsFileUri) {
    LibrdfUri uri = LibrdfUri::fromFilename("./local_filename");
    ASSERT_TRUE(uri.isFileUri());
}

TEST_F(LibrdfUriTests, TestEqualityOperator) {
    LibrdfUri uri1 = LibrdfUri::fromFilename("./local_filename");
    ASSERT_EQ(1, uri1.getUsage());
    LibrdfUri uri2 = LibrdfUri::fromFilename("./local_filename");
    ASSERT_EQ(2, uri1.getUsage());
    ASSERT_EQ(2, uri2.getUsage());
    ASSERT_TRUE(uri1 == uri2);
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
    ASSERT_EQ(1, uri1.getUsage());
    LibrdfUri uri2 = LibrdfUri::fromFilename("./local_filename.rdf");
    ASSERT_EQ(2, uri1.getUsage());
    ASSERT_EQ(2, uri2.getUsage());
    ASSERT_EQ(uri1, uri2);
}

TEST_F(LibrdfUriTests, TestInequality) {
    LibrdfUri uri1 = LibrdfUri::fromFilename("./local_filename1.rdf");
    ASSERT_EQ(1, uri1.getUsage());
    LibrdfUri uri2 = LibrdfUri::fromFilename("./local_filename2.rdf");
    ASSERT_EQ(1, uri2.getUsage());
    ASSERT_NE(uri1, uri2);
}


TEST_F(LibrdfUriTests, TestUriTwiceWithMyConstructsWhenSameUri) {
    LibrdfUri uri1("https://uri.com");
    ASSERT_EQ(1, uri1.getUsage());
    LibrdfUri uri2("https://uri.com");
    ASSERT_EQ(2, uri2.getUsage());
}

TEST_F(LibrdfUriTests, TestUriInANode) {
    LibrdfUri uri("https://uri.com");
    ASSERT_EQ(1, uri.getUsage());
    LibrdfNode node(uri);

    // using the uri in the node increments its usage
    // but the new pointer is owned by the node so user
    // does not have to free
    ASSERT_EQ(2, uri.getUsage());
    ASSERT_EQ(1, node.getUsage());

    // uri2 owns the pointer that is generated (incremented)
    // by getUri
    LibrdfUri uri2 = node.getUri();
    ASSERT_EQ(3, uri.getUsage());
    ASSERT_STREQ(uri2.str().c_str(), uri.str().c_str());

    // destructors take care of the memory
}

TEST_F(LibrdfUriTests, TestUriInANode2) {
    LibrdfUri uri("https://uri.com");
    ASSERT_EQ(1, uri.getUsage());
    LibrdfNode node(uri);

    // using the uri in the node increments its usage
    // but the new pointer is owned by the node so user
    // does not have to free
    ASSERT_EQ(2, uri.getUsage());
    ASSERT_EQ(1, node.getUsage());

    // uri2 owns the pointer that is generated (incremented)
    // by getUri
    LibrdfUri uri2 = node.getUri();
    ASSERT_EQ(3, uri.getUsage());
    LibrdfUri uri3 = node.getUri();
    ASSERT_EQ(4, uri.getUsage());
    ASSERT_STREQ(uri3.str().c_str(), uri.str().c_str());

    // destructors take care of the memory
}

