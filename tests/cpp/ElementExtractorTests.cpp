//
// Created by Ciaran on 11/08/2020.
//

#include "gtest/gtest.h"

#include "omexmeta/ElementExtractor.h"
#include "SBMLFactory.h"
#include "iostream"

using namespace omexmeta;

class ElementExtractorTests : public ::testing::Test {
public:

    std::string sbml = SBMLFactory::getSBML(SBML_NOT_ANNOTATED);


    ElementExtractorTests() = default;

};

TEST_F(ElementExtractorTests, TetsListOfCompartmentsExtraction){
    ElementExtractor elementExtractor(sbml, "listOfCompartments");
    auto elements_ = elementExtractor.getElements();
    ASSERT_EQ(1, elements_.size());
    ASSERT_STREQ("listOfCompartments", (const char*)elements_[0]->name);
}

TEST_F(ElementExtractorTests, TestCompartmentExtraction){
    ElementExtractor elementExtractor(sbml, "compartment");
    auto elements_ = elementExtractor.getElements();
    ASSERT_EQ(1, elements_.size());
    ASSERT_STREQ("compartment", (const char*)elements_[0]->name);
}

TEST_F(ElementExtractorTests, TestReactionExtraction){
    ElementExtractor elementExtractor(sbml, "reaction");
    auto elements_ = elementExtractor.getElements();
    ASSERT_EQ(2, elements_.size());
    ASSERT_STREQ("reaction", (const char*)elements_[0]->name);
    ASSERT_STREQ("reaction", (const char*)elements_[1]->name);
}

TEST_F(ElementExtractorTests, TestElementNamesAreAccessibleAfterExtraction){
    ElementExtractor elementExtractor(SBMLFactory::getSBML(SBML_Semantic_Extraction_Model), "species");
    auto elements_ = elementExtractor.getElements();
    std::vector<std::string> v;
    v.reserve(elements_.size());
    for (auto &it: elements_){
        char* s = ( char*)xmlGetProp(it, (const xmlChar*)"id");
        v.emplace_back(s);
        free(s);
    }
    std::vector<std::string> expected = { "A", "B", "Ca", "PlasmaCa", "Enzyme" };
    ASSERT_EQ(expected, v);

}


























