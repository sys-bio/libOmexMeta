import libcombine
import os
import requests
import sys
import typing
import unittest

# add the source directory to path so we can import code we are testing
_PYTHON_TESTS_DIR = os.path.dirname(__file__)
_TESTS_DIR = os.path.dirname(_PYTHON_TESTS_DIR)
_PROJECT_ROOT = os.path.dirname(_TESTS_DIR)
_SRC_DIR = os.path.join(_PROJECT_ROOT, "src")

sys.path += [_PYTHON_TESTS_DIR, _SRC_DIR]

# module not found by IDE, but it does exist and and tests do run
from pyomexmeta import *
from test_strings import TestStrings

try:
    import tellurium as te
except ImportError:
    raise ImportError("package \"tellurium\" not found. Please `pip install tellurium`")

antimony = """
model TestModel
    r1: A -> B; S*k1*A;
    r2: B -> A; k2*B;
    r3: C -> D; k3*B*C;
    r4: D -> A; k4*D;
    A = 100; 
    B = 0; 
    C = 100; 
    D = 0; 
    S = 1;
    k1 = 0.1;
    k2 = 0.1;
    k3 = 0.1;
    k4 = 0.1;
    compartment nucleus = 1;
    compartment cytosol = 1;
    A in nucleus;
    B in nucleus; 
    C in cytosol;
    D in cytosol;    
end
"""

SBML = te.loada(antimony).getSBML()


class TestRDF(unittest.TestCase):
    rdf_str = """<?xml version="1.1" encoding="utf-8"?>
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

    sbml_uri = "https://www.ebi.ac.uk/biomodels/model/download/BIOMD0000000064.2?filename=BIOMD0000000064_url.xml"

    sbml_file = os.path.join(os.getcwd(), "sbml_file_for_tests.sbml")

    sqlite_fname = os.path.join(os.path.dirname(__file__), "sqlite_db_from_python.db")

    def setUp(self) -> None:
        with open(self.sbml_file, "w") as f:
            f.write(self.rdf_str)

    def tearDown(self) -> None:
        teardown = True
        if teardown:
            if os.path.isfile(self.sbml_file):
                os.remove(self.sbml_file)

            try:
                if os.path.isfile(self.sqlite_fname):
                    os.remove(self.sqlite_fname)
            except PermissionError:
                pass

    def test_crete_new_rdf_obj(self):
        rdf = RDF()
        self.assertIsInstance(rdf._obj, int)

    def test_from_string(self):
        rdf = RDF.from_string(self.rdf_str, "rdfxml")
        print(rdf)
        self.assertEqual(6, len(rdf))

    def test_from_string_for_docs(self):
        rdf_str = """@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
@prefix OMEXlib: <http://omex-library.org/> .
@prefix myOMEX: <http://omex-library.org/NewOmex.omex> .
@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .
<http://omex-library.org/NewOmex.omex/NewModel.xml#>
<http://purl.org/dc/terms/creator> <https://orcid.org/1234-1234-1234-1234> .
"""
        rdf = RDF.from_string(rdf_str, "turtle")
        self.assertEqual(1, len(rdf))

    def test_add_from_string(self):
        rdf = RDF()
        rdf.add_from_string(self.rdf_str, "rdfxml")
        self.assertEqual(6, len(rdf))

    @unittest.skip("url broken")
    def test_from_uri(self):
        rdf = RDF.from_uri(self.sbml_uri, "rdfxml")
        self.assertEqual(277, len(rdf))

    @unittest.skip("url broken")
    def test_add_from_uri(self):
        rdf = RDF()
        rdf.add_from_uri(self.sbml_uri, "rdfxml")
        self.assertEqual(277, len(rdf))

    def test_from_file(self):
        rdf = RDF.from_file(self.sbml_file, "rdfxml")
        self.assertEqual(6, len(rdf))

    def test_add_from_file(self):
        rdf = RDF()
        rdf.add_from_file(self.sbml_file, "rdfxml")
        self.assertEqual(6, len(rdf))

    def test_set_repository_uri(self):
        rdf = RDF()
        rdf.set_repository_uri("https://my-awesome-repository.org")
        actual = rdf.get_repository_uri()
        expected = "https://my-awesome-repository.org/"
        self.assertEqual(expected, actual)

    def test_set_model_metaid(self):
        rdf = RDF()
        rdf.set_model_metaid("ModelMetaid")
        metaid = rdf.get_model_metaid()
        self.assertEqual("ModelMetaid", metaid)
        full_uri = rdf.get_model_level_annotation_uri()
        expected = "http://omex-library.org/NewOmex.omex/NewModel.xml#ModelMetaid"
        self.assertEqual(expected, full_uri)

    def test_get_model_level_annotation_uri(self):
        rdf = RDF()
        full_uri = rdf.get_model_level_annotation_uri()
        expected = "http://omex-library.org/NewOmex.omex/NewModel.xml#NewModel"
        self.assertEqual(expected, full_uri)

    def test_set_archive_uri(self):
        rdf = RDF()
        rdf.set_archive_uri("my-awesome-archive.omex")
        actual = rdf.get_archive_uri()
        expected = "http://omex-library.org/my-awesome-archive.omex/"
        self.assertEqual(expected, actual)

    def test_set_model_uri(self):
        rdf = RDF()
        rdf.set_model_uri("my-awesome-model.xml")
        actual = rdf.get_model_uri()
        expected = "http://omex-library.org/NewOmex.omex/my-awesome-model.xml"
        self.assertEqual(expected, actual)

    def test_get_repository_uri(self):
        rdf = RDF()
        actual = rdf.get_repository_uri()
        expected = "http://omex-library.org/"
        self.assertEqual(expected, actual)

    def test_get_archive_uri(self):
        rdf = RDF()
        actual = rdf.get_archive_uri()
        expected = "http://omex-library.org/NewOmex.omex/"
        self.assertEqual(expected, actual)

    def test_get_model_uri(self):
        rdf = RDF()
        actual = rdf.get_model_uri()
        expected = "http://omex-library.org/NewOmex.omex/NewModel.xml"
        self.assertEqual(expected, actual)

    def test_get_local_uri(self):
        rdf = RDF()
        actual = rdf.get_local_uri()
        expected = "http://omex-library.org/NewOmex.omex/NewModel.rdf#"
        self.assertEqual(expected, actual)

    def test_query_results_as_str(self):
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
        actual = rdf.query_results_as_string(q, "csv")
        self.assertEqual(expected, actual)

    def test_query_results_as_dict(self):

        rdf = RDF.from_string(TestStrings.sbml_with_annotations, "rdfxml")
        query_str = """
        SELECT ?x ?y ?z
        WHERE {
            ?x ?y ?z
        }"""
        results = rdf.query_results_as_dict(query_str)
        self.assertIsInstance(results, dict)
        self.assertEqual(3, len(results))
        self.assertEqual(28, len(results['x']))

    def test_use_sqlite_storage(self):
        rdf = RDF("sqlite", self.sqlite_fname, "new='yes'")
        rdf.add_from_string(self.rdf_str, syntax="rdfxml")
        self.assertTrue(os.path.isfile(self.sqlite_fname))


class EditorTests(unittest.TestCase):
    maxDiff = None

    def setUp(self) -> None:
        self.rdf = RDF()
        self.editor = self.rdf.to_editor(SBML, True, False)

    def test_to_editor(self):
        self.assertIsInstance(self.editor, Editor)

    def test_context_manager_single_annotation_with_sbml_extraction(self):
        editor = self.rdf.to_editor(SBML, generate_new_metaids=True, sbml_semantic_extraction=True)
        with editor.new_singular_annotation() as singular_annotation:
            singular_annotation \
                .about("species0000") \
                .predicate("bqbiol", "is") \
                .resource_uri("uniprot:PD88776")
        expected = """@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .
