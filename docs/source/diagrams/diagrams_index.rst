Building Diagrams
=================

Diagrams of the RDF graph can be produced because the Redland libraries
support serializing to `dot` format, the format used by graphviz. Therefore
using Python, it is trivial to serialize to dot and then draw the diagram
using graphviz. Here is an example where we download the `Teusink2000` glycolysis
model, use an sqlite3 database as a triple store and produce a graph
of the Teusink annotations.


.. tabs::

    .. tab:: Python

        .. literalinclude:: draw_teusink2000.py
            :linenos:
            :language: python
            :caption: Example of drawing a diagram of the RDF graph using graphviz in Python

        Output:

        .. image:: TeusinkDiagram.png
            :width: 400

    .. tab:: C++

        This feature is not yet supported in C++

    .. tab:: C

        This feature is not yet supported in C



