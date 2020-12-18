#include "omexmeta/OmexMeta.h"
#include "omexmeta/OmexMetaCApi.h"

using namespace omexmeta;

int main() {
    const char* turtle_string = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                                "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                                "@prefix OMEXlib: <http://omex-library.org/> .\n"
                                "@prefix local: <http://omex-library.org/Welsh2020.omex/Welsh2020.rdf#> .\n"
                                "\n"
                                "<http://omex-library.org/Welsh2020.omex/Welsh2020.xml#OmexMetaId0001>\n"
                                "    bqbiol:isPropertyOf local:EntityProperty0000 ;\n"
                                "    bqbiol:isVersionOf <https://identifiers.org/OPB/OPB_00340> .\n"
                                "\n"
                                "<http://omex-library.org/Welsh2020.omex/Welsh2020.xml#EntityProperty0000>\n"
                                "    bqbiol:is <https://identifiers.org/uniprot/P84022> ;\n"
                                "    bqbiol:isPartOf <https://identifiers.org/fma/FMA:24178>, <https://identifiers.org/fma/FMA:63877>, <https://identifiers.org/fma/FMA:70737>, <https://identifiers.org/fma/FMA:7163> .\n";


    // remember that the default parser is "guess".
    // the parser will try to figure out which syntax is being used.
    // but if it doesn't guess well, you can use the format argument for `fromString`
    RDF* rdf = RDF_fromString(turtle_string, "guess");

    const char* syntax = "ntriples";

    // we cheat and use c++ for system independent filepath
    const char* filename = (std::filesystem::current_path() /+ "annotations.rdf").string().c_str();

    printf("Serializing to %s \n", syntax);
    int failed = RDF_toFile(rdf, syntax, filename); // 1 if failed else 0
    if (failed) {
        printf("You broke C");
        exit(1);
    }
    printf("RDF graph serialized to \"%s\"", filename);
    printf("Counted \"%d\" triples", RDF_size(rdf));

    // clean up (more cheating)
    if(std::filesystem::exists(filename)){
        std::filesystem::remove(filename);
    }

    RDF_delete(rdf);
    return 0;
}