@prefix semsim: <http://bime.uw.edu/semsim/> .
@prefix OMEXlib: <http://omex-library.org/> .
@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .

local:MediatorParticipant0000
    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#species0001> .

local:ProcessProperty0000
    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#reaction0000> ;
    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_00592> .

local:ProcessProperty0001
    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#reaction0001> ;
    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_00592> .

local:ProcessProperty0002
    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#reaction0002> ;
    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_00592> .

local:ProcessProperty0003
    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#reaction0003> ;
    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_00592> .

local:SinkParticipant0000
    semsim:hasMultiplier "1"^^rdf:double ;
    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#species0001> .

local:SinkParticipant0001
    semsim:hasMultiplier "1"^^rdf:double ;
    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#species0000> .

local:SinkParticipant0002
    semsim:hasMultiplier "1"^^rdf:double ;
    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#species0003> .

local:SinkParticipant0003
    semsim:hasMultiplier "1"^^rdf:double ;
    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#species0000> .

local:SourceParticipant0000
    semsim:hasMultiplier "1"^^rdf:double ;
    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#species0000> .

local:SourceParticipant0001
    semsim:hasMultiplier "1"^^rdf:double ;
    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#species0001> .

local:SourceParticipant0002
    semsim:hasMultiplier "1"^^rdf:double ;
    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#species0002> .

local:SourceParticipant0003
    semsim:hasMultiplier "1"^^rdf:double ;
    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#species0003> .

<http://omex-library.org/NewOmex.omex/NewModel.xml#reaction0000>
    semsim:hasSinkParticipant local:SinkParticipant0000 ;
    semsim:hasSourceParticipant local:SourceParticipant0000 .

<http://omex-library.org/NewOmex.omex/NewModel.xml#reaction0001>
    semsim:hasSinkParticipant local:SinkParticipant0001 ;
    semsim:hasSourceParticipant local:SourceParticipant0001 .

<http://omex-library.org/NewOmex.omex/NewModel.xml#reaction0002>
    semsim:hasMediatorParticipant local:MediatorParticipant0000 ;
    semsim:hasSinkParticipant local:SinkParticipant0002 ;
    semsim:hasSourceParticipant local:SourceParticipant0002 .

<http://omex-library.org/NewOmex.omex/NewModel.xml#reaction0003>
    semsim:hasSinkParticipant local:SinkParticipant0003 ;
    semsim:hasSourceParticipant local:SourceParticipant0003 .

<http://omex-library.org/NewOmex.omex/NewModel.xml#species0000>
    bqbiol:is <https://identifiers.org/uniprot:PD88776> ;
    bqbiol:isPartOf <http://omex-library.org/NewOmex.omex/NewModel.xml#nucleus> .

<http://omex-library.org/NewOmex.omex/NewModel.xml#species0001>
    bqbiol:isPartOf <http://omex-library.org/NewOmex.omex/NewModel.xml#nucleus> .

<http://omex-library.org/NewOmex.omex/NewModel.xml#species0002>
    bqbiol:isPartOf <http://omex-library.org/NewOmex.omex/NewModel.xml#cytosol> .

