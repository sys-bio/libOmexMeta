//
// Created by Ciaran on 3/30/2020.
//
#include "gtest/gtest.h"
#include <semsim/SemSim.h>
#include "sbml/SBMLTypes.h"
#include <iostream>

#include "SBMLFactory.h"

class SemSimSbmlModelNotAnnotatedTests : public ::testing::Test {
protected:
    libsbml::SBMLDocument *doc;

    SemSimSbmlModelNotAnnotatedTests()  {
        doc = semsim_test::SBMLFactory::getModel(semsim_test::SBML_NOT_ANNOTATED);
    };
};

TEST_F(SemSimSbmlModelNotAnnotatedTests, test2){
    semsim::SemSimSBMLModel model(doc);

}