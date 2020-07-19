#include "omexmeta/OmexMetaCApi.h" // omexmeta::RDF

using namespace omexmeta;

int main(){

    const char* fname = "/path/to/annotation_file.rdf";

    // read the string into our RDF graph
    RDF* rdf_ptr = RDF_fromFile(fname, "turtle");

    // free dynamic memory
    RDF_delete(rdf_ptr);
    return 0;
}