<http://omex-library.org/NewOmex.omex/NewModel.xml#species0003>
    bqbiol:isPartOf <http://omex-library.org/NewOmex.omex/NewModel.xml#cytosol> ."""
        self.assertTrue(RDF.equals_rdf_vs_string(self.rdf, expected))

    def test_context_manager_single_annotation_without_sbml_extraction(self):
        editor = self.rdf.to_editor(SBML, generate_new_metaids=True, sbml_semantic_extraction=False)
        with editor.new_singular_annotation() as singular_annotation:
            singular_annotation \
                .about("#species0000") \
                .predicate("bqbiol", "is") \
                .resource_uri("uniprot:PD88776")
        expected = """@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .
@prefix OMEXlib: <http://omex-library.org/> .
@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .
@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .

<http://omex-library.org/NewOmex.omex/NewModel.xml#species0000>
    bqbiol:is <https://identifiers.org/uniprot:PD88776> .
"""
        self.assertTrue(RDF.equals_rdf_vs_string(self.rdf, expected))

    def test_context_manager_single_annotation_simple(self):
        editor = self.rdf.to_editor(SBML, generate_new_metaids=True, sbml_semantic_extraction=False)
        with editor.new_singular_annotation() as example01_singular_annotation:
            example01_singular_annotation.about("species0000") \
                .predicate("bqbiol", "is") \
                .resource_uri("CHEBI:16236")
        expected = """@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .
@prefix OMEXlib: <http://omex-library.org/> .
@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .
@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .

<http://omex-library.org/NewOmex.omex/NewModel.xml#species0000>
    bqbiol:is <https://identifiers.org/CHEBI:16236> .

"""
        self.assertTrue(RDF.equals_rdf_vs_string(self.rdf, expected))

    def test_context_manager_single_annotation_simple2(self):
        editor = self.rdf.to_editor(SBML, generate_new_metaids=True, sbml_semantic_extraction=False)
        with editor.new_singular_annotation() as example01_singular_annotation:
            example01_singular_annotation.about("species0000")
            example01_singular_annotation.predicate("bqbiol", "is")
            example01_singular_annotation.resource_uri("CHEBI:16236")
        expected = """@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .
@prefix OMEXlib: <http://omex-library.org/> .
@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .
@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .

<http://omex-library.org/NewOmex.omex/NewModel.xml#species0000>
    bqbiol:is <https://identifiers.org/CHEBI:16236> .

"""
        self.assertTrue(RDF.equals_rdf_vs_string(self.rdf, expected))

    def test_context_manager_personal_information(self):
        editor = self.rdf.to_editor(SBML, True, False)
        with editor.new_personal_information() as information:
            information \
                .add_creator("1234-1234-1234-1234") \
                .add_mbox("annotations@uw.edu") \
                .add_name("Joe Smith")

        expected = """@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
@prefix dc: <http://purl.org/dc/terms/> .
@prefix foaf: <http://xmlns.com/foaf/0.1/> .
@prefix OMEXlib: <http://omex-library.org/> .
@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .
@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .

<http://omex-library.org/NewOmex.omex/NewModel.xml#TestModel>
    dc:creator <http://omex-library.org/NewOmex.omex/NewModel.xml#PersonalInfo0000> .

<http://omex-library.org/NewOmex.omex/NewModel.xml#PersonalInfo0000>
    foaf:mbox "annotations@uw.edu" ;
    foaf:name "Joe Smith" ;
    dc:creator <https://identifiers.org/orcid/1234-1234-1234-1234> .

"""
        self.assertTrue(RDF.equals_rdf_vs_string(self.rdf, expected, "turtle", True))

    def test_physical_entity_sbml1(self):
        editor = self.rdf.to_editor(TestStrings.sbml, True, False)
        property = editor.new_physical_property()
        property.about("EntityProperty", eUriType.LOCAL_URI) \
            .is_version_of("opb:OPB_12345") \
            .is_property_of("species0001", eUriType.MODEL_URI)

        with editor.new_physical_entity() as physical_entity:
            physical_entity.about("species0001", eUriType.MODEL_URI) \
                .identity("uniprot:PD12345") \
                .is_part_of("fma:1234") \
                .has_property(property=property)
        expected = """@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .
@prefix OMEXlib: <http://omex-library.org/> .
@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .
@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .

local:EntityProperty
    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#species0001> ;
    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_12345> .

<http://omex-library.org/NewOmex.omex/NewModel.xml#species0001>
    bqbiol:is <https://identifiers.org/uniprot:PD12345> ;
    bqbiol:isPartOf <https://identifiers.org/fma:1234> ."""
        self.assertTrue(RDF.equals_rdf_vs_string(self.rdf, expected))

    def test_physical_entity_sbml2(self):
        editor = self.rdf.to_editor(TestStrings.sbml, True, False)
        with editor.new_physical_entity() as physical_entity:
            physical_entity.about("species0000", eUriType.MODEL_URI) \
                .identity("uniprot:PD12345") \
                .is_part_of("fma:1234") \
                .has_property("EntityProperty", eUriType.LOCAL_URI, "opb:OPB_12345")
        expected = """@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .
@prefix OMEXlib: <http://omex-library.org/> .
@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .
@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .

local:EntityProperty
    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#species0000> ;
    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_12345> .

<http://omex-library.org/NewOmex.omex/NewModel.xml#species0000>
    bqbiol:is <https://identifiers.org/uniprot:PD12345> ;
    bqbiol:isPartOf <https://identifiers.org/fma:1234> .
"""
        self.assertTrue(RDF.equals_rdf_vs_string(self.rdf, expected))

    def test_physical_entity_sbml3(self):
        editor = self.rdf.to_editor(TestStrings.sbml, True, False)
        with editor.new_physical_entity() as physical_entity:
            physical_entity.about("species0000", eUriType.MODEL_URI) \
                .identity("uniprot:PD12345") \
                .is_part_of("fma:1234") \
                .has_property("opb:OPB_12345")
        expected = """@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .
@prefix OMEXlib: <http://omex-library.org/> .
@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .
@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .

local:EntityProperty0000
    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#species0000> ;
    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_12345> .

<http://omex-library.org/NewOmex.omex/NewModel.xml#species0000>
    bqbiol:is <https://identifiers.org/uniprot:PD12345> ;
    bqbiol:isPartOf <https://identifiers.org/fma:1234> .
"""
        self.assertTrue(RDF.equals_rdf_vs_string(self.rdf, expected))

    def test_physical_entity_sbml4(self):
        editor = self.rdf.to_editor(TestStrings.sbml, True, False)
        with editor.new_physical_entity() as physical_entity:
            physical_entity.about("species0000", eUriType.MODEL_URI) \
                .identity("uniprot:PD12345") \
                .is_part_of("fma:1234")
        expected = """@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .
@prefix OMEXlib: <http://omex-library.org/> .
@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .
@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .

<http://omex-library.org/NewOmex.omex/NewModel.xml#species0000>
    bqbiol:is <https://identifiers.org/uniprot:PD12345> ;
    bqbiol:isPartOf <https://identifiers.org/fma:1234> .
"""
        self.assertTrue(RDF.equals_rdf_vs_string(self.rdf, expected))

    def test_physical_entity_cellml1(self):
        editor = self.rdf.to_editor(TestStrings.cellml, True, False)
        property = editor.new_physical_property()
        property.about("main.Volume", eUriType.MODEL_URI) \
            .is_version_of("opb:OPB_00154") \
            .is_property_of("entity0", eUriType.LOCAL_URI)

        with editor.new_physical_entity() as physical_entity:
            physical_entity.about("entity0", eUriType.LOCAL_URI) \
                .identity("fma:9570") \
                .is_part_of("fma:18228") \
                .has_property(property=property)
        expected = """@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .
@prefix OMEXlib: <http://omex-library.org/> .
@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .
@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .

local:entity0
    bqbiol:is <https://identifiers.org/fma:9570> ;
    bqbiol:isPartOf <https://identifiers.org/fma:18228> .

<http://omex-library.org/NewOmex.omex/NewModel.xml#main.Volume>
    bqbiol:isPropertyOf local:entity0 ;
    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_00154> .
"""
        self.assertTrue(RDF.equals_rdf_vs_string(self.rdf, expected))

    def test_physical_entity_cellml2(self):
        editor = self.rdf.to_editor(TestStrings.cellml, True, False)

        with editor.new_physical_entity() as physical_entity:
            physical_entity.about("entity0", eUriType.LOCAL_URI) \
                .identity("fma:9570") \
                .is_part_of("fma:18228") \
                .has_property("main.Volume", eUriType.MODEL_URI, "opb:OPB_00154")
        expected = """@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .
@prefix OMEXlib: <http://omex-library.org/> .
@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .
@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .

local:entity0
    bqbiol:is <https://identifiers.org/fma:9570> ;
    bqbiol:isPartOf <https://identifiers.org/fma:18228> .

<http://omex-library.org/NewOmex.omex/NewModel.xml#main.Volume>
    bqbiol:isPropertyOf local:entity0 ;
    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_00154> .
"""
        self.assertTrue(RDF.equals_rdf_vs_string(self.rdf, expected))

    def test_physical_entity_cellml3(self):
        editor = self.rdf.to_editor(TestStrings.cellml, True, False)

        with editor.new_physical_entity() as physical_entity:
            physical_entity \
                .identity("fma:9570") \
                .is_part_of("fma:18228") \
                .has_property(property_about="main.Volume", about_uri_type=eUriType.MODEL_URI,
                              is_version_of="opb:OPB_00154")
        expected = """@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .
@prefix OMEXlib: <http://omex-library.org/> .
@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .
@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .

local:Entity0000
    bqbiol:is <https://identifiers.org/fma:9570> ;
    bqbiol:isPartOf <https://identifiers.org/fma:18228> .

<http://omex-library.org/NewOmex.omex/NewModel.xml#main.Volume>
    bqbiol:isPropertyOf local:Entity0000 ;
    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_00154> .
"""
        self.assertTrue(RDF.equals_rdf_vs_string(self.rdf, expected))

    def test_physical_process_sbml1(self):
        editor = self.rdf.to_editor(TestStrings.sbml, True, False)
        with editor.new_physical_process() as physical_process:
            physical_process.about("reaction0000", eUriType.MODEL_URI) \
                .add_source("species0000", eUriType.MODEL_URI, 1) \
                .add_sink("species0001", eUriType.MODEL_URI, 1) \
                .add_mediator("species0002", eUriType.MODEL_URI) \
                .has_property("ReactionProperty", eUriType.LOCAL_URI, "opb:OPB_00592")
        expected = """@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
@prefix semsim: <http://bime.uw.edu/semsim/> .
@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .
@prefix OMEXlib: <http://omex-library.org/> .
@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .
@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .

local:MediatorParticipant0000
    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#species0002> .

local:ReactionProperty
    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#reaction0000> ;
    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_00592> .

local:SinkParticipant0000
    semsim:hasMultiplier "1"^^rdf:double ;
    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#species0001> .

local:SourceParticipant0000
    semsim:hasMultiplier "1"^^rdf:double ;
    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#species0000> .

<http://omex-library.org/NewOmex.omex/NewModel.xml#reaction0000>
    semsim:hasMediatorParticipant local:MediatorParticipant0000 ;
    semsim:hasSinkParticipant local:SinkParticipant0000 ;
    semsim:hasSourceParticipant local:SourceParticipant0000 .
"""
        self.assertTrue(RDF.equals_rdf_vs_string(self.rdf, expected))

    def test_physical_process_sbml2(self):
        editor = self.rdf.to_editor(TestStrings.sbml, True, False)
        with editor.new_physical_process() as physical_process:
            physical_process.about("reaction0000", eUriType.MODEL_URI) \
                .add_source("species0000", eUriType.MODEL_URI, 1) \
                .add_sink("species0001", eUriType.MODEL_URI, 1) \
                .add_mediator("species0002", eUriType.MODEL_URI) \
                .has_property(is_version_of="opb:OPB_00592")
        expected = """@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
@prefix semsim: <http://bime.uw.edu/semsim/> .
@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .
@prefix OMEXlib: <http://omex-library.org/> .
@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .
@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .

local:MediatorParticipant0000
    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#species0002> .

local:ProcessProperty0000
    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#reaction0000> ;
    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_00592> .

local:SinkParticipant0000
    semsim:hasMultiplier "1"^^rdf:double ;
    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#species0001> .

local:SourceParticipant0000
    semsim:hasMultiplier "1"^^rdf:double ;
    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#species0000> .

<http://omex-library.org/NewOmex.omex/NewModel.xml#reaction0000>
    semsim:hasMediatorParticipant local:MediatorParticipant0000 ;
    semsim:hasSinkParticipant local:SinkParticipant0000 ;
    semsim:hasSourceParticipant local:SourceParticipant0000 .
"""
        self.assertTrue(RDF.equals_rdf_vs_string(self.rdf, expected))

    def test_physical_process_cellml1(self):
        editor = self.rdf.to_editor(TestStrings.cellml, True, False)
        with editor.new_physical_process() as physical_process:
            physical_process.about("Process", eUriType.LOCAL_URI) \
                .add_source("entity1", eUriType.LOCAL_URI, 1) \
                .add_sink("entity2", eUriType.LOCAL_URI, 1) \
                .add_mediator("entity3", eUriType.LOCAL_URI) \
                .has_property("main.ReactionRate", eUriType.MODEL_URI, "opb:OPB_00592")
        expected = """@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
@prefix semsim: <http://bime.uw.edu/semsim/> .
@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .
@prefix OMEXlib: <http://omex-library.org/> .
@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .
@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .

local:MediatorParticipant0000
    semsim:hasPhysicalEntityReference local:entity3 .

local:Process
    semsim:hasMediatorParticipant local:MediatorParticipant0000 ;
    semsim:hasSinkParticipant local:SinkParticipant0000 ;
    semsim:hasSourceParticipant local:SourceParticipant0000 .

local:SinkParticipant0000
    semsim:hasMultiplier "1"^^rdf:double ;
    semsim:hasPhysicalEntityReference local:entity2 .

local:SourceParticipant0000
    semsim:hasMultiplier "1"^^rdf:double ;
    semsim:hasPhysicalEntityReference local:entity1 .

<http://omex-library.org/NewOmex.omex/NewModel.xml#main.ReactionRate>
    bqbiol:isPropertyOf local:Process ;
    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_00592> .
"""
        self.assertTrue(RDF.equals_rdf_vs_string(self.rdf, expected))

    def test_physical_process_cellml2(self):
        editor = self.rdf.to_editor(TestStrings.cellml, True, False)
        with editor.new_physical_process() as physical_process:
            physical_process \
                .add_source("entity1", eUriType.LOCAL_URI, 1) \
                .add_sink("entity2", eUriType.LOCAL_URI, 1) \
                .add_mediator("entity3", eUriType.LOCAL_URI) \
                .has_property(property_about="main.ReactionRate", about_uri_type=eUriType.MODEL_URI,
                              is_version_of="opb:OPB_00592")
        expected = """@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
@prefix semsim: <http://bime.uw.edu/semsim/> .
@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .
@prefix OMEXlib: <http://omex-library.org/> .
@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .
@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .

local:MediatorParticipant0000
    semsim:hasPhysicalEntityReference local:entity3 .

local:Process0000
    semsim:hasMediatorParticipant local:MediatorParticipant0000 ;
    semsim:hasSinkParticipant local:SinkParticipant0000 ;
    semsim:hasSourceParticipant local:SourceParticipant0000 .

local:SinkParticipant0000
    semsim:hasMultiplier "1"^^rdf:double ;
    semsim:hasPhysicalEntityReference local:entity2 .

local:SourceParticipant0000
    semsim:hasMultiplier "1"^^rdf:double ;
    semsim:hasPhysicalEntityReference local:entity1 .

<http://omex-library.org/NewOmex.omex/NewModel.xml#main.ReactionRate>
    bqbiol:isPropertyOf local:Process0000 ;
    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_00592> .

"""
        self.assertTrue(RDF.equals_rdf_vs_string(self.rdf, expected))

    def test_energy_diff_sbml1(self):
        editor = self.rdf.to_editor(TestStrings.sbml, True, False)
        with editor.new_energy_diff() as energy_diff:
            energy_diff.about("reaction0000", eUriType.MODEL_URI) \
                .add_source("species0000", eUriType.MODEL_URI) \
                .add_sink("species0001", eUriType.MODEL_URI) \
                .has_property("localParameter0000", eUriType.LOCAL_URI, "opb:OPB_01058")
        expected = """@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
@prefix semsim: <http://bime.uw.edu/semsim/> .
@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .
@prefix OMEXlib: <http://omex-library.org/> .
@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .
@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .

local:SinkParticipant0000
    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#species0001> .

local:SourceParticipant0000
    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#species0000> .

local:localParameter0000
    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#reaction0000> ;
    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_01058> .

<http://omex-library.org/NewOmex.omex/NewModel.xml#reaction0000>
    semsim:hasSinkParticipant local:SinkParticipant0000 ;
    semsim:hasSourceParticipant local:SourceParticipant0000 .

"""
        self.assertTrue(RDF.equals_rdf_vs_string(self.rdf, expected))

    def test_energy_diff_sbml2(self):
        editor = self.rdf.to_editor(TestStrings.sbml, True, False)
        with editor.new_energy_diff() as energy_diff:
            energy_diff.about("reaction0001", eUriType.MODEL_URI) \
                .add_source("species0001", eUriType.MODEL_URI) \
                .add_sink("species0000", eUriType.MODEL_URI) \
                .has_property(is_version_of="opb:OPB_01058")
        expected = """@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
@prefix semsim: <http://bime.uw.edu/semsim/> .
@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .
@prefix OMEXlib: <http://omex-library.org/> .
@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .
@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .

local:EnergyDiffProperty0000
    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#reaction0001> ;
    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_01058> .

local:SinkParticipant0000
    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#species0000> .

local:SourceParticipant0000
    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#species0001> .

<http://omex-library.org/NewOmex.omex/NewModel.xml#reaction0001>
    semsim:hasSinkParticipant local:SinkParticipant0000 ;
    semsim:hasSourceParticipant local:SourceParticipant0000 .
"""
        self.assertTrue(RDF.equals_rdf_vs_string(self.rdf, expected))

    def test_energy_diff_sbml3(self):
        sbml = """<sbml xmlns="http://www.sbml.org/sbml/level3/version1/core" level="3" version="1">
      <model metaid="NernstExample" id="NernstExample">
        <listOfCompartments>
          <compartment id="cytoplasm" metaid="cytoplasm" spatialDimensions="3" size="1" constant="true"/>
          <compartment id="extracellular" metaid="extracellular" spatialDimensions="3" size="1" constant="true"/>
        </listOfCompartments>
        <listOfSpecies>
          <species id="Ca_ex" metaid="Ca_ex" compartment="extracellular" initialConcentration="2" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>
          <species id="Ca_cyt" metaid="Ca_cyt" compartment="cytoplasm" initialConcentration="0.07" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>
        </listOfSpecies>
        <listOfParameters>
          <parameter id="NP" metaid="NernstPotential" value="137.04" constant="true"/>
        </listOfParameters>
        </model>
    </sbml>"""
        rdf_graph = RDF()
        rdf_graph.set_archive_uri("Example.omex")
        rdf_graph.set_model_uri("Example.sbml")

        editor = rdf_graph.to_editor(sbml, generate_new_metaids=False, sbml_semantic_extraction=False)

        # Ca_cyt: Calcium Ions cytosol
        # Ca_ex: Calcium Ions extracellular space
        # NernstReversalPotential_in: The metaID of the SBML reaction
        # OPB/OPB_01581: Nernst reversal potential
        with editor.new_energy_diff() as energy_in:
            energy_in \
                .about("EnergyDiff000", eUriType.LOCAL_URI) \
                .add_source(physical_entity_reference="Ca_ex", uri_type=eUriType.MODEL_URI) \
                .add_sink(physical_entity_reference="Ca_cyt", uri_type=eUriType.MODEL_URI) \
                .has_property(property_about="NernstPotential", about_uri_type=eUriType.MODEL_URI,
                              is_version_of="OPB:OPB_01581")

        print(rdf_graph)

    def test_energy_diff_cellml1(self):
        editor = self.rdf.to_editor(TestStrings.cellml, True, False)
        with editor.new_energy_diff() as energy_diff:
            energy_diff.about("main.MembraneVoltage", eUriType.MODEL_URI) \
                .add_source("entity1", eUriType.LOCAL_URI) \
                .add_sink("entity2", eUriType.LOCAL_URI) \
                .has_property("EnergyDiffProperty", eUriType.MODEL_URI, "opb:OPB_00592")
        expected = """@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
@prefix semsim: <http://bime.uw.edu/semsim/> .
@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .
@prefix OMEXlib: <http://omex-library.org/> .
@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .
@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .

local:SinkParticipant0000
    semsim:hasPhysicalEntityReference local:entity2 .

local:SourceParticipant0000
    semsim:hasPhysicalEntityReference local:entity1 .

<http://omex-library.org/NewOmex.omex/NewModel.xml#EnergyDiffProperty>
    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#main.MembraneVoltage> ;
    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_00592> .

<http://omex-library.org/NewOmex.omex/NewModel.xml#main.MembraneVoltage>
    semsim:hasSinkParticipant local:SinkParticipant0000 ;
    semsim:hasSourceParticipant local:SourceParticipant0000 .
"""
        self.assertTrue(RDF.equals_rdf_vs_string(self.rdf, expected))

    def test_energy_diff_cellml2(self):
        editor = self.rdf.to_editor(TestStrings.cellml, True, False)
        with editor.new_energy_diff() as energy_diff:
            energy_diff.about("main.MembraneVoltage", eUriType.MODEL_URI) \
                .add_source("entity1", eUriType.LOCAL_URI) \
                .add_sink("entity2", eUriType.LOCAL_URI) \
                .has_property("EnergyDiffProperty", eUriType.MODEL_URI, "opb:OPB_00592")
        expected = """@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
@prefix semsim: <http://bime.uw.edu/semsim/> .
@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .
@prefix OMEXlib: <http://omex-library.org/> .
@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .
@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .

local:SinkParticipant0000
    semsim:hasPhysicalEntityReference local:entity2 .

local:SourceParticipant0000
    semsim:hasPhysicalEntityReference local:entity1 .

<http://omex-library.org/NewOmex.omex/NewModel.xml#EnergyDiffProperty>
    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#main.MembraneVoltage> ;
    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_00592> .

<http://omex-library.org/NewOmex.omex/NewModel.xml#main.MembraneVoltage>
    semsim:hasSinkParticipant local:SinkParticipant0000 ;
    semsim:hasSourceParticipant local:SourceParticipant0000 .
"""
        self.assertTrue(RDF.equals_rdf_vs_string(self.rdf, expected))

    def test_strip_annotations(self):
        expected = """<?xml version="1.0" encoding="UTF-8"?>
<sbml xmlns="http://www.sbml.org/sbml/level3/version1/core" level="3" version="1">
    <model metaid="ToyModel" id="ToyModel">
        <listOfCompartments>
            <compartment id="cytosol" metaid="comp1" spatialDimensions="3" size="1" constant="true"/>
            <compartment id="extraCell" metaid="comp2" spatialDimensions="3" size="10" constant="true"/>
        </listOfCompartments>
        <listOfSpecies>
            <species id="A" metaid="sp_1" compartment="cytosol" initialConcentration="10" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false">
                
            </species>
            <species id="B" metaid="sp_2" compartment="cytosol" initialConcentration="0" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>
            <species id="Ca" metaid="sp_3" compartment="cytosol" initialConcentration="2" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>
            <species id="PlasmaCa" metaid="sp_4" compartment="extraCell" initialConcentration="3" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>
            <species id="Enzyme" metaid="sp_5" compartment="cytosol" initialConcentration="2" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>
        </listOfSpecies>
        <listOfParameters>
            <parameter id="k1" value="0.1" constant="true"/>
            <parameter id="k2" value="0.1" constant="true"/>
        </listOfParameters>
        <listOfReactions>
            <reaction id="r1" metaid="react1" reversible="false" fast="false">
                <listOfReactants>
                    <speciesReference species="B" stoichiometry="1" constant="true"/>
                </listOfReactants>
                <listOfProducts>
                    <speciesReference species="A" stoichiometry="2" constant="true"/>
                </listOfProducts>
                <kineticLaw>
                    <math xmlns="http://www.w3.org/1998/Math/MathML">
                        <apply>
                            <times/>
                            <ci>k2</ci>
                            <ci>B</ci>
                        </apply>
                    </math>
                </kineticLaw>
            </reaction>
            <reaction id="r2" metaid="react2" reversible="false" fast="false">
                <listOfReactants>
                    <speciesReference species="Ca" stoichiometry="1" constant="true"/>
                    <speciesReference species="A" stoichiometry="1" constant="true"/>
                </listOfReactants>
                <listOfProducts>
                    <speciesReference species="PlasmaCa" stoichiometry="1" constant="true"/>
                </listOfProducts>
                <listOfModifiers>
                    <modifierSpeciesReference species="Enzyme"/>
                </listOfModifiers>
                <kineticLaw>
                    <math xmlns="http://www.w3.org/1998/Math/MathML">
                        <apply>
                            <times/>
                            <ci>k2</ci>
                            <ci>Ca</ci>
                        </apply>
                    </math>
                </kineticLaw>
            </reaction>
        </listOfReactions>
    </model>
</sbml>
"""
        editor = self.rdf.to_editor(TestStrings.sbml_with_annotations, False, False)
        stripped = editor.strip_annotations()
        self.assertEqual(expected, stripped)

    def test_get_xml_with_broken_xml(self):
        s = """<?xml version="1.0" encoding="UTF-8"?>
<!-- Created by libAntimony version v2.11.0 with libSBML version 5.18.0. -->
<sbml xmlns="http://www.sbml.org/sbml/level3/version1/core" level="3" version="1">
  <model metaid="SimpleRegulation" id="SimpleRegulation">
    <listOfCompartments>
      <compartment id="cell" spatialDimensions="3" size="1" constant="true" metaid="#OmexMetaId0000"/>
    </listOfCompartments>
    <listOfSpecies>
      <species id="A" compartment="cell" initialConcentration="10" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false" metaid="#OmexMetaId0001"/>
      <species id="B" compartment="cell" initialConcentration="0" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false" metaid="#OmexMetaId0002"/>
      <species id="C" compartment="cell" initialConcentration="10" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false" metaid="#OmexMetaId0003"/>
      <species id="D" compartment="cell" initialConcentration="0" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false" metaid="#OmexMetaId0004"/>
    </listOfSpecies>
    <listOfParameters>
      <parameter id="S" value="0" constant="true"/>
      <parameter id="k1" value="0.1" constant="true"/>
      <parameter id="k2" value="0.1" constant="true"/>
      <parameter id="k3" value="0.1" constant="true"/>
      <parameter id="k4" value="0.1" constant="true"/>
    </listOfParameters>
    <listOfReactions>
      <reaction id="R1" reversible="false" fast="false" metaid="#OmexMetaId0005">
        <listOfReactants>
          <speciesReference species="A" stoichiometry="1" constant="true"/>
        </listOfReactants>
        <listOfProducts>
          <speciesReference species="B" stoichiometry="1" constant="true"/>
        </listOfProducts>
        <kineticLaw metaid="#OmexMetaId0006">
          <math xmlns="http://www.w3.org/1998/Math/MathML">
            <apply>
              <times/>
              <ci> k1 </ci>
              <ci> A </ci>
              <ci> S </ci>
            </apply>
          </math>
        </kineticLaw>
      </reaction>
      <reaction id="R2" reversible="false" fast="false" metaid="#OmexMetaId0007">
        <listOfReactants>
          <speciesReference species="B" stoichiometry="1" constant="true"/>
        </listOfReactants>
        <listOfProducts>
          <speciesReference species="A" stoichiometry="1" constant="true"/>
        </listOfProducts>
        <kineticLaw metaid="#OmexMetaId0008">
          <math xmlns="http://www.w3.org/1998/Math/MathML">
            <apply>
              <times/>
              <ci> k2 </ci>
              <ci> B </ci>
            </apply>
          </math>
        </kineticLaw>
      </reaction>
      <reaction id="R3" reversible="false" fast="false" metaid="#OmexMetaId0009">
        <listOfReactants>
          <speciesReference species="C" stoichiometry="1" constant="true"/>
        </listOfReactants>
        <listOfProducts>
          <speciesReference species="D" stoichiometry="1" constant="true"/>
        </listOfProducts>
        <listOfModifiers>
          <modifierSpeciesReference species="B"/>
        </listOfModifiers>
        <kineticLaw metaid="#OmexMetaId0010">
          <math xmlns="http://www.w3.org/1998/Math/MathML">
            <apply>
              <times/>
              <ci> k3 </ci>
              <ci> C </ci>
              <ci> B </ci>
            </apply>
          </math>
        </kineticLaw>
      </reaction>
      <reaction id="R4" reversible="false" fast="false" metaid="#OmexMetaId0011">
        <listOfReactants>
          <speciesReference species="D" stoichiometry="1" constant="true"/>
        </listOfReactants>
        <listOfProducts>
          <speciesReference species="C" stoichiometry="1" constant="true"/>
        </listOfProducts>
        <kineticLaw metaid="#OmexMetaId0012">
          <math xmlns="http://www.w3.org/1998/Math/MathML">
            <apply>
              <times/>
              <ci> k4 </ci>
              <ci> D </ci>
            </apply>
          </math>
        </kineticLaw>
      </reaction>
    </listOfReactions>
  </model>
</sbml>"""
        # fails because of extraction
        editor = self.rdf.to_editor(s, False, True)
        try:
            editor.get_xml()
        except Exception:
            self.fail("get_xml() failed with ValueError")


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
        editor = rdf.to_editor(self.sbml, generate_new_metaids=True)
        metaids = editor.get_metaids()

        expected = ['SmadNuclearTransport',
                    'compartment0000',
                    'compartment0001',
                    'species0000',
                    'species0001',
                    'parameter0000',
                    'parameter0001',
                    'reaction0000',
                    'kineticLaw0000',
                    'reaction0001',
                    'kineticLaw0001']
        actual = metaids
        self.assertEqual(expected, actual)

    def test_get_xml(self):
        rdf = RDF()
        editor = rdf.to_editor(self.sbml, generate_new_metaids=True)
        xml_with_metaids = editor.get_xml()

        expected = """<?xml version="1.1" encoding="UTF-8"?>
<!-- Created by libAntimony version v2.12.0.3 with libSBML version 5.18.1. -->
<sbml xmlns="http://www.sbml.org/sbml/level3/version1/core" level="3" version="1">
  <model metaid="SmadNuclearTransport" id="SmadNuclearTransport">
    <listOfCompartments>
      <compartment id="cytosol" spatialDimensions="3" constant="true" metaid="#species0000"/>
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
        self.assertTrue(expected, actual)

    def test_annotate_model(self):
        """
        Tests the annotation of a model created in setup.

        Note: autogenerate the participant ID, currently users,
            are asked to give the id, but this isn't really necessary.
        Returns:

        """
        rdf = RDF()
        editor = rdf.to_editor(self.sbml, generate_new_metaids=True)
        # model level annotations
        with editor.new_singular_annotation() as author:
            author.about("SmadNuclearTransport") \
                .predicate_from_uri("https://unknownpredicate.com/changeme#author") \
                .resource_literal("Joe Smith")

        # annotate Smad3nuc
        with editor.new_physical_entity() as smad3nuc:
            smad3nuc \
                .about("species0000", eUriType.MODEL_URI) \
                .has_property(is_version_of="OPB:OPB_00340") \
                .identity("uniprot:P84022") \
                .is_part_of("obo/FMA_7163") \
                .is_part_of("obo/FMA_264020")

        # annotate Smad3nuc
        with editor.new_physical_entity() as smad3nuc:
            smad3nuc \
                .about("species0001", eUriType.MODEL_URI) \
                .has_property(is_version_of="OPB:OPB_00340") \
                .identity("uniprot:P84022") \
                .is_part_of("obo/FMA_7163") \
                .is_part_of("obo/FMA_63877") \
                .is_part_of("obo/FMA_63840")

        # annotate r1 (Smad3Nuc -> Smad3Cyt)
        with editor.new_physical_process() as export_reaction:
            export_reaction \
                .about("reaction0000", eUriType.MODEL_URI) \
                .has_property(is_version_of="OPB:OPB_00237") \
                .add_source("species0000", eUriType.MODEL_URI, 1) \
                .add_sink("species0001", eUriType.MODEL_URI, 1)

        # annotate r2 (Smad3Cyt -> Smad3Nuc)
        with editor.new_physical_process() as export_reaction:
            export_reaction \
                .about("reaction0001", eUriType.MODEL_URI) \
                .has_property(is_version_of="OPB:OPB_00237") \
                .add_source("species0001", eUriType.MODEL_URI, 1) \
                .add_sink("species0000", eUriType.MODEL_URI, 1)

        expected = """@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .
