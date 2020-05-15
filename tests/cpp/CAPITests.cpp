//
// Created by Ciaran on 5/12/2020.
//

#include "gtest/gtest.h"


#include "gtest/gtest.h"
#include "AnnotationSamples.h"
#include "semsim/SemsimCApi.h"
#include "semsim/RDF.h"
#include "SBMLFactory.h"
#include "semsim/XmlAssistant.h"

class CAPITests : public ::testing::Test {
public:

    AnnotationSamples samples = AnnotationSamples();

    CAPITests() = default;

    void TearDown() override {
    };

};


TEST_F(CAPITests, RDFSize) {
    semsim::RDF *rdf_ptr = semsim::new_rdf();
    semsim::RDF_fromString(rdf_ptr, samples.singular_annotation1.c_str(), "rdfxml");
    int actual = semsim::RDF_size(rdf_ptr);
    int expected = 1;
    semsim::RDF_free(rdf_ptr);
    ASSERT_EQ(expected, actual);
}

TEST_F(CAPITests, RDFfromString) {
    semsim::RDF *rdf_ptr = semsim::new_rdf();
    semsim::RDF_fromString(rdf_ptr, samples.rdf_xml_seq_example.c_str(), "rdfxml");
    int actual = semsim::RDF_size(rdf_ptr);
    int expected = 4;
    semsim::RDF_free(rdf_ptr);
    ASSERT_EQ(expected, actual);
}

