#include "AnnotationCopier.h"
#include "../model/computational/datastructures/DataStructure.h"
#include "SemSimTermLibrary.h"
#include "../model/physical/object/PhysicalProperty.h"
#include "../SemSimLibrary.h"
#include "../model/computational/datastructures/MappableVariable.h"

namespace semsim
{
	namespace annotation
	{
		using SemSimLibrary = semsim::SemSimLibrary;
		using DataStructure = semsim::model::computational::datastructures::DataStructure;
		using MappableVariable = semsim::model::computational::datastructures::MappableVariable;
		using PhysicalProperty = semsim::model::physical::object::PhysicalProperty;

		void AnnotationCopier::copyCompositeAnnotation(DataStructure *sourceds, DataStructure *targetds)
		{
			if (sourceds->hasPhysicalProperty())
			{
				targetds->setAssociatedPhysicalProperty(sourceds->getPhysicalProperty());
			}
			else
			{
				targetds->setAssociatedPhysicalProperty(nullptr);
			}

			if (sourceds->hasAssociatedPhysicalComponent())
			{
				targetds->setAssociatedPhysicalModelComponent(sourceds->getAssociatedPhysicalModelComponent());
			}
			else
			{
				targetds->setAssociatedPhysicalModelComponent(nullptr);
			}
		}

		void AnnotationCopier::copyCompositeAnnotation(SemSimTermLibrary *lib, DataStructure *targetds, DataStructure *sourceds)
		{

			// Copy over physical property, physical model component, and singular annotations.
			// If no annotations present in source variable, remove annotations on target variable

			if (sourceds->hasPhysicalProperty())
			{
				int ppindex = lib->getPhysicalPropertyIndex(sourceds->getPhysicalProperty());
				targetds->setAssociatedPhysicalProperty(lib->getAssociatePhysicalProperty(ppindex));
			}
			else
			{
				targetds->setAssociatedPhysicalProperty(nullptr);
			}

			if (sourceds->hasAssociatedPhysicalComponent())
			{
				int pmcindex = lib->getComponentIndex(sourceds->getAssociatedPhysicalModelComponent(), true);
				targetds->setAssociatedPhysicalModelComponent(lib->getComponent(pmcindex));
			}
			else
			{
				targetds->setAssociatedPhysicalModelComponent(nullptr);
			}

			if (sourceds->hasPhysicalDefinitionAnnotation())
			{
				int pmcindex = lib->getPhysicalPropertyIndex(sourceds->getSingularTerm());
				targetds->setSingularAnnotation(static_cast<PhysicalProperty*>(lib->getComponent(pmcindex)));
			}
			else
			{
				targetds->setSingularAnnotation(nullptr);
			}
		}

		Set<MappableVariable*> *AnnotationCopier::copyAllAnnotationsToMappedVariables(MappableVariable *ds, SemSimLibrary *semsimlib)
		{
			Set<MappableVariable*> *allmappedvars = std::unordered_set<MappableVariable*>();
			allmappedvars->addAll(getAllMappedVariables(ds, ds, std::unordered_set<MappableVariable*>()));
			copyAllAnnotations(ds, allmappedvars, semsimlib);

			return allmappedvars;
		}

		Set<MappableVariable*> *AnnotationCopier::copyCompositeAnnotationsToMappedVariables(MappableVariable *ds)
		{
			Set<MappableVariable*> *allmappedvars = std::unordered_set<MappableVariable*>();
			allmappedvars->addAll(getAllMappedVariables(ds, ds, std::unordered_set<MappableVariable*>()));

			for (auto otherds : allmappedvars)
			{

				if (!otherds->isImportedViaSubmodel())
				{
					copyCompositeAnnotation(ds, otherds);
				}

			}

			return allmappedvars;
		}

		Set<MappableVariable*> *AnnotationCopier::copyAllAnnotationsToLocallyMappedVariables(MappableVariable *ds, SemSimLibrary *semsimlib)
		{
			Set<MappableVariable*> *allmappedvars = std::unordered_set<MappableVariable*>();
			allmappedvars->addAll(getAllLocallyMappedVariables(ds, ds, std::unordered_set<MappableVariable*>()));
			copyAllAnnotations(ds, allmappedvars, semsimlib);

			return allmappedvars;
		}

		void AnnotationCopier::copyAllAnnotations(MappableVariable *sourceds, Set<MappableVariable*> *targetdsset, SemSimLibrary *semsimlib)
		{
			for (auto otherds : targetdsset)
			{
				if (!otherds->isImportedViaSubmodel())
				{
					otherds->copyDescription(sourceds);
					otherds->copySingularAnnotations(sourceds, semsimlib);
					copyCompositeAnnotation(sourceds, otherds);
				}
			}
		}

		Set<MappableVariable*> *AnnotationCopier::getAllMappedVariables(MappableVariable *rootds, MappableVariable *ds, Set<MappableVariable*> *runningset)
		{
			Set<MappableVariable*> *allmappedvars = std::unordered_set<MappableVariable*>();
			allmappedvars->addAll(ds->getMappedTo());
			if (ds->getMappedFrom() != nullptr)
			{
				allmappedvars->add(ds->getMappedFrom());
			}

			Set<MappableVariable*> *returnset = runningset;

			for (auto var : allmappedvars)
			{

				if (!returnset->contains(var) && var != rootds)
				{
					returnset->add(var);

					// Iterate recursively
					returnset->addAll(getAllMappedVariables(rootds, var, returnset));
				}
			}

			delete allmappedvars;
			return returnset;
		}

		Set<MappableVariable*> *AnnotationCopier::getAllLocallyMappedVariables(MappableVariable *rootds, MappableVariable *ds, Set<MappableVariable*> *runningset)
		{
			Set<MappableVariable*> *allmappedvars = std::unordered_set<MappableVariable*>();
			allmappedvars->addAll(ds->getMappedTo());
			if (ds->getMappedFrom() != nullptr)
			{
				allmappedvars->add(ds->getMappedFrom());
			}

			Set<MappableVariable*> *returnset = runningset;

			for (auto var : allmappedvars)
			{
				if (!returnset->contains(var) && var != rootds && !var->isImportedViaSubmodel())
				{
					returnset->add(var);

					// Iterate recursively
					returnset->addAll(getAllLocallyMappedVariables(rootds, var, returnset));
				}
			}

			delete allmappedvars;
			return returnset;
		}
	}
}