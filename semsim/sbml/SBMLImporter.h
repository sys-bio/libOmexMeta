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
     */
    class SEMSIM_PUBLIC SBMLImporter {
      public:
        SBMLImporter(LIBSBML_CPP_NAMESPACE_QUALIFIER SBMLDocument* d)
          : m_(d->getModel()) {
            for(unsigned int k=0; k<m->getNumSpecies(); ++k) {
              LIBSBML_CPP_NAMESPACE_QUALIFIER Species* s = m->getSpecies(k);
              result.addComponent(Component(
                CVToAnnotation(s)
              ));
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
        AnnotationPtr ExtractAnnotation(LIBSBML_CPP_NAMESPACE_QUALIFIER SBase* s, LIBSBML_CPP_NAMESPACE_QUALIFIER Model* m) {
          return AnnotationPtr(new SingularAnnotation(
            ExtractSingularAnnotation(s);
          ));
        }

        /// Extract the annotation for a species - can be composite using automatic inference logic
        AnnotationPtr ExtractAnnotation(LIBSBML_CPP_NAMESPACE_QUALIFIER Species* s) {
          try {
            return ExtractCompositeAnnotation(s);
          } catch(std::domain_error) {
            // either the PhysicalProperty or Entity inference failed
            return ExtractSingularAnnotation(s);
          }
        }

        /**
         * Extract a singular annotation from an SBML object.
         * This method is used when a composite annotation cannot be inferred.
         * @param  s The SBML object
         * @return   A singular annotation containing all bqb:is terms as definitions and all other relations as extraneous terms.
         */
        SingularAnnotation ExtractSingularAnnotation(LIBSBML_CPP_NAMESPACE_QUALIFIER SBase* s) {
          SingularAnnotation result;
          PopulateDefinitionsAndTerms(s, result);
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
        EntityDescriptor ExtractSpeciesEntityDescriptor(LIBSBML_CPP_NAMESPACE_QUALIFIER Species* s) {
          EntityDescriptor result;
          for (unsigned int k=0; k<m_->getNumCompartments(); ++k) {
            LIBSBML_CPP_NAMESPACE_QUALIFIER Compartment* c = m_->getCompartment(k);
            if (c->isSetIdAttribute() && s->getCompartment() == c->getId()) {
              try {
                result.addTerm(DescriptorTerm(bqb::occursIn, GetDefinitionURIFor(s)));
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
        Entity ExtractSpeciesEntity(LIBSBML_CPP_NAMESPACE_QUALIFIER Species* s) {
          Entity result;
          PopulateDefinitionsAndTerms(s, result);
          result.addDescriptor(ExtractSpeciesEntityDescriptor(s));
          return result;
        }

        /// Find a Compartment from a given sid; throw if not found
        LIBSBML_CPP_NAMESPACE_QUALIFIER Compartment* GetDefinitionURIFor(LIBSBML_CPP_NAMESPACE_QUALIFIER SBase* s) {
          for (unsigned int i=0; i<s->getNumCVTerms(); ++i) {
            LIBSBML_CPP_NAMESPACE_QUALIFIER CVTerm* t = s->getCVTerm(i);
            switch(t->getQualifierType()) {
              case LIBSBML_CPP_NAMESPACE_QUALIFIER MODEL_QUALIFIER:
                // not handled
                break;
              case LIBSBML_CPP_NAMESPACE_QUALIFIER BIOLOGICAL_QUALIFIER:
                // only bqb::is qualifiers can be used to *define* entities
                if (t->getBiologicalQualifierType() == LIBSBML_CPP_NAMESPACE_QUALIFIER BQB_IS)
                  return Resource(t->getResourceURI(i));
              default:
                break;
            }
          }
          throw std::out_of_range("No definition URI for element");
        }

        /**
         * Populate the *definitions* (URIs specified in CV terms via bqb:is terms)
         * and extraneous terms (URIs specified using any other qualifier)
         * for a @ref SingularAnnotation or @ref Entity in a @ref CompositeAnnotation.
         * @param s The input SBML object
         * @param s The object to populate. Can be either a @ref SingularAnnotation or @ref Entity.
         */
        static void PopulateDefinitionsAndTerms(LIBSBML_CPP_NAMESPACE_QUALIFIER SBase* s, EntityBase& e) {
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
        CompositeAnnotation ExtractCompositeAnnotation(LIBSBML_CPP_NAMESPACE_QUALIFIER Species* s) {
          return CompositeAnnotation(
            GetSpeciesPhysicalProperty(s,m_),
            ExtractSpeciesEntity(s,m_)
          );
        }

        LIBSBML_CPP_NAMESPACE_QUALIFIER Model* m_;
        SBMLModel result_;
    };

}

# endif
