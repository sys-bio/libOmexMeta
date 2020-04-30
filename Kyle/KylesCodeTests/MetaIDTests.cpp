//
// Created by Ciaran on 3/30/2020.
//
#include "gtest/gtest.h"
#include <semsim/SemSim.h>
#include "sbml/SBMLTypes.h"
#include <iostream>

#include "SBMLFactory.h"

class MetaIDTests : public ::testing::Test {
protected:
    libsbml::SBMLDocument *doc;
    std::string xml;

    MetaIDTests() {
        doc = semsim_test::SBMLFactory::getSBMLDocument(semsim_test::SBML_NOT_ANNOTATED);
        xml = semsim_test::SBMLFactory::getModelStr(semsim_test::SBML_NOT_ANNOTATED);
    };
};

TEST_F(MetaIDTests, TestContainsMetaIdPositive) {
    std::cout << xml << std::endl;
    libsbml::Model *model = doc->getModel();
    semsim::MetaID metaId(*model);
    bool actual = metaId.contains("cytosol");
    ASSERT_TRUE(actual);
}

TEST_F(MetaIDTests, TestContainsMetaIdNegative) {
    std::cout << xml << std::endl;
    libsbml::Model *model = doc->getModel();
    semsim::MetaID metaId(*model);
    bool actual = metaId.contains("id00001");
    ASSERT_FALSE(actual);
}

TEST_F(MetaIDTests, TestHasMetaIdsMethod) {
    libsbml::Model *model = doc->getModel();
    semsim::MetaID metaId(*model);
    bool actual = metaId.hasMetaIds();
    ASSERT_FALSE(actual);
}

TEST_F(MetaIDTests, TestAssignMetaIds) {
    libsbml::Model *model = doc->getModel();
    semsim::MetaID metaId(*model);
    metaId.assignMetaIds();
    bool actual = metaId.hasMetaIds();
    ASSERT_TRUE(actual);
}
