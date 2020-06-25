import os
import site
import typing
import unittest

import libcombine
import requests

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

xml = """<?xml version="1.0" encoding="UTF-8"?>
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
       xmlns:semsim="http://www.bhi.washington.edu/semsim#"
       xml:base="file://./annotations.rdf">
      <rdf:Description rdf:about="force_0">
        <semsim:hasSinkParticipant rdf:resource="sink_0"/>
        <semsim:hasSourceParticipant rdf:resource="source_0"/>
      </rdf:Description>
      <rdf:Description rdf:about="parameter_metaid_0">
        <bqbiol:isPropertyOf rdf:resource="force_0"/>
        <bqbiol:isVersionOf rdf:resource="https://identifiers.org/opb/OPB_01058"/>
      </rdf:Description>
      <rdf:Description rdf:about="sink_0">
        <semsim:hasPhysicalEntityReference rdf:resource="species_metaid_1"/>
      </rdf:Description>
      <rdf:Description rdf:about="source_0">
        <semsim:hasPhysicalEntityReference rdf:resource="species_metaid_0"/>
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
        self.assertEqual(6, len(rdf))

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

    def test_query(self):
        rdf = RDF.from_string(self.rdf_str, "rdfxml")
        q = """SELECT ?x ?y ?z 
        WHERE {?x ?y ?z}
        """
        expected = """x,y,z
file://./force_0,http://www.bhi.washington.edu/semsim#hasSinkParticipant,file://./sink_0
file://./force_0,http://www.bhi.washington.edu/semsim#hasSourceParticipant,file://./source_0
file://./parameter_metaid_0,http://biomodels.net/biology-qualifiers/isPropertyOf,file://./force_0
file://./parameter_metaid_0,http://biomodels.net/biology-qualifiers/isVersionOf,https://identifiers.org/opb/OPB_01058
file://./sink_0,http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference,file://./species_metaid_1
file://./source_0,http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference,file://./species_metaid_0
"""
        self.maxDiff = None
        actual = rdf.query(q, "csv")
        self.assertEqual(expected, actual)

    def test_use_sqlite_storage(self):
        fname = os.path.join(os.path.dirname(__file__), "sqlite_test.db")
        print(fname)
        rdf = RDF("sqlite", fname, "new='yes'")
        rdf.add_from_string(self.rdf_str, "rdfxml", "sqlite_test")
        self.assertTrue(os.path.isfile(fname))


class EditorTests(unittest.TestCase):
    maxDiff = None

    def setUp(self) -> None:
        self.rdf = RDF()
        self.editor = self.rdf.to_editor(xml, "sbml")

    def test_to_editor(self):
        self.assertIsInstance(self.editor, Editor)

    def test_context_manager_single_annotation(self):
        with self.rdf.to_editor(xml, "sbml") as editor:
            with editor.new_singular_annotation() as singular_annotation:
                singular_annotation \
                    .set_about("cytosol") \
                    .set_predicate("bqb", "is") \
                    .set_resource_uri("uniprot:PD88776")
        expected = """<?xml version="1.0" encoding="utf-8"?>
<rdf:RDF xmlns:bqbiol="http://biomodels.net/biology-qualifiers/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"
   xml:base="file://./Annotations.rdf">
  <rdf:Description rdf:about="cytosol">
    <bqbiol:is rdf:resource="https://identifiers.org/uniprot/PD88776"/>
  </rdf:Description>
</rdf:RDF>
"""
        actual = str(self.rdf)
        self.assertEqual(expected, actual)

    def test_context_manager_physical_process(self):
        with self.rdf.to_editor(xml, "sbml") as editor:
            with editor.new_physical_process() as physical_process:
                physical_process \
                    .set_physical_property("SemsimMetaid0001", "opb/opb_275") \
                    .add_source(1.0, "physicalEntity4") \
                    .add_sink(1.0, "PhysicalEntity7") \
                    .add_mediator(1.0, "PhysicalEntity8")
        expected = """<?xml version="1.0" encoding="utf-8"?>
