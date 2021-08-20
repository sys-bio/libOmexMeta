//
// Created by Ciaran on 11/08/2020.
//

#include "gtest/gtest.h"

#include "SBMLFactory.h"
#include "omexmeta/RDF.h"
#include "omexmeta/SBMLSemanticExtraction.h"
#include "AnnotationSamples.h"

using namespace omexmeta;

class SBMLSemanticExtractionTests : public ::testing::Test {
public:

    AnnotationSamples samples;

    SBMLSemanticExtractionTests() = default;

};


TEST_F(SBMLSemanticExtractionTests, TestTwoCompartments){
    std::string model_string = SBMLFactory::getSBML(SBML_SEMANTIC_EXTRACTION_MODEL);
    RDF rdf;
    Editor editor = rdf.toEditor(model_string, true);
    SBMLSemanticExtraction extraction(&editor);
    extraction.extractSpeciesCompartmentSemantics();
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix semsim: <http://bime.uw.edu/semsim/> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:MediatorParticipant0000\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#sp_5> .\n"
                           "\n"
                           "local:ProcessProperty0000\n"
                           "    semsim:hasSinkParticipant local:SinkParticipant0000 ;\n"
                           "    semsim:hasSourceParticipant local:SourceParticipant0000 .\n"
                           "\n"
                           "local:ProcessProperty0001\n"
                           "    semsim:hasMediatorParticipant local:MediatorParticipant0000 ;\n"
                           "    semsim:hasSinkParticipant local:SinkParticipant0001 ;\n"
                           "    semsim:hasSourceParticipant local:SourceParticipant0001, local:SourceParticipant0002 .\n"
                           "\n"
                           "local:SinkParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:double ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#sp_1> .\n"
                           "\n"
                           "local:SinkParticipant0001\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:double ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#sp_4> .\n"
                           "\n"
                           "local:SourceParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:double ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#sp_2> .\n"
                           "\n"
                           "local:SourceParticipant0001\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:double ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#sp_3> .\n"
                           "\n"
                           "local:SourceParticipant0002\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:double ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#sp_1> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#react1>\n"
                           "    bqbiol:isPropertyOf local:ProcessProperty0000 ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb/OPB_00592> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#react2>\n"
                           "    bqbiol:isPropertyOf local:ProcessProperty0001 ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb/OPB_00592> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#sp_1>\n"
                           "    bqbiol:isPartOf <http://omex-library.org/NewOmex.omex/NewModel.xml#cytosol> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#sp_2>\n"
                           "    bqbiol:isPartOf <http://omex-library.org/NewOmex.omex/NewModel.xml#cytosol> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#sp_3>\n"
                           "    bqbiol:isPartOf <http://omex-library.org/NewOmex.omex/NewModel.xml#cytosol> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#sp_4>\n"
                           "    bqbiol:isPartOf <http://omex-library.org/NewOmex.omex/NewModel.xml#extraCell> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#sp_5>\n"
                           "    bqbiol:isPartOf <http://omex-library.org/NewOmex.omex/NewModel.xml#cytosol> .\n"
                           "\n";
    RDF::equals(&rdf, expected);
}

TEST_F(SBMLSemanticExtractionTests, TestCompartmentSingleCompartment){
    /*
     * Reminder that species comparment extraction stuff not needed whne only 1 compartment
     */
    std::string model_string = SBMLFactory::getSBML(SBML_NOT_ANNOTATED);
    RDF rdf;
    Editor editor = rdf.toEditor(model_string, true);
    SBMLSemanticExtraction extraction(&editor);
    extraction.extractSpeciesCompartmentSemantics();
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix semsim: <http://bime.uw.edu/semsim/> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:ProcessProperty0000\n"
                           "    semsim:hasSinkParticipant local:SinkParticipant0000, local:SinkParticipant0001 .\n"
                           "\n"
                           "local:SinkParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:double ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0003> .\n"
                           "\n"
                           "local:SinkParticipant0001\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:double ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0004> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0005>\n"
                           "    bqbiol:isPropertyOf local:ProcessProperty0000 ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb/OPB_00592> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0009>\n"
                           "    bqbiol:isPropertyOf local:ProcessProperty0001 ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb/OPB_00592> .\n"
                           "\n";
    std::string actual = rdf.toString();
    std::cout << actual << std::endl;
    RDF::equals(&rdf, expected);
}

