# include "semsim/SemSimQualifiers.h"

# include <stdexcept>

namespace semsim {
  const std::string semsim::root = "http://www.bhi.washington.edu/SemSim#";

  const Relation semsim::hasSinkParticipant = Relation(root+"hasSinkParticipant");
  const Relation semsim::hasSourceParticipant = Relation(root+"hasSourceParticipant");
  const Relation semsim::hasMediatorParticipant = Relation(root+"hasMediatorParticipant");
  const Relation semsim::hasMultiplier = Relation(root+"hasMultiplier");
  const Relation semsim::hasPhysicalEntityReference = Relation(root+"hasPhysicalEntityReference");
  const Relation semsim::hasSBOTerm = Relation(root+"hasSBOTerm");
  const Relation semsim::hasValue = Relation(root+"hasValue");

}
