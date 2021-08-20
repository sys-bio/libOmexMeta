//
// Created by Ciaran on 4/22/2020.
//

#include "CellMLFactory.h"
#include "SBMLFactory.h"
#include "librdf.h"
#include "omexmeta/PhysicalEntity.h"
#include "omexmeta/RDF.h"
#include "vector"
#include "gtest/gtest.h"
#include <vector>

using namespace omexmeta;


class PhysicalEntityTests : public ::testing::Test {

public:
    UriHandler uriHandler;
    PhysicalEntityTests() = default;

    ~PhysicalEntityTests() override = default;
};


/**
 * Tests that we can create and bind a PhysicalProperty to a PhysicalEntity
 * and get the correct annotations for SBML. The "about" method on PhysicalProperty
 * is optional. When not given as user input we generate something appropriate automatically.
 * Here we test the case when the user gives an ID as input.
 */
TEST_F(PhysicalEntityTests, TestPhysicalEntitySBML1) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    PhysicalProperty entity_property = editor.newPhysicalProperty();

    // todo if you do not give argument to "about" method, autogenerate an appropriate ID.
    entity_property.about("EntityProperty", LOCAL_URI)
            .isVersionOf("opb:OPB_12345")
            .isPropertyOf("species0001", MODEL_URI);

    PhysicalEntity physicalEntity = editor.newPhysicalEntity();
    physicalEntity
            .about("species0001", MODEL_URI)
            .identity("uniprot:PD12345")
            .isPartOf("fma:1234")
            .hasProperty(entity_property);

    editor.addPhysicalEntity(physicalEntity);

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:EntityProperty\n"
                           "    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#species0001> ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_12345> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#species0001>\n"
                           "    bqbiol:is <https://identifiers.org/uniprot:PD12345> ;\n"
                           "    bqbiol:isPartOf <https://identifiers.org/fma:1234> .";

    ASSERT_TRUE(RDF::equals(&rdf, expected, "turtle"));
}

/**
 * Tests that we can create and bind a PhysicalProperty to a PhysicalEntity
 * and get the correct annotations. The "about" method on PhysicalProperty
 * is optional. When not given as user input we generate something appropriate automatically.
 * Here we test the case when the user does not give an ID as input. In contrast to TestPhysicalEntityBuilderForSBMLAutomaticEntityIDGeneration
 * we use a more convenient API that the user will end up using.
 */
TEST_F(PhysicalEntityTests, TestPhysicalEntitySBML2) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    PhysicalEntity physicalEntity = editor.newPhysicalEntity();
    physicalEntity
            .about("species0001", MODEL_URI)
            .identity("uniprot:PD12345")
            .isPartOf("fma:1234")
            .hasProperty("EntityProperty", LOCAL_URI, "opb:OPB_12345");//, "species0001", MODEL_URI);

    editor.addPhysicalEntity(physicalEntity);

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:EntityProperty\n"
                           "    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#species0001> ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_12345> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#species0001>\n"
                           "    bqbiol:is <https://identifiers.org/uniprot:PD12345> ;\n"
                           "    bqbiol:isPartOf <https://identifiers.org/fma:1234> .";

    ASSERT_TRUE(RDF::equals(&rdf, expected, "turtle"));
}

/**
 * Tests that we can create and bind a PhysicalProperty to a PhysicalEntity
 * and get the correct annotations. The "about" method on PhysicalProperty
 * is optional. When not given as user input we generate something appropriate automatically.
 * Here we test the case when the user gives an ID as input. In contrast to TestPhysicalEntityBuilderForSBMLAutomaticEntityIDGeneration
 * we use a more convenient API that the user will end up using.
 */
TEST_F(PhysicalEntityTests, TestPhysicalEntitySBML3) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    PhysicalEntity physicalEntity = editor.newPhysicalEntity();

    physicalEntity
            .about("species0001", MODEL_URI)
            .identity("uniprot:PD12345")
            .isPartOf("fma:1234")
            .hasProperty("opb:OPB_12345");

    editor.addPhysicalEntity(physicalEntity);

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:EntityProperty0000\n"
                           "    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#species0001> ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_12345> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#species0001>\n"
                           "    bqbiol:is <https://identifiers.org/uniprot:PD12345> ;\n"
                           "    bqbiol:isPartOf <https://identifiers.org/fma:1234> .";

    ASSERT_TRUE(RDF::equals(&rdf, expected, "turtle"));
}

/**
 * Here we test what happens when the user does not specify a property at all
 */