<rdf:RDF xmlns:bqbiol="http://biomodels.net/biology-qualifiers/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"
   xmlns:semsim="http://www.bhi.washington.edu/semsim#"
   xml:base="file://./Annotations.rdf">
  <rdf:Description rdf:about="MediatorParticipant0000">
    <semsim:hasPhysicalEntityReference rdf:resource="PhysicalEntity8"/>
  </rdf:Description>
  <rdf:Description rdf:about="PhysicalProcess0000">
    <semsim:hasMediatorParticipant rdf:resource="MediatorParticipant0000"/>
    <semsim:hasSinkParticipant rdf:resource="SinkParticipant0000"/>
    <semsim:hasSourceParticipant rdf:resource="SourceParticipant0000"/>
  </rdf:Description>
  <rdf:Description rdf:about="SemsimMetaid0001">
    <bqbiol:isPropertyOf rdf:resource="PhysicalProcess0000"/>
    <bqbiol:isVersionOf rdf:resource="https://identifiers.org/opb/opb_275"/>
  </rdf:Description>
  <rdf:Description rdf:about="SinkParticipant0000">
    <semsim:hasMultiplier rdf:datatype="http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double">1</semsim:hasMultiplier>
    <semsim:hasPhysicalEntityReference rdf:resource="PhysicalEntity7"/>
  </rdf:Description>
  <rdf:Description rdf:about="SourceParticipant0000">
    <semsim:hasMultiplier rdf:datatype="http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double">1</semsim:hasMultiplier>
    <semsim:hasPhysicalEntityReference rdf:resource="physicalEntity4"/>
  </rdf:Description>
</rdf:RDF>
"""
        actual = str(self.rdf)
        print(actual)

        self.assertEqual(expected, actual)

    def test_context_manager_physical_force(self):
        with self.rdf.to_editor(xml, "sbml") as editor:
            with editor.new_physical_force() as physical_force:
                physical_force \
                    .set_physical_property("SemsimMetaid0004", "opb/opb_275") \
                    .add_source(1.0, "physicalEntity4") \
                    .add_sink(1.0, "PhysicalEntity7")
        expected = """<?xml version="1.0" encoding="utf-8"?>
<rdf:RDF xmlns:bqbiol="http://biomodels.net/biology-qualifiers/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"
   xmlns:semsim="http://www.bhi.washington.edu/semsim#"
   xml:base="file://./Annotations.rdf">
  <rdf:Description rdf:about="PhysicalForce0000">
    <semsim:hasSinkParticipant rdf:resource="SinkParticipant0000"/>
    <semsim:hasSourceParticipant rdf:resource="SourceParticipant0000"/>
  </rdf:Description>
  <rdf:Description rdf:about="SemsimMetaid0004">
    <bqbiol:isPropertyOf rdf:resource="PhysicalForce0000"/>
    <bqbiol:isVersionOf rdf:resource="https://identifiers.org/opb/opb_275"/>
  </rdf:Description>
  <rdf:Description rdf:about="SinkParticipant0000">
    <semsim:hasMultiplier rdf:datatype="http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double">1</semsim:hasMultiplier>
    <semsim:hasPhysicalEntityReference rdf:resource="PhysicalEntity7"/>
  </rdf:Description>
  <rdf:Description rdf:about="SourceParticipant0000">
    <semsim:hasMultiplier rdf:datatype="http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double">1</semsim:hasMultiplier>
    <semsim:hasPhysicalEntityReference rdf:resource="physicalEntity4"/>
  </rdf:Description>
</rdf:RDF>
"""
        actual = str(self.rdf)

        print(actual)

        self.assertEqual(expected, actual)


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
        with rdf.to_editor(self.sbml, "sbml") as editor:
            metaids = editor.get_metaids()

        expected = ['SmadNuclearTransport',
                    'SemsimMetaid0000',
                    'SemsimMetaid0001',
                    'SemsimMetaid0002',
                    'SemsimMetaid0003',
                    'SemsimMetaid0004',
                    'SemsimMetaid0005',
                    'SemsimMetaid0006',
                    'SemsimMetaid0007']
        actual = metaids
        self.assertEqual(expected, actual)

    def test_get_xml(self):
        rdf = RDF()
        with rdf.to_editor(self.sbml, "sbml") as editor:
            xml_with_metaids = editor.get_xml()

        expected = """<?xml version="1.0" encoding="UTF-8"?>
