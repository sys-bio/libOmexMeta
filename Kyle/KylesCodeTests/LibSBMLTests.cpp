//
// Created by Ciaran on 3/18/2020.
//



#include "gtest/gtest.h"
#include <sbml/SBMLTypes.h>

#include "ModelStrings.h"

/*
 * Here we test that libsbml can be used outside the context of
 * libsemsim. Failure of this test indicates linker/include errors
 * for libsbml
 */
TEST(LibSBMLTests, TestWeCanExtractModelNameUsingLibsbml) {
    std::string teusink_str = ModelStrings::Teusink2000();
    libsbml::SBMLDocument *doc;
    libsbml::SBMLReader reader;
    doc = reader.readSBMLFromString(teusink_str);
    unsigned int actual = doc->getSBMLDocument()->getNumReactions();
    unsigned int expected = 17;
    ASSERT_EQ(expected, actual);
}