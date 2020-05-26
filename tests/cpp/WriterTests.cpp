#include <semsim/Writer.h>

#include "AnnotationSamples.h"
#include "semsim/RedlandAPIWrapper/RedlandAPIWrapper.h"

#include "gtest/gtest.h"

using namespace semsim;

class WriterTests : public ::testing::Test {

public:
    AnnotationSamples samples;
    LibrdfStorage storage;
    LibrdfModel model;
    LibrdfStatement statement;

    WriterTests() {

        model = LibrdfModel(storage);

        statement = LibrdfStatement(
                std::move(LibrdfNode::fromUriString("http://www.dajobe.org/")),
                std::move(LibrdfNode::fromUriString("http://purl.org/dc/elements/1.1/title")),
                std::move(LibrdfNode::fromLiteral("My Home Page"))
        );
        model.addStatement(statement);
    };

    void test_writer(std::string output_format, const std::string &expected) const {
        semsim::Writer writer(model, "file://./semsim_model.xml", std::move(output_format));
        writer.registerNamespace("http://purl.org/dc/elements/1.1/", "dcterms");
        std::string actual = writer.toString();
        std::cout << actual << std::endl;
        ASSERT_STREQ(expected.c_str(), actual.c_str());
    }
};


TEST_F(WriterTests, TestDefaultConstructor) {
    semsim::Writer writer(model, "./semsim_model.xml", "rdfxml");
    ASSERT_TRUE(true); // test passes if it gets this far.
}

TEST_F(WriterTests, TestWriteModelToRdfXml) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:dcterms=\"http://purl.org/dc/elements/1.1/\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xml:base=\"file://./semsim_model.xml\">\n"
                           "  <rdf:Description rdf:about=\"http://www.dajobe.org/\">\n"
                           "    <dcterms:title rdf:datatype=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#string\">My Home Page</dcterms:title>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n";
    test_writer("rdfxml", expected);
}

TEST_F(WriterTests, TestWriteModelTontriples) {
    std::string expected = "<http://www.dajobe.org/> <http://purl.org/dc/elements/1.1/title> \"My Home Page\"^^<http://www.w3.org/1999/02/22-rdf-syntax-ns#string> .\n";
    test_writer("ntriples", expected);
}

TEST_F(WriterTests, TestWriteModelToturtle) {
    std::string expected = "@base <file://./semsim_model.xml> .\n"
                           "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix dcterms: <http://purl.org/dc/elements/1.1/> .\n"
                           "\n"
                           "<http://www.dajobe.org/>\n"
                           "    dcterms:title \"My Home Page\"^^rdf:string .\n\n";
    test_writer("turtle", expected);
}


TEST_F(WriterTests, TestWriteModelToRdfxmlXmp) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<?xpacket begin='\uFEFF' id='W5M0MpCehiHzreSzNTczkc9d'?>\n"
                           "<x:xmpmeta xmlns:x='adobe:ns:meta/'>\n"
                           "<rdf:RDF xmlns:dcterms=\"http://purl.org/dc/elements/1.1/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xml:base=\"file://./semsim_model.xml\">\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <dcterms:title rdf:datatype=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#string\">My Home Page</dcterms:title>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "</x:xmpmeta>\n"
                           "<?xpacket end='r'?>\n"
                           "";
    test_writer("rdfxml-xmp", expected);
}


TEST_F(WriterTests, Testrdfxmlabbrev) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:dcterms=\"http://purl.org/dc/elements/1.1/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xml:base=\"file://./semsim_model.xml\">\n"
                           "  <rdf:Description rdf:about=\"http://www.dajobe.org/\">\n"
                           "    <dcterms:title rdf:datatype=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#string\">My Home Page</dcterms:title>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    test_writer("rdfxml-abbrev", expected);
}

TEST_F(WriterTests, Testrdfxml) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:dcterms=\"http://purl.org/dc/elements/1.1/\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xml:base=\"file://./semsim_model.xml\">\n"
                           "  <rdf:Description rdf:about=\"http://www.dajobe.org/\">\n"
                           "    <dcterms:title rdf:datatype=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#string\">My Home Page</dcterms:title>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    test_writer("rdfxml", expected);
}

TEST_F(WriterTests, Testdot) {
    std::string expected = "digraph {\n"
                           "\trankdir = LR;\n"
                           "\tcharset=\"utf-8\";\n"
                           "\n"
                           "\t\"Rhttp://www.dajobe.org/\" -> \"LMy Home Page|Datatype: http://www.w3.org/1999/02/22-rdf-syntax-ns#string\" [ label=\"dcterms:title\" ];\n"
                           "\n"
                           "\t// Resources\n"
                           "\t\"Rhttp://www.dajobe.org/\" [ label=\"http://www.dajobe.org/\", shape = ellipse, color = blue ];\n"
                           "\n"
                           "\t// Anonymous nodes\n"
                           "\n"
                           "\t// Literals\n"
                           "\t\"LMy Home Page|Datatype: http://www.w3.org/1999/02/22-rdf-syntax-ns#string\" [ label=\"My Home Page|Datatype: http://www.w3.org/1999/02/22-rdf-syntax-ns#string\", shape = record ];\n"
                           "\n"
                           "\tlabel=\"\\n\\nModel:\\nfile://./semsim_model.xml\\n\\nNamespaces:\\ndcterms: http://purl.org/dc/elements/1.1/\\n\";\n"
                           "}\n"
                           "";
    test_writer("dot", expected);
}

