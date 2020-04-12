//
// Created by Ciaran on 4/11/2020.
//

#include <string>
#include "gtest/gtest.h"
#include "semsim/CombineArchive.h"

class RDFTestsCombine : public ::testing::Test {
public:
    std::string gold_standard_url1 = "https://auckland.figshare.com/ndownloader/files/17432333";
    std::string gold_standard_url2 = "https://auckland.figshare.com/ndownloader/files/15425522";
    std::string gold_standard_url3 = "https://auckland.figshare.com/ndownloader/files/15425513";
    std::string gold_standard_url4 = "https://auckland.figshare.com/ndownloader/files/15425546";
    std::string gold_standard_url5 = "https://auckland.figshare.com/ndownloader/files/17432366";

    RDFTestsCombine() {

    }
};

TEST_F(RDFTestsCombine, tesnakjsbt) {
    CombineArchive combineArchive(gold_standard_url1);

}