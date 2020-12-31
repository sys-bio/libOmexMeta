//
// Created by Ciaran on 4/15/2020.
//
#include "OmexMetaTestUtils.h"
#include "SBMLFactory.h"
#include "omexmeta/Editor.h"
#include "omexmeta/EnergyDiff.h"
#include "omexmeta/OmexMetaXmlAssistant.h"
#include "omexmeta/PhysicalEntity.h"
#include "omexmeta/PhysicalProcess.h"
#include "omexmeta/RDF.h"
#include "gtest/gtest.h"

using namespace omexmeta;

class EditorTests : public ::testing::Test {

public:
    LibrdfStorage storage;
    LibrdfModel model;

    std::string cellml_example = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                                 "<model xmlns=\"http://www.cellml.org/cellml/1.1#\" xmlns:cmeta=\"http://www.cellml.org/metadata/1.0#\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:bqs=\"http://www.cellml.org/bqs/1.0#\" xmlns:semsim=\"http://bime.uw.edu/semsim/#\" xmlns:dc=\"https://dublincore.org/specifications/dublin-core/dcmi-terms/\" xmlns:vCard=\"http://www.w3.org/2001/vcard-rdf/3.0#\" name=\"annotation_examples\" cmeta:id=\"annExamples\">\n"
                                 "  <component name=\"main\">\n"
                                 "    <variable cmeta:id=\"main.Volume\" initial_value=\"100\" name=\"Volume\" units=\"dimensionless\" />\n"
                                 "    <variable cmeta:id=\"main.MembraneVoltage\" initial_value=\"-80\" name=\"MembraneVoltage\" units=\"dimensionless\" />\n"
                                 "    <variable cmeta:id=\"main.ReactionRate\" initial_value=\"1\" name=\"ReactionRate\" units=\"dimensionless\" />\n"
                                 "  </component>\n"
                                 "</model>";


    EditorTests() {
        model = LibrdfModel(storage.get());
    };

    ~EditorTests() override {
        model.freeModel();
        storage.freeStorage();
    }
};

TEST_F(EditorTests, TestMetaIds) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);
    const auto &metaids = editor.getMetaids();
    std::vector<std::string> expected = {"model0000", "unit0000", "unit0001", "#cytosol", "#Meta00001",
                                         "species0000", "species0001", "reaction0000", "kineticLaw0000",
                                         "localParameter0000", "localParameter0001", "reaction0001",
                                         "kineticLaw0001"};
    ASSERT_EQ(expected, metaids);
}

TEST_F(EditorTests, TestRepositoryName1) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    std::string expected = "http://omex-library.org/";
    std::string actual = editor.getRepositoryUri();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(EditorTests, TestepositoryName2) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    std::string expected = "http://myCustomOmexLibrary.org/";
    rdf.setRepositoryUri(expected);
    std::string actual = editor.getRepositoryUri();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(EditorTests, TestArchiveName) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    std::string expected = "http://omex-library.org/myomex.omex/";
    rdf.setArchiveUri("myomex.omex");
    std::string actual = editor.getArchiveUri();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(EditorTests, TestSetModelName) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    rdf.setArchiveUri("MyOmexArchive.omex");
    rdf.setModelUri("smad.sbml");

    std::string expected = "http://omex-library.org/MyOmexArchive.omex/smad.sbml#";
    ASSERT_STREQ(expected.c_str(), editor.getModelUri().c_str());
}

TEST_F(EditorTests, TestSetLocalName) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    rdf.setArchiveUri("MyOmexArchive.omex");
    rdf.setModelUri("smad.sbml");

    std::string expected = "http://omex-library.org/MyOmexArchive.omex/smad.rdf#";
    ASSERT_STREQ(expected.c_str(), editor.getLocalUri().c_str());
}

TEST_F(EditorTests, TestSetLocalNam) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    rdf.setArchiveUri("MyOmexArchive.omex");
    rdf.setModelUri("smad.sbml");

    std::string expected = "http://omex-library.org/MyOmexArchive.omex/smad.rdf#";
    ASSERT_STREQ(expected.c_str(), editor.getLocalUri().c_str());
}

