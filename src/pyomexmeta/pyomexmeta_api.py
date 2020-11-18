from __future__ import annotations

import ctypes as ct
import os
import sys
from typing import List

import shutil
import subprocess

_THIS_DIR = os.path.dirname(__file__)

_EXTRA_SEARCH_DIR_FILE = os.path.join(_THIS_DIR, "ExtraSearchDirectories.txt")

extra_search_paths = []
if (os.path.isfile(_EXTRA_SEARCH_DIR_FILE)):
    with open(_EXTRA_SEARCH_DIR_FILE, "r") as f:
        extra_search_paths = f.read().split("\n")

if sys.platform == "win32":
    extra_search_paths = [i.replace("/", "\\") for i in extra_search_paths]

def get_version():
    with open(os.path.join(_THIS_DIR, "VERSION.txt"), "r") as f:
        __version__ = f.read().strip()
    return __version__


__version__ = get_version()

if sys.platform == "win32":
    try:
        import win32api
    except ImportError:
        raise ImportError("win32api not found. Please run `pip install pywin32`")
    import win32con

_WORKING_DIRECTORY = os.path.dirname(os.path.realpath(__file__))


class Util:

    @staticmethod
    def wsl_available() -> bool:
        """
        heuristic to detect if Windows Subsystem for Linux is available.

        Uses presence of /etc/os-release in the WSL image to say Linux is there.
        This is a de facto file standard across Linux distros.
        """
        if os.name == "nt":
            wsl = shutil.which("wsl")
            if not wsl:
                return False
            return True
        return False

    @staticmethod
    def load_lib():
        omexmeta_capi_location = None

        extensions = [
            f"-{get_version()}.dll",
            f'-{get_version()}.so.{get_version()}',
            f'-{get_version()}.dylib'
        ]
        prefixes = ["", "lib"]

        # when working directory is different from __file__
        current_working_dir = os.getcwd()

        # when in install tree we look this current directory
        pyomexmeta_init_dir = os.path.abspath(os.path.dirname(__file__))

        # when in the build tree we look in ../../lib
        build_tree_bin_dir = os.path.abspath(
            os.path.join(
                os.path.dirname(os.path.dirname(os.path.dirname(__file__))), "bin"
            )
        )
        build_tree_lib_dir = os.path.abspath(
            os.path.join(
                os.path.dirname(os.path.dirname(os.path.dirname(__file__))), "lib"
            )
        )
        # Note: when in source tree we cannot locate the binary.
        search_directories = [current_working_dir, pyomexmeta_init_dir,
                              build_tree_bin_dir, build_tree_lib_dir] + extra_search_paths

        found_library_files = []
        for direct in search_directories:
            for ex in extensions:
                for pre in prefixes:
                    cand = os.path.join(direct, f"{pre}OmexMetaCAPI{ex}")
                    if os.path.isfile(cand):
                        # print(f"Found library at {cand}")
                        found_library_files.append(cand)

        if found_library_files == []:
            raise FileNotFoundError(f"Cannot locate libOmexMeta library in {str(search_directories)}")

        lib = None
        for lib_path in found_library_files:
            try:
                lib = ct.CDLL(lib_path)
            except Exception:
                dll_handle = win32api.LoadLibraryEx(lib_path, 0, win32con.LOAD_WITH_ALTERED_SEARCH_PATH)
                lib = ct.WinDLL(lib_path, handle=dll_handle)
                continue
        if not lib:
            raise ValueError("Could not load library")

        return lib

    @staticmethod
    def load_func(funcname: str, argtypes: List, restype) -> ct.CDLL._FuncPtr:
        func = Util.load_lib().__getattr__(funcname)
        func.restype = restype
        func.argtypes = argtypes
        return func

libomexmeta = Util.load_lib()

class eUriType:
    NONE = 0
    LOCAL_URI = 1
    MODEL_URI = 2
    IDENTIFIERS_URI = 3

class eXmlType:
    SBML = 0
    CELLML = 1