@prefix semsim: <http://bime.uw.edu/semsim/> .
@prefix OMEXlib: <http://omex-library.org/> .
@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .

local:EntityProperty0000
    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#species0000> ;
    bqbiol:isVersionOf <https://identifiers.org/OPB:OPB_00340> .

local:EntityProperty0001
    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#species0001> ;
    bqbiol:isVersionOf <https://identifiers.org/OPB:OPB_00340> .

local:ProcessProperty0000
    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#reaction0000> ;
    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_00592> .

local:ProcessProperty0001
    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#reaction0001> ;
    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_00592> .

local:ProcessProperty0002
    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#reaction0000> ;
    bqbiol:isVersionOf <https://identifiers.org/OPB:OPB_00237> .

local:ProcessProperty0003
    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#reaction0001> ;
    bqbiol:isVersionOf <https://identifiers.org/OPB:OPB_00237> .

local:SinkParticipant0000
    semsim:hasMultiplier "1"^^rdf:double ;
    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#species0000> .

local:SinkParticipant0001
    semsim:hasMultiplier "1"^^rdf:double ;
    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#species0001> .

local:SinkParticipant0002
    semsim:hasMultiplier "1"^^rdf:double ;
    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#species0001> .

local:SinkParticipant0003
    semsim:hasMultiplier "1"^^rdf:double ;
    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#species0000> .

