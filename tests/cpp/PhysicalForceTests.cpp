//
// Created by Ciaran on 4/23/2020.
//


#include "omexmeta/RDF.h"
#include <vector>
#include "gtest/gtest.h"
#include "librdf.h"
#include "omexmeta/PhysicalForce.h"
#include "omexmeta/Participant.h"
#include "omexmeta/SemsimUtils.h"

using namespace semsim;

class PhysicalForceTests : public ::testing::Test {

public:

    LibrdfStorage storage;
    LibrdfModel model;

    PhysicalProperty physical_property;

    PhysicalForceTests() {
        model = LibrdfModel(storage.get());
        physical_property = PhysicalProperty("metaid", "OPB:OPB_00340");
    };

    ~PhysicalForceTests() override {
        model.freeModel();
        storage.freeStorage();
    };
};


TEST_F(PhysicalForceTests, TestPhysicalForceSubjectMetaidNode) {
    Subject subject_metaid = Subject::fromRawPtr(LibrdfNode::fromUriString("MetaId004").get());
    std::vector<SourceParticipant> source_participants(
            {SourceParticipant(
                    model.get(),
                    1.0,
                    "PhysicalEntityReference1"
            )}
    );
    std::vector<SinkParticipant> sink_participants(
            {SinkParticipant(
                    model.get(),
                    1.0,
                    "PhysicalEntityReference2"
            )}
    );
    std::vector<MediatorParticipant> mediator_participants(
            {MediatorParticipant(
                    model.get(),
                    "PhysicalEntityReference3"
            )}
    );

    PhysicalForce force(
            model.get(),
            physical_property,
            source_participants,
            sink_participants
    );
    std::string actual = force.getSubjectStr();
    std::string expected = "metaid";
    ASSERT_STREQ(expected.c_str(), actual.c_str());

    // Without Triple we need to free stuff manually
//    physical_property.free();
    subject_metaid.free();
    source_participants[0].free();
    sink_participants[0].free();
    mediator_participants[0].free();

}


TEST_F(PhysicalForceTests, TestPhysicalProperty1) {
    std::vector<SourceParticipant> source_participants({SourceParticipant(
            model.get(),
            1.0,
            "PhysicalEntityReference1"
    )});
    std::vector<SinkParticipant> sink_participants(
            {SinkParticipant(
                    model.get(),
                    1.0,
                    "PhysicalEntityReference2"
            )}
    );


    PhysicalForce force(
            model.get(),
            physical_property,
            source_participants,
            sink_participants
    );
    std::string actual = force.getPhysicalProperty().getResourceStr();
    std::string expected = "OPB:OPB_00340";
    ASSERT_STREQ(expected.c_str(), actual.c_str());

    // Without Triple we need to free stuff manually
    force.free();

}

TEST_F(PhysicalForceTests, TestPhysicalProperty2) {
    std::vector<SourceParticipant> source_participants({SourceParticipant(
            model.get(),
            1.0,
            "PhysicalEntityReference1"
    )});
    std::vector<SinkParticipant> sink_participants(
            {SinkParticipant(
                    model.get(),
                    1.0,
                    "PhysicalEntityReference2"
            )}
    );

    PhysicalForce force(
            model.get(),
            physical_property,
            source_participants,
            sink_participants
    );
    std::string actual = force.getPhysicalProperty().getSubjectStr();
    std::string expected = "metaid";
    ASSERT_STREQ(expected.c_str(), actual.c_str());

    // Without Triple we need to free stuff manually
    force.free();

}


TEST_F(PhysicalForceTests, TestPhysicalForceNumTriples) {
    PhysicalForce force(
            model.get(),
            physical_property,
            std::vector<SourceParticipant>(
                    {SourceParticipant(
                            model.get(),
                            1.0,
                            "PhysicalEntityReference1"
                    )}
            ),
            std::vector<SinkParticipant>(
                    {SinkParticipant(
                            model.get(),
                            1.0,
                            "PhysicalEntityReference2"
                    )}
            )
    );

    Triples triples = force.toTriples();
    int expected = 8;
    int actual = triples.size();
    ASSERT_EQ(expected, actual
    );
    triples.freeTriples();
}


