//
// Created by Ciaran on 4/5/2020.
//
#include "librdf.h"
#include "gtest/gtest.h"
#include "semsim/Predicate.h"

#include "RedlandAPIWrapper.h"

using namespace semsim;

class PredicateTests : public ::testing::Test {
public:

    std::string bqb_ns = "http://biomodels.net/biology-qualifiers/";


    PredicateTests() {
    }

    ~PredicateTests() override {
    }

};

TEST_F(PredicateTests, TestCreateStaticFunctionFromBasePredicate) {
    Predicate predicate2(bqb_ns, "is", "bqbiol");
    std::string expected = "http://biomodels.net/biology-qualifiers/is";
    std::string actual = predicate2.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PredicateTests, TestGetNode) {
    Predicate predicate2(bqb_ns, "is", "bqbiol");
    std::string expected = "http://biomodels.net/biology-qualifiers/is";
    std::string actual = predicate2.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PredicateTests, TestGetNodeFromPtr) {
    Predicate predicate2(bqb_ns, "is", "bqbiol");
    PredicatePtr ptr = std::make_unique<Predicate>(std::move(predicate2));
    std::string expected = "http://biomodels.net/biology-qualifiers/is";
    std::string actual = ptr->str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PredicateTests, TestGetNodebqb) {
    BiomodelsBiologyQualifier qualifiers("is");
    std::string expected = "http://biomodels.net/biology-qualifiers/is";
    std::string actual = qualifiers.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PredicateTests, TestGetNodeFromPtrBqB) {
    // todo This test exposes a memory leak that I haven't been
    //  able to figure out yet. Save until later when you can confer
    //  with Herbert or Lucian.
    BiomodelsBiologyQualifier qualifiers("is");
    PredicatePtr ptr = std::make_unique<BiomodelsBiologyQualifier>(std::move(qualifiers));
    std::string expected = "http://biomodels.net/biology-qualifiers/is";
    std::string actual = ptr->str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PredicateTests, TestGetNodebqbFails) {
    ASSERT_THROW(BiomodelsBiologyQualifier qualifiers("isnot"), std::logic_error);
}

TEST_F(PredicateTests, TestGetNodebqqPrefix) {
    BiomodelsBiologyQualifier qualifiers("is");
    std::string expected = "bqbiol";
    ASSERT_STREQ(expected.c_str(), qualifiers.getPrefix().c_str());
}

TEST_F(PredicateTests, TestDCTermPrefix) {
    DCTerm term("Description");
    std::string expected = "dcterms";
    ASSERT_STREQ(expected.c_str(), term.getPrefix().c_str());
}

