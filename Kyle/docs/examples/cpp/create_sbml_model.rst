Create & Annotate An SBML Model
===============================

.. literalinclude:: ../../../examples/cpp/create_sbml_model.cpp
   :language: c++
   :emphasize-lines: 1,92,93,100,112,113,116-119,125,132,134
   :linenos:

Expected Output
---------------

.. highlight:: none

::

  **********************************************************
  SBML output:
  **********************************************************

  <?xml version="1.0" encoding="UTF-8"?>
  <sbml xmlns="http://www.sbml.org/sbml/level3/version2/core" level="3" version="2">
    <model id="beta_cell_model">
      <listOfUnitDefinitions>
        <unitDefinition id="molar">
          <listOfUnits>
            <unit kind="mole" exponent="1" scale="1" multiplier="1"/>
            <unit kind="litre" exponent="-1" scale="1" multiplier="1"/>
          </listOfUnits>
        </unitDefinition>
      </listOfUnitDefinitions>
      <listOfCompartments>
        <compartment metaid="cytosol" id="cytosol" size="1" constant="true">
          <annotation>
            <rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:vCard="http://www.w3.org/2001/vcard-rdf/3.0#" xmlns:vCard4="http://www.w3.org/2006/vcard/ns#" xmlns:bqbiol="http://biomodels.net/biology-qualifiers/" xmlns:bqmodel="http://biomodels.net/model-qualifiers/">
              <rdf:Description rdf:about="#cytosol">
                <bqbiol:is>
                  <rdf:Bag>
                    <rdf:li rdf:resource="https://identifiers.org/GO:0005829"/>
                  </rdf:Bag>
                </bqbiol:is>
              </rdf:Description>
            </rdf:RDF>
          </annotation>
        </compartment>
      </listOfCompartments>
      <listOfSpecies>
        <species metaid="glucose" id="glucose" compartment="cytosol" initialConcentration="0" substanceUnits="molar" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false">
          <annotation>
            <rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:vCard="http://www.w3.org/2001/vcard-rdf/3.0#" xmlns:vCard4="http://www.w3.org/2006/vcard/ns#" xmlns:bqbiol="http://biomodels.net/biology-qualifiers/" xmlns:bqmodel="http://biomodels.net/model-qualifiers/">
              <rdf:Description rdf:about="#glucose">
                <bqbiol:is>
                  <rdf:Bag>
                    <rdf:li rdf:resource="http://identifiers.org/CHEBI:17234"/>
                  </rdf:Bag>
                </bqbiol:is>
              </rdf:Description>
            </rdf:RDF>
          </annotation>
        </species>
      </listOfSpecies>
      <listOfReactions>
        <reaction id="glucose_import" reversible="false">
          <listOfProducts>
            <speciesReference species="glucose" constant="false"/>
          </listOfProducts>
          <kineticLaw>
            <math xmlns="http://www.w3.org/1998/Math/MathML">
              <ci> glucose_import_rate </ci>
            </math>
            <listOfLocalParameters>
              <localParameter id="glucose_import_rate" value="1"/>
            </listOfLocalParameters>
          </kineticLaw>
        </reaction>
      </listOfReactions>
    </model>
  </sbml>

  **********************************************************
  RDF serialization of annotations:
  **********************************************************

  @prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
  @prefix bqb: <http://biomodels.net/biology-qualifiers/> .

  <#glucose_entity>
      bqb:is <http://identifiers.org/CHEBI:17234> ;
      bqb:occursIn <./mymodel#cytosol> .

  <./mymodel#cytosol>
      bqb:is <https://identifiers.org/GO:0005829> .

  <./mymodel#glucose>
      bqb:is <http://identifiers.org/opb/OPB_00425> ;
      bqb:isPropertyOf <#glucose_entity> .


  **********************************************************
  RDF serialization with cell type annotation:
  **********************************************************

  @prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
  @prefix bqb: <http://biomodels.net/biology-qualifiers/> .

  <#cytosol_entity>
      bqb:is <https://identifiers.org/GO:0005829> ;
      bqb:isPartOf <#cytosol_entity_term1> .

  <#cytosol_entity_term1>
      bqb:is <https://identifiers.org/CL:0000169> .

  <#glucose_entity>
      bqb:is <http://identifiers.org/CHEBI:17234> ;
      bqb:occursIn <./mymodel#cytosol> .

  <./mymodel#cytosol>
      bqb:is <http://identifiers.org/opb/OPB_00523> ;
      bqb:isPropertyOf <#cytosol_entity> .

  <./mymodel#glucose>
      bqb:is <http://identifiers.org/opb/OPB_00425> ;
      bqb:isPropertyOf <#glucose_entity> .

  **********************************************************
  Humanized version of the annotation information
  (ontology terms replaced by human-readable names):
  **********************************************************

  OPB:spatial volume -> (isPropertyOf) -> #cytosol -> (is) -> GO:cytoplasm -> (isPartOf) -> CL:type B pancreatic cell
  OPB:chemical concentration -> (isPropertyOf) -> #glucose -> (is) -> CHEBI:glucose -> (occursIn) -> #cytosol
