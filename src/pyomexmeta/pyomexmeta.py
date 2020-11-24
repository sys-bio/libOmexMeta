from __future__ import annotations

import ctypes as ct
import os
from contextlib import contextmanager
from typing import List
from sys import executable as _python_interpretor

try:
    # for use from outside the package, as a python package
    from .pyomexmeta_api import PyOmexMetaAPI, eUriType, eXmlType
except ImportError:
    try:  # for internal use
        from pyomexmeta_api import PyOmexMetaAPI, eUriType, eXmlType
    except ImportError:
        # for internal use
        from . import pyomexmeta_api, eUriType, eXmlType

_pyom = PyOmexMetaAPI()


class RDF:

    def __init__(self, storage_type: str = "memory", storage_name: str = "libOmexMetaStore",
                 storage_options: str = None, model_options: str = None, rdf_ptr: ct.c_int64 = None):
        # when pointer argument not given by user, create new instance of RDF
        # argument is only given manually when static methods are used and
        # this is hidden from users.
        if not rdf_ptr:
            self._obj = _pyom.rdf_new(
                storage_type.encode(), storage_name.encode(),
                None if storage_options is None else storage_options.encode(),
                None if model_options is None else model_options.encode(),
            )

        else:
            self._obj = rdf_ptr

    def __len__(self):
        """Returns the number of individual Triples stored in the rdf model"""
        return _pyom.rdf_size(self._obj)

    def __str__(self):
        """Defaults to rdfxml-abbrev syntax"""
        return self.to_string("turtle")

    def __del__(self):
        """deletes the RDF instance"""
        self.delete()

    def _set_rdf_ptr(self, ptr: ct.c_int64):
        """
        Change the RDF pointer to ptr
        Args:
            ptr: a pointer to the C generated RDF object.

        Returns:

        """
        # first remove the existing pointer
        self.delete()
        # then do the switch
        self._obj = ptr

    @staticmethod
    def from_string(rdf_string: str, format: str = "guess", base_uri: str = "Annotations.rdf",
                    storage_type: str = "hashes", storage_name: str = "semsim_storage", storage_options: str = None,
                    model_options: str = None) -> RDF:
        """read rdf from a string"""
        rdf_ptr = _pyom.rdf_from_string(
            rdf_string.encode(), format.encode(), base_uri.encode(),
            storage_type.encode(), storage_name.encode(),
            None if not storage_options else storage_options.encode(),
            None if not storage_options else model_options.encode()
        )
        rdf = RDF()
        rdf._set_rdf_ptr(rdf_ptr)
        return rdf

    def add_from_string(self, rdf_string: str, format: str = "guess", base_uri: str = "Annotations.rdf") -> None:
        _pyom.rdf_add_from_string(self._obj, rdf_string.encode(), format.encode(), base_uri.encode())

    @staticmethod
    def from_uri(uri_string: str, format: str, storage_type: str = "hashes", storage_name: str = "semsim_storage",
                 storage_options: str = None,
                 model_options: str = None) -> RDF:
        rdf_ptr = _pyom.rdf_from_uri(
            uri_string.encode(), format.encode(),
            storage_type.encode(), storage_name.encode(),
            None if not storage_options else storage_options.encode(),
            None if not model_options else model_options.encode()
        )
        rdf = RDF()
        rdf._set_rdf_ptr(rdf_ptr)
        return rdf

    def add_from_uri(self, uri_string: str, format: str) -> None:
        _pyom.rdf_add_from_uri(self._obj, uri_string.encode(), format.encode())

    @staticmethod
    def from_file(filename: str, format: str, storage_type: str = "hashes", storage_name: str = "semsim_storage",
                  storage_options: str = None, model_options: str = None) -> RDF:
        rdf_ptr = _pyom.rdf_from_file(
            filename.encode(), format.encode(),
            storage_type.encode(), storage_name.encode(),
            None if not storage_options else storage_options.encode(),
            None if not storage_options else model_options.encode()
        )
        rdf = RDF()
        rdf._set_rdf_ptr(rdf_ptr)
        return rdf

    @staticmethod
    def equals_rdf_vs_rdf(first_rdf: RDF, second_rdf: RDF, format: str = "turtle") -> bool:
        return _pyom.rdf_equals_rdf_vs_rdf(first_rdf._obj, second_rdf._obj, format.encode())

    @staticmethod
    def equals_rdf_vs_string(rdf: RDF, string: str, format: str = "turtle") -> bool:
        return _pyom.rdf_equals_rdf_vs_string(rdf._obj, string.encode(), format.encode())

    @staticmethod
    def equals_string_vs_string(first_string: str, second_string: str, first_format: str = "turtle",
                                second_format: str = "turtle") -> bool:
        return _pyom.rdf_equals_string_vs_string(first_string.encode(), second_string.encode(), first_format,
                                                 second_format.encode())

    def __eq__(self, other: RDF):
        return self.equals_rdf_vs_rdf(self, other)

    def add_from_file(self, filename: str, format: str) -> None:
        _pyom.rdf_add_from_file(self._obj, filename.encode(), format.encode())

    def delete(self) -> None:
        """destructor. Delete the dynamically allocated rdf object"""
        _pyom.rdf_delete(self._obj)

    def to_string(self, format: str = "turtle") -> str:
        str_ptr = _pyom.rdf_to_string(self._obj, format.encode())
        thestring = _pyom.get_and_free_c_str(str_ptr)
        return thestring

    def to_file(self, format: str, filename: str) -> None:
        _pyom.rdf_to_file(self._obj, format.encode(), filename.encode())

    def set_repository_uri(self, repository_uri: str) -> None:
        _pyom.rdf_set_repository_uri(self._obj, repository_uri.encode())

    def set_archive_uri(self, archive_url: str) -> None:
        _pyom.rdf_set_archive_uri(self._obj, archive_url.encode())

    def set_model_uri(self, model_uri: str) -> None:
        _pyom.rdf_set_model_uri(self._obj, model_uri.encode())

    def get_repository_uri(self) -> str:
        return _pyom.get_and_free_c_str(
            _pyom.rdf_get_repository_uri(self._obj)
        )

    def get_archive_uri(self) -> str:
        return _pyom.get_and_free_c_str(
            _pyom.rdf_get_archive_uri(self._obj)
        )

    def get_model_uri(self) -> str:
        return _pyom.get_and_free_c_str(
            _pyom.rdf_get_model_uri(self._obj)
        )

    def get_local_uri(self) -> str:
        return _pyom.get_and_free_c_str(
            _pyom.rdf_get_local_uri(self._obj)
        )

    def query(self, query_str: str, results_format: str) -> str:
        results_crlf = _pyom.get_and_free_c_str(
            _pyom.rdf_query_results_as_str(
                self._obj, query_str.encode(), results_format.encode())
        )
        results_lf = _pyom.crlf_to_lr(results_crlf)
        return results_lf

    def to_editor(self, xml: str, generate_new_metaids: bool = False, sbml_semantic_extraction: bool = True) -> Editor:
        return Editor(
            _pyom.rdf_to_editor(
                self._obj, xml.encode(),
                generate_new_metaids,
                sbml_semantic_extraction,
            )
        )

    def draw(self, filename: str, **kwargs):
        """
        render an graph of RDF and save to `filename`

        Args:
            filename: where to write. The extension determines the format. See
            https://graphviz.readthedocs.io/en/stable/index.html for more
            details about accepted formats.

        Returns:

        """
        try:
            import graphviz
        except ImportError:
            raise ImportError(f'"graphviz" not found. Install '
                              f'with "sudo apt install graphviz" and then '
                              f'"pip install graphviz". This may be an conda environment issue. Check that '
                              f'you are using the correct python interpretor. The interpreter being used '
                              f'now is \"{_python_interpretor}\"')
        dot = self.to_string("dot")
        src = graphviz.Source(dot, **kwargs)
        src.render(filename)
        print('RDF graph saved to "{}"'.format(filename))
        if not os.path.isfile(filename):
            raise ValueError("Output was not written to file \"{}\"".format(filename))


