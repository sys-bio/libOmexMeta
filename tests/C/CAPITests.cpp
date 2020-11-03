//
// Created by Ciaran on 5/12/2020.
//

#include "gtest/gtest.h"

#include "AnnotationSamples.h"
#include "SBMLFactory.h"

#include "OmexMetaTestUtils.h"
#include "omexmeta/OmexMetaCApi.h"
#include <filesystem>
#include <fstream>


using namespace omexmeta;

class CAPITests : public ::testing::Test {
public:
    AnnotationSamples samples = AnnotationSamples();

    std::filesystem::path fnamep = std::filesystem::current_path() / +"annotation.rdf";
    std::string fname;

    CAPITests() {
        fname = fnamep.string();
    }

    void TearDown() override {
        if (std::filesystem::exists(fname)) {
            std::filesystem::remove(fname);
        }
    };
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
    ASSERT_TRUE(OmexMetaTestUtils::equals(rdf_ptr, expected, "rdfxml"));
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, RDF_fromString) {
    RDF *rdf_ptr = RDF_fromString(samples.composite_annotation_pf.c_str(), "rdfxml", "RDF_fromStringTest.rdf");
    int expected = 6;
    int actual = RDF_size(rdf_ptr);
    ASSERT_EQ(expected, actual);
    RDF_delete(rdf_ptr);
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
    ASSERT_TRUE(OmexMetaTestUtils::equals(rdf_ptr, expected, "turtle"));
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, RDF_fromUri) {
    RDF *rdf_ptr = RDF_fromUri(samples.sbml_url1.c_str(), "rdfxml");
    int expected = 277;
    int actual = RDF_size(rdf_ptr);
    ASSERT_EQ(expected, actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, RDF_addFromUri) {
    RDF *rdf_ptr = RDF_new();
    RDF_addFromUri(rdf_ptr, samples.sbml_url1.c_str(), "rdfxml");
    int expected = 277;
    int actual = RDF_size(rdf_ptr);
    ASSERT_EQ(expected, actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, RDF_addFromUriSqliteStorage) {
    std::filesystem::path fname = std::filesystem::current_path() += "SqliteStorageTest.db";
    RDF *rdf_ptr = RDF_new("sqlite", fname.string().c_str(), "new='yes'");
    RDF_addFromUri(rdf_ptr, samples.sbml_url1.c_str(), "rdfxml");
    int expected = 277;
    int actual = RDF_size(rdf_ptr);
    ASSERT_EQ(expected, actual);
    ASSERT_TRUE(std::filesystem::exists(fname));
    RDF_delete(rdf_ptr);
    std::filesystem::remove(fname);
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

TEST_F(CAPITests, RDFqueryResultsAsStr) {
    RDF *rdf_ptr = RDF_fromString(samples.composite_annotation_pe.c_str(), "rdfxml");

    const char *query = "SELECT ?x ?y ?z \n"
                        "WHERE { ?x ?y ?z }";
    char *results = RDF_query(rdf_ptr, query, "csv");
    std::cout << results << std::endl;
    std::string expected = "x,y,z\n"
                           "http://omex-library.org/NewOmex.omex/NewModel.xml#VLV,http://biomodels.net/biology-qualifiers/isVersionOf,http://identifiers.org/opb/OPB_00154\n"
                           "http://omex-library.org/NewOmex.omex/NewModel.xml#VLV,http://biomodels.net/biology-qualifiers/isPropertyOf,http://omex-library.org/NewOmex.omex/NewModel.xml#entity_0\n"
                           "http://omex-library.org/NewOmex.omex/NewModel.xml#entity_0,http://biomodels.net/biology-qualifiers/is,http://identifiers.org/fma/FMA:9670\n"
                           "http://omex-library.org/NewOmex.omex/NewModel.xml#entity_0,http://biomodels.net/biology-qualifiers/isPartOf,http://identifiers.org/fma/FMA:18228\n";
    ASSERT_STREQ(expected.c_str(), results);
    RDF_delete(rdf_ptr);
    free_c_char_star(results);
}

TEST_F(CAPITests, TestCheckValidMetaid) {
    RDF *rdf_ptr = RDF_new();

    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    Editor_checkValidMetaid(editor_ptr, "#OmexMetaId0000");

    Editor_delete(editor_ptr);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, TestGetMetaID) {
    RDF *rdf_ptr = RDF_new();

    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    char *actual = Editor_getMetaId(editor_ptr, 0);
    std::cout << actual << std::endl;
    const char *expected = "#OmexMetaId0000";
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
    int expected = 13;
    ASSERT_EQ(expected, actual);
    Editor_delete(editor_ptr);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, TestSingularAnnotationSetAbout) {
    RDF *rdf_ptr = RDF_new();

    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);

    SingularAnnotation *singularAnnotation = SingularAnnotation_new(editor_ptr);
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

    SingularAnnotation *singularAnnotation = SingularAnnotation_new(editor_ptr);
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
    RDF *rdf_ptr = RDF_new();

    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);

    SingularAnnotation *singularAnnotation = SingularAnnotation_new(editor_ptr);
    SingularAnnotation_setPredicateFromUri(singularAnnotation, "http://predicate.com/from/uri");
    char *actual = SingularAnnotation_getPredicate(singularAnnotation);
    const char *expected = "http://predicate.com/from/uri";
    ASSERT_STREQ(expected, actual);

    Editor_delete(editor_ptr);
    SingularAnnotation_delete(singularAnnotation);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, TestSingularAnnotationFull) {
    RDF *rdf_ptr = RDF_new();

    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);

    SingularAnnotation *singularAnnotation = SingularAnnotation_new(editor_ptr);
    SingularAnnotation_about(singularAnnotation, "cytosol");
    SingularAnnotation_setPredicateFromUri(singularAnnotation, "http://predicate.com/from/uri");
    SingularAnnotation_setResourceLiteral(singularAnnotation, "Cheese");
    Editor_addSingleAnnotation(editor_ptr, singularAnnotation);

    char *actual = SingularAnnotation_str(singularAnnotation, "turtle");
    printf("%s", actual);
    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#cytosol>\n"
                           "    <http://predicate.com/from/uri> \"Cheese\"^^rdf:string .\n"
                           "\n";
    ASSERT_TRUE(OmexMetaTestUtils::equals(rdf_ptr, expected, "turtle"));

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

    SingularAnnotation *singularAnnotation = SingularAnnotation_new(editor_ptr);
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

    SingularAnnotation *singularAnnotation = SingularAnnotation_new(editor_ptr);
    SingularAnnotation_setResourceUri(singularAnnotation,
                                      "uniprot:PD98723");
    char *actual = SingularAnnotation_getResource(singularAnnotation);
    const char *expected = "https://identifiers.org/uniprot/PD98723";
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

    SingularAnnotation *singularAnnotation = SingularAnnotation_new(editor_ptr);
    SingularAnnotation_setResourceBlank(singularAnnotation, "Nothing");
    char *actual = SingularAnnotation_getResource(singularAnnotation);
    const char *expected = "Nothing";
    ASSERT_STREQ(expected, actual);

    Editor_delete(editor_ptr);
    SingularAnnotation_delete(singularAnnotation);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, TestPhysicalEntity) {
    RDF *rdf_ptr = RDF_new();

    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);

    PhysicalEntity *physical_entity_ptr = PhysicalEntity_new(editor_ptr);
    physical_entity_ptr = PhysicalEntity_about(physical_entity_ptr, "#OmexMetaId0000");
    physical_entity_ptr = PhysicalEntity_hasProperty(physical_entity_ptr, "opb/opb_1234");
    physical_entity_ptr = PhysicalEntity_identity(physical_entity_ptr, "uniprot:PD58736");
    physical_entity_ptr = PhysicalEntity_isPartOf(physical_entity_ptr, "fma:FMA_8764");
    Editor_addPhysicalEntity(editor_ptr, physical_entity_ptr);

    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:EntityProperty0000\n"
                           "    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0000> ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb/opb_1234> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0000>\n"
                           "    bqbiol:is <https://identifiers.org/uniprot/PD58736> ;\n"
                           "    bqbiol:isPartOf <https://identifiers.org/fma/FMA_8764> .";
    ASSERT_TRUE(OmexMetaTestUtils::equals(rdf_ptr, expected, "turtle"));
    Editor_delete(editor_ptr);
    PhysicalEntity_delete(physical_entity_ptr);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, TestPhysicalEntityGetIdentity) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    PhysicalEntity *physical_entity_ptr = PhysicalEntity_new(editor_ptr);
    physical_entity_ptr = PhysicalEntity_about(physical_entity_ptr, "#OmexMetaId0000");
    physical_entity_ptr = PhysicalEntity_hasProperty(physical_entity_ptr, "opb/opb_1234");
    physical_entity_ptr = PhysicalEntity_identity(physical_entity_ptr, "uniprot:PD58736");
    physical_entity_ptr = PhysicalEntity_isPartOf(physical_entity_ptr, "fma:FMA_8764");
    Editor_addPhysicalEntity(editor_ptr, physical_entity_ptr);

    char *actual = PhysicalEntity_getIdentity(physical_entity_ptr);
    const char *expected = "https://identifiers.org/uniprot/PD58736";
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected, actual);

    Editor_delete(editor_ptr);
    // as opposed to PhysicalEntity_delete which would leave behind un-freed nodes.
    PhysicalEntity_freeAll(physical_entity_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, TestPhysicalEntityOptionalProperty) {
    RDF *rdf_ptr = RDF_new();

    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);

    PhysicalEntity *physical_entity_ptr = PhysicalEntity_new(editor_ptr);
    physical_entity_ptr = PhysicalEntity_about(physical_entity_ptr, "#OmexMetaId0000");
    physical_entity_ptr = PhysicalEntity_identity(physical_entity_ptr, "OPB/OPB_12345");
    physical_entity_ptr = PhysicalEntity_hasProperty(physical_entity_ptr, "uniprot:PD58736");
    physical_entity_ptr = PhysicalEntity_isPartOf(physical_entity_ptr, "fma:FMA_8764");
    Editor_addPhysicalEntity(editor_ptr, physical_entity_ptr);

    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:EntityProperty0000\n"
                           "    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0000> ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/uniprot/PD58736> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0000>\n"
                           "    bqbiol:is <https://identifiers.org/OPB/OPB_12345> ;\n"
                           "    bqbiol:isPartOf <https://identifiers.org/fma/FMA_8764> .";
    ASSERT_TRUE(OmexMetaTestUtils::equals(rdf_ptr, expected, "turtle"));

    Editor_delete(editor_ptr);
    PhysicalEntity_delete(physical_entity_ptr);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, TestPhysicalEntityOptionalLocation) {
    RDF *rdf_ptr = RDF_new();

    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);

    PhysicalEntity *physical_entity_ptr = PhysicalEntity_new(editor_ptr);
    physical_entity_ptr = PhysicalEntity_about(physical_entity_ptr, "#OmexMetaId0000");
    physical_entity_ptr = PhysicalEntity_identity(physical_entity_ptr, "uniprot:PD58736");
    physical_entity_ptr = PhysicalEntity_hasProperty(physical_entity_ptr, "opb:opb12345");
    Editor_addPhysicalEntity(editor_ptr, physical_entity_ptr);

    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:EntityProperty0000\n"
                           "    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0000> ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb/opb12345> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0000>\n"
                           "    bqbiol:is <https://identifiers.org/uniprot/PD58736> .";

    ASSERT_TRUE(OmexMetaTestUtils::equals(rdf_ptr, expected, "turtle"));

    Editor_delete(editor_ptr);
    PhysicalEntity_delete(physical_entity_ptr);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, TestPhysicalEntityLocations) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    PhysicalEntity *physical_entity_ptr = PhysicalEntity_new(editor_ptr);
    physical_entity_ptr = PhysicalEntity_about(physical_entity_ptr, "OmexMetaId0000");
    physical_entity_ptr = PhysicalEntity_isPartOf(physical_entity_ptr, "FMA:fma:8376");
    physical_entity_ptr = PhysicalEntity_isPartOf(physical_entity_ptr, "FMA:fma:8377");
    physical_entity_ptr = PhysicalEntity_isPartOf(physical_entity_ptr, "FMA:fma:8378");
    Editor_addPhysicalEntity(editor_ptr, physical_entity_ptr);

    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:EntityProperty0000\n"
                           "    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0000> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0000>\n"
                           "    bqbiol:isPartOf <https://identifiers.org/FMA/fma:8376>, <https://identifiers.org/FMA/fma:8377>, <https://identifiers.org/FMA/fma:8378> .\n"
                           "";
    ASSERT_TRUE(OmexMetaTestUtils::equals(rdf_ptr, expected, "turtle"));
    PhysicalEntity_freeAll(physical_entity_ptr);
    Editor_delete(editor_ptr);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, TestPhysicalProcess) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    PhysicalProcess *physical_process_ptr = PhysicalProcess_new(editor_ptr);

    physical_process_ptr = PhysicalProcess_about(physical_process_ptr, "#OmexMetaId0000");
