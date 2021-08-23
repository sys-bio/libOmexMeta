from __future__ import annotations

import ctypes as ct
import glob
import os
import re
import shutil
import sys
from typing import List

################################################################
#   Some extra code for locating libOmexMeta C API binaries on
#   developer machines for running pyomexmeta directly from the source directory.
#

# todo wrap in a function
_THIS_DIR = os.path.dirname(__file__)
_EXTRA_SEARCH_DIR_FILE = os.path.join(_THIS_DIR, "ExtraSearchDirectories.txt")
_EXTRA_SEARCH_PATHS = []
if (os.path.isfile(_EXTRA_SEARCH_DIR_FILE)):
    with open(_EXTRA_SEARCH_DIR_FILE, "r") as f:
        _EXTRA_SEARCH_PATHS = f.read().split("\n")

# remove comment lines from extra search list
_EXTRA_SEARCH_PATHS = [p for p in _EXTRA_SEARCH_PATHS if not p.startswith("#")]
if sys.platform == "win32":
    _EXTRA_SEARCH_PATHS = [i.replace("/", "\\") for i in _EXTRA_SEARCH_PATHS]


def get_version():
    try:
        # read version from VERSION.txt
        with open(os.path.join(_THIS_DIR, "VERSION.txt"), "r") as f:
            version = f.read().strip()
        return version
    except FileNotFoundError:
        # fall back on extracting version from the OmexMetaCAPI filename
        current_dir = os.path.abspath(os.path.dirname(__file__))
        files_in_current_dir = glob.glob(os.path.join(current_dir, "*"))
        results = [
            re.findall("OmexMetaCAPI-(\d*.\d*.\d*).dll|"
                       "libOmexMetaCAPI.so.(\d*.\d*.\d*)|"
                       "libOmexMetaCAPI.(\d*.\d*.\d*).dylib|"
                       "libOmexMetaCAPI-(\d*.\d*.\d*).dylib",
                       i) for i in files_in_current_dir]
        results = [i for i in results if i != []]

        assert len(results) == 1, f"length of results == {len(results)}"
        results = results[0]  # a list of tuples : [('1.1.18', '', '')]
        results = [i for i in results[0] if i != '']
        assert len(results) == 1, f"length of results == {len(results)}"
        results = results[0]
        assert isinstance(results, str), f"type is: {type(results)}"
        return results


__version__ = get_version()

if sys.platform == "win32":
    # This really was a pain on windows. Whyy?
    try:
        import win32api
    except ImportError as e:
        print(str(e))
        s = f"sys.path: {sys.path}\n"
        s += f"sys.platform: {sys.platform}\n"
        s += f"sys.executable: {sys.executable}\n"
        s += f"sys.version_info: {sys.version_info}\n"
        s += f"sys.version: {sys.version}\n"
        raise ImportError(f"win32api not found. Please run `pip install pywin32`"
                          f"System information: \n {s}")
    import win32con

_WORKING_DIRECTORY = os.path.dirname(os.path.realpath(__file__))


class Util:

    def __init__(self):
        self._lib = self.load_lib()

    def load_lib(self):
        """
        Load the libOmexMeta C API binary. This methods incorporates
        flexibility to load libOmexMeta from multiple locations and works
        from the source, binary and install trees and under site-pacakges.
        Returns:

        """

        # todo note that we are currently using two different strategies for locating the library (see get_version())
        #    consolidate this code
        extensions = [
            f"-{get_version()}.dll",
            f'-{get_version()}.so.{get_version()}',
            f'.so.{get_version()}',
            f'.{get_version()}.dylib',
            f'-{get_version()}.dylib'
        ]
        # "" for windows, lib for linux
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

        search_directories = [current_working_dir, pyomexmeta_init_dir,
                              build_tree_bin_dir, build_tree_lib_dir] + _EXTRA_SEARCH_PATHS

        found_library_files = []
        candidates = []
        for direct in search_directories:
            for ex in extensions:
                for pre in prefixes:
                    cand = os.path.join(direct, f"{pre}OmexMetaCAPI{ex}")
                    candidates.append(cand)
                    if os.path.isfile(cand):
                        # print(f"Found library at {cand}")
                        found_library_files.append(cand)

        if not found_library_files:
            err = 'Cannot locate libOmexMeta library in any of the search locations:\n'
            for c in candidates:
                err += "\t" + c + "\n"
            raise FileNotFoundError(err)

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

    def load_func(self, funcname: str, argtypes: List, restype) -> ct.CDLL._FuncPtr:
        func = self._lib.__getattr__(funcname)
        func.restype = restype
        func.argtypes = argtypes
        return func


libomexmeta = Util().load_lib()


class eUriType:
    NONE = 0
    LOCAL_URI = 1
    MODEL_URI = 2
    IDENTIFIERS_URI = 3


class eLogLevel:
    trace = 0
    debug = 1
    info = 2
    warn = 3
    err = 4
    critical = 5
    off = 6

    enum_items = [
        "trace",
        "debug",
        "info",
        "warning",
        "error",
        "critical",
        "off"
    ]

    def __init__(self, level: int):
        self.level = level

    def __str__(self):
        return self.enum_items[self.level]


class eXmlType:
    SBML = 0
    CELLML = 1


class OmexMetaException(Exception):
    pass


