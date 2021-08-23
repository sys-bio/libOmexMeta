from __future__ import annotations

import ctypes as ct
import os
import sys
from contextlib import contextmanager
from sys import executable as _python_interpretor
from typing import List
from functools import wraps

try:
    # for use from outside the package, as a python package
    from .pyomexmeta_api import PyOmexMetaAPI, eUriType, eXmlType, eLogLevel, OmexMetaException
except ImportError:
    try:  # for internal use
        from pyomexmeta_api import PyOmexMetaAPI, eUriType, eXmlType, eLogLevel, OmexMetaException
    except ImportError:
        # for internal use
        from . import pyomexmeta_api, eUriType, eXmlType, eLogLevel, OmexMetaException

_pyom = PyOmexMetaAPI()

# expose get_last_error at top level so easily importable to other modules
_get_last_error = _pyom.get_last_error


def propagate_omexmeta_error(func):
    """
    If @param func is a callable then this
    function behaves like a decorator, checking
    the return type for a omexmeta error. This is used in simpler functions
    (of which there are many) that only call a omexmeta method.

    If @param func is not callable, then we check
    to see whether func is nullptr or < 0, indicative
    of a omexmeta error. This is used in more complicated
    situations

    Args:
        func: callable or value.

    Returns: a func of @param is callable or the original value if not.

    todo split into two functions (voilation of SRP).
        - check_for_error_value
        - check_for_error_return (for decorator)

    """
    if callable(func):

        @wraps(func)
        def raise_error_if_necessary(*args, **kwargs):
            failed = func(*args, **kwargs)
            if failed is None:
                err = _pyom.get_last_error()
                _pyom.clear_last_error()
                raise OmexMetaException(err)
            if isinstance(failed, int):
                if failed < 0:
                    err = _pyom.get_last_error()
                    _pyom.clear_last_error()
                    raise OmexMetaException(err)
            return failed

        return raise_error_if_necessary
    else:
        value = func
        if value is None:
            err = _pyom.get_last_error()
            _pyom.clear_last_error()
            raise OmexMetaException(err)
    if isinstance(func, int):
        if func < 0:
            err = _pyom.get_last_error()
            _pyom.clear_last_error()
            raise OmexMetaException(err)
    return func


