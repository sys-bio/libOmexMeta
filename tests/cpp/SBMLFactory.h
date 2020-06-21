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
    SBML_BIOMD0000000695
};

/*
 * Abstract class implemented by all SBML models
 */
class SBMLModel {
public:
    SBMLModel() = default;

    virtual std::string strModel() = 0;

};

class SBMLAnnotated : SBMLModel {
public:
    SBMLAnnotated() = default;

    std::string strModel() override {
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
               "      <compartment metaid=\"cytosol\" id=\"cytosol\" size=\"1\" constant=\"true\"/>\n"
               "    </listOfCompartments>\n"
               "    <listOfSpecies>\n"
               "      <species metaid=\"glucose\" id=\"glucose\" compartment=\"cytosol\" initialConcentration=\"0\" substanceUnits=\"molar\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
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

    std::string strModel() override {
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
               "      <compartment metaid=\"cytosol\" id=\"cytosol\" size=\"1\" constant=\"true\"/>\n"
               "    </listOfCompartments>\n"
               "    <listOfSpecies>\n"
               "      <species metaid=\"Meta00001\" id=\"X\" compartment=\"cytosol\" initialConcentration=\"10\" substanceUnits=\"molar\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
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


class SBMLFactory {
public:

    static std::string getSBMLString(ModelType modelType) {
        if (modelType == SBML_ANNOTATED)
            return SBMLAnnotated().strModel();
        else if (modelType == SBML_NOT_ANNOTATED)
            return SBMLNotAnnotated().strModel();
        else {
            throw std::invalid_argument("ModelType is not a valid argument.");
        }
    }
};


#endif //LIBSEMGEN_SBMLFACTORY_H
