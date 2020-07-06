//
// Created by Ciaran on 4/22/2020.
//

#include "omexmeta/RDF.h"
#include <vector>
#include "gtest/gtest.h"
#include "librdf.h"
#include "omexmeta/PhysicalEntity.h"
#include "vector"

using namespace semsim;

class PhysicalEntityTests : public ::testing::Test {

public:

    LibrdfStorage storage;
    LibrdfModel model;

    PhysicalProperty physical_property;

    PhysicalEntityTests() {
        model = LibrdfModel(storage.get());

        physical_property = PhysicalProperty("metaid", "OPB:OPB_00340");
    };

    ~PhysicalEntityTests() {
        model.freeModel();
        storage.freeStorage();
    }
};


TEST_F(PhysicalEntityTests, TestGetSubjectMetaidStr) {
    PhysicalEntity physicalEntity(
            model.get(),
            physical_property,
            Resource::fromRawPtr(LibrdfNode::fromUriString("obo/PR_000000365").get()), // is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:72564").get()),
                     Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:63877").get())
                    })
    );
    std::string actual = physicalEntity.getAbout();
    std::string expected = "metaid";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    //clear up as we didn't use Triple (which owns everything)
    physicalEntity.free();
}


TEST_F(PhysicalEntityTests, TestGetPhysicalPropertyNode) {
    PhysicalEntity physicalEntity(
            model.get(),
            physical_property,
            Resource::fromRawPtr(LibrdfNode::fromUriString("obo/PR_000000365").get()), // is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:72564").get()),
                     Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:63877").get())
                    })
    );
    Resource r(LibrdfNode::fromUriString(
            physicalEntity.getPhysicalProperty().getResourceStr())
    );
    std::string actual = r.str();
    std::string expected = "https://identifiers.org/OPB/OPB_00340";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    //clear up as we didn't use Triple (which owns everything)
    physicalEntity.free();
    r.free();
}


TEST_F(PhysicalEntityTests, TestIdentityResourceStr) {
    PhysicalEntity physicalEntity(
            model.get(),
            physical_property,
            Resource::fromRawPtr(LibrdfNode::fromUriString("obo/PR_000000365").get()), // is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:72564").get()),
                     Resource::fromRawPtr(LibrdfNode::fromUriString("fma:FMA:63877").get())
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
            physical_property,
            Resource::fromRawPtr(LibrdfNode::fromUriString("obo/PR_000000365").get()), // is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:72564").get()),
                     Resource::fromRawPtr(LibrdfNode::fromUriString("fma:FMA:63877").get())
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
            physical_property,
            Resource::fromRawPtr(LibrdfNode::fromUriString("obo/PR_000000365").get()), // is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:72564").get()),
                     Resource::fromRawPtr(LibrdfNode::fromUriString("fma:FMA:63877").get())
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
            physical_property,
            Resource::fromRawPtr(LibrdfNode::fromUriString("obo/PR_000000365").get()), // is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:72564").get()),
                     Resource::fromRawPtr(LibrdfNode::fromUriString("fma:FMA:63877").get())
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
            physical_property,
            Resource::fromRawPtr(LibrdfNode::fromUriString("obo/PR_000000365").get()), // is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:72564").get()),
                     Resource::fromRawPtr(LibrdfNode::fromUriString("fma:FMA:63877").get())
                    })
    );
    std::string actual = physicalEntity.getSubjectStr();
    std::string expected = "metaid";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    //clear up as we didn't use Triple (which owns everything)
    physicalEntity.free();
}

TEST_F(PhysicalEntityTests, TestSubjectFromAbout) {
    PhysicalEntity physicalEntity(
            model.get(),
            physical_property,
            Resource::fromRawPtr(LibrdfNode::fromUriString("obo/PR_000000365").get()), // is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:72564").get()),
                     Resource::fromRawPtr(LibrdfNode::fromUriString("fma:FMA:63877").get())
                    })
    );
    std::string actual = physicalEntity.getAbout();
    std::string expected = "metaid";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    //clear up as we didn't use Triple (which owns everything)
    physicalEntity.free();
}

