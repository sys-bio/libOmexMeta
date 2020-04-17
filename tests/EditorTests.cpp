//
// Created by Ciaran on 4/15/2020.
//
#include "gtest/gtest.h"
#include "SBMLFactory.h"
#include "semsim/Editor.h"
#include "semsim/XmlAssistant.h"

class EditorTests : public ::testing::Test {

public:

    librdf_world* world;
    raptor_world* raptorWorld;
    librdf_storage* storage;
    librdf_model* model;

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
    const auto& metaids = editor.getMetaids();
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
    editor.addAnnotation(
            "SemsimMetaid0010",
            std::make_unique<semsim::Predicate>(semsim::BiomodelsQualifier("is")),
            "https://identifiers.org/uniprot/P0DP23"
            );
    semsim::TripleList tripleList = editor.getTripleList();
    ASSERT_EQ(1, tripleList.size());
    ASSERT_EQ(1, tripleList[0].size());
}

TEST_F(EditorTests, TestToRDFSingleAnnotation1) {
    semsim::RDF rdf;
    semsim::Editor editor = rdf.toEditor(
            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
            semsim::ASSISTANT_TYPE_SBML);
    editor.addAnnotation(
            "SemsimMetaid0004",
            std::make_unique<semsim::Predicate>(semsim::BiomodelsQualifier("is")),
            "https://identifiers.org/uniprot/P0DP23"
            );
    editor.toRDF(rdf);

    std::string actual = rdf.toString("rdfxml", "./MyModel.xml");
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\" xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\" xmlns:dcterms=\"http://purl.org/dc/terms/\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\">\n"
                           "  <rdf:Description rdf:about=\"SemsimMetaid0010\">\n"
                           "    <bqbiol:is rdf:resource=\"https://identifiers.org/uniprot/P0DP23\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n";
    ASSERT_STREQ(expected.c_str(), actual.c_str());

}


TEST_F(EditorTests, TestToRDFSingleAnnotation2) {
    semsim::RDF rdf;
    semsim::Editor editor = rdf.toEditor(
            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
            semsim::ASSISTANT_TYPE_SBML);
    editor.addAnnotation(
            "SemsimMetaid0008",
            std::make_unique<semsim::Predicate>(semsim::BiomodelsQualifier("isDescribedBy")),
            "pubmed:12991237"
            );
    editor.toRDF(rdf);

    std::string actual = rdf.toString("turtle", "./MyModel.xml");
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqmodel: <http://biomodels.net/model-qualifiers/> .\n"
                           "@prefix dcterms: <http://purl.org/dc/terms/> .\n"
                           "@prefix semsim: <http://www.bhi.washington.edu/semsim#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "\n"
                           "<SemsimMetaid0008>\n"
                           "    bqbiol:isDescribedBy <https://identifiers.org/pubmed/12991237> .\n\n";
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(EditorTests, TestToRDFSingleAnnotation3) {
    semsim::RDF rdf;
    semsim::Editor editor = rdf.toEditor(
            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
            semsim::ASSISTANT_TYPE_SBML);
    editor.addAnnotation(
            "SemsimMetaid0008",
            std::make_unique<semsim::Predicate>(semsim::BiomodelsQualifier("isDescribedBy")),
            "pubmed:12991237"
            );
    editor.toRDF(rdf);

    std::string actual = rdf.toString("rdfxml", "./MyModel.xml");
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\" xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\" xmlns:dcterms=\"http://purl.org/dc/terms/\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\">\n"
                           "  <rdf:Description rdf:about=\"SemsimMetaid0008\">\n"
                           "    <bqbiol:isDescribedBy rdf:resource=\"https://identifiers.org/pubmed/12991237\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n";
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(EditorTests, TestToRDFSingularAnnotationWithLiteral) {
    semsim::RDF rdf;
    semsim::Editor editor = rdf.toEditor(
            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
            semsim::ASSISTANT_TYPE_SBML);
    editor.addAnnotation(
            "SemsimMetaid0008",
            std::make_unique<semsim::Predicate>(semsim::DCTerms("Description")),
            "Cardiomyocyte cytosolic ATP concentration"
            );
    editor.toRDF(rdf);

    std::string actual = rdf.toString("rdfxml", "./MyModel.xml");
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\" xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\" xmlns:dcterms=\"http://purl.org/dc/terms/\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\" xml:base=\"./MyModel.xml\">\n"
                           "  <rdf:Description rdf:about=\"SemsimMetaid0008\">\n"
                           "    <dcterms:Description>Cardiomyocyte cytosolic ATP concentration</dcterms:Description>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(EditorTests, TestAddAnnotationCompositeTypePhysicalEntity) {
    semsim::RDF rdf;
    semsim::Editor editor = rdf.toEditor(
            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
            semsim::ASSISTANT_TYPE_SBML);
    editor.addAnnotation(
            "SemsimMetaid0018", "opb/OPB_00154", "SemsimMetaid0014",
            "fma/FMA:9670", "fma/FMA:18228"
    );
    editor.toRDF(rdf);

    std::string actual = rdf.toString("rdfxml", "./MyModel.xml");
    std::cout << actual << std::endl;
}

























