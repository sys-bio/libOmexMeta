//
// Created by Ciaran on 4/5/2020.
//
#include "librdf.h"
#include "gtest/gtest.h"
#include "semsim/Predicate.h"

#include "semsim/RedlandAPIWrapper/RedlandAPIWrapper.h"

class PredicateTests : public ::testing::Test {
public:

    std::string bqb_ns = "http://biomodels.net/biology-qualifiers/";

    semsim::LibrdfWorld world;

    PredicateTests() {
    }

    ~PredicateTests() override {
    }

};

TEST_F(PredicateTests, TestCreateStaticFunctionFromBasePredicate) {
    semsim::Predicate predicate2(world, bqb_ns, "is", "bqbiol");
    std::string expected = "http://biomodels.net/biology-qualifiers/is";
    std::string actual = predicate2.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PredicateTests, TestGetNode) {
    semsim::Predicate predicate2(world, bqb_ns, "is", "bqbiol");
    std::string expected = "http://biomodels.net/biology-qualifiers/is";
    semsim::LibrdfNode node = predicate2.getNode();
    const char *actual = (const char *) librdf_uri_as_string((*node.getNode())->value.uri);
    ASSERT_STREQ(expected.c_str(), actual);
}

TEST_F(PredicateTests, TestGetNode2) {
    semsim::Predicate predicate2(world, bqb_ns, "is", "bqbiol");
    std::string expected = "http://biomodels.net/biology-qualifiers/is";
    semsim::LibrdfNode node = predicate2.getNode();
    std::string actual = node.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PredicateTests, TestGetNodebqb) {
    semsim::BiomodelsBiologyQualifier qualifiers(world, "is");
    std::string expected = "http://biomodels.net/biology-qualifiers/is";
    semsim::LibrdfNode node = qualifiers.getNode();
    const char *actual = (const char *) librdf_uri_as_string((*node.getNode())->value.uri);
    ASSERT_STREQ(expected.c_str(), actual);
}

TEST_F(PredicateTests, TestGetNodebqb2) {
    semsim::BiomodelsBiologyQualifier qualifiers(world, "is");
    std::string expected = "http://biomodels.net/biology-qualifiers/is";
    semsim::LibrdfNode node = qualifiers.getNode();
    std::string actual = node.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PredicateTests, TestGetNodebqbFails) {
    ASSERT_THROW(
            semsim::BiomodelsBiologyQualifier qualifiers(world, "isnot"),
            std::logic_error);
}

TEST_F(PredicateTests, TestGetNodebqqPrefix) {
    semsim::BiomodelsBiologyQualifier qualifiers(world, "is");
    std::string expected = "bqbiol";
    ASSERT_STREQ(expected.c_str(), qualifiers.getPrefix().c_str());
}

TEST_F(PredicateTests, TestDCTermPrefix) {
    semsim::DCTerm term(world, "Description");
    std::string expected = "dcterms";
    ASSERT_STREQ(expected.c_str(), term.getPrefix().c_str());
}

TEST_F(PredicateTests, TestDCTermUri) {
    semsim::DCTerm term(world, "Description");
    std::string expected = "http://purl.org/dc/terms/Description";
    semsim::LibrdfNode node = term.getNode();
    const char *actual = (const char *) librdf_uri_as_string((*node.getNode())->value.uri);
    ASSERT_STREQ(expected.c_str(), actual);
}

