#include "omexmeta/OmexMeta.h"
#include "vector"
using namespace omexmeta;

int main() {
    //get the link to teusink2000
    std::string teusink_biomod_link = "https://www.ebi.ac.uk/biomodels/model/download/BIOMD0000000064.2?filename=BIOMD0000000064_url.xml";

    // download model xml, scan for rdf, create rdf graph and store in sqlite database
    RDF rdf = RDF::fromUri(teusink_biomod_link, "rdfxml");

    std::string query_string = "SELECT ?x ?y\n"
                               "WHERE {\n"
                               "    ?x ?y <http://identifiers.org/obo.chebi/CHEBI:17234>\n"
                               "}";

    // typedef'd std::unordered_map<std::string, std::vector<std::string>>
    ResultsMap resultsMap = rdf.queryResultsAsMap(query_string);

}