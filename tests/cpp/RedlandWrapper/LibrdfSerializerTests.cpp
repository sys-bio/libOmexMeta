//
// Created by Ciaran on 5/17/2020.
//
#include "iostream"
#include "redland/LibrdfSerializer.h"
#include "redland/LibrdfWorld.h"
#include "gtest/gtest.h"

using namespace redland;

class LibrdfSerializerTests : public ::testing::Test {

public:
    LibrdfSerializerTests() = default;
};

TEST_F(LibrdfSerializerTests, TestInstantiateSerializer) {
    LibrdfSerializer serializer1 = LibrdfSerializer("rdfxml");
    ASSERT_NE(serializer1.get(), nullptr);
}

TEST_F(LibrdfSerializerTests, TestInstantiateWrongSerializerName) {
    ASSERT_THROW(LibrdfSerializer("rdfxmj"), std::invalid_argument);
}

TEST_F(LibrdfSerializerTests, TestMoveConstructor) {
    LibrdfSerializer serializer1 = LibrdfSerializer("rdfxml");
    auto serializer1_int_ptr = reinterpret_cast<std::uintptr_t>(serializer1.get());
    LibrdfSerializer serializer2 = std::move(serializer1);
    auto serializer2_int_ptr = reinterpret_cast<std::uintptr_t>(serializer2.get());
    ASSERT_EQ(serializer1.get(), nullptr);
    ASSERT_EQ(serializer1_int_ptr, serializer2_int_ptr);
}

TEST_F(LibrdfSerializerTests, TestMoveAssignment) {
    LibrdfSerializer serializer1 = LibrdfSerializer("rdfxml");
    auto serializer1_int_ptr = reinterpret_cast<std::uintptr_t>(serializer1.get());
    LibrdfSerializer serializer2 = LibrdfSerializer("rdfxml");
    auto serializer2_int_ptr = reinterpret_cast<std::uintptr_t>(serializer2.get());
    serializer1 = std::move(serializer2);
    ASSERT_NE(serializer1_int_ptr, serializer2_int_ptr);
    ASSERT_EQ(serializer2.get(), nullptr);
}


TEST_F(LibrdfSerializerTests, TestToString) {
    LibrdfStorage storage;
    LibrdfModel model(storage);
    LibrdfStatement statement = LibrdfStatement(
            LibrdfNode::fromUriString("https://subject.com"),
            LibrdfNode::fromUriString("https://predicate.com"),
            LibrdfNode::fromUriString("https://resource.com"));
    model.addStatement(statement);
    LibrdfSerializer serializer1 = LibrdfSerializer("rdfxml");
    //    LibrdfUri uri("base_uri");
    std::string actual = serializer1.toString("base_uri", model);
    std::string expected = "<?xml version=\"1.1\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n"
                           "  <rdf:Description rdf:about=\"https://subject.com\">\n"
                           "    <ns0:predicate.com xmlns:ns0=\"https://\" rdf:resource=\"https://resource.com\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}



TEST_F(LibrdfSerializerTests, SetNamespace) {
    LibrdfStorage storage;
    LibrdfModel model(storage);
    LibrdfSerializer serializer("rdfxml");
    serializer.setNamespace("https://namespace.com", "ns");

}


TEST_F(LibrdfSerializerTests, TestToStringTurtle) {
    LibrdfStorage storage;
    LibrdfModel model(storage);
    LibrdfStatement statement = LibrdfStatement(
            LibrdfNode::fromUriString("https://subject.com"),
            LibrdfNode::fromUriString("https://predicate.com"),
            LibrdfNode::fromUriString("https://resource.com"));
    model.addStatement(statement);
    LibrdfSerializer serializer1 = LibrdfSerializer("turtle");
    std::string actual = serializer1.toString("base_uri", model);
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "\n"
                           "<https://subject.com>\n"
                           "    <https://predicate.com> <https://resource.com> .\n\n";
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(LibrdfSerializerTests, TestToStringNTriples) {
    LibrdfStorage storage;
    LibrdfModel model(storage);
    LibrdfStatement statement = LibrdfStatement(
            LibrdfNode::fromUriString("https://subject.com"),
            LibrdfNode::fromUriString("https://predicate.com"),
            LibrdfNode::fromUriString("https://resource.com"));
    model.addStatement(statement);
    LibrdfSerializer serializer1 = LibrdfSerializer("ntriples");
    std::string actual = serializer1.toString("base_uri", model);
    std::string expected = "<https://subject.com> <https://predicate.com> <https://resource.com> .\n";
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(LibrdfSerializerTests, TestBaseUri) {
    LibrdfStorage storage;
    LibrdfModel model(storage);
    LibrdfStatement statement = LibrdfStatement(
            LibrdfNode::fromUriString("https://subject.com"),
            LibrdfNode::fromUriString("https://predicate.com"),
            LibrdfNode::fromUriString("https://resource.com"));
    model.addStatement(statement);
    LibrdfSerializer serializer1 = LibrdfSerializer("ntriples");
    std::string actual = serializer1.toString("base_uri", model);
    std::string expected = "<https://subject.com> <https://predicate.com> <https://resource.com> .\n";
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(LibrdfSerializerTests, TestFeatures) {
    LibrdfStorage storage;
    LibrdfModel model(storage);
    LibrdfStatement statement = LibrdfStatement(
            LibrdfNode::fromUriString("https://subject.com"),
            LibrdfNode::fromUriString("https://predicate.com"),
            LibrdfNode::fromUriString("https://resource.com"));
    model.addStatement(statement);
    LibrdfSerializer serializer("rdfxml-abbrev");

    serializer.setOption("relativeURIs", "0");
    LibrdfUri relativeURIsUri("http://feature.librdf.org/raptor-relativeURIs");
    LibrdfNode relativeURIsNode = LibrdfNode(
            librdf_serializer_get_feature(
                    serializer.get(), relativeURIsUri.getWithoutIncrement()));
    ASSERT_EQ("0", relativeURIsNode.str());

    serializer.setOption("writeBaseURI", "0");
    LibrdfUri writeBaseUriUri("http://feature.librdf.org/raptor-writeBaseURI");
    LibrdfNode writeBaseUriNode = LibrdfNode(
            librdf_serializer_get_feature(
                    serializer.get(), writeBaseUriUri.getWithoutIncrement()));
    ASSERT_EQ("0", writeBaseUriNode.str());
}
