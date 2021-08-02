//
// Created by cw001 on 02/08/2021.
//

#include "SBMLFactory.h"
#include "omexmeta/Editor.h"
#include "omexmeta/EnergyDiff.h"
#include "omexmeta/OmexMetaXml.h"
#include "omexmeta/PhysicalEntity.h"
#include "omexmeta/PhysicalProcess.h"
#include "omexmeta/RDF.h"
#include "gtest/gtest.h"
#include <filesystem>

using namespace omexmeta;
namespace fs = std::filesystem;

class EditorTestsModelLevelAnnotationsFromString : public ::testing::Test {

public:
    EditorTestsModelLevelAnnotationsFromString() = default;

    ~EditorTestsModelLevelAnnotationsFromString() override = default;
};

TEST_F(EditorTestsModelLevelAnnotationsFromString, AddCreator) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    editor.addCreator("0000-1111-2222-3333");

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#TestModelNotAnnotated>\n"
                           "    <https://dublincore.org/specifications/dublin-core/dcmi-terms/creator> <https://orcid.org/0000-1111-2222-3333> .\n"
                           "\n"
                           "";
    std::string actual = rdf.toString("turtle");
    std::cout << actual << std::endl;
    ASSERT_TRUE(RDF::equals(&rdf, expected));
}

TEST_F(EditorTestsModelLevelAnnotationsFromString, AddCreatorFromFile) {
    RDF rdf;

    const std::string &sbml = SBMLFactory::getSBML(SBML_NOT_ANNOTATED);
    const fs::path sbmlFile = fs::current_path() / "sbml.sbml";
    std::ofstream filestream(sbmlFile);
    filestream << sbml;
    filestream.close();
    std::cout << sbmlFile << std::endl;
    Editor editor = rdf.toEditor(sbmlFile.string(), true, false);

    editor.addCreator("0000-1111-2222-3333");

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#TestModelNotAnnotated>\n"
                           "    <https://dublincore.org/specifications/dublin-core/dcmi-terms/creator> <https://orcid.org/0000-1111-2222-3333> .\n"
                           "\n"
                           "";
    std::string actual = rdf.toString("turtle");
    std::cout << actual << std::endl;
    ASSERT_TRUE(RDF::equals(&rdf, expected));

    if (fs::exists(sbmlFile)) {
        fs::remove(sbmlFile);
    }
}

TEST_F(EditorTestsModelLevelAnnotationsFromString, AddCurator) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    editor.addCurator("0000-1111-2222-3333");

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#>\n"
                           "    <https://dublincore.org/specifications/dublin-core/dcmi-terms/creator> <https://orcid.org/0000-1111-2222-3333> .\n"
                           "\n"
                           "";
    std::string actual = rdf.toString("turtle");
    std::cout << actual << std::endl;
    ASSERT_TRUE(RDF::equals(&rdf, expected));
}

TEST_F(EditorTestsModelLevelAnnotationsFromString, AddDateCreated) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    editor.addDateCreated("14/01/1991");

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix dc: <https://dublincore.org/specifications/dublin-core/dcmi-terms/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#TestModelNotAnnotated>\n"
                           "    dc:created [\n"
                           "        dc:W3CDTF \"14/01/1991\"\n"
                           "    ] .";
    RDF expected_rdf = RDF::fromString(expected, "turtle");
    std::cout << rdf.toString() << std::endl;
    std::cout << expected_rdf.toString() << std::endl;

    bool passed = RDF::equals(&rdf, &expected_rdf);
    ASSERT_TRUE(passed);
}

TEST_F(EditorTestsModelLevelAnnotationsFromString, AddDescription) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    editor.addDescription("Predictive model of chip butty consumer's risk of "
                          "heart failure.");

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#TestModelNotAnnotated>\n"
                           "    <https://dublincore.org/specifications/dublin-core/dcmi-terms/description> \"Predictive model of chip butty consumer's risk of heart failure.\" .\n"
                           "\n";
    std::string actual = rdf.toString("turtle");
    std::cout << actual << std::endl;
    ASSERT_TRUE(RDF::equals(&rdf, expected));
}

TEST_F(EditorTestsModelLevelAnnotationsFromString, Pubmed) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    editor.addPubmed("27887851");

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqmodel: <http://biomodels.net/model-qualifiers/> .\n"
                           "@prefix pubmed: <https://identifiers.org/pubmed:> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#TestModelNotAnnotated>\n"
                           "    bqmodel:isDescribedBy <https://identifiers.org/pubmed:27887851> .";
    std::string actual = rdf.toString("turtle");
    std::cout << actual << std::endl;
    ASSERT_TRUE(RDF::equals(&rdf, expected));
}

TEST_F(EditorTestsModelLevelAnnotationsFromString, AddParentModel) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    editor.addParentModel("BIOMD0000011");

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqmodel: <http://biomodels.net/model-qualifiers/> .\n"
                           "@prefix biomod: <https://identifiers.org/biomodels.db:> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#TestModelNotAnnotated>\n"
                           "    bqmodel:isDerivedFrom biomod:BIOMD0000011 .";
    std::string actual = rdf.toString("turtle");
    std::cout << actual << std::endl;
    ASSERT_TRUE(RDF::equals(&rdf, expected));
}


