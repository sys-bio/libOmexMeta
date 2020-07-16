#include "omexmeta/OmexMetaCApi.h" // omexmeta::RDF
#include <cstdio> // printf

using namespace omexmeta;

int main(){

    const char* rdf_str1 = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix myOMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#>\n"
                           "      <http://purl.org/dc/terms/creator> <https://orchid.org/1234-1234-1234-1234> .\n";


    const char* rdf_str2 = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix myOMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:OmexMetaId0000\n"
                           "    bqbiol:is <https://identifiers.org/uniprot/PD12345> .\n";

    // read the first string into our RDF graph
    RDF* rdf_ptr = RDF_from_string(rdf_str1, format="turtle");
    // Add to our RDF graph by reading the second string
    rdf_addFromString(rdf_ptr, rdf_str2, "turtle");
    int number_of_annotations = rdf_size();
    printf("Number of annotations in graph: %d", number_of_annotations);
    RDF_delete(rdf_ptr);
    return 0;
}
