#include "omexmeta/OmexMetaCApi.h" // omexmeta::RDF

using namespace omexmeta;

int main(){

    const char* rdf_str = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                          "@prefix myOMEXlib: <http://omex-library.org/> .\n"
                          "@prefix myOMEX: <http://omex-library.org/NewOmex.omex> .\n"
                          "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                          "\n"
                          "<http://omex-library.org/NewOmex.omex/NewModel.xml#>\n"
                          "    <http://purl.org/dc/terms/creator> <https://orchid.org/1234-1234-1234-1234> .\n\n";
    // uses dynamic memory (i.e. a pointer)
    RDF *rdf_ptr = RDF_fromString(rdf_string, "turtle");
    int number_of_annotations = rdf_size(rdf_ptr);
    printf("Number of annotations in graph: %d\n", number_of_annotations);
    RDF_delete(rdf_ptr);    // delete used memory
    return 0;
}
