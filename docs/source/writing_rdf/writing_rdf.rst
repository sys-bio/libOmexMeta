Serializing RDF Graphs
======================

Serializing is just a fancy term for writing the information
in an RDF graph to a string or file. There are several syntaxes
that are supported by libOmexMeta, including:

    * ntriples, turtle, rdfxml-xmp, rdfxml-abbrev, rdfxml, dot, json-triples, json, nquads, html


Writing to string
-----------------

.. tabs::

    .. tab:: Python

        .. literalinclude:: writing_to_string_python.py
            :language: python
            :caption: Write to a string in Python

        .. literalinclude:: ../../ExampleOutputFiles/writing_to_string_python.txt
            :caption: Output


    .. tab:: C++

        .. literalinclude:: writing_to_string_cpp.cpp
            :language: C++
            :caption: Write to a string in C++

        .. literalinclude:: ../../ExampleOutputFiles/WritingToStringCpp.txt
            :caption: Output


    .. tab:: C

        .. literalinclude:: writing_to_string_c.cpp
            :language: C
            :caption: Write to a string in C

        .. literalinclude:: ../../ExampleOutputFiles/WritingToStringC.txt
            :caption: Output

Writing to a file
-----------------

.. tabs::

    .. tab:: Python

        .. literalinclude:: writing_to_file_python.py
            :language: python
            :caption: Write to a file in Python

        .. literalinclude:: ../../ExampleOutputFiles/writing_to_file_python.txt
            :caption: Output

    .. tab:: C++

        .. literalinclude:: writing_to_file_cpp.cpp
            :language: C++
            :caption: Write to a file in C++

        .. literalinclude:: ../../ExampleOutputFiles/WritingToFileCpp.txt
            :caption: Output

    .. tab:: C

        .. literalinclude:: writing_to_file_c.cpp
            :language: C
            :caption: Write to a file in C

        .. literalinclude:: ../../ExampleOutputFiles/WritingToFileC.txt
            :caption: Output






