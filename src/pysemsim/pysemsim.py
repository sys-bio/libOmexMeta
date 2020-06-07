from __future__ import annotations
from contextlib import contextmanager

import ctypes as ct
import os
from typing import List

from .pysemsim_api import PysemsimAPI


def _xml_type_factory(xml_type: str):
    """
    Helper function used internally for directing the underlying c++
    code to work with cellml or sbml.
    """
    type = None
    if xml_type == "sbml":
        type = 0
    elif xml_type == "cellml":
        type = 1
    else:
        raise ValueError("\"xml_type\" arg must be either \"sbml\" or \"cellml\"")
    return type


class RDF:

    def __init__(self):
        self._obj = PysemsimAPI.rdf_new()

    @staticmethod
    def from_string(rdf_string: str, format: str = "guess") -> RDF:
        """read rdf from a string"""
        rdf = RDF()
        PysemsimAPI.rdf_from_string(rdf._obj, rdf_string.encode(), format.encode())
        return rdf

    def delete(self):
        """destructor. Delete the dynamically allocated rdf object"""
        PysemsimAPI.rdf_delete(self._obj)

    def __len__(self):
        """Returns the number of individual Triples stored in the rdf model"""
        return PysemsimAPI.rdf_size(self._obj)

    def __str__(self):
        return self.to_string("rdfxml-abbrev", base_uri="./Annotation.rdf")

    def to_string(self, format: str, base_uri: str) -> str:
        str_ptr = PysemsimAPI.rdf_to_string(self._obj, format.encode(), base_uri.encode())
        thestring = PysemsimAPI.get_and_free_c_str(str_ptr)
        return thestring

    def get_base_uri(self) -> str:
        return PysemsimAPI.get_and_free_c_str(PysemsimAPI.rdf_get_base_uri(self._obj))

    def set_base_uri(self, uri: str) -> None:
        if not os.path.isfile(uri):
            uri = os.path.join(os.path.realpath(os.getcwd()), uri)
        PysemsimAPI.rdf_set_base_uri(self._obj, uri.encode())

    def query(self, query_str: str, results_format: str) -> str:
        results_crlf = PysemsimAPI.get_and_free_c_str(
            PysemsimAPI.rdf_query_results_as_str(
                self._obj, query_str.encode(), results_format.encode())
        )
        results_lf = PysemsimAPI.crlf_to_lr(results_crlf)
        return results_lf

    def to_editor(self, xml: str, xmltype: str) -> Editor:
        return Editor(PysemsimAPI.rdf_to_editor(self._obj, xml.encode(),
                                                _xml_type_factory(xml_type=xmltype)))


class Editor:

    def __init__(self, editor_ptr):
        self._editor_ptr = editor_ptr

    def __enter__(self):
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        self.to_rdf()
        self.delete()

    # @contextmanager
    # def c(self):
    #     try:
    #         yield self
    #     finally:
    #         self.to_rdf()
    #         self.delete()

    def add_namespace(self, namespace: str, prefix: str) -> None:
        PysemsimAPI.editor_add_namespace(self._editor_ptr, namespace, prefix)

    def add_singular_annotation(self, singular_annotation: SingularAnnotation) -> None:
        PysemsimAPI.editor_add_single_annotation(self._editor_ptr, singular_annotation.get_ptr())

    def add_physical_entity(self, physical_entity: PhysicalEntity) -> None:
        PysemsimAPI.editor_add_physical_entity(self._editor_ptr, physical_entity.get_ptr())

    def add_physical_process(self, physical_process: PhysicalProcess) -> None:
        PysemsimAPI.editor_add_physical_process(self._editor_ptr, physical_process.get_ptr())

    def add_physical_force(self, physical_force: PhysicalForce) -> None:
        PysemsimAPI.editor_add_physical_force(self._editor_ptr, physical_force.get_ptr())

    def check_valid_metaid(self, id: str) -> None:
        PysemsimAPI.editor_check_valid_metaid(self._editor_ptr, id)

    def to_rdf(self) -> None:
        PysemsimAPI.editor_to_rdf(self._editor_ptr)

    def new_singular_annotation(self) -> SingularAnnotation:
        return SingularAnnotation(PysemsimAPI.editor_new_singular_annotation(self._editor_ptr))

    def new_physical_entity(self) -> PhysicalEntity:
        return PhysicalEntity(PysemsimAPI.editor_new_physical_entity(self._editor_ptr))

    def new_physical_process(self) -> PhysicalProcess:
        return PhysicalProcess(PysemsimAPI.editor_new_physical_process(self._editor_ptr))

    def new_physical_force(self) -> PhysicalForce:
        return PhysicalForce(PysemsimAPI.editor_new_physical_force(self._editor_ptr))

    def delete(self):
        PysemsimAPI.editor_delete(self._editor_ptr)