TEST_F(PhysicalForceTests, TestPhysicalForceTrips) {
    PhysicalForce force(
            model.get(),
            physical_property,
            std::vector<SourceParticipant>(
                    {SourceParticipant(
                            model.get(),
                            1.0,
                            "PhysicalEntityReference1"
                    )}
            ),
            std::vector<SinkParticipant>(
                    {SinkParticipant(
                            model.get(),
                            1.0,
                            "PhysicalEntityReference2"
                    )}
            )
    );

    Triples triples = force.toTriples();
    int expected = 8;
    int actual = triples.size();
    ASSERT_EQ(expected, actual);
    triples.freeTriples();
}


TEST_F(PhysicalForceTests, TestPhysicalForceTriples) {
    PhysicalForce force(
            model.get(),
            physical_property,
            std::vector<SourceParticipant>(
                    {SourceParticipant(
                            model.get(),
                            1.0,
                            "PhysicalEntityReference1"
                    )}
            ),
            std::vector<SinkParticipant>(
                    {SinkParticipant(
                            model.get(),
                            1.0,
                            "PhysicalEntityReference2"
                    )}
            )
    );

    Triples triples = force.toTriples();
    std::string actual = triples.str();
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"PhysicalForce0000\">\n"
                           "    <semsim:hasSinkParticipant rdf:resource=\"SinkParticipant0000\"/>\n"
                           "    <semsim:hasSourceParticipant rdf:resource=\"SourceParticipant0000\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"SinkParticipant0000\">\n"
                           "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double\">1</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"PhysicalEntityReference2\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"SourceParticipant0000\">\n"
                           "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double\">1</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"PhysicalEntityReference1\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"metaid\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"PhysicalForce0000\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/OPB/OPB_00340\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    triples.freeTriples();
}


TEST(PhysicalForceTestsNoFixture, TestPhysicalForceBuilder) {
    RDF rdf;
    PhysicalForce force(rdf.getModel());
    //todo considering implementing the builder as a composite builder
    force
            .setPhysicalProperty("Force5", "OPB:OPB_00340")
            .addSource(1, "PhysicalEntityReference1")
            .addSink(2, "PhysicalEntityReference2")
            .addSink(1, "PhysicalEntityReference3");


    Triples triples = force.toTriples();
    std::string actual = triples.str();
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"Force5\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"PhysicalForce0000\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/OPB/OPB_00340\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"PhysicalForce0000\">\n"
                           "    <semsim:hasSinkParticipant rdf:resource=\"SinkParticipant0000\"/>\n"
                           "    <semsim:hasSourceParticipant rdf:resource=\"SourceParticipant0000\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"SinkParticipant0000\">\n"
                           "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double\">1</semsim:hasMultiplier>\n"
                           "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double\">2</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"PhysicalEntityReference2\"/>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"PhysicalEntityReference3\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"SourceParticipant0000\">\n"
                           "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double\">1</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"PhysicalEntityReference1\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    triples.freeTriples();
}


TEST(PhysicalForceTestsNoFixture, TestGenerateTheSamePhysicalForceTwice) {
    RDF rdf;
    PhysicalForce force(rdf.getModel());
    //todo considering implementing the builder as a composite builder
    force.setPhysicalProperty("Force5", "OPB:OPB_00340")
            .addSource(1, "PhysicalEntityReference1")
            .addSink(2, "PhysicalEntityReference2")
            .addSink(1, "PhysicalEntityReference3");

    Triples triples1 = force.toTriples();
    std::string actual1 = triples1.str("ntriples", "base");
    Triples triples2 = force.toTriples();
    std::string actual2 = triples2.str("ntriples", "base");

    ASSERT_STREQ(actual1.c_str(), actual2.c_str());
    triples1.freeTriples();
    triples2.freeTriples();
}

/*******************************************************************
 * Equality Tests
 */

class PhysicalForceEqualityTests : public ::testing::Test {
public:

    LibrdfStorage storage;
    LibrdfModel model;

