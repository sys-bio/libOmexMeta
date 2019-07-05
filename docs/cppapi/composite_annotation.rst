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
relation (see :ref:`bqb::isPropertyOf`).

.. raw:: html

    <p class="noindent" ><object data="../graphics/composite-annotation1-1.svg" width="423.69516 " height="154.82889 " type="image/svg+xml"><p>SVG-Viewer needed.</p></object>



.. raw:: html

    <p class="noindent" ><object data="../graphics/composite-annotation2-1.svg" width="513.79356 " height="451.47919 " type="image/svg+xml"><p>SVG-Viewer needed.</p></object>

.. doxygenclass:: semsim::CompositeAnnotation
   :members:
