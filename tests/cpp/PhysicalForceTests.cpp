//
// Created by Ciaran on 4/23/2020.
//


#include "omexmeta/RDF.h"
#include <vector>
#include "gtest/gtest.h"
#include "librdf.h"
#include "omexmeta/PhysicalForce.h"
#include "omexmeta/Participant.h"
#include "omexmeta/OmexMetaUtils.h"

using namespace omexmeta;

class PhysicalForceTests : public ::testing::Test {

public:

    LibrdfStorage storage;
    LibrdfModel model;
    std::string local_uri = "http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#";

    PhysicalProperty physical_property;

    PhysicalForceTests() {
        model = LibrdfModel(storage.get());
        physical_property = PhysicalProperty("metaid", "OPB:OPB_00340", local_uri);
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
                    "#PhysicalEntityReference1",
                    local_uri
            )}
    );
    std::vector<SinkParticipant> sink_participants(
            {SinkParticipant(
                    model.get(),
                    1.0,
                    "PhysicalEntityReference2", local_uri
            )}
    );
    std::vector<MediatorParticipant> mediator_participants(
            {MediatorParticipant(
                    model.get(),
                    "PhysicalEntityReference3", local_uri
            )}
    );

    PhysicalForce force(
            model.get(),
            local_uri,
            physical_property,
            source_participants,
            sink_participants
    );
    std::string actual = force.getSubjectStr();
    std::string expected = "http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#metaid";
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
            "#PhysicalEntityReference1", local_uri
    )});
    std::vector<SinkParticipant> sink_participants(
            {SinkParticipant(
                    model.get(),
                    1.0,
                    "PhysicalEntityReference2", local_uri
            )}
    );


    PhysicalForce force(
            model.get(),
            local_uri,
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
            "#PhysicalEntityReference1", local_uri
    )});
    std::vector<SinkParticipant> sink_participants(
            {SinkParticipant(
                    model.get(),
                    1.0,
                    "PhysicalEntityReference2", local_uri
            )}
    );

    PhysicalForce force(
            model.get(),
            local_uri,
            physical_property,
            source_participants,
            sink_participants
    );
    std::string actual = force.getPhysicalProperty().getSubjectStr();
    std::string expected = "http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#metaid";
    ASSERT_STREQ(expected.c_str(), actual.c_str());

    // Without Triple we need to free stuff manually
    force.free();

}


