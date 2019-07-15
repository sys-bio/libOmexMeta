# include "semsim/Relation.h"
# include "semsim/BiomodelsQualifiers.h"

namespace semsim {
  std::string Relation::humanize() const {
    return bqb::humanizeQualifier(*this);
  }
}
