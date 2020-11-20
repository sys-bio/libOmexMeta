import glob
import os
import libcombine
from pyomexmeta import RDF
import tellurium as te

#################################################################################################
#   Setup
#   -----
#   In this section we generate some SBML to work with.
#   To do so we use antimony and tellurium.

# The antimony model
ant = """
model MichaelisMenten
    R1: S + E => ES ; kf*S*E;
    R2: ES => S + E ; kb*ES;
    R3: ES => E + P ; kcat*ES;
    S = 100
    E = 0.5
    ES = 0
    P = 0
    kf = 0.1 
    kb = 0.01
    kcat = 0.0001
    compartment Cell = 1.0;
    S in Cell;
    E in Cell;
    ES in Cell;
    P in Cell;
end
"""

# The sbml string can be generated using tellurium
SBML_STRING = te.loada(ant).getSBML()

# This SBML String was printed out and pasted below.
# Then, metaids were added to each SBML attribute that needed them (compartment, species, parameters and reactions)

SBML_STRING = """<?xml version="1.0" encoding="UTF-8"?>
<sbml xmlns="http://www.sbml.org/sbml/level3/version1/core" level="3" version="1">
  <model metaid="MichaelisMenten" id="MichaelisMenten">
    <listOfCompartments>
      <compartment id="Cell" metaid="Cell" spatialDimensions="3" constant="true"/>
    </listOfCompartments>
    <listOfSpecies>
      <species id="S" metaid="S" compartment="Cell" initialConcentration="100" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>
      <species id="E" metaid="E" compartment="Cell" initialConcentration="0.5" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>
      <species id="ES" metaid="ES" compartment="Cell" initialConcentration="0" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>
      <species id="P" metaid="P" compartment="Cell" initialConcentration="0" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>
    </listOfSpecies>
    <listOfParameters>
      <parameter id="kf" metaid="kf" value="0.1" constant="true"/>
      <parameter id="kb" metaid="kb" value="0.01" constant="true"/>
      <parameter id="kcat" metaid="kcat" value="0.0001" constant="true"/>
    </listOfParameters>
    <listOfReactions>
      <reaction id="R1" metaid="R1" reversible="false" fast="false">
        <listOfReactants>
          <speciesReference species="S" stoichiometry="1" constant="true"/>
          <speciesReference species="E" stoichiometry="1" constant="true"/>
        </listOfReactants>
        <listOfProducts>
          <speciesReference species="ES" stoichiometry="1" constant="true"/>
        </listOfProducts>
        <kineticLaw>
          <math xmlns="http://www.w3.org/1998/Math/MathML">
            <apply>
              <times/>
              <ci> kf </ci>
              <ci> S </ci>
              <ci> E </ci>
            </apply>
          </math>
        </kineticLaw>
      </reaction>
      <reaction id="R2" metaid="R2" reversible="false" fast="false">
        <listOfReactants>
          <speciesReference species="ES" stoichiometry="1" constant="true"/>
        </listOfReactants>
        <listOfProducts>
          <speciesReference species="S" stoichiometry="1" constant="true"/>
          <speciesReference species="E" stoichiometry="1" constant="true"/>
        </listOfProducts>
        <kineticLaw>
          <math xmlns="http://www.w3.org/1998/Math/MathML">
            <apply>
              <times/>
              <ci> kb </ci>
              <ci> ES </ci>
            </apply>
          </math>
        </kineticLaw>
      </reaction>
      <reaction id="R3" metaid="R3" reversible="false" fast="false">
        <listOfReactants>
          <speciesReference species="ES" stoichiometry="1" constant="true"/>
        </listOfReactants>
        <listOfProducts>
          <speciesReference species="E" stoichiometry="1" constant="true"/>
          <speciesReference species="P" stoichiometry="1" constant="true"/>
        </listOfProducts>
        <kineticLaw>
          <math xmlns="http://www.w3.org/1998/Math/MathML">
            <apply>
              <times/>
              <ci> kcat </ci>
              <ci> ES </ci>
            </apply>
          </math>
        </kineticLaw>
      </reaction>
    </listOfReactions>
  </model>
</sbml>
"""


