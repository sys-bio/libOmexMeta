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
    semsim::RDF *rdf_ptr = semsim::libsemsim_new_rdf();
    semsim::RDF_fromString(rdf_ptr, samples.singular_annotation1.c_str(), "rdfxml");
    int actual = semsim::RDF_size(rdf_ptr);
    int expected = 1;
    semsim::RDF_free(rdf_ptr);
    ASSERT_EQ(expected, actual);
}

TEST_F(CAPITests, RDFfromString) {
    semsim::RDF *rdf_ptr = semsim::libsemsim_new_rdf();
    semsim::RDF_fromString(rdf_ptr, samples.rdf_xml_seq_example.c_str(), "rdfxml");
    int actual = semsim::RDF_size(rdf_ptr);
    int expected = 4;
    semsim::RDF_free(rdf_ptr);
    ASSERT_EQ(expected, actual);
}

TEST_F(CAPITests, RDFToString) {
    semsim::RDF *rdf_ptr = semsim::libsemsim_new_rdf();
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
    semsim::RDF *rdf_ptr = semsim::libsemsim_new_rdf();
    semsim::RDF_fromString(rdf_ptr, samples.singular_annotation1.c_str(), "rdfxml");
    char *actual = semsim::RDF_getBaseUri(rdf_ptr);
    semsim::RDF_free(rdf_ptr);
    std::cout << actual << std::endl;
    const char *expected = "file://./semsim_model.rdf";
    ASSERT_STREQ(expected, actual);
    free(actual);
}

TEST_F(CAPITests, RDFsetBaseUri) {
    semsim::RDF *rdf_ptr = semsim::libsemsim_new_rdf();
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
    semsim::RDF *rdf_ptr = semsim::libsemsim_new_rdf();
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

TEST_F(CAPITests, TestaddNamespace) {
    semsim::RDF *rdf_ptr = semsim::libsemsim_new_rdf();
    semsim::Editor *editor_ptr = rdf_ptr->toEditorPtr(
            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
            semsim::ASSISTANT_TYPE_SBML
    );
    Editor_addNamespace(editor_ptr, "nameschpashe", "Prephix");
}

TEST_F(CAPITests, TestSingularAnnotationSetAbout) {
    semsim::RDF *rdf_ptr = semsim::libsemsim_new_rdf();

    semsim::Editor *editor_ptr = rdf_ptr->toEditorPtr(
            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
            semsim::ASSISTANT_TYPE_SBML
    );

    semsim::SingularAnnotation* singularAnnotation = semsim::new_singular_annotation(editor_ptr);
    semsim::SingularAnnotation_setAbout(singularAnnotation, "metaid6");
    const char* actual = semsim::SingularAnnotation_getAbout(singularAnnotation);
    const char* expected = "metaid6";
    ASSERT_STREQ(expected, actual);
    free(rdf_ptr);
    free(editor_ptr);
}

TEST_F(CAPITests, TestSingularAnnotationSetPredicate) {
    semsim::RDF *rdf_ptr = semsim::libsemsim_new_rdf();

    semsim::Editor *editor_ptr = rdf_ptr->toEditorPtr(
            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
            semsim::ASSISTANT_TYPE_SBML
    );

    semsim::SingularAnnotation* singularAnnotation = semsim::new_singular_annotation(editor_ptr);
    semsim::SingularAnnotation_setPredicate(singularAnnotation, "bqb", "is");
    const char* actual = semsim::SingularAnnotation_getPredicate(singularAnnotation);
    const char* expected = "http://biomodels.net/biology-qualifiers/is";
    ASSERT_STREQ(expected, actual);
    free(rdf_ptr);
    free(editor_ptr);
}

TEST_F(CAPITests, TestSingularAnnotationSetPredicateNew) {
    semsim::RDF *rdf_ptr = semsim::libsemsim_new_rdf();

    semsim::Editor *editor_ptr = rdf_ptr->toEditorPtr(
            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
            semsim::ASSISTANT_TYPE_SBML
    );

    semsim::SingularAnnotation* singularAnnotation = semsim::new_singular_annotation(editor_ptr);
    semsim::SingularAnnotation_setPredicateNew(singularAnnotation, "UnheardOfNamespace", "NewTerm", "uhon");
    const char* actual = semsim::SingularAnnotation_getPredicate(singularAnnotation);
    const char* expected = "UnheardOfNamespace/NewTerm";
    ASSERT_STREQ(expected, actual);
    free(rdf_ptr);
    free(editor_ptr);
}

TEST_F(CAPITests, TestSingularAnnotationSetResourceLiteral) {
    semsim::RDF *rdf_ptr = semsim::libsemsim_new_rdf();

    semsim::Editor *editor_ptr = rdf_ptr->toEditorPtr(
            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
            semsim::ASSISTANT_TYPE_SBML
    );

    semsim::SingularAnnotation* singularAnnotation = semsim::new_singular_annotation(editor_ptr);
    semsim::SingularAnnotation_setResourceLiteral(singularAnnotation, "LiterallyAString");
    const char* actual = semsim::SingularAnnotation_getResource(singularAnnotation);
    const char* expected = "LiterallyAString";
    ASSERT_STREQ(expected, actual);
    free(rdf_ptr);
    free(editor_ptr);
}

TEST_F(CAPITests, TestSingularAnnotationSetResourceUri) {
    semsim::RDF *rdf_ptr = semsim::libsemsim_new_rdf();

    semsim::Editor *editor_ptr = rdf_ptr->toEditorPtr(
            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
            semsim::ASSISTANT_TYPE_SBML
    );

    semsim::SingularAnnotation* singularAnnotation = semsim::new_singular_annotation(editor_ptr);
    semsim::SingularAnnotation_setResourceUri(singularAnnotation, "uniprot:PD98723");
    const char* actual = semsim::SingularAnnotation_getResource(singularAnnotation);
    const char* expected = "https://identifiers.org/uniprot/PD98723";
    ASSERT_STREQ(expected, actual);
    free(rdf_ptr);
    free(editor_ptr);
}

TEST_F(CAPITests, TestSingularAnnotationSetResourceBlank) {
    semsim::RDF *rdf_ptr = semsim::libsemsim_new_rdf();

    semsim::Editor *editor_ptr = rdf_ptr->toEditorPtr(
            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
            semsim::ASSISTANT_TYPE_SBML
    );

    semsim::SingularAnnotation* singularAnnotation = semsim::new_singular_annotation(editor_ptr);
    semsim::SingularAnnotation_setResourceBlank(singularAnnotation, "Nothing");
    const char* actual = semsim::SingularAnnotation_getResource(singularAnnotation);
    const char* expected = "Nothing";
    ASSERT_STREQ(expected, actual);
    free(rdf_ptr);
    free(editor_ptr);
}

//TEST_F(CAPITests, TestAddSingularAnnotation) {
//    semsim::RDF *rdf_ptr = semsim::libsemsim_new_rdf();
//    semsim::Editor *editor_ptr = libsemsim_new_editor(rdf_ptr, const char* xml, semsim::XmlAssistantType type);
////    ->toEditorPtr(
////            SBMLFactory::getModelStr(SBML_NOT_ANNOTATED),
////            semsim::ASSISTANT_TYPE_SBML
////    );
//    semsim::SingularAnnotation* singularAnnotation = libsemsim_new_singular_annotation(rdf_ptr);
//
////    Editor_addNamespace(editor_ptr, "nameschpashe", "Prephiix");
//
//}


















































