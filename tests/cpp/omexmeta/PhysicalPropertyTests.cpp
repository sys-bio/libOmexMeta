//
// Created by Ciaran on 4/22/2020.
//


#include "omexmeta/PhysicalProperty.h"
#include "omexmeta/Triple.h"
#include "gtest/gtest.h"
#include <omexmeta/RDF.h>

using namespace omexmeta;


class PhysicalPropertyTests : public ::testing::Test {
public:

    LibrdfStorage storage;
    LibrdfModel model;

    UriHandler uriHandler;

    PhysicalPropertyTests() {
        model = LibrdfModel(storage.get());
    }

    ~PhysicalPropertyTests() override {
        model.freeModel();
        storage.freeStorage();
    }
};


TEST_F(PhysicalPropertyTests, TestPhysicalProperty) {
    PhysicalProperty physicalProperty(model.get(), uriHandler);
    physicalProperty.about("species0000", MODEL_URI)
            .isVersionOf("opb/OPB_12345")
            .isPropertyOf("entity0", MODEL_URI);
    Triples triples = physicalProperty.toTriples();

    ASSERT_STREQ("http://omex-library.org/NewOmex.omex/NewModel.xml#species0000", physicalProperty.getAbout().c_str());
    ASSERT_STREQ("http://omex-library.org/NewOmex.omex/NewModel.xml#entity0", physicalProperty.getIsPropertyOfValue().c_str());
    ASSERT_STREQ("opb/OPB_12345", physicalProperty.getIsVersionOfValue().c_str());
}
TEST_F(PhysicalPropertyTests, TestPhysicalPropertyAutoGenerateAbout) {
    PhysicalProperty physicalProperty(model.get(), uriHandler);
    physicalProperty
            .isVersionOf("opb/OPB_12345")
            .isPropertyOf("entity0", MODEL_URI);

    //the call to toTriples is the cue to do any autogeneration that is needed.
    Triples triples = physicalProperty.toTriples();

    ASSERT_STREQ("http://omex-library.org/NewOmex.omex/NewModel.rdf#Property0000", physicalProperty.getAbout().c_str());
    ASSERT_STREQ("http://omex-library.org/NewOmex.omex/NewModel.xml#entity0", physicalProperty.getIsPropertyOfValue().c_str());
    ASSERT_STREQ("opb/OPB_12345", physicalProperty.getIsVersionOfValue().c_str());
}
TEST_F(PhysicalPropertyTests, TestEquality) {
    PhysicalProperty physicalProperty1(model.get(), uriHandler);
    PhysicalProperty physicalProperty2(model.get(), uriHandler);
    physicalProperty1.about("sub", MODEL_URI).isVersionOf("OPB/OPB_1234");
    physicalProperty2.about("sub", MODEL_URI).isVersionOf("OPB/OPB_1234");
    ASSERT_EQ(physicalProperty1, physicalProperty2);
}

TEST_F(PhysicalPropertyTests, TestInequality) {
    PhysicalProperty physicalProperty1(model.get(), uriHandler);
    PhysicalProperty physicalProperty2(model.get(), uriHandler);
    physicalProperty1.about("sub1", MODEL_URI).isVersionOf("OPB/OPB_1234");
    physicalProperty2.about("sub2", MODEL_URI).isVersionOf("OPB/OPB_1234");
    ASSERT_NE(physicalProperty1, physicalProperty2);
}


TEST_F(PhysicalPropertyTests, OptionalProperty) {
    PhysicalProperty physicalProperty(model.get(), uriHandler);
    physicalProperty.about("property_metaid_0", LOCAL_URI);
    Triples triples = physicalProperty.toTriples();
    ASSERT_EQ(1, triples.size());

}




















