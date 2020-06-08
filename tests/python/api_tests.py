import os
import site
import unittest

# take care of directories so we can test the pysemsim api
test_dir = os.path.dirname(os.path.dirname(os.path.realpath(__file__)))
proj_dir = os.path.dirname(test_dir)
src_dir = os.path.join(proj_dir, "src")
pysemsem_dir = os.path.join(src_dir, "pysemsim")

site.addsitedir(src_dir)

from pysemsim import PysemsimAPI


class TestStrings:
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

    singular_annotation2 = """<?xml version=\"1.0\" encoding=\"UTF-8\"?>
   <rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"
            xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\"
            xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"
            xml:base=\"file://./MyModel.rdf\">
   <rdf:Description rdf:about=\"./MyModel.xml#modelmeta1\">
       <bqmodel:isDescribedBy rdf:resource=\"https://identifiers.org/pubmed/12991237\" />
   </rdf:Description>
</rdf:RDF>"""


class TestAPI(unittest.TestCase):

    def setUp(self) -> None:
        # loads the function that makes a new RDF
        self.rdf = PysemsimAPI.rdf_new()

    def tearDown(self) -> None:
        """calls the RDF delete function after each test"""
        # PysemsimAPI.rdf_delete(self.rdf)

    def test_rdf_obj(self):
        self.assertIsInstance(self.rdf, int)

    def test_rdf_from_string_cfunc(self):
        PysemsimAPI.rdf_from_string(self.rdf, TestStrings.singular_annotation2.encode(),
                                    'rdfxml'.encode())  # , "basey.rdf".encode())
        expected = 1
        actual = PysemsimAPI.rdf_size(self.rdf)
        self.assertEqual(expected, actual)
        PysemsimAPI.rdf_delete(self.rdf)

    def test_rdf_to_string_cfunc(self):
        PysemsimAPI.rdf_from_string(self.rdf, TestStrings.singular_annotation2.encode(), "rdfxml".encode())
        string_ptr = PysemsimAPI.rdf_to_string(self.rdf, "rdfxml-abbrev".encode(), "basey.rdf".encode())
        actual2 = PysemsimAPI.get_and_free_c_str(string_ptr)
        expected = """<?xml version="1.0" encoding="utf-8"?>
<rdf:RDF xmlns:bqbiol="http://biomodels.net/biology-qualifiers/"
   xmlns:bqmodel="http://biomodels.net/model-qualifiers/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"
   xml:base="file://basey.rdf">
  <rdf:Description rdf:about="file://./MyModel.xml#modelmeta1">
    <bqmodel:isDescribedBy rdf:resource="https://identifiers.org/pubmed/12991237"/>
  </rdf:Description>
</rdf:RDF>
"""
        self.assertEqual(expected, actual2)

        PysemsimAPI.rdf_delete(self.rdf)

    def test_rdf_get_base_uri(self):
        PysemsimAPI.rdf_from_string(self.rdf, TestStrings.singular_annotation2.encode(), "rdfxml".encode())
        ptr = PysemsimAPI.rdf_get_base_uri(self.rdf)
        actual = PysemsimAPI.get_and_free_c_str(ptr)
        expected = "file://./Annotations.rdf"
        self.assertEqual(expected, actual)

    def test_rdf_set_base_uri(self):
        PysemsimAPI.rdf_from_string(self.rdf, TestStrings.singular_annotation2.encode(), "rdfxml".encode())
        PysemsimAPI.rdf_set_base_uri(self.rdf, "new_base_uri.rdf".encode())
        ptr = PysemsimAPI.rdf_get_base_uri(self.rdf)
        actual = PysemsimAPI.get_and_free_c_str(ptr)
        expected = "file://new_base_uri.rdf"
        self.assertEqual(expected, actual)

    def test_rdf_to_editor(self):
        editor_ptr = PysemsimAPI.rdf_to_editor(self.rdf, TestStrings.xml.encode(), 0)
        self.assertIsInstance(editor_ptr, int)
        PysemsimAPI.editor_delete(editor_ptr)

    def test_editor_new_singular_annotation(self):
        editor_ptr = PysemsimAPI.rdf_to_editor(self.rdf, TestStrings.xml.encode(), 0)
        singular_annotation = PysemsimAPI.editor_new_singular_annotation(editor_ptr)
        self.assertIsInstance(singular_annotation, int)
        PysemsimAPI.singular_annotation_delete(singular_annotation)
        PysemsimAPI.editor_delete(editor_ptr)

    def test_editor_new_physical_entity(self):
        editor_ptr = PysemsimAPI.rdf_to_editor(self.rdf, TestStrings.xml.encode(), 0)
        physical_entity = PysemsimAPI.editor_new_physical_entity(editor_ptr)
        self.assertIsInstance(physical_entity, int)
        PysemsimAPI.editor_delete(editor_ptr)

    def test_editor_new_physical_process(self):
        editor_ptr = PysemsimAPI.rdf_to_editor(self.rdf, TestStrings.xml.encode(), 0)
        physical_process = PysemsimAPI.editor_new_physical_process(editor_ptr)
        self.assertIsInstance(physical_process, int)
        PysemsimAPI.editor_delete(editor_ptr)

    def test_editor_new_physical_force(self):
        editor_ptr = PysemsimAPI.rdf_to_editor(self.rdf, TestStrings.xml.encode(), 0)
        physical_force = PysemsimAPI.editor_new_physical_force(editor_ptr)
        self.assertIsInstance(physical_force, int)
        PysemsimAPI.editor_delete(editor_ptr)

    def test_editor_add_namespace(self):
        editor_ptr = PysemsimAPI.rdf_to_editor(self.rdf, TestStrings.xml.encode(), 0)
        PysemsimAPI.editor_add_namespace(editor_ptr, "https://namespace.com".encode(), "ns_".encode())
        singular_annotation = PysemsimAPI.editor_new_singular_annotation(editor_ptr)
        singular_annotation = PysemsimAPI.singular_annotation_set_about(singular_annotation, "cytoplasm".encode())
        singular_annotation = PysemsimAPI.singular_annotation_set_predicate_uri(singular_annotation,
                                                                                "https://predicate.com/from/uri".encode())
        singular_annotation = PysemsimAPI.singular_annotation_set_resource_literal(singular_annotation,
                                                                                   "namespace test".encode())
        PysemsimAPI.editor_add_single_annotation(editor_ptr, singular_annotation)
        PysemsimAPI.editor_to_rdf(editor_ptr, self.rdf)

        actual = PysemsimAPI.rdf_to_string(self.rdf, "rdfxml-abbrev".encode(), "namespace_test.rdf".encode())
        actual = PysemsimAPI.get_and_free_c_str(actual)
        expected = r"""<?xml version="1.0" encoding="utf-8"?>
<rdf:RDF xmlns:ns_="https://namespace.com"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"
   xml:base="file://namespace_test.rdf">
  <rdf:Description rdf:about="cytoplasm">
    <ns1:uri xmlns:ns1="https://predicate.com/from/"
       rdf:datatype="http://www.w3.org/1999/02/22-rdf-syntax-ns#string">namespace test</ns1:uri>
  </rdf:Description>
</rdf:RDF>
"""
        self.assertEqual(expected, actual)

    def test_editor_check_valid_metaid(self):
        """
        This test can't officially be tested because when this test fails it crashes
        python. However, it is working = When id is wrong we get helpful
        error message.
        """
        editor_ptr = PysemsimAPI.rdf_to_editor(self.rdf, TestStrings.xml.encode(), 0)
        PysemsimAPI.editor_check_valid_metaid(editor_ptr, "SemsimMetaid0000".encode())

    def test_singular_annotation_about(self):
        editor_ptr = PysemsimAPI.rdf_to_editor(self.rdf, TestStrings.xml.encode(), 0)
        singular_annotation = PysemsimAPI.editor_new_singular_annotation(editor_ptr)
        PysemsimAPI.singular_annotation_set_about(singular_annotation, "cytosol".encode())
        ptr = PysemsimAPI.singular_annotation_get_about(singular_annotation)
        actual = PysemsimAPI.get_and_free_c_str(ptr)
        expected = "cytosol"
        self.assertEqual(expected, actual)

    def test_singular_annotation_predicate(self):
        editor_ptr = PysemsimAPI.rdf_to_editor(self.rdf, TestStrings.xml.encode(), 0)
        singular_annotation = PysemsimAPI.editor_new_singular_annotation(editor_ptr)
        PysemsimAPI.singular_annotation_set_predicate(singular_annotation, "bqb".encode(), "is".encode())
        ptr = PysemsimAPI.singular_annotation_get_predicate(singular_annotation)
        actual = PysemsimAPI.get_and_free_c_str(ptr)
        expected = "http://biomodels.net/biology-qualifiers/is"
        self.assertEqual(expected, actual)

    def test_singular_annotation_predicate_uri(self):
        editor_ptr = PysemsimAPI.rdf_to_editor(self.rdf, TestStrings.xml.encode(), 0)
        singular_annotation = PysemsimAPI.editor_new_singular_annotation(editor_ptr)
        PysemsimAPI.singular_annotation_set_predicate_uri(singular_annotation,
                                                          "https://predicate.com/from/uri".encode())
        ptr = PysemsimAPI.singular_annotation_get_predicate(singular_annotation)
        actual = PysemsimAPI.get_and_free_c_str(ptr)
        expected = "https://predicate.com/from/uri"
        self.assertEqual(expected, actual)

    def test_singular_annotation_resource_literal(self):
        editor_ptr = PysemsimAPI.rdf_to_editor(self.rdf, TestStrings.xml.encode(), 0)
        singular_annotation = PysemsimAPI.editor_new_singular_annotation(editor_ptr)
        PysemsimAPI.singular_annotation_set_resource_literal(singular_annotation, "LiteralValue".encode())
        ptr = PysemsimAPI.singular_annotation_get_resource(singular_annotation)
        actual = PysemsimAPI.get_and_free_c_str(ptr)
        expected = "LiteralValue"
        self.assertEqual(expected, actual)

    def test_singular_annotation_resource_uri(self):
        editor_ptr = PysemsimAPI.rdf_to_editor(self.rdf, TestStrings.xml.encode(), 0)
        singular_annotation = PysemsimAPI.editor_new_singular_annotation(editor_ptr)
        PysemsimAPI.singular_annotation_set_resource_uri(singular_annotation, "UriValue".encode())
        ptr = PysemsimAPI.singular_annotation_get_resource(singular_annotation)
        actual = PysemsimAPI.get_and_free_c_str(ptr)
        expected = "UriValue"
        self.assertEqual(expected, actual)

    def test_singular_annotation_resource_blank(self):
        editor_ptr = PysemsimAPI.rdf_to_editor(self.rdf, TestStrings.xml.encode(), 0)
        singular_annotation = PysemsimAPI.editor_new_singular_annotation(editor_ptr)
        PysemsimAPI.singular_annotation_set_resource_blank(singular_annotation, "blank".encode())
        ptr = PysemsimAPI.singular_annotation_get_resource(singular_annotation)
        actual = PysemsimAPI.get_and_free_c_str(ptr)
        expected = "blank"
        self.assertEqual(expected, actual)

    def test_singular_annotation_str(self):
        editor_ptr = PysemsimAPI.rdf_to_editor(self.rdf, TestStrings.xml.encode(), 0)
        singular_annotation = PysemsimAPI.editor_new_singular_annotation(editor_ptr)
        PysemsimAPI.singular_annotation_set_about(singular_annotation, "cytosol".encode())
        PysemsimAPI.singular_annotation_set_predicate(singular_annotation, "bqb".encode(), "is".encode())
        PysemsimAPI.singular_annotation_set_resource_uri(singular_annotation, "uniprot:PD12345".encode())
        ptr = PysemsimAPI.singular_annotation_str(
            singular_annotation, "rdfxml-abbrev".encode(), "singular_annotation.rdf".encode())
        actual = PysemsimAPI.get_and_free_c_str(ptr)
        expected = """<?xml version="1.0" encoding="utf-8"?>
<rdf:RDF xmlns:bqbiol="http://biomodels.net/biology-qualifiers/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"
   xml:base="singular_annotation.rdf">
  <rdf:Description rdf:about="cytosol">
    <bqbiol:is rdf:resource="https://identifiers.org/uniprot/PD12345"/>
  </rdf:Description>
</rdf:RDF>
"""
        self.assertEqual(expected, actual)

    def test_editor_add_single_annotation(self):
        editor_ptr = PysemsimAPI.rdf_to_editor(self.rdf, TestStrings.xml.encode(), 0)
        singular_annotation = PysemsimAPI.editor_new_singular_annotation(editor_ptr)
        PysemsimAPI.singular_annotation_set_about(singular_annotation, "cytosol".encode())
        PysemsimAPI.singular_annotation_set_predicate(singular_annotation, "bqb".encode(), "is".encode())
        PysemsimAPI.singular_annotation_set_resource_uri(singular_annotation, "uniprot:PD12345".encode())
        PysemsimAPI.editor_add_single_annotation(editor_ptr, singular_annotation)
        PysemsimAPI.editor_to_rdf(editor_ptr, self.rdf)
        ptr = PysemsimAPI.rdf_to_string(self.rdf, "turtle".encode(), "turtled_singular_annotation.rdf".encode())
        actual = PysemsimAPI.get_and_free_c_str(ptr)
        expected = """@base <file://turtled_singular_annotation.rdf> .
@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .

<cytosol>
    bqbiol:is <https://identifiers.org/uniprot/PD12345> .

"""
        self.assertEqual(expected, actual)

    def test_physical_entity_about(self):
        editor_ptr = PysemsimAPI.rdf_to_editor(self.rdf, TestStrings.xml.encode(), 0)
        physical_entity = PysemsimAPI.editor_new_physical_entity(editor_ptr)
        PysemsimAPI.physical_entity_set_about(physical_entity, "cytosol".encode())
        ptr = PysemsimAPI.physical_entity_get_about(physical_entity)
        actual = PysemsimAPI.get_and_free_c_str(ptr)
        expected = "cytosol"
        self.assertEqual(expected, actual)

    def test_physical_entity_set_physical_property(self):
        editor_ptr = PysemsimAPI.rdf_to_editor(self.rdf, TestStrings.xml.encode(), 0)
        physical_entity = PysemsimAPI.editor_new_physical_entity(editor_ptr)
        PysemsimAPI.physical_entity_set_physical_property(physical_entity, "opb:opb12345".encode())
        ptr = PysemsimAPI.physical_entity_get_physical_property(physical_entity)
        actual = PysemsimAPI.get_and_free_c_str(ptr)
        expected = "https://identifiers.org/opb/opb12345"
        self.assertEqual(expected, actual)

    def test_physical_entity_set_identity(self):
        editor_ptr = PysemsimAPI.rdf_to_editor(self.rdf, TestStrings.xml.encode(), 0)
        physical_entity = PysemsimAPI.editor_new_physical_entity(editor_ptr)
        PysemsimAPI.physical_entity_set_identity(physical_entity, "uniprot:P456".encode())
        ptr = PysemsimAPI.physical_entity_get_identity(physical_entity)
        actual = PysemsimAPI.get_and_free_c_str(ptr)
        expected = "https://identifiers.org/uniprot/P456"
        self.assertEqual(expected, actual)

    def test_physical_entity_num_locations(self):
        editor_ptr = PysemsimAPI.rdf_to_editor(self.rdf, TestStrings.xml.encode(), 0)
        physical_entity = PysemsimAPI.editor_new_physical_entity(editor_ptr)
        PysemsimAPI.physical_entity_add_location(physical_entity, "fma:fma:3456".encode())
        PysemsimAPI.physical_entity_add_location(physical_entity, "fma/fma:3457".encode())
        actual = PysemsimAPI.physical_entity_get_num_locations(physical_entity)
        expected = 2
        self.assertEqual(expected, actual)

    def test_physical_entity_add_location(self):
        editor_ptr = PysemsimAPI.rdf_to_editor(self.rdf, TestStrings.xml.encode(), 0)
        physical_entity = PysemsimAPI.editor_new_physical_entity(editor_ptr)
        PysemsimAPI.physical_entity_add_location(physical_entity, "fma:fma:3456".encode())
        PysemsimAPI.physical_entity_add_location(physical_entity, "fma/fma:3457".encode())
        num_locations = PysemsimAPI.physical_entity_get_num_locations(physical_entity)
        ptr = [PysemsimAPI.physical_entity_get_location(physical_entity, i) for i in range(num_locations)]
        actual = [PysemsimAPI.get_and_free_c_str(i) for i in ptr]
        expected = ['https://identifiers.org/fma/fma:3456', 'https://identifiers.org/fma/fma:3457']
        self.assertEqual(expected, actual)

    def test_physical_entity_str(self):
        editor_ptr = PysemsimAPI.rdf_to_editor(self.rdf, TestStrings.xml.encode(), 0)
        physical_entity = PysemsimAPI.editor_new_physical_entity(editor_ptr)
        PysemsimAPI.physical_entity_set_about(physical_entity, "cytosol".encode())
        PysemsimAPI.physical_entity_set_physical_property(physical_entity, "opb:opb12345".encode())
        PysemsimAPI.physical_entity_set_identity(physical_entity, "uniprot:P456".encode())
        PysemsimAPI.physical_entity_add_location(physical_entity, "fma:fma:3456".encode())
        PysemsimAPI.physical_entity_add_location(physical_entity, "fma/fma:3457".encode())
        ptr = PysemsimAPI.physical_entity_str(physical_entity, "json".encode(), "jsonified_physical_entity".encode())
        actual = PysemsimAPI.get_and_free_c_str(ptr)

        expected = """
{
  "PhysicalEntity0000" : {
    "http://biomodels.net/biology-qualifiers/is" : [ {
        "value" : "https://identifiers.org/uniprot/P456",
        "type" : "uri"
        }
      
      ],
    "http://biomodels.net/biology-qualifiers/isPartOf" : [ {
        "value" : "https://identifiers.org/fma/fma:3456",
        "type" : "uri"
        }
      ,
      {
        "value" : "https://identifiers.org/fma/fma:3457",
        "type" : "uri"
        }
      
      ]
    }
  ,
  "cytosol" : {
    "http://biomodels.net/biology-qualifiers/isPropertyOf" : [ {
        "value" : "PhysicalEntity0000",
        "type" : "uri"
        }
      
      ],
    "http://biomodels.net/biology-qualifiers/isVersionOf" : [ {
        "value" : "https://identifiers.org/opb/opb12345",
        "type" : "uri"
        }
      
      ]
    }
  }
"""
        self.assertEqual(expected, actual)

    def test_editor_add_physical_entity(self):
        editor_ptr = PysemsimAPI.rdf_to_editor(self.rdf, TestStrings.xml.encode(), 0)
        physical_entity = PysemsimAPI.editor_new_physical_entity(editor_ptr)
        PysemsimAPI.physical_entity_set_about(physical_entity, "cytosol".encode())
        PysemsimAPI.physical_entity_set_physical_property(physical_entity, "opb:opb12345".encode())
        PysemsimAPI.physical_entity_set_identity(physical_entity, "uniprot:P456".encode())
        PysemsimAPI.physical_entity_add_location(physical_entity, "fma:fma:3456".encode())
        PysemsimAPI.physical_entity_add_location(physical_entity, "fma/fma:3457".encode())
        PysemsimAPI.editor_add_physical_entity(editor_ptr, physical_entity)
        ptr = PysemsimAPI.rdf_to_string(self.rdf, "rdfxml-abbrev".encode(), "PhysicalEntity.rdf".encode())
        actual = PysemsimAPI.get_and_free_c_str(ptr)
        print(actual)
        expected = """<?xml version="1.0" encoding="utf-8"?>
<rdf:RDF xmlns:bqbiol="http://biomodels.net/biology-qualifiers/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"
   xml:base="file://PhysicalEntity.rdf">
  <rdf:Description rdf:about="PhysicalEntity0000">
    <bqbiol:is rdf:resource="https://identifiers.org/uniprot/P456"/>
    <bqbiol:isPartOf rdf:resource="https://identifiers.org/fma/fma:3456"/>
    <bqbiol:isPartOf rdf:resource="https://identifiers.org/fma/fma:3457"/>
  </rdf:Description>
  <rdf:Description rdf:about="cytosol">
    <bqbiol:isPropertyOf rdf:resource="PhysicalEntity0000"/>
    <bqbiol:isVersionOf rdf:resource="https://identifiers.org/opb/opb12345"/>
  </rdf:Description>
</rdf:RDF>
"""
        self.assertEqual(expected, actual)

    def test_physical_process_about(self):
        editor_ptr = PysemsimAPI.rdf_to_editor(self.rdf, TestStrings.xml.encode(), 0)
        physical_process = PysemsimAPI.editor_new_physical_process(editor_ptr)
        PysemsimAPI.physical_process_set_about(physical_process, "cytosol".encode())
        ptr = PysemsimAPI.physical_process_get_about(physical_process)
        actual = PysemsimAPI.get_and_free_c_str(ptr)
        expected = "cytosol"
        self.assertEqual(expected, actual)

    def test_physical_process_set_physical_property(self):
        editor_ptr = PysemsimAPI.rdf_to_editor(self.rdf, TestStrings.xml.encode(), 0)
        physical_process = PysemsimAPI.editor_new_physical_process(editor_ptr)
        PysemsimAPI.physical_process_set_physical_property(physical_process, "opb:opb12345".encode())
        ptr = PysemsimAPI.physical_process_get_physical_property(physical_process)
        actual = PysemsimAPI.get_and_free_c_str(ptr)
        expected = "https://identifiers.org/opb/opb12345"
        self.assertEqual(expected, actual)

    def test_physical_process_str(self):
        editor_ptr = PysemsimAPI.rdf_to_editor(self.rdf, TestStrings.xml.encode(), 0)
        physical_process = PysemsimAPI.editor_new_physical_process(editor_ptr)
        PysemsimAPI.physical_process_set_about(physical_process, "cytosol".encode())
        PysemsimAPI.physical_process_set_physical_property(physical_process, "opb:opb12345".encode())
        PysemsimAPI.physical_process_add_source(
            physical_process, "cytoplasm".encode(),
            1.0, "Entity1".encode())

        PysemsimAPI.physical_process_add_sink(
            physical_process, "cytoplasm".encode(),
            1.0, "Entity2".encode())

        PysemsimAPI.physical_process_add_mediator(
            physical_process, "cytoplasm".encode(),
            1.0, "Entity3".encode())
        ptr = PysemsimAPI.physical_process_str(physical_process, "html".encode(),
                                               "html_physical_process_ann.rdf".encode())
        actual = PysemsimAPI.get_and_free_c_str(ptr)
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
      <td><span class="uri"><a href="cytosol">cytosol</a></span></td>
      <td><span class="uri"><a href="http://biomodels.net/biology-qualifiers/isVersionOf">http://biomodels.net/biology-qualifiers/isVersionOf</a></span></td>
      <td><span class="uri"><a href="https://identifiers.org/opb/opb12345">https://identifiers.org/opb/opb12345</a></span></td>
    </tr>
    <tr class="triple">
      <td><span class="uri"><a href="cytosol">cytosol</a></span></td>
      <td><span class="uri"><a href="http://biomodels.net/biology-qualifiers/isPropertyOf">http://biomodels.net/biology-qualifiers/isPropertyOf</a></span></td>
      <td><span class="uri"><a href="PhysicalProcess0000">PhysicalProcess0000</a></span></td>
    </tr>
    <tr class="triple">
      <td><span class="uri"><a href="PhysicalProcess0000">PhysicalProcess0000</a></span></td>
      <td><span class="uri"><a href="http://www.bhi.washington.edu/semsim#hasSourceParticipant">http://www.bhi.washington.edu/semsim#hasSourceParticipant</a></span></td>
      <td><span class="uri"><a href="cytoplasm">cytoplasm</a></span></td>
    </tr>
    <tr class="triple">
      <td><span class="uri"><a href="cytoplasm">cytoplasm</a></span></td>
      <td><span class="uri"><a href="http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference">http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference</a></span></td>
      <td><span class="uri"><a href="Entity1">Entity1</a></span></td>
    </tr>
    <tr class="triple">
      <td><span class="uri"><a href="cytoplasm">cytoplasm</a></span></td>
      <td><span class="uri"><a href="http://www.bhi.washington.edu/semsim#hasMultiplier">http://www.bhi.washington.edu/semsim#hasMultiplier</a></span></td>
      <td><span class="literal"><span class="value">5.26354e-315</span>^^&lt;<span class="datatype">http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double</span>&gt;</span></td>
    </tr>
    <tr class="triple">
      <td><span class="uri"><a href="PhysicalProcess0000">PhysicalProcess0000</a></span></td>
      <td><span class="uri"><a href="http://www.bhi.washington.edu/semsim#hasSinkParticipant">http://www.bhi.washington.edu/semsim#hasSinkParticipant</a></span></td>
      <td><span class="uri"><a href="cytoplasm">cytoplasm</a></span></td>
    </tr>
    <tr class="triple">
      <td><span class="uri"><a href="cytoplasm">cytoplasm</a></span></td>
      <td><span class="uri"><a href="http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference">http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference</a></span></td>
      <td><span class="uri"><a href="Entity2">Entity2</a></span></td>
    </tr>
    <tr class="triple">
      <td><span class="uri"><a href="PhysicalProcess0000">PhysicalProcess0000</a></span></td>
      <td><span class="uri"><a href="http://www.bhi.washington.edu/semsim#hasMediatorParticipant">http://www.bhi.washington.edu/semsim#hasMediatorParticipant</a></span></td>
      <td><span class="uri"><a href="cytoplasm">cytoplasm</a></span></td>
    </tr>
    <tr class="triple">
      <td><span class="uri"><a href="cytoplasm">cytoplasm</a></span></td>
      <td><span class="uri"><a href="http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference">http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference</a></span></td>
      <td><span class="uri"><a href="Entity3">Entity3</a></span></td>
    </tr>
  </table>
  <p>Total number of triples: <span class="count">9</span>.</p>
