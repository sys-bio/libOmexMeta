# ifndef SEMSIM_SBML_MODEL_H_
# define SEMSIM_SBML_MODEL_H_

# include "semsim/Preproc.h"
# include "semsim/Model.h"

# include "sbml/SBMLTypes.h"
# if __cplusplus >= 201103L
# include <unordered_map>
# else
# include <tr1/unordered_map>
# endif

namespace semsim {

    /**
     * This class represents an SBML model imported into SemSim.
     */
    class SEMSIM_PUBLIC SBMLModel : public Model {
      public:
        /**
         * Construct from an SBML model.
         * Creates libSemSim @ref Component "Components"
         * for all species and compartments in the model
         * and a corresponding mapping table.
         * @param m The SBML model to use for initialization.
         */
        SBMLModel(LIBSBML_CPP_NAMESPACE_QUALIFIER Model* m)
          : Model() {
          // all elements must have meta ids
          assignMetaIds(m_);
          for(unsigned int k=0; k<m->getNumSpecies(); ++k) {
            LIBSBML_CPP_NAMESPACE_QUALIFIER Compartment* c = m->getCompartment(k);
            if (c->isSetIdAttribute()) {
              Component *o = addComponent(Component());
              element_map_.insert(std::make_pair(c, o));
              element_id_map_.insert(std::make_pair(c->getId(), o));
            }
          }
          for(unsigned int k=0; k<m->getNumSpecies(); ++k) {
            LIBSBML_CPP_NAMESPACE_QUALIFIER Species* s = m->getSpecies(k);
            if (s->isSetIdAttribute()) {
              Component *o = addComponent(Component());
              element_map_.insert(std::make_pair(s, o));
              element_id_map_.insert(std::make_pair(s->getId(), o));
            }
          }
        }

        /**
         * Set the annotation of a @ref Component based on SBML id.
         * Do nothing if the id is not mapped.
         * @param id         The id of an SBML element.
         * @param annotation The annotation for the component.
         */
        void setComponentAnnotation(const std::string id, const AnnotationBase& annotation) {
          if (hasComponent(id))
            element_id_map_.find(id)->second->setAnnotation(annotation);
        }

        /**
         * Set the annotation of a @ref Component based on SBML id.
         * Do nothing if the id is not mapped.
         * @param id         The id of an SBML element.
         * @param annotation The annotation for the component.
         */
        void setComponentAnnotation(const std::string id, const AnnotationPtr& annotation) {
          if (hasComponent(id))
            element_id_map_.find(id)->second->setAnnotation(*annotation);
        }

        # if __cplusplus >= 201103L
        /**
         * Set the annotation of a @ref Component based on SBML id.
         * Do nothing if the id is not mapped.
         * @param id         The id of an SBML element.
         * @param annotation The annotation for the component.
         */
        void setComponentAnnotation(const std::string id, AnnotationPtr&& annotation) {
          if (hasComponent(id))
            element_id_map_.find(id)->second->setAnnotation(std::move(annotation));
        }
        # endif

        /**
         * Check whether a @ref Component exists for the given SBML id.
         * (species and compartments should return true).
         * @param  id The id of an SBML element.
         * @return    Whether the SBML element has been mapped to a libSemSim @ref Component or not.
         */
        bool hasComponent(const std::string id) const {
          return !(element_id_map_.find(id) == element_id_map_.end());
        }

        /**
         * Return the component corresponding to the given SBML element id (if it exists in the mapping table).
         * Compartments and species should exist in the mapping table.
         * @param  id The id of an SBML element.
         * @return    The component for the given SBML id (if it exists).
         */
        const Component* getComponent(const std::string id) const {
          if (!hasComponent(id))
            throw std::out_of_range("Component does not exist in mapping table");
          return element_id_map_.find(id)->second;
        }

        /**
         * Return the component corresponding to the given SBML element id (if it exists in the mapping table).
         * Compartments and species should exist in the mapping table.
         * @param  id The id of an SBML element.
         * @return    The component for the given SBML id (if it exists).
         */
        Component* getComponent(const std::string id) {
          if (!hasComponent(id))
            throw std::out_of_range("Component does not exist in mapping table");
          return element_id_map_.find(id)->second;
        }
      protected:
        /// Maps SBML model elements to corresponding libSemSim @ref Component.
        SEMSIM_TR1_NAMESPACE_QUAL unordered_map<LIBSBML_CPP_NAMESPACE_QUALIFIER SBase*,Component*> element_map_;
        /// Maps SBML model elements to corresponding libSemSim @ref Component.
        SEMSIM_TR1_NAMESPACE_QUAL unordered_map<std::string,Component*> element_id_map_;
    };

}

# endif
