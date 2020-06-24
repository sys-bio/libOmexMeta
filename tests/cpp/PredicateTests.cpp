//
// Created by Ciaran on 4/5/2020.
//
#include "librdf.h"
#include "gtest/gtest.h"
#include "omexmeta/Predicate.h"

#include "RedlandAPIWrapper.h"

using namespace semsim;

class PredicateTests : public ::testing::Test {
public:

    std::string bqb_ns = "http://biomodels.net/biology-qualifiers/";


    PredicateTests() = default;

};

TEST_F(PredicateTests, TestCreateStaticFunctionFromBasePredicate) {
    Predicate predicate(bqb_ns, "is", "bqbiol");
    std::string expected = "http://biomodels.net/biology-qualifiers/is";
    std::string actual = predicate.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    predicate.freeNode();
}

TEST_F(PredicateTests, TestGetNode) {
    Predicate predicate(bqb_ns, "is", "bqbiol");
    std::string expected = "http://biomodels.net/biology-qualifiers/is";
    std::string actual = predicate.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    predicate.freeNode();
}

TEST_F(PredicateTests, TestGetNodeFromPtr) {
    Predicate predicate(bqb_ns, "is", "bqbiol");
    PredicatePtr ptr = std::make_unique<Predicate>(std::move(predicate));
    std::string expected = "http://biomodels.net/biology-qualifiers/is";
    std::string actual = ptr->str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    predicate.freeNode();
}

TEST_F(PredicateTests, TestGetNodebqb) {
    BiomodelsBiologyQualifier predicate("is");
    std::string expected = "http://biomodels.net/biology-qualifiers/is";
    std::string actual = predicate.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    predicate.freeNode();
}

TEST_F(PredicateTests, TestGetNodeFromPtrBqB) {
    // todo This test exposes a memory leak that I haven't been
    //  able to figure out yet. Save until later when you can confer
    //  with Herbert or Lucian.
    BiomodelsBiologyQualifier predicate("is");
    PredicatePtr ptr = std::make_unique<BiomodelsBiologyQualifier>(predicate);
    std::string expected = "http://biomodels.net/biology-qualifiers/is";
    std::string actual = ptr->str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    predicate.freeNode();
}

//TEST_F(PredicateTests, TestGetNodebqbFails) {
//    /*
//     * How to do this test and free the memory used by predicate.node_?
//     * Do I need to have a finally type block somewhere?
//     */
//    ASSERT_THROW(BiomodelsBiologyQualifier predicate("isnot"), std::logic_error);
//
//}

TEST_F(PredicateTests, TestGetNodebqqPrefix) {
    BiomodelsBiologyQualifier predicate("is");
    std::string expected = "bqbiol";
    ASSERT_STREQ(expected.c_str(), predicate.getPrefix().c_str());
    predicate.freeNode();
}

TEST_F(PredicateTests, TestDCTermPrefix) {
    DCTerm predicate("Description");
    std::string expected = "dcterms";
    ASSERT_STREQ(expected.c_str(), predicate.getPrefix().c_str());
    predicate.freeNode();
}

TEST_F(PredicateTests, TestDCTermUri) {
    DCTerm predicate("Description");
    std::string expected = "http://purl.org/dc/terms/Description";
    std::string actual = predicate.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    predicate.freeNode();
}


TEST_F(PredicateTests, TestDCTermGetNamespace) {
    DCTerm predicate("Description");
    std::string expected = "http://purl.org/dc/terms/";
    std::string actual = predicate.getNamespace();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    predicate.freeNode();
}

TEST_F(PredicateTests, TestDCTermGetPrefix) {
    DCTerm predicate("Description");
    std::string expected = "dcterms";
    std::string actual = predicate.getPrefix();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    predicate.freeNode();
}

TEST_F(PredicateTests, TestBqBiolGetNamespace) {
    BiomodelsBiologyQualifier predicate("is");
    std::string expected = "http://biomodels.net/biology-qualifiers/";
    std::string actual = predicate.getNamespace();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    predicate.freeNode();
}


TEST_F(PredicateTests, TestBqBiolGetPrefix) {
    BiomodelsBiologyQualifier predicate("is");
    std::string expected = "bqbiol";
    std::string actual = predicate.getPrefix();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    predicate.freeNode();
}


TEST_F(PredicateTests, TestBqModelGetNamespace) {
    BiomodelsBiologyQualifier predicate("is");
    std::string expected = "http://biomodels.net/biology-qualifiers/";
    std::string actual = predicate.getNamespace();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    predicate.freeNode();
}


TEST_F(PredicateTests, TestBqModelGetPrefix) {
    BiomodelsBiologyQualifier predicate("is");
    std::string expected = "bqbiol";
    std::string actual = predicate.getPrefix();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    predicate.freeNode();
}