TEST_F(CAPITests, RDFToString) {
    semsim::RDF *rdf_ptr = semsim::new_rdf();
    semsim::RDF_fromString(rdf_ptr, samples.singular_annotation1.c_str(), "rdfxml");
    std::string actual = rdf_ptr->toString("rdfxml-abbrev", "annotation.rdf");
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xml:base=\"file://annotation.rdf\">\n"
                           "  <rdf:Description rdf:about=\"file://./metaid_1\">\n"
                           "    <ns1:is xmlns:ns1=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "       rdf:resource=\"https://identifiers.org/uniprot/P0DP23\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n";
    semsim::RDF_free(rdf_ptr);
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(CAPITests, RDFgetBaseUri) {
    semsim::RDF *rdf_ptr = semsim::new_rdf();
    semsim::RDF_fromString(rdf_ptr, samples.singular_annotation1.c_str(), "rdfxml");
    char *actual = semsim::RDF_getBaseUri(rdf_ptr);
    semsim::RDF_free(rdf_ptr);
    std::cout << actual << std::endl;
    const char *expected = "file://./semsim_model.rdf";
    ASSERT_STREQ(expected, actual);
    free(actual);
}

TEST_F(CAPITests, RDFsetBaseUri) {
    semsim::RDF *rdf_ptr = semsim::new_rdf();
    semsim::RDF_fromString(rdf_ptr, samples.singular_annotation1.c_str(), "rdfxml");
    semsim::RDF_setBaseUri(rdf_ptr, "ANewBaseUri.rdf");
    char *actual = semsim::RDF_getBaseUri(rdf_ptr);
    semsim::RDF_free(rdf_ptr);
    std::cout << actual << std::endl;
    const char *expected = "file://ANewBaseUri.rdf";
    ASSERT_STREQ(expected, actual);
    free(actual); // necessary because we allocated on heap.
}


TEST_F(CAPITests, RDFqueryResultsAsStr) {
    semsim::RDF *rdf_ptr = semsim::new_rdf();
    semsim::RDF_fromString(rdf_ptr, samples.composite_annotation_pe.c_str(), "rdfxml");

    const char *query = "SELECT ?x ?y ?z \n"
                        "WHERE { ?x ?y ?z }";
    const char *results = semsim::RDF_queryResultsAsStr(rdf_ptr, query, "csv");
    semsim::RDF_free(rdf_ptr);
    std::string expected = "x,y,z\r\n"
                           "file://./VLV,http://biomodels.net/biology-qualifiers/isVersionOf,http://identifiers.org/opb/OPB_00154\r\n"
                           "file://./VLV,http://biomodels.net/biology-qualifiers/isPropertyOf,file://./MyModel.rdf#entity_0\r\n"
                           "file://./MyModel.rdf#entity_0,http://biomodels.net/biology-qualifiers/is,http://identifiers.org/fma/FMA:9670\r\n"
                           "file://./MyModel.rdf#entity_0,http://biomodels.net/biology-qualifiers/isPartOf,http://identifiers.org/fma/FMA:18228\r\n";
    ASSERT_STREQ(expected.c_str(), results);
}

TEST_F(CAPITests, TestSingularAnnotationSetAbout) {
    semsim::RDF *rdf_ptr = semsim::new_rdf();

    semsim::Editor *editor_ptr = rdf_ptr->toEditorPtr(
            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
            semsim::ASSISTANT_TYPE_SBML
    );

    semsim::SingularAnnotation *singularAnnotation = semsim::new_singular_annotation(editor_ptr);
    semsim::SingularAnnotation_setAbout(singularAnnotation, "metaid6");
    const char *actual = semsim::SingularAnnotation_getAbout(singularAnnotation);
    const char *expected = "metaid6";
    ASSERT_STREQ(expected, actual);
    free(rdf_ptr);
    free(editor_ptr);
    free(singularAnnotation);
}

TEST_F(CAPITests, TestSingularAnnotationSetPredicate) {
    semsim::RDF *rdf_ptr = semsim::new_rdf();

    semsim::Editor *editor_ptr = rdf_ptr->toEditorPtr(
            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
            semsim::ASSISTANT_TYPE_SBML
    );

    semsim::SingularAnnotation *singularAnnotation = semsim::new_singular_annotation(editor_ptr);
    semsim::SingularAnnotation_setPredicate(singularAnnotation, "bqb", "is");
    const char *actual = semsim::SingularAnnotation_getPredicate(singularAnnotation);
    const char *expected = "http://biomodels.net/biology-qualifiers/is";
    ASSERT_STREQ(expected, actual);
    free(rdf_ptr);
    free(editor_ptr);
    free(singularAnnotation);
}

TEST_F(CAPITests, TestSingularAnnotationSetPredicateNew) {
    semsim::RDF *rdf_ptr = semsim::new_rdf();

    semsim::Editor *editor_ptr = rdf_ptr->toEditorPtr(
            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
            semsim::ASSISTANT_TYPE_SBML
    );

    semsim::SingularAnnotation *singularAnnotation = semsim::new_singular_annotation(editor_ptr);
    semsim::SingularAnnotation_setPredicateNew(singularAnnotation, "UnheardOfNamespace", "NewTerm", "uhon");
    const char *actual = semsim::SingularAnnotation_getPredicate(singularAnnotation);
    const char *expected = "UnheardOfNamespace/NewTerm";
    ASSERT_STREQ(expected, actual);
    free(rdf_ptr);
    free(editor_ptr);
    free(singularAnnotation);
}

TEST_F(CAPITests, TestSingularAnnotationSetResourceLiteral) {
    semsim::RDF *rdf_ptr = semsim::new_rdf();

    semsim::Editor *editor_ptr = rdf_ptr->toEditorPtr(
            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
            semsim::ASSISTANT_TYPE_SBML
    );

    semsim::SingularAnnotation *singularAnnotation = semsim::new_singular_annotation(editor_ptr);
    semsim::SingularAnnotation_setResourceLiteral(singularAnnotation, "LiterallyAString");
    const char *actual = semsim::SingularAnnotation_getResource(singularAnnotation);
    const char *expected = "LiterallyAString";
    ASSERT_STREQ(expected, actual);
    free(rdf_ptr);
    free(editor_ptr);
    free(singularAnnotation);
}

TEST_F(CAPITests, TestSingularAnnotationSetResourceUri) {
    semsim::RDF *rdf_ptr = semsim::new_rdf();

    semsim::Editor *editor_ptr = rdf_ptr->toEditorPtr(
            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
            semsim::ASSISTANT_TYPE_SBML
    );

    semsim::SingularAnnotation *singularAnnotation = semsim::new_singular_annotation(editor_ptr);
    semsim::SingularAnnotation_setResourceUri(singularAnnotation, "uniprot:PD98723");
    const char *actual = semsim::SingularAnnotation_getResource(singularAnnotation);
    const char *expected = "https://identifiers.org/uniprot/PD98723";
    ASSERT_STREQ(expected, actual);
    free(rdf_ptr);
    free(editor_ptr);
    free(singularAnnotation);
}

TEST_F(CAPITests, TestSingularAnnotationSetResourceBlank) {
    semsim::RDF *rdf_ptr = semsim::new_rdf();

    semsim::Editor *editor_ptr = rdf_ptr->toEditorPtr(
            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
            semsim::ASSISTANT_TYPE_SBML
    );

    semsim::SingularAnnotation *singularAnnotation = semsim::new_singular_annotation(editor_ptr);
    semsim::SingularAnnotation_setResourceBlank(singularAnnotation, "Nothing");
    const char *actual = semsim::SingularAnnotation_getResource(singularAnnotation);
    const char *expected = "Nothing";
    ASSERT_STREQ(expected, actual);
    free(rdf_ptr);
    free(editor_ptr);
    free(singularAnnotation);
}


TEST_F(CAPITests, TestPhysicalEntity) {
    HERE();
    semsim::RDF *rdf_ptr = semsim::new_rdf();
    HERE();

    semsim::Editor *editor_ptr = rdf_ptr->toEditorPtr(
            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
            semsim::ASSISTANT_TYPE_SBML
    );
    HERE();

    semsim::PhysicalEntity *physical_entity_ptr = semsim::new_physical_entity(editor_ptr);
    HERE();
    physical_entity_ptr = semsim::PhysicalEntity_setAbout(physical_entity_ptr, "metaid87");
    HERE();
    physical_entity_ptr = semsim::PhysicalEntity_setPhysicalProperty(physical_entity_ptr, "opb/OPB007");
    HERE();
    physical_entity_ptr = semsim::PhysicalEntity_setIdentity(physical_entity_ptr, "uniprot:PD58736");
    HERE();
    physical_entity_ptr = semsim::PhysicalEntity_addLocation(physical_entity_ptr, "fma:FMA_8764");
    HERE();

    const char *actual = semsim::PhysicalEntity_str(physical_entity_ptr, "rdfxml-abbrev", "./annotations.rdf");
    HERE();
    const char *expected = "fed";
    HERE();
    std::cout << actual << std::endl;
    HERE();
    ASSERT_STREQ(expected, actual);
    HERE();
    free(rdf_ptr);
    HERE();
    free(editor_ptr);
    HERE();
}

TEST_F(CAPITests, TestPhysicalEntityAbout) {
    semsim::RDF *rdf_ptr = semsim::new_rdf();
    semsim::Editor *editor_ptr = rdf_ptr->toEditorPtr(
            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
            semsim::ASSISTANT_TYPE_SBML
    );
    semsim::PhysicalEntity *physical_entity_ptr = semsim::new_physical_entity(editor_ptr);
    physical_entity_ptr = semsim::PhysicalEntity_setAbout(physical_entity_ptr, "metaid87");
    const char *actual = semsim::PhysicalEntity_getAbout(physical_entity_ptr);
    const char *expected = "metaid87";
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected, actual);
    free(rdf_ptr);
    free(editor_ptr);
}


