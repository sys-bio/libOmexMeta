//
// Created by Ciaran on 4/15/2020.
//

#include <semsim/Triple.h>
#include "gtest/gtest.h"

class TripleListTests : public ::testing::Test {

public:


    std::string subject_str = "./MyModel#metaid_0";
    std::string subject_str1 = "./MyModel#metaid_1";
    std::string subject_str2 = "./MyModel#metaid_2";
    std::string predicate_str = "http://biomodels.net/biology-qualifiers/is";
    std::string resource_str1 = "uniprot:P0DP23";
    std::string resource_str2 = "uniprot:P0DP24";
    std::string resource_str3 = "uniprot:P0DP25";

    semsim::Triple triple1;
    semsim::Triple triple2;
    semsim::Triple triple3;


    TripleListTests() {
        triple1 = semsim::Triple(
                semsim::Subject(subject_str),
                semsim::BiomodelsQualifier("is"),
                semsim::Resource(resource_str1)
        );


    };
};


