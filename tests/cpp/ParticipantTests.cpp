//
// Created by Ciaran on 4/19/2020.
//

#include "gtest/gtest.h"
#include "librdf.h"
#include "semsim/RDF.h"
#include "semsim/Participant.h"
#include "semsim/SemSim.h"

class ParticipantTests : public ::testing::Test {

public:

    librdf_world *world;
    raptor_world *raptorWorld;
    librdf_storage *storage;
    librdf_model *model;

    ParticipantTests() {
        auto initializer = semsim::RDF::init();
        world = std::get<0>(initializer);
        raptorWorld = std::get<1>(initializer);
        storage = std::get<2>(initializer);
        model = std::get<3>(initializer);
    };
};


TEST_F(ParticipantTests, TestSinkParticipant1) {
    semsim::SinkParticipant sink(world, model, "MetaId0014",
                                 1.0, "MetaId0015"
    );
    std::string actual = sink.getPredicatePtr()->str();
    std::cout << actual << std::endl;
    std::string expected = "http://www.bhi.washington.edu/semsim#hasSinkParticipant";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(ParticipantTests, TestParticipantVec1) {
    semsim::MediatorParticipant mediator(
            world, model, "MetaId0014",
            "MetaId0015"
    );

    semsim::SourceParticipant source(
            world, model, "MetaId0014",
            1.0, "MetaId0015"
    );

    semsim::SinkParticipant sink(
            world, model,
            "MetaId0014",
            1.0, "MetaId0015"
    );

    std::vector<semsim::ParticipantPtr> participants = {
            std::make_shared<semsim::Participant>(source),
            std::make_shared<semsim::Participant>(mediator),
            std::make_shared<semsim::Participant>(sink)
    };

    ASSERT_EQ(3, participants.size());
}


TEST_F(ParticipantTests, TestParticipantVecToTriples) {
    semsim::MediatorParticipant mediator(
            world, model, "MetaId0014",
            "MetaId0015"
    );

    semsim::SourceParticipant source(
            world, model, "MetaId0014",
            1.0, "MetaId0015"
    );

    semsim::SinkParticipant sink(
            world, model,
            "MetaId0014",
            1.0, "MetaId0015"
    );

    std::vector<semsim::ParticipantPtr> participants = {
            std::make_shared<semsim::Participant>(source),
            std::make_shared<semsim::Participant>(mediator),
            std::make_shared<semsim::Participant>(sink)
    };

    std::vector<semsim::Triple> triples;
    for (auto &i : participants) {
        for (auto &j : i->toTriples("metaid")) {
            triples.push_back(j);
        }
    }
    ASSERT_EQ(8, triples.size());
}