class Editor:

    def __init__(self, editor_ptr: ct.c_int64):
        self._obj = editor_ptr

    def __enter__(self):
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        self.delete()

    def add_namespace(self, namespace: str, prefix: str) -> None:
        _pyom.editor_add_namespace(self._obj, namespace, prefix)

    def add_singular_annotation(self, singular_annotation: SingularAnnotation) -> None:
        _pyom.editor_add_single_annotation(self._obj, singular_annotation.get_ptr())

    def add_physical_entity(self, physical_entity: PhysicalEntity) -> None:
        _pyom.editor_add_physical_entity(self._obj, physical_entity.get_ptr())

    def add_physical_process(self, physical_process: PhysicalProcess) -> None:
        _pyom.editor_add_physical_process(self._obj, physical_process.get_ptr())

    def add_energy_diff(self, energy_diff: EnergyDiff) -> None:
        _pyom.editor_add_energy_diff(self._obj, energy_diff.get_ptr())

    def add_personal_information(self, personal_information: PersonalInformation) -> None:
        _pyom.editor_add_personal_information(self._obj, personal_information.get_ptr())

    def add_physical_property(self, property: PhysicalProperty) -> None:
        _pyom.editor_add_physical_property(self._obj, property.get_ptr())

    def check_valid_metaid(self, id: str) -> None:
        _pyom.editor_check_valid_metaid(self._obj, id)

    def get_metaids(self) -> List[str]:
        num_ids = _pyom.editor_get_num_metaids(self._obj)
        return [_pyom.get_and_free_c_str(
            _pyom.editor_get_metaid(self._obj, id)
        ) for id in range(num_ids)]

    def remove_single_annotation(self, single_annotaiton_ptr: ct.c_int64) -> None:
        _pyom.editor_remove_single_annotation(self._obj, single_annotaiton_ptr)

    def remove_physical_entity(self, physical_entity_ptr: ct.c_int64) -> None:
        _pyom.editor_remove_physical_entity(self._obj, physical_entity_ptr)

    def remove_physical_process(self, physical_process_ptr: ct.c_int64) -> None:
        _pyom.editor_remove_physical_process(self._obj, physical_process_ptr)

    def remove_energy_diff(self, energy_diff_ptr: ct.c_int64) -> None:
        _pyom.editor_remove_energy_diff(self._obj, energy_diff_ptr)

    def remove_personal_information(self, personal_information_ptr: ct.c_int64) -> None:
        _pyom.editor_remove_personal_information(self._obj, personal_information_ptr)

    def get_xml(self) -> str:
        return _pyom.get_and_free_c_str(
            _pyom.editor_get_xml(self._obj)
        )

    @contextmanager
    def new_singular_annotation(self) -> SingularAnnotation:
        singular_annotation = SingularAnnotation(_pyom.editor_new_singular_annotation(self._obj))
        try:
            yield singular_annotation
        finally:
            self.add_singular_annotation(singular_annotation)

    @contextmanager
    def new_personal_information(self) -> SingularAnnotation:
        information = PersonalInformation(_pyom.editor_new_personal_information(self._obj))
        try:
            yield information
        finally:
            self.add_personal_information(information)

    @contextmanager
    def new_physical_entity(self) -> PhysicalEntity:
        physical_entity = PhysicalEntity(_pyom.editor_new_physical_entity(self._obj))
        try:
            yield physical_entity
        finally:
            self.add_physical_entity(physical_entity)

    @contextmanager
    def new_physical_process(self) -> PhysicalProcess:
        physical_process = PhysicalProcess(_pyom.editor_new_physical_process(self._obj))
        try:
            yield physical_process
        finally:
            self.add_physical_process(physical_process)

    @contextmanager
    def new_energy_diff(self) -> EnergyDiff:
        energy_diff = EnergyDiff(_pyom.editor_new_energy_diff(self._obj))
        try:
            yield energy_diff
        finally:
            self.add_energy_diff(energy_diff)

    def new_physical_property(self) -> PhysicalProperty:
        return PhysicalProperty(_pyom.editor_new_physical_property(self._obj))

    def delete(self):
        _pyom.editor_delete(self._obj)

    def add_creator(self, creator) -> Editor:
        return Editor(
            _pyom.editor_add_creator(self._obj, creator.encode())
        )

    def add_curator(self, curator) -> Editor:
        return Editor(
            _pyom.editor_add_curator(self._obj, curator.encode())
        )

    def add_taxon(self, taxon) -> Editor:
        return Editor(
            _pyom.editor_add_taxon(self._obj, taxon.encode())
        )

    def add_pubmed(self, pubmed) -> Editor:
        return Editor(
            _pyom.editor_add_pubmed(self._obj, pubmed.encode())
        )

    def add_description(self, description) -> Editor:
        return Editor(
            _pyom.editor_add_description(self._obj, description.encode())
        )

    def add_date_created(self, date_created) -> Editor:
        return Editor(
            _pyom.editor_add_date_created(self._obj, date_created.encode())
        )

    def add_parent_model(self, parent_model) -> Editor:
        return Editor(
            _pyom.editor_add_parent_model(self._obj, parent_model.encode())
        )


