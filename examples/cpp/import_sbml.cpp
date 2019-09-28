# include <semsim/SemSim.h>

# include <iostream>

using namespace semsim;

int main(int argc, char *argv[]) {
  if (argc < 1)
    throw std::runtime_error("Usage: import_sbml filename");

  SBMLModel model = importSBMLFromFile(std::string(argv[1]));

  std::cerr << "**********************************************************\n";
  std::cerr << "RDF annotations\n";
  std::cerr << "**********************************************************\n\n";

  std::cerr << model.getRDF("./mymodel.xml", "turtle") << "\n";

  return 0;
}