</body>
</html>
"""
        self.assertEqual(expected, actual)

    def test_editor_add_physical_process(self):
        editor_ptr = PysemsimAPI.rdf_to_editor(self.rdf, TestStrings.xml.encode(), 0)
        physical_process = PysemsimAPI.editor_new_physical_process(editor_ptr)
        PysemsimAPI.physical_process_set_about(physical_process, "cytosol".encode())
        PysemsimAPI.physical_process_set_physical_property(physical_process, "opb:opb12345".encode())
        PysemsimAPI.physical_process_add_source(
            physical_process, "cytoplasm".encode(),
            1.0, "Entity1".encode())

        PysemsimAPI.physical_process_add_sink(
            physical_process, "cytoplasm".encode(),
            1.0, "Entity2".encode())

        PysemsimAPI.physical_process_add_mediator(
            physical_process, "cytoplasm".encode(),
            1.0, "Entity3".encode())
        PysemsimAPI.editor_add_physical_process(editor_ptr, physical_process)
        ptr = PysemsimAPI.rdf_to_string(self.rdf, "rdfxml".encode(), "PhysicalProcess.rdf".encode())
        actual = PysemsimAPI.get_and_free_c_str(ptr)
        print(actual)
        expected = """<?xml version="1.0" encoding="utf-8"?>
