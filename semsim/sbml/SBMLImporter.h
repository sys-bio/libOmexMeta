# ifndef SEMSIM_SBML_IMPORTER_H_
# define SEMSIM_SBML_IMPORTER_H_

# include "semsim/Preproc.h"
# include "semsim/sbml/SBMLModel.h"
# include "semsim/sbml/Species.h"
# include "semsim/BiomodelsQualifiers.h"

# include "sbml/SBMLTypes.h"

namespace semsim {

    /**
     * This class allows importing SBML models
     * and converting them into SemSim @ref Model "Models",
     * which contain semantic information about the original
     * SBML model.
     * Most of the functions documented for this class are protected
     * methods used to implement internal logic.
     * Usage of this class is as follows:
     *
     * @code{.cpp}
     * // import the SBML
     * semsim::SBMLImporter importer(d);
     * // get the libSemSim wrapper for the SBML model
     * const semsim::SBMLModel& model = importer.getSBMLModel();
     * // do something with the semsim::SBMLModel
     * @endcode
     */
    class SEMSIM_PUBLIC SBMLImporter {
      public:
      /**
       * Construct a libSemSim @ref SBMLModel from an SBML document.
       * @param d The input SBML document.
       */
      SBMLImporter(LIBSBML_CPP_NAMESPACE_QUALIFIER SBMLDocument* d)
        : m_(d->getModel()), result_(d->getModel()) {
        for(unsigned int k=0; k<m_->getNumCompartments(); ++k) {
          LIBSBML_CPP_NAMESPACE_QUALIFIER Compartment* c = m_->getCompartment(k);
          if (c->isSetIdAttribute())
            result_.setComponentAnnotation(c->getId(), extractAnnotation(c));
        }
        for(unsigned int k=0; k<m_->getNumSpecies(); ++k) {
          LIBSBML_CPP_NAMESPACE_QUALIFIER Species* s = m_->getSpecies(k);
          if (s->isSetIdAttribute())
            result_.setComponentAnnotation(s->getId(), extractAnnotation(s));
        }
      }

      /// Return the @ref SBMLModel converted from this document
      SBMLModel& getSBMLModel() {
        return result_;
      }

      /// Return the @ref SBMLModel converted from this document
      const SBMLModel& getSBMLModel() const {
        return result_;
      }

      static const Relation& getRelationFromSBMLQual(LIBSBML_CPP_NAMESPACE_QUALIFIER BiolQualifierType_t q) {
        switch (q) {
          case LIBSBML_CPP_NAMESPACE_QUALIFIER BQB_IS:
            return bqb::is;
          case LIBSBML_CPP_NAMESPACE_QUALIFIER BQB_HAS_PART:
            return bqb::hasPart;
          case LIBSBML_CPP_NAMESPACE_QUALIFIER BQB_IS_PART_OF:
            return bqb::isPartOf;
          case LIBSBML_CPP_NAMESPACE_QUALIFIER BQB_IS_VERSION_OF:
            return bqb::isVersionOf;
          case LIBSBML_CPP_NAMESPACE_QUALIFIER BQB_HAS_VERSION:
            return bqb::hasVersion;
          case LIBSBML_CPP_NAMESPACE_QUALIFIER BQB_IS_HOMOLOG_TO:
            return bqb::isHomologTo;
          case LIBSBML_CPP_NAMESPACE_QUALIFIER BQB_IS_DESCRIBED_BY:
            return bqb::isDescribedBy;
          case LIBSBML_CPP_NAMESPACE_QUALIFIER BQB_IS_ENCODED_BY:
            return bqb::isEncodedBy;
          case LIBSBML_CPP_NAMESPACE_QUALIFIER BQB_ENCODES:
            return bqb::encodes;
          case LIBSBML_CPP_NAMESPACE_QUALIFIER BQB_OCCURS_IN:
            return bqb::occursIn;
          case LIBSBML_CPP_NAMESPACE_QUALIFIER BQB_HAS_PROPERTY:
            return bqb::hasProperty;
          case LIBSBML_CPP_NAMESPACE_QUALIFIER BQB_IS_PROPERTY_OF:
            return bqb::isPropertyOf;
          case LIBSBML_CPP_NAMESPACE_QUALIFIER BQB_HAS_TAXON:
            return bqb::hasTaxon;
          default:
            throw std::runtime_error("Unknown BioModels qualifier");
        }
      }

      protected:
        /// Extract the annotation for any SBML element
        AnnotationPtr extractAnnotation(LIBSBML_CPP_NAMESPACE_QUALIFIER SBase* s) {
          return AnnotationPtr(new SingularAnnotation(
            extractSingularAnnotation(s)
          ));
        }

        /// Extract the annotation for a species - can be composite using automatic inference logic
        AnnotationPtr extractAnnotation(LIBSBML_CPP_NAMESPACE_QUALIFIER Species* s) {
          try {
            return AnnotationPtr(new CompositeAnnotation(
              extractCompositeAnnotation(s)
            ));
          } catch(std::domain_error) {
            // either the PhysicalProperty or Entity inference failed
            return AnnotationPtr(new SingularAnnotation(
              extractSingularAnnotation(s)
            ));
          }
        }

        /// Extract the annotation for a compartment
        AnnotationPtr extractAnnotation(LIBSBML_CPP_NAMESPACE_QUALIFIER Compartment* c) {
          return AnnotationPtr(new SingularAnnotation(
            extractSingularAnnotation(c)
          ));
        }

