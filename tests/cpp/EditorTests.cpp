//
// Created by Ciaran on 4/15/2020.
//
#include "gtest/gtest.h"
#include "SBMLFactory.h"
#include "omexmeta/Editor.h"
#include "omexmeta/SemsimXmlAssistant.h"
#include "omexmeta/PhysicalEntity.h"
#include "omexmeta/PhysicalProcess.h"
#include "omexmeta/PhysicalForce.h"
#include "omexmeta/RDF.h"

using namespace semsim;

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
            SBMLFactory::getSBMLString(SBML_NOT_ANNOTATED),
            SEMSIM_TYPE_SBML);
    const auto &metaids = editor.getMetaids();
    std::vector<std::string> expected = {"SemsimMetaid0000", "SemsimMetaid0001", "SemsimMetaid0002",
                                         "cytosol", "Meta00001", "SemsimMetaid0003", "SemsimMetaid0004",
                                         "SemsimMetaid0005", "SemsimMetaid0006", "SemsimMetaid0007",
                                         "SemsimMetaid0008", "SemsimMetaid0009", "SemsimMetaid0010"};
    ASSERT_EQ(expected, metaids);
}

TEST_F(EditorTests, TestAddAnnotation) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBMLString(SBML_NOT_ANNOTATED),
            SEMSIM_TYPE_SBML);
    PredicatePtr predicatePtr = std::make_shared<Predicate>(
            BiomodelsBiologyQualifier("is"));
    editor.addSingleAnnotation(
            Subject(LibrdfNode::fromUriString("SemsimMetaid0004")),
            predicatePtr,
            Resource(LibrdfNode::fromUriString("uniprot:P0DP23"))
    );
    ASSERT_EQ(1, editor.size());
//    triples.freeTriples();
}

TEST_F(EditorTests, TestAddSingleAnnotationToEditor) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBMLString(SBML_NOT_ANNOTATED),
            SEMSIM_TYPE_SBML);
    Triple triple(LibrdfNode::fromUriString("SemsimMetaid0009").get(),
            BiomodelsBiologyQualifier("is").getNode(),
            Resource(LibrdfNode::fromUriString("uniprot:P0DP23")).getNode());
    editor.addSingleAnnotation(triple);
    int expected = 1;
    int actual = editor.size();
    ASSERT_EQ(expected, actual);
    triple.freeStatement();

}

TEST_F(EditorTests, TestAddSingleAnnotationToRDF1) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBMLString(SBML_NOT_ANNOTATED),
            SEMSIM_TYPE_SBML);
    Subject subject = Subject(LibrdfNode::fromUriString("SemsimMetaid0009"));
    BiomodelsBiologyQualifier predicate("is");
    Resource resource = Resource(LibrdfNode::fromUriString("uniprot:P0DP23"));
    Triple triple(subject.getNode(), predicate.getNode(), resource.getNode());
    editor.addSingleAnnotation(triple);


    std::string actual = rdf.toString("rdfxml", "MyModel.rdf");
    std::cout << actual <<
              std::endl;
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xml:base=\"file://MyModel.rdf\">\n"
                           "  <rdf:Description rdf:about=\"SemsimMetaid0009\">\n"
                           "    <bqbiol:is rdf:resource=\"https://identifiers.org/uniprot/P0DP23\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    triple.freeStatement();
}

