//
// Created by Ciaran on 5/12/2020.
//

#include "gtest/gtest.h"

#include "AnnotationSamples.h"
#include "SBMLFactory.h"

#include "omexmeta/OmexMetaCApi.h"
#include <CellMLFactory.h>
#include <filesystem>
#include <fstream>


using namespace omexmeta;

class CAPITests : public ::testing::Test {
public:
    AnnotationSamples samples = AnnotationSamples();

    std::filesystem::path fnamep = std::filesystem::current_path() / +"annotation.rdf";
    std::string fname;
    std::filesystem::path sqlite_fname = std::filesystem::current_path() += "SqliteStorageTest.db";

    CAPITests() {
        fname = fnamep.string();
    }
};


TEST_F(CAPITests, RDFSize) {
    RDF *rdf_ptr = RDF_fromString(samples.singular_annotation1.c_str(), "rdfxml", "LannotationsBase.rdf");
    int actual = RDF_size(rdf_ptr);
    int expected = 1;
    ASSERT_EQ(expected, actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, RDFToString) {
    RDF *rdf_ptr = RDF_fromString(samples.singular_annotation1.c_str(), "rdfxml");

    std::string expected = "<?xml version=\"1.1\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:OMEXlib=\"http://omex-library.org/\"\n"
                           "   xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:local=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#\"\n"
                           "   xmlns:myOMEX=\"http://omex-library.org/NewOmex.omex/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.xml#metaid_1\">\n"
                           "    <bqbiol:is rdf:resource=\"https://identifiers.org/uniprot/P0DP23\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    ASSERT_TRUE(RDF::equals(rdf_ptr, expected, "rdfxml"));
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, RDF_fromString) {
    RDF *rdf_ptr = RDF_fromString(samples.composite_annotation_pf.c_str(), "rdfxml", "RDF_fromStringTest.rdf");
    int expected = 6;
    int actual = RDF_size(rdf_ptr);
    ASSERT_EQ(expected, actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, RDF_fromStringButWrongSyntax) {
    // we need rdfxml but we give turtle
    ASSERT_NO_THROW(
        RDF *rdf_ptr = RDF_fromString(samples.composite_annotation_pf.c_str(), "turtle", "RDF_fromStringTest.rdf");
        RDF_delete(rdf_ptr);
    );
}

TEST_F(CAPITests, RDF_toFile) {
    RDF *rdf_ptr = RDF_fromString(samples.composite_annotation_pf.c_str(), "rdfxml", "RDF_fromStringTest.rdf");
    RDF_toFile(rdf_ptr, "turtle", fname.c_str());
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, RDF_addFromString) {
    RDF *rdf_ptr = RDF_new();
    RDF_addFromString(rdf_ptr, samples.singular_annotation1.c_str(), "rdfxml");
    int expected = 1;
    int actual = RDF_size(rdf_ptr);
    ASSERT_EQ(expected, actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, RDF_addFromStringOutput) {
    RDF *rdf_ptr = RDF_new();
    RDF_addFromString(rdf_ptr, samples.singular_annotation1.c_str(), "rdfxml");
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#metaid_1>\n"
                           "    bqbiol:is <https://identifiers.org/uniprot/P0DP23> .\n"
                           "\n"
                           "";
    ASSERT_TRUE(RDF::equals(rdf_ptr, expected, "turtle"));
    RDF_delete(rdf_ptr);
}

/**
 * From uri isn't something that we want support for, so we can drop the tests
 */
//TEST_F(CAPITests, RDF_fromUri) {
//    RDF *rdf_ptr = RDF_fromUri(samples.sbml_url1.c_str(), "rdfxml");
//    int expected = 277;
//    int actual = RDF_size(rdf_ptr);
//    ASSERT_EQ(expected, actual);
//    RDF_delete(rdf_ptr);
//}
//
//TEST_F(CAPITests, RDF_addFromUri) {
//    RDF *rdf_ptr = RDF_new();
//    RDF_addFromUri(rdf_ptr, samples.sbml_url1.c_str(), "rdfxml");
//    int expected = 277;
//    int actual = RDF_size(rdf_ptr);
//    ASSERT_EQ(expected, actual);
//    RDF_delete(rdf_ptr);
//}

TEST_F(CAPITests, RDF_addFromUriSqliteStorage) {
    RDF *rdf_ptr = RDF_new("sqlite", sqlite_fname.string().c_str(), "new='yes'");
    RDF_addFromString(rdf_ptr, samples.singular_annotation1.c_str(), "rdfxml");
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#metaid_1>\n"
                           "    bqbiol:is <https://identifiers.org/uniprot/P0DP23> .\n"
                           "\n"
                           "";
    ASSERT_TRUE(RDF::equals(rdf_ptr, expected, "turtle"));
    ASSERT_TRUE(std::filesystem::exists(fname));
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, RDF_fromFile) {
    // we can cheat and use C++ to write the file we need - who's counting
    std::string fname = std::filesystem::current_path().string() + "/TestParseFromFile.rdf";
    std::cout << fname << std::endl;
    std::ofstream f(fname);
    if (f.is_open()) {
        f << samples.composite_annotation_pe << std::endl;
        f.flush();
        f.close();
    } else {
        throw std::logic_error("No file was opened for test");
    }

    RDF *rdf_ptr = RDF_fromFile(fname.c_str(), "rdfxml");
    int expected = 4;
    int actual = RDF_size(rdf_ptr);
    ASSERT_EQ(expected, actual);
    std::remove(fname.c_str());
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, RDF_addFromFile) {
    // we can cheat and use C++ to write the file we need - who's counting
    std::string fname = (std::filesystem::current_path() / +"TestParseFromFile.rdf").string();
    std::cout << fname << std::endl;
    std::ofstream f(fname);
    if (f.is_open()) {
        f << samples.composite_annotation_pe << std::endl;
        f.flush();
        f.close();
    } else {
        throw std::logic_error("No file was opened for test");
    }

    RDF *rdf_ptr = RDF_new();
    RDF_addFromFile(rdf_ptr, fname.c_str(), "rdfxml");
    int expected = 4;
    int actual = RDF_size(rdf_ptr);
    ASSERT_EQ(expected, actual);
    std::remove(fname.c_str());
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, TestCheckValidMetaid) {
    RDF *rdf_ptr = RDF_new();

    Editor *editor_ptr = RDF_toEditor(rdf_ptr, SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    Editor_checkValidMetaid(editor_ptr, "model0000");

    Editor_delete(editor_ptr);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, TestGetMetaID) {
    RDF *rdf_ptr = RDF_new();

    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    char *actual = Editor_getMetaId(editor_ptr, 0);
    std::cout << actual << std::endl;
    const char *expected = "TestModelNotAnnotated";
    ASSERT_STREQ(expected, actual);

    free(actual);
    Editor_delete(editor_ptr);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, TestGetNumMetaIDs) {
    RDF *rdf_ptr = RDF_new();

    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    int actual = Editor_getNumMetaIds(editor_ptr);
    std::cout << actual << std::endl;
    int expected = 11;
    ASSERT_EQ(expected, actual);
    Editor_delete(editor_ptr);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, TestSingularAnnotationSetAbout) {
    RDF *rdf_ptr = RDF_new();

    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);

    SingularAnnotation *singularAnnotation = Editor_newSingularAnnotation(editor_ptr);
    SingularAnnotation_about(singularAnnotation, "metaid6");
    char *actual = SingularAnnotation_getAbout(singularAnnotation);
    const char *expected = "http://omex-library.org/NewOmex.omex/NewModel.xml#metaid6";
    ASSERT_STREQ(expected, actual);

    Editor_delete(editor_ptr);
    SingularAnnotation_delete(singularAnnotation);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, TestSingularAnnotationSetPredicate) {
    RDF *rdf_ptr = RDF_new();

    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);

    SingularAnnotation *singularAnnotation = Editor_newSingularAnnotation(editor_ptr);
    SingularAnnotation_setPredicate(singularAnnotation,
                                    "bqbiol", "is");
    char *actual = SingularAnnotation_getPredicate(singularAnnotation);
    const char *expected = "http://biomodels.net/biology-qualifiers/is";
    ASSERT_STREQ(expected, actual);


    Editor_delete(editor_ptr);
    SingularAnnotation_delete(singularAnnotation);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, TestSingularAnnotationSetPredicateUri) {
//    LOGGER_SET_DEBUG();
//    REDLAND_DEBUG("Starting test TestSingularAnnotationSetPredicateUri");
    RDF *rdf_ptr = RDF_new();

    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);

    SingularAnnotation *singularAnnotation = Editor_newSingularAnnotation(editor_ptr);
    SingularAnnotation_setPredicateFromUri(singularAnnotation, "http://predicate.com/from/uri");
    char *actual = SingularAnnotation_getPredicate(singularAnnotation);
    const char *expected = "http://predicate.com/from/uri";
    ASSERT_STREQ(expected, actual);

    Editor_delete(editor_ptr);
    SingularAnnotation_delete(singularAnnotation);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
    LOGGER_SET_WARN();
}

TEST_F(CAPITests, TestSingularAnnotationFull) {
    RDF *rdf_ptr = RDF_new();

    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);

    SingularAnnotation *singularAnnotation = Editor_newSingularAnnotation(editor_ptr);
    SingularAnnotation_about(singularAnnotation, "species0000");
    SingularAnnotation_setPredicateFromUri(singularAnnotation, "http://predicate.com/from/uri");
    SingularAnnotation_setResourceLiteral(singularAnnotation, "Cheese");
    Editor_addSingleAnnotation(editor_ptr, singularAnnotation);

    char *actual = RDF_toString(rdf_ptr,  "turtle");
    printf("%s", actual);
    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#species0000>\n"
                           "    <http://predicate.com/from/uri> \"Cheese\" .\n"
                           "\n";
    ASSERT_TRUE(RDF::equals(rdf_ptr, expected, "turtle"));

    Editor_delete(editor_ptr);
    SingularAnnotation_delete(singularAnnotation);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, TestEditorPtrMem) {
    // verified with valgrind, not sure how to gtest
    RDF *rdf_ptr = RDF_new();

    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);

    RDF_delete(rdf_ptr);
    delete editor_ptr;
}

