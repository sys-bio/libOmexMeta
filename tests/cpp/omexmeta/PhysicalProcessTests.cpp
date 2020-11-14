//
// Created by Ciaran on 4/23/2020.
//


#include "CellMLFactory.h"
#include "OmexMetaTestUtils.h"
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
            .hasProperty("ReactionProperty", LOCAL_URI)
                .isVersionOf("opb:OPB_00592")
                .isPropertyOf("reaction0000", MODEL_URI);
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
                           "local:ReactionProperty\n"
                           "    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#reaction0000> ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_00592> .\n"
                           "\n"
                           "local:SinkParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#species0001> .\n"
                           "\n"
                           "local:SourceParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
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
            .hasProperty()
                .isVersionOf("opb:OPB_00592");
//                .isPropertyOf("reaction0000", MODEL_URI);
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
                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#species0001> .\n"
                           "\n"
                           "local:SourceParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
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
    physicalProcess.about("main.ReactionRate", MODEL_URI)
            .addSource("entity1", LOCAL_URI, 1)
            .addSink("entity2", LOCAL_URI, 1)
            .addMediator("entity3", LOCAL_URI)
            .hasProperty("main.Volume", MODEL_URI)
                .isVersionOf("opb:OPB_00592")
                .isPropertyOf("main.ReactionRate", MODEL_URI);
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
                           "local:SinkParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
                           "    semsim:hasPhysicalEntityReference local:entity2 .\n"
                           "\n"
                           "local:SourceParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
                           "    semsim:hasPhysicalEntityReference local:entity1 .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#main.ReactionRate>\n"
                           "    semsim:hasMediatorParticipant local:MediatorParticipant0000 ;\n"
                           "    semsim:hasSinkParticipant local:SinkParticipant0000 ;\n"
                           "    semsim:hasSourceParticipant local:SourceParticipant0000 .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#main.Volume>\n"
                           "    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#main.ReactionRate> ;\n"
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
            .hasProperty("main.Volume", MODEL_URI)
                .isVersionOf("opb:OPB_00592");
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
                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
                           "    semsim:hasPhysicalEntityReference local:entity2 .\n"
                           "\n"
                           "local:SourceParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
                           "    semsim:hasPhysicalEntityReference local:entity1 .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#main.Volume>\n"
                           "    bqbiol:isPropertyOf local:Process0000 ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_00592> .\n"
                           "";
    ASSERT_TRUE(RDF::equals(&rdf, expected));

}


