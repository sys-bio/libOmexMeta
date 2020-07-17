#include "omexmeta/RDF.h" // omexmeta::RDF
#include <iostream>     // std::cout, std::endl

using namespace omexmeta;

int main(){

    std::string rdf_str = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                          "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                          "@prefix myOMEXlib: <http://omex-library.org/> .\n"
                          "@prefix myOMEX: <http://omex-library.org/NewOmex.omex> .\n"
                          "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                          "\n"
                          "local:OmexMetaId0000\n"
                          "     bqbiol:is <https://identifiers.org/uniprot/PD12345> .\n";

    // read the string into our RDF graph
    RDF rdf = RDF::fromString(rdf_str, format="turtle");

    std::string fname = "/path/to/annotation_file.rdf";

    // Add to our RDF graph
    rdf.add_from_file(fname, "turtle"); // assume the content of annotation_file is turtle
    return 0;
}