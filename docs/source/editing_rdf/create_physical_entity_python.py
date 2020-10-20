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

with editor.new_physical_entity() as physical_entity:
    physical_entity \
        .set_about("#OmexMetaId0001") \
        .has_property("OPB:OPB_00340") \
        .identity("uniprot/P84022") \
        .add_location("fma/FMA:63877") \
        .add_location("fma:FMA:70737") \
        .add_location("fma/FMA:24178") \
        .add_location("fma/FMA_7163")


print(rdf)