TEST_F(PredicateTests, TestBqModelGetPrefixFromPtr) {
    BiomodelsBiologyQualifier predicate("is");
    std::shared_ptr<BiomodelsBiologyQualifier> term_ptr = std::make_unique<BiomodelsBiologyQualifier>(std::move(predicate));
    std::string expected = "bqbiol";
    std::string actual = term_ptr->getPrefix();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    predicate.freeNode();
}

TEST_F(PredicateTests, TestBqModelGetPrefixFromPtrToBaseClass) {
    BiomodelsBiologyQualifier predicate("is");
    std::shared_ptr<Predicate> term_ptr = std::make_unique<BiomodelsBiologyQualifier>(std::move(predicate));
    std::string expected = "bqbiol";
    std::string actual = term_ptr->getPrefix();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    predicate.freeNode();
}


TEST_F(PredicateTests, TestBqModelGetPrefixFromPtrToBaseClassvsdf) {
    std::shared_ptr<Predicate> term_ptr =
            std::make_unique<Predicate>(BiomodelsBiologyQualifier("is"));
    std::string expected = "bqbiol";
    std::string actual = term_ptr->getPrefix();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    term_ptr->freeNode();
}

TEST_F(PredicateTests, TestSemsimPredicatePrefix) {
    std::shared_ptr<Predicate> term_ptr =
            std::make_unique<Predicate>(SemSim("hasSourceParticipant"));
    std::string expected = "semsim";
    std::string actual = term_ptr->getPrefix();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    term_ptr->freeNode();
}


TEST_F(PredicateTests, TestSemsimPredicateNamespace) {
    std::shared_ptr<Predicate> term_ptr =
            std::make_unique<Predicate>(SemSim("hasSourceParticipant"));
    std::string expected = "http://www.bhi.washington.edu/semsim#";
    std::string actual = term_ptr->getNamespace();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    term_ptr->freeNode();
}

//
//TEST_F(PredicateTests, TestFromUriNode) {
//    std::string url_str = "https://www.notarealaddress.com";
//    Predicate predicate = Predicate::fromRawPtr(LibrdfNode::fromUriString(url_str.c_str()));
//    std::string node_string = predicate.str();
//    ASSERT_STREQ(url_str.c_str(), node_string.c_str());
//    predicate.freeNode();
//}
//
//
//TEST_F(PredicateTests, TestFromUriNodeNamespace) {
//    std::string url_str = "https://www.notarealaddress.com/nota/term";
//    Predicate predicate = Predicate::fromRawPtr(LibrdfNode::fromUriString(url_str.c_str()));
//    const std::string &actual = predicate.getNamespace();
//    std::string expected = "https://www.notarealaddress.com/nota/";
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//    predicate.freeNode();
//}
//
//TEST_F(PredicateTests, TestFromUriNodeNamespaceWhenPrefixIsKnown) {
//    std::string url_str = "https://biomodels.net/biology-qualifiers/is";
//    Predicate predicate = Predicate::fromRawPtr(LibrdfNode::fromUriString(url_str.c_str()));
//    const std::string &actual = predicate.getNamespace();
//    std::string expected = "https://biomodels.net/biology-qualifiers/";
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//    predicate.freeNode();
//}
//
//TEST_F(PredicateTests, TestNamespaceWhenItEndsWithHash) {
//    std::string url_str = "http://www.bhi.washington.edu/semsim#hasSourceParticipant";
//    Predicate predicate = Predicate::fromRawPtr(LibrdfNode::fromUriString(url_str.c_str()));
//    const std::string &actual = predicate.getNamespace();
//    std::string expected = "http://www.bhi.washington.edu/semsim#";
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//    predicate.freeNode();
//}
//
//TEST_F(PredicateTests, TestPrefixWhenNamespaceEndsWithHash) {
//    std::string url_str = "http://www.bhi.washington.edu/semsim#hasSourceParticipant";
//    Predicate predicate = Predicate::fromRawPtr(LibrdfNode::fromUriString(url_str.c_str()));
//    const std::string &actual = predicate.getPrefix();
//    std::string expected = "omexmeta";
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//    predicate.freeNode();
//}
//
//TEST_F(PredicateTests, TestTermWhenNamespaceEndsWithHash) {
//    std::string url_str = "http://www.bhi.washington.edu/semsim#hasSourceParticipant";
//    Predicate predicate = Predicate::fromRawPtr(LibrdfNode::fromUriString(url_str.c_str()));
//    const std::string &actual = predicate.getTerm();
//    std::string expected = "hasSourceParticipant";
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//    predicate.freeNode();
//}
//
//TEST_F(PredicateTests, TestFromUriNodeTerm) {
//    std::string url_str = "https://www.notarealaddress.com/nota/term";
//    Predicate predicate = Predicate::fromRawPtr(LibrdfNode::fromUriString(url_str.c_str()));
//    const std::string &actual = predicate.getTerm();
//    std::string expected = "term";
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//    predicate.freeNode();
//}
//
//TEST_F(PredicateTests, TestFromUriNodePrefix) {
//    std::string url_str = "https://www.notarealaddress.com/nota/term";
//    Predicate predicate = Predicate::fromRawPtr(LibrdfNode::fromUriString(url_str.c_str()));
//    const std::string &actual = predicate.getPrefix();
//    std::string expected = "NotSet";
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//    predicate.freeNode();
//}

