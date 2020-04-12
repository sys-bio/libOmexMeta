//
// Created by Ciaran on 4/11/2020.
//

#include <string>
#include "gtest/gtest.h"
#include "semsim/SemsimCombineArchive.h"
#include "semsim/CurlGet.h"

class RDFTestsCombine : public ::testing::Test {
public:
    std::string gold_standard_url1 = "https://auckland.figshare.com/ndownloader/files/17432333";
    std::string gold_standard_url2 = "https://auckland.figshare.com/ndownloader/files/15425522";
    std::string gold_standard_url3 = "https://auckland.figshare.com/ndownloader/files/15425513";
    std::string gold_standard_url4 = "https://auckland.figshare.com/ndownloader/files/15425546";
    std::string gold_standard_url5 = "https://auckland.figshare.com/ndownloader/files/17432366";

    std::string gold_standard_filename1 = "goldstandard1.omex";
    std::string gold_standard_filename2 = "goldstandard2.omex";
    std::string gold_standard_filename3 = "goldstandard3.omex";
    std::string gold_standard_filename4 = "goldstandard4.omex";
    std::string gold_standard_filename5 = "goldstandard5.omex";

    RDFTestsCombine() {
        semsim::CurlGet::download(gold_standard_url1, gold_standard_filename1);
    }

    static int removeFile(const std::string &filename) {
        if (std::remove(filename.c_str()) != 0)
            perror("File deletion failed");
        else
            std::cout << "File deleted successfully";
        return 0;
    }

    void TearDown() override {
//        removeFile(gold_standard_filename1);
    }
};

TEST_F(RDFTestsCombine, TestThatUrlIsNotFile) {
    semsim::SemsimCombineArchive combineArchive(gold_standard_url1);
    std::string o = "/mnt/d/libsemsim/tests/gold_standard1.omex";
    combineArchive.fromUrl(o);


//    ASSERT_FALSE(combineArchive.isfile());

}























