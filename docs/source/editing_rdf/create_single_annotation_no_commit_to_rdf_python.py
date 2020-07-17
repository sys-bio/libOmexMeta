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

with rdf.to_editor(sbml, "sbml", generate_new_metaids=True) as editor:
    with editor.new_singular_annotation() as singular_annotation:
        singular_annotation \
            .set_about('#OmexMetaId0002') \
            .set_predicate("bqbiol", "is") \
            .set_resource_uri("uniprot/P01137")

        # In python, the singular annotation gets committed to the model
        # automatically after the current context manager looses scope (i.e.
        # at the end of the current with block). But serializing (printing)
        # here does so without adding to the current RDF graph.
        # This features makes more sense in C/C++
        print(singular_annotation)
