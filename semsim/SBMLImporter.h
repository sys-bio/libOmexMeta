# ifndef SEMSIM_SBML_IMPORTER_H_
# define SEMSIM_SBML_IMPORTER_H_

# include "semsim/Preproc.h"
# include "SBMLModel.h"
# include "SBMLSpecies.h"
# include "semsim/BiomodelsQualifiers.h"
# include "semsim/SemSimQualifiers.h"
# include "MetaID.h"
# include "semsim/ontologies/SBO.h"

# include "sbml/SBMLTypes.h"

namespace semsim {

    /**
     * This class allows importing SBML models
     * and converting them into SemSim @ref SemsimModel "Models",
     * which contain semantic information about the original
     * SBML model.
     * Most of the functions documented for this class are protected
     * methods used to implement internal logic.
     * Usage of this class is as follows:
     *
     * @code{.cpp}
     * libsbml::SBMLDocument* d = ...;
     * // import the SBML document
     * semsim::SBMLImporter importer(d);
     * // get the libSemSim wrapper for the SBML model
     * const semsim::SBMLModel& model = importer.getSBMLModel();
     * // do something with the semsim::SBMLModel
     * @endcode
     */
    class SBMLImporter {
    public:
        /**
         * Construct a libSemSim @ref SBMLModel from an SBML document.
         * @param d The input SBML document.
         */
        explicit SBMLImporter(libsbml::SBMLDocument *d)
                : m_(d->getModel()), result_(d) {

            for (unsigned int k = 0; k < m_->getNumCompartments(); ++k) {
                libsbml::Compartment *c = m_->getCompartment(k);
                if (c->isSetMetaId())
                    result_.setComponentAnnotation(c, extractAnnotation(c));
            }
            for (unsigned int k = 0; k < m_->getNumSpecies(); ++k) {
                libsbml::Species *s = m_->getSpecies(k);
                if (s->isSetMetaId())
                    result_.setComponentAnnotation(s, extractAnnotation(s));
            }
            for (unsigned int k = 0; k < m_->getNumReactions(); ++k) {
<<<<<<< HEAD
                libsbml:: Reaction *r = m_->getReaction(k);
=======
                libsbml::Reaction *r = m_->getReaction(k);
>>>>>>> ciaran-develop
                if (r->isSetMetaId())
                    result_.setComponentAnnotation(r, extractAnnotation(r));
                assignParticipants(*result_.getProcess(r), r);
            }
            for (unsigned int k = 0; k < m_->getNumParameters(); ++k) {
<<<<<<< HEAD
                libsbml:: Parameter *p = m_->getParameter(k);
=======
                libsbml::Parameter *p = m_->getParameter(k);
>>>>>>> ciaran-develop
                if (p->isSetMetaId())
                    result_.setComponentAnnotation(p, extractAnnotation(p));
            }
            Annotation::stripAnnotations(d);
        }

        /**
         * Construct from an SBML string
         * @param sbml The raw SBML content
         */
        explicit SBMLImporter(const std::string &sbml)
<<<<<<< HEAD
                : SBMLImporter(libsbml:: readSBMLFromString(sbml.c_str())) {}
=======
                : SBMLImporter(libsbml::readSBMLFromString(sbml.c_str())) {}
>>>>>>> ciaran-develop


        /// Return the @ref SBMLModel converted from this document
        SBMLModel &getSBMLModel() {
            return result_;
        }

