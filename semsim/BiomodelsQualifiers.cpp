# include "semsim/BiomodelsQualifiers.h"

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
}
