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
        /// Import a model from an SBML document
        SBMLModel importSBMLDocument(LIBSBML_CPP_NAMESPACE_QUALIFIER SBMLDocument* d) {
          SBMLModel result;
          LIBSBML_CPP_NAMESPACE_QUALIFIER Model* m=d->getModel();
          for(unsigned int k=0; k<m->getNumSpecies(); ++k) {
            LIBSBML_CPP_NAMESPACE_QUALIFIER Species* s = m->getSpecies(k);
            result.addComponent(Component(
              CVToAnnotation(s)
            ));
          }
          return result;
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
          for (unsigned int k=0; k<m->getNumCompartments(); ++k) {
            LIBSBML_CPP_NAMESPACE_QUALIFIER Compartment* c = m->getCompartment(k);
            if (c->isSetIdAttribute() && s->getCompartment() == c->getId())
              return ExtractCompositeAnnotation
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
                    result.addDefinition(Resource(t->getResourceURI(i)));
                  }
                } else {
                  // all other qualifiers
                  result.addExtraneousTerm(
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
          return result;
        }

        /**
         * Extract a composite annotation from an SBML Species.
         * There are several pieces of information libSemSim tries to use to
         * automatically construct composite annotations for SBML species.
         * @li The @ref PhysicalProperty can sometimes be deduced from substance attributes and units. See @ref SpeciesUnitsToPhysicalProperty.
         * @li If the species is contained in a compartment, the @ref EntityDescriptor can contain a reference to the compartment with a bqb:occursIn qualifier.
         * @param  s The input SBML species.
         * @return   The automatically inferred composite annotation.
         */
        CompositeAnnotation ExtractCompositeAnnotation(LIBSBML_CPP_NAMESPACE_QUALIFIER Species* s) {
          SingularAnnotation result;
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
                    result.addDefinition(Resource(t->getResourceURI(i)));
                  }
                } else {
                  // all other qualifiers
                  result.addExtraneousTerm(
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
          return result;
        }
    };

}

# endif
