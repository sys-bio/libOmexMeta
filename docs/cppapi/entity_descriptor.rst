.. _entity_descriptor:

****************
EntityDescriptor
****************

An :ref:`EntityDescriptor` describes "what" a model element is and "where" it is located in the physical world.
An entity descriptor is essentially a linear chain of descriptor terms joined by
*structural relations*, which are `BioModels qualifiers <http://co.mbine.org/standards/qualifiers>`_ that describe the relationship between subsequent entries in the descriptor term sequence.
For example, if an annotation describes *cytosolic glucose concentration in a pancreatic beta cell*, then
the entity descriptor would be:

.. raw:: html

    <p class="noindent" style="text-align: center"><object data="../graphics/descriptor-example-1.svg" width="568.33885 " height="51.32285 " type="image/svg+xml"><p>SVG-Viewer needed.</p></object>

Consider another example from an physiological model.
Suppose the model contains a variable that represents the
*volume of blood in the left ventricle*:

.. raw:: html

    <p class="noindent" style="text-align: center"><object data="../graphics/descriptor-example2-1.svg" width="262.13062 " height="51.32285 " align="center" type="image/svg+xml"><p>SVG-Viewer needed.</p></object>

.. highlight:: c++

.. doxygenclass:: semsim::EntityDescriptor
   :members:
