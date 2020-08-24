#include "omexmeta/OmexMetaCApi.h" // omexmeta::RDF
#include <cstdio>     // printf

using namespace omexmeta;

int main(){

    const char* rdf_str = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                          "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                          "@prefix OMEXlib: <http://omex-library.org/> .\n"
                          "@prefix myOMEX: <http://omex-library.org/NewOmex.omex> .\n"
                          "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                          "\n"
                          "local:OmexMetaId0000\n"
                          "   bqbiol:is <https://identifiers.org/uniprot/PD12345> .\n";

    // collect the link from "https://www.ebi.ac.uk/biomodels/BIOMD0000000308#Files"
    const char* tyson2003 = "https://www.ebi.ac.uk/biomodels/model/download/BIOMD0000000308.2?filename=BIOMD0000000308_url.xml";

    // first create a RDF graph, by any means available - here we choose from_string
    RDF* rdf_ptr = RDF_fromString(rdf_str, "turtle");

    // And now add to it from a uri
    RDF_addFromUri(rdf_ptr, tyson2003, "rdfxml");

    printf("Number of annotations in graph: %d\n", RDF_size(rdf_ptr));
    RDF_delete(rdf_ptr);
    return 0;
}