TEST_F(EditorTests, TestEditorFromSBMLInFile) {
    std::ofstream myfile;
    myfile.open("example.sbml");
    myfile << SBMLFactory::getSBML(SBML_NOT_ANNOTATED);
    myfile.close();

    RDF rdf;
    Editor editor = rdf.toEditor("example.sbml", true, false);
    editor.addSingleAnnotation(
            Subject(editor.createNodeWithModelUri("species0001")),
            std::make_unique<Predicate>(BiomodelsBiologyQualifier("isDescribedBy")),
            Resource(LibrdfNode::fromUriString("pubmed:12991237")));

    std::string actual = rdf.toString();
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#species0001>\n"
                           "    bqbiol:isDescribedBy <https://identifiers.org/pubmed:12991237> .";
    std::cout << actual << std::endl;
    ASSERT_TRUE(OmexMetaTestUtils::equals(&rdf, expected));

    remove("example.sbml");
}

TEST_F(EditorTests, TestAddAnnotation) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);
    PredicatePtr predicatePtr = std::make_shared<Predicate>(
            BiomodelsBiologyQualifier("is"));
    editor.addSingleAnnotation(
            Subject(LibrdfNode::fromUriString("species0000")),
            predicatePtr,
            Resource(LibrdfNode::fromUriString("uniprot/P0DP23")));
    ASSERT_EQ(1, editor.size());
    //    triples.freeTriples();
}

TEST_F(EditorTests, TestAddSingleAnnotationToEditor) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);
    Triple triple(LibrdfNode::fromUriString("species0001").get(),
                  BiomodelsBiologyQualifier("is").getNode(),
                  Resource(LibrdfNode::fromUriString("uniprot/P0DP23")).getNode());
    editor.addSingleAnnotation(triple);
    int expected = 1;
    int actual = editor.size();
    ASSERT_EQ(expected, actual);
    triple.freeStatement();
}

TEST_F(EditorTests, TestEditorCreateUriRelativeToLocalUri) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);
    rdf.setArchiveUri("MyOmexArchive.omex");
    rdf.setModelUri("mymodel.sbml");
    LibrdfNode node = editor.createNodeWithModelUri("species0000");
    std::string actual = node.str();
    std::string expected = "http://omex-library.org/MyOmexArchive.omex/mymodel.sbml#species0000";
    ASSERT_STREQ(actual.c_str(), expected.c_str());
    node.freeNode();
}

TEST_F(EditorTests, TestAddSingleAnnotationToRDF1) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED),
            true,
            false);
    Subject subject = Subject(editor.createNodeWithModelUri("species0001"));
    BiomodelsBiologyQualifier predicate("is");
    Resource resource = Resource(LibrdfNode::fromUriString("uniprot/P0DP23"));
    Triple triple(subject.getNode(), predicate.getNode(), resource.getNode());

    editor.addSingleAnnotation(triple);

    std::string actual = rdf.toString();
    std::cout << actual << std::endl;
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#species0001>\n"
                           "    bqbiol:is <https://identifiers.org/uniprot/P0DP23> .\n"
                           "\n";
    ASSERT_TRUE(OmexMetaTestUtils::equals(&rdf, expected));
    triple.freeStatement();
}

TEST_F(EditorTests, TestAddSingleAnnotationToRDF2) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);
    editor.addSingleAnnotation(
            Subject(editor.createNodeWithModelUri("unit0000")),
            std::make_shared<Predicate>(BiomodelsBiologyQualifier("isDescribedBy")),
            Resource(LibrdfNode::fromUriString("pubmed/12991237")));

    std::string actual = rdf.toString("turtle");
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#unit0000>\n"
                           "    bqbiol:isDescribedBy <https://identifiers.org/pubmed/12991237> .\n"
                           "\n"
                           "";
    std::cout << actual << std::endl;
    ASSERT_TRUE(OmexMetaTestUtils::equals(&rdf, expected));
}

