//
// Created by Ciaran on 4/22/2020.
//

//
// Created by Ciaran on 4/22/2020.
//

#include <semsim/RDF.h>
#include "gtest/gtest.h"
#include "librdf.h"
#include "semsim/PhysicalEntity.h"
#include "semsim/AnnotationType.h"


class PhysicalPhenomenonTests : public ::testing::Test {

public:

    librdf_world *world;
    raptor_world *raptorWorld;
    librdf_storage *storage;
    librdf_model *model;

    PhysicalPhenomenonTests() {
        auto initializer = semsim::RDF::init();
        world = std::get<0>(initializer);
        raptorWorld = std::get<1>(initializer);
        storage = std::get<2>(initializer);
        model = std::get<3>(initializer);
    };
};


TEST_F(PhysicalPhenomenonTests, TestSubjectStr) {
    semsim::PhysicalPhenomenon phenomenon(
            world,
            semsim::Subject(world, semsim::RDFURINode(world, "metaid004")),
            semsim::PhysicalPropertyResource(world, "OPB:OPB_12345"),
            semsim::PHYSICAL_ENTITY
    );
    std::string expected = "metaid004";
    std::string actual = phenomenon.getSubject().str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PhysicalPhenomenonTests, TestSubjectNodeToStr) {
    semsim::PhysicalPhenomenon phenomenon(
            world,
            semsim::Subject(world, semsim::RDFURINode(world, "metaid004")),
            semsim::PhysicalPropertyResource(world, "OPB:OPB_12345"),
            semsim::PHYSICAL_ENTITY
    );
    std::string expected = "metaid004";
    std::string actual = (const char *) librdf_uri_as_string(
            librdf_node_get_uri(
                    phenomenon.getSubject().toRdfNode()
            )
    );
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PhysicalPhenomenonTests, TestPhysicalProperty) {
    semsim::PhysicalPhenomenon phenomenon(
            world,
            semsim::Subject(world, semsim::RDFURINode(world, "metaid004")),
            semsim::PhysicalPropertyResource(world, "OPB:OPB_12345"),
            semsim::PHYSICAL_ENTITY
    );
    std::string expected = "OPB:OPB_12345";
    std::string actual = phenomenon.getPhysicalProperty().str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}














