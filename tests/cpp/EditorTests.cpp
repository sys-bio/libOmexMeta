//
// Created by Ciaran on 4/15/2020.
//
#include "gtest/gtest.h"
#include "SBMLFactory.h"
#include "semsim/Editor.h"
#include "semsim/SemsimXmlAssistant.h"
#include "semsim/PhysicalEntity.h"
#include "semsim/PhysicalProcess.h"
#include "semsim/PhysicalForce.h"
#include "semsim/RDF.h"

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
    Subject subject = Subject(LibrdfNode::fromUriString("SemsimMetaid0009"));
    BiomodelsBiologyQualifier predicate("is");
    Resource resource = Resource(LibrdfNode::fromUriString("uniprot:P0DP23"));
    Triple triple(subject.getNode(), predicate.getNode(), resource.getNode());
    editor.addSingleAnnotation(triple);
    int expected = 1;
    int actual = editor.size();
    ASSERT_EQ(expected, actual);
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
}


TEST_F(EditorTests, TestAddPhysicalEntityToEditor) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBMLString(SBML_NOT_ANNOTATED),
            SEMSIM_TYPE_SBML
    );

    Subject subject(LibrdfNode::fromUriString("VLV"));
    PhysicalPropertyResource ppr("OPB:OPB_00154");
    Resource r(LibrdfNode::fromUriString("fma:FMA:9670")); // is smad3
    std::vector<Resource> resources;
    resources.emplace_back(std::move(LibrdfNode::fromUriString("fma/FMA:9697")));
    PhysicalEntity physicalEntity = PhysicalEntity(
            rdf.getModel(), subject, ppr, r, resources
    );
    std::shared_ptr<PhysicalEntity> ptr = std::make_shared<PhysicalEntity>(physicalEntity);
    editor.addCompositeAnnotation(ptr);
    int expected = 4;
    int actual = editor.size();
    ASSERT_EQ(expected, actual);

}


TEST_F(EditorTests, TestAddAnnotationCompositeTypePhysicalProcess) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBMLString(SBML_NOT_ANNOTATED),
            SEMSIM_TYPE_SBML);

    editor.addCompositeAnnotation(
            std::make_shared<PhysicalProcess>(
                    PhysicalProcess(
                            model.get(),
                            Subject(LibrdfNode::fromUriString("MetaId004")),
                            PhysicalPropertyResource("OPB:OPB1234"),
                            std::vector<SourceParticipant>(
                                    {SourceParticipant(model.get(),
                                                       "SourceId1",
                                                       1.0,
                                                       "PhysicalEntityReference1"
                                    )}
                            ),
                            std::vector<SinkParticipant>(
                                    {SinkParticipant(model.get(),
                                                     "SinkId1",
                                                     1.0,
                                                     "PhysicalEntityReference2"
                                    )}
                            ),
                            std::vector<MediatorParticipant>(
                                    {MediatorParticipant(model.get(),
                                                         "MediatorID1",
                                                         "PhysicalEntityReference3"
                                    )}
                            )
                    )
            )
    );

    
    std::string actual = rdf.toString("rdfxml-abbrev", "file://./annotations.rdf");
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"MediatorID1\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"PhysicalEntityReference3\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"MetaId004\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"PhysicalProcess0000\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/OPB/OPB1234\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"PhysicalProcess0000\">\n"
                           "    <semsim:hasMediatorParticipant rdf:resource=\"MediatorID1\"/>\n"
                           "    <semsim:hasSinkParticipant rdf:resource=\"SinkId1\"/>\n"
                           "    <semsim:hasSourceParticipant rdf:resource=\"SourceId1\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"SinkId1\">\n"
                           "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double\">1</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"PhysicalEntityReference2\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"SourceId1\">\n"
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

    editor.addCompositeAnnotation(
            std::make_shared<PhysicalForce>(
                    PhysicalForce(
                            model.get(),
                            Subject(LibrdfNode::fromUriString("MetaId004")),
                            PhysicalPropertyResource("OPB:OPB1234"),
                            std::vector<SourceParticipant>(
                                    {SourceParticipant(model.get(),
                                                       "SourceId1",
                                                       1.0,
                                                       "PhysicalEntityReference1"
                                    )}
                            ),
                            std::vector<SinkParticipant>(
                                    {SinkParticipant(model.get(),
                                                     "SinkId1",
                                                     1.0,
                                                     "PhysicalEntityReference2"
                                    )}
                            )
                    )
            )
    );

    
    std::string actual = rdf.toString("rdfxml-abbrev", "file://./annotations.rdf");
    std::cout << actual <<
              std::endl;
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"MetaId004\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"PhysicalForce0000\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/OPB/OPB1234\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"PhysicalForce0000\">\n"
                           "    <semsim:hasSinkParticipant rdf:resource=\"SinkId1\"/>\n"
                           "    <semsim:hasSourceParticipant rdf:resource=\"SourceId1\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"SinkId1\">\n"
                           "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double\">1</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"PhysicalEntityReference2\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"SourceId1\">\n"
                           "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double\">1</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"PhysicalEntityReference1\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
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
}