TEST_F(PhysicalEntityTests, TestPhysicalEntitySBML4) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    PhysicalEntity physicalEntity = editor.newPhysicalEntity();

    physicalEntity
            .about("species0000", MODEL_URI)
            .identity("uniprot:PD12345")
            .isPartOf("fma:1234");
    editor.addPhysicalEntity(physicalEntity);

    PhysicalEntity physicalEntity2 = editor.newPhysicalEntity();

    physicalEntity2
            .about("species0001", MODEL_URI)
            .identity("uniprot:PD12346")
            .isPartOf("fma:1235");
    editor.addPhysicalEntity(physicalEntity2);

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#species0000>\n"
                           "    bqbiol:is <https://identifiers.org/uniprot:PD12345> ;\n"
                           "    bqbiol:isPartOf <https://identifiers.org/fma:1234> ."
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#species0001>\n"
                           "    bqbiol:is <https://identifiers.org/uniprot:PD12346> ;\n"
                           "    bqbiol:isPartOf <https://identifiers.org/fma:1235> .";

    ASSERT_TRUE(RDF::equals(&rdf, expected, "turtle"));
}


/**
 * We add 4 "isPartOf" terms but no property in this test
 */
TEST_F(PhysicalEntityTests, TestPhysicalEntitySBML5) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    PhysicalEntity physicalEntity = editor.newPhysicalEntity();

    physicalEntity
            .about("species0000", MODEL_URI)
            .isPartOf("fma:1234", IDENTIFIERS_URI)
            .isPartOf("fma:1235", IDENTIFIERS_URI)
            .isPartOf("fma:1236", IDENTIFIERS_URI);
    editor.addPhysicalEntity(physicalEntity);


    PhysicalEntity physicalEntity2 = editor.newPhysicalEntity();
    physicalEntity2
            .about("ALocalID", LOCAL_URI)
            .isPartOf("fma:1234", IDENTIFIERS_URI)
            .isPartOf("fma:1235", IDENTIFIERS_URI)
            .isPartOf("fma:1236", IDENTIFIERS_URI);
    editor.addPhysicalEntity(physicalEntity2);


    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#species0000>\n"
                           "    bqbiol:isPartOf <https://identifiers.org/fma:1234> ;"
                           "    bqbiol:isPartOf <https://identifiers.org/fma:1235> ;"
                           "    bqbiol:isPartOf <https://identifiers.org/fma:1236> ."
                           "\n"
                           "local:ALocalID\n"
                           "    bqbiol:isPartOf <https://identifiers.org/fma:1234> ;"
                           "    bqbiol:isPartOf <https://identifiers.org/fma:1235> ;"
                           "    bqbiol:isPartOf <https://identifiers.org/fma:1236> ."
                           "\n";

    ASSERT_TRUE(RDF::equals(&rdf, expected, "turtle"));
}


TEST_F(PhysicalEntityTests, TestPhysicalEntityCellML1) {

    RDF rdf;
    Editor editor = rdf.toEditor(
            CellMLFactory::getCellML(CELLML_TOY), false, false);

    PhysicalProperty entity_property = editor.newPhysicalProperty();
    entity_property.about("main.Volume", MODEL_URI)
            .isVersionOf("opb:OPB_00154")
            .isPropertyOf("entity0", LOCAL_URI);

    PhysicalEntity physicalEntity = editor.newPhysicalEntity();
    physicalEntity
            .about("entity0", LOCAL_URI)
            .identity("fma:9670")
            .isPartOf("fma:18228")
            .hasProperty(entity_property);

    editor.addPhysicalEntity(physicalEntity);

    std::cout << rdf.toString() << std::endl;

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#entity0>\n"
                           "    bqbiol:is <https://identifiers.org/fma:9670> ;\n"
                           "    bqbiol:isPartOf <https://identifiers.org/fma:18228> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#main.Volume>\n"
                           "    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.rdf#entity0> ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_00154> .";

    ASSERT_TRUE(RDF::equals(&rdf, expected, "turtle"));
}

/*
 * Here we test the creation of PhysicalEntity for CellML. We create a PhysicalProperty
 * via the hasProperty method and all fields are manually specified by the user. Note that
 * the physicalEntity.about call and the isPropertyOf call are the same in this instance. This
 * is intended and in a subsequent test we autmate the generation of these values.
 */
TEST_F(PhysicalEntityTests, TestPhysicalEntityCellML2) {

    RDF rdf;
    Editor editor = rdf.toEditor(
            CellMLFactory::getCellML(CELLML_TOY), false, false);

    PhysicalEntity physicalEntity = editor.newPhysicalEntity();
    physicalEntity
            .about("entity0", LOCAL_URI)
            .identity("fma:9670")
            .isPartOf("fma:18228")
            .hasProperty("main.Volume", MODEL_URI, "opb:OPB_00154");//, "entity0", LOCAL_URI);

    editor.addPhysicalEntity(physicalEntity);

    std::cout << rdf.toString() << std::endl;

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#entity0>\n"
                           "    bqbiol:is <https://identifiers.org/fma:9670> ;\n"
                           "    bqbiol:isPartOf <https://identifiers.org/fma:18228> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#main.Volume>\n"
                           "    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.rdf#entity0> ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_00154> .";

    ASSERT_TRUE(RDF::equals(&rdf, expected, "turtle"));
}

