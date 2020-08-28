from __future__ import annotations

import ctypes as ct
import os
import sys
from typing import List
from functools import wraps

if sys.platform == "win32":
    try:
        import win32api
    except ImportError:
        raise ImportError("win32api not found. Please run `pip install pywin32`")
    import win32con

_WORKING_DIRECTORY = os.path.dirname(os.path.realpath(__file__))


class Util:

    @staticmethod
    def load_lib() -> ct.CDLL:
        if sys.platform == "linux":
            lib_path = os.path.join(_WORKING_DIRECTORY, "libOmexMetaCAPI.so.1.1.9")
            try:
                lib = ct.CDLL(lib_path)
            except OSError as e:
                if str(e) == "libxml2.so.2: cannot open shared object file: No such file or directory":
                    raise FileNotFoundError("Dependency library libxml2.so was not found. Run "
                                            "\"$ sudo apt install -y libxml2 libxml2-dev\"")

                elif str(e) == "libxslt.so.1: cannot open shared object file: No such file or directory":
                    raise FileNotFoundError("Dependency library libxsl2.so was not found. Run "
                                            "\"$ sudo apt install -y libxslt1-dev\"")

                elif str(e) == "libpq.so.5: cannot open shared object file: No such file or directory":
                    raise FileNotFoundError("Dependency library libpq.so was not found. Run "
                                            "\"$ sudo apt install -y libpq-dev\"")

                elif "libc.so.6:" in str(e):
                    raise FileNotFoundError("Dependency library libstdc++.so.6 was not found. Run "
                                            "\"$ sudo apt install -y software-properties-common "
                                            "&& sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test "
                                            "&& apt-get update "
                                            "&& sudo apt install -y g++-10\"")
                else:
                    raise e

        elif sys.platform == "win32":
            # windows has to be difficult
            lib_path = os.path.join(_WORKING_DIRECTORY, "OmexMetaCAPI.dll")
            dll_handle = win32api.LoadLibraryEx(lib_path, 0, win32con.LOAD_WITH_ALTERED_SEARCH_PATH)
            lib = ct.WinDLL(lib_path, handle=dll_handle)
        else:
            raise ValueError("Currently only implemented for windows or linux systems. Platform is " + sys.platform)

        if not lib:
            raise ValueError("libomexmeta.so not found")
        return lib

    @staticmethod
    def load_func(funcname: str, argtypes: List, restype) -> ct.CDLL._FuncPtr:
        func = Util.load_lib().__getattr__(funcname)
        func.restype = restype
        func.argtypes = argtypes
        return func


libomexmeta = Util.load_lib()


