# include "semsim/rdf/RDFReader.h"

# include "raptor2.h"
# include <iostream>

namespace semsim {
    static std::string RaptorURIToString(raptor_uri* u) {
      unsigned char* c = raptor_uri_to_string(u);
      std::string result((const char*)c);
      raptor_free_memory(c);
      return result;
    }

    static URI RaptorTermToURI(raptor_term* t) {
      if (!t)
        throw std::runtime_error("Raptor term is null");
      switch (t->type) {
        case RAPTOR_TERM_TYPE_URI:
          return URI(RaptorURIToString(t->value.uri));
        default:
          throw std::runtime_error("Raptor term is wrong type - not a URI");
      }
    }

    static void process_triple(void* user_data, raptor_statement* triple) {
      std::cerr << "triple " << RaptorTermToURI(triple->subject).toString() << "\n";
    }

    void applyRDFAnnotationsToModel(const Model& model, const std::string& rdf, const std::string& rdf_format) {
      raptor_world* world = raptor_new_world();
      raptor_parser* rdf_parser = raptor_new_parser(world, "rdfxml");
      raptor_parser_set_statement_handler(rdf_parser, NULL, process_triple);

      unsigned char* uri_string = raptor_uri_filename_to_uri_string(".");
      raptor_uri* uri = raptor_new_uri(world, uri_string);
      raptor_uri* base_uri = raptor_uri_copy(uri);

      raptor_parser_parse_start(rdf_parser, base_uri);
      raptor_parser_parse_chunk(rdf_parser, (const unsigned char*)rdf.c_str(), rdf.size(), 1);

      raptor_free_parser(rdf_parser);
      raptor_free_uri(base_uri);
      raptor_free_uri(uri);
      raptor_free_memory(uri_string);

      raptor_free_world(world);
    }
}