TEST_F(CAPITests, TestPhysicalEntityPhysicalProperty) {
    semsim::RDF *rdf_ptr = semsim::new_rdf();
    semsim::Editor *editor_ptr = rdf_ptr->toEditorPtr(
            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
            semsim::ASSISTANT_TYPE_SBML
    );
    semsim::PhysicalEntity *physical_entity_ptr = semsim::new_physical_entity(editor_ptr);
    physical_entity_ptr = semsim::PhysicalEntity_setPhysicalProperty(physical_entity_ptr, "opb/opb_465");
    const char *actual = semsim::PhysicalEntity_getPhysicalProperty(physical_entity_ptr);
    const char *expected = "https://identifiers.org/opb/opb_465";
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected, actual);
    free(rdf_ptr);
    free(editor_ptr);
}

TEST_F(CAPITests, TestPhysicalEntityGetIdentity) {
    semsim::RDF *rdf_ptr = semsim::new_rdf();
    semsim::Editor *editor_ptr = rdf_ptr->toEditorPtr(
            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
            semsim::ASSISTANT_TYPE_SBML
    );
    semsim::PhysicalEntity *physical_entity_ptr = semsim::new_physical_entity(editor_ptr);
    physical_entity_ptr = semsim::PhysicalEntity_setIdentity(physical_entity_ptr, "uniprot/PD7363");
    const char *actual = semsim::PhysicalEntity_getIdentity(physical_entity_ptr);
    const char *expected = "https://identifiers.org/uniprot/PD7363";
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected, actual);
    free(rdf_ptr);
    free(editor_ptr);
}

