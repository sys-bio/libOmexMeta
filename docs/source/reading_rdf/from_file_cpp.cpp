#include "omexmeta/RDF.h" // omexmeta::RDF
#include <iostream>     // std::cout, std::endl

using namespace omexmeta;

int main(){

    std::string fname = "/path/to/annotation_file.rdf";

    // Add to our RDF graph
    RDF rdf = RDF::fromFile(fname, "turtle"); // assume the content of annotation_file is turtle
    return 0;
}