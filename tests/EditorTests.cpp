//
// Created by Ciaran on 4/15/2020.
//
#include "gtest/gtest.h"
#include "SBMLFactory.h"
#include "semsim/Editor.h"
#include "semsim/XmlAssistant.h"
#include "semsim/PhysicalEntity.h"
#include "semsim/PhysicalProcess.h"
#include "semsim/PhysicalForce.h"

class EditorTests : public ::testing::Test {

public:

    librdf_world *world;
    raptor_world *raptorWorld;
    librdf_storage *storage;
    librdf_model *model;

    EditorTests() {
        auto initializer = semsim::RDF::init();
        world = std::get<0>(initializer);
        raptorWorld = std::get<1>(initializer);
        storage = std::get<2>(initializer);
        model = std::get<3>(initializer);
    };
};


TEST_F(EditorTests, TestMetaIds) {
    semsim::RDF rdf;
    semsim::Editor editor = rdf.toEditor(
            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
            semsim::ASSISTANT_TYPE_SBML);
    const auto &metaids = editor.getMetaids();
    std::vector<std::string> expected = {"SemsimMetaid0000", "SemsimMetaid0001", "SemsimMetaid0002", "cytosol",
                                         "Meta00001", "SemsimMetaid0003", "SemsimMetaid0004", "SemsimMetaid0005",
                                         "SemsimMetaid0006", "SemsimMetaid0007", "SemsimMetaid0008", "SemsimMetaid0009",
                                         "SemsimMetaid0010"};
    ASSERT_EQ(expected, metaids);
}

TEST_F(EditorTests, TestAddAnnotation) {
    semsim::RDF rdf;
    semsim::Editor editor = rdf.toEditor(
            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
            semsim::ASSISTANT_TYPE_SBML);
    semsim::PredicatePtr predicatePtr = std::make_shared<semsim::Predicate>(
            semsim::BiomodelsBiologyQualifier(world, "is"));
    editor.addSingleAnnotation(
            semsim::Subject(world, semsim::RDFURINode(world, "SemsimMetaid0004")),
            predicatePtr,
            semsim::Resource(world, semsim::RDFURINode(world, "uniprot:P0DP23"))
    );
    semsim::NestedTriples tripleList = editor.getTripleList();
    ASSERT_EQ(1, tripleList.size());
    ASSERT_EQ(1, tripleList[0].size());
}

