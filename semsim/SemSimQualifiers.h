# ifndef SEMSIM_SEMSIM_QUALIFIERS_H_
# define SEMSIM_SEMSIM_QUALIFIERS_H_


# include "semsim/Relation.h"

namespace semsim {

    /**
     * This class contains all the SemSim qualifiers.
     */
    class semsim {
    public:
         static std::string root;

         static Relation hasSinkParticipant;
         static Relation hasSourceParticipant;
         static Relation hasMediatorParticipant;
         static Relation hasMultiplier;
         static Relation hasPhysicalEntityReference;
         static Relation hasSBOTerm;
         static Relation hasValue;
    };
}
# endif
