//
// Created by Ciaran on 11/07/2020.
//

#include "omexmeta/PersonalInformation.h"
#include "omexmeta/RDF.h"
#include "redland/RedlandAPI.h"
#include "gtest/gtest.h"

using namespace omexmeta;

class PersonalInformationTests : public ::testing::Test {
public:
    redland::LibrdfStorage storage;
    redland::LibrdfModel model;

    UriHandler uriHandler;

    PersonalInformationTests() {
        model = redland::LibrdfModel(storage.get());
    }

    ~PersonalInformationTests() override {
        model.freeModel();
        storage.freeStorage();
    }
};

TEST_F(PersonalInformationTests, TestAddFoaf) {
    uriHandler.setModel("TestModel.sbml");
    PersonalInformation information(model.get(), uriHandler);
    LibrdfNode value = LibrdfNode::fromLiteral("Joe Blogs");
    information.addFoaf("name", value);
    Triples triples = information.getTriples();
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix dc: <https://dublincore.org/specifications/dublin-core/dcmi-terms/> .\n"
                           "@prefix foaf: <http://xmlns.com/foaf/0.1/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/TestModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/TestModel.sbml>\n"
                           "    dc:creator <http://omex-library.org/NewOmex.omex/TestModel.sbml#PersonalInfo0000> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/TestModel.sbml#PersonalInfo0000>\n"
                           "    foaf:name \"Joe Blogs\"^^rdf:string .\n";
    ASSERT_TRUE(RDF::equals(triples, expected));

    triples.freeTriples();
}

TEST_F(PersonalInformationTests, TestAddFoafUsingLiteral) {
    uriHandler.setModel("TestModel.sbml");
    PersonalInformation information(model.get(), uriHandler);
    information.addFoafLiteral("name", "Ciaran Welsh");
    Triples triples = information.getTriples();
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix dc: <https://dublincore.org/specifications/dublin-core/dcmi-terms/> .\n"
                           "@prefix foaf: <http://xmlns.com/foaf/0.1/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/TestModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/TestModel.sbml>\n"
                           "    dc:creator <http://omex-library.org/NewOmex.omex/TestModel.sbml#PersonalInfo0000> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/TestModel.sbml#PersonalInfo0000>\n"
                           "    foaf:name \"Ciaran Welsh\"^^rdf:string .";
    ASSERT_TRUE(RDF::equals(triples, expected, "turtle"));
    triples.freeTriples();
}


TEST_F(PersonalInformationTests, TestAddFoafUsingUri) {
    uriHandler.setModel("TestModel.sbml");
    ASSERT_STREQ(uriHandler.getModel().c_str(), "http://omex-library.org/NewOmex.omex/TestModel.sbml");
    ASSERT_STREQ(uriHandler.getLocal().c_str(), "http://omex-library.org/NewOmex.omex/TestModel.rdf#");
    PersonalInformation information(model.get(), uriHandler);
    information.addFoafUri("accountName", "https://orcid.org/0000-0001-8254-4957");
    Triples triples = information.getTriples();
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix dc: <https://dublincore.org/specifications/dublin-core/dcmi-terms/> .\n"
                           "@prefix foaf: <http://xmlns.com/foaf/0.1/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/TestModel.sbml>\n"
                           "    dc:creator <http://omex-library.org/NewOmex.omex/TestModel.sbml#PersonalInfo0000> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/TestModel.sbml#PersonalInfo0000>\n"
                           "    foaf:accountName <https://orcid.org/0000-0001-8254-4957> .";
    ASSERT_TRUE(RDF::equals(triples, expected, "turtle"));
    triples.freeTriples();
}
TEST_F(PersonalInformationTests, TestAddName) {
    uriHandler.setModel("TestModel.sbml");
    PersonalInformation information(model.get(), uriHandler);
    information.addName("Ciaran Welsh");
    Triples triples = information.getTriples();

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix dc: <https://dublincore.org/specifications/dublin-core/dcmi-terms/> .\n"
                           "@prefix foaf: <http://xmlns.com/foaf/0.1/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/TestModel.sbml>\n"
                           "    dc:creator <http://omex-library.org/NewOmex.omex/TestModel.sbml#PersonalInfo0000> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/TestModel.sbml#PersonalInfo0000>\n"
                           "    foaf:name \"Ciaran Welsh\"^^rdf:string .";
    ASSERT_TRUE(RDF::equals(triples, expected, "turtle"));
    triples.freeTriples();
}

