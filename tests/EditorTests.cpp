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
    // todo this is a weak test: I should really go and get all the metaids using libxml for comparison
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
    editor.addSingleAnnotation(
            semsim::Subject(world, semsim::RDFURINode(world, "SemsimMetaid0014")),
            std::make_shared<semsim::Predicate>(semsim::BiomodelsQualifier(world, "is")),
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
            std::make_shared<semsim::Predicate>(semsim::BiomodelsQualifier(world, "is")),
            semsim::Resource(world, semsim::RDFURINode(world, "uniprot:P0DP23"))
    );
    editor.addSingleAnnotation(triple);
    editor.toRDF();

    std::string actual = rdf.toString("rdfxml", "./MyModel.xml");
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\" xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\" xmlns:dcterms=\"http://purl.org/dc/terms/\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\" xml:base=\"./MyModel.xml\">\n"
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
            std::make_shared<semsim::Predicate>(semsim::BiomodelsQualifier(world, "isDescribedBy")),
            semsim::Resource(world, semsim::RDFURINode(world, "pubmed:12991237"))
    );
    editor.toRDF();

    std::string actual = rdf.toString("turtle", "./MyModel.xml");
    std::string expected = "@base <./MyModel.xml> .\n"
                           "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqmodel: <http://biomodels.net/model-qualifiers/> .\n"
                           "@prefix dcterms: <http://purl.org/dc/terms/> .\n"
                           "@prefix semsim: <http://www.bhi.washington.edu/semsim#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "\n"
                           "<SemsimMetaid0008>\n"
                           "    bqbiol:isDescribedBy <pubmed:12991237> .\n\n"
                           "";
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
            std::make_unique<semsim::Predicate>(semsim::BiomodelsQualifier(world, "isDescribedBy")),
            semsim::Resource(world, semsim::RDFURINode(world, "pubmed:12991237"))
    );
    editor.toRDF();

    std::string actual = rdf.toString("rdfxml", "./MyModel.xml");
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\" xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\" xmlns:dcterms=\"http://purl.org/dc/terms/\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\" xml:base=\"./MyModel.xml\">\n"
                           "  <rdf:Description rdf:about=\"SemsimMetaid0008\">\n"
                           "    <bqbiol:isDescribedBy rdf:resource=\"pubmed:12991237\"/>\n"
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

    std::string actual = rdf.toString("rdfxml", "./MyModel.xml");
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\" xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\" xmlns:dcterms=\"http://purl.org/dc/terms/\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\" xml:base=\"./MyModel.xml\">\n"
                           "  <rdf:Description rdf:about=\"SemsimMetaid0008\">\n"
                           "    <dcterms:Description rdf:datatype=\"http://www.w3.org/2001/XMLSchema#string\">Cardiomyocyte cytosolic ATP concentration</dcterms:Description>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n";
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(EditorTests, TestConnectorTripleSize) {
    semsim::RDF rdf;
    semsim::Editor editor = rdf.toEditor(
            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
            semsim::ASSISTANT_TYPE_SBML
    );
    std::vector<semsim::Triple> triples = editor.connectionTriple("SemsimMetaid0018", "opb:OPB_00154",
                                                                  "SemsimMetaid0014");
    ASSERT_EQ(2, triples.size());
}