TEST_F(PhysicalEntityTests, TestAboutIsSet) {
    PhysicalEntity physicalEntity(
            model.get(),
            physical_property,
            Resource::fromRawPtr(LibrdfNode::fromUriString("obo/PR_000000365").get()), // is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:72564").get()),
                     Resource::fromRawPtr(LibrdfNode::fromUriString("fma:FMA:63877").get())
                    })
    );
    std::cout << physicalEntity.getAbout() << std::endl;
    ASSERT_FALSE(physicalEntity.getAbout().empty());
    //clear up as we didn't use Triple (which owns everything)
    physicalEntity.free();
}

TEST(PhysicalEntityTestsNoFixture, TestToTripleRefCounts) {
    LibrdfStorage storage;
    LibrdfModel model(storage.get());

    // ensure physical property has 1 reference
    PhysicalProperty property("metaid", "opb:opb_1234");
//    ASSERT_EQ(1, property.getNode()->usage);

    // ensure is resource has 1 reference
    Resource is = Resource::fromRawPtr(LibrdfNode::fromUriString("obo/PR_000000365").get()); // is smad3
    ASSERT_EQ(1, is.getNode()->usage);

    // ensure is ispartof has 1 reference per location
    std::vector<Resource> ispartof;
    ispartof.push_back(std::move(
            Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:72564").get()
            )));
    ispartof.push_back(std::move(
            Resource::fromRawPtr(LibrdfNode::fromUriString("fma:FMA:63877").get())
    ));
    ASSERT_EQ(1, ispartof[0].getNode()->usage);
    ASSERT_EQ(1, ispartof[1].getNode()->usage);

    PhysicalEntity physicalEntity(
            model.get(),
            property,
            is, ispartof
    );

    Triples triples = physicalEntity.toTriples();
//    // unpack triples by move for testing (pop removes from back)
    Triple triple5 = triples.pop();
    Triple triple4 = triples.pop();
    Triple triple3 = triples.pop();
    Triple triple2 = triples.pop();
    Triple triple1 = triples.pop();

    // make sure all triples have a usage count of 1
    ASSERT_EQ(1, triple1.getStatement()->usage);
    ASSERT_EQ(1, triple2.getStatement()->usage);
    ASSERT_EQ(1, triple3.getStatement()->usage);
    ASSERT_EQ(1, triple4.getStatement()->usage);
    ASSERT_EQ(1, triple5.getStatement()->usage);

    // Recently changed PhysicalPProperty which changes triple1 from 2 to 1.
    ASSERT_EQ(1, triple1.getSubject()->usage);
    ASSERT_EQ(1, triple2.getSubject()->usage);
    ASSERT_EQ(1, triple3.getSubject()->usage);
    ASSERT_EQ(1, triple4.getSubject()->usage);
    ASSERT_EQ(1, triple5.getSubject()->usage);

    // All predicate nodes are used once
    ASSERT_EQ(1, triple1.getPredicate()->usage);
    ASSERT_EQ(1, triple2.getPredicate()->usage);
    ASSERT_EQ(1, triple3.getPredicate()->usage);
    ASSERT_EQ(1, triple4.getPredicate()->usage);
    ASSERT_EQ(1, triple5.getPredicate()->usage);

    // All object nodes are used once
    ASSERT_EQ(1, triple1.getResource()->usage);
    ASSERT_EQ(1, triple2.getResource()->usage);
    ASSERT_EQ(1, triple3.getResource()->usage);
    ASSERT_EQ(1, triple4.getResource()->usage);
    ASSERT_EQ(1, triple5.getResource()->usage);

    // and free up resources
    triple1.freeStatement();
    triple2.freeStatement();
    triple3.freeStatement();
    triple4.freeStatement();
    triple5.freeStatement();
    model.freeModel();
    storage.freeStorage();
}

TEST_F(PhysicalEntityTests, TestToTripleSize) {
    Resource is = Resource::fromRawPtr(LibrdfNode::fromUriString("obo/PR_000000365").get()); // is smad3
    std::vector<Resource> ispartof;
    ispartof.push_back(std::move(
            Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:72564").get()
            )));
    ispartof.push_back(std::move(
            Resource::fromRawPtr(LibrdfNode::fromUriString("fma:FMA:63877").get())
    ));

    PhysicalEntity physicalEntity(
            model.get(),
            physical_property,
            is, ispartof
    );

    Triples triples = physicalEntity.toTriples();

    int expected = 5; // 5 because we have two location triples.
    int actual = triples.size();
    ASSERT_EQ(expected, actual);
    triples.freeTriples();
}


