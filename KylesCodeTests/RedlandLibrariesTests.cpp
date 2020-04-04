//
// Created by Ciaran on 3/19/2020.
//

/*
 * This document serves two purposes: 1) test that raptor2 is configured correctly
 * and working as it should and 2) serve as a place to try out the redland RDF libraries.
 * Strictly speaking these tests are not exactly relevant to libsemsim.
 */


#include "gtest/gtest.h"

#include "raptor2.h"
//#include "librdf.h"
//#include "rasqal.h"
//#include "rdf_init.h"
#include "redland.h"

#include "semsim/Error.h"

class RDFExamples {
public:

    RDFExamples() = default;

    static const char *rdf_ntriples_example() {
        std::string triple = "<http://bigasterisk.com/foaf.rdf#drewp> <http://www.w3.org/1999/02/22-rdf-syntax-ns#type> <http://xmlns.com/foaf/0.1/Person> .\n"
                             "<http://bigasterisk.com/foaf.rdf#drewp> <http://example.com/says> \"Hello world\" .";
        return triple.c_str();
    }

    static const char *rdf_xml_example() {
        std::string xml = "<rdf:RDF \n"
                          "    xmlns=\"http://xmlns.com/foaf/0.1/\"\n"
                          "    xmlns:dc=\"http://purl.org/dc/terms/\"\n"
                          "    xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n"
                          "\n"
                          "    <Document rdf:about=\"http://www.w3.org/2001/sw/RDFCore/ntriples/\">\n"
                          "        <dc:title xml:lang=\"en-US\">N-Triples</dc:title>\n"
                          "        <maker>\n"
                          "            <Person rdf:nodeID=\"art\">\n"
                          "                <name>Art Barstow</name>\n"
                          "            </Person>\n"
                          "        </maker>\n"
                          "        <maker>\n"
                          "            <Person rdf:nodeID=\"dave\">\n"
                          "                <name>Dave Beckett</name>\n"
                          "            </Person>\n"
                          "        </maker>\n"
                          "    </Document>\n"
                          "</rdf:RDF>";
        return xml.c_str();
    }

    /*
     * This example taken from here: * https://www.w3.org/TR/rdf-syntax-grammar/#example7 should look like
     * this in rdf:
     * <http://www.w3.org/TR/rdf-syntax-grammar> <http://purl.org/dc/elements/1.1/title> "RDF/XML Syntax Specification (Revised)" .
     *  _:genid1 <http://example.org/stuff/1.0/fullName> "Dave Beckett" .
     *  _:genid1 <http://example.org/stuff/1.0/homePage> <http://purl.org/net/dajobe/> .
     *  <http://www.w3.org/TR/rdf-syntax-grammar> <http://example.org/stuff/1.0/editor> _:genid1 .
     */
    static const char *rdf_xml_example7() {

        std::string xml = "<?xml version=\"1.0\"?>\n"
                          "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                          "            xmlns:dc=\"http://purl.org/dc/elements/1.1/\"\n"
                          "            xmlns:ex=\"http://example.org/stuff/1.0/\">\n"
                          "\n"
                          "  <rdf:Description rdf:about=\"http://www.w3.org/TR/rdf-syntax-grammar\"\n"
                          "             dc:title=\"RDF1.1 XML Syntax\">\n"
                          "    <ex:editor>\n"
                          "      <rdf:Description ex:fullName=\"Dave Beckett\">\n"
                          "        <ex:homePage rdf:resource=\"http://purl.org/net/dajobe/\" />\n"
                          "      </rdf:Description>\n"
                          "    </ex:editor>\n"
                          "  </rdf:Description>\n"
                          "\n"
                          "</rdf:RDF>";
        return xml.c_str();
    }


};

TEST(RedlandTests, TestInitialiseAndTearDownRaptor) {
    // Initialise raptor
    raptor_world *world;
    world = raptor_new_world();

    // free memory used by raptor
    raptor_free_world(world);

    // if we get this far without error, test passes
    ASSERT_TRUE(true);
}