class RDF:

    def __init__(self, storage_type: str = "memory", storage_name: str = "libOmexMetaStore",
                 storage_options: str = None, model_options: str = None, rdf_ptr: ct.c_int64 = None):
        """Create an :class:`RDF` empty graph.

        This is a central object in libOmexMeta and pyomexmeta from which
        all annotations are created, stored, read, written and queried. Arguments to :class:`RDF` are passed on
        to the redland libraries and affect how the :class:`RDF` graph is stored. The default
        is to store the :class:`RDF` graph in memory.

        Args:
            storage_type: memory (default), hashes, file, uri or sqlite. See https://librdf.org/docs/api/redland-storage-modules.html
            storage_name: An arbitrary name for your storage. Not important when storage_type is memory but will be the
                          name of a `file` or database if `storage_type` is on disk
            storage_options: Options forwarded onto the redland libraries backend. Unfortunately, the redland library
                             docs are not brilliant at describing these options and so neither are we. Please see https://librdf.org/docs/api/redland-storage.html
            model_options:   Options that are forwarded onto the redland libraries librdf_model* object. Similar to `storage_options` these
                             are not described in great detail in the redland lib docs. Please see `https://librdf.org/docs/api/redland-model.html#librdf-new-model`
            rdf_ptr:         A pointer (or memory address), stored as ctypes c_int64, that points to a preexisting instance
                             of an :class:`RDF` in memory. todo consider whether to remove this option in favour of using only :class:`RDF`._set_rdf_ptr.

        .. code-block: python
            :linenos:

            # create an empty :class:`RDF` graph in memory
            rdf = RDF()
            # create a new sqlite database storage called MyFavouriteAnnotations
            RDF("sqlite", "MyFavouriteAnnotations", "new='yes'")

        """
        # when pointer argument not given by user, create new instance of :class:`RDF`
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

    @propagate_omexmeta_error
    def __len__(self) -> int:
        """Returns the number of individual Triples stored in the rdf model"""
        return _pyom.rdf_size(self._obj)

    def __str__(self) -> str:
        """Defaults to rdfxml-abbrev syntax"""
        return self.to_string("turtle")

    def __del__(self) -> None:
        """deletes the :class:`RDF` instance"""
        self.delete()

    def _set_rdf_ptr(self, ptr: ct.c_int64) -> None:
        """Change the :class:`RDF` pointer to ptr
        Args:
            ptr: a pointer to the C generated :class:`RDF` object.

        Returns: None

        """
        # first remove the existing pointer
        self.delete()
        # then do the switch
        self._obj = ptr

    @staticmethod
    def from_string(rdf_string: str, syntax: str = "guess",
                    storage_type: str = "hashes", storage_name: str = "pyomexmeta_storage", storage_options: str = None,
                    model_options: str = None) -> RDF:
        """Read RDF from a string and create an :class:`RDF` object with it.

        This is a static method, i.e. it should be used without an instantiated instance of :class:`RDF`.

        Args:
            rdf_string:     The rdf string to parse. It can be in any supported syntax.
            syntax:         `guess` is default which will try to make an educated guess
                            as to what syntax is contained in `rdf_string`. However, sometimes
                            the syntax cannot be identified and this will need to be specified
                            manually. Other options are rdfxml, ntriples, turtle, nquads, guess.
                            Note: the easiest way to get a list of available syntax options is to
                            run your program with deliberately the wrong `syntax` argument
            storage_type:    See :meth:`RDF.__init__`
            storage_name:    See :meth:`RDF.__init__`
            storage_options: See :meth:`RDF.__init__`
            model_options:   See :meth:`RDF.__init__`

        Returns: An :class:`RDF` object that contains the RDF graph described by rdf_string.

        Examples:
            >>> rdf_string = "RDF string encoded in turtle syntax"
            >>> rdf = RDF.from_string(rdf_string, "turtle")

        See Also:
            :meth:`RDF.add_from_string`

        """
        rdf_ptr = _pyom.rdf_from_string(
            rdf_string.encode(), syntax.encode(),
            storage_type.encode(), storage_name.encode(),
            None if not storage_options else storage_options.encode(),
            None if not storage_options else model_options.encode()
        )

        propagate_omexmeta_error(rdf_ptr)
        rdf = RDF()
        rdf._set_rdf_ptr(rdf_ptr)
        return rdf

    @propagate_omexmeta_error
    def add_from_string(self, rdf_string: str, syntax: str = "guess") -> None:
        """Add annotations to the existing :class:`RDF` graph (self) from `rdf_string`

        Args:
            rdf_string: The string containing the annotations that you want to add to the current :class:`RDF` graph
            syntax:     The syntax used by `rdf_string` (default=`guess`). 
                        Other options are rdfxml, ntriples, turtle, nquads, guess. 

        Returns: None

        Examples:
            >>> rdf = RDF()
            >>> rdf.add_from_string("insert rdf string here")

        """
        return _pyom.rdf_add_from_string(self._obj, rdf_string.encode(), syntax.encode())

    @staticmethod
    def from_uri(uri_string: str, syntax: str = "guess", storage_type: str = "hashes",
                 storage_name: str = "pyomexmeta_storage",
                 storage_options: str = None,
                 model_options: str = None) -> RDF:
        """ Create an :class:`RDF` object from content in a URI.

        This is a static method i.e. called without an instance of :class:`RDF`.
        
        Args:
            uri_string: The uri from which to download an :class:`RDF` graph from.
            syntax:     The syntax of the graph pointed to by uri_string.
            storage_type:   See :meth:`RDF.__init__`
            storage_name:   See :meth:`RDF.__init__`
            storage_options:See :meth:`RDF.__init__`
            model_options:  See :meth:`RDF.__init__`

        Returns: :class:`RDF`

        Examples:
            >>> rdf = RDF.from_uri("http://myrdfgraph.org/rdfspecial")

        """
        rdf_ptr = _pyom.rdf_from_uri(
            uri_string.encode(), syntax.encode(),
            storage_type.encode(), storage_name.encode(),
            None if not storage_options else storage_options.encode(),
            None if not model_options else model_options.encode()
        )
        propagate_omexmeta_error(rdf_ptr)
        rdf = RDF()
        rdf._set_rdf_ptr(rdf_ptr)
        return rdf

    @propagate_omexmeta_error
    def add_from_uri(self, uri_string: str, syntax: str = "guess") -> None:
        """Add RDF from a uri to an existing :class:`RDF` graph

        Args:
            uri_string: The uri from which to download rdf from
            syntax:     The syntax of the rdf content pointed to by uri_string

        Returns: None

        """
        return _pyom.rdf_add_from_uri(self._obj, uri_string.encode(), syntax.encode())

    @staticmethod
    def from_file(filename: str, syntax: str = "guess", storage_type: str = "hashes",
                  storage_name: str = "pyomexmeta_storage",
                  storage_options: str = None, model_options: str = None) -> RDF:
        """Create an :class:`RDF` graph from a file on disk.

        This is a static method and is therefore called without an instance of :class:`RDF` (see example)

        Args:
            filename:       The location on disk of the file containing rdf for parsing
            syntax:         The syntax for the rdf content in `filename`. See :class:`RDF`.
            storage_type:   See :meth:`RDF.__init__`
            storage_name:   See :meth:`RDF.__init__`
            storage_options:See :meth:`RDF.__init__`
            model_options:  See :meth:`RDF.__init__`

        Returns:

        Examples:
            >>> rdf = RDF.from_file("/path/to/rdf_file.rdf", "turtle")

        See Also:
            :meth:`RDF.add_from_file`

        """
        rdf_ptr = _pyom.rdf_from_file(
            filename.encode(), syntax.encode(),
            storage_type.encode(), storage_name.encode(),
            None if not storage_options else storage_options.encode(),
            None if not storage_options else model_options.encode()
        )
        propagate_omexmeta_error(rdf_ptr)
        rdf = RDF()
        rdf._set_rdf_ptr(rdf_ptr)
        return rdf

    @staticmethod
    @propagate_omexmeta_error
    def equals_rdf_vs_rdf(first_rdf: RDF, second_rdf: RDF, syntax: str = "turtle", verbose: bool = False) -> bool:
        """Equality operator for comparing :class:`RDF` objects.

        This is the "default" equality operator used by :meth:`RDF.__eq__`. `first_rdf`
        and `second_rdf` are considered equal if all triples contained in each are identical.
        The only exception is regarding blank nodes, which are considered equal even if their
        label is different. For developers: this condition for blank nodes was necessary, because
        they are usually automatically assigned random labels when reading from an rdf graph.

        This method is static - it does not require an instance of :class:`RDF` to use. See Examples.

        Args:
            first_rdf:  Left operand to equality operator
            second_rdf: Right operand to equality operator
            syntax:     When verbose is True, use this syntax for displaying the two different gaphs
            verbose:    When True, output both left and right operands as a string to console encoded as `syntax`

        Returns: bool

        .. code-block: python
            :linenos:

            rdf1 = RDF.from_string("first rdf string")
            rdf2 = RDF.from_string("second rdf string")
            if RDF.equals_rdf_vs_rdf(rdf1, rdf2):
                print("rdf1 and rdf2 are equivalent RDF graphs")

        See Also:
            :meth:`equals_rdf_vs_string`
            :meth:`equals_string_vs_string`

        """
        return _pyom.rdf_equals_rdf_vs_rdf(first_rdf._obj, second_rdf._obj, syntax.encode(), verbose)

    @staticmethod
    @propagate_omexmeta_error
    def equals_rdf_vs_string(rdf: RDF, string: str, syntax: str = "turtle", verbose: bool = False) -> bool:
        """Equality operator comparing an RDF graph (left operand) to a serialized RDF graph encoded in `syntax`

        This method is the same as :meth:`equals_rdf_vs_rdf` excapt that the second
        argument `string` is not an instance of :class:`RDF` but a str.

        Args:
            rdf:     The :class:`RDF` object to compare with `string`. Left operand.
            string:  An rdf graph encoded in `syntax` to compare with `rdf`. Right operand.
            syntax:  Syntax for right operand, `string`. This syntax is also used for displaying
                     left and right operands to console when verbose is True
            verbose: Display left and right operands using `syntax` for inspection.

        Returns: bool

        .. code-block: python
            :linenos:

            rdf1 = RDF.from_string("first rdf string")
            rdf_string = "second rdf string"
            if RDF.equals_rdf_vs_string(rdf1, rdf_string):
                print("rdf1 and rdf_string are equivalent RDF graphs")

        See Also:
            :meth:`equals_rdf_vs_rdf`
            :meth:`equals_string_vs_string`

        """
        return _pyom.rdf_equals_rdf_vs_string(rdf._obj, string.encode(), syntax.encode(), verbose)

    @staticmethod
    @propagate_omexmeta_error
    def equals_string_vs_string(first_string: str, second_string: str, first_syntax: str = "turtle",
                                second_syntax: str = "turtle", verbose: bool = False) -> bool:
        """Equality operator comparing two rdf graphs both of which are serialized to strings.

        This method is the same as :meth:`equals_rdf_vs_rdf` except that both
        left and right operands are strings, encoded in `first_syntax` and `second_syntax`
        respectively.

        Args:
            first_string:   The rdf graph for the left operand, encoded in `first_syntax`
            second_string:  The rdf graph for the right operand, encoded in `second_syntax`
            first_syntax:   The syntax used by `first_string`
            second_syntax:  The syntax used by `second_string`
            verbose:        When True, print out rdf graphs encoded by `first_string` and
                            `second_string` to console using `first_syntax` and `second_syntax`
                            respectively.


        Returns: bool


        .. code-block: python
            :linenos:

            rdf_string1 = "first rdf string"
            rdf_string2 = "second rdf string"
            if RDF.equals_string_vs_string(rdf_string1, rdf_string2):
               print("rdf_string1 and rdf_string2 are equivalent RDF graphs")

        See Also:
            :meth:`equals_rdf_vs_rdf`
            :meth:`equals_rdf_vs_string`

        """
        return _pyom.rdf_equals_string_vs_string(first_string.encode(), second_string.encode(), first_syntax,
                                                 second_syntax.encode(), verbose)

    @propagate_omexmeta_error
    def __eq__(self, other: RDF):
        """Equality operator for :class:`RDF`"""
        return self.equals_rdf_vs_rdf(self, other)

    @propagate_omexmeta_error
    def __ne__(self, other: RDF):
        """Inequality operator for :class:`RDF`"""
        return not self == other

    @propagate_omexmeta_error
    def add_from_file(self, filename: str, syntax: str) -> None:
        """Add to this existing :class:`RDF` class from RDF serialized as `syntax`
        in `filename`

        Args:
            filename: Location of the file on disk containing RDF to add to existing RDF graph
            syntax:   The syntax used by `filename` for storing RDF.

        Returns: None

        Examples:
            >>> rdf = RDF.from_file("annot.rdf") # read from file on disk into new RDF graph
            >>> rdf.add_from_file("another_annot.rdf") # add to the existing rdf graph

        See Also:
            :meth:`RDF.from_string`
            :meth:`RDF.add_from_string`
            :meth:`RDF.from_file`

        """
        return _pyom.rdf_add_from_file(self._obj, filename.encode(), syntax.encode())

    def delete(self) -> None:
        """destructor. Delete the dynamically allocated rdf object"""
        return _pyom.rdf_delete(self._obj)

    def to_string(self, syntax: str = "turtle") -> str:
        """Serialize this :class":`RDF` graph using `syntax` syntax.

        This method is used by :meth:`RDF.__str__` for printing an RDF graph
        as default "turtle" syntax

        Args:
            syntax: The syntax to use for serializing content contained in this :class:`RDF` graph.
                    Options are ntriples, turtle, rdfxml-abbrev, rdfxml, dot,
                    json-triples, json, nquads, html

                .. note:

                    Deliberately run your program with the wrong string arg to be presented
                    with a list of valid syntaxes.

        Returns:
            (str) serialized RDF graph as string.

        Examples:
            >>> rdf = RDF.from_file("annot.rdf", "rdfxml")
            >>> rdf.to_string("turtle")

        See Also:
            :meth:`RDF.__str__`

        """
        str_ptr = _pyom.rdf_to_string(self._obj, syntax.encode())
        propagate_omexmeta_error(str_ptr)
        thestring = _pyom.get_and_free_c_str(str_ptr)
        return thestring

    @propagate_omexmeta_error
    def to_file(self, filename: str, syntax: str, ) -> None:
        """Serialize the annotations contained in this :meth:`RDF` graph to a file on disk

        Args:
            filename: A valid location on disk. Location for storing :class:`RDF` graph.
            syntax:   Which syntax to use for serialization of :class:`RDF` graph

        Returns: None

        """
        return _pyom.rdf_to_file(self._obj, syntax.encode(), filename.encode())

    @propagate_omexmeta_error
    def set_repository_uri(self, repository_uri: str) -> None:
        """Set the respository uri.

        This is used to construct the local and model uri's.

        Args:
            repository_uri: (str) uri to use for replacing the default
                            respository uri (http://omex-library.org/)
        Examples:
            >>> rdf = RDF.from_file("annot.rdf")
            >>> rdf.set_repository_uri("https://Repositorious.org")
            >>> rdf.set_archive_uri("Arch.omex")
            >>> rdf.set_model_uri("SignallingNetwork.sbml")
            >>> rdf.get_model_uri()
            https://Repositorious.org/Arch.omex/SignallingNetwork.sbml
            >>> rdf.get_local_uri()
            https://Repositorious.org/Arch.omex/SignallingNetwork.rdf
        """
        return _pyom.rdf_set_repository_uri(self._obj, repository_uri.encode())

    @propagate_omexmeta_error
    def set_archive_uri(self, archive_url: str) -> None:
        """Set the "archive" portion of model and local uri's.

        Args:
            archive_url: (str) default is "NewOmex.omex". String to use for replacement.

        Returns: None

        Examples:
            >>> rdf = RDF.from_file("annot.rdf")
            >>> rdf.set_repository_uri("https://Repositorious.org")
            >>> rdf.set_archive_uri("Arch.omex")
            >>> rdf.set_model_uri("SignallingNetwork.sbml")
            >>> rdf.get_model_uri()
            https://Repositorious.org/Arch.omex/SignallingNetwork.sbml
            >>> rdf.get_local_uri()
            https://Repositorious.org/Arch.omex/SignallingNetwork.rdf

        """
        return _pyom.rdf_set_archive_uri(self._obj, archive_url.encode())

    @propagate_omexmeta_error
    def set_model_uri(self, model_uri: str) -> None:
        """Sets the string used for model filename.

        This string is also used for the local portion of the local uri.

        Args:
            model_uri: (str) default is NewModel.xml. String to use for model uri.

        Returns: None

        Examples:
            >>> rdf = RDF.from_file("annot.rdf")
            >>> rdf.set_repository_uri("https://Repositorious.org")
            >>> rdf.set_archive_uri("Arch.omex")
            >>> rdf.set_model_uri("SignallingNetwork.sbml")
            >>> rdf.get_model_uri()
            https://Repositorious.org/Arch.omex/SignallingNetwork.sbml
            >>> rdf.get_local_uri()
            https://Repositorious.org/Arch.omex/SignallingNetwork.rdf

        """
        return _pyom.rdf_set_model_uri(self._obj, model_uri.encode())

    def get_model_metaid(self) -> str:
        """return the current string being used for the model elements metaid.

        This defaults to the string "NewModel" but is replaced with the metaid for the
        first "model" element it finds when an XML is opened in the :meth:`Editor`.

        See Also:
            :meth:`RDF.set_model_metaid`
            :meth:`RDF.get_model_level_annotation_uri`

        Examples:
            >>> rdf = RDF.from_file("annot.rdf")
            >>> rdf.get_model_metaid()
            NewModel
            >>> rdf.get_model_level_annotation_uri()
            http://omex-library.org/NewOmex.omex/NewModel.xml#NewModel
            >>> rdf.set_model_metaid("ModelMetaid")
            >>> rdf.get_model_metaid()
            ModelMetaid
            >>> rdf.get_model_level_annotation_uri()
            http://omex-library.org/NewOmex.omex/NewModel.xml#ModelMetaid

        Returns: str

        """
        return _pyom.get_and_free_c_str(_pyom.rdf_get_model_metaid(self._obj))

    def set_model_metaid(self, model_metaid: str) -> None:
        """Set the string to use for the model level annotation uri.

        Model level annotations should be placed on the ``model`` element that has a metaid.
        This method provides a way of changing which ``model`` element is annotated, in case
        there is more than one. The default is "NewModel" which gets changed to the name
        of the metaid of the first ``model`` element that is found, once an xml is loaded into
        the Editor class.

        Args:
            model_metaid: (str) a new name for a model metaid. It is the users responsibility to ensure this name is accurate.

        Examples:
            >>> rdf = RDF.from_file("annot.rdf")
            >>> rdf.get_model_metaid()
            NewModel
            >>> rdf.get_model_level_annotation_uri()
            http://omex-library.org/NewOmex.omex/NewModel.xml#NewModel
            >>> rdf.set_model_metaid("ModelMetaid")
            >>> rdf.get_model_metaid()
            ModelMetaid
            >>> rdf.get_model_level_annotation_uri()
            http://omex-library.org/NewOmex.omex/NewModel.xml#ModelMetaid

        Returns: None

        """
        return _pyom.rdf_set_model_metaid(self._obj, model_metaid.encode())

    def get_model_level_annotation_uri(self) -> str:
        """Returns the uri that is used for model level annotations as a string

        This string is the "model_uri" concatonated with the metaid for the "model" element.

        Returns: (str) the uri

        Examples:
            >>> rdf = RDF.from_file("annot.rdf")
            >>> rdf.get_model_metaid()
            NewModel
            >>> rdf.get_model_level_annotation_uri()
            http://omex-library.org/NewOmex.omex/NewModel.xml#NewModel
            >>> rdf.set_model_metaid("ModelMetaid")
            >>> rdf.get_model_metaid()
            ModelMetaid
            >>> rdf.get_model_level_annotation_uri()
            http://omex-library.org/NewOmex.omex/NewModel.xml#ModelMetaid

        """
        return _pyom.get_and_free_c_str(_pyom.rdf_get_model_level_annotation_uri(self._obj))

    def get_repository_uri(self) -> str:
        """Returns the string used for repository uri"""
        string_ptr = _pyom.rdf_get_repository_uri(self._obj)
        propagate_omexmeta_error(string_ptr)
        return _pyom.get_and_free_c_str(string_ptr)

    def get_archive_uri(self) -> str:
        """Returns the string used for archive (i.e. omex) uri"""
        string_ptr = _pyom.rdf_get_archive_uri(self._obj)
        propagate_omexmeta_error(string_ptr)
        return _pyom.get_and_free_c_str(string_ptr)

    def get_model_uri(self) -> str:
        """Returns the string used for model uri.

        This string also gets used for local uri
        """
        string_ptr = _pyom.rdf_get_model_uri(self._obj)
        propagate_omexmeta_error(string_ptr)
        return _pyom.get_and_free_c_str(string_ptr)

    def get_local_uri(self) -> str:
        """Returns the string used for local uri.

        This is set indirectly through the model_uri

        """
        string_ptr = _pyom.rdf_get_local_uri(self._obj)
        propagate_omexmeta_error(string_ptr)
        return _pyom.get_and_free_c_str(string_ptr)

    def query_results_as_string(self, query_str: str, results_syntax: str) -> str:
        """Query the :class:`RDF` using sparql.

        Returns the results as a string in the specified format.

        Args:
            query_str: (str) A SPAQRL query
            results_syntax: What syntax to use for the results?
                            Options are: xml, json, table, csv, mkr, tsv, html, turtle, rdfxml
                            If incorrect string given, options are presented to user.

        Returns: string. Results
        
        Examples:
            >>> rdf = RDF.from_file("annot.rdf") # read from file on disk
            >>> rdf.query_results_as_string("SELECT *?x ?y ?z WHERE { ?x ?y ?z }", results_syntax="csv") # selects everything

        See Also:
            query_results_as_dict

        """
        query_results_ptr = _pyom.rdf_query_results_as_str(
            self._obj, query_str.encode(), results_syntax.encode())
        propagate_omexmeta_error(query_results_ptr)
        results_crlf = _pyom.get_and_free_c_str(query_results_ptr)
        results_lf = _pyom.crlf_to_lr(results_crlf)
        return results_lf

    def query_results_as_dict(self, query_str: str) -> dict:
        """Query the :class:`RDF` using sparql

        Returns the results as a dict[variable_name] = list(results)

        Args:
            query_str: (str) A SPAQRL query

        Returns: dict

        Examples:
            >>> rdf = RDF.from_file("annot.rdf") # read from file on disk
            >>> rdf.query_results_as_dict("SELECT *?x ?y ?z WHERE { ?x ?y ?z }") # selects everything

        See Also:
            query_results_as_str

        """
        # Do the query, get the pointer to the map obj
        results_map_ptr = _pyom.rdf_query_results_as_map(self._obj, query_str.encode())
        propagate_omexmeta_error(results_map_ptr)

        # how many elements in the map?
        map_size = _pyom.results_map_get_size(results_map_ptr)
        propagate_omexmeta_error(map_size)

        # get the keys in the map
        map_keys = _pyom.results_map_get_keys(results_map_ptr)
        propagate_omexmeta_error(map_keys)

        results_dict = dict()

        # iterate over the number of elements in the map
        for i in range(map_size):
            # get the string value of key i
            key = _pyom.string_vector_get_element_at_idx(map_keys, i)
            propagate_omexmeta_error(key)
            key = _pyom.get_and_free_c_str(key)

            # assign new key in our results dict
            results_dict[key] = []

            # get the value of the string vector that is mapped to by key
            string_vector_at_key = _pyom.results_map_get_string_vector_at(results_map_ptr, key.encode())
            propagate_omexmeta_error(string_vector_at_key)

            # get the size of the string vector
            string_vector_size = _pyom.string_vector_get_size(string_vector_at_key)
            propagate_omexmeta_error(string_vector_size)

            # iterate over the string vector and pop the results into the results dict
            for i in range(string_vector_size):
                # collect the value of the element at position i as string
                val = _pyom.string_vector_get_element_at_idx(string_vector_at_key, i)
                propagate_omexmeta_error(val)
                val = _pyom.get_and_free_c_str(val)
                results_dict[key].append(val)

            # clean up heap memory
            _pyom.string_vector_delete(string_vector_at_key)
        _pyom.string_vector_delete(map_keys)
        _pyom.results_map_delete(results_map_ptr)
        return results_dict

    def to_editor(self, xml: str, generate_new_metaids: bool = False, sbml_semantic_extraction: bool = True) -> Editor:
        """Create an Editor object which is the interface for creating and removing annotations
        associated with a given xml.

        Args:
            xml: The xml string for annotation (creating/deleting/amending)
            generate_new_metaids: (bool) When True, if metaids are not available on xml elements, this flag automatically creates them
            sbml_semantic_extraction: When xml is an sbml string, this flag determines whether to automatically
                                      extract semantic information from the sbml. Does nothing if xml is not sbml.

        Returns: :class:`Editor`

        Examples:
            >>> rdf = RDF()
            >>> editor = rdf.to_editor("<insert sbml string here>", True, True)
            >>> editor.add_description("Insulin signalling network")

        See Also:
            :class:`Editor`

        """
        obj = _pyom.rdf_to_editor(
            self._obj, xml.encode(),
            generate_new_metaids,
            sbml_semantic_extraction,
        )
        propagate_omexmeta_error(obj)
        return Editor(obj)

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
                              f'with "[sudo apt][choco][brew] install graphviz" and then '
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
    """Primary interface for creating new, modifying existing or deleting annotations from an rdf graph """

    def __init__(self, editor_ptr: ct.c_int64):
        """Editor constructor.

        Most users should not use the constructor directly but instead use the
        creator method :meth:`RDF.to_editor`. This ensures that the necessary references
        to the parent RDF object (and existing namespaces etc) are properly passed
        to the :class:`Editor` class.

        Args:
            editor_ptr: A pointer (a ctypes c_int64) that points to an Editor object in memory

        See Also
            :meth:`RDF.to_editor`
        """
        self._obj = editor_ptr

    def __enter__(self):
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        self.delete()

    @propagate_omexmeta_error
    def add_namespace(self, namespace: str, prefix: str) -> None:
        """Add a new namespace to the RDF graph.

        Args:
            namespace: The full uri for the namespace
            prefix:  The prefix that may be used instead of the full uri

        Returns: None

        Examples:
            >>> rdf = RDF()
            >>> editor = rdf.to_editor("<insert xml here>")
            >>> editor.add_namespace("http://fantasticalNamespace", "fanta")

        """
        return _pyom.editor_add_namespace(self._obj, namespace, prefix)

    @propagate_omexmeta_error
    def add_singular_annotation(self, singular_annotation: SingularAnnotation) -> None:
        """Adds a SingularAnnotation, which represents a single Triple. The SingularAnnotation
        is added to the RDF graph that created this :class:`Editor` object.

        Users can add arbitrary singular annotations to an RDF graph.

        Users do not normally call this method themselves, because the preferred
        user interface is to use the context manager for :class:`SingularAnnotation`.
        If the context manager for :class:`SingularAnnotation` is not used to
        create the :class:`SingularAnnotation` object, then this method must be called
        to add the :class:`SingularAnnotation` object to the relevant :class:`RDF` object
        See Examples.

        Args:
            singular_annotation: An instance of SingularAnnotation to add to the model

        .. code-block: python
            :linenos:

            # Users should do the following. This implicitly calls the
            # :meth:`Editor.add_singular_annotation` after the `with` block has finished.
            rdf = RDF()
            editor = rdf.to_editor("<insert xml here>")
            with editor.new_singular_annotation() as singular_annotation:
               singular_annotation.about("SmadNuclearTransport") \
                    .predicate_from_uri("http://CaptainPredicate.org")\
                    .resource_literal("Literally a resource")

            # If the context manager is not used, you must manually call :meth:`Editor.add_singular_annotation`
            rdf = RDF()
            editor = rdf.to_editor("<insert xml here>")
            singular_annotation = editor.new_singular_annotation()
            singular_annotation.about("SmadNuclearTransport") \
                .predicate_from_uri("http://CaptainPredicate.org")\
                .resource_literal("Literally a resource")
            editor.add_singular_annotation(singular_annotation)

        See Also:
            :class:`SingularAnnotation`

        Returns: None

        """
        val = _pyom.editor_add_single_annotation(self._obj, singular_annotation.get_ptr())
        return val

    @propagate_omexmeta_error
    def add_physical_entity(self, physical_entity: PhysicalEntity) -> None:
        """Adds a PhysicalEntity to the relevant RDF graph (the one that created
        this :class:`Editor`).

        Users do not normally call this method themselves, because the preferred
        user interface is to use the context manager for :class:`PhysicalEntity`.
        If the context manager for :class:`PhysicalEntity` is not used to
        create the :class:`PhysicalEntity` object, then this method must be called
        to add the :class:`PhysicalEntity` object to the relevant :class:`RDF` object
        See Examples.

        Args:
            physical_entity: An instance of :class:`PhysicalEntity` to add to the model

        .. code-block: python
            :linenos:

            # Users should do the following. This implicitly calls the
            # :meth:`Editor.add_physical_entity` after the `with` block has finished.
            rdf = RDF()
            editor = rdf.to_editor("<insert sbml here>")
            with editor.new_physical_entity() as physical_entity:
               physical_entity \
                   .about("species0000", eUriType.MODEL_URI) \
                   .has_property(is_version_of="OPB:OPB_00340") \
                   .identity("uniprot:P84022") \
                   .is_part_of("obo/FMA_7163") \
                   .is_part_of("obo/FMA_264020")

            # If the context manager is not used, you must manually call :meth:`Editor.add_physical_entity`
            rdf = RDF()
            editor = rdf.to_editor("<insert xml here>")
            physical_entity = editor.new_physical_entity()
            physical_entity \
                .about("species0000", eUriType.MODEL_URI) \
                .has_property(is_version_of="OPB:OPB_00340") \
                .identity("uniprot:P84022") \
                .is_part_of("obo/FMA_7163") \
                .is_part_of("obo/FMA_264020")
            editor.add_physical_entity(physical_entity)

        See Also:
            :class:`PhysicalEntity`

        Returns: None

        """
        err_code = _pyom.editor_add_physical_entity(self._obj, physical_entity.get_ptr())
        return err_code

    @propagate_omexmeta_error
    def add_physical_process(self, physical_process: PhysicalProcess) -> None:
        """Adds a PhysicalProcess to the relevant RDF graph (the one that created
        this :class:`Editor`).

        Users do not normally call this method themselves, because the preferred
        user interface is to use the context manager for :class:`PhysicalProcess`.
        If the context manager for :class:`PhysicalProcess` is not used to
        create the :class:`PhysicalProcess` object, then this method must be called
        to add the :class:`PhysicalProcess` object to the relevant :class:`RDF` object
        See Examples.

        Args:
            physical_process: An instance of :class:`PhysicalProcess` to add to the model

        .. code-block: python
            :linenos:

            # Users should do the following. This implicitly calls the
            # :meth:`Editor.add_physical_process` after the `with` block has finished.
            rdf = RDF()
            editor = rdf.to_editor("<insert sbml here>")
            with editor.new_physical_process() as physical_process:
                physical_process \
                    .about("reaction0000", eUriType.MODEL_URI) \
                    .has_property(is_version_of="OPB:OPB_00237") \
                    .add_source("species0000", eUriType.MODEL_URI, 1) \
                    .add_sink("species0001", eUriType.MODEL_URI, 1)

            # If the context manager is not used, you must manually call :meth:`Editor.add_physical_process`
            rdf = RDF()
            editor = rdf.to_editor("<insert xml here>")
            physical_process = editor.new_physical_process()
            physical_process \
                .about("reaction0000", eUriType.MODEL_URI) \
                .has_property(is_version_of="OPB:OPB_00237") \
                .add_source("species0000", eUriType.MODEL_URI, 1) \
                .add_sink("species0001", eUriType.MODEL_URI, 1)
            editor.add_physical_process(physical_process)

        See Also:
            :class:`PhysicalProcess`

        Returns: None

        """
        return _pyom.editor_add_physical_process(self._obj, physical_process.get_ptr())

    @propagate_omexmeta_error
    def add_energy_diff(self, energy_diff: EnergyDiff) -> None:
        """Adds a EnergyDiff to the relevant RDF graph (the one that created
        this :class:`Editor`).

        Users do not normally call this method themselves, because the preferred
        user interface is to use the context manager for :class:`EnergyDiff`.
        If the context manager for :class:`EnergyDiff` is not used to
        create the :class:`EnergyDiff` object, then this method must be called
        to add the :class:`EnergyDiff` object to the relevant :class:`RDF` object
        See Examples.

        Args:
            energy_diff: An instance of :class:`EnergyDiff` to add to the model

        .. code-block: python
            :linenos:

            # Users should do the following. This implicitly calls the
            # :meth:`Editor.add_energy_diff` after the `with` block has finished.
            rdf = RDF()
            editor = rdf.to_editor("<insert sbml here>")
            with editor.new_energy_diff() as energy_diff:
               energy_diff.about("reaction0000", eUriType.MODEL_URI) \
                   .add_source("species0000", eUriType.MODEL_URI) \
                   .add_sink("species0001", eUriType.MODEL_URI) \
                   .has_property("localParameter0000", eUriType.LOCAL_URI, "opb:OPB_01058")

            # If the context manager is not used, you must manually call :meth:`Editor.add_energy_diff`
            rdf = RDF()
            editor = rdf.to_editor("<insert xml here>")
            energy_diff = editor.new_energy_diff()
            energy_diff \
                .about("reaction0000", eUriType.MODEL_URI) \
                .has_property(is_version_of="OPB:OPB_00237") \
                .add_source("species0000", eUriType.MODEL_URI, 1) \
                .add_sink("species0001", eUriType.MODEL_URI, 1)
            editor.add_energy_diff(energy_diff)
            
        See Also:
            :class:`EnergyDiff`

        Returns: None

        """
        return _pyom.editor_add_energy_diff(self._obj, energy_diff.get_ptr())

    @propagate_omexmeta_error
    def add_personal_information(self, personal_information: PersonalInformation) -> None:
        """Adds a PersonalInformation to the relevant RDF graph (the one that created
        this :class:`Editor`).

        Users do not normally call this method themselves, because the preferred
        user interface is to use the context manager for :class:`PersonalInformation`.
        If the context manager for :class:`PersonalInformation` is not used to
        create the :class:`PersonalInformation` object, then this method must be called
        to add the :class:`PersonalInformation` object to the relevant :class:`RDF` object
        See Examples.

        Args:
            personal_information: An instance of :class:`PersonalInformation` to add to the model

        .. code-block: python
            :linenos:

            # Users should do the following. This implicitly calls the
            # :meth:`Editor.add_personal_information` after the `with` block has finished.
            rdf = RDF()
            editor = rdf.to_editor("<insert sbml here>")
            with editor.new_personal_information() as personal_information:
                personal_information.add_creator("1234-1234-1234-1234") \
                    .add_name("Ciaran") \
                    .add_mbox("cwelsh2@uw.edu") \
                    .add_account_name("1234-1234-1234-1234") \
                    .add_account_service_homepage("https://github.com/sys-bio/libomexmeta")

            # If the context manager is not used, you must manually call :meth:`Editor.add_personal_information`
            rdf = RDF()
            editor = rdf.to_editor("<insert xml here>")
            personal_information = editor.new_personal_information()
            personal_information \
                .about("reaction0000", eUriType.MODEL_URI) \
                .has_property(is_version_of="OPB:OPB_00237") \
                .add_source("species0000", eUriType.MODEL_URI, 1) \
                .add_sink("species0001", eUriType.MODEL_URI, 1)
            editor.add_personal_information(personal_information)
            
        See Also:
            :class:`PersonalInformation`

        Returns: None

        """
        return _pyom.editor_add_personal_information(self._obj, personal_information.get_ptr())

    @propagate_omexmeta_error
    def add_physical_property(self, property: PhysicalProperty) -> None:
        """Adds a PhysicalProperty to the relevant RDF graph (the one that created
        this :class:`Editor`).

        Composite annotations usually create their own :class:`PhysicalProperty` but this method
        gives users the option to add one manually.

        Users do not normally call this method themselves, because the preferred
        user interface is to use the context manager for :class:`PhysicalProperty`.
        If the context manager for :class:`PhysicalProperty` is not used to
        create the :class:`PhysicalProperty` object, then this method must be called
        to add the :class:`PhysicalProperty` object to the relevant :class:`RDF` object
        See Examples.

        Args:
            property: An instance of :class:`PhysicalProperty` to add to the model

        .. code-block: python
            :linenos:

            # Users should do the following. This implicitly calls the
            # :meth:`Editor.add_personal_information` after the `with` block has finished.
            rdf = RDF()
            editor = rdf.to_editor("<insert sbml here>")
            property = editor.new_physical_property()
            property.about("EntityProperty", eUriType.LOCAL_URI) \
                .is_version_of("opb:OPB_12345") \
                .is_property_of("species0001", eUriType.MODEL_URI)
            with editor.new_physical_entity() as physical_entity:
                physical_entity.about("species0001", eUriType.MODEL_URI) \
                    .identity("uniprot:PD12345") \
                    .is_part_of("fma:1234") \
                    .has_property(property=property)
            # Or to add the property outside of a composite annotation
            editor.add_physical_property(property)

        See Also:
            :class:`PhysicalProperty`

        Returns: None

        """
        return _pyom.editor_add_physical_property(self._obj, property.get_ptr())

    @propagate_omexmeta_error
    def check_valid_metaid(self, id: str) -> None:
        """Convenience method for checking whether the metaid `id` is valid for this RDF graph"""
        return _pyom.editor_check_valid_metaid(self._obj, id)

    def get_metaids(self) -> List[str]:
        """Return a list of available metaids for current xml model"""
        num_ids = _pyom.editor_get_num_metaids(self._obj)
        propagate_omexmeta_error(num_ids)
        return [_pyom.get_and_free_c_str(
            propagate_omexmeta_error(_pyom.editor_get_metaid(self._obj, id))
        ) for id in range(num_ids)]

    @propagate_omexmeta_error
    def remove_single_annotation(self, single_annotaiton_ptr: ct.c_int64) -> None:
        """Remove a :class:`SingularAnnotation` from the RDF graph. Does nothing if not exists"""
        return _pyom.editor_remove_single_annotation(self._obj, single_annotaiton_ptr)

    @propagate_omexmeta_error
    def remove_physical_entity(self, physical_entity_ptr: ct.c_int64) -> None:
        """Remove a :class:`PhysicalEntity` from the RDF graph. Does nothing if not exists"""
        return _pyom.editor_remove_physical_entity(self._obj, physical_entity_ptr)

    @propagate_omexmeta_error
    def remove_physical_process(self, physical_process_ptr: ct.c_int64) -> None:
        """Remove a :class:`PhysicalProcess` from the RDF graph. Does nothing if not exists"""
        return _pyom.editor_remove_physical_process(self._obj, physical_process_ptr)

    @propagate_omexmeta_error
    def remove_energy_diff(self, energy_diff_ptr: ct.c_int64) -> None:
        """Remove a :class:`EnergyDiff` from the RDF graph. Does nothing if not exists"""
        return _pyom.editor_remove_energy_diff(self._obj, energy_diff_ptr)

    @propagate_omexmeta_error
    def remove_personal_information(self, personal_information_ptr: ct.c_int64) -> None:
        """Remove a :class:`PersonalInformation` from the RDF graph. Does nothing if not exists"""
        return _pyom.editor_remove_personal_information(self._obj, personal_information_ptr)

    def get_xml(self) -> str:
        """Returns the xml currently being edited by this :class:`Editor`"""
        return _pyom.get_and_free_c_str(
            propagate_omexmeta_error(_pyom.editor_get_xml(self._obj))
        )

    @contextmanager
    def new_singular_annotation(self) -> SingularAnnotation:
        """Create a new :class:`SingularAnnotation` object.
        
        This is a context manager, i.e. designed to be used inside a `with` block. 
        Doing so, automatically adds this :class:`SingularAnnotation` to the relevant
        :class:`RDF` object. Use without a context manager requires users to manually 
        add the :class:`SingularAnnotation` to the :class:`RDF` 
        using :meth:`add_singular_annotation`
        
        .. code-block: python
            :linenos:

            rdf = RDF()
            editor = rdf.to_editor("insert xml here")
            with editor.new_singular_annotation() as singular_annotation:
               singular_annotation.about("SmadNuclearTransport") \
                    .predicate_from_uri("http://CaptainPredicate.org")\
                    .resource_literal("Literally a resource")

        See Also:
            :class:`SingularAnnotation`

        Returns:
            :class:`SingularAnnotation`

        """
        obj = _pyom.editor_new_singular_annotation(self._obj)
        if obj is None:
            raise OmexMetaException(_pyom.get_last_error())
        singular_annotation = SingularAnnotation(obj)
        try:
            yield singular_annotation
        finally:
            self.add_singular_annotation(singular_annotation)

    @contextmanager
    def new_personal_information(self) -> PersonalInformation:
        """Create a new :class:`PersonalInformation` object.

        This is a context manager, i.e. designed to be used inside a `with` block.
        Doing so, automatically adds this :class:`PersonalInformation` to the relevant
        :class:`RDF` object. Use without a context manager requires users to manually
        add the :class:`PersonalInformation` to the :class:`RDF`
        using :meth:`add_personal_information`

        .. code-block: python
            :linenos:

            rdf = RDF()
            editor = rdf.to_editor("<insert sbml here>")
            with editor.new_personal_information() as personal_information:
                personal_information.add_creator("1234-1234-1234-1234") \
                    .add_name("Ciaran") \
                    .add_mbox("cwelsh2@uw.edu") \
                    .add_account_name("1234-1234-1234-1234") \
                    .add_account_service_homepage("https://github.com/sys-bio/libomexmeta")


        See Also:
            :class:`PersonalInformation`

        Returns:
             :class:`PersonalInformation`

        """
        obj = _pyom.editor_new_personal_information(self._obj)
        if obj is None:
            raise OmexMetaException(_pyom.get_last_error())
        information = PersonalInformation(obj)
        try:
            yield information
        finally:
            self.add_personal_information(information)

    @contextmanager
    def new_physical_entity(self) -> PhysicalEntity:
        """Create a new :class:`PhysicalEntity` object.

        This is a context manager, i.e. designed to be used inside a `with` block.
        Doing so, automatically adds this :class:`PhysicalEntity` to the relevant
        :class:`RDF` object. Use without a context manager requires users to manually
        add the :class:`PhysicalEntity` to the :class:`RDF`
        using :meth:`add_physical_entity`

        .. code-block: python
            :linenos:

            rdf = RDF()
            editor = rdf.to_editor("<insert sbml here>")
            with editor.new_physical_entity() as physical_entity:
               physical_entity \
                   .about("species0000", eUriType.MODEL_URI) \
                   .has_property(is_version_of="OPB:OPB_00340") \
                   .identity("uniprot:P84022") \
                   .is_part_of("obo/FMA_7163") \
                   .is_part_of("obo/FMA_264020")


        See Also:
            :class:`PhysicalEntity`

        Returns:
             :class:`PhysicalEntity`

        """
        obj = _pyom.editor_new_physical_entity(self._obj)
        if obj is None:
            raise OmexMetaException(_pyom.get_last_error())
        physical_entity = PhysicalEntity(obj)
        try:
            yield physical_entity
        finally:
            self.add_physical_entity(physical_entity)

    @contextmanager
    def new_physical_process(self) -> PhysicalProcess:
        """Create a new :class:`PhysicalProcess` object.

        This is a context manager, i.e. designed to be used inside a `with` block.
        Doing so, automatically adds this :class:`PhysicalProcess` to the relevant
        :class:`RDF` object. Use without a context manager requires users to manually
        add the :class:`PhysicalProcess` to the :class:`RDF`
        using :meth:`add_physical_process`

        .. code-block: python
            :linenos:

            rdf = RDF()
            editor = rdf.to_editor("<insert sbml here>")
            with editor.new_physical_process() as physical_process:
                physical_process \
                    .about("reaction0000", eUriType.MODEL_URI) \
                    .has_property(is_version_of="OPB:OPB_00237") \
                    .add_source("species0000", eUriType.MODEL_URI, 1) \
                    .add_sink("species0001", eUriType.MODEL_URI, 1)


        See Also:
            :class:`PhysicalProcess`

        Returns:
             :class:`PhysicalProcess`

        """
        obj = _pyom.editor_new_physical_process(self._obj)
        if obj is None:
            raise OmexMetaException(_pyom.get_last_error())
        physical_process = PhysicalProcess(obj)
        try:
            yield physical_process
        finally:
            self.add_physical_process(physical_process)

    @contextmanager
    def new_energy_diff(self) -> EnergyDiff:
        """Create a new :class:`EnergyDiff` object.

        This is a context manager, i.e. designed to be used inside a `with` block.
        Doing so, automatically adds this :class:`EnergyDiff` to the relevant
        :class:`RDF` object. Use without a context manager requires users to manually
        add the :class:`EnergyDiff` to the :class:`RDF`
        using :meth:`add_energy_diff`

        .. code-block: python
            :linenos:

            rdf = RDF()
            editor = rdf.to_editor("<insert sbml here>")
            with editor.new_energy_diff() as energy_diff:
               energy_diff.about("reaction0000", eUriType.MODEL_URI) \
                   .add_source("species0000", eUriType.MODEL_URI) \
                   .add_sink("species0001", eUriType.MODEL_URI) \
                   .has_property("localParameter0000", eUriType.LOCAL_URI, "opb:OPB_01058")



        See Also:
            :class:`EnergyDiff`

        Returns:
             :class:`EnergyDiff`

        """
        obj = _pyom.editor_new_energy_diff(self._obj)
        if obj is None:
            raise OmexMetaException(_pyom.get_last_error())
        energy_diff = EnergyDiff(obj)
        try:
            yield energy_diff
        finally:
            self.add_energy_diff(energy_diff)

    def new_physical_property(self) -> PhysicalProperty:
        """Create a new :class:`EnergyDiff` object """
        obj = _pyom.editor_new_physical_property(self._obj)
        if obj is None:
            raise OmexMetaException(_pyom.get_last_error())
        return PhysicalProperty(obj)

    def delete(self):
        """clean up resources used by this :class:`Editor` object"""
        return _pyom.editor_delete(self._obj)

    @propagate_omexmeta_error
    def add_creator(self, creator) -> Editor:
        """Add model level annotation "creator" to the rdf graph"""
        self._obj = _pyom.editor_add_creator(self._obj, creator.encode())
        propagate_omexmeta_error(self._obj)
        return self

    def add_curator(self, curator) -> Editor:
        """Add model level annotation "curator" to the rdf graph"""
        self._obj = _pyom.editor_add_contributor(self._obj, curator.encode())
        propagate_omexmeta_error(self._obj)
        return self

    def add_taxon(self, taxon) -> Editor:
        """Add model level annotation "taxon" to the rdf graph"""
        self._obj = _pyom.editor_add_taxon(self._obj, taxon.encode())
        propagate_omexmeta_error(self._obj)
        return self

    def add_pubmed(self, pubmed) -> Editor:
        """Add model level annotation "pubmed" to the rdf graph"""
        self._obj = _pyom.editor_add_pubmed(self._obj, pubmed.encode())
        propagate_omexmeta_error(self._obj)
        return self

    def add_description(self, description) -> Editor:
        """Add model level annotation "description" to the rdf graph"""
        self._obj = _pyom.editor_add_description(self._obj, description.encode())
        propagate_omexmeta_error(self._obj)
        return self

    def add_date_created(self, date_created) -> Editor:
        """Add model level annotation "date created" to the rdf graph"""
        self._obj = _pyom.editor_add_date_created(self._obj, date_created.encode())
        propagate_omexmeta_error(self._obj)
        return self

    def add_parent_model(self, parent_model) -> Editor:
        """Add model level annotation "parent model" to the rdf graph"""
        self._obj = _pyom.editor_add_parent_model(self._obj, parent_model.encode())
        propagate_omexmeta_error(self._obj)
        return self

    def strip_annotations(self, annotationElementName: str = "annotation") -> str:
        xml = _pyom.get_and_free_c_str(_pyom.editor_strip_annotations(self._obj, annotationElementName.encode()))
        propagate_omexmeta_error(self._obj)
        return xml


