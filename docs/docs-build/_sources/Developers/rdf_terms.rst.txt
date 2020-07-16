LibrdfNode Vs Subject/predicate/resource
========================================

There is some duplicated functionality in OmexMeta which arose out of adapting
the original design to unforeseen complications. `Subject`, `Predicate` and `Resource`
objects all exist for the primary purpose of instantiating a `LibrdfNode`, which
contains a `librdf_node*` and is the base component of a `librdf_statement`. The original
intent was that `Subject`, `Predicate` and `Resource` place another layer of abstraction
on top of `LibrdfNode` for convenience and quality control - i.e. a `Predicate` can
only be a `Uri` type node while `Resource` can be any of `blank`, `uri` or `literal`.
The reality is that `LibrdfNode` is already quite convenient as it has some static methods
for creating each type of node. For future improvements, it may be good to think about
how we can consolidate the functionality provided by these two layers (`LibrdfNode` vs
`Subject/Predicate/Resource`) in the creation of `LibrdfNode`s.
