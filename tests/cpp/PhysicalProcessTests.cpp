//
// Created by Ciaran on 4/23/2020.
//


#include "omexmeta/RDF.h"
#include <vector>
#include "gtest/gtest.h"
#include "librdf.h"
#include "omexmeta/PhysicalEntity.h"
#include "omexmeta/PhysicalProcess.h"
#include "omexmeta/Participant.h"
#include "omexmeta/SemsimUtils.h"

using namespace semsim;

class PhysicalProcessTests : public ::testing::Test {

public:

    LibrdfStorage storage;
    LibrdfModel model;

    PhysicalProperty physical_property;

    PhysicalProcessTests() {
        model = LibrdfModel(storage.get());

        physical_property = PhysicalProperty("metaid", "OPB:OPB_00340");
    };

    ~PhysicalProcessTests() override {
        model.freeModel();
        storage.freeStorage();
    };
};

TEST_F(PhysicalProcessTests, TestPhysicalProcessSubjectMetaidNode) {
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

    PhysicalProcess process(
            model.get(),
            physical_property,
            source_participants,
            sink_participants,
            mediator_participants
    );

    std::string actual = process.getSubjectStr();
    std::string expected = "metaid";
    ASSERT_STREQ(expected.c_str(), actual.c_str());

    // Without Triple we need to free stuff manually
    //physical_property.free();
    subject_metaid.free();
    source_participants[0].free();
    sink_participants[0].free();
    mediator_participants[0].free();
}


TEST_F(PhysicalProcessTests, TestPhysicalProcessSource) {
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

    PhysicalProcess process(
            model.get(),
            physical_property,
            source_participants,
            sink_participants,
            mediator_participants
    );

    std::string actual = process.getSources()[0].getSubject();
    std::string expected = "SourceParticipant";
    ASSERT_STREQ(expected.c_str(), actual.c_str());

    // Without Triple we need to free stuff manually
    //physical_property.free();
    source_participants[0].free();
    sink_participants[0].free();
    mediator_participants[0].free();
}


TEST_F(PhysicalProcessTests, TestPhysicalProcessNumTriples) {
    PhysicalProcess process(
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
            ),
            std::vector<MediatorParticipant>(
                    {MediatorParticipant(

                            model.get(),
                                    "PhysicalEntityReference3"
                    )}
            )
    );

    Triples triples = process.toTriples();
    std::cout << triples.str() << std::endl;
    int expected = 10;
    int actual = triples.size();
    ASSERT_EQ(expected, actual);
    triples.freeTriples();

}


TEST_F(PhysicalProcessTests, TestPhysicalProcessTrips) {
    PhysicalProcess process(
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
            ),
            std::vector<MediatorParticipant>(
                    {MediatorParticipant(

                            model.get(),
                                    "PhysicalEntityReference3"
                    )}
            )
    );
    Triples triples = process.toTriples();

    int expected = 10;
    int actual = triples.size();
    ASSERT_EQ(expected, actual);
    triples.freeTriples();
}

TEST_F(PhysicalProcessTests, TestPhysicalProcessToTriplesStr) {
    PhysicalProcess process(
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
            ),
            std::vector<MediatorParticipant>(
                    {MediatorParticipant(

                            model.get(),
                                    "PhysicalEntityReference3"
                    )}
            )
    );
    Triples triples = process.toTriples();

    std::string actual = triples.str();
    std::cout << actual << std::endl;
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xmlns:omexmeta=\"http://www.bhi.washington.edu/omexmeta#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"MediatorParticipant0000\">\n"
                           "    <omexmeta:hasPhysicalEntityReference rdf:resource=\"PhysicalEntityReference3\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"PhysicalProcess0000\">\n"
                           "    <omexmeta:hasMediatorParticipant rdf:resource=\"MediatorParticipant0000\"/>\n"
                           "    <omexmeta:hasSinkParticipant rdf:resource=\"SinkParticipant0000\"/>\n"
                           "    <omexmeta:hasSourceParticipant rdf:resource=\"SourceParticipant0000\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"SinkParticipant0000\">\n"
                           "    <omexmeta:hasMultiplier rdf:datatype=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double\">1</omexmeta:hasMultiplier>\n"
                           "    <omexmeta:hasPhysicalEntityReference rdf:resource=\"PhysicalEntityReference2\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"SourceParticipant0000\">\n"
                           "    <omexmeta:hasMultiplier rdf:datatype=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double\">1</omexmeta:hasMultiplier>\n"
                           "    <omexmeta:hasPhysicalEntityReference rdf:resource=\"PhysicalEntityReference1\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"metaid\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"PhysicalProcess0000\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/OPB/OPB_00340\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    triples.freeTriples();
}