class SingularAnnotation:
    """Interface for handling single annotations or Triples (or rdf statements).

    This is the lowest level interface exposed to users. It allows you to create
    arbitrary RDF triples and add them to the RDF graph.

    :class:`SingularAnnotation` objects are created using the :meth:`Editor.new_singular_annotation`
    method.

    All :class:`SingularAnnotation` objects need to call the :meth:`SingularAnnotation.about`
    method to set the subject portion of the triple object being created.

    The predicate portion may be set with the predicate factory, invoked
    with the :meth:`SingularAnnotation.predicate` method or directly from a
    full uri using :meth:`SingularAnnotation.set_predicate_from_uri` method

    The resource portion of the triple may be set with one of
        * :meth:`SingularAnnotation.set_resource_literal`
        * :meth:`SingularAnnotation.set_resource_uri`
        * :meth:`SingularAnnotation.set_resource_blank`

    for creating a literal, uri or blank note respectively.

    From section 2.3.6 in the OmexMeta specification:

    Singular annotations within COMBINE archive annotation files should be
    encoded as a single RDF triple. The subject of the triple is
    the annotated element and should be formatted as a relative URI.
    The predicate is the URI of a BioModels.net qualifier linking the subject to a
    URI from a knowledge resource or the Dublin Core Metadata Terms qualifier
    description. The object of the triple should be an identifiers.org-formatted
    URI indicating a concept in a knowledge resource, or a text string for free-text
    definitions of model elements.

    The following is an example singular semantic annotation indicating that the
    model element with meta- data ID “meta0013” from the model file “MyModel.sbml”
    represents adenosine tri-phosphate:

    .. code-block:

        myOMEX:MyModel.sbml#meta0013 bqbiol:is chebi:15422 .

    The following is an example free-text description of a model variable with metadata ID “meta0014”:

    .. code-block:

        myOMEX:MyModel.sbml#meta0014
              dc:description  "Cardiomyocyte cytosolic ATP concentration" .

    .. code-block: python
        :linenos:

        # Note that these examples are semantically nonesense!
        rdf = RDF()
        editor = rdf.to_editor("<insert xml here>")
        with editor.new_singular_annotation() as s1:
            s1.about("species0000") \ # species0000 is a metaid in sbml
                .predicate("bqbiol", "is") \ #use the "is" predicate from bqbiol (BiomodelsBiologyQualifier) namespace
                .resource_uri("uniprot:PD88776") # create a uri resource node

        with editor.new_singular_annotation() as s2:
            s2.about("species0000") \ # species0000 is a metaid in sbml
                .predicate("bqmodel", "isDerivedFrom") \ #use the "isDerivedFrom" predicate from bqmodel (BiomodelsModelQualifier) namespace
                .resource_literal("Something Literal") # create a uri resource node

        with editor.new_singular_annotation() as s3a:
            s3a.about("species0000") \ # species0000 is a metaid in sbml
                .set_predicate_from_uri("http://homegrownpredicate.org") \ #use a predicate directly from a uri
                .resource_blank("This Is A Blank Identifier") # create a blank resource node
        with editor.new_singular_annotation() as s3b:
            s3b.about("This Is A Blank Identifier") \
                .set_predicate_from_uri("foaf", "name") \
                .set_resource_literal("James")
    """

    def __init__(self, singular_annotation_ptr: ct.c_int64):
        """Constructor for a :meth:`SingularAnnotation` object.

        This constructor should not be used directly by users. Instead
        use the :meth:`Editor.new_singular_annotation` method.

        Methods in this class implement a builder interface, by returning a
        a reference to self. This allows optional chaining of methods together.

        Args:
            singular_annotation_ptr: A pointer to an SingularAnnotation which exist in memory
        """
        self._obj = singular_annotation_ptr

    def get_ptr(self) -> ct.c_int64:
        """returns the underlying pointer to the memory address that stores this :class:`SingularAnnotation`"""
        return self._obj

    def about(self, about: str) -> SingularAnnotation:
        """Create a subject node with the string `about`

        Args:
            about:  a metaid that exists in the model. Errors when this metaid does
                    not exist in the model you are annotating, and presents you
                    with available metaids.

        Returns:
            :class:`SingularAnnotation` reference to self object

        """
        self._obj = _pyom.singular_annotation_about(self._obj, about.encode())
        propagate_omexmeta_error(self._obj)
        return self

    def predicate(self, namespace: str, term: str) -> SingularAnnotation:
        """This method provides a factory interface for predicate node creation.

        Args:
            namespace: One of
                * "bqbiol"   BiomodelsBiologyQualifier. http://biomodels.net/biology-qualifiers/
                * "bqmodel"  BiomodelsModelQualifier.   http://biomodels.net/model-qualifiers/
                * "dc"       DCTerm.                    http://purl.org/dc/terms/
                * "semsim"   SemSim.                    http://bime.uw.edu/semsim/
                * "foaf"     Foaf.                      http://xmlns.com/foaf/0.1/

            term: the string of the term in namespace that you would like to use. All
                  terms are supported but there are a finite set from which you cannot
                  deviate. Attempts to create a `term` in `namespace` that does not exist
                  results in an error, with a list of available `terms` in namespace `namespace`

        Returns:
            :class:`SingularAnnotation` reference to self object

        """
        self._obj = _pyom.singular_annotation_predicate(self._obj, namespace.encode(), term.encode())
        propagate_omexmeta_error(self._obj)
        return self

    def set_predicate_from_uri(self, uri: str) -> SingularAnnotation:
        """Create a predicate node from an arbitrary uri

        Deprecated, use :meth:`SingularAnnotation.predicate_from_uri` instead

        Args:
            uri: A uri to use for predicate

        Returns:
            :class:`SingularAnnotation` reference to self object

        """
        self._obj = _pyom.singular_annotation_set_predicate_from_uri(self._obj, uri.encode())
        propagate_omexmeta_error(self._obj)
        return self

    def set_resource_literal(self, literal: str) -> SingularAnnotation:
        """Create a literal resource node

        Deprecated, use :meth:`SingularAnnotation.resource_literal` instead

        Args:
            literal: The string to use for the literal node

        Returns:
            :class:`SingularAnnotation` reference to self object

        """
        self._obj = _pyom.singular_annotation_set_resource_literal(self._obj, literal.encode())
        propagate_omexmeta_error(self._obj)
        return self

    def set_resource_uri(self, uri: str) -> SingularAnnotation:
        """Create a uri resource node

        Deprecated, use :meth:`SingularAnnotation.resource_uri` instead

        Args:
            uri: The string to use for the uri

        Returns:
            :class:`SingularAnnotation` reference to self object

        """
        self._obj = _pyom.singular_annotation_set_resource_uri(self._obj, uri.encode())
        propagate_omexmeta_error(self._obj)
        return self

    def set_resource_blank(self, blank_id: str) -> SingularAnnotation:
        """Create a blank resource node

        Deprecated, use :meth:`SingularAnnotation.resource_blank` instead

        Args:
            blank_id: The string to use for the blank node

        Returns:
            :class:`SingularAnnotation` reference to self object

        """
        self._obj = _pyom.singular_annotation_set_resource_blank(self._obj, blank_id.encode())
        propagate_omexmeta_error(self._obj)
        return self

    def predicate_from_uri(self, uri: str) -> SingularAnnotation:
        """Create a uri resource node

        Args:
            uri: A uri string to use for resource

        Returns:
            :class:`SingularAnnotation` reference to self object

        """
        self._obj = _pyom.singular_annotation_predicate_from_uri(self._obj, uri.encode())
        propagate_omexmeta_error(self._obj)
        return self

    def resource_literal(self, literal: str) -> SingularAnnotation:
        """Create a literal resource

        Args:
            literal: string to use for literal resource node

        Returns:
            :class:`SingularAnnotation` reference to self object

        """
        self._obj = _pyom.singular_annotation_resource_literal(self._obj, literal.encode())
        propagate_omexmeta_error(self._obj)
        return self

    def resource_uri(self, uri: str) -> SingularAnnotation:
        """Create a uri resource node

        Args:
            uri: A uri to use for uri node

        Returns:
            :class:`SingularAnnotation` reference to self object

        """
        self._obj = _pyom.singular_annotation_resource_uri(self._obj, uri.encode())
        propagate_omexmeta_error(self._obj)
        return self

    def resource_blank(self, blank_id: str) -> SingularAnnotation:
        """Create a blank resource node

        Args:
            blank_id: A string to use for label of blank resource node

        Returns:
            :class:`SingularAnnotation` reference to self object

        """
        self._obj = _pyom.singular_annotation_resource_blank(self._obj, blank_id.encode())
        propagate_omexmeta_error(self._obj)
        return self

    def get_about(self) -> str:
        """Returns the about (subject) portion of rdf triple"""
        return _pyom.get_and_free_c_str(
            propagate_omexmeta_error(
                _pyom.singular_annotation_get_about(self._obj)
            )
        )

    def get_predicate(self) -> str:
        """Return the predicate portion of the rdf triple"""
        return _pyom.get_and_free_c_str(
            propagate_omexmeta_error(_pyom.singular_annotation_get_predicate(self._obj)))

    def get_resource(self) -> str:
        """return the resource portion of the rdf triple"""
        return _pyom.get_and_free_c_str(
            propagate_omexmeta_error(_pyom.singular_annotation_get_resource(self._obj)))

    def delete(self) -> None:
        """clean up resources associated with this :class:`SingularAnnotation`"""
        return _pyom.singular_annotation_delete(self._obj)


