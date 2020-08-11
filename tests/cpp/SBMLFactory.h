//
// Created by Ciaran on 3/29/2020.
//

#ifndef LIBSEMGEN_SBMLFACTORY_H
#define LIBSEMGEN_SBMLFACTORY_H

#include <utility>
#include <string>
#include <stdexcept>


enum ModelType {
    SBML_ANNOTATED,
    SBML_NOT_ANNOTATED,
    SBML_Semantic_Extraction_Model
};

/*
 * Abstract class implemented by all SBML models
 */
class SBMLModel {
public:
    SBMLModel() = default;

    virtual std::string str() = 0;

};

class SBMLAnnotated : SBMLModel {
public:
    SBMLAnnotated() = default;

    std::string str() override {
        return "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
               "<sbml xmlns=\"http://www.sbml.org/sbml/level3/version2/core\" level=\"3\" version=\"2\">\n"
               "  <model id=\"beta_cell_model\">\n"
               "    <listOfUnitDefinitions>\n"
               "      <unitDefinition id=\"molar\">\n"
               "        <listOfUnits>\n"
               "          <unit kind=\"mole\" exponent=\"1\" scale=\"1\" multiplier=\"1\"/>\n"
               "          <unit kind=\"litre\" exponent=\"-1\" scale=\"1\" multiplier=\"1\"/>\n"
               "        </listOfUnits>\n"
               "      </unitDefinition>\n"
               "    </listOfUnitDefinitions>\n"
               "    <listOfCompartments>\n"
               "      <compartment metaid=\"#cytosol\" id=\"cytosol\" size=\"1\" constant=\"true\"/>\n"
               "    </listOfCompartments>\n"
               "    <listOfSpecies>\n"
               "      <species metaid=\"#glucose\" id=\"glucose\" compartment=\"cytosol\" initialConcentration=\"0\" substanceUnits=\"molar\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
               "    </listOfSpecies>\n"
               "    <listOfReactions>\n"
               "      <reaction id=\"glucose_import\" reversible=\"false\">\n"
               "        <listOfProducts>\n"
               "          <speciesReference species=\"glucose\" constant=\"false\"/>\n"
               "        </listOfProducts>\n"
               "        <kineticLaw>\n"
               "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
               "            <ci> glucose_import_rate </ci>\n"
               "          </math>\n"
               "          <listOfLocalParameters>\n"
               "            <localParameter id=\"glucose_import_rate\" value=\"1\"/>\n"
               "          </listOfLocalParameters>\n"
               "        </kineticLaw>\n"
               "      </reaction>\n"
               "    </listOfReactions>\n"
               "  </model>\n"
               "</sbml>\n";
    }
};

class SBMLNotAnnotated : SBMLModel {
public:
    SBMLNotAnnotated() = default;

    std::string str() override {
        return "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
               "<sbml xmlns=\"http://www.sbml.org/sbml/level3/version2/core\" level=\"3\" version=\"2\">\n"
               "  <model id=\"TestModelNotAnnotated\">\n"
               "    <listOfUnitDefinitions>\n"
               "      <unitDefinition id=\"molar\">\n"
               "        <listOfUnits>\n"
               "          <unit kind=\"mole\" exponent=\"1\" scale=\"1\" multiplier=\"1\"/>\n"
               "          <unit kind=\"litre\" exponent=\"-1\" scale=\"1\" multiplier=\"1\"/>\n"
               "        </listOfUnits>\n"
               "      </unitDefinition>\n"
               "    </listOfUnitDefinitions>\n"
               "    <listOfCompartments>\n"
               "      <compartment metaid=\"#cytosol\" id=\"cytosol\" size=\"1\" constant=\"true\"/>\n"
               "    </listOfCompartments>\n"
               "    <listOfSpecies>\n"
               "      <species metaid=\"#Meta00001\" id=\"X\" compartment=\"cytosol\" initialConcentration=\"10\" substanceUnits=\"molar\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
               "      <species id=\"Y\" compartment=\"cytosol\" initialConcentration=\"20\" substanceUnits=\"molar\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
               "      <species id=\"Y\" compartment=\"cytosol\" initialConcentration=\"15\" substanceUnits=\"molar\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
               "    </listOfSpecies>\n"
               "    <listOfReactions>\n"
               "      <reaction id=\"X2Y\" reversible=\"false\">\n"
               "        <listOfProducts>\n"
               "          <speciesReference species=\"Y\" constant=\"false\"/>\n"
               "        </listOfProducts>\n"
               "        <kineticLaw>\n"
               "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
               "            <apply>\n"
               "              <times/>\n"
               "              <ci> x </ci>\n"
               "              <ci> kx2y </ci>\n"
               "            </apply>\n"
               "          </math>\n"
               "          <listOfLocalParameters>\n"
               "            <localParameter id=\"kx2y\" value=\"1\"/>\n"
               "            <localParameter id=\"ky2z\" value=\"1\"/>\n"
               "          </listOfLocalParameters>\n"
               "        </kineticLaw>\n"
               "      </reaction>\n"
               "      <reaction id=\"y2z\" reversible=\"false\">\n"
               "        <listOfProducts>\n"
               "          <speciesReference species=\"Z\" constant=\"false\"/>\n"
               "        </listOfProducts>\n"
               "        <kineticLaw>\n"
               "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
               "            <apply>\n"
               "              <times/>\n"
               "              <ci> y </ci>\n"
               "              <ci> ky2z </ci>\n"
               "            </apply>\n"
               "          </math>\n"
               "        </kineticLaw>\n"
               "      </reaction>\n"
               "    </listOfReactions>\n"
               "  </model>\n"
               "</sbml>\n";
    }
};