class SingularAnnotation:

    def __init__(self, singular_annotation_ptr: ct.c_int64):
        self._obj = singular_annotation_ptr

    def get_ptr(self) -> ct.c_int64:
        return self._obj

    def about(self, about: str) -> SingularAnnotation:
        self._obj = _pyom.singular_annotation_about(self._obj, about.encode())
        return self

    def set_predicate(self, namespace: str, term: str) -> SingularAnnotation:
        self._obj = _pyom.singular_annotation_set_predicate(self._obj, namespace.encode(), term.encode())
        return self

    def predicate(self, namespace: str, term: str) -> SingularAnnotation:
        self._obj = _pyom.singular_annotation_predicate(self._obj, namespace.encode(), term.encode())
        return self

    def set_predicate_from_uri(self, uri: str) -> SingularAnnotation:
        self._obj = _pyom.singular_annotation_set_predicate_from_uri(self._obj, uri.encode())
        return self

    def set_resource_literal(self, literal: str) -> SingularAnnotation:
        self._obj = _pyom.singular_annotation_set_resource_literal(self._obj, literal.encode())
        return self

    def set_resource_uri(self, uri: str) -> SingularAnnotation:
        self._obj = _pyom.singular_annotation_set_resource_uri(self._obj, uri.encode())
        return self

    def set_resource_blank(self, blank_id: str) -> SingularAnnotation:
        self._obj = _pyom.singular_annotation_set_resource_blank(self._obj, blank_id.encode())
        return self

    def predicate_from_uri(self, uri: str) -> SingularAnnotation:
        self._obj = _pyom.singular_annotation_predicate_from_uri(self._obj, uri.encode())
        return self

    def resource_literal(self, literal: str) -> SingularAnnotation:
        self._obj = _pyom.singular_annotation_resource_literal(self._obj, literal.encode())
        return self

    def resource_uri(self, uri: str) -> SingularAnnotation:
        self._obj = _pyom.singular_annotation_resource_uri(self._obj, uri.encode())
        return self

    def resource_blank(self, blank_id: str) -> SingularAnnotation:
        self._obj = _pyom.singular_annotation_resource_blank(self._obj, blank_id.encode())
        return self

    def get_about(self) -> str:
        return _pyom.get_and_free_c_str(_pyom.singular_annotation_get_about(self._obj))

    def __str__(self):
        return self.to_string("turtle")

    def to_string(self, format: str) -> str:
        return _pyom.get_and_free_c_str(
            _pyom.singular_annotation_str(self._obj, format.encode()))

    def get_predicate(self) -> str:
        return _pyom.get_and_free_c_str(
            _pyom.singular_annotation_get_predicate(self._obj))

    def get_resource(self) -> str:
        return _pyom.get_and_free_c_str(
            _pyom.singular_annotation_get_resource(self._obj))

    def delete(self) -> None:
        _pyom.singular_annotation_delete(self._obj)


