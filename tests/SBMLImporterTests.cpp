//
// Created by Ciaran on 3/17/2020.
//

#include "gtest/gtest.h"
#include "semsim/SBMLImporter.h"
#include "ModelStrings.h"

using namespace semsim;
using namespace std;

class SBMLImporterTest : public ::testing::Test {
 protected:
  void SetUp() override {
      teusink = ModelStrings::Teusink2000();
      sbmlDocument = reader.readSBMLFromString(teusink);
  }
   void TearDown() override {

  }

  std::string teusink;
  libsbml::SBMLDocument* sbmlDocument;
  libsbml::SBMLReader reader;

};


TEST_F(SBMLImporterTest, test){
    SBMLImporter sbmlImporter(sbmlDocument);
    SBMLModel &sbmlModel = sbmlImporter.getSBMLModel();
//    Components components = sbmlModel.getComponents();

//    cout << &components[0] << endl;
//    for (auto i : components){
//        cout << i << endl;
//    }
//    std::string h = sbmlModel.humanize();
//    cout << h << endl;

//    cout <<  sbmlImporter.getSBMLModel()
}








