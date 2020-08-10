import os
import site
import typing
import unittest
import libcombine
import requests
import zipfile
from sys import platform
# import matplotlib as mpl
# mpl.use('TkAgg', warn=False)

test_dir = os.path.dirname(os.path.dirname(os.path.realpath(__file__)))
proj_dir = os.path.dirname(test_dir)
src_dir = os.path.join(proj_dir, "src")
pysemsem_dir = os.path.join(src_dir, "pyomexmeta")

site.addsitedir(src_dir)

# module not found by IDE, but it does exist and and tests do run
from pyomexmeta import *

try:
    import tellurium as te
except ImportError:
    raise ImportError("package \"tellurium\" not found. Please `pip install tellurium`")

XML = """<?xml version="1.0" encoding="UTF-8"?>
<sbml xmlns="http://www.sbml.org/sbml/level3/version2/core" level="3" version="2">
  <model id="TestModelNotAnnotated">
    <listOfUnitDefinitions>
      <unitDefinition id="molar">
        <listOfUnits>
          <unit kind="mole" exponent="1" scale="1" multiplier="1"/>
          <unit kind="litre" exponent="-1" scale="1" multiplier="1"/>
        </listOfUnits>
      </unitDefinition>
    </listOfUnitDefinitions>
    <listOfCompartments>
      <compartment metaid="cytosol" id="cytosol" size="1" constant="true"/>
    </listOfCompartments>
    <listOfSpecies>
      <species metaid="Meta00001" id="X" compartment="cytosol" initialConcentration="10" substanceUnits="molar" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>
      <species id="Y" compartment="cytosol" initialConcentration="20" substanceUnits="molar" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>
      <species id="Y" compartment="cytosol" initialConcentration="15" substanceUnits="molar" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>
    </listOfSpecies>
    <listOfReactions>
      <reaction id="X2Y" reversible="false">
        <listOfProducts>
          <speciesReference species="Y" constant="false"/>
        </listOfProducts>
        <kineticLaw>
          <math xmlns="http://www.w3.org/1998/Math/MathML">
            <apply>
              <times/>
              <ci> x </ci>
              <ci> kx2y </ci>
            </apply>
          </math>
          <listOfLocalParameters>
            <localParameter id="kx2y" value="1"/>
            <localParameter id="ky2z" value="1"/>
          </listOfLocalParameters>
        </kineticLaw>
      </reaction>
      <reaction id="y2z" reversible="false">
        <listOfProducts>
          <speciesReference species="Z" constant="false"/>
        </listOfProducts>
        <kineticLaw>
          <math xmlns="http://www.w3.org/1998/Math/MathML">
            <apply>
              <times/>
              <ci> y </ci>
              <ci> ky2z </ci>
            </apply>
          </math>
        </kineticLaw>
      </reaction>
    </listOfReactions>
  </model>
</sbml>"""