TEST_F(CAPITests, TestSingularAnnotationSetResourceLiteral) {
    RDF *rdf_ptr = RDF_new();

    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);

    SingularAnnotation *singularAnnotation = Editor_newSingularAnnotation(editor_ptr);
    SingularAnnotation_setResourceLiteral(singularAnnotation,
                                          "LiterallyAString");
    char *actual = SingularAnnotation_getResource(singularAnnotation);
    const char *expected = "LiterallyAString";
    ASSERT_STREQ(expected, actual);


    Editor_delete(editor_ptr);
    SingularAnnotation_delete(singularAnnotation);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, TestSingularAnnotationSetResourceUri) {
    RDF *rdf_ptr = RDF_new();

    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);

    SingularAnnotation *singularAnnotation = Editor_newSingularAnnotation(editor_ptr);
    SingularAnnotation_setResourceUri(singularAnnotation,
                                      "uniprot:PD98723");
    char *actual = SingularAnnotation_getResource(singularAnnotation);
    const char *expected = "https://identifiers.org/uniprot:PD98723";
    ASSERT_STREQ(expected, actual);

    Editor_delete(editor_ptr);
    SingularAnnotation_delete(singularAnnotation);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, TestSingularAnnotationSetResourceBlank) {
    RDF *rdf_ptr = RDF_new();

    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);

    SingularAnnotation *singularAnnotation = Editor_newSingularAnnotation(editor_ptr);
    SingularAnnotation_setResourceBlank(singularAnnotation, "Nothing");
    char *actual = SingularAnnotation_getResource(singularAnnotation);
    const char *expected = "Nothing";
    ASSERT_STREQ(expected, actual);

    Editor_delete(editor_ptr);
    SingularAnnotation_delete(singularAnnotation);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, TestPhysicalEntitySBML1) {
    RDF *rdf_ptr = RDF_new();

    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);

    PhysicalProperty *entity_property = editor_ptr->newPhysicalPropertyPtr();
    entity_property = PhysicalProperty_about(entity_property, "EntityProperty", LOCAL_URI);
    entity_property = PhysicalProperty_isVersionOf(entity_property, "opb:OPB_12345");
    entity_property = PhysicalProperty_isPropertyOf(entity_property, "species0001", MODEL_URI);

    PhysicalEntity *physical_entity_ptr = Editor_newPhysicalEntity(editor_ptr);
    physical_entity_ptr = PhysicalEntity_about(physical_entity_ptr, "species0001");
    physical_entity_ptr = PhysicalEntity_identity(physical_entity_ptr, "uniprot:PD12345");
    physical_entity_ptr = PhysicalEntity_isPartOf(physical_entity_ptr, "FMA:1234", IDENTIFIERS_URI);
    physical_entity_ptr = PhysicalEntity_hasProperty(physical_entity_ptr, entity_property);
    Editor_addPhysicalEntity(editor_ptr, physical_entity_ptr);

    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
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
                           "    bqbiol:isPartOf <https://identifiers.org/FMA:1234> .";
    ASSERT_TRUE(RDF_equals_rdf_vs_string(rdf_ptr, expected, "turtle"));
    Editor_delete(editor_ptr);
    PhysicalEntity_delete(physical_entity_ptr);
    PhysicalProperty_delete(entity_property);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, TestPhysicalEntitySBML2) {
    RDF *rdf_ptr = RDF_new();

    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);


    PhysicalEntity *physical_entity_ptr = Editor_newPhysicalEntity(editor_ptr);
    physical_entity_ptr = PhysicalEntity_about(physical_entity_ptr, "species0001", MODEL_URI);
    physical_entity_ptr = PhysicalEntity_identity(physical_entity_ptr, "uniprot:PD12345");
    physical_entity_ptr = PhysicalEntity_isPartOf(physical_entity_ptr, "FMA:1234", IDENTIFIERS_URI);
    physical_entity_ptr = PhysicalEntity_hasPropertyFull(physical_entity_ptr, "EntityProperty", LOCAL_URI, "opb:OPB_12345");
    Editor_addPhysicalEntity(editor_ptr, physical_entity_ptr);

    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
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
                           "    bqbiol:isPartOf <https://identifiers.org/FMA:1234> .";
    ASSERT_TRUE(RDF::equals(rdf_ptr, expected, "turtle"));
    Editor_delete(editor_ptr);
    PhysicalEntity_delete(physical_entity_ptr);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, TestPhysicalEntitySBML3) {
    RDF *rdf_ptr = RDF_new();

    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);


    PhysicalEntity *physical_entity_ptr = Editor_newPhysicalEntity(editor_ptr);
    physical_entity_ptr = PhysicalEntity_about(physical_entity_ptr, "species0001", MODEL_URI);
    physical_entity_ptr = PhysicalEntity_identity(physical_entity_ptr, "uniprot:PD12345");
    physical_entity_ptr = PhysicalEntity_isPartOf(physical_entity_ptr, "FMA:1234", IDENTIFIERS_URI);
    physical_entity_ptr = PhysicalEntity_hasPropertyisVersionOf(physical_entity_ptr, "opb:OPB_12345");
    Editor_addPhysicalEntity(editor_ptr, physical_entity_ptr);

    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
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
                           "    bqbiol:isPartOf <https://identifiers.org/FMA:1234> .";
    ASSERT_TRUE(RDF::equals(rdf_ptr, expected, "turtle"));
    Editor_delete(editor_ptr);
    PhysicalEntity_delete(physical_entity_ptr);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, TestPhysicalEntityCellML1) {

    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      CellMLFactory::getCellML(CELLML_TOY).c_str(), false, false);

    PhysicalProperty *entity_property = Editor_newPhysicalProperty(editor_ptr);
    entity_property = PhysicalProperty_about(entity_property, "main.Volume", MODEL_URI);
    entity_property = PhysicalProperty_isVersionOf(entity_property, "opb:OPB_00154");
    entity_property = PhysicalProperty_isPropertyOf(entity_property, "entity0", LOCAL_URI);

    PhysicalEntity *entity = Editor_newPhysicalEntity(editor_ptr);
    entity = PhysicalEntity_about(entity, "entity0", LOCAL_URI);
    entity = PhysicalEntity_identity(entity, "fma:9670");
    entity = PhysicalEntity_isPartOf(entity, "fma:18228", IDENTIFIERS_URI);
    entity = PhysicalEntity_hasProperty(entity, entity_property);

    Editor_addPhysicalEntity(editor_ptr, entity);

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
    ASSERT_TRUE(RDF::equals(rdf_ptr, expected, "turtle"));

    PhysicalEntity_delete(entity);
    PhysicalProperty_delete(entity_property);
    Editor_delete(editor_ptr);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, TestPhysicalEntityCellML2) {

    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      CellMLFactory::getCellML(CELLML_TOY).c_str(), false, false);

    PhysicalEntity *entity = Editor_newPhysicalEntity(editor_ptr);
    entity = PhysicalEntity_about(entity, "entity0", LOCAL_URI);
    entity = PhysicalEntity_identity(entity, "fma:9670");
    entity = PhysicalEntity_isPartOf(entity, "fma:18228", IDENTIFIERS_URI);
    entity = PhysicalEntity_hasPropertyFull(entity, "main.Volume", MODEL_URI, "opb:OPB_00154");

    Editor_addPhysicalEntity(editor_ptr, entity);

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
    ASSERT_TRUE(RDF::equals(rdf_ptr, expected, "turtle"));

    PhysicalEntity_delete(entity);
    Editor_delete(editor_ptr);
    RDF_delete(rdf_ptr);
}


