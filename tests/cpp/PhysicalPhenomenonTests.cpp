//
// Created by Ciaran on 4/22/2020.
//

//
// Created by Ciaran on 4/22/2020.
//

#include "gtest/gtest.h"
#include "librdf.h"
#include "AnnotationSamples.h"
#include "semsim/PhysicalEntity.h"
#include "semsim/AnnotationType.h"

using namespace semsim;

class PhysicalPhenomenonTests : public ::testing::Test {

public:

    AnnotationSamples samples;

    LibrdfStorage storage;
    LibrdfModel model;

    PhysicalPhenomenonTests() {
        model = LibrdfModel(storage.get());
    };
    ~PhysicalPhenomenonTests() override {
        model.freeModel();
        storage.freeStorage();
    };
};

/*
 * todo note that Now the subjec tmetaid is embedded in
 *  the resource, it is probably a good idea to modify the argumetns to physical phenomenon.
 *  and subclasses
 */
TEST_F(PhysicalPhenomenonTests, TestSubjectStr) {
    Subject subject = Subject::fromRawPtr(LibrdfNode::fromUriString("metaid004").get());
    PhysicalProperty resource = PhysicalProperty("metaid004", "OPB:OPB_12345");
    PhysicalPhenomenon phenomenon(
            model.get(),
            subject,
            resource,
            PHYSICAL_ENTITY
    );
    std::string expected = "metaid004";
    std::string actual = phenomenon.getSubject().str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    subject.free();
//    resource.free();
}

TEST_F(PhysicalPhenomenonTests, TestSubjectNodeToStr) {
    Subject subject = Subject::fromRawPtr(LibrdfNode::fromUriString("metaid004").get());
    PhysicalProperty resource = PhysicalProperty("metaid004", "OPB:OPB_12345");
    PhysicalPhenomenon phenomenon(
            model.get(),
            subject,
            resource,
            PHYSICAL_ENTITY
    );
    std::string expected = "metaid004";
    std::string actual = (const char *) librdf_uri_as_string(
            librdf_node_get_uri(
                    phenomenon.getSubject().getNode()
            )
    );
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    subject.free();
//    resource.free();
}

TEST_F(PhysicalPhenomenonTests, TestPhysicalProperty) {
    Subject subject = Subject::fromRawPtr(LibrdfNode::fromUriString("metaid004").get());
    PhysicalProperty resource = PhysicalProperty("metaid004", "OPB:OPB_12345");
    PhysicalPhenomenon phenomenon(
            model.get(),
            subject,
            resource,
            PHYSICAL_ENTITY
    );
    std::string expected = "OPB/OPB_12345";
    std::string actual = phenomenon.getPhysicalProperty().getResourceStr();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    subject.free();
//    resource.free();
}