    PhysicalForceEqualityTests() {
        model = LibrdfModel(storage.get());
    }

    ~PhysicalForceEqualityTests() override {
        storage.freeStorage();
        model.freeModel();
    }

};

TEST_F(PhysicalForceEqualityTests, TestEquality) {
    PhysicalForce force1(model.get());
    force1.setPhysicalProperty("property_metaid_0", "opb/OPB_00592")
            .addSource(1.0, "species_metaid0")
            .addSource(2.0, "species_metaid1")
            .addSink(1.0, "species_metaid2");

    PhysicalForce force2(model.get());
    force2.setPhysicalProperty("property_metaid_0", "opb/OPB_00592")
            .addSource(1.0, "species_metaid0")
            .addSource(2.0, "species_metaid1")
            .addSink(1.0, "species_metaid2");
    ASSERT_EQ(force1, force2);
    force1.free();
    force2.free();
}

TEST_F(PhysicalForceEqualityTests, TestInequality1) {
    PhysicalForce force1(model.get());
    force1.setPhysicalProperty("property_metaid_1", "opb/OPB_00592")
            .addSource(1.0, "species_metaid0")
            .addSource(2.0, "species_metaid1")
            .addSink(1.0, "species_metaid2");

    PhysicalForce force2(model.get());
    force2.setPhysicalProperty("property_metaid_0", "opb/OPB_00592")
            .addSource(1.0, "species_metaid0")
            .addSource(2.0, "species_metaid1")
            .addSink(1.0, "species_metaid2");
    ASSERT_NE(force1, force2);

    force1.free();
    force2.free();
}

TEST_F(PhysicalForceEqualityTests, TestInequality2) {
    PhysicalForce force1(model.get());
    force1.setPhysicalProperty("property_metaid_0", "opb/OPB_00593")
            .addSource(1.0, "species_metaid0")
            .addSource(2.0, "species_metaid1")
            .addSink(1.0, "species_metaid2");

    PhysicalForce force2(model.get());
    force2.setPhysicalProperty("property_metaid_0", "opb/OPB_00597")
            .addSource(1.0, "species_metaid0")
            .addSource(2.0, "species_metaid1")
            .addSink(1.0, "species_metaid2");

    ASSERT_NE(force1, force2);

    force1.free();
    force2.free();
}

TEST_F(PhysicalForceEqualityTests, TestInequality3) {
    PhysicalForce force1(model.get());
    force1.setPhysicalProperty("property_metaid_1", "opb/OPB_00592")
            .addSource(1.0, "species_metaid0")
            .addSource(2.0, "species_metaid1")
            .addSink(1.0, "species_metaid2");

    PhysicalForce force2(model.get());
    force2.setPhysicalProperty("property_metaid_1", "opb/OPB_00592")
            .addSource(1.0, "species_metaid0")
            .addSource(2.0, "species_metaid2")
            .addSink(1.0, "species_metaid1");
    ASSERT_NE(force1, force2);

    force1.free();
    force2.free();
}

TEST_F(PhysicalForceEqualityTests, TestInequality4) {
    PhysicalForce force1(model.get());
    force1.setPhysicalProperty("property_metaid_1", "opb/OPB_00592")
            .addSource(1.0, "species_metaid0")
            .addSource(2.0, "species_metaid1")
            .addSink(1.0, "species_metaid2");

    PhysicalForce force2(model.get());
    force2.setPhysicalProperty("property_metaid_1", "opb/OPB_00592")
            .addSource(2.0, "species_metaid0")
            .addSource(2.0, "species_metaid1")
            .addSink(1.0, "species_metaid2");
    ASSERT_NE(force1, force2);

    force1.free();
    force2.free();
}