TEST_F(PhysicalEntityTests, TestTriples) {
    PhysicalEntity physicalEntity(
            model.get(),
            physical_property,
            Resource::fromRawPtr(LibrdfNode::fromUriString("obo/PR_000000365").get()), // is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:72564").get()),
                     Resource::fromRawPtr(LibrdfNode::fromUriString("fma:FMA:63877").get())
                    })
    );
    Triples triples = physicalEntity.toTriples();
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"#PhysicalEntity0000\">\n"
                           "    <bqbiol:is rdf:resource=\"https://identifiers.org/obo/PR_000000365\"/>\n"
                           "    <bqbiol:isPartOf rdf:resource=\"https://identifiers.org/fma/FMA:63877\"/>\n"
                           "    <bqbiol:isPartOf rdf:resource=\"https://identifiers.org/fma/FMA:72564\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"metaid\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"#PhysicalEntity0000\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/OPB/OPB_00340\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n";
    std::string s = triples.str();
    std::cout << s << std::endl;
    ASSERT_STREQ(s.c_str(), expected.c_str());
    triples.freeTriples();

}




//TEST_F(PhysicalEntityTests, TestCallingToTriplesTwice) {
//    /*
//     * Calling toTriples twice doesn;t seem to work because we free the subject.
//     */
//
//}

//TEST_F(PhysicalEntityTests, TestPhysicalPropertyIsSet) {
//    PhysicalEntity physicalEntity(
//            model.get(),
////            physical_property,
//            Resource::fromRawPtr(LibrdfNode::fromUriString("obo/PR_000000365").get()), // is smad3
//            std::vector<Resource>(
//                    {Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:72564").get()),
//                     Resource::fromRawPtr(LibrdfNode::fromUriString("fma:FMA:63877").get())
//                    })
//    );
////    ASSERT_TRUE(physicalEntity.getPhysicalProperty().isSet());
//    //clear up as we didn't use Triple (which owns everything)
//    physicalEntity.free();
//}


TEST_F(PhysicalEntityTests, TestPhysicalEntityBuilderInterface) {
    PhysicalEntity physicalEntity(model.get());
    physicalEntity
            .setPhysicalProperty("VLV", "OPB:OPB_00154")
            .setIdentity("fma/FMA:9690")
            .addLocation("fma:FMA:18228");

    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"#PhysicalEntity0000\">\n"
                           "    <bqbiol:is rdf:resource=\"https://identifiers.org/fma/FMA:9690\"/>\n"
                           "    <bqbiol:isPartOf rdf:resource=\"https://identifiers.org/fma/FMA:18228\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"VLV\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"#PhysicalEntity0000\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/OPB/OPB_00154\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    Triples triples = physicalEntity.toTriples();
    ASSERT_STREQ(triples.str().c_str(), expected.c_str());
    triples.freeTriples();
//    physical_property.free();
}


//TEST_F(PhysicalEntityTests, TestPhysicalEntityBuilderIsPhysicalPropertySet) {
//    PhysicalEntity physicalEntity(model.get());
//    physicalEntity = physicalEntity.setPhysicalProperty(physical_property);
//    ASSERT_TRUE(physicalEntity.getPhysicalProperty().isSet());
//    //clear up as we didn't use Triple (which owns everything)
//    physicalEntity.free();
//}

TEST_F(PhysicalEntityTests, TestPhysicalEntityBuilderAddTwoItems) {
    PhysicalEntity physicalEntity(model.get());
    physicalEntity
            .setPhysicalProperty(physical_property);
//    ASSERT_TRUE(physicalEntity.getPhysicalProperty().isSet());
    ASSERT_FALSE(physicalEntity.getAbout().empty());
    physicalEntity.free();
}

