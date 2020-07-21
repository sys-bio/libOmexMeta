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

with rdf.to_editor(sbml, "sbml", generate_new_metaids=True) as editor:
    sbml_with_metaids = editor.get_xml()
    print(sbml_with_metaids)

    # Physical Entity 1
    # volume of blood in heart
    with editor.new_physical_entity() as lhs:
        lhs.set_physical_property("#OmexMetaId0001", "OPB:OPB_01551") \
            .set_identity("FMA:9670") \
            .set_location("FMA:7088")

    # Physical Entity 2
    # volume of blood in lung
    with editor.new_physical_entity() as rhs:
        rhs.set_physical_property("#OmexMetaId0002", "OPB:OPB_01551") \
            .set_identity("FMA:9670") \
            .set_location("FMA:7195")

    # Property: Osmotic Pressure
    with editor.new_physical_force() as physical_force:
        physical_force \
            .set_physical_property("#OmexMetaId0005", "PB:OPB_01012") \
            .add_source(multiplier=1, physical_entity_reference="#OmexMetaId0001") \
            .add_sink(multiplier=1, physical_entity_reference="#OmexMetaId0002") \

print(rdf)

