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
        RDF_new_cfunc = Util.load_func(libsemsim, "new_rdf", [], ct.c_int64)

        self._obj = RDF_new_cfunc()

        self._rdf_size_cfunc = Util.load_func(libsemsim, "RDF_size", [ct.c_int64], ct.c_int64)
        self._rdf_from_string_cfunc = Util.load_func(libsemsim, "RDF_fromString",
                                                     [ct.c_int64, ct.c_char_p, ct.c_char_p], None)
        self._rdf_to_string_cfunc = Util.load_func(libsemsim, "RDF_toString", [ct.c_int64, ct.c_char_p, ct.c_char_p],
                                                   ct.c_char_p)
        self._rdf_free_cfunc = Util.load_func(libsemsim, "RDF_free", [ct.c_int64], None)
        self._rdf_getBaseUri_cfunc = Util.load_func(libsemsim, "RDF_getBaseUri", [ct.c_int64], ct.c_char_p)
        self._rdf_setBaseUri_cfunc = Util.load_func(libsemsim, "RDF_setBaseUri", [ct.c_int64, ct.c_char_p], None)
        self._rdf_queryResultsAsStr_cfunc = Util.load_func(libsemsim, "RDF_queryResultsAsStr",
                                                           [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_char_p)
        self._rdf_to_editor = Util.load_func(libsemsim, "RDF_toEditor", [ct.c_int64, ct.c_char_p, ct.c_int], ct.c_int64)

    @staticmethod
    def from_string(rdf_string: str, format: str = "guess") -> RDF:
        rdf = RDF()
        rdf._rdf_from_string_cfunc(rdf._obj, rdf_string.encode(), format.encode())
        return rdf

    def __del__(self):
        """destructor. Delete the dynamically allocated rdf object"""
        self._rdf_free_cfunc(self._obj)

    def __len__(self):
        """Returns the number of individual Triples stored in the rdf model"""
        return self._rdf_size_cfunc(self._obj)

    def __str__(self):
        return self.to_string("rdfxml-abbrev", base_uri="./Annotation.rdf")

    def to_string(self, format: str, base_uri: str) -> str:
        return self._rdf_to_string_cfunc(self._obj, format.encode(), base_uri.encode()).decode()

    def get_base_uri(self) -> str:
        return self._rdf_getBaseUri_cfunc(self._obj).decode()

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
        self.editor_ptr = editor_ptr

        self._addNamespace_func = Util.load_func(libsemsim, "Editor_addNamespace", [ct.c_int64, ct.c_char_p],
                                                 ct.c_void_p)
        self._addSingleAnnotation_func = Util.load_func(libsemsim, "Editor_addSingleAnnotation",
                                                        [ct.c_int64, ct.c_int64], ct.c_void_p)
        self._addPhysicalEntity_func = Util.load_func(libsemsim, "Editor_addPhysicalEntity", [ct.c_int64, ct.c_int64],
                                                      ct.c_void_p)
        self._addPhysicalProcess_func = Util.load_func(libsemsim, "Editor_addPhysicalProcess", [ct.c_int64, ct.c_int64],
                                                       ct.c_void_p)
        self._addPhysicalForce_func = Util.load_func(libsemsim, "Editor_addPhysicalForce", [ct.c_int64, ct.c_int64],
                                                     ct.c_void_p)
        self._checkValidMetaid_func = Util.load_func(libsemsim, "Editor_checkValidMetaid", [ct.c_int64, ct.c_char_p],
                                                     ct.c_void_p)
        self._toRDF_func = Util.load_func(libsemsim, "Editor_toRDF", [ct.c_int64], ct.c_void_p)

        self._new_singular_annotation = Util.load_func(libsemsim, "new_singular_annotation", [ct.c_int64], ct.c_int64)
        self._new_physical_entity = Util.load_func(libsemsim, "new_physical_entity", [ct.c_int64], ct.c_int64)
        self._new_physical_process = Util.load_func(libsemsim, "new_physical_process", [ct.c_int64], ct.c_int64)
        self._new_physical_force = Util.load_func(libsemsim, "new_physical_force", [ct.c_int64], ct.c_int64)

    def add_namespace(self, namespace: str, prefix: str) -> None:
        self._addNamespace_func(self.editor_ptr, namespace, str)

    def add_singular_annotation(self, singular_annotation: SingularAnnotation) -> None:
        self._addSingleAnnotation_func(self.editor_ptr, singular_annotation.get_ptr())

    def add_physical_entity(self, physical_entity: PhysicalEntity) -> None:
        self._addPhysicalEntity_func(self.editor_ptr, physical_entity.get_ptr())

    def add_physical_process(self, physical_process: PhysicalProcess) -> None:
        self._addPhysicalProcess_func(self.editor_ptr, physical_process.get_ptr())

    def add_physical_force(self, physical_force: PhysicalForce) -> None:
        self._addPhysicalForce_func(self.editor_ptr, physical_force.get_ptr())

    def check_valid_metaid(self, id: str) -> None:
        self._checkValidMetaid_func(self.editor_ptr, id)

    def to_rdf(self) -> None:
        self._toRDF_func(self.editor_ptr)

    def new_singular_annotation(self) -> SingularAnnotation:
        return SingularAnnotation(self._new_singular_annotation(self.editor_ptr))

    def new_physical_entity(self) -> PhysicalEntity:
        return PhysicalEntity(self._new_physical_entity(self.editor_ptr))

    def new_physical_process(self) -> PhysicalProcess:
        return PhysicalProcess(self._new_physical_process(self.editor_ptr))

    def new_physical_force(self) -> PhysicalForce:
        return PhysicalForce(self._new_physical_force(self.editor_ptr))


class SingularAnnotation:

    def __init__(self, singular_annotation_ptr):
        self._singular_annotation_ptr = singular_annotation_ptr

        self._setAbout = Util.load_func(libsemsim, "SingularAnnotation_setAbout", [ct.c_int64, ct.c_char_p], ct.c_int64)
        self._setPredicate = Util.load_func(libsemsim, "SingularAnnotation_setPredicate",
                                            [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_int64)
        self._setPredicateNew = Util.load_func(libsemsim, "SingularAnnotation_setPredicateNew",
                                               [ct.c_int64, ct.c_char_p, ct.c_char_p, ct.c_char_p], ct.c_int64)
        self._setResourceLiteral = Util.load_func(libsemsim, "SingularAnnotation_setResourceLiteral",
                                                  [ct.c_int64, ct.c_char_p], ct.c_int64)
        self._setResourceUri = Util.load_func(libsemsim, "SingularAnnotation_setResourceUri", [ct.c_int64, ct.c_char_p],
                                              ct.c_int64)
        self._setResourceBlank = Util.load_func(libsemsim, "SingularAnnotation_setResourceBlank",
                                                [ct.c_int64, ct.c_char_p], ct.c_int64)
        self._getAbout = Util.load_func(libsemsim, "SingularAnnotation_getAbout", [ct.c_int64], ct.c_char_p)
        self._str_func = Util.load_func(libsemsim, "SingularAnnotation_str", [ct.c_int64, ct.c_char_p, ct.c_char_p],
                                        ct.c_char_p)
        self._getPredicate = Util.load_func(libsemsim, "SingularAnnotation_getPredicate", [ct.c_int64], ct.c_char_p)
        self._getResource = Util.load_func(libsemsim, "SingularAnnotation_getResource", [ct.c_int64], ct.c_char_p)

    def get_ptr(self):
        return self._singular_annotation_ptr

    def set_about(self, about: str) -> SingularAnnotation:
        self._setAbout(self._singular_annotation_ptr, about.encode())
        return self

    def set_predicate(self, namespace: str, term: str) -> SingularAnnotation:
        self._setPredicate(self._singular_annotation_ptr, namespace.encode(), term.encode())
        return self

    def set_predicate_new(self, namespace: str, term: str, prefix: str) -> SingularAnnotation:
        self._setPredicateNew(self._singular_annotation_ptr, namespace.encode(), term.encode(), prefix.encode())
        return self

    def set_resource_literal(self, literal: str) -> SingularAnnotation:
        self._setResourceLiteral(self._singular_annotation_ptr, literal.encode())
        return self

    def set_resource_uri(self, uri: str) -> SingularAnnotation:
        self._setResourceUri(self._singular_annotation_ptr, uri.encode())
        return self

    def set_resource_blank(self, blank_id: str) -> SingularAnnotation:
        self._setResourceBlank(self._singular_annotation_ptr, blank_id.encode())
        return self

    def get_about(self) -> str:
        return self._getAbout(self._singular_annotation_ptr)

    def __str__(self):
        return self.to_string("rdfxml-abbrev", "./Annotation.rdf").decode()

    def to_string(self, format: str, base_uri: str) -> str:
        return self._str_func(self._singular_annotation_ptr, format.encode(), base_uri.encode())

    def get_predicate(self) -> str:
        return self._getPredicate(self._singular_annotation_ptr)

    def get_resource(self) -> str:
        return self._getResource(self._singular_annotation_ptr)


class PhysicalEntity:

    def __init__(self, physical_entity_ptr):
        self._physical_entity_ptr = physical_entity_ptr

        self._setAbout = Util.load_func(libsemsim, "PhysicalEntity_setAbout", [ct.c_int64, ct.c_char_p], ct.c_void_p)
        self._setPhysicalProperty = Util.load_func(libsemsim, "PhysicalEntity_setPhysicalProperty",
                                                   [ct.c_int64, ct.c_char_p], ct.c_void_p)
        self._setIdentity = Util.load_func(libsemsim, "PhysicalEntity_setIdentity", [ct.c_int64, ct.c_char_p],
                                           ct.c_void_p)
        self._addLocation = Util.load_func(libsemsim, "PhysicalEntity_addLocation", [ct.c_int64, ct.c_char_p],
                                           ct.c_void_p)
        self._getAbout = Util.load_func(libsemsim, "PhysicalEntity_getAbout", [ct.c_int64], ct.c_char_p)
        self._getPhysicalProperty = Util.load_func(libsemsim, "PhysicalEntity_getPhysicalProperty", [ct.c_int64],
                                                   ct.c_char_p)
        self._getIdentity = Util.load_func(libsemsim, "PhysicalEntity_getIdentity", [ct.c_int64], ct.c_char_p)
        self._getNumLocations = Util.load_func(libsemsim, "PhysicalEntity_getNumLocations", [ct.c_int64], ct.c_int)
        self._getLocations = Util.load_func(libsemsim, "PhysicalEntity_getLocations", [ct.c_int64], ct.c_void_p)
        self._str_func = Util.load_func(libsemsim, "PhysicalEntity_str", [ct.c_int64, ct.c_char_p, ct.c_char_p],
                                        ct.c_char_p)

    def get_ptr(self) -> ct.c_int64:
        return self._physical_entity_ptr

    def set_about(self, about: str) -> PhysicalEntity:
        self._setAbout(self._physical_entity_ptr, about.encode())
        return self

    def set_physical_property(self, property: str) -> PhysicalEntity:
        self._setPhysicalProperty(self.get_ptr(), property.encode())
        return self

    def set_identity(self, identity: str) -> PhysicalEntity:
        self._setIdentity(self.get_ptr(), identity.encode())
        return self

    def add_location(self, location: str) -> PhysicalEntity:
        self._addLocation(self.get_ptr(), location.encode())
        return self

    def get_about(self) -> str:
        return self._getAbout(self.get_ptr())

    def get_physical_property(self) -> str:
        return self._getPhysicalProperty(self.get_ptr())

    def get_identity(self) -> str:
        return self._getIdentity(self.get_ptr())

    def get_num_locations(self) -> int:
        return self._getNumLocations(self.get_ptr())

    def get_locations(self) -> List[str]:
        return self._getLocations(self.get_ptr(), )

    def to_string(self, format: str, base_uri: str) -> str:
        return self._str_func(self.get_ptr(), format.encode(), base_uri.encode()).decode()

    def __str__(self):
        return self.to_string("rdfxml-abbrev", "./Annotation.rdf")


class PhysicalProcess:

    def __init__(self, physical_process_ptr):
        self._physical_process_ptr = physical_process_ptr

        self._setAbout = Util.load_func(libsemsim, "PhysicalProcess_setAbout", [ct.c_int64, ct.c_char_p], ct.c_void_p)
        self._setPhysicalProperty = Util.load_func(libsemsim, "PhysicalProcess_setPhysicalProperty",
                                                   [ct.c_int64, ct.c_char_p], ct.c_void_p)
        self._addSource = Util.load_func(libsemsim, "PhysicalProcess_addSource",
                                         [ct.c_int64, ct.c_char_p, ct.c_float, ct.c_char_p], ct.c_void_p)
        self._addSink = Util.load_func(libsemsim, "PhysicalProcess_addSink",
                                       [ct.c_int64, ct.c_char_p, ct.c_float, ct.c_char_p], ct.c_void_p)
        self._addMediator = Util.load_func(libsemsim, "PhysicalProcess_addMediator",
                                           [ct.c_int64, ct.c_char_p, ct.c_float, ct.c_char_p], ct.c_void_p)
        self._str_func = Util.load_func(libsemsim, "PhysicalProcess_str",
                                        [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_char_p)
        self._getAbout = Util.load_func(libsemsim, "PhysicalProcess_getAbout", [ct.c_int64], ct.c_char_p)
        self._getPhysicalProperty = Util.load_func(libsemsim, "PhysicalProcess_getPhysicalProperty", [ct.c_int64],
                                                   ct.c_char_p)

    def get_ptr(self):
        return self._physical_process_ptr

    def set_about(self, about: str) -> PhysicalProcess:
        self._setAbout(self._physical_process_ptr, about.encode())
        return self

    def set_physical_property(self, property: str) -> PhysicalProcess:
        self._setPhysicalProperty(self._physical_process_ptr, property.encode())
        return self

    def add_source(self, source_id: str, multiplier: float, physical_entity_reference: str) -> PhysicalProcess:
        self._addSource(self._physical_process_ptr, source_id.encode(), multiplier, physical_entity_reference.encode())
        return self

    def add_sink(self, sink_id: str, multiplier: float, physical_entity_reference: str) -> PhysicalProcess:
        self._addSink(self._physical_process_ptr, sink_id.encode(), multiplier, physical_entity_reference.encode())
        return self

    def add_mediator(self, mediator_id: str, multiplier: float, physical_entity_reference: str) -> PhysicalProcess:
        self._addMediator(self._physical_process_ptr, mediator_id.encode(), multiplier,
                          physical_entity_reference.encode())
        return self

    def to_string(self, format: str, base_uri: str):
        return self._str_func(self._physical_process_ptr, format.encode(), base_uri.encode()).decode()

    def __str__(self):
        return self.to_string("rdfxml-abbrev", "./Annotation.rdf")

    def get_about(self) -> str:
        return self._getAbout(self._physical_process_ptr)

    def get_physical_property(self):
        return self._getPhysicalProperty(self._physical_process_ptr)


class PhysicalForce:

    def __init__(self, physical_force_ptr):
        self._physical_force_ptr = physical_force_ptr

        self._setAbout = Util.load_func(libsemsim, "PhysicalForce_setAbout", [ct.c_int64, ct.c_char_p], ct.c_void_p)
        self._setPhysicalProperty = Util.load_func(libsemsim, "PhysicalForce_setPhysicalProperty",
                                                   [ct.c_int64, ct.c_char_p], ct.c_void_p)
        self._addSource = Util.load_func(libsemsim, "PhysicalForce_addSource",
                                         [ct.c_int64, ct.c_char_p, ct.c_float, ct.c_char_p], ct.c_void_p)
        self._addSink = Util.load_func(libsemsim, "PhysicalForce_addSink",
                                       [ct.c_int64, ct.c_char_p, ct.c_float, ct.c_char_p], ct.c_void_p)
        self._str_func = Util.load_func(libsemsim, "PhysicalForce_str",
                                        [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_char_p)
        self._getAbout = Util.load_func(libsemsim, "PhysicalForce_getAbout", [ct.c_int64], ct.c_char_p)
        self._getPhysicalProperty = Util.load_func(libsemsim, "PhysicalForce_getPhysicalProperty", [ct.c_int64],
                                                   ct.c_char_p)

    def get_ptr(self):
        return self._physical_force_ptr

    def set_about(self, about: str) -> PhysicalForce:
        self._setAbout(self._physical_force_ptr, about.encode())
        return self

    def set_physical_property(self, property: str) -> PhysicalForce:
        self._setPhysicalProperty(self._physical_force_ptr, property.encode())
        return self

    def add_source(self, source_id: str, multiplier: float, physical_entity_reference: str) -> PhysicalForce:
        self._addSource(self._physical_force_ptr, source_id.encode(), multiplier, physical_entity_reference.encode())
        return self

    def add_sink(self, sink_id: str, multiplier: float, physical_entity_reference: str) -> PhysicalForce:
        self._addSink(self._physical_force_ptr, sink_id.encode(), multiplier, physical_entity_reference.encode())
        return self

    def to_string(self, format: str, base_uri: str):
        return self._str_func(self._physical_force_ptr, format.encode(), base_uri.encode()).decode()

    def __str__(self):
        return self.to_string("rdfxml-abbrev", "./Annotation.rdf")

    def get_about(self) -> str:
        return self._getAbout(self._physical_force_ptr)

    def get_physical_property(self):
        return self._getPhysicalProperty(self._physical_force_ptr)
