from __future__ import annotations

import ctypes as ct
import os
import sys
from typing import List

if sys.platform != 'linux':
    raise NotImplementedError("Currently pysemsim is only supported "
                              "for linux systems. ")

_WORKING_DIRECTORY = os.path.dirname(os.path.realpath(__file__))


class Util:

    @staticmethod
    def load_lib() -> ct.CDLL:
        lib_path = os.path.join(_WORKING_DIRECTORY, "libsemsim.so")
        lib = ct.CDLL(lib_path)
        if not lib:
            raise ValueError("libsemsim.so not found")
        return lib

    @staticmethod
    def load_func(funcname: str, argtypes: List, restype) -> ct.CDLL._FuncPtr:
        func = Util.load_lib().__getattr__(funcname)
        func.restype = restype
        func.argtypes = argtypes
        return func


libsemsim = Util.load_lib()


class PysemsimAPI:

    # RDF methods
    @staticmethod
    def get_and_free_c_str(c_string_ptr: ct.c_int64) -> str:
        """Uses ctypes to transfer a C string to a python string and free the C string"""
        free_func = Util.load_func("free_c_char_star", [ct.c_void_p], None)
        string = ct.cast(c_string_ptr, ct.c_char_p).value
        decoded_str = string.decode()
        free_func(c_string_ptr)  # free the data
        del c_string_ptr  # free the ptr
        return decoded_str

    @staticmethod
    def crlf_to_lr(string: str) -> str:
        """Helper method for converting line endings. For developers"""
        return string.replace('\r\n', '\n')

    free_char_star = Util.load_func("free_c_char_star", [ct.c_char_p], None)
    rdf_new = Util.load_func("RDF_new", [], ct.c_void_p)
    rdf_size = Util.load_func("RDF_size", [ct.c_int64], ct.c_int64)

    rdf_from_string = Util.load_func("RDF_fromString",
                                     [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_void_p)
    rdf_to_string = Util.load_func("RDF_toString", [ct.c_int64, ct.c_char_p, ct.c_char_p],
                                   ct.c_int64)
    rdf_delete = Util.load_func("RDF_delete", [ct.c_int64], None)
    rdf_get_base_uri = Util.load_func("RDF_getBaseUri", [ct.c_int64], ct.c_int64)
    rdf_set_base_uri = Util.load_func("RDF_setBaseUri", [ct.c_int64, ct.c_char_p], None)
    rdf_query_results_as_str = Util.load_func("RDF_queryResultsAsStr",
                                                  [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_int64)
    rdf_to_editor = Util.load_func("RDF_toEditor", [ct.c_int64, ct.c_char_p, ct.c_int], ct.c_int64)

    # Editor methods
    editor_add_namespace = Util.load_func("Editor_addNamespace", [ct.c_int64, ct.c_char_p, ct.c_char_p],
                                          ct.c_void_p)
    editor_add_single_annotation = Util.load_func("Editor_addSingleAnnotation",
                                                  [ct.c_int64, ct.c_int64], ct.c_void_p)
    editor_add_physical_entity = Util.load_func("Editor_addPhysicalEntity", [ct.c_int64, ct.c_int64],
                                                ct.c_void_p)
    editor_add_physical_process = Util.load_func("Editor_addPhysicalProcess", [ct.c_int64, ct.c_int64],
                                                 ct.c_void_p)
    editor_add_physical_force = Util.load_func("Editor_addPhysicalForce", [ct.c_int64, ct.c_int64],
                                               ct.c_void_p)
    editor_check_valid_metaid = Util.load_func("Editor_checkValidMetaid", [ct.c_int64, ct.c_char_p],
                                               ct.c_void_p)
    editor_to_rdf = Util.load_func("Editor_toRDF", [ct.c_int64], ct.c_void_p)

    editor_new_singular_annotation = Util.load_func("SingularAnnotation_new", [ct.c_int64],
                                                    ct.c_int64)
    editor_new_physical_entity = Util.load_func("PhysicalEntity_new", [ct.c_int64], ct.c_int64)
    editor_new_physical_process = Util.load_func("PhysicalProcess_new", [ct.c_int64], ct.c_int64)
    editor_new_physical_force = Util.load_func("PhysicalForce_new", [ct.c_int64], ct.c_int64)
    editor_delete = Util.load_func("Editor_delete", [ct.c_int64], None)

    # singular annotation methods
    singular_annotation_set_about = Util.load_func("SingularAnnotation_setAbout", [ct.c_int64, ct.c_char_p], ct.c_int64)
    singular_annotation_set_predicate = Util.load_func("SingularAnnotation_setPredicate",
                                                       [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_int64)
    singular_annotation_set_predicate_uri = Util.load_func("SingularAnnotation_setPredicateFromUri",
                                                           [ct.c_int64, ct.c_char_p], ct.c_int64)

    singular_annotation_set_resource_literal = Util.load_func("SingularAnnotation_setResourceLiteral",
                                                              [ct.c_int64, ct.c_char_p], ct.c_int64)
    singular_annotation_set_resource_uri = Util.load_func("SingularAnnotation_setResourceUri",
                                                          [ct.c_int64, ct.c_char_p],
                                                          ct.c_int64)
    singular_annotation_set_resource_blank = Util.load_func("SingularAnnotation_setResourceBlank",
                                                            [ct.c_int64, ct.c_char_p], ct.c_int64)
    singular_annotation_get_about = Util.load_func("SingularAnnotation_getAbout", [ct.c_int64],
                                                   ct.c_int64)
    singular_annotation_str = Util.load_func("SingularAnnotation_str",
                                             [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_int64)
    singular_annotation_get_predicate = Util.load_func("SingularAnnotation_getPredicate", [ct.c_int64],
                                                       ct.c_int64)
    singular_annotation_get_resource = Util.load_func("SingularAnnotation_getResource", [ct.c_int64],
                                                      ct.c_int64)
    singular_annotation_delete = Util.load_func("SingularAnnotation_delete", [ct.c_int64], None)

    # PhysicalEntity methods
    physical_entity_set_about = Util.load_func("PhysicalEntity_setAbout", [ct.c_int64, ct.c_char_p], ct.c_int64)
    physical_entity_set_physical_property = Util.load_func("PhysicalEntity_setPhysicalProperty",
                                                           [ct.c_int64, ct.c_char_p], ct.c_int64)
    physical_entity_set_identity = Util.load_func("PhysicalEntity_setIdentity", [ct.c_int64, ct.c_char_p], ct.c_int64)
    physical_entity_add_location = Util.load_func("PhysicalEntity_addLocation", [ct.c_int64, ct.c_char_p], ct.c_int64)
    physical_entity_get_about = Util.load_func("PhysicalEntity_getAbout", [ct.c_int64], ct.c_int64)
    physical_entity_get_physical_property = Util.load_func("PhysicalEntity_getPhysicalProperty", [ct.c_int64],
                                                           ct.c_int64)
    physical_entity_get_identity = Util.load_func("PhysicalEntity_getIdentity", [ct.c_int64], ct.c_int64)
    physical_entity_get_num_locations = Util.load_func("PhysicalEntity_getNumLocations", [ct.c_int64],
                                                       ct.c_int)
    physical_entity_get_location = Util.load_func("PhysicalEntity_getLocation", [ct.c_int64, ct.c_int64], ct.c_int64)
    physical_entity_str = Util.load_func("PhysicalEntity_str", [ct.c_int64, ct.c_char_p, ct.c_char_p],
                                         ct.c_int64)
    physical_entity_delete = Util.load_func("PhysicalEntity_delete", [ct.c_int64], None)

    physical_entity_free_all = Util.load_func("PhysicalEntity_freeAll", [ct.c_int64], None)

    # PhysicalProcess methods
    physical_process_set_about = Util.load_func("PhysicalProcess_setAbout", [ct.c_int64, ct.c_char_p], ct.c_int64)
    physical_process_set_physical_property = Util.load_func("PhysicalProcess_setPhysicalProperty",
                                                            [ct.c_int64, ct.c_char_p], ct.c_int64)
    physical_process_add_source = Util.load_func("PhysicalProcess_addSource",
                                                 [ct.c_int64, ct.c_char_p, ct.c_float, ct.c_char_p], ct.c_int64)
    physical_process_add_sink = Util.load_func("PhysicalProcess_addSink",
                                               [ct.c_int64, ct.c_char_p, ct.c_float, ct.c_char_p], ct.c_int64)
    physical_process_add_mediator = Util.load_func("PhysicalProcess_addMediator",
                                                   [ct.c_int64, ct.c_char_p, ct.c_float, ct.c_char_p], ct.c_int64)
    physical_process_str = Util.load_func("PhysicalProcess_str",
                                          [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_int64)
    physical_process_get_about = Util.load_func("PhysicalProcess_getAbout", [ct.c_int64], ct.c_int64)
    physical_process_get_physical_property = Util.load_func("PhysicalProcess_getPhysicalProperty",
                                                            [ct.c_int64],
                                                            ct.c_int64)
    physical_process_delete = Util.load_func("PhysicalProcess_delete", [ct.c_int64], None)

    physical_process_free_all = Util.load_func("PhysicalProcess_freeAll", [ct.c_int64], None)

    # PhysicalForce Methods
    physical_force_set_about = Util.load_func("PhysicalForce_setAbout", [ct.c_int64, ct.c_char_p],
                                              ct.c_int64)
    physical_force_set_physical_property = Util.load_func("PhysicalForce_setPhysicalProperty",
                                                          [ct.c_int64, ct.c_char_p], ct.c_int64)
    physical_force_add_source = Util.load_func("PhysicalForce_addSource",
                                               [ct.c_int64, ct.c_char_p, ct.c_float, ct.c_char_p], ct.c_int64)
    physical_force_add_sink = Util.load_func("PhysicalForce_addSink",
                                             [ct.c_int64, ct.c_char_p, ct.c_float, ct.c_char_p], ct.c_int64)
    physical_force_str = Util.load_func("PhysicalForce_str",
                                        [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_int64)
    physical_force_get_about = Util.load_func("PhysicalForce_getAbout", [ct.c_int64], ct.c_int64)
    physical_force_get_physical_property = Util.load_func("PhysicalForce_getPhysicalProperty",
                                                          [ct.c_int64],
                                                          ct.c_int64)
    physical_force_delete = Util.load_func("PhysicalForce_delete", [ct.c_int64], None)

    physical_force_free_all = Util.load_func("PhysicalForce_freeAll", [ct.c_int64], None)

