//
// Created by Ciaran on 4/22/2020.
//

#include <semsim/RDF.h>
#include <vector>
#include "gtest/gtest.h"
#include "librdf.h"
#include "semsim/PhysicalEntity.h"

using namespace semsim;

class PhysicalEntityTests : public ::testing::Test {

    
public:

    LibrdfStorage storage;
    LibrdfModel model;

    PhysicalPropertyResource physical_property;

    PhysicalEntityTests() {
        model = LibrdfModel(storage);

        physical_property = PhysicalPropertyResource("OPB:OPB_00340");
    };
};


TEST_F(PhysicalEntityTests, TestGetSubjectMetaidStr) {
    RDF rdf;
    PhysicalEntity physicalEntity(
            model,
            Subject::fromRawPtr( LibrdfNode::fromUriString( "Metaid0034")),
            physical_property,
            Resource::fromRawPtr( LibrdfNode::fromUriString( "obo/PR_000000365")), // is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr( LibrdfNode::fromUriString( "https://identifiers.org/fma/FMA:72564")),
                     Resource::fromRawPtr( LibrdfNode::fromUriString( "https://identifiers.org/fma/FMA:63877"))
                    })
    );
    std::string actual = physicalEntity.getSubject().str();
    std::string expected = "Metaid0034";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PhysicalEntityTests, TestGetSubjectMetaidFromNode) {
    RDF rdf;
    PhysicalEntity physicalEntity(
            model,
            Subject::fromRawPtr( LibrdfNode::fromUriString( "Metaid0034")),
            physical_property,
            Resource::fromRawPtr( LibrdfNode::fromUriString( "obo/PR_000000365")), // is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr( LibrdfNode::fromUriString( "https://identifiers.org/fma/FMA:72564")),
                     Resource::fromRawPtr( LibrdfNode::fromUriString( "https://identifiers.org/fma/FMA:63877"))
                    })
    );
    std::string actual = (const char *) librdf_uri_as_string(
            librdf_node_get_uri(physicalEntity.getSubject().getNode()));
    std::string expected = "Metaid0034";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PhysicalEntityTests, TestGetPhysicalPropertyNode) {
    RDF rdf;
    PhysicalEntity physicalEntity(
            model,
            Subject::fromRawPtr( LibrdfNode::fromUriString( "Metaid0034")),
            physical_property,
            Resource::fromRawPtr( LibrdfNode::fromUriString( "obo/PR_000000365")), // is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr( LibrdfNode::fromUriString( "https://identifiers.org/fma/FMA:72564")),
                     Resource::fromRawPtr( LibrdfNode::fromUriString( "https://identifiers.org/fma/FMA:63877"))
                    })
    );
    std::string actual = (const char *) librdf_uri_as_string(
            librdf_node_get_uri(physicalEntity.getPhysicalProperty().getNode()));
    std::string expected = "https://identifiers.org/OPB/OPB_00340";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PhysicalEntityTests, TestGetPhysicalPropertyStr) {
    RDF rdf;
    PhysicalEntity physicalEntity(
            
            model,
            Subject::fromRawPtr( LibrdfNode::fromUriString( "Metaid0034")),
            physical_property,
            Resource::fromRawPtr( LibrdfNode::fromUriString( "obo/PR_000000365")), // is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr( LibrdfNode::fromUriString( "https://identifiers.org/fma/FMA:72564")),
                     Resource::fromRawPtr( LibrdfNode::fromUriString( "https://identifiers.org/fma/FMA:63877"))
                    })
    );
    std::string actual = physicalEntity.getPhysicalProperty().str();
    std::string expected = "https://identifiers.org/OPB/OPB_00340";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(PhysicalEntityTests, TestIdentityResourceStr) {
    RDF rdf;
    PhysicalEntity physicalEntity(
            
            model,
            Subject::fromRawPtr( LibrdfNode::fromUriString( "Metaid0034")),
            physical_property,
            Resource::fromRawPtr( LibrdfNode::fromUriString( "obo/PR_000000365")), // is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr( LibrdfNode::fromUriString( "https://identifiers.org/fma/FMA:72564")),
                     Resource::fromRawPtr( LibrdfNode::fromUriString( "fma:FMA:63877"))
                    })
    );
    std::string actual = physicalEntity.getIdentityResource().str();
    std::string expected = "https://identifiers.org/obo/PR_000000365";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(PhysicalEntityTests, TestIdentityResourceNode) {
    RDF rdf;
    PhysicalEntity physicalEntity(
            
            model,
            Subject::fromRawPtr( LibrdfNode::fromUriString( "Metaid0034")),
            physical_property,
            Resource::fromRawPtr( LibrdfNode::fromUriString( "obo/PR_000000365")), // is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr( LibrdfNode::fromUriString( "https://identifiers.org/fma/FMA:72564")),
                     Resource::fromRawPtr( LibrdfNode::fromUriString( "fma:FMA:63877"))
                    })
    );
    std::string actual = (const char *) librdf_uri_as_string(
            librdf_node_get_uri(physicalEntity.getIdentityResource().getNode()));
    std::string expected = "https://identifiers.org/obo/PR_000000365";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PhysicalEntityTests, TestLocationResourceStr) {
    RDF rdf;
    PhysicalEntity physicalEntity(
            
            model,
            Subject::fromRawPtr( LibrdfNode::fromUriString( "Metaid0034")),
            physical_property,
            Resource::fromRawPtr( LibrdfNode::fromUriString( "obo/PR_000000365")), // is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr( LibrdfNode::fromUriString( "https://identifiers.org/fma/FMA:72564")),
                     Resource::fromRawPtr( LibrdfNode::fromUriString( "fma:FMA:63877"))
                    })
    );
    std::ostringstream actual;
    for (auto &it: physicalEntity.getLocationResources()) {
        actual << it.str()<<std::endl;
    }
    std::string expected = "https://identifiers.org/fma/FMA:72564\n"
                           "https://identifiers.org/fma/FMA:63877\n";
    ASSERT_STREQ(expected.c_str(), actual.str().c_str());
}

