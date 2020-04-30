Create & Annotate An SBML Model
===============================

.. literalinclude:: ../../../examples/python/create_sbml_model.py
   :language: python
   :emphasize-lines: 53,54,58,60,70,82-83,87-90,99,106,108
   :linenos:

Expected Output
---------------

.. highlight:: none

::

  **********************************************************
  SBML output:
  **********************************************************
  <?xml version="1.0" encoding="UTF-8"?>
  <!-- Created by libAntimony version v2.11.0 with libSBML version 5.17.1. -->
  <sbml xmlns="http://www.sbml.org/sbml/level3/version1/core" level="3" version="1">
    <model metaid="beta_cell_model" id="beta_cell_model">
      <listOfUnitDefinitions>
        <unitDefinition id="molar_per_volume">
          <listOfUnits>
            <unit kind="mole" exponent="1" scale="1" multiplier="1"/>
            <unit kind="litre" exponent="-1" scale="1" multiplier="1"/>
            <unit kind="litre" exponent="-1" scale="0" multiplier="1"/>
          </listOfUnits>
        </unitDefinition>
        <unitDefinition id="molar">
          <listOfUnits>
            <unit kind="mole" exponent="1" scale="1" multiplier="1"/>
            <unit kind="litre" exponent="-1" scale="1" multiplier="1"/>
          </listOfUnits>
        </unitDefinition>
      </listOfUnitDefinitions>
      <listOfCompartments>
        <compartment metaid="beta_cell_model.cytosol" id="cytosol" spatialDimensions="3" size="1" constant="true">
          <annotation>
            <rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:vCard="http://www.w3.org/2001/vcard-rdf/3.0#" xmlns:vCard4="http://www.w3.org/2006/vcard/ns#" xmlns:bqbiol="http://biomodels.net/biology-qualifiers/" xmlns:bqmodel="http://biomodels.net/model-qualifiers/">
              <rdf:Description rdf:about="#beta_cell_model.cytosol">
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
        <species metaid="beta_cell_model.glucose" id="glucose" compartment="cytosol" initialConcentration="0" substanceUnits="molar" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false">
          <annotation>
            <rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#" xmlns:dcterms="http://purl.org/dc/terms/" xmlns:vCard="http://www.w3.org/2001/vcard-rdf/3.0#" xmlns:vCard4="http://www.w3.org/2006/vcard/ns#" xmlns:bqbiol="http://biomodels.net/biology-qualifiers/" xmlns:bqmodel="http://biomodels.net/model-qualifiers/">
              <rdf:Description rdf:about="#beta_cell_model.glucose">
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
      <listOfParameters>
        <parameter id="glucose_import_glucose_import_rate" value="1" constant="true"/>
      </listOfParameters>
      <listOfReactions>
        <reaction id="glucose_import" reversible="false" fast="false">
          <listOfProducts>
            <speciesReference species="glucose" stoichiometry="1" constant="true"/>
          </listOfProducts>
          <kineticLaw>
            <math xmlns="http://www.w3.org/1998/Math/MathML">
              <ci> glucose_import_glucose_import_rate </ci>
            </math>
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

  <#beta_cell_model.glucose_entity>
      bqb:is <http://identifiers.org/CHEBI:17234> ;
      bqb:occursIn <./my-sbml-file.xml#beta_cell_model.cytosol> .

  <./my-sbml-file.xml#beta_cell_model.cytosol>
      bqb:is <https://identifiers.org/GO:0005829> .

  <./my-sbml-file.xml#beta_cell_model.glucose>
      bqb:is <http://identifiers.org/opb/OPB_00425> ;
      bqb:isPropertyOf <#beta_cell_model.glucose_entity> .


  **********************************************************
  RDF serialization with cell type annotation:
  **********************************************************

  @prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
  @prefix bqb: <http://biomodels.net/biology-qualifiers/> .

  <#beta_cell_model.cytosol_entity>
      bqb:is <https://identifiers.org/GO:0005829> ;
      bqb:isPartOf <#beta_cell_model.cytosol_entity_term1> .

  <#beta_cell_model.cytosol_entity_term1>
      bqb:is <https://identifiers.org/CL:0000169> .

  <#beta_cell_model.glucose_entity>
      bqb:is <http://identifiers.org/CHEBI:17234> ;
      bqb:occursIn <./my-sbml-file.xml#beta_cell_model.cytosol> .

  <./my-sbml-file.xml#beta_cell_model.cytosol>
      bqb:is <http://identifiers.org/opb/OPB_00523> ;
      bqb:isPropertyOf <#beta_cell_model.cytosol_entity> .

  <./my-sbml-file.xml#beta_cell_model.glucose>
      bqb:is <http://identifiers.org/opb/OPB_00425> ;
      bqb:isPropertyOf <#beta_cell_model.glucose_entity> .

  **********************************************************
  Humanized version of the annotation information
  (ontology terms replaced by human-readable names):
  **********************************************************

  OPB:spatial volume -> (isPropertyOf) -> #beta_cell_model.cytosol -> (is) -> GO:cytoplasm -> (isPartOf) -> CL:type B pancreatic cell
  OPB:chemical concentration -> (isPropertyOf) -> #beta_cell_model.glucose -> (is) -> CHEBI:glucose -> (occursIn) -> #beta_cell_model.cytosol