TEST_F(EditorTests, TestAddSingleAnnotationToRDF2) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBMLString(SBML_NOT_ANNOTATED),
            SEMSIM_TYPE_SBML);
    editor.addSingleAnnotation(
            Subject(LibrdfNode::fromUriString("SemsimMetaid0008")),
            std::make_shared<Predicate>(BiomodelsBiologyQualifier("isDescribedBy")),
            Resource(LibrdfNode::fromUriString("pubmed:12991237"))
    );

    std::string actual = rdf.toString("turtle", "file://./annotations.rdf");
    std::string expected = "@base <file://./annotations.rdf> .\n"
                           "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "\n"
                           "<SemsimMetaid0008>\n"
                           "    bqbiol:isDescribedBy <https://identifiers.org/pubmed/12991237> .\n"
                           "\n";
    std::cout << actual <<
              std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(EditorTests, TestAddSingleAnnotationToRDF3) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBMLString(SBML_NOT_ANNOTATED),
            SEMSIM_TYPE_SBML);
    editor.
            addSingleAnnotation(
            Subject(LibrdfNode::fromUriString("SemsimMetaid0008")),
            std::make_unique<Predicate>(BiomodelsBiologyQualifier("isDescribedBy")),
            Resource(LibrdfNode::fromUriString("pubmed:12991237"))
    );

    std::string actual = rdf.toString("rdfxml", "file://./annotations.rdf");
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"SemsimMetaid0008\">\n"
                           "    <bqbiol:isDescribedBy rdf:resource=\"https://identifiers.org/pubmed/12991237\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    std::cout << actual <<
              std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(EditorTests, TestToRDFSingularAnnotationWithLiteral) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBMLString(SBML_NOT_ANNOTATED),
            SEMSIM_TYPE_SBML);
    editor.
            addSingleAnnotation(
            Subject(LibrdfNode::fromUriString("SemsimMetaid0008")),
            std::make_unique<Predicate>(DCTerm("Description")),
            Resource(LibrdfNode::fromLiteral("Cardiomyocyte cytosolic ATP concentration"))
    );

    std::string actual = rdf.toString("rdfxml", "file://./annotations.rdf");
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:dcterms=\"http://purl.org/dc/terms/\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"SemsimMetaid0008\">\n"
                           "    <dcterms:Description rdf:datatype=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#string\">Cardiomyocyte cytosolic ATP concentration</dcterms:Description>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n";
    std::cout << actual <<
              std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(EditorTests, TestSingularAnnotWithBuilderPattern) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBMLString(SBML_NOT_ANNOTATED),
            SEMSIM_TYPE_SBML);

    SingularAnnotation singularAnnotation;
    singularAnnotation.setAbout("SemsimMetaid0001")
            .setPredicate("bqb", "isVersionOf")
            .setResourceUri("uniprot:PD02635");

    editor.addSingleAnnotation(singularAnnotation);

    std::string actual = rdf.toString("rdfxml", "MyModel.rdf");
    std::cout << actual << std::endl;
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xml:base=\"file://MyModel.rdf\">\n"
                           "  <rdf:Description rdf:about=\"SemsimMetaid0001\">\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/uniprot/PD02635\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    singularAnnotation.freeStatement();

}


TEST_F(EditorTests, TestAddPhysicalEntityToEditor) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBMLString(SBML_NOT_ANNOTATED),
            SEMSIM_TYPE_SBML
    );

    PhysicalProperty ppr("metaid", "OPB:OPB_00154");
    Resource r(LibrdfNode::fromUriString("fma:FMA:9670")); // is smad3
    std::vector<Resource> resources;
    resources.emplace_back(std::move(LibrdfNode::fromUriString("fma/FMA:9697")));
    PhysicalEntity physicalEntity = PhysicalEntity(
            rdf.getModel(), ppr, r, resources
    );
//    std::shared_ptr<PhysicalEntity> ptr = std::make_shared<PhysicalEntity>(physicalEntity);
    editor.addCompositeAnnotation(&physicalEntity);
    int expected = 4;
    int actual = editor.size();
    ASSERT_EQ(expected, actual);

}


