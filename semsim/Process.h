# ifndef SEMSIM_PROCESS_H_
# define SEMSIM_PROCESS_H_

# include "semsim/Preproc.h"
# include "semsim/Component.h"

# include <string>

namespace semsim {

    /**
     * A @ref Process is a component that represents a physical process.
     * It has sources and sinks, as well as its own annotation element.
     */
    class SEMSIM_PUBLIC Process : public Component {
      public:
        /// Empty constructor
        Process() {}

        /// Construct from a singular annotation
        Process(const SingularAnnotation& annotation)
          : Component(annotation) {}

        # if __cplusplus >= 201103L
        /// Move-construct from a singular annotation
        Process(SingularAnnotation&& annotation)
          : Component(std::move(annotation)) {}
        # endif

        /// Construct from a composite annotation
        Process(const CompositeAnnotation& annotation)
          : Component(annotation) {}

        # if __cplusplus >= 201103L
        /// Move-construct from a composite annotation
        Process(CompositeAnnotation&& annotation)
          : Component(std::move(annotation)) {}
        # endif

        Process(const Process& other)
          : Component(other) {}

        # if __cplusplus >= 201103L
        /// Move-construct from a component
        Process(Process&& other)
          : Component(std::move(other)) {}
        # endif


        /**
         * Serialize this annotation to RDF using the Raptor library.
         * @param sbml_base_uri   The base URI of the SBML document relative to this (e.g. a relative path in a COMBINE archive).
         * @param world      Raptor world object. Must be initialized prior to calling this function.
         * @param serializer Raptor serializer object. Must be initialized prior to calling this function.
         * @return the URI for this entity.
         */
        virtual void serializeToRDF(const URI& sbml_base_uri, raptor_world* world, raptor_serializer* serializer) const {
          getAnnotation().serializeToRDF(sbml_base_uri, world, serializer);
        }

      };

}

# endif
