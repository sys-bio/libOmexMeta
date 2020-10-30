//
// Created by Ciaran on 4/15/2020.
//
#include "OmexMetaTestUtils.h"
#include "SBMLFactory.h"
#include "omexmeta/Editor.h"
#include "omexmeta/OmexMetaXmlAssistant.h"
#include "omexmeta/PhysicalEntity.h"
#include "omexmeta/PhysicalForce.h"
#include "omexmeta/PhysicalProcess.h"
#include "omexmeta/RDF.h"
#include "gtest/gtest.h"

using namespace omexmeta;

class EditorTests : public ::testing::Test {

public:
    LibrdfStorage storage;
    LibrdfModel model;

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
    std::vector<std::string> expected = {"#OmexMetaId0000", "#OmexMetaId0001", "#OmexMetaId0002",
                                         "#cytosol", "#Meta00001", "#OmexMetaId0003", "#OmexMetaId0004",
                                         "#OmexMetaId0005", "#OmexMetaId0006", "#OmexMetaId0007",
                                         "#OmexMetaId0008", "#OmexMetaId0009", "#OmexMetaId0010"};
    ASSERT_EQ(expected, metaids);
}

TEST_F(EditorTests, TestRepositoryName1) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    std::string expected = "http://omex-library.org/";
    std::string actual = editor.getRepositoryUri();
    ASSERT_TRUE(OmexMetaTestUtils::equals(&rdf, expected));
}

TEST_F(EditorTests, TestepositoryName2) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    std::string expected = "http://myCustomOmexLibrary.org/";
    rdf.setRepositoryUri(expected);
    std::string actual = editor.getRepositoryUri();
    ASSERT_TRUE(OmexMetaTestUtils::equals(&rdf, expected));
}

TEST_F(EditorTests, TestArchiveName) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    std::string expected = "http://omex-library.org/myomex.omex";
    rdf.setArchiveUri("myomex");
    std::string actual = editor.getArchiveUri();
    ASSERT_TRUE(OmexMetaTestUtils::equals(&rdf, expected));
}

TEST_F(EditorTests, TestArchiveName2) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    std::string expected = "http://omex-library.org/newOmex.omex";
    rdf.setArchiveUri("newOmex.omex");
    std::string actual = editor.getArchiveUri();
    ASSERT_TRUE(OmexMetaTestUtils::equals(&rdf, expected));
}

TEST_F(EditorTests, TestArchiveName3) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    std::string expected = "http://omex-library.org/momex.omex";
    rdf.setArchiveUri("momex.omex");
    std::string actual = editor.getArchiveUri();
    ASSERT_TRUE(OmexMetaTestUtils::equals(&rdf, expected));
}

TEST_F(EditorTests, TestSetModelName) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    rdf.setArchiveUri("MyOmexArchive");
    rdf.setModelUri("smad.sbml");

    std::string expected = "http://omex-library.org/MyOmexArchive.omex/smad.sbml#";
    ASSERT_STREQ(expected.c_str(), editor.getModelUri().c_str());
}

TEST_F(EditorTests, TestSetLocalName) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    rdf.setArchiveUri("MyOmexArchive");
    rdf.setModelUri("smad.sbml");

    std::string expected = "http://omex-library.org/MyOmexArchive.omex/smad.rdf#";
    ASSERT_STREQ(expected.c_str(), editor.getLocalUri().c_str());
}

TEST_F(EditorTests, TestSetLocalNam) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    rdf.setArchiveUri("MyOmexArchive");
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
            Subject(editor.createNodeWithModelUri("#OmexMetaId0008")),
            std::make_unique<Predicate>(BiomodelsBiologyQualifier("isDescribedBy")),
            Resource(LibrdfNode::fromUriString("pubmed:12991237")));

    std::string actual = rdf.toString();
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0008>\n"
                           "    bqbiol:isDescribedBy <https://identifiers.org/pubmed/12991237> .\n\n";
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
            Subject(LibrdfNode::fromUriString("#OmexMetaId0004")),
            predicatePtr,
            Resource(LibrdfNode::fromUriString("uniprot:P0DP23")));
    ASSERT_EQ(1, editor.size());
    //    triples.freeTriples();
}

TEST_F(EditorTests, TestAddSingleAnnotationToEditor) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);
    Triple triple(LibrdfNode::fromUriString("#OmexMetaId0009").get(),
                  BiomodelsBiologyQualifier("is").getNode(),
                  Resource(LibrdfNode::fromUriString("uniprot:P0DP23")).getNode());
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
    rdf.setArchiveUri("MyOmexArchive");
    rdf.setModelUri("mymodel.sbml");
    LibrdfNode node = editor.createNodeWithModelUri("#OmexMetaId0009");
    std::string actual = node.str();
    std::string expected = "http://omex-library.org/MyOmexArchive.omex/mymodel.sbml#OmexMetaId0009";
    ASSERT_TRUE(OmexMetaTestUtils::equals(&rdf, expected));

    node.freeNode();
}

TEST_F(EditorTests, TestAddSingleAnnotationToRDF1) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED),
            true,
            false);
    Subject subject = Subject(editor.createNodeWithModelUri("#OmexMetaId0009"));
    BiomodelsBiologyQualifier predicate("is");
    Resource resource = Resource(LibrdfNode::fromUriString("uniprot:P0DP23"));
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
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0009>\n"
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
            Subject(editor.createNodeWithModelUri("#OmexMetaId0008")),
            std::make_shared<Predicate>(BiomodelsBiologyQualifier("isDescribedBy")),
            Resource(LibrdfNode::fromUriString("pubmed:12991237")));

    std::string actual = rdf.toString("turtle");
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0008>\n"
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
            Subject(editor.createNodeWithModelUri("#OmexMetaId0008")),
            std::make_unique<Predicate>(BiomodelsBiologyQualifier("isDescribedBy")),
            Resource(LibrdfNode::fromUriString("pubmed:12991237")));

    std::string actual = rdf.toString();
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0008>\n"
                           "    bqbiol:isDescribedBy <https://identifiers.org/pubmed/12991237> .\n\n";
    std::cout << actual << std::endl;
    ASSERT_TRUE(OmexMetaTestUtils::equals(&rdf, expected));
}

TEST_F(EditorTests, TestToRDFSingularAnnotationWithLiteral) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);
    editor.addSingleAnnotation(
            Subject(editor.createNodeWithModelUri("OmexMetaId0008")),
            std::make_unique<Predicate>(DCTerm("description")),
            Resource(LibrdfNode::fromLiteral("Cardiomyocyte cytosolic ATP concentration")));

    std::string actual = rdf.toString("turtle");
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix dc: <https://dublincore.org/specifications/dublin-core/dcmi-terms/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0008>\n"
                           "    dc:description \"Cardiomyocyte cytosolic ATP concentration\"^^rdf:string .\n"
                           "\n";
    std::cout << actual << std::endl;
    ASSERT_TRUE(OmexMetaTestUtils::equals(&rdf, expected));
}

