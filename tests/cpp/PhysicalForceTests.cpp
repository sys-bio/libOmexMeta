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

class PhysicalForceTests : public ::testing::Test {

public:

    librdf_world *world;
    raptor_world *raptorWorld;
    librdf_storage *storage;
    librdf_model *model;

    semsim::PhysicalPropertyResource physical_property;

    PhysicalForceTests() {
        auto initializer = semsim::RDF::init();
        world = std::get<0>(initializer);
        raptorWorld = std::get<1>(initializer);
        storage = std::get<2>(initializer);
        model = std::get<3>(initializer);

        physical_property = semsim::PhysicalPropertyResource(
                // chemical concentration
                world, semsim::RDFURINode(world, "OPB:OPB_00340")
        );
    };
};

TEST_F(PhysicalForceTests, TestPhysicalForceSubjectMetaidNode
) {
semsim::PhysicalForce force(
        world,
        model,
        semsim::Subject(world, semsim::RDFURINode(world, "MetaId004")),
        physical_property,
        std::vector<semsim::SourceParticipant>(
                {semsim::SourceParticipant(
                        world,
                        model,
                        "SourceId1",
                        1.0,
                        "PhysicalEntityReference1"
                )}
        ),
        std::vector<semsim::SinkParticipant>(
                {semsim::SinkParticipant(
                        world,
                        model,
                        "SinkId1",
                        1.0,
                        "PhysicalEntityReference2"
                )}
        )
);

std::string actual = (const char *) librdf_uri_as_string(librdf_node_get_uri(force.getSubject().getNode()));
    std::string expected = "MetaId004";
ASSERT_STREQ(expected
.

c_str(), actual

.

c_str()

);
}


TEST_F(PhysicalForceTests, TestPhysicalForceSource
) {
semsim::PhysicalForce force(
        world,
        model,
        semsim::Subject(world, semsim::RDFURINode(world, "MetaId004")),
        physical_property,
        std::vector<semsim::SourceParticipant>(
                {semsim::SourceParticipant(
                        world,
                        model,
                        "SourceId1",
                        1.0,
                        "PhysicalEntityReference1"
                )}
        ),
        std::vector<semsim::SinkParticipant>(
                {semsim::SinkParticipant(
                        world,
                        model,
                        "SinkId1",
                        1.0,
                        "PhysicalEntityReference2"
                )}
        )
);

semsim::Triples sources_triples = force.getSources()[0].toTriples("sources_metaid");
std::ostringstream actual;
for (
auto &it
: sources_triples) {
    librdf_node_type node_type = librdf_node_get_type(it.getResource().getNode());

if (node_type == LIBRDF_NODE_TYPE_RESOURCE) {
actual <<
librdf_uri_as_string(
        librdf_node_get_uri(
                it.getResource().getNode()
)
) <<
std::endl;
} else if (node_type == LIBRDF_NODE_TYPE_LITERAL) {
actual <<
librdf_node_get_literal_value(it
                                      .

                                              getResource()

                                      .

                                              getNode()

) <<
std::endl;
}

}
std::string expected = "SourceId1\n"
                       "PhysicalEntityReference1\n"
                       "1\n";
ASSERT_STREQ(expected
.

c_str(), actual

.

str()

.

c_str()

);
}


TEST_F(PhysicalForceTests, TestPhysicalForceNumTriples
) {
semsim::PhysicalForce force(
        world,
        model,
        semsim::Subject(world, semsim::RDFURINode(world, "MetaId004")),
        physical_property,
        std::vector<semsim::SourceParticipant>(
                {semsim::SourceParticipant(
                        world,
                        model,
                        "SourceId1",
                        1.0,
                        "PhysicalEntityReference1"
                )}
        ),
        std::vector<semsim::SinkParticipant>(
                {semsim::SinkParticipant(
                        world,
                        model,
                        "SinkId1",
                        1.0,
                        "PhysicalEntityReference2"
                )}
        )
);

semsim::Triples triples = force.toTriples();
int expected = 8;
int actual = triples.size();
ASSERT_EQ(expected, actual
);
}


