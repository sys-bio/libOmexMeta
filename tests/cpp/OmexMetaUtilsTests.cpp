//
// Created by Ciaran on 4/13/2020.
//
#include "gtest/gtest.h"
#include "iostream"
#include "AnnotationSamples.h"
#include "SBMLFactory.h"
#include "omexmeta/RDF.h"

using namespace omexmeta;

class OmexMetaUtilsTests : public ::testing::Test {
public:

    AnnotationSamples samples;

    OmexMetaUtilsTests() = default;

};

TEST_F(OmexMetaUtilsTests, TestFileExists) {
    // we first download
    CurlGet::download(samples.sbml_url1, samples.sbml_filename1);
    ASSERT_TRUE(OmexMetaUtils::exists(samples.sbml_filename1));
}

TEST_F(OmexMetaUtilsTests, TestFileDoesNotExists) {
    ASSERT_FALSE(OmexMetaUtils::exists("./CheeseBiscuits.cheddar"));
}

TEST_F(OmexMetaUtilsTests, TestDeleteFile) {
    CurlGet::download(samples.sbml_url1, samples.sbml_filename1);
    assert(OmexMetaUtils::exists(samples.sbml_filename1));
    OmexMetaUtils::removeFile(samples.sbml_filename1);
    ASSERT_FALSE(OmexMetaUtils::exists(samples.sbml_filename1));
}

TEST_F(OmexMetaUtilsTests, TestRemoveIfExists) {
    CurlGet::download(samples.sbml_url1, samples.sbml_filename1);
    assert(OmexMetaUtils::exists(samples.sbml_filename1));
    OmexMetaUtils::removeIfExists(samples.sbml_filename1);
    ASSERT_FALSE(OmexMetaUtils::exists(samples.sbml_filename1));
}

TEST_F(OmexMetaUtilsTests, TestRemoveIfExists2) {
    std::string fname = "./cheese_biscuits.blue";
    OmexMetaUtils::removeIfExists(fname); // should not error
    ASSERT_FALSE(OmexMetaUtils::exists(fname));
}

TEST_F(OmexMetaUtilsTests, TestPrefixFile) {

    std::string fname = (std::filesystem::current_path() /= "cheese_biscuits.blue").string();
    fname = OmexMetaUtils::prepareBaseUri(fname);

//    std::string expected = "file://" + fname;
    std::string expected = fname;
    ASSERT_STREQ(expected.c_str(), fname.c_str());
}

