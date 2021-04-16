//
// Created by Ciaran on 4/4/2020.
//

#include "AnnotationSamples.h"
#include "omexmeta/Predicate.h"
#include "omexmeta/Triple.h"
#include "gtest/gtest.h"

using namespace omexmeta;

class TripleTests : public ::testing::Test {
public:
    AnnotationSamples samples;
    std::string subject_str = "./NewModel#metaid_0";
    std::string predicate_str = "http://biomodels.net/biology-qualifiers/is";
    std::string resource_namespace = "uniprot";
    std::string resource_id = "P0DP23";

    UriHandler uriHandler;

    LibrdfNode subject;
    LibrdfNode resource;
    BiomodelsBiologyQualifier predicate;


    //todo subject could pass the world_ to the node
    TripleTests() {
        subject =  LibrdfNode::fromUriString(subject_str);
        resource = LibrdfNode::fromUriString(resource_namespace + "/" + resource_id);
        predicate = BiomodelsBiologyQualifier("is");
    }
};

TEST_F(TripleTests, TestInstantiation1) {
    Triple triple(uriHandler, subject.get(), predicate.get(), resource.get());
    // could fail with valgrind
}

TEST(TripleTestsNoFixture, TestInstantiationEmptyForBuilder) {
    // when we use builder interface, Triple is created empty and we fill in the bits of information  from user input
    UriHandler uriHandler;
    Triple triple(uriHandler);
    ASSERT_TRUE(triple.isEmpty());
    // remember to free the unused resources from test fixture
}

TEST_F(TripleTests, TestInstantiation2) {
    Triple triple(uriHandler, subject,
                  std::make_shared<Predicate>(predicate),
                  resource);
    ASSERT_TRUE(true);// if we get this far the test has passed
}

TEST_F(TripleTests, TestSubjectStringUsingLibrdf) {
    Triple triple(uriHandler, subject.get(), predicate.get(), resource.get());
    std::string &expected = subject_str;
    librdf_node *node = triple.getSubjectAsRawNode();
    librdf_uri *uri = librdf_node_get_uri(node);
    const char *actual = (const char *) librdf_uri_as_string(uri);
    ASSERT_STREQ(expected.c_str(), actual);
    librdf_free_node(node);
}


TEST_F(TripleTests, TestSubjectStrUsingWrapper) {
    Triple triple(uriHandler, subject.get(), predicate.get(), resource.get());
    std::string &expected = subject_str;
    ASSERT_STREQ(expected.c_str(), triple.getSubjectNode().str().c_str());
}

TEST_F(TripleTests, TestPredicate) {
    Triple triple(uriHandler, subject.get(), predicate.get(), resource.get());
    std::string expected = predicate_str;
    ASSERT_STREQ(expected.c_str(), triple.getPredicateNode().str().c_str());
}


TEST_F(TripleTests, TestResource) {
    Triple triple(uriHandler, subject.get(), predicate.get(), resource.get());
    ASSERT_STREQ(triple.getResourceNode().str().c_str(), "https://identifiers.org/uniprot/P0DP23");
}

TEST(TripleTestsNoFixture, TestEquality) {
    UriHandler uriHandler;
    Triple triple1(
            uriHandler,
            LibrdfNode::fromUriString("subject").get(),
            LibrdfNode::fromUriString("predicate").get(),
            LibrdfNode::fromUriString("resource").get());
    Triple triple2(
            uriHandler,
            LibrdfNode::fromUriString("subject").get(),
            LibrdfNode::fromUriString("predicate").get(),
            LibrdfNode::fromUriString("resource").get());
    ASSERT_EQ(triple1, triple2);
}

TEST(TripleTestsNoFixture, TestInequality) {
    UriHandler uriHandler;
    Triple triple1(
            uriHandler,
            LibrdfNode::fromUriString("subject1").get(),
            LibrdfNode::fromUriString("predicate1").get(),
            LibrdfNode::fromUriString("resource1").get());
    Triple triple2(
            uriHandler,
            LibrdfNode::fromUriString("subject2").get(),
            LibrdfNode::fromUriString("predicate2").get(),
            LibrdfNode::fromUriString("resource2").get());
    ASSERT_NE(triple1, triple2);
}

TEST_F(TripleTests, TestStatementResource) {
    Triple triple(uriHandler, subject.get(), predicate.get(), resource.get());
    librdf_statement *statement = triple.get();
    librdf_node *n = librdf_statement_get_object(statement);
    librdf_uri *uri = librdf_node_get_uri(n);
    unsigned char *s = librdf_uri_as_string(uri);
    std::string expected = "https://identifiers.org/uniprot/P0DP23";
    ASSERT_STREQ(expected.c_str(), (const char *) s);
    librdf_free_statement(statement);
}