TEST_F(EditorTestsModelLevelAnnotationsFromString, TestaddCurator) {
    RDF rdf;
    Editor editor = rdf.toEditor(SBMLFactory::getSBML(SBML_NOT_ANNOTATED2), true, false);
    editor.addCurator("1234-1234-1234-1234");
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "@prefix dc: <https://dublincore.org/specifications/dublin-core/dcmi-terms/> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#>\n"
                           "    dc:creator <https://orcid.org/1234-1234-1234-1234> .";
    std::cout << rdf.toString() << std::endl;
    ASSERT_TRUE(RDF::equals(&rdf, expected));
}
TEST_F(EditorTestsModelLevelAnnotationsFromString, TestaddDateCreated) {
    RDF rdf;
    Editor editor = rdf.toEditor(SBMLFactory::getSBML(SBML_NOT_ANNOTATED2), true, false);
    editor.addDateCreated("20-01-2020");
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix dc: <https://dublincore.org/specifications/dublin-core/dcmi-terms/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#TestModelNotAnnotated>\n"
                           "    dc:created [\n"
                           "        dc:W3CDTF \"20-01-2020\"\n"
                           "    ] .\n"
                           "";
    std::cout << rdf.toString() << std::endl;
    ASSERT_TRUE(RDF::equals(&rdf, expected));
}
TEST_F(EditorTestsModelLevelAnnotationsFromString, TestaddDescription) {
    RDF rdf;
    Editor editor = rdf.toEditor(SBMLFactory::getSBML(SBML_NOT_ANNOTATED2), true, false);
    editor.addDescription("Descripting");
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "@prefix dc: <https://dublincore.org/specifications/dublin-core/dcmi-terms/> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#TestModelNotAnnotated>\n"
                           "    dc:description \"Descripting\" .\n"
                           "";
    std::cout << rdf.toString() << std::endl;
    ASSERT_TRUE(RDF::equals(&rdf, expected));
}
TEST_F(EditorTestsModelLevelAnnotationsFromString, TestaddPubmed) {
    RDF rdf;
    Editor editor = rdf.toEditor(SBMLFactory::getSBML(SBML_NOT_ANNOTATED2), true, false);
    editor.addPubmed("12345");
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "@prefix bqmodel: <http://biomodels.net/model-qualifiers/> .\n"
                           "@prefix pubmed: <https://identifiers.org/pubmed:> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#TestModelNotAnnotated>\n"
                           "    bqmodel:isDescribedBy pubmed:12345 .\n"
                           "";
    std::cout << rdf.toString() << std::endl;
    ASSERT_TRUE(RDF::equals(&rdf, expected));
}
TEST_F(EditorTestsModelLevelAnnotationsFromString, TestaddParentModel) {
    RDF rdf;
    Editor editor = rdf.toEditor(SBMLFactory::getSBML(SBML_NOT_ANNOTATED2), true, false);
    editor.addParentModel("BIO12345");
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "@prefix biomod: <https://identifiers.org/biomodels.db:> .\n"
                           "@prefix bqmodel: <http://biomodels.net/model-qualifiers/> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#TestModelNotAnnotated>\n"
                           "    bqmodel:isDerivedFrom biomod:BIO12345 .\n"
                           "";
    std::cout << rdf.toString() << std::endl;
    ASSERT_TRUE(RDF::equals(&rdf, expected, "turtle", true));
}

TEST_F(EditorTestsModelLevelAnnotationsFromString, TestaddTaxon) {
    RDF rdf;
    Editor editor = rdf.toEditor(SBMLFactory::getSBML(SBML_NOT_ANNOTATED2), true, false);
    editor.addTaxon("9696");
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix NCBI_Taxon: <https://identifiers.org/taxonomy:> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#TestModelNotAnnotated>\n"
                           "    bqbiol:hasTaxon NCBI_Taxon:9696 .";
    std::cout << rdf.toString() << std::endl;
    ASSERT_TRUE(RDF::equals(&rdf, expected));
}


class EditorTestsModelLevelAnnotationsFromFile : public ::testing::Test {
public:
    fs::path fname = fs::current_path() / "ASbmlFile.sbml";
    RDF rdf;
    Editor* editor = nullptr;

    EditorTestsModelLevelAnnotationsFromFile() {
        const std::string& sbml = SBMLFactory::getSBML(SBML_NOT_ANNOTATED2);
        std::ofstream ofs(fname);
        ofs << sbml ;
        ofs.close();
        editor = rdf.toEditorPtr(fname.string(), true, false);


    }

    ~EditorTestsModelLevelAnnotationsFromFile() override {
        if (fs::exists(fname)) {
            fs::remove(fname);
        }

        if (editor){
            delete editor;
            editor = nullptr;
        }

    };


};