TEST_F(EditorTests, TestSingularAnnotWithBuilderPattern) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    SingularAnnotation singularAnnotation = editor.newSingularAnnotation("#OmexMetaId0001");
    singularAnnotation
            .setPredicate("bqbiol", "isVersionOf")
            .setResourceUri("uniprot:PD02635");

    editor.addSingleAnnotation(singularAnnotation);

    std::string actual = rdf.toString("turtle");
    std::cout << actual << std::endl;
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0001>\n"
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
            .about("OmexMetaId0001")
            .setPredicate("bqbiol", "isVersionOf")
            .setResourceUri("uniprot:PD02635");

    editor.addSingleAnnotation(singularAnnotation);

    std::string actual = rdf.toString("turtle");
    std::cout << actual << std::endl;
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0001>\n"
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
            .about("OmexMetaId0001")
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
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0001>\n"
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
            .about("OmexMetaId0001")
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
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0001>\n"
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
            .about("#OmexMetaId0001")
            .setPredicate("bqbiol", "isVersionOf")
            .setResourceUri("uniprot:PD02635");

    editor.addSingleAnnotation(singularAnnotation);
    editor.removeSingleAnnotation(singularAnnotation);

    SingularAnnotation singularAnnotation2 = editor.newSingularAnnotation("#OmexMetaId0001");
    singularAnnotation2
            .setPredicate("bqbiol", "isVersionOf")
            .setResourceUri("uniprot:PD02636");

    editor.addSingleAnnotation(singularAnnotation2);

    std::string actual = rdf.toString("turtle");
    std::cout << actual << std::endl;
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0001>\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/uniprot/PD02636> .\n"
                           "\n"
                           "";
    ASSERT_TRUE(OmexMetaTestUtils::equals(&rdf, expected));

    singularAnnotation.freeStatement();
    singularAnnotation2.freeStatement();
}

TEST_F(EditorTests, TestAddPhysicalEntityToEditor) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), false, false);

    PhysicalProperty ppr("metaid", "OPB:OPB_00154", editor.getModelUri());
    Resource r(LibrdfNode::fromUriString("fma:FMA:9670"));// is smad3
    std::vector<Resource> resources;
    resources.emplace_back(std::move(LibrdfNode::fromUriString("fma/FMA:9697")));
    PhysicalEntity physicalEntity(
            rdf.getModel(), editor.getModelUri(), editor.getLocalUri(), ppr, r, resources);
    //    std::shared_ptr<PhysicalEntity> ptr = std::make_shared<PhysicalEntity>(physicalEntity);
    editor.addCompositeAnnotation(&physicalEntity);
    int expected = 4;
    int actual = editor.size();
    ASSERT_EQ(expected, actual);
}

TEST_F(EditorTests, TestSingularAnnotationBuilder) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);


    SingularAnnotation singularAnnotation = editor.newSingularAnnotation("#OmexMetaId0001");
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
            .about("#OmexMetaId0001")
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
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#>\n"
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
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#>\n"
                           "    dc:created [\n"
                           "        dc:W3CDTF \"14/01/1991\"^^rdf:string\n"
                           "    ] .";
    RDF expected_rdf = RDF::fromString(expected, "turtle");
    std::cout << rdf.toString() << std::endl;
    std::cout << expected_rdf.toString() << std::endl;

    ASSERT_TRUE(OmexMetaTestUtils::equals(&rdf, &expected_rdf));


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
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#>\n"
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
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#>\n"
                           "    <http://biomodels.net/model-qualifiers/isDescribedBy> <https://identifiers.org/pubmed/27887851> .\n"
                           "\n"
                           "";
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
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#>\n"
                           "    <http://biomodels.net/model-qualifiers/isDerivedFrom> <https://identifiers.org/biomod/BIOMD0000011> .\n"
                           "\n"
                           "";
    std::string actual = rdf.toString("turtle");
    std::cout << actual << std::endl;
    ASSERT_TRUE(OmexMetaTestUtils::equals(&rdf, expected));
}

TEST_F(EditorTests, TestPhysicalEntityBuilder) {

    RDF rdf;

    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);


    PhysicalEntity physicalEntity = editor.newPhysicalEntity();

    physicalEntity
            .setPhysicalProperty("#OmexMetaId0000", "opb:opb_1234")
            .setIdentity("uniprot:PD12345")
            .addLocation("fma:fma:1234");


    editor.addPhysicalEntity(physicalEntity);


    int expected = 4;
    int actual = rdf.size();
    ASSERT_EQ(expected, actual);
}

TEST_F(EditorTests, TestPhysicalForceBuilder) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    PhysicalForce physicalForce = editor.newPhysicalForce();
    physicalForce
            .setPhysicalProperty("#OmexMetaId0000", "OPB:OPB1234")
            .addSource(1.0, "PhysicalEntity1")
            .addSink(1.0, "PhysicalEntity2");

    editor.addPhysicalForce(physicalForce);
    int expected = 8;
    int actual = rdf.size();
    ASSERT_EQ(expected, actual);
}

TEST_F(EditorTests, TestPhysicalForceBuilder2) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    PhysicalForce physicalForce = editor.newPhysicalForce();
    physicalForce
            .about("#OmexMetaId0000")
            .hasProperty("OPB:OPB1234")
            .addSource(1.0, "PhysicalEntity1")
            .addSink(1.0, "PhysicalEntity2");

    editor.addPhysicalForce(physicalForce);
    int expected = 8;
    int actual = rdf.size();
    ASSERT_EQ(expected, actual);
}

TEST_F(EditorTests, TestPhysicalProcessBuilder) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    PhysicalProcess physicalProcess = editor.newPhysicalProcess();
    physicalProcess
            .setPhysicalProperty("#OmexMetaId0000", "OPB:OPB1234")
            .addSource(1.0, "PhysicalEntity1")
            .addSink(1.0, "PhysicalEntity2")
            .addMediator("PhysicalEntity3");

    editor.addPhysicalProcess(physicalProcess);

    int expected = 10;
    int actual = rdf.size();
    ASSERT_EQ(expected, actual);
}

TEST_F(EditorTests, TestSingularAnnotationBuilderAlternativeInterface) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    SingularAnnotation singularAnnotation = editor.newSingularAnnotation("#OmexMetaId0000");
    singularAnnotation
            .setPredicate("bqbiol", "is")
            .setResourceLiteral("resource");

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0000>\n"
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

    SingularAnnotation singularAnnotation = editor.newSingularAnnotation("#OmexMetaId0001");
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

