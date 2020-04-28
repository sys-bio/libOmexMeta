//
// Created by Ciaran on 4/9/2020.
//

//
// Created by Ciaran on 4/8/2020.
//


#include <semsim/Writer.h>

#include <utility>
#include "gtest/gtest.h"
#include "semsim/RDF.h"
#include "semsim/SemSim.h"
#include "AnnotationSamples.h"

class WriterTests : public ::testing::Test {

public:
    AnnotationSamples samples;
    librdf_world *world;
    raptor_world *raptor_world_ptr;
    librdf_storage *storage;
    librdf_model *model;
    librdf_statement *statement;


    WriterTests() {
        world = librdf_new_world();
        librdf_world_open(world);
        raptor_world_ptr = librdf_world_get_raptor(world);
        storage = librdf_new_storage(world, "memory", "semsim_store", nullptr);
        if (!storage) {
            throw std::invalid_argument("Failed to create new storage\n");
        }
        model = librdf_new_model(world, storage, nullptr);
        if (!model) {
            throw std::invalid_argument("Failed to create model\n");
        }
        statement = librdf_new_statement_from_nodes(
                world,
                librdf_new_node_from_uri_string(world, (const unsigned char *) "http://www.dajobe.org/"),
                librdf_new_node_from_uri_string(world, (const unsigned char *) "http://purl.org/dc/elements/1.1/title"),
                librdf_new_node_from_literal(world, (const unsigned char *) "My Home Page", nullptr, 0)
        );
        librdf_model_add_statement(model, statement);
    };

    void test_writer(std::string output_format, const std::string& expected) {
        semsim::Writer writer(world, model, "file://./semsim_model.xml" , std::move(output_format));
        writer.registerNamespace("http://purl.org/dc/elements/1.1/", "dcterms");
        std::string actual = writer.toString();
        std::cout << actual << std::endl;
        ASSERT_STREQ(expected.c_str(), actual.c_str());
    }
};


TEST_F(WriterTests, TestDefaultConstructor) {
    semsim::Writer writer(world, model, "./semsim_model.xml", "rdfxml");
    ASSERT_TRUE(true); // test passes if it gets this far.
}

TEST_F(WriterTests, TestWriteModelToRdfXml) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:dcterms=\"http://purl.org/dc/elements/1.1/\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xml:base=\"file://./semsim_model.xml\">\n"
                           "  <rdf:Description rdf:about=\"http://www.dajobe.org/\">\n"
                           "    <dcterms:title>My Home Page</dcterms:title>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n";
    test_writer("rdfxml", expected);
}

TEST_F(WriterTests, TestWriteModelTontriples) {
    std::string expected = "<http://www.dajobe.org/> <http://purl.org/dc/elements/1.1/title> \"My Home Page\" .\n";
    test_writer("ntriples", expected);
}
//todo test output format validator

TEST_F(WriterTests, TestWriteModelToturtle) {
    std::string expected = "@base <file://./semsim_model.xml> .\n"
                           "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix dcterms: <http://purl.org/dc/elements/1.1/> .\n"
                           "\n"
                           "<http://www.dajobe.org/>\n"
                           "    dcterms:title \"My Home Page\" .\n\n";
    test_writer("turtle", expected);
}

TEST_F(WriterTests, TestWriteModelTotrig3) {
    auto x0 = librdf_serializer_get_description(world, 0);
    auto x1 = librdf_serializer_get_description(world, 1);
    auto x2 = librdf_serializer_get_description(world, 2);
    auto x3 = librdf_serializer_get_description(world, 3);
    auto x4 = librdf_serializer_get_description(world, 4);
    auto x5 = librdf_serializer_get_description(world, 5);
    auto x6 = librdf_serializer_get_description(world, 6);
    auto x7 = librdf_serializer_get_description(world, 7);
    auto x8 = librdf_serializer_get_description(world, 8);
    auto x9 = librdf_serializer_get_description(world, 9);
    auto x10 = librdf_serializer_get_description(world, 10);
    auto x11 = librdf_serializer_get_description(world, 11);
    std::cout << *x0->names << std::endl;
    std::cout << *x1->names << std::endl;
    std::cout << *x2->names << std::endl;
    std::cout << *x3->names << std::endl;
    std::cout << *x4->names << std::endl;
    std::cout << *x5->names << std::endl;
    std::cout << *x6->names << std::endl;
    std::cout << *x7->names << std::endl;
    std::cout << *x8->names << std::endl;
    std::cout << *x9->names << std::endl;
    std::cout << *x10->names << std::endl;
    std::cout << *x11->names << std::endl;
}


