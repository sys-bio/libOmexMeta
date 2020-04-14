//
// Created by Ciaran on 4/14/2020.
//

#include "gtest/gtest.h"
#include "SBMLFactory.h"
#include "semsim/XmlAssistant.h"


class XmlAssistantTests : public ::testing::Test {
public:

    SBMLFactory factory;

    XmlAssistantTests() {

    }
};


TEST_F(XmlAssistantTests, TestGenerateMetaIdMethod) {
    std::vector<std::string> vec = {};
    long count = 0;
    semsim::MetaID metaId("SemsimMetaid", 0, 4);
    std::string actual;
    semsim::XmlAssistant::generateMetaId(vec, count, metaId, actual);
    std::string expected = "SemsimMetaid0000";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(XmlAssistantTests, TestGenerateMetaIdMethod2) {
    std::vector<std::string> vec = {"SemsimMetaid0000"};
    long count = 0;
    std::string actual;
    semsim::MetaID metaId("SemsimMetaid", 0, 4);
    semsim::XmlAssistant::generateMetaId(vec, count, metaId, actual);
    std::string expected = "SemsimMetaid0001";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(XmlAssistantTests, TestAddingMetaIDsToEveryElementOfXMLDoc) {
    // todo this is a weak test, make it stronger
    std::string sbml_str = SBMLFactory::getModelStr(SBML_NOT_ANNOTATED);
    semsim::XmlAssistant xmlAssistant(sbml_str);
    sbml_str = xmlAssistant.addMetaIds();
    int expected = 32;
    int actual = sizeof(sbml_str);
    ASSERT_EQ(expected, actual);
}

