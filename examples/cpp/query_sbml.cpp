# include <semsim/SemSim.h>

# include "raptor2.h"
# include "rasqal.h"

# include <iostream>

using namespace semsim;

int main(int argc, char *argv[]) {
  if (argc < 2)
    throw std::runtime_error("Usage: query_sbml filename \"query\"");

  SBMLModel model = importSBMLFromFile(std::string(argv[1]));

  std::cerr << "**********************************************************\n";
  std::cerr << "RDF annotations\n";
  std::cerr << "**********************************************************\n\n";

  std::string rdf = model.getRDF("./mymodel.xml", "turtle");

  std::cerr << rdf << "\n";


  rasqal_world* my_rasqal_world = rasqal_new_world();
  rasqal_world_open(my_rasqal_world);
  raptor_world* my_raptor_world = rasqal_world_get_raptor(my_rasqal_world);

  raptor_iostream* my_raptor_iostr = raptor_new_iostream_from_string(my_raptor_world, (void*)rdf.c_str(), rdf.size());

  unsigned char* uri_string = raptor_uri_filename_to_uri_string("./mymodel.xml");
  raptor_uri* uri = raptor_new_uri(my_raptor_world, uri_string);
  raptor_uri* base_uri = raptor_uri_copy(uri);

  rasqal_data_graph* dg = rasqal_new_data_graph_from_iostream(
            my_rasqal_world,
            my_raptor_iostr,
            base_uri,
            NULL,
            RASQAL_DATA_GRAPH_BACKGROUND,
            NULL,
            (const char*)"turtle",
            NULL);

  rasqal_query *rq=rasqal_new_query(my_rasqal_world,(const char*)"sparql",NULL);
  const unsigned char* query_string=(const unsigned char*)argv[2];
  rasqal_query_prepare(rq,query_string,base_uri);
  rasqal_query_add_data_graph(rq, dg);
  rasqal_query_results* results=rasqal_query_execute(rq);

  std::cerr << "**********************************************************\n";
  if (rasqal_query_results_is_boolean(results)) {
    std::cerr << "Result: " << (rasqal_query_results_get_boolean(results) ? "True" : "False") << "\n";
  } else if (rasqal_query_results_is_bindings(results)) {
    while(!rasqal_query_results_finished(results)) {
      std::cerr << "Results (" << rasqal_query_results_get_count(results) << ")\n";
      for(int i=0;i<rasqal_query_results_get_bindings_count(results);i++) {
        const unsigned char *name = rasqal_query_results_get_binding_name(results,i);
        rasqal_literal *value = rasqal_query_results_get_binding_value(results,i);
        std::string strvalue = (const char*)rasqal_literal_as_string(value);
        std::cerr << "  " << name << " " << strvalue << "\n";
      }
      rasqal_query_results_next(results);
    }
  } else if (rasqal_query_results_is_graph(results)) {
    do {
      std::cerr << "triple\n";
      raptor_statement* s = rasqal_query_results_get_triple(results);
    } while (!rasqal_query_results_next_triple(results));
  } else {
    std::cerr << "Cannot display query results\n";
  }
  std::cerr << "**********************************************************\n";

  rasqal_free_query_results(results);
  rasqal_free_query(rq);

  raptor_free_uri(uri);
  raptor_free_uri(base_uri);

  rasqal_free_data_graph(dg);
  raptor_free_iostream(my_raptor_iostr);

  raptor_free_memory(uri_string);

  rasqal_free_world(my_rasqal_world);

  return 0;
}