class TestRDF(unittest.TestCase):
    rdf_str = """<?xml version="1.0" encoding="utf-8"?>
    <rdf:RDF xmlns:bqbiol="http://biomodels.net/biology-qualifiers/"
       xmlns:bqmodel="http://biomodels.net/model-qualifiers/"
       xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"
       xmlns:semsim="http://www.bhi.washington.edu/semsim#">
      <rdf:Description rdf:about="http://omex-library.org/NewOmex.omex/NewModel.rdf#force_0">
        <semsim:hasSinkParticipant rdf:resource="http://omex-library.org/NewOmex.omex/NewModel.rdf#sink_0"/>
        <semsim:hasSourceParticipant rdf:resource="http://omex-library.org/NewOmex.omex/NewModel.rdf#source_0"/>
      </rdf:Description>
      <rdf:Description rdf:about="http://omex-library.org/NewOmex.omex/NewModel.rdf#parameter_metaid_0">
        <bqbiol:isPropertyOf rdf:resource="http://omex-library.org/NewOmex.omex/NewModel.rdf#force_0"/>
        <bqbiol:isVersionOf rdf:resource="https://identifiers.org/opb/OPB_01058"/>
      </rdf:Description>
      <rdf:Description rdf:about="http://omex-library.org/NewOmex.omex/NewModel.rdf#sink_0">
        <semsim:hasPhysicalEntityReference rdf:resource="http://omex-library.org/NewOmex.omex/NewModel.rdf#species_metaid_1"/>
      </rdf:Description>
      <rdf:Description rdf:about="http://omex-library.org/NewOmex.omex/NewModel.rdf#source_0">
        <semsim:hasPhysicalEntityReference rdf:resource="http://omex-library.org/NewOmex.omex/NewModel.rdf#species_metaid_0"/>
      </rdf:Description>
    </rdf:RDF>"""

    sbml_uri = "https://www.ebi.ac.uk/biomodels/model/download/BIOMD0000000064.2?filename=BIOMD0000000064_url.xml";

    sbml_file = os.path.join(os.getcwd(), "sbml_file_for_tests.sbml")

    def setUp(self) -> None:
        with open(self.sbml_file, "w") as f:
            f.write(self.rdf_str)

    def tearDown(self) -> None:
        teardown = True
        if teardown:
            if os.path.isfile(self.sbml_file):
                os.remove(self.sbml_file)

    def test_crete_new_rdf_obj(self):
        rdf = RDF()
        self.assertIsInstance(rdf._obj, int)

    def test_from_string(self):
        rdf = RDF.from_string(self.rdf_str, "rdfxml")
        print(rdf)
        self.assertEqual(6, len(rdf))

    def test_from_string_for_docs(self):
        rdf_str = """
@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
@prefix myOMEXlib: <http://omex-library.org/> .
@prefix myOMEX: <http://omex-library.org/NewOmex.omex> .
@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .
<http://omex-library.org/NewOmex.omex/NewModel.xml#>
<http://purl.org/dc/terms/creator> <https://orchid.org/1234-1234-1234-1234> .
"""
        rdf = RDF.from_string(rdf_str, format="turtle")
        self.assertEqual(1, len(rdf))


    def test_add_from_string(self):
        rdf = RDF()
        RDF.add_from_string(rdf, self.rdf_str, "rdfxml", "test_add_from_string.rdf")
        self.assertEqual(6, len(rdf))

    def test_from_uri(self):
        rdf = RDF.from_uri(self.sbml_uri, "rdfxml")
        self.assertEqual(277, len(rdf))

    def test_add_from_uri(self):
        rdf = RDF()
        RDF.add_from_uri(rdf, self.sbml_uri, "rdfxml")
        self.assertEqual(277, len(rdf))

    def test_from_file(self):
        rdf = RDF.from_file(self.sbml_file, "rdfxml")
        self.assertEqual(6, len(rdf))

    def test_add_from_file(self):
        rdf = RDF()
        RDF.add_from_file(rdf, self.sbml_file, "rdfxml")
        self.assertEqual(6, len(rdf))

    def test_set_repository_uri(self):
        rdf = RDF()
        rdf.set_repository_uri("https://my-awesome-repository.org")
        actual = rdf.get_repository_uri()
        expected = "https://my-awesome-repository.org/"
        self.assertEqual(expected, actual)

    def test_set_archive_uri(self):
        rdf = RDF()
        rdf.set_archive_uri("my-awesome-archive.omex")
        actual = rdf.get_archive_uri()
        expected = "http://omex-library.org/my-awesome-archive.omex"
        self.assertEqual(expected, actual)

    def test_set_model_uri(self):
        rdf = RDF()
        rdf.set_model_uri("my-awesome-model.xml")
        actual = rdf.get_model_uri()
        expected = "http://omex-library.org/NewOmex.omex/my-awesome-model.xml#"
        self.assertEqual(expected, actual)

    def test_get_repository_uri(self):
        rdf = RDF()
        actual = rdf.get_repository_uri()
        expected = "http://omex-library.org/"
        self.assertEqual(expected, actual)

    def test_get_archive_uri(self):
        rdf = RDF()
        actual = rdf.get_archive_uri()
        expected = "http://omex-library.org/NewOmex.omex"
        self.assertEqual(expected, actual)

    def test_get_model_uri(self):
        rdf = RDF()
        actual = rdf.get_model_uri()
        expected = "http://omex-library.org/NewOmex.omex/NewModel.xml#"
        self.assertEqual(expected, actual)

    def test_get_local_uri(self):
        rdf = RDF()
        actual = rdf.get_local_uri()
        expected = "http://omex-library.org/NewOmex.omex/NewModel.rdf#"
        self.assertEqual(expected, actual)

    def test_query(self):
        rdf = RDF.from_string(self.rdf_str, "rdfxml")
        q = """SELECT ?x ?y ?z 
        WHERE {?x ?y ?z}
        """
        expected = """x,y,z
http://omex-library.org/NewOmex.omex/NewModel.rdf#force_0,http://www.bhi.washington.edu/semsim#hasSinkParticipant,http://omex-library.org/NewOmex.omex/NewModel.rdf#sink_0
http://omex-library.org/NewOmex.omex/NewModel.rdf#force_0,http://www.bhi.washington.edu/semsim#hasSourceParticipant,http://omex-library.org/NewOmex.omex/NewModel.rdf#source_0
http://omex-library.org/NewOmex.omex/NewModel.rdf#parameter_metaid_0,http://biomodels.net/biology-qualifiers/isPropertyOf,http://omex-library.org/NewOmex.omex/NewModel.rdf#force_0
http://omex-library.org/NewOmex.omex/NewModel.rdf#parameter_metaid_0,http://biomodels.net/biology-qualifiers/isVersionOf,https://identifiers.org/opb/OPB_01058
http://omex-library.org/NewOmex.omex/NewModel.rdf#sink_0,http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference,http://omex-library.org/NewOmex.omex/NewModel.rdf#species_metaid_1
http://omex-library.org/NewOmex.omex/NewModel.rdf#source_0,http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference,http://omex-library.org/NewOmex.omex/NewModel.rdf#species_metaid_0
"""
        self.maxDiff = None
        actual = rdf.query(q, "csv")
        self.assertEqual(expected, actual)

    def test_use_sqlite_storage(self):
        fname = os.path.join(os.path.dirname(__file__), "sqlite_db_from_python.db")
        rdf = RDF("sqlite", fname, "new='yes'")
        rdf.add_from_uri(self.sbml_uri, "rdfxml")
        self.assertTrue(os.path.isfile(fname))
        # while os.path.isfile(fname):
        #     try:
        #         os.remove(fname)
        #     except PermissionError:
        #         print("failed to remove " + fname)
        #         import time
        #         time.sleep(1)


