#include <cstdio>
#include "omexmeta/OmexMetaCApi.h"
#include <filesystem>

using namespace omexmeta;

int writeToFile(const char* fname);

int writeToFile(const char* fname) {
    printf("%s:%d", __FILE__, __LINE__);
    const char *rdf_str = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                          "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                          "@prefix OMEXlib: <http://omex-library.org/> .\n"
                          "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                          "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                          "\n"
                          "<http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0000>\n"
                          "     bqbiol:is <https://identifiers.org/uniprot/PD12345> .\n";
    printf("%s:%d", __FILE__, __LINE__);

    FILE *fp;
    printf("%s:%d", __FILE__, __LINE__);
    int i;
    printf("%s:%d", __FILE__, __LINE__);
    /* open the file for writing*/
    fp = fopen(fname, "w");
    printf("%s:%d", __FILE__, __LINE__);

    for (i = 0; i < 10; i++) {
    printf("%s:%d", __FILE__, __LINE__);
        fprintf(fp, "%s", rdf_str);
    printf("%s:%d", __FILE__, __LINE__);
    }

    /* close the file*/
    printf("%s:%d", __FILE__, __LINE__);
    fclose(fp);
    printf("%s:%d", __FILE__, __LINE__);
    return 0;
}

int main() {

    // here we cheat and use C++ to get filepath that will work on all systems (>C++17)
    std::filesystem::path fname = std::filesystem::current_path() /+ "annotation_file.rdf";

    // write to file
    writeToFile(fname.string().c_str());

    // create an RDF graph so we have something to add to
    RDF* rdf_ptr = RDF_new();

    // Add to our RDF graph
    RDF_addFromFile(rdf_ptr, fname.string().c_str(), "turtle");// assume the content of annotation_file is turtle

    // generate some output
    char*rdfxml_string = RDF_toString(rdf_ptr, "rdfxml-abbrev");

    // print to console
    printf("%s", rdfxml_string);

    // free dynamically generated output string
    free(rdfxml_string);

    // clear up the file we wrote
    remove(fname);

    // clear up rdf
    RDF_delete(rdf_ptr);

    return 0;
}