"""
guve sing ann ptr to editor so it doesnt need argument to commitbg ti edutir
give singylar ann a to editor method

"""
class SingularAnnotation:

    def __init__(self, singular_annotation_ptr):
        self._obj = singular_annotation_ptr

    # def __enter__(self):
    #     return self
    #
    # def __exit__(self, exc_type, exc_val, exc_tb):
    #     self.to_rdf()
    #     self.delete()

    def get_ptr(self):
        return self._obj

    def set_about(self, about: str) -> SingularAnnotation:
        self._obj = PysemsimAPI.singular_annotation_set_about(self._obj, about.encode())
        return self

    def set_predicate(self, namespace: str, term: str) -> SingularAnnotation:
        self._obj = PysemsimAPI.singular_annotation_set_predicate(self._obj, namespace.encode(), term.encode())
        return self

    def set_predicate_uri(self, namespace: str, uri: str) -> SingularAnnotation:
        self._obj = PysemsimAPI.singular_annotation_set_predicate_uri(self._obj, uri.encode())
        return self

    def set_resource_literal(self, literal: str) -> SingularAnnotation:
        self._obj = PysemsimAPI.singular_annotation_set_resource_literal(self._obj, literal.encode())
        return self

    def set_resource_uri(self, uri: str) -> SingularAnnotation:
        self._obj = PysemsimAPI.singular_annotation_set_resource_uri(self._obj, uri.encode())
        return self

    def set_resource_blank(self, blank_id: str) -> SingularAnnotation:
        self._obj = PysemsimAPI.singular_annotation_set_resource_blank(self._obj, blank_id.encode())
        return self

    def get_about(self) -> str:
        return PysemsimAPI.get_and_free_c_str(PysemsimAPI.singular_annotation_get_about(self._obj))

    def __str__(self):
        return self.to_string("rdfxml-abbrev", "./Annotation.rdf")

    def to_string(self, format: str, base_uri: str) -> str:
        return PysemsimAPI.get_and_free_c_str(
            PysemsimAPI.singular_annotation_str(self._obj, format.encode(), base_uri.encode()))

    def get_predicate(self) -> str:
        return PysemsimAPI.get_and_free_c_str(
            PysemsimAPI.singular_annotation_get_predicate(self._obj))

    def get_resource(self) -> str:
        return PysemsimAPI.get_and_free_c_str(
            PysemsimAPI.singular_annotation_get_resource(self._obj))

    def delete(self):
        PysemsimAPI.singular_annotation_delete(self._obj)


class PhysicalEntity:

    def __init__(self, physical_entity_ptr):
        self._obj = physical_entity_ptr

    def get_ptr(self) -> ct.c_int64:
        return self._obj

    def set_about(self, about: str) -> PhysicalEntity:
        self._obj = PysemsimAPI.physical_entity_set_about(self._obj, about.encode())
        return self

    def set_physical_property(self, property: str) -> PhysicalEntity:
        self._obj = PysemsimAPI.physical_entity_set_physical_property(self.get_ptr(), property.encode())
        return self

    def set_identity(self, identity: str) -> PhysicalEntity:
        self._obj = PysemsimAPI.physical_entity_set_identity(self.get_ptr(), identity.encode())
        return self

    def add_location(self, location: str) -> PhysicalEntity:
        self._obj = PysemsimAPI.physical_entity_add_location(self.get_ptr(), location.encode())
        return self

    def get_about(self) -> str:
        return PysemsimAPI.get_and_free_c_str(PysemsimAPI.physical_entity_get_about(self.get_ptr()))

    def get_physical_property(self) -> str:
        return PysemsimAPI.get_and_free_c_str(PysemsimAPI.physical_entity_get_physical_property(self.get_ptr()))

    def get_identity(self) -> str:
        return PysemsimAPI.get_and_free_c_str(PysemsimAPI.physical_entity_get_identity(self.get_ptr()))

    def get_num_locations(self) -> int:
        return PysemsimAPI.physical_entity_get_num_locations(self.get_ptr())

    def get_locations(self) -> List[str]:
        return [PysemsimAPI.get_and_free_c_str(
            PysemsimAPI.physical_entity_get_location(self.get_ptr(), i)
        ) for i in range(self.get_num_locations())]

    def to_string(self, format: str, base_uri: str) -> str:
        return PysemsimAPI.get_and_free_c_str(
            PysemsimAPI.physical_entity_str(self.get_ptr(), format.encode(), base_uri.encode())
        )

    def __str__(self):
        return self.to_string("rdfxml-abbrev", "./Annotation.rdf")

    def delete(self):
        PysemsimAPI.physical_entity_delete(self._obj)


