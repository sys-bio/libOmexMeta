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
    std::string actual = rdf.toString("rdfxml", "file://./annotations.rdf");
    std::cout << actual << std::endl;
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "         xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "         xml:base=\"file://MyModel.xml\">\n"
                           "    <rdf:Description rdf:about=\"VLV\">\n"
                           "        <bqbiol:isVersionOf rdf:resource=\"http://identifiers.org/opb/OPB_00154\"/>\n"
                           "        <bqbiol:isPropertyOf rdf:resource=\"PhysicalEntity0000\"/>\n"
                           "    </rdf:Description>\n"
                           "    <rdf:Description rdf:about=\"#entity_0\">\n"
                           "        <bqbiol:is rdf:resource=\"http://identifiers.org/fma/FMA:9670\"/>\n"
                           "        <bqbiol:isPartOf rdf:resource=\"http://identifiers.org/fma/FMA:18228\"/>\n"
                           "    </rdf:Description>\n"
                           "</rdf:RDF>\n";
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
    std::string actual = rdf.toString("rdfxml-abbrev", "file://./annotations.rdf");
    std::cout << actual << std::endl;
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "         xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "         xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\"\n"
                           "         xml:base=\"file://MyModel.xml\">\n"
                           "    <rdf:Description rdf:about=\"property_metaid_0\">\n"
                           "        <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/opb/OPB_00592\"/>\n"
                           "        <bqbiol:isPropertyOf rdf:resource=\"file://MyModel.xml#process_metaid_0\"/>\n"
                           "    </rdf:Description>\n"
                           "    <rdf:Description rdf:about=\"source_0\">\n"
                           "        <semsim:hasMultiplier>1.0</semsim:hasMultiplier>\n"
                           "        <semsim:hasPhysicalEntityReference rdf:resource=\"file://MyModel.xml#species_metaid_0\"/>\n"
                           "    </rdf:Description>\n"
                           "    <rdf:Description rdf:about=\"sink_0\">\n"
                           "        <semsim:hasMultiplier>2.0</semsim:hasMultiplier>\n"
                           "        <semsim:hasPhysicalEntityReference rdf:resource=\"file://MyModel.xml#species_metaid_1\"/>\n"
                           "    </rdf:Description>\n"
                           "    <rdf:Description rdf:about=\"#mediator_0\">\n"
                           "        <semsim:hasPhysicalEntityReference rdf:resource=\"file://MyModel.xml#species_metaid_2\"/>\n"
                           "    </rdf:Description>\n"
                           "</rdf:RDF>\n";
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
    std::string actual = rdf.toString("rdfxml-abbrev", "file://./annotations.rdf");
    std::cout << actual << std::endl;
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "         xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "         xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\"\n"
                           "         xml:base=\"file://MyModel.xml\">\n"
                           "    <rdf:Description rdf:about=\"parameter_metaid_0\">\n"
                           "        <bqbiol:isPropertyOf rdf:resource=\"./MyModel.sbml#force_0\"/>\n"
                           "        <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/opb/OPB_01058\"/>\n"
                           "    </rdf:Description>\n"
                           "    <rdf:Description rdf:about=\"force_0\">\n"
                           "        <semsim:hasSourceParticipant rdf:resource=\"./MyModel.sbml#source_0\"/>\n"
                           "        <semsim:hasSinkParticipant rdf:resource=\"./MyModel.sbml#sink_0\"/>\n"
                           "    </rdf:Description>\n"
                           "    <rdf:Description rdf:about=\"source_0\">\n"
                           "        <semsim:hasPhysicalEntityReference rdf:resource=\"./MyModel.sbml#species_metaid_0\"/>\n"
                           "    </rdf:Description>\n"
                           "    <rdf:Description rdf:about=\"sink_0\">\n"
                           "        <semsim:hasPhysicalEntityReference rdf:resource=\"./MyModel.sbml#species_metaid_1\"/>\n"
                           "    </rdf:Description>\n"
                           "</rdf:RDF>\n";
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

























