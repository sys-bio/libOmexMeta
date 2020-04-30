//
// Created by Ciaran on 3/30/2020.
//

//
// Created by Ciaran on 3/30/2020.
//
#include "gtest/gtest.h"
#include <semsim/SemSim.h>
#include "sbml/SBMLTypes.h"
#include <iostream>

#include "SBMLFactory.h"

class ComponentTests : public ::testing::Test {
protected:
    libsbml::SBMLDocument *doc;

    ComponentTests() {
        doc = semsim_test::SBMLFactory::getSBMLDocument(semsim_test::SBML_NOT_ANNOTATED);
    };
};

TEST_F(ComponentTests, test2) {
    semsim::SemSimSBMLModel model(doc);

}



