TEST_F(PredicateTests, TestDCTermUri2) {
    semsim::DCTerm term(world, "Description");
    std::string expected = "http://purl.org/dc/terms/Description";
    semsim::LibrdfNode node = term.getNode();
    std::string actual = node.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PredicateTests, TestDCTermGetNamespace) {
    semsim::DCTerm term(world, "Description");
    std::string expected = "http://purl.org/dc/terms/";
    std::string actual = term.getNamespace();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PredicateTests, TestDCTermGetPrefix) {
    semsim::DCTerm term(world, "Description");
    std::string expected = "dcterms";
    std::string actual = term.getPrefix();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PredicateTests, TestBqBiolGetNamespace) {
    semsim::BiomodelsBiologyQualifier term(world, "is");
    std::string expected = "http://biomodels.net/biology-qualifiers/";
    std::string actual = term.getNamespace();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(PredicateTests, TestBqBiolGetPrefix) {
    semsim::BiomodelsBiologyQualifier term(world, "is");
    std::string expected = "bqbiol";
    std::string actual = term.getPrefix();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(PredicateTests, TestBqModelGetNamespace) {
    semsim::BiomodelsModelQualifier term(world, "is");
    std::string expected = "http://biomodels.net/model-qualifiers/";
    std::string actual = term.getNamespace();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(PredicateTests, TestBqModelGetPrefix) {
    semsim::BiomodelsModelQualifier term(world, "is");
    std::string expected = "bqmodel";
    std::string actual = term.getPrefix();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(PredicateTests, TestBqModelGetPrefixFromPtr) {
    semsim::BiomodelsModelQualifier term(world, "is");
    std::shared_ptr<semsim::BiomodelsModelQualifier> term_ptr = std::make_shared<semsim::BiomodelsModelQualifier>(term);
    std::string expected = "bqmodel";
    std::string actual = term_ptr->getPrefix();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(PredicateTests, TestBqModelGetPrefixFromPtrToBaseClass) {
    semsim::BiomodelsModelQualifier term(world, "is");
    std::shared_ptr<semsim::Predicate> term_ptr = std::make_shared<semsim::BiomodelsModelQualifier>(term);
    std::string expected = "bqmodel";
    std::string actual = term_ptr->getPrefix();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(PredicateTests, TestBqModelGetPrefixFromPtrToBaseClassvsdf) {
    std::shared_ptr<semsim::Predicate> term_ptr =
            std::make_shared<semsim::Predicate>(semsim::BiomodelsBiologyQualifier(world, "is"));
    std::string expected = "bqbiol";
    std::string actual = term_ptr->getPrefix();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PredicateTests, TestSemsimPredicatePrefix) {
    std::shared_ptr<semsim::Predicate> term_ptr =
            std::make_shared<semsim::Predicate>(semsim::SemSim(world, "hasSourceParticipant"));
    std::string expected = "semsim";
    std::string actual = term_ptr->getPrefix();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(PredicateTests, TestSemsimPredicateNamespace) {
    std::shared_ptr<semsim::Predicate> term_ptr =
            std::make_shared<semsim::Predicate>(semsim::SemSim(world, "hasSourceParticipant"));
    std::string expected = "http://www.bhi.washington.edu/semsim#";
    std::string actual = term_ptr->getNamespace();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(PredicateTests, TestFromUriNode) {
    std::string url_str = "https://www.notarealaddress.com";
    semsim::Predicate predicate(world, world.newNodeUriString(url_str.c_str()));
    semsim::LibrdfNode n = predicate.getNode();
    std::string node_string = n.str();
    ASSERT_STREQ(url_str.c_str(), node_string.c_str());
}


TEST_F(PredicateTests, TestFromUriNodeNamespace) {
    std::string url_str = "https://www.notarealaddress.com/nota/term";
    semsim::Predicate predicate(world, world.newNodeUriString(url_str.c_str()));
    semsim::LibrdfNode n = predicate.getNode();
    const std::string &actual = predicate.getNamespace();
    std::string expected = "https://www.notarealaddress.com/nota/";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PredicateTests, TestFromUriNodeNamespaceWhenPrefixIsKnown) {
    std::string url_str = "https://biomodels.net/biology-qualifiers/is";
    semsim::Predicate predicate(world, world.newNodeUriString(url_str.c_str()));
    semsim::LibrdfNode n = predicate.getNode();
    const std::string &actual = predicate.getNamespace();
    std::string expected = "https://biomodels.net/biology-qualifiers/";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PredicateTests, TestNamespaceWhenItEndsWithHash) {
    std::string url_str = "http://www.bhi.washington.edu/semsim#hasSourceParticipant";
    semsim::Predicate predicate(world, world.newNodeUriString(url_str.c_str()));
    semsim::LibrdfNode n = predicate.getNode();
    const std::string &actual = predicate.getNamespace();
    std::string expected = "http://www.bhi.washington.edu/semsim#";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PredicateTests, TestPrefixWhenNamespaceEndsWithHash) {
    std::string url_str = "http://www.bhi.washington.edu/semsim#hasSourceParticipant";
    semsim::Predicate predicate(world, world.newNodeUriString(url_str.c_str()));
    semsim::LibrdfNode n = predicate.getNode();
    const std::string &actual = predicate.getPrefix();
    std::string expected = "semsim";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PredicateTests, TestTermWhenNamespaceEndsWithHash) {
    std::string url_str = "http://www.bhi.washington.edu/semsim#hasSourceParticipant";
    semsim::Predicate predicate(world, world.newNodeUriString(url_str.c_str()));
    semsim::LibrdfNode n = predicate.getNode();
    const std::string &actual = predicate.getTerm();
    std::string expected = "hasSourceParticipant";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PredicateTests, TestFromUriNodeTerm) {
    std::string url_str = "https://www.notarealaddress.com/nota/term";
    semsim::Predicate predicate(world, world.newNodeUriString(url_str.c_str()));
    semsim::LibrdfNode n = predicate.getNode();
    const std::string &actual = predicate.getTerm();
    std::string expected = "term";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PredicateTests, TestFromUriNodePrefix) {
    std::string url_str = "https://www.notarealaddress.com/nota/term";
    semsim::Predicate predicate(world, world.newNodeUriString(url_str.c_str()));
    semsim::LibrdfNode n = predicate.getNode();
    const std::string &actual = predicate.getPrefix();
    std::string expected = "NotSet";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PredicateTests, TestNamespaceKnownWhenNamespaceIsKnown) {
    std::string ns = "http://purl.org/dc/terms/";
    ASSERT_TRUE(semsim::Predicate::namespaceKnown(ns)
    );
}


TEST_F(PredicateTests, TestNamespaceKnownWhenNamespaceIsNotKnown) {
    std::string ns = "http://www.notarealaddress.com/nota/";
    ASSERT_FALSE(semsim::Predicate::namespaceKnown(ns)
    );
}

TEST_F(PredicateTests, TestPredicateFactory) {
    semsim::PredicatePtr predicatePtr = semsim::PredicateFactory(world, "bqb", "is");
    std::string actual = predicatePtr->str();
    std::string expected = "http://biomodels.net/biology-qualifiers/is";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PredicateTests, TestPredicateFactory1err) {
    ASSERT_THROW(semsim::PredicateFactory(world, "unknown", "description"), std::invalid_argument
    );
}

TEST_F(PredicateTests, TestPredicateFactory2) {
    semsim::PredicatePtr predicatePtr = semsim::PredicateFactory(world, "dc", "Description");
    std::string actual = predicatePtr->str();
    std::string expected = "http://purl.org/dc/terms/Description";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PredicateTests, TestPredicateFactory2err) {
    ASSERT_THROW(semsim::PredicateFactory(world, "dc", "description"), std::invalid_argument
    );
}

TEST_F(PredicateTests, TestPredicateFactory3) {
    semsim::PredicatePtr predicatePtr = semsim::PredicateFactory(world, "BiomodelsModelQualifier", "hasInstance");
    std::string actual = predicatePtr->str();
    std::string expected = "http://biomodels.net/model-qualifiers/hasInstance";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PredicateTests, TestPredicateFactory4) {
    semsim::PredicatePtr predicatePtr = semsim::PredicateFactory(world, "BiomodelsModelQualifier", "hasInstance");
    std::string actual = predicatePtr->str();
    std::string expected = "http://biomodels.net/model-qualifiers/hasInstance";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(PredicateTests, TestPredicateWithoutSubclass) {
    semsim::Predicate predicate = semsim::Predicate(world, "ns", "term", "prefix");
    std::string actual = predicate.str();
    std::string expected = "ns/term";
    ASSERT_STREQ(actual.c_str(), expected.c_str());
}

TEST_F(PredicateTests, TestPredicateWithoutSubclass2) {
    semsim::PredicatePtr predicate = std::make_shared<semsim::Predicate>(
            semsim::Predicate(world, "ns", "term", "prefix")
    );
    std::string actual = predicate->str();
    std::string expected = "ns/term";
    ASSERT_STREQ(actual.c_str(), expected.c_str());
}

TEST_F(PredicateTests, TestPredicateWithoutSubclass3) {
    semsim::PredicatePtr predicate = std::make_shared<semsim::Predicate>(
            semsim::Predicate(world, "https://stackoverflow.com/questions/", "how-do-you", "so")
    );
    std::string actual = predicate->str();
    std::string expected = "https://stackoverflow.com/questions/how-do-you";
    ASSERT_STREQ(actual.c_str(), expected.c_str());
}











