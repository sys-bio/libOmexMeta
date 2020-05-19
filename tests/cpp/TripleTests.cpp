//
// Created by Ciaran on 4/4/2020.
//

#include <semsim/Predicate.h>
#include <semsim/Resource.h>
#include <semsim/Triple.h>
#include "semsim/RDFNode.h"
#include "gtest/gtest.h"
#include "semsim/SemsimUtils.h"

class TripleTests : public ::testing::Test {
public:

    std::string subject_str = "./MyModel#metaid_0";
    std::string predicate_str = "http://biomodels.net/biology-qualifiers/is";
    std::string resource_namespace = "uniprot";
    std::string resource_id = "P0DP23";


    std::string sample_annotation1 = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                                     "<rdf:RDF xmlns:bqb=\"http://biomodels.net/biology-qualifiers/\"\n"
                                     "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n"
                                     "  <rdf:Description rdf:about=\"./MyModel#metaid_0\">\n"
                                     "    <bqb:is rdf:resource=\"https://identifiers.org/uniprot/P0DP23\"/>\n"
                                     "  </rdf:Description>\n"
                                     "</rdf:RDF>";
    std::string sample_annotation2 = "<annotation>\n"
                                     "    <rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                                     "             xmlns:dc=\"http://purl.org/dc/elements/1.1/\" xmlns:dcterms=\"http://purl.org/dc/terms/\"\n"
                                     "             xmlns:vCard=\"http://www.w3.org/2001/vcard-rdf/3.0#\"\n"
                                     "             xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                                     "             xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\">\n"
                                     "        <rdf:Description rdf:about=\"#metaid_1\">\n"
                                     "            <bqbiol:is>\n"
                                     "                <rdf:Bag>\n"
                                     "                    <rdf:li rdf:resource=\"http://identifiers.org/chebi/CHEBI:15343\"/>\n"
                                     "                </rdf:Bag>\n"
                                     "            </bqbiol:is>\n"
                                     "        </rdf:Description>\n"
                                     "    </rdf:RDF>\n"
                                     "</annotation>";

    std::string sample_annotation3 = "<annotation>\n"
                                     "    <rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                                     "             xmlns:dc=\"http://purl.org/dc/elements/1.1/\" xmlns:dcterms=\"http://purl.org/dc/terms/\"\n"
                                     "             xmlns:vCard=\"http://www.w3.org/2001/vcard-rdf/3.0#\"\n"
                                     "             xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                                     "             xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\">\n"
                                     "        <rdf:Description rdf:about=\"#metaid_2\">\n"
                                     "            <bqbiol:is>\n"
                                     "                <rdf:Bag>\n"
                                     "                    <rdf:li rdf:resource=\"http://identifiers.org/chebi/CHEBI:28907\"/>\n"
                                     "                </rdf:Bag>\n"
                                     "            </bqbiol:is>\n"
                                     "        </rdf:Description>\n"
                                     "    </rdf:RDF>\n"
                                     "</annotation>";

    semsim::Subject subject;
    semsim::Resource resource;
    semsim::BiomodelsBiologyQualifier predicate;
    semsim::PredicatePtr predicatePtr;

    librdf_world *world_;

    //todo subject could pass the world_ to the node
    TripleTests() {
        world_ = librdf_new_world();
        this->subject = semsim::Subject(world_, semsim::RDFURINode(world_, subject_str));
        this->resource = semsim::Resource(world_, semsim::RDFURINode(world_, resource_namespace + "/" + resource_id));
        this->predicate = semsim::BiomodelsBiologyQualifier(world_, "is");
        predicatePtr = std::make_shared<semsim::Predicate>(predicate);

    }
};

TEST_F(TripleTests, TestInstantiation1
) {
semsim::Triple triple(world_,
                      subject,
                      std::make_shared<semsim::Predicate>(predicate),
                      resource);
ASSERT_TRUE(true); // if we get this far the test has passed
}

TEST_F(TripleTests, TestInstantiation2
) {
semsim::Triple triple(world_, subject, predicate, resource);
ASSERT_TRUE(true); // if we get this far the test has passed
}

TEST_F(TripleTests, TestSubjectMetaId
) {
semsim::Triple triple(world_, subject,
                      std::make_shared<semsim::Predicate>(predicate), resource);
std::string &expected = subject_str;
std::string actual = triple.getSubject().str();
ASSERT_STREQ(expected
.

c_str(), actual

.

c_str()

);
}