class EditorTests(unittest.TestCase):
    maxDiff = None

    def setUp(self) -> None:
        self.rdf = RDF()
        self.editor = self.rdf.to_editor(XML, "sbml", True)

    def test_to_editor(self):
        self.assertIsInstance(self.editor, Editor)

    def test_context_manager_single_annotation(self):
        with self.rdf.to_editor(XML, "sbml", True) as editor:
            with editor.new_singular_annotation() as singular_annotation:
                singular_annotation \
                    .set_about("cytosol") \
                    .set_predicate("bqbiol", "is") \
                    .set_resource_uri("uniprot:PD88776")
        expected = """@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .
@prefix myOMEXlib: <http://omex-library.org/> .
@prefix myOMEX: <http://omex-library.org/NewOmex.omex> .
@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .

local:cytosol
    bqbiol:is <https://identifiers.org/uniprot/PD88776> .

"""
        actual = str(self.rdf)
        self.assertEqual(expected, actual)

    def test_context_manager_physical_process(self):
        with self.rdf.to_editor(XML, "sbml", True) as editor:
            with editor.new_physical_process() as physical_process:
                physical_process \
                    .set_physical_property("OmexMetaId0001", "opb/opb_275") \
                    .add_source(1.0, "physicalEntity4") \
                    .add_sink(1.0, "PhysicalEntity7") \
                    .add_mediator(1.0, "PhysicalEntity8")
        expected = """@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .
@prefix semsim: <http://www.bhi.washington.edu/semsim#> .
@prefix myOMEXlib: <http://omex-library.org/> .
@prefix myOMEX: <http://omex-library.org/NewOmex.omex> .
@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .

local:MediatorParticipant0000
    semsim:hasPhysicalEntityReference local:PhysicalEntity8 .

local:OmexMetaId0001
    bqbiol:isPropertyOf local:PhysicalProcess0000 ;
    bqbiol:isVersionOf <https://identifiers.org/opb/opb_275> .

local:PhysicalProcess0000
    semsim:hasMediatorParticipant local:MediatorParticipant0000 ;
    semsim:hasSinkParticipant local:SinkParticipant0000 ;
    semsim:hasSourceParticipant local:SourceParticipant0000 .

local:SinkParticipant0000
    semsim:hasMultiplier "1"^^<http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double> ;
    semsim:hasPhysicalEntityReference local:PhysicalEntity7 .

local:SourceParticipant0000
    semsim:hasMultiplier "1"^^<http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double> ;
    semsim:hasPhysicalEntityReference local:physicalEntity4 .

"""
        actual = str(self.rdf)
        print(actual)

        for i in actual.split("\n"):
            self.assertTrue(i.strip() in actual)

    def test_context_manager_physical_force(self):
        with self.rdf.to_editor(XML, "sbml", True) as editor:
            with editor.new_physical_force() as physical_force:
                physical_force \
                    .set_physical_property("OmexMetaId0004", "opb/opb_275") \
                    .add_source(1.0, "physicalEntity4") \
                    .add_sink(1.0, "PhysicalEntity7")
        expected = """@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .
@prefix semsim: <http://www.bhi.washington.edu/semsim#> .
@prefix myOMEXlib: <http://omex-library.org/> .
@prefix myOMEX: <http://omex-library.org/NewOmex.omex> .
@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .

local:OmexMetaId0004
    bqbiol:isPropertyOf local:PhysicalForce0000 ;
    bqbiol:isVersionOf <https://identifiers.org/opb/opb_275> .

local:PhysicalForce0000
    semsim:hasSinkParticipant local:SinkParticipant0000 ;
    semsim:hasSourceParticipant local:SourceParticipant0000 .

local:SinkParticipant0000
    semsim:hasMultiplier "1"^^<http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double> ;
    semsim:hasPhysicalEntityReference local:PhysicalEntity7 .

local:SourceParticipant0000
    semsim:hasMultiplier "1"^^<http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double> ;
    semsim:hasPhysicalEntityReference local:physicalEntity4 .

"""
        actual = str(self.rdf)

        print(actual)

        for i in actual.split("\n"):
            self.assertTrue(i.strip() in actual)

    def test_context_manager_personal_information(self):
        with self.rdf.to_editor(XML, "sbml", True) as editor:
            with editor.new_personal_information() as information:
                information \
                    .add_creator("1234-1234-1234-1234") \
                    .add_mbox("annotations@uw.edu")\
                    .add_name("Ciaran Welsh")

        expected = """@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
@prefix dcterms: <http://purl.org/dc/terms/> .
@prefix foaf: <http://xmlns.com/foaf/0.1/> .
@prefix myOMEXlib: <http://omex-library.org/> .
@prefix myOMEX: <http://omex-library.org/NewOmex.omex> .
@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .

<http://omex-library.org/NewOmex.omex/NewModel.xml#>
    dcterms:creator <http://omex-library.org/NewOmex.omex/NewModel.xml#PersonalInfo0000> .

<http://omex-library.org/NewOmex.omex/NewModel.xml#PersonalInfo0000>
    dcterms:creator <1234-1234-1234-1234> ;
    foaf:mbox "annotations@uw.edu"^^rdf:string ;
    foaf:name "Ciaran Welsh"^^rdf:string .

"""
        actual = str(self.rdf)

        print(actual)

        for i in actual.split("\n"):
            self.assertTrue(i.strip() in actual)


