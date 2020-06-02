//
// Created by Ciaran on 4/19/2020.
//

#include "gtest/gtest.h"
#include "librdf.h"
#include "semsim/RDF.h"
#include "semsim/Participant.h"

using namespace semsim;

class ParticipantTests : public ::testing::Test {

public:

    LibrdfStorage storage;
    LibrdfModel model;

    ParticipantTests() {
        model = LibrdfModel(storage);
    };
};


TEST_F(ParticipantTests, TestSinkParticipant1) {
    SinkParticipant sink(model, "MetaId0014",
                         1.0, "MetaId0015"
    );
    std::string actual = sink.getPredicatePtr()->str();
    std::cout << actual << std::endl;
    std::string expected = "http://www.bhi.washington.edu/semsim#hasSinkParticipant";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(ParticipantTests, TestToTriples1) {
    SinkParticipant sink(model, "MetaId0014",
                         1.0, "MetaId0015"
    );
    std::ostringstream os;
    Triples triples = sink.toTriples("metaid");
    for (auto &it: triples){
        os << it->getAbout();
    }
    std::string actual = os.str();
    std::cout << actual << std::endl;
    std::string expected = "http://www.bhi.washington.edu/semsim#hasSinkParticipant";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(ParticipantTests, TestParticipantVec1) {
    MediatorParticipant mediator(
            model, "MetaId0014",
            "MetaId0015"
    );

    SourceParticipant source(
            model, "MetaId0014",
            1.0, "MetaId0015"
    );

    SinkParticipant sink(
            model,
            "MetaId0014",
            1.0, "MetaId0015"
    );

    std::vector<Participant *> participants = {
            &source,
            &mediator,
            &sink
    };

    ASSERT_EQ(3, participants.size());
}


TEST_F(ParticipantTests, TestParticipantVecToTriples) {
    MediatorParticipant mediator(
            model, "MetaId0014",
            "MetaId0015"
    );

    SourceParticipant source(
            model, "MetaId0014",
            1.0, "MetaId0015"
    );

    SinkParticipant sink(
            model,
            "MetaId0014",
            1.0, "MetaId0015"
    );

    std::vector<Participant *> participants = {
            &source,
            &mediator,
            &sink
    };

    std::vector<Triple> triples;
    for (auto &i: participants) {
        for (auto &j: i->toTriples("metaid")) {
            triples.push_back(std::move(*j));
        }
    }
    ASSERT_EQ(8, triples.size());
}