TEST_F(TripleTests, TestSubjectMetaId2
) {
semsim::Triple triple(world_, subject,
                      predicatePtr, resource);
std::string &expected = subject_str;
std::string actual = triple.getSubject().str();
ASSERT_STREQ(expected
.

c_str(), actual

.

c_str()

);
}

TEST_F(TripleTests, TestPredicate1
) {
semsim::Triple triple(world_, subject, predicate, resource);
std::string expected = predicate_str;
ASSERT_STREQ(expected
.

c_str(), triple

.getPredicatePtr()->str().

c_str()

);
}


TEST_F(TripleTests, TestPredicate2
) {
semsim::Triple triple(world_, subject, predicate, resource);
std::string expected = predicate_str;
const char *actual = (const char *) librdf_uri_as_string(
        librdf_node_get_uri(triple.getPredicatePtr()->toRdfNode()));
ASSERT_STREQ(expected
.

c_str(), triple

.getPredicatePtr()->str().

c_str()

);
}

//TEST_F(TripleTests, TestPredicate3) {
//    semsim::Triple triple(world_, subject, predicate, resource);
//    std::string expected = predicate_str;
//    std::cout << triple.getPredicatePtr()->str() << std::endl;
//    std::cout << triple.getPredicatePtr()->getUri() << std::endl;
//    std::cout << triple.getPredicatePtr()->getTerm() << std::endl;
//    std::cout << triple.getPredicatePtr()->getNamespace() << std::endl;
////    const char* actual = (const char*) librdf_uri_as_string(librdf_node_get_uri(triple.getPredicatePtr()->toRdfNode()));
////    ASSERT_STREQ(expected.c_str(), triple.getPredicatePtr()->str().c_str());
//}


//
//
//TEST_F(TripleTests, TestPredicate2) {
//    semsim::Triple triple(subject, std::make_unique<semsim::Predicate>(predicate), resource, world_);
//    std::string expected = predicate_str;
//    ASSERT_STREQ(expected.c_str(), triple.getPredicate()->getUri().str().c_str());
//}
//
TEST_F(TripleTests, TestResource
) {
semsim::Triple triple(world_, subject, predicatePtr, resource);
std::string actual = triple.getResource().str();
std::string expected = resource_id;
ASSERT_STREQ(expected
.

c_str(), resource_id

.

c_str()

);
}
TEST_F(TripleTests, TestResource2
) {
semsim::Triple triple(world_, subject, predicatePtr, resource);
std::string actual = (const char *) librdf_uri_to_string(librdf_node_get_uri(triple.getResource().toRdfNode()));
std::string expected = resource_id;
ASSERT_STREQ(expected
.

c_str(), resource_id

.

c_str()

);
}

TEST_F(TripleTests, TestTripleVecGetResource
) {
semsim::Triple triple1(world_, subject, predicatePtr, resource);
semsim::Triple triple2(world_, subject, predicatePtr, resource);
std::vector<semsim::Triple> vec = {triple1, triple2};
std::string actual = (const char *) librdf_uri_to_string(librdf_node_get_uri(vec[0].getResource().toRdfNode()));
std::string expected = "https://identifiers.org/uniprot/P0DP23";
ASSERT_STREQ(expected
.

c_str(), actual

.

c_str()

);
}

//TEST_F(TripleTests, TestTripleFromStrings) {
//    semsim::Triple triple1("metaid001", predicatePtr, "uniprot:P07362", world_);
//    std::string actual = triple1.getResource().str();
//    std::string expected = "https://identifiers.org/uniprot/P07362";
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}
//
TEST_F(TripleTests, TestToStatementSubject
) {
semsim::Triple triple1(world_, subject, predicatePtr, resource);
librdf_statement *statement = triple1.toStatement();
auto x = librdf_statement_get_subject(statement); // anonymous struct
std::string actual = (const char *) librdf_uri_as_string(x->value.uri);
std::string expected = "./MyModel#metaid_0";
ASSERT_STREQ(expected
.

c_str(), actual

.

c_str()

);
}

TEST_F(TripleTests, TestToStatementPrediacte
) {
semsim::Triple triple1(world_, subject, predicatePtr, resource);
librdf_statement *statement = triple1.toStatement();
auto x = librdf_statement_get_predicate(statement); // anonymous struct
std::string actual = (const char *) librdf_uri_as_string(x->value.uri);
std::string expected = "http://biomodels.net/biology-qualifiers/is";
ASSERT_STREQ(expected
.

c_str(), actual

.

c_str()

);
}