TEST_F(EditorTests, TestConnectorTripleSubjectString) {
    semsim::RDF rdf;
    semsim::Editor editor = rdf.toEditor(
            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
            semsim::ASSISTANT_TYPE_SBML
    );
    std::vector<semsim::Triple> triples = editor.connectionTriple("SemsimMetaid0018", "opb:OPB_00154",
                                                                  "SemsimMetaid0014");
    std::string actual = triples[0].getSubject().str();
    std::string expected = "SemsimMetaid0018";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(EditorTests, TestConnectorTripleResourceStr) {
    semsim::RDF rdf;
    semsim::Editor editor = rdf.toEditor(
            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
            semsim::ASSISTANT_TYPE_SBML
    );
    std::vector<semsim::Triple> triples = editor.connectionTriple("SemsimMetaid0018", "opb:OPB_00154",
                                                                  "SemsimMetaid0014");
    std::string actual = triples[0].getResource().str();
    std::string expected = "https://identifiers.org/opb/OPB_00154";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(EditorTests, TestConnectorTripleVecSize) {
    semsim::RDF rdf;
    semsim::Editor editor = rdf.toEditor(
            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
            semsim::ASSISTANT_TYPE_SBML
    );
    std::vector<std::string> vec = {"SemsimMetaid0014", "SemsimMetaid0015", "SemsimMetaid0016"};
    std::vector<semsim::Triple> triples = editor.connectionTriple("SemsimMetaid0018", "opb:OPB_00154", vec);
    ASSERT_EQ(5, triples.size());
    std::string actual = triples[0].getResource().str();
    std::string expected = "https://identifiers.org/opb/OPB_00154";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(EditorTests, Tripnips) {
    semsim::RDF rdf;
    semsim::Editor editor = rdf.toEditor(
            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
            semsim::ASSISTANT_TYPE_SBML
    );

    editor.addCompositeAnnotation(
            std::make_shared<semsim::PhysicalEntity>(
                    semsim::PhysicalEntity(
                            world,
                            semsim::Subject(world, semsim::RDFURINode(world, "Metaid0034")),
                            semsim::PhysicalPropertyResource(
                                    // chemical concentration
                                    world, semsim::RDFURINode(world, "OPB:OPB_00340")
                            ),
                            semsim::Resource(world, semsim::RDFURINode(world, "obo/PR_000000365")), // is smad3
                            std::vector<semsim::Resource>(
                                    {semsim::Resource(world,
                                                      semsim::RDFURINode(world,
                                                                         "https://identifiers.org/fma/FMA:72564")),
                                     semsim::Resource(world, semsim::RDFURINode(world, "fma:FMA:63877"))
                                    })
                    )
            )
    );
    editor.toRDF();
    std::string actual = rdf.toString("rdfxml");
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\" xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\" xmlns:dcterms=\"http://purl.org/dc/terms/\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\" xml:base=\"./SemsimModel\">\n"
                           "  <rdf:Description rdf:about=\"Metaid0034\">\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/OPB/OPB_00340\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"Metaid0034\">\n"
                           "    <bqbiol:is rdf:resource=\"https://identifiers.org/obo/PR_000000365\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"entityMetaidPlaceholder\">\n"
                           "    <bqbiol:isPartOf rdf:resource=\"https://identifiers.org/fma/FMA:72564\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"entityMetaidPlaceholder\">\n"
                           "    <bqbiol:isPartOf rdf:resource=\"https://identifiers.org/fma/FMA:63877\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

//TEST_F(EditorTests, TestConnectorTripleVec) {
//    semsim::RDF rdf;
//    semsim::Editor editor = rdf.toEditor(
//            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
//            semsim::ASSISTANT_TYPE_SBML
//            );
//    std::vector<std::string> vec = {"SemsimMetaid0014", "SemsimMetaid0015", "SemsimMetaid0016"};
//    std::vector<semsim::Triple> triples = editor.connectionTriple("SemsimMetaid0018", "opb:OPB_00154", vec);
//    std::string actual = triples[4].getResource().str();
//    std::string expected = "https://identifiers.org/opb/OPB_00154";
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}

TEST_F(EditorTests, TestConnectorTripleVecStr) {
    semsim::RDF rdf;
    semsim::Editor editor = rdf.toEditor(
            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
            semsim::ASSISTANT_TYPE_SBML
    );
    std::vector<std::string> vec = {"SemsimMetaid0014", "SemsimMetaid0015", "SemsimMetaid0016"};
    std::vector<semsim::Triple> triples = editor.connectionTriple("SemsimMetaid0018", "opb:OPB_00154", vec);
    editor.addAnnotation(triples);
    editor.toRDF();
    std::string actual = rdf.toString("rdfxml", "./Base.xml");
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\" xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\" xmlns:dcterms=\"http://purl.org/dc/terms/\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\" xml:base=\"./Base.xml\">\n"
                           "  <rdf:Description rdf:about=\"SemsimMetaid0018\">\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/opb/OPB_00154\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"SemsimMetaid0018\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"SemsimMetaid0014\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"SemsimMetaid0018\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"SemsimMetaid0015\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"SemsimMetaid0018\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"SemsimMetaid0016\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(EditorTests, TestAddAnnotationCompositeTypePhysicalEntity) {
    semsim::RDF rdf;
    semsim::Editor editor = rdf.toEditor(
            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
            semsim::ASSISTANT_TYPE_SBML);
    editor.addPhysicalEntityAnnotation(
            "SemsimMetaid0018", "opb/OPB_00154", "SemsimMetaid0014",
            semsim::Resource(world, semsim::RDFURINode(world, "fma/FMA:9670")),
            semsim::Resource(world, semsim::RDFURINode(world, "fma/FMA:18228"))
    );
    editor.toRDF();

    std::string actual = rdf.toString("rdfxml", "./MyModel.xml");
    std::string expected = "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\" xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\" xmlns:dcterms=\"http://purl.org/dc/terms/\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\" xml:base=\"./MyModel.xml\">\n"
                           "  <rdf:Description rdf:about=\"SemsimMetaid0018\">\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/opb/OPB_00154\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"SemsimMetaid0018\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"SemsimMetaid0014\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"SemsimMetaid0014\">\n"
                           "    <bqbiol:is rdf:resource=\"https://identifiers.org/fma/FMA:9670\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"SemsimMetaid0014\">\n"
                           "    <bqbiol:isPartOf rdf:resource=\"https://identifiers.org/fma/FMA:18228\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    std::cout << actual << std::endl;
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
                            semsim::Subject(world, semsim::RDFURINode(world, "MetaId004")),
                            semsim::PhysicalPropertyResource(world, "OPB:OPB1234"),
                            std::vector<semsim::SourceParticipant>(
                                    {semsim::SourceParticipant(
                                            world,
                                            "SourceId1",
                                            semsim::Resource(world, semsim::RDFURINode(world, "fake/identifier003")),
                                            1.0,
                                            "PhysicalEntityReference1"
                                    )}
                            ),
                            std::vector<semsim::SinkParticipant>(
                                    {semsim::SinkParticipant(
                                            world,
                                            "SinkId1",
                                            semsim::Resource(world, semsim::RDFURINode(world, "fake/identifier004")),
                                            1.0,
                                            "PhysicalEntityReference2"
                                    )}
                            ),
                            std::vector<semsim::MediatorParticipant>(
                                    {semsim::MediatorParticipant(
                                            world,
                                            "MediatorID1",
                                            semsim::Resource(world, semsim::RDFURINode(world, "fake/identifier005")),
                                            "PhysicalEntityReference3"
                                    )}
                            )
                    )
            )
    );

    editor.toRDF();
    std::string actual = rdf.toString("rdfxml", "./MyModel.xml");
    std::cout << actual << std::endl;
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\" xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\" xmlns:dcterms=\"http://purl.org/dc/terms/\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:semsim=\"http://www.bhi.washington.edu/semsim/\" xml:base=\"./MyModel.xml\">\n"
                           "  <rdf:Description rdf:about=\"AMetaid004\">\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/OPB/OPB1234\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"SourceId1\">\n"
                           "    <semsim:hasSourceParticipant rdf:resource=\"https://identifiers.org/fake/identifier003\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"https://identifiers.org/fake/identifier003\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"PhysicalEntityReference1\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"https://identifiers.org/fake/identifier003\">\n"
                           "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/2001/XMLSchema#string\">1</semsim:hasMultiplier>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"SinkId1\">\n"
                           "    <semsim:hasSinkParticipant rdf:resource=\"https://identifiers.org/fake/identifier004\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"https://identifiers.org/fake/identifier004\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"PhysicalEntityReference2\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"https://identifiers.org/fake/identifier004\">\n"
                           "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/2001/XMLSchema#string\">1</semsim:hasMultiplier>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"MediatorID1\">\n"
                           "    <semsim:hasMediatorParticipant rdf:resource=\"https://identifiers.org/fake/identifier005\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"https://identifiers.org/fake/identifier005\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"PhysicalEntityReference3\"/>\n"
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
                            semsim::Subject(world, semsim::RDFURINode(world, "MetaId004")),
                            semsim::PhysicalPropertyResource(world, "OPB:OPB1234"),
                            std::vector<semsim::SourceParticipant>(
                                    {semsim::SourceParticipant(
                                            world,
                                            "SourceId1",
                                            semsim::Resource(world, semsim::RDFURINode(world, "fake/identifier003")),
                                            1.0,
                                            "PhysicalEntityReference1"
                                    )}
                            ),
                            std::vector<semsim::SinkParticipant>(
                                    {semsim::SinkParticipant(
                                            world,
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
    std::string actual = rdf.toString("rdfxml", "./MyModel.xml");
    std::cout << actual << std::endl;
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\" xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\" xmlns:dcterms=\"http://purl.org/dc/terms/\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:semsim=\"http://www.bhi.washington.edu/semsim/\" xml:base=\"./MyModel.xml\">\n"
                           "  <rdf:Description rdf:about=\"AMetaid004\">\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/OPB/OPB1234\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"SourceId1\">\n"
                           "    <semsim:hasSourceParticipant rdf:resource=\"https://identifiers.org/fake/identifier003\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"https://identifiers.org/fake/identifier003\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"PhysicalEntityReference1\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"https://identifiers.org/fake/identifier003\">\n"
                           "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/2001/XMLSchema#string\">1</semsim:hasMultiplier>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"SinkId1\">\n"
                           "    <semsim:hasSinkParticipant rdf:resource=\"https://identifiers.org/fake/identifier004\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"https://identifiers.org/fake/identifier004\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"PhysicalEntityReference2\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"https://identifiers.org/fake/identifier004\">\n"
                           "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/2001/XMLSchema#string\">1</semsim:hasMultiplier>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n";
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

























