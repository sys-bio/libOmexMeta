Reading RDF
============

Reading RDF graphs revolves around the `from*` and `add_from*` methods,
where the wildcard `*` is one of `string`, `url` or `filename`. The `from*`
methods are static methods and create a new `RDF` graph while the `add_from*` methods add to the
existing `RDF` graph.

When reading RDF, you must pass the name of which parser you would like to use.
The default is the "guess" parser, which will try to figure out which syntax
you've given it. However, the guess parser is imperfect, so if you know which
syntax you are reading, you can specify this as an argument. The accepted
formats are:

    * rdfxml, ntriples, turtle, trig, rss-tag-soup, grddl, guess, rdfa, nquads, guess, ,

Reading from a string
---------------------

.. tabs::

    .. tab:: Python

        .. literalinclude:: from_string_python.py
            :linenos:
            :language: python
            :caption: Read from a string in Python

        .. literalinclude:: ../../ExampleOutputFiles/from_string_python.txt
            :linenos:
            :caption: Output

    .. tab:: C++

        .. literalinclude:: from_string_cpp.cpp
            :linenos:
            :language: C++
            :caption: Read from a string in C++

        .. literalinclude:: ../../ExampleOutputFiles/from_string_cpp.txt
            :linenos:
            :caption: Output

    .. tab:: C

        .. literalinclude:: from_string_c.cpp
            :linenos:
            :language: C
            :caption: Read from a string in C

        .. literalinclude:: ../../ExampleOutputFiles/from_string_c.txt
            :linenos:
            :caption: Output


Adding from a string
--------------------

.. tabs::

    .. tab:: Python

        .. literalinclude:: add_from_string_python.py
            :linenos:
            :language: python
            :caption: Read from a string and add to existing graph in Python

        .. literalinclude:: ../../ExampleOutputFiles/add_from_string_python.txt
            :linenos:
            :caption: Output

    .. tab:: C++


        .. literalinclude:: add_from_string_cpp.cpp
            :linenos:
            :language: C++
            :caption: Read from a string and add to existing graph in C++

        .. literalinclude:: ../../ExampleOutputFiles/add_from_string_cpp.txt
            :linenos:
            :caption: Output

    .. tab:: C

        .. literalinclude:: add_from_string_c.cpp
            :linenos:
            :language: C
            :caption: Read from a string and add to existing graph in C

        .. literalinclude:: ../../ExampleOutputFiles/add_from_string_c.txt
            :linenos:
            :caption: Output


Reading from a file
-------------------

.. tabs::

    .. tab:: Python

        .. literalinclude:: from_file_python.py
            :linenos:
            :language: python
            :caption: Read from a file in Python

        .. literalinclude:: ../../ExampleOutputFiles/from_file_python.txt
            :linenos:
            :caption: Output

    .. tab:: C++

        .. literalinclude:: from_file_cpp.cpp
            :linenos:
            :language: C++
            :caption: Read from a file in C++

        .. literalinclude:: ../../ExampleOutputFiles/from_file_cpp.txt
            :linenos:
            :caption: Output

    .. tab:: C

        .. literalinclude:: from_file_c.cpp
            :linenos:
            :language: C
            :caption: Read from a file in C

        .. literalinclude:: ../../ExampleOutputFiles/from_file_c.txt
            :linenos:
            :caption: Output


Adding from a file
--------------------

.. tabs::

    .. tab:: Python

        .. literalinclude:: add_from_file_python.py
            :linenos:
            :language: python
            :caption: Read from a file and add to existing graph in Python

        .. literalinclude:: ../../ExampleOutputFiles/add_from_file_python.txt
            :linenos:
            :caption: Output

    .. tab:: C++

        .. literalinclude:: add_from_file_cpp.cpp
            :linenos:
            :language: C++
            :caption: Read from a file and add to existing graph in C++

        .. literalinclude:: ../../ExampleOutputFiles/add_from_file_cpp.txt
            :linenos:
            :caption: Output

    .. tab:: C

        .. literalinclude:: add_from_file_c.cpp
            :linenos:
            :language: C
            :caption: Read from a file and add to existing graph in C

        .. literalinclude:: ../../ExampleOutputFiles/add_from_file_c.txt
            :linenos:
            :caption: Output