TEST_F(PhysicalForceTests, TestPhysicalForceTrips
) {
semsim::PhysicalForce force(
        world,
        model,
        semsim::Subject(world, semsim::RDFURINode(world, "MetaId004")),
        physical_property,
        std::vector<semsim::SourceParticipant>(
                {semsim::SourceParticipant(
                        world,
                        model,
                        "SourceId1",
                        1.0,
                        "PhysicalEntityReference1"
                )}
        ),
        std::vector<semsim::SinkParticipant>(
                {semsim::SinkParticipant(
                        world,
                        model,
                        "SinkId1",
                        1.0,
                        "PhysicalEntityReference2"
                )}
        )
);

semsim::Triples triples = force.toTriples();
int expected = 8;
int actual = triples.size();
ASSERT_EQ(expected, actual
);
}


TEST_F(PhysicalForceTests, TestPhysicalForceTriples
) {
semsim::PhysicalForce force(
        world,
        model,
        semsim::Subject(world, semsim::RDFURINode(world, "ForceId0000")),
        physical_property,
        std::vector<semsim::SourceParticipant>(
                {semsim::SourceParticipant(
                        world,
                        model,
                        "SourceId1",
                        1.0,
                        "PhysicalEntityReference1"
                )}
        ),
        std::vector<semsim::SinkParticipant>(
                {semsim::SinkParticipant(
                        world,
                        model,
                        "SinkId1",
                        1.0,
                        "PhysicalEntityReference2"
                )}
        )
);

semsim::Triples triples = force.toTriples();
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
                       "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/2001/XMLSchema#double\">1</semsim:hasMultiplier>\n"
                       "    <semsim:hasPhysicalEntityReference rdf:resource=\"PhysicalEntityReference2\"/>\n"
                       "  </rdf:Description>\n"
                       "  <rdf:Description rdf:about=\"SourceId1\">\n"
                       "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/2001/XMLSchema#double\">1</semsim:hasMultiplier>\n"
                       "    <semsim:hasPhysicalEntityReference rdf:resource=\"PhysicalEntityReference1\"/>\n"
                       "  </rdf:Description>\n"
                       "</rdf:RDF>\n"
                       "";
std::cout << actual <<
std::endl;
ASSERT_STREQ(expected
.

c_str(), actual

.

c_str()

);
}


TEST_F(PhysicalForceTests, TestPhysicalForceBuilder
) {
semsim::PhysicalForce force(world, model);
force.setAbout("Force5")
.
setPhysicalProperty(physical_property)
.addSource("Source1", 1, "PhysicalEntityReference1")
.addSink("Sink1", 2, "PhysicalEntityReference2")
.addSink("Sink2", 1, "PhysicalEntityReference3");


semsim::Triples triples = force.toTriples();
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
                       "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/2001/XMLSchema#double\">2</semsim:hasMultiplier>\n"
                       "    <semsim:hasPhysicalEntityReference rdf:resource=\"PhysicalEntityReference2\"/>\n"
                       "  </rdf:Description>\n"
                       "  <rdf:Description rdf:about=\"Sink2\">\n"
                       "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/2001/XMLSchema#double\">1</semsim:hasMultiplier>\n"
                       "    <semsim:hasPhysicalEntityReference rdf:resource=\"PhysicalEntityReference3\"/>\n"
                       "  </rdf:Description>\n"
                       "  <rdf:Description rdf:about=\"Source1\">\n"
                       "    <semsim:hasMultiplier rdf:datatype=\"http://www.w3.org/2001/XMLSchema#double\">1</semsim:hasMultiplier>\n"
                       "    <semsim:hasPhysicalEntityReference rdf:resource=\"PhysicalEntityReference1\"/>\n"
                       "  </rdf:Description>\n"
                       "</rdf:RDF>\n"
                       "";
std::cout << actual <<
std::endl;
ASSERT_STREQ(expected
.

c_str(), actual

.

c_str()

);
}