TEST_F(PredicateTests, TestDCTermUri) {
    DCTerm term("Description");
    std::string expected = "http://purl.org/dc/terms/Description";
    std::string actual = term.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(PredicateTests, TestDCTermGetNamespace) {
    DCTerm term("Description");
    std::string expected = "http://purl.org/dc/terms/";
    std::string actual = term.getNamespace();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PredicateTests, TestDCTermGetPrefix) {
    DCTerm term("Description");
    std::string expected = "dcterms";
    std::string actual = term.getPrefix();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PredicateTests, TestBqBiolGetNamespace) {
    BiomodelsBiologyQualifier term("is");
    std::string expected = "http://biomodels.net/biology-qualifiers/";
    std::string actual = term.getNamespace();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(PredicateTests, TestBqBiolGetPrefix) {
    BiomodelsBiologyQualifier term("is");
    std::string expected = "bqbiol";
    std::string actual = term.getPrefix();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(PredicateTests, TestBqModelGetNamespace) {
    BiomodelsBiologyQualifier term("is");
    std::string expected = "http://biomodels.net/biology-qualifiers/";
    std::string actual = term.getNamespace();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(PredicateTests, TestBqModelGetPrefix) {
    BiomodelsBiologyQualifier term("is");
    std::string expected = "bqbiol";
    std::string actual = term.getPrefix();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(PredicateTests, TestBqModelGetPrefixFromPtr) {
    BiomodelsBiologyQualifier term("is");
    std::shared_ptr<BiomodelsBiologyQualifier> term_ptr = std::make_unique<BiomodelsBiologyQualifier>(std::move(term));
    std::string expected = "bqbiol";
    std::string actual = term_ptr->getPrefix();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(PredicateTests, TestBqModelGetPrefixFromPtrToBaseClass) {
    BiomodelsBiologyQualifier term("is");
    std::shared_ptr<Predicate> term_ptr = std::make_unique<BiomodelsBiologyQualifier>(std::move(term));
    std::string expected = "bqbiol";
    std::string actual = term_ptr->getPrefix();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(PredicateTests, TestBqModelGetPrefixFromPtrToBaseClassvsdf) {
    std::shared_ptr<Predicate> term_ptr =
            std::make_unique<Predicate>(BiomodelsBiologyQualifier("is"));
    std::string expected = "bqbiol";
    std::string actual = term_ptr->getPrefix();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PredicateTests, TestSemsimPredicatePrefix) {
    std::shared_ptr<Predicate> term_ptr =
            std::make_unique<Predicate>(SemSim("hasSourceParticipant"));
    std::string expected = "semsim";
    std::string actual = term_ptr->getPrefix();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(PredicateTests, TestSemsimPredicateNamespace) {
    std::shared_ptr<Predicate> term_ptr =
            std::make_unique<Predicate>(SemSim("hasSourceParticipant"));
    std::string expected = "http://www.bhi.washington.edu/semsim#";
    std::string actual = term_ptr->getNamespace();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(PredicateTests, TestFromUriNode) {
    std::string url_str = "https://www.notarealaddress.com";
    Predicate predicate(LibrdfNode::fromUriString(url_str.c_str()));
    std::string node_string = predicate.str();
    ASSERT_STREQ(url_str.c_str(), node_string.c_str());
}


TEST_F(PredicateTests, TestFromUriNodeNamespace) {
    std::string url_str = "https://www.notarealaddress.com/nota/term";
    Predicate predicate(LibrdfNode::fromUriString(url_str.c_str()));
    const std::string &actual = predicate.getNamespace();
    std::string expected = "https://www.notarealaddress.com/nota/";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PredicateTests, TestFromUriNodeNamespaceWhenPrefixIsKnown) {
    std::string url_str = "https://biomodels.net/biology-qualifiers/is";
    Predicate predicate(LibrdfNode::fromUriString(url_str.c_str()));
    const std::string &actual = predicate.getNamespace();
    std::string expected = "https://biomodels.net/biology-qualifiers/";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PredicateTests, TestNamespaceWhenItEndsWithHash) {
    std::string url_str = "http://www.bhi.washington.edu/semsim#hasSourceParticipant";
    Predicate predicate(LibrdfNode::fromUriString(url_str.c_str()));
    const std::string &actual = predicate.getNamespace();
    std::string expected = "http://www.bhi.washington.edu/semsim#";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PredicateTests, TestPrefixWhenNamespaceEndsWithHash) {
    std::string url_str = "http://www.bhi.washington.edu/semsim#hasSourceParticipant";
    Predicate predicate(LibrdfNode::fromUriString(url_str.c_str()));
    const std::string &actual = predicate.getPrefix();
    std::string expected = "semsim";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PredicateTests, TestTermWhenNamespaceEndsWithHash) {
    std::string url_str = "http://www.bhi.washington.edu/semsim#hasSourceParticipant";
    Predicate predicate(LibrdfNode::fromUriString(url_str.c_str()));
    const std::string &actual = predicate.getTerm();
    std::string expected = "hasSourceParticipant";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PredicateTests, TestFromUriNodeTerm) {
    std::string url_str = "https://www.notarealaddress.com/nota/term";
    Predicate predicate(LibrdfNode::fromUriString(url_str.c_str()));
    const std::string &actual = predicate.getTerm();
    std::string expected = "term";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PredicateTests, TestFromUriNodePrefix) {
    std::string url_str = "https://www.notarealaddress.com/nota/term";
    Predicate predicate(LibrdfNode::fromUriString(url_str.c_str()));
    const std::string &actual = predicate.getPrefix();
    std::string expected = "NotSet";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PredicateTests, TestNamespaceKnownWhenNamespaceIsKnown) {
    std::string ns = "http://purl.org/dc/terms/";
    ASSERT_TRUE(Predicate::namespaceKnown(ns)
    );
}


TEST_F(PredicateTests, TestNamespaceKnownWhenNamespaceIsNotKnown) {
    std::string ns = "http://www.notarealaddress.com/nota/";
    ASSERT_FALSE(Predicate::namespaceKnown(ns)
    );
}

TEST_F(PredicateTests, TestPredicateFactory) {
    PredicatePtr predicatePtr = PredicateFactory("bqb", "is");
    std::string actual = predicatePtr->str();
    std::string expected = "http://biomodels.net/biology-qualifiers/is";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PredicateTests, TestPredicateFactory1err) {
    ASSERT_THROW(PredicateFactory("unknown", "description"), std::invalid_argument
    );
}

TEST_F(PredicateTests, TestPredicateFactory2) {
    PredicatePtr predicatePtr = PredicateFactory("dc", "Description");
    std::string actual = predicatePtr->str();
    std::string expected = "http://purl.org/dc/terms/Description";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PredicateTests, TestPredicateFactory2err) {
    ASSERT_THROW(PredicateFactory("dc", "description"), std::invalid_argument
    );
}

TEST_F(PredicateTests, TestPredicateFactory3) {
    PredicatePtr predicatePtr = PredicateFactory("BiomodelsModelQualifier", "hasInstance");
    std::string actual = predicatePtr->str();
    std::string expected = "http://biomodels.net/model-qualifiers/hasInstance";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PredicateTests, TestPredicateFactory4) {
    PredicatePtr predicatePtr = PredicateFactory("BiomodelsModelQualifier", "hasInstance");
    std::string actual = predicatePtr->str();
    std::string expected = "http://biomodels.net/model-qualifiers/hasInstance";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(PredicateTests, TestPredicateWithoutSubclass) {
    Predicate predicate = Predicate("ns", "term", "prefix");
    std::string actual = predicate.str();
    std::string expected = "ns/term";
    ASSERT_STREQ(actual.c_str(), expected.c_str());
}

TEST_F(PredicateTests, TestPredicateWithoutSubclass2) {
    PredicatePtr predicate = std::make_unique<Predicate>(
            Predicate("ns", "term", "prefix")
    );
    std::string actual = predicate->str();
    std::string expected = "ns/term";
    ASSERT_STREQ(actual.c_str(), expected.c_str());
}

TEST_F(PredicateTests, TestPredicateWithoutSubclass3) {
    PredicatePtr predicate = std::make_unique<Predicate>(
            Predicate("https://stackoverflow.com/questions/", "how-do-you", "so")
    );
    std::string actual = predicate->str();
    std::string expected = "https://stackoverflow.com/questions/how-do-you";
    ASSERT_STREQ(actual.c_str(), expected.c_str());
}











