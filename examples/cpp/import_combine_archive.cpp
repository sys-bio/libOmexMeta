# include <semsim/SemSim.h>

# include <iostream>

using namespace semsim;

int main() {
  SBMLModel model = importSBMLOmex("/tmp/combine.omex", "model.xml", "annotations.xml");

  std::cerr << "**********************************************************\n";
  std::cerr << "RDF annotations\n";
  std::cerr << "**********************************************************\n\n";

  std::cerr << model.getRDF("./mymodel.xml", "turtle") << "\n";

  return 0;
}