local:SourceParticipant0000
    semsim:hasMultiplier "1"^^rdf:double ;
    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#species0001> .

local:SourceParticipant0001
    semsim:hasMultiplier "1"^^rdf:double ;
    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#species0000> .

local:SourceParticipant0002
    semsim:hasMultiplier "1"^^rdf:double ;
    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#species0000> .

local:SourceParticipant0003
    semsim:hasMultiplier "1"^^rdf:double ;
    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#species0001> .

<http://omex-library.org/NewOmex.omex/NewModel.xml#SmadNuclearTransport>
    <https://unknownpredicate.com/changeme#author> "Joe Smith" .

<http://omex-library.org/NewOmex.omex/NewModel.xml#reaction0000>
    semsim:hasSinkParticipant local:SinkParticipant0000, local:SinkParticipant0002 ;
    semsim:hasSourceParticipant local:SourceParticipant0000, local:SourceParticipant0002 .

<http://omex-library.org/NewOmex.omex/NewModel.xml#reaction0001>
    semsim:hasSinkParticipant local:SinkParticipant0001, local:SinkParticipant0003 ;
    semsim:hasSourceParticipant local:SourceParticipant0001, local:SourceParticipant0003 .

<http://omex-library.org/NewOmex.omex/NewModel.xml#species0000>
    bqbiol:is <https://identifiers.org/uniprot:P84022> ;
    bqbiol:isPartOf <http://omex-library.org/NewOmex.omex/NewModel.xml#cytosol>, <https://identifiers.org/obo/FMA_264020>, <https://identifiers.org/obo/FMA_7163> .

