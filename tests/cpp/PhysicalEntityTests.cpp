//
// Created by Ciaran on 4/22/2020.
//

#include <semsim/RDF.h>
#include <vector>
#include "gtest/gtest.h"
#include "librdf.h"
#include "semsim/PhysicalEntity.h"
#include "vector"

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
    PhysicalEntity physicalEntity(
            model.get(),
            Subject::fromRawPtr(LibrdfNode::fromUriString("Metaid0034")),
            physical_property,
            Resource::fromRawPtr(LibrdfNode::fromUriString("obo/PR_000000365")), // is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:72564")),
                     Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:63877"))
                    })
    );
    std::string actual = physicalEntity.getSubject().str();
    std::string expected = "Metaid0034";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    //clear up as we didn't use Triple (which owns everything)
    physicalEntity.free();
}

TEST_F(PhysicalEntityTests, TestGetSubjectMetaidFromNode) {
    PhysicalEntity physicalEntity(
            model.get(),
            Subject::fromRawPtr(LibrdfNode::fromUriString("Metaid0034")),
            physical_property,
            Resource::fromRawPtr(LibrdfNode::fromUriString("obo/PR_000000365")), // is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:72564")),
                     Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:63877"))
                    })
    );
    std::string actual = (const char *) librdf_uri_as_string(
            librdf_node_get_uri(physicalEntity.getSubject().getNode()));
    std::string expected = "Metaid0034";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    //clear up as we didn't use Triple (which owns everything)
    physicalEntity.free();
}

TEST_F(PhysicalEntityTests, TestGetPhysicalPropertyNode) {
    PhysicalEntity physicalEntity(
            model.get(),
            Subject::fromRawPtr(LibrdfNode::fromUriString("Metaid0034")),
            physical_property,
            Resource::fromRawPtr(LibrdfNode::fromUriString("obo/PR_000000365")), // is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:72564")),
                     Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:63877"))
                    })
    );
    std::string actual = (const char *) librdf_uri_as_string(
            librdf_node_get_uri(physicalEntity.getPhysicalProperty().getNode()));
    std::string expected = "https://identifiers.org/OPB/OPB_00340";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    //clear up as we didn't use Triple (which owns everything)
    physicalEntity.free();
}

TEST_F(PhysicalEntityTests, TestGetPhysicalPropertyStr) {
    PhysicalEntity physicalEntity(
            model.get(),
            Subject::fromRawPtr(LibrdfNode::fromUriString("Metaid0034")),
            physical_property,
            Resource::fromRawPtr(LibrdfNode::fromUriString("obo/PR_000000365")), // is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:72564")),
                     Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:63877"))
                    })
    );
    std::string actual = physicalEntity.getPhysicalProperty().str();
    std::string expected = "https://identifiers.org/OPB/OPB_00340";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    //clear up as we didn't use Triple (which owns everything)
    physicalEntity.free();
}


TEST_F(PhysicalEntityTests, TestIdentityResourceStr) {
    PhysicalEntity physicalEntity(
            model.get(),
            Subject::fromRawPtr(LibrdfNode::fromUriString("Metaid0034")),
            physical_property,
            Resource::fromRawPtr(LibrdfNode::fromUriString("obo/PR_000000365")), // is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:72564")),
                     Resource::fromRawPtr(LibrdfNode::fromUriString("fma:FMA:63877"))
                    })
    );
    std::string actual = physicalEntity.getIdentityResource().str();
    std::string expected = "https://identifiers.org/obo/PR_000000365";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    //clear up as we didn't use Triple (which owns everything)
    physicalEntity.free();
}


TEST_F(PhysicalEntityTests, TestIdentityResourceNode) {
    PhysicalEntity physicalEntity(
            model.get(),
            Subject::fromRawPtr(LibrdfNode::fromUriString("Metaid0034")),
            physical_property,
            Resource::fromRawPtr(LibrdfNode::fromUriString("obo/PR_000000365")), // is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:72564")),
                     Resource::fromRawPtr(LibrdfNode::fromUriString("fma:FMA:63877"))
                    })
    );
    std::string actual = (const char *) librdf_uri_as_string(
            librdf_node_get_uri(physicalEntity.getIdentityResource().getNode()));
    std::string expected = "https://identifiers.org/obo/PR_000000365";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    //clear up as we didn't use Triple (which owns everything)
    physicalEntity.free();
}

