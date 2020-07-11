//
// Created by Ciaran on 11/07/2020.
//

#include "gtest/gtest.h"
#include "RedlandAPIWrapper.h"
#include "omexmeta/PersonalInformation.h"

using namespace omexmeta;

class PersonalInformationTests : public ::testing::Test {
public:

    redland::LibrdfStorage storage;
    redland::LibrdfModel model;

    std::string local_uri = "http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#";

    PersonalInformationTests() {
        model = redland::LibrdfModel(storage.get());
    }

    ~PersonalInformationTests() override {
        model.freeModel();
        storage.freeStorage();
    }
};

TEST_F(PersonalInformationTests, test){
//    PersonalInformation information(model.get(), local_uri);
}



















