TEST_F(PhysicalProcessTests, TestPhysicalProcessBuilder1) {
    PhysicalProcess process(model.get());
    process.setPhysicalProperty("property_metaid_0", "opb/OPB_00592")
            .addSource(1.0, "species_metaid0")
            .addSource(2.0, "species_metaid1")
            .addSink(1.0, "species_metaid2")
            .addMediator(1.0, "species_metaid2");

    Triples triples = process.toTriples();

    std::string actual = triples.str();
    std::cout << actual << std::endl;
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xmlns:omexmeta=\"http://www.bhi.washington.edu/omexmeta#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"MediatorParticipant0000\">\n"
                           "    <omexmeta:hasPhysicalEntityReference rdf:resource=\"species_metaid2\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"PhysicalProcess0000\">\n"
                           "    <omexmeta:hasMediatorParticipant rdf:resource=\"MediatorParticipant0000\"/>\n"
                           "    <omexmeta:hasSinkParticipant rdf:resource=\"SinkParticipant0000\"/>\n"
                           "    <omexmeta:hasSourceParticipant rdf:resource=\"SourceParticipant0000\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"SinkParticipant0000\">\n"
                           "    <omexmeta:hasMultiplier rdf:datatype=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double\">1</omexmeta:hasMultiplier>\n"
                           "    <omexmeta:hasPhysicalEntityReference rdf:resource=\"species_metaid2\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"SourceParticipant0000\">\n"
                           "    <omexmeta:hasMultiplier rdf:datatype=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double\">1</omexmeta:hasMultiplier>\n"
                           "    <omexmeta:hasMultiplier rdf:datatype=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double\">2</omexmeta:hasMultiplier>\n"
                           "    <omexmeta:hasPhysicalEntityReference rdf:resource=\"species_metaid0\"/>\n"
                           "    <omexmeta:hasPhysicalEntityReference rdf:resource=\"species_metaid1\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"property_metaid_0\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"PhysicalProcess0000\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/opb/OPB_00592\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    ASSERT_STREQ(expected.c_str(), actual.c_str());

    // remember to free the unused physical property from test fixture
    //physical_property.free();
    triples.freeTriples();
}

TEST_F(PhysicalProcessTests, TestEquality) {
    PhysicalProcess process1(model.get());
    process1.setPhysicalProperty("property_metaid_0", "opb/OPB_00592")
            .addSource(1.0, "species_metaid0")
            .addSource(2.0, "species_metaid1")
            .addSink(1.0, "species_metaid2")
            .addMediator(1.0, "species_metaid2");

    PhysicalProcess process2(model.get());
    process2.setPhysicalProperty("property_metaid_0", "opb/OPB_00592")
            .addSource(1.0, "species_metaid0")
            .addSource(2.0, "species_metaid1")
            .addSink(1.0, "species_metaid2")
            .addMediator(1.0, "species_metaid2");
    ASSERT_EQ(process1, process2);
    process1.free();
    process2.free();
}

TEST_F(PhysicalProcessTests, TestInequality) {
    PhysicalProcess process1(model.get());
    process1.setPhysicalProperty("property_metaid_1", "opb/OPB_00592")
            .addSource(1.0, "species_metaid0")
            .addSource(2.0, "species_metaid1")
            .addSink(1.0, "species_metaid2")
            .addMediator(1.0, "species_metaid2");

    PhysicalProcess process2(model.get());
    process2.setPhysicalProperty("property_metaid_0", "opb/OPB_00592")
            .addSource(1.0, "species_metaid0")
            .addSource(2.0, "species_metaid1")
            .addSink(1.0, "species_metaid2")
            .addMediator(1.0, "species_metaid2");
    ASSERT_NE(process1, process2);

    process1.free();
    process2.free();
}




















