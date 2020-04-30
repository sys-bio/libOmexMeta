//
// Created by Ciaran on 3/30/2020.
//
#include "gtest/gtest.h"
#include <semsim/SemSim.h>
#include "sbml/SBMLTypes.h"
#include <iostream>

#include "SBMLFactory.h"

class SemSimModelNotAnnotatedTests : public ::testing::Test {
protected:
    libsbml::SBMLDocument *doc;

    SemSimModelNotAnnotatedTests() {
        doc = semsim_test::SBMLFactory::getSBMLDocument(semsim_test::SBML_NOT_ANNOTATED);
    };
};

TEST_F(SemSimModelNotAnnotatedTests, test2) {
    semsim::SemSimSBMLModel model(doc);

}