TEST_F(EditorTests, TestRemovePhysicalForce) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    PhysicalForce physicalForce = editor.newPhysicalForce();
    physicalForce
            .setPhysicalProperty("#OmexMetaId0002", "OPB:OPB1234")
            .addSource(1.0, "PhysicalEntity1")
            .addSink(1.0, "PhysicalEntity2");
    editor.addPhysicalForce(physicalForce);
    ASSERT_EQ(8, rdf.size());
    editor.removePhysicalForce(physicalForce);
    int expected = 0;
    int actual = rdf.size();
    ASSERT_EQ(expected, actual);
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

TEST_F(EditorTests, TestRemovePhysicalProcess) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    PhysicalProcess physicalProcess = editor.newPhysicalProcess();
    physicalProcess
            .setPhysicalProperty("#OmexMetaId0004", "OPB:OPB1234")
            .addSource(1.0, "PhysicalEntity1")
            .addMediator("PhysicalEntity1")
            .addSink(1.0, "PhysicalEntity2");
    editor.addPhysicalProcess(physicalProcess);
    ASSERT_EQ(10, rdf.size());
    editor.removePhysicalProcess(physicalProcess);
    int expected = 0;
    int actual = rdf.size();
    ASSERT_EQ(expected, actual);
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
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#>\n"
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

TEST_F(EditorTests, TestAddTwoDifferentPhysicalEntities) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED2), true);

    std::cout << editor.getXml() << std::endl;
    std::string r1_metaid = "#OmexMetaId0005";
    std::string r2_metaid = "#OmexMetaId0009";

    PhysicalProcess r1 = editor.newPhysicalProcess();
    r1.setPhysicalProperty(r1_metaid, "OPB:OPB1234")
            .addSource(1.0, "#Meta00001")
            .addSink(1.0, "#OmexMetaId0003");
    editor.addPhysicalProcess(r1);

    PhysicalProcess r2 = editor.newPhysicalProcess();
    r2.setPhysicalProperty(r2_metaid, "OPB:OPB1234")
            .addSource(1.0, "#OmexMetaId0003")
            .addSink(1.0, "#OmexMetaId0004")
            .addMediator("#Meta00001");
    editor.addPhysicalProcess(r2);

    std::cout << rdf.toString("turtle") << std::endl;
}

TEST_F(EditorTests, TestEditorWithoutGivingTypeInformation) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED2), true);

    std::cout << editor.getXml() << std::endl;
    std::string r1_metaid = "#OmexMetaId0005";
    std::string r2_metaid = "#OmexMetaId0009";

    PhysicalProcess r1 = editor.newPhysicalProcess();
    r1.setPhysicalProperty(r1_metaid, "OPB:OPB1234")
            .addSource(1.0, "#Meta00001")
            .addSink(1.0, "#OmexMetaId0003");
    editor.addPhysicalProcess(r1);

    PhysicalProcess r2 = editor.newPhysicalProcess();
    r2.setPhysicalProperty(r2_metaid, "OPB:OPB1234")
            .addSource(1.0, "#OmexMetaId0003")
            .addSink(1.0, "#OmexMetaId0004")
            .addMediator("#Meta00001");
    editor.addPhysicalProcess(r2);

    std::cout << rdf.toString("turtle") << std::endl;
}

/*****************************************************************
 * Test PhysicalEntity memory accountability
 */
class EditorTestsPhysicalEntityMemory : public ::testing::Test {
public:
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);
    PhysicalEntity physicalEntity = editor.newPhysicalEntity();

    EditorTestsPhysicalEntityMemory() {
        physicalEntity
                .setPhysicalProperty("#OmexMetaId0000", "opb:opb_1234")
                .setIdentity("uniprot:PD12345")
                .addLocation("fma:fma:1234");
    };
};

TEST_F(EditorTestsPhysicalEntityMemory, TestPhysicalEntityAdds4TriplesToModel) {

    editor.addPhysicalEntity(physicalEntity);
    ASSERT_EQ(4, rdf.size());
}

TEST_F(EditorTestsPhysicalEntityMemory, TestUnpackTriplesAndAccountForStatements) {
    Triples triples = physicalEntity.toTriples();

    // unpack triples
    Triple triple4 = triples.pop();
    Triple triple3 = triples.pop();
    Triple triple2 = triples.pop();
    Triple triple1 = triples.pop();

    // make sure we've emptied the triples object
    ASSERT_EQ(0, triples.size());

    // check that all statements have 1 usage
    ASSERT_EQ(1, triple1.getStatement()->usage);
    ASSERT_EQ(1, triple2.getStatement()->usage);
    ASSERT_EQ(1, triple3.getStatement()->usage);
    ASSERT_EQ(1, triple4.getStatement()->usage);

    triple4.freeStatement();
    triple3.freeStatement();
    triple2.freeStatement();
    triple1.freeStatement();
}

TEST_F(EditorTestsPhysicalEntityMemory, TestUnpackTriplesAndAccountForTerms) {
    Triples triples = physicalEntity.toTriples();

    // unpack triples
    Triple triple4 = triples.pop();
    Triple triple3 = triples.pop();
    Triple triple2 = triples.pop();
    Triple triple1 = triples.pop();

    // make sure we've emptied the triples object
    ASSERT_EQ(0, triples.size());

    ASSERT_EQ(1, triple1.getSubject()->usage);
    ASSERT_EQ(1, triple2.getSubject()->usage);
    ASSERT_EQ(1, triple3.getSubject()->usage);
    ASSERT_EQ(1, triple4.getSubject()->usage);

    ASSERT_EQ(1, triple1.getPredicate()->usage);
    ASSERT_EQ(1, triple2.getPredicate()->usage);
    ASSERT_EQ(1, triple3.getPredicate()->usage);
    ASSERT_EQ(1, triple4.getPredicate()->usage);

    ASSERT_EQ(1, triple1.getResource()->usage);
    ASSERT_EQ(1, triple2.getResource()->usage);
    ASSERT_EQ(1, triple3.getResource()->usage);
    ASSERT_EQ(1, triple4.getResource()->usage);

    triple4.freeStatement();
    triple3.freeStatement();
    triple2.freeStatement();
    triple1.freeStatement();
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
class EditorTestsDeletePhysicalEntity : public ::testing::Test {
public:
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBML(SBML_NOT_ANNOTATED), true, false);

    std::string local_uri = "http://omex-library.org/NewOmex.omex/NewModel.rdf#";

    EditorTestsDeletePhysicalEntity() = default;
};

TEST_F(EditorTestsDeletePhysicalEntity, TestRDFSizeBeforeRemovingAndNoMemoryLeaks) {
    PhysicalEntity physicalEntity = editor.newPhysicalEntity();
    physicalEntity
            .setPhysicalProperty("#OmexMetaId0000", "opb:opb_1234")
            .setIdentity("uniprot:PD12345")
            .addLocation("fma:fma:1234");
    editor.addPhysicalEntity(physicalEntity);
    ASSERT_EQ(4, rdf.size());
    //    editor.removePhysicalEntity(physicalEntity);
}

TEST_F(EditorTestsDeletePhysicalEntity, TestRemoveSingleTriple1) {
    Triple triple(
            LibrdfNode::fromUriString("#OmexMetaId0000"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isVersionOf"),
            LibrdfNode::fromUriString("https://identifiers.org/opb/opb_1234"));
    editor.addSingleAnnotation(triple);
    ASSERT_EQ(1, rdf.size());
    editor.removeSingleAnnotation(triple);
    ASSERT_EQ(0, rdf.size());
    triple.freeTriple();
}

TEST_F(EditorTestsDeletePhysicalEntity, TestRemoveSingleTriple2) {
    /* Take and delete triple number 1
 * 1) <#OmexMetaId0000> <http://biomodels.net/biology-qualifiers/isVersionOf> <https://identifiers.org/opb/opb_1234> .
 * 2) <#OmexMetaId0000> <http://biomodels.net/biology-qualifiers/isPropertyOf> <EntityProperty0001> .
 * 3) <EntityProperty0001> <http://biomodels.net/biology-qualifiers/is> <https://identifiers.org/uniprot/PD12345> .
 * 4) <EntityProperty0001> <http://biomodels.net/biology-qualifiers/isPartOf> <https://identifiers.org/fma/fma:1234> .
 */
    Triple triple(
            LibrdfNode::fromUriString("#OmexMetaId0000"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPropertyOf"),
            LibrdfNode::fromUriString("EntityProperty0001"));
    editor.addSingleAnnotation(triple);
    ASSERT_EQ(1, rdf.size());
    editor.removeSingleAnnotation(triple);
    ASSERT_EQ(0, rdf.size());
    triple.freeTriple();
}

TEST_F(EditorTestsDeletePhysicalEntity, TestRemoveSingleTriple3) {
    /* Take and delete triple number 1
     * 1) <#OmexMetaId0000> <http://biomodels.net/biology-qualifiers/isVersionOf> <https://identifiers.org/opb/opb_1234> .
     * 2) <#OmexMetaId0000> <http://biomodels.net/biology-qualifiers/isPropertyOf> <EntityProperty0001> .
     * 3) <EntityProperty0001> <http://biomodels.net/biology-qualifiers/is> <https://identifiers.org/uniprot/PD12345> .
     * 4) <EntityProperty0001> <http://biomodels.net/biology-qualifiers/isPartOf> <https://identifiers.org/fma/fma:1234> .
     */
    Triple triple(
            LibrdfNode::fromUriString("#Meta00001"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/is"),
            LibrdfNode::fromUriString("https://identifiers.org/uniprot/PD12345"));
    editor.addSingleAnnotation(triple);
    ASSERT_EQ(1, rdf.size());
    editor.removeSingleAnnotation(triple);
    ASSERT_EQ(0, rdf.size());
    triple.freeTriple();
}

TEST_F(EditorTestsDeletePhysicalEntity, TestRemoveSingleTriple4) {
    /* Take and delete triple number 1
 * 1) <#OmexMetaId0000> <http://biomodels.net/biology-qualifiers/isVersionOf> <https://identifiers.org/opb/opb_1234> .
 * 2) <#OmexMetaId0000> <http://biomodels.net/biology-qualifiers/isPropertyOf> <EntityProperty0001> .
 * 3) <EntityProperty0001> <http://biomodels.net/biology-qualifiers/is> <https://identifiers.org/uniprot/PD12345> .
 * 4) <EntityProperty0001> <http://biomodels.net/biology-qualifiers/isPartOf> <https://identifiers.org/fma/fma:1234> .
 */
    Triple triple(
            LibrdfNode::fromUriString("#cytosol"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf"),
            LibrdfNode::fromUriString("https://identifiers.org/fma/fma:1234"));
    editor.addSingleAnnotation(triple);
    ASSERT_EQ(1, rdf.size());
    editor.removeSingleAnnotation(triple);
    ASSERT_EQ(0, rdf.size());
    triple.freeTriple();
}

TEST_F(EditorTestsDeletePhysicalEntity, TestRemoveSingleTripleWithFreeInMiddle) {
    Triple triple(
            LibrdfNode::fromUriString("#cytosol"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf"),
            LibrdfNode::fromUriString("https://identifiers.org/fma/fma:1234"));
    editor.addSingleAnnotation(triple);
    ASSERT_EQ(1, rdf.size());
    triple.freeTriple();

    Triple triple2(
            LibrdfNode::fromUriString("#cytosol"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf"),
            LibrdfNode::fromUriString("https://identifiers.org/fma/fma:1234"));
    editor.removeSingleAnnotation(triple2);
    ASSERT_EQ(0, rdf.size());
    triple2.freeTriple();
}

TEST_F(EditorTestsDeletePhysicalEntity, TestRemoveSingleTripleFromTriples) {
    Triple triple(
            LibrdfNode::fromUriString("#cytosol"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf"),
            LibrdfNode::fromUriString("https://identifiers.org/fma/fma:1234"));
    // put triple in Triples
    Triples triples(1);
    triples.move_back(triple);

    // add to the model
    for (auto &it : triples) {
        editor.addSingleAnnotation(it);
    }

    // check rdf size
    ASSERT_EQ(1, rdf.size());

    // free triples
    triples.freeTriples();

    // get the Triples again. Same content, different instance
    Triple triple2(
            LibrdfNode::fromUriString("#cytosol"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf"),
            LibrdfNode::fromUriString("https://identifiers.org/fma/fma:1234"));
    // put triple in Triples
    Triples triples2(1);
    triples2.move_back(triple2);

    // use it to remove the triple
    for (auto &it : triples2) {
        editor.removeSingleAnnotation(it);
    }
    // should be no triples left now in rdf
    ASSERT_EQ(0, rdf.size());

    // free
    triples2.freeTriples();
}

TEST_F(EditorTestsDeletePhysicalEntity, TestRemoveTwoTripleObjsFromTriplesDifferentContent) {
    // Here these triples have different content. Next test they have same content.
    Triple triple1(
            LibrdfNode::fromUriString("cytosol1"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf1"),
            LibrdfNode::fromUriString("https://identifiers.org/fma/fma:12341"));
    Triple triple2(
            LibrdfNode::fromUriString("cytosol2"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf2"),
            LibrdfNode::fromUriString("https://identifiers.org/fma/fma:12342"));
    // put triple in Triples
    Triples triples(2);
    triples.move_back(triple1);
    triples.move_back(triple2);

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
    triples.freeTriples();
}

TEST_F(EditorTestsDeletePhysicalEntity, TestRemoveTwoTripleObjsFromTriplesSameSubject) {
    // Here these triples have different content. Next test they have same content.
    Triple triple1(
            LibrdfNode::fromUriString("cytosol"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf1"),
            LibrdfNode::fromUriString("https://identifiers.org/fma/fma:12341"));
    Triple triple2(
            LibrdfNode::fromUriString("cytosol"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf2"),
            LibrdfNode::fromUriString("https://identifiers.org/fma/fma:12342"));
    // put triple in Triples
    Triples triples(2);
    triples.move_back(triple1);
    triples.move_back(triple2);

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
    triples.freeTriples();
}

TEST_F(EditorTestsDeletePhysicalEntity, TestRemoveTwoTripleObjsFromTriplesSameSubjectAndPredicate) {
    // Here these triples have different content. Next test they have same content.
    Triple triple1(
            LibrdfNode::fromUriString("cytosol"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf"),
            LibrdfNode::fromUriString("https://identifiers.org/fma/fma:12341"));
    Triple triple2(
            LibrdfNode::fromUriString("cytosol"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf"),
            LibrdfNode::fromUriString("https://identifiers.org/fma/fma:12342"));
    // put triple in Triples
    Triples triples(2);
    triples.move_back(triple1);
    triples.move_back(triple2);

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
    triples.freeTriples();
}

TEST_F(EditorTestsDeletePhysicalEntity, TestRemoveTwoTripleObjsFromTriplesSameSubjectAndResource) {
    // Here these triples have different content. Next test they have same content.
    Triple triple1(
            LibrdfNode::fromUriString("cytosol"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf1"),
            LibrdfNode::fromUriString("https://identifiers.org/fma/fma:1234"));
    Triple triple2(
            LibrdfNode::fromUriString("cytosol"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf2"),
            LibrdfNode::fromUriString("https://identifiers.org/fma/fma:1234"));
    // put triple in Triples
    Triples triples(2);
    triples.move_back(triple1);
    triples.move_back(triple2);

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
    triples.freeTriples();
}

TEST_F(EditorTestsDeletePhysicalEntity, TestRemoveTwoTripleObjsFromTriplesSamePredicateAndResource) {
    // Here these triples have different content. Next test they have same content.
    Triple triple1(
            LibrdfNode::fromUriString("cytosol1"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf"),
            LibrdfNode::fromUriString("https://identifiers.org/fma/fma:1234"));
    Triple triple2(
            LibrdfNode::fromUriString("cytosol2"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf"),
            LibrdfNode::fromUriString("https://identifiers.org/fma/fma:1234"));
    // put triple in Triples
    Triples triples(2);
    triples.move_back(triple1);
    triples.move_back(triple2);

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
    triples.freeTriples();
}

TEST_F(EditorTestsDeletePhysicalEntity, TestRemoveTwoTripleObjsFromTriplesSameEverything) {
    /*
     * When trying to add a duplicate triple to the model,
     * it seems that raptor catches it and does not add the triple again.
     */
    Triple triple1(
            LibrdfNode::fromUriString("cytosol"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf"),
            LibrdfNode::fromUriString("https://identifiers.org/fma/fma:1234"));

    Triple triple2(
            LibrdfNode::fromUriString("cytosol"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf"),
            LibrdfNode::fromUriString("https://identifiers.org/fma/fma:1234"));
    // put triple in Triples
    Triples triples(2);
    triples.move_back(triple1);
    triples.move_back(triple2);

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
    triples.freeTriples();
}

TEST_F(EditorTestsDeletePhysicalEntity, TestRemoveTwoTripleObjsFromTriplesWithFreeInMiddle) {
    Triple triple1(
            LibrdfNode::fromUriString("#cytosol"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf"),
            LibrdfNode::fromUriString("https://identifiers.org/fma/fma:1234"));
    Triple triple2(
            LibrdfNode::fromUriString("#cytosol"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf"),
            LibrdfNode::fromUriString("https://identifiers.org/fma/fma:1234"));
    // put triple in Triples
    Triples triples(2);
    triples.move_back(triple1);
    triples.move_back(triple2);

    // add to the model
    for (auto &it : triples) {
        editor.addSingleAnnotation(it);
    }

    // check rdf size
    // These are duplicates, so only 1 will be added to the raptor model
    ASSERT_EQ(1, rdf.size());

    // free triples
    triples.freeTriples();

    Triple triple3(
            LibrdfNode::fromUriString("#cytosol"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf"),
            LibrdfNode::fromUriString("https://identifiers.org/fma/fma:1234"));
    Triple triple4(
            LibrdfNode::fromUriString("#cytosol"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf"),
            LibrdfNode::fromUriString("https://identifiers.org/fma/fma:1234"));
    // put triple in Triples
    Triples triples2(2);
    triples2.move_back(triple3);
    triples2.move_back(triple4);

    // use it to remove the triple
    for (auto &it : triples2) {
        editor.removeSingleAnnotation(it);
    }
    // should be no triples left now in rdf
    ASSERT_EQ(0, rdf.size());

    // free
    triples2.freeTriples();
}


TEST_F(EditorTestsDeletePhysicalEntity, TestRemoveDoubleTriple1And2Sequential) {
    /* Take and delete triple number 1
 * 1) <#OmexMetaId0000> <http://biomodels.net/biology-qualifiers/isVersionOf> <https://identifiers.org/opb/opb_1234> .
 * 2) <#OmexMetaId0000> <http://biomodels.net/biology-qualifiers/isPropertyOf> <EntityProperty0001> .
 * 3) <EntityProperty0001> <http://biomodels.net/biology-qualifiers/is> <https://identifiers.org/uniprot/PD12345> .
 * 4) <EntityProperty0001> <http://biomodels.net/biology-qualifiers/isPartOf> <https://identifiers.org/fma/fma:1234> .
 */
    Triple triple(
            LibrdfNode::fromUriString("#OmexMetaId0000"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isVersionOf"),
            LibrdfNode::fromUriString("https://identifiers.org/opb/opb_1234"));
    editor.addSingleAnnotation(triple);
    ASSERT_EQ(1, rdf.size());
    editor.removeSingleAnnotation(triple);
    ASSERT_EQ(0, rdf.size());
    triple.freeTriple();

    Triple triple2(
            LibrdfNode::fromUriString("#OmexMetaId0000"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPropertyOf"),
            LibrdfNode::fromUriString("EntityProperty0001"));
    editor.addSingleAnnotation(triple2);
    ASSERT_EQ(1, rdf.size());
    editor.removeSingleAnnotation(triple2);
    ASSERT_EQ(0, rdf.size());
    triple2.freeTriple();
}

TEST_F(EditorTestsDeletePhysicalEntity, TestRemoveDoubleTriple1And2SequentialAndFreeOnlyAtEnd) {
    /* Take and delete triple number 1
 * 1) <#OmexMetaId0000> <http://biomodels.net/biology-qualifiers/isVersionOf> <https://identifiers.org/opb/opb_1234> .
 * 2) <#OmexMetaId0000> <http://biomodels.net/biology-qualifiers/isPropertyOf> <EntityProperty0001> .
 * 3) <EntityProperty0001> <http://biomodels.net/biology-qualifiers/is> <https://identifiers.org/uniprot/PD12345> .
 * 4) <EntityProperty0001> <http://biomodels.net/biology-qualifiers/isPartOf> <https://identifiers.org/fma/fma:1234> .
 */
    Triple triple(
            LibrdfNode::fromUriString("#OmexMetaId0000"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isVersionOf"),
            LibrdfNode::fromUriString("https://identifiers.org/opb/opb_1234"));
    editor.addSingleAnnotation(triple);
    ASSERT_EQ(1, rdf.size());
    editor.removeSingleAnnotation(triple);
    ASSERT_EQ(0, rdf.size());

    Triple triple2(
            LibrdfNode::fromUriString("https://#OmexMetaId0000"),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPropertyOf"),
            LibrdfNode::fromUriString("EntityProperty0001"));
    editor.addSingleAnnotation(triple2);
    ASSERT_EQ(1, rdf.size());
    editor.removeSingleAnnotation(triple2);
    ASSERT_EQ(0, rdf.size());
    triple.freeTriple();
    triple2.freeTriple();
}

TEST_F(EditorTestsDeletePhysicalEntity, TestCreateAddAndRemoveTripleFromAPhysicalPropertyWithoutDeletingItInMiddle) {
    /* Take and delete triple number 1
 * 1) <#OmexMetaId0000> <http://biomodels.net/biology-qualifiers/isVersionOf> <https://identifiers.org/opb/opb_1234> .
 * 2) <#OmexMetaId0000> <http://biomodels.net/biology-qualifiers/isPropertyOf> <EntityProperty0001> .
 * 3) <EntityProperty0001> <http://biomodels.net/biology-qualifiers/is> <https://identifiers.org/uniprot/PD12345> .
 * 4) <EntityProperty0001> <http://biomodels.net/biology-qualifiers/isPartOf> <https://identifiers.org/fma/fma:1234> .
 */
    PhysicalProperty property("http://omex-library.org/NewOmex.omex/NewModel.rdf#OmexMetaId0001", "https://identifiers.org/opb/opb_1234", local_uri);
    Triples triples = property.toTriples("http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0000");
    std::cout << triples.str() << std::endl;
    for (auto &it : triples) {
        editor.addSingleAnnotation(it);
    }
    ASSERT_EQ(2, rdf.size());
    for (auto &it : triples) {
        editor.removeSingleAnnotation(it);
    }
    ASSERT_EQ(0, rdf.size());
    triples.freeTriples();
}

TEST_F(EditorTestsDeletePhysicalEntity, TestCreateAddAndRemoveTripleFromAPhysicalPropertyWithFreeInMiddle) {
    /* Take and delete triple number 1
 * 1) <#OmexMetaId0000> <http://biomodels.net/biology-qualifiers/isVersionOf> <https://identifiers.org/opb/opb_1234> .
 * 2) <#OmexMetaId0000> <http://biomodels.net/biology-qualifiers/isPropertyOf> <EntityProperty0001> .
 * 3) <EntityProperty0001> <http://biomodels.net/biology-qualifiers/is> <https://identifiers.org/uniprot/PD12345> .
 * 4) <EntityProperty0001> <http://biomodels.net/biology-qualifiers/isPartOf> <https://identifiers.org/fma/fma:1234> .
 */
    PhysicalProperty property("http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0001", "https://identifiers.org/opb/opb_1234", editor.getModelUri());
    Triples triples = property.toTriples("http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0001");
    std::cout << rdf.toString() << std::endl;
    for (auto &it : triples) {
        editor.addSingleAnnotation(it);
    }
    std::cout << rdf.toString() << std::endl;
    ASSERT_EQ(2, rdf.size());
    triples.freeTriples();

    Triples triples2 = property.toTriples("http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0001");
    std::cout << triples2.size() << std::endl;

    for (auto &it : triples2) {
        std::cout << it.str() << std::endl;
        editor.removeSingleAnnotation(it);
    }
    std::cout << rdf.toString() << std::endl;
    ASSERT_EQ(0, rdf.size());
    triples2.freeTriples();
}

TEST_F(EditorTestsDeletePhysicalEntity, TestCreateAddAndRemoveTripleFromAPropertyOfPhysicalEntity) {
    /* Take and delete triple number 1
 * 1) <#OmexMetaId0000> <http://biomodels.net/biology-qualifiers/isVersionOf> <https://identifiers.org/opb/opb_1234> .
 * 2) <#OmexMetaId0000> <http://biomodels.net/biology-qualifiers/isPropertyOf> <EntityProperty0001> .
 * 3) <EntityProperty0001> <http://biomodels.net/biology-qualifiers/is> <https://identifiers.org/uniprot/PD12345> .
 * 4) <EntityProperty0001> <http://biomodels.net/biology-qualifiers/isPartOf> <https://identifiers.org/fma/fma:1234> .
 */
    PhysicalEntity physicalEntity = editor.newPhysicalEntity();
    physicalEntity
            .setPhysicalProperty("http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0000", "opb:opb_1234")
            .setIdentity("uniprot:PD12345")
            .addLocation("fma:fma:1234");
    Triples triples = physicalEntity.toTriples();
    std::cout << triples.str() << std::endl;
    for (auto &it : triples) {
        editor.addSingleAnnotationNoValidation(it);
    }
    ASSERT_EQ(4, rdf.size());
    for (auto &it : triples) {
        editor.removeSingleAnnotation(it);
    }
    ASSERT_EQ(0, rdf.size());
    triples.freeTriples();
}

TEST_F(EditorTestsDeletePhysicalEntity,
       TestCreateAddAndRemoveTripleFromAPropertyOfPhysicalEntityWithNamespaceHandling) {
    PhysicalEntity physicalEntity = editor.newPhysicalEntity();
    physicalEntity
            .setPhysicalProperty("http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0000", "opb:opb_1234")
            .setIdentity("uniprot:PD12345")
            .addLocation("fma:fma:1234");
    Triples triples = physicalEntity.toTriples();
    std::cout << triples.str() << std::endl;
    for (auto &it : triples) {
        editor.addSingleAnnotationNoValidation(it);
        editor.addNamespaceFromAnnotation(it.getPredicateStr());
    }
    ASSERT_EQ(4, rdf.size());
    for (auto &it : triples) {
        editor.removeSingleAnnotation(it);
    }
    ASSERT_EQ(0, rdf.size());
    triples.freeTriples();
}

TEST_F(EditorTestsDeletePhysicalEntity, TestCreateAddAndRemoveTripleFromAPropertyOfPhysicalEntityWithFreeInMiddle) {
    PhysicalEntity physicalEntity = editor.newPhysicalEntity();
    physicalEntity
            .setPhysicalProperty("http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0000", "opb:opb_1234")
            .setIdentity("uniprot:PD12345")
            .addLocation("fma:fma:1234");
    Triples triples = physicalEntity.toTriples();
    for (auto &it : triples) {
        editor.addSingleAnnotationNoValidation(it);
        editor.addNamespaceFromAnnotation(it.getPredicateStr());
    }
    ASSERT_EQ(4, rdf.size());
    triples.freeTriples();

    Triples triples2 = physicalEntity.toTriples();
    for (auto &it : triples2) {
        editor.removeSingleAnnotation(it);
    }
    ASSERT_EQ(0, rdf.size());
    //    triples2.freeTriples();
}

TEST_F(EditorTestsDeletePhysicalEntity, TestCreateAddAndRemovePhysicalEntityUsingSingleTripleObjsRemove1) {
    PhysicalEntity physicalEntity = editor.newPhysicalEntity();
    physicalEntity
            .setPhysicalProperty("http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0000", "opb:opb_1234")
            .setIdentity("uniprot:PD12345")
            .addLocation("fma:fma:1234");
    Triples triples = physicalEntity.toTriples();
    for (auto &it : triples) {
        editor.addSingleAnnotationNoValidation(it);
        editor.addNamespaceFromAnnotation(it.getPredicateStr());
    }
    ASSERT_EQ(4, rdf.size());
    triples.freeTriples();

    Triple triple1(
            LibrdfNode::fromUriString(
                    OmexMetaUtils::concatMetaIdAndUri("#EntityProperty0000", physicalEntity.getLocalUri())),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/is"),
            LibrdfNode::fromUriString("https://identifiers.org/uniprot/PD12345"));
    Triple triple2(
            LibrdfNode::fromUriString(
                    OmexMetaUtils::concatMetaIdAndUri("#EntityProperty0000", physicalEntity.getLocalUri())),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf"),
            LibrdfNode::fromUriString("https://identifiers.org/fma/fma:1234"));
    Triple triple3(
            LibrdfNode::fromUriString(
                    OmexMetaUtils::concatMetaIdAndUri("#OmexMetaId0000", physicalEntity.getModelUri())),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPropertyOf"),
            LibrdfNode::fromUriString(
                    OmexMetaUtils::concatMetaIdAndUri("#EntityProperty0000", physicalEntity.getLocalUri())));
    Triple triple4(
            LibrdfNode::fromUriString(
                    OmexMetaUtils::concatMetaIdAndUri("#OmexMetaId0000", physicalEntity.getModelUri())),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isVersionOf"),
            LibrdfNode::fromUriString("https://identifiers.org/opb/opb_1234"));
    editor.removeSingleAnnotation(triple1);
    ASSERT_EQ(3, rdf.size());
    triple1.freeTriple();
    triple2.freeTriple();
    triple3.freeTriple();
    triple4.freeTriple();
}

TEST_F(EditorTestsDeletePhysicalEntity, TestCreateAddAndRemovePhysicalEntityUsingSingleTripleObjsRemove2) {
    PhysicalEntity physicalEntity = editor.newPhysicalEntity();
    physicalEntity
            .setPhysicalProperty("http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0000", "opb:opb_1234")
            .setIdentity("uniprot:PD12345")
            .addLocation("fma:fma:1234");
    Triples triples = physicalEntity.toTriples();
    for (auto &it : triples) {
        editor.addSingleAnnotationNoValidation(it);
        editor.addNamespaceFromAnnotation(it.getPredicateStr());
    }
    ASSERT_EQ(4, rdf.size());
    triples.freeTriples();

    Triple triple1(
            LibrdfNode::fromUriString(
                    OmexMetaUtils::concatMetaIdAndUri("#EntityProperty0000", physicalEntity.getLocalUri())),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/is"),
            LibrdfNode::fromUriString("https://identifiers.org/uniprot/PD12345"));
    Triple triple2(
            LibrdfNode::fromUriString(
                    OmexMetaUtils::concatMetaIdAndUri("#EntityProperty0000", physicalEntity.getLocalUri())),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf"),
            LibrdfNode::fromUriString("https://identifiers.org/fma/fma:1234"));
    Triple triple3(
            LibrdfNode::fromUriString(
                    OmexMetaUtils::concatMetaIdAndUri("#OmexMetaId0000", physicalEntity.getModelUri())),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPropertyOf"),
            LibrdfNode::fromUriString(
                    OmexMetaUtils::concatMetaIdAndUri("#EntityProperty0000", physicalEntity.getLocalUri())));
    Triple triple4(
            LibrdfNode::fromUriString(
                    OmexMetaUtils::concatMetaIdAndUri("#OmexMetaId0000", physicalEntity.getLocalUri())),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isVersionOf"),
            LibrdfNode::fromUriString("https://identifiers.org/opb/opb_1234"));

    editor.removeSingleAnnotation(triple2);
    ASSERT_EQ(3, rdf.size());

    triple1.freeTriple();
    triple2.freeTriple();
    triple3.freeTriple();
    triple4.freeTriple();
}

TEST_F(EditorTestsDeletePhysicalEntity, TestCreateAddAndRemovePhysicalEntityUsingSingleTripleObjsRemove3) {
    PhysicalEntity physicalEntity = editor.newPhysicalEntity();
    physicalEntity
            .setPhysicalProperty("#OmexMetaId0000", "opb:opb_1234")
            .setIdentity("uniprot:PD12345")
            .addLocation("fma:fma:1234");
    Triples triples = physicalEntity.toTriples();
    for (auto &it : triples) {
        editor.addSingleAnnotationNoValidation(it);
        editor.addNamespaceFromAnnotation(it.getPredicateStr());
    }
    ASSERT_EQ(4, rdf.size());
    triples.freeTriples();

    Triple triple1(
            LibrdfNode::fromUriString(
                    OmexMetaUtils::concatMetaIdAndUri("#EntityProperty0000", physicalEntity.getLocalUri())),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/is"),
            LibrdfNode::fromUriString("https://identifiers.org/uniprot/PD12345"));
    Triple triple2(
            LibrdfNode::fromUriString(
                    OmexMetaUtils::concatMetaIdAndUri("#EntityProperty0000", physicalEntity.getLocalUri())),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf"),
            LibrdfNode::fromUriString("https://identifiers.org/fma/fma:1234"));
    Triple triple3(
            LibrdfNode::fromUriString(
                    OmexMetaUtils::concatMetaIdAndUri("#OmexMetaId0000", physicalEntity.getModelUri())),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPropertyOf"),
            LibrdfNode::fromUriString(
                    OmexMetaUtils::concatMetaIdAndUri("#EntityProperty0000", physicalEntity.getLocalUri())));
    Triple triple4(
            LibrdfNode::fromUriString(
                    OmexMetaUtils::concatMetaIdAndUri("#OmexMetaId0000", physicalEntity.getModelUri())),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isVersionOf"),
            LibrdfNode::fromUriString("https://identifiers.org/opb/opb_1234"));

    editor.removeSingleAnnotation(triple3);
    ASSERT_EQ(3, rdf.size());

    triple1.freeTriple();
    triple2.freeTriple();
    triple3.freeTriple();
    triple4.freeTriple();
}

TEST_F(EditorTestsDeletePhysicalEntity, TestCreateAddAndRemovePhysicalEntityUsingSingleTripleObjsRemove4) {
    PhysicalEntity physicalEntity = editor.newPhysicalEntity();
    physicalEntity
            .setPhysicalProperty("#OmexMetaId0000", "opb:opb_1234")
            .setIdentity("uniprot:PD12345")
            .addLocation("fma:fma:1234");
    Triples triples = physicalEntity.toTriples();
    for (auto &it : triples) {
        editor.addSingleAnnotationNoValidation(it);
        editor.addNamespaceFromAnnotation(it.getPredicateStr());
    }
    ASSERT_EQ(4, rdf.size());
    triples.freeTriples();

    Triple triple1(
            LibrdfNode::fromUriString(
                    OmexMetaUtils::concatMetaIdAndUri("#EntityProperty0000", physicalEntity.getLocalUri())),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/is"),
            LibrdfNode::fromUriString("https://identifiers.org/uniprot/PD12345"));
    Triple triple2(
            LibrdfNode::fromUriString(
                    OmexMetaUtils::concatMetaIdAndUri("#EntityProperty0000", physicalEntity.getLocalUri())),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf"),
            LibrdfNode::fromUriString("https://identifiers.org/fma/fma:1234"));
    Triple triple3(
            LibrdfNode::fromUriString(
                    OmexMetaUtils::concatMetaIdAndUri("#OmexMetaId0000", physicalEntity.getModelUri())),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPropertyOf"),
            LibrdfNode::fromUriString(
                    OmexMetaUtils::concatMetaIdAndUri("#EntityProperty0000", physicalEntity.getLocalUri())));
    Triple triple4(
            LibrdfNode::fromUriString(
                    OmexMetaUtils::concatMetaIdAndUri("#OmexMetaId0000", physicalEntity.getModelUri())),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isVersionOf"),
            LibrdfNode::fromUriString("https://identifiers.org/opb/opb_1234"));
    editor.removeSingleAnnotation(triple4);
    ASSERT_EQ(3, rdf.size());

    triple1.freeTriple();
    triple2.freeTriple();
    triple3.freeTriple();
    triple4.freeTriple();
}

TEST_F(EditorTestsDeletePhysicalEntity, TestCreateAddAndRemovePhysicalEntityUsingSingleTripleObjsRemove1And2) {
    PhysicalEntity physicalEntity = editor.newPhysicalEntity();
    physicalEntity
            .setPhysicalProperty("#OmexMetaId0000", "opb:opb_1234")
            .setIdentity("uniprot:PD12345")
            .addLocation("fma:fma:1234");
    Triples triples = physicalEntity.toTriples();
    for (auto &it : triples) {
        editor.addSingleAnnotationNoValidation(it);
        editor.addNamespaceFromAnnotation(it.getPredicateStr());
    }
    ASSERT_EQ(4, rdf.size());
    triples.freeTriples();

    Triple triple1(
            LibrdfNode::fromUriString(
                    OmexMetaUtils::concatMetaIdAndUri("#EntityProperty0000", physicalEntity.getLocalUri())),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/is"),
            LibrdfNode::fromUriString("https://identifiers.org/uniprot/PD12345"));
    Triple triple2(
            LibrdfNode::fromUriString(
                    OmexMetaUtils::concatMetaIdAndUri("#EntityProperty0000", physicalEntity.getLocalUri())),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPartOf"),
            LibrdfNode::fromUriString("https://identifiers.org/fma/fma:1234"));
    Triple triple3(
            LibrdfNode::fromUriString(
                    OmexMetaUtils::concatMetaIdAndUri("#OmexMetaId0000", physicalEntity.getModelUri())),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isPropertyOf"),
            LibrdfNode::fromUriString(
                    OmexMetaUtils::concatMetaIdAndUri("#EntityProperty0000", physicalEntity.getLocalUri())));
    Triple triple4(
            LibrdfNode::fromUriString(
                    OmexMetaUtils::concatMetaIdAndUri("#OmexMetaId0000", physicalEntity.getModelUri())),
            LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/isVersionOf"),
            LibrdfNode::fromUriString("https://identifiers.org/opb/opb_1234"));

    editor.removeSingleAnnotation(triple1);
    editor.removeSingleAnnotation(triple2);
    ASSERT_EQ(2, rdf.size());

    triple1.freeTriple();
    triple2.freeTriple();
    triple3.freeTriple();
    triple4.freeTriple();
}


TEST_F(EditorTestsDeletePhysicalEntity, TestAddAndRemovePhysicalEntity) {
    PhysicalEntity physicalEntity = editor.newPhysicalEntity();
    physicalEntity
            .setPhysicalProperty("http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0000", "opb:opb_1234")
            .setIdentity("uniprot:PD12345")
            .addLocation("fma:fma:1234");
    editor.addPhysicalEntity(physicalEntity);
    ASSERT_EQ(4, rdf.size());
    editor.removePhysicalEntity(physicalEntity);
    ASSERT_EQ(0, rdf.size());
}


TEST_F(EditorTestsDeletePhysicalEntity, TestDeleteFirstTriple) {
    PhysicalEntity physicalEntity = editor.newPhysicalEntity();
    physicalEntity
            .setPhysicalProperty("http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0000", "opb:opb_1234")
            .setIdentity("uniprot:PD12345")
            .addLocation("fma:fma:1234");
    editor.addPhysicalEntity(physicalEntity);

    /* Take and delete triple number 1
     * 1) <#OmexMetaId0000> <http://biomodels.net/biology-qualifiers/isVersionOf> <https://identifiers.org/opb/opb_1234> .
     * 2) <#OmexMetaId0000> <http://biomodels.net/biology-qualifiers/isPropertyOf> <EntityProperty0001> .
     * 3) <EntityProperty0001> <http://biomodels.net/biology-qualifiers/is> <https://identifiers.org/uniprot/PD12345> .
     * 4) <EntityProperty0001> <http://biomodels.net/biology-qualifiers/isPartOf> <https://identifiers.org/fma/fma:1234> .
     */

    Triples triples = physicalEntity.toTriples();
    std::cout << triples.str("ntriples", "base") << std::endl;
    Triple triple = triples.pop_front();

    editor.removeSingleAnnotation(triple);
    ASSERT_EQ(3, rdf.size());

    triple.freeTriple();
}