class AnnotateAModelTest(unittest.TestCase):
    maxDiff = None

    def setUp(self) -> None:
        ant = """
        model SmadNuclearTransport
            compartment cytosol;
            compartment nucleus;
            Smad3Cyt in cytosol;
            Smad3Nuc in nucleus;
            k1 = 0.1;
            k2 = 1;
            Smad3Nuc = 10;
            Smad3Cyt = 10;
            r1: Smad3Nuc => Smad3Cyt; k1*Smad3Nuc;
            r2: Smad3Cyt => Smad3Nuc; k2*Smad3Cyt;
        end
        """
        self.sbml = te.antimonyToSBML(ant)

    def test_get_metaids(self):
        rdf = RDF()
        with rdf.to_editor(self.sbml, "sbml", generate_new_metaids=True) as editor:
            metaids = editor.get_metaids()

        expected = ['SmadNuclearTransport',
                    '#OmexMetaId0000',
                    '#OmexMetaId0001',
                    '#OmexMetaId0002',
                    '#OmexMetaId0003',
                    '#OmexMetaId0004',
                    '#OmexMetaId0005',
                    '#OmexMetaId0006',
                    '#OmexMetaId0007']
        actual = metaids
        self.assertEqual(expected, actual)

    def test_get_xml(self):
        rdf = RDF()
        with rdf.to_editor(self.sbml, "sbml", generate_new_metaids=True) as editor:
            xml_with_metaids = editor.get_xml()

        expected = """<?xml version="1.0" encoding="UTF-8"?>
<!-- Created by libAntimony version v2.12.0 with libSBML version 5.18.1. -->
<sbml xmlns="http://www.sbml.org/sbml/level3/version1/core" level="3" version="1">
  <model metaid="SmadNuclearTransport" id="SmadNuclearTransport">
    <listOfCompartments>
      <compartment id="cytosol" spatialDimensions="3" constant="true" metaid="#OmexMetaId0000"/>
      <compartment id="nucleus" spatialDimensions="3" constant="true" metaid="#OmexMetaId0001"/>
    </listOfCompartments>
    <listOfSpecies>
      <species id="Smad3Cyt" compartment="cytosol" initialConcentration="10" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false" metaid="#OmexMetaId0002"/>
      <species id="Smad3Nuc" compartment="nucleus" initialConcentration="10" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false" metaid="#OmexMetaId0003"/>
    </listOfSpecies>
    <listOfParameters>
      <parameter id="k1" value="0.1" constant="true"/>
      <parameter id="k2" value="1" constant="true"/>
    </listOfParameters>
    <listOfReactions>
      <reaction id="r1" reversible="false" fast="false" metaid="#OmexMetaId0004">
        <listOfReactants>
          <speciesReference species="Smad3Nuc" stoichiometry="1" constant="true"/>
        </listOfReactants>
        <listOfProducts>
          <speciesReference species="Smad3Cyt" stoichiometry="1" constant="true"/>
        </listOfProducts>
        <kineticLaw metaid="#OmexMetaId0005">
          <math xmlns="http://www.w3.org/1998/Math/MathML">
            <apply>
              <times/>
              <ci> k1 </ci>
              <ci> Smad3Nuc </ci>
            </apply>
          </math>
        </kineticLaw>
      </reaction>
      <reaction id="r2" reversible="false" fast="false" metaid="#OmexMetaId0006">
        <listOfReactants>
          <speciesReference species="Smad3Cyt" stoichiometry="1" constant="true"/>
        </listOfReactants>
        <listOfProducts>
          <speciesReference species="Smad3Nuc" stoichiometry="1" constant="true"/>
        </listOfProducts>
        <kineticLaw metaid="#OmexMetaId0007">
          <math xmlns="http://www.w3.org/1998/Math/MathML">
            <apply>
              <times/>
              <ci> k2 </ci>
              <ci> Smad3Cyt </ci>
            </apply>
          </math>
        </kineticLaw>
      </reaction>
    </listOfReactions>
  </model>
</sbml>
"""
        actual = xml_with_metaids
        print(actual)
        self.assertEqual(expected, actual)

    def test_annotate_model(self):
        """
        Tests the annotation of a model created in setup.

        Note: autogenerate the participant ID, currently users,
            are asked to give the id, but this isn't really necessary.
        Returns:

        """
        rdf = RDF()
        with rdf.to_editor(self.sbml, "sbml", generate_new_metaids=True) as editor:
            # model level annotations
            with editor.new_singular_annotation() as author:
                author.set_about("SmadNuclearTransport") \
                    .set_predicate_from_uri("https://unknownpredicate.com/changeme#author") \
                    .set_resource_literal("Ciaran Welsh")

            # annotate Smad3nuc
            with editor.new_physical_entity() as smad3nuc:
                smad3nuc \
                    .set_physical_property("OmexMetaId0002", "OPB:OPB_00340") \
                    .set_identity("uniprot:P84022") \
                    .add_location("obo/FMA_7163") \
                    .add_location("obo/FMA_264020")

            # annotate Smad3nuc
            with editor.new_physical_entity() as smad3nuc:
                smad3nuc \
                    .set_physical_property("OmexMetaId0003", "OPB:OPB_00340") \
                    .set_identity("uniprot:P84022") \
                    .add_location("obo/FMA_7163") \
                    .add_location("obo/FMA_63877") \
                    .add_location("obo/FMA_63840")

            # annotate r1 (Smad3Nuc -> Smad3Cyt)
            with editor.new_physical_process() as export_reaction:
                export_reaction \
                    .set_physical_property("OmexMetaId0004", "OPB:OPB_00237") \
                    .add_source(1, "OmexMetaId0003") \
                    .add_sink(1, "OmexMetaId0002")

            # annotate r2 (Smad3Cyt -> Smad3Nuc)
            with editor.new_physical_process() as export_reaction:
                export_reaction \
                    .set_physical_property("OmexMetaId0005", "OPB:OPB_00237") \
                    .add_source(1, "OmexMetaId0002") \
                    .add_sink(1, "OmexMetaId0003")

        expected = """@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .
@prefix semsim: <http://www.bhi.washington.edu/semsim#> .
@prefix myOMEXlib: <http://omex-library.org/> .
@prefix myOMEX: <http://omex-library.org/NewOmex.omex> .
@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .

local:OmexMetaId0002
    bqbiol:isPropertyOf local:PhysicalEntity0000 ;
    bqbiol:isVersionOf <https://identifiers.org/OPB/OPB_00340> .

local:OmexMetaId0003
    bqbiol:isPropertyOf local:PhysicalEntity0000 ;
    bqbiol:isVersionOf <https://identifiers.org/OPB/OPB_00340> .

local:OmexMetaId0004
    bqbiol:isPropertyOf local:PhysicalProcess0000 ;
    bqbiol:isVersionOf <https://identifiers.org/OPB/OPB_00237> .

local:OmexMetaId0005
    bqbiol:isPropertyOf local:PhysicalProcess0000 ;
    bqbiol:isVersionOf <https://identifiers.org/OPB/OPB_00237> .

local:PhysicalEntity0000
    bqbiol:is <https://identifiers.org/uniprot/P84022> ;
    bqbiol:isPartOf <https://identifiers.org/obo/FMA_264020>, <https://identifiers.org/obo/FMA_63840>, <https://identifiers.org/obo/FMA_63877>, <https://identifiers.org/obo/FMA_7163> .

local:PhysicalProcess0000
    semsim:hasSinkParticipant local:SinkParticipant0000 ;
    semsim:hasSourceParticipant local:SourceParticipant0000 .

local:SinkParticipant0000
    semsim:hasMultiplier "1"^^<http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double> ;
    semsim:hasPhysicalEntityReference local:OmexMetaId0002, local:OmexMetaId0003 .

local:SmadNuclearTransport
    <https://unknownpredicate.com/changeme#author> "Ciaran Welsh"^^rdf:string .

local:SourceParticipant0000
    semsim:hasMultiplier "1"^^<http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double> ;
    semsim:hasPhysicalEntityReference local:OmexMetaId0002, local:OmexMetaId0003 .

"""

        actual = str(rdf)
        print(actual)
        for i in actual.split("\n"):
            self.assertTrue(i.strip() in actual)


