#include "omexmeta/RDF.h" // omexmeta::RDF
#include <iostream>     // std::cout, std::endl

using namespace omexmeta;

int main(){

    // collect the link from "https://www.ebi.ac.uk/biomodels/BIOMD0000000308#Files"
    std::string model_uri = "https://www.ebi.ac.uk/biomodels/model/download/BIOMD0000000308.2?filename=BIOMD0000000308_url.xml";

    // download the model, scan document for annotations and build a graph
    RDF rdf = RDF::fromUri(model_uri, "rdfxml");

    std::cout << "Number of annotations in graph: " << rdf.size() << std::endl;
    return 0;
}