<http://omex-library.org/NewOmex.omex/NewModel.xml#species0001>
    bqbiol:is <https://identifiers.org/uniprot:P84022> ;
    bqbiol:isPartOf <http://omex-library.org/NewOmex.omex/NewModel.xml#nucleus>, <https://identifiers.org/obo/FMA_63840>, <https://identifiers.org/obo/FMA_63877>, <https://identifiers.org/obo/FMA_7163> .
"""

        self.assertTrue(RDF.equals_rdf_vs_string(rdf, expected))

    def test_to_editor_with_sbml_extraction(self):
        rdf = RDF()
        editor = rdf.to_editor(self.sbml, generate_new_metaids=True, sbml_semantic_extraction=True)
        # model level annotations
        with editor.new_singular_annotation() as author:
            author.about("SmadNuclearTransport") \
                .predicate_from_uri("https://unknownpredicate.com/changeme#author") \
                .resource_literal("Joe Smith")
        expected = """@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .
@prefix semsim: <http://bime.uw.edu/semsim/> .
@prefix OMEXlib: <http://omex-library.org/> .
@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .

local:ProcessProperty0000
    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#reaction0000> ;
    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_00592> .

local:ProcessProperty0001
    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#reaction0001> ;
    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_00592> .

local:SinkParticipant0000
    semsim:hasMultiplier "1"^^rdf:double ;
    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#species0000> .