//    physical_process_ptr = PhysicalProcess_isVersionOf(physical_process_ptr, "opb/opb93864");
    physical_process_ptr = PhysicalProcess_hasProperty(physical_process_ptr, "GO:GO12345");
    physical_process_ptr = PhysicalProcess_addSink(
            physical_process_ptr, 1, "Entity8");
    physical_process_ptr = PhysicalProcess_addSource(
            physical_process_ptr, 1, "Entity8");
    physical_process_ptr = PhysicalProcess_addMediator(
            physical_process_ptr, "Entity8");

    Editor_addPhysicalProcess(editor_ptr, physical_process_ptr);

    printf(RDF_toString(rdf_ptr, "turtle"), stdout);

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix semsim: <http://www.bhi.washington.edu/semsim#> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:MediatorParticipant0000\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#Entity8> .\n"
                           "\n"
                           "local:ProcessProperty0000\n"
                           "    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0000> ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/GO:GO12345> .\n"
                           "\n"
                           "local:SinkParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#Entity8> .\n"
                           "\n"
                           "local:SourceParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#Entity8> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0000>\n"
                           "    semsim:hasMediatorParticipant local:MediatorParticipant0000 ;\n"
                           "    semsim:hasSinkParticipant local:SinkParticipant0000 ;\n"
                           "    semsim:hasSourceParticipant local:SourceParticipant0000 .\n"
                           "";
    ASSERT_TRUE(OmexMetaTestUtils::equals(rdf_ptr, expected, "turtle"));

    Editor_delete(editor_ptr);
    PhysicalProcess_delete(physical_process_ptr);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, TestPhysicalProcess2) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    PhysicalProcess *physical_process_ptr = PhysicalProcess_new(editor_ptr);

    physical_process_ptr = PhysicalProcess_about(physical_process_ptr, "#OmexMetaId0000");
    physical_process_ptr = PhysicalProcess_hasProperty(physical_process_ptr, "opb/opb93864");
    physical_process_ptr = PhysicalProcess_isVersionOf(physical_process_ptr, "GO:12345");
    physical_process_ptr = PhysicalProcess_addSink(
            physical_process_ptr, 1, "Entity8");
    physical_process_ptr = PhysicalProcess_addSource(
            physical_process_ptr, 1, "Entity8");
    physical_process_ptr = PhysicalProcess_addMediator(
            physical_process_ptr, "Entity8");

    Editor_addPhysicalProcess(editor_ptr, physical_process_ptr);
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix semsim: <http://www.bhi.washington.edu/semsim#> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:MediatorParticipant0000\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#Entity8> .\n"
                           "\n"
                           "local:ProcessProperty0000\n"
                           "    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0000> ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb/opb93864> .\n"
                           "\n"
                           "local:SinkParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#Entity8> .\n"
                           "\n"
                           "local:SourceParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#Entity8> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0000>\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/GO:12345> ;\n"
                           "    semsim:hasMediatorParticipant local:MediatorParticipant0000 ;\n"
                           "    semsim:hasSinkParticipant local:SinkParticipant0000 ;\n"
                           "    semsim:hasSourceParticipant local:SourceParticipant0000 .";
    ASSERT_TRUE(OmexMetaTestUtils::equals(rdf_ptr, expected, "turtle"));

    Editor_delete(editor_ptr);
    PhysicalProcess_delete(physical_process_ptr);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, TestPhysicalForce) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    PhysicalForce *physical_force_ptr = PhysicalForce_new(editor_ptr);

    physical_force_ptr = PhysicalForce_setPhysicalProperty(physical_force_ptr, "#OmexMetaId0000", "opb/opb93864");
    physical_force_ptr = PhysicalForce_addSink(
            physical_force_ptr, 1, "Entity8");
    physical_force_ptr = PhysicalForce_addSource(
            physical_force_ptr, 1, "Entity9");
    Editor_addPhysicalForce(editor_ptr, physical_force_ptr);

    char *actual = PhysicalForce_str(physical_force_ptr, "turtle", "./Annot.rdf");
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix semsim: <http://www.bhi.washington.edu/semsim#> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:ForceProperty0000\n"
                           "    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0000> ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb/opb93864> .\n"
                           "\n"
                           "local:SinkParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#Entity8> .\n"
                           "\n"
                           "local:SourceParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#Entity9> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0000>\n"
                           "    semsim:hasSinkParticipant local:SinkParticipant0000 ;\n"
                           "    semsim:hasSourceParticipant local:SourceParticipant0000 .";
    std::cout << actual << std::endl;
    ASSERT_TRUE(OmexMetaTestUtils::equals(rdf_ptr, expected, "turtle"));


    RDF_delete(rdf_ptr);
    Editor_delete(editor_ptr);
    PhysicalForce_delete(physical_force_ptr);
    free_c_char_star(actual);
}

