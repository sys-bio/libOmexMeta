
#include "CellMLFactory.h"
#include "OmexMetaTestUtils.h"
#include "SBMLFactory.h"
#include "librdf.h"
#include "omexmeta/EnergyDiff.h"
#include "omexmeta/OmexMetaUtils.h"
#include "omexmeta/Participant.h"
#include "omexmeta/PhysicalEntity.h"
#include "omexmeta/RDF.h"
#include "gtest/gtest.h"
#include <vector>

using namespace omexmeta;


class EnergyDiffTests : public ::testing::Test {
};

// todo think about returning *this from physical entity when modifying a physical property.

/**
 * Test creation of EnergyDiff type of composite annotation.
 */
TEST_F(EnergyDiffTests, TestEnergyDiffSBML1) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    EnergyDiff energyDiff = editor.newEnergyDiff();
    energyDiff.about("EnergyDiff_0", LOCAL_URI)
            .addSource("source_23", MODEL_URI)
            .addSink("sink_12", MODEL_URI)
            .hasProperty("parameter_metaid_0", MODEL_URI, "opb:OPB_01058");//, "EnergyDiff_0", MODEL_URI);
    editor.addEnergyDiff(energyDiff);

    // participants in a force do not have stoic

    std::cout << rdf.toString() << std::endl;

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix semsim: <http://bime.uw.edu/semsim/> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:SinkParticipant0000\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#sink_12> .\n"
                           "\n"
                           "local:SourceParticipant0000\n"
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
 * Test creation of EnergyDiff type of composite annotation.
 * In sbml the subject portion of the physical property (of energy differential)
 * needs to be created locally to the rdf document. This test requires libOmexMeta to autogenerate
 * the subject portion of the Property triples. (EnergyDiffProperty in EnergyDiffTests::TestEnergyDiffSBML1)
 */
TEST_F(EnergyDiffTests, TestEnergyDiffSBML2) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    EnergyDiff energyDiff = editor.newEnergyDiff();
    energyDiff.about("EnergyDiff_0", LOCAL_URI)
            .addSource("source_23", MODEL_URI)
            .addSink("sink_12", MODEL_URI)
            .hasProperty("parameter_metaid_0", MODEL_URI, "opb:OPB_01058");
    editor.addEnergyDiff(energyDiff);

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix semsim: <http://bime.uw.edu/semsim/> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:SinkParticipant0000\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#sink_12> .\n"
                           "\n"
                           "local:SourceParticipant0000\n"
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
 * Test creation of EnergyDiff type of composite annotation.
 * We do so with manually created uri's for the energy differential's property id
 * (EnergyDiffProperty in this example). The process id is a cellml variable metaid and it is used
 * twice in this example.
 */
TEST_F(EnergyDiffTests, TestEnergyDiffCellML1) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            CellMLFactory::getCellML(CELLML_TOY_EXTENDED), false, false);

    EnergyDiff energyDiff = editor.newEnergyDiff();
    energyDiff.about("Force", LOCAL_URI)
            .addSource("entity1", LOCAL_URI)
            .addSink("entity2", LOCAL_URI)
            .hasProperty("main.MembraneVoltage", MODEL_URI, "opb:OPB_00592");
    editor.addEnergyDiff(energyDiff);
    // force --> No stoic
    std::cout << rdf.toString() << std::endl;

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
                           "    semsim:hasPhysicalEntityReference local:entity2 .\n"
                           "\n"
                           "local:SourceParticipant0000\n"
                           "    semsim:hasPhysicalEntityReference local:entity1 .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#main.MembraneVoltage>\n"
                           "    bqbiol:isPropertyOf local:Force ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_00592> .";
    ASSERT_TRUE(RDF::equals(&rdf, expected));
}

/**
 * Test creation of EnergyDiff type of composite annotation.
 * We autogenerate
 *  1)
 */
TEST_F(EnergyDiffTests, TestEnergyDiffCellML2) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            CellMLFactory::getCellML(CELLML_TOY_EXTENDED), false, false);
    // todo change EnergyDiffProperty0000 to EnergyDiffProperty0000
    EnergyDiff energyDiff = editor.newEnergyDiff();
    energyDiff
            .addSource("entity1", LOCAL_URI)
            .addSink("entity2", LOCAL_URI)
            .hasProperty("opb:OPB_00592");
    editor.addEnergyDiff(energyDiff);
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix semsim: <http://bime.uw.edu/semsim/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:EnergyDiff0000\n"
                           "    semsim:hasSinkParticipant local:SinkParticipant0000 ;\n"
                           "    semsim:hasSourceParticipant local:SourceParticipant0000 .\n"
                           "\n"
                           "local:EnergyDiffProperty0000\n"
                           "    bqbiol:isPropertyOf local:EnergyDiff0000 ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_00592> .\n"
                           "\n"
                           "local:SinkParticipant0000\n"
                           "    semsim:hasPhysicalEntityReference local:entity2 .\n"
                           "\n"
                           "local:SourceParticipant0000\n"
                           "    semsim:hasPhysicalEntityReference local:entity1 .\n";
    ASSERT_TRUE(RDF::equals(&rdf, expected));
}

TEST_F(EnergyDiffTests, TestRemoveEnergyDiff) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    EnergyDiff physicalForce = editor.newEnergyDiff();
    physicalForce
            .about("species0001")
            .addSource("PhysicalEntity1", LOCAL_URI)
            .addSink("PhysicalEntity2", LOCAL_URI)
            .hasProperty("OPB:OPB1234");
    editor.addEnergyDiff(physicalForce);

    ASSERT_EQ(6, rdf.size());
    editor.removeEnergyDiff(physicalForce);
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix semsim: <http://bime.uw.edu/semsim/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n";
    ASSERT_TRUE(RDF::equals(&rdf, expected));
}