TEST_F(CAPITests, TestPhysicalEntityCellML3) {

    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      CellMLFactory::getCellML(CELLML_TOY).c_str(), false, false);

    PhysicalEntity *entity = Editor_newPhysicalEntity(editor_ptr);
    entity = PhysicalEntity_identity(entity, "fma:9670");
    entity = PhysicalEntity_isPartOf(entity, "fma:18228", IDENTIFIERS_URI);
    entity = PhysicalEntity_hasPropertyFull(entity, "main.Volume", MODEL_URI, "opb:OPB_00154");

    Editor_addPhysicalEntity(editor_ptr, entity);

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
    ASSERT_TRUE(RDF::equals(rdf_ptr, expected, "turtle"));

    PhysicalEntity_delete(entity);
    Editor_delete(editor_ptr);
    RDF_delete(rdf_ptr);
}


TEST_F(CAPITests, TestPhysicalEntityLocations) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    PhysicalEntity *physical_entity_ptr = Editor_newPhysicalEntity(editor_ptr);
    physical_entity_ptr = PhysicalEntity_about(physical_entity_ptr, "ALocalID", LOCAL_URI);
    physical_entity_ptr = PhysicalEntity_isPartOf(physical_entity_ptr, "FMA:8376", IDENTIFIERS_URI);
    physical_entity_ptr = PhysicalEntity_isPartOf(physical_entity_ptr, "FMA:8377", IDENTIFIERS_URI);
    physical_entity_ptr = PhysicalEntity_isPartOf(physical_entity_ptr, "FMA:8378", IDENTIFIERS_URI);
    Editor_addPhysicalEntity(editor_ptr, physical_entity_ptr);
    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:ALocalID\n"
                           "    bqbiol:isPartOf <https://identifiers.org/FMA:8376>, <https://identifiers.org/FMA:8377>, <https://identifiers.org/FMA:8378> .\n";
    ASSERT_TRUE(RDF::equals(rdf_ptr, expected, "turtle"));
    Editor_delete(editor_ptr);
    RDF_delete(rdf_ptr);
    PhysicalEntity_delete(physical_entity_ptr);
}