TEST(PhysicalForceTestsNoFixture, TestUsagesPhysicalForce) {
    LibrdfStorage storage;
    LibrdfModel model(storage.get());
    PhysicalForce force(model.get());
    force.setPhysicalProperty("parameter_metaid_0", "opb/OPB_01058")
            .addSource(2.0, "species_metaid_0")
            .addSink(1.0, "species_metaid_1");
    Triples triples = force.toTriples();
    ASSERT_EQ(8, triples.size());

    std::cout << triples.str() << std::endl;

    //<parameter_metaid_0> <http://biomodels.net/biology-qualifiers/isVersionOf> <https://identifiers.org/opb/OPB_01058> .
    Triple triple1 = triples.pop_front();
    auto m1 = triple1.getUsages();
    std::cout << triple1.str("ntriples", "triple1") << std::endl;
    ASSERT_EQ(2, m1["subject_uri"]);
    ASSERT_EQ(1, m1["predicate_uri"]);
    ASSERT_EQ(1, m1["resource_uri"]);

    // <parameter_metaid_0> <http://biomodels.net/biology-qualifiers/isPropertyOf> <PhysicalForce0000> .
    Triple triple2 = triples.pop_front();
    std::cout << triple2.str("ntriples", "triple1") << std::endl;
    auto m2 = triple2.getUsages();
    ASSERT_EQ(2, m2["subject_uri"]);
    ASSERT_EQ(1, m2["predicate_uri"]);
    ASSERT_EQ(3, m2["resource_uri"]);

    // <PhysicalForce0000> <http://www.bhi.washington.edu/semsim#hasSourceParticipant> <SourceParticipant0000> .
    Triple triple3 = triples.pop_front();
    std::cout << triple3.str("ntriples", "triple1") << std::endl;
    auto m3 = triple3.getUsages();
    ASSERT_EQ(3, m3["subject_uri"]);
    ASSERT_EQ(1, m3["predicate_uri"]);
    ASSERT_EQ(3, m3["resource_uri"]);

    // <SourceParticipant0000> <http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference> <species_metaid_0> .
    Triple triple4 = triples.pop_front();
    std::cout << triple4.str("ntriples", "triple1") << std::endl;
    auto m4 = triple4.getUsages();
    ASSERT_EQ(3, m4["subject_uri"]);
    ASSERT_EQ(2, m4["predicate_uri"]);
    ASSERT_EQ(1, m4["resource_uri"]);

    // <SourceParticipant0000> <http://www.bhi.washington.edu/semsim#hasMultiplier> "2"^^<http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double> .
    Triple triple5 = triples.pop_front();
    std::cout << triple5.str("ntriples", "triple1") << std::endl;
    auto m5 = triple5.getUsages();
    ASSERT_EQ(3, m5["subject_uri"]);
    ASSERT_EQ(2, m5["predicate_uri"]);
    // resource uri not defined

    //<PhysicalForce0000> <http://www.bhi.washington.edu/semsim#hasSinkParticipant> <SinkParticipant0000> .
    Triple triple6 = triples.pop_front();
    std::cout << triple6.str("ntriples", "triple1") << std::endl;
    auto m6 = triple6.getUsages();
    ASSERT_EQ(3, m6["subject_uri"]);
    ASSERT_EQ(1, m6["predicate_uri"]);
    // resource uri not defined

    // <SinkParticipant0000> <http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference> <species_metaid_1> .
    Triple triple7 = triples.pop_front();
    std::cout << triple7.str("ntriples", "triple1") << std::endl;
    auto m7 = triple7.getUsages();
    ASSERT_EQ(3, m7["subject_uri"]);
    ASSERT_EQ(2, m7["predicate_uri"]);
    ASSERT_EQ(1, m7["resource_uri"]);

    // <SinkParticipant0000> <http://www.bhi.washington.edu/semsim#hasMultiplier> "1"^^<http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double> .
    Triple triple8 = triples.pop_front();
    std::cout << triple8.str("ntriples", "triple1") << std::endl;
    auto m8 = triple8.getUsages();
    ASSERT_EQ(3, m8["subject_uri"]);
    ASSERT_EQ(2, m8["predicate_uri"]);
    // resource uri not defined

    triple1.freeTriple();
    triple2.freeTriple();
    triple3.freeTriple();
    triple4.freeTriple();
    triple5.freeTriple();
    triple6.freeTriple();
    triple7.freeTriple();
    triple8.freeTriple();

    model.freeModel();
    storage.freeStorage();
}


