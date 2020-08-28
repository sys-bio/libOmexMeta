//
// Created by Ciaran on 11/08/2020.
//

#include "gtest/gtest.h"

#include "omexmeta/SBMLSemanticExtraction.h"
#include "SBMLFactory.h"

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
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#sp_1>\n"
                           "    bqbiol:isPartOf <cytosol> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#sp_2>\n"
                           "    bqbiol:isPartOf <cytosol> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#sp_3>\n"
                           "    bqbiol:isPartOf <cytosol> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#sp_4>\n"
                           "    bqbiol:isPartOf <extraCell> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#sp_5>\n"
                           "    bqbiol:isPartOf <cytosol> .\n"
                           "\n";
    std::string actual = rdf.toString();
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(SBMLSemanticExtractionTests, TestCompartmentSingleCompartment){
    /*
     * Reminder that species comparment extraction stuff not needed whne only 1 compartment
     */
    std::string model_string = SBMLFactory::getSBML(SBML_NOT_ANNOTATED);
    RDF rdf;
    SBMLSemanticExtraction extraction(&rdf, model_string);
    extraction.extractSpeciesCompartmentSemantics();
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n";
    std::string actual = rdf.toString();
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(SBMLSemanticExtractionTests, test){
    std::string model_string = SBMLFactory::getSBML(SBML_Semantic_Extraction_Model);
    RDF rdf;
    rdf.setArchiveUri("AnAwesomeOmex.omex");
    rdf.setModelUri("Model1.xml");
    SBMLSemanticExtraction extraction(&rdf, model_string);
    extraction.extractProcessesFromReactions();
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix semsim: <http://www.bhi.washington.edu/semsim#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/AnAwesomeOmex.omex> .\n"
                           "@prefix local: <http://omex-library.org/AnAwesomeOmex.omex/Model1.rdf#> .\n"
                           "\n"
                           "local:MediatorParticipant0000\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/AnAwesomeOmex.omex/Model1.xml#Enzyme> .\n"
                           "\n"
                           "local:PhysicalProcess0000\n"
                           "    semsim:hasSinkParticipant local:SinkParticipant0000 ;\n"
                           "    semsim:hasSourceParticipant local:SourceParticipant0000 .\n"
                           "\n"
                           "local:PhysicalProcess0001\n"
                           "    semsim:hasMediatorParticipant local:MediatorParticipant0000 ;\n"
                           "    semsim:hasSinkParticipant local:SinkParticipant0001 ;\n"
                           "    semsim:hasSourceParticipant local:SourceParticipant0001, local:SourceParticipant0002 .\n"
                           "\n"
                           "local:SinkParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:double ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/AnAwesomeOmex.omex/Model1.xml#A> .\n"
                           "\n"
                           "local:SinkParticipant0001\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:double ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/AnAwesomeOmex.omex/Model1.xml#PlasmaCa> .\n"
                           "\n"
                           "local:SourceParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:double ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/AnAwesomeOmex.omex/Model1.xml#B> .\n"
                           "\n"
                           "local:SourceParticipant0001\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:double ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/AnAwesomeOmex.omex/Model1.xml#Ca> .\n"
                           "\n"
                           "local:SourceParticipant0002\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:double ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/AnAwesomeOmex.omex/Model1.xml#A> .\n"
                           "\n"
                           "<http://omex-library.org/AnAwesomeOmex.omex/Model1.xml#react1>\n"
                           "    bqbiol:isPropertyOf local:PhysicalProcess0000 ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb/OPB_00592> .\n"
                           "\n"
                           "<http://omex-library.org/AnAwesomeOmex.omex/Model1.xml#react2>\n"
                           "    bqbiol:isPropertyOf local:PhysicalProcess0001 ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb/OPB_00592> .\n\n";
    std::string actual = rdf.toString("turtle");
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}










