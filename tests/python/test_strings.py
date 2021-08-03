class TestStrings:
    # deprecated. Use sbml
    xml = """<?xml version="1.1" encoding="UTF-8"?>
    <sbml xmlns="http://www.sbml.org/sbml/level3/version2/core" level="3" version="2">
      <model id="TestModelNotAnnotated">
        <listOfUnitDefinitions>
          <unitDefinition id="molar">
            <listOfUnits>
              <unit kind="mole" exponent="1" scale="1" multiplier="1"/>
              <unit kind="litre" exponent="-1" scale="1" multiplier="1"/>
            </listOfUnits>
          </unitDefinition>
        </listOfUnitDefinitions>
        <listOfCompartments>
          <compartment metaid="cytosol" id="cytosol" size="1" constant="True"/>
        </listOfCompartments>
        <listOfSpecies>
          <species metaid="Meta00001" id="X" compartment="cytosol" initialConcentration="10" substanceUnits="molar" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>
          <species id="Y" compartment="cytosol" initialConcentration="20" substanceUnits="molar" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>
          <species id="Y" compartment="cytosol" initialConcentration="15" substanceUnits="molar" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>
        </listOfSpecies>
        <listOfReactions>
          <reaction id="X2Y" reversible="false">
            <listOfProducts>
              <speciesReference species="Y" constant="false"/>
            </listOfProducts>
            <kineticLaw>
              <math xmlns="http://www.w3.org/1998/Math/MathML">
                <apply>
                  <times/>
                  <ci> x </ci>
                  <ci> kx2y </ci>
                </apply>
              </math>
              <listOfLocalParameters>
                <localParameter id="kx2y" value="1"/>
                <localParameter id="ky2z" value="1"/>
              </listOfLocalParameters>
            </kineticLaw>
          </reaction>
          <reaction id="y2z" reversible="false">
            <listOfProducts>
              <speciesReference species="Z" constant="false"/>
            </listOfProducts>
            <kineticLaw>
              <math xmlns="http://www.w3.org/1998/Math/MathML">
                <apply>
                  <times/>
                  <ci> y </ci>
                  <ci> ky2z </ci>
                </apply>
              </math>
            </kineticLaw>
          </reaction>
        </listOfReactions>
      </model>
    </sbml>"""

    sbml_with_annotations = """<?xml version="1.0" encoding="UTF-8"?>
<sbml xmlns="http://www.sbml.org/sbml/level3/version1/core" level="3" version="1">
    <model metaid="ToyModel" id="ToyModel">
        <listOfCompartments>
            <compartment id="cytosol" metaid="comp1" spatialDimensions="3" size="1" constant="true"/>
            <compartment id="extraCell" metaid="comp2" spatialDimensions="3" size="10" constant="true"/>
        </listOfCompartments>
        <listOfSpecies>
            <species id="A" metaid="sp_1" compartment="cytosol" initialConcentration="10" hasOnlySubstanceUnits="false"
                     boundaryCondition="false" constant="false">
                <annotation>
                    <rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"
                             xmlns:bqbiol="http://biomodels.net/biology-qualifiers/">
                        <rdf:Description rdf:about="#DescriptionAnnotationWithBag">
                            <bqbiol:is>
                                <rdf:Bag>
                                    <rdf:li rdf:resource="http://identifiers.org/uniprot/P00742"/>
                                    <rdf:li rdf:resource="http://identifiers.org/uniprot/P00743"/>
                                </rdf:Bag>
                            </bqbiol:is>
                        </rdf:Description>
                    </rdf:RDF>
                </annotation>
            </species>
            <species id="B" metaid="sp_2" compartment="cytosol" initialConcentration="0" hasOnlySubstanceUnits="false"
                     boundaryCondition="false" constant="false"/>
            <species id="Ca" metaid="sp_3" compartment="cytosol" initialConcentration="2" hasOnlySubstanceUnits="false"
                     boundaryCondition="false" constant="false"/>
            <species id="PlasmaCa" metaid="sp_4" compartment="extraCell" initialConcentration="3"
                     hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>
            <species id="Enzyme" metaid="sp_5" compartment="cytosol" initialConcentration="2"
                     hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>
        </listOfSpecies>
        <listOfParameters>
            <parameter id="k1" value="0.1" constant="true"/>
            <parameter id="k2" value="0.1" constant="true"/>
        </listOfParameters>
        <listOfReactions>
            <reaction id="r1" metaid="react1" reversible="false" fast="false">
                <listOfReactants>
                    <speciesReference species="B" stoichiometry="1" constant="true"/>
                </listOfReactants>
                <listOfProducts>
                    <speciesReference species="A" stoichiometry="2" constant="true"/>
                </listOfProducts>
                <kineticLaw>
                    <math xmlns="http://www.w3.org/1998/Math/MathML">
                        <apply>
                            <times/>
                            <ci>k2</ci>
                            <ci>B</ci>
                        </apply>
                    </math>
                </kineticLaw>
            </reaction>
            <reaction id="r2" metaid="react2" reversible="false" fast="false">
                <listOfReactants>
                    <speciesReference species="Ca" stoichiometry="1" constant="true"/>
                    <speciesReference species="A" stoichiometry="1" constant="true"/>
                </listOfReactants>
                <listOfProducts>
                    <speciesReference species="PlasmaCa" stoichiometry="1" constant="true"/>
                </listOfProducts>
                <listOfModifiers>
                    <modifierSpeciesReference species="Enzyme"/>
                </listOfModifiers>
                <kineticLaw>
                    <math xmlns="http://www.w3.org/1998/Math/MathML">
                        <apply>
                            <times/>
                            <ci>k2</ci>
                            <ci>Ca</ci>
                        </apply>
                    </math>
                </kineticLaw>
            </reaction>
        </listOfReactions>
    </model>
</sbml>"""

    singular_annotation2 = """<?xml version=\"1.1\" encoding=\"UTF-8\"?>
   <rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"
            xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\"
            xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\">
   <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.xml#modelmeta1\">
       <bqmodel:isDescribedBy rdf:resource=\"https://identifiers.org/pubmed/12991237\" />
   </rdf:Description>
</rdf:RDF>"""

    cellml = '''<?xml version=\"1.1\" encoding=\"UTF-8\"?>
                <model xmlns=\"http://www.cellml.org/cellml/1.1#\" xmlns:cmeta=\"http://www.cellml.org/metadata/1.0#\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:bqs=\"http://www.cellml.org/bqs/1.0#\" xmlns:semsim=\"http://bime.uw.edu/semsim/#\" xmlns:dc=\"http://purl.org/dc/terms/\" xmlns:vCard=\"http://www.w3.org/2001/vcard-rdf/3.0#\" name=\"annotation_examples\" cmeta:id=\"annExamples\">
                  <component name=\"main\">
                    <variable cmeta:id=\"main.Volume\" initial_value=\"100\" name=\"Volume\" units=\"dimensionless\" />
                    <variable cmeta:id=\"main.MembraneVoltage\" initial_value=\"-80\" name=\"MembraneVoltage\" units=\"dimensionless\" />
                    <variable cmeta:id=\"main.ReactionRate\" initial_value=\"1\" name=\"ReactionRate\" units=\"dimensionless\" />
                  </component>
                </model>'''

    sbml = xml

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
