The Error System
================

There are a lot of room for improvements here. Errors in OmexMeta are simply
a string with the error type being called, the function in which it is called
and the error message. The error messages given are designed to be as
helpful as possible, but I have not invested time in making it more convenient.
It would be nice to have a set of macro's we could use for this purpose, and dare
I say it - tracebacks. I miss Python.