TEST_F(PhysicalEntityTests, TestLocationResourceStr) {
    PhysicalEntity physicalEntity(
            model.get(),
            Subject::fromRawPtr(LibrdfNode::fromUriString("Metaid0034")),
            physical_property,
            Resource::fromRawPtr(LibrdfNode::fromUriString("obo/PR_000000365")), // is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:72564")),
                     Resource::fromRawPtr(LibrdfNode::fromUriString("fma:FMA:63877"))
                    })
    );
    std::ostringstream actual;
    for (auto &it: physicalEntity.getLocationResources()) {
        actual << it.str() << std::endl;
    }
    std::string expected = "https://identifiers.org/fma/FMA:72564\n"
                           "https://identifiers.org/fma/FMA:63877\n";
    ASSERT_STREQ(expected.c_str(), actual.str().c_str());
    //clear up as we didn't use Triple (which owns everything)
    physicalEntity.free();
}

TEST_F(PhysicalEntityTests, TestLocationResourceNode) {
    PhysicalEntity physicalEntity(
            model.get(),
            Subject::fromRawPtr(LibrdfNode::fromUriString("Metaid0034")),
            physical_property,
            Resource::fromRawPtr(LibrdfNode::fromUriString("obo/PR_000000365")), // is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:72564")),
                     Resource::fromRawPtr(LibrdfNode::fromUriString("fma:FMA:63877"))
                    })
    );
    std::ostringstream actual;
    for (auto &it: physicalEntity.getLocationResources()) {
        actual << librdf_uri_as_string(librdf_node_get_uri(it.getNode())) << std::endl;
    }
    std::string expected = "https://identifiers.org/fma/FMA:72564\n"
                           "https://identifiers.org/fma/FMA:63877\n";
    ASSERT_STREQ(expected.c_str(), actual.str().c_str());
    //clear up as we didn't use Triple (which owns everything)
    physicalEntity.free();
}

TEST_F(PhysicalEntityTests, TestSubject) {
    PhysicalEntity physicalEntity(
            model.get(),
            Subject::fromRawPtr(LibrdfNode::fromUriString("Metaid0034")),
            physical_property,
            Resource::fromRawPtr(LibrdfNode::fromUriString("obo/PR_000000365")), // is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:72564")),
                     Resource::fromRawPtr(LibrdfNode::fromUriString("fma:FMA:63877"))
                    })
    );
    std::string actual = physicalEntity.getSubject().str();
    std::string expected = "Metaid0034";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    //clear up as we didn't use Triple (which owns everything)
    physicalEntity.free();
}

TEST_F(PhysicalEntityTests, TestSubjectFromAbout) {
    PhysicalEntity physicalEntity(
            model.get(),
            Subject::fromRawPtr(LibrdfNode::fromUriString("Metaid0034")),
            physical_property,
            Resource::fromRawPtr(LibrdfNode::fromUriString("obo/PR_000000365")), // is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:72564")),
                     Resource::fromRawPtr(LibrdfNode::fromUriString("fma:FMA:63877"))
                    })
    );
    std::string actual = physicalEntity.getAbout().str();
    std::string expected = "Metaid0034";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    //clear up as we didn't use Triple (which owns everything)
    physicalEntity.free();
}

TEST_F(PhysicalEntityTests, TestAboutIsSet) {
    PhysicalEntity physicalEntity(
            model.get(),
            Subject::fromRawPtr(LibrdfNode::fromUriString("Metaid0034")),
            physical_property,
            Resource::fromRawPtr(LibrdfNode::fromUriString("obo/PR_000000365")), // is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:72564")),
                     Resource::fromRawPtr(LibrdfNode::fromUriString("fma:FMA:63877"))
                    })
    );
    std::cout << physicalEntity.getAbout().str() << std::endl;
    ASSERT_TRUE(physicalEntity.getAbout().isSet());
    //clear up as we didn't use Triple (which owns everything)
    physicalEntity.free();
}

TEST_F(PhysicalEntityTests, TestToTripleSize) {
    Resource is = Resource::fromRawPtr(LibrdfNode::fromUriString("obo/PR_000000365")); // is smad3
    Subject subject = Subject::fromRawPtr(LibrdfNode::fromUriString("Metaid0034"));
    std::vector<Resource> ispartof(
            {Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:72564")),
             Resource::fromRawPtr(LibrdfNode::fromUriString("fma:FMA:63877"))
            });

    /*
     * if passing in a Subject to property resource
     * does not work, lets just make subject take a string and we
     * build internally
     */
    PhysicalEntity physicalEntity(
            model.get(),
            subject,
            physical_property,
            is, ispartof
    );
//    physicalEntity.free();

    // So how does triples free subject / predicate?
    Triples triples = physicalEntity.toTriples();
//    int expected = 5;
//    int actual = triples.size();
//    ASSERT_EQ(expected, actual);
    subject.free();

    // so the subject is not being directly used in a triple.Why not?
}


