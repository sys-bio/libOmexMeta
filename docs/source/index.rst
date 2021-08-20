##########################
libOmexMeta documentation!
##########################



.. toctree::
   :maxdepth: 1
   :hidden:

   background.rst
   Install/install.rst
   reading_rdf/reading_rdf.rst
   writing_rdf/writing_rdf.rst
   singular_annotations/index.rst
   composite_annotations/index.rst
   stripping_annotations/index.rst
   querying_rdf/querying_rdf.rst
   diagrams/diagrams_index.rst
   errors_and_logging/errors_and_logging.rst
   annotating_models/annotating_models_index.rst
   download_biomodels/download_biomodels.rst
   APIReference/api_reference_index.rst
   Developers/developers_index.rst

LibOMEXmeta is a library aimed at providing developer-level support for
reading, writing, editing and managing semantic annotations for biosimulation
models.  The `COMBINE modeling community <http://co.mbine.org/>`_  has developed
consensus around how best to annotate models and how to package these models
into archives (OMEX files) that include the modeling source code, the annotations,
files that describe parameters and settings needed for simulations (in a SEDML file),
and potentially the data used for these modeling efforts. This consensus was initially
described in the  publication `"Harmonizing semantic annotations for computational
models in biology" (Briefings in Bioinformatics, 2018) <https://academic.oup.com/bib/article/20/2/540/5164345)>`_.

The goal of semantic annotations are to make explicit the biology that underlies the
semantics of biosimulation models. By using standard knowledge resources about biology
and biological processes (such as CheBI, Uniprot, and ontologies of anatomy), we can
make the models more understandable, reusable and reproducible. More information can
be found at the `OMEX Metadata Specification web page <http://co.mbine.org/standards/omex-metadata>`_.

LibOmexMeta is a C++ library with a C interface that is used to build a Python front end (pyomexmeta). libOmexMeta uses `RDF <https://www.w3.org/RDF/>`_
as a framework for representing these annotations. At the core of libOmexMeta are the `Redland libraries <http://librdf.org/>`_:

    * `raptor2 <http://librdf.org/raptor/>`_ for parsing RDF syntax into RDF graphs and serializing the output
    * `rasqal <http://librdf.org/rasqal/>`_ for querying RDF graphs
    * `librdf <http://librdf.org/>`_ as a front end to raptor2 and rasqal and for triple stores.

Features
========

`Parsers <http://librdf.org/raptor/api-1.4/raptor-parsers.html>`_
------------------------------------------------------------------

  * rdfxml, ntriples, turtle, guess, rdfa, nquads

`Serializers <http://librdf.org/raptor/api-1.4/raptor-serializers.html>`_
-------------------------------------------------------------------------

   * ntriples, turtle, rdfxml-xmp, rdfxml-abbrev, rdfxml, dot, json-triples, json, nquads, html

`Querying <http://librdf.org/rasqal/docs/api/>`_
------------------------------------------------

  * Languages
    * `SPARQL <https://www.w3.org/TR/sparql11-query/>`_
  * Query result formats:
    * xml, json, table, csv, mkr, tsv, html, turtle, rdfxml,

`Storages modules <http://librdf.org/docs/api/redland-storage-modules.html>`_
--------------------------------------------------------------------------------

  * hashes, memory, file, sqlite, uri, tstore (may be supported on request), postgresql (may be uspported on request), virtuoso (may be supported on request)


Platform
========

  * Windows
  * Linux Ubuntu 18.04 / 20.04, untested on other flavours.
  * MacOS

Docker
-------

You can get a docker image using

.. code-block:: bash

    $ docker pull ciaranwelsh/libomexmeta:v1.1.0

This is an Ubuntu 18.04 based container that has libOmexMeta prebuilt and installed
under `/libOmexMeta/install-docker`. See `dockerfile <https://github.com/sys-bio/libOmexMeta/blob/master/Dockerfile>`_ for full set of commands to build libOmexMeta on ubuntu.
Conda is preconfigured and pyomexmeta is installed.


Downloading Binaries
====================

You can download binaries from the `releases tab <https://github.com/sys-bio/libOmexMeta/releases>`_


Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`
