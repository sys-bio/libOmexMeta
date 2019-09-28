# ifndef SEMSIM_PARTICIPANT_H_
# define SEMSIM_PARTICIPANT_H_

namespace semsim {

    /**
     * A @ref Participant is the base class of reactants / products in a reaction.
     */
    class SEMSIM_PUBLIC Participant {
      public:
        /// Virtual dtor
        virtual ~Participant() {}
    };

}

# endif