TEST_F(EditorTests, TestAddAnnotationCompositeTypePhysicalProcess) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBMLString(SBML_NOT_ANNOTATED),
            SEMSIM_TYPE_SBML);

    PhysicalProcess process = PhysicalProcess(
            model.get(),
            PhysicalProperty("MetaId004", "OPB:OPB1234"),
            std::vector<SourceParticipant>(
                    {SourceParticipant(model.get(),
                                       1.0,
                                       "PhysicalEntityReference1"
                    )}
            ),
            std::vector<SinkParticipant>(
                    {SinkParticipant(model.get(),
                                     1.0,
                                     "PhysicalEntityReference2"
                    )}
            ),
            std::vector<MediatorParticipant>(
                    {MediatorParticipant(model.get(),
                                         "PhysicalEntityReference3"
                    )}
            )
    );

    editor.addCompositeAnnotation(&process);

    std::string actual = rdf.toString("rdfxml-abbrev", "file://./annotations.rdf");
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"MediatorParticipant0000\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"PhysicalEntityReference3\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"MetaId004\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"PhysicalProcess0000\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/OPB/OPB1234\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"PhysicalProcess0000\">\n"
                           "    <semsim:hasMediatorParticipant rdf:resource=\"MediatorParticipant0000\"/>\n"
                           "    <semsim:hasSinkParticipant rdf:resource=\"SinkParticipant0000\"/>\n"
                           "    <semsim:hasSourceParticipant rdf:resource=\"SourceParticipant0000\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"SinkParticipant0000\">\n"
                           "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double\">1</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"PhysicalEntityReference2\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"SourceParticipant0000\">\n"
                           "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double\">1</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"PhysicalEntityReference1\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(EditorTests, TestAddAnnotationCompositeTypePhysicalForce) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBMLString(SBML_NOT_ANNOTATED),
            SEMSIM_TYPE_SBML);

    PhysicalForce force = PhysicalForce(
                    model.get(),
                    PhysicalProperty("metaid", "OPB:OPB1234"),
                    std::vector<SourceParticipant>(
                            {SourceParticipant(model.get(),
                                                       1.0,
                                               "PhysicalEntityReference1"
                            )}
                    ),
                    std::vector<SinkParticipant>(
                            {SinkParticipant(model.get(),
                                                     1.0,
                                             "PhysicalEntityReference2"
                            )}
                    )
    );

    editor.addCompositeAnnotation(&force);


    std::string actual = rdf.toString("rdfxml-abbrev", "file://./annotations.rdf");
    std::cout << actual <<
              std::endl;
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"PhysicalForce0000\">\n"
                           "    <semsim:hasSinkParticipant rdf:resource=\"SinkParticipant0000\"/>\n"
                           "    <semsim:hasSourceParticipant rdf:resource=\"SourceParticipant0000\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"SinkParticipant0000\">\n"
                           "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double\">1</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"PhysicalEntityReference2\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"SourceParticipant0000\">\n"
                           "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double\">1</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"PhysicalEntityReference1\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"metaid\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"PhysicalForce0000\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/OPB/OPB1234\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n";
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(EditorTests, TestSingularAnnotationBuilder) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBMLString(SBML_NOT_ANNOTATED),
            SEMSIM_TYPE_SBML);


    SingularAnnotation singularAnnotation;
    singularAnnotation
            .setAbout("SemsimMetaid0000")
            .setPredicate("bqb", "is")
            .setResourceLiteral("resource");

    editor.addSingleAnnotation(singularAnnotation);

    int expected = 1;
    int actual = rdf.size();
    ASSERT_EQ(expected, actual);
    singularAnnotation.freeStatement();
}


TEST_F(EditorTests, TestPhysicalEntityBuilder) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBMLString(SBML_NOT_ANNOTATED),
            SEMSIM_TYPE_SBML);

    PhysicalEntity physicalEntity = editor.createPhysicalEntity();
    physicalEntity
            .setPhysicalProperty("SemsimMetaid0000", "opb:opb_1234")
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
            SBMLFactory::getSBMLString(SBML_NOT_ANNOTATED),
            SEMSIM_TYPE_SBML);

    PhysicalForce physicalForce = editor.createPhysicalForce();
    physicalForce
            .setPhysicalProperty("SemsimMetaid0000", "OPB:OPB1234")
            .addSource( 1.0, "PhysicalEntity1")
            .addSink( 1.0, "PhysicalEntity2");

    editor.addPhysicalForce(physicalForce);


    int expected = 8;
    int actual = rdf.size();
    ASSERT_EQ(expected, actual);
}

TEST_F(EditorTests, TestPhysicalProcessBuilder) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBMLString(SBML_NOT_ANNOTATED),
            SEMSIM_TYPE_SBML);

    PhysicalProcess physicalProcess = editor.createPhysicalProcess();
    physicalProcess
            .setPhysicalProperty("SemsimMetaid0000", "OPB:OPB1234")
            .addSource( 1.0, "PhysicalEntity1")
            .addSink( 1.0, "PhysicalEntity2")
            .addMediator( 1.0, "PhysicalEntity3");

    editor.addPhysicalProcess(physicalProcess);

    int expected = 10;
    int actual = rdf.size();
    ASSERT_EQ(expected, actual);
}


TEST_F(EditorTests, TestRemoveSingularAnnotation) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBMLString(SBML_NOT_ANNOTATED),
            SEMSIM_TYPE_SBML);

    SingularAnnotation singularAnnotation;
    singularAnnotation
            .setAbout("SemsimMetaid0000")
            .setPredicate("bqb", "is")
            .setResourceLiteral("resource");

    editor.addSingleAnnotation(singularAnnotation);

    ASSERT_EQ(1, rdf.size());

    editor.removeSingleAnnotation(singularAnnotation);
    int expected = 0;
    int actual = rdf.size();
    ASSERT_EQ(expected, actual);
    singularAnnotation.freeStatement();
}


