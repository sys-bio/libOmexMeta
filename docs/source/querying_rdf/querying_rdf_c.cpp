#include "omexmeta/OmexMeta.h"
#include "omexmeta/OmexMetaCApi.h"

using namespace omexmeta;

int main() {
    //get the link to teusink2000
    const char* teusink_biomod_link = "http://www.ebi.ac.uk/biomodels-main/download?mid=BIOMD0000000064";

    // download model xml, scan for rdf, create rdf graph and store in sqlite database
    RDF* rdf = RDF_fromUri(teusink_biomod_link, "rdfxml");

    const char* query_string = "SELECT ?x ?y\n"
                               "WHERE {\n"
                               "    ?x ?y <http://identifiers.org/obo.chebi/CHEBI:17234>\n"
                               "}";

    const char* results_formats[9] = {
            "xml",
            "json",
            "table",
            "csv",
            "mkr",
            "tsv",
            "html",
            "turtle",
            "rdfxml",
    };

    for (int i=0; i<9; i++){
        printf("Sparql results format: %s\n", results_formats[i]);
        char* string = RDF_query(rdf, query_string, results_formats[i]);
        printf("%s\n\n", string);
        free(string);
    }
    RDF_delete(rdf);

}