//
//TEST_F(PhysicalProcessTests, TestPhysicalProcessBuilder2) {
//    RDF rdf;
//    Editor editor = rdf.toEditor(
//            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);
//
//    PhysicalProcess physicalProcess = editor.newPhysicalProcess();
//    physicalProcess
//            .about("reaction0001")
//            .variableMetaId("cmeta:id=...")// point 1
////            .isVersionOf("OPB:OPB1234")
//            .addSource(1.0, "PhysicalEntity1")
//            .addSink(1.0, "PhysicalEntity2")
//            .addMediator("PhysicalEntity3");
//
//    editor.addPhysicalProcess(physicalProcess);
//
//    std::cout << rdf.toString() << std::endl;
//
//    /*
//     * In cellml, for PhysicalProcess you would not use the local:ProcessProperty id
//     * but instead the metaid to the variable in the cellml source code.
//     *
//variableMetaID:
//    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.rdf#reaction0001> ; // optional id argument. User is expected to provide this by doesn't have to as we'll generate for them if not.
//    bqbiol:isVersionOf <https://identifiers.org/OPB:OPB1234> .
//
//     */
//
//    int expected = 10;
//    int actual = rdf.size();
//    ASSERT_EQ(expected, actual);
//}
//
//TEST_F(PhysicalProcessTests, TestPhysicalProcessBuilderWithAbout) {
//    RDF rdf;
//    Editor editor = rdf.toEditor(
//            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);
//
//    PhysicalProcess physicalProcess = editor.newPhysicalProcess();
//    physicalProcess
//            .about("reaction0001")
//            //            .variableMetaId("cmeta:id=...")// point 1
////            .isVersionOf("OPB:OPB1234")
//            .addSource(1.0, "PhysicalEntity1")
//            .addSink(1.0, "PhysicalEntity2")
//            .addMediator("PhysicalEntity3");
//    editor.addPhysicalProcess(physicalProcess);
//
//    std::cout << rdf.toString() << std::endl;
//
//    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
//                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
//                           "@prefix semsim: <http://bime.uw.edu/semsim/> .\n"
//                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
//                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
//                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
//                           "\n"
//                           "local:MediatorParticipant0000\n"
//                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#PhysicalEntity3> .\n"
//                           "\n"
//                           "local:ProcessProperty0000\n"
//                           "    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#reaction0001> ;\n"
//                           "    bqbiol:isVersionOf <https://identifiers.org/OPB:OPB1234> .\n"
//                           "\n"
//                           "local:SinkParticipant0000\n"
//                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
//                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#PhysicalEntity2> .\n"
//                           "\n"
//                           "local:SourceParticipant0000\n"
//                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
//                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#PhysicalEntity1> .\n"
//                           "\n"
//                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#reaction0001>\n"
//                           "    semsim:hasMediatorParticipant local:MediatorParticipant0000 ;\n"
//                           "    semsim:hasSinkParticipant local:SinkParticipant0000 ;\n"
//                           "    semsim:hasSourceParticipant local:SourceParticipant0000 .\n"
//                           "";
//    ASSERT_TRUE(RDF::equals(&rdf, expected));
//    /*
//     * In cellml, for PhysicalProcess you would not use the local:ProcessProperty id
//     * but instead the metaid to the variable in the cellml source code.
//     *
//variableMetaID:
//    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.rdf#reaction0001> ; // optional id argument. User is expected to provide this by doesn't have to as we'll generate for them if not.
//    bqbiol:isVersionOf <https://identifiers.org/OPB:OPB1234> .
//
//     */
//}
//
//TEST_F(PhysicalProcessTests, TestPhysicalProcessBuilderWithoutAbout) {
//    RDF rdf;
//    Editor editor = rdf.toEditor(
//            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);
//
//    PhysicalProcess physicalProcess = editor.newPhysicalProcess();
//    physicalProcess
//            //            .about("reaction0001")
//            //            .variableMetaId("cmeta:id=...")// point 1
////            .isVersionOf("OPB:OPB1234")
//            .addSource(1.0, "PhysicalEntity1")
//            .addSink(1.0, "PhysicalEntity2")
//            .addMediator("PhysicalEntity3");
//    editor.addPhysicalProcess(physicalProcess);
//
//    std::cout << rdf.toString() << std::endl;
//
//    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
//                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
//                           "@prefix semsim: <http://bime.uw.edu/semsim/> .\n"
//                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
//                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
//                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
//                           "\n"
//                           "local:MediatorParticipant0000\n"
//                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#PhysicalEntity3> .\n"
//                           "\n"
//                           "local:ProcessProperty0000\n"
//                           "    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.rdf#Process0000> ;\n"
//                           "    bqbiol:isVersionOf <https://identifiers.org/OPB:OPB1234> .\n"
//                           "\n"
//                           "local:SinkParticipant0000\n"
//                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
//                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#PhysicalEntity2> .\n"
//                           "\n"
//                           "local:SourceParticipant0000\n"
//                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
//                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#PhysicalEntity1> .\n"
//                           "\n"
//                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#Process0000>\n"
//                           "    semsim:hasMediatorParticipant local:MediatorParticipant0000 ;\n"
//                           "    semsim:hasSinkParticipant local:SinkParticipant0000 ;\n"
//                           "    semsim:hasSourceParticipant local:SourceParticipant0000 .\n"
//                           "";
//    ASSERT_TRUE(RDF::equals(&rdf, expected));
//    /*
//     * In cellml, for PhysicalProcess you would not use the local:ProcessProperty id
//     * but instead the metaid to the variable in the cellml source code.
//     *
//variableMetaID:
//    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.rdf#reaction0001> ; // optional id argument. User is expected to provide this by doesn't have to as we'll generate for them if not.
//    bqbiol:isVersionOf <https://identifiers.org/OPB:OPB1234> .
//
//     */
//}
//
//TEST_F(PhysicalProcessTests, TestPhysicalProcessBuilderWithVariableMetaId) {
//    RDF rdf;
//    Editor editor = rdf.toEditor(
//            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);
//
//    PhysicalProcess physicalProcess = editor.newPhysicalProcess();
//    physicalProcess
//            //            .about("reaction0001")
//            .variableMetaId("AnExistingCellMLVariable")// point 1
////            .isVersionOf("OPB:OPB1234")
//            .addSource(1.0, "PhysicalEntity1")
//            .addSink(1.0, "PhysicalEntity2")
//            .addMediator("PhysicalEntity3");
//    editor.addPhysicalProcess(physicalProcess);
//
//    std::cout << rdf.toString() << std::endl;
//
//    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
//                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
//                           "@prefix semsim: <http://bime.uw.edu/semsim/> .\n"
//                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
//                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
//                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
//                           "\n"
//                           "local:MediatorParticipant0000\n"
//                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#PhysicalEntity3> .\n"
//                           "\n"
//                           "local:AnExistingCellMLVariable\n"
//                           "    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.rdf#Process0000> ;\n"
//                           "    bqbiol:isVersionOf <https://identifiers.org/OPB:OPB1234> .\n"
//                           "\n"
//                           "local:SinkParticipant0000\n"
//                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
//                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#PhysicalEntity2> .\n"
//                           "\n"
//                           "local:SourceParticipant0000\n"
//                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
//                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#PhysicalEntity1> .\n"
//                           "\n"
//                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#Process0000>\n"
//                           "    semsim:hasMediatorParticipant local:MediatorParticipant0000 ;\n"
//                           "    semsim:hasSinkParticipant local:SinkParticipant0000 ;\n"
//                           "    semsim:hasSourceParticipant local:SourceParticipant0000 .\n"
//                           "";
//    ASSERT_TRUE(RDF::equals(&rdf, expected));
//    /*
//     * In cellml, for PhysicalProcess you would not use the local:ProcessProperty id
//     * but instead the metaid to the variable in the cellml source code.
//     *
//variableMetaID:
//    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.rdf#reaction0001> ; // optional id argument. User is expected to provide this by doesn't have to as we'll generate for them if not.
//    bqbiol:isVersionOf <https://identifiers.org/OPB:OPB1234> .
//
//     */
//}