TEST_F(PhysicalEntityTests, TestTriples) {
    PhysicalEntity physicalEntity(
            model.get(),
            Subject::fromRawPtr(LibrdfNode::fromUriString("Metaid0034")),
            physical_property,
            Resource::fromRawPtr(LibrdfNode::fromUriString("obo/PR_000000365")), // is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:72564")),
                     Resource::fromRawPtr(LibrdfNode::fromUriString("fma:FMA:63877"))
                    })
    );
    std::cout << physicalEntity.toTriples().str() << std::endl;
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
    HERE();
    Triples triples = physicalEntity.toTriples();
    HERE();
    std::string s = triples.str();
    HERE();
    ASSERT_STREQ(s.c_str(), expected.c_str());
}

TEST_F(PhysicalEntityTests, TestPhysicalPropertyIsSet) {
    PhysicalEntity physicalEntity(
            model.get(),
            Subject::fromRawPtr(LibrdfNode::fromUriString("Metaid0034")),
            physical_property,
            Resource::fromRawPtr(LibrdfNode::fromUriString("obo/PR_000000365")), // is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:72564")),
                     Resource::fromRawPtr(LibrdfNode::fromUriString("fma:FMA:63877"))
                    })
    );
    ASSERT_TRUE(physicalEntity.getPhysicalProperty().isSet());
    //clear up as we didn't use Triple (which owns everything)
    physicalEntity.free();
}


TEST_F(PhysicalEntityTests, TestPhysicalEntityBuilderInterface) {
    PhysicalEntity physicalEntity(model.get());
    physicalEntity.setAbout("VLV")
            .setPhysicalProperty("OPB:OPB_00154")
            .setIdentity("fma/FMA:9690")
            .addLocation("fma:FMA:18228");

    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"PhysicalEntity0000\">\n"
                           "    <bqbiol:is rdf:resource=\"https://identifiers.org/fma/FMA:9690\"/>\n"
                           "    <bqbiol:isPartOf rdf:resource=\"https://identifiers.org/fma/FMA:18228\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"VLV\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"PhysicalEntity0000\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/OPB/OPB_00154\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    ASSERT_STREQ(physicalEntity.toTriples().str().c_str(), expected.c_str());

}


TEST_F(PhysicalEntityTests, TestPhysicalEntityBuilderIsPhysicalPropertySet) {
    PhysicalEntity physicalEntity(model.get());
    physicalEntity = physicalEntity.setPhysicalProperty(physical_property);
    ASSERT_TRUE(physicalEntity.getPhysicalProperty().isSet());
    //clear up as we didn't use Triple (which owns everything)
    physicalEntity.free();
}

TEST_F(PhysicalEntityTests, TestPhysicalEntityBuilderAddTwoItems) {
    PhysicalEntity physicalEntity(model.get());
    physicalEntity = physicalEntity
            .setPhysicalProperty(physical_property)
            .setAbout("cheese");
    ASSERT_TRUE(physicalEntity.getPhysicalProperty().isSet());
    ASSERT_TRUE(physicalEntity.getAbout().isSet());
    physicalEntity.free();
}

TEST_F(PhysicalEntityTests, TestPhysicalEntityBuilderAddTwoItemsWhenYouAddPhysicalPropertySecond) {
    PhysicalEntity physicalEntity(model.get());
    physicalEntity.setAbout("cheese").setPhysicalProperty(physical_property);
    ASSERT_TRUE(physicalEntity.getAbout().isSet());
    ASSERT_TRUE(physicalEntity.getPhysicalProperty().isSet());
    physicalEntity.free();
}

TEST_F(PhysicalEntityTests, TestPhysicalEntityBuilder) {
    PhysicalEntity physicalEntity(model.get());
    physicalEntity.setAbout("Metaid0034")
            .setPhysicalProperty(physical_property)
            .setIdentity("obo/PR_000000365")
            .addLocation("https://identifiers.org/fma/FMA:72564")
            .addLocation("fma:FMA:63877");
    ASSERT_TRUE(physicalEntity.getAbout().isSet());
    ASSERT_TRUE(physicalEntity.getPhysicalProperty().isSet());
    physicalEntity.free();
}


TEST_F(PhysicalEntityTests, TestPhysicalEntityBuilderToTriples) {
    PhysicalEntity physicalEntity(model.get());
    physicalEntity.setAbout("Metaid0034")
            .setPhysicalProperty(physical_property)
            .setIdentity("obo/PR_000000365")
            .addLocation("https://identifiers.org/fma/FMA:72564")
            .addLocation("fma:FMA:63877");

    std::string actual = physicalEntity.toTriples().str();
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
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}









