//
// Created by Ciaran on 11/07/2020.
//

#include "gtest/gtest.h"
#include "RedlandAPIWrapper.h"
#include "omexmeta/PersonalInformation.h"

using namespace omexmeta;

class PersonalInformationTests : public ::testing::Test {
public:

    redland::LibrdfStorage storage;
    redland::LibrdfModel model;

    std::string local_uri = "http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#";

    PersonalInformationTests() {
        model = redland::LibrdfModel(storage.get());
    }

    ~PersonalInformationTests() override {
        model.freeModel();
        storage.freeStorage();
    }
};

TEST_F(PersonalInformationTests, TestAddFoaf){
    PersonalInformation information(model.get(), local_uri, "TestModel.sbml");
    LibrdfNode value = LibrdfNode::fromLiteral("Ciaran Welsh");
    information.addFoaf("name", value);
    Triples triples = information.getTriples();
    std::string actual = triples.str();
    std::cout << actual << std::endl;
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:dcterms=\"http://purl.org/dc/terms/\"\n"
                           "   xmlns:foaf=\"http://xmlns.com/foaf/0.1/\"\n"
                           "   xmlns:local=\"http://MyOmexLibrary.org/MyOmex.omex/MyModel.rdf#\"\n"
                           "   xmlns:myOMEX=\"http://MyOmexLibrary.org/MyOmex.omex/MyModel.xml\"\n"
                           "   xmlns:myOMEXlib=\"http://MyOmexLibrary.org/MyOmex.omex\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n"
                           "  <rdf:Description rdf:about=\"TestModel.sbml\">\n"
                           "    <dcterms:creator rdf:resource=\"http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#PersonalInfo0000\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#PersonalInfo0000\">\n"
                           "    <foaf:name rdf:datatype=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#string\">Ciaran Welsh</foaf:name>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PersonalInformationTests, TestAddFoafUsingLiteral) {
    PersonalInformation information(model.get(), local_uri, "TestModel.sbml");
    information.addFoafLiteral("name", "Ciaran Welsh");
    Triples triples = information.getTriples();
    std::string actual = triples.str();
    std::cout << actual << std::endl;
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:dcterms=\"http://purl.org/dc/terms/\"\n"
                           "   xmlns:foaf=\"http://xmlns.com/foaf/0.1/\"\n"
                           "   xmlns:local=\"http://MyOmexLibrary.org/MyOmex.omex/MyModel.rdf#\"\n"
                           "   xmlns:myOMEX=\"http://MyOmexLibrary.org/MyOmex.omex/MyModel.xml\"\n"
                           "   xmlns:myOMEXlib=\"http://MyOmexLibrary.org/MyOmex.omex\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n"
                           "  <rdf:Description rdf:about=\"TestModel.sbml\">\n"
                           "    <dcterms:creator rdf:resource=\"http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#PersonalInfo0000\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#PersonalInfo0000\">\n"
                           "    <foaf:name rdf:datatype=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#string\">Ciaran Welsh</foaf:name>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(PersonalInformationTests, TestAddFoafUsingUri) {
    PersonalInformation information(model.get(), local_uri, "TestModel.sbml");
    information.addFoafUri("accountName", "https://orcid.org/0000-0001-8254-4957");
    Triples triples = information.getTriples();
    std::string actual = triples.str();
    std::cout << actual << std::endl;
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:dcterms=\"http://purl.org/dc/terms/\"\n"
                           "   xmlns:foaf=\"http://xmlns.com/foaf/0.1/\"\n"
                           "   xmlns:local=\"http://MyOmexLibrary.org/MyOmex.omex/MyModel.rdf#\"\n"
                           "   xmlns:myOMEX=\"http://MyOmexLibrary.org/MyOmex.omex/MyModel.xml\"\n"
                           "   xmlns:myOMEXlib=\"http://MyOmexLibrary.org/MyOmex.omex\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n"
                           "  <rdf:Description rdf:about=\"TestModel.sbml\">\n"
                           "    <dcterms:creator rdf:resource=\"http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#PersonalInfo0000\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#PersonalInfo0000\">\n"
                           "    <foaf:accountName rdf:resource=\"https://orcid.org/0000-0001-8254-4957\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PersonalInformationTests, TestAddName) {
    PersonalInformation information(model.get(), local_uri, "TestModel.sbml");
    information.addName("Ciaran Welsh");
    Triples triples = information.getTriples();
    std::string actual = triples.str();
    std::cout << actual << std::endl;
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:dcterms=\"http://purl.org/dc/terms/\"\n"
                           "   xmlns:foaf=\"http://xmlns.com/foaf/0.1/\"\n"
                           "   xmlns:local=\"http://MyOmexLibrary.org/MyOmex.omex/MyModel.rdf#\"\n"
                           "   xmlns:myOMEX=\"http://MyOmexLibrary.org/MyOmex.omex/MyModel.xml\"\n"
                           "   xmlns:myOMEXlib=\"http://MyOmexLibrary.org/MyOmex.omex\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n"
                           "  <rdf:Description rdf:about=\"TestModel.sbml\">\n"
                           "    <dcterms:creator rdf:resource=\"http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#PersonalInfo0000\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#PersonalInfo0000\">\n"
                           "    <foaf:name rdf:datatype=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#string\">Ciaran Welsh</foaf:name>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PersonalInformationTests, TestMBox) {
    PersonalInformation information(model.get(), local_uri, "TestModel.sbml");
    information.addMbox("annotations@uw.edu");
    Triples triples = information.getTriples();
    std::string actual = triples.str();
    std::cout << actual << std::endl;
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:dcterms=\"http://purl.org/dc/terms/\"\n"
                           "   xmlns:foaf=\"http://xmlns.com/foaf/0.1/\"\n"
                           "   xmlns:local=\"http://MyOmexLibrary.org/MyOmex.omex/MyModel.rdf#\"\n"
                           "   xmlns:myOMEX=\"http://MyOmexLibrary.org/MyOmex.omex/MyModel.xml\"\n"
                           "   xmlns:myOMEXlib=\"http://MyOmexLibrary.org/MyOmex.omex\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n"
                           "  <rdf:Description rdf:about=\"TestModel.sbml\">\n"
                           "    <dcterms:creator rdf:resource=\"http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#PersonalInfo0000\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#PersonalInfo0000\">\n"
                           "    <foaf:mbox rdf:datatype=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#string\">annotations@uw.edu</foaf:mbox>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PersonalInformationTests, TestAccountName) {
    PersonalInformation information(model.get(), local_uri, "TestModel.sbml");
    information.addAccountName("0000-0001-9876-3928");
    Triples triples = information.getTriples();
    std::string actual = triples.str();
    std::cout << actual << std::endl;
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:dcterms=\"http://purl.org/dc/terms/\"\n"
                           "   xmlns:foaf=\"http://xmlns.com/foaf/0.1/\"\n"
                           "   xmlns:local=\"http://MyOmexLibrary.org/MyOmex.omex/MyModel.rdf#\"\n"
                           "   xmlns:myOMEX=\"http://MyOmexLibrary.org/MyOmex.omex/MyModel.xml\"\n"
                           "   xmlns:myOMEXlib=\"http://MyOmexLibrary.org/MyOmex.omex\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n"
                           "  <rdf:Description rdf:about=\"TestModel.sbml\">\n"
                           "    <dcterms:creator rdf:resource=\"http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#PersonalInfo0000\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#PersonalInfo0000\">\n"
                           "    <foaf:accountName rdf:resource=\"https://orcid.org/0000-0001-9876-3928\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PersonalInformationTests, TestaddAccountServiceHomepage) {
    PersonalInformation information(model.get(), local_uri, "TestModel.sbml");
    information.addAccountServiceHomepage("https://github.com/sys-bio/libOmexMeta");
    Triples triples = information.getTriples();
    std::string actual = triples.str();
    std::cout << actual << std::endl;
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:dcterms=\"http://purl.org/dc/terms/\"\n"
                           "   xmlns:foaf=\"http://xmlns.com/foaf/0.1/\"\n"
                           "   xmlns:local=\"http://MyOmexLibrary.org/MyOmex.omex/MyModel.rdf#\"\n"
                           "   xmlns:myOMEX=\"http://MyOmexLibrary.org/MyOmex.omex/MyModel.xml\"\n"
                           "   xmlns:myOMEXlib=\"http://MyOmexLibrary.org/MyOmex.omex\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n"
                           "  <rdf:Description rdf:about=\"TestModel.sbml\">\n"
                           "    <dcterms:creator rdf:resource=\"http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#PersonalInfo0000\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#PersonalInfo0000\">\n"
                           "    <foaf:accountServiceHomepage rdf:resource=\"https://github.com/sys-bio/libOmexMeta\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(PersonalInformationTests, TestMultipleEntries) {
    PersonalInformation information(model.get(), local_uri, "TestModel.sbml");
    information.addName("Ciaran Welsh")
        .addAccountName("0000-1111-2222-3333")
        .addAccountServiceHomepage("https://github.com/sys-bio/libOmexMeta")
        .addMbox("annotations.uw.edu");

    Triples triples = information.getTriples();
    std::string actual = triples.str();
    std::cout << actual << std::endl;
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:dcterms=\"http://purl.org/dc/terms/\"\n"
                           "   xmlns:foaf=\"http://xmlns.com/foaf/0.1/\"\n"
                           "   xmlns:local=\"http://MyOmexLibrary.org/MyOmex.omex/MyModel.rdf#\"\n"
                           "   xmlns:myOMEX=\"http://MyOmexLibrary.org/MyOmex.omex/MyModel.xml\"\n"
                           "   xmlns:myOMEXlib=\"http://MyOmexLibrary.org/MyOmex.omex\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n"
                           "  <rdf:Description rdf:about=\"TestModel.sbml\">\n"
                           "    <dcterms:creator rdf:resource=\"http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#PersonalInfo0000\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://MyOmexLibrary.org/myomex.omex/mymodel.rdf#PersonalInfo0000\">\n"
                           "    <foaf:accountName rdf:resource=\"https://orcid.org/0000-1111-2222-3333\"/>\n"
                           "    <foaf:accountServiceHomepage rdf:resource=\"https://github.com/sys-bio/libOmexMeta\"/>\n"
                           "    <foaf:mbox rdf:datatype=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#string\">annotations.uw.edu</foaf:mbox>\n"
                           "    <foaf:name rdf:datatype=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#string\">Ciaran Welsh</foaf:name>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


















































