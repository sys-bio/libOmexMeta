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
#include "Error.h"

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


TEST(RedlandTests, TestNTripleParser) {
    // collect ntriple into a stream obj
    raptor_iostream *stream;
//    stream << RDFExamples::rdf_ntriples_example() << std::endl;
//
    // Initialise raptor
    raptor_world *world;
    world = raptor_new_world();
//
//    raptor_parser* rdf_parser;
//    rdf_parser = raptor_new_parser(world, "ntriple");
//
//    if (rdf_parser == nullptr){
//        throw semsim::NullPointerException("rdf_parser is nullprt");
//    }
//
//    raptor_uri_s uri = "http://bigasterisk.com";
//    raptor_parser_parse_iostream(rdf_parser, ntriple_stream, );
//
//    // free memory used by raptor
    raptor_free_world(world);

}

TEST(RedlandTests, TestCodeFromGithub) {
    // example code here: https://stackoverflow.com/questions/48387060/using-raptor-rdf-parser-toolkit-to-generate-a-foaf-rdfxml-file/48490811#48490811
    raptor_world *world = NULL;
    raptor_serializer *rdf_serializer = NULL;
    unsigned char *uri_string;
    raptor_uri *base_uri;
    raptor_statement *triple;

    world = raptor_new_world();

//    uri_string = raptor_uri_filename_to_uri_string(argv[1]);
//    base_uri = raptor_new_uri(world, uri_string);
//
//    rdf_serializer = raptor_new_serializer(world, "rdfxml-abbrev");
//    raptor_serializer_start_to_file_handle(rdf_serializer, base_uri, stdout);
//
//    const unsigned char *foaf_prefix = (const unsigned char *) "foaf";
//    raptor_uri *foaf_uri = raptor_new_uri(world, (const unsigned char *) "http://xmlns.com/foaf/0.1/");
//    raptor_serializer_set_namespace(rdf_serializer, foaf_uri, foaf_prefix);
//
//    const unsigned char *rdf_prefix = (const unsigned char *) "rdf";
//    raptor_uri *rdf_uri = raptor_new_uri(world, (const unsigned char *) "http://www.w3.org/1999/02/22-rdf-syntax-ns#");
//    raptor_serializer_set_namespace(rdf_serializer, rdf_uri, rdf_prefix);
//
//    {
//        raptor_statement *triple = NULL;
//        triple = raptor_new_statement(world);
//
//        triple->subject = raptor_new_term_from_blank(world, (const unsigned char *) "b1");
//        triple->predicate = raptor_new_term_from_uri_string(world,
//                                                            (const unsigned char *) "http://xmlns.com/foaf/0.1/name");
//        triple->object = raptor_new_term_from_literal(world, (unsigned char *) "Jimmy Wales", NULL, NULL);
//
//        raptor_serializer_serialize_statement(rdf_serializer, triple);
//        raptor_free_statement(triple);
//    }
//
//    {
//        raptor_statement *triple = NULL;
//        triple = raptor_new_statement(world);
//
//        triple->subject = raptor_new_term_from_blank(world, (const unsigned char *) "b1");
//        triple->predicate = raptor_new_term_from_uri_string(world,
//                                                            (const unsigned char *) "http://xmlns.com/foaf/0.1/mbox");
//        triple->object = raptor_new_term_from_uri_string(world, (unsigned char *) "mailto:jwales@bomis.com");
//
//        raptor_serializer_serialize_statement(rdf_serializer, triple);
//        raptor_free_statement(triple);
//    }
//
//    {
//        raptor_statement *triple = NULL;
//        triple = raptor_new_statement(world);
//
//        triple->subject = raptor_new_term_from_blank(world, (const unsigned char *) "b1");
//        triple->predicate = raptor_new_term_from_uri_string(world,
//                                                            (const unsigned char *) "http://www.w3.org/1999/02/22-rdf-syntax-ns#type");
//        triple->object = raptor_new_term_from_uri_string(world, (unsigned char *) "http://xmlns.com/foaf/0.1/Person");
//
//        raptor_serializer_serialize_statement(rdf_serializer, triple);
//        raptor_free_statement(triple);
//    }
//
//    raptor_serializer_serialize_end(rdf_serializer);
//    raptor_free_serializer(rdf_serializer);
//    raptor_free_uri(base_uri);
//    raptor_free_memory(uri_string);
    raptor_free_world(world);
}



