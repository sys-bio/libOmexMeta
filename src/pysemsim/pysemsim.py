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
    def load_func(lib: ct.CDLL, funcname: str, argtypes: List, restype) -> ct.CDLL._FuncPtr:
        func = lib.__getattr__(funcname)
        func.restype = restype
        func.argtypes = argtypes
        return func

    @staticmethod
    def crlf_to_lr(string: str) -> str:
        return string.replace('\r\n', '\n')

    @staticmethod
    def get_and_free_c_str(c_string_ptr: ct.c_int64) -> str:
        free_func = Util.load_func(Util.load_lib(), "free_c_char_star", [ct.c_void_p], None)
        string = ct.cast(c_string_ptr, ct.c_char_p).value
        decoded_str = string.decode()
        free_func(c_string_ptr)  # free the data
        del c_string_ptr  # free the ptr
        return decoded_str


libsemsim = Util.load_lib()


class _XmlAssistantType:
    """
    Class used internally for directing the underlying c++
    code to work with cellml or sbml.
    """

    def __init__(self, xml_type):
        self.type = None
        if xml_type == "sbml":
            self.type = 0
        elif xml_type == "cellml":
            self.type = 1
        else:
            raise ValueError("\"xml_type\" arg must be either \"sbml\" or \"cellml\"")

    def getType(self):
        return self.type


