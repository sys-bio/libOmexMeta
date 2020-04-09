//
// Created by Ciaran on 4/9/2020.
//

//
// Created by Ciaran on 4/8/2020.
//


#include <semsim/Writer.h>
#include "gtest/gtest.h"
#include "semsim/RDF.h"
#include "semsim/SemSim.h"
#include "AnnotationSamples.h"

class WriterTests : public ::testing::Test {

public:
    AnnoationSamples samples;
    librdf_world *world;
    raptor_world *raptor_world_ptr;
    librdf_storage *storage;
    librdf_model *model;


    WriterTests() {
        world = librdf_new_world();
        librdf_world_open(world);
        raptor_world_ptr = librdf_world_get_raptor(world);
        storage = librdf_new_storage(world, "memory", "semsim_store", nullptr);
        if (!storage) {
            throw std::invalid_argument("Failed to create new storage\n");
        }
        model = librdf_new_model(world, storage, nullptr);
        if (!model) {
            throw std::invalid_argument("Failed to create model\n");
        }

    };

};


TEST_F(WriterTests, TestDefaultConstructor) {
    semsim::Writer writer(world, model, "rdfxml");
    ASSERT_TRUE(true); // test passes if it gets this far.
}


TEST_F(WriterTests, TestDefaultConstructor2) {
    semsim::RDF rdfModel;
    rdfModel.fromString(samples.sample_annotation1);
    rdfModel.toString("rdfxml");
}


TEST_F(WriterTests, TestThatMakeSerializerFunctionBreaksWithWrongFormatArgument) {

}











