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
    semsim::CurlGet::download(samples.sbml_url1, samples.sbml_filename1);
    ASSERT_TRUE(semsim::SemsimUtils::exists(samples.sbml_filename1));
}

TEST_F(SemsimUtilsTests, TestFileDoesNotExists) {
    ASSERT_FALSE(semsim::SemsimUtils::exists("./CheeseBiscuits.cheddar"));
}

TEST_F(SemsimUtilsTests, TestDeleteFile) {
    semsim::CurlGet::download(samples.sbml_url1, samples.sbml_filename1);
    assert(semsim::SemsimUtils::exists(samples.sbml_filename1));
    semsim::SemsimUtils::removeFile(samples.sbml_filename1);
    ASSERT_FALSE(semsim::SemsimUtils::exists(samples.sbml_filename1));
}

TEST_F(SemsimUtilsTests, TestRemoveIfExists) {
    semsim::CurlGet::download(samples.sbml_url1, samples.sbml_filename1);
    assert(semsim::SemsimUtils::exists(samples.sbml_filename1));
    semsim::SemsimUtils::removeIfExists(samples.sbml_filename1);
    ASSERT_FALSE(semsim::SemsimUtils::exists(samples.sbml_filename1));
}

TEST_F(SemsimUtilsTests, TestRemoveIfExists2) {
    std::string fname = "./cheese_biscuits.blue";
    semsim::SemsimUtils::removeIfExists(fname); // should not error
    ASSERT_FALSE(semsim::SemsimUtils::exists(fname));
}

TEST_F(SemsimUtilsTests, TestPrefixFile) {
    std::string fname = "./cheese_biscuits.blue";
    fname = semsim::SemsimUtils::addFilePrefixToString(fname);
    std::string expected = "file://./cheese_biscuits.blue";
    std::string actual = fname;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}