class PhysicalProperty:

    def __init__(self, physical_property_ptr: ct.c_int64):
        self._obj = physical_property_ptr

    def get_ptr(self):
        return self._obj

    def get_about(self) -> str:
        return _pyom.get_and_free_c_str(
            _pyom.physical_property_get_about(self._obj)
        )

    def about(self, about: str, uri_type: eUriType) -> PhysicalProperty:
        _pyom.physical_property_about(self._obj, about.encode(), uri_type)
        return self

    def get_is_version_of_value(self) -> str:
        return _pyom.get_and_free_c_str(
            _pyom.physical_property_get_is_version_of_value(self._obj)
        )

    def is_property_of(self, is_property_of_value: str, uri_type: eUriType = eUriType.NONE) -> PhysicalProperty:
        _pyom.physical_property_is_property_of(self._obj, is_property_of_value.encode(), uri_type)
        return self

    def is_version_of(self, is_version_of_value: str) -> PhysicalProperty:
        _pyom.physical_property_is_version_of(self._obj, is_version_of_value.encode())
        return self

    def get_is_property_of_value(self) -> str:
        return _pyom.get_and_free_c_str(
            _pyom.physical_property_get_is_property_of_value(self._obj)
        )

    def delete(self) -> None:
        _pyom.physical_property_delete(self._obj)