<rdf:RDF xmlns:bqbiol="http://biomodels.net/biology-qualifiers/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#" xmlns:semsim="http://www.bhi.washington.edu/semsim#" xml:base="file://PhysicalProcess.rdf">
  <rdf:Description rdf:about="cytosol">
    <bqbiol:isVersionOf rdf:resource="https://identifiers.org/opb/opb12345"/>
  </rdf:Description>
  <rdf:Description rdf:about="cytosol">
    <bqbiol:isPropertyOf rdf:resource="PhysicalProcess0000"/>
  </rdf:Description>
  <rdf:Description rdf:about="PhysicalProcess0000">
    <semsim:hasSourceParticipant rdf:resource="cytoplasm"/>
  </rdf:Description>
  <rdf:Description rdf:about="cytoplasm">
    <semsim:hasPhysicalEntityReference rdf:resource="Entity1"/>
  </rdf:Description>
  <rdf:Description rdf:about="cytoplasm">
    <semsim:hasMultiplier rdf:datatype="http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double">5.26354e-315</semsim:hasMultiplier>
  </rdf:Description>
  <rdf:Description rdf:about="PhysicalProcess0000">
    <semsim:hasSinkParticipant rdf:resource="cytoplasm"/>
  </rdf:Description>
  <rdf:Description rdf:about="cytoplasm">
    <semsim:hasPhysicalEntityReference rdf:resource="Entity2"/>
  </rdf:Description>
  <rdf:Description rdf:about="PhysicalProcess0000">
    <semsim:hasMediatorParticipant rdf:resource="cytoplasm"/>
  </rdf:Description>
  <rdf:Description rdf:about="cytoplasm">
    <semsim:hasPhysicalEntityReference rdf:resource="Entity3"/>
  </rdf:Description>