TEST_F(PhysicalEntityTests, TestPhysicalEntityBuilderAddTwoItemsWhenYouAddPhysicalPropertySecond) {
    PhysicalEntity physicalEntity(model.get());
    physicalEntity.setPhysicalProperty(physical_property);
    ASSERT_FALSE(physicalEntity.getAbout().empty());
//    ASSERT_TRUE(physicalEntity.getPhysicalProperty().isSet());
    physicalEntity.free();
}

TEST_F(PhysicalEntityTests, TestPhysicalEntityBuilder) {
    PhysicalEntity physicalEntity(model.get());
    physicalEntity
            .setPhysicalProperty(physical_property)
            .setIdentity("obo/PR_000000365")
            .addLocation("https://identifiers.org/fma/FMA:72564")
            .addLocation("fma:FMA:63877");
    ASSERT_FALSE(physicalEntity.getAbout().empty());
//    ASSERT_TRUE(physicalEntity.getPhysicalProperty().isSet());
    physicalEntity.free();
}


TEST_F(PhysicalEntityTests, TestPhysicalEntityBuilderToTriples) {
    PhysicalEntity physicalEntity(model.get());
    physicalEntity
            .setPhysicalProperty(physical_property)
            .setIdentity("obo/PR_000000365")
            .addLocation("https://identifiers.org/fma/FMA:72564")
            .addLocation("fma:FMA:63877");

    Triples triples = physicalEntity.toTriples();
    std::string actual = triples.str();
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"#PhysicalEntity0000\">\n"
                           "    <bqbiol:is rdf:resource=\"https://identifiers.org/obo/PR_000000365\"/>\n"
                           "    <bqbiol:isPartOf rdf:resource=\"https://identifiers.org/fma/FMA:63877\"/>\n"
                           "    <bqbiol:isPartOf rdf:resource=\"https://identifiers.org/fma/FMA:72564\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"metaid\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"#PhysicalEntity0000\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/OPB/OPB_00340\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    triples.freeTriples();
}


TEST_F(PhysicalEntityTests, TestPhysicalEntityBuilderToTriplesFromStringPhysicalProperty) {
    PhysicalEntity physicalEntity(model.get());
    physicalEntity
            .setPhysicalProperty("metaid", "OPB:OPB_00340")
            .setIdentity("obo/PR_000000365")
            .addLocation("https://identifiers.org/fma/FMA:72564")
            .addLocation("fma:FMA:63877");
    Triples triples = physicalEntity.toTriples();
    ASSERT_EQ(5, triples.size());
    std::string actual = triples.str("ntriples", "TestPhysicalEntityBuilder2");
    printf("%s", actual.c_str());
    std::string expected =
            "<metaid> <http://biomodels.net/biology-qualifiers/isPropertyOf> <#PhysicalEntity0000> .\n"
            "<metaid> <http://biomodels.net/biology-qualifiers/isVersionOf> <https://identifiers.org/OPB/OPB_00340> .\n"
            "<#PhysicalEntity0000> <http://biomodels.net/biology-qualifiers/is> <https://identifiers.org/obo/PR_000000365> .\n"
            "<#PhysicalEntity0000> <http://biomodels.net/biology-qualifiers/isPartOf> <https://identifiers.org/fma/FMA:72564> .\n"
            "<#PhysicalEntity0000> <http://biomodels.net/biology-qualifiers/isPartOf> <https://identifiers.org/fma/FMA:63877> .\n";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    triples.freeTriples();
}

TEST(PhysicalEntityTestsNoFixture, TestEquality) {
    LibrdfStorage storage;
    LibrdfModel model(storage.get());

    PhysicalEntity physicalEntity1(
            model.get(),
            PhysicalProperty("metaid", "opb:opb_1234"),
            Resource::fromRawPtr(LibrdfNode::fromUriString("obo/PR_000000365").get()), // is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:72564").get()),
                     Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:63877").get())
                    })
    );
    PhysicalEntity physicalEntity2(
            model.get(),
            PhysicalProperty("metaid", "opb:opb_1234"),
            Resource::fromRawPtr(LibrdfNode::fromUriString("obo/PR_000000365").get()), // is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:72564").get()),
                     Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:63877").get())
                    })
    );
    ASSERT_EQ(physicalEntity1, physicalEntity2);
    model.freeModel();
    storage.freeStorage();
    physicalEntity1.free();
    physicalEntity2.free();
}