TEST_F(PhysicalForceTests, TestPhysicalForceNumTriples) {
    PhysicalForce force(
            model.get(),
            local_uri,
            physical_property,
            std::vector<SourceParticipant>(
                    {SourceParticipant(
                            model.get(),
                            1.0,
                            "#PhysicalEntityReference1", local_uri
                    )}
            ),
            std::vector<SinkParticipant>(
                    {SinkParticipant(
                            model.get(),
                            1.0,
                            "PhysicalEntityReference2", local_uri
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
            local_uri,
            physical_property,
            std::vector<SourceParticipant>(
                    {SourceParticipant(
                            model.get(),
                            1.0,
                            "#PhysicalEntityReference1", local_uri
                    )}
            ),
            std::vector<SinkParticipant>(
                    {SinkParticipant(
                            model.get(),
                            1.0,
                            "PhysicalEntityReference2", local_uri
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
            local_uri,
            physical_property,
            std::vector<SourceParticipant>(
                    {SourceParticipant(
                            model.get(),
                            1.0,
                            "#PhysicalEntityReference1", local_uri
                    )}
            ),
            std::vector<SinkParticipant>(
                    {SinkParticipant(
                            model.get(),
                            1.0,
                            "PhysicalEntityReference2", local_uri
                    )}
            )
    );

    Triples triples = force.toTriples();
    std::string actual = triples.str();
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:local=\"http://MyOmexLibrary.org/MyOmex.omex/MyModel.rdf#\"\n"
                           "   xmlns:myOMEX=\"http://MyOmexLibrary.org/MyOmex.omex/MyModel.xml\"\n"
                           "   xmlns:myOMEXlib=\"http://MyOmexLibrary.org/MyOmex.omex\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\">\n"
                           "  <rdf:Description rdf:about=\"http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#PhysicalForce0000\">\n"
                           "    <semsim:hasSinkParticipant rdf:resource=\"http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#SinkParticipant0000\"/>\n"
                           "    <semsim:hasSourceParticipant rdf:resource=\"http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#SourceParticipant0000\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#SinkParticipant0000\">\n"
                           "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double\">1</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#PhysicalEntityReference2\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#SourceParticipant0000\">\n"
                           "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double\">1</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#PhysicalEntityReference1\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#metaid\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#PhysicalForce0000\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/OPB/OPB_00340\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n";
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    triples.freeTriples();
}


TEST(PhysicalForceTestsNoFixture, TestPhysicalForceBuilder) {
    std::string local_uri = "http://MyOmexLibrary/myomex.omex/mymodel.rdf#";
    RDF rdf;
    PhysicalForce force(rdf.getModel());
    force.setLocalUri(local_uri);
    //todo considering implementing the builder as a composite builder
    force.setPhysicalProperty("Force5", "OPB:OPB_00340")
            .addSource(1, "#PhysicalEntityReference1")
            .addSink(2, "PhysicalEntityReference2")
            .addSink(1, "PhysicalEntityReference3");

    Triples triples = force.toTriples();
    std::string actual = triples.str();
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:local=\"http://MyOmexLibrary.org/MyOmex.omex/MyModel.rdf#\"\n"
                           "   xmlns:myOMEX=\"http://MyOmexLibrary.org/MyOmex.omex/MyModel.xml\"\n"
                           "   xmlns:myOMEXlib=\"http://MyOmexLibrary.org/MyOmex.omex\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\">\n"
                           "  <rdf:Description rdf:about=\"http://MyOmexLibrary/myomex.omex/mymodel.rdf#Force5\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"http://MyOmexLibrary/myomex.omex/mymodel.rdf#PhysicalForce0000\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/OPB/OPB_00340\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://MyOmexLibrary/myomex.omex/mymodel.rdf#PhysicalForce0000\">\n"
                           "    <semsim:hasSinkParticipant rdf:resource=\"http://MyOmexLibrary/myomex.omex/mymodel.rdf#SinkParticipant0000\"/>\n"
                           "    <semsim:hasSourceParticipant rdf:resource=\"http://MyOmexLibrary/myomex.omex/mymodel.rdf#SourceParticipant0000\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://MyOmexLibrary/myomex.omex/mymodel.rdf#SinkParticipant0000\">\n"
                           "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double\">1</semsim:hasMultiplier>\n"
                           "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double\">2</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"http://MyOmexLibrary/myomex.omex/mymodel.rdf#PhysicalEntityReference2\"/>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"http://MyOmexLibrary/myomex.omex/mymodel.rdf#PhysicalEntityReference3\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://MyOmexLibrary/myomex.omex/mymodel.rdf#SourceParticipant0000\">\n"
                           "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double\">1</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"http://MyOmexLibrary/myomex.omex/mymodel.rdf#PhysicalEntityReference1\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n";
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    triples.freeTriples();
}


TEST(PhysicalForceTestsNoFixture, TestGenerateTheSamePhysicalForceTwice) {
    std::string local_uri = "http://MyOmexLibrary/myomex.omex/mymodel.rdf#";
    RDF rdf;
    PhysicalForce force(rdf.getModel());
    force.setLocalUri(local_uri);
    //todo considering implementing the builder as a composite builder
    force.setPhysicalProperty("Force5", "OPB:OPB_00340")
            .addSource(1, "#PhysicalEntityReference1")
            .addSink(2, "PhysicalEntityReference2")
            .addSink(1, "PhysicalEntityReference3");

    Triples triples1 = force.toTriples();
    std::string actual1 = triples1.str("ntriples", "base");
    std::cout << actual1 << std::endl;
    Triples triples2 = force.toTriples();
    std::string actual2 = triples2.str("ntriples", "base");
    std::cout << actual1 << std::endl;

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
    std::string local_uri = "http://MyOmexLibrary/myomex.omex/mymodel.rdf#";


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
    force1.setLocalUri(local_uri);
    force1.setPhysicalProperty("property_metaid_0", "opb/OPB_00592")
            .addSource(1.0, "species_metaid0")
            .addSource(2.0, "species_metaid1")
            .addSink(1.0, "species_metaid2");

    PhysicalForce force2(model.get());
    force2.setLocalUri(local_uri);
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
    force1.setLocalUri(local_uri);
    force1.setPhysicalProperty("property_metaid_1", "opb/OPB_00592")
            .addSource(1.0, "species_metaid0")
            .addSource(2.0, "species_metaid1")
            .addSink(1.0, "species_metaid2");

    PhysicalForce force2(model.get());
    force2.setLocalUri(local_uri);
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
    force1.setLocalUri(local_uri);
    force1.setPhysicalProperty("property_metaid_0", "opb/OPB_00593")
            .addSource(1.0, "species_metaid0")
            .addSource(2.0, "species_metaid1")
            .addSink(1.0, "species_metaid2");

    PhysicalForce force2(model.get());
    force2.setLocalUri(local_uri);
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
    force1.setLocalUri(local_uri);
    force1.setPhysicalProperty("property_metaid_1", "opb/OPB_00592")
            .addSource(1.0, "species_metaid0")
            .addSource(2.0, "species_metaid1")
            .addSink(1.0, "species_metaid2");

    PhysicalForce force2(model.get());
    force2.setLocalUri(local_uri);
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
    force1.setLocalUri(local_uri);
    force1.setPhysicalProperty("property_metaid_1", "opb/OPB_00592")
            .addSource(1.0, "species_metaid0")
            .addSource(2.0, "species_metaid1")
            .addSink(1.0, "species_metaid2");

    PhysicalForce force2(model.get());
    force2.setLocalUri(local_uri);
    force2.setPhysicalProperty("property_metaid_1", "opb/OPB_00592")
            .addSource(2.0, "species_metaid0")
            .addSource(2.0, "species_metaid1")
            .addSink(1.0, "species_metaid2");
    ASSERT_NE(force1, force2);

    force1.free();
    force2.free();
}




