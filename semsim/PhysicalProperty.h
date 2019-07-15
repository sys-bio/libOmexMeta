# ifndef SEMSIM_PHYSICAL_PROPERTY_H_
# define SEMSIM_PHYSICAL_PROPERTY_H_

# include "semsim/Preproc.h"
# include "semsim/Resource.h"

namespace semsim {
    /**
     * A physical property describes what type of quantity (volume, concentration, Moles,
     * pressure, etc.) a variable in a model represents.
     * Physical properties always point to a single term in the
     * <a href="http://bioportal.bioontology.org/ontologies/OPB">Ontology of Physics for Biology</a>,
     * which can be accessed using the @ref OPB class.
     */
    class SEMSIM_PUBLIC PhysicalProperty {
      public:
        /// Construct from a resource
        PhysicalProperty(const Resource& resource)
          : resource_(resource) {}

        # if __cplusplus >= 201103L
        /// Move-construct from a resource
        PhysicalProperty(Resource&& resource)
          : resource_(std::move(resource)) {}
        # endif

        /// Construct directly from a string that contains the resource URI
        PhysicalProperty(const std::string& resource)
          : resource_(resource) {}

        # if __cplusplus >= 201103L
        /// Move-construct directly from a string that contains the resource URI
        PhysicalProperty(std::string&& resource)
          : resource_(std::move(resource)) {}
        # endif

        /**
         * @return The @ref Resource for this @ref PhysicalProperty.
         */
        const Resource& getResource() const {
          return resource_;
        }

        /**
         * @return The @ref Resource for this @ref PhysicalProperty.
         */
        Resource& getResource() {
          return resource_;
        }

        /**
         * Return a human--readable representation of the annotation
         * information. Ontology terms will be replaced with human-readable
         * names.
         */
        std::string humanize() const {
          return resource_.humanize();
        }

      protected:
        Resource resource_;
    };
}

# endif