class PhysicalProperty:
    """Interface for handling PhysicalProperty objects

    PhysicalProperty objects are used by all composite annotations. They are
    comprised of two Triples: "isVersionOf" and an "isPropertyOf" which denote
    the physical property that this thing which bears the physical property
    has and a reference to the thing which bears the physical property.

    Please see the OmexMeta specification for more details.
    """

    def __init__(self, physical_property_ptr: ct.c_int64):
        self._obj = physical_property_ptr

    def get_ptr(self):
        return self._obj

    @propagate_omexmeta_error
    def get_about(self) -> str:
        return _pyom.get_and_free_c_str(
            propagate_omexmeta_error(
                _pyom.physical_property_get_about(self._obj)
            )
        )

    def about(self, about: str, uri_type: eUriType) -> PhysicalProperty:
        propagate_omexmeta_error(_pyom.physical_property_about(self._obj, about.encode(), uri_type))
        return self

    def get_is_version_of_value(self) -> str:
        return _pyom.get_and_free_c_str(
            propagate_omexmeta_error(_pyom.physical_property_get_is_version_of_value(self._obj))
        )

    def is_property_of(self, is_property_of_value: str, uri_type: eUriType = eUriType.NONE) -> PhysicalProperty:
        propagate_omexmeta_error(
            _pyom.physical_property_is_property_of(self._obj, is_property_of_value.encode(), uri_type))
        return self

    def is_version_of(self, is_version_of_value: str) -> PhysicalProperty:
        propagate_omexmeta_error(_pyom.physical_property_is_version_of(self._obj, is_version_of_value.encode()))
        return self

    def get_is_property_of_value(self) -> str:
        return _pyom.get_and_free_c_str(
            propagate_omexmeta_error(_pyom.physical_property_get_is_property_of_value(self._obj))
        )

    def delete(self) -> None:
        return _pyom.physical_property_delete(self._obj)


