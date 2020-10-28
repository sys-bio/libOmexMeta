//
// Created by Ciaran on 4/22/2020.
//

#include "librdf.h"
#include "omexmeta/PhysicalEntity.h"
#include "omexmeta/RDF.h"
#include "vector"
#include "gtest/gtest.h"
#include <vector>

using namespace omexmeta;

class PhysicalEntityTests : public ::testing::Test {

public:
    LibrdfStorage storage;
    LibrdfModel model;

    PhysicalProperty physical_property;
    std::string local_uri = "http://omex-library.org/NewOmex.omex/NewModel.rdf#";
    std::string model_uri = "http://omex-library.org/NewOmex.omex/NewModel.xml#";

    PhysicalEntityTests() {
        model = LibrdfModel(storage.get());
        physical_property = PhysicalProperty("metaid", "OPB:OPB_00340", model_uri);
    };

    ~PhysicalEntityTests() override {
        model.freeModel();
        storage.freeStorage();
    }
};


TEST_F(PhysicalEntityTests, TestGetSubjectMetaidStr) {
    PhysicalEntity physicalEntity(
            model.get(),
            model_uri,
            local_uri,
            physical_property,
            Resource::fromRawPtr(LibrdfNode::fromUriString("obo/PR_000000365").get()),// is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:72564").get()),
                     Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:63877").get())}));
    std::string actual = physicalEntity.getAbout();
    std::string expected = "http://omex-library.org/NewOmex.omex/NewModel.xml#metaid";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    //clear up as we didn't use Triple (which owns everything)
    physicalEntity.free();
}


TEST_F(PhysicalEntityTests, TestGetPhysicalPropertyNode) {
    PhysicalEntity physicalEntity(
            model.get(),
            model_uri,
            local_uri,
            physical_property,
            Resource::fromRawPtr(LibrdfNode::fromUriString("obo/PR_000000365").get()),// is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:72564").get()),
                     Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:63877").get())}));
    Resource r(LibrdfNode::fromUriString(
            physicalEntity.getPhysicalProperty().getResourceStr()));
    std::string actual = r.str();
    std::string expected = "https://identifiers.org/OPB:OPB_00340";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    //clear up as we didn't use Triple (which owns everything)
    physicalEntity.free();
    r.free();
}


TEST_F(PhysicalEntityTests, TestIdentityResourceStr) {
    PhysicalEntity physicalEntity(
            model.get(),
            model_uri,
            local_uri,
            physical_property,
            Resource::fromRawPtr(LibrdfNode::fromUriString("obo/PR_000000365").get()),// is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:72564").get()),
                     Resource::fromRawPtr(LibrdfNode::fromUriString("fma:FMA:63877").get())}));
    std::string actual = physicalEntity.getIdentityResource().str();
    std::string expected = "https://identifiers.org/obo/PR_000000365";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    //clear up as we didn't use Triple (which owns everything)
    physicalEntity.free();
}


TEST_F(PhysicalEntityTests, TestIdentityResourceNode) {
    PhysicalEntity physicalEntity(
            model.get(),
            model_uri,
            local_uri,
            physical_property,
            Resource::fromRawPtr(LibrdfNode::fromUriString("obo/PR_000000365").get()),// is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:72564").get()),
                     Resource::fromRawPtr(LibrdfNode::fromUriString("fma:FMA:63877").get())}));
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
            model_uri,
            local_uri,
            physical_property,
            Resource::fromRawPtr(LibrdfNode::fromUriString("obo/PR_000000365").get()),// is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:72564").get()),
                     Resource::fromRawPtr(LibrdfNode::fromUriString("fma:FMA:63877").get())}));
    std::ostringstream actual;
    for (auto &it : physicalEntity.getLocationResources()) {
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
            model_uri,
            local_uri,
            physical_property,
            Resource::fromRawPtr(LibrdfNode::fromUriString("obo/PR_000000365").get()),// is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:72564").get()),
                     Resource::fromRawPtr(LibrdfNode::fromUriString("fma:FMA:63877").get())}));
    std::ostringstream actual;
    for (auto &it : physicalEntity.getLocationResources()) {
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
            model_uri,
            local_uri,
            physical_property,
            Resource::fromRawPtr(LibrdfNode::fromUriString("obo/PR_000000365").get()),// is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:72564").get()),
                     Resource::fromRawPtr(LibrdfNode::fromUriString("fma:FMA:63877").get())}));
    std::string actual = physicalEntity.getSubjectStr();
    std::string expected = "http://omex-library.org/NewOmex.omex/NewModel.xml#metaid";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    //clear up as we didn't use Triple (which owns everything)
    physicalEntity.free();
}

