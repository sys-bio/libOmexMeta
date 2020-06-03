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
        model = LibrdfModel(storage);
    };

};


TEST_F(EditorTests, TestMetaIds) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBMLString(SBML_NOT_ANNOTATED),
            SEMSIM_TYPE_SBML);
    const auto &metaids = editor.getMetaids();
    std::vector<std::string> expected = {
            "SemsimMetaid0000", "SemsimMetaid0001", "SemsimMetaid0002",
            "SemsimMetaid0003", "SemsimMetaid0004", "SemsimMetaid0005",
            "SemsimMetaid0006", "SemsimMetaid0007", "cytosol", "SemsimMetaid0008",
            "Meta00001", "SemsimMetaid0009", "SemsimMetaid0010", "SemsimMetaid0011",
            "SemsimMetaid0012", "SemsimMetaid0013", "SemsimMetaid0014",
            "SemsimMetaid0015", "SemsimMetaid0016", "SemsimMetaid0017",
            "SemsimMetaid0018", "SemsimMetaid0019", "SemsimMetaid0020",
            "SemsimMetaid0021", "SemsimMetaid0022", "SemsimMetaid0023",
            "SemsimMetaid0024", "SemsimMetaid0025", "SemsimMetaid0026",
            "SemsimMetaid0027", "SemsimMetaid0028", "SemsimMetaid0029",
            "SemsimMetaid0030", "SemsimMetaid0031", "SemsimMetaid0032"
    };
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
            Subject::fromRawPtr(LibrdfNode::fromUriString("SemsimMetaid0004")),
            predicatePtr,
            Resource::fromRawPtr(LibrdfNode::fromUriString("uniprot:P0DP23"))
    );
    NestedTriples tripleList = editor.getTripleList();
    ASSERT_EQ(1, tripleList.size());
    ASSERT_EQ(1, tripleList[0].size());
}

TEST_F(EditorTests, TestToRDFSingleAnnotation1) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBMLString(SBML_NOT_ANNOTATED),
            SEMSIM_TYPE_SBML);
    Subject subject = Subject::fromRawPtr(LibrdfNode::fromUriString("SemsimMetaid0014"));
    BiomodelsBiologyQualifier predicate("is");
    Resource resource = Resource::fromRawPtr(LibrdfNode::fromUriString("uniprot:P0DP23"));
    Triple triple(
            subject.getNode(), predicate.getNode(), resource.getNode()
    );
    editor.addSingleAnnotation(triple);
    editor.toRDF();

    std::string actual = rdf.toString("rdfxml", "MyModel.rdf");
    std::cout << actual <<
              std::endl;
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xml:base=\"file://MyModel.rdf\">\n"
                           "  <rdf:Description rdf:about=\"SemsimMetaid0014\">\n"
                           "    <bqbiol:is rdf:resource=\"https://identifiers.org/uniprot/P0DP23\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(EditorTests, TestToRDFSingleAnnotation2) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBMLString(SBML_NOT_ANNOTATED),
            SEMSIM_TYPE_SBML);
    editor.addSingleAnnotation(
            Subject::fromRawPtr(LibrdfNode::fromUriString("SemsimMetaid0008")),
            std::make_shared<Predicate>(BiomodelsBiologyQualifier("isDescribedBy")),
            Resource::fromRawPtr(LibrdfNode::fromUriString("pubmed:12991237"))
    );
    editor.toRDF();
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

TEST_F(EditorTests, TestToRDFSingleAnnotation3) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBMLString(SBML_NOT_ANNOTATED),
            SEMSIM_TYPE_SBML);
    editor.
            addSingleAnnotation(
            Subject::fromRawPtr(LibrdfNode::fromUriString("SemsimMetaid0008")),
            std::make_unique<Predicate>(BiomodelsBiologyQualifier("isDescribedBy")),
            Resource::fromRawPtr(LibrdfNode::fromUriString("pubmed:12991237"))
    );
    editor.toRDF();
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
            Subject::fromRawPtr(LibrdfNode::fromUriString("SemsimMetaid0008")),
            std::make_unique<Predicate>(DCTerm("Description")),
            Resource::fromRawPtr(LibrdfNode::fromLiteral("Cardiomyocyte cytosolic ATP concentration"))
    );
    editor.toRDF();
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
    singularAnnotation.setAbout("Metaid4")
            .setPredicate("bqb", "isVersionOf")
            .setResourceUri("uniprot:PD02635");

    editor.addSingleAnnotation(singularAnnotation);
    editor.toRDF();
    std::string actual = rdf.toString("rdfxml", "MyModel.rdf");
    std::cout << actual << std::endl;
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xml:base=\"file://MyModel.rdf\">\n"
                           "  <rdf:Description rdf:about=\"Metaid4\">\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/uniprot/PD02635\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(EditorTests, TestCompositeAnnotationPhysicalEntity) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBMLString(SBML_NOT_ANNOTATED),
            SEMSIM_TYPE_SBML
    );

    editor.addCompositeAnnotation(
            std::make_shared<PhysicalEntity>(PhysicalEntity(
                    rdf.getModel(),
                    Subject::fromRawPtr(LibrdfNode::fromUriString("VLV")),
                    PhysicalPropertyResource("OPB:OPB_00154"),
                    Resource::fromRawPtr(LibrdfNode::fromUriString("fma:FMA:9670")), // is smad3
                    std::vector<Resource>({Resource::fromRawPtr(LibrdfNode::fromUriString("fma/FMA:9697"))})
                                             )
            )
    );

    editor.toRDF();
    std::string actual = rdf.toString("rdfxml-abbrev", "file://./annotations.rdf");
    std::cout << actual << std::endl;
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"PhysicalEntity0000\">\n"
                           "    <bqbiol:is rdf:resource=\"https://identifiers.org/fma/FMA:9670\"/>\n"
                           "    <bqbiol:isPartOf rdf:resource=\"https://identifiers.org/fma/FMA:9697\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"VLV\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"PhysicalEntity0000\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/OPB/OPB_00154\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(EditorTests, TestAddAnnotationCompositeTypePhysicalProcess) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBMLString(SBML_NOT_ANNOTATED),
            SEMSIM_TYPE_SBML);

    editor.
            addCompositeAnnotation(
            std::make_shared<PhysicalProcess>(
                    PhysicalProcess(
                            model.get(),
                            Subject::fromRawPtr(LibrdfNode::fromUriString("MetaId004")),
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

    editor.toRDF();
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
    std::cout << actual <<
              std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(EditorTests, TestAddAnnotationCompositeTypePhysicalForce) {
    RDF rdf;
    Editor editor = rdf.toEditor(
            SBMLFactory::getSBMLString(SBML_NOT_ANNOTATED),
            SEMSIM_TYPE_SBML);

    editor.
            addCompositeAnnotation(
            std::make_shared<PhysicalForce>(
                    PhysicalForce(

                            model.get(),
                            Subject::fromRawPtr(LibrdfNode::fromUriString("MetaId004")),
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

    editor.toRDF();
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
    std::cout << actual <<
              std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

