local:SinkParticipant0001
    semsim:hasMultiplier "1"^^rdf:double ;
    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#species0001> .

local:SourceParticipant0000
    semsim:hasMultiplier "1"^^rdf:double ;
    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#species0001> .

local:SourceParticipant0001
    semsim:hasMultiplier "1"^^rdf:double ;
    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#species0000> .

<http://omex-library.org/NewOmex.omex/NewModel.xml#SmadNuclearTransport>
    <https://unknownpredicate.com/changeme#author> "Joe Smith" .

<http://omex-library.org/NewOmex.omex/NewModel.xml#reaction0000>
    semsim:hasSinkParticipant local:SinkParticipant0000 ;
    semsim:hasSourceParticipant local:SourceParticipant0000 .

<http://omex-library.org/NewOmex.omex/NewModel.xml#reaction0001>
    semsim:hasSinkParticipant local:SinkParticipant0001 ;
    semsim:hasSourceParticipant local:SourceParticipant0001 .

<http://omex-library.org/NewOmex.omex/NewModel.xml#species0000>
    bqbiol:isPartOf <http://omex-library.org/NewOmex.omex/NewModel.xml#cytosol> .

<http://omex-library.org/NewOmex.omex/NewModel.xml#species0001>
    bqbiol:isPartOf <http://omex-library.org/NewOmex.omex/NewModel.xml#nucleus> ."""
        self.assertTrue(RDF.equals_rdf_vs_string(rdf, expected))

    def test_to_editor_without_sbml_extraction(self):
        rdf = RDF()
        editor = rdf.to_editor(self.sbml, generate_new_metaids=True, sbml_semantic_extraction=False)
        # model level annotations
        with editor.new_singular_annotation() as author:
            author.about("SmadNuclearTransport") \
                .predicate_from_uri("https://unknownpredicate.com/changeme#author") \
                .resource_literal("Joe Smith")

        expected = """@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
@prefix OMEXlib: <http://omex-library.org/> .
@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .
@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .

<http://omex-library.org/NewOmex.omex/NewModel.xml#SmadNuclearTransport>
    <https://unknownpredicate.com/changeme#author> "Joe Smith" .

"""
        self.assertTrue(RDF.equals_rdf_vs_string(rdf, expected))

    def test_personal_information(self):
        rdf = RDF()
        editor = rdf.to_editor(self.sbml, generate_new_metaids=True, sbml_semantic_extraction=False)
        with editor.new_personal_information() as personal_information:
            personal_information.add_creator("1234-1234-1234-1234") \
                .add_name("Ciaran") \
                .add_mbox("cwelsh2@uw.edu") \
                .add_account_name("1234-1234-1234-1234") \
                .add_account_service_homepage("https://github.com/sys-bio/libomexmeta")
        expected = """@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
@prefix dc: <http://purl.org/dc/terms/> .
@prefix foaf: <http://xmlns.com/foaf/0.1/> .
@prefix OMEXlib: <http://omex-library.org/> .
@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .
@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .

<http://omex-library.org/NewOmex.omex/NewModel.xml#SmadNuclearTransport>
    dc:creator <http://omex-library.org/NewOmex.omex/NewModel.xml#PersonalInfo0000> .

<http://omex-library.org/NewOmex.omex/NewModel.xml#PersonalInfo0000>
    foaf:accountName <https://orcid.org/1234-1234-1234-1234> ;
    foaf:accountServiceHomepage <https://github.com/sys-bio/libomexmeta> ;
    foaf:mbox "cwelsh2@uw.edu" ;
    foaf:name "Ciaran" ;
    dc:creator <https://identifiers.org/orcid/1234-1234-1234-1234> .

"""
        self.assertTrue(RDF.equals_rdf_vs_string(rdf, expected, "turtle", True))

    def test_model_level_annotation(self):
        rdf = RDF()
        editor = rdf.to_editor(self.sbml, generate_new_metaids=True, sbml_semantic_extraction=False)
        with editor.new_personal_information() as personal_information:
            personal_information.add_creator("1234-1234-1234-1234") \
                .add_name("Ciaran") \
                .add_mbox("cwelsh2@uw.edu") \
                .add_account_name("1234-1234-1234-1234") \
                .add_account_service_homepage("https://github.com/sys-bio/libomexmeta")
        expected = """@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
@prefix dc: <http://purl.org/dc/terms/> .
@prefix foaf: <http://xmlns.com/foaf/0.1/> .
@prefix OMEXlib: <http://omex-library.org/> .
@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .
@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .

<http://omex-library.org/NewOmex.omex/NewModel.xml#SmadNuclearTransport>
    dc:creator <http://omex-library.org/NewOmex.omex/NewModel.xml#PersonalInfo0000> .

<http://omex-library.org/NewOmex.omex/NewModel.xml#PersonalInfo0000>
    foaf:accountName <https://orcid.org/1234-1234-1234-1234> ;
    foaf:accountServiceHomepage <https://github.com/sys-bio/libomexmeta> ;
    foaf:mbox "cwelsh2@uw.edu" ;
    foaf:name "Ciaran" ;
    dc:creator <https://identifiers.org/orcid/1234-1234-1234-1234> .
"""
        self.assertTrue(RDF.equals_rdf_vs_string(rdf, expected, "turtle", True))


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

    def test_query_results_as_str(self):
        self.download_file(self.gold_standard_url1, self.gold_standard_filename1)
        s = self.extract_rdf_from_combine_archive(self.gold_standard_filename1)[0]
        rdf = RDF.from_string(s, "rdfxml")
        query_str = """
        PREFIX bqbiol: <http://biomodels.net/biology-qualifiers/>
        SELECT ?x ?y ?z
        WHERE {
            ?x ?y ?z
        }"""
        results = rdf.query_results_as_string(query_str, "rdfxml")
        results_rdf = RDF()
        results_rdf.add_from_string(results)
        self.assertEqual(234, len(results_rdf))


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
        self.output_filename = os.path.join(os.path.dirname(__file__), "test_draw")

    def tearDown(self) -> None:
        if os.path.isfile(self.output_filename + ".jpeg"):
            os.remove(self.output_filename + ".jpeg")

        if os.path.isfile(self.output_filename):
            os.remove(self.output_filename)

    @unittest.skip("graphviz executable not found on some systems (on CI). ")
    def test(self):
        rdf = RDF()
        with rdf.to_editor(self.sbml, generate_new_metaids=True) as editor:
            with editor.new_singular_annotation() as s:
                s.about("species0000") \
                    .predicate("bqbiol", "is") \
                    .resource_uri("fma/FMA_66835")
        rdf.draw(self.output_filename, format="jpeg")
        self.assertTrue(os.path.isfile(self.output_filename))


