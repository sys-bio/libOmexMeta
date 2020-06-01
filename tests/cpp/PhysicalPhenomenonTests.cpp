//
// Created by Ciaran on 4/22/2020.
//

//
// Created by Ciaran on 4/22/2020.
//

#include <semsim/_RDF.h>
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
        model = LibrdfModel(storage);
    };
};


TEST_F(PhysicalPhenomenonTests, TestSubjectStr) {
    PhysicalPhenomenon phenomenon(
            model,
            Subject::fromRawPtr(LibrdfNode::fromUriString("metaid004")),
            PhysicalPropertyResource("OPB:OPB_12345"),
            PHYSICAL_ENTITY
    );
    std::string expected = "metaid004";
    std::string actual = phenomenon.getSubject().str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PhysicalPhenomenonTests, TestSubjectNodeToStr) {
    PhysicalPhenomenon phenomenon(
            model,
            Subject::fromRawPtr(LibrdfNode::fromUriString("metaid004")),
            PhysicalPropertyResource("OPB:OPB_12345"),
            PHYSICAL_ENTITY
    );
    std::string expected = "metaid004";
    std::string actual = (const char *) librdf_uri_as_string(
            librdf_node_get_uri(
                    phenomenon.getSubject().getNode()
            )
    );
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PhysicalPhenomenonTests, TestPhysicalProperty) {
    PhysicalPhenomenon phenomenon(
            model,
            Subject::fromRawPtr(LibrdfNode::fromUriString("metaid004")),
            PhysicalPropertyResource("OPB:OPB_12345"),
            PHYSICAL_ENTITY
    );
    std::string expected = "https://identifiers.org/OPB/OPB_12345";
    std::string actual = phenomenon.getPhysicalProperty().str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}












