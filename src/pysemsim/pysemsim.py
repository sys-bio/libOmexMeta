from __future__ import annotations

import ctypes as ct
import os
from typing import List

from .pysemsim_api import PysemsimAPI


class _XmlAssistantType:
    """
    Class used internally for directing the underlying c++
    code to work with cellml or sbml.
    """

    def __init__(self, xml_type):
        type = None
        if xml_type == "sbml":
            type = 0
        elif xml_type == "cellml":
            type = 1
        else:
            raise ValueError("\"xml_type\" arg must be either \"sbml\" or \"cellml\"")

    def getType(self):
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
        results_crlf = PysemsimAPI.rdf_query_results_as_str(
            self._obj, query_str.encode(), results_format.encode()).decode("utf-8")
        results_lf = PysemsimAPI.crlf_to_lr(results_crlf)
        return results_lf

    def to_editor(self, xml: str, xmltype: str) -> Editor:
        return Editor(PysemsimAPI.rdf_to_editor(self._obj, xml.encode(), _XmlAssistantType(xml_type=xmltype).getType()))


class Editor:

    def __init__(self, editor_ptr):
        self._editor_ptr = editor_ptr

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


class SingularAnnotation:

    def __init__(self, singular_annotation_ptr):
        self._singular_annotation_ptr = singular_annotation_ptr

    def get_ptr(self):
        return self._singular_annotation_ptr

    def set_about(self, about: str) -> SingularAnnotation:
        PysemsimAPI.singular_annotation_set_about(self._singular_annotation_ptr, about.encode())
        return self

    def set_predicate(self, namespace: str, term: str) -> SingularAnnotation:
        PysemsimAPI.singular_annotation_set_predicate(self._singular_annotation_ptr, namespace.encode(), term.encode())
        return self

    def set_predicate_uri(self, namespace: str, uri: str) -> SingularAnnotation:
        PysemsimAPI.singular_annotation_set_predicate_uri(self._singular_annotation_ptr, uri.encode())
        return self

    def set_resource_literal(self, literal: str) -> SingularAnnotation:
        PysemsimAPI.singular_annotation_set_resource_literal(self._singular_annotation_ptr, literal.encode())
        return self

    def set_resource_uri(self, uri: str) -> SingularAnnotation:
        PysemsimAPI.singular_annotation_set_resource_uri(self._singular_annotation_ptr, uri.encode())
        return self

    def set_resource_blank(self, blank_id: str) -> SingularAnnotation:
        PysemsimAPI.singular_annotation_set_resource_blank(self._singular_annotation_ptr, blank_id.encode())
        return self

    def get_about(self) -> str:
        return PysemsimAPI.get_and_free_c_str(PysemsimAPI.singular_annotation_get_about(self._singular_annotation_ptr))

    def __str__(self):
        return self.to_string("rdfxml-abbrev", "./Annotation.rdf")

    def to_string(self, format: str, base_uri: str) -> str:
        return PysemsimAPI.get_and_free_c_str(
            PysemsimAPI.singular_annotation_str(self._singular_annotation_ptr, format.encode(), base_uri.encode()))

    def get_predicate(self) -> str:
        return PysemsimAPI.get_and_free_c_str(
            PysemsimAPI.singular_annotation_get_predicate(self._singular_annotation_ptr))

    def get_resource(self) -> str:
        return PysemsimAPI.get_and_free_c_str(
            PysemsimAPI.singular_annotation_get_resource(self._singular_annotation_ptr))

    def delete(self):
        PysemsimAPI.singular_annotation_delete(self._singular_annotation_ptr)


class PhysicalEntity:

    def __init__(self, physical_entity_ptr):
        self._physical_entity_ptr = physical_entity_ptr

    def get_ptr(self) -> ct.c_int64:
        return self._physical_entity_ptr

    def set_about(self, about: str) -> PhysicalEntity:
        PysemsimAPI.physical_entity_set_about(self._physical_entity_ptr, about.encode())
        return self

    def set_physical_property(self, property: str) -> PhysicalEntity:
        PysemsimAPI.physical_entity_set_physical_property(self.get_ptr(), property.encode())
        return self

    def set_identity(self, identity: str) -> PhysicalEntity:
        PysemsimAPI.physical_entity_set_identity(self.get_ptr(), identity.encode())
        return self

    def add_location(self, location: str) -> PhysicalEntity:
        PysemsimAPI.physical_entity_add_location(self.get_ptr(), location.encode())
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
        PysemsimAPI.physical_entity_delete(self._physical_entity_ptr)


