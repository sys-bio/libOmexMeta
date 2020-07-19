#include "omexmeta/OmexMeta.h"
#include "omexmeta/OmexMetaCApi.h"

using namespace omexmeta;

int main(){

    const char* rdf_str = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                          "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                          "@prefix myOMEXlib: <http://omex-library.org/> .\n"
                          "@prefix myOMEX: <http://omex-library.org/NewOmex.omex> .\n"
                          "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                          "\n"
                          "local:OmexMetaId0000\n"
                          "     bqbiol:is <https://identifiers.org/uniprot/PD12345> .\n";
    
    // read the string into our RDF graph

    RDF* rdf_ptr = RDF_fromString(rdf_str, "turtle");
    
    const char* fname = "/mnt/d/libOmexMeta/annotation_file.rdf";
    
    // Add to our RDF graph 
    RDF_addFromFile(rdf_ptr, fname, "turtle"); // assume the content of annotation_file is turtle
    RDF_delete(rdf_ptr);
    return 0;
}