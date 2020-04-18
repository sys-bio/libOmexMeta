//
// Created by Ciaran on 4/5/2020.
//
#include "librdf.h"
#include "gtest/gtest.h"
#include "semsim/Predicate2.h"


class PredicateTests : public ::testing::Test {
public:

    std::string bqb_ns = "http://biomodels.net/biology-qualifiers/";

    librdf_world *world;
    librdf_model *model;
    librdf_storage *storage;

    PredicateTests() {
        world = librdf_new_world();
        storage = librdf_new_storage(world, "memory", "test", nullptr);
        model = librdf_new_model(world, storage, nullptr);

    }

    ~PredicateTests() override {
        librdf_free_world(world);
        librdf_free_model(model);
        librdf_free_storage(storage);
    }

};

TEST_F(PredicateTests, TestCreateStaticFunctionFromBasePredicate) {
    semsim::Predicate2 predicate2(world, bqb_ns, "is", "bqbiol");
    std::string expected = "http://biomodels.net/biology-qualifiers/is";
    std::string actual = predicate2.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PredicateTests, TestToRdfNode) {
    semsim::Predicate2 predicate2(world, bqb_ns, "is", "bqbiol");
    std::string expected = "http://biomodels.net/biology-qualifiers/is";
    librdf_node *node = predicate2.toRdfNode();
    const char *actual = (const char *) librdf_uri_as_string(node->value.uri);
    ASSERT_STREQ(expected.c_str(), actual);
}


TEST_F(PredicateTests, TestToRdfNodebqb) {
    semsim::BiomodelsQualifiers qualifiers(world, "is");
    std::string expected = "http://biomodels.net/biology-qualifiers/is";
    librdf_node *node = qualifiers.toRdfNode();
    const char *actual = (const char *) librdf_uri_as_string(node->value.uri);
    ASSERT_STREQ(expected.c_str(), actual);
}

TEST_F(PredicateTests, TestToRdfNodebqbFails) {
    ASSERT_THROW(semsim::BiomodelsQualifiers qualifiers(world, "isnot"),
                 std::logic_error);
}

TEST_F(PredicateTests, TestToRdfNodebqqPrefix) {
    semsim::BiomodelsQualifiers qualifiers(world, "is");
    std::string expected = "bqbiol";
    ASSERT_STREQ(expected.c_str(), qualifiers.getPrefix().c_str());
}

TEST_F(PredicateTests, TestDCTermPrefix) {
    semsim::DCTerm term(world, "Description");
    std::string expected = "dc";
    ASSERT_STREQ(expected.c_str(), term.getPrefix().c_str());
}

TEST_F(PredicateTests, TestDCTermUri) {
    semsim::DCTerm term(world, "Description");
    std::string expected = "http://purl.org/dc/terms/Description";
    librdf_node *node = term.toRdfNode();
    const char *actual = (const char *) librdf_uri_as_string(node->value.uri);
    ASSERT_STREQ(expected.c_str(), actual);
}