class PhysicalProcess:

    def __init__(self, physical_process_ptr):
        self._physical_process_ptr = physical_process_ptr

    def get_ptr(self):
        return self._physical_process_ptr

    def set_about(self, about: str) -> PhysicalProcess:
        PysemsimAPI.physical_process_set_about(self._physical_process_ptr, about.encode())
        return self

    def set_physical_property(self, property: str) -> PhysicalProcess:
        PysemsimAPI.physical_process_set_physical_property(self._physical_process_ptr, property.encode())
        return self

    def add_source(self, source_id: str, multiplier: float, physical_entity_reference: str) -> PhysicalProcess:
        PysemsimAPI.physical_process_add_source(self._physical_process_ptr, source_id.encode(), multiplier,
                              physical_entity_reference.encode())
        return self

    def add_sink(self, sink_id: str, multiplier: float, physical_entity_reference: str) -> PhysicalProcess:
        PysemsimAPI.physical_process_add_sink(self._physical_process_ptr, sink_id.encode(), multiplier,
                            physical_entity_reference.encode())
        return self

    def add_mediator(self, mediator_id: str, multiplier: float, physical_entity_reference: str) -> PhysicalProcess:
        PysemsimAPI.physical_process_add_mediator(self._physical_process_ptr, mediator_id.encode(), multiplier,
                                physical_entity_reference.encode())
        return self

    def to_string(self, format: str, base_uri: str):
        return PysemsimAPI.get_and_free_c_str(
            PysemsimAPI.physical_process_str(self._physical_process_ptr, format.encode(), base_uri.encode()))

    def __str__(self):
        return self.to_string("rdfxml-abbrev", "./Annotation.rdf")

    def get_about(self) -> str:
        return PysemsimAPI.get_and_free_c_str(self.PysemsimAPI.physical_process_get_about(self._physical_process_ptr))

    def get_physical_property(self):
        return PysemsimAPI.get_and_free_c_str(self.PysemsimAPI.physical_process_get_physical_property(self._physical_process_ptr))

    def delete(self):
        PysemsimAPI.physical_process_delete(self._physical_process_ptr)


class PhysicalForce:

    def __init__(self, physical_force_ptr):
        self._physical_force_ptr = physical_force_ptr

    def get_ptr(self):
        return self._physical_force_ptr

    def set_about(self, about: str) -> PhysicalForce:
        PysemsimAPI.physical_force_set_about(self._physical_force_ptr, about.encode())
        return self

    def set_physical_property(self, property: str) -> PhysicalForce:
        PysemsimAPI.physical_force_set_physical_property(self._physical_force_ptr, property.encode())
        return self

    def add_source(self, source_id: str, multiplier: float, physical_entity_reference: str) -> PhysicalForce:
        PysemsimAPI.physical_force_add_source(self._physical_force_ptr, source_id.encode(), multiplier,
                              physical_entity_reference.encode())
        return self

    def add_sink(self, sink_id: str, multiplier: float, physical_entity_reference: str) -> PhysicalForce:
        PysemsimAPI.physical_force_add_sink(self._physical_force_ptr, sink_id.encode(), multiplier, physical_entity_reference.encode())
        return self

    def to_string(self, format: str, base_uri: str):
        return PysemsimAPI.get_and_free_c_str(
            PysemsimAPI.physical_force_str(self._physical_force_ptr, format.encode(), base_uri.encode()))

    def __str__(self):
        return self.to_string("rdfxml-abbrev", "./Annotation.rdf")

    def get_about(self) -> str:
        return PysemsimAPI.get_and_free_c_str(PysemsimAPI.physical_force_get_about(self._physical_force_ptr))

    def get_physical_property(self):
        return PysemsimAPI.get_and_free_c_str(PysemsimAPI.physical_force_get_physical_property(self._physical_force_ptr))

    def delete(self):
        PysemsimAPI.physical_force_delete(self._physical_force_ptr)
