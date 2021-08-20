# will be deleted soon.

import pyomexmeta as pyo

import os

sbml_invalid_metaids = """<?xml version="1.0" encoding="UTF-8"?>
<!-- Created by libAntimony version v2.11.0 with libSBML version 5.18.0. -->
<sbml xmlns="http://www.sbml.org/sbml/level3/version1/core" level="3" version="1">
  <model metaid="SimpleRegulation" id="SimpleRegulation">
    <listOfCompartments>
      <compartment id="cell" spatialDimensions="3" size="1" constant="true" metaid="#OmexMetaId0000"/>
    </listOfCompartments>
    <listOfSpecies>
      <species id="A" compartment="cell" initialConcentration="10" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false" metaid="#OmexMetaId0001"/>
      <species id="B" compartment="cell" initialConcentration="0" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false" metaid="#OmexMetaId0002"/>
      <species id="C" compartment="cell" initialConcentration="10" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false" metaid="#OmexMetaId0003"/>
      <species id="D" compartment="cell" initialConcentration="0" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false" metaid="#OmexMetaId0004"/>
    </listOfSpecies>
    <listOfParameters>
      <parameter id="S" value="0" constant="true"/>
      <parameter id="k1" value="0.1" constant="true"/>
      <parameter id="k2" value="0.1" constant="true"/>
      <parameter id="k3" value="0.1" constant="true"/>
      <parameter id="k4" value="0.1" constant="true"/>
    </listOfParameters>
    <listOfReactions>
      <reaction id="R1" reversible="false" fast="false" metaid="#OmexMetaId0005">
        <listOfReactants>
          <speciesReference species="A" stoichiometry="1" constant="true"/>
        </listOfReactants>
        <listOfProducts>
          <speciesReference species="B" stoichiometry="1" constant="true"/>
        </listOfProducts>
        <kineticLaw metaid="#OmexMetaId0006">
          <math xmlns="http://www.w3.org/1998/Math/MathML">
            <apply>
              <times/>
              <ci> k1 </ci>
              <ci> A </ci>
              <ci> S </ci>
            </apply>
          </math>
        </kineticLaw>
      </reaction>
      <reaction id="R2" reversible="false" fast="false" metaid="#OmexMetaId0007">
        <listOfReactants>
          <speciesReference species="B" stoichiometry="1" constant="true"/>
        </listOfReactants>
        <listOfProducts>
          <speciesReference species="A" stoichiometry="1" constant="true"/>
        </listOfProducts>
        <kineticLaw metaid="#OmexMetaId0008">
          <math xmlns="http://www.w3.org/1998/Math/MathML">
            <apply>
              <times/>
              <ci> k2 </ci>
              <ci> B </ci>
            </apply>
          </math>
        </kineticLaw>
      </reaction>
      <reaction id="R3" reversible="false" fast="false" metaid="#OmexMetaId0009">
        <listOfReactants>
          <speciesReference species="C" stoichiometry="1" constant="true"/>
        </listOfReactants>
        <listOfProducts>
          <speciesReference species="D" stoichiometry="1" constant="true"/>
        </listOfProducts>
        <listOfModifiers>
          <modifierSpeciesReference species="B"/>
        </listOfModifiers>
        <kineticLaw metaid="#OmexMetaId0010">
          <math xmlns="http://www.w3.org/1998/Math/MathML">
            <apply>
              <times/>
              <ci> k3 </ci>
              <ci> C </ci>
              <ci> B </ci>
            </apply>
          </math>
        </kineticLaw>
      </reaction>
      <reaction id="R4" reversible="false" fast="false" metaid="#OmexMetaId0011">
        <listOfReactants>
          <speciesReference species="D" stoichiometry="1" constant="true"/>
        </listOfReactants>
        <listOfProducts>
          <speciesReference species="C" stoichiometry="1" constant="true"/>
        </listOfProducts>
        <kineticLaw metaid="#OmexMetaId0012">
          <math xmlns="http://www.w3.org/1998/Math/MathML">
            <apply>
              <times/>
              <ci> k4 </ci>
              <ci> D </ci>
            </apply>
          </math>
        </kineticLaw>
      </reaction>
    </listOfReactions>
  </model>
</sbml>"""


rdf = pyo.RDF.from_string(sbml_invalid_metaids)

print(rdf)
