TEST_F(CAPITests, TestPhysicalProcessSBML1) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    PhysicalProcess *physical_process_ptr = Editor_newPhysicalProcess(editor_ptr);

    physical_process_ptr = PhysicalProcess_about(physical_process_ptr, "reaction0000", MODEL_URI);
    physical_process_ptr = PhysicalProcess_addSource(physical_process_ptr, "species0000", MODEL_URI, 1);
    physical_process_ptr = PhysicalProcess_addSink(physical_process_ptr, "species0001", MODEL_URI, 1);
    physical_process_ptr = PhysicalProcess_addMediator(physical_process_ptr, "species0002", MODEL_URI);
    physical_process_ptr = PhysicalProcess_hasPropertyFull(physical_process_ptr, "ReactionProperty", LOCAL_URI, "opb:OPB_00592");

    Editor_addPhysicalProcess(editor_ptr, physical_process_ptr);

    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
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
    ASSERT_TRUE(RDF::equals(rdf_ptr, expected, "turtle"));

    Editor_delete(editor_ptr);
    PhysicalProcess_delete(physical_process_ptr);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, TestPhysicalProcessSBML2) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    PhysicalProcess *physical_process_ptr = Editor_newPhysicalProcess(editor_ptr);

    physical_process_ptr = PhysicalProcess_about(physical_process_ptr, "reaction0000", MODEL_URI);
    physical_process_ptr = PhysicalProcess_addSource(physical_process_ptr, "species0000", MODEL_URI, 1);
    physical_process_ptr = PhysicalProcess_addSink(physical_process_ptr, "species0001", MODEL_URI, 1);
    physical_process_ptr = PhysicalProcess_addMediator(physical_process_ptr, "species0002", MODEL_URI);
    physical_process_ptr = PhysicalProcess_hasPropertyisVersionOf(physical_process_ptr, "opb:OPB_00592");

    Editor_addPhysicalProcess(editor_ptr, physical_process_ptr);

    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
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
    ASSERT_TRUE(RDF::equals(rdf_ptr, expected, "turtle"));

    Editor_delete(editor_ptr);
    PhysicalProcess_delete(physical_process_ptr);
    RDF_delete(rdf_ptr);
}


TEST_F(CAPITests, TestPhysicalProcessCellML1) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      CellMLFactory::getCellML(CELLML_TOY_EXTENDED).c_str(), true, false);
    PhysicalProcess *physical_process_ptr = Editor_newPhysicalProcess(editor_ptr);

    physical_process_ptr = PhysicalProcess_about(physical_process_ptr, "Process", LOCAL_URI);
    physical_process_ptr = PhysicalProcess_addSource(physical_process_ptr, "entity1", LOCAL_URI, 1);
    physical_process_ptr = PhysicalProcess_addSink(physical_process_ptr, "entity2", LOCAL_URI, 1);
    physical_process_ptr = PhysicalProcess_addMediator(physical_process_ptr, "entity3", LOCAL_URI);
    physical_process_ptr = PhysicalProcess_hasPropertyFull(physical_process_ptr, "main.ReactionRate", MODEL_URI, "opb:OPB_00592");

    Editor_addPhysicalProcess(editor_ptr, physical_process_ptr);

    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
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
    ASSERT_TRUE(RDF::equals(rdf_ptr, expected, "turtle"));

    Editor_delete(editor_ptr);
    PhysicalProcess_delete(physical_process_ptr);
    RDF_delete(rdf_ptr);
}


TEST_F(CAPITests, TestPhysicalProcessCellML2) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      CellMLFactory::getCellML(CELLML_TOY_EXTENDED).c_str(), true, false);
    PhysicalProcess *physical_process_ptr = Editor_newPhysicalProcess(editor_ptr);

    physical_process_ptr = PhysicalProcess_addSource(physical_process_ptr, "entity1", LOCAL_URI, 1);
    physical_process_ptr = PhysicalProcess_addSink(physical_process_ptr, "entity2", LOCAL_URI, 1);
    physical_process_ptr = PhysicalProcess_addMediator(physical_process_ptr, "entity3", LOCAL_URI);
    physical_process_ptr = PhysicalProcess_hasPropertyFull(physical_process_ptr, "main.ReactionRate", MODEL_URI, "opb:OPB_00592");

    Editor_addPhysicalProcess(editor_ptr, physical_process_ptr);

    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix semsim: <http://bime.uw.edu/semsim/> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
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
                           "    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_00592> .";
    ASSERT_TRUE(RDF::equals(rdf_ptr, expected, "turtle"));

    Editor_delete(editor_ptr);
    PhysicalProcess_delete(physical_process_ptr);
    RDF_delete(rdf_ptr);
}


TEST_F(CAPITests, TestEnergyDiffSBML1) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      CellMLFactory::getCellML(CELLML_TOY_EXTENDED).c_str(), true, false);
    EnergyDiff *energy_diff_ptr = Editor_newEnergyDiff(editor_ptr);

    energy_diff_ptr = EnergyDiff_about(energy_diff_ptr, "main.MembraneVoltage", MODEL_URI);
    energy_diff_ptr = EnergyDiff_addSource(energy_diff_ptr, "source_23", MODEL_URI);
    energy_diff_ptr = EnergyDiff_addSink(energy_diff_ptr, "sink_12", MODEL_URI);
    energy_diff_ptr = EnergyDiff_hasPropertyFull(energy_diff_ptr, "parameter_metaid_0", LOCAL_URI, "opb:OPB_01058");

    Editor_addEnergyDiff(editor_ptr, energy_diff_ptr);

    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix semsim: <http://bime.uw.edu/semsim/> .\n"
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
                           "local:parameter_metaid_0\n"
                           "    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#main.MembraneVoltage> ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_01058> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#main.MembraneVoltage>\n"
                           "    semsim:hasSinkParticipant local:SinkParticipant0000 ;\n"
                           "    semsim:hasSourceParticipant local:SourceParticipant0000 .";
    ASSERT_TRUE(RDF::equals(rdf_ptr, expected, "turtle"));

    Editor_delete(editor_ptr);
    EnergyDiff_delete(energy_diff_ptr);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, TestEnergyDiffSBML2) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      CellMLFactory::getCellML(CELLML_TOY_EXTENDED).c_str(), true, false);
    EnergyDiff *energy_diff_ptr = Editor_newEnergyDiff(editor_ptr);

    energy_diff_ptr = EnergyDiff_about(energy_diff_ptr, "main.MembraneVoltage", MODEL_URI);
    energy_diff_ptr = EnergyDiff_addSource(energy_diff_ptr, "source_23", MODEL_URI);
    energy_diff_ptr = EnergyDiff_addSink(energy_diff_ptr, "sink_12", MODEL_URI);
    energy_diff_ptr = EnergyDiff_hasPropertyisVersionOf(energy_diff_ptr, "opb:OPB_01058");

    Editor_addEnergyDiff(editor_ptr, energy_diff_ptr);

    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix semsim: <http://bime.uw.edu/semsim/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:EnergyDiffProperty0000\n"
                           "    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#main.MembraneVoltage> ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_01058> .\n"
                           "\n"
                           "local:SinkParticipant0000\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#sink_12> .\n"
                           "\n"
                           "local:SourceParticipant0000\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#source_23> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#main.MembraneVoltage>\n"
                           "    semsim:hasSinkParticipant local:SinkParticipant0000 ;\n"
                           "    semsim:hasSourceParticipant local:SourceParticipant0000 .";
    ASSERT_TRUE(RDF::equals(rdf_ptr, expected, "turtle"));

    Editor_delete(editor_ptr);
    EnergyDiff_delete(energy_diff_ptr);
    RDF_delete(rdf_ptr);
}


