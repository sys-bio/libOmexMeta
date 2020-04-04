//
// Created by Ciaran on 3/23/2020.
//

#ifndef LIBSEMGEN_SBMLTEST_H
#define LIBSEMGEN_SBMLTEST_H

#include "sbml/SBMLTypes.h"
#include "ModelStrings.h"

void sbmlTest() {
    std::string teusink_str = ModelStrings::Teusink2000();
    libsbml::SBMLDocument *doc;
    libsbml::SBMLReader reader;
    doc = reader.readSBMLFromString(teusink_str);
    unsigned int actual = doc->getModel()->getNumReactions();
    unsigned int expected = 17;
//    ASSERT_EQ(expected, actual);
};


#endif //LIBSEMGEN_SBMLTEST_H