class _PropertyBearer:
    """Abstraction layer for Composite annotation classes. All composite annotations
    are PropertyBearers so we abstract and shared code among them.

    This class is private
    """

    def __init__(self, name: str, obj: ct.c_int64):
        self._obj = obj
        self.name = name

    def has_property(self, property_about: str = None, about_uri_type: eUriType = None,
                     is_version_of: str = None, property: PhysicalProperty = None) -> _PropertyBearer:
        """Create a PhysicalProperty associated with a PhysicalEntity, EnergyDiff or PhysicalProcess.

        This method has 3 signatures in the underlying C++ library. This method unpacks the
        user supplied arguments and passes them to the correct signature, depending on what is supplied.

        The first signature is used with sbml models and requires only the `is_version_of` arument. This
        is commonly used for annotating sbml models and therefore, when only one string argument
        is passed to :meth:`has_property` the argument is used for the `is_version_of` argument
        (see example below).

        Args:
            is_version_of: (str) represents an OPB term from the Ontology of Physical Biology.

        .. code-block: python
            :linenos:

            rdf = RDF()
            editor = self.rdf.to_editor("insert sbml here")
            with editor.new_physical_entity() as physical_entity:
                physical_entity.about("species0000", eUriType.MODEL_URI) \
                    .identity("uniprot:PD12345") \
                    .is_part_of("fma:1234") \
                    .has_property("opb:OPB_12345") # same as has_property(is_version_of="opb:OPB_12345")

        In the above case, the necessary local identifiers are created automatically and are guarenteed
        to be unique throughout your RDF graph. In some circumstances, you might want to have control
        over the metaids used for local uri's. The above would create a :class:`PhysicalProperty`
        with the subject or "about" portion equal to `local:EntityProperty0000`. We can set this ourselves
        using the second overload, which requires three arguments:

        Args:
            `property_about`: The subject or "about" portion of the :class:`PhysicalProperty` triples.
            `about_uri_type`  eUriType.LOCAL_URI if the uri for `property_about` should be local to the
                              annotation (rdf) graph or eUriType.MODEL_URI if it instead points to a
                              element of the model (which is common in CellML).
            `is_version_of` The OPB term to use for the "isVersionOf" predicate

        .. code-block: python
            :linenos:

            rdf = RDF()
            editor = rdf.to_editor("<insert sbml here>", generate_new_metaids=True, sbml_semantic_extraction=False)
            with editor.new_physical_entity() as physical_entity:
                physical_entity.about("species0000", eUriType.MODEL_URI) \
                    .identity("uniprot:PD12345") \
                    .is_part_of("fma:1234") \
                    .has_property("EntityProperty", eUriType.LOCAL_URI, "opb:OPB_12345")

        Finally, you can create the :class:`Property` yourself and pass that to :meth:`has_property` instead.
        This is often more useful in CellML models.

        .. code-block: python
            :linenos:

            rdf = RDF()
            editor = rdf.to_editor"(<insert cellml here>")
            property = editor.new_physical_property()
            property.about("main.Volume", eUriType.MODEL_URI) \
                .is_version_of("opb:OPB_00154") \
                .is_property_of("entity0", eUriType.LOCAL_URI)
            with editor.new_physical_entity() as physical_entity:
                physical_entity.about("entity0", eUriType.LOCAL_URI) \
                    .identity("fma:9570") \
                    .is_part_of("fma:18228") \
                    .has_property(property=property)

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
            propagate_omexmeta_error(has_property(self._obj, property.get_ptr()))
            return self

        # When the user provices all of the arguments we can use the "full" signature
        if (property_about
                and is_version_of
                and about_uri_type
        ):
            propagate_omexmeta_error(
                has_property_full(
                    self._obj, property_about.encode(), about_uri_type, is_version_of.encode())
            )
            return self

        # When the user only provides argument to is_version_of we use the  hasPropertyIsVersionOf version
        if is_version_of and not property_about and not about_uri_type:
            propagate_omexmeta_error(
                has_property_is_version_of(self._obj, is_version_of.encode())
            )
            return self

        # if user provides a single string, it is assumed to be the is_version_of string NOT the property_about
        if property_about and not is_version_of and not about_uri_type and not property:
            propagate_omexmeta_error(
                has_property_is_version_of(self._obj, property_about.encode())
            )
            return self

        # if we get this far then the user has made an error
        raise ValueError(f'Argument combination to "{self.__class__.__name__}" is invalid')


class PhysicalEntity(_PropertyBearer):
    """Interface for creating PhysicalEntity composite annotations.

    :class:`PhysicalEntity` implements the Builder pattern, so methods
    always return a reference to self, so that method calls can be chained
    together.

    From section 2.3.7.1 of the OmexMeta specification:

    Consider a CellML variable that simulates blood volume in the left coronary artery.
    The physical property simulated is volume; more precisely, fluid volume. This fluid
    volume is a property of blood in the lumen of the left coronary artery. Because there
    is no existing knowledge resource term that represents “blood volume in the left
    coronary artery”, we instead construct a composite annotation using a combination
    of existing knowledge resource terms. For the physical property portions, we
    recommend using terms from the Ontology of Physics for Biology (OPB [13]) because
    the OPB provides a comprehensive, formally- structured hierarchy of physical properties.
    In this case, we would use the OPB term “Fluid volume” (OPB:OPB 00154). The second part
    of the composite annotation, blood in the left ventricle, can be created by linking two
    terms from the Foundational Model of Anatomy (FMA [14]), namely “Portion of blood”
    (FMA:9670) and “Lumen of left coronary artery” (FMA:18228). We link these two FMA
    terms using the isPartOf BioModels.net qualifier to produce a composite physical
    entity. Thus, the composite annotation links the model element being annotated to
    the physical property it represents (via the isVersionOf BioModels.net qualifier)
    as well as to the composite physical entity that bears the property (via the
    isPropertyOf BioModels.net qualifier).

    Encoded as RDF (turtle format), this example would be serialized as:

         myOMEX:MyModel.cellml#VLV bqbiol:isVersionOf opb:OPB_00154  ;
                                   bqbiol:isPropertyOf local:entity_0 .
         local:entity_0 bqbiol:is fma:9670 ;
                        bqbiol:isPartOf fma:18228 .

    Note that the local RDF resource entity 0 needs to be created when encoding the CSA. This
    is required because there are no structures in the CellML schema that represent physical
    entities, so they are instantiated as RDF resources in the OMEX metadata document. Such
    instantiation is often not needed for SBML models, since SBML provides explicit XML elements
    for representing the bearers of physical properties including chemical species, compartments
    and reactions, and these elements can have unique metadata identifiers assigned to them.

    However, instantiation of a resource that represents the full concept described by the composite
    annotation is needed for the properties of species, compartments, and reactions in SBML models.
    Although SBML uses XML structures for declaring physical entities (<compartment> and <species>
    elements) as well as processes (<reaction> elements), it does not declare XML elements that
    represent the properties of those entities and processes. Instead, the property is indicated
    by an XML attribute on the entities and processes. Therefore, to ensure that these properties
    are searchable in OMEX annotations, we rec- ommend instantiating a generic RDF resource for
    each physical property that is implicitly represented in an SBML model. Note that this does
    not have to be done when annotating an SBML parameter because the SBML parameter element
    includes a metadata ID that can be explicitly referenced in the OMEX metadata file.
    """

    def __init__(self, physical_entity_ptr: ct.c_int64):
        """Constructor for :class:`PhysicalEntity`.

        This constructor is not designed to be used directly by users. Instead
        users should create a :class:`PhysicalEntity` directly from the an instance
        of :class:`Editor`.

        Args:
            physical_entity_ptr: A ctypes int64 integer representing the memory address (pointer)
                                 of this PhysicalEntity.
        """
        self._obj = physical_entity_ptr
        super().__init__("physical_entity", self._obj)

    def get_ptr(self) -> ct.c_int64:
        """Returns the memory address that points to this PhysicalEntity"""
        return self._obj

    def identity(self, identity: str) -> PhysicalEntity:
        """The bqbiol:is part of a PhysicalEntity type composite annotation

        Args:
            identity: (str) when `identity` has the format "name:id", the resulting
                      resource uri will be expanded to https://identifiers.org/name:id.
                      When `identity` begins with the characters "http" the uri will
                      be assumed already a full uri and is used as is.

        Returns:
            :class:`PhysicalEntity`. Reference to self

        """
        self._obj = _pyom.physical_entity_identity(self.get_ptr(), identity.encode())
        propagate_omexmeta_error(self._obj)
        return self

    def get_identity(self) -> str:
        """Return the string currently being used for the identity portion of :class:`PhysicalEntity`"""
        return _pyom.get_and_free_c_str(
            propagate_omexmeta_error(
                _pyom.physical_entity_get_identity(self.get_ptr())
            )
        )

    @propagate_omexmeta_error
    def get_num_locations(self) -> int:
        """Returns the number of location portions that exist in this :class:`PhysicalEntity`"""
        return _pyom.physical_entity_get_num_locations(self.get_ptr())

    def get_locations(self) -> List[str]:
        """Returns a list of location uris used in this :class:`PhysicalEntity`"""
        return [_pyom.get_and_free_c_str(
            propagate_omexmeta_error(
                _pyom.physical_entity_get_location(self.get_ptr(), i)
            )
        ) for i in range(self.get_num_locations())]

    def delete(self) -> None:
        """Clear up resources used by this :class:`PhysicalEntity`"""
        _pyom.physical_entity_delete(self._obj)

    def about(self, about: str, type: eUriType) -> PhysicalEntity:
        """Sets the about (subject) portion of the PhysicalEntity.

        .. note:
            Do not confuse this with the about (or subject) portion of the
            :class:`PhysicalProperty`

        i.e:
            local:EntityProperty0000 <-- *Not* this. This is the PhysicalProperty "about"
                bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#species0000> ;
                bqbiol:isVersionOf <https://identifiers.org/opb:OPB_12345> .

            <http://omex-library.org/NewOmex.omex/NewModel.xml#species0000> <-- this
                bqbiol:is <https://identifiers.org/uniprot:PD12345> ;
                bqbiol:isPartOf <https://identifiers.org/fma:1234> .

        This can either be
            - a uri of a metaid that exists in the model xml, such
              as the case with sbml
            - could need creating in this local namespace (i.e. internal to the RDF graph),
              such as the case with CellML

        Users need to know which use case they need for their annotation language.

        Args:
            about: The string to use as the metaid. When `type` is eUriType.MODEL_URI
                   then this string must be an existing metaid in the xml. When
                   `type` is eUriType.LOCAL_URI, this name can be arbitrary, as long
                   as its unique within the RDF graph.
            type: either eUriType.MODEL_URI or eUriType.LOCAL_URI

        Returns:
            :class:`PhysicalEntity`. Reference to self
        """
        self._obj = _pyom.physical_entity_about(self.get_ptr(), about.encode(), type)
        propagate_omexmeta_error(self._obj)
        return self

    def is_part_of(self, is_part_of: str, type: eUriType = eUriType.IDENTIFIERS_URI) -> PhysicalEntity:
        """Adds an entry in the list of bqbiol:isPartOf predicates for this :class:`PhysicalEntity`

        This method can be called an arbitrary number of times since the number of entries
        in this list can be any. The level of organisation is assumed
        to get smaller with successive entries. i.e. start big and get smaller as smaller things
        are part of bigger things.

        Args:
            is_part_of: The string to use for bqbiol:isPartOf. If this string has the format "name:id"
                        and `type` is eUriType.IDENTIFIERS_URI the string will be expanded
                        into "https://identifiers.org/name:id". If it instead begins with
                        "https" then the string will be used as is.
            type: A eUriType.

        Returns:
            :class:`PhysicalEntity`. Reference to self
        """
        self._obj = _pyom.physical_entity_is_part_of(self.get_ptr(), is_part_of.encode(), type)
        propagate_omexmeta_error(self._obj)
        return self

    def has_part(self, part: str) -> PhysicalEntity:
        """Adds an entry in the list of bqbiol:hasPart predicates

        This method can be called an arbitrary number of times for situations
        where you are adding items to complex.

        Args:
            part: String to use for resource portion of the hasPart triple.
                  Will be expanded into an identifiers.org identifier if the
                  string has the format "name:id:

        Returns:
            :class:`PhysicalEntity`. Reference to self
        """
        self._obj = _pyom.physical_entity_has_part(self.get_ptr(), part.encode())
        propagate_omexmeta_error(self._obj)
        return self


class PhysicalProcess(_PropertyBearer):
    """Interface for creating PhysicalProcess type composite annotations

    From section 2.3.7.2 of the OmexMeta specification:

    The example annotation above is for a physical property of a physical entity. However,
    models also include variables for the rates of physical processes, such as chemical reactions,
    transport of solutes, flow of fluids in vessels, etc., For these entities, we recommend the
    use of a composite annotation, where a custom physical process is instantiated and linked to
    its participants: the energetic sources and sinks as well as mediators whose amounts modulate
    the magnitude of the physical process property.

    Sources, sinks and mediators are the physical entities that participate in the process: source
    amounts are consumed by the process, sink amounts are produced, and mediator amounts remain
    unchanged. In the biochemical domain, sources and sinks correspond to ”reactants” and ”products”,
    but the former terms are much broader. Below, we provide an example of a composite annotation
    for the rate of a chemical reaction with one source, one sink, and one mediator.

    First, we assert statements indicating that the model includes a variable that represents
    a physical property of a process that is a chemical flow rate (opb:OPB 00592).

        myOMEX:MyModel.xml#property_metaid_0
             bqbiol:isPropertyOf local:process_0 ;
             bqbiol:isVersionOf  opb:OPB_00592 .

    The above annotation would be appropriate for a CellML model, where property metaid 0
    points to the CellML variable representing the chemical flow rate. However, in SBML models,
    processes are indicated by reactions, and there is no separate entity of variable for the
    flow rate. Therefore, an annotation about chemical flow rate for an SBML model would have
    to be defined within the RDF file, using the local: namespace. That annotation would make
    reference to the process, which would have a corresponding entity (the reaction) in the SBML file.

    We next assert statements that indicate the physical entity participants in the process: the
    energetic sources, sinks, and mediators. In this case, there is one source, one sink, and one
    mediator. Optionally, the sources and sinks can include stoichiometry statements (using the
    semsim:hasMultiplier quali- fier) to indicate the production/consumption ratios for the process
    participants (mediator participation statements cannot include stoichiometries).

    Optionally, we can also name or describe the process itself. Often, there is no knowledge
    resource for naming processes, but within the realm of biochemical reactions, many are
    named by resources such as the Gene Ontology (process branch) and RHEA (for metabolic
    reactions).

        local:process_0
               semsim:hasSourceParticipant local:source_0 ;
               semsim:hasSinkParticipant local:sink_0 ;
               semsim:hasMediatorParticipant local:mediator_0 ;
               bqbiol:isVersionOf <https://identifiers.org/GO:0004022> .
        local:source_0
               semsim:hasMultiplier 1.0 ;
               semsim:hasPhysicalEntityReference myOMEX:MyModel.xml#species_metaid_0 .
        local:sink_0
               semsim:hasMultiplier  2.0 ;
               semsim:hasPhysicalEntityReference myOMEX:MyModel.xml#species_metaid_1 .
        local:mediator_0
               semsim:hasPhysicalEntityReference myOMEX:MyModel.xml#species_metaid_2 .

    RDF statements indicating the biological identity of the chemical species that participate
    in the process (the resources with the species metaid * URI fragments in this example)
    would be included elsewhere in the RDF. For SBML models where these chemical species are
    explicitly represented using <species> elements, the metadata IDs should point to those
    elements in the SBML code. For other formats, such as CellML, that do not support such
    elements, the metadata IDs should point to physical entities instantiated elsewhere in
    the RDF, using the local: namespace.

    We recognize that creating composite annotations for biological processes in
    this manner can duplicate information that is present in an SBML model’s
    reaction network structure. However, because annota- tions are stored in
    a separate location from the source code, these composite annotations are
    necessary, so that all biological features represented in a model are exposed
    in the RDF metadata. This way, the community can more easily apply RDF-processing
    tools to analyze, query, and reason over semantic metadata in COMBINE archives,
    in a manner that is independent of the source code used by the model.

    """

    def __init__(self, physical_process_ptr: ct.c_int64):
        """Constructor for :class:`PhysicalProcess`.

        This constructor is not designed to be used directly by users. Instead
        users should create a :class:`PhysicalProcess` directly from the an instance
        of :class:`Editor`.

        Args:
            physical_process_ptr: A ctypes int64 integer representing the memory address (pointer)
                                 of this PhysicalProcess.
        """
        self._obj = physical_process_ptr
        super().__init__("physical_process", self._obj)

    def get_ptr(self) -> ct.c_int64:
        """Returns the memory address that points to this PhysicalProcess"""
        return self._obj

    def add_source(self, physical_entity_reference: str, uri_type: eUriType,
                   multiplier: float = 1.0) -> PhysicalProcess:
        """Adds an energetic source to this :class:`PhysicalProcess`, such as a reactant in a reaction

        Args:
            physical_entity_reference: The string of the metaid for the energetic source.
                                       If `uri_type` is eUriType.MODEL_URI (for instance when
                                       annotating sbml), this string needs to exist as a metaid
                                       on an element of xml. If `uri_type` is eUriType.LOCAL_URI
                                       (i.e. CellML) then this identifier can be string that is unique
                                       in the rdf document
            uri_type:                  One of eUriType.LOCAL_URI or eUriType.MODEL_URI
            multiplier:                int representing the stoichiometry of the source

        Returns:
            :class:`PhysicalProcess`. Reference to self.

        """
        self._obj = _pyom.physical_process_add_source(
            self._obj, physical_entity_reference.encode(), uri_type, multiplier
        )
        propagate_omexmeta_error(self._obj)
        return self

    def add_sink(self, physical_entity_reference: str, uri_type: eUriType, multiplier: float = 1.0) -> PhysicalProcess:
        """Adds an energetic sink to this :class:`PhysicalProcess`, such as a product in a reaction

        Args:
            physical_entity_reference: The string of the metaid for the energetic sink.
                                       If `uri_type` is eUriType.MODEL_URI (for instance when
                                       annotating sbml), this string needs to exist as a metaid
                                       on an element of xml. If `uri_type` is eUriType.LOCAL_URI
                                       (i.e. CellML) then this identifier can be string that is unique
                                       in the rdf document
            uri_type:                  One of eUriType.LOCAL_URI or eUriType.MODEL_URI
            multiplier:                int representing the stoichiometry of the sink

        Returns:
            :class:`PhysicalProcess`. Reference to self.

        """
        self._obj = _pyom.physical_process_add_sink(
            self._obj, physical_entity_reference.encode(), uri_type, multiplier
        )

        propagate_omexmeta_error(self._obj)
        return self

    def add_mediator(self, physical_entity_reference: str, uri_type: eUriType) -> PhysicalProcess:
        """Adds an energetic mediator to this :class:`PhysicalProcess`, such as a enzyme or other catalyst in a reaction

        Args:
            physical_entity_reference: The string of the metaid for the energetic mediator.
                                       If `uri_type` is eUriType.MODEL_URI (for instance when
                                       annotating sbml), this string needs to exist as a metaid
                                       on an element of xml. If `uri_type` is eUriType.LOCAL_URI
                                       (i.e. CellML) then this identifier can be string that is unique
                                       in the rdf document
            uri_type:                  One of eUriType.LOCAL_URI or eUriType.MODEL_URI
            multiplier:                int representing the stoichiometry of the mediator

        Returns:
            :class:`PhysicalProcess`. Reference to self.

        """
        self._obj = _pyom.physical_process_add_mediator(self._obj, physical_entity_reference.encode(), uri_type)
        propagate_omexmeta_error(self._obj)
        return self

    def delete(self) -> None:
        """Clear up resources used by this :class:`PhysicalProcess`"""
        return _pyom.physical_process_delete(self._obj)

    def about(self, about: str, uri_type: eUriType) -> PhysicalProcess:
        """Sets the about (subject) portion of the PhysicalProcess.

        This can be either:
            - a uri of a metaid that exists in the model xml, such as the case with sbml
            - could need creating in this local namespace (i.e. internal to the RDF graph),
              such as the case with CellML

        Users need to know which use case they need for their annotation language.

        Args:
            about: The string to use as the metaid. When `type` is eUriType.MODEL_URI
                   then this string must be an existing metaid in the xml. When
                   `type` is eUriType.LOCAL_URI, this name can be arbitrary, as long
                   as its unique within the RDF graph.
            type: either eUriType.MODEL_URI or eUriType.LOCAL_URI

        Returns:
            :class:`PhysicalProcess`. Reference to self

        """
        self._obj = _pyom.physical_process_about(self.get_ptr(), about.encode(), uri_type)
        propagate_omexmeta_error(self._obj)
        return self

    def is_version_of(self, version: str, uri_type: eUriType = eUriType.IDENTIFIERS_URI) -> PhysicalProcess:
        """Deprecated. Use hasProperty intead"""
        self._obj = _pyom.physical_process_is_version_of(self.get_ptr(), version.encode(), uri_type)
        propagate_omexmeta_error(self._obj)
        return self


class EnergyDiff(_PropertyBearer):
    """Interface for creating EnergyDiff (Energy Differential) types of Composite annotations.

    From Section 2.3.7.4 of the OmexMeta specification
    Composite annotations can also be used to represent the properties of energy differentials.
    These include, for example, membrane potentials, chemical potentials and fluid pressures.
    The structure of annotations for these properties is similar to process properties. Because
    energy differences are not conventionally

    named or represented explicitly in model code, we use a local resource in the RDF with
    its energetic sources and sinks specified. (Mediators and stoichiometries are only
    used for process annotations.)

    The following is an example that represents the electrical potential caused by a difference
    in the amount of charged ions on either side of a cell membrane. For this example, we assume
    a model element with metadata ID “parameter metaid 0” represents this biological property.
    We assert triples stating that the model element represents a property of an energy
    difference, and specifically that it represents a voltage (OPB:OPB 01058):

        myOMEX:MyModel.sbml#parameter_metaid_0
              bqbiol:isPropertyOf local:EnergyDiff_0 ;
              bqbiol:isVersionOf opb:OPB_01058 .

    We add triples that indicate the physical entity participants (energetic sources and sinks)
    whose properties define that energy difference:

        local:EnergyDiff_0
           semsim:hasSourceParticipant :source_23 ;
           semsim:hasSinkParticipant :sink_12 .
        local:source_23
           semsim:hasPhysicalEntityReference myOMEX:MyModel.sbml#species_metaid_42 .
        local:sink_12
           semsim:hasPhysicalEntityReference myOMEX:MyModel.sbml#species_metaid_37 .

    For SBML models, the URI fragments species metaid 42 and species metaid 37 would
    correspond to metadata IDs on <species> elements in the SBML code (species such as
    intra- and extra-cellular calcium ions, for example). Importantly, for models in
    CellML or other formats that do not include the explicit representation of physical
    entities, these metadata IDs would point to physical entity resources instantiated
    elsewhere in the RDF metadata.

    """

    def __init__(self, energy_diff_ptr: ct.c_int64):
        """Constructor for :class:`EnergyDiff`.

        This constructor is not designed to be used directly by users. Instead
        users should create a :class:`EnergyDiff` directly from the an instance
        of :class:`Editor`.

        Args:
            energy_diff_ptr: A ctypes int64 integer representing the memory address (pointer)
                                 of this EnergyDiff.
        """
        self._obj = energy_diff_ptr
        super().__init__("energy_diff", self._obj)

    def get_ptr(self) -> ct.c_int64:
        """Returns the memory address that points to this PhysicalEntity"""
        return self._obj

    def add_source(self, physical_entity_reference: str, uri_type: eUriType) -> EnergyDiff:
        """Adds an energetic source to this :class:`PhysicalProcess`, such as a reactant in a reaction

        .. note::
            A source in a :class:`EnergyDiff` does not have a multiplier, like the :class:`PhysicalProcess` does

        Args:
            physical_entity_reference: The string of the metaid for the energetic source.
                                       If `uri_type` is eUriType.MODEL_URI (for instance when
                                       annotating sbml), this string needs to exist as a metaid
                                       on an element of xml. If `uri_type` is eUriType.LOCAL_URI
                                       (i.e. CellML) then this identifier can be string that is unique
                                       in the rdf document
            uri_type:                  One of eUriType.LOCAL_URI or eUriType.MODEL_URI

        Returns:
            :class:`EnergyDiff`. Reference to self.

        """
        self._obj = _pyom.energy_diff_add_source(
            self._obj, physical_entity_reference.encode(), uri_type
        )
        propagate_omexmeta_error(self._obj)
        return self

    def add_sink(self, physical_entity_reference: str, uri_type: eUriType) -> EnergyDiff:
        """Adds an energetic sink to this :class:`EnergyDiff`, such as a product in a reaction

        .. note::
            A source in a :class:`EnergyDiff` does not have a multiplier, like the :class:`PhysicalProcess` does


        Args:
            physical_entity_reference: The string of the metaid for the energetic sink.
                                       If `uri_type` is eUriType.MODEL_URI (for instance when
                                       annotating sbml), this string needs to exist as a metaid
                                       on an element of xml. If `uri_type` is eUriType.LOCAL_URI
                                       (i.e. CellML) then this identifier can be string that is unique
                                       in the rdf document
            uri_type:                  One of eUriType.LOCAL_URI or eUriType.MODEL_URI

        Returns:
            :class:`EnergyDiff`. Reference to self.

        """
        self._obj = _pyom.energy_diff_add_sink(
            self._obj, physical_entity_reference.encode(), uri_type
        )
        propagate_omexmeta_error(self._obj)
        return self

    def delete(self) -> None:
        """Clear up resources used by this :class:`PhysicalProcess`"""
        _pyom.energy_diff_delete(self._obj)

    def about(self, about: str, uri_type: eUriType) -> EnergyDiff:
        """Sets the about (subject) portion of the EnergyDiff.

        This can be either:
            - a uri of a metaid that exists in the model xml, such as the case with sbml
            - could need creating in this local namespace (i.e. internal to the RDF graph),
              such as the case with CellML

        Users need to know which use case they need for their annotation language.

        Args:
            about: The string to use as the metaid. When `type` is eUriType.MODEL_URI
                   then this string must be an existing metaid in the xml. When
                   `type` is eUriType.LOCAL_URI, this name can be arbitrary, as long
                   as its unique within the RDF graph.
            type: either eUriType.MODEL_URI or eUriType.LOCAL_URI

        Returns:
            :class:`PhysicalProcess`. Reference to self

        """
        self._obj = _pyom.energy_diff_about(self.get_ptr(), about.encode(), uri_type)
        propagate_omexmeta_error(self._obj)
        return self


class PersonalInformation:
    """Interface for creating a PersonalInformation set of triples"""

    def __init__(self, personal_information_ptr: ct.c_int64):
        """Constructor for :class:`PersonalInformation`.

        This constructor is not designed to be used directly by users. Instead
        users should create a :class:`PersonalInformation` directly from the an instance
        of :class:`Editor`.

        Args:
            personal_information_ptr: A ctypes int64 integer representing the memory address (pointer)
                                 of this PersonalInformation.
        """
        self._obj = personal_information_ptr

    def get_ptr(self) -> ct.c_int64:
        """Returns the memory address that points to this PhysicalProcess"""
        return self._obj

    def get_local_uri(self) -> str:
        """Deprecated. Get uri's only from the :class:`RDF` or :class:`Editor` classes"""
        return _pyom.get_and_free_c_str(
            propagate_omexmeta_error(
                _pyom.personal_information_get_local_uri(self._obj)
            )
        )

    def add_creator(self, value: str) -> PersonalInformation:
        """Add a creator to this PersonalInformation"""
        self._obj = _pyom.personal_information_add_creator(self._obj, value.encode())
        propagate_omexmeta_error(self._obj)
        return self

    def add_name(self, value: str) -> PersonalInformation:
        """Add a name to this PersonalInformation"""
        self._obj = _pyom.personal_information_add_name(self._obj, value.encode())
        propagate_omexmeta_error(self._obj)
        return self

    def add_mbox(self, value: str) -> PersonalInformation:
        """Add a email to this PersonalInformation"""
        self._obj = _pyom.personal_information_add_mbox(self._obj, value.encode())
        propagate_omexmeta_error(self._obj)
        return self

    def add_account_name(self, value: str) -> PersonalInformation:
        """Add a account name to this PersonalInformation"""
        self._obj = _pyom.personal_information_add_account_name(self._obj, value.encode())
        propagate_omexmeta_error(self._obj)
        return self

    def add_account_service_homepage(self, value: str) -> PersonalInformation:
        """Add a webpage to this PersonalInformation"""
        self._obj = _pyom.personal_information_add_account_service_homepage(self._obj, value.encode())
        propagate_omexmeta_error(self._obj)
        return self

    def add_foaf_blank(self, value: str) -> PersonalInformation:
        """Add a blank resource node with a foaf predicate"""
        self._obj = _pyom.personal_information_add_foaf_blank(self._obj, value.encode())
        propagate_omexmeta_error(self._obj)
        return self

    def add_foaf_uri(self, value: str) -> PersonalInformation:
        """Add a uri resource node with a foaf predicate"""
        self._obj = _pyom.personal_information_add_foaf_uri(self._obj, value.encode())
        propagate_omexmeta_error(self._obj)
        return self

    def add_foaf_literal(self, value: str) -> PersonalInformation:
        """Add a literal resource node with a foaf predicate"""
        self._obj = _pyom.personal_information_add_foaf_literal(self._obj, value.encode())
        propagate_omexmeta_error(self._obj)
        return self

    def get_metaid(self) -> str:
        """Get the metaid to which this class:`PersonalInformation` associates"""
        return _pyom.get_and_free_c_str(
            propagate_omexmeta_error(
                _pyom.personal_information_get_metaid(self._obj)
            )
        )

    @propagate_omexmeta_error
    def set_metaid(self, metaid: str) -> None:
        """Set the metaid to which this class:`PersonalInformation` associates"""
        return _pyom.personal_information_set_metaid(self._obj, metaid.encode())

    def get_model_uri(self) -> str:
        """Deprecated. Use :class:`Editor` or :class:`RDF` for accesing Uris"""
        return _pyom.get_and_free_c_str(
            propagate_omexmeta_error(
                _pyom.personal_information_get_model_uri(self._obj)
            )
        )

    def delete(self):
        """Clean up resources associated with this object"""
        return _pyom.personal_information_delete(self._obj)


