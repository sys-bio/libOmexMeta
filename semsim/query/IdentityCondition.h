# ifndef SEMSIM_QUERY_IDENTITY_CONDITION_H_
# define SEMSIM_QUERY_IDENTITY_CONDITION_H_

#include <semsim/EntityBase.h>

#include <utility>
# include "semsim/Resource.h"

namespace semsim {

    /**
     * The base class for all conditions in queries.
     */
    class SEMSIM_PUBLIC IdentityCondition {
    public:
        /// Construct a matching rule for the given resource.
        explicit IdentityCondition(Resource resource)
                : resource_(std::move(resource)) {}

        /// @return @c true if the condition matches the given element.
        virtual bool matches(const Component &component) const {
            if (component.hasCompositeAnnotation())
                return matchEntity(component.getCompositeAnnotation().getEntity());
            else
                return matchEntity(component.getSingularAnnotation());
        }

        /// @return @c true if the entity matches the resource of this condition.
        bool matchEntity(const EntityBase &entity) const {
            return resource_.matchesDefinition(entity);
        }

    protected:
        Resource resource_;
    };

}

# endif