TEST_F(EditorTestsModelLevelAnnotationsFromFile, AddCreator){
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix dc: <https://dublincore.org/specifications/dublin-core/dcmi-terms/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#TestModelNotAnnotated>\n"
                           "    dc:creator <https://orcid.org/1234-1234-1234-1234> .";
    std::cout << "rdf.getRepositoryUri(): " << rdf.getRepositoryUri() << std::endl;
    std::cout << "rdf.getArchiveUri(): " << rdf.getArchiveUri() << std::endl;
    std::cout << "rdf.getModelUri(): " << rdf.getModelUri() << std::endl;
    std::cout << "rdf.getLocalUri(): " << rdf.getLocalUri() << std::endl;
    editor->addCreator("1234-1234-1234-1234");
    ASSERT_TRUE(RDF::equals(&rdf, expected, "turtle", true));
}

TEST_F(EditorTestsModelLevelAnnotationsFromFile, AddCurator){
    const std::string& expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                                  "@prefix dc: <https://dublincore.org/specifications/dublin-core/dcmi-terms/> .\n"
                                  "@prefix OMEXlib: <http://omex-library.org/> .\n"
                                  "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                                  "\n"
                                  "<http://omex-library.org/NewOmex.omex/NewModel.rdf#>\n"
                                  "    dc:creator <https://orcid.org/1234-1234-1234-1234> .";
    editor->addCurator("1234-1234-1234-1234");
    ASSERT_TRUE(RDF::equals(&rdf, expected, "turtle", true));
}

TEST_F(EditorTestsModelLevelAnnotationsFromFile, AddDescription){
    const std::string& expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                                  "@prefix dc: <https://dublincore.org/specifications/dublin-core/dcmi-terms/> .\n"
                                  "@prefix OMEXlib: <http://omex-library.org/> .\n"
                                  "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                                  "\n"
                                  "<http://omex-library.org/NewOmex.omex/NewModel.xml#TestModelNotAnnotated>\n"
                                  "    dc:description \"Descripting\" .";
    editor->addDescription("Descripting");
    ASSERT_TRUE(RDF::equals(&rdf, expected, "turtle", true));
}

TEST_F(EditorTestsModelLevelAnnotationsFromFile, AddPubmed){
    const std::string& expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                                  "@prefix bqmodel: <http://biomodels.net/model-qualifiers/> .\n"
                                  "@prefix pubmed: <https://identifiers.org/pubmed:> .\n"
                                  "@prefix OMEXlib: <http://omex-library.org/> .\n"
                                  "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                                  "\n"
                                  "<http://omex-library.org/NewOmex.omex/NewModel.xml#TestModelNotAnnotated>\n"
                                  "    bqmodel:isDescribedBy <https://identifiers.org/pubmed:1234-1234-1234-1234> .";
    editor->addPubmed("1234-1234-1234-1234");
    ASSERT_TRUE(RDF::equals(&rdf, expected, "turtle", true));
}

TEST_F(EditorTestsModelLevelAnnotationsFromFile, AddParentModel){
    const std::string& expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                                  "@prefix bqmodel: <http://biomodels.net/model-qualifiers/> .\n"
                                  "@prefix biomod: <https://identifiers.org/biomodels.db:> .\n"
                                  "@prefix OMEXlib: <http://omex-library.org/> .\n"
                                  "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                                  "\n"
                                  "<http://omex-library.org/NewOmex.omex/NewModel.xml#TestModelNotAnnotated>\n"
                                  "    bqmodel:isDerivedFrom <https://identifiers.org/biomodels.db:1234-1234-1234-1234> .";
    editor->addParentModel("1234-1234-1234-1234");
    ASSERT_TRUE(RDF::equals(&rdf, expected, "turtle", true));
}

TEST_F(EditorTestsModelLevelAnnotationsFromFile, AddDateCreated){
    const std::string& expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                                  "@prefix dc: <https://dublincore.org/specifications/dublin-core/dcmi-terms/> .\n"
                                  "@prefix OMEXlib: <http://omex-library.org/> .\n"
                                  "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                                  "\n"
                                  "<http://omex-library.org/NewOmex.omex/NewModel.xml#TestModelNotAnnotated>\n"
                                  "    dc:created [\n"
                                  "        dc:W3CDTF \"1/2/2012\"\n"
                                  "    ] .";
    editor->addDateCreated("1/2/2012");
    ASSERT_TRUE(RDF::equals(&rdf, expected, "turtle", true));
}

TEST_F(EditorTestsModelLevelAnnotationsFromFile, AddTaxon){
    const std::string& expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                                  "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                                  "@prefix NCBI_Taxon: <https://identifiers.org/taxonomy:> .\n"
                                  "@prefix OMEXlib: <http://omex-library.org/> .\n"
                                  "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                                  "\n"
                                  "<http://omex-library.org/NewOmex.omex/NewModel.xml#TestModelNotAnnotated>\n"
                                  "    bqbiol:hasTaxon <https://identifiers.org/taxonomy:1234-1234-1234-1234> .";
    editor->addTaxon("1234-1234-1234-1234");
    ASSERT_TRUE(RDF::equals(&rdf, expected, "turtle", true));
}