TEST_F(EditorTests, TestPhysicalEntityBuilder) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBMLString(SBML_NOT_ANNOTATED),
            SEMSIM_TYPE_SBML);

    PhysicalEntity physicalEntity = editor.createPhysicalEntity();
    physicalEntity
            .setAbout("SemsimMetaid0000")
            .setPhysicalProperty("opb:opb_1234")
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
            .setAbout("SemsimMetaid0000")
            .setPhysicalProperty("opb:opb1234")
            .addSource("sourceMetaid", 1.0, "PhysicalEntity1")
            .addSink("sinkMetaid", 1.0, "PhysicalEntity2");

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
            .setAbout("SemsimMetaid0000")
            .setPhysicalProperty("opb:opb1234")
            .addSource("sourceMetaid", 1.0, "PhysicalEntity1")
            .addSink("sinkMetaid", 1.0, "PhysicalEntity2")
            .addMediator("mediatorMetaid", 1.0, "PhysicalEntity3");

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
}

TEST_F(EditorTests, TestRemovePhysicalEntity) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBMLString(SBML_NOT_ANNOTATED),
            SEMSIM_TYPE_SBML);

    PhysicalEntity physicalEntity = editor.createPhysicalEntity();
    physicalEntity
            .setAbout("SemsimMetaid0000")
            .setPhysicalProperty("opb:opb_1234")
            .setIdentity("uniprot:PD12345")
            .addLocation("fma:fma:1234");

    editor.addPhysicalEntity(physicalEntity);

    ASSERT_EQ(4, rdf.size());

    editor.removePhysicalEntity(physicalEntity);
//
//    int expected = 0;
//    int actual = rdf.size();
//    ASSERT_EQ(expected, actual);
}

//
//TEST_F(EditorTests, TestRemovePhysicalForce) {
//    RDF rdf;
//    Editor editor = rdf.toEditor(
//            SBMLFactory::getSBMLString(SBML_NOT_ANNOTATED),
//            SEMSIM_TYPE_SBML);
//
//    PhysicalForce physicalForce = editor.createPhysicalForce();
//    physicalForce
//            .setAbout("SemsimMetaid0000")
//            .setPhysicalProperty("opb:opb1234")
//            .addSource("sourceMetaid", 1.0, "PhysicalEntity1")
//            .addSink("sinkMetaid", 1.0, "PhysicalEntity2");
//
//    editor.addPhysicalForce(physicalForce);
//    
//
//    ASSERT_EQ(7, rdf.size());
//    editor.removePhysicalForce(physicalForce);
//    int expected = 0;
//    int actual = rdf.size();
//    ASSERT_EQ(expected, actual);
//}
//
//TEST_F(EditorTests, TestRemovePhysicalProcess) {
//    RDF rdf;
//    Editor editor = rdf.toEditor(
//            SBMLFactory::getSBMLString(SBML_NOT_ANNOTATED),
//            SEMSIM_TYPE_SBML);
//
//    PhysicalProcess physicalProcess = editor.createPhysicalProcess();
//    physicalProcess
//            .setAbout("SemsimMetaid0000")
//            .setPhysicalProperty("opb:opb1234")
//            .addSource("sourceMetaid", 1.0, "PhysicalEntity1")
//            .addSink("sinkMetaid", 1.0, "PhysicalEntity2")
//            .addSink("mediatorMetaid", 1.0, "PhysicalEntity3");
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





