TEST_F(PhysicalEntityTests, TestLocationResourceNode) {
    RDF rdf;
    PhysicalEntity physicalEntity(
            model,
            Subject::fromRawPtr( LibrdfNode::fromUriString( "Metaid0034")),
            physical_property,
            Resource::fromRawPtr( LibrdfNode::fromUriString( "obo/PR_000000365")), // is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr( LibrdfNode::fromUriString( "https://identifiers.org/fma/FMA:72564")),
                     Resource::fromRawPtr( LibrdfNode::fromUriString( "fma:FMA:63877"))
                    })
    );
    std::ostringstream actual;
    for (auto &it: physicalEntity.getLocationResources()) {
        actual << librdf_uri_as_string(librdf_node_get_uri(it.getNode())) <<std::endl;
    }
    std::string expected = "https://identifiers.org/fma/FMA:72564\n"
                           "https://identifiers.org/fma/FMA:63877\n";
    ASSERT_STREQ(expected.c_str(), actual.str().c_str());
}

TEST_F(PhysicalEntityTests, TestToTripleSize) {
    RDF rdf;
    PhysicalEntity physicalEntity(
            
            model,
            Subject::fromRawPtr( LibrdfNode::fromUriString( "Metaid0034")),
            physical_property,
            Resource::fromRawPtr( LibrdfNode::fromUriString( "obo/PR_000000365")), // is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr( LibrdfNode::fromUriString( "https://identifiers.org/fma/FMA:72564")),
                     Resource::fromRawPtr( LibrdfNode::fromUriString( "fma:FMA:63877"))
                    })
    );

    Triples triples = physicalEntity.toTriples();
    int expected = 5;
    int actual = triples.size();
    ASSERT_EQ(expected, actual
    );
}


TEST_F(PhysicalEntityTests, TestTriples) {
    RDF rdf;
    PhysicalEntity physicalEntity(
            model,
            Subject::fromRawPtr( LibrdfNode::fromUriString( "Metaid0034")),
            physical_property,
            Resource::fromRawPtr( LibrdfNode::fromUriString( "obo/PR_000000365")), // is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr( LibrdfNode::fromUriString( "https://identifiers.org/fma/FMA:72564")),
                     Resource::fromRawPtr( LibrdfNode::fromUriString( "fma:FMA:63877"))
                    })
    );
    std::cout << physicalEntity.toTriples().str()<<std::endl;
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"Metaid0034\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"PhysicalEntity0000\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/OPB/OPB_00340\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"PhysicalEntity0000\">\n"
                           "    <bqbiol:is rdf:resource=\"https://identifiers.org/obo/PR_000000365\"/>\n"
                           "    <bqbiol:isPartOf rdf:resource=\"https://identifiers.org/fma/FMA:63877\"/>\n"
                           "    <bqbiol:isPartOf rdf:resource=\"https://identifiers.org/fma/FMA:72564\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    ASSERT_STREQ(physicalEntity.toTriples().str().c_str(),
            expected.c_str());
}

TEST_F(PhysicalEntityTests, TestPhysicalPropertyIsSet) {
    RDF rdf;
    PhysicalEntity physicalEntity(
            model,
            Subject::fromRawPtr( LibrdfNode::fromUriString( "Metaid0034")),
            physical_property,
            Resource::fromRawPtr( LibrdfNode::fromUriString( "obo/PR_000000365")), // is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr( LibrdfNode::fromUriString( "https://identifiers.org/fma/FMA:72564")),
                     Resource::fromRawPtr( LibrdfNode::fromUriString( "fma:FMA:63877"))
                    })
    );
    ASSERT_TRUE(physicalEntity.getPhysicalProperty().isSet());
}


