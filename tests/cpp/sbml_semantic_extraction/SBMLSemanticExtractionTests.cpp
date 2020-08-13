//
// Created by Ciaran on 11/08/2020.
//

#include "gtest/gtest.h"

#include "omexmeta/sbml_semantic_extraction/SBMLSemanticExtraction.h"
#include "../SBMLFactory.h"

using namespace omexmeta;

class SBMLSemanticExtractionTests : public ::testing::Test {
public:

    SBMLSemanticExtractionTests() = default;

};


TEST_F(SBMLSemanticExtractionTests, TestTwoCompartments){
    std::string model_string = SBMLFactory::getSBML(SBML_Semantic_Extraction_Model);
    RDF rdf;
    SBMLSemanticExtraction extraction(&rdf, model_string);
    extraction.extractSpeciesCompartmentSemantics();
    std::string expected = "<?xml version=\"1.1\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:local=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#\"\n"
                           "   xmlns:myOMEX=\"http://omex-library.org/NewOmex.omex\"\n"
                           "   xmlns:myOMEXlib=\"http://omex-library.org/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.xml#sp_1\">\n"
                           "    <bqbiol:isPartOf rdf:resource=\"cytosol\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.xml#sp_2\">\n"
                           "    <bqbiol:isPartOf rdf:resource=\"cytosol\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.xml#sp_3\">\n"
                           "    <bqbiol:isPartOf rdf:resource=\"cytosol\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.xml#sp_4\">\n"
                           "    <bqbiol:isPartOf rdf:resource=\"extraCell\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.xml#sp_5\">\n"
                           "    <bqbiol:isPartOf rdf:resource=\"cytosol\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n";
    std::string actual = rdf.toString();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(SBMLSemanticExtractionTests, TestCompartmentSingleCompartment){
    std::string model_string = SBMLFactory::getSBML(SBML_NOT_ANNOTATED);
    RDF rdf;
    SBMLSemanticExtraction extraction(&rdf, model_string);
    extraction.extractSpeciesCompartmentSemantics();
    std::string expected = "<?xml version=\"1.1\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:local=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#\"\n"
                           "   xmlns:myOMEX=\"http://omex-library.org/NewOmex.omex\"\n"
                           "   xmlns:myOMEXlib=\"http://omex-library.org/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"/>\n";
    std::string actual = rdf.toString();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(SBMLSemanticExtractionTests, test){
    /*
     * myOMEX:Toymodel.sbml#react1
     *      semsim:hasSourceParticipant local:source0 ;
     *      semsim:hasSinkParticipant local:sink0 .
     *
     * local:source0 semsim:hasMultiplier 1.0 ;
     * semsim:hasPhyscialEntityReference myOMEX:ToyModel.sbml#sp_2 .
     *
     * local:sink0 semsim:hasMultiplier 2.0 ; semsim:hasPhyscialEntityReference
     * myOMEX:ToyModel.sbml#sp_1 .
     *
     *
     * myOMEX:Toymodel.sbml#react2
     *      semsim:hasSourceParticipant local:source1 ;
     *      semsim:hasSourceParticipant local:source2 ;
     *      semsim:hasSinkParticipant local:sink1 ;
     *      semsim:hasMediatorParticipant local:mediator1 .
     *
     * local:source1 semsim:hasMultiplier 1.0 ;
     * semsim:hasPhyscialEntityReference myOMEX:ToyModel.sbml#sp_3 .
     *
     * local:source2 semsim:hasMultiplier 1.0 ;
     * semsim:hasPhyscialEntityReference myOMEX:ToyModel.sbml#sp_1 .
     *
     * local:sink1 semsim:hasMultiplier 1.0 ; semsim:hasPhyscialEntityReference
     * myOMEX:ToyModel.sbml#sp_4 .
     *
     * local:mediator1 semsim:hasPhysicalEntityReference
     * myOMEX:Toymodel.sbml#sp_5 .
     *
     */
    std::string model_string = SBMLFactory::getSBML(SBML_Semantic_Extraction_Model);
    RDF rdf;
    SBMLSemanticExtraction extraction(&rdf, model_string);
    extraction.extractProcessesFromReactions();
    std::cout <<rdf.toString("turtle") << std::endl;
}










