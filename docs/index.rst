.. SemSim documentation master file

libSemSim: Enabling Better Semantic Information in Systems Biology Models
======================================================================

Introduction
============

Traditionally, biological models have often been constructed with more
attention to the *mathematical* detail of their encoding than
the *biological* concepts they represent.

Consider models in the online `BioModels repository <https://www.ebi.ac.uk/biomodels/>`_.
These models are encoded in the `Systems Biology Markup Language (SBML) <http://sbml.org/Main_Page>`_,
which describes the states ("species" in SBML) and processes ("reactions" in SBML) that make up a dynamical system.
From a purely mathematical perspective, this state/process representation can be translated directly
into a set of differential equations (for deterministic simulations) or master equations (for stochastic simulations).
This, the following would be a valid SBML model (using `Antimony <http://antimony.sourceforge.net/>`_ syntax):

::

  # a reaction J0 converts A to B
  var species A, B, C
  J0: A -> B; k*A*B*C
  # variable initializations
  A = 10
  B = 0
  C = 1
  k = 1

However, this example is completely nonsensical from a biological perspective.
What are the quantities A, B, and C? What is the process J0?
To encode this information, SBML uses controlled-vocabulary (CV) terms to connect
model elements to *resources*, which are URIs that point to ontology terms
describing what the elements are intended to represent in the physical world.
In the preceding example, assume that the reaction in question was
the conversion of phosphoenol pyruvate (`A`) to pyruvate (`B`) by the enzyme pyruvate kinase (`C`).
Chemical entities such as metabolites can be described via the ChEBI database:
the `CHEBI:18021 <https://identifiers.org/CHEBI:18021>`_ term describes phosphoenol pyruvate
and `CHEBI:15361 <https://identifiers.org/CHEBI:15361>`_ describes pyruvate.
The pyruvate kinase enzyme can be described by the `Protein Ontology (PR) <http://bioportal.bioontology.org/ontologies/PR?p=summary>`_ as
`PR_000023655 <https://identifiers.org/pr/PR:000023655>`_ (if amino acid sequence / organism of origin is not important)
or `UniProt <https://www.uniprot.org/>`_ (if amino acid sequence / organism *is* important).
Using these ontology terms, we can encode the *chemical identity* of the variables
in the model, but there are still quite a few key pieces of biological information that are missing.
*Where* does this reaction take place? *What* type(s) of cell does it occur in?
Some of this information can also be encoded in / extracted from SBML with some difficulty, but not in a form suitable
for automated semantic logic (such as would be possible using `OWL <https://www.w3.org/TR/owl2-overview/>`_).

Semantic annotations play an even more important role in CellML models.
Unlike SBML, CellML does not have a structured way of specifying what model elements represent
(abstractions such as species, reactions, and comaprtments are lost).
Thus, semantic annotations are the only way to establish biological meaning in CellML models.

To address these drawbacks, we previously developed `SimSem/SemGen <http://sbp.bhi.washington.edu/projects/semgen>`_.
SemSim is a library for working with semantic annotations in SBML and CellML models, and SemGen
is a GUI application for annotating models :cite:`10.1093/bioinformatics/bty829`.
Both SemSim and SemGen were written in Java.
This project (libSemSim) aims to provide a C++ / Python (via an extension module) implementation with a lean / reduced feature set.

In both projects (Java/C++), the main goal is to provide a tool for working with *composite annotations*,
which are designed to address the limitations of current annotation systems in CellML and SBML.
We have previously described the benefits and use cases of composite annotations
:cite:`gennari2011multiple,neal2018harmonizing`.

Basic Usage
===========

There are two principal classes in libSemSim: :ref:`SingularAnnotation` and :ref:`CompositeAnnotation`.
Singular annotations are equivalent to traditional MIRIAM annotations :cite:`Novere2005` (using SBML CV terms) and are only useful for linking
model elements to ontology terms.
They allow the user to describe the *chemical identity* of an SBML species (for example).
Composite annotations are much more expressive.
In addition to describing the chemical identity of a model element, they
allow for describing *physical quantity* being modeled (is it a molecule concentration or amount?),
the *physical domain* where the model element occurs (e.g. the cytosol, nucleus, mitochondrion intermembrane space, etc.),
and the *cell type* being model (e.g. a pancreatic beta cell).
While SBML currently allows expressing some (but not all) of these concepts, extracting this
information requires considerable effort.
On the other hand, libSemSim uses RDF files contained in `COMBINE Archives <https://combinearchive.org/index/>`_ for encoding all annotation`information.
The RDF content is suitable for querying or using with semantic reasoning engines such as `OWL <https://www.w3.org/OWL/>`_.`

Reading / Constructing Models
=============================

:ref:`Models <Model>` in libSemSim are essentially shadowed copies of SBML or CellML models
containing additional semantic information encoded in the two major annotation classes mentioned above.
In most cases, you will construct a libSemSim model by first reading in an SBML or CellML model,
adding semantic information via :ref:`CompositeAnnotations <CompositeAnnotation>`, and writing the results
to a COMBINE Archive containing the original SBML / CellML model and an RDF file containing all annotation information.
By default, libSemSim will strip the annotation information out of an SBML or CellML model and encode it in RDF instead.

TODO: code example

.. toctree::
   :maxdepth: 3
   :caption: Contents:

   cppapi/index.rst
   examples/index.rst

References
==========

.. bibliography:: refs.bib
   :cited:
   :style: plain

Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`