TEST_F(CAPITests, TestEnergyDiffCellML1) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      CellMLFactory::getCellML(CELLML_TOY_EXTENDED).c_str(), true, false);
    EnergyDiff *energy_diff_ptr = Editor_newEnergyDiff(editor_ptr);

    energy_diff_ptr = EnergyDiff_about(energy_diff_ptr, "main.MembraneVoltage", MODEL_URI);
    energy_diff_ptr = EnergyDiff_addSource(energy_diff_ptr, "entity1", LOCAL_URI);
    energy_diff_ptr = EnergyDiff_addSink(energy_diff_ptr, "entity2", LOCAL_URI);
    energy_diff_ptr = EnergyDiff_hasPropertyFull(energy_diff_ptr, "EnergyDiffProperty", MODEL_URI, "opb:OPB_00592");

    Editor_addEnergyDiff(editor_ptr, energy_diff_ptr);

    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix semsim: <http://bime.uw.edu/semsim/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#EnergyDiffProperty>\n"
                           "    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#main.MembraneVoltage> ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_00592> .\n"
                           "\n"
                           "local:SinkParticipant0000\n"
                           "    semsim:hasPhysicalEntityReference local:entity2 .\n"
                           "\n"
                           "local:SourceParticipant0000\n"
                           "    semsim:hasPhysicalEntityReference local:entity1 .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#main.MembraneVoltage>\n"
                           "    semsim:hasSinkParticipant local:SinkParticipant0000 ;\n"
                           "    semsim:hasSourceParticipant local:SourceParticipant0000 .";
    ASSERT_TRUE(RDF::equals(rdf_ptr, expected, "turtle"));

    Editor_delete(editor_ptr);
    EnergyDiff_delete(energy_diff_ptr);
    RDF_delete(rdf_ptr);
}


TEST_F(CAPITests, TestRDFTwice1) {
    RDF *rdf_ptr1 = RDF_new();
    RDF *rdf_ptr2 = RDF_new();
    ASSERT_NE(rdf_ptr1, rdf_ptr2);
    RDF_delete(rdf_ptr1);
    RDF_delete(rdf_ptr2);
}

TEST_F(CAPITests, TestRDFTwice3) {
    RDF *rdf_ptr1 = RDF_new();
    RDF *rdf_ptr2 = RDF_new();
    ASSERT_NE(rdf_ptr1->getStorage(), rdf_ptr2->getStorage());
    RDF_delete(rdf_ptr1);
    RDF_delete(rdf_ptr2);
}

TEST_F(CAPITests, RDFgetArchiveUri) {
    RDF *rdf_ptr = RDF_new();
    char *actual = RDF_getArchiveUri(rdf_ptr);
    const char *expected = "http://omex-library.org/NewOmex.omex/";
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected, actual);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}


TEST_F(CAPITests, RDFgetLocalUri) {
    RDF *rdf_ptr = RDF_new();
    char *actual = RDF_getLocalUri(rdf_ptr);
    const char *expected = "http://omex-library.org/NewOmex.omex/NewModel.rdf#";
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected, actual);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, RDFgetModelUri) {
    RDF *rdf_ptr = RDF_new();
    char *actual = RDF_getModelUri(rdf_ptr);
    const char *expected = "http://omex-library.org/NewOmex.omex/NewModel.xml";
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected, actual);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, RDFgetOmexRepository) {
    RDF *rdf_ptr = RDF_new();
    char *actual = RDF_getRepositoryUri(rdf_ptr);
    const char *expected = "http://omex-library.org/";
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected, actual);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, RDFgetModelLevelAnnotationUri) {
    RDF *rdf_ptr = RDF_new();
    char *actual = RDF_getModelLevelAnnotationUri(rdf_ptr);
    const char *expected = "http://omex-library.org/NewOmex.omex/NewModel.xml#NewModel";
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected, actual);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}


TEST_F(CAPITests, RDFsetModelMetaid) {
    RDF *rdf_ptr = RDF_new();
    RDF_setModelMetaid(rdf_ptr, "ModelMetaid");
    const char *expected = "http://omex-library.org/NewOmex.omex/NewModel.xml#ModelMetaid";
    char *metaid = RDF_getModelMetaid(rdf_ptr);
    ASSERT_STREQ("ModelMetaid", metaid);
    free_c_char_star(metaid);
    char *actual = RDF_getModelLevelAnnotationUri(rdf_ptr);
    ASSERT_STREQ(expected, actual);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}


