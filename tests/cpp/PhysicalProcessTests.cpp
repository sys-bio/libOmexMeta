//
// Created by Ciaran on 4/23/2020.
//


#include <semsim/RDF.h>
#include <vector>
#include "gtest/gtest.h"
#include "librdf.h"
#include "semsim/PhysicalEntity.h"
#include "semsim/PhysicalProcess.h"
#include "semsim/Participant.h"
#include "semsim/SemsimUtils.h"

using namespace semsim;

class PhysicalProcessTests : public ::testing::Test {

public:

    LibrdfStorage storage;
    LibrdfModel model;

    PhysicalPropertyResource physical_property;

    PhysicalProcessTests() {
        model = LibrdfModel(storage.get());

        physical_property = PhysicalPropertyResource("OPB:OPB_00340");
    };
    ~PhysicalProcessTests() override {
        model.freeModel();
        storage.freeStorage();
    };
};

TEST_F(PhysicalProcessTests, TestPhysicalProcessSubjectMetaidNode) {
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

    PhysicalProcess process(
            model.get(),
            subject_metaid,
            physical_property,
            source_participants,
            sink_participants,
            mediator_participants
    );

    std::string actual = process.getSubject().str();
    std::string expected = "MetaId004";
    ASSERT_STREQ(expected.c_str(), actual.c_str());

    // Without Triple we need to free stuff manually
    physical_property.free();
    subject_metaid.free();
    source_participants[0].free();
    sink_participants[0].free();
    mediator_participants[0].free();
}


TEST_F(PhysicalProcessTests, TestPhysicalProcessSource) {
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

    PhysicalProcess process(
            model.get(),
            subject_metaid,
            physical_property,
            source_participants,
            sink_participants,
            mediator_participants
    );

    std::string actual = process.getSources()[0].getSubject();
    std::string expected = "SourceId1";
    ASSERT_STREQ(expected.c_str(), actual.c_str());

    // Without Triple we need to free stuff manually
    physical_property.free();
    subject_metaid.free();
    source_participants[0].free();
    sink_participants[0].free();
    mediator_participants[0].free();
}



TEST_F(PhysicalProcessTests, TestPhysicalProcessNumTriples) {
    PhysicalProcess process(
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
            ),
            std::vector<MediatorParticipant>(
                    {MediatorParticipant(

                            model.get(),
                            "MediatorID1",
                            "PhysicalEntityReference3"
                    )}
            )
    );

    Triples triples = process.toTriples();
    std::cout << triples.str() << std::endl;
    int expected = 10;
    int actual = triples.size();
    ASSERT_EQ(expected, actual);
}


TEST_F(PhysicalProcessTests, TestPhysicalProcessTrips) {
    PhysicalProcess process(
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
            ),
            std::vector<MediatorParticipant>(
                    {MediatorParticipant(

                            model.get(),
                            "MediatorID1",
                            "PhysicalEntityReference3"
                    )}
            )
    );
    Triples triples = process.toTriples();

    int expected = 10;
    int actual = triples.size();
    ASSERT_EQ(expected, actual);
}

TEST_F(PhysicalProcessTests, TestPhysicalProcessToTriplesStr) {
    PhysicalProcess process(
            model.get(),
            Subject::fromRawPtr(LibrdfNode::fromUriString("VLV")),
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
            ),
            std::vector<MediatorParticipant>(
                    {MediatorParticipant(

                            model.get(),
                            "MediatorID1",
                            "PhysicalEntityReference3"
                    )}
            )
    );
    Triples triples = process.toTriples();

    std::string actual = triples.str();
    std::cout << actual <<
              std::endl;
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"MediatorID1\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"PhysicalEntityReference3\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"PhysicalProcess0000\">\n"
                           "    <semsim:hasMediatorParticipant rdf:resource=\"MediatorID1\"/>\n"
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
                           "  <rdf:Description rdf:about=\"VLV\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"PhysicalProcess0000\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/OPB/OPB_00340\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PhysicalProcessTests, TestPhysicalProcessBuilder1) {
    PhysicalProcess process(model.get());
    process.setAbout("property_metaid_0")
            .setPhysicalProperty("opb/OPB_00592")
            .addSource("source_0", 1.0, "species_metaid0")
            .addSource("source_1", 2.0, "species_metaid1")
            .addSink("sink_0", 1.0, "species_metaid2")
            .addMediator("mediator_0", 1.0, "species_metaid2");

    Triples triples = process.toTriples();

    std::string actual = triples.str();
    std::cout << actual << std::endl;
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"PhysicalProcess0000\">\n"
                           "    <semsim:hasMediatorParticipant rdf:resource=\"mediator_0\"/>\n"
                           "    <semsim:hasSinkParticipant rdf:resource=\"sink_0\"/>\n"
                           "    <semsim:hasSourceParticipant rdf:resource=\"source_0\"/>\n"
                           "    <semsim:hasSourceParticipant rdf:resource=\"source_1\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"mediator_0\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"species_metaid2\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"property_metaid_0\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"PhysicalProcess0000\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/opb/OPB_00592\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"sink_0\">\n"
                           "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double\">1</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"species_metaid2\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"source_0\">\n"
                           "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double\">1</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"species_metaid0\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"source_1\">\n"
                           "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double\">2</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"species_metaid1\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    ASSERT_STREQ(expected.c_str(), actual.c_str());

    // remember to free the unused physical property from test fixture
    physical_property.free();
}
