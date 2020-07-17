#include "omexmeta/OmexMetaCApi.h" // omexmeta::RDF
#include <cstdio> // printf

using namespace omexmeta;

int main(){

    // collect the link from "https://www.ebi.ac.uk/biomodels/BIOMD0000000308#Files"
    const char* model_uri = "https://www.ebi.ac.uk/biomodels/model/download/BIOMD0000000308.2?filename=BIOMD0000000308_url.xml";

    // download the model, scan document for annotations and docs-build a graph
    RDF *rdf_ptr = RDF_fromUri(model_uri, "rdfxml");

    int number_of_annotations = RDF_size(rdf_ptr);
    printf("Number of annotations in graph: %d\n", number_of_annotations);

    // remember to free the dynamically allocated RDF object
    RDF_delete(rdf_ptr);
    return 0;

}






