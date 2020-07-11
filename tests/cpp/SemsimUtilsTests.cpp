//
// Created by Ciaran on 4/13/2020.
//
#include "gtest/gtest.h"
#include "iostream"
#include "AnnotationSamples.h"

class SemsimUtilsTests : public ::testing::Test {
public:

    AnnotationSamples samples;

    SemsimUtilsTests() = default;

};

TEST_F(SemsimUtilsTests, TestFileExists) {
    // we first download
    omexmeta::CurlGet::download(samples.sbml_url1, samples.sbml_filename1);
    ASSERT_TRUE(omexmeta::OmexMetaUtils::exists(samples.sbml_filename1));
}

TEST_F(SemsimUtilsTests, TestFileDoesNotExists) {
    ASSERT_FALSE(omexmeta::OmexMetaUtils::exists("./CheeseBiscuits.cheddar"));
}

TEST_F(SemsimUtilsTests, TestDeleteFile) {
    omexmeta::CurlGet::download(samples.sbml_url1, samples.sbml_filename1);
    assert(omexmeta::OmexMetaUtils::exists(samples.sbml_filename1));
    omexmeta::OmexMetaUtils::removeFile(samples.sbml_filename1);
    ASSERT_FALSE(omexmeta::OmexMetaUtils::exists(samples.sbml_filename1));
}

TEST_F(SemsimUtilsTests, TestRemoveIfExists) {
    omexmeta::CurlGet::download(samples.sbml_url1, samples.sbml_filename1);
    assert(omexmeta::OmexMetaUtils::exists(samples.sbml_filename1));
    omexmeta::OmexMetaUtils::removeIfExists(samples.sbml_filename1);
    ASSERT_FALSE(omexmeta::OmexMetaUtils::exists(samples.sbml_filename1));
}

TEST_F(SemsimUtilsTests, TestRemoveIfExists2) {
    std::string fname = "./cheese_biscuits.blue";
    omexmeta::OmexMetaUtils::removeIfExists(fname); // should not error
    ASSERT_FALSE(omexmeta::OmexMetaUtils::exists(fname));
}

TEST_F(SemsimUtilsTests, TestPrefixFile) {

    std::string fname = (std::filesystem::current_path() /= "cheese_biscuits.blue").string();
    fname = omexmeta::OmexMetaUtils::prepareBaseUri(fname);

//    std::string expected = "file://" + fname;
    std::string expected = fname;
    ASSERT_STREQ(expected.c_str(), fname.c_str());
}

TEST_F(SemsimUtilsTests, TestGEtNamespacesFromUri) {
    std::string uri = "http://uri.com/identifiers/PD1234";
    std::string expected = "http://uri.com/identifiers/";
    std::string actual = omexmeta::OmexMetaUtils::getNamespaceFromUri(uri);
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(SemsimUtilsTests, TestGEtNamespacesFromUriSemsim) {
    std::string uri = "http://www.bhi.washington.edu/semsim#hasSourceParticipant";
    std::string expected = "http://www.bhi.washington.edu/semsim#";
    std::string actual = omexmeta::OmexMetaUtils::getNamespaceFromUri(uri);
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(SemsimUtilsTests, TestIsFormattedUri1) {
    std::string uri = "http://www.bhi.washington.edu/semsim#hasSourceParticipant";
    ASSERT_TRUE(omexmeta::OmexMetaUtils::isFormattedUri(uri));
}

TEST_F(SemsimUtilsTests, TestIsFormattedUri2) {
    std::string uri = "https://www.bhi.washington.edu/semsim#hasSourceParticipant";
    ASSERT_TRUE(omexmeta::OmexMetaUtils::isFormattedUri(uri));
}

TEST_F(SemsimUtilsTests, TestIsFormattedUri3) {
    std::string uri = "file://www.bhi.washington.edu/semsim#hasSourceParticipant";
    ASSERT_TRUE(omexmeta::OmexMetaUtils::isFormattedUri(uri));
}

TEST_F(SemsimUtilsTests, TestIsFormattedUri4) {
    std::string uri = "hasSourceParticipant";
    ASSERT_FALSE(omexmeta::OmexMetaUtils::isFormattedUri(uri));
}

TEST_F(SemsimUtilsTests, TestHasEndingTrue) {
    std::string s = "IAmAStringWithAnEnding.omex";
    ASSERT_TRUE(omexmeta::OmexMetaUtils::stringHasEnding(s, ".omex"));
}

TEST_F(SemsimUtilsTests, TestHasEndingFalse) {
    std::string s = "IAmAStringWithAnEndingomex";
    ASSERT_FALSE(omexmeta::OmexMetaUtils::stringHasEnding(s, ".omex"));
}

TEST_F(SemsimUtilsTests, configureSelfStrings) {
    std::vector<std::string> vec = omexmeta::OmexMetaUtils::configureSelfStrings("OmexLibrary.omex", "model.sbml");
    ASSERT_STREQ("http://MyOmexLibrary.org/OmexLibrary.omex", vec[0].c_str());
    ASSERT_STREQ("http://MyOmexLibrary.org/OmexLibrary.omex/model.sbml", vec[1].c_str());
    ASSERT_STREQ("http://MyOmexLibrary.org/OmexLibrary.omex/model.rdf#", vec[2].c_str());
}

TEST_F(SemsimUtilsTests, TestAddLocalPrefixToMetaid) {
    std::string actual = omexmeta::OmexMetaUtils::addLocalPrefixToMetaid("Metaid00001", "http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#");
    std::string expected = "http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#Metaid00001";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(SemsimUtilsTests, TestAddLocalPrefixToMetaid2) {
    std::string actual = omexmeta::OmexMetaUtils::addLocalPrefixToMetaid("http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#Metaid00001", "http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#");
    std::string expected = "http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#Metaid00001";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(SemsimUtilsTests, TestAddLocalPrefixToMetaid3) {
    std::string actual = omexmeta::OmexMetaUtils::addLocalPrefixToMetaid("#Metaid00001", "http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#");
    std::string expected = "http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#Metaid00001";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


