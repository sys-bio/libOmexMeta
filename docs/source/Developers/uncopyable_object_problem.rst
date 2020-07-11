The "Uncopyable object" problem
===============================

Here I detail why most objects are not copyable and what it would take to
get them copyable.

The crux of the problem is that `librdf_uri*` is not a copyable entity. This is by design in redland.
When you try to create a new `librdf_uri` redland will check the existing uri's and if it finds a match,
it'll return it, instead of making a new one. Note that even the `librdf_new_uri_from_uri` function
which is stated to be a copy constructor in the redland docs, only takes shallow copies. Practically,
this means that redland returns the *same* `librdf_uri` pointer but increments the
`librdf_uri` count attribute.

This has significant implications for pretty much all omexmeta objects, particularly in the annotation creation
API. In order to make copy constructors, the underlying reference counter system must be manipulated correctly.
On the surface this sounds easy, you just add 1 whenever you copy and subtract 1 whenever you delete, unless
the count is at 1 in which case you call `free`. The problem is that the redland libraries are complicated
and the documentation is terrible (and outdated). So this strategy will theoretically work, if you get it right,
but its very easy to get wrong without intimate knowledge of the redland libraries. Really, the whole reference
counter system should be replaced with a `std::shared_ptr` to handle this automatically, but this is not a small
task.

The solution, which isn't ideal but a compromise, is to enforce the objects in the redland c++ wrapper
to be unique by disabling the copy constructor and copy assignment constructor. Note, this is the same strategy employed
by `std::unique_ptr`. Practically, this means that objects must be moved using `std::move` instead of copied. This
is quite a restriction on what is possible and sometimes the most straight forward design needs to be modified
to account for this.
