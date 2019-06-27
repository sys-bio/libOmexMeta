# ifndef SEMSIM_COMPONENT_H_
# define SEMSIM_COMPONENT_H_

# include "semsim/definitions/SemSimTypes.h"
# include "semsim/SemSimObject.h"
# include "semsim/URI.h"

# include <string>

namespace semsim {
    /**
     * A SemSimComponent is a {@link SemSimObject} that includes
     * semantic features. The most important feature of a component
     * is its definition URI, which is specified by an annotation.
     */
    class SemSimComponent : public SemSimObject {

      protected:
        URI referenceuri;

      public:
        virtual ~SemSimComponent() {}

        // SemSimComponent(SemSimTypes type);

        /**
         * Copy constructor.
         * @param other The SemSimComponent to copy
         */
        // SemSimComponent(const SemSimComponent& other);

        /**
         * Whether this component has an annotation that defines
         * its semantic meaning, either physically (for entities
         * that represent physical quantities) or otherwise.
         * @return Whether this component has a semantic definition (supplied via an annotation)
         */
        bool hasDefinitionAnnotation();

        /** @return Whether the component is a physical component. Method
         * is overriden by subclasses. */
        // bool isPhysicalComponent();

        /**
         * Add the component to a specified {@link SemSimModel}
         * @param model The specified {@link SemSimModel}
         * @return The SemSimComponent added to the model
         */
        // const SemSimComponent& addToModel(SemSimModel& model) = 0;
    };
}

# endif
