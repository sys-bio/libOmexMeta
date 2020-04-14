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


//TEST_F(XmlAssistantTests, test){
//    std::string sbml_str = factory.getModelStr(SBML_NOT_ANNOTATED);
//    std::cout << sbml_str << std::endl;
//    semsim::XmlAssistant xmlAssistant(sbml_str);
//
//}

