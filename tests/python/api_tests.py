import ctypes as ct
import os
import site
import unittest

test_dir = os.path.dirname(os.path.dirname(os.path.realpath(__file__)))
proj_dir = os.path.dirname(test_dir)
src_dir = os.path.join(proj_dir, "src")
pysemsem_dir = os.path.join(src_dir, "pysemsim")

site.addsitedir(src_dir)

from pysemsim import Util

libsemsim = Util.load_lib()

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


class TestAPI(unittest.TestCase):

    def setUp(self) -> None:
        RDF_new_cfunc = Util.load_func(libsemsim, "RDF_new", [], ct.c_int64)
        self.rdf = RDF_new_cfunc()

    def tearDown(self) -> None:
        _rdf_delete_cfunc = Util.load_func(libsemsim, "RDF_delete", [ct.c_int64], None)
        _rdf_delete_cfunc(self.rdf)

    def test_rdf_obj(self):
        RDF_new_cfunc = Util.load_func(libsemsim, "RDF_new", [], ct.c_int64)
        new_obj = RDF_new_cfunc()
        self.assertIsInstance(new_obj, int)

    def test_rdf_from_string_cfunc(self):
        _rdf_from_string_cfunc = Util.load_func(
            libsemsim, "RDF_fromString",
            [ct.c_int64, ct.c_char_p, ct.c_char_p], None)
        format = 'rdfxml'
        print(1)
        _rdf_from_string_cfunc(self.rdf, xml.encode(), format.encode())
        print(2)

    def test_rdf_size_cfunc(self):
        _rdf_size_cfunc = Util.load_func(libsemsim, "RDF_size", [ct.c_int64], ct.c_int64)

    # def test_rdf_to_string_cfunc(self):
    #     _rdf_to_string_cfunc = Util.load_func(libsemsim, "RDF_toString", [ct.c_int64, ct.c_char_p, ct.c_char_p],
    #                                           ct.c_void_p)
    #
    # def test_rdf_getBaseUri_cfunc(self):
    #     _rdf_getBaseUri_cfunc = Util.load_func(libsemsim, "RDF_getBaseUri", [ct.c_int64], ct.c_void_p)
    #
    # def test_rdf_setBaseUri_cfunc(self):
    #     _rdf_setBaseUri_cfunc = Util.load_func(libsemsim, "RDF_setBaseUri", [ct.c_int64, ct.c_char_p], None)
    #
    # def test_rdf_queryResultsAsStr_cfunc(self):
    #     _rdf_queryResultsAsStr_cfunc = Util.load_func(libsemsim, "RDF_queryResultsAsStr",
    #                                                   [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_char_p)
    #
    # def test_rdf_to_editor(self):
    #     _rdf_to_editor = Util.load_func(libsemsim, "RDF_toEditor", [ct.c_int64, ct.c_char_p, ct.c_int], ct.c_int64)
    #
    # def test_editor_ptr(self):
    #     _editor_ptr = editor_ptr
    #
    # def test_addNamespace_cfunc(self):
    #     _addNamespace_cfunc = Util.load_func(libsemsim, "Editor_addNamespace", [ct.c_int64, ct.c_char_p], ct.c_void_p)
    #
    # def test_addSingleAnnotation_cfunc(self):
    #     _addSingleAnnotation_cfunc = Util.load_func(libsemsim, "Editor_addSingleAnnotation", [ct.c_int64, ct.c_int64],
    #                                                 ct.c_void_p)
    #
    # def test_addPhysicalEntity_cfunc(self):
    #     _addPhysicalEntity_cfunc = Util.load_func(libsemsim, "Editor_addPhysicalEntity", [ct.c_int64, ct.c_int64],
    #                                               ct.c_void_p)
    #
    # def test_addPhysicalProcess_cfunc(self):
    #     _addPhysicalProcess_cfunc = Util.load_func(libsemsim, "Editor_addPhysicalProcess", [ct.c_int64, ct.c_int64],
    #                                                ct.c_void_p)
    #
    # def test_addPhysicalForce_cfunc(self):
    #     _addPhysicalForce_cfunc = Util.load_func(libsemsim, "Editor_addPhysicalForce", [ct.c_int64, ct.c_int64],
    #                                              ct.c_void_p)
    #
    # def test_checkValidMetaid_cfunc(self):
    #     _checkValidMetaid_cfunc = Util.load_func(libsemsim, "Editor_checkValidMetaid", [ct.c_int64, ct.c_char_p],
    #                                              ct.c_void_p)
    #
    # def test_toRDF_cfunc(self):
    #     _toRDF_cfunc = Util.load_func(libsemsim, "Editor_toRDF", [ct.c_int64], ct.c_void_p)
    #
    # def test_new_singular_annotation_cfunc(self):
    #     _new_singular_annotation_cfunc = Util.load_func(libsemsim, "SingularAnnotation_new", [ct.c_int64], ct.c_int64)
    #
    # def test_new_physical_entity_cfunc(self):
    #     _new_physical_entity_cfunc = Util.load_func(libsemsim, "PhysicalEntity_new", [ct.c_int64], ct.c_int64)
    #
    # def test_new_physical_process_cfunc(self):
    #     _new_physical_process_cfunc = Util.load_func(libsemsim, "PhysicalProcess_new", [ct.c_int64], ct.c_int64)
    #
    # def test_new_physical_force_cfunc(self):
    #     _new_physical_force_cfunc = Util.load_func(libsemsim, "PhysicalForce_new", [ct.c_int64], ct.c_int64)
    #
    # def test_delete_cfunc(self):
    #     _delete_cfunc = Util.load_func(libsemsim, "Editor_delete", [ct.c_int64], None)
    #
    # def test_singular_annotation_ptr(self):
    #     _singular_annotation_ptr = singular_annotation_ptr
    #
    # def test_setAbout_cfunc(self):
    #     _setAbout_cfunc = Util.load_func(libsemsim, "SingularAnnotation_setAbout", [ct.c_int64, ct.c_char_p],
    #                                      ct.c_int64)
    #
    # def test_setPredicate_cfunc(self):
    #     _setPredicate_cfunc = Util.load_func(libsemsim, "SingularAnnotation_setPredicate",
    #                                          [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_int64)
    #
    # def test_setPredicateNew_cfunc(self):
    #     _setPredicateNew_cfunc = Util.load_func(libsemsim, "SingularAnnotation_setPredicateNew",
    #                                             [ct.c_int64, ct.c_char_p, ct.c_char_p, ct.c_char_p], ct.c_int64)
    #
    # def test_setResourceLiteral_cfunc(self):
    #     _setResourceLiteral_cfunc = Util.load_func(libsemsim, "SingularAnnotation_setResourceLiteral",
    #                                                [ct.c_int64, ct.c_char_p], ct.c_int64)
    #
    # def test_setResourceUri_cfunc(self):
    #     _setResourceUri_cfunc = Util.load_func(libsemsim, "SingularAnnotation_setResourceUri",
    #                                            [ct.c_int64, ct.c_char_p], ct.c_int64)
    #
    # def test_setResourceBlank_cfunc(self):
    #     _setResourceBlank_cfunc = Util.load_func(libsemsim, "SingularAnnotation_setResourceBlank",
    #                                              [ct.c_int64, ct.c_char_p], ct.c_int64)
    #
    # def test_getAbout_cfunc(self):
    #     _getAbout_cfunc = Util.load_func(libsemsim, "SingularAnnotation_getAbout", [ct.c_int64], ct.c_void_p)
    #
    # def test_str_cfunc(self):
    #     _str_cfunc = Util.load_func(libsemsim, "SingularAnnotation_str", [ct.c_int64, ct.c_char_p, ct.c_char_p],
    #                                 ct.c_void_p)
    #
    # def test_getPredicate_cfunc(self):
    #     _getPredicate_cfunc = Util.load_func(libsemsim, "SingularAnnotation_getPredicate", [ct.c_int64], ct.c_void_p)
    #
    # def test_getResource_cfunc(self):
    #     _getResource_cfunc = Util.load_func(libsemsim, "SingularAnnotation_getResource", [ct.c_int64], ct.c_void_p)
    #
    # def test_delete_cfunc(self):
    #     _delete_cfunc = Util.load_func(libsemsim, "SingularAnnotation_delete", [ct.c_int64], None)
    #
    # def test_physical_entity_ptr(self):
    #     _physical_entity_ptr = physical_entity_ptr
    #
    # def test_setAbout_cfunc(self):
    #     _setAbout_cfunc = Util.load_func(libsemsim, "PhysicalEntity_setAbout", [ct.c_int64, ct.c_char_p], ct.c_void_p)
    #
    # def test_setPhysicalProperty_cfunc(self):
    #     _setPhysicalProperty_cfunc = Util.load_func(libsemsim, "PhysicalEntity_setPhysicalProperty",
    #                                                 [ct.c_int64, ct.c_char_p], ct.c_void_p)
    #
    # def test_setIdentity_cfunc(self):
    #     _setIdentity_cfunc = Util.load_func(libsemsim, "PhysicalEntity_setIdentity", [ct.c_int64, ct.c_char_p],
    #                                         ct.c_void_p)
    #
    # def test_addLocation_cfunc(self):
    #     _addLocation_cfunc = Util.load_func(libsemsim, "PhysicalEntity_addLocation", [ct.c_int64, ct.c_char_p],
    #                                         ct.c_void_p)
    #
    # def test_getAbout_cfunc(self):
    #     _getAbout_cfunc = Util.load_func(libsemsim, "PhysicalEntity_getAbout", [ct.c_int64], ct.c_void_p)
    #
    # def test_getPhysicalProperty_cfunc(self):
    #     _getPhysicalProperty_cfunc = Util.load_func(libsemsim, "PhysicalEntity_getPhysicalProperty", [ct.c_int64],
    #                                                 ct.c_void_p)
    #
    # def test_getIdentity_cfunc(self):
    #     _getIdentity_cfunc = Util.load_func(libsemsim, "PhysicalEntity_getIdentity", [ct.c_int64], ct.c_void_p)
    #
    # def test_getNumLocations_cfunc(self):
    #     _getNumLocations_cfunc = Util.load_func(libsemsim, "PhysicalEntity_getNumLocations", [ct.c_int64], ct.c_int)
    #
    # def test_getLocations_cfunc(self):
    #     _getLocations_cfunc = Util.load_func(libsemsim, "PhysicalEntity_getLocations", [ct.c_int64], ct.c_void_p)
    #
    # def test_str_cfunc(self):
    #     _str_cfunc = Util.load_func(libsemsim, "PhysicalEntity_str", [ct.c_int64, ct.c_char_p, ct.c_char_p],
    #                                 ct.c_void_p)
    #
    # def test_delete_cfunc(self):
    #     _delete_cfunc = Util.load_func(libsemsim, "PhysicalEntity_delete", [ct.c_int64], None)
    #
    # def test_physical_process_ptr(self):
    #     _physical_process_ptr = physical_process_ptr
    #
    # def test_setAbout_cfunc(self):
    #     _setAbout_cfunc = Util.load_func(libsemsim, "PhysicalProcess_setAbout", [ct.c_int64, ct.c_char_p], ct.c_void_p)
    #
    # def test_setPhysicalProperty_cfunc(self):
    #     _setPhysicalProperty_cfunc = Util.load_func(libsemsim, "PhysicalProcess_setPhysicalProperty",
    #                                                 [ct.c_int64, ct.c_char_p], ct.c_void_p)
    #
    # def test_addSource_cfunc(self):
    #     _addSource_cfunc = Util.load_func(libsemsim, "PhysicalProcess_addSource",
    #                                       [ct.c_int64, ct.c_char_p, ct.c_float, ct.c_char_p], ct.c_void_p)
    #
    # def test_addSink_cfunc(self):
    #     _addSink_cfunc = Util.load_func(libsemsim, "PhysicalProcess_addSink",
    #                                     [ct.c_int64, ct.c_char_p, ct.c_float, ct.c_char_p], ct.c_void_p)
    #
    # def test_addMediator_cfunc(self):
    #     _addMediator_cfunc = Util.load_func(libsemsim, "PhysicalProcess_addMediator",
    #                                         [ct.c_int64, ct.c_char_p, ct.c_float, ct.c_char_p], ct.c_void_p)
    #
    # def test_str_cfunc(self):
    #     _str_cfunc = Util.load_func(libsemsim, "PhysicalProcess_str", [ct.c_int64, ct.c_char_p, ct.c_char_p],
    #                                 ct.c_void_p)
    #
    # def test_getAbout_cfunc(self):
    #     _getAbout_cfunc = Util.load_func(libsemsim, "PhysicalProcess_getAbout", [ct.c_int64], ct.c_void_p)
    #
    # def test_getPhysicalProperty_cfunc(self):
    #     _getPhysicalProperty_cfunc = Util.load_func(libsemsim, "PhysicalProcess_getPhysicalProperty", [ct.c_int64],
    #                                                 ct.c_void_p)
    #
    # def test_delete_cfunc(self):
    #     _delete_cfunc = Util.load_func(libsemsim, "PhysicalProcess_delete", [ct.c_int64], None)
    #
    # def test_physical_force_ptr(self):
    #     _physical_force_ptr = physical_force_ptr
    #
    # def test_setAbout_cfunc(self):
    #     _setAbout_cfunc = Util.load_func(libsemsim, "PhysicalForce_setAbout", [ct.c_int64, ct.c_char_p], ct.c_void_p)
    #
    # def test_setPhysicalProperty_cfunc(self):
    #     _setPhysicalProperty_cfunc = Util.load_func(libsemsim, "PhysicalForce_setPhysicalProperty",
    #                                                 [ct.c_int64, ct.c_char_p], ct.c_void_p)
    #
    # def test_addSource_cfunc(self):
    #     _addSource_cfunc = Util.load_func(libsemsim, "PhysicalForce_addSource",
    #                                       [ct.c_int64, ct.c_char_p, ct.c_float, ct.c_char_p], ct.c_void_p)
    #
    # def test_addSink_cfunc(self):
    #     _addSink_cfunc = Util.load_func(libsemsim, "PhysicalForce_addSink",
    #                                     [ct.c_int64, ct.c_char_p, ct.c_float, ct.c_char_p], ct.c_void_p)
    #
    # def test_str_cfunc(self):
    #     _str_cfunc = Util.load_func(libsemsim, "PhysicalForce_str", [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_void_p)
    #
    # def test_getAbout_cfunc(self):
    #     _getAbout_cfunc = Util.load_func(libsemsim, "PhysicalForce_getAbout", [ct.c_int64], ct.c_void_p)
    #
    # def test_getPhysicalProperty_cfunc(self):
    #     _getPhysicalProperty_cfunc = Util.load_func(libsemsim, "PhysicalForce_getPhysicalProperty", [ct.c_int64],
    #                                                 ct.c_void_p)
    #
    # def test_delete_cfunc(self):
    #     _delete_cfunc = Util.load_func(libsemsim, "PhysicalForce_delete", [ct.c_int64], None)


if __name__ == "__main__":
    unittest.TestCase()