//TEST_F(EditorTests, TestPhysicalProcessBuilder) {
//    RDF rdf;
//    Editor editor = rdf.toEditor(
//            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);
//
//    PhysicalProcess physicalProcess = editor.newPhysicalProcess();
//    physicalProcess
//            .about("reaction0001")
//            .variableMetaId("cmeta:id=...")// point 1
//            .isVersionOf("OPB:OPB1234")
//            .addSource(1.0, "PhysicalEntity1")
//            .addSink(1.0, "PhysicalEntity2")
//            .addMediator("PhysicalEntity3");
//
//    editor.addPhysicalProcess(physicalProcess);
//
//    std::cout << rdf.toString() << std::endl;
//
//    /*
//     * In cellml, for PhysicalProcess you would not use the local:ProcessProperty id
//     * but instead the metaid to the variable in the cellml source code.
//     *
//variableMetaID:
//    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.rdf#reaction0001> ; // optional id argument. User is expected to provide this by doesn't have to as we'll generate for them if not.
//    bqbiol:isVersionOf <https://identifiers.org/OPB:OPB1234> .
//
//     */
//
//    int expected = 10;
//    int actual = rdf.size();
//    ASSERT_EQ(expected, actual);
//}
//
//TEST_F(EditorTests, TestPhysicalProcessBuilderWithAbout) {
//    RDF rdf;
//    Editor editor = rdf.toEditor(
//            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);
//
//    PhysicalProcess physicalProcess = editor.newPhysicalProcess();
//    physicalProcess
//            .about("reaction0001")
//            //            .variableMetaId("cmeta:id=...")// point 1
//            .isVersionOf("OPB:OPB1234")
//            .addSource(1.0, "PhysicalEntity1")
//            .addSink(1.0, "PhysicalEntity2")
//            .addMediator("PhysicalEntity3");
//    editor.addPhysicalProcess(physicalProcess);
//
//    std::cout << rdf.toString() << std::endl;
//
//    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
//                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
//                           "@prefix semsim: <http://bime.uw.edu/semsim/> .\n"
//                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
//                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
//                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
//                           "\n"
//                           "local:MediatorParticipant0000\n"
//                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#PhysicalEntity3> .\n"
//                           "\n"
//                           "local:ProcessProperty0000\n"
//                           "    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#reaction0001> ;\n"
//                           "    bqbiol:isVersionOf <https://identifiers.org/OPB:OPB1234> .\n"
//                           "\n"
//                           "local:SinkParticipant0000\n"
//                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
//                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#PhysicalEntity2> .\n"
//                           "\n"
//                           "local:SourceParticipant0000\n"
//                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
//                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#PhysicalEntity1> .\n"
//                           "\n"
//                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#reaction0001>\n"
//                           "    semsim:hasMediatorParticipant local:MediatorParticipant0000 ;\n"
//                           "    semsim:hasSinkParticipant local:SinkParticipant0000 ;\n"
//                           "    semsim:hasSourceParticipant local:SourceParticipant0000 .\n"
//                           "";
//    ASSERT_TRUE(RDF::equals(&rdf, expected));
//    /*
//     * In cellml, for PhysicalProcess you would not use the local:ProcessProperty id
//     * but instead the metaid to the variable in the cellml source code.
//     *
//variableMetaID:
//    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.rdf#reaction0001> ; // optional id argument. User is expected to provide this by doesn't have to as we'll generate for them if not.
//    bqbiol:isVersionOf <https://identifiers.org/OPB:OPB1234> .
//
//     */
//}
//
//TEST_F(EditorTests, TestPhysicalProcessBuilderWithoutAbout) {
//    RDF rdf;
//    Editor editor = rdf.toEditor(
//            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);
//
//    PhysicalProcess physicalProcess = editor.newPhysicalProcess();
//    physicalProcess
//            //            .about("reaction0001")
//            //            .variableMetaId("cmeta:id=...")// point 1
//            .isVersionOf("OPB:OPB1234")
//            .addSource(1.0, "PhysicalEntity1")
//            .addSink(1.0, "PhysicalEntity2")
//            .addMediator("PhysicalEntity3");
//    editor.addPhysicalProcess(physicalProcess);
//
//    std::cout << rdf.toString() << std::endl;
//
//    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
//                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
//                           "@prefix semsim: <http://bime.uw.edu/semsim/> .\n"
//                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
//                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
//                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
//                           "\n"
//                           "local:MediatorParticipant0000\n"
//                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#PhysicalEntity3> .\n"
//                           "\n"
//                           "local:ProcessProperty0000\n"
//                           "    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.rdf#Process0000> ;\n"
//                           "    bqbiol:isVersionOf <https://identifiers.org/OPB:OPB1234> .\n"
//                           "\n"
//                           "local:SinkParticipant0000\n"
//                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
//                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#PhysicalEntity2> .\n"
//                           "\n"
//                           "local:SourceParticipant0000\n"
//                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
//                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#PhysicalEntity1> .\n"
//                           "\n"
//                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#Process0000>\n"
//                           "    semsim:hasMediatorParticipant local:MediatorParticipant0000 ;\n"
//                           "    semsim:hasSinkParticipant local:SinkParticipant0000 ;\n"
//                           "    semsim:hasSourceParticipant local:SourceParticipant0000 .\n"
//                           "";
//    ASSERT_TRUE(RDF::equals(&rdf, expected));
//    /*
//     * In cellml, for PhysicalProcess you would not use the local:ProcessProperty id
//     * but instead the metaid to the variable in the cellml source code.
//     *
//variableMetaID:
//    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.rdf#reaction0001> ; // optional id argument. User is expected to provide this by doesn't have to as we'll generate for them if not.
//    bqbiol:isVersionOf <https://identifiers.org/OPB:OPB1234> .
//
//     */
//}
//
//TEST_F(EditorTests, TestPhysicalProcessBuilderWithVariableMetaId) {
//    RDF rdf;
//    Editor editor = rdf.toEditor(
//            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);
//
//    PhysicalProcess physicalProcess = editor.newPhysicalProcess();
//    physicalProcess
//            //            .about("reaction0001")
//            .variableMetaId("AnExistingCellMLVariable")// point 1
//            .isVersionOf("OPB:OPB1234")
//            .addSource(1.0, "PhysicalEntity1")
//            .addSink(1.0, "PhysicalEntity2")
//            .addMediator("PhysicalEntity3");
//    editor.addPhysicalProcess(physicalProcess);
//
//    std::cout << rdf.toString() << std::endl;
//
//    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
//                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
//                           "@prefix semsim: <http://bime.uw.edu/semsim/> .\n"
//                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
//                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
//                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
//                           "\n"
//                           "local:MediatorParticipant0000\n"
//                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#PhysicalEntity3> .\n"
//                           "\n"
//                           "local:AnExistingCellMLVariable\n"
//                           "    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.rdf#Process0000> ;\n"
//                           "    bqbiol:isVersionOf <https://identifiers.org/OPB:OPB1234> .\n"
//                           "\n"
//                           "local:SinkParticipant0000\n"
//                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
//                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#PhysicalEntity2> .\n"
//                           "\n"
//                           "local:SourceParticipant0000\n"
//                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
//                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#PhysicalEntity1> .\n"
//                           "\n"
//                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#Process0000>\n"
//                           "    semsim:hasMediatorParticipant local:MediatorParticipant0000 ;\n"
//                           "    semsim:hasSinkParticipant local:SinkParticipant0000 ;\n"
//                           "    semsim:hasSourceParticipant local:SourceParticipant0000 .\n"
//                           "";
//    ASSERT_TRUE(RDF::equals(&rdf, expected));
//    /*
//     * In cellml, for PhysicalProcess you would not use the local:ProcessProperty id
//     * but instead the metaid to the variable in the cellml source code.
//     *
//variableMetaID:
//    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.rdf#reaction0001> ; // optional id argument. User is expected to provide this by doesn't have to as we'll generate for them if not.
//    bqbiol:isVersionOf <https://identifiers.org/OPB:OPB1234> .
//
//     */
//}