        /**
         * Extract a singular annotation from an SBML object.
         * This method is used when a composite annotation cannot be inferred.
         * @param  s The SBML object
         * @return   A singular annotation containing all bqb:is terms as definitions and all other relations as extraneous terms.
         */
        SingularAnnotation extractSingularAnnotation(LIBSBML_CPP_NAMESPACE_QUALIFIER SBase* s) {
          SingularAnnotation result;
          populateDefinitionsAndTerms(s, result);
          return result;
        }

        /**
         * Extract an @ref Entity from an SBML object.
         * Uses identical logic to @ref ExtractSingularAnnotation
         * @param  s The SBML object
         * @return   A singular annotation containing all bqb:is terms as definitions and all other relations as extraneous terms.
         */
        // Entity ExtractEntity(LIBSBML_CPP_NAMESPACE_QUALIFIER SBase* s) {
        //   Entity result;
        //   PopulateDefinitionsAndTerms(s, result);
        //   return result;
        // }

        /**
         * Extract the @ref EntityDescriptor for an SBML species.
         * The @ref EntityDescriptor may contain the enclosing compartment
         * (if any) referenced with a bqb:occursIn qualifier.
         */
        EntityDescriptor extractSpeciesEntityDescriptor(LIBSBML_CPP_NAMESPACE_QUALIFIER Species* s) {
          EntityDescriptor result;
          for (unsigned int k=0; k<m_->getNumCompartments(); ++k) {
            LIBSBML_CPP_NAMESPACE_QUALIFIER Compartment* c = m_->getCompartment(k);
            if (c->isSetIdAttribute() && s->getCompartment() == c->getId()) {
              try {
                result.addTerm(DescriptorTerm(bqb::occursIn, result_.getComponent(s->getId())));
              } catch (std::out_of_range) {
                // no definition uri - do nothing
              }
            }
          }
          return result;
        }

        /**
         * Try to deduce the @ref Entity
         * from an SBML species.
         * If the species is contained in a compartment, the compartment
         * will be included in the @ref EntityDescriptor using the bqb:occursIn qualifier.
         */
        Entity extractSpeciesEntity(LIBSBML_CPP_NAMESPACE_QUALIFIER Species* s) {
          Entity result;
          populateDefinitionsAndTerms(s, result);
          result.addDescriptor(extractSpeciesEntityDescriptor(s));
          return result;
        }

        /// Return a @ref Object weak pointer for the specified object (if it is in the @ref SBMLModel).
        Component* getComponentFor(LIBSBML_CPP_NAMESPACE_QUALIFIER SBase* s) {
          if (s->isSetIdAttribute() && result_.hasComponent(s->getId()))
            return result_.getComponent(s->getId());
          else
            throw std::out_of_range("No such object in model");
        }

        /// Return a @ref Resource for the specified object (if it is in the @ref SBMLModel).
        Resource getResourceFor(LIBSBML_CPP_NAMESPACE_QUALIFIER SBase* s) {
          return Resource(getComponentFor(s));
        }

        /**
         * Populate the *definitions* (URIs specified in CV terms via bqb:is terms)
         * and extraneous terms (URIs specified using any other qualifier)
         * for a @ref SingularAnnotation or @ref Entity in a @ref CompositeAnnotation.
         * @param s The input SBML object
         * @param s The object to populate. Can be either a @ref SingularAnnotation or @ref Entity.
         */
        static void populateDefinitionsAndTerms(LIBSBML_CPP_NAMESPACE_QUALIFIER SBase* s, EntityBase& e) {
          for (unsigned int i=0; i<s->getNumCVTerms(); ++i) {
            LIBSBML_CPP_NAMESPACE_QUALIFIER CVTerm* t = s->getCVTerm(i);
            switch(t->getQualifierType()) {
              case LIBSBML_CPP_NAMESPACE_QUALIFIER MODEL_QUALIFIER:
                // not handled
                break;
              case LIBSBML_CPP_NAMESPACE_QUALIFIER BIOLOGICAL_QUALIFIER:
                // only bqb::is qualifiers can be used to *define* entities
                if (t->getBiologicalQualifierType() == LIBSBML_CPP_NAMESPACE_QUALIFIER BQB_IS) {
                  for (unsigned int i=0; i<t->getNumResources(); ++i) {
                    e.addDefinition(Resource(t->getResourceURI(i)));
                  }
                } else {
                  // all other qualifiers
                  e.addExtraneousTerm(
                    Term(
                      getRelationFromSBMLQual(t->getBiologicalQualifierType()),
                      Resource(t->getResourceURI(i))
                    )
                  );
                }
                break;
              default:
                break;
            }
          }
        }

        /**
         * Extract a composite annotation from an SBML Species.
         * There are several pieces of information libSemSim tries to use to
         * automatically construct composite annotations for SBML species.
         * @li The @ref PhysicalProperty can sometimes be deduced from substance attributes and units. See @ref SpeciesToPhysicalProperty.
         * @li If the species is contained in a compartment, the @ref EntityDescriptor can contain a reference to the compartment with a bqb:occursIn qualifier.
         * @param  s The input SBML species.
         * @return   The automatically inferred composite annotation.
         */
        CompositeAnnotation extractCompositeAnnotation(LIBSBML_CPP_NAMESPACE_QUALIFIER Species* s) {
          return CompositeAnnotation(
            GetSpeciesPhysicalProperty(s,m_),
            extractSpeciesEntity(s)
          );
        }

        LIBSBML_CPP_NAMESPACE_QUALIFIER Model* m_;
        SBMLModel result_;
    };

}

# endif
