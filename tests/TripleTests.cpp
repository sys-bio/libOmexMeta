//
// Created by Ciaran on 4/4/2020.
//

#include <semsim/Predicate.h>
#include <semsim/Resource.h>
#include <semsim/Triple.h>
#include "gtest/gtest.h"


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
//    semsim::BiomodelsQualifier predicate;
    semsim::Resource resource;
    semsim::BiomodelsQualifier predicate;


    TripleTests() {
        this->subject = semsim::Subject(subject_str);
        this->resource = semsim::Resource(resource_namespace, resource_id);
        this->predicate = semsim::BiomodelsQualifier("is");
    }
};

TEST_F(TripleTests, TestInstantiationFromUniquePtr) {
    semsim::Triple triple(
            subject,
            std::make_unique<semsim::Predicate>(predicate),
            resource
    );
    ASSERT_TRUE(true); // if we get this far the test has passed
}

TEST_F(TripleTests, TestInstantiationFromPredicateValue) {
    semsim::Triple triple(
            subject,
            predicate,
            resource
    );
    ASSERT_TRUE(true); // if we get this far the test has passed
}

TEST_F(TripleTests, TestInstantiation3) {
    semsim::Triple triple(
            subject,
            semsim::BiomodelsQualifier("is"),
            resource
    );
    ASSERT_TRUE(true); // if we get this far the test has passed
}

TEST_F(TripleTests, TestSubjectMetaId) {
    semsim::Triple triple(
            subject,
            predicate,
            resource
    );
    std::string subject_metaid = triple.getSubject().getMetaId();
    std::string expected = subject_str;
    ASSERT_STREQ(expected.c_str(), subject_metaid.c_str());
}

TEST_F(TripleTests, TestSubjectMetaId2) {
    semsim::Triple triple(
            subject,
            std::make_unique<semsim::Predicate>(predicate),
            resource
    );
    std::string subject_metaid = triple.getSubject().getMetaId();
    std::string expected = subject_str;
    ASSERT_STREQ(expected.c_str(), subject_metaid.c_str());
}

TEST_F(TripleTests, TestPredicate1) {
    semsim::Triple triple(subject, predicate, resource);
    std::string expected = predicate_str;
    ASSERT_STREQ(expected.c_str(), triple.getPredicate()->getUri().str().c_str());
}


TEST_F(TripleTests, TestPredicate2) {
    semsim::Triple triple(subject, std::make_unique<semsim::Predicate>(predicate), resource);
    std::string expected = predicate_str;
    ASSERT_STREQ(expected.c_str(), triple.getPredicate()->getUri().str().c_str());
}

TEST_F(TripleTests, TestResource) {
    semsim::Triple triple(subject, predicate, resource);
    std::string actual = triple.getResource().getIdentifier();
    std::string expected = resource_id;
    ASSERT_STREQ(expected.c_str(), resource_id.c_str());
}

TEST_F(TripleTests, TestTripleGetResource) {
    semsim::Triple triple1(subject, predicate, resource);
    semsim::Triple triple2(subject, predicate, resource);
    std::vector<semsim::Triple> vec = {triple1, triple2};
    std::string actual = vec[0].getResource().build();
    std::string expected = "https://identifiers.org/uniprot/P0DP23";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

//TEST_F(TripleTests, TestSerializeATripleToRdfXmlAbbrv) {
//    semsim::Triple triple(subject, predicate, resource);
//    std::string actual = triple.serialize("rdfxml-abbrev");
//    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
//                           "<rdf:RDF xmlns:bqb=\"http://biomodels.net/biology-qualifiers/\"\n"
//                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n"
//                           "  <rdf:Description rdf:about=\"./MyModel#metaid_0\">\n"
//                           "    <bqb:is rdf:resource=\"https://identifiers.org/uniprot/P0DP23\"/>\n"
//                           "  </rdf:Description>\n"
//                           "</rdf:RDF>\n";
//    std::cout << actual << std::endl;
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}
//
//
//TEST_F(TripleTests, TestReadFromXml) {
//    std::cout << __FILE__ << ":" << __LINE__ << std::endl;
//    semsim::Triple::from_xml(sample_annotation1);
//    std::cout << __FILE__ << ":" << __LINE__ << std::endl;
////    std::cout << triple.getResource() << std::endl;
//}































