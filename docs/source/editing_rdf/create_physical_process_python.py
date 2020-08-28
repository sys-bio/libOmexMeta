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

with rdf.to_editor(sbml, generate_new_metaids=True) as editor:
    sbml_with_metaids = editor.get_xml()
    print(sbml_with_metaids)


    # Physical Entity: smad3
    with editor.new_physical_entity() as smad3:
        smad3 \
            .set_physical_property("#OmexMetaId0001", "OPB:OPB_00340") \
            .set_identity("uniprot/P84022") \
            .add_location("fma/FMA:63877") \
            .add_location("fma:FMA:70737") \
            .add_location("fma/FMA:24178") \
            .add_location("fma/FMA_7163")

    # Physical Entity: psmad3
    with editor.new_physical_entity() as psmad3:
        psmad3 \
            .set_physical_property("#OmexMetaId0002", "OPB:OPB_00340") \
            .set_identity("uniprot/P84022") \
            .add_location("fma/FMA:63877") \
            .add_location("fma:FMA:70737") \
            .add_location("fma/FMA:24178") \
            .add_location("fma/FMA_7163")

    # Physical Entity 1
    with editor.new_physical_entity() as lhs:
        lhs.set_physical_property("#OmexMetaId0002", "OPB:OPB_00340") \
            .set_identity("P84022") \
            .set_location("FMA:7195")

    # annotate reaction #OmexMetaId0011 as the chemical concentration
    # flow rate OPB:OPB_00593 of Smad3 to phosphorylated smad3
    with editor.new_physical_process() as physical_process:
        physical_process \
            .set_physical_property("#OmexMetaId0005", "OPB:OPB_00593") \
            .add_source(multiplier=1, physical_entity_reference="#OmexMetaID0001") \
            .add_sink(multiplier=1, physical_entity_reference="#OmexMetaID0002") \
            .add_mediator(multiplier=1, physical_entity_reference="#OmexMetaID0003")


print(rdf)

