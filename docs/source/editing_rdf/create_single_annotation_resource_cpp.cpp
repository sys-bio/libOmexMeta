#include "omexmeta/OmexMeta.h"

using namespace omexmeta;

int main(){

    std::string sbml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                       "<!-- Created by libAntimony version v2.12.0 with libSBML version 5.18.1. -->\n"
                       "<sbml xmlns=\"http://www.sbml.org/sbml/level3/version1/core\" level=\"3\" version=\"1\">\n"
                       "  <model metaid=\"ToyModel\" id=\"ToyModel\">\n"
                       "    <listOfCompartments>\n"
                       "      <compartment id=\"cytosol\" spatialDimensions=\"3\" size=\"1\" constant=\"true\"/>\n"
                       "    </listOfCompartments>\n"
                       "    <listOfSpecies>\n"
                       "      <species id=\"A\" compartment=\"cytosol\" initialConcentration=\"10\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                       "      <species id=\"B\" compartment=\"cytosol\" initialConcentration=\"0\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                       "    </listOfSpecies>\n"
                       "    <listOfParameters>\n"
                       "      <parameter id=\"k1\" value=\"0.1\" constant=\"true\"/>\n"
                       "      <parameter id=\"k2\" value=\"0.1\" constant=\"true\"/>\n"
                       "    </listOfParameters>\n"
                       "    <listOfReactions>\n"
                       "      <reaction id=\"r1\" reversible=\"false\" fast=\"false\">\n"
                       "        <listOfReactants>\n"
                       "          <speciesReference species=\"B\" stoichiometry=\"1\" constant=\"true\"/>\n"
                       "        </listOfReactants>\n"
                       "        <listOfProducts>\n"
                       "          <speciesReference species=\"A\" stoichiometry=\"1\" constant=\"true\"/>\n"
                       "        </listOfProducts>\n"
                       "        <kineticLaw>\n"
                       "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
                       "            <apply>\n"
                       "              <times/>\n"
                       "              <ci> k2 </ci>\n"
                       "              <ci> B </ci>\n"
                       "            </apply>\n"
                       "          </math>\n"
                       "        </kineticLaw>\n"
                       "      </reaction>\n"
                       "    </listOfReactions>\n"
                       "  </model>\n"
                       "</sbml>\n";

    // create an empty RDF object
    RDF rdf = RDF();

    // create editor object
    Editor editor = rdf.toEditor(sbml, true, false);

    SingularAnnotation literal = editor.newSingularAnnotation();
    literal
        .about("ToyModel")
        .setPredicate("dc", "description")
        .setResourceLiteral("This is a toy model for demonstration purposes");
    editor.addSingleAnnotation(literal);

    SingularAnnotation blank = editor.newSingularAnnotation();
    blank
        .about("#OmexMetaId0001")
        .setPredicate("dc", "description")
        .setResourceBlank("BlankIdentifier");
    editor.addSingleAnnotation(blank);

    // The `uniprot/PD1234` gets resolved to https://identifier.org/uniprot/PD12345
    SingularAnnotation uri1 = editor.newSingularAnnotation();
    uri1.about("#OmexMetaId0002")
        .setPredicate("bqbiol", "is")
        .setResourceUri("uniprot/PD1234");
    editor.addSingleAnnotation(uri1);

    // In fact, this can be string with a format string1/string2
    SingularAnnotation uri2 = editor.newSingularAnnotation();
    uri2.about("#OmexMetaId0002")
        .predicate("bqbiol", "is")
        .resourceUri("string1/string2");
    editor.addSingleAnnotation(uri2);

    std::cout << rdf.toString() << std::endl;

    return 0;
}