//TEST_F(PhysicalProcessTests, TestEquality) {
//    PhysicalProcess process1(model.get());
//    process1.setModelUri(model_uri);
//    process1.setLocalUri(local_uri);
//    process1.setPhysicalProperty("property_metaid_0", "opb:OPB_00592")
//            .addSource(1.0, "species_metaid0")
//            .addSource(2.0, "species_metaid1")
//            .addSink(1.0, "species_metaid2")
//            .addMediator("species_metaid2");
//
//    PhysicalProcess process2(model.get());
//    process2.setModelUri(model_uri);
//    process2.setLocalUri(local_uri);
//    process2.setPhysicalProperty("property_metaid_0", "opb:OPB_00592")
//            .addSource(1.0, "species_metaid0")
//            .addSource(2.0, "species_metaid1")
//            .addSink(1.0, "species_metaid2")
//            .addMediator("species_metaid2");
//    ASSERT_EQ(process1, process2);
//    process1.free();
//    process2.free();
//}
//
//TEST_F(PhysicalProcessTests, TestInequality) {
//    PhysicalProcess process1(model.get());
//    process1.setModelUri(model_uri);
//    process1.setLocalUri(local_uri);
//    process1.setPhysicalProperty("property_metaid_1", "opb:OPB_00592")
//            .addSource(1.0, "species_metaid0")
//            .addSource(2.0, "species_metaid1")
//            .addSink(1.0, "species_metaid2")
//            .addMediator("species_metaid2");
//
//    PhysicalProcess process2(model.get());
//    process2.setModelUri(model_uri);
//    process2.setLocalUri(local_uri);
//    process2.setPhysicalProperty("property_metaid_0", "opb:OPB_00592")
//            .addSource(1.0, "species_metaid0")
//            .addSource(2.0, "species_metaid1")
//            .addSink(1.0, "species_metaid2")
//            .addMediator("species_metaid2");
//    ASSERT_NE(process1, process2);
//
//    process1.free();
//    process2.free();
//}