TEST_F(CAPITests, TestPhysicalEntityLocations) {
    semsim::RDF *rdf_ptr = semsim::new_rdf();
    semsim::Editor *editor_ptr = rdf_ptr->toEditorPtr(
            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
            semsim::ASSISTANT_TYPE_SBML
    );
    semsim::PhysicalEntity *physical_entity_ptr = semsim::new_physical_entity(editor_ptr);
    physical_entity_ptr = semsim::PhysicalEntity_addLocation(physical_entity_ptr, "FMA:fma:8376");
    physical_entity_ptr = semsim::PhysicalEntity_addLocation(physical_entity_ptr, "FMA:fma:8377");
    physical_entity_ptr = semsim::PhysicalEntity_addLocation(physical_entity_ptr, "FMA:fma:8378");
    char **actual = semsim::PhysicalEntity_getLocations(physical_entity_ptr);
    const char *expected = "https://identifiers.org/FMA/fma:8376\n"
                           "https://identifiers.org/FMA/fma:8377\n"
                           "https://identifiers.org/FMA/fma:8378\n";
    std::ostringstream os;
    for (int i = 0; i < semsim::PhysicalEntity_getNumLocations(physical_entity_ptr); i++) {
        os << *actual << '\n';
        actual++;
    }
    ASSERT_STREQ(expected, os.str().c_str());
    free(rdf_ptr);
    free(editor_ptr);
}


TEST_F(CAPITests, TestPhysicalEntityNumLocations) {
    semsim::RDF *rdf_ptr = semsim::new_rdf();
    semsim::Editor *editor_ptr = rdf_ptr->toEditorPtr(
            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
            semsim::ASSISTANT_TYPE_SBML
    );
    semsim::PhysicalEntity *physical_entity_ptr = semsim::new_physical_entity(editor_ptr);
    physical_entity_ptr = semsim::PhysicalEntity_addLocation(physical_entity_ptr, "FMA:fma:8376");
    physical_entity_ptr = semsim::PhysicalEntity_addLocation(physical_entity_ptr, "FMA:fma:8377");
    physical_entity_ptr = semsim::PhysicalEntity_addLocation(physical_entity_ptr, "FMA:fma:8378");
    int expected = 3;
    int actual = semsim::PhysicalEntity_getNumLocations(physical_entity_ptr);
    free(rdf_ptr);
    free(editor_ptr);
}


TEST_F(CAPITests, TestPhysicalEntityStr) {
    semsim::RDF *rdf_ptr = semsim::new_rdf();
    semsim::Editor *editor_ptr = rdf_ptr->toEditorPtr(
            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
            semsim::ASSISTANT_TYPE_SBML
    );
    semsim::PhysicalEntity *physical_entity_ptr = semsim::new_physical_entity(editor_ptr);
    physical_entity_ptr = semsim::PhysicalEntity_setPhysicalProperty(physical_entity_ptr, "opb/opb_465");
    physical_entity_ptr = semsim::PhysicalEntity_setAbout(physical_entity_ptr, "metaid87");
    physical_entity_ptr = semsim::PhysicalEntity_setIdentity(physical_entity_ptr, "uniprot/PD7363");
    physical_entity_ptr = semsim::PhysicalEntity_addLocation(physical_entity_ptr, "FMA:fma:8376");
    physical_entity_ptr = semsim::PhysicalEntity_addLocation(physical_entity_ptr, "FMA:fma:8377");
    physical_entity_ptr = semsim::PhysicalEntity_addLocation(physical_entity_ptr, "FMA:fma:8378");
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xml:base=\"file://./Annot.rdf\">\n"
                           "  <rdf:Description rdf:about=\"PhysicalEntity0000\">\n"
                           "    <bqbiol:is rdf:resource=\"https://identifiers.org/uniprot/PD7363\"/>\n"
                           "    <bqbiol:isPartOf rdf:resource=\"https://identifiers.org/FMA/fma:8376\"/>\n"
                           "    <bqbiol:isPartOf rdf:resource=\"https://identifiers.org/FMA/fma:8377\"/>\n"
                           "    <bqbiol:isPartOf rdf:resource=\"https://identifiers.org/FMA/fma:8378\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"metaid87\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"PhysicalEntity0000\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/opb/opb_465\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n";
    const char *actual = semsim::PhysicalEntity_str(physical_entity_ptr, "rdfxml-abbrev", "./Annot.rdf");
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual);
    free(rdf_ptr);
    free(editor_ptr);
}


