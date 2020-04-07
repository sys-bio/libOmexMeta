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

    semsim::Subject subject;
    semsim::Predicate predicate;
    semsim::Resource resource;

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

    TripleTests() :
            subject(semsim::Subject(subject_str)),
            predicate(semsim::BiomodelsQualifier("is").make_shared()),
            resource(semsim::Resource(resource_namespace, resource_id)) {}
};

TEST_F(TripleTests, TestSubjectMetaId) {
    semsim::Triple triple(subject, predicate, resource);
    std::string subject_metaid = triple.getSubject().getMetaId();
    std::string expected = subject_str;
    ASSERT_STREQ(expected.c_str(), subject_metaid.c_str());
}

TEST_F(TripleTests, TestPredicate) {
    semsim::Triple triple(subject, predicate, resource);
    semsim::Predicate predicate1 = triple.getPredicate();
    std::string expected = predicate_str;
    ASSERT_STREQ(expected.c_str(), predicate1.getUri().str().c_str());
}

TEST_F(TripleTests, TestResource) {
    semsim::Triple triple(subject, predicate, resource);
    std::string actual = triple.getResource().getIdentifier();
    std::string expected = resource_id;
    ASSERT_STREQ(expected.c_str(), resource_id.c_str());
}

TEST_F(TripleTests, TestSerializeATripleToRdfXmlAbbrv) {
    semsim::Triple triple(subject, predicate, resource);
    std::string actual = triple.serialize("rdfxml-abbrev");
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqb=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n"
                           "  <rdf:Description rdf:about=\"./MyModel#metaid_0\">\n"
                           "    <bqb:is rdf:resource=\"https://identifiers.org/uniprot/P0DP23\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n";
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(TripleTests, TestReadFromXml) {
    semsim::Triple::from_xml(sample_annotation1);
//    std::cout << triple.getResource() << std::endl;
}































