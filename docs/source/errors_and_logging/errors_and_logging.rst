Errors and Logging
====================

Errors from libOmexMeta and dependency libraries librdf, raptor and rasqal
by default write to the console but can be redirected to a file instead.
There are 7 logging levels used - in order of precedence, they are:

    - trace = 0
    - debug = 1
    - info = 2
    - warn = 3
    - err = 4
    - critical = 5
    - off = 6

To set the logging level:

.. tabs::

    .. tab:: Python

        .. literalinclude:: change_logging_level.py
            :lanuage: python
            :caption: How to change the logging level