TEST_F(EditorTests, TestAddSingleAnnotationToRDF3) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);
    editor.addSingleAnnotation(
            Subject(editor.createNodeWithModelUri("species0001")),
            std::make_unique<Predicate>(BiomodelsBiologyQualifier("isDescribedBy")),
            Resource(LibrdfNode::fromUriString("pubmed/12991237")));

    std::string actual = rdf.toString();
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#species0001>\n"
                           "    bqbiol:isDescribedBy <https://identifiers.org/pubmed/12991237> .\n\n";
    std::cout << actual << std::endl;
    ASSERT_TRUE(OmexMetaTestUtils::equals(&rdf, expected));
}

TEST_F(EditorTests, TestToRDFSingularAnnotationWithLiteral) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);
    editor.addSingleAnnotation(
            Subject(editor.createNodeWithModelUri("species0001")),
            std::make_unique<Predicate>(DCTerm("description")),
            Resource(LibrdfNode::fromLiteral("Cardiomyocyte cytosolic ATP concentration")));

    std::string actual = rdf.toString("turtle");
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix dc: <https://dublincore.org/specifications/dublin-core/dcmi-terms/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#species0001>\n"
                           "    dc:description \"Cardiomyocyte cytosolic ATP concentration\"^^rdf:string .\n"
                           "\n";
    std::cout << actual << std::endl;
    ASSERT_TRUE(OmexMetaTestUtils::equals(&rdf, expected));
}

TEST_F(EditorTests, TestSingularAnnotWithBuilderPattern) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    SingularAnnotation singularAnnotation = editor.newSingularAnnotation();

    singularAnnotation
            .about("species0001")
            .setPredicate("bqbiol", "isVersionOf")
            .setResourceUri("uniprot/PD02635");

    editor.addSingleAnnotation(singularAnnotation);

    std::string actual = rdf.toString("turtle");
    std::cout << actual << std::endl;
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#species0001>\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/uniprot/PD02635> .\n"
                           "\n"
                           "";
    ASSERT_TRUE(OmexMetaTestUtils::equals(&rdf, expected));

    singularAnnotation.freeStatement();
}

TEST_F(EditorTests, TestSingularAnnotWithBuilderPattern2) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    SingularAnnotation singularAnnotation = editor.newSingularAnnotation();
    singularAnnotation
            .about("species0001")
            .setPredicate("bqbiol", "isVersionOf")
            .setResourceUri("uniprot/PD02635");

    editor.addSingleAnnotation(singularAnnotation);

    std::string actual = rdf.toString("turtle");
    std::cout << actual << std::endl;
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#species0001>\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/uniprot/PD02635> .\n"
                           "\n"
                           "";
    ASSERT_TRUE(OmexMetaTestUtils::equals(&rdf, expected));

    singularAnnotation.freeStatement();
}

TEST_F(EditorTests, TestSingularAnnotWithBuilderPatternChebiResource) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    SingularAnnotation singularAnnotation = editor.newSingularAnnotation();
    singularAnnotation
            .about("species0001")
            .setPredicate("bqbiol", "isVersionOf")
            .setResourceUri("CHEBI:16253");

    editor.addSingleAnnotation(singularAnnotation);

    std::string actual = rdf.toString("turtle");
    std::cout << actual << std::endl;
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#species0001>\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/CHEBI:16253> .\n"
                           "\n"
                           "";
    ASSERT_TRUE(OmexMetaTestUtils::equals(&rdf, expected));

    singularAnnotation.freeStatement();
}

TEST_F(EditorTests, TestSingularAnnotWithBuilderPatternOPBResource) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    SingularAnnotation singularAnnotation = editor.newSingularAnnotation();
    singularAnnotation
            .about("species0001")
            .setPredicate("bqbiol", "isVersionOf")
            .setResourceUri("OPB:16253");

    editor.addSingleAnnotation(singularAnnotation);

    std::string actual = rdf.toString("turtle");
    std::cout << actual << std::endl;
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#species0001>\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/OPB:16253> .\n"
                           "\n"
                           "";
    ASSERT_TRUE(OmexMetaTestUtils::equals(&rdf, expected));

    singularAnnotation.freeStatement();
}