TEST_F(CAPITests, EditorgetLocalUri) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    char *actual = Editor_getLocalUri(editor_ptr);
    const char *expected = "http://omex-library.org/NewOmex.omex/NewModel.rdf#";
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected, actual);
    Editor_delete(editor_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, EditorgetModelUri) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    char *actual = Editor_getModelUri(editor_ptr);
    const char *expected = "http://omex-library.org/NewOmex.omex/NewModel.xml";
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected, actual);
    Editor_delete(editor_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, EditorgetOmexRepository) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    char *actual = Editor_getRepositoryUri(editor_ptr);
    const char *expected = "http://omex-library.org/";
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected, actual);
    Editor_delete(editor_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, EditorsetOmexRepository) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    RDF_setRepositoryUri(rdf_ptr, "http://newOmexRepo.org");
    const char *expected = "http://newOmexRepo.org/";
    char *actual = Editor_getRepositoryUri(editor_ptr);
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected, actual);
    Editor_delete(editor_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, EditorsetArchiveUri) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    RDF_setArchiveUri(rdf_ptr, "newArchive.omex");
    char *actual = Editor_getArchiveUri(editor_ptr);
    const char *expected = "http://omex-library.org/newArchive.omex/";
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected, actual);
    Editor_delete(editor_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, RDFsetModelUri) {
    RDF *rdf_ptr = RDF_new();
    RDF_setModelUri(rdf_ptr, "newModelName");
    const char *expected = "http://omex-library.org/NewOmex.omex/newModelName.xml";
    char *actual = RDF_getModelUri(rdf_ptr);
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected, actual);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, RDFgetModelUriDefault) {
    RDF *rdf_ptr = RDF_new();
    const char *expected = "http://omex-library.org/NewOmex.omex/NewModel.xml";
    char *actual = RDF_getModelUri(rdf_ptr);
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected, actual);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, RDFsetLocalUri) {
    RDF *rdf_ptr = RDF_new();
    RDF_setModelUri(rdf_ptr, "newModelName");
    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/newModelName.rdf#> .";
    char *actual = RDF_getLocalUri(rdf_ptr);
    std::cout << actual << std::endl;
    ASSERT_TRUE(RDF::equals(rdf_ptr, expected));
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, EditorGetLocalUri) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    const char *expected = "http://omex-library.org/NewOmex.omex/NewModel.rdf#";
    char *actual = Editor_getLocalUri(editor_ptr);
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected, actual);
    Editor_delete(editor_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}


TEST_F(CAPITests, EditoraddCreator) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    Editor_addCreator(editor_ptr, "1234-1234-1234-1234");
    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#TestModelNotAnnotated>\n"
                           "    <http://purl.org/dc/terms/creator> <https://orcid.org/1234-1234-1234-1234> .\n"
                           "\n"
                           "";
    char *actual = RDF_toString(rdf_ptr, "turtle");
    std::cout << actual << std::endl;
    ASSERT_TRUE(RDF::equals(rdf_ptr, expected, "turtle"));
    Editor_delete(editor_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, EditoraddContributor) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    Editor_addContributor(editor_ptr, "1234-1234-1234-1234");
    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#>\n"
                           "    <http://purl.org/dc/terms/contributor> <https://orcid.org/1234-1234-1234-1234> .\n"
                           "\n"
                           "";
    char *actual = RDF_toString(rdf_ptr, "turtle");
    std::cout << actual << std::endl;
    ASSERT_TRUE(RDF::equals(rdf_ptr, expected, "turtle"));
    Editor_delete(editor_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, Editortaxon) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    Editor_addTaxon(editor_ptr, "9898");
    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix NCBI_Taxon: <https://identifiers.org/taxonomy:> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#TestModelNotAnnotated>\n"
                           "    bqbiol:hasTaxon NCBI_Taxon:9898 .\n"
                           "\n"
                           "";
    char *actual = RDF_toString(rdf_ptr, "turtle");
    std::cout << actual << std::endl;
    ASSERT_TRUE(RDF::equals(rdf_ptr, expected, "turtle"));
    Editor_delete(editor_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, Editorpubmed) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    Editor_addPubmed(editor_ptr, "12345678");
    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#TestModelNotAnnotated>\n"
                           "    <http://biomodels.net/model-qualifiers/isDescribedBy> <https://identifiers.org/pubmed:12345678> .\n"
                           "\n"
                           "";
    char *actual = RDF_toString(rdf_ptr, "turtle");
    std::cout << actual << std::endl;
    ASSERT_TRUE(RDF::equals(rdf_ptr, expected, "turtle"));
    Editor_delete(editor_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, EditoraddDescription) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    Editor_addDescription(editor_ptr, "A model");
    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#TestModelNotAnnotated>\n"
                           "    <http://purl.org/dc/terms/description> \"A model\" .\n"
                           "\n"
                           "";
    char *actual = RDF_toString(rdf_ptr, "turtle");
    std::cout << actual << std::endl;
    ASSERT_TRUE(RDF::equals(rdf_ptr, expected, "turtle"));
    Editor_delete(editor_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, EditoraddDateCreated) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    Editor_addDateCreated(editor_ptr, "2020-11-23");
    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix dc: <http://purl.org/dc/terms/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#TestModelNotAnnotated>\n"
                           "    dc:created \"2020-11-23\"^^dc:W3CDTF\n .";

    char *actual = RDF_toString(rdf_ptr, "turtle");
    std::cout << actual << std::endl;
    ASSERT_TRUE(RDF::equals(rdf_ptr, expected, "turtle"));
    Editor_delete(editor_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, EditoraddParentModel) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    Editor_addParentModel(editor_ptr, "BIOMD000001");
    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqmodel: <http://biomodels.net/model-qualifiers/> .\n"
                           "@prefix biomod: <https://identifiers.org/biomodels.db:> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#TestModelNotAnnotated>\n"
                           "    bqmodel:isDerivedFrom <https://identifiers.org/biomodels.db:BIOMD000001> .\n"
                           "";
    char *actual = RDF_toString(rdf_ptr, "turtle");
    std::cout << actual << std::endl;
    ASSERT_TRUE(RDF::equals(rdf_ptr, expected, "turtle"));
    Editor_delete(editor_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, EditorGetXml) {
    ASSERT_NO_THROW(
            RDF *rdf_ptr = RDF_new();
            Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                              SBMLFactory::getSBML(SBML_INVALID_METAIDS).c_str(), true, true);
            char *xml = Editor_getXml(editor_ptr);
            Editor_delete(editor_ptr);
            free_c_char_star(xml);
            RDF_delete(rdf_ptr);
            );
}