        /// Return the @ref SBMLModel converted from this document
        const SBMLModel &getSBMLModel() const {
            return result_;
        }

<<<<<<< HEAD
        static const Relation &getRelationFromSBMLQual(libsbml:: BiolQualifierType_t q) {
            switch (q) {
                case libsbml:: BQB_IS:
                    return bqb::is;
                case libsbml:: BQB_HAS_PART:
                    return bqb::hasPart;
                case libsbml:: BQB_IS_PART_OF:
                    return bqb::isPartOf;
                case libsbml:: BQB_IS_VERSION_OF:
                    return bqb::isVersionOf;
                case libsbml:: BQB_HAS_VERSION:
                    return bqb::hasVersion;
                case libsbml:: BQB_IS_HOMOLOG_TO:
                    return bqb::isHomologTo;
                case libsbml:: BQB_IS_DESCRIBED_BY:
                    return bqb::isDescribedBy;
                case libsbml:: BQB_IS_ENCODED_BY:
                    return bqb::isEncodedBy;
                case libsbml:: BQB_ENCODES:
                    return bqb::encodes;
                case libsbml:: BQB_OCCURS_IN:
                    return bqb::occursIn;
                case libsbml:: BQB_HAS_PROPERTY:
                    return bqb::hasProperty;
                case libsbml:: BQB_IS_PROPERTY_OF:
                    return bqb::isPropertyOf;
                case libsbml:: BQB_HAS_TAXON:
=======
        static const Relation &getRelationFromSBMLQual(libsbml::BiolQualifierType_t q) {
            switch (q) {
                case libsbml::BQB_IS:
                    return bqb::is;
                case libsbml::BQB_HAS_PART:
                    return bqb::hasPart;
                case libsbml::BQB_IS_PART_OF:
                    return bqb::isPartOf;
                case libsbml::BQB_IS_VERSION_OF:
                    return bqb::isVersionOf;
                case libsbml::BQB_HAS_VERSION:
                    return bqb::hasVersion;
                case libsbml::BQB_IS_HOMOLOG_TO:
                    return bqb::isHomologTo;
                case libsbml::BQB_IS_DESCRIBED_BY:
                    return bqb::isDescribedBy;
                case libsbml::BQB_IS_ENCODED_BY:
                    return bqb::isEncodedBy;
                case libsbml::BQB_ENCODES:
                    return bqb::encodes;
                case libsbml::BQB_OCCURS_IN:
                    return bqb::occursIn;
                case libsbml::BQB_HAS_PROPERTY:
                    return bqb::hasProperty;
                case libsbml::BQB_IS_PROPERTY_OF:
                    return bqb::isPropertyOf;
                case libsbml::BQB_HAS_TAXON:
>>>>>>> ciaran-develop
                    return bqb::hasTaxon;
                default:
                    throw std::runtime_error("Unknown BioModels qualifier");
            }
        }

    protected:
        /// Extract the annotation for any SBML element
<<<<<<< HEAD
        AnnotationPtr extractAnnotation(libsbml:: SBase *s) {
=======
        AnnotationPtr extractAnnotation(libsbml::SBase *s) {
>>>>>>> ciaran-develop
            return AnnotationPtr(new SingularAnnotation(
                    extractSingularAnnotation(s)
            ));
        }

        /// Extract the annotation for a species - can be composite using automatic inference logic
<<<<<<< HEAD
        AnnotationPtr extractAnnotation(libsbml:: Species *s) {
=======
        AnnotationPtr extractAnnotation(libsbml::Species *s) {
>>>>>>> ciaran-develop
            try {
                return AnnotationPtr(new CompositeAnnotation(
                        extractCompositeAnnotation(s)
                ));
            } catch (std::domain_error) {
                // either the PhysicalProperty or Entity inference failed
                return AnnotationPtr(new SingularAnnotation(
                        extractSingularAnnotation(s)
                ));
            }
        }

        /// Extract the annotation for a compartment
<<<<<<< HEAD
        AnnotationPtr extractAnnotation(libsbml:: Compartment *c) {
=======
        AnnotationPtr extractAnnotation(libsbml::Compartment *c) {
>>>>>>> ciaran-develop
            return AnnotationPtr(new SingularAnnotation(
                    extractSingularAnnotation(c)
            ));
        }

        /// Extract the annotation for a compartment
<<<<<<< HEAD
        AnnotationPtr extractAnnotation(libsbml:: Reaction *r) {
=======
        AnnotationPtr extractAnnotation(libsbml::Reaction *r) {
>>>>>>> ciaran-develop
            return AnnotationPtr(new SingularAnnotation(
                    extractSingularAnnotation(r)
            ));
        }

        /// Extract the annotation for a parameter
<<<<<<< HEAD
        AnnotationPtr extractAnnotation(libsbml:: Parameter *p) {
=======
        AnnotationPtr extractAnnotation(libsbml::Parameter *p) {
>>>>>>> ciaran-develop
            return AnnotationPtr(new SingularAnnotation(
                    extractSingularAnnotation(p)
            ));
        }

        /**
         * Extract a singular annotation from an SBML object.
         * This method is used when a composite annotation cannot be inferred.
         * @param  s The SBML object
         * @return   A singular annotation containing all bqb:is terms as definitions and all other relations as extraneous terms.
         */
<<<<<<< HEAD
        static SingularAnnotation extractSingularAnnotation(libsbml:: SBase *s) {
=======
        static SingularAnnotation extractSingularAnnotation(libsbml::SBase *s) {
>>>>>>> ciaran-develop
            if (!s->isSetMetaId())
                throw std::runtime_error("This SBML object does not have an assigned meta id");
            SingularAnnotation result(s->getMetaId());
            populateDefinitionsAndTerms(s, result);
            populateSBOTerm(s, result);
            return result;
        }


<<<<<<< HEAD
        static SingularAnnotation extractSingularAnnotation(libsbml:: Parameter *p) {
            if (!p->isSetMetaId())
                throw std::runtime_error("This SBML object does not have an assigned meta id");
            SingularAnnotation result = extractSingularAnnotation((libsbml:: SBase *) p);
=======
        static SingularAnnotation extractSingularAnnotation(libsbml::Parameter *p) {
            if (!p->isSetMetaId())
                throw std::runtime_error("This SBML object does not have an assigned meta id");
            SingularAnnotation result = extractSingularAnnotation((libsbml::SBase *) p);
>>>>>>> ciaran-develop
            if (p->isSetValue())
                result.addExtraneousTerm(
                        Term(
                                semsim::hasValue,
                                p->getValue()
                        )
                );
            return result;
        }

        /**
         * Extract an @ref Entity from an SBML object.
         * Uses identical logic to @ref ExtractSingularAnnotation
         * @param  s The SBML object
         * @return   A singular annotation containing all bqb:is terms as definitions and all other relations as extraneous terms.
         */
        // Entity ExtractEntity(libsbml:: SBase* s) {
        //   Entity result;
        //   PopulateDefinitionsAndTerms(s, result);
        //   return result;
        // }

        /**
         * Extract the @ref EntityDescriptor for an SBML species.
         * The @ref EntityDescriptor may contain the enclosing compartment
         * (if any) referenced with a bqb:occursIn qualifier.
         */
<<<<<<< HEAD
        EntityDescriptor extractSpeciesEntityDescriptor(libsbml:: Species *s) {
            EntityDescriptor result;
            for (unsigned int k = 0; k < m_->getNumCompartments(); ++k) {
                libsbml:: Compartment *c = m_->getCompartment(k);
=======
        EntityDescriptor extractSpeciesEntityDescriptor(libsbml::Species *s) {
            EntityDescriptor result;
            for (unsigned int k = 0; k < m_->getNumCompartments(); ++k) {
                libsbml::Compartment *c = m_->getCompartment(k);
>>>>>>> ciaran-develop
                if (c->isSetIdAttribute() && s->getCompartment() == c->getId()) {
                    try {
                        result.addTerm(DescriptorTerm(bqb::occursIn, result_.getComponent(c)));
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
<<<<<<< HEAD
        Entity extractSpeciesEntity(libsbml:: Species *s) {
=======
        Entity extractSpeciesEntity(libsbml::Species *s) {
>>>>>>> ciaran-develop
            if (!s->isSetMetaId())
                throw std::runtime_error("The SBML species is missing a meta id");
            Entity result(s->getMetaId());
            populateDefinitionsAndTerms(s, result);
            populateSBOTerm(s, result);
            result.addDescriptor(extractSpeciesEntityDescriptor(s));
            return result;
        }

        /// Return a @ref Object weak pointer for the specified object (if it is in the @ref SBMLModel).
<<<<<<< HEAD
        Component *getComponentFor(libsbml:: SBase *s) {
=======
        Component *getComponentFor(libsbml::SBase *s) {
>>>>>>> ciaran-develop
            if (s->isSetIdAttribute() && result_.hasComponent(s->getId()))
                return result_.getComponent(s);
            else
                throw std::out_of_range("No such object in model");
        }

        /// Return a @ref Resource for the specified object (if it is in the @ref SBMLModel).
<<<<<<< HEAD
        Resource getResourceFor(libsbml:: SBase *s) {
=======
        Resource getResourceFor(libsbml::SBase *s) {
>>>>>>> ciaran-develop
            return Resource(getComponentFor(s));
        }

        /**
         * Populate the *definitions* (URIs specified in CV terms via bqb:is terms)
         * and extraneous terms (URIs specified using any other qualifier)
         * for a @ref SingularAnnotation or @ref Entity in a @ref CompositeAnnotation.
         * @param s The input SBML object
         * @param s The object to populate. Can be either a @ref SingularAnnotation or @ref Entity.
         */
<<<<<<< HEAD
        static void populateDefinitionsAndTerms(libsbml:: SBase *s, EntityBase &e) {
            for (unsigned int i = 0; i < s->getNumCVTerms(); ++i) {
                libsbml:: CVTerm *t = s->getCVTerm(i);
                switch (t->getQualifierType()) {
                    case libsbml:: MODEL_QUALIFIER:
                        // not handled
                        break;
                    case libsbml:: BIOLOGICAL_QUALIFIER:
                        // only bqb::is qualifiers can be used to *define* entities
                        if (t->getBiologicalQualifierType() == libsbml:: BQB_IS) {
=======
        static void populateDefinitionsAndTerms(libsbml::SBase *s, EntityBase &e) {
            for (unsigned int i = 0; i < s->getNumCVTerms(); ++i) {
                libsbml::CVTerm *t = s->getCVTerm(i);
                switch (t->getQualifierType()) {
                    case libsbml::MODEL_QUALIFIER:
                        // not handled
                        break;
                    case libsbml::BIOLOGICAL_QUALIFIER:
                        // only bqb::is qualifiers can be used to *define* entities
                        if (t->getBiologicalQualifierType() == libsbml::BQB_IS) {
>>>>>>> ciaran-develop
                            for (unsigned int i = 0; i < t->getNumResources(); ++i) {
                                e.addDefinition(Resource(t->getResourceURI(i)));
                            }
                        } else {
                            // all other qualifiers
                            for (unsigned int i = 0; i < t->getNumResources(); ++i) {
                                e.addExtraneousTerm(
                                        Term(
                                                getRelationFromSBMLQual(t->getBiologicalQualifierType()),
                                                Resource(t->getResourceURI(i))
                                        )
                                );
                            }
                        }
                        break;
                    default:
                        break;
                }
            }
        }

        /**
         * Populate the SBO term if it exists.
         */
<<<<<<< HEAD
        static void populateSBOTerm(libsbml:: SBase *s, EntityBase &e) {
=======
        static void populateSBOTerm(libsbml::SBase *s, EntityBase &e) {
>>>>>>> ciaran-develop
            if (s->isSetSBOTerm()) {
                e.addExtraneousTerm(
                        Term(
                                semsim::hasSBOTerm,
                                SBO::get(s->getSBOTerm())
                        )
                );
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
<<<<<<< HEAD
        CompositeAnnotation extractCompositeAnnotation(libsbml:: Species *s) {
=======
        CompositeAnnotation extractCompositeAnnotation(libsbml::Species *s) {
>>>>>>> ciaran-develop
            if (!s->isSetMetaId())
                throw std::runtime_error("The SBML species is missing a meta id");
            return CompositeAnnotation(
                    s->getMetaId(),
                    SBMLSpecies::GetSpeciesPhysicalProperty(s, m_),
                    extractSpeciesEntity(s)
            );
        }

<<<<<<< HEAD
        static std::string makeUniqueMetaId(const SemSimModel &model, const std::string &base) {
=======
        static std::string makeUniqueMetaId(const SemsimModel &model, const std::string &base) {
>>>>>>> ciaran-develop
            for (unsigned int k = 0; k < 1000; ++k) {
                std::stringstream ss;
                ss << base << k;
                if (!model.containsMetaId(ss.str()))
                    return ss.str();
            }
            throw std::runtime_error("Unable to create unique meta id.");
        }

<<<<<<< HEAD
        void assignParticipants(Process &process, libsbml:: Reaction *r) {
            for (unsigned int k = 0; k < r->getNumReactants(); ++k) {
                libsbml:: SpeciesReference *p = r->getReactant(k);
=======
        void assignParticipants(Process &process, libsbml::Reaction *r) {
            for (unsigned int k = 0; k < r->getNumReactants(); ++k) {
                libsbml::SpeciesReference *p = r->getReactant(k);
>>>>>>> ciaran-develop
                process.addSource(Source(
                        makeUniqueMetaId(result_, "source"),
                        result_.getComponent(m_->getElementBySId(p->getSpecies())),
                        p->isSetStoichiometry() ? p->getStoichiometry() : 1));
            }
            for (unsigned int k = 0; k < r->getNumProducts(); ++k) {
<<<<<<< HEAD
                libsbml:: SpeciesReference *p = r->getProduct(k);
=======
                libsbml::SpeciesReference *p = r->getProduct(k);
>>>>>>> ciaran-develop
                process.addSink(Sink(
                        makeUniqueMetaId(result_, "sink"),
                        result_.getComponent(m_->getElementBySId(p->getSpecies())),
                        p->isSetStoichiometry() ? p->getStoichiometry() : 1));
            }
            for (unsigned int k = 0; k < r->getNumModifiers(); ++k) {
<<<<<<< HEAD
                libsbml:: ModifierSpeciesReference *p = r->getModifier(k);
=======
                libsbml::ModifierSpeciesReference *p = r->getModifier(k);
>>>>>>> ciaran-develop
                process.addMediator(Mediator(
                        makeUniqueMetaId(result_, "mediator"),
                        result_.getComponent(m_->getElementBySId(p->getSpecies()))));
            }
        }

<<<<<<< HEAD
        libsbml:: Model *m_;
=======
        libsbml::Model *m_;
>>>>>>> ciaran-develop
        SBMLModel result_;
    };

    /**
     * Helper function for importing an SBML file.
     * @param sbml_path    The path to the SBML file.
     */
    inline SBMLModel importSBMLFromFile(
            const std::string &sbml_path) {
<<<<<<< HEAD
        libsbml:: SBMLReader reader;
        libsbml:: SBMLDocument *d = reader.readSBMLFromFile(sbml_path);
=======
        libsbml::SBMLReader reader;
        libsbml::SBMLDocument *d = reader.readSBMLFromFile(sbml_path);
>>>>>>> ciaran-develop
        if (d->getNumErrors()) {
            // if all are warnings, continue - else abort
            for (unsigned int i = 0; i < d->getNumErrors(); ++i) {
                if (!d->getError(i)->isWarning()) {
                    std::stringstream ss;
                    ss << d->getNumErrors() << " errors in SBML document.\n";
                    for (unsigned int j = 0; j < d->getNumErrors(); ++j) {
                        if (!d->getError(j)->isWarning())
                            ss << "Error " << j + 1 << ": " << d->getError(j)->getMessage() << "\n";
                    }
                    throw std::runtime_error("Errors reading SBML:\n" + ss.str());
                }
            }
        }
        SBMLImporter i(d);
        return std::move(i.getSBMLModel());
    }

}

# endif
