//
// Created by Ciaran on 4/22/2020.
//

//
// Created by Ciaran on 4/22/2020.
//

#include "AnnotationSamples.h"
#include "librdf.h"
#include "omexmeta/AnnotationType.h"
#include "omexmeta/PhysicalEntity.h"
#include "gtest/gtest.h"

using namespace omexmeta;

class PhysicalPhenomenonTests : public ::testing::Test {

public:
    AnnotationSamples samples;

    LibrdfStorage storage;
    LibrdfModel model;
    UriHandler uriHandler;

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
    PhysicalProperty resource = PhysicalProperty(model.get(), uriHandler).about("metaid004").isVersionOf("OPB:OPB_12345");
    PropertyBearer phenomenon(
            model.get(),
            uriHandler,
            resource,
            PHYSICAL_ENTITY);
    std::string expected = "metaid004";
    std::string actual = phenomenon.getSubjectStr();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    subject.free();
}

TEST_F(PhysicalPhenomenonTests, TestSubjectNodeToStr) {
    Subject subject = Subject::fromRawPtr(LibrdfNode::fromUriString("metaid004").get());
    PhysicalProperty resource = PhysicalProperty(model.get(), uriHandler).about("metaid004").isVersionOf("OPB:OPB_12345");
    PropertyBearer phenomenon(
            model.get(),
            uriHandler,
            resource,
            PHYSICAL_ENTITY);
    std::string expected = "metaid004";
    std::string actual = phenomenon.getSubjectStr();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    subject.free();
}