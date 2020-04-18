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
    librdf_node* node = predicate2.toRdfNode();
    const char* actual = (const char*)librdf_uri_as_string(node->value.uri);
    ASSERT_STREQ(expected.c_str(), actual);
}


TEST_F(PredicateTests, TestToRdfNodebqb) {
    semsim::BiomodelsQualifiers qualifiers(world, "is");
    std::string expected = "http://biomodels.net/biology-qualifiers/is";
    librdf_node* node = qualifiers.toRdfNode();
    const char* actual = (const char*)librdf_uri_as_string(node->value.uri);
    ASSERT_STREQ(expected.c_str(), actual);
}

TEST_F(PredicateTests, TestToRdfNodebqbFails) {
    ASSERT_THROW(semsim::BiomodelsQualifiers qualifiers(world, "isnot"),
            std::logic_error);
}

TEST_F(PredicateTests, TestToRdfNodebqqPrefix) {
    semsim::BiomodelsQualifiers qualifiers(world, "is");
    std::string expected = "bqbiol";
    ASSERT_STREQ(expected.c_str(), qualifiers.prefix_.c_str());
}


//TEST_F(PredicateTests, TestCreateStaticFunctionFromBasePredicate) {
//    semsim::Predicate2 predicate2 = semsim::Predicate2::create(world, bqb_ns, "is", "bqbiol");
//    std::string expected = "http://biomodels.net/biology-qualifiers/is";
//    std::string actual = predicate2.str();
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}
//TEST_F(PredicateTests, TestCreateStaticFunctionFromBasePredicateNonStatic) {
//    semsim::Predicate2 predicate2 = semsim::Predicate2::create(world, bqb_ns, "is", "bqbiol");
//    std::string expected = "http://biomodels.net/biology-qualifiers/is";
//    std::string actual = predicate2.str();
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}
//TEST_F(PredicateTests, TestToRdfNode) {
//    semsim::Predicate2 predicate2 = semsim::Predicate2::create(world, bqb_ns, "is", "bqbiol");
//    std::string expected = "http://biomodels.net/biology-qualifiers/is";
//    librdf_node* node = predicate2.toRdfNode();
//    const char* actual = (const char*)librdf_uri_as_string(node->value.uri);
//    ASSERT_STREQ(expected.c_str(), actual);
//}
/*
 * another potential implementation would to have multiple static functions,
 * one for each set of terms we want to use. I.e. dublin core and bqbiol...
 * This leave a problem for validation however. How would be achieve
 * this? We could make validate static as well, and provide it with a
 * list of strings as an argument to check against. Then we could hard code the
 * valid_terms_ vectors. But this means we would need to pass the parameters
 * to predicate every time. So this doesn't work!
 */
//TEST_F(PredicateTests, TestBqbCreateStaticFunctionFromBasePredicate) {
//    semsim::BiomodelsQualifiers b = semsim::BiomodelsQualifiers::create(world, "namespace", "term", "prefix");
//    std::cout << b.str() << std::endl;
//    semsim::BiomodelsQualifiers predicate2 = semsim::BiomodelsQualifiers::create("is");
//    std::string expected = "http://biomodels.net/biology-qualifiers/is";
//    std::string actual = predicate2.str();
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}
//TEST_F(PredicateTests, TestBqbToRdfNode) {
//    semsim::Predicate2 predicate2 = semsim::Predicate2::create(world, bqb_ns, "is", "bqbiol");
//    std::string expected = "http://biomodels.net/biology-qualifiers/is";
//    librdf_node* node = predicate2.toRdfNode();
//    const char* actual = (const char*)librdf_uri_as_string(node->value.uri);
//    ASSERT_STREQ(expected.c_str(), actual);
//}
//
//
//TEST_F(PredicateTests, TestFailure) {
//    ASSERT_THROW(semsim::BiomodelsQualifier bqb_is("isa"), std::invalid_argument);
//}
//
//
//TEST_F(PredicateTests, TestNamespace) {
//    semsim::BiomodelsQualifier bqb_is("is");
//    std::string expected = "http://biomodels.net/biology-qualifiers/";
//    ASSERT_STREQ(expected.c_str(), bqb_is.getNamespace().c_str());
//}
//
//
//TEST_F(PredicateTests, TestStr) {
//    semsim::BiomodelsQualifier bqb_is("is");
//    std::string expected = "http://biomodels.net/biology-qualifiers/is";
//    ASSERT_STREQ(expected.c_str(), bqb_is.str().c_str());
//}
//
//TEST_F(PredicateTests, TestPrefix) {
//    semsim::BiomodelsQualifier bqb_is("is");
//    std::string expected = "bqbiol";
//    ASSERT_STREQ(expected.c_str(), bqb_is.getPrefix().c_str());
//}
//
//TEST_F(PredicateTests, TestTerm) {
//    semsim::BiomodelsQualifier bqb_is("is");
//    std::string expected = "is";
//    ASSERT_STREQ(expected.c_str(), bqb_is.getTerm().c_str());
//}
//
//TEST_F(PredicateTests, TestNamespaceDCTerms) {
//    semsim::DCTerms description("Description");
//    std::string expected = "http://purl.org/dc/terms/";
//    ASSERT_STREQ(expected.c_str(), description.getNamespace().c_str());
//}
//
//
//TEST_F(PredicateTests, TestStrDCTerms) {
//    semsim::DCTerms description("Description");
//    std::string expected = "http://purl.org/dc/terms/Description";
//    ASSERT_STREQ(expected.c_str(), description.str().c_str());
//}
//
//TEST_F(PredicateTests, TestPrefixDCTerms) {
//    semsim::DCTerms description("Description");
//    std::string expected = "dc";
//    ASSERT_STREQ(expected.c_str(), description.getPrefix().c_str());
//}
//
//TEST_F(PredicateTests, TestTermDCTerms) {
//    semsim::DCTerms description("Description");
//    std::string expected = "Description";
//    ASSERT_STREQ(expected.c_str(), description.getTerm().c_str());
//}
//
//