</rdf:RDF>
"""
        self.assertEqual(expected, actual)

    def test_physical_force_about(self):
        editor_ptr = PysemsimAPI.rdf_to_editor(self.rdf, TestStrings.xml.encode(), 0)
        physical_force = PysemsimAPI.editor_new_physical_force(editor_ptr)
        PysemsimAPI.physical_force_set_about(physical_force, "cytosol".encode())
        ptr = PysemsimAPI.physical_force_get_about(physical_force)
        actual = PysemsimAPI.get_and_free_c_str(ptr)
        expected = "cytosol"
        self.assertEqual(expected, actual)

    def test_physical_force_set_physical_property(self):
        editor_ptr = PysemsimAPI.rdf_to_editor(self.rdf, TestStrings.xml.encode(), 0)
        physical_force = PysemsimAPI.editor_new_physical_force(editor_ptr)
        PysemsimAPI.physical_force_set_physical_property(physical_force, "opb:opb12345".encode())
        ptr = PysemsimAPI.physical_force_get_physical_property(physical_force)
        actual = PysemsimAPI.get_and_free_c_str(ptr)
        expected = "https://identifiers.org/opb/opb12345"
        self.assertEqual(expected, actual)

    def test_physical_force_str(self):
        editor_ptr = PysemsimAPI.rdf_to_editor(self.rdf, TestStrings.xml.encode(), 0)
        physical_force = PysemsimAPI.editor_new_physical_force(editor_ptr)
        PysemsimAPI.physical_force_set_about(physical_force, "cytosol".encode())
        PysemsimAPI.physical_force_set_physical_property(physical_force, "opb:opb12345".encode())
        PysemsimAPI.physical_force_add_source(
            physical_force, "cytoplasm".encode(),
            1.0, "Entity1".encode())

        PysemsimAPI.physical_force_add_sink(
            physical_force, "cytoplasm".encode(),
            1.0, "Entity2".encode())

        ptr = PysemsimAPI.physical_force_str(physical_force, "turtle".encode(),
                                             "html_physical_process_ann.rdf".encode())
        actual = PysemsimAPI.get_and_free_c_str(ptr)
        # print(actual)
        expected = """@base <file://html_physical_process_ann.rdf> .