/*
 * Here we test the creation of PhysicalEntity for CellML. We create a PhysicalProperty
 * via the hasProperty method and all fields are manually specified by the user. Note that
 * the physicalEntity.about call and the isPropertyOf call are the same so we autogenerate the local uri
 * to go here.
 */
TEST_F(PhysicalEntityTests, TestPhysicalEntityCellML3) {

    RDF rdf;
    Editor editor = rdf.toEditor(
            CellMLFactory::getCellML(CELLML_TOY_EXTENDED), false, false);

    PhysicalEntity physicalEntity = editor.newPhysicalEntity();
    physicalEntity
            .identity("fma:9670")
            .isPartOf("fma:18228")
            .hasProperty("main.Volume", MODEL_URI, "opb:OPB_00154");

    editor.addPhysicalEntity(physicalEntity);

    std::cout << rdf.toString() << std::endl;

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:Entity0000\n"
                           "    bqbiol:is <https://identifiers.org/fma:9670> ;\n"
                           "    bqbiol:isPartOf <https://identifiers.org/fma:18228> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#main.Volume>\n"
                           "    bqbiol:isPropertyOf local:Entity0000 ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_00154> .";

    ASSERT_TRUE(RDF::equals(&rdf, expected, "turtle"));
}

/**
 * @brief A call to toTriples() generates a Triples object. This test
 * makes sure that the exact same set of triples is generated each time
 */
TEST_F(PhysicalEntityTests, TestPhysicalEntitySameTriplesGeneratedEveryTime) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);


    PhysicalEntity physicalEntity = editor.newPhysicalEntity();
    physicalEntity
            .about("species0001", MODEL_URI)
            .identity("uniprot:PD12345")
            .isPartOf("fma:1234")
            .hasProperty("obp:OBP_12345");


    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:EntityProperty0000\n"
                           "    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#species0001> ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/obp/OBP_12345> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#species0001>\n"
                           "    bqbiol:is <https://identifiers.org/uniprot:PD12345> ;\n"
                           "    bqbiol:isPartOf <https://identifiers.org/fma:1234> .";

    Triples triples1 = physicalEntity.toTriples();
    ASSERT_TRUE(RDF::equals(triples1, expected, "turtle"));

    Triples triples2 = physicalEntity.toTriples();
    ASSERT_TRUE(RDF::equals(triples2, expected, "turtle"));
}


/*****************************************************************
 * Test PhysicalEntity memory accountability
 */
class PhysicalEntityMemory : public ::testing::Test {
public:
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);
    PhysicalEntity physicalEntity = editor.newPhysicalEntity();

    PhysicalEntityMemory() {
        physicalEntity
                .about("species0000")
                .identity("uniprot/PD12345")
                .isPartOf("fma:1234")
                .hasProperty("opb:opb_1234");
    };
};

TEST_F(PhysicalEntityMemory, TestPhysicalEntityAdds4TriplesToModel) {

    editor.addPhysicalEntity(physicalEntity);
    ASSERT_EQ(4, rdf.size());
}

//TEST_F(PhysicalEntityMemory, TestUnpackTriplesAndAccountForStatements) {
//    Triples triples = physicalEntity.toTriples();
//
//    // unpack triples
//    Triple triple4 = triples.pop();
//    Triple triple3 = triples.pop();
//    Triple triple2 = triples.pop();
//    Triple triple1 = triples.pop();
//
//    // make sure we've emptied the triples object
//    ASSERT_EQ(0, triples.size());
//
//    // check that all statements have 1 usage
//    ASSERT_EQ(1, triple1.getStatement().getUsage());
//    ASSERT_EQ(1, triple2.getStatement().getUsage());
//    ASSERT_EQ(1, triple3.getStatement().getUsage());
//    ASSERT_EQ(1, triple4.getStatement().getUsage());
//}

