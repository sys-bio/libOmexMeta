//
// Created by Ciaran on 02/08/2021.
//

#include "omexmeta/OmexMeta.h"
#include <filesystem>
#include <gtest/gtest.h>

using namespace omexmeta;

class CheckBiomodelsTests : public ::testing::Test {
public:
    std::string biomodels_tmpdir = R"(D:\temp-biomodels\final)";
    std::vector<std::string> brokenFiles;

    CheckBiomodelsTests() {
        brokenFiles = std::vector<std::string>(
                {"BIOMD0000000094/BIOMD0000000094_url_newest_celldesigner_export.xml",
                 "BIOMD0000000220/BIOMD0000000220_url_newest_celldesigner_export.xml",
                 "BIOMD0000000094/BIOMD0000000094_url.xml",
                 "BIOMD0000000192/BIOMD0000000192_url.xml",
                 "BIOMD0000000220/BIOMD0000000220_url.xml",
                 "BIOMD0000000226/BIOMD0000000226_url.xml",
                 "BIOMD0000000227/BIOMD0000000227_url.xml",
                 "BIOMD0000000394/BIOMD0000000394_url.xml",
                 "BIOMD0000000395/BIOMD0000000395_url.xml",
                 "BIOMD0000000396/BIOMD0000000396_url.xml",
                 "BIOMD0000000397/BIOMD0000000397_url.xml",
                 "BIOMD0000000398/BIOMD0000000398_url.xml",
                 "BIOMD0000000436/BIOMD0000000436_url.xml"});
        for (auto &fname : brokenFiles) {
            fname = (std::filesystem::path(biomodels_tmpdir) / fname).string();
            if (!std::filesystem::exists(fname)) {
                throw std::invalid_argument("no file named: \"" + fname + "\"");
            }
        }
    };
};

// requires local files to run so disabled. Will be deleted soon
TEST_F(CheckBiomodelsTests, DISABLED_f11) {

    for (const auto &fname : brokenFiles) {
        try {
            RDF rdf = RDF::fromFile(fname, "rdfxml");
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
            continue;
        }
    }

    //    std::cout << rdf.toString("turtle") << std::endl;
}

// requires local files to run so disabled. Will be deleted soon
TEST_F(CheckBiomodelsTests, DISABLED_f2) {
    RDF rdf = RDF::fromFile(brokenFiles[2], "rdfxml");

    std::cout << rdf.toString("turtle") << std::endl;
}