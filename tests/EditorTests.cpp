//
// Created by Ciaran on 4/15/2020.
//
#include "gtest/gtest.h"
#include "SBMLFactory.h"
#include "semsim/Editor.h"
#include "semsim/XmlAssistant.h"

class EditorTests : public ::testing::Test {

public:


    EditorTests() {
    };
};


TEST_F(EditorTests, TestTemplatedEditorWithWrongType) {

}

TEST_F(EditorTests, Test) {
    semsim::Editor<semsim::SBMLAssistant> editor(SBMLFactory::getModelStr(SBML_NOT_ANNOTATED));
    std::string sbml = editor.addMetaIds();
    std::cout <<sbml << std::endl;

}

























