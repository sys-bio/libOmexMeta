//
// Created by Ciaran on 4/4/2020.
//

#include <semsim/Predicate.h>
#include <semsim/Resource.h>
#include <semsim/Triple.h>
#include "gtest/gtest.h"


class TripleTests : public ::testing::Test {
public:


    std::string subject_str;
    std::string predicate_str;
    std::string resource_namespace;
    std::string resource_id;
    semsim::Subject subject;
    semsim::Predicate predicate;
    semsim::Resource resource;

    TripleTests() :
        subject_str("./MyModel#metaid_0"),
        predicate_str("http://biomodels.net/biology-qualifiers/is"),
        resource_namespace("uniprot"),
        resource_id("P0DP23"),
        subject(semsim::Subject(subject_str)),
        predicate(semsim::Predicate(predicate_str)),
        resource(semsim::Resource(resource_namespace, resource_id)){}
};

TEST_F(TripleTests, TestSubjectMetaId) {
    semsim::Triple triple(subject, predicate, resource);
    std::string subject_metaid = triple.getSubject().getMetaId();
    std::string expected = subject_str;
    ASSERT_STREQ(expected.c_str(), subject_metaid.c_str());
}

TEST_F(TripleTests, TestPredicate) {
    semsim::Triple triple(subject, predicate, resource);
    std::string subject_metaid = triple.getPredicate().getUri().str();
    std::string expected = predicate_str;
    ASSERT_STREQ(expected.c_str(), subject_metaid.c_str());
}

TEST_F(TripleTests, TestResource) {
    semsim::Triple triple(subject, predicate, resource);
    std::string actual= triple.getResource().getIdentifier();
    std::string expected = resource_id;
    ASSERT_STREQ(expected.c_str(), resource_id.c_str());
}