class PyOmexMetaAPI:
    """
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

    # char *RDF_toString(RDF *rdf_ptr, const char *format);
    rdf_to_string = Util.load_func("RDF_toString", [ct.c_int64, ct.c_char_p], ct.c_int64)

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

    # Editor RDF_toEditor(RDF *rdf_ptr, const char *xml, bool generate_new_metaids, bool sbml_semantic_extraction);
    rdf_to_editor = Util.load_func("RDF_toEditor", [ct.c_int64, ct.c_char_p, ct.c_bool, ct.c_bool], ct.c_int64)

    # bool RDF_equals_rdf_vs_string(RDF *rdf_ptr, const char *serialized_rdf, const char *format) {
    rdf_equals_rdf_vs_string = Util.load_func("RDF_equals_rdf_vs_string", [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_bool)

    # bool RDF_equals_rdf_vs_rdf(RDF *rdf_ptr1, RDF *rdf_ptr2, const char *format) {
    rdf_equals_rdf_vs_rdf = Util.load_func("RDF_equals_rdf_vs_rdf", [ct.c_int64, ct.c_int64, ct.c_char_p], ct.c_bool)

    # bool RDF_equals_string_vs_string(const char *first_rdf_graph, const char *second_rdf_graph, const char *format) {
    rdf_equals_string_vs_string = Util.load_func("RDF_equals_string_vs_string", [ct.c_char_p, ct.c_char_p, ct.c_char_p], ct.c_bool)


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

    # void Editor_addPhysicalProperty(Editor *editor_ptr, PhysicalProperty *physicalProperty);
    editor_add_physical_property = Util.load_func("Editor_addPhysicalProperty", [ct.c_int64, ct.c_int64],
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

    # SingularAnnotation *Editor_newSingularAnnotation(Editor *editor_ptr);
    editor_new_singular_annotation = Util.load_func("Editor_newSingularAnnotation", [ct.c_int64], ct.c_int64)

    # PhysicalEntity *Editor_newPhysicalEntity(Editor *editor_ptr);
    editor_new_physical_entity = Util.load_func("Editor_newPhysicalEntity", [ct.c_int64], ct.c_int64)

    # PhysicalProcess *Editor_newPhysicalProcess(Editor *editor_ptr);
    editor_new_physical_process = Util.load_func("Editor_newPhysicalProcess", [ct.c_int64], ct.c_int64)

    # PhysicalForce *Editor_newPhysicalForce(Editor *editor_ptr);
    editor_new_physical_force = Util.load_func("Editor_newPhysicalForce", [ct.c_int64], ct.c_int64)

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

    # Editor* Editor_addCreator(Editor *editor_ptr, std::string orcid_id);
    editor_add_creator = Util.load_func("Editor_addCreator", [ct.c_int64, ct.c_char_p], ct.c_int64)

    # Editor* Editor_addCurator(Editor *editor_ptr, std::string orcid_id);
    editor_add_curator = Util.load_func("Editor_addCurator", [ct.c_int64, ct.c_char_p], ct.c_int64)

    # Editor* Editor_addTaxon(Editor *editor_ptr, const char *taxon_id);
    editor_add_taxon = Util.load_func("Editor_addTaxon", [ct.c_int64, ct.c_char_p], ct.c_int64)

    # Editor* Editor_addPubmed(Editor *editor_ptr, const char *pubmedid);
    editor_add_pubmed = Util.load_func("Editor_addPubmed", [ct.c_int64, ct.c_char_p], ct.c_int64)

    # Editor* Editor_addDescription(Editor *editor_ptr, const char *date);
    editor_add_description = Util.load_func("Editor_addDescription", [ct.c_int64, ct.c_char_p], ct.c_int64)

    # Editor* Editor_addDateCreated(Editor *editor_ptr, const char *date);
    editor_add_date_created = Util.load_func("Editor_addDateCreated", [ct.c_int64, ct.c_char_p], ct.c_int64)

    # Editor* Editor_addParentModel(Editor *editor_ptr, const char *biomod_id);
    editor_add_parent_model = Util.load_func("Editor_addParentModel", [ct.c_int64, ct.c_char_p], ct.c_int64)

    #################################################################
    # SingularAnnotations methods
    #

    # SingularAnnotation *SingularAnnotation_about(SingularAnnotation *singular_annotation, const char *about);
    singular_annotation_about = Util.load_func("SingularAnnotation_about", [ct.c_int64, ct.c_char_p], ct.c_int64)

    # SingularAnnotation * SingularAnnotation_setPredicate(SingularAnnotation *singular_annotation, const char *namespace_,const char *term);
    singular_annotation_set_predicate = Util.load_func("SingularAnnotation_setPredicate",
                                                       [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_int64)

    # SingularAnnotation *
    #   SingularAnnotation_predicate(SingularAnnotation *singular_annotation, const char *namespace_, const char *term);
    singular_annotation_predicate = Util.load_func("SingularAnnotation_predicate",
                                                   [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_int64)

    # SingularAnnotation *SingularAnnotation_setPredicateFromUri(
    #         SingularAnnotation *singular_annotation, const char *uri);
    singular_annotation_set_predicate_from_uri = Util.load_func("SingularAnnotation_setPredicateFromUri",
                                                                [ct.c_int64, ct.c_char_p], ct.c_int64)

    # SingularAnnotation *SingularAnnotation_predicateFromUri(
    #         SingularAnnotation *singular_annotation, const char *uri);
    singular_annotation_predicate_from_uri = Util.load_func("SingularAnnotation_predicateFromUri",
                                                            [ct.c_int64, ct.c_char_p], ct.c_int64)

    # SingularAnnotation *SingularAnnotation_setResourceLiteral(
    #         SingularAnnotation *singular_annotation, const char *literal);
    singular_annotation_set_resource_literal = Util.load_func("SingularAnnotation_setResourceLiteral",
                                                              [ct.c_int64, ct.c_char_p], ct.c_int64)

    # SingularAnnotation *SingularAnnotation_resourceLiteral(
    #         SingularAnnotation *singular_annotation, const char *literal);
    singular_annotation_resource_literal = Util.load_func("SingularAnnotation_resourceLiteral",
                                                          [ct.c_int64, ct.c_char_p], ct.c_int64)

    # SingularAnnotation *
    # SingularAnnotation_setResourceUri(SingularAnnotation *singular_annotation, const char *identifiers_uri);
    singular_annotation_set_resource_uri = Util.load_func("SingularAnnotation_setResourceUri",
                                                          [ct.c_int64, ct.c_char_p],
                                                          ct.c_int64)
    # SingularAnnotation *
    # SingularAnnotation_resourceUri(SingularAnnotation *singular_annotation, const char *identifiers_uri);
    singular_annotation_resource_uri = Util.load_func("SingularAnnotation_resourceUri",
                                                      [ct.c_int64, ct.c_char_p],
                                                      ct.c_int64)

    # SingularAnnotation *
    # SingularAnnotation_setResourceBlank(SingularAnnotation *singular_annotation, const char *blank_id);
    singular_annotation_set_resource_blank = Util.load_func("SingularAnnotation_setResourceBlank",
                                                            [ct.c_int64, ct.c_char_p], ct.c_int64)

    # SingularAnnotation *
    # SingularAnnotation_resourceBlank(SingularAnnotation *singular_annotation, const char *blank_id);
    singular_annotation_resource_blank = Util.load_func("SingularAnnotation_resourceBlank",
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
    # PhysicalProperty methods
    #

    # PhysicalProperty *Editor_newPhysicalProperty(Editor *editor_ptr) {
    editor_new_physical_property = Util.load_func("Editor_newPhysicalProperty", [ct.c_int64], ct.c_int64)

    # char* PhysicalProperty_getAbout(PhysicalProperty* property) ;
    physical_property_get_about = Util.load_func("PhysicalProperty_getAbout", [ct.c_int64], ct.c_int64)

    # PhysicalProperty* PhysicalProperty_about(PhysicalProperty* property, const char* about, eUriType type = eUriType::NONE);
    physical_property_about = Util.load_func("PhysicalProperty_about", [ct.c_int64, ct.c_char_p, ct.c_int64], ct.c_int64)

    # char*  PhysicalProperty_getIsVersionOfValue(PhysicalProperty* property);
    physical_property_get_is_version_of_value = Util.load_func("PhysicalProperty_getIsVersionOfValue", [ct.c_int64], ct.c_int64 )

    # PhysicalProperty* PhysicalProperty_isPropertyOf(PhysicalProperty* property, const char* is_property_of, eUriType type);
    physical_property_is_property_of = Util.load_func("PhysicalProperty_isPropertyOf", [ct.c_int64, ct.c_char_p, ct.c_int64], ct.c_int64 )

    # PhysicalProperty* PhysicalProperty_isVersionOf(PhysicalProperty* property, const char* is_version_of);
    physical_property_is_version_of = Util.load_func("PhysicalProperty_isVersionOf", [ct.c_int64, ct.c_char_p], ct.c_int64 )

    # char* PhysicalProperty_getIsPropertyOfValue(PhysicalProperty* property);
    physical_property_get_is_property_of_value = Util.load_func("PhysicalProperty_getIsPropertyOfValue", [ct.c_int64], ct.c_int64 )

    # int PhysicalProperty_delete(PhysicalProperty* property);
    physical_property_delete = Util.load_func("PhysicalProperty_delete", [ct.c_int64], ct.c_int64 )

    #################################################################
    # PhysicalEntity methods
    #

    # PhysicalEntity *PhysicalEntity_setIdentity(
    #         PhysicalEntity *physical_entity_ptr, const char *identity_resource);
    physical_entity_set_identity = Util.load_func("PhysicalEntity_setIdentity", [ct.c_int64, ct.c_char_p], ct.c_int64)

    # PhysicalEntity *PhysicalEntity_identity(
    #        PhysicalEntity *physical_entity_ptr, const char *identity_resource);
    physical_entity_identity = Util.load_func("PhysicalEntity_identity", [ct.c_int64, ct.c_char_p], ct.c_int64)

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

    # PhysicalEntity *PhysicalEntity_hasProperty(PhysicalEntity *physical_entity_ptr, PhysicalProperty* property);
    physical_entity_has_property = Util.load_func("PhysicalEntity_hasProperty", [ct.c_int64, ct.c_int64], ct.c_int64)

    # PhysicalEntity *PhysicalEntity_hasPropertyisVersionOf(PhysicalEntity *physical_entity_ptr, const char* isVersionOf) ;
    physical_entity_has_property_is_version_of = Util.load_func("PhysicalEntity_hasPropertyisVersionOf", [ct.c_int64, ct.c_char_p], ct.c_int64)

    # PhysicalEntity *PhysicalEntity_hasPropertyFull(PhysicalEntity *physical_entity_ptr, const char* property_about, eUriType about_uri_type, const char* is_version_of) ;
    physical_entity_has_property_full = Util.load_func("PhysicalEntity_hasPropertyFull", [ct.c_int64, ct.c_char_p, ct.c_int64, ct.c_char_p], ct.c_int64)

    # void PhysicalEntity_delete(PhysicalEntity *physical_entity_ptr);
    physical_entity_delete = Util.load_func("PhysicalEntity_delete", [ct.c_int64], None)

    # void PhysicalEntity_freeAll(PhysicalEntity *physical_entity_ptr);
    physical_entity_free_all = Util.load_func("PhysicalEntity_freeAll", [ct.c_int64], None)

    # PhysicalEntity *PhysicalEntity_about(PhysicalEntity *physical_entity_ptr, const char *about, eUriType type) {
    physical_entity_about = Util.load_func("PhysicalEntity_about", [ct.c_int64, ct.c_char_p, ct.c_int64], ct.c_int64)

    # PhysicalEntity *PhysicalEntity_isPartOf(PhysicalEntity *physical_entity_ptr, const char *is_part_of);
    physical_entity_is_part_of = Util.load_func("PhysicalEntity_isPartOf", [ct.c_int64, ct.c_char_p], ct.c_int64)

    # PhysicalEntity *PhysicalEntity_hasPart(PhysicalEntity *physical_entity_ptr, const char *part);
    physical_entity_has_part = Util.load_func("PhysicalEntity_hasPart", [ct.c_int64, ct.c_char_p], ct.c_int64)

    #################################################################
    # PhysicalProcess methods
    #

    # PhysicalProcess *
    # PhysicalProcess_addSource(PhysicalProcess *physical_process,
    #                          const char *physical_entity_reference, eUriType type, int multiplier)
    physical_process_add_source = Util.load_func("PhysicalProcess_addSource",
                                                 [ct.c_int64, ct.c_char_p, ct.c_int64, ct.c_int64], ct.c_int64)

    # PhysicalProcess *
    # PhysicalProcess_addSink(PhysicalProcess *physical_process,
    #                        const char *physical_entity_reference, eUriType type, int multiplier)
    physical_process_add_sink = Util.load_func("PhysicalProcess_addSink",
                                               [ct.c_int64, ct.c_char_p, ct.c_int64, ct.c_int64], ct.c_int64)

    #     PhysicalProcess *
    #     PhysicalProcess_addMediator(PhysicalProcess *physical_process,
    #                                 const char *physical_entity_reference, eUriType type)
    physical_process_add_mediator = Util.load_func("PhysicalProcess_addMediator",
                                                   [ct.c_int64, ct.c_char_p, ct.c_int64], ct.c_int64)

    # char *PhysicalProcess_str(PhysicalProcess *physical_process_ptr, const char *format, const char *base_uri);
    physical_process_str = Util.load_func("PhysicalProcess_str",
                                          [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_int64)

    # PhysicalProcess *PhysicalProcess_isVersionOf(PhysicalProcess *physical_process_ptr, const char *version, eUriType type){
    physical_process_is_version_of = Util.load_func("PhysicalProcess_isVersionOf", [ct.c_int64, ct.c_char_p, ct.c_int64], ct.c_int64)

    # PhysicalProcess *PhysicalProcess_hasProperty(PhysicalProcess *physical_entity_ptr, PhysicalProperty* property);
    physical_process_has_property = Util.load_func("PhysicalProcess_hasProperty", [ct.c_int64], ct.c_int64)

    # PhysicalProcess *PhysicalProcess_hasPropertyisVersionOf(PhysicalProcess *physical_process_ptr, const char* isVersionOf) ;
    physical_process_has_property_is_version_of = Util.load_func("PhysicalProcess_hasPropertyisVersionOf", [ct.c_int64, ct.c_char_p], ct.c_int64)

    # PhysicalProcess *PhysicalProcess_hasPropertyFull(PhysicalProcess *physical_process_ptr, const char* property_about, eUriType about_uri_type, const char* is_version_of) ;
    physical_process_has_property_full = Util.load_func("PhysicalProcess_hasPropertyFull", [ct.c_int64, ct.c_char_p, ct.c_int64, ct.c_char_p], ct.c_int64)

    # void PhysicalProcess_delete(PhysicalProcess *physicalProcess);
    physical_process_delete = Util.load_func("PhysicalProcess_delete", [ct.c_int64], None)

    # void PhysicalProcess_freeAll(PhysicalProcess *physicalProcess);
    physical_process_free_all = Util.load_func("PhysicalProcess_freeAll", [ct.c_int64], None)

    # PhysicalProcess *PhysicalProcess_about(PhysicalProcess *physical_process_ptr, const char *about, eUriType type);
    physical_process_about = Util.load_func("PhysicalProcess_about", [ct.c_int64, ct.c_char_p, ct.c_int64], ct.c_int64)


    #################################################################
    # PhysicalForce Methods
    #

    # PhysicalForce *PhysicalForce_setPhysicalProperty(
    #         PhysicalForce *physical_force_ptr, const char *subject_metaid, const char *physical_property);
    physical_force_set_physical_property = Util.load_func("PhysicalForce_setPhysicalProperty",
                                                          [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_int64)

    #    PhysicalForce *PhysicalForce_addSource(PhysicalForce *physical_force_ptr,
    #                                        const char *physical_entity_reference, eUriType type, int multiplier)
    physical_force_add_source = Util.load_func("PhysicalForce_addSource",
                                               [ct.c_int64, ct.c_char_p, ct.c_int64, ct.c_int64], ct.c_int64)

    #    PhysicalForce *PhysicalForce_addSink(PhysicalForce *physical_force_ptr,
    #                                      const char *physical_entity_reference, eUriType type, int multiplier) {
    physical_force_add_sink = Util.load_func("PhysicalForce_addSink",
                                             [ct.c_int64, ct.c_char_p, ct.c_int64, ct.c_int64], ct.c_int64)

    # char *PhysicalForce_str(PhysicalForce *physical_force_ptr, const char *format, const char *base_uri);
    physical_force_str = Util.load_func("PhysicalForce_str",
                                        [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_int64)

    # PhysicalForce *PhysicalForce_hasProperty(PhysicalForce *physical_entity_ptr, PhysicalProperty* property);
    physical_force_has_property = Util.load_func("PhysicalForce_hasProperty", [ct.c_int64], ct.c_int64)

    # PhysicalForce *PhysicalForce_hasPropertyisVersionOf(PhysicalForce *physical_process_ptr, const char* isVersionOf) ;
    physical_force_has_property_is_version_of = Util.load_func("PhysicalForce_hasPropertyisVersionOf", [ct.c_int64, ct.c_char_p], ct.c_int64)

    # PhysicalForce *PhysicalForce_hasPropertyFull(PhysicalForce *physical_process_ptr, const char* property_about, eUriType about_uri_type, const char* is_version_of) ;
    physical_force_has_property_full = Util.load_func("PhysicalForce_hasPropertyFull", [ct.c_int64, ct.c_char_p, ct.c_int64, ct.c_char_p], ct.c_int64)

    # void PhysicalForce_delete(PhysicalForce *physicalForce);
    physical_force_delete = Util.load_func("PhysicalForce_delete", [ct.c_int64], None)

    # void PhysicalForce_freeAll(PhysicalForce *physical_force_ptr);
    physical_force_free_all = Util.load_func("PhysicalForce_freeAll", [ct.c_int64], None)

    # PhysicalForce *PhysicalForce_about(PhysicalForce *physical_force_ptr, const char *about, eUriType type);
    physical_force_about = Util.load_func("PhysicalForce_about", [ct.c_int64, ct.c_char_p, ct.c_int64], ct.c_int64)

    #################################################################
    # PersonalInformation Methods
    #

    # PersonalInformation *Editor_newPersonalInformation(Editor *editor_ptr);
    editor_new_personal_information = Util.load_func("Editor_newPersonalInformation", [ct.c_int64], ct.c_int64)

    # char *PersonalInformation_getLocalUri(PersonalInformation *information);
    personal_information_get_local_uri = Util.load_func("PersonalInformation_getLocalUri", [ct.c_int64], ct.c_int64)

    # void PersonalInformation_setLocalUri(PersonalInformation *information, const char *localUri);
    personal_information_set_local_uri = Util.load_func("PersonalInformation_setLocalUri", [ct.c_int64, ct.c_char_p],
                                                        None)

    # PersonalInformation *PersonalInformation_addCreator(PersonalInformation *information, const char *value);
    personal_information_add_creator = Util.load_func("PersonalInformation_addCreator", [ct.c_int64, ct.c_char_p],
                                                      ct.c_int64)

    # PersonalInformation *PersonalInformation_addName(PersonalInformation *information, const char *value);
    personal_information_add_name = Util.load_func("PersonalInformation_addName", [ct.c_int64, ct.c_char_p], ct.c_int64)

    # PersonalInformation *PersonalInformation_addMbox(PersonalInformation *information, const char *value);
    personal_information_add_mbox = Util.load_func("PersonalInformation_addMbox", [ct.c_int64, ct.c_char_p], ct.c_int64)

    # PersonalInformation *PersonalInformation_addAccountName(PersonalInformation *information, const char *value);
    personal_information_add_account_name = Util.load_func("PersonalInformation_addAccountName",
                                                           [ct.c_int64, ct.c_char_p],
                                                           ct.c_int64)

    # PersonalInformation *PersonalInformation_addAccountServiceHomepage(PersonalInformation *information, const char *value);
    personal_information_add_account_service_homepage = Util.load_func("PersonalInformation_addAccountServiceHomepage",
                                                                       [ct.c_int64, ct.c_char_p], ct.c_int64)

    # PersonalInformation *PersonalInformation_addFoafBlank(PersonalInformation *information, const char *predicate, const char *blank_value);
    personal_information_add_foaf_blank = Util.load_func("PersonalInformation_addFoafBlank",
                                                         [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_int64)

    # PersonalInformation *PersonalInformation_addFoafUri(PersonalInformation *information, const char *predicate, const char *uri_value);
    personal_information_add_foaf_uri = Util.load_func("PersonalInformation_addFoafUri",
                                                       [ct.c_int64, ct.c_char_p, ct.c_char_p],
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
    personal_information_set_model_uri = Util.load_func("PersonalInformation_setModelUri", [ct.c_int64, ct.c_char_p],
                                                        None)

    # void PersonalInformation_delete(PersonalInformation* information);
    personal_information_delete = Util.load_func("PersonalInformation_delete", [ct.c_int64], None)
