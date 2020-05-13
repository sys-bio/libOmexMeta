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


class RDF:

    def __init__(self):
        RDF_new_cfunc = Util.load_func(libsemsim, "RDF_new_ptr", [], ct.c_int64)

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

    @staticmethod
    def from_string(rdf_string: str, format: str = "guess") -> RDF:
        rdf = RDF()
        rdf._rdf_from_string_cfunc(rdf._obj, rdf_string.encode(), format.encode())
        return rdf

    def to_string(self, format: str = "rdfxml-abbrev", base_uri: str = "annotations.rdf") -> str:
        return self._rdf_to_string_cfunc(self._obj, format.encode(), base_uri.encode())

    def __del__(self):
        """destructor. Delete the dynamically allocated rdf object"""
        self._rdf_free_cfunc(self._obj)

    def __len__(self):
        """Returns the number of individual Triples stored in the rdf model"""
        return self._rdf_size_cfunc(self._obj)

    def get_base_uri(self) -> str:
        return self._rdf_getBaseUri_cfunc(self._obj).decode()

    def set_base_uri(self, uri: str) -> None:
        if not os.path.isfile(uri):
            uri = os.path.join(os.path.realpath(os.getcwd()), uri)
        self._rdf_setBaseUri_cfunc(self._obj, uri.encode())

    def query(self, query_str, results_format) -> str:
        results_crlf = self._rdf_queryResultsAsStr_cfunc(self._obj, query_str.encode(), results_format.encode()).decode(
            "utf-8")
        results_lf = Util.crlf_to_lr(results_crlf)
        return results_lf
