from pyomexmeta import RDF

# create an empty RDF object
rdf = RDF()

editor = rdf.to_editor("models/ComplexBinding.sbml", generate_new_metaids=True, sbml_semantic_extraction=False)

sbml_with_metaids = editor.get_xml()
print(sbml_with_metaids)

# Remember that in Python, the with block takes care of adding the annotation to our RDF graph
# so that its not possible to forget.
# Annotate the Shc entity
with editor.new_physical_entity() as Shc:
    Shc \
        .about("Shc") \
        .has_property("OPB:OPB_00340") \
        .identity("uniprot/P29353")

    # We could optionally annot
    # ate where we are modelling Shc, for instance nucleus, cytoplasm, skin, bone, etc. Here
    # we do not need to since we are only modelling reactions in the cytoplasm.

# Annotate the Sos entity
with editor.new_physical_entity() as Sos:
    Sos \
        .about("Sos") \
        .has_property("OPB:OPB_00340") \
        .identity("uniprot/Q07889")

# Annotate the Grb2 entity
with editor.new_physical_entity() as Grb2:
    Grb2 \
        .about("Grb2") \
        .has_property("OPB:OPB_00340") \
        .identity("uniprot/P62993")


# Annotate the shc_sos_grb2 entity
with editor.new_physical_entity() as shc_sos_grb2:
    shc_sos_grb2 \
        .about("Shc_Sos_Grb2") \
        .has_property("OPB:OPB_00340") \
        .has_part("uniprot/P29353") \
        .has_part("uniprot/Q07889") \
        .has_part("uniprot/P62993")

# annotate the binding reaction
with editor.new_physical_process() as binding_reaction:
    binding_reaction.about("Binding") \
            .has_property("OPB:OPB_00340") \
            .add_source(1, "Shc") \
            .add_source(1, "Grb2") \
            .add_source(1, "Sos") \
            .add_sink(1, "Shc_Sos_Grb2")

# annotate the unbinding reaction
with editor.new_physical_process() as unbinding_reaction:
    unbinding_reaction.about("Unbinding") \
            .has_property("OPB:OPB_00340") \
            .add_source(1, "Shc_Sos_Grb2") \
            .add_sink(1, "Shc") \
            .add_sink(1, "Grb2") \
            .add_sink(1, "Sos")

print(rdf)