TEST_F(EditorTests, TestEditASingularAnnotWithBuilderPatternThenRemove) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    SingularAnnotation singularAnnotation = editor.newSingularAnnotation();
    singularAnnotation
            .about("#species0001")
            .setPredicate("bqbiol", "isVersionOf")
            .setResourceUri("uniprot/PD02635");

    editor.addSingleAnnotation(singularAnnotation);
    editor.removeSingleAnnotation(singularAnnotation);

    SingularAnnotation singularAnnotation2 = editor.newSingularAnnotation("#species0001");
    singularAnnotation2
            .setPredicate("bqbiol", "isVersionOf")
            .setResourceUri("uniprot/PD02636");

    editor.addSingleAnnotation(singularAnnotation2);

    std::string actual = rdf.toString("turtle");
    std::cout << actual << std::endl;
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#species0001>\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/uniprot/PD02636> .\n"
                           "\n"
                           "";
    ASSERT_TRUE(OmexMetaTestUtils::equals(&rdf, expected));

    singularAnnotation.freeStatement();
    singularAnnotation2.freeStatement();
}

TEST_F(EditorTests, TestSingularAnnotationBuilder) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);


    SingularAnnotation singularAnnotation = editor.newSingularAnnotation("#species0001");
    singularAnnotation
            .setPredicate("bqbiol", "is")
            .setResourceLiteral("resource");

    editor.addSingleAnnotation(singularAnnotation);

    int expected = 1;
    int actual = rdf.size();
    ASSERT_EQ(expected, actual);
    singularAnnotation.freeStatement();
}

TEST_F(EditorTests, TestSingularAnnotationBuilder2) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);


    SingularAnnotation singularAnnotation = editor.newSingularAnnotation();
    singularAnnotation
            .about("#species0001")
            .setPredicate("bqbiol", "is")
            .setResourceLiteral("resource");

    editor.addSingleAnnotation(singularAnnotation);

    int expected = 1;
    int actual = rdf.size();
    ASSERT_EQ(expected, actual);
    singularAnnotation.freeStatement();
}

TEST_F(EditorTests, TestModelLevelAnnotationAddCreator) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    editor.addCreator("0000-1111-2222-3333");

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml>\n"
                           "    <https://dublincore.org/specifications/dublin-core/dcmi-terms/creator> <https://orchid.org/0000-1111-2222-3333> .\n"
                           "\n"
                           "";
    std::string actual = rdf.toString("turtle");
    std::cout << actual << std::endl;
    ASSERT_TRUE(OmexMetaTestUtils::equals(&rdf, expected));
}

TEST_F(EditorTests, TestModelLevelAnnotationAddCurator) {
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
                           "    <https://dublincore.org/specifications/dublin-core/dcmi-terms/creator> <https://orchid.org/0000-1111-2222-3333> .\n"
                           "\n"
                           "";
    std::string actual = rdf.toString("turtle");
    std::cout << actual << std::endl;
    ASSERT_TRUE(OmexMetaTestUtils::equals(&rdf, expected));
}

TEST_F(EditorTests, TestModelLevelAnnotationAddDateCreated) {
    std::cout << __FILE__ << ":" << __LINE__ << std::endl;
    RDF rdf;
    std::cout << __FILE__ << ":" << __LINE__ << std::endl;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);
    std::cout << __FILE__ << ":" << __LINE__ << std::endl;

    editor.addDateCreated("14/01/1991");
    std::cout << __FILE__ << ":" << __LINE__ << std::endl;

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix dc: <https://dublincore.org/specifications/dublin-core/dcmi-terms/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml>\n"
                           "    dc:created [\n"
                           "        dc:W3CDTF \"14/01/1991\"^^rdf:string\n"
                           "    ] .";
    std::cout << __FILE__ << ":" << __LINE__ << std::endl;
    RDF expected_rdf = RDF::fromString(expected, "turtle");
    std::cout << __FILE__ << ":" << __LINE__ << std::endl;
    std::cout << rdf.toString() << std::endl;
    std::cout << __FILE__ << ":" << __LINE__ << std::endl;
    std::cout << expected_rdf.toString() << std::endl;
    std::cout << __FILE__ << ":" << __LINE__ << std::endl;

    bool passed = OmexMetaTestUtils::equals(&rdf, &expected_rdf);
    std::cout << __FILE__ << ":" << __LINE__ << std::endl;
    ASSERT_TRUE(passed);
    std::cout << __FILE__ << ":" << __LINE__ << std::endl;
}

