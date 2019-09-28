# include <semsim/SemSim.h>

# include "raptor2.h"
# include "rasqal.h"

# include <iostream>

using namespace semsim;

int main(int argc, char *argv[]) {
  if (argc < 3)
    throw std::runtime_error("Usage: query_sbml_tiered filename \"query\"");

  SBMLModel model = importSBMLFromFile(std::string(argv[1]));

  std::cerr << "**********************************************************\n";
  std::cerr << "RDF annotations\n";
  std::cerr << "**********************************************************\n\n";

  std::string rdf = model.getRDF("./mymodel.xml", "turtle");

  std::cerr << rdf << "\n";

  std::cerr << "**********************************************************\n";
  RasqalQuery query1(rdf);
  RasqalQueryResult query_result1=query1.run(argv[2]);
  std::cerr << query_result1.toString();
  std::cerr << "**********************************************************\n";

  std::cerr << "**********************************************************\n";
  RasqalQuery query2(query_result1.toRDFString("turtle"));
  std::cerr << query2.run(argv[3]).toString();
  std::cerr << "**********************************************************\n";

  return 0;
}
