#include "omexmeta/omexmeta.h"

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
    Editor editor = rdf.toEditor(sbml, OMEXMETA_TYPE_SBML, true);

    // Print out metaids to console
    std::vector<std::string> metaids = editor.getMetaids();
    for (auto &id: metaids){
    std::cout << id << ", ";
    }
    std::cout << std::endl;

    // create out annotation
    SingularAnnotation singular_annotation = editor.newSingularAnnotation();
    singular_annotation
        .setAbout("#OmexMetaId0001")
        .setPredicate("bqbiol", "is")
        .setResourceUri("uniprot/P01137");

    // in C/C++ we need to manually add the annotation to the editor
    editor.addSingleAnnotation(singular_annotation);

    // The Singular annotation object contains a dynamically allocated
    // librdf_statement* from the redland libraries which must be freed
    // by the caller. Now we've use the singular_annotation object
    // we can release the used memory.
    singular_annotation.freeTriple();

    std::cout << rdf.toString("turtle") << std::endl;

    return 0;
}