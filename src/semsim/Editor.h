//
// Created by Ciaran on 4/15/2020.
//

#ifndef LIBSEMSIM_EDITOR_H
#define LIBSEMSIM_EDITOR_H


#include "semsim/SemsimXmlAssistant.h"
#include "semsim/Predicate.h"
#include "semsim/Resource.h"
#include "semsim/Triple.h"
#include "semsim/Participant.h"
#include "semsim/PhysicalPhenomenon.h"
#include "semsim/PhysicalEntity.h"
#include "semsim/PhysicalProcess.h"
#include "semsim/PhysicalForce.h"
#include "RedlandAPIWrapper.h"
#include "semsim/Error.h"
#include "semsim/SemsimUtils.h"

#include "librdf.h"

#include <utility>

using namespace redland;

// todo implement this logic from Maxes email
/*
 * Here's the basic logic that we use in SemGen to determine which OPB physical property is represented by a <species> in an SBML model:
 *
 * Using libSBML, we first look up the substance base units for the model and also whether the species's "hasOnlySubstanceUnits" attribute is true...
 *
 * if the substance base unit is mole
 *      if hasOnlySubstanceUnits for species is TRUE, then use OPB:Chemical_molar_amount (OPB_00425)
 *      else use OPB:Chemical_concentration (OPB_00340)
 *
 * else if the substance base unit is item
 *      if hasOnlySubstanceUnits for species is TRUE, then use OPB:Particle_count (OPB_01001)
 *      else use OPB:Particle_concentration (OPB_01000)
 *
 * else if the base unit is kilogram or gram
 *      if hasOnlySubstanceUnits is TRUE, then use OPB:Mass_of_solid_entity (OPB_01226)
 *      else
 *           if the spatial dimensions of the compartment containing the species = 1, use OPB:Mass_lineal_density (OPB_00190)
 *           else, if the spatial dimensions of the compartment containing the species = 2, use OPB:Mass_areal_density (OPB_00258)
 *           else, if the spatial dimensions of the compartment containing the species = 3, use OPB:Mass_volumetric_density (OPB_00101)
 *
 * Hope that's helpful for determining which OPB property to use in composite annotations for SBML <species>.
 *
 * Any questions, just lemme know.
 */

namespace semsim {

    typedef std::unordered_map<std::string, std::string> NamespaceMap;

    class Editor {
    private:
        std::string xml_;
        std::vector<std::string> metaids_;
        NestedTriples triple_list_;
        const LibrdfModel& model_;
        std::unordered_map<std::string, std::string> &namespaces_;

        void extractNamespacesFromTriplesVector(Triples triples);

    public:
        const NamespaceMap &getNamespaces() const;

        librdf_model* getModel() const;

        void setNamespaces(const NamespaceMap &namespaces);

        // probably need to send our librdf model etc to the editor
        const NestedTriples &getTripleList() const;

        explicit Editor(const std::string &xml, SemsimXmlType type,
                        const LibrdfModel& model, NamespaceMap &ns_map);

        const std::string &getXml() const;

        const std::vector<std::string> &getMetaids() const;

        void addSingleAnnotation(Subject subject, PredicatePtr predicate_ptr, Resource resource);

        void addNamespace(std::string ns, std::string prefix);

        void addSingleAnnotation(const SingularAnnotation &singularAnnotation);

        void addCompositeAnnotation(PhysicalPhenomenonPtr phenomenonPtr);

        void addPhysicalEntity(PhysicalEntity physicalEntity);

        void addPhysicalProcess(PhysicalProcess physicalProcess);

        void addPhysicalForce(PhysicalForce physicalForce);

        void addAnnotationFromNestedTriples(NestedTriples tripleList);
        //overloaded

        void removeAnnotation(std::string metaid);

        void toRDF();

        void checkValidMetaid(const std::string &metaid);

        void addAnnotationFromTriples(Triples triples);

        /*
         * @brief extract namespace part of uri from @parameter predicate_string
         * and add it to namespace_ if we know it.
         */
        void addNamespaceFromAnnotation(std::string predicate_string);
    };

}

#endif //LIBSEMSIM_EDITOR_H