TEST_F(CAPITests, PersonalInformationaddCreator) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    PersonalInformation *information = Editor_newPersonalInformation(editor_ptr);
    PersonalInformation_addCreator(information, "2134-1234-1234-1234");
    Editor_addPersonalInformation(editor_ptr, information);
    char *actual = RDF_toString(rdf_ptr, "turtle");
    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix dc: <http://purl.org/dc/terms/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#TestModelNotAnnotated>\n"
                           "    dc:creator <http://omex-library.org/NewOmex.omex/NewModel.xml#PersonalInfo0000> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#PersonalInfo0000>\n"
                           "    dc:creator <https://identifiers.org/orcid/2134-1234-1234-1234> .";
    std::cout << actual << std::endl;
    ASSERT_TRUE(RDF::equals(rdf_ptr, expected, "turtle"));
    PersonalInformation_delete(information);
    Editor_delete(editor_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

//TEST_F(CAPITests, PersonalInformationaddCurator) {
//    RDF *rdf_ptr = RDF_new();
//    Editor *editor_ptr = rdf_ptr->toEditorPtr(
//            SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(),
//            OMEXMETA_TYPE_SBML
//    );
//    PersonalInformation *information = Editor_newPersonalInformation(editor_ptr);
//    PersonalInformation_addCurator(information, "2134-1234-1234-1234");
//    char *actual = RDF_toString(rdf_ptr, "turtle");
//    const char *expected = "https://identifiers.org/uniprot:PD7363";
//    std::cout << actual << std::endl;
//    ASSERT_STREQ(expected, actual);
//    Editor_delete(editor_ptr);
//    free_c_char_star(actual);
//    RDF_delete(rdf_ptr);
//
//}

TEST_F(CAPITests, PersonalInformationaddName) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);

    PersonalInformation *information = Editor_newPersonalInformation(editor_ptr);
    PersonalInformation_addName(information, "Ciaran Welsh");
    Editor_addPersonalInformation(editor_ptr, information);
    char *actual = RDF_toString(rdf_ptr, "turtle");
    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix foaf: <http://xmlns.com/foaf/0.1/> .\n"
                           "@prefix dc: <http://purl.org/dc/terms/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#TestModelNotAnnotated>\n"
                           "    dc:creator <http://omex-library.org/NewOmex.omex/NewModel.xml#PersonalInfo0000> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#PersonalInfo0000>\n"
                           "    foaf:name \"Ciaran Welsh\" .\n"
                           "\n"
                           "";
    std::cout << actual << std::endl;
    ASSERT_TRUE(RDF::equals(rdf_ptr, expected, "turtle"));
    PersonalInformation_delete(information);
    Editor_delete(editor_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, PersonalInformationaddMbox) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    PersonalInformation *information = Editor_newPersonalInformation(editor_ptr);
    PersonalInformation_addMbox(information, "cwelsh2@ue.edu");
    Editor_addPersonalInformation(editor_ptr, information);
    char *actual = RDF_toString(rdf_ptr, "turtle");
    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix foaf: <http://xmlns.com/foaf/0.1/> .\n"
                           "@prefix dc: <http://purl.org/dc/terms/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#TestModelNotAnnotated>\n"
                           "    dc:creator <http://omex-library.org/NewOmex.omex/NewModel.xml#PersonalInfo0000> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#PersonalInfo0000>\n"
                           "    foaf:mbox \"cwelsh2@ue.edu\" .\n"
                           "\n"
                           "";
    std::cout << actual << std::endl;
    ASSERT_TRUE(RDF::equals(rdf_ptr, expected, "turtle"));
    PersonalInformation_delete(information);
    Editor_delete(editor_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, PersonalInformationaddAccountName) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    PersonalInformation *information = Editor_newPersonalInformation(editor_ptr);
    PersonalInformation_addAccountName(information, "2134-1234-1234-1234");
    Editor_addPersonalInformation(editor_ptr, information);
    char *actual = RDF_toString(rdf_ptr, "turtle");
    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix foaf: <http://xmlns.com/foaf/0.1/> .\n"
                           "@prefix dc: <http://purl.org/dc/terms/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#TestModelNotAnnotated>\n"
                           "    dc:creator <http://omex-library.org/NewOmex.omex/NewModel.xml#PersonalInfo0000> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#PersonalInfo0000>\n"
                           "    foaf:accountName <https://orcid.org/2134-1234-1234-1234> .\n"
                           "\n";
    std::cout << actual << std::endl;
    ASSERT_TRUE(RDF::equals(rdf_ptr, expected, "turtle"));
    PersonalInformation_delete(information);
    Editor_delete(editor_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, PersonalInformationaddAccountServiceHomepage) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    PersonalInformation *information = Editor_newPersonalInformation(editor_ptr);
    PersonalInformation_addAccountServiceHomepage(information, "https://github.com/sys-bio/libOmexMeta");
    Editor_addPersonalInformation(editor_ptr, information);
    char *actual = RDF_toString(rdf_ptr, "turtle");
    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix foaf: <http://xmlns.com/foaf/0.1/> .\n"
                           "@prefix dc: <http://purl.org/dc/terms/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#TestModelNotAnnotated>\n"
                           "    dc:creator <http://omex-library.org/NewOmex.omex/NewModel.xml#PersonalInfo0000> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#PersonalInfo0000>\n"
                           "    foaf:accountServiceHomepage <https://github.com/sys-bio/libOmexMeta> .\n"
                           "\n"
                           "";
    std::cout << actual << std::endl;
    ASSERT_TRUE(RDF::equals(rdf_ptr, expected, "turtle"));
    PersonalInformation_delete(information);
    Editor_delete(editor_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, PersonalInformationaddFoafUri) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    PersonalInformation *information = Editor_newPersonalInformation(editor_ptr);
    PersonalInformation_addFoafLiteral(information, "accountServiceHomepage", "https://github.com/sys-bio/libOmexMeta");
    Editor_addPersonalInformation(editor_ptr, information);
    char *actual = RDF_toString(rdf_ptr, "turtle");
    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix foaf: <http://xmlns.com/foaf/0.1/> .\n"
                           "@prefix dc: <http://purl.org/dc/terms/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#TestModelNotAnnotated>\n"
                           "    dc:creator <http://omex-library.org/NewOmex.omex/NewModel.xml#PersonalInfo0000> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#PersonalInfo0000>\n"
                           "    foaf:accountServiceHomepage \"https://github.com/sys-bio/libOmexMeta\" .\n"
                           "\n"
                           "";
    std::cout << actual << std::endl;
    ASSERT_TRUE(RDF::equals(rdf_ptr, expected, "turtle"));
    PersonalInformation_delete(information);
    Editor_delete(editor_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, PersonalInformationaddFoafLiteral) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    PersonalInformation *information = Editor_newPersonalInformation(editor_ptr);
    PersonalInformation_addFoafLiteral(information, "name", "Ciaran Welsh");
    Editor_addPersonalInformation(editor_ptr, information);
    char *actual = RDF_toString(rdf_ptr, "turtle");
    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix foaf: <http://xmlns.com/foaf/0.1/> .\n"
                           "@prefix dc: <http://purl.org/dc/terms/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#TestModelNotAnnotated>\n"
                           "    dc:creator <http://omex-library.org/NewOmex.omex/NewModel.xml#PersonalInfo0000> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#PersonalInfo0000>\n"
                           "    foaf:name \"Ciaran Welsh\" .\n"
                           "\n";
    std::cout << actual << std::endl;
    ASSERT_TRUE(RDF::equals(rdf_ptr, expected, "turtle"));
    PersonalInformation_delete(information);
    Editor_delete(editor_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, PersonalInformationgetMetaid) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    PersonalInformation *information = Editor_newPersonalInformation(editor_ptr);
    char *actual = PersonalInformation_getMetaid(information);
    Editor_addPersonalInformation(editor_ptr, information);
    editor_ptr->addPersonalInformation(information);
    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix dc: <http://purl.org/dc/terms/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#TestModelNotAnnotated>\n"
                           "    dc:creator <http://omex-library.org/NewOmex.omex/NewModel.xml#PersonalInfo0000> .\n"
                           "";
    std::cout << actual << std::endl;
    ASSERT_TRUE(RDF::equals(rdf_ptr, expected, "turtle"));
    PersonalInformation_delete(information);
    Editor_delete(editor_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}