class PyOmexMetaAPI:
    """
    Encourage developers to mainain the order of functions loaded here
    to be as close as possible as that in OmexMetaCApi.h as it facilitates development

    Explain decision to only set self uri's from RDF not editor.
    """

    utils = Util()

    # RDF methods
    def get_and_free_c_str(self, c_string_ptr: ct.c_int64) -> str:
        """Uses ctypes to transfer a C string to a python string and free the C string"""
        free_func = self.utils.load_func("free_c_char_star", [ct.c_void_p], None)
        string = ct.cast(c_string_ptr, ct.c_char_p).value
        decoded_str = string.decode()
        free_func(c_string_ptr)  # free the data
        del c_string_ptr  # free the ptr
        return decoded_str

    @staticmethod
    def crlf_to_lr(string: str) -> str:
        """Helper method for converting line endings. Needed mostly for query. For developers"""
        return string.replace('\r\n', '\n')

    # int free_c_char_star(char *c);
    free_char_star = utils.load_func("free_c_char_star", [ct.c_char_p], None)

    # char* getLastError()
    def get_last_error(self):
        _get_last_error = self.utils.load_func("getLastError", [], ct.c_int64)
        error = _get_last_error()
        if error is None or error == 0:
            return None
        return self.get_and_free_c_str(error)

    clear_last_error = utils.load_func("clearLastError", [], None)
    #################################################################
    # RDF methods
    #
    function_that_returns_null = utils.load_func("functionThatReturnsNullptr", [], ct.c_int64)

    # RDF *RDF_new(const char *storage_type = "memory", const char *storage_name = "semsim_store",
    #              const char *storage_options = nullptr, const char *model_options = nullptr);
    rdf_new = utils.load_func("RDF_new", [ct.c_char_p, ct.c_char_p, ct.c_char_p, ct.c_char_p], ct.c_int64)

    # int RDF_size(RDF *rdf_ptr);
    rdf_size = utils.load_func("RDF_size", [ct.c_int64], ct.c_int)

    # RDF *RDF_fromString(const char *str, const char *format,
    #                         const char *storage_type = "memory", const char *storage_name = "semsim_store",
    #                         const char *storage_options = nullptr, const char *model_options = nullptr);
    rdf_from_string = utils.load_func("RDF_fromString",
                                      [ct.c_char_p, ct.c_char_p,
                                       ct.c_char_p, ct.c_char_p, ct.c_void_p, ct.c_void_p], ct.c_int64)

    # int RDF_addFromString(RDF *rdf_ptr, const char *str, const char *format);
    rdf_add_from_string = utils.load_func("RDF_addFromString", [ct.c_int64, ct.c_char_p, ct.c_char_p],
                                          ct.c_int)

    # RDF *RDF_fromUri(const char *uri_string, const char *format,
    #                  const char *storage_type = "memory", const char *storage_name = "semsim_store",
    #                  const char *storage_options = nullptr, const char *model_options = nullptr);
    rdf_from_uri = utils.load_func("RDF_fromUri",
                                   [ct.c_char_p, ct.c_char_p,
                                    ct.c_char_p, ct.c_char_p,
                                    ct.c_char_p, ct.c_char_p], ct.c_int64)

    # int RDF_addFromUri(RDF *rdf_ptr, const char *uri_string, const char *format);
    rdf_add_from_uri = utils.load_func("RDF_addFromUri", [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_int)

    # RDF *RDF_fromFile(const char *filename, const char *format, const char *storage_type = "memory",
    #                   const char *storage_name = "semsim_store",
    #                   const char *storage_options = nullptr, const char *model_options = nullptr);
    rdf_from_file = utils.load_func("RDF_fromFile", [ct.c_char_p, ct.c_char_p,
                                                     ct.c_char_p, ct.c_char_p,
                                                     ct.c_char_p, ct.c_char_p], ct.c_int64)

    # int RDF_addFromFile(RDF *rdf_ptr, const char *uri_string, const char *format);
    rdf_add_from_file = utils.load_func("RDF_addFromFile", [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_int)

    # char *RDF_toString(RDF *rdf_ptr, const char *format);
    rdf_to_string = utils.load_func("RDF_toString", [ct.c_int64, ct.c_char_p], ct.c_int64)

    # int RDF_toFile(RDF *rdf_ptr, const char *format, const char *filename);
    rdf_to_file = utils.load_func("RDF_toFile", [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_int)

    # int RDF_delete(RDF *rdf_ptr);
    rdf_delete = utils.load_func("RDF_delete", [ct.c_int64], ct.c_int)

    # char *RDF_queryResultsAsString(RDF *rdf_ptr, const char *query_str, const char *results_format);
    rdf_query_results_as_str = utils.load_func("RDF_queryResultsAsString", [ct.c_int64, ct.c_char_p, ct.c_char_p],
                                               ct.c_int64)

    # Note yet supported - how to get std::unordered_map into a Python dict? Problem for later
    # ResultsMap RDF_queryResultsAsMap(RDF *rdf_ptr, const char *query_str, const char *results_format);
    rdf_query_results_as_map = utils.load_func("RDF_queryResultsAsMap", [ct.c_int64, ct.c_char_p], ct.c_int64)

    # int RDF_setRepositoryUri(RDF *rdf_ptr, std::string repository_uri);
    rdf_set_repository_uri = utils.load_func("RDF_setRepositoryUri", [ct.c_int64, ct.c_char_p], ct.c_int64)

    # int RDF_setArchiveUri(RDF *rdf_ptr, std::string archive_uri);
    rdf_set_archive_uri = utils.load_func("RDF_setArchiveUri", [ct.c_int64, ct.c_char_p], ct.c_int64)

    # int RDF_setModelUri(RDF *rdf_ptr, std::string model_uri);
    rdf_set_model_uri = utils.load_func("RDF_setModelUri", [ct.c_int64, ct.c_char_p], ct.c_int64)

    # void RDF::setModelMetaid(const std::string& modelMetaid);
    rdf_set_model_metaid = utils.load_func("RDF_setModelMetaid", [ct.c_int64, ct.c_char_p], ct.c_int64)

    # char* RDF_getRepositoryUri(RDF *rdf_ptr);
    rdf_get_repository_uri = utils.load_func("RDF_getRepositoryUri", [ct.c_int64], ct.c_int64)

    # char *RDF_getModelLevelAnnotationUri(RDF *rdf_ptr);
    rdf_get_model_level_annotation_uri = utils.load_func("RDF_getModelLevelAnnotationUri", [ct.c_int64], ct.c_int64)

    # char* RDF_getArchiveUri(RDF *rdf_ptr);
    rdf_get_archive_uri = utils.load_func("RDF_getArchiveUri", [ct.c_int64], ct.c_int64)

    # char* RDF_getModelUri(RDF *rdf_ptr);
    rdf_get_model_uri = utils.load_func("RDF_getModelUri", [ct.c_int64], ct.c_int64)

    # char* RDF_getLocalUri(RDF *rdf_ptr);
    rdf_get_local_uri = utils.load_func("RDF_getLocalUri", [ct.c_int64], ct.c_int64)

    # const std::string &RDF::getModelMetaid();
    rdf_get_model_metaid = utils.load_func("RDF_getModelMetaid", [ct.c_int64], ct.c_int64)

    # Editor RDF_toEditor(RDF *rdf_ptr, const char *xml, bool generate_new_metaids, bool sbml_semantic_extraction);
    rdf_to_editor = utils.load_func("RDF_toEditor", [ct.c_int64, ct.c_char_p, ct.c_bool, ct.c_bool], ct.c_int64)

    # bool RDF_equals_rdf_vs_string(RDF *rdf_ptr, const char *serialized_rdf, const char *format, bool, bool verbose) {
    rdf_equals_rdf_vs_string = utils.load_func("RDF_equals_rdf_vs_string",
                                               [ct.c_int64, ct.c_char_p, ct.c_char_p, ct.c_bool],
                                               ct.c_bool)

    # bool RDF_equals_rdf_vs_rdf(RDF *rdf_ptr1, RDF *rdf_ptr2, const char *format, bool verbose) {
    rdf_equals_rdf_vs_rdf = utils.load_func("RDF_equals_rdf_vs_rdf", [ct.c_int64, ct.c_int64, ct.c_char_p, ct.c_bool],
                                            ct.c_bool)

    # bool RDF_equals_string_vs_string(const char *first_rdf_graph, const char *second_rdf_graph, const char *format, bool verbose) {
    rdf_equals_string_vs_string = utils.load_func("RDF_equals_string_vs_string",
                                                  [ct.c_char_p, ct.c_char_p, ct.c_char_p, ct.c_bool],
                                                  ct.c_bool)

    #################################################################
    # Editor methods
    #

    # int Editor_addNamespace(Editor *editor_ptr, const char *namespace_, const char *prefix);
    editor_add_namespace = utils.load_func("Editor_addNamespace", [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_int)

    # int Editor_addSingleAnnotation(Editor *editor_ptr, SingularAnnotation *singularAnnotation);
    editor_add_single_annotation = utils.load_func("Editor_addSingleAnnotation",
                                                   [ct.c_int64, ct.c_int64], ct.c_int)

    # int Editor_addPhysicalEntity(Editor *editor_ptr, PhysicalEntity *physicalEntity);
    editor_add_physical_entity = utils.load_func("Editor_addPhysicalEntity", [ct.c_int64, ct.c_int64], ct.c_int)

    # int Editor_addPhysicalProcess(Editor *editor_ptr, PhysicalProcess *physicalProcess);
    editor_add_physical_process = utils.load_func("Editor_addPhysicalProcess", [ct.c_int64, ct.c_int64], ct.c_int)

    # int Editor_addEnergyDiff(Editor *editor_ptr, EnergyDiff *physicalForce);
    editor_add_energy_diff = utils.load_func("Editor_addEnergyDiff", [ct.c_int64, ct.c_int64], ct.c_int)

    # int Editor_addPhysicalProperty(Editor *editor_ptr, PhysicalProperty *physicalProperty);
    editor_add_physical_property = utils.load_func("Editor_addPhysicalProperty", [ct.c_int64, ct.c_int64],
                                                   ct.c_int)

    # int Editor_checkValidMetaid(Editor *editor_ptr, const char *id);
    editor_check_valid_metaid = utils.load_func("Editor_checkValidMetaid", [ct.c_int64, ct.c_char_p],
                                                ct.c_int)

    # int Editor_removeSingleAnnotation(Editor *editor_ptr, SingularAnnotation *singularAnnotation);
    editor_remove_single_annotation = utils.load_func("Editor_removeSingleAnnotation", [ct.c_int64], ct.c_int)

    # int Editor_removePhysicalEntity(Editor *editor_ptr, PhysicalEntity *physicalEntity);
    editor_remove_physical_entity = utils.load_func("Editor_removePhysicalEntity", [ct.c_int64], ct.c_int)

    # int Editor_removePhysicalProcess(Editor *editor_ptr, PhysicalProcess *physicalProcess);
    editor_remove_physical_process = utils.load_func("Editor_removePhysicalProcess", [ct.c_int64], ct.c_int)

    # int Editor_removeEnergyDiff(Editor *editor_ptr, EnergyDiff *physicalForce);
    editor_remove_energy_diff = utils.load_func("Editor_removeEnergyDiff", [ct.c_int64], ct.c_int)

    # int Editor_removePersonalInformation(Editor *editor_ptr, PersonalInformation *information);
    editor_remove_personal_information = utils.load_func("Editor_removePersonalInformation", [ct.c_int64], ct.c_int)

    # int Editor_addPersonalInformation(Editor *editor_ptr, PersonalInformation *personalInformation);
    editor_add_personal_information = utils.load_func("Editor_addPersonalInformation", [ct.c_int64, ct.c_int64],
                                                      ct.c_int)

    # char *Editor_getMetaId(Editor *editor_ptr, int index);
    editor_get_metaid = utils.load_func("Editor_getMetaId", [ct.c_int64, ct.c_int64], ct.c_int64)

    # int Editor_getNumMetaIds(Editor *editor_ptr);
    editor_get_num_metaids = utils.load_func("Editor_getNumMetaIds", [ct.c_int64], ct.c_int64)

    # char *Editor_getXml(Editor *editor_ptr);
    editor_get_xml = utils.load_func("Editor_getXml", [ct.c_int64], ct.c_int64)

    # SingularAnnotation *Editor_newSingularAnnotation(Editor *editor_ptr);
    editor_new_singular_annotation = utils.load_func("Editor_newSingularAnnotation", [ct.c_int64], ct.c_int64)

    # PhysicalEntity *Editor_newPhysicalEntity(Editor *editor_ptr);
    editor_new_physical_entity = utils.load_func("Editor_newPhysicalEntity", [ct.c_int64], ct.c_int64)

    # PhysicalProcess *Editor_newPhysicalProcess(Editor *editor_ptr);
    editor_new_physical_process = utils.load_func("Editor_newPhysicalProcess", [ct.c_int64], ct.c_int64)

    # EnergyDiff *Editor_newEnergyDiff(Editor *editor_ptr);
    editor_new_energy_diff = utils.load_func("Editor_newEnergyDiff", [ct.c_int64], ct.c_int64)

    # int Editor_delete(Editor *editor_ptr);
    editor_delete = utils.load_func("Editor_delete", [ct.c_int64], ct.c_int)

    # char*Editor_getArchiveUri(Editor *editor_ptr);
    editor_get_archive_uri = utils.load_func("Editor_getArchiveUri", [ct.c_int64], ct.c_int64)

    # char*Editor_getLocalUri(Editor *editor_ptr);
    editor_get_local_uri = utils.load_func("Editor_getLocalUri", [ct.c_int64], ct.c_int64)

    # char*Editor_getModelUri(Editor *editor_ptr);
    editor_get_model_uri = utils.load_func("Editor_getModelUri", [ct.c_int64], ct.c_int64)

    # char*Editor_getRepositoryUri(Editor *editor_ptr);
    editor_get_repository_uri = utils.load_func("Editor_getRepositoryUri", [ct.c_int64], ct.c_int64)

    # Editor* Editor_addCreator(Editor *editor_ptr, std::string orcid_id);
    editor_add_creator = utils.load_func("Editor_addCreator", [ct.c_int64, ct.c_char_p], ct.c_int64)

    # char *Editor_stripAnnotations(Editor *editor_ptr, const char* annotationElementName)
    editor_strip_annotations = utils.load_func("Editor_stripAnnotations", [ct.c_int64, ct.c_char_p], ct.c_int64)

    # Editor* Editor_addContributor(Editor *editor_ptr, std::string orcid_id);
    editor_add_contributor = utils.load_func("Editor_addContributor", [ct.c_int64, ct.c_char_p], ct.c_int64)

    # Editor* Editor_addTaxon(Editor *editor_ptr, const char *taxon_id);
    editor_add_taxon = utils.load_func("Editor_addTaxon", [ct.c_int64, ct.c_char_p], ct.c_int64)

    # Editor* Editor_addPubmed(Editor *editor_ptr, const char *pubmedid);
    editor_add_pubmed = utils.load_func("Editor_addPubmed", [ct.c_int64, ct.c_char_p], ct.c_int64)

    # Editor* Editor_addDescription(Editor *editor_ptr, const char *date);
    editor_add_description = utils.load_func("Editor_addDescription", [ct.c_int64, ct.c_char_p], ct.c_int64)

    # Editor* Editor_addDateCreated(Editor *editor_ptr, const char *date);
    editor_add_date_created = utils.load_func("Editor_addDateCreated", [ct.c_int64, ct.c_char_p], ct.c_int64)

    # Editor* Editor_addParentModel(Editor *editor_ptr, const char *biomod_id);
    editor_add_parent_model = utils.load_func("Editor_addParentModel", [ct.c_int64, ct.c_char_p], ct.c_int64)

    #################################################################
    # SingularAnnotations methods
    #

    # SingularAnnotation *SingularAnnotation_about(SingularAnnotation *singular_annotation, const char *about);
    singular_annotation_about = utils.load_func("SingularAnnotation_about", [ct.c_int64, ct.c_char_p], ct.c_int64)

    # SingularAnnotation * SingularAnnotation_setPredicate(SingularAnnotation *singular_annotation, const char *namespace_,const char *term);
    singular_annotation_set_predicate = utils.load_func("SingularAnnotation_setPredicate",
                                                        [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_int64)

    # SingularAnnotation *
    #   SingularAnnotation_predicate(SingularAnnotation *singular_annotation, const char *namespace_, const char *term);
    singular_annotation_predicate = utils.load_func("SingularAnnotation_predicate",
                                                    [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_int64)

    # SingularAnnotation *SingularAnnotation_setPredicateFromUri(
    #         SingularAnnotation *singular_annotation, const char *uri);
    singular_annotation_set_predicate_from_uri = utils.load_func("SingularAnnotation_setPredicateFromUri",
                                                                 [ct.c_int64, ct.c_char_p], ct.c_int64)

    # SingularAnnotation *SingularAnnotation_predicateFromUri(
    #         SingularAnnotation *singular_annotation, const char *uri);
    singular_annotation_predicate_from_uri = utils.load_func("SingularAnnotation_predicateFromUri",
                                                             [ct.c_int64, ct.c_char_p], ct.c_int64)

    # SingularAnnotation *SingularAnnotation_setResourceLiteral(
    #         SingularAnnotation *singular_annotation, const char *literal);
    singular_annotation_set_resource_literal = utils.load_func("SingularAnnotation_setResourceLiteral",
                                                               [ct.c_int64, ct.c_char_p], ct.c_int64)

    # SingularAnnotation *SingularAnnotation_resourceLiteral(
    #         SingularAnnotation *singular_annotation, const char *literal);
    singular_annotation_resource_literal = utils.load_func("SingularAnnotation_resourceLiteral",
                                                           [ct.c_int64, ct.c_char_p], ct.c_int64)

    # SingularAnnotation *
    # SingularAnnotation_setResourceUri(SingularAnnotation *singular_annotation, const char *identifiers_uri);
    singular_annotation_set_resource_uri = utils.load_func("SingularAnnotation_setResourceUri",
                                                           [ct.c_int64, ct.c_char_p],
                                                           ct.c_int64)
    # SingularAnnotation *
    # SingularAnnotation_resourceUri(SingularAnnotation *singular_annotation, const char *identifiers_uri);
    singular_annotation_resource_uri = utils.load_func("SingularAnnotation_resourceUri",
                                                       [ct.c_int64, ct.c_char_p],
                                                       ct.c_int64)

    # SingularAnnotation *
    # SingularAnnotation_setResourceBlank(SingularAnnotation *singular_annotation, const char *blank_id);
    singular_annotation_set_resource_blank = utils.load_func("SingularAnnotation_setResourceBlank",
                                                             [ct.c_int64, ct.c_char_p], ct.c_int64)

    # SingularAnnotation *
    # SingularAnnotation_resourceBlank(SingularAnnotation *singular_annotation, const char *blank_id);
    singular_annotation_resource_blank = utils.load_func("SingularAnnotation_resourceBlank",
                                                         [ct.c_int64, ct.c_char_p], ct.c_int64)

    # char *SingularAnnotation_getAbout(SingularAnnotation *singular_annotation);
    singular_annotation_get_about = utils.load_func("SingularAnnotation_getAbout", [ct.c_int64], ct.c_int64)

    # char *SingularAnnotation_getPredicate(SingularAnnotation *singular_annotation);
    singular_annotation_get_predicate = utils.load_func("SingularAnnotation_getPredicate", [ct.c_int64], ct.c_int64)

    # char *SingularAnnotation_getResource(SingularAnnotation *singular_annotation);
    singular_annotation_get_resource = utils.load_func("SingularAnnotation_getResource", [ct.c_int64], ct.c_int64)

    # int SingularAnnotation_delete(SingularAnnotation *singularAnnotation);
    singular_annotation_delete = utils.load_func("SingularAnnotation_delete", [ct.c_int64], ct.c_int)

    #################################################################
    # PhysicalProperty methods
    #

    # PhysicalProperty *Editor_newPhysicalProperty(Editor *editor_ptr) {
    editor_new_physical_property = utils.load_func("Editor_newPhysicalProperty", [ct.c_int64], ct.c_int64)

    # char* PhysicalProperty_getAbout(PhysicalProperty* property) ;
    physical_property_get_about = utils.load_func("PhysicalProperty_getAbout", [ct.c_int64], ct.c_int64)

    # PhysicalProperty* PhysicalProperty_about(PhysicalProperty* property, const char* about, eUriType type = eUriType::NONE);
    physical_property_about = utils.load_func("PhysicalProperty_about", [ct.c_int64, ct.c_char_p, ct.c_int64],
                                              ct.c_int64)

    # char*  PhysicalProperty_getIsVersionOfValue(PhysicalProperty* property);
    physical_property_get_is_version_of_value = utils.load_func("PhysicalProperty_getIsVersionOfValue", [ct.c_int64],
                                                                ct.c_int64)

    # PhysicalProperty* PhysicalProperty_isPropertyOf(PhysicalProperty* property, const char* is_property_of, eUriType type);
    physical_property_is_property_of = utils.load_func("PhysicalProperty_isPropertyOf",
                                                       [ct.c_int64, ct.c_char_p, ct.c_int64], ct.c_int64)

    # PhysicalProperty* PhysicalProperty_isVersionOf(PhysicalProperty* property, const char* is_version_of);
    physical_property_is_version_of = utils.load_func("PhysicalProperty_isVersionOf", [ct.c_int64, ct.c_char_p],
                                                      ct.c_int64)

    # char* PhysicalProperty_getIsPropertyOfValue(PhysicalProperty* property);
    physical_property_get_is_property_of_value = utils.load_func("PhysicalProperty_getIsPropertyOfValue", [ct.c_int64],
                                                                 ct.c_int64)

    # int PhysicalProperty_delete(PhysicalProperty* property);
    physical_property_delete = utils.load_func("PhysicalProperty_delete", [ct.c_int64], ct.c_int)

    #################################################################
    # PhysicalEntity methods
    #

    # PhysicalEntity *PhysicalEntity_identity(
    #        PhysicalEntity *physical_entity_ptr, const char *identity_resource);
    physical_entity_identity = utils.load_func("PhysicalEntity_identity", [ct.c_int64, ct.c_char_p], ct.c_int64)

    # char *PhysicalEntity_getIdentity(PhysicalEntity *physical_entity_ptr);
    physical_entity_get_identity = utils.load_func("PhysicalEntity_getIdentity", [ct.c_int64], ct.c_int64)

    # int PhysicalEntity_getNumLocations(PhysicalEntity *physicalEntity);
    physical_entity_get_num_locations = utils.load_func("PhysicalEntity_getNumLocations", [ct.c_int64],
                                                        ct.c_int)

    # char *PhysicalEntity_getLocation(PhysicalEntity *physical_entity_ptr, int index);
    physical_entity_get_location = utils.load_func("PhysicalEntity_getLocation", [ct.c_int64, ct.c_int64], ct.c_int64)

    # PhysicalEntity *PhysicalEntity_hasProperty(PhysicalEntity *physical_entity_ptr, PhysicalProperty* property);
    physical_entity_has_property = utils.load_func("PhysicalEntity_hasProperty", [ct.c_int64, ct.c_int64], ct.c_int64)

    # PhysicalEntity *PhysicalEntity_hasPropertyisVersionOf(PhysicalEntity *physical_entity_ptr, const char* isVersionOf) ;
    physical_entity_has_property_is_version_of = utils.load_func("PhysicalEntity_hasPropertyisVersionOf",
                                                                 [ct.c_int64, ct.c_char_p], ct.c_int64)

    # PhysicalEntity *PhysicalEntity_hasPropertyFull(PhysicalEntity *physical_entity_ptr, const char* property_about, eUriType about_uri_type, const char* is_version_of) ;
    physical_entity_has_property_full = utils.load_func("PhysicalEntity_hasPropertyFull",
                                                        [ct.c_int64, ct.c_char_p, ct.c_int64, ct.c_char_p], ct.c_int64)

    # int PhysicalEntity_delete(PhysicalEntity *physical_entity_ptr);
    physical_entity_delete = utils.load_func("PhysicalEntity_delete", [ct.c_int64], ct.c_int)

    # PhysicalEntity *PhysicalEntity_about(PhysicalEntity *physical_entity_ptr, const char *about, eUriType type) {
    physical_entity_about = utils.load_func("PhysicalEntity_about", [ct.c_int64, ct.c_char_p, ct.c_int64], ct.c_int64)

    # PhysicalEntity *PhysicalEntity_isPartOf(PhysicalEntity *physical_entity_ptr, const char *is_part_of, eUriType type);
    physical_entity_is_part_of = utils.load_func("PhysicalEntity_isPartOf", [ct.c_int64, ct.c_char_p, ct.c_int64],
                                                 ct.c_int64)

    # PhysicalEntity *PhysicalEntity_hasPart(PhysicalEntity *physical_entity_ptr, const char *part);
    physical_entity_has_part = utils.load_func("PhysicalEntity_hasPart", [ct.c_int64, ct.c_char_p], ct.c_int64)

    #################################################################
    # PhysicalProcess methods
    #

    # PhysicalProcess *
    # PhysicalProcess_addSource(PhysicalProcess *physical_process,
    #                          const char *physical_entity_reference, eUriType type, double multiplier)
    physical_process_add_source = utils.load_func("PhysicalProcess_addSource",
                                                  [ct.c_int64, ct.c_char_p, ct.c_int64, ct.c_double], ct.c_int64)

    # PhysicalProcess *
    # PhysicalProcess_addSink(PhysicalProcess *physical_process,
    #                        const char *physical_entity_reference, eUriType type, double multiplier)
    physical_process_add_sink = utils.load_func("PhysicalProcess_addSink",
                                                [ct.c_int64, ct.c_char_p, ct.c_int64, ct.c_double], ct.c_int64)

    #     PhysicalProcess *
    #     PhysicalProcess_addMediator(PhysicalProcess *physical_process,
    #                                 const char *physical_entity_reference, eUriType type)
    physical_process_add_mediator = utils.load_func("PhysicalProcess_addMediator",
                                                    [ct.c_int64, ct.c_char_p, ct.c_int64], ct.c_int64)

    # PhysicalProcess *PhysicalProcess_isVersionOf(PhysicalProcess *physical_process_ptr, const char *version, eUriType type){
    physical_process_is_version_of = utils.load_func("PhysicalProcess_isVersionOf",
                                                     [ct.c_int64, ct.c_char_p, ct.c_int64], ct.c_int64)

    # PhysicalProcess *PhysicalProcess_hasProperty(PhysicalProcess *physical_entity_ptr, PhysicalProperty* property);
    physical_process_has_property = utils.load_func("PhysicalProcess_hasProperty", [ct.c_int64], ct.c_int64)

    # PhysicalProcess *PhysicalProcess_hasPropertyisVersionOf(PhysicalProcess *physical_process_ptr, const char* isVersionOf) ;
    physical_process_has_property_is_version_of = utils.load_func("PhysicalProcess_hasPropertyisVersionOf",
                                                                  [ct.c_int64, ct.c_char_p], ct.c_int64)

    # PhysicalProcess *PhysicalProcess_hasPropertyFull(PhysicalProcess *physical_process_ptr, const char* property_about, eUriType about_uri_type, const char* is_version_of) ;
    physical_process_has_property_full = utils.load_func("PhysicalProcess_hasPropertyFull",
                                                         [ct.c_int64, ct.c_char_p, ct.c_int64, ct.c_char_p], ct.c_int64)

    # int PhysicalProcess_delete(PhysicalProcess *physicalProcess);
    physical_process_delete = utils.load_func("PhysicalProcess_delete", [ct.c_int64], ct.c_int)

    # PhysicalProcess *PhysicalProcess_about(PhysicalProcess *physical_process_ptr, const char *about, eUriType type);
    physical_process_about = utils.load_func("PhysicalProcess_about", [ct.c_int64, ct.c_char_p, ct.c_int64], ct.c_int64)

    #################################################################
    # EnergyDiff Methods
    #

    # EnergyDiff *EnergyDiff_setPhysicalProperty(
    #         EnergyDiff *energy_diff_ptr, const char *subject_metaid, const char *physical_property);
    energy_diff_set_physical_property = utils.load_func("EnergyDiff_setPhysicalProperty",
                                                        [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_int64)

    #    EnergyDiff *EnergyDiff_addSource(EnergyDiff *energy_diff_ptr,
    #                                        const char *physical_entity_reference, eUriType type)
    energy_diff_add_source = utils.load_func("EnergyDiff_addSource",
                                             [ct.c_int64, ct.c_char_p, ct.c_int64], ct.c_int64)

    #    EnergyDiff *EnergyDiff_addSink(EnergyDiff *energy_diff_ptr,
    #                                      const char *physical_entity_reference, eUriType type) {
    energy_diff_add_sink = utils.load_func("EnergyDiff_addSink",
                                           [ct.c_int64, ct.c_char_p, ct.c_int64], ct.c_int64)

    # EnergyDiff *EnergyDiff_hasProperty(EnergyDiff *physical_entity_ptr, PhysicalProperty* property);
    energy_diff_has_property = utils.load_func("EnergyDiff_hasProperty", [ct.c_int64], ct.c_int64)

    # EnergyDiff *EnergyDiff_hasPropertyisVersionOf(EnergyDiff *physical_process_ptr, const char* isVersionOf) ;
    energy_diff_has_property_is_version_of = utils.load_func("EnergyDiff_hasPropertyisVersionOf",
                                                             [ct.c_int64, ct.c_char_p], ct.c_int64)

    # EnergyDiff *EnergyDiff_hasPropertyFull(EnergyDiff *physical_process_ptr, const char* property_about, eUriType about_uri_type, const char* is_version_of) ;
    energy_diff_has_property_full = utils.load_func("EnergyDiff_hasPropertyFull",
                                                    [ct.c_int64, ct.c_char_p, ct.c_int64, ct.c_char_p], ct.c_int64)

    # int EnergyDiff_delete(EnergyDiff *physicalForce);
    energy_diff_delete = utils.load_func("EnergyDiff_delete", [ct.c_int64], ct.c_int)

    # EnergyDiff *EnergyDiff_about(EnergyDiff *energy_diff_ptr, const char *about, eUriType type);
    energy_diff_about = utils.load_func("EnergyDiff_about", [ct.c_int64, ct.c_char_p, ct.c_int64], ct.c_int64)

    #################################################################
    # PersonalInformation Methods
    #

    # PersonalInformation *Editor_newPersonalInformation(Editor *editor_ptr);
    editor_new_personal_information = utils.load_func("Editor_newPersonalInformation", [ct.c_int64], ct.c_int64)

    # char *PersonalInformation_getLocalUri(PersonalInformation *information);
    personal_information_get_local_uri = utils.load_func("PersonalInformation_getLocalUri", [ct.c_int64], ct.c_int64)

    # PersonalInformation *PersonalInformation_addCreator(PersonalInformation *information, const char *value);
    personal_information_add_creator = utils.load_func("PersonalInformation_addCreator", [ct.c_int64, ct.c_char_p],
                                                       ct.c_int64)

    # PersonalInformation *PersonalInformation_addName(PersonalInformation *information, const char *value);
    personal_information_add_name = utils.load_func("PersonalInformation_addName", [ct.c_int64, ct.c_char_p],
                                                    ct.c_int64)

    # PersonalInformation *PersonalInformation_addMbox(PersonalInformation *information, const char *value);
    personal_information_add_mbox = utils.load_func("PersonalInformation_addMbox", [ct.c_int64, ct.c_char_p],
                                                    ct.c_int64)

    # PersonalInformation *PersonalInformation_addAccountName(PersonalInformation *information, const char *value);
    personal_information_add_account_name = utils.load_func("PersonalInformation_addAccountName",
                                                            [ct.c_int64, ct.c_char_p],
                                                            ct.c_int64)

    # PersonalInformation *PersonalInformation_addAccountServiceHomepage(PersonalInformation *information, const char *value);
    personal_information_add_account_service_homepage = utils.load_func("PersonalInformation_addAccountServiceHomepage",
                                                                        [ct.c_int64, ct.c_char_p], ct.c_int64)

    # PersonalInformation *PersonalInformation_addFoafBlank(PersonalInformation *information, const char *predicate, const char *blank_value);
    personal_information_add_foaf_blank = utils.load_func("PersonalInformation_addFoafBlank",
                                                          [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_int64)

    # PersonalInformation *PersonalInformation_addFoafUri(PersonalInformation *information, const char *predicate, const char *uri_value);
    personal_information_add_foaf_uri = utils.load_func("PersonalInformation_addFoafUri",
                                                        [ct.c_int64, ct.c_char_p, ct.c_char_p],
                                                        ct.c_int64)

    # PersonalInformation *PersonalInformation_addFoafLiteral(PersonalInformation *information, const char *predicate,const char *literal_value);
    personal_information_add_foaf_literal = utils.load_func("PersonalInformation_addFoafLiteral",
                                                            [ct.c_int64, ct.c_char_p, ct.c_char_p], ct.c_int64)

    # char *PersonalInformation_getMetaid(PersonalInformation *information);
    personal_information_get_metaid = utils.load_func("PersonalInformation_getMetaid", [ct.c_int64], ct.c_int64)

    # int PersonalInformation_setMetaid(PersonalInformation *information, const char *metaid);
    personal_information_set_metaid = utils.load_func("PersonalInformation_setMetaid", [ct.c_int64, ct.c_char_p],
                                                      ct.c_int)

    # int PersonalInformation_delete(PersonalInformation* information);
    personal_information_delete = utils.load_func("PersonalInformation_delete", [ct.c_int64], ct.c_int)

    #################################################
    #   Auxillary functions
    #

    # int StringVector_getSize(std::vector<std::string>* vec);
    string_vector_get_size = utils.load_func("StringVector_getSize", [ct.c_int64], ct.c_int64)

    # char* StringVector_getElementAtIdx(std::vector<std::string>* vec, int idx);
    string_vector_get_element_at_idx = utils.load_func("StringVector_getElementAtIdx", [ct.c_int64, ct.c_int64],
                                                       ct.c_int64)

    # void StringVector_delete(std::vector<std::string> *strVec);
    string_vector_delete = utils.load_func("StringVector_delete", [ct.c_int64], ct.c_void_p)

    # int ResultsMap_getSize(ResultsMap* resultsMap);
    results_map_get_size = utils.load_func("ResultsMap_getSize", [ct.c_int64], ct.c_int64)

    # std::vector<std::string>* ResultsMap_getStringVectorAt(ResultsMap* resultsMap, const char* key);
    results_map_get_string_vector_at = utils.load_func("ResultsMap_getStringVectorAt", [ct.c_int64, ct.c_char_p],
                                                       ct.c_int64)

    # std::vector<std::string>* ResultsMap_getKeys(ResultsMap* resultsMap);
    results_map_get_keys = utils.load_func("ResultsMap_getKeys", [ct.c_int64], ct.c_int64)

    # void ResultsMap_delete(ResultsMap * resultsMap);
    results_map_delete = utils.load_func("ResultsMap_delete", [ct.c_int64], ct.c_void_p)

    # Logger API
    # Note - you'll need to initialise the logger by calling logger_get_logger once at the start
    # of the program, if you are using the raw pyomexmeta api directly. If using the front facing
    # pyomexmeta api then the initialization is handled in the constructor for RDF.

    # Logger *Logger_getLogger()
    logger_get_logger = utils.load_func("Logger_getLogger", [], ct.c_int64)

    # void Logger_setFormatter(const char* format)
    logger_set_formatter = utils.load_func("Logger_setFormatter", [ct.c_char_p], ct.c_void_p)

    # void Logger_setLevel(Logger::LogLevel level)
    logger_set_level = utils.load_func("Logger_setLevel", [ct.c_int64], ct.c_void_p)

    # Logger::LogLevel Logger_getLevel()
    logger_get_level = utils.load_func("Logger_getLevel", [], ct.c_int64)

    # void Logger_enableBacktrace(int num)
    logger_enable_backtrace = utils.load_func("Logger_enableBacktrace", [ct.c_int64], ct.c_void_p)

    # void Logger_disableBacktrace()
    logger_disable_backtrace = utils.load_func("Logger_disableBacktrace", [], ct.c_void_p)

    # void Logger_dumpBacktrace();
    logger_dump_backtrace = utils.load_func("Logger_dumpBacktrace", [], ct.c_void_p)

    # void Logger_consoleLogger()
    logger_console_logger = utils.load_func("Logger_consoleLogger", [], ct.c_void_p)

    # void Logger_fileLogger(const char*filename)
    logger_file_logger = utils.load_func("Logger_fileLogger", [ct.c_char_p], ct.c_void_p)

    # void Logger_info(const char* message)
    logger_info = utils.load_func("Logger_info", [ct.c_char_p], ct.c_void_p)

    # void Logger_trace(const char* message)
    logger_trace = utils.load_func("Logger_trace", [ct.c_char_p], ct.c_void_p)

    # void Logger_debug(const char* message)
    logger_debug = utils.load_func("Logger_debug", [ct.c_char_p], ct.c_void_p)

    # void Logger_warn(const char* message)
    logger_warn = utils.load_func("Logger_warn", [ct.c_char_p], ct.c_void_p)

    # void Logger_error(const char* message)
    logger_error = utils.load_func("Logger_error", [ct.c_char_p], ct.c_void_p)

    # void Logger_critical(const char* message)
    logger_critical = utils.load_func("Logger_critical", [ct.c_char_p], ct.c_void_p)

    #  void Logger_clear();
    logger_clear = utils.load_func("Logger_clear", [], ct.c_void_p)

    #  int Logger_size();
    logger_size = utils.load_func("Logger_size", [], ct.c_int64)

    #  Message *Logger_getMessageI(int idx);
    logger_get_message_i = utils.load_func("Logger_getMessageI", [ct.c_int64], ct.c_int64)

    # void Logger_flush();
    logger_flush = utils.load_func("Logger_flush", [], ct.c_void_p)

    # void Logger_flushOn(int level);
    logger_flush_on = utils.load_func("Logger_flushOn", [ct.c_int64], ct.c_void_p)

    #  int Message_getLevel(Message *message);
    message_get_level = utils.load_func("Message_getLevel", [ct.c_int64], ct.c_int64)

    # char *Message_getMessage(Message *message);
    message_get_message = utils.load_func("Message_getMessage", [ct.c_int64], ct.c_int64)

    # void Message_deleteMessage(Message *message);
    message_delete_message = utils.load_func("Message_deleteMessage", [ct.c_int64], ct.c_void_p)
