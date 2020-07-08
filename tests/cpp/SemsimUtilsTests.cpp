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

    std::string fname = std::filesystem::current_path() /= "cheese_biscuits.blue";
    fname = omexmeta::SemsimUtils::addFilePrefixToString(fname);

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