class RDF:

    def __init__(self):
        RDF_new_cfunc = Util.load_func(libsemsim, "RDF_new", [], ct.c_int64)

        self._obj = RDF_new_cfunc()

        self._rdf_size_cfunc = Util.load_func(libsemsim, "RDF_size", [ct.c_int64], ct.c_int64)
        self._rdf_from_string_cfunc = Util.load_func(libsemsim, "RDF_fromString",
                                                     [ct.c_int64, ct.c_char_p, ct.c_char_p], None)
        self._rdf_to_string_cfunc = Util.load_func(libsemsim, "RDF_toString", [ct.c_int64, ct.c_char_p, ct.c_char_p],
                                                   ct.c_char_p)
        self._rdf_delete_cfunc = Util.load_func(libsemsim, "RDF_delete", [ct.c_int64], None)
        self._rdf_getBaseUri_cfunc = Util.load_func(libsemsim, "RDF_getBaseUri", [ct.c_int64], ct.c_void_p)
        self._rdf_setBaseUri_cfunc = Util.load_func(libsemsim, "RDF_setBaseUri", [ct.c_int64, ct.c_char_p], None)
        self._rdf_queryResultsAsStr_cfunc = Util.load_func(libsemsim, "RDF_queryResultsAsStr",
                                                           [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_char_p)
        self._rdf_to_editor = Util.load_func(libsemsim, "RDF_toEditor", [ct.c_int64, ct.c_char_p, ct.c_int], ct.c_int64)

    @staticmethod
    def from_string(rdf_string: str, format: str = "guess") -> RDF:
        rdf = RDF()
        rdf._rdf_from_string_cfunc(rdf._obj, rdf_string.encode(), format.encode())
        return rdf

    def delete(self):
        """destructor. Delete the dynamically allocated rdf object"""
        self._rdf_delete_cfunc(self._obj)

    def __len__(self):
        """Returns the number of individual Triples stored in the rdf model"""
        return self._rdf_size_cfunc(self._obj)

    def __str__(self):
        return self.to_string("rdfxml-abbrev", base_uri="./Annotation.rdf")

    def to_string(self, format: str, base_uri: str) -> str:
        str_ptr = self._rdf_to_string_cfunc(self._obj, format.encode(), base_uri.encode())
        thestring = Util.get_and_free_c_str(str_ptr)
        return thestring

    def get_base_uri(self) -> str:
        return Util.get_and_free_c_str(self._rdf_getBaseUri_cfunc(self._obj))

    def set_base_uri(self, uri: str) -> None:
        if not os.path.isfile(uri):
            uri = os.path.join(os.path.realpath(os.getcwd()), uri)
        self._rdf_setBaseUri_cfunc(self._obj, uri.encode())

    def query(self, query_str: str, results_format: str) -> str:
        results_crlf = self._rdf_queryResultsAsStr_cfunc(self._obj, query_str.encode(), results_format.encode()).decode(
            "utf-8")
        results_lf = Util.crlf_to_lr(results_crlf)
        return results_lf

    def to_editor(self, xml: str, xmltype: str) -> Editor:
        return Editor(self._rdf_to_editor(self._obj, xml.encode(), _XmlAssistantType(xml_type=xmltype).getType()))


class Editor:

    def __init__(self, editor_ptr):
        self._editor_ptr = editor_ptr

        self._addNamespace_cfunc = Util.load_func(libsemsim, "Editor_addNamespace", [ct.c_int64, ct.c_char_p],
                                                  ct.c_void_p)
        self._addSingleAnnotation_cfunc = Util.load_func(libsemsim, "Editor_addSingleAnnotation",
                                                         [ct.c_int64, ct.c_int64], ct.c_void_p)
        self._addPhysicalEntity_cfunc = Util.load_func(libsemsim, "Editor_addPhysicalEntity", [ct.c_int64, ct.c_int64],
                                                       ct.c_void_p)
        self._addPhysicalProcess_cfunc = Util.load_func(libsemsim, "Editor_addPhysicalProcess", [ct.c_int64, ct.c_int64],
                                                        ct.c_void_p)
        self._addPhysicalForce_cfunc = Util.load_func(libsemsim, "Editor_addPhysicalForce", [ct.c_int64, ct.c_int64],
                                                      ct.c_void_p)
        self._checkValidMetaid_cfunc = Util.load_func(libsemsim, "Editor_checkValidMetaid", [ct.c_int64, ct.c_char_p],
                                                      ct.c_void_p)
        self._toRDF_cfunc = Util.load_func(libsemsim, "Editor_toRDF", [ct.c_int64], ct.c_void_p)

        self._new_singular_annotation_cfunc = Util.load_func(libsemsim, "SingularAnnotation_new", [ct.c_int64], ct.c_int64)
        self._new_physical_entity_cfunc = Util.load_func(libsemsim, "PhysicalEntity_new", [ct.c_int64], ct.c_int64)
        self._new_physical_process_cfunc = Util.load_func(libsemsim, "PhysicalProcess_new", [ct.c_int64], ct.c_int64)
        self._new_physical_force_cfunc = Util.load_func(libsemsim, "PhysicalForce_new", [ct.c_int64], ct.c_int64)
        self._delete_cfunc = Util.load_func(libsemsim, "Editor_delete", [ct.c_int64], None)

    def add_namespace(self, namespace: str, prefix: str) -> None:
        self._addNamespace_cfunc(self._editor_ptr, namespace, str)

    def add_singular_annotation(self, singular_annotation: SingularAnnotation) -> None:
        self._addSingleAnnotation_cfunc(self._editor_ptr, singular_annotation.get_ptr())

    def add_physical_entity(self, physical_entity: PhysicalEntity) -> None:
        self._addPhysicalEntity_cfunc(self._editor_ptr, physical_entity.get_ptr())

    def add_physical_process(self, physical_process: PhysicalProcess) -> None:
        self._addPhysicalProcess_cfunc(self._editor_ptr, physical_process.get_ptr())

    def add_physical_force(self, physical_force: PhysicalForce) -> None:
        self._addPhysicalForce_cfunc(self._editor_ptr, physical_force.get_ptr())

    def check_valid_metaid(self, id: str) -> None:
        self._checkValidMetaid_cfunc(self._editor_ptr, id)

    def to_rdf(self) -> None:
        self._toRDF_cfunc(self._editor_ptr)

    def new_singular_annotation(self) -> SingularAnnotation:
        return SingularAnnotation(self._new_singular_annotation_cfunc(self._editor_ptr))

    def new_physical_entity(self) -> PhysicalEntity:
        return PhysicalEntity(self._new_physical_entity_cfunc(self._editor_ptr))

    def new_physical_process(self) -> PhysicalProcess:
        return PhysicalProcess(self._new_physical_process_cfunc(self._editor_ptr))

    def new_physical_force(self) -> PhysicalForce:
        return PhysicalForce(self._new_physical_force_cfunc(self._editor_ptr))

    def delete(self):
        self._delete_cfunc(self._editor_ptr)

class SingularAnnotation:

    def __init__(self, singular_annotation_ptr):
        self._singular_annotation_ptr = singular_annotation_ptr

        self._setAbout_cfunc = Util.load_func(libsemsim, "SingularAnnotation_setAbout", [ct.c_int64, ct.c_char_p], ct.c_int64)
        self._setPredicate_cfunc = Util.load_func(libsemsim, "SingularAnnotation_setPredicate",
                                                  [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_int64)
        self._setPredicateNew_cfunc = Util.load_func(libsemsim, "SingularAnnotation_setPredicateNew",
                                                     [ct.c_int64, ct.c_char_p, ct.c_char_p, ct.c_char_p], ct.c_int64)
        self._setResourceLiteral_cfunc = Util.load_func(libsemsim, "SingularAnnotation_setResourceLiteral",
                                                        [ct.c_int64, ct.c_char_p], ct.c_int64)
        self._setResourceUri_cfunc = Util.load_func(libsemsim, "SingularAnnotation_setResourceUri", [ct.c_int64, ct.c_char_p],
                                                    ct.c_int64)
        self._setResourceBlank_cfunc = Util.load_func(libsemsim, "SingularAnnotation_setResourceBlank",
                                                      [ct.c_int64, ct.c_char_p], ct.c_int64)
        self._getAbout_cfunc = Util.load_func(libsemsim, "SingularAnnotation_getAbout", [ct.c_int64], ct.c_void_p)
        self._str_cfunc = Util.load_func(libsemsim, "SingularAnnotation_str", [ct.c_int64, ct.c_char_p, ct.c_char_p],
                                         ct.c_void_p)
        self._getPredicate_cfunc = Util.load_func(libsemsim, "SingularAnnotation_getPredicate", [ct.c_int64], ct.c_void_p)
        self._getResource_cfunc = Util.load_func(libsemsim, "SingularAnnotation_getResource", [ct.c_int64], ct.c_void_p)
        self._delete_cfunc = Util.load_func(libsemsim, "SingularAnnotation_delete", [ct.c_int64], None)

    def get_ptr(self):
        return self._singular_annotation_ptr

    def set_about(self, about: str) -> SingularAnnotation:
        self._setAbout_cfunc(self._singular_annotation_ptr, about.encode())
        return self

    def set_predicate(self, namespace: str, term: str) -> SingularAnnotation:
        self._setPredicate_cfunc(self._singular_annotation_ptr, namespace.encode(), term.encode())
        return self

    def set_predicate_new(self, namespace: str, term: str, prefix: str) -> SingularAnnotation:
        self._setPredicateNew_cfunc(self._singular_annotation_ptr, namespace.encode(), term.encode(), prefix.encode())
        return self

    def set_resource_literal(self, literal: str) -> SingularAnnotation:
        self._setResourceLiteral_cfunc(self._singular_annotation_ptr, literal.encode())
        return self

    def set_resource_uri(self, uri: str) -> SingularAnnotation:
        self._setResourceUri_cfunc(self._singular_annotation_ptr, uri.encode())
        return self

    def set_resource_blank(self, blank_id: str) -> SingularAnnotation:
        self._setResourceBlank_cfunc(self._singular_annotation_ptr, blank_id.encode())
        return self

    def get_about(self) -> str:
        return Util.get_and_free_c_str(self._getAbout_cfunc(self._singular_annotation_ptr))

    def __str__(self):
        return self.to_string("rdfxml-abbrev", "./Annotation.rdf")

    def to_string(self, format: str, base_uri: str) -> str:
        return Util.get_and_free_c_str(
            self._str_cfunc(self._singular_annotation_ptr, format.encode(), base_uri.encode()))

    def get_predicate(self) -> str:
        return Util.get_and_free_c_str(self._getPredicate_cfunc(self._singular_annotation_ptr))

    def get_resource(self) -> str:
        return Util.get_and_free_c_str(self._getResource_cfunc(self._singular_annotation_ptr))

    def delete(self):
        self._delete_cfunc(self._singular_annotation_ptr)


class PhysicalEntity:

    def __init__(self, physical_entity_ptr):
        self._physical_entity_ptr = physical_entity_ptr

        self._setAbout_cfunc = Util.load_func(libsemsim, "PhysicalEntity_setAbout", [ct.c_int64, ct.c_char_p], ct.c_void_p)
        self._setPhysicalProperty_cfunc = Util.load_func(libsemsim, "PhysicalEntity_setPhysicalProperty",
                                                         [ct.c_int64, ct.c_char_p], ct.c_void_p)
        self._setIdentity_cfunc = Util.load_func(libsemsim, "PhysicalEntity_setIdentity", [ct.c_int64, ct.c_char_p],
                                                 ct.c_void_p)
        self._addLocation_cfunc = Util.load_func(libsemsim, "PhysicalEntity_addLocation", [ct.c_int64, ct.c_char_p],
                                                 ct.c_void_p)
        self._getAbout_cfunc = Util.load_func(libsemsim, "PhysicalEntity_getAbout", [ct.c_int64], ct.c_void_p)
        self._getPhysicalProperty_cfunc = Util.load_func(libsemsim, "PhysicalEntity_getPhysicalProperty", [ct.c_int64],
                                                         ct.c_void_p)
        self._getIdentity_cfunc = Util.load_func(libsemsim, "PhysicalEntity_getIdentity", [ct.c_int64], ct.c_void_p)
        self._getNumLocations_cfunc = Util.load_func(libsemsim, "PhysicalEntity_getNumLocations", [ct.c_int64], ct.c_int)
        self._getLocations_cfunc = Util.load_func(libsemsim, "PhysicalEntity_getLocations", [ct.c_int64], ct.c_void_p)
        self._str_cfunc = Util.load_func(libsemsim, "PhysicalEntity_str", [ct.c_int64, ct.c_char_p, ct.c_char_p],
                                         ct.c_void_p)
        self._delete_cfunc = Util.load_func(libsemsim, "PhysicalEntity_delete", [ct.c_int64], None)

    def get_ptr(self) -> ct.c_int64:
        return self._physical_entity_ptr

    def set_about(self, about: str) -> PhysicalEntity:
        self._setAbout_cfunc(self._physical_entity_ptr, about.encode())
        return self

    def set_physical_property(self, property: str) -> PhysicalEntity:
        self._setPhysicalProperty_cfunc(self.get_ptr(), property.encode())
        return self

    def set_identity(self, identity: str) -> PhysicalEntity:
        self._setIdentity_cfunc(self.get_ptr(), identity.encode())
        return self

    def add_location(self, location: str) -> PhysicalEntity:
        self._addLocation_cfunc(self.get_ptr(), location.encode())
        return self

    def get_about(self) -> str:
        return Util.get_and_free_c_str(self._getAbout_cfunc(self.get_ptr()))

    def get_physical_property(self) -> str:
        return Util.get_and_free_c_str(self._getPhysicalProperty_cfunc(self.get_ptr()))

    def get_identity(self) -> str:
        return Util.get_and_free_c_str(self._getIdentity_cfunc(self.get_ptr()))

    def get_num_locations(self) -> int:
        return self._getNumLocations_cfunc(self.get_ptr())

    def get_locations(self) -> List[str]:
        return self._getLocations_cfunc(self.get_ptr(), )

    def to_string(self, format: str, base_uri: str) -> str:
        return Util.get_and_free_c_str(self._str_cfunc(self.get_ptr(), format.encode(), base_uri.encode()))

    def __str__(self):
        return self.to_string("rdfxml-abbrev", "./Annotation.rdf")

    def delete(self):
        self._delete_cfunc(self._physical_entity_ptr)


class PhysicalProcess:

    def __init__(self, physical_process_ptr):
        self._physical_process_ptr = physical_process_ptr

        self._setAbout_cfunc = Util.load_func(libsemsim, "PhysicalProcess_setAbout", [ct.c_int64, ct.c_char_p], ct.c_void_p)
        self._setPhysicalProperty_cfunc = Util.load_func(libsemsim, "PhysicalProcess_setPhysicalProperty",
                                                         [ct.c_int64, ct.c_char_p], ct.c_void_p)
        self._addSource_cfunc = Util.load_func(libsemsim, "PhysicalProcess_addSource",
                                               [ct.c_int64, ct.c_char_p, ct.c_float, ct.c_char_p], ct.c_void_p)
        self._addSink_cfunc = Util.load_func(libsemsim, "PhysicalProcess_addSink",
                                             [ct.c_int64, ct.c_char_p, ct.c_float, ct.c_char_p], ct.c_void_p)
        self._addMediator_cfunc = Util.load_func(libsemsim, "PhysicalProcess_addMediator",
                                                 [ct.c_int64, ct.c_char_p, ct.c_float, ct.c_char_p], ct.c_void_p)
        self._str_cfunc = Util.load_func(libsemsim, "PhysicalProcess_str",
                                         [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_void_p)
        self._getAbout_cfunc = Util.load_func(libsemsim, "PhysicalProcess_getAbout", [ct.c_int64], ct.c_void_p)
        self._getPhysicalProperty_cfunc = Util.load_func(libsemsim, "PhysicalProcess_getPhysicalProperty", [ct.c_int64],
                                                         ct.c_void_p)
        self._delete_cfunc = Util.load_func(libsemsim, "PhysicalProcess_delete", [ct.c_int64], None)

    def get_ptr(self):
        return self._physical_process_ptr

    def set_about(self, about: str) -> PhysicalProcess:
        self._setAbout_cfunc(self._physical_process_ptr, about.encode())
        return self

    def set_physical_property(self, property: str) -> PhysicalProcess:
        self._setPhysicalProperty_cfunc(self._physical_process_ptr, property.encode())
        return self

    def add_source(self, source_id: str, multiplier: float, physical_entity_reference: str) -> PhysicalProcess:
        self._addSource_cfunc(self._physical_process_ptr, source_id.encode(), multiplier, physical_entity_reference.encode())
        return self

    def add_sink(self, sink_id: str, multiplier: float, physical_entity_reference: str) -> PhysicalProcess:
        self._addSink_cfunc(self._physical_process_ptr, sink_id.encode(), multiplier, physical_entity_reference.encode())
        return self

    def add_mediator(self, mediator_id: str, multiplier: float, physical_entity_reference: str) -> PhysicalProcess:
        self._addMediator_cfunc(self._physical_process_ptr, mediator_id.encode(), multiplier,
                                physical_entity_reference.encode())
        return self

    def to_string(self, format: str, base_uri: str):
        return Util.get_and_free_c_str(self._str_cfunc(self._physical_process_ptr, format.encode(), base_uri.encode()))

    def __str__(self):
        return self.to_string("rdfxml-abbrev", "./Annotation.rdf")

    def get_about(self) -> str:
        return Util.get_and_free_c_str(self._getAbout_cfunc(self._physical_process_ptr))

    def get_physical_property(self):
        return Util.get_and_free_c_str(self._getPhysicalProperty_cfunc(self._physical_process_ptr))

    def delete(self):
        self._delete_cfunc(self._physical_process_ptr)


class PhysicalForce:

    def __init__(self, physical_force_ptr):
        self._physical_force_ptr = physical_force_ptr

        self._setAbout_cfunc = Util.load_func(libsemsim, "PhysicalForce_setAbout", [ct.c_int64, ct.c_char_p], ct.c_void_p)
        self._setPhysicalProperty_cfunc = Util.load_func(libsemsim, "PhysicalForce_setPhysicalProperty",
                                                         [ct.c_int64, ct.c_char_p], ct.c_void_p)
        self._addSource_cfunc = Util.load_func(libsemsim, "PhysicalForce_addSource",
                                               [ct.c_int64, ct.c_char_p, ct.c_float, ct.c_char_p], ct.c_void_p)
        self._addSink_cfunc = Util.load_func(libsemsim, "PhysicalForce_addSink",
                                             [ct.c_int64, ct.c_char_p, ct.c_float, ct.c_char_p], ct.c_void_p)
        self._str_cfunc = Util.load_func(libsemsim, "PhysicalForce_str",
                                         [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_void_p)
        self._getAbout_cfunc = Util.load_func(libsemsim, "PhysicalForce_getAbout", [ct.c_int64], ct.c_void_p)
        self._getPhysicalProperty_cfunc = Util.load_func(libsemsim, "PhysicalForce_getPhysicalProperty", [ct.c_int64],
                                                         ct.c_void_p)
        self._delete_cfunc = Util.load_func(libsemsim, "PhysicalForce_delete", [ct.c_int64], None)

    def get_ptr(self):
        return self._physical_force_ptr

    def set_about(self, about: str) -> PhysicalForce:
        self._setAbout_cfunc(self._physical_force_ptr, about.encode())
        return self

    def set_physical_property(self, property: str) -> PhysicalForce:
        self._setPhysicalProperty_cfunc(self._physical_force_ptr, property.encode())
        return self

    def add_source(self, source_id: str, multiplier: float, physical_entity_reference: str) -> PhysicalForce:
        self._addSource_cfunc(self._physical_force_ptr, source_id.encode(), multiplier, physical_entity_reference.encode())
        return self

    def add_sink(self, sink_id: str, multiplier: float, physical_entity_reference: str) -> PhysicalForce:
        self._addSink_cfunc(self._physical_force_ptr, sink_id.encode(), multiplier, physical_entity_reference.encode())
        return self

    def to_string(self, format: str, base_uri: str):
        return Util.get_and_free_c_str(self._str_cfunc(self._physical_force_ptr, format.encode(), base_uri.encode()))

    def __str__(self):
        return self.to_string("rdfxml-abbrev", "./Annotation.rdf")

    def get_about(self) -> str:
        return Util.get_and_free_c_str(self._getAbout_cfunc(self._physical_force_ptr))

    def get_physical_property(self):
        return Util.get_and_free_c_str(self._getPhysicalProperty_cfunc(self._physical_force_ptr))

    def delete(self):
        self._delete_cfunc(self._physical_force_ptr)
