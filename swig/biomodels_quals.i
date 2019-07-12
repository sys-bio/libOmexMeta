namespace semsim {
  class bqb {
    public:
      %immutable;
      static Relation is;
      static Relation hasPart;
      static Relation isPartOf;
      static Relation isVersionOf;
      static Relation hasVersion;
      static Relation isHomologTo;
      static Relation isDescribedBy;
      static Relation isEncodedBy;
      static Relation encodes;
      static Relation occursIn;
      static Relation hasProperty;
      static Relation isPropertyOf;
      static Relation hasTaxon;
  };
}

%pythoncode %{
class bqb_meta(type):
    @property
    def _is(cls):
        return bqb_wrapper._is.fget()
    @property
    def hasPart(cls):
        return bqb_wrapper.hasPart.fget()
    @property
    def isPartOf(cls):
        return bqb_wrapper.isPartOf.fget()
    @property
    def isVersionOf(cls):
        return bqb_wrapper.isVersionOf.fget()
    @property
    def hasVersion(cls):
        return bqb_wrapper.hasVersion.fget()
    @property
    def isHomologTo(cls):
        return bqb_wrapper.isHomologTo.fget()
    @property
    def isDescribedBy(cls):
        return bqb_wrapper.isDescribedBy.fget()
    @property
    def isEncodedBy(cls):
        return bqb_wrapper.isEncodedBy.fget()
    @property
    def encodes(cls):
        return bqb_wrapper.encodes.fget()
    @property
    def occursIn(cls):
        return bqb_wrapper.occursIn.fget()
    @property
    def hasProperty(cls):
        return bqb_wrapper.hasProperty.fget()
    @property
    def isPropertyOf(cls):
        return bqb_wrapper.isPropertyOf.fget()
    @property
    def hasTaxon(cls):
        return bqb_wrapper.hasTaxon.fget()

class bqb(metaclass=bqb_meta):
    pass
%}