TEST_F(CAPITests, TestPhysicalProcess) {
    semsim::RDF *rdf_ptr = semsim::new_rdf();
    semsim::Editor *editor_ptr = rdf_ptr->toEditorPtr(
            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
            semsim::ASSISTANT_TYPE_SBML
    );
    semsim::PhysicalProcess *physical_process_ptr = semsim::new_physical_process(editor_ptr);

    physical_process_ptr = semsim::PhysicalProcess_setAbout(physical_process_ptr, "Metaid0937");
    physical_process_ptr = semsim::PhysicalProcess_setPhysicalProperty(physical_process_ptr, "opb/opb93864");
    physical_process_ptr = semsim::PhysicalProcess_addSink(
            physical_process_ptr, "Sink9", 1.0, "Entity8");
    physical_process_ptr = semsim::PhysicalProcess_addSource(
            physical_process_ptr, "Source1", 1.0, "Entity8");
    physical_process_ptr = semsim::PhysicalProcess_addMediator(
            physical_process_ptr, "Mod4", 1.0, "Entity8");

    std::string actual = physical_process_ptr->toTriples().str();
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"Metaid0937\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"PhysicalProcess0000\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/opb/opb93864\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"Mod4\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"Entity8\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"PhysicalProcess0000\">\n"
                           "    <semsim:hasMediatorParticipant rdf:resource=\"Mod4\"/>\n"
                           "    <semsim:hasSinkParticipant rdf:resource=\"Sink9\"/>\n"
                           "    <semsim:hasSourceParticipant rdf:resource=\"Source1\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"Sink9\">\n"
                           "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/2001/XMLSchema#double\">1</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"Entity8\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"Source1\">\n"
                           "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/2001/XMLSchema#double\">1</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"Entity8\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n";
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());

    free(rdf_ptr);
    free(editor_ptr);
}

TEST_F(CAPITests, TestPhysicalForce) {
    semsim::RDF *rdf_ptr = semsim::new_rdf();
    semsim::Editor *editor_ptr = rdf_ptr->toEditorPtr(
            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
            semsim::ASSISTANT_TYPE_SBML
    );
    semsim::PhysicalForce *physical_force_ptr = semsim::new_physical_force(editor_ptr);

    physical_force_ptr = semsim::PhysicalForce_setAbout(physical_force_ptr, "Metaid0937");
    physical_force_ptr = semsim::PhysicalForce_setPhysicalProperty(physical_force_ptr, "opb/opb93864");
    physical_force_ptr = semsim::PhysicalForce_addSink(
            physical_force_ptr, "Sink9", 1.0, "Entity8");
    physical_force_ptr = semsim::PhysicalForce_addSource(
            physical_force_ptr, "Source1", 1.0, "Entity9");

    std::string actual = physical_force_ptr->toTriples().str();
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"Metaid0937\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"PhysicalForce0000\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/opb/opb93864\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"PhysicalForce0000\">\n"
                           "    <semsim:hasSinkParticipant rdf:resource=\"Sink9\"/>\n"
                           "    <semsim:hasSourceParticipant rdf:resource=\"Source1\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"Sink9\">\n"
                           "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/2001/XMLSchema#double\">1</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"Entity8\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"Source1\">\n"
                           "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/2001/XMLSchema#double\">1</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"Entity9\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n";
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());

    free(rdf_ptr);
    free(editor_ptr);
}