class SBMLSemanticExtractionModel : SBMLModel {
public:
    SBMLSemanticExtractionModel() = default;

    std::string str() override {
        return "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
               "<sbml xmlns=\"http://www.sbml.org/sbml/level3/version1/core\" level=\"3\" version=\"1\">\n"
               "    <model metaid=\"ToyModel\" id=\"ToyModel\">\n"
               "        <listOfCompartments>\n"
               "            <compartment id=\"cytosol\" metaid=\"comp1\" spatialDimensions=\"3\" size=\"1\" constant=\"true\"/>\n"
               "            <compartment id=\"extraCell\" metaid=\"comp2\" spatialDimensions=\"3\" size=\"10\" constant=\"true\"/>\n"
               "        </listOfCompartments>\n"
               "        <listOfSpecies>\n"
               "            <species id=\"A\" metaid=\"sp_1\" compartment=\"cytosol\" initialConcentration=\"10\" hasOnlySubstanceUnits=\"false\"\n"
               "                     boundaryCondition=\"false\" constant=\"false\">\n"
               "                <annotation>\n"
               "                    <rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
               "                             xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\">\n"
               "                        <rdf:Description rdf:about=\"#_1\">\n"
               "                            <bqbiol:is>\n"
               "                                <rdf:Bag>\n"
               "                                    <rdf:li rdf:resource=\"http://identifiers.org/uniprot/P00742\"/>\n"
               "                                </rdf:Bag>\n"
               "                            </bqbiol:is>\n"
               "                        </rdf:Description>\n"
               "                    </rdf:RDF>\n"
               "                </annotation>\n"
               "            </species>\n"
               "            <species id=\"B\" metaid=\"sp_2\" compartment=\"cytosol\" initialConcentration=\"0\" hasOnlySubstanceUnits=\"false\"\n"
               "                     boundaryCondition=\"false\" constant=\"false\"/>\n"
               "            <species id=\"Ca\" metaid=\"sp_3\" compartment=\"cytosol\" initialConcentration=\"2\" hasOnlySubstanceUnits=\"false\"\n"
               "                     boundaryCondition=\"false\" constant=\"false\"/>\n"
               "            <species id=\"PlasmaCa\" metaid=\"sp_4\" compartment=\"extraCell\" initialConcentration=\"3\"\n"
               "                     hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
               "            <species id=\"Enzyme\" metaid=\"sp_5\" compartment=\"cytosol\" initialConcentration=\"2\"\n"
               "                     hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
               "        </listOfSpecies>\n"
               "        <listOfParameters>\n"
               "            <parameter id=\"k1\" value=\"0.1\" constant=\"true\"/>\n"
               "            <parameter id=\"k2\" value=\"0.1\" constant=\"true\"/>\n"
               "        </listOfParameters>\n"
               "        <listOfReactions>\n"
               "            <reaction id=\"r1\" metaid=\"react1\" reversible=\"false\" fast=\"false\">\n"
               "                <listOfReactants>\n"
               "                    <speciesReference species=\"B\" stoichiometry=\"1\" constant=\"true\"/>\n"
               "                </listOfReactants>\n"
               "                <listOfProducts>\n"
               "                    <speciesReference species=\"A\" stoichiometry=\"2\" constant=\"true\"/>\n"
               "                </listOfProducts>\n"
               "                <kineticLaw>\n"
               "                    <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
               "                        <apply>\n"
               "                            <times/>\n"
               "                            <ci>k2</ci>\n"
               "                            <ci>B</ci>\n"
               "                        </apply>\n"
               "                    </math>\n"
               "                </kineticLaw>\n"
               "            </reaction>\n"
               "            <reaction id=\"r2\" metaid=\"react2\" reversible=\"false\" fast=\"false\">\n"
               "                <listOfReactants>\n"
               "                    <speciesReference species=\"Ca\" stoichiometry=\"1\" constant=\"true\"/>\n"
               "                    <speciesReference species=\"A\" stoichiometry=\"1\" constant=\"true\"/>\n"
               "                </listOfReactants>\n"
               "                <listOfProducts>\n"
               "                    <speciesReference species=\"PlasmaCa\" stoichiometry=\"1\" constant=\"true\"/>\n"
               "                </listOfProducts>\n"
               "                <listOfModifiers>\n"
               "                    <modifierSpeciesReference species=\"Enzyme\"/>\n"
               "                </listOfModifiers>\n"
               "                <kineticLaw>\n"
               "                    <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
               "                        <apply>\n"
               "                            <times/>\n"
               "                            <ci>k2</ci>\n"
               "                            <ci>Ca</ci>\n"
               "                        </apply>\n"
               "                    </math>\n"
               "                </kineticLaw>\n"
               "            </reaction>\n"
               "        </listOfReactions>\n"
               "    </model>\n"
               "</sbml>\n"
               "";
    }
};


class SBMLFactory {
public:

    static std::string getSBML(ModelType modelType) {
        if (modelType == SBML_ANNOTATED)
            return SBMLAnnotated().str();
        else if (modelType == SBML_NOT_ANNOTATED)
            return SBMLNotAnnotated().str();
        else if (modelType == SBML_Semantic_Extraction_Model)
            return SBMLSemanticExtractionModel().str();
        else {
            throw std::invalid_argument("ModelType is not a valid argument.");
        }
    }

};


#endif //LIBSEMGEN_SBMLFACTORY_H