TEST_F(PhysicalEntityMemory, TestUnpackTriplesAndAccountForTermsAndUris) {

    Triples triples = physicalEntity.toTriples();
    //    RDF rdf;
    //    rdf.addTriples(triples);
    //    std::cout << rdf.toString() << std::endl;
    /**
     * The act of calling Triples::operator[] copies the node reference
     * incrementing the reference counter by 1 until the current scope
     * ends, when the extra copy is deleted. A scope here is
     * `triples[0].getSubjectNode().getUsage()` since its a temporary object
     */
    ASSERT_EQ(1 + 1, triples[0].getSubjectNode().getUsage());
    ASSERT_EQ(1 + 1, triples[0].getPredicateNode().getUsage());
    ASSERT_EQ(1 + 1, triples[0].getResourceNode().getUsage());

    ASSERT_EQ(1 + 1, triples[1].getSubjectNode().getUsage());
    ASSERT_EQ(1 + 1, triples[1].getPredicateNode().getUsage());
    ASSERT_EQ(1 + 1, triples[1].getResourceNode().getUsage());

    ASSERT_EQ(1 + 1, triples[2].getSubjectNode().getUsage());
    ASSERT_EQ(1 + 1, triples[2].getPredicateNode().getUsage());
    ASSERT_EQ(1 + 1, triples[2].getResourceNode().getUsage());

    ASSERT_EQ(1 + 1, triples[3].getSubjectNode().getUsage());
    ASSERT_EQ(1 + 1, triples[3].getPredicateNode().getUsage());
    ASSERT_EQ(1 + 1, triples[3].getResourceNode().getUsage());

}


/**********************************************
 * Tests for deleting PhysicalEntity
 */

/*
 * Note: This was way harder than it should have been because I neglected to
 * remember that the toTriples() method autogenerates some subject portions of
 * some triples. Therefore calling it twice would generate a new metaid and
 * it wouldn't be equal to the originally generated annotation.
 *
 * Took me a while to figure this out, hence why there are loads of remove* tests.
 */
class DeletePhysicalEntity : public ::testing::Test {
public:
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    UriHandler uriHandler;
    DeletePhysicalEntity() = default;
};

TEST_F(DeletePhysicalEntity, TestRDFSizeBeforeRemovingAndNoMemoryLeaks) {
    PhysicalEntity physicalEntity = editor.newPhysicalEntity();
    physicalEntity
            .about("species0000")
            .hasProperty("opb:opb_1234")
            .identity("uniprot/PD12345")
            .isPartOf("fma:1234");
    editor.addPhysicalEntity(physicalEntity);
    ASSERT_EQ(4, rdf.size());
    //    editor.removePhysicalEntity(physicalEntity);
}

