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

class PhysicalProcessTests : public ::testing::Test {

public:

    librdf_world *world;
    raptor_world *raptorWorld;
    librdf_storage *storage;
    librdf_model *model;

    semsim::PhysicalPropertyResource physical_property;

    PhysicalProcessTests() {
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

TEST_F(PhysicalProcessTests, TestPhysicalProcessSubjectMetaidNode) {
    semsim::PhysicalProcess process(
            world,
            semsim::Subject(world, semsim::RDFURINode(world, "MetaId004")),
            physical_property,
            std::vector<semsim::SourceParticipant>(
                    {semsim::SourceParticipant(
                            world,
                            "SourceId1",
                            semsim::Resource(world, semsim::RDFURINode(world, "fake/identifier003")),
                            1.0,
                            "PhysicalEntityReference1"
                    )}
            ),
            std::vector<semsim::SinkParticipant>(
                    {semsim::SinkParticipant(
                            world,
                            "SinkId1",
                            semsim::Resource(world, semsim::RDFURINode(world, "fake/identifier004")),
                            1.0,
                            "PhysicalEntityReference2"
                    )}
            ),
            std::vector<semsim::MediatorParticipant>(
                    {semsim::MediatorParticipant(
                            world,
                            "MediatorID1",
                            semsim::Resource(world, semsim::RDFURINode(world, "fake/identifier005")),
                            "PhysicalEntityReference3"
                    )}
            )
    );

    std::string actual = (const char *) librdf_uri_as_string(librdf_node_get_uri(process.getSubject().toRdfNode()));
    std::string expected = "MetaId004";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(PhysicalProcessTests, TestPhysicalProcessSource) {
    semsim::PhysicalProcess process(
            world,
            semsim::Subject(world, semsim::RDFURINode(world, "MetaId004")),
            physical_property,
            std::vector<semsim::SourceParticipant>(
                    {semsim::SourceParticipant(
                            world,
                            "SourceId1",
                            semsim::Resource(world, semsim::RDFURINode(world, "fake/identifier003")),
                            1.0,
                            "PhysicalEntityReference1"
                    )}
            ),
            std::vector<semsim::SinkParticipant>(
                    {semsim::SinkParticipant(
                            world,
                            "SinkId1",
                            semsim::Resource(world, semsim::RDFURINode(world, "fake/identifier004")),
                            1.0,
                            "PhysicalEntityReference2"
                    )}
            ),
            std::vector<semsim::MediatorParticipant>(
                    {semsim::MediatorParticipant(
                            world,
                            "MediatorID1",
                            semsim::Resource(world, semsim::RDFURINode(world, "fake/identifier005")),
                            "PhysicalEntityReference3"
                    )}
            )
    );

    semsim::Triples sources_triples = process.getSources()[0].toTriples();
    std::ostringstream actual;
    for (auto &it : sources_triples) {
        librdf_node_type node_type = librdf_node_get_type(it.getResource().toRdfNode());

        if (node_type == LIBRDF_NODE_TYPE_RESOURCE) {
            actual << librdf_uri_as_string(
                    librdf_node_get_uri(
                            it.getResource().toRdfNode()
                    )
            ) << std::endl;
        } else if (node_type == LIBRDF_NODE_TYPE_LITERAL) {
            actual << librdf_node_get_literal_value(it.getResource().toRdfNode()) << std::endl;
        }

    }
    std::string expected = "https://identifiers.org/fake/identifier003\n"
                           "PhysicalEntityReference1\n"
                           "1\n";
    ASSERT_STREQ(expected.c_str(), actual.str().c_str());
}


TEST_F(PhysicalProcessTests, TestPhysicalProcessNumTriples) {
    semsim::PhysicalProcess process(
            world,
            semsim::Subject(world, semsim::RDFURINode(world, "MetaId004")),
            physical_property,
            std::vector<semsim::SourceParticipant>(
                    {semsim::SourceParticipant(
                            world,
                            "SourceId1",
                            semsim::Resource(world, semsim::RDFURINode(world, "fake/identifier003")),
                            1.0,
                            "PhysicalEntityReference1"
                    )}
            ),
            std::vector<semsim::SinkParticipant>(
                    {semsim::SinkParticipant(
                            world,
                            "SinkId1",
                            semsim::Resource(world, semsim::RDFURINode(world, "fake/identifier004")),
                            1.0,
                            "PhysicalEntityReference2"
                    )}
            ),
            std::vector<semsim::MediatorParticipant>(
                    {semsim::MediatorParticipant(
                            world,
                            "MediatorID1",
                            semsim::Resource(world, semsim::RDFURINode(world, "fake/identifier005")),
                            "PhysicalEntityReference3"
                    )}
            )
    );

    semsim::Triples triples = process.toTriples();
    int expected = 9;
    int actual = triples.size();
    ASSERT_EQ(expected, actual);
}


TEST_F(PhysicalProcessTests, TestPhysicalProcessTrips) {
    semsim::RDF rdf;

    semsim::PhysicalProcess process(
            world,
            semsim::Subject(world, semsim::RDFURINode(world, "MetaId004")),
            physical_property,
            std::vector<semsim::SourceParticipant>(
                    {semsim::SourceParticipant(
                            world,
                            "SourceId1",
                            semsim::Resource(world, semsim::RDFURINode(world, "fake/identifier003")),
                            1.0,
                            "PhysicalEntityReference1"
                    )}
            ),
            std::vector<semsim::SinkParticipant>(
                    {semsim::SinkParticipant(
                            world,
                            "SinkId1",
                            semsim::Resource(world, semsim::RDFURINode(world, "fake/identifier004")),
                            1.0,
                            "PhysicalEntityReference2"
                    )}
            ),
            std::vector<semsim::MediatorParticipant>(
                    {semsim::MediatorParticipant(
                            world,
                            "MediatorID1",
                            semsim::Resource(world, semsim::RDFURINode(world, "fake/identifier005")),
                            "PhysicalEntityReference3"
                    )}
            )
    );
    semsim::Triples triples = process.toTriples();

    int expected = 9;
    int actual = triples.size();
    ASSERT_EQ(expected, actual);
}

