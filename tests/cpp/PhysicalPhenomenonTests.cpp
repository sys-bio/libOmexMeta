//
// Created by Ciaran on 4/22/2020.
//

//
// Created by Ciaran on 4/22/2020.
//

#include "gtest/gtest.h"
#include "librdf.h"
#include "AnnotationSamples.h"
#include "omexmeta/PhysicalEntity.h"
#include "omexmeta/AnnotationType.h"

using namespace omexmeta;

class PhysicalPhenomenonTests : public ::testing::Test {

public:

    AnnotationSamples samples;

    LibrdfStorage storage;
    LibrdfModel model;
    std::string model_uri = "http://omex-library.org/NewOmex.omex/NewModel.xml#";
    std::string local_uri = "http://omex-library.org/NewOmex.omex/NewModel.rdf#";

    PhysicalPhenomenonTests() {
        model = LibrdfModel(storage.get());
    };
    ~PhysicalPhenomenonTests() override {
        model.freeModel();
        storage.freeStorage();
    };
};


TEST_F(PhysicalPhenomenonTests, TestSubjectStr) {
    Subject subject = Subject::fromRawPtr(LibrdfNode::fromUriString("metaid004").get());
    PhysicalProperty resource = PhysicalProperty("metaid004", "OPB:OPB_12345", model_uri);
    PhysicalPhenomenon phenomenon(
            model.get(),
            model_uri,
            local_uri,
            resource,
            PHYSICAL_ENTITY
    );
    std::string expected = "http://omex-library.org/NewOmex.omex/NewModel.rdf#metaid004";
    std::string actual = phenomenon.getSubjectStr();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    subject.free();
}

TEST_F(PhysicalPhenomenonTests, TestSubjectNodeToStr) {
    Subject subject = Subject::fromRawPtr(LibrdfNode::fromUriString("metaid004").get());
    PhysicalProperty resource = PhysicalProperty("metaid004", "OPB:OPB_12345", local_uri);
    PhysicalPhenomenon phenomenon(
            model.get(),
            model_uri,
            local_uri,
            resource,
            PHYSICAL_ENTITY
    );
    std::string expected = "http://omex-library.org/NewOmex.omex/NewModel.rdf#metaid004";
    std::string actual = phenomenon.getSubjectStr();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    subject.free();
}

TEST_F(PhysicalPhenomenonTests, TestPhysicalProperty) {
    /*
     * todo Weak test - improve
     */
    Subject subject = Subject::fromRawPtr(LibrdfNode::fromUriString("metaid004").get());
    PhysicalProperty resource = PhysicalProperty("metaid", "OPB:OPB_12345", local_uri);
    PhysicalPhenomenon phenomenon(
            model.get(),
            model_uri,
            local_uri,
            resource,
            PHYSICAL_ENTITY
    );
    std::string expected = "OPB:OPB_12345";
    std::string actual = phenomenon.getPhysicalProperty().getResourceStr();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    subject.free();
}












