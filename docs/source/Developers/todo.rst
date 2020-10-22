libOmexMeta ToDo list
======================

This is a list of things that I think will improve libomexmeta and should be considered by developers who continue this work.


    * Implement equality operators for triples, composites and Editor and RDF. Then, change tests that use string comparisons to instead use the equality operator. This will bypass the problem in that different systems/compilers output RDF in arbitrary order which breaks the tests. Note: this has been started in that Triple objects and composite annotations can be compared reliably but editor and RDF objects cannot.

    * Add a "description" to all types of annotation.
