TEST_F(PhysicalEntityTests, TestSubjectFromAbout) {
    PhysicalEntity physicalEntity(
            model.get(),
            model_uri,
            local_uri,
            physical_property,
            Resource::fromRawPtr(LibrdfNode::fromUriString("obo/PR_000000365").get()),// is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:72564").get()),
                     Resource::fromRawPtr(LibrdfNode::fromUriString("fma:FMA:63877").get())}));
    std::string actual = physicalEntity.getAbout();
    std::string expected = "http://omex-library.org/NewOmex.omex/NewModel.xml#metaid";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    //clear up as we didn't use Triple (which owns everything)
    physicalEntity.free();
}

TEST_F(PhysicalEntityTests, TestAboutIsSet) {
    PhysicalEntity physicalEntity(
            model.get(),
            model_uri,
            local_uri,
            physical_property,
            Resource::fromRawPtr(LibrdfNode::fromUriString("obo/PR_000000365").get()),// is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:72564").get()),
                     Resource::fromRawPtr(LibrdfNode::fromUriString("fma:FMA:63877").get())}));
    std::cout << physicalEntity.getAbout() << std::endl;
    ASSERT_FALSE(physicalEntity.getAbout().empty());
    //clear up as we didn't use Triple (which owns everything)
    physicalEntity.free();
}

