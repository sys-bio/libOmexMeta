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
    ASSERT_TRUE(omexmeta::SemsimUtils::exists(samples.sbml_filename1));
}

TEST_F(SemsimUtilsTests, TestFileDoesNotExists) {
    ASSERT_FALSE(omexmeta::SemsimUtils::exists("./CheeseBiscuits.cheddar"));
}

TEST_F(SemsimUtilsTests, TestDeleteFile) {
    omexmeta::CurlGet::download(samples.sbml_url1, samples.sbml_filename1);
    assert(omexmeta::SemsimUtils::exists(samples.sbml_filename1));
    omexmeta::SemsimUtils::removeFile(samples.sbml_filename1);
    ASSERT_FALSE(omexmeta::SemsimUtils::exists(samples.sbml_filename1));
}

TEST_F(SemsimUtilsTests, TestRemoveIfExists) {
    omexmeta::CurlGet::download(samples.sbml_url1, samples.sbml_filename1);
    assert(omexmeta::SemsimUtils::exists(samples.sbml_filename1));
    omexmeta::SemsimUtils::removeIfExists(samples.sbml_filename1);
    ASSERT_FALSE(omexmeta::SemsimUtils::exists(samples.sbml_filename1));
}

TEST_F(SemsimUtilsTests, TestRemoveIfExists2) {
    std::string fname = "./cheese_biscuits.blue";
    omexmeta::SemsimUtils::removeIfExists(fname); // should not error
    ASSERT_FALSE(omexmeta::SemsimUtils::exists(fname));
}

TEST_F(SemsimUtilsTests, TestPrefixFile) {

    std::string fname = (std::filesystem::current_path() /= "cheese_biscuits.blue").string();
    fname = omexmeta::SemsimUtils::prepareBaseUri(fname);

//    std::string expected = "file://" + fname;
    std::string expected = fname;
    ASSERT_STREQ(expected.c_str(), fname.c_str());
}

TEST_F(SemsimUtilsTests, TestGEtNamespacesFromUri) {
    std::string uri = "http://uri.com/identifiers/PD1234";
    std::string expected = "http://uri.com/identifiers/";
    std::string actual = omexmeta::SemsimUtils::getNamespaceFromUri(uri);
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(SemsimUtilsTests, TestGEtNamespacesFromUriSemsim) {
    std::string uri = "http://www.bhi.washington.edu/semsim#hasSourceParticipant";
    std::string expected = "http://www.bhi.washington.edu/semsim#";
    std::string actual = omexmeta::SemsimUtils::getNamespaceFromUri(uri);
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(SemsimUtilsTests, TestIsFormattedUri1) {
    std::string uri = "http://www.bhi.washington.edu/semsim#hasSourceParticipant";
    ASSERT_TRUE(omexmeta::SemsimUtils::isFormattedUri(uri));
}

TEST_F(SemsimUtilsTests, TestIsFormattedUri2) {
    std::string uri = "https://www.bhi.washington.edu/semsim#hasSourceParticipant";
    ASSERT_TRUE(omexmeta::SemsimUtils::isFormattedUri(uri));
}

TEST_F(SemsimUtilsTests, TestIsFormattedUri3) {
    std::string uri = "file://www.bhi.washington.edu/semsim#hasSourceParticipant";
    ASSERT_TRUE(omexmeta::SemsimUtils::isFormattedUri(uri));
}

TEST_F(SemsimUtilsTests, TestIsFormattedUri4) {
    std::string uri = "hasSourceParticipant";
    ASSERT_FALSE(omexmeta::SemsimUtils::isFormattedUri(uri));
}

TEST_F(SemsimUtilsTests, TestHasEndingTrue) {
    std::string s = "IAmAStringWithAnEnding.omex";
    ASSERT_TRUE(omexmeta::SemsimUtils::hasEnding(s, ".omex"));
}

TEST_F(SemsimUtilsTests, TestHasEndingFalse) {
    std::string s = "IAmAStringWithAnEndingomex";
    ASSERT_FALSE(omexmeta::SemsimUtils::hasEnding(s, ".omex"));
}

TEST_F(SemsimUtilsTests, configureSelfStrings) {
    std::vector<std::string> vec = omexmeta::SemsimUtils::configureSelfStrings("OmexLibrary.omex", "model.sbml");
    ASSERT_STREQ("http://MyOmexLibrary.org/OmexLibrary.omex", vec[0].c_str());
    ASSERT_STREQ("http://MyOmexLibrary.org/OmexLibrary.omex/model.sbml", vec[1].c_str());
    ASSERT_STREQ("http://MyOmexLibrary.org/OmexLibrary.omex/model.rdf#", vec[2].c_str());
}