TEST_F(TripleTests, TestToStatementResource
) {
semsim::Triple triple1(world_, subject, predicatePtr, resource);
librdf_statement *statement = triple1.toStatement();
raptor_term *x = librdf_statement_get_object(statement); // anonymous struct
const char *actual = (const char *) librdf_uri_as_string(x->value.uri);
const char *expected = "https://identifiers.org/uniprot/P0DP23";
ASSERT_STREQ(expected, actual
);
}

TEST_F(TripleTests, TestFromStatementSubject
) {
semsim::Triple triple1(world_, subject, predicatePtr, resource);
// quickly create a statement
librdf_statement *statement = triple1.toStatement();
semsim::Triple triple2 = semsim::Triple::fromStatement(world_, statement);
std::string actual = triple2.getSubject().str();
std::string expected = "./MyModel#metaid_0";
ASSERT_STREQ(expected
.

c_str(), actual

.

c_str()

);
}

TEST_F(TripleTests, TestFromStatementResource
) {
semsim::Triple triple1(world_, subject, predicatePtr, resource);
// quickly create a statement
librdf_statement *statement = triple1.toStatement();
semsim::Triple triple2 = semsim::Triple::fromStatement(world_, statement);
std::string actual = triple2.getResource().str();
std::string expected = "https://identifiers.org/uniprot/P0DP23";
ASSERT_STREQ(expected
.

c_str(), actual

.

c_str()

);
}

TEST_F(TripleTests, TestFromStatementPredicate
) {
semsim::Triple triple1(world_, subject, predicatePtr, resource);
// quickly create a statement
librdf_statement *statement = triple1.toStatement();
semsim::Triple triple2 = semsim::Triple::fromStatement(world_, statement);
std::string actual = triple2.getPredicatePtr()->str();
std::string expected = "http://biomodels.net/biology-qualifiers/is";
ASSERT_STREQ(expected
.

c_str(), actual

.

c_str()

);
}


TEST_F(TripleTests, TestAbout
) {
semsim::Triple triple(world_);
triple.setAbout("metaid2");
std::string expected = "metaid2";
std::string actual = triple.getAbout();
ASSERT_STREQ(expected
.

c_str(), actual

.

c_str()

);
}


TEST_F(TripleTests, TestSetPredicate
) {
semsim::Triple triple(world_);
triple.setPredicate("bqb", "is");
std::string expected = "http://biomodels.net/biology-qualifiers/is";
std::string actual = triple.getPredicatePtr()->str();
ASSERT_STREQ(expected
.

c_str(), actual

.

c_str()

);
}

TEST_F(TripleTests, TestSetPredicate2
) {
semsim::Triple triple(world_);
triple.setPredicateNew("https://stackoverflow.com/questions/", "how-do-you", "so");
std::string expected = "https://stackoverflow.com/questions/how-do-you";
semsim::PredicatePtr predicatePtr = triple.getPredicatePtr();
std::string actual = predicatePtr->str();
ASSERT_STREQ(expected
.

c_str(), actual

.

c_str()

);
}

TEST_F(TripleTests, TestResourceLiteral
) {
semsim::Triple triple(world_);
triple.setResourceLiteral("Annotating");
std::string expected = "Annotating";
std::string actual = triple.getResource().str();
ASSERT_STREQ(expected
.

c_str(), actual

.

c_str()

);
}

TEST_F(TripleTests, TestResourceUri
) {
semsim::Triple triple(world_);
triple.setResourceUri("AnnotatingUri");
std::string expected = "AnnotatingUri";
std::string actual = triple.getResource().str();
ASSERT_STREQ(expected
.

c_str(), actual

.

c_str()

);
}

TEST_F(TripleTests, TestResourceBlank
) {
semsim::Triple triple(world_);
triple.setResourceBlank("AnnotatingBlank");
std::string expected = "AnnotatingBlank";
std::string actual = triple.getResource().str();
ASSERT_STREQ(expected
.

c_str(), actual

.

c_str()

);
}

TEST_F(TripleTests, TestBuilderPattern
) {
semsim::Triple triple(world_);

triple.setAbout("metaid1")
.setPredicate("bqb", "is")
.setResourceUri("uniprot/PD4034");

std::string actual = triple.str();
std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                       "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                       "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                       "   xml:base=\"file://./annotations.rdf\">\n"
                       "  <rdf:Description rdf:about=\"metaid1\">\n"
                       "    <bqbiol:is rdf:resource=\"https://identifiers.org/uniprot/PD4034\"/>\n"
                       "  </rdf:Description>\n"
                       "</rdf:RDF>\n";
ASSERT_STREQ(expected
.

c_str(), actual

.

c_str()

);
}





