class GoldStandardOmexArchiveTests(unittest.TestCase):
    maxDiff = None

    # urls and filepaths for the gold standard omex archives
    gold_standard_url1 = "https://auckland.figshare.com/ndownloader/files/17432333"
    gold_standard_url2 = "https://auckland.figshare.com/ndownloader/files/15425522"
    gold_standard_url3 = "https://auckland.figshare.com/ndownloader/files/15425513"
    gold_standard_url4 = "https://auckland.figshare.com/ndownloader/files/15425546"
    gold_standard_url5 = "https://auckland.figshare.com/ndownloader/files/17432366"

    gold_standard_filename1 = os.path.join(os.getcwd(), "goldstandard1.omex")
    gold_standard_filename2 = os.path.join(os.getcwd(), "goldstandard2.omex")
    gold_standard_filename3 = os.path.join(os.getcwd(), "goldstandard3.omex")
    gold_standard_filename4 = os.path.join(os.getcwd(), "goldstandard4.omex")
    gold_standard_filename5 = os.path.join(os.getcwd(), "goldstandard5.omex")

    def setUp(self) -> None:
        pass

    def download_file(self, url: str, local_fname: str):
        with requests.get(url, stream=True) as r:
            r.raise_for_status()
            with open(local_fname, 'wb') as f:
                for chunk in r.iter_content(chunk_size=8192):
                    f.write(chunk)
        return local_fname

    def tearDown(self) -> None:
        teardown = True
        if teardown:
            for i in [
                self.gold_standard_filename1,
                self.gold_standard_filename2,
                self.gold_standard_filename3,
                self.gold_standard_filename4,
                self.gold_standard_filename5]:
                if os.path.isfile(i):
                    os.remove(i)

    def extract_rdf_from_combine_archive(self, archive_path: str) -> typing.List[str]:
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

    def gold_standard_test(self, gold_standard_url: str, gold_standard_filename: str, size: int):
        # get the gold standard omex file from the tinterweb
        self.download_file(gold_standard_url, gold_standard_filename)

        # get rdf string from omex file usign libcombine
        rdf_strings = self.extract_rdf_from_combine_archive(gold_standard_filename)
        assert (len(rdf_strings) == 1), len(rdf_strings)

        # now libomexmeta can read the string into an rdf graph
        rdf = RDF.from_string(rdf_strings[0])

        # serialize to html, because why not?
        self.assertEqual(size, len(rdf))

    def test_gold_standard1(self):
        self.gold_standard_test(self.gold_standard_url1, self.gold_standard_filename1, 23)

    def test_gold_standard2(self):
        self.gold_standard_test(self.gold_standard_url2, self.gold_standard_filename2, 429)

    def test_gold_standard3(self):
        self.gold_standard_test(self.gold_standard_url3, self.gold_standard_filename3, 546)

    def test_gold_standard4(self):
        self.gold_standard_test(self.gold_standard_url4, self.gold_standard_filename4, 629)

    def test_gold_standard5(self):
        self.gold_standard_test(self.gold_standard_url5, self.gold_standard_filename5, 69)

    def test_query(self):
        self.download_file(self.gold_standard_url1, self.gold_standard_filename1)
        s = self.extract_rdf_from_combine_archive(self.gold_standard_filename1)[0]
        rdf = RDF.from_string(s, "rdfxml")
        query_str = """
        PREFIX bqbiol: <http://biomodels.net/biology-qualifiers/>
        SELECT ?x ?y ?z
        WHERE {
            ?x ?y ?z
        }"""
        results = rdf.query(query_str, "rdfxml")
        results_rdf = RDF()
        results_rdf.add_from_string(results)
        self.assertEqual(234, len(results_rdf))

    def test(self):
        ant1 = """
            model SBML1
                compartment cytosol = 1.0;
                A in cytosol;
                B in cytosol
                A = 10; 
                B = 0;
                k1 = 0.1;
                k2 = 0.1;
                r1: A => B; k1*A
                r1: B => A; k2*B
            end
            """

        ant2 = """
            model SBML1
                compartment cytosol = 1.0;
                C in cytosol;
                D in cytosol
                C = 10; 
                D = 0;
                k1 = 0.1;
                k2 = 0.1;
                r1: C => D; k1*C
                r1: D => C; k2*D
            end
            """
        sbml1 = te.antimonyToSBML(ant1)
        sbml2 = te.antimonyToSBML(ant2)

        rdf = RDF()
        with rdf.to_editor(sbml1, "sbml", True) as editor:
            print(editor.get_xml())
            with editor.new_singular_annotation() as singular_annotation:
                singular_annotation.set_about("OmexMetaId0000") \
                    .set_predicate("bqbiol", "is") \
                    .set_resource_uri("fma/FMA_66835")

        print(rdf)


