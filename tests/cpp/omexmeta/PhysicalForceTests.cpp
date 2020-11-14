
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
    PhysicalForce.about("EnergyDiff_0", MODEL_URI)
            .addSource("source_23", MODEL_URI, 1)
            .addSink("sink_12",MODEL_URI,  1)
            .hasProperty("parameter_metaid_0", LOCAL_URI)
                .isVersionOf("opb:OPB_01058")
                .isPropertyOf("EnergyDiff_0", MODEL_URI);
    editor.addPhysicalForce(PhysicalForce);

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix semsim: <http://bime.uw.edu/semsim/> .\n"
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
                           "local:parameter_metaid_0\n"
                           "    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#EnergyDiff_0> ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_01058> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#EnergyDiff_0>\n"
                           "    semsim:hasSinkParticipant local:SinkParticipant0000 ;\n"
                           "    semsim:hasSourceParticipant local:SourceParticipant0000 .";
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
    PhysicalForce.about("EnergyDiff_0", MODEL_URI)
            .addSource("source_23", MODEL_URI, 1)
            .addSink("sink_12", MODEL_URI, 1)
            .hasProperty()
                .isVersionOf("opb:OPB_01058")
                .isPropertyOf("EnergyDiff_0", MODEL_URI);
    editor.addPhysicalForce(PhysicalForce);

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix semsim: <http://bime.uw.edu/semsim/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:ForceProperty0000\n"
                           "    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#EnergyDiff_0> ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_01058> .\n"
                           "\n"
                           "local:SinkParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#sink_12> .\n"
                           "\n"
                           "local:SourceParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#source_23> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#EnergyDiff_0>\n"
                           "    semsim:hasSinkParticipant local:SinkParticipant0000 ;\n"
                           "    semsim:hasSourceParticipant local:SourceParticipant0000 .";
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
    PhysicalForce.about("main.MembraneVoltage", MODEL_URI)
            .addSource("entity1", LOCAL_URI, 1)
            .addSink("entity2", LOCAL_URI, 1)
            .hasProperty("ForceProperty", MODEL_URI)
                .isVersionOf("opb:OPB_00592")
                .isPropertyOf("main.MembraneVoltage", MODEL_URI);
    editor.addPhysicalForce(PhysicalForce);

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix semsim: <http://bime.uw.edu/semsim/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#ForceProperty>\n"
                           "    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#main.MembraneVoltage> ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_00592> .\n"
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
                           "    semsim:hasSinkParticipant local:SinkParticipant0000 ;\n"
                           "    semsim:hasSourceParticipant local:SourceParticipant0000 .";
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

    PhysicalForce PhysicalForce = editor.newPhysicalForce();
    PhysicalForce.about("main.MembraneVoltage", MODEL_URI)
            .addSource("entity1", LOCAL_URI, 1)
            .addSink("entity2", LOCAL_URI, 1)
            .hasProperty()
                .isVersionOf("opb:OPB_00592");
    editor.addPhysicalForce(PhysicalForce);
   std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix semsim: <http://bime.uw.edu/semsim/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:ForceProperty0000\n"
                           "    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#main.MembraneVoltage> ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_00592> .\n"
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
                           "    semsim:hasSinkParticipant local:SinkParticipant0000 ;\n"
                           "    semsim:hasSourceParticipant local:SourceParticipant0000 .";
    ASSERT_TRUE(RDF::equals(&rdf, expected));

}

//TEST_F(EditorTests, TestRemovePhysicalForce) {
//    RDF rdf;
//    Editor editor = rdf.toEditor(
//            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);
//
//    PhysicalForce physicalForce = editor.newPhysicalForce();
//    physicalForce
//            .setPhysicalProperty("#OmexMetaId0002", "OPB:OPB1234")
//            .addSource("PhysicalEntity1", 1.0)
//            .addSink(1.0, "PhysicalEntity2");
//    editor.addPhysicalForce(physicalForce);
//    ASSERT_EQ(8, rdf.size());
//    editor.removePhysicalForce(physicalForce);
//    int expected = 0;
//    int actual = rdf.size();
//    ASSERT_EQ(expected, actual);
//}