TEST(TripleTestsNoFixture, TestAboutTwoArguments) {
    UriHandler uriHandler;
    Triple triple(uriHandler);
    triple.about("http://omex-library/myomex.omex", "mymodel.xml", "metaid2");
    std::string expected = "http://omex-library/myomex.omex/mymodel.xml#metaid2";
    std::string actual = triple.getAbout();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST(TripleTestsNoFixture, TestAboutOneArgumentWithSetLocal) {
    UriHandler uriHandler;
    Triple triple(uriHandler);
    triple.setModelUri("model.xml");
    triple.about("metaid2");
    std::string expected = "http://omex-library.org/NewOmex.omex/model.xml#metaid2";
    std::string actual = triple.getAbout();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST(TripleTestsNoFixture, TestAboutAgain2) {
    UriHandler uriHandler;
    Triple triple(uriHandler);

    triple.setModelUri("model.xml");
    triple.about("#metaid3");
    std::string expected = "http://omex-library.org/NewOmex.omex/model.xml#metaid3";
    std::string actual = triple.getAbout();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST(TripleTestsNoFixture, TestSetPredicate) {
    UriHandler uriHandler;
    Triple triple(uriHandler);
    triple.setPredicate("bqbiol", "is");
    std::string expected = "http://biomodels.net/biology-qualifiers/is";
    ASSERT_STREQ(expected.c_str(), triple.getPredicateNode().str().c_str());
}


TEST(TripleTestsNoFixture, TestResourceLiteral) {
    UriHandler uriHandler;
    Triple triple(uriHandler);
    triple.setResourceLiteral("Annotating");
    std::string expected = "Annotating";
    std::string actual = triple.getResourceNode().str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST(TripleTestsNoFixture, TestResourceUri) {
    UriHandler uriHandler;
    Triple triple(uriHandler);
    triple.setResourceUri("AnnotatingUri");
    std::string expected = "AnnotatingUri";
    ASSERT_STREQ(expected.c_str(), triple.getResourceNode().str().c_str());
}

TEST(TripleTestsNoFixture, TestResourceBlank) {
    UriHandler uriHandler;
    Triple triple(uriHandler);
    triple.setResourceBlank("AnnotatingBlank");
    std::string expected = "AnnotatingBlank";
    ASSERT_STREQ(expected.c_str(), triple.getResourceNode().str().c_str());
}

TEST_F(TripleTests, TestStatementSubject) {
    UriHandler uriHandler;
    Triple triple(uriHandler, subject.get(), predicate.get(), resource.get());
    std::string expected = "./NewModel#metaid_0";
    ASSERT_STREQ(expected.c_str(), triple.getSubjectNode().str().c_str());
}

TEST_F(TripleTests, TestBuilderPattern1) {
    Triple triple(uriHandler);
    //    triple.setLocalUri("http://omex-library.org/NewOmex.omex/NewModel.rdf");
    triple.setModelUri("NewModel.xml");
    triple.about("metaid1")
            .setPredicate("bqbiol", "is")
            .setResourceUri("uniprot/PD4034");

    ASSERT_STREQ(triple.getSubjectNode().str().c_str(), "http://omex-library.org/NewOmex.omex/NewModel.xml#metaid1");
    ASSERT_STREQ(triple.getPredicateNode().str().c_str(), "http://biomodels.net/biology-qualifiers/is");
    ASSERT_STREQ(triple.getResourceNode().str().c_str(), "https://identifiers.org/uniprot/PD4034");
}

TEST_F(TripleTests, TestMoveATriple) {
    Triple triple1(uriHandler);
    triple1.about("metaid1")
            .setPredicate("bqbiol", "is")
            .setResourceUri("uniprot/PD4034");
    ASSERT_EQ(1, triple1.getUsage());
    Triple triple2 = std::move(triple1);
    ASSERT_EQ(1, triple2.getUsage());

    ASSERT_STREQ(triple2.getSubjectNode().str().c_str(), "http://omex-library.org/NewOmex.omex/NewModel.xml#metaid1");
    ASSERT_STREQ(triple2.getPredicateNode().str().c_str(), "http://biomodels.net/biology-qualifiers/is");
    ASSERT_STREQ(triple2.getResourceNode().str().c_str(), "https://identifiers.org/uniprot/PD4034");

}

TEST_F(TripleTests, TestMoveAssignmentOperator) {
    Triple triple1(uriHandler);
    triple1.about("metaid1")
            .setPredicate("bqbiol", "is")
            .setResourceUri("uniprot/PD4034");
    Triple triple2(uriHandler);
    triple2.about("metaid2")
            .setPredicate("bqbiol", "is")
            .setResourceUri("uniprot/PD4035");
    triple2 = std::move(triple1);

    ASSERT_STREQ(triple2.getSubjectNode().str().c_str(), "http://omex-library.org/NewOmex.omex/NewModel.xml#metaid1");
    ASSERT_STREQ(triple2.getPredicateNode().str().c_str(), "http://biomodels.net/biology-qualifiers/is");
    ASSERT_STREQ(triple2.getResourceNode().str().c_str(), "https://identifiers.org/uniprot/PD4034");

}


TEST_F(TripleTests, TestBuilderPattern2) {
    UriHandler uriHandler;
    Triple triple(uriHandler);
    triple.setModelUri("model.xml");
    triple.about("#metaid00001")
            .setPredicate("bqbiol", "is")
            .setResourceBlank("Blank");

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/omex.omex/model.xml#metaid00001>\n"
                           "    bqbiol:is _:Blank .\n"
                           "\n"
                           "";

    ASSERT_STREQ(triple.getSubjectNode().str().c_str(), "http://omex-library.org/NewOmex.omex/model.xml#metaid00001");
    ASSERT_STREQ(triple.getPredicateNode().str().c_str(), "http://biomodels.net/biology-qualifiers/is");
    ASSERT_STREQ(triple.getResourceNode().str().c_str(), "Blank");
}


class TripleTestsVector : public ::testing::Test {

public:
    AnnotationSamples samples;
    std::string subject_str = "./NewModel#metaid_0";
    std::string predicate_str = "http://biomodels.net/biology-qualifiers/is";
    std::string resource_namespace = "uniprot";
    std::string resource_id = "P0DP23";

    LibrdfNode subject;
    LibrdfNode resource;
    BiomodelsBiologyQualifier predicate;

    UriHandler uriHandler;


    //todo subject could pass the world_ to the node
    TripleTestsVector() {
        subject =  LibrdfNode::fromUriString(subject_str);
        resource = LibrdfNode::fromUriString(resource_namespace + "/" + resource_id);
        predicate = BiomodelsBiologyQualifier("is");
    }
};

/*
 * Now we have moved the triple into a vector, we
 * must free the statement from the vector, not the
 * original triple
 */
TEST_F(TripleTestsVector, TestTripleVecMove) {
    Triple triple(uriHandler, subject.get(), predicate.get(), resource.get());
    std::vector<Triple> vec;
    vec.push_back(std::move(triple));
    std::string actual = vec[0].getResourceNode().str();
    std::string expected = "https://identifiers.org/uniprot/P0DP23";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}
//TEST_F(TripleTestsVector, t) {
//    Triple triple(uriHandler, subject.get(), predicate.getNode(), resource.get());
//    std::vector<Triple> vec;
//    vec.push_back(std::move(triple));
//    ASSERT_EQ(1, vec.size());
//
//}


class TestTripleTwice : public ::testing::Test {
public:
    /*
     * A collection of test to try and figure out
     * why I cannot create two Triples objects from a
     * PhysicalEntity and free them both. Here I try to
     * reproduce the problem by process of elimination.
     */
    TestTripleTwice() = default;
};

/*
 * Test two Triple with raw nodes
 */

TEST(TestTripleTwice, WithRawNodes) {
    UriHandler uriHandler;
    Triple triple1(
            uriHandler,
            LibrdfNode::fromUriString("subject").get(),
            LibrdfNode::fromUriString("predicate").get(),
            LibrdfNode::fromUriString("resource").get());
    Triple triple2(
            uriHandler,
            LibrdfNode::fromUriString("subject").get(),
            LibrdfNode::fromUriString("predicate").get(),
            LibrdfNode::fromUriString("resource").get());
}

/*
 * Now test two triples with Subject Predicate and Resource
 */
TEST(TestTripleTwice, WithSubjectPredAndRes) {
    UriHandler uriHandler;
    Triple triple1(
            uriHandler,
            LibrdfNode::fromUriString("subject").get(),
            Predicate("uniprot", "PD1234", "uni").get(),
            LibrdfNode::fromUriString("resource").get());
    Triple triple2(
            uriHandler,
            LibrdfNode::fromUriString("subject").get(),
            Predicate("uniprot", "PD1234", "uni").get(),
            LibrdfNode::fromUriString("resource").get());
}

/*
 * Try with different predicate
 */
TEST(TestTripleTwice, WithSubjectBiomodelModelQualifierAndRes) {
    UriHandler uriHandler;
    Triple triple1(
            uriHandler,
            LibrdfNode::fromUriString("subject").get(),
            BiomodelsBiologyQualifier("is").get(),
            LibrdfNode::fromUriString("resource").get());
    Triple triple2(
            uriHandler,
            LibrdfNode::fromUriString("subject").get(),
            Predicate("uniprot", "PD1234", "uni").get(),
            LibrdfNode::fromUriString("resource").get());
}


TEST(TestTripleTwice, WithRawNodesWithMovingTheFirst) {
    UriHandler uriHandler;
    Triple triple1(
            uriHandler,
            LibrdfNode::fromUriString("subject").get(),
            LibrdfNode::fromUriString("predicate").get(),
            LibrdfNode::fromUriString("resource").get());
    Triple triple2 = std::move(triple1);
    Triple triple3(
            uriHandler,
            LibrdfNode::fromUriString("subject").get(),
            LibrdfNode::fromUriString("predicate").get(),
            LibrdfNode::fromUriString("resource").get());
}