class LoggerTests(unittest.TestCase):

    def setUp(self) -> None:
        pass

    def tearDown(self) -> None:
        pass

    def test_default_level(self):
        actual = Logger.get_level()
        expected = eLogLevel.warn
        self.assertEqual(actual, expected)

    def test_use_console_logger_out_of_the_box(self):
        Logger.info("Information is not displayed by default beecause the default level is warn")
        Logger.warn("Warnings are displayed to console")

    def test_file_logger(self):
        fname = os.path.join(os.path.abspath(os.path.dirname(__file__)), "log.log")
        print(fname)
        Logger.file_logger(fname)
        Logger.critical("A critical message that you just must see")
        if os.path.isfile(fname):
            try:
                os.remove(fname)
            except OSError as e:
                Logger.warn(str(e))

    def test_f(self):
        from os.path import join, exists, dirname, abspath
        from os import remove
        from pyomexmeta import RDF, Logger

        cellml = '''<?xml version=\"1.1\" encoding=\"UTF-8\"?>
                <model xmlns=\"http://www.cellml.org/cellml/1.1#\" xmlns:cmeta=\"http://www.cellml.org/metadata/1.0#\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:bqs=\"http://www.cellml.org/bqs/1.0#\" xmlns:semsim=\"http://bime.uw.edu/semsim/#\" xmlns:dc=\"http://purl.org/dc/terms/\" xmlns:vCard=\"http://www.w3.org/2001/vcard-rdf/3.0#\" name=\"annotation_examples\" cmeta:id=\"annExamples\">
                  <component name=\"main\">
                    <variable cmeta:id=\"main.Volume\" initial_value=\"100\" name=\"Volume\" units=\"dimensionless\" />
                    <variable cmeta:id=\"main.MembraneVoltage\" initial_value=\"-80\" name=\"MembraneVoltage\" units=\"dimensionless\" />
                    <variable cmeta:id=\"main.ReactionRate\" initial_value=\"1\" name=\"ReactionRate\" units=\"dimensionless\" />
                  </component>
                </model>'''

        logger_file = "log.log"
        print("check logger_file: ", logger_file)

        # if already exists, remove
        if exists(logger_file):
            remove(logger_file)
        assert not exists(logger_file)

        # activate the file logger
        Logger.file_logger(logger_file)
        rdf = RDF.from_string(cellml, syntax="turtle")  # nothing is emitted to console

        # now check logger_file
        with open(logger_file, 'r') as file:
            print(file.read())

    def test_set_logging_level(self):
        Logger.set_level(eLogLevel.info)
        Logger.info("Doing information")


if __name__ == "__main__":
    unittest.main()