TEST_F(OmexMetaUtilsTests, TestGEtNamespacesFromUri) {
    std::string uri = "http://uri.com/identifiers/PD1234";
    std::string expected = "http://uri.com/identifiers/";
    std::string actual = OmexMetaUtils::getNamespaceFromUri(uri);
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(OmexMetaUtilsTests, TestGEtNamespacesFromUriSemsim) {
    std::string uri = "http://www.bhi.washington.edu/semsim#hasSourceParticipant";
    std::string expected = "http://www.bhi.washington.edu/semsim#";
    std::string actual = OmexMetaUtils::getNamespaceFromUri(uri);
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(OmexMetaUtilsTests, TestIsFormattedUri1) {
    std::string uri = "http://www.bhi.washington.edu/semsim#hasSourceParticipant";
    ASSERT_TRUE(OmexMetaUtils::isFormattedUri(uri));
}

TEST_F(OmexMetaUtilsTests, TestIsFormattedUri2) {
    std::string uri = "https://www.bhi.washington.edu/semsim#hasSourceParticipant";
    ASSERT_TRUE(OmexMetaUtils::isFormattedUri(uri));
}

TEST_F(OmexMetaUtilsTests, TestIsFormattedUri3) {
    std::string uri = "file://www.bhi.washington.edu/semsim#hasSourceParticipant";
    ASSERT_TRUE(OmexMetaUtils::isFormattedUri(uri));
}

TEST_F(OmexMetaUtilsTests, TestIsFormattedUri4) {
    std::string uri = "hasSourceParticipant";
    ASSERT_FALSE(OmexMetaUtils::isFormattedUri(uri));
}

TEST_F(OmexMetaUtilsTests, TestHasEndingTrue) {
    std::string s = "IAmAStringWithAnEnding.omex";
    ASSERT_TRUE(OmexMetaUtils::endsWith(s, ".omex"));
}

TEST_F(OmexMetaUtilsTests, TestHasEndingFalse) {
    std::string s = "IAmAStringWithAnEndingomex";
    ASSERT_FALSE(OmexMetaUtils::endsWith(s, ".omex"));
}

TEST_F(OmexMetaUtilsTests, TestConfigurePrefixStrings) {
    std::vector<std::string> vec = OmexMetaUtils::configurePrefixStrings(
            "http://omex-library.org/",
            "OmexLibrary.omex/",
            "model.sbml"
    );
    ASSERT_STREQ("http://omex-library.org/", vec[0].c_str());
    ASSERT_STREQ("http://omex-library.org/OmexLibrary.omex/", vec[1].c_str());
    ASSERT_STREQ("http://omex-library.org/OmexLibrary.omex/model.rdf#", vec[2].c_str());
}

TEST_F(OmexMetaUtilsTests, TestAddLocalPrefixToMetaid) {
    std::string actual = OmexMetaUtils::concatMetaIdAndUri("Metaid00001",
                                                           "http://omex-library.org/NewOmex.omex/NewModel.rdf#");
    std::string expected = "http://omex-library.org/NewOmex.omex/NewModel.rdf#Metaid00001";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(OmexMetaUtilsTests, TestAddLocalPrefixToMetaid2) {
    std::string actual = OmexMetaUtils::concatMetaIdAndUri(
            "http://omex-library.org/NewOmex.omex/NewModel.rdf#Metaid00001",
            "http://omex-library.org/NewOmex.omex/NewModel.rdf#");
    std::string expected = "http://omex-library.org/NewOmex.omex/NewModel.rdf#Metaid00001";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(OmexMetaUtilsTests, TestAddLocalPrefixToMetaid3) {
    std::string actual = OmexMetaUtils::concatMetaIdAndUri("#Metaid00001",
                                                           "http://omex-library.org/NewOmex.omex/NewModel.rdf#");
    std::string expected = "http://omex-library.org/NewOmex.omex/NewModel.rdf#Metaid00001";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(OmexMetaUtilsTests, TestStartsWith) {
    std::string s1 = "AString";
    std::string s2 = "A";
    ASSERT_TRUE(OmexMetaUtils::startsWith(s1, s2));
}

TEST_F(OmexMetaUtilsTests, TestStartsWithFail) {
    std::string s1 = "AString";
    std::string s2 = "N";
    ASSERT_FALSE(OmexMetaUtils::startsWith(s1, s2));
}

TEST_F(OmexMetaUtilsTests, TestStringInVector) {
    std::vector<std::string> vec = {
            "A", "B", "C"
    };
    ASSERT_TRUE(OmexMetaUtils::stringInVector(vec, "A"));
    ASSERT_TRUE(OmexMetaUtils::stringInVector(vec, "B"));
    ASSERT_FALSE(OmexMetaUtils::stringInVector(vec, "D"));
}

TEST_F(OmexMetaUtilsTests, TestGenerateMetaids) {
    RDF rdf;
    Editor editor = rdf.toEditor(SBMLFactory::getSBML(SBML_NOT_ANNOTATED2), true, OMEXMETA_TYPE_SBML);

    std::string metaid1 = OmexMetaUtils::generateUniqueMetaid(
            rdf.getModel(),
            "#OmexMetaId"
    );
    // add annotation to the modelw ith the generated metaid
    SingularAnnotation singularAnnotation = editor.newSingularAnnotation();
    singularAnnotation.setAbout(metaid1)
            .setPredicate("bqbiol", "is")
            .setResourceLiteral("FirstAnnotation");
    editor.addSingleAnnotation(singularAnnotation);

    // now try to generate a new metaid. It should not be the same as the first
    std::string metaid2 = OmexMetaUtils::generateUniqueMetaid(
            rdf.getModel(),
            "metaid"
    );
    ASSERT_STREQ("#OmexMetaId0000", metaid1.c_str());
    ASSERT_STREQ("#metaid0000", metaid2.c_str());
}


