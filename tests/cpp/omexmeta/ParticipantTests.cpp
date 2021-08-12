//
// Created by Ciaran on 4/19/2020.
//

#include "gtest/gtest.h"
#include "librdf.h"
#include "omexmeta/RDF.h"
#include "omexmeta/Participant.h"

using namespace omexmeta;

class ParticipantTests : public ::testing::Test {

public:

    LibrdfStorage storage;
    LibrdfModel model;
//    std::string model_uri = "http://omex-library.org/NewOmex.omex/NewModel.xml#";
//    std::string local_uri = "http://omex-library.org/NewOmex.omex/NewModel.rdf#";
    UriHandler uriHandler;
    std::vector<std::string> exclusions;

    ParticipantTests() {
        model = LibrdfModel(storage);
    };

    ~ParticipantTests() override {
    };
};

/*
 * Try using raw pointers for predicate and participant and letting triple do the freeing
 */
TEST_F(ParticipantTests, TestCreateParticipant) {
    Participant participant(
            model, "MetaId0014", uriHandler, "hasSourceParticipant",
            1.0, "MetaId0015", MODEL_URI
    );
    std::cout << participant.getPredicate() <<std::endl;
    SemSim ss(participant.getPredicate());
    std::string actual = ss.str();
    std::cout << actual << std::endl;
    std::string expected = "http://bime.uw.edu/semsim/hasSourceParticipant";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    participant.free();
    ss.freeNode();
}

TEST_F(ParticipantTests, TestSinkParticipant1) {
    SinkParticipant sink(model, 1.0, "MetaId0015", MODEL_URI, uriHandler);
    // SemSim predicate is made on the fly now.
    SemSim ss(sink.getPredicate());
    std::string actual = ss.str();
    std::cout << actual << std::endl;
    std::string expected = "http://bime.uw.edu/semsim/hasSinkParticipant";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    sink.free();
    ss.freeNode();
}

TEST_F(ParticipantTests, TestSinkParticipantMakMetaid) {
    SinkParticipant sink(model, 1.0, "MetaId0015", MODEL_URI, uriHandler);
    std::string actual = sink.createMetaid("SinkParticipant", exclusions);
    std::cout << actual << std::endl;
    std::string expected = "SinkParticipant0000";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    sink.free();
}

TEST_F(ParticipantTests, TestSinkParticipantGetLocalUri) {
    SinkParticipant sink(model, 1.0, "MetaId0015", MODEL_URI, uriHandler);
    std::string actual = sink.getLocalUri();
    std::cout << actual << std::endl;
    std::string expected = uriHandler.getLocalUri();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    sink.free();
}


TEST_F(ParticipantTests, TestCreateTripleFromParticipantInfo) {
    SinkParticipant sink(model, 1.0, "MetaId0015", MODEL_URI, uriHandler);
    Triple triple(
            uriHandler,
            LibrdfNode::fromUriString(OmexMetaUtils::concatMetaIdAndUri(sink.getSubject(), sink.getLocalUri())),
            SemSim(sink.getPredicate()).getNode(),
            LibrdfNode::fromUriString(OmexMetaUtils::concatMetaIdAndUri(sink.getPhysicalEntityReference(), sink.getModelUri()))
    );
    // triple assumes responsibility for freeing subject, resource and preicate
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix semsim: <http://bime.uw.edu/semsim/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:SinkParticipant\n"
                           "    semsim:hasSinkParticipant <http://omex-library.org/NewOmex.omex/NewModel.xml#MetaId0015> .\n"
                           "\n"
                           "";
    model.addStatement(triple);
    LibrdfSerializer serializer("turtle");
    std::string actual = serializer.toString("uri", model);
    std::cout << actual << std::endl;
    ASSERT_TRUE(RDF::equals(triple, expected));
}

