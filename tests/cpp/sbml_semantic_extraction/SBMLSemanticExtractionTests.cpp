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
    std::string model_string = SBMLFactory::getSBML(SBML_Semantic_Extraction_Model);
    RDF rdf;
    SBMLSemanticExtraction extraction(&rdf, model_string);
    extraction.extractProcessesFromReactions();
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix semsim: <http://www.bhi.washington.edu/semsim#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix myOMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:MediatorParticipant0000\n"
                           "    semsim:hasPhysicalEntityReference local:Enzyme .\n"
                           "\n"
                           "local:PhysicalProcess0000\n"
                           "    semsim:hasSinkParticipant local:SinkParticipant0000 ;\n"
                           "    semsim:hasSourceParticipant local:SourceParticipant0000 .\n"
                           "\n"
                           "local:PhysicalProcess0001\n"
                           "    semsim:hasMediatorParticipant local:MediatorParticipant0000 ;\n"
                           "    semsim:hasSinkParticipant local:SinkParticipant0001 ;\n"
                           "    semsim:hasSourceParticipant local:SourceParticipant0001 .\n"
                           "\n"
                           "local:SinkParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^<http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double> ;\n"
                           "    semsim:hasPhysicalEntityReference local:A .\n"
                           "\n"
                           "local:SinkParticipant0001\n"
                           "    semsim:hasMultiplier \"1\"^^<http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double> ;\n"
                           "    semsim:hasPhysicalEntityReference local:PlasmaCa .\n"
                           "\n"
                           "local:SourceParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^<http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double> ;\n"
                           "    semsim:hasPhysicalEntityReference local:B .\n"
                           "\n"
                           "local:SourceParticipant0001\n"
                           "    semsim:hasMultiplier \"1\"^^<http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double> ;\n"
                           "    semsim:hasPhysicalEntityReference local:A, local:Ca .\n"
                           "\n"
                           "local:react1\n"
                           "    bqbiol:isPropertyOf local:PhysicalProcess0000 ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb/:opb_1234> .\n"
                           "\n"
                           "local:react2\n"
                           "    bqbiol:isPropertyOf local:PhysicalProcess0001 ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb/:opb_1234> .\n"
                           "";
    std::string actual = rdf.toString("turtle");
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}










