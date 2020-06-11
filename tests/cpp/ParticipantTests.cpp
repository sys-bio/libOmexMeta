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
        model = LibrdfModel(storage.get());
    };

    ~ParticipantTests(){
        storage.freeStorage();
        model.freeModel();
    };
};

/*
 * Try using raw pointers for predicate and participant and letting triple do the freeing
 */
TEST_F(ParticipantTests, TestCreateParticipant) {
    Participant participant(
            model.get(), "MetaId0014", "hasSourceParticipant",
            1.0, "MetaId0015"
    );
    std::string actual = participant.getPredicate().str();
    std::cout << actual << std::endl;
    std::string expected = "http://www.bhi.washington.edu/semsim#hasSourceParticipant";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    participant.free();
}

TEST_F(ParticipantTests, TestSinkParticipant1) {
    SinkParticipant sink(model.get(), "MetaId0014",
                         1.0, "MetaId0015"
    );
    std::string actual = sink.getPredicate().str();
    std::cout << actual << std::endl;
    std::string expected = "http://www.bhi.washington.edu/semsim#hasSinkParticipant";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    sink.free();
}

TEST_F(ParticipantTests, TestCreateTripleFromParticipantInfo) {
    SinkParticipant sink(model.get(), "MetaId0014",
                         1.0, "MetaId0015"
    );
    Triple triple(
            LibrdfNode::fromUriString(sink.getSubject()).get(),
            sink.getPredicate().getNode(),
            LibrdfNode::fromUriString(sink.getSubject()).get()
    );
    // triple assumes responsibility for freeing subject, resource and preicate
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"MetaId0014\">\n"
                           "    <semsim:hasSinkParticipant rdf:resource=\"MetaId0014\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n";
    std::string actual = triple.str();
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    triple.freeStatement();
}


TEST_F(ParticipantTests, TestCreateTripleVector) {
    SinkParticipant sink(model.get(), "MetaId0014",
                         1.0, "MetaId0015"
    );
    Triple triple(
            LibrdfNode::fromUriString(sink.getSubject()).get(),
            sink.getPredicate().getNode(),
            LibrdfNode::fromUriString(sink.getSubject()).get()
    );
    Triples triples;
    triples.move_back(triple);
    // triple assumes responsibility for freeing subject, resource and preicate
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"MetaId0014\">\n"
                           "    <semsim:hasSinkParticipant rdf:resource=\"MetaId0014\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n";
    std::string actual = triples[0].str();
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    triples.freeTriples();
}

TEST_F(ParticipantTests, TestToTriples1) {
    SinkParticipant sink(model.get(), "MetaId0014",
                         1.0, "MetaId0015"
    );
    std::ostringstream os;
    Triples triples = sink.toTriples("metaid");
    std::string actual = triples.str();
    std::cout << actual << std::endl;
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"MetaId0014\">\n"
                           "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double\">1</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"MetaId0015\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"metaid\">\n"
                           "    <semsim:hasSinkParticipant rdf:resource=\"MetaId0014\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    triples.freeTriples();
}


TEST_F(ParticipantTests, TestParticipantVecToTriples) {
    MediatorParticipant mediator(
            model.get(), "MetaId0014",
            "MetaId0015"
    );

    SourceParticipant source(
            model.get(), "MetaId0014",
            1.0, "MetaId0015"
    );

    SinkParticipant sink(
            model.get(),
            "MetaId0014",
            1.0, "MetaId0015"
    );

    std::vector<Participant *> participants = {
            &source,
            &mediator,
            &sink
    };

    Triples triples;
    for (auto &i: participants) {
        for (auto &j: i->toTriples("metaid")) {
            triples.move_back(j);
        }
    }
    ASSERT_EQ(8, triples.size());

    triples.freeTriples();

}












