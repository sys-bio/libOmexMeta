#include "omexmeta/OmexMeta.h"
#include <vector>
#include <filesystem>

using namespace omexmeta;

int main() {
    std::string turtle_string = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                                "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                                "@prefix OMEXlib: <http://omex-library.org/> .\n"
                                "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                                "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                                "\n"
                                "<http://omex-library.org/Welsh2020.omex/Welsh2020.xml#OmexMetaId0001>\n"
                                "    bqbiol:isPropertyOf local:PhysicalEntity0000 ;\n"
                                "    bqbiol:isVersionOf <https://identifiers.org/OPB/OPB_00340> .\n"
                                "\n"
                                "<http://omex-library.org/Welsh2020.omex/Welsh2020.xml#PhysicalEntity0000>\n"
                                "    bqbiol:is <https://identifiers.org/uniprot/P84022> ;\n"
                                "    bqbiol:isPartOf <https://identifiers.org/fma/FMA:24178>, <https://identifiers.org/fma/FMA:63877>, <https://identifiers.org/fma/FMA:70737>, <https://identifiers.org/fma/FMA:7163> .\n";


    // remember that the default parser is "guess".
    // the parser will try to figure out which syntax is being used.
    // but if it doesn't guess well, you can use the format argument for `fromString`
    RDF rdf = RDF::fromString(turtle_string);

    std::string syntax = "ntriples";
    std::filesystem::path filename = std::filesystem::current_path() /+ "annotations.rdf";
    std::cout << "Serializing to " << syntax << ":" << std::endl;
    rdf.toFile(syntax, filename.string());
    std::cout << "RDF graph serialized to \"" << filename << "\"" << std::endl;

    // clean up
    if(std::filesystem::exists(filename)){
        std::filesystem::remove(filename);
    }

    return 0;
}