TEST_F(EditorTests, TestToRDFSingleAnnotation1) {
    semsim::RDF rdf;
    semsim::Editor editor = rdf.toEditor(
            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
            semsim::ASSISTANT_TYPE_SBML);
    semsim::Triple triple(
            world,
            semsim::Subject(world, semsim::RDFURINode(world, "SemsimMetaid0014")),
            std::make_shared<semsim::Predicate>(semsim::BiomodelsBiologyQualifier(world, "is")),
            semsim::Resource(world, semsim::RDFURINode(world, "uniprot:P0DP23"))
    );
    editor.addSingleAnnotation(triple);
    editor.toRDF();

    std::string actual = rdf.toString("rdfxml", "MyModel.rdf");
    std::cout << actual << std::endl;
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
    semsim::RDF rdf;
    semsim::Editor editor = rdf.toEditor(
            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
            semsim::ASSISTANT_TYPE_SBML);
    editor.addSingleAnnotation(
            semsim::Subject(world, semsim::RDFURINode(world, "SemsimMetaid0008")),
            std::make_shared<semsim::Predicate>(semsim::BiomodelsBiologyQualifier(world, "isDescribedBy")),
            semsim::Resource(world, semsim::RDFURINode(world, "pubmed:12991237"))
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
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(EditorTests, TestToRDFSingleAnnotation3) {
    semsim::RDF rdf;
    semsim::Editor editor = rdf.toEditor(
            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
            semsim::ASSISTANT_TYPE_SBML);
    editor.addSingleAnnotation(
            semsim::Subject(world, semsim::RDFURINode(world, "SemsimMetaid0008")),
            std::make_unique<semsim::Predicate>(semsim::BiomodelsBiologyQualifier(world, "isDescribedBy")),
            semsim::Resource(world, semsim::RDFURINode(world, "pubmed:12991237"))
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
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(EditorTests, TestToRDFSingularAnnotationWithLiteral) {
    semsim::RDF rdf;
    semsim::Editor editor = rdf.toEditor(
            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
            semsim::ASSISTANT_TYPE_SBML);
    editor.addSingleAnnotation(
            semsim::Subject(world, semsim::RDFURINode(world, "SemsimMetaid0008")),
            std::make_unique<semsim::Predicate>(semsim::DCTerm(world, "Description")),
            semsim::Resource(world, semsim::RDFLiteralNode(world, "Cardiomyocyte cytosolic ATP concentration"))
    );
    editor.toRDF();

    std::string actual = rdf.toString("rdfxml", "file://./annotations.rdf");
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:dcterms=\"http://purl.org/dc/terms/\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"SemsimMetaid0008\">\n"
                           "    <dcterms:Description rdf:datatype=\"http://www.w3.org/2001/XMLSchema#string\">Cardiomyocyte cytosolic ATP concentration</dcterms:Description>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(EditorTests, TestCompositeAnnotationPhysicalEntity) {
    semsim::RDF rdf;
    semsim::Editor editor = rdf.toEditor(
            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
            semsim::ASSISTANT_TYPE_SBML
    );

    editor.addCompositeAnnotation(
            std::make_shared<semsim::PhysicalEntity>(
                    semsim::PhysicalEntity(
                            world,
                            model,
                            semsim::Subject(world, semsim::RDFURINode(world, "VLV")),
                            semsim::PhysicalPropertyResource(
                                    // chemical concentration
                                    world, semsim::RDFURINode(world, "OPB:OPB_00154")
                            ),
                            semsim::Resource(world, semsim::RDFURINode(world, "fma:FMA:9670")), // is smad3
                            std::vector<semsim::Resource>(
                                    {
                                            semsim::Resource(world, semsim::RDFURINode(world, "fma/FMA:9697"))
                                    })
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
    semsim::RDF rdf;
    semsim::Editor editor = rdf.toEditor(
            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
            semsim::ASSISTANT_TYPE_SBML);

    editor.addCompositeAnnotation(
            std::make_shared<semsim::PhysicalProcess>(
                    semsim::PhysicalProcess(
                            world,
                            model,
                            semsim::Subject(world, semsim::RDFURINode(world, "MetaId004")),
                            semsim::PhysicalPropertyResource(world, "OPB:OPB1234"),
                            std::vector<semsim::SourceParticipant>(
                                    {semsim::SourceParticipant(
                                            world,
                                            model,
                                            "SourceId1",
                                            semsim::Resource(world, semsim::RDFURINode(world, "fake/identifier003")),
                                            1.0,
                                            "PhysicalEntityReference1"
                                    )}
                            ),
                            std::vector<semsim::SinkParticipant>(
                                    {semsim::SinkParticipant(
                                            world,
                                            model,
                                            "SinkId1",
                                            semsim::Resource(world, semsim::RDFURINode(world, "fake/identifier004")),
                                            1.0,
                                            "PhysicalEntityReference2"
                                    )}
                            ),
                            std::vector<semsim::MediatorParticipant>(
                                    {semsim::MediatorParticipant(
                                            world,
                                            model,
                                            "MediatorID1",
                                            semsim::Resource(world, semsim::RDFURINode(world, "fake/identifier005")),
                                            "PhysicalEntityReference3"
                                    )}
                            )
                    )
            )
    );

    editor.toRDF();
    std::string actual = rdf.toString("rdfxml-abbrev", "file://./annotations.rdf");
    std::cout << actual << std::endl;
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"MediatorID\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"PhysicalEntityReference3\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"MetaId004\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"PhysicalProcess0000\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/OPB/OPB1234\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"PhysicalProcess0000\">\n"
                           "    <semsim:hasMediatorParticipant rdf:resource=\"MediatorID\"/>\n"
                           "    <semsim:hasSinkParticipant rdf:resource=\"SinkID\"/>\n"
                           "    <semsim:hasSourceParticipant rdf:resource=\"SourceID\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"SinkID\">\n"
                           "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/2001/XMLSchema#string\">1</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"PhysicalEntityReference2\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"SourceID\">\n"
                           "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/2001/XMLSchema#string\">1</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"PhysicalEntityReference1\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(EditorTests, TestAddAnnotationCompositeTypePhysicalForce) {
    semsim::RDF rdf;
    semsim::Editor editor = rdf.toEditor(
            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
            semsim::ASSISTANT_TYPE_SBML);

    editor.addCompositeAnnotation(
            std::make_shared<semsim::PhysicalForce>(
                    semsim::PhysicalForce(
                            world,
                            model,
                            semsim::Subject(world, semsim::RDFURINode(world, "MetaId004")),
                            semsim::PhysicalPropertyResource(world, "OPB:OPB1234"),
                            std::vector<semsim::SourceParticipant>(
                                    {semsim::SourceParticipant(
                                            world,
                                            model,
                                            "SourceId1",
                                            semsim::Resource(world, semsim::RDFURINode(world, "fake/identifier003")),
                                            1.0,
                                            "PhysicalEntityReference1"
                                    )}
                            ),
                            std::vector<semsim::SinkParticipant>(
                                    {semsim::SinkParticipant(
                                            world,
                                            model,
                                            "SinkId1",
                                            semsim::Resource(world, semsim::RDFURINode(world, "fake/identifier004")),
                                            1.0,
                                            "PhysicalEntityReference2"
                                    )}
                            )
                    )
            )
    );

    editor.toRDF();
    std::string actual = rdf.toString("rdfxml-abbrev", "file://./annotations.rdf");
    std::cout << actual << std::endl;
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
                           "    <semsim:hasSinkParticipant rdf:resource=\"SinkID\"/>\n"
                           "    <semsim:hasSourceParticipant rdf:resource=\"SourceID\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"SinkID\">\n"
                           "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/2001/XMLSchema#string\">1</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"PhysicalEntityReference2\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"SourceID\">\n"
                           "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/2001/XMLSchema#string\">1</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"PhysicalEntityReference1\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

























