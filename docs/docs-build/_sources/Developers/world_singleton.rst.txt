The `World` Singleton
=====================

`Librdf` is a convenience API around both `raptor2` and `rasqal`, with some additional
triple store capabilities. Each of these three libraries has a `*_world` object, which
is of central importance to their use. Practically, this meant that in my initial implementation
I had to use the `world` argument all over the place. For instance, creating a `triple` required
using the `librdf_world*` 4 times, once for each of the RDF terms and again for the `librdf_statement`.

Instead of creating this ulgy API, I decided to make the `redland::World` class who's job it is to instantiate
the `librdf_world` the first time it is called and then retrieve it each subsequent time. This design pattern
is called a `Singleton`. It is very "googleable" and has some harsh criticisms, however, in this situation I
believe it has been used correctly and effectively such that it dramatically improves the API by enabling the
hiding away of directly passing `librdf_world*` to objects that need them.

It should always be remembered that there is only ever a single `librdf_world`. You can have multiple RDF
graphs in memory at once (i.e. multiple `RDF` classes instantiated) but they will always be sharing a central
`librdf_world`.

