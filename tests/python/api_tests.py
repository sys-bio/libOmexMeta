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
        PysemsimAPI.rdf_delete(self.rdf)

    def test_rdf_obj(self):
        self.assertIsInstance(self.rdf, int)

    def test_rdf_from_string_cfunc(self):
        PysemsimAPI.rdf_from_string(self.rdf, TestStrings.singular_annotation2.encode(),
                                    'rdfxml'.encode())  # , "basey.rdf".encode())
        expected = 1
        actual = PysemsimAPI.rdf_size(self.rdf)
        self.assertEqual(expected, actual)

    def test_rdf_to_string_cfunc(self):
        PysemsimAPI.rdf_from_string(self.rdf, TestStrings.singular_annotation2.encode(), "rdfxml".encode())
        actual = PysemsimAPI.rdf_to_string(self.rdf, "rdfxml-abbrev".encode(), "basey.rdf".encode())
        actual.decode()
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
        self.assertEqual(expected, actual.decode())

    def test_rdf_get_base_uri(self):
        PysemsimAPI.rdf_from_string(self.rdf, TestStrings.singular_annotation2.encode(), "rdfxml".encode())
        actual = PysemsimAPI.rdf_get_base_uri(self.rdf)
        expected = "file://./Annotations.rdf"
        self.assertEqual(expected, actual.decode())

    def test_rdf_set_base_uri(self):
        PysemsimAPI.rdf_from_string(self.rdf, TestStrings.singular_annotation2.encode(), "rdfxml".encode())
        PysemsimAPI.rdf_set_base_uri(self.rdf, "new_base_uri.rdf".encode())
        actual = PysemsimAPI.rdf_get_base_uri(self.rdf)
        expected = "file://new_base_uri.rdf"
        self.assertEqual(expected, actual.decode())

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

    def test_singular_annotation_about(self):
        editor_ptr = PysemsimAPI.rdf_to_editor(self.rdf, TestStrings.xml.encode(), 0)
        singular_annotation = PysemsimAPI.editor_new_singular_annotation(editor_ptr)
        PysemsimAPI.singular_annotation_set_about(singular_annotation, "cytosol".encode())
        actual = PysemsimAPI.singular_annotation_get_about(singular_annotation)
        expected = "cytosol"
        self.assertEqual(expected, actual.decode())

    def test_singular_annotation_predicate(self):
        editor_ptr = PysemsimAPI.rdf_to_editor(self.rdf, TestStrings.xml.encode(), 0)
        singular_annotation = PysemsimAPI.editor_new_singular_annotation(editor_ptr)
        PysemsimAPI.singular_annotation_set_predicate(singular_annotation, "bqb".encode(), "is".encode())
        actual = PysemsimAPI.singular_annotation_get_predicate(singular_annotation)
        expected = "http://biomodels.net/biology-qualifiers/is"
        self.assertEqual(expected, actual.decode())

    def test_singular_annotation_resource_literal(self):
        editor_ptr = PysemsimAPI.rdf_to_editor(self.rdf, TestStrings.xml.encode(), 0)
        singular_annotation = PysemsimAPI.editor_new_singular_annotation(editor_ptr)
        PysemsimAPI.singular_annotation_set_resource_literal(singular_annotation, "LiteralValue".encode())
        actual = PysemsimAPI.singular_annotation_get_resource(singular_annotation)
        expected = "LiteralValue"
        self.assertEqual(expected, actual.decode())

    def test_singular_annotation_resource_uri(self):
        editor_ptr = PysemsimAPI.rdf_to_editor(self.rdf, TestStrings.xml.encode(), 0)
        singular_annotation = PysemsimAPI.editor_new_singular_annotation(editor_ptr)
        PysemsimAPI.singular_annotation_set_resource_uri(singular_annotation, "UriValue".encode())
        actual = PysemsimAPI.singular_annotation_get_resource(singular_annotation)
        expected = "UriValue"
        self.assertEqual(expected, actual.decode())

    def test_singular_annotation_resource_blank(self):
        editor_ptr = PysemsimAPI.rdf_to_editor(self.rdf, TestStrings.xml.encode(), 0)
        singular_annotation = PysemsimAPI.editor_new_singular_annotation(editor_ptr)
        PysemsimAPI.singular_annotation_set_resource_blank(singular_annotation, "blank".encode())
        actual = PysemsimAPI.singular_annotation_get_resource(singular_annotation)
        expected = "blank"
        self.assertEqual(expected, actual.decode())

    def test_singular_annotation_str(self):
        editor_ptr = PysemsimAPI.rdf_to_editor(self.rdf, TestStrings.xml.encode(), 0)
        singular_annotation = PysemsimAPI.editor_new_singular_annotation(editor_ptr)
        PysemsimAPI.singular_annotation_set_about(singular_annotation, "cytosol".encode())
        PysemsimAPI.singular_annotation_set_predicate(singular_annotation, "bqb".encode(), "is".encode())
        PysemsimAPI.singular_annotation_set_resource_uri(singular_annotation, "uniprot:PD12345".encode())
        actual = PysemsimAPI.singular_annotation_str(
            singular_annotation, "rdfxml-abbrev".encode(), "singular_annotation.rdf".encode())
        expected = """<?xml version="1.0" encoding="utf-8"?>
<rdf:RDF xmlns:bqbiol="http://biomodels.net/biology-qualifiers/"
   xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"
   xml:base="singular_annotation.rdf">
  <rdf:Description rdf:about="cytosol">
    <bqbiol:is rdf:resource="https://identifiers.org/uniprot/PD12345"/>
  </rdf:Description>
</rdf:RDF>
"""
        self.assertEqual(expected, actual.decode())

    def test_editor_add_single_annotation(self):
        editor_ptr = PysemsimAPI.rdf_to_editor(self.rdf, TestStrings.xml.encode(), 0)
        singular_annotation = PysemsimAPI.editor_new_singular_annotation(editor_ptr)
        PysemsimAPI.singular_annotation_set_about(singular_annotation, "cytosol".encode())
        PysemsimAPI.singular_annotation_set_predicate(singular_annotation, "bqb".encode(), "is".encode())
        PysemsimAPI.singular_annotation_set_resource_uri(singular_annotation, "uniprot:PD12345".encode())
        PysemsimAPI.editor_add_single_annotation(editor_ptr, singular_annotation)
        PysemsimAPI.editor_to_rdf(editor_ptr, self.rdf)
        actual = PysemsimAPI.rdf_to_string(self.rdf, "turtle".encode(), "turtled_singular_annotation.rdf".encode())
        expected = """@base <file://turtled_singular_annotation.rdf> .
@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .

<cytosol>
    bqbiol:is <https://identifiers.org/uniprot/PD12345> .

"""
        self.assertEqual(expected, actual.decode())

    def test_physical_entity_about(self):
        editor_ptr = PysemsimAPI.rdf_to_editor(self.rdf, TestStrings.xml.encode(), 0)
        physical_entity = PysemsimAPI.editor_new_physical_entity(editor_ptr)
        PysemsimAPI.physical_entity_set_about(physical_entity, "cytosol".encode())
        actual = PysemsimAPI.physical_entity_get_about(physical_entity)
        expected = "cytosol"
        self.assertEqual(expected, actual.decode())

    def test_physical_entity_set_physical_property(self):
        editor_ptr = PysemsimAPI.rdf_to_editor(self.rdf, TestStrings.xml.encode(), 0)
        physical_entity = PysemsimAPI.editor_new_physical_entity(editor_ptr)
        PysemsimAPI.physical_entity_set_physical_property(physical_entity, "opb:opb12345".encode())
        actual = PysemsimAPI.physical_entity_get_physical_property(physical_entity)
        expected = "https://identifiers.org/opb/opb12345"
        self.assertEqual(expected, actual.decode())

    def test_physical_entity_set_identity(self):
        editor_ptr = PysemsimAPI.rdf_to_editor(self.rdf, TestStrings.xml.encode(), 0)
        physical_entity = PysemsimAPI.editor_new_physical_entity(editor_ptr)
        PysemsimAPI.physical_entity_set_identity(physical_entity, "uniprot:P456".encode())
        actual = PysemsimAPI.physical_entity_get_identity(physical_entity)
        expected = "https://identifiers.org/uniprot/P456"
        self.assertEqual(expected, actual.decode())

    def test_physical_entity_add_location(self):
        PysemsimAPI.physical_entity_add_location()

    #
    # def test_physical_entity_get_num_locations(self):
    #     PysemsimAPI.physical_entity_get_num_locations()
    #
    # def test_physical_entity_str(self):
    #     PysemsimAPI.physical_entity_str()
    #
    # def test_physical_entity_delete(self):
    #     PysemsimAPI.physical_entity_delete()
    #
    # def test_physical_process_set_about(self):
    #     PysemsimAPI.physical_process_set_about()
    #
    # def test_physical_process_set_physical_property(self):
    #     PysemsimAPI.physical_process_set_physical_property()
    #
    # def test_physical_process_add_source(self):
    #     PysemsimAPI.physical_process_add_source()
    #
    # def test_physical_process_add_sink(self):
    #     PysemsimAPI.physical_process_add_sink()
    #
    # def test_physical_process_add_mediator(self):
    #     PysemsimAPI.physical_process_add_mediator()
    #
    # def test_physical_process_str(self):
    #     PysemsimAPI.physical_process_str()
    #
    # def test_physical_process_get_about(self):
    #     PysemsimAPI.physical_process_get_about()
    #
    # def test_physical_process_get_physical_property(self):
    #     PysemsimAPI.physical_process_get_physical_property()
    #
    # def test_physical_process_delete(self):
    #     PysemsimAPI.physical_process_delete()
    #
    # def test_physical_property_set_about(self):
    #     PysemsimAPI.physical_property_set_about()
    #
    # def test_physical_property_set_physical_property(self):
    #     PysemsimAPI.physical_property_set_physical_property()
    #
    # def test_physical_property_add_source(self):
    #     PysemsimAPI.physical_property_add_source()
    #
    # def test_physical_property_add_sink(self):
    #     PysemsimAPI.physical_property_add_sink()
    #
    # def test_physical_property_str(self):
    #     PysemsimAPI.physical_property_str()
    #
    # def test_physical_property_get_about(self):
    #     PysemsimAPI.physical_property_get_about()
    #
    # def test_physical_property_get_physical_property(self):
    #     PysemsimAPI.physical_property_get_physical_property()
    #
    # def test_physical_property_delete(self):
    #     PysemsimAPI.physical_property_delete()
    #

    # def test_editor_add_namespace(self):
    #     editor_ptr = PysemsimAPI.rdf_to_editor(self.rdf, TestStrings.xml.encode(), 0)
    #     PysemsimAPI.editor_add_namespace()

    # def test_editor_add_physical_entity(self):
    #     PysemsimAPI.editor_add_physical_entity()
    #
    # def test_editor_add_physical_process(self):
    #     PysemsimAPI.editor_add_physical_process()
    #
    # def test_editor_add_physical_force(self):
    #     PysemsimAPI.editor_add_physical_force()
    #
    # def test_editor_check_valid_metaid(self):
    #     PysemsimAPI.editor_check_valid_metaid()
    #
    # def test_editor_to_rdf(self):
    #     PysemsimAPI.editor_to_rdf()
    #


if __name__ == "__main__":
    unittest.TestCase()
