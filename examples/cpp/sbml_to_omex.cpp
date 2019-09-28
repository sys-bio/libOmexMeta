# include <semsim/SemSim.h>

# include <iostream>

using namespace semsim;

int main(int argc, char *argv[]) {
  if (argc < 1+4)
    throw std::runtime_error("Usage: import_sbml sbml-filename output-omex-filename sbml-path-in-omex rdf-path-in-omex");

  SBMLModel model = importSBMLFromFile(std::string(argv[1]));

  std::cerr << "**********************************************************\n";
  std::cerr << "RDF annotations\n";
  std::cerr << "**********************************************************\n\n";

  std::cerr << model.getRDF("./mymodel.xml", "turtle") << "\n";

  exportToOmex(model, std::string(argv[2]), std::string(argv[3]), std::string(argv[4]));

  std::cerr << "wrote omex to " << std::string(argv[2]) << "\n";

  return 0;
}
