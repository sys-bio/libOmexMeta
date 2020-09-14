//
// Created by Ciaran on 14/09/2020.
//

#include "gtest/gtest.h"
#include "omexmeta/OmexMeta.h"
#include "SBMLFactory.h"
#include "filesystem"

using namespace omexmeta;


//class JohnsTest : public ::testing::Test {
//public:
//    JohnsTest() = default;
//
//
//};

int main() {

//    std::string sbml = SBMLFactory::getSBML(SBML_BIOMD366);

    RDF rdf = RDF::fromFile(R"(D:\libOmexMeta\tests\cpp\Yan2012.xml)", "rdfxml");

//    rdf.toFile(R"(D:\libOmexMeta\tests\cpp\WithRDFBagSetToOFF.rdf)", "turtle");
    std::cout << rdf.toString("turtle") << std::endl;


};