
#include "gtest/gtest.h"


#include "omexmeta/OmexMeta.h" // omexmeta::RDF
#include <iostream>     // std::cout, std::endl
#include <filesystem>

using namespace omexmeta;

/**
 * store an annotation string
 */
std::string getSBMLStringInput() {
    return std::string("@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                       "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                       "@prefix OMEXlib: <http://omex-library.org/> .\n"
                       "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                       "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                       "\n"
                       "<http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0000>\n"
                       "     bqbiol:is <https://identifiers.org/uniprot/PD12345> .\n");
}

}

/**
 * Write some annotations in turtle format to a file
 */
int writeToFile(const std::string &fname) {
    std::ofstream annot_file;
    annot_file.open(fname);
    annot_file << getSBMLStringInput();
    annot_file.close();
    return 0;
}


int main() {
    RDF rdf = RDF::fromString(getSBMLStringInput(), "turtle");
    std::string output_from_string = rdf.toString("rdfxml-abbrev");

//    assert(expectedOutput().c_str(), output_from_string.c_str());


//    // create an empty rdf graph
//    RDF rdf = RDF();
//
//    // note: you need C++17 standard minimum to use std::filesystem
//    std::filesystem::path fname = std::filesystem::current_path() /+ "annotation_file.rdf";
//
//    // write some annotations to a file so we can read it in with add from file
//    writeToFile(fname.string());
//
//    // Add to our RDF graph
//    rdf.addFromFile(fname.string(), "turtle"); // assume the content of annotation_file is turtle
//
//    // clear up file we wrote
//    remove(fname.string().c_str());
//
//    std::string xml_abbrev_string = rdf.toString("rdfxml-abbrev");
//
//    // Write rdf graph to rdfxml and print to console
//    std::cout << xml_abbrev_string << std::endl;
//
//    // RDF clears up after itself via RAII

    return 0;
}