/*
 * Question: Is the autogenerated ID field causng this problem?
 * When we automatically generate an ID, we take the next numerical
 * id. When we generate a statement, we create a new id. If we then
 * try to generate another statement from the same compositite annotation
 * We autoamtically generate a new ID for it, even though we need the old one.
 * BUUUUG.
 *
 */
TEST_F(EditorTests, TestRemovePhysicalForce) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBMLString(SBML_NOT_ANNOTATED),
            SEMSIM_TYPE_SBML);

    PhysicalForce physicalForce = editor.createPhysicalForce();
    physicalForce
            .setPhysicalProperty("SemsimMetaid0002", "OPB:OPB1234")
            .addSource( 1.0, "PhysicalEntity1")
            .addSink( 1.0, "PhysicalEntity2");

    editor.addPhysicalForce(physicalForce);

    std::cout << rdf.toString("rdfxml-abbrev", "base") << std::endl;

//    ASSERT_EQ(8, rdf.size());
//    editor.removePhysicalForce(physicalForce);
//    std::cout << rdf.toString("rdfxml-abbrev", "base") << std::endl;
//    int expected = 0;
//    int actual = rdf.size();
//    ASSERT_EQ(expected, actual);
}

//TEST_F(EditorTests, TestRemovePhysicalProcess) {
//    RDF rdf;
//    Editor editor = rdf.toEditor(
//            SBMLFactory::getSBMLString(SBML_NOT_ANNOTATED),
//            SEMSIM_TYPE_SBML);
//
//    PhysicalProcess physicalProcess = editor.createPhysicalProcess();
//    physicalProcess
//            .setAbout("SemsimMetaid0000")
//            .setPhysicalProperty("metaid", "OPB:OPB1234")
//            .addSource( 1.0, "PhysicalEntity1")
//            .addSink( 1.0, "PhysicalEntity2")
//            .addSink( 1.0, "PhysicalEntity3");
//
//    editor.addPhysicalProcess(physicalProcess);
//    
//
//    ASSERT_EQ(10, rdf.size());
//    editor.removePhysicalProcess(physicalProcess);
//    int expected = 0;
//    int actual = rdf.size();
//    ASSERT_EQ(expected, actual);
//}
//




/*****************************************************************
 * Test PhysicalEntity memory accountability
 */
class EditorTestsPhysicalEntityMemory : public ::testing::Test {
public:

    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBMLString(SBML_NOT_ANNOTATED),
            SEMSIM_TYPE_SBML);
    PhysicalEntity physicalEntity = editor.createPhysicalEntity();

    EditorTestsPhysicalEntityMemory() {
        physicalEntity
                .setAbout("SemsimMetaid0000")
                .setPhysicalProperty("SemsimMetaid0000", "opb:opb_1234")
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

class EditorTestsDeletePhysicalEntity : public ::testing::Test {
public:
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBMLString(SBML_NOT_ANNOTATED),
            SEMSIM_TYPE_SBML);

    PhysicalEntity physicalEntity = editor.createPhysicalEntity();

    EditorTestsDeletePhysicalEntity() {
        physicalEntity
                .setAbout("SemsimMetaid0000")
                .setPhysicalProperty("SemsimMetaid0000", "opb:opb_1234")
                .setIdentity("uniprot:PD12345")
                .addLocation("fma:fma:1234");
        editor.addPhysicalEntity(physicalEntity);
    }

};

TEST_F(EditorTestsDeletePhysicalEntity, TestRDFSizeBeforeRemovingAndNoMemoryLeaks) {
    ASSERT_EQ(4, rdf.size());
    Triples triples = physicalEntity.toTriples();
    ASSERT_EQ(4, triples.size());
}

TEST_F(EditorTestsDeletePhysicalEntity, TestDeleteFirstTriple) {
    Triples triples = physicalEntity.toTriples();
//    Triple triple = triples.pop_front();
//    std::cout << triple.str("ntriples", "base") << std::endl;
//    triple.freeTriple();
//    triples.freeTriples();
//
//    triples.freeTriples();
////
//    ASSERT_EQ(3, triples.size());
//
//    editor.removeSingleAnnotation(triple);
//    ASSERT_EQ(3, rdf.size());
//    triples.freeTriples();
//    triple.freeTriple();
//physicalEntity.free();


}

