TEST_F(PredicateTests, TestNamespaceKnownWhenNamespaceIsKnown) {
    std::string ns = "http://purl.org/dc/terms/";
    ASSERT_TRUE(Predicate::namespaceKnown(ns)
    );
}


TEST_F(PredicateTests, TestNamespaceKnownWhenNamespaceIsNotKnown) {
    std::string ns = "http://www.notarealaddress.com/nota/";
    ASSERT_FALSE(Predicate::namespaceKnown(ns));
}

TEST_F(PredicateTests, TestPredicateFactory) {
    PredicatePtr predicatePtr = PredicateFactory("bqb", "is");
    std::string actual = predicatePtr->str();
    std::string expected = "http://biomodels.net/biology-qualifiers/is";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    predicatePtr->freeNode();
}

// How to test without leak?
//TEST_F(PredicateTests, TestPredicateFactory1err) {
//    ASSERT_THROW(PredicateFactory("unknown", "description"), std::invalid_argument);
//}

TEST_F(PredicateTests, TestPredicateFactory2) {
    PredicatePtr predicatePtr = PredicateFactory("dc", "Description");
    std::string actual = predicatePtr->str();
    std::string expected = "http://purl.org/dc/terms/Description";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    predicatePtr->freeNode();
}

// how to test without leak?
//TEST_F(PredicateTests, TestPredicateFactory2err) {
//    ASSERT_THROW(PredicateFactory("dc", "description"), std::invalid_argument
//    );
//}

TEST_F(PredicateTests, TestPredicateFactory3) {
    PredicatePtr predicatePtr = PredicateFactory("BiomodelsModelQualifier", "hasInstance");
    std::string actual = predicatePtr->str();
    std::string expected = "http://biomodels.net/model-qualifiers/hasInstance";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    predicatePtr->freeNode();
}

TEST_F(PredicateTests, TestPredicateFactory4) {
    PredicatePtr predicatePtr = PredicateFactory("BiomodelsModelQualifier", "hasInstance");
    std::string actual = predicatePtr->str();
    std::string expected = "http://biomodels.net/model-qualifiers/hasInstance";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    predicatePtr->freeNode();
}


TEST_F(PredicateTests, TestPredicateWithoutSubclass) {
    Predicate predicate = Predicate("ns", "term", "prefix");
    std::string actual = predicate.str();
    std::string expected = "ns/term";
    ASSERT_STREQ(actual.c_str(), expected.c_str());
    predicate.freeNode();
}

TEST_F(PredicateTests, TestPredicateWithoutSubclass2) {
    PredicatePtr predicate = std::make_unique<Predicate>(
            Predicate("ns", "term", "prefix")
    );
    std::string actual = predicate->str();
    std::string expected = "ns/term";
    ASSERT_STREQ(actual.c_str(), expected.c_str());
    predicate->freeNode();
}

TEST_F(PredicateTests, TestPredicateWithoutSubclass3) {
    PredicatePtr predicate = std::make_unique<Predicate>(
            Predicate("https://stackoverflow.com/questions/", "how-do-you", "so")
    );
    std::string actual = predicate->str();
    std::string expected = "https://stackoverflow.com/questions/how-do-you";
    ASSERT_STREQ(actual.c_str(), expected.c_str());
    predicate->freeNode();
}

TEST(PredicateTestsNoFixture, TestEquality) {
    BiomodelsModelQualifier predicate1("isDerivedFrom");
    BiomodelsModelQualifier predicate2("isDerivedFrom");
    ASSERT_EQ(predicate1, predicate2);
    predicate1.freeNode();
    predicate2.freeNode();
}

TEST(PredicateTestsNoFixture, TestInequality) {
    BiomodelsModelQualifier predicate1("isDerivedFrom");
    BiomodelsModelQualifier predicate2("isDescribedBy");
    ASSERT_NE(predicate1, predicate2);
    predicate1.freeNode();
    predicate2.freeNode();
}


