TEST_F(CAPITests, RDFToEditorTestWithSemanticExtraction) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr, SBMLFactory::getSBML(SBML_SEMANTIC_EXTRACTION_MODEL).c_str(), true, true);

    char *actual = RDF_toString(rdf_ptr, "turtle");
    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix semsim: <http://bime.uw.edu/semsim/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:MediatorParticipant0000\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#sp_5> .\n"
                           "\n"
                           "local:ProcessProperty0000\n"
                           "    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#react1> ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_00592> .\n"
                           "\n"
                           "local:ProcessProperty0001\n"
                           "    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#react2> ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_00592> .\n"
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
                           "    semsim:hasSinkParticipant local:SinkParticipant0000 ;\n"
                           "    semsim:hasSourceParticipant local:SourceParticipant0000 .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#react2>\n"
                           "    semsim:hasMediatorParticipant local:MediatorParticipant0000 ;\n"
                           "    semsim:hasSinkParticipant local:SinkParticipant0001 ;\n"
                           "    semsim:hasSourceParticipant local:SourceParticipant0001, local:SourceParticipant0002 .\n"
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
                           "    bqbiol:isPartOf <http://omex-library.org/NewOmex.omex/NewModel.xml#cytosol> .\n";
    ASSERT_TRUE(RDF::equals(rdf_ptr, expected, "turtle"));

    Editor_delete(editor_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}


TEST_F(CAPITests, RDFToEditorTestWithoutSemanticExtraction) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr, SBMLFactory::getSBML(SBML_SEMANTIC_EXTRACTION_MODEL).c_str(), true, false);

    char *actual = RDF_toString(rdf_ptr, "turtle");
    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n";
    printf("%s", actual);
    ASSERT_TRUE(RDF::equals(rdf_ptr, expected, "turtle"));

    Editor_delete(editor_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, EditorStripAnnotations) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr, SBMLFactory::getSBML(SBML_SEMANTIC_EXTRACTION_MODEL).c_str(), false, false);
    char *actual = Editor_stripAnnotations(editor_ptr);
    const char *expected = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                           "<sbml xmlns=\"http://www.sbml.org/sbml/level3/version1/core\" level=\"3\" version=\"1\">\n"
                           "    <model metaid=\"ToyModel\" id=\"ToyModel\">\n"
                           "        <listOfCompartments>\n"
                           "            <compartment id=\"cytosol\" metaid=\"comp1\" spatialDimensions=\"3\" size=\"1\" constant=\"true\"/>\n"
                           "            <compartment id=\"extraCell\" metaid=\"comp2\" spatialDimensions=\"3\" size=\"10\" constant=\"true\"/>\n"
                           "        </listOfCompartments>\n"
                           "        <listOfSpecies>\n"
                           "            <species id=\"A\" metaid=\"sp_1\" compartment=\"cytosol\" initialConcentration=\"10\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\">\n"
                           "                \n"
                           "            </species>\n"
                           "            <species id=\"B\" metaid=\"sp_2\" compartment=\"cytosol\" initialConcentration=\"0\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                           "            <species id=\"Ca\" metaid=\"sp_3\" compartment=\"cytosol\" initialConcentration=\"2\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                           "            <species id=\"PlasmaCa\" metaid=\"sp_4\" compartment=\"extraCell\" initialConcentration=\"3\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                           "            <species id=\"Enzyme\" metaid=\"sp_5\" compartment=\"cytosol\" initialConcentration=\"2\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                           "        </listOfSpecies>\n"
                           "        <listOfParameters>\n"
                           "            <parameter id=\"k1\" value=\"0.1\" constant=\"true\"/>\n"
                           "            <parameter id=\"k2\" value=\"0.1\" constant=\"true\"/>\n"
                           "        </listOfParameters>\n"
                           "        <listOfReactions>\n"
                           "            <reaction id=\"r1\" metaid=\"react1\" reversible=\"false\" fast=\"false\">\n"
                           "                <listOfReactants>\n"
                           "                    <speciesReference species=\"B\" stoichiometry=\"1\" constant=\"true\"/>\n"
                           "                </listOfReactants>\n"
                           "                <listOfProducts>\n"
                           "                    <speciesReference species=\"A\" stoichiometry=\"2\" constant=\"true\"/>\n"
                           "                </listOfProducts>\n"
                           "                <kineticLaw>\n"
                           "                    <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
                           "                        <apply>\n"
                           "                            <times/>\n"
                           "                            <ci>k2</ci>\n"
                           "                            <ci>B</ci>\n"
                           "                        </apply>\n"
                           "                    </math>\n"
                           "                </kineticLaw>\n"
                           "            </reaction>\n"
                           "            <reaction id=\"r2\" metaid=\"react2\" reversible=\"false\" fast=\"false\">\n"
                           "                <listOfReactants>\n"
                           "                    <speciesReference species=\"Ca\" stoichiometry=\"1\" constant=\"true\"/>\n"
                           "                    <speciesReference species=\"A\" stoichiometry=\"1\" constant=\"true\"/>\n"
                           "                </listOfReactants>\n"
                           "                <listOfProducts>\n"
                           "                    <speciesReference species=\"PlasmaCa\" stoichiometry=\"1\" constant=\"true\"/>\n"
                           "                </listOfProducts>\n"
                           "                <listOfModifiers>\n"
                           "                    <modifierSpeciesReference species=\"Enzyme\"/>\n"
                           "                </listOfModifiers>\n"
                           "                <kineticLaw>\n"
                           "                    <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
                           "                        <apply>\n"
                           "                            <times/>\n"
                           "                            <ci>k2</ci>\n"
                           "                            <ci>Ca</ci>\n"
                           "                        </apply>\n"
                           "                    </math>\n"
                           "                </kineticLaw>\n"
                           "            </reaction>\n"
                           "        </listOfReactions>\n"
                           "    </model>\n"
                           "</sbml>\n";
    printf("%s", actual);
    ASSERT_STREQ(expected, actual);

    Editor_delete(editor_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}