class Message:

    def __init__(self, message_ptr: ct.c_int64):
        """ Container for a message and its logging level

        This message is constructed by `Logger.get_message_i`

        Parameters
        ----------
        message_ptr: a pointer to the redland::Message type in the C++ api.
        """
        self._obj = message_ptr

    def __del__(self) -> None:
        """Destruct a Message object"""
        _pyom.message_delete_message(self._obj)

    def get_level(self) -> eLogLevel:
        """Returns the logging level for this Message"""
        return eLogLevel(_pyom.message_get_level(self._obj))

    def get_message(self) -> str:
        """Returns the content of this message as a string"""
        return _pyom.get_and_free_c_str(_pyom.message_get_message(self._obj))

    def __str__(self):
        return f"{str(self.get_level())}: {self.get_message()}"


class Logger:

    def __init__(self):
        self._obj = self.get_logger()

    def __getitem__(self, idx) -> Message:
        return Message(_pyom.logger_get_message_i(idx))

    def __len__(self):
        return _pyom.logger_size()

    @staticmethod
    def get_logger() -> Logger:
        """returns memory address of logger instance"""
        return _pyom.logger_get_logger()

    @staticmethod
    def set_formatter(format: str) -> None:
        """Format string for the logger

        See `here <https://github.com/gabime/spdlog/wiki/3.-Custom-formatting#pattern-flags>`_ for valid formatting codes

        """
        return _pyom.logger_set_formatter(format.encode())

    @staticmethod
    def set_level(level: eLogLevel) -> None:
        """Set the current log level.

        Valid logging levels are:
          - eLogLevel.trace = 0
          - eLogLevel.debug = 1
          - eLogLevel.info = 2
          - eLogLevel.warn = 3
          - eLogLevel.err = 4
          - eLogLevel.critical = 5
          - eLogLevel.off = 6

        Only messages with a priority equal to
        or greater than the current log level
        will be shown.

        """
        return _pyom.logger_set_level(level)

    @staticmethod
    def get_level() -> int:
        """Returns the value of the current log level"""
        return _pyom.logger_get_level()

    @staticmethod
    def enable_backtrace(num: int) -> None:
        """Turn on backtrace feature, for traceback
        in the underlying c/c++ libraries.

        Experimental feature. Backtracing
        will show the last num logging messages when dumped with
        dump_backtrace (i.e. after error).

        Args:
            num (int): How many logging messages to show on dumping the log stack trace

        """
        return _pyom.logger_enable_backtrace(num)

    @staticmethod
    def disable_backtrace(self) -> None:
        """Turn off backtrace feature

        Experimental feature

        """
        return _pyom.logger_disable_backtrace()

    @staticmethod
    def console_logger() -> None:
        """Switch to a console logger

        Turns off file_logger and activates the console logger"""
        return _pyom.logger_console_logger()

    @staticmethod
    def file_logger(filepath: str) -> None:
        """Switch to a file logger

        Args:
            filepath: valid path to where you would like to store logging messages

        Turns off console logger and activate file_logger"""
        return _pyom.logger_file_logger(filepath.encode())

    @staticmethod
    def info(message: str) -> None:
        """Log an info message"""
        return _pyom.logger_info(message.encode())

    @staticmethod
    def trace(message: str) -> None:
        """Log an trace message"""
        return _pyom.logger_trace(message.encode())

    @staticmethod
    def debug(message: str) -> None:
        """Log an debug message"""
        return _pyom.logger_debug(message.encode())

    @staticmethod
    def warn(message: str) -> None:
        """Log a warning message"""
        return _pyom.logger_warn(message.encode())

    @staticmethod
    def error(message: str) -> None:
        """Log a error message"""
        return _pyom.logger_error(message.encode())

    @staticmethod
    def critical(message: str) -> None:
        """Log a critical message"""
        return _pyom.logger_critical(message.encode())

    @staticmethod
    def clear() -> None:
        """Clear all logging messages, putting size (aka len) back to 0"""
        _pyom.logger_clear()

    @staticmethod
    def size() -> int:
        """Returns the number of logging message there are contained in this logger"""
        return _pyom.logger_size()

    @staticmethod
    def flush() -> None:
        """Flush the content in the current logger to disk"""
        _pyom.logger_flush()

    @staticmethod
    def flush_on(level: eLogLevel) -> None:
        """Flush content in the current logger with log level `level` to disk"""
        _pyom.logger_flush_on(level.level)