##########################################################################################
#   Helper functions
#   -----------------
#


def create_combine_archive(sbml, name, annotation_string=None):
    """
    Create a combine archive using libcombine. Archive will contain
    a single sbml file with the Manifest that is autocreated by libcombine.
    If annotation_string is not None, an additional annotation file will be
    stored in the combine containing annotation_string.
    Args:
        sbml: the sbml string to be put into a file
        name: Name used for archive and file in archive
        annotation_string: None or string containing the annotation for the combine archive

    Returns:

    """
    current_directory = dir_path = os.path.dirname(os.path.realpath(__file__))
    combine_archive_filename = os.path.join(current_directory, f"{name}.omex")
    archive = libcombine.CombineArchive()
    archive.addFileFromString(
        content=sbml,  # the string contining sbml
        targetName=f"{name}.sbml",  # name the content in archive
        format="sbml",  # format of this content
        isMaster=True  # boolean indicating whether the file should be opened first if there are multiple ones.
    )
    if annotation_string:
        archive.addFileFromString(
            annotation_string,
            f"{name}.rdf",
            "turtle",
            False
        )
    archive.writeToFile(combine_archive_filename)
    if not os.path.isfile(combine_archive_filename):
        raise FileNotFoundError(combine_archive_filename)

    print(f"Archive written to \"{combine_archive_filename}\"")
    return combine_archive_filename


def extract_sbml_from_combine_archive(archive_path):
    """
    Opens a combine archive and extracts sbml models as a list of strings.
    Args:
        archive_path: full path to combine archive on disk

    Returns:

    """
    if not os.path.isfile(archive_path):
        raise FileNotFoundError(archive_path)

    # read the archive using libcombine
    archive = libcombine.CombineArchive()

    # note the skipOmex flag. This is needed to expose any files with an "rdf" extension.
    archive.initializeFromArchive(archive_path, skipOmex=True)  # new in libcombine!

    # filter through the entries in the omex archive for sbml extension files
    annotation_entries = [i.c_str() for i in archive.getAllLocations() if i[-4:] == "sbml"]

    # read the rdf into a python string
    return [archive.extractEntryToString(i) for i in annotation_entries]


def extract_rdf_from_combine_archive(archive_path: str):
    """
    Opens a combine archive and extracts annotation string as a list.
    Args:
        archive_path: full path to combine archive on disk

    Returns:

    """
    if not os.path.isfile(archive_path):
        raise FileNotFoundError(archive_path)

    # read the archive using libcombine
    archive = libcombine.CombineArchive()

    # note the skipOmex flag. This is needed to expose any files with an "rdf" extension.
    archive.initializeFromArchive(archive_path, skipOmex=True)  # new in libcombine!

    # filter through the entries in the omex archive for rdf extension files
    annotation_entries = [i.c_str() for i in archive.getAllLocations() if i[-4:] == ".rdf"]

    # read the rdf into a python string
    return [archive.extractEntryToString(i) for i in annotation_entries]


#############################################################################################
#   Demonstration of OmexMeta Specification v1.1
#

