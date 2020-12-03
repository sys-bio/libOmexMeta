from pyomexmeta import RDF, eUriType
import os


sbml = """<?xml version="1.1" encoding="UTF-8"?>
<sbml xmlns="http://www.sbml.org/sbml/level3/version1/core" level="3" version="1">
  <model metaid="ComplexBinding" id="ComplexBinding">
    <listOfCompartments>
      <compartment id="cytoplasm" spatialDimensions="3" size="1" constant="true"/>
    </listOfCompartments>
    <listOfSpecies>
      <species id="Shc"  metaid="Shc" compartment="cytoplasm" initialConcentration="1" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>
      <species id="Sos"  metaid="Sos" compartment="cytoplasm" initialConcentration="1" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>
      <species id="Grb2" metaid="Grb2" compartment="cytoplasm" initialConcentration="1" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>
      <species id="Shc_Sos_Grb2" metaid="Shc_Sos_Grb2" compartment="cytoplasm" initialConcentration="0" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>
    </listOfSpecies>
    <listOfParameters>
      <parameter id="k_bind" metaid="k_bind" value="0.1" constant="true"/>
      <parameter id="k_unbind" metaid="k_unbind" value="0.1" constant="true"/>
    </listOfParameters>
    <listOfReactions>
      <reaction id="Binding" metaid="Binding" reversible="false" fast="false">
        <listOfReactants>
          <speciesReference species="Shc" stoichiometry="1" constant="true"/>
          <speciesReference species="Sos" stoichiometry="1" constant="true"/>
          <speciesReference species="Grb2" stoichiometry="1" constant="true"/>
        </listOfReactants>
        <listOfProducts>
          <speciesReference species="Shc_Sos_Grb2" stoichiometry="1" constant="true"/>
        </listOfProducts>
        <kineticLaw>
          <math xmlns="http://www.w3.org/1998/Math/MathML">
            <apply>
              <times/>
              <ci> cytoplasm </ci>
              <ci> k_bind </ci>
              <ci> Shc </ci>
              <ci> Sos </ci>
              <ci> Grb2 </ci>
            </apply>
          </math>
        </kineticLaw>
      </reaction>
      <reaction id="Unbinding" metaid="Unbinding" reversible="false" fast="false">
        <listOfReactants>
          <speciesReference species="Shc_Sos_Grb2" stoichiometry="1" constant="true"/>
        </listOfReactants>
        <listOfProducts>
          <speciesReference species="Shc" stoichiometry="1" constant="true"/>
          <speciesReference species="Sos" stoichiometry="1" constant="true"/>
          <speciesReference species="Grb2" stoichiometry="1" constant="true"/>
        </listOfProducts>
        <kineticLaw>
          <math xmlns="http://www.w3.org/1998/Math/MathML">
            <apply>
              <times/>
              <ci> cytoplasm </ci>
              <ci> k_unbind </ci>
              <ci> Shc_Sos_Grb2 </ci>
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

# Remember that in Python, the with block takes care of adding the annotation to our RDF graph
# so that its not possible to forget.
# Annotate the Shc entity
with editor.new_physical_entity() as Shc:
    Shc \
        .about("Shc", eUriType.MODEL_URI) \
        .has_property("OPB:OPB_00340") \
        .identity("uniprot/P29353")

    # We could optionally annot
    # ate where we are modelling Shc, for instance nucleus, cytoplasm, skin, bone, etc. Here
    # we do not need to since we are only modelling reactions in the cytoplasm.

# Annotate the Sos entity
with editor.new_physical_entity() as Sos:
    Sos \
        .about("Sos", eUriType.MODEL_URI) \
        .has_property("OPB:OPB_00340") \
        .identity("uniprot/Q07889")

# Annotate the Grb2 entity
with editor.new_physical_entity() as Grb2:
    Grb2 \
        .about("Grb2", eUriType.MODEL_URI) \
        .has_property("OPB:OPB_00340") \
        .identity("uniprot/P62993")


# Annotate the shc_sos_grb2 entity
with editor.new_physical_entity() as shc_sos_grb2:
    shc_sos_grb2 \
        .about("Shc_Sos_Grb2", eUriType.MODEL_URI) \
        .has_property("OPB:OPB_00340") \
        .has_part("uniprot/P29353") \
        .has_part("uniprot/Q07889") \
        .has_part("uniprot/P62993")

# annotate the binding reaction
with editor.new_physical_process() as binding_reaction:
    binding_reaction.about("Binding", eUriType.MODEL_URI) \
            .has_property("OPB:OPB_00340") \
            .add_source("Shc", eUriType.MODEL_URI, 1.0) \
            .add_source("Grb2", eUriType.MODEL_URI, 1.0) \
            .add_source("Sos", eUriType.MODEL_URI, 1.0) \
            .add_sink("Shc_Sos_Grb2", eUriType.MODEL_URI, 1.0)

# annotate the unbinding reaction
with editor.new_physical_process() as unbinding_reaction:
    unbinding_reaction.about("Unbinding", eUriType.MODEL_URI) \
            .has_property("OPB:OPB_00340") \
            .add_source("Shc_Sos_Grb2", eUriType.MODEL_URI, 1.0) \
            .add_sink("Shc", eUriType.MODEL_URI, 1.0) \
            .add_sink("Grb2", eUriType.MODEL_URI, 1.0) \
            .add_sink("Sos", eUriType.MODEL_URI, 1.0)

print(rdf)


