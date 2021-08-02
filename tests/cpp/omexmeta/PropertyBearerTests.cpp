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

class PhysicalPropertyBearerTests : public ::testing::Test {

public:
    AnnotationSamples samples;

    LibrdfStorage storage;
    LibrdfModel model;
    UriHandler uriHandler;

    PhysicalPropertyBearerTests() {
        model = LibrdfModel(storage);
    };
    ~PhysicalPropertyBearerTests() override {
        model.freeModel();
        storage.freeStorage();
    };
};


TEST_F(PhysicalPropertyBearerTests, TestSubjectStr) {
    LibrdfNode subject = LibrdfNode::fromUriString("metaid004");
    PhysicalProperty resource = PhysicalProperty(model.get(), uriHandler).about("metaid004").isVersionOf("OPB:OPB_12345");
    PropertyBearer propertyBearer(
            model.get(),
            uriHandler,
            resource,
            PHYSICAL_ENTITY);
    std::string expected = "metaid004";
    std::string actual = propertyBearer.getPropertyAbout();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    subject.freeNode();
}

TEST_F(PhysicalPropertyBearerTests, TestSubjectNodeToStr) {
    LibrdfNode subject = LibrdfNode::fromUriString("metaid004");
    PhysicalProperty resource = PhysicalProperty(model.get(), uriHandler).about("metaid004").isVersionOf("OPB:OPB_12345");
    PropertyBearer propertyBearer(
            model.get(),
            uriHandler,
            resource,
            PHYSICAL_ENTITY);
    std::string expected = "metaid004";
    std::string actual = propertyBearer.getPropertyAbout();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    subject.freeNode();
}