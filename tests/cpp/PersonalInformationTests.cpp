//
// Created by Ciaran on 11/07/2020.
//

#include "gtest/gtest.h"
#include "RedlandWrapper.h"
#include "omexmeta/PersonalInformation.h"

using namespace omexmeta;

class PersonalInformationTests : public ::testing::Test {
public:

    redland::LibrdfStorage storage;
    redland::LibrdfModel model;

    std::string local_uri = "http://omex-library.org/NewOmex.omex/NewModel.rdf#";

    PersonalInformationTests() {
        model = redland::LibrdfModel(storage.get());
    }

    ~PersonalInformationTests() override {
        model.freeModel();
        storage.freeStorage();
    }
};

TEST_F(PersonalInformationTests, TestAddFoaf){
    PersonalInformation information(model.get(), "TestModel.sbml", local_uri);
    LibrdfNode value = LibrdfNode::fromLiteral("Ciaran Welsh");
    information.addFoaf("name", value);
    Triples triples = information.getTriples();
    std::string actual = triples.str("turtle");
    std::cout << actual << std::endl;
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix dcterms: <http://purl.org/dc/terms/> .\n"
                           "@prefix foaf: <http://xmlns.com/foaf/0.1/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<TestModel.sbml>\n"
                           "    dcterms:creator <TestModel.sbml#PersonalInfo0000> .\n"
                           "\n"
                           "<TestModel.sbml#PersonalInfo0000>\n"
                           "    foaf:name \"Ciaran Welsh\"^^rdf:string .\n\n";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    triples.freeTriples();
}

TEST_F(PersonalInformationTests, TestAddFoafUsingLiteral) {
    PersonalInformation information(model.get(), "TestModel.sbml", local_uri);
    information.addFoafLiteral("name", "Ciaran Welsh");
    Triples triples = information.getTriples();
    std::string actual = triples.str("turtle");
    std::cout << actual << std::endl;
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix dcterms: <http://purl.org/dc/terms/> .\n"
                           "@prefix foaf: <http://xmlns.com/foaf/0.1/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<TestModel.sbml>\n"
                           "    dcterms:creator <TestModel.sbml#PersonalInfo0000> .\n"
                           "\n"
                           "<TestModel.sbml#PersonalInfo0000>\n"
                           "    foaf:name \"Ciaran Welsh\"^^rdf:string .\n"
                           "\n";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    triples.freeTriples();
}


TEST_F(PersonalInformationTests, TestAddFoafUsingUri) {
    PersonalInformation information(model.get(), "TestModel.sbml", local_uri);
    information.addFoafUri("accountName", "https://orcid.org/0000-0001-8254-4957");
    Triples triples = information.getTriples();
    std::string actual = triples.str("turtle");
    std::cout << actual << std::endl;
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix dcterms: <http://purl.org/dc/terms/> .\n"
                           "@prefix foaf: <http://xmlns.com/foaf/0.1/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<TestModel.sbml>\n"
                           "    dcterms:creator <TestModel.sbml#PersonalInfo0000> .\n"
                           "\n"
                           "<TestModel.sbml#PersonalInfo0000>\n"
                           "    foaf:accountName <https://orcid.org/0000-0001-8254-4957> .\n"
                           "\n";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    triples.freeTriples();
}

TEST_F(PersonalInformationTests, TestAddName) {
    PersonalInformation information(model.get(), "TestModel.sbml", local_uri);
    information.addName("Ciaran Welsh");
    Triples triples = information.getTriples();
    std::string actual = triples.str("turtle");
    std::cout << actual << std::endl;
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix dcterms: <http://purl.org/dc/terms/> .\n"
                           "@prefix foaf: <http://xmlns.com/foaf/0.1/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<TestModel.sbml>\n"
                           "    dcterms:creator <TestModel.sbml#PersonalInfo0000> .\n"
                           "\n"
                           "<TestModel.sbml#PersonalInfo0000>\n"
                           "    foaf:name \"Ciaran Welsh\"^^rdf:string .\n"
                           "\n";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    triples.freeTriples();
}

