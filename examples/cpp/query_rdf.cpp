# include <semsim/SemSim.h>

# include "raptor2.h"
# include "rasqal.h"

# include <iostream>

using namespace semsim;

int main(int argc, char *argv[]) {
  if (argc < 1+2)
    throw std::runtime_error("Usage: query_rdf filename \"query1\" \"query2\"");

  std::cerr << "**********************************************************\n";
  RasqalQuery query1(argv[1], "rdfxml", true);
  RasqalQueryResult query_result1=query1.run(argv[2]);
  std::string rdf1 = query_result1.toRDFString("turtle");
  std::cerr << query_result1.toString();
  std::cerr << "**********************************************************\n";

  if (argc >= 4) {
    std::cerr << "\nSecond query\n\n";
    std::cerr << "**********************************************************\n";
    RasqalQuery query2(rdf1);
    std::cerr << query2.run(argv[3]).toString();
    std::cerr << "**********************************************************\n";
  }

  return 0;
}
