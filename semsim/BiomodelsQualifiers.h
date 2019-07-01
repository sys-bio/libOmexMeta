# ifndef SEMSIM_BIOMODELS_QUALIFIERS_H_
# define SEMSIM_BIOMODELS_QUALIFIERS_H_

# include "semsim/Preproc.h"
# include "semsim/Relation.h"

namespace semsim {

    /**
     * This class contains all members from the collection of
     * <a href="http://co.mbine.org/standards/qualifiers">BioModels biolocial qualifers</a>.
     * The members are:
     *
     * @code{.cpp}
     * Relation qual = bqb::encodes;
     * Relation qual = bqb::hasPart;
     * Relation qual = bqb::hasProperty;
     * Relation qual = bqb::hasVersion;
     * Relation qual = bqb::is;
     * Relation qual = bqb::isDescribedBy;
     * Relation qual = bqb::isEncodedBy;
     * Relation qual = bqb::isHomologTo;
     * Relation qual = bqb::isPartOf;
     * Relation qual = bqb::isPropertyOf;
     * Relation qual = bqb::isVersionOf;
     * Relation qual = bqb::occursIn;
     * Relation qual = bqb::hasTaxon;
     * @endcode
     */
    class SEMSIM_PUBLIC bqb {
      public:
        SEMSIM_CONSTEXPR static std::string root = "http://biomodels.net/biology-qualifiers/";

        SEMSIM_CONSTEXPR static Relation is = Relation(root+"is");
    };
}
# endif
