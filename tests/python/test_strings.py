class TestStrings:
    # deprecated. Use sbml
    sbml = """<?xml version="1.1" encoding="UTF-8"?>
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

    invalid_rdf = """<?xml version="1.0" encoding="utf-8"?>
<rdf:RDF
    xmlns:bqbiol="http://biomodels.net/biology-qualifiers/"
    xmlns:bqmodel="http://biomodels.net/model-qualifiers/"
    xmlns:collex="http://www.collex.org/schema#"
    xmlns:dc="http://dublincore.org/specifications/dublin-core/dcmi-terms/"
    xmlns:dcterms="http://purl.org/dc/terms/"
    xmlns:foaf="http://xmlns.com/foaf/0.1/"
    xmlns:om="http://ontology.eil.utoronto.ca/icity/OM/"
    xmlns:prism="http://prismstandard.org/namespaces/basic/2.0/"
    xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"
    xmlns:rdfs="http://www.w3.org/2000/01/rdf-schema#"
    xmlns:scoro="http://purl.org/spar/scoro/"
>
  <rdf:Description rdf:about="http://omex-libary.org/BioSim0001.omex">
    <!-- name -->
    <dc:title>Name</dc:title>

    <!-- short summary -->
    <dc:abstract>Short summary</dc:abstract>

    <!-- keywords -->
    <prism:keyword>tag 1</prism:keyword>
    <prism:keyword>tag 2</prism:keyword>

    <!-- thumbnail image -->
    <collex:thumbnail rdf:resource="http://omex-libary.org/BioSim0001.omex/thumbnail.png"/>

    <!-- long description -->
    <dc:description>Description</dc:description>

    <!-- taxon -->
    <bqbiol:hasTaxon rdf:resource="local:_00001"/>

    <!-- gene, RNA, protein, cell type, tissue, organ, disease -->
    <bqbiol:encodes rdf:resource="local:_00002"/>

    <!-- more information (i.e., domain specific information beyond recommended relationships and identifiers) -->
    <om:temporalUnit rdf:resource="local:_00003"/>

    <!-- source from which model package was derived (e.g., GitHub repository) -->
    <dc:source rdf:resource="local:_00004"/>

    <!-- ancestor(s) of this work -->
    <bqmodel:isDerivedFrom rdf:resource="local:_00005"/>

    <!-- successor(s) of this work -->
    <scoro:successor rdf:resource="local:_00006"/>

    <!-- related things to provide hyperlinks to -->
    <rdfs:seeAlso rdf:resource="local:_00007"/>

    <!-- other identifiers -->
    <bqmodel:is rdf:resource="local:_00008"/>

    <!-- authors(s) -->
    <dc:creator rdf:resource="local:_00009"/>

    <!-- contributor(s) -->
    <dc:contributor rdf:resource="local:_00010"/>

    <!-- citations -->
    <bqmodel:isDescribedBy rdf:resource="local:_00011"/>
    <bqmodel:isDescribedBy rdf:resource="local:_00012"/>

    <!-- license -->
    <dc:license rdf:resource="local:_00013"/>

    <!-- funder -->
    <scoro:funder rdf:resource="local:_00014"/>

    <!-- created -->
    <dc:created>
      <rdf:Description>
        <dc:W3CDTF>2020-06-18</dc:W3CDTF>
      </rdf:Description>
    </dc:created>

    <!-- modified -->
    <dc:modified>
      <dcterms:W3CDTF>
        <rdf:value>2021-06-18</rdf:value>
      </dcterms:W3CDTF>
    </dc:modified>
  </rdf:Description>

  <!-- taxon -->
  <rdf:Description rdf:about="local:_00001">
    <dc:identifier rdf:resource="https://identifiers.org/taxonomy/9606"/>
    <rdfs:label>Homo sapiens</rdfs:label>
  </rdf:Description>

  <!-- gene, RNA, protein, cell type, tissue, organ -->
  <rdf:Description rdf:about="local:_00002">
    <dc:identifier rdf:resource="https://identifiers.org/CL:0001057"/>
    <rdfs:label>myeloid dendritic cell, human</rdfs:label>
  </rdf:Description>

  <!-- more information -->
  <rdf:Description rdf:about="local:_00003">
    <dc:identifier rdf:resource="http://www.w3.org/2006/time#second"/>
    <rdfs:label>second</rdfs:label>
    <dc:description>Temporal unit</dc:description>
  </rdf:Description>

  <!-- source -->
  <rdf:Description rdf:about="local:_00004">
    <dc:identifier rdf:resource="https://github.org/lab/project"/>
    <rdfs:label>Tsur 2019 model source code</rdfs:label>
  </rdf:Description>

  <!-- ancestor(s) of this work -->
  <rdf:Description rdf:about="local:_00005">
    <dc:identifier rdf:resource="https://identifiers.org/biomodels.db:BIOMD0000000837"/>
    <rdfs:label>Hanson2016 - Toxicity Management in CAR T cell therapy for B-ALL</rdfs:label>
  </rdf:Description>

  <!-- successor(s) of this work -->
  <rdf:Description rdf:about="local:_00006">
    <dc:identifier rdf:resource="https://identifiers.org/biomodels.db:BIOMD0000000839"/>
    <rdfs:label>Almeida2019 - Transcription-based circadian ...</rdfs:label>
  </rdf:Description>

  <!-- related things (e.g., models of similar systems from other groups) -->
  <rdf:Description rdf:about="local:_00007">
    <dc:identifier rdf:resource="https://identifiers.org/biomodels.db:BIOMD0000000836"/>
    <rdfs:label>Radosavljevic2009_BioterroristAttack_PanicProtection_1</rdfs:label>
  </rdf:Description>

  <!-- other identifiers -->
  <rdf:Description rdf:about="local:_00008">
    <dc:identifier rdf:resource="https://identifiers.org/biomodels.db:BIOMD0000000838"/>
    <rdfs:label>biomodels.db:BIOMD0000000838</rdfs:label>
  </rdf:Description>

  <!-- citations(s) -->
  <rdf:Description rdf:about="local:_00011">
    <dc:identifier rdf:resource="https://identifiers.org/doi:10.1016/j.copbio.2017.12.013"/>
    <rdfs:label>Goldberg AP, Szigeti B, Chew YH, Sekar JA, Roth YD &amp; Karr JR. Emerging whole-cell modeling principles and methods. Curr Opin Biotechnol 2018, 51:97-102.</rdfs:label>
  </rdf:Description>

  <rdf:Description rdf:about="local:_00012">
    <dc:identifier rdf:resource="https://identifiers.org/pubmed:29275251"/>
    <rdfs:label>Goldberg AP, Szigeti B, Chew YH, Sekar JA, Roth YD &amp; Karr JR. Emerging whole-cell modeling principles and methods. Curr Opin Biotechnol 2018, 51:97-102.</rdfs:label>
  </rdf:Description>

    <!-- authors(s) -->
  <rdf:Description rdf:about="local:_00009">
    <foaf:accountName rdf:resource="https://orcid.org/0000-0001-8254-4958"/>
    <foaf:name>Jonathan Karr</foaf:name>

    <dc:identifier rdf:resource="https://identifiers.org/orcid:0000-0001-8254-4958"/>
    <rdfs:label>Jonathan Karr</rdfs:label>
  </rdf:Description>

  <!-- contributor(s) -->
  <rdf:Description rdf:about="local:_00010">
    <foaf:name>Name of person with no ORCID account</foaf:name>

    <rdfs:label>Name of person with no ORCID account</rdfs:label>
  </rdf:Description>

  <!-- license -->
  <rdf:Description rdf:about="local:_00013">
    <dc:identifier rdf:resource="https://identifiers.org/spdx:MIT"/>
    <rdfs:label>MIT</rdfs:label>
  </rdf:Description>

  <!-- funder -->
  <rdf:Description rdf:about="local:_00014">
    <dc:identifier rdf:resource="https://identifiers.org/doi:10.13039/100000001"/>
    <rdfs:label>National Science Foundation</rdfs:label>
  </rdf:Description>
</rdf:RDF"""