class DrawTests(unittest.TestCase):
    def setUp(self) -> None:
        ant = """
                model SBML1
                    compartment cytosol = 1.0;
                    A in cytosol;
                    B in cytosol
                    A = 10; 
                    B = 0;
                    k1 = 0.1;
                    k2 = 0.1;
                    r1: A => B; k1*A
                    r1: B => A; k2*B
                end
                """
        self.sbml = te.antimonyToSBML(ant)

    def tearDown(self) -> None:
        pass

    def test(self):
        rdf = RDF()
        with rdf.to_editor(self.sbml, "sbml", generate_new_metaids=True) as editor:
            with editor.new_singular_annotation() as s:
                s.set_about("OmexMetaId0000") \
                    .set_predicate("bqbiol", "is") \
                    .set_resource_uri("fma/FMA_66835")
        fname = os.path.join(os.path.realpath("."), "test_draw.png")
        rdf.draw(fname)
        self.assertTrue(os.path.isfile(fname))
        os.remove(fname)


"""
The test below takes too long to run. It works. 
"""
# class TestHorrendouslyLargeRDFFile(unittest.TestCase):
#
#     def setUp(self) -> None:
#         self.zip_fname = os.path.join(
#             os.path.dirname(__file__), "BrendaParameters.zip"
#         )
#         if not os.path.isfile(self.zip_fname):
#             raise FileNotFoundError(self.zip_fname)
#
#         with zipfile.ZipFile(self.zip_fname, 'r') as zip_ref:
#             zip_ref.extractall(os.path.dirname(self.zip_fname))
#
#         self.fname = os.path.join(os.path.dirname(__file__), "brenda_parameters_1.xml")
#         if not os.path.isfile(self.fname):
#             raise FileNotFoundError(self.fname)
#
#     def test_sqlite(self):
#         db_file = os.path.join(os.path.dirname(__file__), "BrendaAnnotDatabaseSQLite.db")
#         rdf = RDF("sqlite", db_file, "new='yes'")
#         rdf.add_from_file(self.fname, "rdfxml")
#         print(len(rdf))
#
#     def test_bdb(self):
#         rdf = RDF("hashes", "BrendaAnnotDatabaseBDB.db", "hash-type='bdb',dir='{}'".format(os.path.dirname(__file__)))
#         rdf.add_from_file(self.fname, "rdfxml")
#         print(len(rdf))



