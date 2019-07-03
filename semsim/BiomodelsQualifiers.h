# ifndef SEMSIM_BIOMODELS_QUALIFIERS_H_
# define SEMSIM_BIOMODELS_QUALIFIERS_H_

# include "semsim/Preproc.h"
# include "semsim/Relation.h"

namespace semsim {

    /**
     * This class contains all members from the collection of
     * <a href="http://co.mbine.org/standards/qualifiers">BioModels biolocial qualifers</a>.
     * BioModels biology qualifiers are used as predicates in RDF to annotation singular and composite annotations.
     * The most important relation is @c bqb::is, which is used to *define* elements in a model.
     * When building annotations, you should always define elements with a single
     * definition URI using @ref EntityBase::addDefinition "SingularAnnotation::addDefinition"
     * or @ref EntityBase::addDefinition "Entity::addDefinition" on the @ref Entity
     * object contained in a @ref CompositeAnnotation (which you can get using @ref CompositeAnnotation::getEntity).
     * When you define elements using one of these functions, the definitions will
     * automatically use the @c bqb::is qualifier.
     *
     * Another important qualifier is @c bqb::isPropertyOf. This is automatically
     * inserted by libSemSim when serializing the @ref PhysicalProperty of
     * @ref CompositeAnnotation "CompositeAnnotations".
     *
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
    class __attribute__ ((visibility ("default"))) bqb {
      public:
        const static std::string root;

        __attribute__ ((visibility ("default"))) const static Relation is;
        const static Relation hasPart;
        const static Relation isPartOf;
        const static Relation isVersionOf;
        const static Relation hasVersion;
        const static Relation isHomologTo;
        const static Relation isDescribedBy;
        const static Relation isEncodedBy;
        const static Relation encodes;
        const static Relation occursIn;
        const static Relation hasProperty;
        const static Relation isPropertyOf;
        const static Relation hasTaxon;
    };
}
# endif
