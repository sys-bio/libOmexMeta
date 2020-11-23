from pyomexmeta import RDF, eUriType
sbml = """<?xml version="1.0" encoding="UTF-8"?>
<!-- Created by libAntimony version v2.12.0 with libSBML version 5.18.1. -->
<sbml xmlns="http://www.sbml.org/sbml/level3/version1/core" level="3" version="1">
  <model metaid="SimpleRegulation" id="SimpleRegulation">
    <listOfCompartments>
      <compartment id="cell" spatialDimensions="3" size="1" constant="true"/>
    </listOfCompartments>
    <listOfSpecies>
      <species id="A" metaid="SpeciesA" compartment="cell" initialConcentration="10" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>
      <species id="B" metaid="SpeciesB" compartment="cell" initialConcentration="0" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>
      <species id="C" metaid="SpeciesC" compartment="cell" initialConcentration="10" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>
      <species id="D" metaid="SpeciesD" compartment="cell" initialConcentration="0" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>
    </listOfSpecies>
    <listOfParameters>
      <parameter id="S"  metaid="S" value="0" constant="true"/>
      <parameter id="k1" metaid="k1" value="0.1" constant="true"/>
      <parameter id="k2" metaid="k2" value="0.1" constant="true"/>
      <parameter id="k3" metaid="k3" value="0.1" constant="true"/>
      <parameter id="k4" metaid="k4" value="0.1" constant="true"/>
    </listOfParameters>
    <listOfReactions>
      <reaction id="R1" metaid="R1" reversible="false" fast="false">
        <listOfReactants>
          <speciesReference species="A" stoichiometry="1" constant="true"/>
        </listOfReactants>
        <listOfProducts>
          <speciesReference species="B" stoichiometry="1" constant="true"/>
        </listOfProducts>
        <kineticLaw metaid="KineticLawForReaction1">
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
      <reaction id="R2" metaid="R2" reversible="false" fast="false">
        <listOfReactants>
          <speciesReference species="B" stoichiometry="1" constant="true"/>
        </listOfReactants>
        <listOfProducts>
          <speciesReference species="A" stoichiometry="1" constant="true"/>
        </listOfProducts>
        <kineticLaw metaid="KineticLawForReaction2">
          <math xmlns="http://www.w3.org/1998/Math/MathML">
            <apply>
              <times/>
              <ci> k2 </ci>
              <ci> B </ci>
            </apply>
          </math>
        </kineticLaw>
      </reaction>
      <reaction id="R3" reversible="false" fast="false">
        <listOfReactants>
          <speciesReference species="C" stoichiometry="1" constant="true"/>
        </listOfReactants>
        <listOfProducts>
          <speciesReference species="D" stoichiometry="1" constant="true"/>
        </listOfProducts>
        <listOfModifiers>
          <modifierSpeciesReference species="B"/>
        </listOfModifiers>
        <kineticLaw>
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
      <reaction id="R4" reversible="false" fast="false">
        <listOfReactants>
          <speciesReference species="D" stoichiometry="1" constant="true"/>
        </listOfReactants>
        <listOfProducts>
          <speciesReference species="C" stoichiometry="1" constant="true"/>
        </listOfProducts>
        <kineticLaw>
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
</sbml>
"""

# create an empty RDF object
rdf = RDF()

editor = rdf.to_editor(sbml, generate_new_metaids=True, sbml_semantic_extraction=False)

sbml_with_metaids = editor.get_xml()
print(sbml_with_metaids)

with editor.new_physical_entity() as physical_entity:
    physical_entity \
        .about("SpeciesA", eUriType.MODEL_URI) \
        .identity("uniprot/PD12345") \
        .is_part_of("fma:1234") \
        .has_property( "EntityProperty", eUriType.LOCAL_URI, "opb:OPB_12345")


print(rdf)


