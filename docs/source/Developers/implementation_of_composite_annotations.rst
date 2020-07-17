Implementation of Composite Annotations
========================================

The composite annotation types `Physical*` generate triples objects
when needed and then free's them. This was implemented this way as
it helped avoid memory issues but perhaps a better implementation would be similar to
that in the PersonalInformation class. That is, keep a triples object
at the class level of (say) PhysicalEntity.