//#include "omexmeta/RDF.h"
//#include <vector>
//#include "gtest/gtest.h"
//#include "librdf.h"
//#include "omexmeta/PhysicalForce.h"
//#include "omexmeta/Participant.h"
//#include "omexmeta/OmexMetaUtils.h"
//#include "OmexMetaTestUtils.h"
//
//using namespace omexmeta;
//
//class PhysicalForceTests : public ::testing::Test {
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
//    PhysicalForceTests() {
//        model = LibrdfModel(storage.get());
//        physical_property = PhysicalProperty("metaid", "OPB:OPB_00340", model_uri);
//    };
//
//    ~PhysicalForceTests() override {
//        model.freeModel();
//        storage.freeStorage();
//    };
//};
//
//
//TEST_F(PhysicalForceTests, TestPhysicalForceSubjectMetaidNode) {
//    Subject subject_metaid = Subject::fromRawPtr(LibrdfNode::fromUriString("MetaId004").get());
//    std::vector<SourceParticipant> source_participants(
//            {SourceParticipant(
//                    model.get(),
//                    1.0,
//                    "#PhysicalEntityReference1",
//                    model_uri, local_uri
//            )}
//    );
//    std::vector<SinkParticipant> sink_participants(
//            {SinkParticipant(
//                    model.get(),
//                    1.0,
//                    "PhysicalEntityReference2", model_uri, local_uri
//            )}
//    );
//    std::vector<MediatorParticipant> mediator_participants(
//            {MediatorParticipant(
//                    model.get(),
//                    "PhysicalEntityReference3", model_uri, local_uri
//            )}
//    );
//
//    PhysicalForce force(
//            model.get(),
//            model_uri,
//            local_uri,physical_property,
//            source_participants,
//            sink_participants
//    );
//    std::string actual = force.getSubjectStr();
//    std::string expected = "http://omex-library.org/NewOmex.omex/NewModel.xml#metaid";
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//
//    // Without Triple we need to free stuff manually
////    physical_property.free();
//    subject_metaid.free();
//    source_participants[0].free();
//    sink_participants[0].free();
//    mediator_participants[0].free();
//
//}
//
//
//TEST_F(PhysicalForceTests, TestPhysicalProperty1) {
//    std::vector<SourceParticipant> source_participants({SourceParticipant(
//            model.get(),
//            1.0,
//            "#PhysicalEntityReference1", model_uri, local_uri
//    )});
//    std::vector<SinkParticipant> sink_participants(
//            {SinkParticipant(
//                    model.get(),
//                    1.0,
//                    "PhysicalEntityReference2", model_uri, local_uri
//            )}
//    );
//
//
//    PhysicalForce force(
//            model.get(),
//            model_uri,
//            local_uri,physical_property,
//            source_participants,
//            sink_participants
//    );
//    std::string actual = force.getPhysicalProperty().getIsVersionOfValue();
//    std::string expected = "OPB:OPB_00340";
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//
//    // Without Triple we need to free stuff manually
//    force.free();
//
//}
//
//TEST_F(PhysicalForceTests, TestPhysicalProperty2) {
//    std::vector<SourceParticipant> source_participants({SourceParticipant(
//            model.get(),
//            1.0,
//            "#PhysicalEntityReference1", model_uri, local_uri
//    )});
//    std::vector<SinkParticipant> sink_participants(
//            {SinkParticipant(
//                    model.get(),
//                    1.0,
//                    "PhysicalEntityReference2", model_uri, local_uri
//            )}
//    );
//
//    PhysicalForce force(
//            model.get(),
//            model_uri,
//            local_uri,physical_property,
//            source_participants,
//            sink_participants
//    );
//    std::string actual = force.getPhysicalProperty().getAbout();
//    std::string expected = "http://omex-library.org/NewOmex.omex/NewModel.xml#metaid";
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//
//    // Without Triple we need to free stuff manually
//    force.free();
//
//}
//
//
//TEST_F(PhysicalForceTests, TestPhysicalForceNumTriples) {
//    PhysicalForce force(
//            model.get(),
//            model_uri,
//            local_uri,physical_property,
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
//            )
//    );
//
//    Triples triples = force.toTriples();
//    int expected = 8;
//    int actual = triples.size();
//    ASSERT_EQ(expected, actual
//    );
//    triples.freeTriples();
//}
//
//
//TEST_F(PhysicalForceTests, TestPhysicalForceTrips) {
//    PhysicalForce force(
//            model.get(),
//            model_uri,
//            local_uri,physical_property,
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
//            )
//    );
//
//    Triples triples = force.toTriples();
//    int expected = 8;
//    int actual = triples.size();
//    ASSERT_EQ(expected, actual);
//    triples.freeTriples();
//}
//
//
//
//TEST(PhysicalForceTestsNoFixture, TestPhysicalForceBuilder) {
//    std::string local_uri = "http://omex-library.org/NewOmex.omex/NewModel.rdf#";
//    std::string model_uri = "http://omex-library.org/NewOmex.omex/NewModel.xml#";
//    RDF rdf;
//    PhysicalForce force(rdf.getModel());
//    force.setModelUri(model_uri);
//    force.setLocalUri(local_uri);
//    //todo considering implementing the builder as a composite builder
//    force.about("Force5")
//            .isVersionOf("OPB:OPB_00340")
//            .addSource(1, "#PhysicalEntityReference1")
//            .addSink(2, "PhysicalEntityReference2")
//            .addSink(1, "PhysicalEntityReference3");
//    Triples triples = force.toTriples();
//    std::string actual = triples.str("turtle");
//    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
//                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
//                           "@prefix semsim: <http://bime.uw.edu/semsim/> .\n"
//                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
//                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
//                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
//                           "\n"
//                           "local:ForceProperty0000\n"
//                           "    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#Force5> ;\n"
//                           "    bqbiol:isVersionOf <https://identifiers.org/OPB:OPB_00340> .\n"
//                           "\n"
//                           "local:SinkParticipant0000\n"
//                           "    semsim:hasMultiplier \"2\"^^rdf:int ;\n"
//                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#PhysicalEntityReference2> .\n"
//                           "\n"
//                           "local:SinkParticipant0001\n"
//                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
//                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#PhysicalEntityReference3> .\n"
//                           "\n"
//                           "local:SourceParticipant0000\n"
//                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
//                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#PhysicalEntityReference1> .\n"
//                           "\n"
//                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#Force5>\n"
//                           "    semsim:hasSinkParticipant local:SinkParticipant0000, local:SinkParticipant0001 ;\n"
//                           "    semsim:hasSourceParticipant local:SourceParticipant0000 .";
//    std::cout << actual << std::endl;
//    ASSERT_TRUE(OmexMetaTestUtils::equals(triples, expected));
//    triples.freeTriples();
//}
//
//
//TEST(PhysicalForceTestsNoFixture, TestGenerateTheSamePhysicalForceTwice) {
//    std::string model_uri = "http://omex-library.org/myomex.omex/mymodel.xml#";
//    std::string local_uri = "http://omex-library.org/myomex.omex/mymodel.rdf#";
//    RDF rdf;
//    PhysicalForce force(rdf.getModel());
//    force.setModelUri(model_uri);
//    force.setLocalUri(local_uri);
//    //todo considering implementing the builder as a composite builder
//    force.setPhysicalProperty("Force5", "OPB:OPB_00340")
//            .addSource(1, "#PhysicalEntityReference1")
//            .addSink(2, "PhysicalEntityReference2")
//            .addSink(1, "PhysicalEntityReference3");
//
//    Triples triples1 = force.toTriples();
//    std::string actual1 = triples1.str("ntriples", "base");
//    std::cout << actual1 << std::endl;
//    Triples triples2 = force.toTriples();
//    std::string actual2 = triples2.str("ntriples", "base");
//    std::cout << actual1 << std::endl;
//
//    ASSERT_STREQ(actual1.c_str(), actual2.c_str());
//    triples1.freeTriples();
//    triples2.freeTriples();
//}
//
///*******************************************************************
// * Equality Tests
// */
//
//class PhysicalForceEqualityTests : public ::testing::Test {
//public:
//
//    LibrdfStorage storage;
//    LibrdfModel model;
//    std::string model_uri = "http://omex-library.org/myomex.omex/mymodel.xml#";
//    std::string local_uri = "http://omex-library.org/myomex.omex/mymodel.rdf#";
//
//
//    PhysicalForceEqualityTests() {
//        model = LibrdfModel(storage.get());
//    }
//
//    ~PhysicalForceEqualityTests() override {
//        storage.freeStorage();
//        model.freeModel();
//    }
//
//};
//
//TEST_F(PhysicalForceEqualityTests, TestEquality) {
//    PhysicalForce force1(model.get());
//    force1.setModelUri(model_uri);
//    force1.setLocalUri(local_uri);
//    force1.setPhysicalProperty("property_metaid_0", "opb/OPB_00592")
//            .addSource(1.0, "species_metaid0")
//            .addSource(2.0, "species_metaid1")
//            .addSink(1.0, "species_metaid2");
//
//    PhysicalForce force2(model.get());
//    force2.setModelUri(model_uri);
//    force2.setLocalUri(local_uri);
//    force2.setPhysicalProperty("property_metaid_0", "opb/OPB_00592")
//            .addSource(1.0, "species_metaid0")
//            .addSource(2.0, "species_metaid1")
//            .addSink(1.0, "species_metaid2");
//    ASSERT_EQ(force1, force2);
//    force1.free();
//    force2.free();
//}
//
//TEST_F(PhysicalForceEqualityTests, TestInequality1) {
//    PhysicalForce force1(model.get());
//    force1.setModelUri(model_uri);
//    force1.setLocalUri(local_uri);
//    force1.setPhysicalProperty("property_metaid_1", "opb/OPB_00592")
//            .addSource(1.0, "species_metaid0")
//            .addSource(2.0, "species_metaid1")
//            .addSink(1.0, "species_metaid2");
//
//    PhysicalForce force2(model.get());
//    force2.setLocalUri(local_uri);
//    force2.setModelUri(model_uri);
//    force2.setPhysicalProperty("property_metaid_0", "opb/OPB_00592")
//            .addSource(1.0, "species_metaid0")
//            .addSource(2.0, "species_metaid1")
//            .addSink(1.0, "species_metaid2");
//    ASSERT_NE(force1, force2);
//
//    force1.free();
//    force2.free();
//}
//
//TEST_F(PhysicalForceEqualityTests, TestInequality2) {
//    PhysicalForce force1(model.get());
//    force1.setModelUri(model_uri);
//    force1.setLocalUri(local_uri);
//    force1.setPhysicalProperty("property_metaid_0", "opb/OPB_00593")
//            .addSource(1.0, "species_metaid0")
//            .addSource(2.0, "species_metaid1")
//            .addSink(1.0, "species_metaid2");
//
//    PhysicalForce force2(model.get());
//    force2.setModelUri(model_uri);
//    force2.setLocalUri(local_uri);
//    force2.setPhysicalProperty("property_metaid_0", "opb/OPB_00597")
//            .addSource(1.0, "species_metaid0")
//            .addSource(2.0, "species_metaid1")
//            .addSink(1.0, "species_metaid2");
//
//    ASSERT_NE(force1, force2);
//
//    force1.free();
//    force2.free();
//}
//
//TEST_F(PhysicalForceEqualityTests, TestInequality3) {
//    PhysicalForce force1(model.get());
//    force1.setLocalUri(local_uri);
//    force1.setModelUri(model_uri);
//    force1.setPhysicalProperty("property_metaid_1", "opb/OPB_00592")
//            .addSource(1.0, "species_metaid0")
//            .addSource(2.0, "species_metaid1")
//            .addSink(1.0, "species_metaid2");
//
//    PhysicalForce force2(model.get());
//    force2.setModelUri(model_uri);
//    force2.setLocalUri(local_uri);
//    force2.setPhysicalProperty("property_metaid_1", "opb/OPB_00592")
//            .addSource(1.0, "species_metaid0")
//            .addSource(2.0, "species_metaid2")
//            .addSink(1.0, "species_metaid1");
//    ASSERT_NE(force1, force2);
//
//    force1.free();
//    force2.free();
//}
//
//TEST_F(PhysicalForceEqualityTests, TestInequality4) {
//    PhysicalForce force1(model.get());
//    force1.setModelUri(model_uri);
//    force1.setLocalUri(local_uri);
//    force1.setPhysicalProperty("property_metaid_1", "opb/OPB_00592")
//            .addSource(1.0, "species_metaid0")
//            .addSource(2.0, "species_metaid1")
//            .addSink(1.0, "species_metaid2");
//
//    PhysicalForce force2(model.get());
//    force2.setModelUri(model_uri);
//    force2.setLocalUri(local_uri);
//    force2.setPhysicalProperty("property_metaid_1", "opb/OPB_00592")
//            .addSource(2.0, "species_metaid0")
//            .addSource(2.0, "species_metaid1")
//            .addSink(1.0, "species_metaid2");
//    ASSERT_NE(force1, force2);
//
//    force1.free();
//    force2.free();
//}
//