TEST_F(WriterTests, TestJsonTriples) {
    std::string expected = "{\n"
                           "  \"triples\" : [\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"http://www.dajobe.org/\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://purl.org/dc/elements/1.1/title\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"My Home Page\",\n"
                           "        \"datatype\" : \"http://www.w3.org/1999/02/22-rdf-syntax-ns#string\",\n"
                           "        \"type\" : \"literal\"\n"
                           "        }\n"
                           "      \n"
                           "      }\n"
                           "    ]\n"
                           "  }\n"
                           "";
    test_writer("json-triples", expected);
}

TEST_F(WriterTests, Testjson) {
    std::string expected = "\n"
                           "{\n"
                           "  \"http://www.dajobe.org/\" : {\n"
                           "    \"http://purl.org/dc/elements/1.1/title\" : [ {\n"
                           "        \"value\" : \"My Home Page\",\n"
                           "        \"datatype\" : \"http://www.w3.org/1999/02/22-rdf-syntax-ns#string\",\n"
                           "        \"type\" : \"literal\"\n"
                           "        }\n"
                           "      \n"
                           "      ]\n"
                           "    }\n"
                           "  }\n"
                           "";
    test_writer("json", expected);
}

TEST_F(WriterTests, Testhtml) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1//EN\"\n"
                           "        \"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd\">\n"
                           "<html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
                           "<head>\n"
                           "  <title>Raptor Graph Serialisation</title>\n"
                           "</head>\n"
                           "<body>\n"
                           "  <table id=\"triples\" border=\"1\">\n"
                           "    <tr>\n"
                           "      <th>Subject</th>\n"
                           "      <th>Predicate</th>\n"
                           "      <th>Object</th>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"http://www.dajobe.org/\">http://www.dajobe.org/</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://purl.org/dc/elements/1.1/title\">http://purl.org/dc/elements/1.1/title</a></span></td>\n"
                           "      <td><span class=\"literal\"><span class=\"value\">My Home Page</span>^^&lt;<span class=\"datatype\">http://www.w3.org/1999/02/22-rdf-syntax-ns#string</span>&gt;</span></td>\n"
                           "    </tr>\n"
                           "  </table>\n"
                           "  <p>Total number of triples: <span class=\"count\">1</span>.</p>\n"
                           "</body>\n"
                           "</html>\n"
                           "";
    test_writer("html", expected);
}

TEST_F(WriterTests, Testnquads) {
    std::string expected = "<http://www.dajobe.org/> <http://purl.org/dc/elements/1.1/title> \"My Home Page\"^^<http://www.w3.org/1999/02/22-rdf-syntax-ns#string> .\n";
    test_writer("nquads", expected);
}

//
//TEST_F(WriterTests, WriterTestFromTriple) {
//semsim::Subject subject = semsim::Subject(semsim::RDFURINode("Soooobject"));
//semsim::Resource resource = semsim::Resource(semsim::RDFURINode("resource/identifier"));
//semsim::BiomodelsBiologyQualifier predicate = semsim::BiomodelsBiologyQualifier("is");
//semsim::PredicatePtr predicatePtr = std::make_shared<semsim::Predicate>(predicate);
//
//semsim::Triple triple(subject, predicatePtr, resource);
//
//semsim::TripleWriter tripleWriter(triple);
//std::cout << tripleWriter.
//
//toString()
//
//<<
//std::endl;
//std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
//                       "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
//                       "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
//                       "   xml:base=\"file://annotation.rdf\">\n"
//                       "  <rdf:Description rdf:about=\"Soooobject\">\n"
//                       "    <bqbiol:is rdf:resource=\"https://identifiers.org/resource/identifier\"/>\n"
//                       "  </rdf:Description>\n"
//                       "</rdf:RDF>\n";
//std::string actual = tripleWriter.toString();
//ASSERT_STREQ(expected
//.
//
//c_str(), actual
//
//.
//
//c_str()
//
//);
//}
//
//TEST_F(WriterTests, WriterTestFromTriples) {
//semsim::Subject subject = semsim::Subject(semsim::RDFURINode("Soooobject"));
//semsim::Resource resource = semsim::Resource(semsim::RDFURINode("resource/identifier"));
//semsim::BiomodelsBiologyQualifier predicate = semsim::BiomodelsBiologyQualifier("is");
//semsim::BiomodelsBiologyQualifier predicate2 = semsim::BiomodelsBiologyQualifier("isPartOf");
//semsim::PredicatePtr predicatePtr = std::make_shared<semsim::Predicate>(predicate);
//semsim::PredicatePtr predicatePtr2 = std::make_shared<semsim::Predicate>(predicate2);
//
//semsim::Triple triple1(subject, predicatePtr, resource);
//semsim::Triple triple2(subject, predicatePtr2, resource);
//semsim::Triples triples({triple1, triple2});
//
//semsim::TripleWriter tripleWriter(triples);
//std::cout << tripleWriter.
//
//toString()
//
//<<
//std::endl;
//std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
//                       "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
//                       "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
//                       "   xml:base=\"file://annotation.rdf\">\n"
//                       "  <rdf:Description rdf:about=\"Soooobject\">\n"
//                       "    <bqbiol:is rdf:resource=\"https://identifiers.org/resource/identifier\"/>\n"
//                       "    <bqbiol:isPartOf rdf:resource=\"https://identifiers.org/resource/identifier\"/>\n"
//                       "  </rdf:Description>\n"
//                       "</rdf:RDF>\n"
//                       "";
//std::string actual = tripleWriter.toString();
//ASSERT_STREQ(expected
//.
//
//c_str(), actual
//
//.
//
//c_str()
//
//);
//}
//
//
//

