TEST_F(CAPITests, TestEditorToRDF) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    PhysicalProcess *physical_process_ptr = PhysicalProcess_new(editor_ptr);

    physical_process_ptr = PhysicalProcess_setPhysicalProperty(physical_process_ptr, "#OmexMetaId0006",
                                                               "opb/opb93864");
    physical_process_ptr = PhysicalProcess_addSink(
            physical_process_ptr, 1.0, "Entity8");
    physical_process_ptr = PhysicalProcess_addSource(
            physical_process_ptr, 1, "Entity8");
    physical_process_ptr = PhysicalProcess_addMediator(
            physical_process_ptr, "Entity8");
    Editor_addPhysicalProcess(editor_ptr, physical_process_ptr);

    PhysicalEntity *physical_entity_ptr = PhysicalEntity_new(editor_ptr);
    physical_entity_ptr = PhysicalEntity_about(physical_entity_ptr, "#OmexMetaId0007");
    physical_entity_ptr = PhysicalEntity_hasProperty(physical_entity_ptr, "opb/opb_465");
    physical_entity_ptr = PhysicalEntity_identity(physical_entity_ptr, "uniprot/PD7363");
    physical_entity_ptr = PhysicalEntity_isPartOf(physical_entity_ptr, "FMA:fma:8376");
    physical_entity_ptr = PhysicalEntity_isPartOf(physical_entity_ptr, "FMA:fma:8377");
    physical_entity_ptr = PhysicalEntity_isPartOf(physical_entity_ptr, "FMA:fma:8378");

    PhysicalForce *physical_force_ptr = PhysicalForce_new(editor_ptr);

    physical_force_ptr = PhysicalForce_setPhysicalProperty(physical_force_ptr, "#OmexMetaId0008", "opb/opb93864");
    physical_force_ptr = PhysicalForce_addSink(
            physical_force_ptr, 1, "Entity8");
    physical_force_ptr = PhysicalForce_addSource(
            physical_force_ptr, 1, "Entity9");


    Editor_addPhysicalProcess(editor_ptr, physical_process_ptr);
    Editor_addPhysicalEntity(editor_ptr, physical_entity_ptr);
    Editor_addPhysicalForce(editor_ptr, physical_force_ptr);
    //    Editor_toRDF(editor_ptr);

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix semsim: <http://www.bhi.washington.edu/semsim#> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:EntityProperty0000\n"
                           "    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0007> ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb/opb_465> .\n"
                           "\n"
                           "local:ForceProperty0000\n"
                           "    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0008> ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb/opb93864> .\n"
                           "\n"
                           "local:MediatorParticipant0000\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#Entity8> .\n"
                           "\n"
                           "local:ProcessProperty0000\n"
                           "    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0006> ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb/opb93864> .\n"
                           "\n"
                           "local:SinkParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#Entity8> .\n"
                           "\n"
                           "local:SinkParticipant0001\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#Entity8> .\n"
                           "\n"
                           "local:SourceParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#Entity8> .\n"
                           "\n"
                           "local:SourceParticipant0001\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#Entity9> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0006>\n"
                           "    semsim:hasMediatorParticipant local:MediatorParticipant0000 ;\n"
                           "    semsim:hasSinkParticipant local:SinkParticipant0000 ;\n"
                           "    semsim:hasSourceParticipant local:SourceParticipant0000 .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0007>\n"
                           "    bqbiol:is <https://identifiers.org/uniprot/PD7363> ;\n"
                           "    bqbiol:isPartOf <https://identifiers.org/FMA/fma:8376>, <https://identifiers.org/FMA/fma:8377>, <https://identifiers.org/FMA/fma:8378> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0008>\n"
                           "    semsim:hasSinkParticipant local:SinkParticipant0001 ;\n"
                           "    semsim:hasSourceParticipant local:SourceParticipant0001 .";
    //    ASSERT_TRUE(OmexMetaTestUtils::equals(rdf_ptr, expected, "turtle"));

    Editor_delete(editor_ptr);
    PhysicalEntity_delete(physical_entity_ptr);
    PhysicalProcess_delete(physical_process_ptr);
    PhysicalForce_delete(physical_force_ptr);
    RDF_delete(rdf_ptr);
}