class _PropertyBearer:
    """
    We only want to write this function once for all CompositeAnnotations
    """

    def __init__(self, name: str, obj: ct.c_int64):
        self._obj = obj
        self.name = name

    def has_property(self, property_about: str = None, about_uri_type: eUriType = None,
                     is_version_of: str = None, property: PhysicalProperty = None) -> _PropertyBearer:
        """
        Create a PhysicalProperty associated with a PhysicalEntity, EnergyDiff or PhysicalProcess.

        This method has 4 signatures which can be used in different circumstances.
        In the full signature the user provides all the information needed

            -  PhysicalEntity *PhysicalEntity_hasPropertyFull(
                    PhysicalEntity *physical_entity_ptr,
                    const char* property_about, eUriType about_uri_type,
                    const char* is_version_of
                ) ;
            -  PhysicalEntity *PhysicalEntity_hasProperty(
                    PhysicalEntity *physical_entity_ptr,
                    PhysicalProperty* property
                );
            -  PhysicalEntity *PhysicalEntity_hasPropertyisVersionOf(
                    PhysicalEntity *physical_entity_ptr, const char* isVersionOf
                ) ;
        """
        _valid = ["physical_entity", "physical_process", "energy_diff"]
        if self.name not in _valid:
            raise ValueError(f"name argument must be one of {_valid}")

        has_property = getattr(PyOmexMetaAPI, self.name + "_has_property")
        has_property_is_version_of = getattr(PyOmexMetaAPI, self.name + "_has_property_is_version_of")
        has_property_full = getattr(PyOmexMetaAPI, self.name + "_has_property_full")

        # When the user provides None of the arguments we error
        if (not property_about
                and not is_version_of
                and not about_uri_type
                and not property
        ):
            raise ValueError(f"No arguments given to \"{self.__class__.__name__}\" method \"has_property\"")

        # when the user provides the property argument in addition to any of the other arguments we error
        if (
                (property and property_about)
                or (property and about_uri_type)
                or (property and is_version_of)
        ):
            raise ValueError("When using the \"property\" argument you must not provide "
                             "values to any of the other arguments")

        # When the user provides the property argument and none of the others we use the addProperty signature
        if (
                (property and not property_about)
                or (property and not about_uri_type)
                or (property and not is_version_of)
        ):
            has_property(self._obj, property.get_ptr())
            return self

        # When the user provices all of the arguments we can use the "full" signature
        if (property_about
                and is_version_of
                and about_uri_type
        ):
            has_property_full(
                self._obj, property_about.encode(), about_uri_type, is_version_of.encode())
            return self

        # When the user only provides argument to is_version_of we use the  hasPropertyIsVersionOf version
        if (is_version_of and not property_about and not about_uri_type):

            has_property_is_version_of(self._obj, is_version_of.encode())
            return self

        # if user provides a single string, it is assumed to be the is_version_of string NOT the property_about
        if property_about and not is_version_of and not about_uri_type and not property:
            has_property_is_version_of(self._obj, property_about.encode())
            return self

        # if we get this far then the user has made an error
        raise ValueError(f'Argument combination to "{self.__class__.__name__}" is invalid')


