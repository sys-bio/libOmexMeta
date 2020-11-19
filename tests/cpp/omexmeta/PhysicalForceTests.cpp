
#include "CellMLFactory.h"
#include "OmexMetaTestUtils.h"
#include "SBMLFactory.h"
#include "librdf.h"
#include "omexmeta/OmexMetaUtils.h"
#include "omexmeta/Participant.h"
#include "omexmeta/PhysicalEntity.h"
#include "omexmeta/PhysicalForce.h"
#include "omexmeta/RDF.h"
#include "gtest/gtest.h"
#include <vector>

using namespace omexmeta;


class PhysicalForceTests : public ::testing::Test {
};

// todo think about returning *this from physical entity when modifying a physical property.

/**
 * Test creation of PhysicalForce type of composite annotation.
 */
TEST_F(PhysicalForceTests, TestPhysicalForceSBML1) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    PhysicalForce PhysicalForce = editor.newPhysicalForce();
    PhysicalForce.about("EnergyDiff_0", LOCAL_URI)
            .addSource("source_23", MODEL_URI, 1)
            .addSink("sink_12",MODEL_URI,  1)
            .hasProperty("parameter_metaid_0", MODEL_URI, "opb:OPB_01058");//, "EnergyDiff_0", MODEL_URI);
    editor.addPhysicalForce(PhysicalForce);

    // participants in a force do not have stoic

    std::cout << rdf.toString()<<std::endl;

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix semsim: <http://bime.uw.edu/semsim/> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:SinkParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#sink_12> .\n"
                           "\n"
                           "local:SourceParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#source_23> .\n"
                           "\n"
                           "local:EnergyDiff_0\n"
                           "    semsim:hasSinkParticipant local:SinkParticipant0000 ;\n"
                           "    semsim:hasSourceParticipant local:SourceParticipant0000 .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#parameter_metaid_0>\n"
                           "    bqbiol:isPropertyOf local:EnergyDiff_0 ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_01058> .";
    ASSERT_TRUE(RDF::equals(&rdf, expected));

}

/**
 * Test creation of PhysicalForce type of composite annotation.
 * In sbml the subject portion of the physical property (of physical force)
 * needs to be created locally to the rdf document. This test requires libOmexMeta to autogenerate
 * the subject portion of the Property triples. (ForceProperty in PhysicalForceTests::TestPhysicalForceSBML1)
 */
TEST_F(PhysicalForceTests, TestPhysicalForceSBML2) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    PhysicalForce PhysicalForce = editor.newPhysicalForce();
    PhysicalForce.about("EnergyDiff_0", LOCAL_URI)
            .addSource("source_23", MODEL_URI, 1)
            .addSink("sink_12", MODEL_URI, 1)
            .hasProperty("parameter_metaid_0", MODEL_URI, "opb:OPB_01058");
    editor.addPhysicalForce(PhysicalForce);

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix semsim: <http://bime.uw.edu/semsim/> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:SinkParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#sink_12> .\n"
                           "\n"
                           "local:SourceParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#source_23> .\n"
                           "\n"
                           "local:EnergyDiff_0\n"
                           "    semsim:hasSinkParticipant local:SinkParticipant0000 ;\n"
                           "    semsim:hasSourceParticipant local:SourceParticipant0000 .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#parameter_metaid_0>\n"
                           "    bqbiol:isPropertyOf local:EnergyDiff_0 ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_01058> .";
    ASSERT_TRUE(RDF::equals(&rdf, expected));

}


/**
 * Test creation of PhysicalForce type of composite annotation.
 * We do so with manually created uri's for the physical force's property id
 * (ForceProperty in this example). The process id is a cellml variable metaid and it is used
 * twice in this example.
 */
TEST_F(PhysicalForceTests, TestPhysicalForceCellML1) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            CellMLFactory::getCellML(CELLML_TOY_EXTENDED), false, false);

    PhysicalForce PhysicalForce = editor.newPhysicalForce();
    PhysicalForce.about("Force", LOCAL_URI)
            .addSource("entity1", LOCAL_URI, 1)
            .addSink("entity2", LOCAL_URI, 1)
            .hasProperty("main.MembraneVoltage", MODEL_URI, "opb:OPB_00592");
    editor.addPhysicalForce(PhysicalForce);
    // force --> No stoic
    std::cout << rdf.toString()<<std::endl;

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix semsim: <http://bime.uw.edu/semsim/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:Force\n"
                           "    semsim:hasSinkParticipant local:SinkParticipant0000 ;\n"
                           "    semsim:hasSourceParticipant local:SourceParticipant0000 .\n"
                           "\n"
                           "local:SinkParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
                           "    semsim:hasPhysicalEntityReference local:entity2 .\n"
                           "\n"
                           "local:SourceParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
                           "    semsim:hasPhysicalEntityReference local:entity1 .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#main.MembraneVoltage>\n"
                           "    bqbiol:isPropertyOf local:Force ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_00592> .";
    ASSERT_TRUE(RDF::equals(&rdf, expected));

}

/**
 * Test creation of PhysicalForce type of composite annotation.
 * We autogenerate
 *  1)
 */
TEST_F(PhysicalForceTests, TestPhysicalForceCellML2) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            CellMLFactory::getCellML(CELLML_TOY_EXTENDED), false, false);
    // todo change ForceProperty0000 to EnergyDiffProperty0000
    PhysicalForce PhysicalForce = editor.newPhysicalForce();
    PhysicalForce
            .addSource("entity1", LOCAL_URI, 1)
            .addSink("entity2", LOCAL_URI, 1)
            .hasProperty("opb:OPB_00592");
    editor.addPhysicalForce(PhysicalForce);
   std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix semsim: <http://bime.uw.edu/semsim/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:Force0000\n"
                           "    semsim:hasSinkParticipant local:SinkParticipant0000 ;\n"
                           "    semsim:hasSourceParticipant local:SourceParticipant0000 .\n"
                           "\n"
                           "local:ForceProperty0000\n"
                           "    bqbiol:isPropertyOf local:Force0000 ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_00592> .\n"
                           "\n"
                           "local:SinkParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
                           "    semsim:hasPhysicalEntityReference local:entity2 .\n"
                           "\n"
                           "local:SourceParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
                           "    semsim:hasPhysicalEntityReference local:entity1 .\n";
    ASSERT_TRUE(RDF::equals(&rdf, expected));

}

TEST_F(PhysicalForceTests, TestRemovePhysicalForce) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    PhysicalForce physicalForce = editor.newPhysicalForce();
    physicalForce
            .about("#OmexMetaId0002")
            .addSource("PhysicalEntity1",LOCAL_URI, 1.0)
            .addSink("PhysicalEntity2" , LOCAL_URI, 1.0)
            .hasProperty("OPB:OPB1234");
    editor.addPhysicalForce(physicalForce);
    ASSERT_EQ(8, rdf.size());
    editor.removePhysicalForce(physicalForce);
    int expected = 0;
    int actual = rdf.size();
    ASSERT_EQ(expected, actual);
}