/*
 * todo support for equality operators
 */

TEST_F(CAPITests, TestRDFTwice1) {
    RDF *rdf_ptr1 = RDF_new();
    RDF *rdf_ptr2 = RDF_new();
    ASSERT_NE(rdf_ptr1, rdf_ptr2);
    RDF_delete(rdf_ptr1);
    RDF_delete(rdf_ptr2);
}

TEST_F(CAPITests, TestRDFTwice2) {
    RDF *rdf_ptr1 = RDF_new();
    RDF *rdf_ptr2 = RDF_new();
    ASSERT_NE(rdf_ptr1->getModel(), rdf_ptr2->getModel());
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
    const char *expected = "http://omex-library.org/NewOmex.omex/NewModel.xml#";
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
    const char *expected = "http://omex-library.org/NewOmex.omex/NewModel.xml#";
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
    RDF_setArchiveUri(rdf_ptr, "newArchive");
    char *actual = Editor_getArchiveUri(editor_ptr);
    const char *expected = "http://omex-library.org/newArchive.omex";
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected, actual);
    Editor_delete(editor_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, RDFsetModelUri) {
    RDF *rdf_ptr = RDF_new();
    RDF_setModelUri(rdf_ptr, "newModelName");
    const char *expected = "http://omex-library.org/NewOmex.omex/newModelName.xml#";
    char *actual = RDF_getModelUri(rdf_ptr);
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected, actual);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, RDFgetModelUriDefault) {
    RDF *rdf_ptr = RDF_new();
    const char *expected = "http://omex-library.org/NewOmex.omex/NewModel.xml#";
    char *actual = RDF_getModelUri(rdf_ptr);
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected, actual);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, RDFsetLocalUri) {
    RDF *rdf_ptr = RDF_new();
    RDF_setModelUri(rdf_ptr, "newModelName");
    const char *expected = "http://omex-library.org/NewOmex.omex/newModelName.rdf#";
    char *actual = RDF_getLocalUri(rdf_ptr);
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected, actual);
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
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#>\n"
                           "    <https://dublincore.org/specifications/dublin-core/dcmi-terms/creator> <https://orchid.org/1234-1234-1234-1234> .\n"
                           "\n"
                           "";
    char *actual = RDF_toString(rdf_ptr, "turtle");
    std::cout << actual << std::endl;
    ASSERT_TRUE(OmexMetaTestUtils::equals(rdf_ptr, expected, "turtle"));
    Editor_delete(editor_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, EditoraddCurator) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    Editor_addCurator(editor_ptr, "1234-1234-1234-1234");
    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#>\n"
                           "    <https://dublincore.org/specifications/dublin-core/dcmi-terms/creator> <https://orchid.org/1234-1234-1234-1234> .\n"
                           "\n"
                           "";
    char *actual = RDF_toString(rdf_ptr, "turtle");
    std::cout << actual << std::endl;
    ASSERT_TRUE(OmexMetaTestUtils::equals(rdf_ptr, expected, "turtle"));
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
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#>\n"
                           "    <bqbiol:hasTaxon> <NCBI_Taxon:9898> .\n"
                           "\n"
                           "";
    char *actual = RDF_toString(rdf_ptr, "turtle");
    std::cout << actual << std::endl;
    ASSERT_TRUE(OmexMetaTestUtils::equals(rdf_ptr, expected, "turtle"));
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
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#>\n"
                           "    <http://biomodels.net/model-qualifiers/isDescribedBy> <https://identifiers.org/pubmed/12345678> .\n"
                           "\n"
                           "";
    char *actual = RDF_toString(rdf_ptr, "turtle");
    std::cout << actual << std::endl;
    ASSERT_TRUE(OmexMetaTestUtils::equals(rdf_ptr, expected, "turtle"));
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
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#>\n"
                           "    <https://dublincore.org/specifications/dublin-core/dcmi-terms/description> \"A model\"^^rdf:string .\n"
                           "\n"
                           "";
    char *actual = RDF_toString(rdf_ptr, "turtle");
    std::cout << actual << std::endl;
    ASSERT_TRUE(OmexMetaTestUtils::equals(rdf_ptr, expected, "turtle"));
    Editor_delete(editor_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, EditoraddDateCreated) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    Editor_addDateCreated(editor_ptr, "14/01/1991");
    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#>\n"
                           "    <https://dublincore.org/specifications/dublin-core/dcmi-terms/created> \"14/01/1991\"^^rdf:string .\n"
                           "\n"
                           "";
    char *actual = RDF_toString(rdf_ptr, "turtle");
    std::cout << actual << std::endl;
    ASSERT_TRUE(OmexMetaTestUtils::equals(rdf_ptr, expected, "turtle"));
    Editor_delete(editor_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, EditoraddPersonalInformation) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);

    //    Editor_addPersonalInformation(editor_ptr, p);
    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "";
    char *actual = RDF_toString(rdf_ptr, "turtle");
    std::cout << actual << std::endl;
    ASSERT_TRUE(OmexMetaTestUtils::equals(rdf_ptr, expected, "turtle"));
    Editor_delete(editor_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, EditoraddParentModel) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    Editor_addParentModel(editor_ptr, "BIOMD000001.xml");
    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#>\n"
                           "    <http://biomodels.net/model-qualifiers/isDerivedFrom> <https://identifiers.org/biomod/BIOMD000001.xml> .\n"
                           "\n"
                           "";
    char *actual = RDF_toString(rdf_ptr, "turtle");
    std::cout << actual << std::endl;
    ASSERT_TRUE(OmexMetaTestUtils::equals(rdf_ptr, expected, "turtle"));
    Editor_delete(editor_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, PersonalInformationgetLocalUri) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    PersonalInformation *information = PersonalInformation_new(editor_ptr);
    char *actual = PersonalInformation_getLocalUri(information);
    Editor_addPersonalInformation(editor_ptr, information);
    const char *expected = "http://omex-library.org/NewOmex.omex/NewModel.rdf#";
    std::cout << actual << std::endl;
    ASSERT_TRUE(OmexMetaTestUtils::equals(rdf_ptr, expected, "turtle"));
    PersonalInformation_delete(information);
    Editor_delete(editor_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, PersonalInformationsetLocalUri) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    PersonalInformation *information = PersonalInformation_new(editor_ptr);
    PersonalInformation_setLocalUri(information, "localUri");
    Editor_addPersonalInformation(editor_ptr, information);
    char *actual = PersonalInformation_getLocalUri(information);
    const char *expected = "localUri";
    std::cout << actual << std::endl;
    ASSERT_TRUE(OmexMetaTestUtils::equals(rdf_ptr, expected, "turtle"));
    PersonalInformation_delete(information);
    Editor_delete(editor_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, PersonalInformationaddCreator) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    PersonalInformation *information = PersonalInformation_new(editor_ptr);
    PersonalInformation_addCreator(information, "2134-1234-1234-1234");
    Editor_addPersonalInformation(editor_ptr, information);
    char *actual = RDF_toString(rdf_ptr, "turtle");
    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix dc: <https://dublincore.org/specifications/dublin-core/dcmi-terms/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#>\n"
                           "    dc:creator <http://omex-library.org/NewOmex.omex/NewModel.xml#PersonalInfo0000> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#PersonalInfo0000>\n"
                           "    dc:creator <2134-1234-1234-1234> .\n"
                           "\n"
                           "";
    std::cout << actual << std::endl;
    ASSERT_TRUE(OmexMetaTestUtils::equals(rdf_ptr, expected, "turtle"));
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
//    PersonalInformation *information = PersonalInformation_new(editor_ptr);
//    PersonalInformation_addCurator(information, "2134-1234-1234-1234");
//    char *actual = RDF_toString(rdf_ptr, "turtle");
//    const char *expected = "https://identifiers.org/uniprot/PD7363";
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

    PersonalInformation *information = PersonalInformation_new(editor_ptr);
    PersonalInformation_addName(information, "Ciaran Welsh");
    Editor_addPersonalInformation(editor_ptr, information);
    char *actual = RDF_toString(rdf_ptr, "turtle");
    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix foaf: <http://xmlns.com/foaf/0.1/> .\n"
                           "@prefix dc: <https://dublincore.org/specifications/dublin-core/dcmi-terms/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#>\n"
                           "    dc:creator <http://omex-library.org/NewOmex.omex/NewModel.xml#PersonalInfo0000> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#PersonalInfo0000>\n"
                           "    foaf:name \"Ciaran Welsh\"^^rdf:string .\n"
                           "\n"
                           "";
    std::cout << actual << std::endl;
    ASSERT_TRUE(OmexMetaTestUtils::equals(rdf_ptr, expected, "turtle"));
    PersonalInformation_delete(information);
    Editor_delete(editor_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, PersonalInformationaddMbox) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    PersonalInformation *information = PersonalInformation_new(editor_ptr);
    PersonalInformation_addMbox(information, "cwelsh2@ue.edu");
    Editor_addPersonalInformation(editor_ptr, information);
    char *actual = RDF_toString(rdf_ptr, "turtle");
    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix foaf: <http://xmlns.com/foaf/0.1/> .\n"
                           "@prefix dc: <https://dublincore.org/specifications/dublin-core/dcmi-terms/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#>\n"
                           "    dc:creator <http://omex-library.org/NewOmex.omex/NewModel.xml#PersonalInfo0000> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#PersonalInfo0000>\n"
                           "    foaf:mbox \"cwelsh2@ue.edu\"^^rdf:string .\n"
                           "\n"
                           "";
    std::cout << actual << std::endl;
    ASSERT_TRUE(OmexMetaTestUtils::equals(rdf_ptr, expected, "turtle"));
    PersonalInformation_delete(information);
    Editor_delete(editor_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, PersonalInformationaddAccountName) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    PersonalInformation *information = PersonalInformation_new(editor_ptr);
    PersonalInformation_addAccountName(information, "2134-1234-1234-1234");
    Editor_addPersonalInformation(editor_ptr, information);
    char *actual = RDF_toString(rdf_ptr, "turtle");
    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix foaf: <http://xmlns.com/foaf/0.1/> .\n"
                           "@prefix dc: <https://dublincore.org/specifications/dublin-core/dcmi-terms/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#>\n"
                           "    dc:creator <http://omex-library.org/NewOmex.omex/NewModel.xml#PersonalInfo0000> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#PersonalInfo0000>\n"
                           "    foaf:accountName <https://orcid.org/2134-1234-1234-1234> .\n"
                           "\n";
    std::cout << actual << std::endl;
    ASSERT_TRUE(OmexMetaTestUtils::equals(rdf_ptr, expected, "turtle"));
    PersonalInformation_delete(information);
    Editor_delete(editor_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, PersonalInformationaddAccountServiceHomepage) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    PersonalInformation *information = PersonalInformation_new(editor_ptr);
    PersonalInformation_addAccountServiceHomepage(information, "https://github.com/sys-bio/libOmexMeta");
    Editor_addPersonalInformation(editor_ptr, information);
    char *actual = RDF_toString(rdf_ptr, "turtle");
    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix foaf: <http://xmlns.com/foaf/0.1/> .\n"
                           "@prefix dc: <https://dublincore.org/specifications/dublin-core/dcmi-terms/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#>\n"
                           "    dc:creator <http://omex-library.org/NewOmex.omex/NewModel.xml#PersonalInfo0000> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#PersonalInfo0000>\n"
                           "    foaf:accountServiceHomepage <https://github.com/sys-bio/libOmexMeta> .\n"
                           "\n"
                           "";
    std::cout << actual << std::endl;
    ASSERT_TRUE(OmexMetaTestUtils::equals(rdf_ptr, expected, "turtle"));
    PersonalInformation_delete(information);
    Editor_delete(editor_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, PersonalInformationaddFoafUri) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    PersonalInformation *information = PersonalInformation_new(editor_ptr);
    PersonalInformation_addFoafLiteral(information, "accountServiceHomepage", "https://github.com/sys-bio/libOmexMeta");
    Editor_addPersonalInformation(editor_ptr, information);
    char *actual = RDF_toString(rdf_ptr, "turtle");
    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix foaf: <http://xmlns.com/foaf/0.1/> .\n"
                           "@prefix dc: <https://dublincore.org/specifications/dublin-core/dcmi-terms/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#>\n"
                           "    dc:creator <http://omex-library.org/NewOmex.omex/NewModel.xml#PersonalInfo0000> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#PersonalInfo0000>\n"
                           "    foaf:accountServiceHomepage \"https://github.com/sys-bio/libOmexMeta\"^^rdf:string .\n"
                           "\n"
                           "";
    std::cout << actual << std::endl;
    ASSERT_TRUE(OmexMetaTestUtils::equals(rdf_ptr, expected, "turtle"));
    PersonalInformation_delete(information);
    Editor_delete(editor_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, PersonalInformationaddFoafLiteral) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    PersonalInformation *information = PersonalInformation_new(editor_ptr);
    PersonalInformation_addFoafLiteral(information, "name", "Ciaran Welsh");
    Editor_addPersonalInformation(editor_ptr, information);
    char *actual = RDF_toString(rdf_ptr, "turtle");
    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix foaf: <http://xmlns.com/foaf/0.1/> .\n"
                           "@prefix dc: <https://dublincore.org/specifications/dublin-core/dcmi-terms/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#>\n"
                           "    dc:creator <http://omex-library.org/NewOmex.omex/NewModel.xml#PersonalInfo0000> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#PersonalInfo0000>\n"
                           "    foaf:name \"Ciaran Welsh\"^^rdf:string .\n"
                           "\n";
    std::cout << actual << std::endl;
    ASSERT_TRUE(OmexMetaTestUtils::equals(rdf_ptr, expected, "turtle"));
    PersonalInformation_delete(information);
    Editor_delete(editor_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, PersonalInformationgetMetaid) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    PersonalInformation *information = PersonalInformation_new(editor_ptr);
    char *actual = PersonalInformation_getMetaid(information);
    Editor_addPersonalInformation(editor_ptr, information);
    editor_ptr->addPersonalInformation(information);
    const char *expected = "http://omex-library.org/NewOmex.omex/NewModel.xml#PersonalInfo0000";
    std::cout << actual << std::endl;
    ASSERT_TRUE(OmexMetaTestUtils::equals(rdf_ptr, expected, "turtle"));
    PersonalInformation_delete(information);
    Editor_delete(editor_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, PersonalInformationsetMetaid) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    PersonalInformation *information = PersonalInformation_new(editor_ptr);
    PersonalInformation_setMetaid(information, "NewMEtaid");
    Editor_addPersonalInformation(editor_ptr, information);
    char *actual = PersonalInformation_getMetaid(information);
    const char *expected = "NewMEtaid";
    std::cout << actual << std::endl;
    ASSERT_TRUE(OmexMetaTestUtils::equals(rdf_ptr, expected, "turtle"));
    PersonalInformation_delete(information);
    Editor_delete(editor_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, PersonalInformationgetModelName) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    PersonalInformation *information = PersonalInformation_new(editor_ptr);
    Editor_addPersonalInformation(editor_ptr, information);
    char *actual = PersonalInformation_getModelUri(information);
    const char *expected = "http://omex-library.org/NewOmex.omex/NewModel.xml#";
    std::cout << actual << std::endl;
    ASSERT_TRUE(OmexMetaTestUtils::equals(rdf_ptr, expected, "turtle"));
    PersonalInformation_delete(information);
    Editor_delete(editor_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}

