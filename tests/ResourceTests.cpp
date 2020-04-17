//
// Created by Ciaran on 4/4/2020.
//

#include <semsim/Resource.h>
#include <semsim/uri.h>
#include "gtest/gtest.h"
#include "librdf.h"

class ResourceTests : public ::testing::Test {
public:

    std::string ns;
    std::string id;

    void SetUp() override {
        ns = "genecards";
        id = "ABL1";
    }
};

TEST_F(ResourceTests, TestResourceUri1) {
    semsim::URITerm term = semsim::URITerm("https://en.wikipedia.org/wiki/Adolf_Hitler");
    semsim::Resource resource(&term);
    std::string expected = "https://en.wikipedia.org/wiki/Adolf_Hitler";
    std::string actual = resource.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(ResourceTests, TestResourceUri2) {
    semsim::URITerm term = semsim::IdentifiersURITerm("fma/FMA:1234");
    semsim::Resource resource(&term);
    std::string expected = "https://identifiers.org/fma/FMA:1234";
    std::string actual = resource.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}
TEST_F(ResourceTests, TestResourceUri3) {
    librdf_new_node_from_literal;
    librdf_new_node_from_uri;
    librdf_new_node_from_blank_identifier;
    librdf_new_node_from_typed_literal;
    librdf_new_node_from_uri_string;
    librdf_new_node_from_uri_local_name;

//    semsim::URITerm term = semsim::IdentifiersURITerm("fma/FMA:1234");
//    semsim::Resource resource(&term);
//    std::string expected = "https://identifiers.org/fma/FMA:1234";
//    std::string actual = resource.str();
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
}
//TEST_F(ResourceTests, TestResourceUri3) {
//    semsim::Resource resource("fma:FMA:1234");
//    std::string expected = "https://identifiers.org/fma/FMA:1234";
//    std::string actual = resource.str();
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}
//
//TEST_F(ResourceTests, TestResourceUri4) {
//    semsim::Resource resource("/file/on/disk");
//    std::string expected = "/file/on/disk";
//    std::string actual = resource.str();
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}
//
//TEST_F(ResourceTests, TestResourceUri5) {
//    semsim::Resource resource("./relative/file/on/disk");
//    std::string expected = "./relative/file/on/disk";
//    std::string actual = resource.str();
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}
//

//TEST_F(ResourceTests, TestGetResourceNamespace) {
//    semsim::Resource resource(ns, id);
//    const std::string &expected = "genecards";
//    const std::string &ns2 = resource.getResourceNamespace();
//    ASSERT_STREQ(expected.c_str(), ns2.c_str());
//}
//
//TEST_F(ResourceTests, TestDefaultConstructor) {
//    semsim::Resource resource;
//    ASSERT_TRUE(true); // if the test gets this far its passed.
//}
//
//
//TEST_F(ResourceTests, TestGetUri) {
//    semsim::Resource resource(ns, id);
//    const std::string &expected = "ABL1";
//    const std::string &actual = resource.getIdentifier();
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}
//
//TEST_F(ResourceTests, TestEqualityOperator) {
//    semsim::Resource resource1(ns, id);
//    semsim::Resource resource2(ns, id);
//    ASSERT_EQ(resource1, resource2);
//}
//
//TEST_F(ResourceTests, TestInequalityOperator) {
//    semsim::Resource resource1(ns, id);
//    semsim::Resource resource2(ns, "cheese");
//    ASSERT_NE(resource1, resource2);
//}
//
//TEST_F(ResourceTests, TestStreamOperator) {
//    semsim::Resource resource1(ns, id);
//    std::ostringstream os;
//    os << resource1;
//    std::string expected = "Resource(https://identifiers.org/genecards/ABL1)";
//    ASSERT_STREQ(expected.c_str(), os.str().c_str());
//}
//
//
//TEST_F(ResourceTests, TestStringSpliter1) {
//    std::vector<std::string> expected = {"cheese"};
//    std::vector<std::string> actual = semsim::Resource::splitStringBy("cheese", ':');
//    ASSERT_EQ(expected, actual);
//}
//
//TEST_F(ResourceTests, TestStringSpliter2) {
//    std::vector<std::string> expected = {"cheese", "biscuits"};
//    std::vector<std::string> actual = semsim::Resource::splitStringBy("cheese:biscuits", ':');
//    ASSERT_EQ(expected, actual);
//}
//
//
//TEST_F(ResourceTests, TestFromString1) {
//    semsim::Resource resource1("genecards/ABL1");
//    const std::string &actual = resource1.getResourceNamespace();
//    std::string expected = "genecards";
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}
//
//TEST_F(ResourceTests, TestFromString2) {
//    semsim::Resource resource1("genecards:ABL1");
//    const std::string &actual = resource1.getResourceNamespace();
//    std::string expected = "genecards";
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}
//
//TEST_F(ResourceTests, TestFromString3) {
//    ASSERT_THROW(semsim::Resource resource1("https://google.org/uniprot/P0DP23"), std::invalid_argument);
//}
//
//TEST_F(ResourceTests, TestFromString4) {
//    semsim::Resource resource1("https://identifiers.org/uniprot/P0DP23");
//    const std::string &actual = resource1.getIdentifier();
//    std::string expected = "P0DP23";
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}
//
//TEST_F(ResourceTests, Teststr) {
//    semsim::Resource resource1("genecards:ABL1");
//    std::string expected = "https://identifiers.org/genecards/ABL1";
//    std::string actual = resource1.str();
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}
//
//TEST_F(ResourceTests, TestResourceWithColinInName) {
//    semsim::Resource resource1("fma:FMA:9697");
//    std::string expected = "https://identifiers.org/fma/FMA:9697";
//    std::string actual = resource1.str();
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}
//
//TEST_F(ResourceTests, TestResourceWithColinInName2) {
//    semsim::Resource resource1("fma/FMA:9697");
//    std::string expected = "https://identifiers.org/fma/FMA:9697";
//    std::string actual = resource1.str();
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}
//
//TEST_F(ResourceTests, Teststr2) {
//    semsim::Resource resource1("genecards", "ABL1");
//    std::string expected = "https://identifiers.org/genecards/ABL1";
//    std::string actual = resource1.str();
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}
//
//TEST_F(ResourceTests, TeststrFromResourceInAVector) {
//    semsim::Resource resource1("genecards", "ABL1");
//    semsim::Resource resource2("genecards", "ABL2");
//    std::vector<semsim::Resource> vec = {resource1, resource2};
//    std::string expected = "https://identifiers.org/genecards/ABL1";
//    std::string actual = vec[0].str();
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}
//
//
//TEST_F(ResourceTests, TestResourceFromLiteral) {
//    std::string literal = "Cardiomyocyte cytosolic ATP concentration";
//    semsim::Resource resource(literal);
//    std::string actual = resource.str();
//    ASSERT_STREQ(literal.c_str(), actual.c_str());
//}
//
//
//TEST_F(ResourceTests, TestResourceFrom) {
//    std::string id = "#metaid1";
//    semsim::Resource resource("./some/place/on/disk", id);
//    std::string actual = resource.str();
//    std::cout << actual << std::endl;
////    ASSERT_STREQ(id.c_str(), actual.c_str());
//}
