TEST_F(CAPITests, TestEditorToRDF) {
    semsim::RDF *rdf_ptr = semsim::new_rdf();
    semsim::Editor *editor_ptr = rdf_ptr->toEditorPtr(
            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
            semsim::ASSISTANT_TYPE_SBML
    );
    semsim::PhysicalProcess *physical_process_ptr = semsim::new_physical_process(editor_ptr);

    physical_process_ptr = semsim::PhysicalProcess_setAbout(physical_process_ptr, "Metaid0937");
    physical_process_ptr = semsim::PhysicalProcess_setPhysicalProperty(physical_process_ptr, "opb/opb93864");
    physical_process_ptr = semsim::PhysicalProcess_addSink(
            physical_process_ptr, "Sink9", 1.0, "Entity8");
    physical_process_ptr = semsim::PhysicalProcess_addSource(
            physical_process_ptr, "Source1", 1.0, "Entity8");
    physical_process_ptr = semsim::PhysicalProcess_addMediator(
            physical_process_ptr, "Mod4", 1.0, "Entity8");

    semsim::PhysicalEntity *physical_entity_ptr = semsim::new_physical_entity(editor_ptr);
    physical_entity_ptr = semsim::PhysicalEntity_setPhysicalProperty(physical_entity_ptr, "opb/opb_465");
    physical_entity_ptr = semsim::PhysicalEntity_setAbout(physical_entity_ptr, "metaid87");
    physical_entity_ptr = semsim::PhysicalEntity_setIdentity(physical_entity_ptr, "uniprot/PD7363");
    physical_entity_ptr = semsim::PhysicalEntity_addLocation(physical_entity_ptr, "FMA:fma:8376");
    physical_entity_ptr = semsim::PhysicalEntity_addLocation(physical_entity_ptr, "FMA:fma:8377");
    physical_entity_ptr = semsim::PhysicalEntity_addLocation(physical_entity_ptr, "FMA:fma:8378");

    semsim::PhysicalForce *physical_force_ptr = semsim::new_physical_force(editor_ptr);

    physical_force_ptr = semsim::PhysicalForce_setAbout(physical_force_ptr, "Metaid0937");
    physical_force_ptr = semsim::PhysicalForce_setPhysicalProperty(physical_force_ptr, "opb/opb93864");
    physical_force_ptr = semsim::PhysicalForce_addSink(
            physical_force_ptr, "Sink9", 1.0, "Entity8");
    physical_force_ptr = semsim::PhysicalForce_addSource(
            physical_force_ptr, "Source1", 1.0, "Entity9");


    semsim::Editor_addPhysicalProcess(editor_ptr, physical_process_ptr);
    semsim::Editor_addPhysicalEntity(editor_ptr, physical_entity_ptr);
    semsim::Editor_addPhysicalForce(editor_ptr, physical_force_ptr);

    semsim::Editor_toRDF(editor_ptr);
    free(editor_ptr);

    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\"\n"
                           "   xml:base=\"file://./Annot.rdf\">\n"
                           "  <rdf:Description rdf:about=\"Metaid0937\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"PhysicalForce0000\"/>\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"PhysicalProcess0000\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/opb/opb93864\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"Mod4\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"Entity8\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"PhysicalEntity0000\">\n"
                           "    <bqbiol:is rdf:resource=\"https://identifiers.org/uniprot/PD7363\"/>\n"
                           "    <bqbiol:isPartOf rdf:resource=\"https://identifiers.org/FMA/fma:8376\"/>\n"
                           "    <bqbiol:isPartOf rdf:resource=\"https://identifiers.org/FMA/fma:8377\"/>\n"
                           "    <bqbiol:isPartOf rdf:resource=\"https://identifiers.org/FMA/fma:8378\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"PhysicalForce0000\">\n"
                           "    <semsim:hasSinkParticipant rdf:resource=\"Sink9\"/>\n"
                           "    <semsim:hasSourceParticipant rdf:resource=\"Source1\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"PhysicalProcess0000\">\n"
                           "    <semsim:hasMediatorParticipant rdf:resource=\"Mod4\"/>\n"
                           "    <semsim:hasSinkParticipant rdf:resource=\"Sink9\"/>\n"
                           "    <semsim:hasSourceParticipant rdf:resource=\"Source1\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"Sink9\">\n"
                           "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/2001/XMLSchema#double\">1</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"Entity8\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"Source1\">\n"
                           "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/2001/XMLSchema#double\">1</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"Entity8\"/>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"Entity9\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"metaid87\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"PhysicalEntity0000\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/opb/opb_465\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n";
    std::string actual = semsim::RDF_toString(rdf_ptr, "rdfxml-abbrev", "./Annot.rdf");
    std::cout << actual << std::endl;
    free(rdf_ptr);


}















