class OtherTests(unittest.TestCase):

    def setUp(self) -> None:
        pass

    def test(self):
        import tellurium as te
        from pyomexmeta import RDF, Editor
        ant = """
model SBML1
    compartment cytosol = 1.0;
    A in cytosol;
    B in cytosol
    A = 10;
    B = 0;
    k1 = 0.1;
    k2 = 0.1;
    r1: A => B; k1*A
    r1: B => A; k2*B
end"""
        sbml = te.antimonyToSBML(ant)
        print(sbml)

        rdf = RDF()
        with rdf.to_editor(sbml, "sbml", True) as editor:
            print(editor.get_metaids()) # prints out model metaids

            with editor.new_singular_annotation() as identity:
                identity\
                    .set_about('#OmexMetaId0000') \
                    .set_predicate("bqbiol", "is")\
                    .set_resource_uri("uniprot:PD12345")
        print(rdf)



        # rdf2 = RDF.from_string(str(rdf))
        # print(rdf2.to_string("turtle", "turtle_syntax.rdf"))



        # print(rdf.to_string("seria", "file://myOMEXLib.com"))
        # q = """SELECT *
        # WHERE { ?x ?y ?z }"""
        # rdf.query(q, "res")

    def test(self):
        # import pyomexmeta as pyOM # my preference, see next line (though you can choose whichever suits you)
        # from pyomexmeta import RDF
        #
        # import libcombine
        # # Don't bother with argv - this is for
        # # command line program, but there is no real need for this here
        # # from sys import argv
        #
        # # os is useful for finding the file that we want
        # import os
        #
        # # Lets just check what directory Python is running from:
        # print(
        #     os.getcwd())  # prints C:\Users\Ciaran\Desktop on mine, where I pasted your script and saved as example.py along with BIOMD0000000503.xml
        #
        # # now get a path to BIOMD0000000503.xml
        # file = os.path.join(os.path.dirname(__file__), "BIOMD0000000503.xml")
        #
        # # make sure we got it right
        # if not os.path.isfile(file):
        #     raise ValueError(
        #         "Didn't find your file at \"{}\". Put BIOMD0000000503.xml in the same directory as the python file containing this code".format(
        #             file))
        #
        # # argv[0] =
        # # "Documents\gennari\SemBIoProcess\CenterReproducbility\libOMEXmeta\testing\BIOMD0000000503.xml"
        # # argv[1] =
        # # "Documents\gennari\SemBIoProcess\CenterReproducbility\libOMEXmeta\BIOMD_503.rdf"
        # # argv[2] = "turtle"
        #
        # # rdfstring = pyOM.RDF.from_file(argv[0],"rdfxml") # note that this produces the RDF *object, not the RDF string
        # rdf = RDF.from_file(file, "rdfxml")
        # # now we can get the string:
        # turtle_string = rdf.to_string("turtle")
        # print(turtle_string)
        #
        # # Incidently, because turtle is the default we can also do:
        # print(rdf)  # we like python for its syntatic sugar
        #
        # # if you want to write a file you can do the standard python way:
        # outfile = os.path.join(os.path.dirname(__file__), "output_turtle.rdf")
        # with open(outfile, "w") as f:
        #     f.write(turtle_string)
        #
        # # But this is what the RDF object does behind the scenes anyway:
        # rdf.to_file("turtle", outfile)  # this line is equivalent to the above "with" statement

        # actual = rdfstring.to_string(argv[2])
        # print(actual, file=open(argv[1], 'w'))

        # indicently, there is another way to read annotations from models in biomodels:
        biomod_url = "https://www.ebi.ac.uk/biomodels/model/download/BIOMD0000000503.2?filename=BIOMD0000000503_url.xml"
        rdf_from_uri = RDF.from_uri(biomod_url, "rdfxml")
        # print(rdf_from_uri)
        f = os.path.join(os.path.dirname(__file__), "outfile.rdf")
        rdf_from_uri.to_file("turtle", f)


if __name__ == "__main__":
    unittest.main()
