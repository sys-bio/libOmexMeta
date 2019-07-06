# ifndef SEMSIM_MODEL_H_
# define SEMSIM_MODEL_H_

# include "semsim/Preproc.h"
# include "semsim/Component.h"

namespace semsim {

    /**
     * A @ref Component is any element of an SBML or CellML model.
     * It can represent an SBML species, reaction, or compartment.
     */
    class SEMSIM_PUBLIC Model {
      public:
        /// The type used to store the collection of @ref Component "Components". Treat as opaque.
        typedef std::vector<ComponentPtr> Components;

        /// Add a new component to the model (copy)
        Component* addComponent(const Component& component) {
          components_.push_back(ComponentPtr(new Component(component)));
          return &*components_.back();
        }

        # if __cplusplus >= 201103L
        /// Add a new component to the model (move)
        Component* addComponent(Component&& component) {
          components_.emplace_back(new Component(std::move(component)));
          return &*components_.back();
        }
        # endif

        /**
         * Get the collection of components contained in this model.
         * The return type is guaranteed to be iterable.
         * Otherwise, treat it as opaque.
         */
        const Components& getComponents() const {
          return components_;
        }

        /**
         * Get the collection of components contained in this model.
         * The return type is guaranteed to be iterable.
         * Otherwise, treat it as opaque.
         */
        Components& getComponents() {
          return components_;
        }

        /**
         * Get the number of components in the model.
         */
        std::size_t getNumComponents() const {
          return components_.size();
        }

      protected:
        // Stores the @ref Component "Components" for this model.
        Components components_;
    };

}

# endif