class PyOmexMetaAPI:
    """
    todo: Explain why we use return int64 type for functions that return char*:

    Encourage developers to mainain the order of functions loaded here
    to be as close as possible as that in OmexMetaCApi.h as it facilitates development

    Explain decision to only set self uri's from RDF not editor.
    """

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
        """Helper method for converting line endings. Needed mostly for query. For developers"""
        return string.replace('\r\n', '\n')

    # void free_c_char_star(char *c);
    free_char_star = Util.load_func("free_c_char_star", [ct.c_char_p], None)

    #################################################################
    # RDF methods
    #

    # RDF *RDF_new(const char *storage_type = "memory", const char *storage_name = "semsim_store",
    #              const char *storage_options = nullptr, const char *model_options = nullptr);
    rdf_new = Util.load_func("RDF_new", [ct.c_char_p, ct.c_char_p, ct.c_char_p, ct.c_char_p], ct.c_void_p)

    # int RDF_size(RDF *rdf_ptr);
    rdf_size = Util.load_func("RDF_size", [ct.c_int64], ct.c_int64)

    # RDF *RDF_fromString(const char *str, const char *format, const char *baseuri = "./Annotations.rdf",
    #                         const char *storage_type = "memory", const char *storage_name = "semsim_store",
    #                         const char *storage_options = nullptr, const char *model_options = nullptr);
    rdf_from_string = Util.load_func("RDF_fromString",
                                     [ct.c_char_p, ct.c_char_p, ct.c_char_p,
                                      ct.c_char_p, ct.c_char_p, ct.c_void_p, ct.c_void_p], ct.c_int64)

    # void RDF_addFromString(RDF *rdf_ptr, const char *str, const char *format, const char *base_uri);
    rdf_add_from_string = Util.load_func("RDF_addFromString", [ct.c_int64, ct.c_char_p, ct.c_char_p, ct.c_char_p],
                                         ct.c_void_p)

    # RDF *RDF_fromUri(const char *uri_string, const char *format,
    #                  const char *storage_type = "memory", const char *storage_name = "semsim_store",
    #                  const char *storage_options = nullptr, const char *model_options = nullptr);
    rdf_from_uri = Util.load_func("RDF_fromUri",
                                  [ct.c_char_p, ct.c_char_p,
                                   ct.c_char_p, ct.c_char_p,
                                   ct.c_char_p, ct.c_char_p], ct.c_int64)

    # void RDF_addFromUri(RDF *rdf_ptr, const char *uri_string, const char *format);
    rdf_add_from_uri = Util.load_func("RDF_addFromUri", [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_void_p)

    # RDF *RDF_fromFile(const char *filename, const char *format, const char *storage_type = "memory",
    #                   const char *storage_name = "semsim_store",
    #                   const char *storage_options = nullptr, const char *model_options = nullptr);
    rdf_from_file = Util.load_func("RDF_fromFile", [ct.c_char_p, ct.c_char_p,
                                                    ct.c_char_p, ct.c_char_p,
                                                    ct.c_char_p, ct.c_char_p], ct.c_int64)

    # void RDF_addFromFile(RDF *rdf_ptr, const char *uri_string, const char *format);
    rdf_add_from_file = Util.load_func("RDF_addFromFile", [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_int64)

    # char *RDF_toString(RDF *rdf_ptr, const char *format, const char *base_uri);
    rdf_to_string = Util.load_func("RDF_toString", [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_int64)

    # void RDF_toFile(RDF *rdf_ptr, const char *format, const char *filename);
    rdf_to_file = Util.load_func("RDF_toFile", [ct.c_int64, ct.c_char_p, ct.c_char_p], None)

    # void RDF_delete(RDF *rdf_ptr);
    rdf_delete = Util.load_func("RDF_delete", [ct.c_int64], None)

    # char *RDF_query(RDF *rdf_ptr, const char *query_str, const char *results_format);
    rdf_query_results_as_str = Util.load_func("RDF_query", [ct.c_int64, ct.c_char_p, ct.c_char_p],
                                              ct.c_int64)

    # void RDF_setRepositoryUri(RDF *rdf_ptr, std::string repository_uri);
    rdf_set_repository_uri = Util.load_func("RDF_setRepositoryUri", [ct.c_int64, ct.c_char_p], None)

    # void RDF_setArchiveUri(RDF *rdf_ptr, std::string archive_uri);
    rdf_set_archive_uri = Util.load_func("RDF_setArchiveUri", [ct.c_int64, ct.c_char_p], None)

    # void RDF_setModelUri(RDF *rdf_ptr, std::string model_uri);
    rdf_set_model_uri = Util.load_func("RDF_setModelUri", [ct.c_int64, ct.c_char_p], None)

    # char* RDF_getRepositoryUri(RDF *rdf_ptr);
    rdf_get_repository_uri = Util.load_func("RDF_getRepositoryUri", [ct.c_int64], ct.c_int64)

    # char* RDF_getArchiveUri(RDF *rdf_ptr);
    rdf_get_archive_uri = Util.load_func("RDF_getArchiveUri", [ct.c_int64], ct.c_int64)

    #
    # char* RDF_getModelUri(RDF *rdf_ptr);
    rdf_get_model_uri = Util.load_func("RDF_getModelUri", [ct.c_int64], ct.c_int64)

    #
    # char* RDF_getLocalUri(RDF *rdf_ptr);
    rdf_get_local_uri = Util.load_func("RDF_getLocalUri", [ct.c_int64], ct.c_int64)

    # Editor *RDF_toEditor(RDF *rdf_ptr, const char *xml, bool generate_new_metaids) {
    rdf_to_editor = Util.load_func("RDF_toEditor", [ct.c_int64, ct.c_char_p, ct.c_bool], ct.c_int64)
    #################################################################
    # Editor methods
    #

    # void Editor_addNamespace(Editor *editor_ptr, const char *namespace_, const char *prefix);
    editor_add_namespace = Util.load_func("Editor_addNamespace", [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_void_p)

    # void Editor_addSingleAnnotation(Editor *editor_ptr, SingularAnnotation *singularAnnotation);
    editor_add_single_annotation = Util.load_func("Editor_addSingleAnnotation",
                                                  [ct.c_int64, ct.c_int64], ct.c_void_p)

    # void Editor_addPhysicalEntity(Editor *editor_ptr, PhysicalEntity *physicalEntity);
    editor_add_physical_entity = Util.load_func("Editor_addPhysicalEntity", [ct.c_int64, ct.c_int64],
                                                ct.c_void_p)

    # void Editor_addPhysicalProcess(Editor *editor_ptr, PhysicalProcess *physicalProcess);
    editor_add_physical_process = Util.load_func("Editor_addPhysicalProcess", [ct.c_int64, ct.c_int64],
                                                 ct.c_void_p)

    # void Editor_addPhysicalForce(Editor *editor_ptr, PhysicalForce *physicalForce);
    editor_add_physical_force = Util.load_func("Editor_addPhysicalForce", [ct.c_int64, ct.c_int64],
                                               ct.c_void_p)

    # void Editor_checkValidMetaid(Editor *editor_ptr, const char *id);
    editor_check_valid_metaid = Util.load_func("Editor_checkValidMetaid", [ct.c_int64, ct.c_char_p],
                                               ct.c_void_p)

    # void Editor_removeSingleAnnotation(Editor *editor_ptr, SingularAnnotation *singularAnnotation);
    editor_remove_single_annotation = Util.load_func("Editor_removeSingleAnnotation", [ct.c_int64], None)

    # void Editor_removePhysicalEntity(Editor *editor_ptr, PhysicalEntity *physicalEntity);
    editor_remove_physical_entity = Util.load_func("Editor_removePhysicalEntity", [ct.c_int64], None)

    # void Editor_removePhysicalProcess(Editor *editor_ptr, PhysicalProcess *physicalProcess);
    editor_remove_physical_process = Util.load_func("Editor_removePhysicalProcess", [ct.c_int64], None)

    # void Editor_removePhysicalForce(Editor *editor_ptr, PhysicalForce *physicalForce);
    editor_remove_physical_force = Util.load_func("Editor_removePhysicalForce", [ct.c_int64], None)

    # void Editor_removePersonalInformation(Editor *editor_ptr, PersonalInformation *information);
    editor_remove_personal_information = Util.load_func("Editor_removePersonalInformation", [ct.c_int64], None)

    # SEMSIM_API void Editor_addPersonalInformation(Editor *editor_ptr, PersonalInformation *personalInformation);
    editor_add_personal_information = Util.load_func("Editor_addPersonalInformation", [ct.c_int64, ct.c_int64], None)

    # char *Editor_getMetaId(Editor *editor_ptr, int index);
    editor_get_metaid = Util.load_func("Editor_getMetaId", [ct.c_int64, ct.c_int64], ct.c_int64)

    # int Editor_getNumMetaIds(Editor *editor_ptr);
    editor_get_num_metaids = Util.load_func("Editor_getNumMetaIds", [ct.c_int64], ct.c_int64)

    # char *Editor_getXml(Editor *editor_ptr);
    editor_get_xml = Util.load_func("Editor_getXml", [ct.c_int64], ct.c_int64)

    # SingularAnnotation *SingularAnnotation_new(Editor *editor_ptr);
    editor_new_singular_annotation = Util.load_func("SingularAnnotation_new", [ct.c_int64], ct.c_int64)

    # PhysicalEntity *PhysicalEntity_new(Editor *editor_ptr);
    editor_new_physical_entity = Util.load_func("PhysicalEntity_new", [ct.c_int64], ct.c_int64)

    # PhysicalProcess *PhysicalProcess_new(Editor *editor_ptr);
    editor_new_physical_process = Util.load_func("PhysicalProcess_new", [ct.c_int64], ct.c_int64)

    # PhysicalForce *PhysicalForce_new(Editor *editor_ptr);
    editor_new_physical_force = Util.load_func("PhysicalForce_new", [ct.c_int64], ct.c_int64)

    # void Editor_delete(Editor *editor_ptr);
    editor_delete = Util.load_func("Editor_delete", [ct.c_int64], None)

    # char*Editor_getArchiveUri(Editor *editor_ptr);
    editor_get_archive_uri = Util.load_func("Editor_getArchiveUri", [ct.c_int64], ct.c_int64)

    # char*Editor_getLocalUri(Editor *editor_ptr);
    editor_get_local_uri = Util.load_func("Editor_getLocalUri", [ct.c_int64], ct.c_int64)

    # char*Editor_getModelUri(Editor *editor_ptr);
    editor_get_model_uri = Util.load_func("Editor_getModelUri", [ct.c_int64], ct.c_int64)

    # char*Editor_getRepositoryUri(Editor *editor_ptr);
    editor_get_repository_uri = Util.load_func("Editor_getRepositoryUri", [ct.c_int64], ct.c_int64)

    # void Editor_addCreator(Editor *editor_ptr, std::string orcid_id);
    editor_add_creator = Util.load_func("Editor_addCreator", [ct.c_int64, ct.c_char_p], None)

    # void Editor_addCurator(Editor *editor_ptr, std::string orcid_id);
    editor_add_curator = Util.load_func("Editor_addCurator", [ct.c_int64, ct.c_char_p], None)

    # void Editor_addTaxon(Editor *editor_ptr, const char *taxon_id);
    editor_add_taxon = Util.load_func("Editor_addTaxon", [ct.c_int64, ct.c_char_p], None)

    # void Editor_addPubmed(Editor *editor_ptr, const char *pubmedid);
    editor_add_pubmed = Util.load_func("Editor_addPubmed", [ct.c_int64, ct.c_char_p], None)

    # void Editor_addDescription(Editor *editor_ptr, const char *date);
    editor_add_description = Util.load_func("Editor_addDescription", [ct.c_int64, ct.c_char_p], None)

    # void Editor_addDateCreated(Editor *editor_ptr, const char *date);
    editor_add_date_created = Util.load_func("Editor_addDateCreated", [ct.c_int64, ct.c_char_p], None)

    # void Editor_addParentModel(Editor *editor_ptr, const char *biomod_id);
    editor_add_parent_model = Util.load_func("Editor_addParentModel", [ct.c_int64, ct.c_char_p], None)

    #################################################################
    # SingularAnnotations methods
    #

    # SingularAnnotation *SingularAnnotation_setAbout(SingularAnnotation *singular_annotation, const char *about);
    singular_annotation_set_about = Util.load_func("SingularAnnotation_setAbout", [ct.c_int64, ct.c_char_p], ct.c_int64)

    # SingularAnnotation * SingularAnnotation_setPredicate(SingularAnnotation *singular_annotation, const char *namespace_,const char *term);
    singular_annotation_set_predicate = Util.load_func("SingularAnnotation_setPredicate",
                                                       [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_int64)

    # SingularAnnotation *SingularAnnotation_setPredicateFromUri(
    #         SingularAnnotation *singular_annotation, const char *uri);
    singular_annotation_set_predicate_from_uri = Util.load_func("SingularAnnotation_setPredicateFromUri",
                                                                [ct.c_int64, ct.c_char_p], ct.c_int64)

    # SingularAnnotation *SingularAnnotation_setResourceLiteral(
    #         SingularAnnotation *singular_annotation, const char *literal);
    singular_annotation_set_resource_literal = Util.load_func("SingularAnnotation_setResourceLiteral",
                                                              [ct.c_int64, ct.c_char_p], ct.c_int64)
    # SingularAnnotation *
    # SingularAnnotation_setResourceUri(SingularAnnotation *singular_annotation, const char *identifiers_uri);
    singular_annotation_set_resource_uri = Util.load_func("SingularAnnotation_setResourceUri",
                                                          [ct.c_int64, ct.c_char_p],
                                                          ct.c_int64)
    # SingularAnnotation *
    # SingularAnnotation_setResourceBlank(SingularAnnotation *singular_annotation, const char *blank_id);
    singular_annotation_set_resource_blank = Util.load_func("SingularAnnotation_setResourceBlank",
                                                            [ct.c_int64, ct.c_char_p], ct.c_int64)

    # char *SingularAnnotation_getAbout(SingularAnnotation *singular_annotation);
    singular_annotation_get_about = Util.load_func("SingularAnnotation_getAbout", [ct.c_int64], ct.c_int64)

    # char * SingularAnnotation_str(SingularAnnotation * singular_annotation, const char * format)
    singular_annotation_str = Util.load_func("SingularAnnotation_str", [ct.c_int64, ct.c_char_p], ct.c_int64)

    # char *SingularAnnotation_getPredicate(SingularAnnotation *singular_annotation);
    singular_annotation_get_predicate = Util.load_func("SingularAnnotation_getPredicate", [ct.c_int64], ct.c_int64)

    # char *SingularAnnotation_getResource(SingularAnnotation *singular_annotation);
    singular_annotation_get_resource = Util.load_func("SingularAnnotation_getResource", [ct.c_int64], ct.c_int64)

    # void SingularAnnotation_delete(SingularAnnotation *singularAnnotation);
    singular_annotation_delete = Util.load_func("SingularAnnotation_delete", [ct.c_int64], None)

    #################################################################
    # PhysicalEntity methods
    #

    # PhysicalEntity *PhysicalEntity_setPhysicalProperty(
    #      PhysicalEntity *physical_entity_ptr, const char *subject_metaid, const char *physical_property);
    physical_entity_set_physical_property = Util.load_func("PhysicalEntity_setPhysicalProperty",
                                                           [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_int64)
    # PhysicalEntity *PhysicalEntity_setIdentity(
    #         PhysicalEntity *physical_entity_ptr, const char *identity_resource);
    physical_entity_set_identity = Util.load_func("PhysicalEntity_setIdentity", [ct.c_int64, ct.c_char_p], ct.c_int64)

    # PhysicalEntity *PhysicalEntity_addLocation(
    #         PhysicalEntity *physical_entity_ptr, const char *location_resource);
    physical_entity_add_location = Util.load_func("PhysicalEntity_addLocation", [ct.c_int64, ct.c_char_p], ct.c_int64)

    # char *PhysicalEntity_getIdentity(PhysicalEntity *physical_entity_ptr);
    physical_entity_get_identity = Util.load_func("PhysicalEntity_getIdentity", [ct.c_int64], ct.c_int64)

    # int PhysicalEntity_getNumLocations(PhysicalEntity *physicalEntity);
    physical_entity_get_num_locations = Util.load_func("PhysicalEntity_getNumLocations", [ct.c_int64],
                                                       ct.c_int)

    # char *PhysicalEntity_getLocation(PhysicalEntity *physical_entity_ptr, int index);
    physical_entity_get_location = Util.load_func("PhysicalEntity_getLocation", [ct.c_int64, ct.c_int64], ct.c_int64)

    # char *PhysicalEntity_str(PhysicalEntity *physical_entity_ptr, const char *format, const char *base_uri);
    physical_entity_str = Util.load_func("PhysicalEntity_str", [ct.c_int64, ct.c_char_p, ct.c_char_p],
                                         ct.c_int64)
    # void PhysicalEntity_delete(PhysicalEntity *physical_entity_ptr);
    physical_entity_delete = Util.load_func("PhysicalEntity_delete", [ct.c_int64], None)

    # void PhysicalEntity_freeAll(PhysicalEntity *physical_entity_ptr);
    physical_entity_free_all = Util.load_func("PhysicalEntity_freeAll", [ct.c_int64], None)

    #################################################################
    # PhysicalProcess methods
    #

    # PhysicalProcess *PhysicalProcess_setPhysicalProperty(
    #         PhysicalProcess *physical_process, const char *subject_metaid, const char *physical_property);
    physical_process_set_physical_property = Util.load_func("PhysicalProcess_setPhysicalProperty",
                                                            [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_int64)

    # PhysicalProcess *PhysicalProcess_addSource(
    #         PhysicalProcess *physical_process, double multiplier,
    #         const char *physical_entity_reference);
    physical_process_add_source = Util.load_func("PhysicalProcess_addSource",
                                                 [ct.c_int64, ct.c_double, ct.c_char_p], ct.c_int64)

    # PhysicalProcess *PhysicalProcess_addSink(
    #         PhysicalProcess *physical_process, double multiplier,
    #         const char *physical_entity_reference);
    physical_process_add_sink = Util.load_func("PhysicalProcess_addSink",
                                               [ct.c_int64, ct.c_double, ct.c_char_p], ct.c_int64)

    # PhysicalProcess *PhysicalProcess_addMediator(
    #         PhysicalProcess *physical_process, double multiplier,
    #         const char *physical_entity_reference);
    physical_process_add_mediator = Util.load_func("PhysicalProcess_addMediator",
                                                   [ct.c_int64, ct.c_double, ct.c_char_p], ct.c_int64)

    # char *PhysicalProcess_str(PhysicalProcess *physical_process_ptr, const char *format, const char *base_uri);
    physical_process_str = Util.load_func("PhysicalProcess_str",
                                          [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_int64)

    # void PhysicalProcess_delete(PhysicalProcess *physicalProcess);
    physical_process_delete = Util.load_func("PhysicalProcess_delete", [ct.c_int64], None)

    # void PhysicalProcess_freeAll(PhysicalProcess *physicalProcess);
    physical_process_free_all = Util.load_func("PhysicalProcess_freeAll", [ct.c_int64], None)

    #################################################################
    # PhysicalForce Methods
    #

    # PhysicalForce *PhysicalForce_setPhysicalProperty(
    #         PhysicalForce *physical_force_ptr, const char *subject_metaid, const char *physical_property);
    physical_force_set_physical_property = Util.load_func("PhysicalForce_setPhysicalProperty",
                                                          [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_int64)

    # PhysicalForce *PhysicalForce_addSource(
    #         PhysicalForce *physical_force_ptr, double multiplier,
    #         const char *physical_entity_reference);
    physical_force_add_source = Util.load_func("PhysicalForce_addSource",
                                               [ct.c_int64, ct.c_double, ct.c_char_p], ct.c_int64)

    # PhysicalForce *PhysicalForce_addSink(
    #         PhysicalForce *physical_force_ptr, double multiplier,
    #         const char *physical_entity_reference);
    physical_force_add_sink = Util.load_func("PhysicalForce_addSink",
                                             [ct.c_int64, ct.c_double, ct.c_char_p], ct.c_int64)

    # char *PhysicalForce_str(PhysicalForce *physical_force_ptr, const char *format, const char *base_uri);
    physical_force_str = Util.load_func("PhysicalForce_str",
                                        [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_int64)

    # void PhysicalForce_delete(PhysicalForce *physicalForce);
    physical_force_delete = Util.load_func("PhysicalForce_delete", [ct.c_int64], None)

    # void PhysicalForce_freeAll(PhysicalForce *physical_force_ptr);
    physical_force_free_all = Util.load_func("PhysicalForce_freeAll", [ct.c_int64], None)

    #################################################################
    # PersonalInformation Methods
    #

    # PersonalInformation *PersonalInformation_new(Editor *editor_ptr);
    editor_new_personal_information = Util.load_func("PersonalInformation_new", [ct.c_int64], ct.c_int64)

    # char *PersonalInformation_getLocalUri(PersonalInformation *information);
    personal_information_get_local_uri = Util.load_func("PersonalInformation_getLocalUri", [ct.c_int64], ct.c_int64)

    # void PersonalInformation_setLocalUri(PersonalInformation *information, const char *localUri);
    personal_information_set_local_uri = Util.load_func("PersonalInformation_setLocalUri", [ct.c_int64, ct.c_char_p], None)

    # PersonalInformation *PersonalInformation_addCreator(PersonalInformation *information, const char *value);
    personal_information_add_creator = Util.load_func("PersonalInformation_addCreator", [ct.c_int64, ct.c_char_p], ct.c_int64)

    # PersonalInformation *PersonalInformation_addName(PersonalInformation *information, const char *value);
    personal_information_add_name = Util.load_func("PersonalInformation_addName", [ct.c_int64, ct.c_char_p], ct.c_int64)

    # PersonalInformation *PersonalInformation_addMbox(PersonalInformation *information, const char *value);
    personal_information_add_mbox = Util.load_func("PersonalInformation_addMbox", [ct.c_int64, ct.c_char_p], ct.c_int64)

    # PersonalInformation *PersonalInformation_addAccountName(PersonalInformation *information, const char *value);
    personal_information_add_account_name = Util.load_func("PersonalInformation_addAccountName", [ct.c_int64, ct.c_char_p],
                                              ct.c_int64)

    # PersonalInformation *PersonalInformation_addAccountServiceHomepage(PersonalInformation *information, const char *value);
    personal_information_add_account_service_homepage = Util.load_func("PersonalInformation_addAccountServiceHomepage",
                                              [ct.c_int64, ct.c_char_p], ct.c_int64)

    # PersonalInformation *PersonalInformation_addFoafBlank(PersonalInformation *information, const char *predicate, const char *blank_value);
    personal_information_add_foaf_blank = Util.load_func("PersonalInformation_addFoafBlank", [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_int64)

    # PersonalInformation *PersonalInformation_addFoafUri(PersonalInformation *information, const char *predicate, const char *uri_value);
    personal_information_add_foaf_uri = Util.load_func("PersonalInformation_addFoafUri", [ct.c_int64, ct.c_char_p, ct.c_char_p],
                                              ct.c_int64)

    # PersonalInformation *PersonalInformation_addFoafLiteral(PersonalInformation *information, const char *predicate,const char *literal_value);
    personal_information_add_foaf_literal = Util.load_func("PersonalInformation_addFoafLiteral",
                                              [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_int64)

    # char *PersonalInformation_getMetaid(PersonalInformation *information);
    personal_information_get_metaid = Util.load_func("PersonalInformation_getMetaid", [ct.c_int64], ct.c_int64)

    # void PersonalInformation_setMetaid(PersonalInformation *information, const char *metaid);
    personal_information_set_metaid = Util.load_func("PersonalInformation_setMetaid", [ct.c_int64, ct.c_char_p], None)

    # char *PersonalInformation_getModelUri(PersonalInformation *information);
    personal_information_get_model_uri = Util.load_func("PersonalInformation_getModelUri", [ct.c_int64], ct.c_int64)

    # void PersonalInformation_setModelUri(PersonalInformation *information, const char *modelUri);
    personal_information_set_model_uri = Util.load_func("PersonalInformation_setModelUri", [ct.c_int64, ct.c_char_p], None)

    # void PersonalInformation_delete(PersonalInformation* information);
    personal_information_delete = Util.load_func("PersonalInformation_delete", [ct.c_int64], None)