TEST_F(DeletePhysicalEntity, TestRemoveSingleTriple1) {
    Triple triple(
            uriHandler,
            LibrdfNode::fromUriString("species0000"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isVersionOf"),
            LibrdfNode::fromUriString("https://identifiers.org/opb/opb_1234"));
    editor.addSingleAnnotation(triple);
    ASSERT_EQ(1, rdf.size());
    editor.removeSingleAnnotation(triple);
    ASSERT_EQ(0, rdf.size());
}

TEST_F(DeletePhysicalEntity, TestRemoveSingleTriple2) {
    /* Take and delete triple number 1
 * 1) <species0000> <http://biomodels.net/biology-qualifiers/isVersionOf> <https://identifiers.org/opb/opb_1234> .
 * 2) <species0000> <http://biomodels.net/biology-qualifiers/isPropertyOf> <EntityProperty0001> .
 * 3) <EntityProperty0001> <http://biomodels.net/biology-qualifiers/is> <https://identifiers.org/uniprot/PD12345> .
 * 4) <EntityProperty0001> <http://biomodels.net/biology-qualifiers/isPartOf> <https://identifiers.org/fma:1234> .
 */
    Triple triple(
            uriHandler,
            LibrdfNode::fromUriString("species0000"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPropertyOf"),
            LibrdfNode::fromUriString("EntityProperty0001"));
    editor.addSingleAnnotation(triple);
    ASSERT_EQ(1, rdf.size());
    editor.removeSingleAnnotation(triple);
    ASSERT_EQ(0, rdf.size());
}

TEST_F(DeletePhysicalEntity, TestRemoveSingleTriple3) {
    /* Take and delete triple number 1
     * 1) <species0000> <http://biomodels.net/biology-qualifiers/isVersionOf> <https://identifiers.org/opb/opb_1234> .
     * 2) <species0000> <http://biomodels.net/biology-qualifiers/isPropertyOf> <EntityProperty0001> .
     * 3) <EntityProperty0001> <http://biomodels.net/biology-qualifiers/is> <https://identifiers.org/uniprot/PD12345> .
     * 4) <EntityProperty0001> <http://biomodels.net/biology-qualifiers/isPartOf> <https://identifiers.org/fma:1234> .
     */
    Triple triple(
            uriHandler,
            LibrdfNode::fromUriString("#Meta00001"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/is"),
            LibrdfNode::fromUriString("https://identifiers.org/uniprot/PD12345"));
    editor.addSingleAnnotation(triple);
    ASSERT_EQ(1, rdf.size());
    editor.removeSingleAnnotation(triple);
    ASSERT_EQ(0, rdf.size());
}

TEST_F(DeletePhysicalEntity, TestRemoveSingleTriple4) {
    /* Take and delete triple number 1
 * 1) <species0000> <http://biomodels.net/biology-qualifiers/isVersionOf> <https://identifiers.org/opb/opb_1234> .
 * 2) <species0000> <http://biomodels.net/biology-qualifiers/isPropertyOf> <EntityProperty0001> .
 * 3) <EntityProperty0001> <http://biomodels.net/biology-qualifiers/is> <https://identifiers.org/uniprot/PD12345> .
 * 4) <EntityProperty0001> <http://biomodels.net/biology-qualifiers/isPartOf> <https://identifiers.org/fma:1234> .
 */
    Triple triple(
            uriHandler,
            LibrdfNode::fromUriString("#cytosol"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf"),
            LibrdfNode::fromUriString("https://identifiers.org/fma:1234"));
    editor.addSingleAnnotation(triple);
    ASSERT_EQ(1, rdf.size());
    editor.removeSingleAnnotation(triple);
    ASSERT_EQ(0, rdf.size());
}

TEST_F(DeletePhysicalEntity, TestRemoveSingleTripleTwoTriples) {
    Triple triple(
            uriHandler,
            LibrdfNode::fromUriString("#cytosol"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf"),
            LibrdfNode::fromUriString("https://identifiers.org/fma:1234"));
    editor.addSingleAnnotation(triple);
    ASSERT_EQ(1, rdf.size());

    Triple triple2(
            uriHandler,
            LibrdfNode::fromUriString("#cytosol"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf"),
            LibrdfNode::fromUriString("https://identifiers.org/fma:1234"));
    editor.removeSingleAnnotation(triple2);
    ASSERT_EQ(0, rdf.size());
}

TEST_F(DeletePhysicalEntity, TestRemoveSingleTripleFromTriples) {
    Triple triple(
            uriHandler,
            LibrdfNode::fromUriString("#cytosol"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf"),
            LibrdfNode::fromUriString("https://identifiers.org/fma:1234"));
    // put triple in Triples
    Triples triples(1);
    triples.moveBack(triple);

    // add to the model
    for (auto &it : triples) {
        editor.addSingleAnnotation(it);
    }

    // check rdf size
    ASSERT_EQ(1, rdf.size());

    // get the Triples again. Same content, different instance
    Triple triple2(
            uriHandler,
            LibrdfNode::fromUriString("#cytosol"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf"),
            LibrdfNode::fromUriString("https://identifiers.org/fma:1234"));
    // put triple in Triples
    Triples triples2(1);
    triples2.moveBack(triple2);

    // use it to remove the triple
    for (auto &it : triples2) {
        editor.removeSingleAnnotation(it);
    }
    // should be no triples left now in rdf
    ASSERT_EQ(0, rdf.size());

}

TEST_F(DeletePhysicalEntity, TestRemoveTwoTripleObjsFromTriplesDifferentContent) {
    // Here these triples have different content. Next test they have same content.
    Triple triple1(
            uriHandler,
            LibrdfNode::fromUriString("cytosol1"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf1"),
            LibrdfNode::fromUriString("https://identifiers.org/fma:12341"));
    Triple triple2(
            uriHandler,
            LibrdfNode::fromUriString("cytosol2"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf2"),
            LibrdfNode::fromUriString("https://identifiers.org/fma:12342"));
    // put triple in Triples
    Triples triples(2);
    triples.moveBack(triple1);
    triples.moveBack(triple2);

    // add to the model
    for (auto &it : triples) {
        editor.addSingleAnnotationNoValidation(it);
    }

    // check rdf size
    ASSERT_EQ(2, rdf.size());

    // use it to remove the triple
    for (auto &it : triples) {
        editor.removeSingleAnnotation(it);
    }
    // should be no triples left now in rdf
    ASSERT_EQ(0, rdf.size());

    // free
}

TEST_F(DeletePhysicalEntity, TestRemoveTwoTripleObjsFromTriplesSameSubject) {
    // Here these triples have different content. Next test they have same content.
    Triple triple1(
            uriHandler,
            LibrdfNode::fromUriString("cytosol"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf1"),
            LibrdfNode::fromUriString("https://identifiers.org/fma:12341"));
    Triple triple2(
            uriHandler,
            LibrdfNode::fromUriString("cytosol"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf2"),
            LibrdfNode::fromUriString("https://identifiers.org/fma:12342"));
    // put triple in Triples
    Triples triples(2);
    triples.moveBack(triple1);
    triples.moveBack(triple2);

    // add to the model
    for (auto &it : triples) {
        editor.addSingleAnnotationNoValidation(it);
    }

    // check rdf size
    ASSERT_EQ(2, rdf.size());

    // use it to remove the triple
    for (auto &it : triples) {
        editor.removeSingleAnnotation(it);
    }
    // should be no triples left now in rdf
    ASSERT_EQ(0, rdf.size());

    // free
}

TEST_F(DeletePhysicalEntity, TestRemoveTwoTripleObjsFromTriplesSameSubjectAndPredicate) {
    // Here these triples have different content. Next test they have same content.
    Triple triple1(
            uriHandler,
            LibrdfNode::fromUriString("cytosol"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf"),
            LibrdfNode::fromUriString("https://identifiers.org/fma:12341"));
    Triple triple2(
            uriHandler,
            LibrdfNode::fromUriString("cytosol"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf"),
            LibrdfNode::fromUriString("https://identifiers.org/fma:12342"));
    // put triple in Triples
    Triples triples(2);
    triples.moveBack(triple1);
    triples.moveBack(triple2);

    // add to the model
    for (auto &it : triples) {
        editor.addSingleAnnotationNoValidation(it);
    }

    // check rdf size
    ASSERT_EQ(2, rdf.size());

    // use it to remove the triple
    for (auto &it : triples) {
        editor.removeSingleAnnotation(it);
    }
    // should be no triples left now in rdf
    ASSERT_EQ(0, rdf.size());

    // free
}

TEST_F(DeletePhysicalEntity, TestRemoveTwoTripleObjsFromTriplesSameSubjectAndResource) {
    // Here these triples have different content. Next test they have same content.
    Triple triple1(
            uriHandler,
            LibrdfNode::fromUriString("cytosol"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf1"),
            LibrdfNode::fromUriString("https://identifiers.org/fma:1234"));
    Triple triple2(
            uriHandler,
            LibrdfNode::fromUriString("cytosol"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf2"),
            LibrdfNode::fromUriString("https://identifiers.org/fma:1234"));
    // put triple in Triples
    Triples triples(2);
    triples.moveBack(triple1);
    triples.moveBack(triple2);

    // add to the model
    for (auto &it : triples) {
        editor.addSingleAnnotationNoValidation(it);
    }

    // check rdf size
    ASSERT_EQ(2, rdf.size());

    // use it to remove the triple
    for (auto &it : triples) {
        editor.removeSingleAnnotation(it);
    }
    // should be no triples left now in rdf
    ASSERT_EQ(0, rdf.size());

    // free
}

TEST_F(DeletePhysicalEntity, TestRemoveTwoTripleObjsFromTriplesSamePredicateAndResource) {
    // Here these triples have different content. Next test they have same content.
    Triple triple1(
            uriHandler,
            LibrdfNode::fromUriString("cytosol1"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf"),
            LibrdfNode::fromUriString("https://identifiers.org/fma:1234"));
    Triple triple2(
            uriHandler,
            LibrdfNode::fromUriString("cytosol2"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf"),
            LibrdfNode::fromUriString("https://identifiers.org/fma:1234"));
    // put triple in Triples
    Triples triples(2);
    triples.moveBack(triple1);
    triples.moveBack(triple2);

    // add to the model
    for (auto &it : triples) {
        editor.addSingleAnnotationNoValidation(it);
    }

    // check rdf size
    ASSERT_EQ(2, rdf.size());

    // use it to remove the triple
    for (auto &it : triples) {
        editor.removeSingleAnnotation(it);
    }
    // should be no triples left now in rdf
    ASSERT_EQ(0, rdf.size());

    // free
}

TEST_F(DeletePhysicalEntity, TestRemoveTwoTripleObjsFromTriplesSameEverything) {
    /*
     * When trying to add a duplicate triple to the model,
     * it seems that raptor catches it and does not add the triple again.
     */
    Triple triple1(
            uriHandler,
            LibrdfNode::fromUriString("cytosol"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf"),
            LibrdfNode::fromUriString("https://identifiers.org/fma:1234"));

    Triple triple2(
            uriHandler,
            LibrdfNode::fromUriString("cytosol"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf"),
            LibrdfNode::fromUriString("https://identifiers.org/fma:1234"));
    // put triple in Triples
    Triples triples(2);
    triples.moveBack(triple1);
    triples.moveBack(triple2);

    // add to the model
    for (auto &it : triples) {
        editor.addSingleAnnotationNoValidation(it);
    }

    std::cout << rdf.toString() << std::endl;

    // check rdf size (using gtest here breaks the test? :/)
    // this is 1 because these two triples are duplicates.
    // Raptor catches duplicates
    ASSERT_EQ(1, rdf.size());

    // use it to remove the triple
    for (auto &it : triples) {
        editor.removeSingleAnnotation(it);
    }
    std::cout << rdf.toString() << std::endl;
    // should be no triples left now in rdf
    ASSERT_EQ(0, rdf.size());

    // free
}

TEST_F(DeletePhysicalEntity, TestRemoveTwoTripleObjsFromTriplesWithFreeInMiddle) {
    Triple triple1(
            uriHandler,
            LibrdfNode::fromUriString("#cytosol"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf"),
            LibrdfNode::fromUriString("https://identifiers.org/fma:1234"));
    Triple triple2(
            uriHandler,
            LibrdfNode::fromUriString("#cytosol"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf"),
            LibrdfNode::fromUriString("https://identifiers.org/fma:1234"));
    // put triple in Triples
    Triples triples(2);
    triples.moveBack(triple1);
    triples.moveBack(triple2);

    // add to the model
    for (auto &it : triples) {
        editor.addSingleAnnotation(it);
    }

    // check rdf size
    // These are duplicates, so only 1 will be added to the raptor model
    ASSERT_EQ(1, rdf.size());

    // free triples


    Triple triple3(
            uriHandler,
            LibrdfNode::fromUriString("#cytosol"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf"),
            LibrdfNode::fromUriString("https://identifiers.org/fma:1234"));
    Triple triple4(
            uriHandler,
            LibrdfNode::fromUriString("#cytosol"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf"),
            LibrdfNode::fromUriString("https://identifiers.org/fma:1234"));
    // put triple in Triples
    Triples triples2(2);
    triples2.moveBack(triple3);
    triples2.moveBack(triple4);

    // use it to remove the triple
    for (auto &it : triples2) {
        editor.removeSingleAnnotation(it);
    }
    // should be no triples left now in rdf
    ASSERT_EQ(0, rdf.size());

    // free
}


TEST_F(DeletePhysicalEntity, TestRemoveDoubleTriple1And2Sequential) {
    /* Take and delete triple number 1
 * 1) <species0000> <http://biomodels.net/biology-qualifiers/isVersionOf> <https://identifiers.org/opb/opb_1234> .
 * 2) <species0000> <http://biomodels.net/biology-qualifiers/isPropertyOf> <EntityProperty0001> .
 * 3) <EntityProperty0001> <http://biomodels.net/biology-qualifiers/is> <https://identifiers.org/uniprot/PD12345> .
 * 4) <EntityProperty0001> <http://biomodels.net/biology-qualifiers/isPartOf> <https://identifiers.org/fma:1234> .
 */
    Triple triple(
            uriHandler,
            LibrdfNode::fromUriString("species0000"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isVersionOf"),
            LibrdfNode::fromUriString("https://identifiers.org/opb/opb_1234"));
    editor.addSingleAnnotation(triple);
    ASSERT_EQ(1, rdf.size());
    editor.removeSingleAnnotation(triple);
    ASSERT_EQ(0, rdf.size());

    Triple triple2(
            uriHandler,
            LibrdfNode::fromUriString("species0000"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPropertyOf"),
            LibrdfNode::fromUriString("EntityProperty0001"));
    editor.addSingleAnnotation(triple2);
    ASSERT_EQ(1, rdf.size());
    editor.removeSingleAnnotation(triple2);
    ASSERT_EQ(0, rdf.size());
}

TEST_F(DeletePhysicalEntity, TestRemoveDoubleTriple1And2SequentialAndFreeOnlyAtEnd) {
    /* Take and delete triple number 1
 * 1) <species0000> <http://biomodels.net/biology-qualifiers/isVersionOf> <https://identifiers.org/opb/opb_1234> .
 * 2) <species0000> <http://biomodels.net/biology-qualifiers/isPropertyOf> <EntityProperty0001> .
 * 3) <EntityProperty0001> <http://biomodels.net/biology-qualifiers/is> <https://identifiers.org/uniprot/PD12345> .
 * 4) <EntityProperty0001> <http://biomodels.net/biology-qualifiers/isPartOf> <https://identifiers.org/fma:1234> .
 */
    Triple triple(
            uriHandler,
            LibrdfNode::fromUriString("https://uri.com#species0000"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isVersionOf"),
            LibrdfNode::fromUriString("https://identifiers.org/opb/opb_1234"));
    editor.addSingleAnnotation(triple);
    ASSERT_EQ(1, rdf.size());
    editor.removeSingleAnnotation(triple);
    ASSERT_EQ(0, rdf.size());

    Triple triple2(
            uriHandler,
            LibrdfNode::fromUriString("https://uri.com#species0000"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPropertyOf"),
            LibrdfNode::fromUriString("EntityProperty0001"));
    editor.addSingleAnnotation(triple2);
    ASSERT_EQ(1, rdf.size());
    editor.removeSingleAnnotation(triple2);
    ASSERT_EQ(0, rdf.size());
}

TEST_F(DeletePhysicalEntity, TestCreateAddAndRemoveTripleFromAPropertyOfPhysicalEntity) {
    /* Take and delete triple number 1
 * 1) <species0000> <http://biomodels.net/biology-qualifiers/isVersionOf> <https://identifiers.org/opb/opb_1234> .
 * 2) <species0000> <http://biomodels.net/biology-qualifiers/isPropertyOf> <EntityProperty0001> .
 * 3) <EntityProperty0001> <http://biomodels.net/biology-qualifiers/is> <https://identifiers.org/uniprot/PD12345> .
 * 4) <EntityProperty0001> <http://biomodels.net/biology-qualifiers/isPartOf> <https://identifiers.org/fma:1234> .
 */
    PhysicalEntity physicalEntity = editor.newPhysicalEntity();
    physicalEntity
            .about("http://omex-library.org/NewOmex.omex/NewModel.xmlspecies0000")
            .hasProperty("opb:opb_1234")
            .identity("uniprot/PD12345")
            .isPartOf("fma:1234");
    Triples triples = physicalEntity.toTriples();
    for (auto &it : triples) {
        editor.addSingleAnnotationNoValidation(it);
    }
    ASSERT_EQ(4, rdf.size());
    for (auto &it : triples) {
        editor.removeSingleAnnotation(it);
    }
    ASSERT_EQ(0, rdf.size());
}

TEST_F(DeletePhysicalEntity,
       TestCreateAddAndRemoveTripleFromAPropertyOfPhysicalEntityWithNamespaceHandling) {
    PhysicalEntity physicalEntity = editor.newPhysicalEntity();
    physicalEntity
            .about("http://omex-library.org/NewOmex.omex/NewModel.xmlspecies0000")
            .hasProperty("opb:opb_1234")
            .identity("uniprot/PD12345")
            .isPartOf("fma:1234");
    Triples triples = physicalEntity.toTriples();
    for (auto &it : triples) {
        editor.addSingleAnnotationNoValidation(it);
        editor.addNamespaceFromAnnotation(it.getPredicateNode().str());
    }
    ASSERT_EQ(4, rdf.size());
    for (auto &it : triples) {
        editor.removeSingleAnnotation(it);
    }
    ASSERT_EQ(0, rdf.size());
}


TEST_F(DeletePhysicalEntity, TestAddAndRemovePhysicalEntity) {
    PhysicalEntity physicalEntity = editor.newPhysicalEntity();
    physicalEntity
            .about("http://omex-library.org/NewOmex.omex/NewModel.xml#species0000")
            .hasProperty("opb:opb_1234")
            .identity("uniprot/PD12345")
            .isPartOf("fma:1234");
    editor.addPhysicalEntity(physicalEntity);
    ASSERT_EQ(4, rdf.size());
    editor.removePhysicalEntity(physicalEntity);
    ASSERT_EQ(0, rdf.size());
}


TEST_F(DeletePhysicalEntity, TestDeleteFirstTriple) {
    PhysicalEntity physicalEntity = editor.newPhysicalEntity();
    physicalEntity
            .about("http://omex-library.org/NewOmex.omex/NewModel.xml#species0000")
            .hasProperty("opb:opb_1234")
            .identity("uniprot/PD12345")
            .isPartOf("fma:1234");
    editor.addPhysicalEntity(physicalEntity);

    /* Take and delete triple number 1
     * 1) <species0000> <http://biomodels.net/biology-qualifiers/isVersionOf> <https://identifiers.org/opb/opb_1234> .
     * 2) <species0000> <http://biomodels.net/biology-qualifiers/isPropertyOf> <EntityProperty0001> .
     * 3) <EntityProperty0001> <http://biomodels.net/biology-qualifiers/is> <https://identifiers.org/uniprot/PD12345> .
     * 4) <EntityProperty0001> <http://biomodels.net/biology-qualifiers/isPartOf> <https://identifiers.org/fma:1234> .
     */

    Triples triples = physicalEntity.toTriples();
    Triple triple = triples.pop();

    editor.removeSingleAnnotation(triple);
    ASSERT_EQ(3, rdf.size());

}