TEST_F(WriterTests, TestWriteModelToRdfxmlXmp) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<?xpacket begin='\uFEFF' id='W5M0MpCehiHzreSzNTczkc9d'?>\n"
                           "<x:xmpmeta xmlns:x='adobe:ns:meta/'>\n"
                           "<rdf:RDF xmlns:dcterms=\"http://purl.org/dc/elements/1.1/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xml:base=\"file://./semsim_model.xml\">\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <dcterms:title>My Home Page</dcterms:title>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "</x:xmpmeta>\n"
                           "<?xpacket end='r'?>\n"
                           "";
    test_writer("rdfxml-xmp", expected);
}


TEST_F(WriterTests, Testrdfxmlabbrev){
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:dcterms=\"http://purl.org/dc/elements/1.1/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xml:base=\"file://./semsim_model.xml\">\n"
                           "  <rdf:Description rdf:about=\"http://www.dajobe.org/\">\n"
                           "    <dcterms:title>My Home Page</dcterms:title>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    test_writer("rdfxml-abbrev", expected);
}
TEST_F(WriterTests, Testrdfxml){
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:dcterms=\"http://purl.org/dc/elements/1.1/\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xml:base=\"file://./semsim_model.xml\">\n"
                           "  <rdf:Description rdf:about=\"http://www.dajobe.org/\">\n"
                           "    <dcterms:title>My Home Page</dcterms:title>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    test_writer("rdfxml", expected);
}

TEST_F(WriterTests, Testdot){
    std::string expected = "digraph {\n"
                           "\trankdir = LR;\n"
                           "\tcharset=\"utf-8\";\n"
                           "\n"
                           "\t\"Rhttp://www.dajobe.org/\" -> \"LMy Home Page\" [ label=\"dcterms:title\" ];\n"
                           "\n"
                           "\t// Resources\n"
                           "\t\"Rhttp://www.dajobe.org/\" [ label=\"http://www.dajobe.org/\", shape = ellipse, color = blue ];\n"
                           "\n"
                           "\t// Anonymous nodes\n"
                           "\n"
                           "\t// Literals\n"
                           "\t\"LMy Home Page\" [ label=\"My Home Page\", shape = record ];\n"
                           "\n"
                           "\tlabel=\"\\n\\nModel:\\nfile://./semsim_model.xml\\n\\nNamespaces:\\ndcterms: http://purl.org/dc/elements/1.1/\\n\";\n"
                           "}\n"
                           "";
    test_writer("dot", expected);
}
TEST_F(WriterTests, TestJsonTriples){
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
                           "        \"type\" : \"literal\"\n"
                           "        }\n"
                           "      \n"
                           "      }\n"
                           "    ]\n"
                           "  }\n";
    test_writer("json-triples", expected);
}
TEST_F(WriterTests, Testjson){
    std::string expected = "\n{\n"
                           "  \"http://www.dajobe.org/\" : {\n"
                           "    \"http://purl.org/dc/elements/1.1/title\" : [ {\n"
                           "        \"value\" : \"My Home Page\",\n"
                           "        \"type\" : \"literal\"\n"
                           "        }\n"
                           "      \n"
                           "      ]\n"
                           "    }\n"
                           "  }\n";
    test_writer("json", expected);
}
TEST_F(WriterTests, Testhtml){
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
                           "      <td><span class=\"literal\"><span class=\"value\">My Home Page</span></span></td>\n"
                           "    </tr>\n"
                           "  </table>\n"
                           "  <p>Total number of triples: <span class=\"count\">1</span>.</p>\n"
                           "</body>\n"
                           "</html>\n";
    test_writer("html", expected);
}
TEST_F(WriterTests, Testnquads){
    std::string expected = "<http://www.dajobe.org/> <http://purl.org/dc/elements/1.1/title> \"My Home Page\" .\n";
    test_writer("nquads", expected);
}




