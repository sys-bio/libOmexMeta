from pyomexmeta import RDF, SingularAnnotation

sbml = """<?xml version="1.0" encoding="UTF-8"?>
<!-- Created by libAntimony version v2.12.0 with libSBML version 5.18.1. -->
<sbml xmlns="http://www.sbml.org/sbml/level3/version1/core" level="3" version="1">
  <model metaid="ToyModel" id="ToyModel">
    <listOfCompartments>
      <compartment id="cytosol" spatialDimensions="3" size="1" constant="true"/>
    </listOfCompartments>
    <listOfSpecies>
      <species id="A" compartment="cytosol" initialConcentration="10" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>
      <species id="B" compartment="cytosol" initialConcentration="0" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>
    </listOfSpecies>
    <listOfParameters>
      <parameter id="k1" value="0.1" constant="true"/>
      <parameter id="k2" value="0.1" constant="true"/>
    </listOfParameters>
    <listOfReactions>
      <reaction id="r1" reversible="false" fast="false">
        <listOfReactants>
          <speciesReference species="B" stoichiometry="1" constant="true"/>
        </listOfReactants>
        <listOfProducts>
          <speciesReference species="A" stoichiometry="1" constant="true"/>
        </listOfProducts>
        <kineticLaw>
          <math xmlns="http://www.w3.org/1998/Math/MathML">
            <apply>
              <times/>
              <ci> k2 </ci>
              <ci> B </ci>
            </apply>
          </math>
        </kineticLaw>
      </reaction>
    </listOfReactions>
  </model>
</sbml>"""

# create an empty RDF object
rdf = RDF()

editor = rdf.to_editor(sbml, generate_new_metaids=True)
with editor.new_singular_annotation() as literal:
    literal \
        .about('ToyModel') \
        .predicate("dc", "description") \
        .resource_literal("This is a toy model for demonstration purposes")

with editor.new_singular_annotation() as blank:
    blank \
        .about('#OmexMetaId0001') \
        .predicate("dc", "description") \
        .resource_blank("BankIdentifier")

# The `uniprot/PD1234` gets resolved to https://identifier.org/uniprot/PD12345
with editor.new_singular_annotation() as uri:
    uri \
        .about('#OmexMetaId0002') \
        .predicate("bqbiol", "is") \
        .resource_uri("uniprot/PD1234")

# In fact, this can be string with a format string1/string2
with editor.new_singular_annotation() as uri:
    uri \
        .about('#OmexMetaId0003') \
        .predicate("bqbiol", "is") \
        .resource_uri("string1/string2")

# Colons work too
with editor.new_singular_annotation() as uri:
    uri \
        .about('#OmexMetaId0004') \
        .predicate("bqbiol", "is") \
        .resource_uri("FMA:75132")

print(len(rdf))
print(rdf)