<!-- Created by libAntimony version v2.11.0 with libSBML version 5.18.0. -->
<sbml xmlns="http://www.sbml.org/sbml/level3/version1/core" level="3" version="1">
  <model metaid="SmadNuclearTransport" id="SmadNuclearTransport">
    <listOfCompartments>
      <compartment id="cytosol" spatialDimensions="3" constant="true" metaid="SemsimMetaid0000"/>
      <compartment id="nucleus" spatialDimensions="3" constant="true" metaid="SemsimMetaid0001"/>
    </listOfCompartments>
    <listOfSpecies>
      <species id="Smad3Cyt" compartment="cytosol" initialConcentration="10" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false" metaid="SemsimMetaid0002"/>
      <species id="Smad3Nuc" compartment="nucleus" initialConcentration="10" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false" metaid="SemsimMetaid0003"/>
    </listOfSpecies>
    <listOfParameters>
      <parameter id="k1" value="0.1" constant="true"/>
      <parameter id="k2" value="1" constant="true"/>
    </listOfParameters>
    <listOfReactions>
      <reaction id="r1" reversible="false" fast="false" metaid="SemsimMetaid0004">
        <listOfReactants>
          <speciesReference species="Smad3Nuc" stoichiometry="1" constant="true"/>
        </listOfReactants>
        <listOfProducts>
          <speciesReference species="Smad3Cyt" stoichiometry="1" constant="true"/>
        </listOfProducts>
        <kineticLaw metaid="SemsimMetaid0005">
          <math xmlns="http://www.w3.org/1998/Math/MathML">
            <apply>
              <times/>
              <ci> k1 </ci>
              <ci> Smad3Nuc </ci>
            </apply>
          </math>
        </kineticLaw>
      </reaction>
      <reaction id="r2" reversible="false" fast="false" metaid="SemsimMetaid0006">
        <listOfReactants>
          <speciesReference species="Smad3Cyt" stoichiometry="1" constant="true"/>
        </listOfReactants>
        <listOfProducts>
          <speciesReference species="Smad3Nuc" stoichiometry="1" constant="true"/>
        </listOfProducts>
        <kineticLaw metaid="SemsimMetaid0007">
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

        self.assertEqual(expected, actual)

    def test_annotate_model(self):
        """
        Tests the annotation of a model created in setup.

        Note: autogenerate the participant ID, currently users,
            are asked to give the id, but this isn't really necessary.
        Returns:

        """
        rdf = RDF()
        with rdf.to_editor(self.sbml, "sbml") as editor:
            # model level annotations
            with editor.new_singular_annotation() as author:
                author.set_about("SmadNuclearTransport") \
                    .set_predicate_uri("https://unknownpredicate.com/changeme#author") \
                    .set_resource_literal("Ciaran Welsh")

            # annotate Smad3nuc
            with editor.new_physical_entity() as smad3nuc:
                smad3nuc \
                    .set_physical_property("SemsimMetaid0002", "OPB:OPB_00340") \
                    .set_identity("uniprot:P84022") \
                    .add_location("obo/FMA_7163") \
                    .add_location("obo/FMA_264020")

            # annotate Smad3nuc
            with editor.new_physical_entity() as smad3nuc:
                smad3nuc \
                    .set_physical_property("SemsimMetaid0003", "OPB:OPB_00340") \
                    .set_identity("uniprot:P84022") \
                    .add_location("obo/FMA_7163") \
                    .add_location("obo/FMA_63877") \
                    .add_location("obo/FMA_63840")

            # annotate r1 (Smad3Nuc -> Smad3Cyt)
            with editor.new_physical_process() as export_reaction:
                export_reaction \
                    .set_physical_property("SemsimMetaid0004", "OPB:OPB_00237") \
                    .add_source(1, "SemsimMetaid0003") \
                    .add_sink(1, "SemsimMetaid0002")

            # annotate r2 (Smad3Cyt -> Smad3Nuc)
            with editor.new_physical_process() as export_reaction:
                export_reaction \
                    .set_physical_property("SemsimMetaid0005", "OPB:OPB_00237") \
                    .add_source(1, "SemsimMetaid0002") \
                    .add_sink(1, "SemsimMetaid0003")

        expected = """<?xml version="1.0" encoding="utf-8"?>
<rdf:RDF xmlns:bqbiol="http://biomodels.net/biology-qualifiers/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"
   xmlns:semsim="http://www.bhi.washington.edu/semsim#"
   xml:base="file://./Annotations.rdf">
  <rdf:Description rdf:about="PhysicalEntity0000">
    <bqbiol:is rdf:resource="https://identifiers.org/uniprot/P84022"/>
    <bqbiol:isPartOf rdf:resource="https://identifiers.org/obo/FMA_264020"/>
    <bqbiol:isPartOf rdf:resource="https://identifiers.org/obo/FMA_7163"/>
  </rdf:Description>
  <rdf:Description rdf:about="PhysicalEntity0001">
    <bqbiol:is rdf:resource="https://identifiers.org/uniprot/P84022"/>
    <bqbiol:isPartOf rdf:resource="https://identifiers.org/obo/FMA_63840"/>
    <bqbiol:isPartOf rdf:resource="https://identifiers.org/obo/FMA_63877"/>
    <bqbiol:isPartOf rdf:resource="https://identifiers.org/obo/FMA_7163"/>
  </rdf:Description>
  <rdf:Description rdf:about="PhysicalProcess0000">
    <semsim:hasSinkParticipant rdf:resource="SinkParticipant0000"/>
    <semsim:hasSourceParticipant rdf:resource="SourceParticipant0000"/>
  </rdf:Description>
  <rdf:Description rdf:about="PhysicalProcess0001">
    <semsim:hasSinkParticipant rdf:resource="SinkParticipant0001"/>
    <semsim:hasSourceParticipant rdf:resource="SourceParticipant0001"/>
  </rdf:Description>
  <rdf:Description rdf:about="SemsimMetaid0002">
    <bqbiol:isPropertyOf rdf:resource="PhysicalEntity0000"/>
    <bqbiol:isVersionOf rdf:resource="https://identifiers.org/OPB/OPB_00340"/>
  </rdf:Description>
  <rdf:Description rdf:about="SemsimMetaid0003">
    <bqbiol:isPropertyOf rdf:resource="PhysicalEntity0001"/>
    <bqbiol:isVersionOf rdf:resource="https://identifiers.org/OPB/OPB_00340"/>
  </rdf:Description>
  <rdf:Description rdf:about="SemsimMetaid0004">
    <bqbiol:isPropertyOf rdf:resource="PhysicalProcess0000"/>
    <bqbiol:isVersionOf rdf:resource="https://identifiers.org/OPB/OPB_00237"/>
  </rdf:Description>
  <rdf:Description rdf:about="SemsimMetaid0005">
    <bqbiol:isPropertyOf rdf:resource="PhysicalProcess0001"/>
    <bqbiol:isVersionOf rdf:resource="https://identifiers.org/OPB/OPB_00237"/>
  </rdf:Description>
  <rdf:Description rdf:about="SinkParticipant0000">
    <semsim:hasMultiplier rdf:datatype="http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double">1</semsim:hasMultiplier>
    <semsim:hasPhysicalEntityReference rdf:resource="SemsimMetaid0002"/>
  </rdf:Description>
  <rdf:Description rdf:about="SinkParticipant0001">
    <semsim:hasMultiplier rdf:datatype="http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double">1</semsim:hasMultiplier>
    <semsim:hasPhysicalEntityReference rdf:resource="SemsimMetaid0003"/>
  </rdf:Description>
  <rdf:Description rdf:about="SmadNuclearTransport">
    <ns1:author xmlns:ns1="https://unknownpredicate.com/changeme#"
       rdf:datatype="http://www.w3.org/1999/02/22-rdf-syntax-ns#string">Ciaran Welsh</ns1:author>
  </rdf:Description>
  <rdf:Description rdf:about="SourceParticipant0000">
    <semsim:hasMultiplier rdf:datatype="http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double">1</semsim:hasMultiplier>
    <semsim:hasPhysicalEntityReference rdf:resource="SemsimMetaid0003"/>
  </rdf:Description>
  <rdf:Description rdf:about="SourceParticipant0001">
    <semsim:hasMultiplier rdf:datatype="http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double">1</semsim:hasMultiplier>
    <semsim:hasPhysicalEntityReference rdf:resource="SemsimMetaid0002"/>
  </rdf:Description>
</rdf:RDF>
"""
        actual = str(rdf)
        print(actual)
        self.assertEqual(expected, actual)


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

    def gold_standard_test(self, gold_standard_url: str, gold_standard_filename: str,
                           expected_output: str, format: str):
        # get the gold standard omex file from the tinterweb
        self.download_file(gold_standard_url, gold_standard_filename)

        # get rdf string from omex file usign libcombine
        rdf_strings = self.extract_rdf_from_combine_archive(gold_standard_filename)
        assert (len(rdf_strings) == 1), len(rdf_strings)

        # now libomexmeta can read the string into an rdf graph
        rdf = RDF.from_string(rdf_strings[0])

        # serialize to html, because why not?
        actual = rdf.to_string(format, gold_standard_filename)[:500]  # shorten
        print(actual)
        self.assertEqual(expected_output, actual)

    def gold_standard_test_by_line(self, gold_standard_url: str, gold_standard_filename: str,
                                   expected_output: str, format: str):
        """
        Same as gold_standard_test but matched line by line.
        :param gold_standard_url:
        :param gold_standard_filename:
        :param expected_output:
        :param format:
        :return:
        """
        # get the gold standard omex file from the tinterweb
        self.download_file(gold_standard_url, gold_standard_filename)

        # get rdf string from omex file usign libcombine
        rdf_strings = self.extract_rdf_from_combine_archive(gold_standard_filename)
        assert (len(rdf_strings) == 1), len(rdf_strings)

        # now libomexmeta can read the string into an rdf graph
        rdf = RDF.from_string(rdf_strings[0])

        # serialize to html, because why not?
        actual = rdf.to_string(format, gold_standard_filename)[:500]  # shorten
        for i in actual.split("\n"):
            self.assertTrue(i in actual)

    def test_gold_standard1(self):
        expected = """<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN"
        "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
  <title>Raptor Graph Serialisation</title>
</head>
<body>
  <table id="triples" border="1">
    <tr>
      <th>Subject</th>
      <th>Predicate</th>
      <th>Object</th>
    </tr>
    <tr class="triple">
      <td><span class="uri"><a href="BIOMD0000000204_new.sbml#metaid15">BIOMD0000000204_new.sbml#m"""
        self.gold_standard_test(self.gold_standard_url1, self.gold_standard_filename1, expected, "html")

    def test_gold_standard2(self):
        # note we skip the irst line which contains a filename. This is different on different
        # platforms and different systems
        expected = """@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .
@prefix dcterms: <http://purl.org/dc/terms/> .
@prefix bqmodel: <http://biomodels.net/model-qualifiers/> .

<smith_2004.cellml#aorta.E_es_ao>
    dcterms:description "Aortic end systolic elastance" .

<smith_2004.cellml#aorta.P_lv>
    bqbiol:isPropertyOf <smith_2004.cellml#force_5> ;
    bqbiol:isVersionOf <ht"""
        print(self.gold_standard_url2, self.gold_standard_filename2)
        self.gold_standard_test_by_line(self.gold_standard_url2, self.gold_standard_filename2, expected, "turtle")

    def test_gold_standard3(self):
        expected = """<?xml version="1.0" encoding="utf-8"?>
<rdf:RDF xmlns:bqbiol="http://biomodels.net/biology-qualifiers/"
   xmlns:bqmodel="http://biomodels.net/model-qualifiers/"
   xmlns:dcterms="http://purl.org/dc/terms/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"
  <rdf:Description rdf:about="aslanidi_atrial_model_2009_LindbladCa_corrected.cellml#Ca_handling_by_the_SR.Ca_i">
    <bqbiol:isPropertyOf rdf:resource="aslanidi_a"""
        self.gold_standard_test_by_line(self.gold_standard_url3, self.gold_standard_filename3, expected,
                                        "rdfxml-abbrev")

    def test_gold_standard4(self):
        expected = """<gerard_2009.cellml#Mdi.time> <http://biomodels.net/biology-qualifiers/is> <https://identifiers.org/opb/OPB_01023> .
<gerard_2009.cellml#BC.time> <http://biomodels.net/biology-qualifiers/is> <https://identifiers.org/opb/OPB_01023> .
<gerard_2009.cellml#Cb.Cb> <http://biomodels.net/biology-qualifiers/isPropertyOf> <gerard_2009.cellml#entity_34> .
<gerard_2009.cellml#Cb.Cb> <http://biomodels.net/biology-qualifiers/isVersionOf> <https://identifiers.org/opb/OPB_00340> .
<gerard_2009.cellml#p27.Md> <"""
        self.gold_standard_test(self.gold_standard_url4, self.gold_standard_filename4, expected, "ntriples")

    def test_gold_standard5(self):
        expected = """digraph {
	rankdir = LR;
	charset="utf-8";

	"RBIOMD0000000498.sbml#process_1" -> "RBIOMD0000000498.sbml#mediator_1" [ label="http://www.bhi.washington.edu/SemSim#hasMediatorParticipant" ];
	"RBIOMD0000000498.sbml#process_1" -> "RBIOMD0000000498.sbml#sink_1" [ label="http://www.bhi.washington.edu/SemSim#hasSinkParticipant" ];
	"RBIOMD0000000498.sbml#process_1" -> "RBIOMD0000000498.sbml#source_1" [ label="http://www.bhi.washington.edu/SemSim#hasSourceParticipant" ];
	"RBIOMD0000000498.sbml#proces"""
        self.gold_standard_test(self.gold_standard_url5, self.gold_standard_filename5, expected, "dot")

    def test_query(self):
        self.download_file(self.gold_standard_url3, self.gold_standard_filename3)
        s = self.extract_rdf_from_combine_archive(self.gold_standard_filename3)[0]
        rdf = RDF.from_string(s, "guess")
        query_str = """
        PREFIX bqbiol: <http://biomodels.net/biology-qualifiers/>
        SELECT ?x ?z
        WHERE {
            ?x bqbiol:isPropertyOf ?z
        }"""
        actual = rdf.query(query_str, "csv")[:500]
        expected = """x,z
aslanidi_atrial_model_2009_LindbladCa_corrected.cellml#sodium_current_i_Na,aslanidi_atrial_model_2009_LindbladCa_corrected.cellml#process_0
aslanidi_atrial_model_2009_LindbladCa_corrected.cellml#intracellular_ion_concentrations.i_up,aslanidi_atrial_model_2009_LindbladCa_corrected.cellml#process_13
aslanidi_atrial_model_2009_LindbladCa_corrected.cellml#T_type_Ca_channel_f_T_gate.V,aslanidi_atrial_model_2009_LindbladCa_corrected.cellml#entity_0
aslanidi_atrial_model_2009_LindbladCa_corrected.c"""

        self.assertEqual(expected, actual)

    def test_query2(self):
        self.download_file(self.gold_standard_url3, self.gold_standard_filename3)
        s = self.extract_rdf_from_combine_archive(self.gold_standard_filename3)[0]
        rdf = RDF.from_string(s, "guess")
        query_str = """
        PREFIX semsim: <http://www.bhi.washington.edu/semsim#>
        SELECT ?x ?z
        WHERE {
            ?x semsim:hasPhysicalEntityReference ?z
        }"""
        actual = rdf.query(query_str, "csv")

    #         expected = """x,z
    # aslanidi_atrial_model_2009_LindbladCa_corrected.cellml#sodium_current_i_Na,aslanidi_atrial_model_2009_LindbladCa_corrected.cellml#process_0
    # aslanidi_atrial_model_2009_LindbladCa_corrected.cellml#intracellular_ion_concentrations.i_up,aslanidi_atrial_model_2009_LindbladCa_corrected.cellml#process_13
    # aslanidi_atrial_model_2009_LindbladCa_corrected.cellml#T_type_Ca_channel_f_T_gate.V,aslanidi_atrial_model_2009_LindbladCa_corrected.cellml#entity_0
    # aslanidi_atrial_model_2009_LindbladCa_corrected.c"""

    #         self.assertEqual(expected, actual)

    def test_to_triples(self):
        self.download_file(self.gold_standard_url3, self.gold_standard_filename3)
        s = self.extract_rdf_from_combine_archive(self.gold_standard_filename3)[0]
        rdf = RDF.from_string(s, "guess")

        print(rdf)

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
        with rdf.to_editor(sbml1, "sbml") as editor:
            print(editor.get_xml())
            with editor.new_singular_annotation() as singular_annotation:
                singular_annotation.set_about("SemsimMetaid0000") \
                    .set_predicate("bqb", "is") \
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
        with rdf.to_editor(self.sbml, "sbml") as editor:
            with editor.new_singular_annotation() as s:
                s.set_about("SemsimMetaid0000") \
                    .set_predicate("bqb", "is") \
                    .set_resource_uri("fma/FMA_66835")
        fname = os.path.join(os.path.realpath("."), "test_draw.png")
        rdf.draw(fname)
        self.assertTrue(os.path.isfile(fname))
        os.remove(fname)


if __name__ == "__main__":
    unittest.main()