TEST_F(ParticipantTests, TestCreateTripleVector) {
    SinkParticipant sink(model, 1.0, "MetaId0015", MODEL_URI, uriHandler);
    Triple triple(
            uriHandler,
            LibrdfNode::fromUriString(OmexMetaUtils::concatMetaIdAndUri(sink.getSubject(), sink.getLocalUri())),
            SemSim(sink.getPredicate()).getNode(),
            LibrdfNode::fromUriString(OmexMetaUtils::concatMetaIdAndUri(sink.getPhysicalEntityReference(), sink.getModelUri()))
    );
    Triples triples;
    triples.moveBack(triple);

    // triple assumes responsibility for freeing subject, resource and preicate
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix semsim: <http://bime.uw.edu/semsim/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:SinkParticipant\n"
                           "    semsim:hasSinkParticipant <http://omex-library.org/NewOmex.omex/NewModel.xml#MetaId0015> .\n"
                           "\n";
    ASSERT_TRUE(RDF::equals(triples, expected));

}

TEST_F(ParticipantTests, TestToTriples1) {
    SinkParticipant sink(model, 1.0, "MetaId0015", MODEL_URI, uriHandler);
    std::ostringstream os;
    Triples triples = sink.toTriples("https://metaid", exclusions);
    for (auto t: triples){
        model.addStatement(t);
    }
    LibrdfSerializer serializer("turtle");
    std::string actual = serializer.toString("uri", model);
    std::cout << actual << std::endl;
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix semsim: <http://bime.uw.edu/semsim/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:SinkParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:double ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#MetaId0015> .\n"
                           "\n"
                           "<https://metaid>\n"
                           "    semsim:hasSinkParticipant local:SinkParticipant0000 .\n"
                           "\n";
    ASSERT_TRUE(RDF::equals(triples, expected));

}

TEST_F(ParticipantTests, TestToTriplesWhenMultiplierIs0) {
    SinkParticipant sink(model, 0.0, "MetaId0015", MODEL_URI, uriHandler);
    std::ostringstream os;
    Triples triples = sink.toTriples("https://metaid", exclusions);
    for (auto t: triples){
        model.addStatement(t);
    }
    LibrdfSerializer serializer("turtle");
    std::string actual = serializer.toString("uri", model);
    std::cout << actual << std::endl;
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix semsim: <http://bime.uw.edu/semsim/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:SinkParticipant0000\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#MetaId0015> .\n"
                           "\n"
                           "<https://metaid>\n"
                           "    semsim:hasSinkParticipant local:SinkParticipant0000 .\n"
                           "\n"
                           "";
    ASSERT_TRUE(RDF::equals(triples, expected));

}

TEST_F(ParticipantTests, TestToTriplesMediator) {
    MediatorParticipant mediator(model, "MetaId0015", MODEL_URI, uriHandler);
    std::ostringstream os;
    Triples triples = mediator.toTriples("https://metaid", exclusions);
    for (auto t: triples){
        model.addStatement(t);
    }
    LibrdfSerializer serializer("turtle");
    std::string actual = serializer.toString("uri", model);
    std::cout << actual << std::endl;
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix semsim: <http://bime.uw.edu/semsim/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:MediatorParticipant0000\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#MetaId0015> .\n"
                           "\n"
                           "<https://metaid>\n"
                           "    semsim:hasMediatorParticipant local:MediatorParticipant0000 .\n"
                           "\n"
                           "";
    ASSERT_TRUE(RDF::equals(triples, expected));

}

class ParticipantTestsToTriplesTwice : public ::testing::Test {
public:

    LibrdfStorage storage;
    LibrdfModel model;

    UriHandler uriHandler;
    std::vector<std::string> exclusions;
    ParticipantTestsToTriplesTwice() {
        model = LibrdfModel(storage);
    }

    ~ParticipantTestsToTriplesTwice() {
    }
};


TEST_F(ParticipantTests, TestParticipantVecToTriples) {
    MediatorParticipant mediator(model, "MetaId0015", MODEL_URI, uriHandler);

    SourceParticipant source(model, 1.0, "MetaId0015", MODEL_URI, uriHandler);

    SinkParticipant sink(model, 1.0, "MetaId0015", MODEL_URI, uriHandler);

    std::vector<Participant *> participants = {
            &source,
            &mediator,
            &sink
    };

    Triples triples;
    for (auto &i: participants) {
        for (auto &j: i->toTriples("http://metaid", exclusions)) {
            triples.moveBack(j);
        }
    }
    ASSERT_EQ(8, triples.size());



}