class RedlandTestFixture : public ::testing::Test {
public:
    librdf_world_s *world;
    librdf_storage *storage;
    librdf_parser *parser;
    librdf_model *model;
    librdf_stream *stream;
    librdf_node *subject, *predicate;
    librdf_iterator *iterator;
    librdf_statement *partial_statement, *statement;
    const char *input = RDFExamples::rdf_ntriples_example();
    librdf_uri *uri;
    char *parser_name = nullptr;
    int count;
    raptor_world *raptor_world_ptr;
    raptor_iostream *iostream;

    void SetUp() override {
        world = librdf_new_world();
        librdf_world_open(world);
        raptor_world_ptr = librdf_world_get_raptor(world);

        uri = librdf_new_uri(world, (const unsigned char *) "http://www.w3.org/1999/02/22-rdf-syntax-ns#");

        storage = librdf_new_storage(world, "memory", "test", nullptr);

        model = librdf_new_model(world, storage, nullptr);

        parser = librdf_new_parser(world, "rdfxml", nullptr, nullptr);
    }

    void TearDown() override {
        librdf_free_parser(parser);

        librdf_free_statement(statement);

        raptor_free_iostream(iostream);
    }

    static void print_triple(void *user_data, raptor_statement *triple) {
        raptor_statement_print_as_ntriples(triple, stdout);
        fputc('\n', stdout);
    }
};


TEST_F(RedlandTestFixture, TestReadRdfXmlFromFileAndPrintToStdOutWithRaptor) {
    raptor_world *world = nullptr;
    raptor_parser *rdf_parser = nullptr;
    unsigned char *uri_string;
    raptor_uri *uri, *base_uri;

    world = raptor_new_world();

    rdf_parser = raptor_new_parser(world, "rdfxml");

    raptor_parser_set_statement_handler(rdf_parser, nullptr, print_triple);

    uri_string = raptor_uri_filename_to_uri_string("/mnt/d/libsemsim/tests/rdfxml_example1.txt");
    uri = raptor_new_uri(world, uri_string);
    base_uri = raptor_uri_copy(uri);

    raptor_parser_parse_file(rdf_parser, uri, base_uri);

    // release memory
    raptor_free_parser(rdf_parser);
    raptor_free_uri(base_uri);
    raptor_free_uri(uri);
    raptor_free_memory(uri_string);
    raptor_free_world(world);
}

TEST_F(RedlandTestFixture, TestReadRdfXmlFromStringAndPrintToStdOutWithRaptor) {
    raptor_world *world = nullptr;
    raptor_parser *rdf_parser = nullptr;
    unsigned char *uri_string;
    raptor_uri *uri, *base_uri;

    world = raptor_new_world();

    rdf_parser = raptor_new_parser(world, "rdfxml");

    raptor_parser_set_statement_handler(rdf_parser, nullptr, print_triple);

    uri_string = raptor_uri_filename_to_uri_string("/mnt/d/libsemsim/tests/rdfxml_example1.txt");
    uri = raptor_new_uri(world, uri_string);
    base_uri = raptor_uri_copy(uri);

    raptor_parser_parse_file(rdf_parser, uri, base_uri);

    // release memory
    raptor_free_parser(rdf_parser);
    raptor_free_uri(base_uri);
    raptor_free_uri(uri);
    raptor_free_memory(uri_string);
    raptor_free_world(world);
}

