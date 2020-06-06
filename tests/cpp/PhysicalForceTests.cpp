//
// Created by Ciaran on 4/23/2020.
//


#include <semsim/RDF.h>
#include <vector>
#include "gtest/gtest.h"
#include "librdf.h"
#include "semsim/PhysicalForce.h"
#include "semsim/Participant.h"
#include "semsim/SemsimUtils.h"

using namespace semsim;

class PhysicalForceTests : public ::testing::Test {

public:

    LibrdfStorage storage;
    LibrdfModel model;

    PhysicalPropertyResource physical_property;

    PhysicalForceTests() {
        model = LibrdfModel(storage.get());
        physical_property = PhysicalPropertyResource("OPB:OPB_00340");
    };
    ~PhysicalForceTests() override {
        model.freeModel();
        storage.freeStorage();
    };
};


TEST_F(PhysicalForceTests, TestPhysicalForceSubjectMetaidNode) {
    Subject subject_metaid = Subject::fromRawPtr(LibrdfNode::fromUriString("MetaId004"));
    std::vector<SourceParticipant> source_participants(
            {SourceParticipant(
                    model.get(),
                    "SourceId1",
                    1.0,
                    "PhysicalEntityReference1"
            )}
    );
    std::vector<SinkParticipant> sink_participants(
            {SinkParticipant(
                    model.get(),
                    "SinkId1",
                    1.0,
                    "PhysicalEntityReference2"
            )}
    );
    std::vector<MediatorParticipant> mediator_participants(
            {MediatorParticipant(
                    model.get(),
                    "MediatorID1",
                    "PhysicalEntityReference3"
            )}
    );

    PhysicalForce force(
            model.get(),
            subject_metaid,
            physical_property,
            source_participants,
            sink_participants
    );
    std::string actual = force.getSubject().str();
    std::string expected = "MetaId004";
    ASSERT_STREQ(expected.c_str(), actual.c_str());

    // Without Triple we need to free stuff manually
    physical_property.free();
    subject_metaid.free();
    source_participants[0].free();
    sink_participants[0].free();
    mediator_participants[0].free();

}


TEST_F(PhysicalForceTests, TestPhysicalForceNumTriples) {
    PhysicalForce force(
            model.get(),
            Subject::fromRawPtr(LibrdfNode::fromUriString("MetaId004")),
            physical_property,
            std::vector<SourceParticipant>(
                    {SourceParticipant(
                            model.get(),
                            "SourceId1",
                            1.0,
                            "PhysicalEntityReference1"
                    )}
            ),
            std::vector<SinkParticipant>(
                    {SinkParticipant(
                            model.get(),
                            "SinkId1",
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
}


TEST_F(PhysicalForceTests, TestPhysicalForceTrips) {
    PhysicalForce force(
            model.get(),
            Subject::fromRawPtr(LibrdfNode::fromUriString("MetaId004")),
            physical_property,
            std::vector<SourceParticipant>(
                    {SourceParticipant(
                            model.get(),
                            "SourceId1",
                            1.0,
                            "PhysicalEntityReference1"
                    )}
            ),
            std::vector<SinkParticipant>(
                    {SinkParticipant(
                            model.get(),
                            "SinkId1",
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
}


TEST_F(PhysicalForceTests, TestPhysicalForceTriples) {
    PhysicalForce force(
            model.get(),
            Subject::fromRawPtr(LibrdfNode::fromUriString("ForceId0000")),
            physical_property,
            std::vector<SourceParticipant>(
                    {SourceParticipant(
                            model.get(),
                            "SourceId1",
                            1.0,
                            "PhysicalEntityReference1"
                    )}
            ),
            std::vector<SinkParticipant>(
                    {SinkParticipant(
                            model.get(),
                            "SinkId1",
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
                           "  <rdf:Description rdf:about=\"ForceId0000\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"PhysicalForce0000\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/OPB/OPB_00340\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"PhysicalForce0000\">\n"
                           "    <semsim:hasSinkParticipant rdf:resource=\"SinkId1\"/>\n"
                           "    <semsim:hasSourceParticipant rdf:resource=\"SourceId1\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"SinkId1\">\n"
                           "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double\">1</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"PhysicalEntityReference2\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"SourceId1\">\n"
                           "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double\">1</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"PhysicalEntityReference1\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST(PhysicalForceTestsNoFixture, TestPhysicalForceBuilder) {
    RDF rdf;
    PhysicalForce force(rdf.getModel());
    //todo considering implementing the builder as a composite builder
    force.setAbout("Force5")
            .setPhysicalProperty("OPB:OPB_00340")
            .addSource("Source1", 1, "PhysicalEntityReference1")
            .addSink("Sink1", 2, "PhysicalEntityReference2")
            .addSink("Sink2", 1, "PhysicalEntityReference3");


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
                           "    <semsim:hasSinkParticipant rdf:resource=\"Sink1\"/>\n"
                           "    <semsim:hasSinkParticipant rdf:resource=\"Sink2\"/>\n"
                           "    <semsim:hasSourceParticipant rdf:resource=\"Source1\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"Sink1\">\n"
                           "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double\">2</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"PhysicalEntityReference2\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"Sink2\">\n"
                           "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double\">1</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"PhysicalEntityReference3\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"Source1\">\n"
                           "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double\">1</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"PhysicalEntityReference1\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n";
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