TEST_F(EditorTests, TestModelLevelAnnotationAddDescription) {
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
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml>\n"
                           "    <https://dublincore.org/specifications/dublin-core/dcmi-terms/description> \"Predictive model of chip butty consumer's risk of heart failure.\"^^rdf:string .\n"
                           "\n";
    std::string actual = rdf.toString("turtle");
    std::cout << actual << std::endl;
    ASSERT_TRUE(OmexMetaTestUtils::equals(&rdf, expected));
}

TEST_F(EditorTests, TestModelLevelAnnotationPubmed) {
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
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml>\n"
                           "    bqmodel:isDescribedBy <https://identifiers.org/pubmed:27887851> .";
    std::string actual = rdf.toString("turtle");
    std::cout << actual << std::endl;
    ASSERT_TRUE(OmexMetaTestUtils::equals(&rdf, expected));
}

TEST_F(EditorTests, TestModelLevelAnnotationAddParentModel) {
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
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml>\n"
                           "    bqmodel:isDerivedFrom biomod:BIOMD0000011 .";
    std::string actual = rdf.toString("turtle");
    std::cout << actual << std::endl;
    ASSERT_TRUE(OmexMetaTestUtils::equals(&rdf, expected));
}

TEST_F(EditorTests, TestSingularAnnotationBuilderAlternativeInterface) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    SingularAnnotation singularAnnotation = editor.newSingularAnnotation();
    singularAnnotation.about("species0000")
            .setPredicate("bqbiol", "is")
            .setResourceLiteral("resource");
    editor.addSingleAnnotation(singularAnnotation);

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#species0000>\n"
                           "    bqbiol:is \"resource\"^^rdf:string .\n\n";
    std::string actual = singularAnnotation.str("turtle");
    std::cout << actual << std::endl;
    ASSERT_TRUE(OmexMetaTestUtils::equals(&rdf, expected));

    singularAnnotation.freeTriple();
}

TEST_F(EditorTests, TestRemoveSingularAnnotation) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    SingularAnnotation singularAnnotation = editor.newSingularAnnotation("#species0001");
    singularAnnotation
            .setPredicate("bqbiol", "is")
            .setResourceLiteral("resource");

    editor.addSingleAnnotation(singularAnnotation);

    ASSERT_EQ(1, rdf.size());

    editor.removeSingleAnnotation(singularAnnotation);
    int expected = 0;
    int actual = rdf.size();
    ASSERT_EQ(expected, actual);
    singularAnnotation.freeStatement();
}


TEST_F(EditorTests, TestRemovePersonalInformation) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    PersonalInformation information = editor.newPersonalInformation();
    information.addMbox("annot@uw.edu");
    editor.addPersonalInformation(&information);
    ASSERT_EQ(2, rdf.size());
    editor.removePersonalInformation(&information);
    int actual = rdf.size();
    ASSERT_EQ(0, actual);
}


TEST_F(EditorTests, TestAddPersonalInformation) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    PersonalInformation information = editor.newPersonalInformation();
    information.addAccountName("1234-1234-1234-1234")
            .addAccountServiceHomepage("https://github.com/sys-bio/libOmexMeta")
            .addMbox("annotations@uw.edu")
            .addName("Ciaran Welsh");
    editor.addPersonalInformation(&information);
    std::string actual = rdf.toString("turtle");
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix foaf: <http://xmlns.com/foaf/0.1/> .\n"
                           "@prefix dc: <https://dublincore.org/specifications/dublin-core/dcmi-terms/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml>\n"
                           "    dc:creator <http://omex-library.org/NewOmex.omex/NewModel.xml#PersonalInfo0000> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#PersonalInfo0000>\n"
                           "    foaf:accountName <https://orcid.org/1234-1234-1234-1234> ;\n"
                           "    foaf:accountServiceHomepage <https://github.com/sys-bio/libOmexMeta> ;\n"
                           "    foaf:mbox \"annotations@uw.edu\"^^rdf:string ;\n"
                           "    foaf:name \"Ciaran Welsh\"^^rdf:string .\n"
                           "\n"
                           "";
    std::cout << actual << std::endl;
    ASSERT_TRUE(OmexMetaTestUtils::equals(&rdf, expected));
}


