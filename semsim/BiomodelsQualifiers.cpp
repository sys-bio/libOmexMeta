# include "semsim/BiomodelsQualifiers.h"

# include <stdexcept>

namespace semsim {
  const std::string bqb::root = "http://biomodels.net/biology-qualifiers/";

  const Relation bqb::is = Relation(root+"is");
  const Relation bqb::hasPart = Relation(root+"hasPart");
  const Relation bqb::isPartOf = Relation(root+"isPartOf");
  const Relation bqb::isVersionOf = Relation(root+"isVersionOf");
  const Relation bqb::hasVersion = Relation(root+"hasVersion");
  const Relation bqb::isHomologTo = Relation(root+"isHomologTo");
  const Relation bqb::isDescribedBy = Relation(root+"isDescribedBy");
  const Relation bqb::isEncodedBy = Relation(root+"isEncodedBy");
  const Relation bqb::encodes = Relation(root+"encodes");
  const Relation bqb::occursIn = Relation(root+"occursIn");
  const Relation bqb::hasProperty = Relation(root+"hasProperty");
  const Relation bqb::isPropertyOf = Relation(root+"isPropertyOf");
  const Relation bqb::hasTaxon = Relation(root+"hasTaxon");

  std::string bqb::humanizeQualifier(const Relation& q) {
    if (q == bqb::is)
      return "is";
    else if (q == bqb::hasPart)
      return "hasPart";
    else if (q == bqb::isPartOf)
      return "isPartOf";
    else if (q == bqb::isVersionOf)
      return "isVersionOf";
    else if (q == bqb::hasVersion)
      return "hasVersion";
    else if (q == bqb::isHomologTo)
      return "isHomologTo";
    else if (q == bqb::isDescribedBy)
      return "isDescribedBy";
    else if (q == bqb::isEncodedBy)
      return "isEncodedBy";
    else if (q == bqb::encodes)
      return "encodes";
    else if (q == bqb::occursIn)
      return "occursIn";
    else if (q == bqb::hasProperty)
      return "hasProperty";
    else if (q == bqb::isPropertyOf)
      return "isPropertyOf";
    else if (q == bqb::hasTaxon)
      return "hasTaxon";
    else
      throw std::runtime_error("No such qualifier in bqb");
  }
}