//TEST_F(PhysicalEntityTests, TestPhysicalEntityBuilderInterface) {
//    RDF rdf;
//    PhysicalEntity physicalEntity( rdf.getModel());
//
//    physicalEntity.setAbout("VLV")
//            .setPhysicalProperty("OPB:OPB_00154")
//            .setIdentity("fma/FMA:9690")
//            .addLocation("fma:FMA:18228");
//
//    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
//                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
//                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
//                           "   xml:base=\"file://./annotations.rdf\">\n"
//                           "  <rdf:Description rdf:about=\"PhysicalEntity0000\">\n"
//                           "    <bqbiol:is rdf:resource=\"https://identifiers.org/fma/FMA:9690\"/>\n"
//                           "    <bqbiol:isPartOf rdf:resource=\"https://identifiers.org/fma/FMA:18228\"/>\n"
//                           "  </rdf:Description>\n"
//                           "  <rdf:Description rdf:about=\"VLV\">\n"
//                           "    <bqbiol:isPropertyOf rdf:resource=\"PhysicalEntity0000\"/>\n"
//                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/OPB/OPB_00154\"/>\n"
//                           "  </rdf:Description>\n"
//                           "</rdf:RDF>\n"
//                           "";
//    ASSERT_STREQ(physicalEntity.toTriples().str().c_str(), expected.c_str());
//}


//TEST_F(PhysicalEntityTests, TestPhysicalEntityBuilderIsPhysicalPropertySet) {
//    RDF rdf;
//    PhysicalEntity physicalEntity(rdf.model);
//    physicalEntity = physicalEntity.setPhysicalProperty(physical_property);
//    ASSERT_TRUE(physicalEntity.getPhysicalProperty().isSet()    );
//}

//TEST_F(PhysicalEntityTests, TestPhysicalEntityBuilderAddTwoItems) {
//    RDF rdf;
//    PhysicalEntity physicalEntity(rdf.model_);
//    physicalEntity = physicalEntity
//            .setPhysicalProperty(physical_property)
//            .setAbout("cheese");
//    ASSERT_TRUE(physicalEntity.getPhysicalProperty().isSet());
//    ASSERT_TRUE(physicalEntity.getAbout().isSet());
//}

//TEST_F(PhysicalEntityTests, TestPhysicalEntityBuilderAddTwoItemsWhenYouAddPhysicalPropertySecond) {
//    RDF rdf;
//    PhysicalEntity physicalEntity(rdf.model_);
//    physicalEntity.setAbout("cheese").setPhysicalProperty(physical_property);
//    ASSERT_TRUE(physicalEntity.getAbout().isSet());
//    ASSERT_TRUE(physicalEntity.getPhysicalProperty().isSet());
//}

//TEST_F(PhysicalEntityTests, TestPhysicalEntityBuilder) {
//    RDF rdf;
//    PhysicalEntity physicalEntity( rdf.model_);
//    physicalEntity.setAbout("Metaid0034")
//            .setPhysicalProperty(physical_property)
//            .setIdentity("obo/PR_000000365")
//            .addLocation("https://identifiers.org/fma/FMA:72564")
//            .addLocation("fma:FMA:63877");
//    ASSERT_TRUE(physicalEntity.getAbout().isSet());
//    ASSERT_TRUE(physicalEntity.getPhysicalProperty().isSet());
//}
//
//
//TEST_F(PhysicalEntityTests, TestPhysicalEntityBuilderToTriples) {
//    RDF rdf;
//    PhysicalEntity physicalEntity( rdf.model_);
//    physicalEntity.setAbout("Metaid0034")
//            .setPhysicalProperty(physical_property)
//            .setIdentity("obo/PR_000000365")
//            .addLocation("https://identifiers.org/fma/FMA:72564")
//            .addLocation("fma:FMA:63877");
//
//    std::string actual = physicalEntity.toTriples().str();
//    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
//                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
//                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
//                           "   xml:base=\"file://./annotations.rdf\">\n"
//                           "  <rdf:Description rdf:about=\"Metaid0034\">\n"
//                           "    <bqbiol:isPropertyOf rdf:resource=\"PhysicalEntity0000\"/>\n"
//                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/OPB/OPB_00340\"/>\n"
//                           "  </rdf:Description>\n"
//                           "  <rdf:Description rdf:about=\"PhysicalEntity0000\">\n"
//                           "    <bqbiol:is rdf:resource=\"https://identifiers.org/obo/PR_000000365\"/>\n"
//                           "    <bqbiol:isPartOf rdf:resource=\"https://identifiers.org/fma/FMA:63877\"/>\n"
//                           "    <bqbiol:isPartOf rdf:resource=\"https://identifiers.org/fma/FMA:72564\"/>\n"
//                           "  </rdf:Description>\n"
//                           "</rdf:RDF>\n"
//                           "";
//    std::cout << actual << std::endl;
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}









