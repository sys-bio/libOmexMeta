.. _composite_annotation:

*******************
CompositeAnnotation
*******************

.. highlight:: c++

A :ref:`CompositeAnnotation` contains two elements:
a :ref:`PhysicalProperty` and an :ref:`Entity`.
The :ref:`PhysicalProperty` describes the type of quantity being modeled, e.g.
molecule concentration (Molar), amount (moles or grams), fluid volume (L), pressure (Pa), etc.
A composite annotation always contains **exactly one** physical property.
When the model is exported to RDF, the physical property will be encoded using an isPropertyOf
relation (see :ref:`bqb::isPropertyOf <Biomodels Qualifiers>`).
The following diagram shows a composite annotation and its two most important elements -
the physical property and entity.

.. raw:: html

    <p class="noindent" style="text-align: center"><object data="../graphics/composite-annotation1-1.svg" width="423.69516 " height="154.82889 " type="image/svg+xml"><p>SVG-Viewer needed.</p></object>

The :ref:`Entity` describes *what* the model element
is and (optionally) *where* it is in the physical world.
An entity contains a *definition URI* which describes what it is
(e.g. a `ChEBI <https://www.ebi.ac.uk/chebi/>`_ identifier for reaction network models or an `FMA <https://bioportal.bioontology.org/ontologies/FMA>`_ identifier for physiological models),
and an optional linear chain of *descriptor terms* which provide further information
that describes *where* the element is in the physical world.
See the documentation of the :ref:`EntityDescriptor` class for an example.
Expanding the :ref:`Entity` part of a composite annotation yields the following diagram:

.. raw:: html

    <p class="noindent" style="text-align: center"><object data="../graphics/composite-annotation2-1.svg" width="513.79356 " height="451.47919 " type="image/svg+xml"><p>SVG-Viewer needed.</p></object>

.. doxygenclass:: semsim::CompositeAnnotation
   :members:
