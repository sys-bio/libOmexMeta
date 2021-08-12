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
    std::string actual = triple.str();
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
    std::string actual = triples.str();
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
    std::string actual = triples.str();
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
    std::string actual = triples.str();
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

/*
 * First check the numbers of references in a single triple
 */
TEST_F(ParticipantTestsToTriplesTwice, TestToTriplesRefAccountability) {
    SinkParticipant sink(model, 1.0, "MetaId0015", MODEL_URI, uriHandler);
    Triples triples1 = sink.toTriples("https://Process1", exclusions);

    // Sinks have 3 triples
    ASSERT_EQ(3, triples1.size());

    // each triple is used once
    ASSERT_EQ(1, triples1[0].getStatement()->usage);
    ASSERT_EQ(1, triples1[1].getStatement()->usage);
    ASSERT_EQ(1, triples1[2].getStatement()->usage);

    // check usage of subjects
    ASSERT_EQ(1, triples1[0].getSubjectNode().getUsage());
    ASSERT_EQ(1, triples1[1].getSubjectNode().getUsage());
    ASSERT_EQ(1, triples1[2].getSubjectNode().getUsage());

    // check usage of predicates
    ASSERT_EQ(1, triples1[0].getPredicateNode().getUsage());
    ASSERT_EQ(1, triples1[1].getPredicateNode().getUsage());
    ASSERT_EQ(1, triples1[2].getPredicateNode().getUsage());


    // check usage of resources
    ASSERT_EQ(1, triples1[0].getResourceNode().getUsage());
    ASSERT_EQ(1, triples1[1].getResourceNode().getUsage());
    ASSERT_EQ(1, triples1[2].getResourceNode().getUsage());

}

/*
 * Now throw another triple in the mix
 */
TEST_F(ParticipantTestsToTriplesTwice, TestToTriplesTwice) {
    SinkParticipant sink(model, 1.0, "MetaId0015", MODEL_URI, uriHandler);
    Triples triples1 = sink.toTriples("https://Process1", exclusions);
    Triples triples2 = sink.toTriples("https://Process1", exclusions);

    // Sinks have 3 triples
    ASSERT_EQ(3, triples1.size());
    ASSERT_EQ(3, triples2.size());

    // each triple is used once
    ASSERT_EQ(1, triples1[0].getStatement()->usage);
    ASSERT_EQ(1, triples1[1].getStatement()->usage);
    ASSERT_EQ(1, triples1[2].getStatement()->usage);

    ASSERT_EQ(1, triples2[0].getStatement()->usage);
    ASSERT_EQ(1, triples2[1].getStatement()->usage);
    ASSERT_EQ(1, triples2[2].getStatement()->usage);

    // check usage of subjects
    ASSERT_EQ(1, triples1[0].getSubjectNode().getUsage());
    ASSERT_EQ(1, triples1[1].getSubjectNode().getUsage());
    ASSERT_EQ(1, triples1[2].getSubjectNode().getUsage());

    ASSERT_EQ(1, triples2[0].getSubjectNode().getUsage());
    ASSERT_EQ(1, triples2[1].getSubjectNode().getUsage());
    ASSERT_EQ(1, triples2[2].getSubjectNode().getUsage());

    // check usage of predicates
    ASSERT_EQ(1, triples1[0].getPredicateNode().getUsage());
    ASSERT_EQ(1, triples1[1].getPredicateNode().getUsage());
    ASSERT_EQ(1, triples1[2].getPredicateNode().getUsage());

    ASSERT_EQ(1, triples2[0].getPredicateNode().getUsage());
    ASSERT_EQ(1, triples2[1].getPredicateNode().getUsage());
    ASSERT_EQ(1, triples2[2].getPredicateNode().getUsage());


    // check usage of Resource
    ASSERT_EQ(1, triples1[0].getResourceNode().getUsage());
    ASSERT_EQ(1, triples1[1].getResourceNode().getUsage());
    ASSERT_EQ(1, triples1[2].getResourceNode().getUsage());

    ASSERT_EQ(1, triples2[0].getResourceNode().getUsage());
    ASSERT_EQ(1, triples2[1].getResourceNode().getUsage());
    ASSERT_EQ(1, triples2[2].getResourceNode().getUsage());

    /*
     * The nodes are all used once
     * But the Uri's can be shared
     */



}

TEST_F(ParticipantTestsToTriplesTwice, TestToTriplesTwiceMemoryAddresses) {
    SinkParticipant sink(model, 1.0, "MetaId0015", MODEL_URI, uriHandler);
    Triples triples1 = sink.toTriples("https://Process1", exclusions);
    Triples triples2 = sink.toTriples("https://Process1", exclusions);

    std::cout << triples1.str("ntriples", "triples1") << std::endl;
    std::cout << triples2.str("ntriples", "triples2") << std::endl;
    /*
     * The goal of this test is to figure out which
     * data blocks are common between the two triples?
     *
     * Name                     Uri times should be used        Times used
     * ----                     -------------- ---------        ---------
     * Process1                     2                               2
     * hasSinkParticipant           2                               1
     * metaid14                     6                               6
     * metaid15                     2                               2
     */
    ASSERT_EQ(triples1[0].getSubjectNode().getUri(), triples2[0].getSubjectNode().getUri());
    ASSERT_EQ(triples1[0].getResourceNode().getUri(), triples2[0].getResourceNode().getUri());
    ASSERT_EQ(triples1[0].getPredicateNode().getUri(), triples2[0].getPredicateNode().getUri());

}


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













