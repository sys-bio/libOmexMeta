Errors and Logging
====================

By default, ``libOmexMeta`` and its dependencies ``librdf``, ``raptor`` and ``sparql``
log information, errors and warnings to console. In the following, an error is produced
because the ``rdfxml`` string is being treated as ``turtle`` syntax.

.. tabs::

    .. tab:: Python

        .. literalinclude:: logging1_python.py
            :language: python
            :caption: Information, warnings and errors are logged to console by libOmexMeta and its dependencies

        .. literalinclude:: ../../ExampleOutputFiles/logging1_python.txt
            :caption: Output


    .. tab:: C++

        .. literalinclude:: logging1_cpp.cpp
            :language: C++
            :caption: Information, warnings and errors are logged to console by libOmexMeta and its dependencies

        .. literalinclude:: ../../ExampleOutputFiles/Logging1Cpp.txt
            :caption: Output


    .. tab:: C

        .. literalinclude:: logging1_c.cpp
            :language: C
            :caption: Information, warnings and errors are logged to console by libOmexMeta and its dependencies

        .. literalinclude:: ../../ExampleOutputFiles/Logging1C.txt
            :caption: Output

Logging Levels
--------------

The default logging level is ``warn`` which will cause libOmexMeta to display all
logging messages with a precedence level equal to or greater than ``warn``. The logging
levels and their precedence levels are:

    - ``trace``     = 0
    - ``debug``     = 1
    - ``info``      = 2
    - ``warn``      = 3
    - ``err``       = 4
    - ``critical``  = 5
    - ``off``       = 6

Users can choose their preferred logging level.

.. tabs::

    .. tab:: Python

        .. literalinclude:: logging2_python.py
            :language: python
            :caption: How to change the logging level python

        .. literalinclude:: ../../ExampleOutputFiles/logging2_python.txt
            :caption: Output


    .. tab:: C++

        .. literalinclude:: logging2_cpp.cpp
            :language: C++
            :caption: How to change the logging level C++

        .. literalinclude:: ../../ExampleOutputFiles/Logging2Cpp.txt
            :caption: Output


    .. tab:: C

        .. literalinclude:: logging2_c.cpp
            :language: C
            :caption: How to change the logging level C

        .. literalinclude:: ../../ExampleOutputFiles/Logging2C.txt
            :caption: Output


Custom Formatting
-------------------

Users can choose how the logging messages are formatted. Logging in libOmexMeta is handled by a dependency
library called `spdlog <https://github.com/gabime/spdlog>`_. Users should see
`their documentation <https://github.com/gabime/spdlog/wiki/3.-Custom-formatting#pattern-flags>`_
for a list of valid formatting symbols and their purpose.

.. tabs::

    .. tab:: Python

        .. literalinclude:: logging3_python.py
            :language: python
            :caption: Custom formatting for the logger

        .. literalinclude:: ../../ExampleOutputFiles/logging3_python.txt
            :caption: Output


    .. tab:: C++

        .. literalinclude:: logging3_cpp.cpp
            :language: C++
            :caption: Custom formatting for the logger

        .. literalinclude:: ../../ExampleOutputFiles/Logging3Cpp.txt
            :caption: Output


    .. tab:: C

        .. literalinclude:: logging3_c.cpp
            :language: C
            :caption: Custom formatting for the logger

        .. literalinclude:: ../../ExampleOutputFiles/Logging3C.txt
            :caption: Output


Switching to the file logger
----------------------------

Users can optionally redirect logging messages to a file of their choosing. Activating the file logger
automatically deactivates the console logger, and reactivating the console logger disables the file logger.
Properties such as current logging level and formatting strings are preserved when
switching between the file and console loggers.


.. tabs::

    .. tab:: Python

        .. literalinclude:: logging4_python.py
            :language: python
            :caption: Switching between file and console logging

        .. literalinclude:: ../../ExampleOutputFiles/logging4_python.txt
            :caption: Output


    .. tab:: C++

        .. literalinclude:: logging4_cpp.cpp
            :language: C++
            :caption: Switching between file and console logging

        .. literalinclude:: ../../ExampleOutputFiles/Logging4Cpp.txt
            :caption: Output


    .. tab:: C

        .. literalinclude:: logging4_c.cpp
            :language: C
            :caption: Switching between file and console logging

        .. literalinclude:: ../../ExampleOutputFiles/Logging4C.txt
            :caption: Output


Using the logger
-----------------

The logger is also available for use in your own programs.



.. tabs::

    .. tab:: Python

        .. literalinclude:: logging5_python.py
            :language: python
            :caption: Using the logger

        .. literalinclude:: ../../ExampleOutputFiles/logging5_python.txt
            :caption: Output


    .. tab:: C++

        .. literalinclude:: logging5_cpp.cpp
            :language: C++
            :caption: Using the logger

        .. literalinclude:: ../../ExampleOutputFiles/Logging5Cpp.txt
            :caption: Output


    .. tab:: C

        .. literalinclude:: logging5_c.cpp
            :language: C
            :caption: Using the logger

        .. literalinclude:: ../../ExampleOutputFiles/Logging5C.txt
            :caption: Output







