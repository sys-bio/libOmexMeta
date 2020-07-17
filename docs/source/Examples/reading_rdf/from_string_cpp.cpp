#include "omexmeta/RDF.h" // omexmeta::RDF
#include <iostream>     // std::cout, std::endl

using namespace omexmeta;

int main(){

    std::string rdf_str = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                          "@prefix myOMEXlib: <http://omex-library.org/> .\n"
                          "@prefix myOMEX: <http://omex-library.org/NewOmex.omex> .\n"
                          "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                          "\n"
                          "<http://omex-library.org/NewOmex.omex/NewModel.xml#>\n"
                          "    <http://purl.org/dc/terms/creator> <https://orchid.org/1234-1234-1234-1234> .\n\n";
    RDF rdf = RDF::fromString(rdf_string, "turtle");
    int number_of_annotations = rdf.size();
    std::cout << "Number of annotations in graph: " << number_of_annotations << std::endl;
    return 0;
}