//class PhysicalProcessTests : public ::testing::Test {
//
//public:
//
//    LibrdfStorage storage;
//    LibrdfModel model;
//    std::string model_uri = "http://omex-library.org/NewOmex.omex/NewModel.xml#";
//    std::string local_uri = "http://omex-library.org/NewOmex.omex/NewModel.rdf#";
//
//    PhysicalProperty physical_property;
//
//    PhysicalProcessTests() {
//        model = LibrdfModel(storage.get());
//
//        physical_property = PhysicalProperty("metaid", "OPB:OPB_00340", model_uri);
//    };
//
//
//    ~PhysicalProcessTests() override {
//        model.freeModel();
//        storage.freeStorage();
//    };
//};
//
//TEST_F(PhysicalProcessTests, TestPhysicalProcessSubjectMetaidNode) {
//    Subject subject_metaid = Subject::fromRawPtr(LibrdfNode::fromUriString("MetaId004").get());
//    std::vector <SourceParticipant> source_participants(
//            {SourceParticipant(
//                    model.get(),
//                    1.0,
//                    "#PhysicalEntityReference1", model_uri, local_uri
//            )}
//    );
//    std::vector <SinkParticipant> sink_participants(
//            {SinkParticipant(
//                    model.get(),
//                    1.0,
//                    "PhysicalEntityReference2", model_uri, local_uri
//            )}
//    );
//    std::vector <MediatorParticipant> mediator_participants(
//            {MediatorParticipant(
//                    model.get(),
//                    "PhysicalEntityReference3", model_uri, local_uri
//            )}
//    );
//
//    PhysicalProcess process(
//            model.get(),
//            model_uri,
//            local_uri,
//            physical_property,
//            source_participants,
//            sink_participants,
//            mediator_participants
//    );
//
//    std::string actual = process.getSubjectStr();
//    std::string expected = "http://omex-library.org/NewOmex.omex/NewModel.xml#metaid";
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//
//    // Without Triple we need to free stuff manually
//    //physical_property.free();
//    subject_metaid.free();
//    source_participants[0].free();
//    sink_participants[0].free();
//    mediator_participants[0].free();
//}
//
//
//TEST_F(PhysicalProcessTests, TestPhysicalProcessSource) {
//    std::vector <SourceParticipant> source_participants(
//            {SourceParticipant(
//                    model.get(),
//                    1.0,
//                    "#PhysicalEntityReference1", model_uri, local_uri
//            )}
//    );
//    std::vector <SinkParticipant> sink_participants(
//            {SinkParticipant(
//                    model.get(),
//                    1.0,
//                    "PhysicalEntityReference2", model_uri, local_uri
//            )}
//    );
//    std::vector <MediatorParticipant> mediator_participants(
//            {MediatorParticipant(
//                    model.get(),
//                    "PhysicalEntityReference3", model_uri, local_uri
//            )}
//    );
//
//    PhysicalProcess process(
//            model.get(),
//            model_uri,
//            local_uri,
//            physical_property,
//            source_participants,
//            sink_participants,
//            mediator_participants
//    );
//
//    std::string actual = process.getSources()[0].getSubject();
//    std::string expected = "SourceParticipant";
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//
//    // Without Triple we need to free stuff manually
//    //physical_property.free();
//    source_participants[0].free();
//    sink_participants[0].free();
//    mediator_participants[0].free();
//}
//
//
//TEST_F(PhysicalProcessTests, TestPhysicalProcessNumTriples) {
//    PhysicalProcess process(
//            model.get(),
//            model_uri,
//            local_uri,
//            physical_property,
//            std::vector<SourceParticipant>(
//                    {SourceParticipant(
//                            model.get(),
//                            1.0,
//                            "#PhysicalEntityReference1", model_uri, local_uri
//                    )}
//            ),
//            std::vector<SinkParticipant>(
//                    {SinkParticipant(
//
//                            model.get(),
//                            1.0,
//                            "PhysicalEntityReference2", model_uri, local_uri
//                    )}
//            ),
//            std::vector<MediatorParticipant>(
//                    {MediatorParticipant(
//
//                            model.get(),
//                            "PhysicalEntityReference3", model_uri, local_uri
//                    )}
//            )
//    );
//
//    Triples triples = process.toTriples();
//    std::cout << triples.str() << std::endl;
//    int expected = 10;
//    int actual = triples.size();
//    ASSERT_EQ(expected, actual);
//    triples.freeTriples();
//
//}
//
//
//TEST_F(PhysicalProcessTests, TestPhysicalProcessTrips) {
//    PhysicalProcess process(
//            model.get(),
//            model_uri,
//            local_uri,
//            physical_property,
//            std::vector<SourceParticipant>(
//                    {SourceParticipant(
//                            model.get(),
//                            1.0,
//                            "#PhysicalEntityReference1", model_uri, local_uri
//                    )}
//            ),
//            std::vector<SinkParticipant>(
//                    {SinkParticipant(
//                            model.get(),
//                            1.0,
//                            "PhysicalEntityReference2", model_uri, local_uri
//                    )}
//            ),
//            std::vector<MediatorParticipant>(
//                    {MediatorParticipant(
//
//                            model.get(),
//                            "PhysicalEntityReference3", model_uri, local_uri
//                    )}
//            )
//    );
//    Triples triples = process.toTriples();
//
//    int expected = 10;
//    int actual = triples.size();
//    ASSERT_EQ(expected, actual);
//    triples.freeTriples();
//}