TEST(PhysicalEntityTestsNoFixture, TestToTripleRefCounts) {
    LibrdfStorage storage;
    LibrdfModel model(storage.get());

    std::string model_uri = "http://omex-library.org/NewOmex.omex/NewModel.xml#";
    std::string local_uri = "http://omex-library.org/NewOmex.omex/NewModel.rdf#";

    // ensure physical property has 1 reference
    PhysicalProperty property("metaid", "opb:opb_1234", model_uri);
    //    ASSERT_EQ(1, property.getNode()->usage);

    // ensure is resource has 1 reference
    Resource is = Resource::fromRawPtr(LibrdfNode::fromUriString("obo/PR_000000365").get());// is smad3
    ASSERT_EQ(1, is.getNode()->usage);

    // ensure is ispartof has 1 reference per location
    std::vector<Resource> ispartof;
    ispartof.push_back(std::move(
            Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:72564").get())));
    ispartof.push_back(std::move(
            Resource::fromRawPtr(LibrdfNode::fromUriString("fma:FMA:63877").get())));
    ASSERT_EQ(1, ispartof[0].getNode()->usage);
    ASSERT_EQ(1, ispartof[1].getNode()->usage);

    PhysicalEntity physicalEntity(
            model.get(),
            model_uri,
            local_uri,
            property,
            is, ispartof);

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
    Resource is = Resource::fromRawPtr(LibrdfNode::fromUriString("obo/PR_000000365").get());// is smad3
    std::vector<Resource> ispartof;
    ispartof.push_back(std::move(
            Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:72564").get())));
    ispartof.push_back(std::move(
            Resource::fromRawPtr(LibrdfNode::fromUriString("fma:FMA:63877").get())));

    PhysicalEntity physicalEntity(
            model.get(),
            model_uri,
            local_uri,
            physical_property,
            is, ispartof);

    Triples triples = physicalEntity.toTriples();

    int expected = 5;// 5 because we have two location triples.
    int actual = triples.size();
    ASSERT_EQ(expected, actual);
    triples.freeTriples();
}


TEST_F(PhysicalEntityTests, TestTriples) {
    PhysicalEntity physicalEntity(
            model.get(),
            model_uri,
            local_uri,
            physical_property,
            Resource::fromRawPtr(LibrdfNode::fromUriString("obo/PR_000000365").get()),// is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:72564").get()),
                     Resource::fromRawPtr(LibrdfNode::fromUriString("fma:FMA:63877").get())}));
    Triples triples = physicalEntity.toTriples();
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:PhysicalEntity0000\n"
                           "    bqbiol:is <https://identifiers.org/obo/PR_000000365> ;\n"
                           "    bqbiol:isPartOf <https://identifiers.org/fma/FMA:63877>, <https://identifiers.org/fma/FMA:72564> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#metaid>\n"
                           "    bqbiol:isPropertyOf local:PhysicalEntity0000 ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/OPB/OPB_00340> .\n"
                           "\n";
    std::string s = triples.str("turtle");
    std::cout << s << std::endl;
    ASSERT_STREQ(s.c_str(), expected.c_str());
    triples.freeTriples();
}

TEST_F(PhysicalEntityTests, TestPhysicalEntityBuilderInterface) {
    PhysicalEntity physicalEntity(model.get());

    // When we create a physicalEntity outside the context of Editor, using the builder inteface,
    // we need to manually give it a local uri.
    // users will always use the builder interface and not have to do this manually.
    physicalEntity.setModelUri(model_uri);
    physicalEntity.setLocalUri(local_uri);
    physicalEntity
            .setPhysicalProperty("VLV", "OPB:OPB_00154")
            .identity("fma/FMA:9690")
            .isPartOf("fma:FMA:18228");

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:PhysicalEntity0000\n"
                           "    bqbiol:is <https://identifiers.org/fma/FMA:9690> ;\n"
                           "    bqbiol:isPartOf <https://identifiers.org/fma/FMA:18228> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#VLV>\n"
                           "    bqbiol:isPropertyOf local:PhysicalEntity0000 ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/OPB/OPB_00154> .\n"
                           "\n"
                           "";
    Triples triples = physicalEntity.toTriples();
    std::string actual = triples.str();
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    triples.freeTriples();
}


TEST_F(PhysicalEntityTests, TestPhysicalEntityBuilderAddTwoItems) {
    PhysicalEntity physicalEntity(model.get());
    physicalEntity.setModelUri(model_uri);
    physicalEntity.setLocalUri(local_uri);

    physicalEntity
            .setPhysicalProperty(physical_property);
    ASSERT_FALSE(physicalEntity.getAbout().empty());
    physicalEntity.free();
}

TEST_F(PhysicalEntityTests, TestPhysicalEntityBuilderAddTwoItemsWhenYouAddPhysicalPropertySecond) {
    PhysicalEntity physicalEntity(model.get());
    physicalEntity.setModelUri(model_uri);
    physicalEntity.setLocalUri(local_uri);
    physicalEntity.setPhysicalProperty(physical_property);
    ASSERT_FALSE(physicalEntity.getAbout().empty());
    //    ASSERT_TRUE(physicalEntity.getPhysicalProperty().isSet());
    physicalEntity.free();
}

TEST_F(PhysicalEntityTests, TestPhysicalEntityBuilder) {
    PhysicalEntity physicalEntity(model.get());
    physicalEntity.setModelUri(model_uri);
    physicalEntity.setLocalUri(local_uri);
    physicalEntity
            .setPhysicalProperty(physical_property)
            .identity("obo/PR_000000365")
            .isPartOf("https://identifiers.org/fma/FMA:72564")
            .isPartOf("fma:FMA:63877");
    ASSERT_FALSE(physicalEntity.getAbout().empty());
    //    ASSERT_TRUE(physicalEntity.getPhysicalProperty().isSet());
    physicalEntity.free();
}

TEST_F(PhysicalEntityTests, TestPhysicalEntityBuilder2) {
    PhysicalEntity physicalEntity(model.get());
    physicalEntity.setModelUri(model_uri);
    physicalEntity.setLocalUri(local_uri);
    physicalEntity
            .about("glucose_c")
            .identity("CHEBI:17234")
            .isPartOf("GO:0005737")
            .hasProperty("OPB:00340");
    Triples triples = physicalEntity.toTriples();
    RDF rdf;
    rdf.addTriples(triples);

    std::cout << rdf.toString() << std::endl;

//    std::string actual = physicalEntity.toTriples().str("turtle");
//    std::string expected_string = "@prefix OMEXlib: <http://omex-library.org/> .\n"
//                                  "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
//                                  "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
//                                  "\n"
//                                  "local:PhysicalEntity0000\n"
//                                  "    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#glucose_c> ;\n"
//                                  "    bqbiol:isVersionOf <https://identifiers.org/OPB:00340> .\n"
//                                  "\n"
//                                  "<http://omex-library.org/NewOmex.omex/NewModel.xml#glucose_c>\n"
//                                  "    bqbiol:is <https://identifiers.org/CHEBI:17234> ;\n"
//                                  "    bqbiol:isPartOf <https://identifiers.org/GO:0005737> .\n"
//                                  "\n";
//    RDF rdf = RDF::fromString(expected_string, "turtle");
//    LibrdfModel expected_model(rdf.getModel());
//    LibrdfModel actual_model(physicalEntity.getModel());
//    ASSERT_TRUE(expected_model == actual_model);
//
//    expected_model.freeModel();
//    actual_model.freeModel();

    physicalEntity.free();

    /*
     * This is what we have, and its wrong.

        <http://omex-library.org/NewOmex.omex/NewModel.xml#glucose_c>
            bqbiol:isPropertyOf local:PhysicalEntity0000 ;
            bqbiol:isVersionOf <https://identifiers.org/OPB:00340> .

        local:PhysicalEntity0000
            bqbiol:is <https://identifiers.org/CHEBI:17234> ;
            bqbiol:isPartOf <https://identifiers.org/GO:0005737> .


     */
}


TEST_F(PhysicalEntityTests, TestPhysicalEntityBuilderToTriples) {
    PhysicalEntity physicalEntity(model.get());
    physicalEntity.setModelUri(model_uri);
    physicalEntity.setLocalUri(local_uri);
    physicalEntity
            .setPhysicalProperty(physical_property)
            .identity("obo/PR_000000365")
            .isPartOf("https://identifiers.org/fma/FMA:72564")
            .isPartOf("fma:FMA:63877");

    Triples triples = physicalEntity.toTriples();
    std::string actual = triples.str();
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:PhysicalEntity0000\n"
                           "    bqbiol:is <https://identifiers.org/obo/PR_000000365> ;\n"
                           "    bqbiol:isPartOf <https://identifiers.org/fma/FMA:63877>, <https://identifiers.org/fma/FMA:72564> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#metaid>\n"
                           "    bqbiol:isPropertyOf local:PhysicalEntity0000 ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/OPB/OPB_00340> .\n"
                           "\n"
                           "";
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    triples.freeTriples();
}

TEST_F(PhysicalEntityTests, TestPhysicalEntityBuilderToTriplesOptionalIsPartOf) {
    PhysicalEntity physicalEntity(model.get());
    physicalEntity.setModelUri(model_uri);
    physicalEntity.setLocalUri(local_uri);
    physicalEntity
            .setPhysicalProperty(physical_property)
            .identity("obo/PR_000000365");

    Triples triples = physicalEntity.toTriples();
    std::string actual = triples.str();
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:PhysicalEntity0000\n"
                           "    bqbiol:is <https://identifiers.org/obo/PR_000000365> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#metaid>\n"
                           "    bqbiol:isPropertyOf local:PhysicalEntity0000 ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/OPB/OPB_00340> .\n"
                           "\n"
                           "";
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    triples.freeTriples();
}

TEST_F(PhysicalEntityTests, TestPhysicalEntityBuilderOptionalIdentityField) {
    PhysicalEntity physicalEntity(model.get());
    physicalEntity.setModelUri(model_uri);
    physicalEntity.setLocalUri(local_uri);
    physicalEntity
            .setPhysicalProperty(physical_property)
            .isPartOf("https://identifiers.org/fma/FMA:72564")
            .isPartOf("fma:FMA:63877");
    std::string actual = physicalEntity.toTriples().str();
    std::cout << actual << std::endl;
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:PhysicalEntity0000\n"
                           "    bqbiol:isPartOf <https://identifiers.org/fma/FMA:63877>, <https://identifiers.org/fma/FMA:72564> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#metaid>\n"
                           "    bqbiol:isPropertyOf local:PhysicalEntity0000 ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/OPB/OPB_00340> .\n"
                           "\n";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    physicalEntity.free();
}

TEST_F(PhysicalEntityTests, TestPhysicalEntityBuilderHasPart) {
    PhysicalEntity physicalEntity(model.get());
    physicalEntity.setModelUri(model_uri);
    physicalEntity.setLocalUri(local_uri);
    physicalEntity
            .setPhysicalProperty(physical_property)
            .hasPart("uniprot/PD12345")
            .hasPart("uniprot/PD12346");
    std::string actual = physicalEntity.toTriples().str();
    std::cout << actual << std::endl;
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:PhysicalEntity0000\n"
                           "    bqbiol:hasPart <https://identifiers.org/uniprot/PD12345>, <https://identifiers.org/uniprot/PD12346> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#metaid>\n"
                           "    bqbiol:isPropertyOf local:PhysicalEntity0000 ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/OPB/OPB_00340> .\n"
                           "\n";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    physicalEntity.free();
}


TEST_F(PhysicalEntityTests, TestPhysicalEntityBuilderToTriplesFromStringPhysicalProperty) {
    PhysicalEntity physicalEntity(model.get());
    physicalEntity.setModelUri(model_uri);
    physicalEntity.setLocalUri(local_uri);
    physicalEntity
            .setPhysicalProperty("metaid", "OPB:OPB_00340")
            .identity("obo/PR_000000365")
            .isPartOf("https://identifiers.org/fma/FMA:72564")
            .isPartOf("fma:FMA:63877");
    Triples triples = physicalEntity.toTriples();
    ASSERT_EQ(5, triples.size());
    std::string actual = triples.str("ntriples", "TestPhysicalEntityBuilder2");
    printf("%s", actual.c_str());
    std::string expected = "<http://omex-library.org/NewOmex.omex/NewModel.xml#metaid> <http://biomodels.net/biology-qualifiers/isPropertyOf> <http://omex-library.org/NewOmex.omex/NewModel.rdf#PhysicalEntity0000> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#metaid> <http://biomodels.net/biology-qualifiers/isVersionOf> <https://identifiers.org/OPB/OPB_00340> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#PhysicalEntity0000> <http://biomodels.net/biology-qualifiers/is> <https://identifiers.org/obo/PR_000000365> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#PhysicalEntity0000> <http://biomodels.net/biology-qualifiers/isPartOf> <https://identifiers.org/fma/FMA:72564> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#PhysicalEntity0000> <http://biomodels.net/biology-qualifiers/isPartOf> <https://identifiers.org/fma/FMA:63877> .\n";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    triples.freeTriples();
}

TEST_F(PhysicalEntityTests, TestPhysicalEntityBuilderToTriplesFromStringPhysicalProperty2) {
    PhysicalEntity physicalEntity(model.get());
    physicalEntity.setModelUri(model_uri);
    physicalEntity.setLocalUri(local_uri);

    physicalEntity
            .about("metaid")
            .hasProperty("OPB:OPB_00340")
            .identity("uniprot/PD12345")
            .isPartOf("https://identifiers.org/fma/FMA:72564")
            .isPartOf("fma:FMA:63877");

    Triples triples = physicalEntity.toTriples();

    ASSERT_EQ(5, triples.size());

    std::string actual = triples.str("ntriples", "TestPhysicalEntityBuilder2");

    printf("%s", actual.c_str());

    std::string expected = "<http://omex-library.org/NewOmex.omex/NewModel.xml#metaid> <http://biomodels.net/biology-qualifiers/isPropertyOf> <http://omex-library.org/NewOmex.omex/NewModel.rdf#PhysicalEntity0000> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#metaid> <http://biomodels.net/biology-qualifiers/isVersionOf> <https://identifiers.org/OPB/OPB_00340> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#PhysicalEntity0000> <http://biomodels.net/biology-qualifiers/is> <https://identifiers.org/uniprot/PD12345> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#PhysicalEntity0000> <http://biomodels.net/biology-qualifiers/isPartOf> <https://identifiers.org/fma/FMA:72564> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#PhysicalEntity0000> <http://biomodels.net/biology-qualifiers/isPartOf> <https://identifiers.org/fma/FMA:63877> .\n";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    triples.freeTriples();
}

TEST_F(PhysicalEntityTests, TestPhysicalEntityBuilderToTriplesFromStringNoProperty) {
    PhysicalEntity physicalEntity(model.get());
    physicalEntity.setModelUri(model_uri);
    physicalEntity.setLocalUri(local_uri);
    physicalEntity
            .about("metaid")
            .hasProperty("obo/OPB12345")
            .identity("uniprot/PR12345")
            .isPartOf("https://identifiers.org/fma/FMA:72564")
            .isPartOf("fma:FMA:63877");
    Triples triples = physicalEntity.toTriples();
    ASSERT_EQ(5, triples.size());
    std::string actual = triples.str("ntriples", "TestPhysicalEntityBuilder2");
    printf("%s", actual.c_str());
    std::string expected = "<http://omex-library.org/NewOmex.omex/NewModel.xml#metaid> <http://biomodels.net/biology-qualifiers/isPropertyOf> <http://omex-library.org/NewOmex.omex/NewModel.rdf#PhysicalEntity0000> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#metaid> <http://biomodels.net/biology-qualifiers/isVersionOf> <https://identifiers.org/obo/OPB12345> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#PhysicalEntity0000> <http://biomodels.net/biology-qualifiers/is> <https://identifiers.org/uniprot/PR12345> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#PhysicalEntity0000> <http://biomodels.net/biology-qualifiers/isPartOf> <https://identifiers.org/fma/FMA:72564> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#PhysicalEntity0000> <http://biomodels.net/biology-qualifiers/isPartOf> <https://identifiers.org/fma/FMA:63877> .\n";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    triples.freeTriples();
}

TEST(PhysicalEntityTestsNoFixture, TestEquality) {
    LibrdfStorage storage;
    LibrdfModel model(storage.get());

    std::string model_uri = "http://omex-library.org/NewOmex.omex/NewModel.xml#";

    PhysicalEntity physicalEntity1(
            model.get(),
            "http://omex-library.org/NewOmex.omex/NewModel.xml#",
            "http://omex-library.org/NewOmex.omex/NewModel.rdf#",
            PhysicalProperty("metaid", "opb:opb_1234", model_uri),
            Resource::fromRawPtr(LibrdfNode::fromUriString("obo/PR_000000365").get()),// is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:72564").get()),
                     Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:63877").get())}));
    PhysicalEntity physicalEntity2(
            model.get(),
            "http://omex-library.org/NewOmex.omex/NewModel.xml#",
            "http://omex-library.org/NewOmex.omex/NewModel.rdf#",
            PhysicalProperty("metaid", "opb:opb_1234", model_uri),
            Resource::fromRawPtr(LibrdfNode::fromUriString("obo/PR_000000365").get()),// is smad3
            std::vector<Resource>(
                    {Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:72564").get()),
                     Resource::fromRawPtr(LibrdfNode::fromUriString("https://identifiers.org/fma/FMA:63877").get())}));
    ASSERT_EQ(physicalEntity1, physicalEntity2);
    model.freeModel();
    storage.freeStorage();
    physicalEntity1.free();
    physicalEntity2.free();
}
