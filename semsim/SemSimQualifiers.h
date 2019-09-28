# ifndef SEMSIM_SEMSIM_QUALIFIERS_H_
# define SEMSIM_SEMSIM_QUALIFIERS_H_

# include "semsim/Preproc.h"
# include "semsim/Relation.h"

namespace semsim {

    /**
     * This class contains all the SemSim qualifiers.
     */
    class SEMSIM_PUBLIC semsim {
      public:
        const static std::string root;

        const static Relation hasSinkParticipant;
        const static Relation hasSourceParticipant;
        const static Relation hasMediatorParticipant;
        const static Relation hasMultiplier;
        const static Relation hasPhysicalEntityReference;
        const static Relation hasSBOTerm;
        const static Relation hasValue;
    };
}
# endif
