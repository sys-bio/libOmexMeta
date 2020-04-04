//
// Created by Ciaran on 4/2/2020.
//



#include <semsim/uri.h>
#include <semsim/Resource.h>
#include <sbml/SBMLTypes.h>
#include "gtest/gtest.h"
#include "SBMLFactory.h"

using namespace semsim;
using namespace std;

class ResourceTests : public ::testing::Test {
public:
    std::string url_str1;
    Url url;
    SBMLDocument* doc;

    void SetUp() override {
        url_str1 = "http://www.example.com/#cheese";
        url = Url(url_str1);

        doc = semsim_test::SBMLFactory::getSBMLDocument(semsim_test::SBML_ANNOTATED);
    }

};


TEST_F(ResourceTests, TestInstantiation){
    Resource resource(url);
    ASSERT_STREQ(resource.toString().c_str(), url_str1.c_str());
}


TEST_F(ResourceTests, TestFromString){
    Resource resource(url_str1);
    ASSERT_STREQ(resource.toString().c_str(), url_str1.c_str());
}

TEST_F(ResourceTests, TestCopyAssignment){
    Resource resource1(url_str1);
    Resource resource2 = resource1;
    ASSERT_STREQ(resource2.toString().c_str(), url_str1.c_str());
}

TEST_F(ResourceTests, TestCopyConstructor){
    Resource resource1(url_str1);
    Resource resource2(resource1);
    ASSERT_STREQ(resource1.toString().c_str(), url_str1.c_str());
    ASSERT_STREQ(resource2.toString().c_str(), url_str1.c_str());
}

TEST_F(ResourceTests, TestMoveCopy){
    Resource resource1(url_str1);
    Resource resource2(std::move(resource1));
    ASSERT_STRNE(resource1.toString().c_str(), url_str1.c_str());
    ASSERT_STREQ(resource2.toString().c_str(), url_str1.c_str());
}

TEST_F(ResourceTests, TestMoveAssignment){
    Resource resource1(url_str1);
    Resource resource2 = std::move(resource1);
    ASSERT_STRNE(resource1.toString().c_str(), url_str1.c_str());
    ASSERT_STREQ(resource2.toString().c_str(), url_str1.c_str());
}


TEST_F(ResourceTests, TestConstructFromElement){
    libsbml::Compartment *compartment = doc->getModel()->getCompartment(0);
    SingularAnnotation annotation(compartment->getMetaId());
    Component component = Component(annotation);
    Resource resource1(&component);
    ASSERT_TRUE(resource1.isLocal());
}

TEST_F(ResourceTests, TestHumanize){
    libsbml::Compartment *compartment = doc->getModel()->getCompartment(0);
    SingularAnnotation annotation(compartment->getMetaId());
    Component component = Component(annotation);
    Resource resource1(&component);
    ostringstream os;
    os << resource1.humanize();
    ASSERT_STREQ(os.str().c_str(), "#cytosol");
}
TEST_F(ResourceTests, TestGetElement){
    libsbml::Compartment *compartment = doc->getModel()->getCompartment(0);
    SingularAnnotation annotation(compartment->getMetaId());
    Component component = Component(annotation);
    Resource resource1(&component);
    ostringstream os;
    os << resource1.getElement()->getMetaId();
    ASSERT_STREQ("cytosol", os.str().c_str());
}

/*
 * The resource can be either external or internal. The external
 * ones have aurl and the internal ones point to an sbase. Presumably the internal
 * ones als have a url, but they do not look like they are ever assigned.
 *
 * This composite annotation looks like it was an after thought in the design. A patch
 * that was added after the design was chosen.
 */































