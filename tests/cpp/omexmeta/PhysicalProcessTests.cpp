//
// Created by Ciaran on 4/23/2020.
//


#include "CellMLFactory.h"
#include "SBMLFactory.h"
#include "librdf.h"
#include "omexmeta/OmexMetaUtils.h"
#include "omexmeta/Participant.h"
#include "omexmeta/PhysicalEntity.h"
#include "omexmeta/PhysicalProcess.h"
#include "omexmeta/RDF.h"
#include "gtest/gtest.h"
#include <vector>

using namespace omexmeta;


class PhysicalProcessTests : public ::testing::Test {
};

// todo think about returning *this from physical entity when modifying a physical property.

/**
 * Test creation of PhysicalProcess type of composite annotation.
 * In sbml the subject portion of the physical property (of physical process)
 * needs to be created locally to the rdf document. This test does this with user specified
 * ids.
 */
TEST_F(PhysicalProcessTests, TestPhysicalProcessSBML1) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    PhysicalProcess physicalProcess = editor.newPhysicalProcess();
    physicalProcess.about("reaction0000", MODEL_URI)
            .addSource("species0000", MODEL_URI, 1)
            .addSink("species0001", MODEL_URI, 1)
            .addMediator("species0002", MODEL_URI )
            .hasProperty("ReactionProperty", LOCAL_URI, "opb:OPB_00592");//, "reaction0000", MODEL_URI);
    editor.addPhysicalProcess(physicalProcess);

    std::cout << rdf.toString() << std::endl;

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix semsim: <http://bime.uw.edu/semsim/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:MediatorParticipant0000\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#species0002> .\n"
                           "\n"
                           "local:ReactionProperty\n"
                           "    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#reaction0000> ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_00592> .\n"
                           "\n"
                           "local:SinkParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:double ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#species0001> .\n"
                           "\n"
                           "local:SourceParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:double ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#species0000> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#reaction0000>\n"
                           "    semsim:hasMediatorParticipant local:MediatorParticipant0000 ;\n"
                           "    semsim:hasSinkParticipant local:SinkParticipant0000 ;\n"
                           "    semsim:hasSourceParticipant local:SourceParticipant0000 .\n"
                           "";
    ASSERT_TRUE(RDF::equals(&rdf, expected));

}

/**
 * Test creation of PhysicalProcess type of composite annotation.
 * In sbml the subject portion of the physical property (of physical process)
 * needs to be created locally to the rdf document. This test requires libOmexMeta to autogenerate
 * the subject portion of the Property triples. (ReactionProperty in PhysicalProcessTests::TestPhysicalProcessSBML1)
 */
TEST_F(PhysicalProcessTests, TestPhysicalProcessSBML2) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    PhysicalProcess physicalProcess = editor.newPhysicalProcess();
    physicalProcess.about("reaction0000", MODEL_URI)
            .addSource("species0000",MODEL_URI,  1)
            .addSink("species0001", MODEL_URI, 1)
            .addMediator("species0002", MODEL_URI)
            .hasProperty("opb:OPB_00592");
    editor.addPhysicalProcess(physicalProcess);

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix semsim: <http://bime.uw.edu/semsim/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:MediatorParticipant0000\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#species0002> .\n"
                           "\n"
                           "local:ProcessProperty0000\n"
                           "    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#reaction0000> ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_00592> .\n"
                           "\n"
                           "local:SinkParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:double ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#species0001> .\n"
                           "\n"
                           "local:SourceParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:double ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#species0000> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#reaction0000>\n"
                           "    semsim:hasMediatorParticipant local:MediatorParticipant0000 ;\n"
                           "    semsim:hasSinkParticipant local:SinkParticipant0000 ;\n"
                           "    semsim:hasSourceParticipant local:SourceParticipant0000 .\n"
                           "";
    ASSERT_TRUE(RDF::equals(&rdf, expected));

}


/**
 * Test creation of PhysicalProcess type of composite annotation.
 * We do so with manually created uri's for the physical process's property id
 * (ReactionProperty in this example). The process id is a cellml variable metaid and it is used
 * twice in this example.
 */
