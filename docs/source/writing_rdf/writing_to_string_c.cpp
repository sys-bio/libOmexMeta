#include "omexmeta/OmexMeta.h"
#include "omexmeta/OmexMetaCApi.h"

using namespace omexmeta;

int main() {
    const char* turtle_string = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                                "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                                "@prefix myOMEXlib: <http://omex-library.org/> .\n"
                                "@prefix myOMEX: <http://omex-library.org/NewOmex.omex> .\n"
                                "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                                "\n"
                                "local:OmexMetaId0001\n"
                                "    bqbiol:isPropertyOf local:PhysicalEntity0000 ;\n"
                                "    bqbiol:isVersionOf <https://identifiers.org/OPB/OPB_00340> .\n"
                                "\n"
                                "local:PhysicalEntity0000\n"
                                "    bqbiol:is <https://identifiers.org/uniprot/P84022> ;\n"
                                "    bqbiol:isPartOf <https://identifiers.org/fma/FMA:24178>, <https://identifiers.org/fma/FMA:63877>, <https://identifiers.org/fma/FMA:70737>, <https://identifiers.org/fma/FMA:7163> .\n";


    // remember that the default parser is "guess".
    // the parser will try to figure out which syntax is being used.
    // but if it doesn't guess well, you can use the format argument for `fromString`
    RDF* rdf = RDF_fromString(turtle_string, "guess");

    const char* formats[10] = {
            "ntriples",
            "turtle",
            "rdfxml-xmp",
            "rdfxml-abbrev",
            "rdfxml",
            "dot",
            "json-triples",
            "json",
            "nquads",
            "html"
    };

    for (int i=0; i<10; i++){
        printf("Serializing to %s: \n", formats[i]);
        char* string = RDF_toString(rdf, formats[i]);
        printf("%s\n", string );
        printf("\n\n");
        free(string);
    }

    RDF_delete(rdf);
    return 0;
}