TEST_F(EditorTests, TestaddCreator) {
    RDF rdf;
    Editor editor = rdf.toEditor(SBMLFactory::getSBML(SBML_NOT_ANNOTATED2), true, false);
    editor.addCreator("1234-1234-1234-1234");
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix dc: <https://dublincore.org/specifications/dublin-core/dcmi-terms/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml>\n"
                           "    dc:creator <https://orchid.org/1234-1234-1234-1234> .";
    std::cout << rdf.toString() << std::endl;
    ASSERT_TRUE(OmexMetaTestUtils::equals(&rdf, expected));
}
TEST_F(EditorTests, TestaddCurator) {
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
                           "    dc:creator <https://orchid.org/1234-1234-1234-1234> .";
    std::cout << rdf.toString() << std::endl;
    ASSERT_TRUE(OmexMetaTestUtils::equals(&rdf, expected));
}
TEST_F(EditorTests, TestaddDateCreated) {
    RDF rdf;
    Editor editor = rdf.toEditor(SBMLFactory::getSBML(SBML_NOT_ANNOTATED2), true, false);
    editor.addDateCreated("20-01-2020");
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix dc: <https://dublincore.org/specifications/dublin-core/dcmi-terms/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml>\n"
                           "    dc:created [\n"
                           "        dc:W3CDTF \"20-01-2020\"^^rdf:string\n"
                           "    ] .\n"
                           "";
    std::cout << rdf.toString() << std::endl;
    ASSERT_TRUE(OmexMetaTestUtils::equals(&rdf, expected));
}
TEST_F(EditorTests, TestaddDescription) {
    RDF rdf;
    Editor editor = rdf.toEditor(SBMLFactory::getSBML(SBML_NOT_ANNOTATED2), true, false);
    editor.addDescription("Descripting");
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "@prefix dc: <https://dublincore.org/specifications/dublin-core/dcmi-terms/> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml>\n"
                           "    dc:description \"Descripting\"^^rdf:string .\n"
                           "";
    std::cout << rdf.toString() << std::endl;
    ASSERT_TRUE(OmexMetaTestUtils::equals(&rdf, expected));
}
TEST_F(EditorTests, TestaddPubmed) {
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
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml>\n"
                           "    bqmodel:isDescribedBy pubmed:12345 .\n"
                           "";
    std::cout << rdf.toString() << std::endl;
    ASSERT_TRUE(OmexMetaTestUtils::equals(&rdf, expected));
}
TEST_F(EditorTests, TestaddParentModel) {
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
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml>\n"
                           "    bqmodel:isDerivedFrom biomod:BIO12345 .\n"
                           "";
    std::cout << rdf.toString() << std::endl;
    ASSERT_TRUE(OmexMetaTestUtils::equals(&rdf, expected));
}

TEST_F(EditorTests, TestaddTaxon) {
    RDF rdf;
    Editor editor = rdf.toEditor(SBMLFactory::getSBML(SBML_NOT_ANNOTATED2), true, false);
    editor.addTaxon("9696");
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix NCBI_Taxon: <https://identifiers.org/taxonomy:> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "myOMEX:NewModel.xml\n"
                           "    bqbiol:hasTaxon NCBI_Taxon:9696 .";
    std::cout << rdf.toString() << std::endl;
    ASSERT_TRUE(OmexMetaTestUtils::equals(&rdf, expected));
}

/**
 * Check that we can access the metaid of a parameter in sbml for the about
 * section of a composite annotation. All parameters metaid from listOfParameters in sbml
 * should be accessible.
 */
TEST_F(EditorTests, LocalParameterAvailable) {
    RDF rdf;
    Editor editor = rdf.toEditor(SBMLFactory::getSBML(SBML_NERNST_POTENTIAL), false, false);
    SingularAnnotation singularAnnotation = editor.newSingularAnnotation();
    singularAnnotation.about("NernstPotential", MODEL_URI)
        .predicate("bqbiol", "isPropertyOf")
        .resourceUri("stuff");
    editor.addSingleAnnotation(singularAnnotation);
    std::cout << rdf.toString()<<std::endl;
}