class PhysicalEntity(_PropertyBearer):

    def __init__(self, physical_entity_ptr: ct.c_int64):
        self._obj = physical_entity_ptr
        super().__init__("physical_entity", self._obj)

    def get_ptr(self) -> ct.c_int64:
        return self._obj

    def identity(self, identity: str) -> PhysicalEntity:
        self._obj = _pyom.physical_entity_identity(self.get_ptr(), identity.encode())
        return self

    def get_identity(self) -> str:
        return _pyom.get_and_free_c_str(_pyom.physical_entity_get_identity(self.get_ptr()))

    def get_num_locations(self) -> int:
        return _pyom.physical_entity_get_num_locations(self.get_ptr())

    def get_locations(self) -> List[str]:
        return [_pyom.get_and_free_c_str(
            _pyom.physical_entity_get_location(self.get_ptr(), i)
        ) for i in range(self.get_num_locations())]

    def to_string(self, format: str, base_uri: str = "Annotations.rdf") -> str:
        return _pyom.get_and_free_c_str(
            _pyom.physical_entity_str(self.get_ptr(), format.encode(), base_uri.encode())
        )

    def __str__(self):
        return self.to_string("turtle")

    def delete(self) -> None:
        _pyom.physical_entity_delete(self._obj)

    def about(self, about: str, type: eUriType) -> PhysicalEntity:
        self._obj = _pyom.physical_entity_about(self.get_ptr(), about.encode(), type)
        return self

    def is_part_of(self, is_part_of: str) -> PhysicalEntity:
        self._obj = _pyom.physical_entity_is_part_of(self.get_ptr(), is_part_of.encode())
        return self

    def has_part(self, part: str) -> PhysicalEntity:
        self._obj = _pyom.physical_entity_has_part(self.get_ptr(), part.encode())
        return self


class PhysicalProcess(_PropertyBearer):

    def __init__(self, physical_process_ptr: ct.c_int64):
        self._obj = physical_process_ptr
        super().__init__("physical_process", self._obj)

    def get_ptr(self) -> ct.c_int64:
        return self._obj

    def add_source(self, physical_entity_reference: str, uri_type: eUriType, multiplier: float = 1.0) -> PhysicalProcess:
        self._obj = _pyom.physical_process_add_source(
            self._obj, physical_entity_reference.encode(), uri_type, multiplier
        )
        return self

    def add_sink(self, physical_entity_reference: str, uri_type: eUriType, multiplier: float = 1.0) -> PhysicalProcess:
        self._obj = _pyom.physical_process_add_sink(
            self._obj, physical_entity_reference.encode(), uri_type, multiplier
        )
        return self

    def add_mediator(self, physical_entity_reference: str, uri_type: eUriType) -> PhysicalProcess:
        self._obj = _pyom.physical_process_add_mediator(self._obj, physical_entity_reference.encode(), uri_type)
        return self

    def to_string(self, format: str, base_uri: str = "Annotations.rdf"):
        return _pyom.get_and_free_c_str(
            _pyom.physical_process_str(self._obj, format.encode(), base_uri.encode()))

    def __str__(self):
        return self.to_string("turtle")

    def delete(self) -> None:
        _pyom.physical_process_delete(self._obj)

    def about(self, about: str, uri_type: eUriType) -> PhysicalProcess:
        self._obj = _pyom.physical_process_about(self.get_ptr(), about.encode(), uri_type)
        return self

    def is_version_of(self, version: str, uri_type: eUriType = eUriType.IDENTIFIERS_URI) -> PhysicalProcess:
        self._obj = _pyom.physical_process_is_version_of(self.get_ptr(), version.encode(), uri_type)
        return self


