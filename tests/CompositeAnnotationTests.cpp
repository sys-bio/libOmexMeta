//
// Created by Ciaran on 4/23/2020.
//


#include "gtest/gtest.h"
#include "librdf.h"
#include <semsim/RDF.h>
#include <vector>
#include "semsim/PhysicalEntity.h"

class CompositeAnnotationTests : public ::testing::Test {

public:

    librdf_world *world;
    raptor_world *raptorWorld;
    librdf_storage *storage;
    librdf_model *model;

    semsim::PhysicalPropertyResource physical_property;
    semsim::PhysicalEntity entity;

    CompositeAnnotationTests() {
        auto initializer = semsim::RDF::init();
        world = std::get<0>(initializer);
        raptorWorld = std::get<1>(initializer);
        storage = std::get<2>(initializer);
        model = std::get<3>(initializer);

        physical_property = semsim::PhysicalPropertyResource(
                // chemical concentration
                world, semsim::RDFURINode(world, "OPB:OPB_00340")
        );

        entity = semsim::PhysicalEntity(
                world,
                semsim::Subject(world, semsim::RDFURINode(world, "Entity0")),
                physical_property,
                semsim::Resource(world, semsim::RDFURINode(world, "fake/00001")),
                std::vector<semsim::Resource>({
                                                      semsim::Resource(world, semsim::RDFURINode(world, "fake/00002")),
                                                      semsim::Resource(world, semsim::RDFURINode(world, "fake/00003"))
                                              })

        );
    };
};


TEST_F(CompositeAnnotationTests, test) {


}




















