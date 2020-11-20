import tellurium as te
from pyomexmeta import RDF

antimony_string = """
model SimpleRegulation
    compartment cell = 1;
    S in cell;
    A in cell;
    B in cell;
    C in cell;
    D in cell;

    S = 0;
    A = 10;
    B = 0; 
    C = 10;
    D = 0;

    k1 = 0.1;
    k2 = 0.1;
    k3 = 0.1;
    k4 = 0.1;

    R1: A => B; k1*A*S;
    R2: B => A; k2*B;
    R3: C => D; k3*C*B;
    R4: D => C; k4*D;

end
"""

sbml = te.antimonyToSBML(antimony_string)

# create an empty RDF object
rdf = RDF()

editor = rdf.to_editor(sbml, generate_new_metaids=True, sbml_semantic_extraction=False)


sbml_with_metaids = editor.get_xml()
print(sbml_with_metaids)

# Property: Osmotic Pressure
with editor.new_energy_diff() as energy_diff:
    energy_diff \
        .about("#OmexMetaId0005") \
        .has_property("OPB:OPB_01012") \
        .add_source(multiplier=1, physical_entity_reference="#OmexMetaId0001") \
        .add_sink(multiplier=1, physical_entity_reference="#OmexMetaId0002")

print(rdf)