class EnergyDiff(_PropertyBearer):

    def __init__(self, energy_diff_ptr: ct.c_int64):
        self._obj = energy_diff_ptr
        super().__init__("energy_diff", self._obj)

    def get_ptr(self) -> ct.c_int64:
        return self._obj

    def add_source(self, physical_entity_reference: str, uri_type: eUriType) -> EnergyDiff:
        self._obj = _pyom.energy_diff_add_source(
            self._obj, physical_entity_reference.encode(), uri_type
        )
        return self

    def add_sink(self, physical_entity_reference: str, uri_type: eUriType) -> EnergyDiff:
        self._obj = _pyom.energy_diff_add_sink(
            self._obj, physical_entity_reference.encode(), uri_type
        )
        return self

    def to_string(self, format: str, base_uri: str = "Annotations.rdf"):
        return _pyom.get_and_free_c_str(
            _pyom.energy_diff_str(self._obj, format.encode(), base_uri.encode()))

    def __str__(self):
        return self.to_string("turtle")

    def delete(self) -> None:
        _pyom.energy_diff_delete(self._obj)

    def about(self, about: str, uri_type: eUriType) -> EnergyDiff:
        self._obj = _pyom.energy_diff_about(self.get_ptr(), about.encode(), uri_type)
        return self


class PersonalInformation:

    def __init__(self, personal_information_ptr: ct.c_int64):
        self._obj = personal_information_ptr

    def get_ptr(self) -> ct.c_int64:
        return self._obj

    def to_string(self, format: str, base_uri: str = "Annotations.rdf"):
        return _pyom.get_and_free_c_str(
            _pyom.energy_diff_str(self._obj, format.encode(), base_uri.encode()))

    def get_local_uri(self) -> str:
        return _pyom.get_and_free_c_str(
            _pyom.personal_information_get_local_uri(self._obj)
        )

    def set_local_uri(self, local_uri: str) -> None:
        _pyom.personal_information_set_local_uri(self._obj, local_uri.encode())

    def add_creator(self, value: str) -> PersonalInformation:
        _pyom.personal_information_add_creator(self._obj, value.encode())
        return self

    def add_name(self, value: str) -> PersonalInformation:
        _pyom.personal_information_add_name(self._obj, value.encode())
        return self

    def add_mbox(self, value: str) -> PersonalInformation:
        _pyom.personal_information_add_mbox(self._obj, value.encode())
        return self

    def add_account_name(self, value: str) -> PersonalInformation:
        _pyom.personal_information_add_account_name(self._obj, value.encode())
        return self

    def add_account_service_homepage(self, value: str) -> PersonalInformation:
        _pyom.personal_information_add_account_service_homepage(self._obj, value.encode())
        return self

    def add_foaf_blank(self, value: str) -> PersonalInformation:
        _pyom.personal_information_add_foaf_blank(self._obj, value.encode())
        return self

    def add_foaf_uri(self, value: str) -> PersonalInformation:
        _pyom.personal_information_add_foaf_uri(self._obj, value.encode())
        return self

    def add_foaf_literal(self, value: str) -> PersonalInformation:
        _pyom.personal_information_add_foaf_literal(self._obj, value.encode())
        return self

    def get_metaid(self) -> str:
        return _pyom.get_and_free_c_str(
            _pyom.personal_information_get_metaid(self._obj)
        )

    def set_metaid(self, metaid: str) -> None:
        _pyom.personal_information_set_metaid(self._obj, metaid.encode())

    def get_model_uri(self) -> str:
        return _pyom.get_and_free_c_str(
            _pyom.personal_information_get_model_uri(self._obj)
        )

    def set_model_uri(self, model_uri: str) -> None:
        _pyom.personal_information_set_model_uri(self._obj, model_uri.encode())

    def delete(self):
        _pyom.personal_information_delete(self._obj)
