Comparing Redland and its C++ Wrapper
=====================================

The Redland Wrapper is a C++ layer around the underlying C libraries
that libOmexMeta depends on. Its not perfect, not is it a comprehensive
Redland Library wrapper, but for our intents and purposed it works.

Here is a demonstration of how to create a new Triple using the
Redland API and the Redland Wrapper.

.. tabs::

    .. tab:: The Redland Library: librdf

        .. literalinclude:: creating_a_rdf_graph_with_a_statement_redland.c
            :language: C
            :caption: Create a triple store, an RDF model and add a triple to the model, using the librdf redland API.

    .. tab:: The Redland Wrapper

        .. literalinclude:: creating_a_rdf_graph_with_a_statement_wrapper.cpp
            :language: C++
            :caption: Create a triple store, an RDF model and add a triple to the model, using the Redland Wrapper.