TEST_F(PersonalInformationTests, TestMBox) {
    uriHandler.setModel("TestModel.sbml");
    PersonalInformation information(model.get(), uriHandler);
    information.addMbox("annotations@uw.edu");
    Triples triples = information.getTriples();

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix dc: <https://dublincore.org/specifications/dublin-core/dcmi-terms/> .\n"
                           "@prefix foaf: <http://xmlns.com/foaf/0.1/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/TestModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/TestModel.sbml>\n"
                           "    dc:creator <http://omex-library.org/NewOmex.omex/TestModel.sbml#PersonalInfo0000> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/TestModel.sbml#PersonalInfo0000>\n"
                           "    foaf:mbox \"annotations@uw.edu\"^^rdf:string .";
    ASSERT_TRUE(RDF::equals(triples, expected, "turtle"));
    triples.freeTriples();
}

TEST_F(PersonalInformationTests, TestAccountName) {
    uriHandler.setModel("TestModel.sbml");
    PersonalInformation information(model.get(), uriHandler);
    information.addAccountName("0000-0001-9876-3928");
    Triples triples = information.getTriples();

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix dc: <https://dublincore.org/specifications/dublin-core/dcmi-terms/> .\n"
                           "@prefix foaf: <http://xmlns.com/foaf/0.1/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/TestModel.sbml>\n"
                           "    dc:creator <http://omex-library.org/NewOmex.omex/TestModel.sbml#PersonalInfo0000> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/TestModel.sbml#PersonalInfo0000>\n"
                           "    foaf:accountName <https://orcid.org/0000-0001-9876-3928> .\n";
    ASSERT_TRUE(RDF::equals(triples, expected, "turtle"));
    triples.freeTriples();
}

TEST_F(PersonalInformationTests, TestaddAccountServiceHomepage) {
    uriHandler.setModel("TestModel.sbml");
    PersonalInformation information(model.get(), uriHandler);
    information.addAccountServiceHomepage("https://github.com/sys-bio/libOmexMeta");
    Triples triples = information.getTriples();

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix dc: <https://dublincore.org/specifications/dublin-core/dcmi-terms/> .\n"
                           "@prefix foaf: <http://xmlns.com/foaf/0.1/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/TestModel.sbml>\n"
                           "    dc:creator <http://omex-library.org/NewOmex.omex/TestModel.sbml#PersonalInfo0000> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/TestModel.sbml#PersonalInfo0000>\n"
                           "    foaf:accountServiceHomepage <https://github.com/sys-bio/libOmexMeta> .";
    ASSERT_TRUE(RDF::equals(triples, expected, "turtle"));
    triples.freeTriples();
}

TEST_F(PersonalInformationTests, TestMultipleEntries) {
    uriHandler.setModel("TestModel.sbml");
    PersonalInformation information(model.get(), uriHandler);
    information.addName("Ciaran Welsh")
            .addAccountName("0000-1111-2222-3333")
            .addAccountServiceHomepage("https://github.com/sys-bio/libOmexMeta")
            .addMbox("annotations.uw.edu");

    Triples triples = information.getTriples();

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix dc: <https://dublincore.org/specifications/dublin-core/dcmi-terms/> .\n"
                           "@prefix foaf: <http://xmlns.com/foaf/0.1/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/TestModel.sbml>\n"
                           "    dc:creator <http://omex-library.org/NewOmex.omex/TestModel.sbml#PersonalInfo0000> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/TestModel.sbml#PersonalInfo0000>\n"
                           "    foaf:accountName <https://orcid.org/0000-1111-2222-3333> ;\n"
                           "    foaf:accountServiceHomepage <https://github.com/sys-bio/libOmexMeta> ;\n"
                           "    foaf:mbox \"annotations.uw.edu\"^^rdf:string ;\n"
                           "    foaf:name \"Ciaran Welsh\"^^rdf:string .";
    ASSERT_TRUE(RDF::equals(triples, expected, "turtle"));
    triples.freeTriples();
}