TEST_F(PhysicalProcessTests, TestPhysicalProcessCellML1) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            CellMLFactory::getCellML(CELLML_TOY_EXTENDED), false, false);

    PhysicalProcess physicalProcess = editor.newPhysicalProcess();
    physicalProcess.about("Process", LOCAL_URI)
            .addSource("entity1", LOCAL_URI, 1)
            .addSink("entity2", LOCAL_URI, 1)
            .addMediator("entity3", LOCAL_URI)
            .hasProperty("main.ReactionRate", MODEL_URI, "opb:OPB_00592");
    editor.addPhysicalProcess(physicalProcess);

    std::cout << rdf.toString() << std::endl;

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix semsim: <http://bime.uw.edu/semsim/> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:MediatorParticipant0000\n"
                           "    semsim:hasPhysicalEntityReference local:entity3 .\n"
                           "\n"
                           "local:Process\n"
                           "    semsim:hasMediatorParticipant local:MediatorParticipant0000 ;\n"
                           "    semsim:hasSinkParticipant local:SinkParticipant0000 ;\n"
                           "    semsim:hasSourceParticipant local:SourceParticipant0000 .\n"
                           "\n"
                           "local:SinkParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:double ;\n"
                           "    semsim:hasPhysicalEntityReference local:entity2 .\n"
                           "\n"
                           "local:SourceParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:double ;\n"
                           "    semsim:hasPhysicalEntityReference local:entity1 .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#main.ReactionRate>\n"
                           "    bqbiol:isPropertyOf local:Process ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_00592> .";
    ASSERT_TRUE(RDF::equals(&rdf, expected));

}

/**
 * Test creation of PhysicalProcess type of composite annotation.
 * We autogenerate
 *  1)
 */
TEST_F(PhysicalProcessTests, TestPhysicalProcessCellML2) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            CellMLFactory::getCellML(CELLML_TOY_EXTENDED), false, false);

    PhysicalProcess physicalProcess = editor.newPhysicalProcess();
    physicalProcess
            .addSource("entity1",LOCAL_URI,  1)
            .addSink("entity2", LOCAL_URI, 1)
            .addMediator("entity3", LOCAL_URI )
            .hasProperty("main.ReactionRate", MODEL_URI, "opb:OPB_00592");
    editor.addPhysicalProcess(physicalProcess);

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix semsim: <http://bime.uw.edu/semsim/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:MediatorParticipant0000\n"
                           "    semsim:hasPhysicalEntityReference local:entity3 .\n"
                           "\n"
                           "local:Process0000\n"
                           "    semsim:hasMediatorParticipant local:MediatorParticipant0000 ;\n"
                           "    semsim:hasSinkParticipant local:SinkParticipant0000 ;\n"
                           "    semsim:hasSourceParticipant local:SourceParticipant0000 .\n"
                           "\n"
                           "local:SinkParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:double ;\n"
                           "    semsim:hasPhysicalEntityReference local:entity2 .\n"
                           "\n"
                           "local:SourceParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:double ;\n"
                           "    semsim:hasPhysicalEntityReference local:entity1 .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#main.ReactionRate>\n"
                           "    bqbiol:isPropertyOf local:Process0000 ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_00592> .\n"
                           "";
    ASSERT_TRUE(RDF::equals(&rdf, expected));

}


TEST_F(PhysicalProcessTests, TestRemovePhysicalProcess) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    PhysicalProcess physicalProcess = editor.newPhysicalProcess();
    physicalProcess
            .addSource("PhysicalEntity1", MODEL_URI, 1.0)
            .addMediator("PhysicalEntity1", MODEL_URI)
            .addSink("PhysicalEntity2", MODEL_URI, 1)
            .hasProperty("OmexMetaId0004", MODEL_URI, "OPB:OPB1234");

    editor.addPhysicalProcess(physicalProcess);
    ASSERT_EQ(10, rdf.size());
    editor.removePhysicalProcess(physicalProcess);
    int expected = 0;
    int actual = rdf.size();
    ASSERT_EQ(expected, actual);
    physicalProcess.free();
}
