TEST_F(CAPITests, PersonalInformationsetModelUri) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr,
                                      SBMLFactory::getSBML(SBML_NOT_ANNOTATED).c_str(), true, false);
    PersonalInformation *information = PersonalInformation_new(editor_ptr);
    PersonalInformation_setModelUri(information, "newModelName");
    Editor_addPersonalInformation(editor_ptr, information);
    char *actual = PersonalInformation_getModelUri(information);
    const char *expected = "newModelName";
    std::cout << actual << std::endl;
    ASSERT_TRUE(OmexMetaTestUtils::equals(rdf_ptr, expected, "turtle"));
    PersonalInformation_delete(information);
    Editor_delete(editor_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}


TEST_F(CAPITests, RDFToEditorTestWithSemanticExtraction) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr, SBMLFactory::getSBML(SBML_Semantic_Extraction_Model).c_str(), true, true);

    char *actual = RDF_toString(rdf_ptr, "turtle");
    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix semsim: <http://www.bhi.washington.edu/semsim#> .\n"
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
                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#sp_1> .\n"
                           "\n"
                           "local:SinkParticipant0001\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#sp_4> .\n"
                           "\n"
                           "local:SourceParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#sp_2> .\n"
                           "\n"
                           "local:SourceParticipant0001\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#sp_3> .\n"
                           "\n"
                           "local:SourceParticipant0002\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
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
                           "    bqbiol:isPartOf <http://omex-library.org/NewOmex.omex/NewModel.xml#cytosol> .\n\n";
    printf("%s", actual);
    ASSERT_TRUE(OmexMetaTestUtils::equals(rdf_ptr, expected, "turtle"));

    Editor_delete(editor_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}


TEST_F(CAPITests, RDFToEditorTestWithoutSemanticExtraction) {
    RDF *rdf_ptr = RDF_new();
    Editor *editor_ptr = RDF_toEditor(rdf_ptr, SBMLFactory::getSBML(SBML_Semantic_Extraction_Model).c_str(), true, false);

    char *actual = RDF_toString(rdf_ptr, "turtle");
    const char *expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n";
    printf("%s", actual);
    ASSERT_TRUE(OmexMetaTestUtils::equals(rdf_ptr, expected, "turtle"));

    Editor_delete(editor_ptr);
    free_c_char_star(actual);
    RDF_delete(rdf_ptr);
}