class OmexMetaSpec1_1:
    """
    This class is a container around some examples of using libOmexMeta via the
    pyomexmeta python front end. Each example is self contained and has corresponding
    method calls in both C++ and C, if either of those are you language of choice.
    """

    def section2_3_4_model_level_annotations(self):
        """Example of how to create model level annotations"""
        # Create a combine archive called MichaelisMenten1.omex that contains a MichaelisMenten1.sbml file
        combine_archive_filename = create_combine_archive(SBML_STRING, name="ModelLevelAnnotations")

        # we extract the sbml from the combine archive
        sbml = extract_sbml_from_combine_archive(combine_archive_filename)

        # sbml is a list of all sbml files in archive. We know there is only 1, so get the string
        if len(sbml) != 1:
            raise ValueError("Something is wrong - you should only have 1 sbml file in the combine archive")

        sbml = sbml[0]

        # create an RDF object. Its empty.
        rdf = RDF()
        rdf.set_model_uri("ModelLevelAnnotations")

        # create an editor. Note these are the default arguments - but shown here for completeness
        editor = rdf.to_editor(sbml, generate_new_metaids=False, sbml_semantic_extraction=True)

        editor.add_creator("orcid:0000-0001-8254-4957")\
            .add_curator("orcid:0000-0001-8254-4958")\
            .add_taxon("taxon/9895")\
            .add_pubmed("pubmed/12334")\
            .add_description("My supercool model")\
            .add_date_created("18-09-2020")\
            .add_parent_model("pubmed/123456")

        fname = create_combine_archive(sbml, "ModelLevelAnnotations", str(rdf))

        return fname

    def section2_3_4_personal_information(self):
        """Example of how to use the PersonalInformation class"""
        # Create a combine archive called MichaelisMenten1.omex that contains a MichaelisMenten1.sbml file
        combine_archive_filename = create_combine_archive(SBML_STRING, name="PersonalInformation")

        # we extract the sbml from the combine archive
        sbml = extract_sbml_from_combine_archive(combine_archive_filename)

        # sbml is a list of all sbml files in archive. We know there is only 1, so get the string
        if len(sbml) != 1:
            raise ValueError("Something is wrong - you should only have 1 sbml file in the combine archive")

        sbml = sbml[0]

        # create an RDF object. Its empty.
        rdf = RDF()
        rdf.set_model_uri("PersonalInformation")

        # create an editor. Note these are the default arguments - but shown here for completeness
        editor = rdf.to_editor(sbml, generate_new_metaids=False, sbml_semantic_extraction=True)

        # Here we use a "with" block.
        # internally, the "with" block will always execute a piece of code before
        # exiting the with block. In this case, it calls "Editor.add_personal_information()"
        # so that the user cannot forget to do it.
        # Note that in C or C++, the user must remember to add a newly created annotation to the editor.
        with editor.new_personal_information() as information:
            information.add_creator("orcid:0000-0001-8254-4957") \
                .add_name("Robin hood") \
                .add_mbox("rhood@theifinthenight.com") \
                .add_account_name("stolen_goods") \
                .add_account_service_homepage("https://get-your-free-stuff-here.com")

        fname = create_combine_archive(sbml, "PersonalInformation", str(rdf))

        return fname

    def section2_3_6_singular_annotations(self):
        """Example of how to create singular annotations"""
        # Create a combine archive called MichaelisMenten1.omex that contains a MichaelisMenten1.sbml file
        combine_archive_filename = create_combine_archive(SBML_STRING, name="SingularAnnotations")

        # we extract the sbml from the combine archive
        sbml = extract_sbml_from_combine_archive(combine_archive_filename)

        # sbml is a list of all sbml files in archive. We know there is only 1, so get the string
        if len(sbml) != 1:
            raise ValueError("Something is wrong - you should only have 1 sbml file in the combine archive")

        sbml = sbml[0]

        # create an RDF object. Its empty.
        rdf = RDF()
        rdf.set_model_uri("SingularAnnotations")

        # here we turn off semantic extraction to make output clearer
        editor = rdf.to_editor(sbml, generate_new_metaids=False, sbml_semantic_extraction=False)

        with editor.new_singular_annotation() as example_using_bqbiol_pred_and_uri_resource:
            example_using_bqbiol_pred_and_uri_resource.about("S") \
                .predicate("bqbiol", "is") \
                .resource_uri("uniprot/Q15796")

        with editor.new_singular_annotation() as example_using_bqmodel_pred_and_literal_resource:
            example_using_bqmodel_pred_and_literal_resource.about("MichaelisMenten") \
                .predicate("bqmodel", "isDescribedBy") \
                .resource_literal("Anything can go here. It is a string literal.")

        # recreate the combine archive
        fname = create_combine_archive(sbml, "SingularAnnotations", str(rdf))

        return fname

    def section2_3_7_1_physical_entity(self):
        """Example of how to create physical entity type composite annotations"""
        # Create a combine archive called MichaelisMenten1.omex that contains a MichaelisMenten1.sbml file
        combine_archive_filename = create_combine_archive(SBML_STRING, name="PhysicalEntity")

        # we extract the sbml from the combine archive
        sbml = extract_sbml_from_combine_archive(combine_archive_filename)

        # sbml is a list of all sbml files in archive. We know there is only 1, so get the string
        if len(sbml) != 1:
            raise ValueError("Something is wrong - you should only have 1 sbml file in the combine archive")

        sbml = sbml[0]

        # create an RDF object. Its empty.
        rdf = RDF()
        rdf.set_model_uri("PhysicalEntity")

        # sbml semantic extraction will automatically create these physical entities for us.
        # here, we turn it off so we can create them manually
        editor = rdf.to_editor(sbml, generate_new_metaids=False, sbml_semantic_extraction=False)

        # note: the syntax "fma:fma_12345" == "fma/fma_12345"
        # OPB:OPB_00340 = concentration of chemical
        # FMA:66836 = part of cytosol
        # FMA:63877 = fibroblast
        with editor.new_physical_entity() as substrate_entity:
            substrate_entity.about("S") \
                .has_property("OPB:OPB_00340") \
                .identity("uniprot/Q15796") \
                .is_part_of("FMA:66836") \
                .is_part_of("FMA:63877")

        with editor.new_physical_entity() as product_entity:
            product_entity.about("P") \
                .has_property("OPB:OPB_00340") \
                .identity("uniprot/smad2-p") \
                .is_part_of("FMA:66836") \
                .is_part_of("FMA:63877")

        with editor.new_physical_entity() as enzyme_entity:
            enzyme_entity.about("E") \
                .has_property("OPB:OPB_00340") \
                .identity("uniprot/P37173") \
                .is_part_of("FMA:66836") \
                .is_part_of("FMA:63877")

        with editor.new_physical_entity() as complex_entity:
            complex_entity.about("ES") \
                .has_property("OPB:OPB_00340") \
                .identity("uniprot/P37173") \
                .is_part_of("FMA:66836") \
                .is_part_of("FMA:63877")

        fname = create_combine_archive(sbml, "PhysicalEntity", str(rdf))

        return fname

    def section2_3_7_2_physical_process(self):
        """Example of how to create PhysicalProcess type composite annotations"""

        # Create a combine archive called MichaelisMenten1.omex that contains a MichaelisMenten1.sbml file
        combine_archive_filename = create_combine_archive(SBML_STRING, name="PhysicalProcess")

        # we extract the sbml from the combine archive
        sbml = extract_sbml_from_combine_archive(combine_archive_filename)

        # sbml is a list of all sbml files in archive. We know there is only 1, so get the string
        if len(sbml) != 1:
            raise ValueError("Something is wrong - you should only have 1 sbml file in the combine archive")

        sbml = sbml[0]

        # create an RDF object. Its empty.
        rdf = RDF()
        rdf.set_model_uri("PhysicalProcess")

        # sbml semantic extraction will automatically create these physical entities for us.
        # here, we turn it off so we can create them manually
        editor = rdf.to_editor(sbml, generate_new_metaids=False, sbml_semantic_extraction=False)

        # physical process composite annotations use references to physical entities.
        # therefore we build on the content from OmexMetaSpec1_1.section2_3_7_1_physical_entity()

        with editor.new_physical_entity() as substrate_entity:
            substrate_entity.about("S") \
                .has_property("OPB:OPB_00340") \
                .identity("uniprot/Q15796") \
                .is_part_of("FMA:66836") \
                .is_part_of("FMA:63877")

        with editor.new_physical_entity() as product_entity:
            product_entity.about("P") \
                .has_property("OPB:OPB_00340") \
                .identity("uniprot/smad2-p") \
                .is_part_of("FMA:66836") \
                .is_part_of("FMA:63877")

        with editor.new_physical_entity() as enzyme_entity:
            enzyme_entity.about("E") \
                .has_property("OPB:OPB_00340") \
                .identity("uniprot/P37173") \
                .is_part_of("FMA:66836") \
                .is_part_of("FMA:63877")

        with editor.new_physical_entity() as complex_entity:
            complex_entity.about("ES") \
                .has_property("OPB:OPB_00340") \
                .identity("uniprot/SmadReceptorComplex") \
                .is_part_of("FMA:66836") \
                .is_part_of("FMA:63877")

        ## optionally print out xml to look at the metaids
        # print(editor.get_xml())
        # print(editor.get_metaids())

        # We now create annotations for three reactions (physical processes)
        #  that are simulated in the sbml model
        with editor.new_physical_process() as substrate_bind_enzyme:
            substrate_bind_enzyme.about("R1") \
                .has_property("OPB:OPB_00593") \
                .add_source(1.0, "EntityProperty0000") \
                .add_source(1.0, "EntityProperty0003") \
                .add_sink(1.0, "EntityProperty0000") \
                .is_version_of()

        with editor.new_physical_process() as substrate_unbind_enzyme:
            substrate_unbind_enzyme.about("R2") \
                .has_property("OPB:OPB_00593") \
                .add_sink(1.0, "EntityProperty0000") \
                .add_sink(1.0, "EntityProperty0003") \
                .add_source(1.0, "EntityProperty0000")

        with editor.new_physical_process() as product_formation:
            product_formation.about("R3") \
                .has_property("OPB:OPB_00593") \
                .add_sink(1.0, "EntityProperty0002") \
                .add_sink(1.0, "EntityProperty0001") \
                .add_source(1.0, "EntityProperty0003")

        fname = create_combine_archive(sbml, "PhysicalProcess", str(rdf))

        return fname

    def section2_3_7_3_energy_diff(self):
        """Example of how to create EnergyDiff type composite annotations"""

        # Create a combine archive called MichaelisMenten1.omex that contains a MichaelisMenten1.sbml file
        combine_archive_filename = create_combine_archive(SBML_STRING, name="EnergyDiff")

        # we extract the sbml from the combine archive
        sbml = extract_sbml_from_combine_archive(combine_archive_filename)

        # sbml is a list of all sbml files in archive. We know there is only 1, so get the string
        if len(sbml) != 1:
            raise ValueError("Something is wrong - you should only have 1 sbml file in the combine archive")

        sbml = sbml[0]

        # create an RDF object. Its empty.
        rdf = RDF()
        rdf.set_model_uri("EnergyDiff")

        # sbml semantic extraction will automatically create these physical entities for us.
        # here, we turn it off so we can create them manually
        editor = rdf.to_editor(sbml, generate_new_metaids=False, sbml_semantic_extraction=False)

        # OPB:OPB_00378 = chemical potential
        with editor.new_energy_diff() as physcial_force:
            physcial_force.about("S") \
                .has_property("OPB:OPB_00378") \
                .add_source(1.0, "EntityProperty0002") \
                .add_sink(1.0, "EntityProperty0001")

        fname = create_combine_archive(sbml, "EnergyDiff", str(rdf))

        return fname


if __name__ == "__main__":

    # when True, delete all created omex archives.
    CLEAN_UP = False

    spec_examples = OmexMetaSpec1_1()
    spec_examples.section2_3_4_model_level_annotations()
    spec_examples.section2_3_4_personal_information()
    spec_examples.section2_3_6_singular_annotations()
    spec_examples.section2_3_7_1_physical_entity()
    spec_examples.section2_3_7_2_physical_process()
    spec_examples.section2_3_7_3_energy_diff()

    directory = os.path.join(os.path.dirname(os.path.abspath(__file__)), "*.omex")
    omex_files = glob.glob(directory)

    # error if we have not created 6 omex files.
    # When this script runs without error, we assume we've passed.
    if len(omex_files) != 6:
        raise FileNotFoundError("Something has gone wrong. You should have 6 omex files")

    if CLEAN_UP:
        # prevents cluttering of the repository.
        [os.remove(i) for i in omex_files]