class PhysicalProcess:

    def __init__(self, physical_process_ptr):
        self._obj = physical_process_ptr

    def get_ptr(self):
        return self._obj

    def set_about(self, about: str) -> PhysicalProcess:
        self._obj = PysemsimAPI.physical_process_set_about(self._obj, about.encode())
        return self

    def set_physical_property(self, property: str) -> PhysicalProcess:
        self._obj = PysemsimAPI.physical_process_set_physical_property(self._obj, property.encode())
        return self

    def add_source(self, source_id: str, multiplier: float, physical_entity_reference: str) -> PhysicalProcess:
        self._obj = PysemsimAPI.physical_process_add_source(self._obj, source_id.encode(), multiplier,
                                                            physical_entity_reference.encode())
        return self

    def add_sink(self, sink_id: str, multiplier: float, physical_entity_reference: str) -> PhysicalProcess:
        self._obj = PysemsimAPI.physical_process_add_sink(self._obj, sink_id.encode(), multiplier,
                                                          physical_entity_reference.encode())
        return self

    def add_mediator(self, mediator_id: str, multiplier: float, physical_entity_reference: str) -> PhysicalProcess:
        self._obj = PysemsimAPI.physical_process_add_mediator(self._obj, mediator_id.encode(), multiplier,
                                                              physical_entity_reference.encode())
        return self

    def to_string(self, format: str, base_uri: str):
        return PysemsimAPI.get_and_free_c_str(
            PysemsimAPI.physical_process_str(self._obj, format.encode(), base_uri.encode()))

    def __str__(self):
        return self.to_string("rdfxml-abbrev", "./Annotation.rdf")

    def get_about(self) -> str:
        return PysemsimAPI.get_and_free_c_str(self.PysemsimAPI.physical_process_get_about(self._obj))

    def get_physical_property(self):
        return PysemsimAPI.get_and_free_c_str(
            self.PysemsimAPI.physical_process_get_physical_property(self._obj))

    def delete(self):
        PysemsimAPI.physical_process_delete(self._obj)


class PhysicalForce:

    def __init__(self, physical_force_ptr):
        self._obj = physical_force_ptr

    def get_ptr(self):
        return self._obj

    def set_about(self, about: str) -> PhysicalForce:
        self._obj = PysemsimAPI.physical_force_set_about(self._obj, about.encode())
        return self

    def set_physical_property(self, property: str) -> PhysicalForce:
        self._obj = PysemsimAPI.physical_force_set_physical_property(self._obj, property.encode())
        return self

    def add_source(self, source_id: str, multiplier: float, physical_entity_reference: str) -> PhysicalForce:
        self._obj = PysemsimAPI.physical_force_add_source(self._obj, source_id.encode(), multiplier,
                                                          physical_entity_reference.encode())
        return self

    def add_sink(self, sink_id: str, multiplier: float, physical_entity_reference: str) -> PhysicalForce:
        self._obj = PysemsimAPI.physical_force_add_sink(self._obj, sink_id.encode(), multiplier,
                                                        physical_entity_reference.encode())
        return self

    def to_string(self, format: str, base_uri: str):
        return PysemsimAPI.get_and_free_c_str(
            PysemsimAPI.physical_force_str(self._obj, format.encode(), base_uri.encode()))

    def __str__(self):
        return self.to_string("rdfxml-abbrev", "./Annotation.rdf")

    def get_about(self) -> str:
        return PysemsimAPI.get_and_free_c_str(PysemsimAPI.physical_force_get_about(self._obj))

    def get_physical_property(self):
        return PysemsimAPI.get_and_free_c_str(
            PysemsimAPI.physical_force_get_physical_property(self._obj))

    def delete(self):
        PysemsimAPI.physical_force_delete(self._obj)
