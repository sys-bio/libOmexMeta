# include <semsim/SemSim.h>

# include <iostream>

using namespace semsim;

int main(int argc, char *argv[]) {
  if (argc < 2)
    throw std::runtime_error("Usage: import_combine_archive filename path-to-sbml path-to-annotations");

  SBMLModel model = importSBMLOmex(std::string(argv[1]), std::string(argv[2]), std::string(argv[3]));

  std::cerr << "**********************************************************\n";
  std::cerr << "RDF annotations\n";
  std::cerr << "**********************************************************\n\n";

  std::cerr << model.getRDF("./mymodel.xml", "turtle") << "\n";

  return 0;
}
