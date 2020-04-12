//
// Created by Ciaran on 4/11/2020.
//

#include "gtest/gtest.h"
#include "semsim/CurlGet.h"
#include "semsim/SemSim.h"
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
        removeFile(regular_webpage_filename);
        removeFile(omex_filename);
    };

    static int removeFile(std::string filename) {
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

    static void downloadAndCheckSize(std::string url, std::string filename, int expected_size) {
        //38kb
        semsim::CurlGet::download(url, filename);
        int size = getFileSize(filename);
        ASSERT_EQ(expected_size, size);
        removeFile(filename);
    }
};

TEST_F(CurlGetTests, TestDownloadHtml) {
    //38kb
    downloadAndCheckSize(regular_webpage_url, regular_webpage_filename, 38858);
}

TEST_F(CurlGetTests, TestDownloadOmexFile) {
    downloadAndCheckSize(omex_file_url, omex_filename, 4726);
}


TEST_F(CurlGetTests, TestDownloadSBMLFile) {
    downloadAndCheckSize(sbml_file_url, sbml_filename, 236281);
}


TEST_F(CurlGetTests, TestDownloadCellML) {
    downloadAndCheckSize(cellml_file_url, cellml_filename, 60656);
}








