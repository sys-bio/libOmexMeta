#include "omexmeta/OmexMetaCApi.h" // omexmeta::RDF

using namespace omexmeta;


int writeToFile(const char* fname) {
    const char *rdf_str = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                          "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                          "@prefix OMEXlib: <http://omex-library.org/> .\n"
                          "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                          "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                          "\n"
                          "<http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0000>\n"
                          "     bqbiol:is <https://identifiers.org/uniprot/PD12345> .\n";

    FILE *fp;
    int i;
    /* open the file for writing*/
    fp = fopen(fname, "w");

    for (i = 0; i < 10; i++) {
        fprintf(fp, "%s", rdf_str);
    }

    /* close the file*/
    fclose(fp);
    return 0;
}


int main(){


    std::filesystem::path fname = std::filesystem::current_path() /+ "annotation_file.rdf";

    writeToFile(fname.string().c_str());

    // read the string into our RDF graph
    RDF* rdf_ptr = RDF_fromFile( fname.string().c_str(), "turtle");

    printf("%d triples read from file", rdf_ptr->size());

    // clear up the file we wrote
    remove(fname.string().c_str());

    // clear up rdf
    RDF_delete(rdf_ptr);

    return 0;
}