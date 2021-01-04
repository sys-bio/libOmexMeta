from pyomexmeta import RDF, eUriType

sbml = """<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<sbml xmlns=\"http://www.sbml.org/sbml/level3/version1/core\" level=\"3\" version=\"1\">
  <model metaid=\"EnergyDiff\" id=\"EnergyDiff\">
    <listOfCompartments>
      <compartment id=\"cytoplasm\" metaid=\"cytoplasm\" spatialDimensions=\"3\" size=\"1\" constant=\"true\"/>
      <compartment id=\"extracellular\" metaid=\"extracellular\" spatialDimensions=\"3\" size=\"1\" constant=\"true\"/>
    </listOfCompartments>
    <listOfSpecies>
      <species id=\"Ca_ex\" metaid=\"Ca_ex\" compartment=\"extracellular\" initialConcentration=\"1\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>
      <species id=\"Ca_cyt\" metaid=\"Ca_cyt\" compartment=\"cytoplasm\" initialConcentration=\"0.3\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>
    </listOfSpecies>
    <listOfParameters>
      <parameter id=\"k1\" metaid=\"k1\" value=\"0.1\" constant=\"true\"/>
      <parameter id=\"k2\" metaid=\"k2\" value=\"0.1\" constant=\"true\"/>
      <parameter id=\"N_Ca\" metaid=\"NernstPotential\"/>
    </listOfParameters>
    <listOfReactions>
      <reaction id=\"NernstReversalPotential_in\" metaid=\"NernstReversalPotential_in\" reversible=\"false\" fast=\"false\">
        <listOfReactants>
          <speciesReference species=\"Ca_ex\" stoichiometry=\"1\" constant=\"true\"/>
        </listOfReactants>
        <listOfProducts>
          <speciesReference species=\"Ca_cyt\" stoichiometry=\"1\" constant=\"true\"/>
        </listOfProducts>
        <kineticLaw>
          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">
            <apply>
              <times/>
              <ci> cytoplasm </ci>
              <ci> k1 </ci>
              <ci> Ca_ex </ci>
            </apply>
          </math>
        </kineticLaw>
      </reaction>
      <reaction id=\"NernstReversalPotential_out\" metaid=\"NernstReversalPotential_out\" reversible=\"false\" fast=\"false\">
        <listOfReactants>
          <speciesReference species=\"Ca_cyt\" stoichiometry=\"1\" constant=\"true\"/>
        </listOfReactants>
        <listOfProducts>
          <speciesReference species=\"Ca_ex\" stoichiometry=\"1\" constant=\"true\"/>
        </listOfProducts>
        <kineticLaw>
          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">
            <apply>
              <times/>
              <ci> extracellular </ci>
              <ci> k2 </ci>
              <ci> Ca_cyt </ci>
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

# Property: Osmotic Pressure
with editor.new_energy_diff() as energy_diff:
    # about(): this could be named anything provided it is unique to the rdf graph because it is a LOCAL_URI
    energy_diff.about(about="MembranePotential", uri_type=eUriType.LOCAL_URI)
    energy_diff.add_source(physical_entity_reference="Ca_ex", uri_type=eUriType.MODEL_URI)
    energy_diff.add_sink(physical_entity_reference="Ca_cyt",uri_type= eUriType.MODEL_URI)
    # for energy differentials we use the full signature of hasProperty.
    # The arguments are as follows:
    #  - NernstPotential: the "about" value that is used for the property associated with the energy differential
    #  - MODEL_URI: the uri type for the previous argument. In SBML this is a <parameter> and therefore a MODEL_URI
    #      while in CellML this is a construct local to the rdf document (so LOCAL_URI)
    #  - OPB:OPB_01581: the OPB term associated with the property (isVersionOf)
    energy_diff.has_property(property_about="NernstPotential", about_uri_type=eUriType.MODEL_URI, is_version_of="OPB:OPB_01581")

print(rdf)

