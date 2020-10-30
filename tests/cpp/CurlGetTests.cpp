//
// Created by Ciaran on 4/11/2020.
//

#include "gtest/gtest.h"
#include "omexmeta/CurlGet.h"
#include <iostream>
#include <fstream>

class CurlGetTests : public ::testing::Test {
public:
    std::string regular_webpage_url = "https://isocpp.org/wiki/faq/mixing-c-and-cpp";
    std::string omex_file_url = "https://auckland.figshare.com/ndownloader/files/17432333";
    std::string sbml_file_url = "https://www.ebi.ac.uk/biomodels/model/download/BIOMD0000000600.2?filename=BIOMD0000000600_url.xml";
    std::string cellml_file_url = "https://models.cellml.org/workspace/warren_tawhai_crampin_2009/@@rawfile/7a277ddc5b1acbb9c6dde1189df14d614a0be6e7/warren_2010.cellml";

    std::string regular_webpage_filename = "thewebpage.html";
    std::string omex_filename = "theomexfile.omex";
    std::string sbml_filename = "thesbml.sbml";
    std::string cellml_filename = "thecellml.cellml";

    CurlGetTests() = default;

    void TearDown() override {
    };

    static int removeFile(const std::string &filename) {
        if (std::remove(filename.c_str()) != 0)
            perror("File deletion failed");
        else
            std::cout << "File deleted successfully";

        return 0;
    }


    static int getFileSize(const std::string &filename) {
        std::streampos begin, end;
        std::ifstream myfile(filename, std::ios::binary);
        begin = myfile.tellg();
        myfile.seekg(0, std::ios::end);
        end = myfile.tellg();
        myfile.close();
        std::cout << "size is: " << (end - begin) << " bytes.\n";
        return end - begin;
    }

    static void downloadAndCheckSizeRange(std::string url, std::string filename, int expected_size_lower,
                                          int expected_size_higher) {
        omexmeta::CurlGet::download(url, filename);
        int size = getFileSize(filename);
        ASSERT_LE(expected_size_lower, size);
        ASSERT_GE(expected_size_higher, size);
        removeFile(filename);
    }
};

TEST_F(CurlGetTests, TestDownloadHtml) {
    downloadAndCheckSizeRange(regular_webpage_url, regular_webpage_filename,
                              38702 - 1000, 38702 + 1000);
}


TEST_F(CurlGetTests, TestDownloadSBMLFile) {
    downloadAndCheckSizeRange(sbml_file_url, sbml_filename,
                              236281 - 100, 236281 + 100);
}


TEST_F(CurlGetTests, TestDownloadCellML) {
    downloadAndCheckSizeRange(cellml_file_url, cellml_filename,
                              60656 - 100, 60656 + 100);
}