//TEST_F(PhysicalProcessTests, TestPhysicalProcessBuilder1) {
//    PhysicalProcess process(model.get());
//    process.setModelUri(model_uri);
//    process.setLocalUri(local_uri);
//    process.about("process_metaid_0")
//            .isVersionOf("opb:OPB_00592")
//            .isVersionOf("GO:12345")
//            .addSource(1.0, "species_metaid0")
//            .addSource(2.0, "species_metaid1")
//            .addSink(1.0, "species_metaid2")
//            .addMediator("species_metaid2");
//
//    Triples triples = process.toTriples();
//
//    std::cout << triples.str() << std::endl;
//
//    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
//                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
//                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
//                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
//                           "\n"
//                           "local:MediatorParticipant0000\n"
//                           "    <http://bime.uw.edu/semsim/hasPhysicalEntityReference> <http://omex-library.org/NewOmex.omex/NewModel.xml#species_metaid2> .\n"
//                           "\n"
//                           "local:ProcessProperty0000\n"
//                           "    <http://biomodels.net/biology-qualifiers/isPropertyOf> <http://omex-library.org/NewOmex.omex/NewModel.xml#process_metaid_0> ;\n"
//                           "    <http://biomodels.net/biology-qualifiers/isVersionOf> <https://identifiers.org/opb:OPB_00592> .\n"
//                           "\n"
//                           "local:SinkParticipant0000\n"
//                           "    <http://bime.uw.edu/semsim/hasMultiplier> \"1\"^^rdf:int ;\n"
//                           "    <http://bime.uw.edu/semsim/hasPhysicalEntityReference> <http://omex-library.org/NewOmex.omex/NewModel.xml#species_metaid2> .\n"
//                           "\n"
//                           "local:SourceParticipant0000\n"
//                           "    <http://bime.uw.edu/semsim/hasMultiplier> \"1\"^^rdf:int ;\n"
//                           "    <http://bime.uw.edu/semsim/hasPhysicalEntityReference> <http://omex-library.org/NewOmex.omex/NewModel.xml#species_metaid0> .\n"
//                           "\n"
//                           "local:SourceParticipant0001\n"
//                           "    <http://bime.uw.edu/semsim/hasMultiplier> \"2\"^^rdf:int ;\n"
//                           "    <http://bime.uw.edu/semsim/hasPhysicalEntityReference> <http://omex-library.org/NewOmex.omex/NewModel.xml#species_metaid1> .\n"
//                           "\n"
//                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#process_metaid_0>\n"
//                           "    <http://bime.uw.edu/semsim/hasMediatorParticipant> local:MediatorParticipant0000 ;\n"
//                           "    <http://bime.uw.edu/semsim/hasSinkParticipant> local:SinkParticipant0000 ;\n"
//                           "    <http://bime.uw.edu/semsim/hasSourceParticipant> local:SourceParticipant0000, local:SourceParticipant0001 ;\n"
//                           "    <http://biomodels.net/biology-qualifiers/isVersionOf> <https://identifiers.org/GO:12345> .\n"
//                           "\n"
//                           "\n"
//                           "D:\\libOmexMeta\\tests\\cpp\\omexmeta\\PhysicalProcessTests.cpp(257): error: Value of: OmexMetaTestUtils::equals(triples, expected)\n"
//                           "  Actual: false\n"
//                           "Expected: true";
//
//    ASSERT_TRUE(OmexMetaTestUtils::equals(triples, expected));
//
//    // remember to free the unused physical property from test fixture
//    triples.freeTriples();
//}

