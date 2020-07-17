#include "omexmeta/RDF.h" // omexmeta::RDF
#include <cstdio>     // printf

using namespace omexmeta;

int main(){

    std::string fname = "/path/to/annotation_file.rdf";

    // read the string into our RDF graph
    RDF* rdf_ptr = RDF_fromFile(fname, format="turtle");

    // free dynamic memory
    RDF_delete(rdf_ptr);
    return 0;
}