//// test based on https://github.com/dajobe/librdf/blob/master/examples/example1.c
//TEST(RedlandTests, TestNTripleParser) {
//    librdf_world_s *world;
//    librdf_storage *storage;
//    librdf_parser *parser;
//    librdf_model *model;
//    librdf_stream *stream;
//    librdf_node *subject, *predicate;
//    librdf_iterator *iterator;
//    librdf_statement *partial_statement, *statement;
//    const char *input = RDFExamples::rdf_ntriples_example();
//    librdf_uri * uri;
//    char *parser_name = nullptr;
//    int count;
//    raptor_world *raptor_world_ptr;
//    raptor_iostream *iostream;
//
//    world = librdf_new_world();
//    librdf_world_open(world);
//    raptor_world_ptr = librdf_world_get_raptor(world);
//
//    uri = librdf_new_uri(world, (const unsigned char *) "http://www.w3.org/1999/02/22-rdf-syntax-ns#");
//
//    storage = librdf_new_storage(world, "memory", "test", nullptr);
//
//    model = librdf_new_model(world, storage, nullptr);
//
//    parser = librdf_new_parser(world, "rdfxml", nullptr, nullptr);
//
////    fprintf(stdout, "Parsing URI %s", librdf_uri_as_string(uri));
//    const unsigned char *uri_str = librdf_uri_as_string(uri);
//    std::cout << uri_str << std::endl;
//    librdf_free_parser(parser);
//
//    statement = librdf_new_statement_from_nodes(world,
//                                                librdf_new_node_from_uri_string(world,
//                                                                                (const unsigned char *) "http://www.dajobe.org/"),
//                                                librdf_new_node_from_uri_string(world,
//                                                                                (const unsigned char *) "http://purl.org/dc/elements/1.1/title"),
//                                                librdf_new_node_from_literal(world,
//                                                                             (const unsigned char *) "My home Page",
//                                                                             nullptr, 0)
//    );
//
//    librdf_model_add_statement(model, statement);
//
//    librdf_free_statement(statement);
//
//    iostream = raptor_new_iostream_to_file_handle(raptor_world_ptr, stdout);
//
//    void *str = nullptr;
//    size_t str_len;
//    /*
//     * search for raptor_iostream*
//     */
////    raptor_iostream_string_write(x, iostream);
////    std::cout << x << std::endl;
////    std::cout << *x << std::endl;
////    raptor_string_ntriples_write(s, sizeof(iostream), (const char*)" ", iostream)
//    raptor_iostream *iostr = nullptr;
//
//    raptor_new_iostream_to_string(raptor_world_ptr, &str, &str_len, nullptr);
//
//    std::cout << str << std::endl;
//
//
////    const char* actual = raptor_write_string_iostream_finish(iostream);
//    const char *expected = "<http://www.dajobe.org/> <http://purl.org/dc/elements/1.1/title> \"My home Page\".";
////    librdf_model_write(model, iostream);
//    raptor_free_iostream(iostream);
////    ASSERT_STREQ(expected, actual);
//}

TEST_F(RedlandTestFixture, TestX) {
    const unsigned char *uri_str = librdf_uri_as_string(uri);
    std::cout << uri_str << std::endl;

    statement = librdf_new_statement_from_nodes(world,
                                                librdf_new_node_from_uri_string(world,
                                                                                (const unsigned char *) "http://www.dajobe.org/"),
                                                librdf_new_node_from_uri_string(world,
                                                                                (const unsigned char *) "http://purl.org/dc/elements/1.1/title"),
                                                librdf_new_node_from_literal(world,
                                                                             (const unsigned char *) "My home Page",
                                                                             nullptr, 0)
    );
    librdf_model_add_statement(model, statement);

    unsigned char *s;
    int rc;

    iostream = raptor_new_iostream_to_string(raptor_world_ptr,
                                             (void **) &s, nullptr, malloc);

    rc = librdf_statement_write(statement, iostream);
    std::cout << "statement writed sucess: " << rc << std::endl;
    std::cout << "s" << s << std::endl;

//    write_to_string(raptor_world_ptr, )
}

TEST_F(RedlandTestFixture, Testy) {
/*
 * The typical sequence of operations to serialize is to create a serializer object,
 * set various callback and features, start the serializing, send some RDF triples to
 * the serializer object, finish the serializing and destroy the serializer object.
*/
    librdf_serializer *serializer;
    librdf_stream *stream;

    serializer = librdf_new_serializer(world, "rdfxml", NULL, NULL);

//    librdf_stream_write()

    raptor_uri *uri = raptor_new_uri(raptor_world_ptr, (const unsigned char *) "http://example.org/base");
    void *string;  /* destination for string */
    size_t length; /* length of constructed string */

    std::cout << string << std::endl;
    std::cout << length << std::endl;

//    raptor_new_iostream_from_string(raptor_world_ptr, string, nullptr);
//
//    raptor_serializer_start_to_string(rdf_serializer, uri,
//                                      &string, &length);
//
//    std::cout << string << std::endl;
//    std::cout << length << std::endl;
}

