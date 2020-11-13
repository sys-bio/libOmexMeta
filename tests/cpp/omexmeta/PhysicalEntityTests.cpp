//
// Created by Ciaran on 4/22/2020.
//

#include "CellMLFactory.h"
#include "OmexMetaTestUtils.h"
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

    PhysicalEntityTests()= default;;

    ~PhysicalEntityTests() override = default;
};


/**
 * Tests that we can create and bind a PhysicalProperty to a PhysicalEntity
 * and get the correct annotations for SBML. The "about" method on PhysicalProperty
 * is optional. When not given as user input we generate something appropriate automatically.
 * Here we test the case when the user gives an ID as input.
 */
TEST_F(PhysicalEntityTests, TestPhysicalEntityBuilderForSBMLAutomaticEntityIDGeneration) {
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
            .identity("uniprot:PD12345")
            .addLocation("fma:1234")
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
TEST_F(PhysicalEntityTests, TestPhysicalEntityBuilderForSBMLAutomaticEntityIDGenerationAlternativeAPI) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    PhysicalEntity physicalEntity = editor.newPhysicalEntity();
    physicalEntity
            .identity("uniprot:PD12345")
            .addLocation("fma:1234")
            .hasProperty()
                .isVersionOf("opb:OPB_12345")
                .isPropertyOf("species0001", MODEL_URI);

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
 * Tests that we can create and bind a PhysicalProperty to a PhysicalEntity
 * and get the correct annotations. The "about" method on PhysicalProperty
 * is optional. When not given as user input we generate something appropriate automatically.
 * Here we test the case when the user gives an ID as input. In contrast to TestPhysicalEntityBuilderForSBMLAutomaticEntityIDGeneration
 * we use a more convenient API that the user will end up using.
 */
 TEST_F(PhysicalEntityTests, TestPhysicalEntityBuilderForSBMLManualEntityIDGeneration) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    PhysicalEntity physicalEntity = editor.newPhysicalEntity();
    physicalEntity
            .identity("uniprot:PD12345")
            .addLocation("fma:1234")
            .hasProperty("EntityProperty3", LOCAL_URI)
                .isVersionOf("opb:OPB_12345")
                .isPropertyOf("species0001", MODEL_URI);

    editor.addPhysicalEntity(physicalEntity);

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:EntityProperty3\n"
                           "    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#species0001> ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_12345> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#species0001>\n"
                           "    bqbiol:is <https://identifiers.org/uniprot:PD12345> ;\n"
                           "    bqbiol:isPartOf <https://identifiers.org/fma:1234> .";

    ASSERT_TRUE(RDF::equals(&rdf, expected, "turtle"));
}


TEST_F(PhysicalEntityTests, TestPhysicalEntityBuilderForCellMLBasicInterface) {

    RDF rdf;
    Editor editor = rdf.toEditor(
            CellMLFactory::getCellML(CELLML_TOY), false, false);

    PhysicalProperty entity_property = editor.newPhysicalProperty();
    entity_property.about("main.Volume", MODEL_URI)
            .isVersionOf("opb:OPB_00154")
            .isPropertyOf("entity_0", LOCAL_URI);

    PhysicalEntity physicalEntity = editor.newPhysicalEntity();
    physicalEntity
            .identity("fma:9670")
            .addLocation("fma:18228")
            .hasProperty(entity_property);

    editor.addPhysicalEntity(physicalEntity);

    std::cout << rdf.toString() << std::endl;

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:entity_0\n"
                           "    bqbiol:is <https://identifiers.org/fma:9670> ;\n"
                           "    bqbiol:isPartOf <https://identifiers.org/fma:18228> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#main.Volume>\n"
                           "    bqbiol:isPropertyOf local:entity_0 ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_00154> .";

    ASSERT_TRUE(RDF::equals(&rdf, expected, "turtle"));
}

/*
 * Here we test the creation of PhysicalEntity for CellML. We create a PhysicalProperty
 * via the hasProperty method and all fields are manually specified by the user. Note that
 * the physicalEntity.about call and the isPropertyOf call are the same in this instance. This
 * is intended and in a subsequent test we autmate the generation of these values.
 */
TEST_F(PhysicalEntityTests, TestPhysicalEntityBuilderForCellMLUserInterfaceAndUserSpecifyEverything) {

    RDF rdf;
    Editor editor = rdf.toEditor(
            CellMLFactory::getCellML(CELLML_TOY), false, false);

    PhysicalEntity physicalEntity = editor.newPhysicalEntity();
    physicalEntity
            .about("CellMLEntity", LOCAL_URI)
            .identity("fma:9670")
            .addLocation("fma:18228")
            .hasProperty("main.Volume", MODEL_URI)
                .isVersionOf("opb:OPB_00154")
                .isPropertyOf("CellMLEntity", LOCAL_URI);

    editor.addPhysicalEntity(physicalEntity);

    std::cout << rdf.toString() << std::endl;

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:CellMLEntity\n"
                           "    bqbiol:is <https://identifiers.org/fma:9670> ;\n"
                           "    bqbiol:isPartOf <https://identifiers.org/fma:18228> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#main.Volume>\n"
                           "    bqbiol:isPropertyOf local:CellMLEntity ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_00154> .";

    ASSERT_TRUE(RDF::equals(&rdf, expected, "turtle"));
}

/*
 * Here we test the creation of PhysicalEntity for CellML. We create a PhysicalProperty
 * via the hasProperty method and all fields are manually specified by the user. Note that
 * the physicalEntity.about call and the isPropertyOf call are the same so we autogenerate the local uri
 * to go here.
 */
TEST_F(PhysicalEntityTests, TestPhysicalEntityBuilderForCellMLUserInterfaceAutogenerateEntityID) {

    RDF rdf;
    Editor editor = rdf.toEditor(
            CellMLFactory::getCellML(CELLML_TOY), false, false);

    PhysicalEntity physicalEntity = editor.newPhysicalEntity();
    physicalEntity
            .identity("fma:9670")
            .addLocation("fma:18228")
            .hasProperty("main.Volume", MODEL_URI)
                .isVersionOf("opb:OPB_00154");

    editor.addPhysicalEntity(physicalEntity);

    std::cout << rdf.toString() << std::endl;

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:EntityProperty0000\n"
                           "    bqbiol:is <https://identifiers.org/fma:9670> ;\n"
                           "    bqbiol:isPartOf <https://identifiers.org/fma:18228> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#main.Volume>\n"
                           "    bqbiol:isPropertyOf local:EntityProperty0000 ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_00154> .";

    ASSERT_TRUE(RDF::equals(&rdf, expected, "turtle"));
}