TEST_F(PersonalInformationTests, TestMBox) {
    PersonalInformation information(model.get(), "TestModel.sbml", local_uri);
    information.addMbox("annotations@uw.edu");
    Triples triples = information.getTriples();
    std::string actual = triples.str("turtle");
    std::cout << actual << std::endl;
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix dcterms: <http://purl.org/dc/terms/> .\n"
                           "@prefix foaf: <http://xmlns.com/foaf/0.1/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<TestModel.sbml>\n"
                           "    dcterms:creator <TestModel.sbml#PersonalInfo0000> .\n"
                           "\n"
                           "<TestModel.sbml#PersonalInfo0000>\n"
                           "    foaf:mbox \"annotations@uw.edu\"^^rdf:string .\n"
                           "\n";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    triples.freeTriples();
}

TEST_F(PersonalInformationTests, TestAccountName) {
    PersonalInformation information(model.get(), "TestModel.sbml", local_uri);
    information.addAccountName("0000-0001-9876-3928");
    Triples triples = information.getTriples();
    std::string actual = triples.str("turtle");
    std::cout << actual << std::endl;
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix dcterms: <http://purl.org/dc/terms/> .\n"
                           "@prefix foaf: <http://xmlns.com/foaf/0.1/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<TestModel.sbml>\n"
                           "    dcterms:creator <TestModel.sbml#PersonalInfo0000> .\n"
                           "\n"
                           "<TestModel.sbml#PersonalInfo0000>\n"
                           "    foaf:accountName <https://orcid.org/0000-0001-9876-3928> .\n"
                           "\n";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    triples.freeTriples();
}

TEST_F(PersonalInformationTests, TestaddAccountServiceHomepage) {
    PersonalInformation information(model.get(), "TestModel.sbml", local_uri);
    information.addAccountServiceHomepage("https://github.com/sys-bio/libOmexMeta");
    Triples triples = information.getTriples();
    std::string actual = triples.str("turtle");
    std::cout << actual << std::endl;
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix dcterms: <http://purl.org/dc/terms/> .\n"
                           "@prefix foaf: <http://xmlns.com/foaf/0.1/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<TestModel.sbml>\n"
                           "    dcterms:creator <TestModel.sbml#PersonalInfo0000> .\n"
                           "\n"
                           "<TestModel.sbml#PersonalInfo0000>\n"
                           "    foaf:accountServiceHomepage <https://github.com/sys-bio/libOmexMeta> .\n"
                           "\n";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    triples.freeTriples();
}

TEST_F(PersonalInformationTests, TestMultipleEntries) {
    PersonalInformation information(model.get(), "TestModel.sbml", local_uri);
    information.addName("Ciaran Welsh")
        .addAccountName("0000-1111-2222-3333")
        .addAccountServiceHomepage("https://github.com/sys-bio/libOmexMeta")
        .addMbox("annotations.uw.edu");

    Triples triples = information.getTriples();
    std::string actual = triples.str("turtle");
    std::cout << actual << std::endl;
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix dcterms: <http://purl.org/dc/terms/> .\n"
                           "@prefix foaf: <http://xmlns.com/foaf/0.1/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<TestModel.sbml>\n"
                           "    dcterms:creator <TestModel.sbml#PersonalInfo0000> .\n"
                           "\n"
                           "<TestModel.sbml#PersonalInfo0000>\n"
                           "    foaf:accountName <https://orcid.org/0000-1111-2222-3333> ;\n"
                           "    foaf:accountServiceHomepage <https://github.com/sys-bio/libOmexMeta> ;\n"
                           "    foaf:mbox \"annotations.uw.edu\"^^rdf:string ;\n"
                           "    foaf:name \"Ciaran Welsh\"^^rdf:string .\n"
                           "\n";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    triples.freeTriples();
}


















