@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .
@prefix semsim: <http://www.bhi.washington.edu/semsim#> .

<PhysicalForce0000>
    semsim:hasSinkParticipant <cytoplasm> ;
    semsim:hasSourceParticipant <cytoplasm> .

<cytoplasm>
    semsim:hasMultiplier "5.26354e-315"^^<http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double> ;
    semsim:hasPhysicalEntityReference <Entity1>, <Entity2> .

<cytosol>
    bqbiol:isPropertyOf <PhysicalForce0000> ;
    bqbiol:isVersionOf <https://identifiers.org/opb/opb12345> .

"""
        self.assertEqual(expected, actual)
        PysemsimAPI.physical_force_free_all(physical_force)

    def test_editor_add_physical_force(self):
        editor_ptr = PysemsimAPI.rdf_to_editor(self.rdf, TestStrings.xml.encode(), 0)
        physical_force = PysemsimAPI.editor_new_physical_force(editor_ptr)
        PysemsimAPI.physical_force_set_about(physical_force, "cytosol".encode())
        PysemsimAPI.physical_force_set_physical_property(physical_force, "opb:opb12345".encode())
        PysemsimAPI.physical_force_add_source(
            physical_force, "cytoplasm".encode(),
            1.0, "Entity1".encode())

        PysemsimAPI.physical_force_add_sink(
            physical_force, "cytoplasm".encode(),
            1.0, "Entity2".encode())

        PysemsimAPI.editor_add_physical_force(editor_ptr, physical_force)
        ptr = PysemsimAPI.rdf_to_string(self.rdf, "turtle".encode(),
                                             "PhysicalForce.rdf".encode())
        actual = PysemsimAPI.get_and_free_c_str(ptr)
        expected = """@base <file://html_physical_process_ann.rdf> .
@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .
@prefix semsim: <http://www.bhi.washington.edu/semsim#> .

<PhysicalForce0000>
    semsim:hasSinkParticipant <cytoplasm> ;
    semsim:hasSourceParticipant <cytoplasm> .

<cytoplasm>
    semsim:hasMultiplier "5.26354e-315"^^<http://www.w3.org/1999/02/22-rdf-syntax-ns#http://www.w3.org/2001/XMLSchema#double> ;
    semsim:hasPhysicalEntityReference <Entity1>, <Entity2> .

<cytosol>
    bqbiol:isPropertyOf <PhysicalForce0000> ;
    bqbiol:isVersionOf <https://identifiers.org/opb/opb12345> .

"""
        self.assertEqual(expected, actual)
        PysemsimAPI.physical_force_free_all(physical_force)


if __name__ == "__main__":
    unittest.TestCase()