TEST_F(SBMLSemanticExtractionTests, TestReactionExtraction){
    std::string model_string = SBMLFactory::getSBML(SBML_SEMANTIC_EXTRACTION_MODEL);
//    std::cout << model_string << std::endl;
    RDF rdf;
    rdf.setArchiveUri("AnAwesomeOmex.omex");
    rdf.setModelUri("Model1.xml");
    Editor editor = rdf.toEditor(model_string, true);
    SBMLSemanticExtraction extraction(&editor);
    extraction.extractProcessesFromReactions();
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix semsim: <http://bime.uw.edu/semsim/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix local: <http://omex-library.org/AnAwesomeOmex.omex/Model1.rdf#> .\n"
                           "\n"
                           "local:MediatorParticipant0000\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/AnAwesomeOmex.omex/Model1.xml#sp_5> .\n"
                           "\n"
                           "local:MediatorParticipant0001\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/AnAwesomeOmex.omex/Model1.xml#sp_5> .\n"
                           "\n"
                           "local:ProcessProperty0000\n"
                           "    bqbiol:isPropertyOf <http://omex-library.org/AnAwesomeOmex.omex/Model1.xml#react1> ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_00592> .\n"
                           "\n"
                           "local:ProcessProperty0001\n"
                           "    bqbiol:isPropertyOf <http://omex-library.org/AnAwesomeOmex.omex/Model1.xml#react2> ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_00592> .\n"
                           "\n"
                           "local:ProcessProperty0002\n"
                           "    bqbiol:isPropertyOf <http://omex-library.org/AnAwesomeOmex.omex/Model1.xml#react1> ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_00592> .\n"
                           "\n"
                           "local:ProcessProperty0003\n"
                           "    bqbiol:isPropertyOf <http://omex-library.org/AnAwesomeOmex.omex/Model1.xml#react2> ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_00592> .\n"
                           "\n"
                           "local:SinkParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:double ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/AnAwesomeOmex.omex/Model1.xml#sp_1> .\n"
                           "\n"
                           "local:SinkParticipant0001\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:double ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/AnAwesomeOmex.omex/Model1.xml#sp_4> .\n"
                           "\n"
                           "local:SinkParticipant0002\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:double ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/AnAwesomeOmex.omex/Model1.xml#sp_1> .\n"
                           "\n"
                           "local:SinkParticipant0003\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:double ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/AnAwesomeOmex.omex/Model1.xml#sp_4> .\n"
                           "\n"
                           "local:SourceParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:double ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/AnAwesomeOmex.omex/Model1.xml#sp_2> .\n"
                           "\n"
                           "local:SourceParticipant0001\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:double ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/AnAwesomeOmex.omex/Model1.xml#sp_3> .\n"
                           "\n"
                           "local:SourceParticipant0002\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:double ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/AnAwesomeOmex.omex/Model1.xml#sp_1> .\n"
                           "\n"
                           "local:SourceParticipant0003\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:double ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/AnAwesomeOmex.omex/Model1.xml#sp_2> .\n"
                           "\n"
                           "local:SourceParticipant0004\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:double ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/AnAwesomeOmex.omex/Model1.xml#sp_3> .\n"
                           "\n"
                           "local:SourceParticipant0005\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:double ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/AnAwesomeOmex.omex/Model1.xml#sp_1> .\n"
                           "\n"
                           "<http://omex-library.org/AnAwesomeOmex.omex/Model1.xml#react1>\n"
                           "    semsim:hasSinkParticipant local:SinkParticipant0000, local:SinkParticipant0002 ;\n"
                           "    semsim:hasSourceParticipant local:SourceParticipant0000, local:SourceParticipant0003 .\n"
                           "\n"
                           "<http://omex-library.org/AnAwesomeOmex.omex/Model1.xml#react2>\n"
                           "    semsim:hasMediatorParticipant local:MediatorParticipant0000, local:MediatorParticipant0001 ;\n"
                           "    semsim:hasSinkParticipant local:SinkParticipant0001, local:SinkParticipant0003 ;\n"
                           "    semsim:hasSourceParticipant local:SourceParticipant0001, local:SourceParticipant0002, local:SourceParticipant0004, local:SourceParticipant0005 .\n"
                           "\n"
                           "<http://omex-library.org/AnAwesomeOmex.omex/Model1.xml#sp_1>\n"
                           "    bqbiol:isPartOf <http://omex-library.org/AnAwesomeOmex.omex/Model1.xml#cytosol> .\n"
                           "\n"
                           "<http://omex-library.org/AnAwesomeOmex.omex/Model1.xml#sp_2>\n"
                           "    bqbiol:isPartOf <http://omex-library.org/AnAwesomeOmex.omex/Model1.xml#cytosol> .\n"
                           "\n"
                           "<http://omex-library.org/AnAwesomeOmex.omex/Model1.xml#sp_3>\n"
                           "    bqbiol:isPartOf <http://omex-library.org/AnAwesomeOmex.omex/Model1.xml#cytosol> .\n"
                           "\n"
                           "<http://omex-library.org/AnAwesomeOmex.omex/Model1.xml#sp_4>\n"
                           "    bqbiol:isPartOf <http://omex-library.org/AnAwesomeOmex.omex/Model1.xml#extraCell> .\n"
                           "\n"
                           "<http://omex-library.org/AnAwesomeOmex.omex/Model1.xml#sp_5>\n"
                           "    bqbiol:isPartOf <http://omex-library.org/AnAwesomeOmex.omex/Model1.xml#cytosol> .";
    std::string actual = rdf.toString("turtle");
    std::cout << actual << std::endl;
    RDF::equals(&rdf, expected);
}




