//
// Created by Ciaran on 4/20/2020.
//

#ifndef LIBSEMGEN_PARTICIPANT_H
#define LIBSEMGEN_PARTICIPANT_H

#include "librdf.h"
#include <string>
#include "semsim/Resource.h"
#include "Subject.h"
#include "Triple.h"
#include "Triples.h"


namespace semsim {

    /*
     * Superclass of participant types allow us
     * to group participant types into vector.
     */
    class Participant {
        librdf_world *world_;
        librdf_model *model_;
        std::string subject_;
        Resource resource_;
        PredicatePtr predicate_ptr_;
        double multiplier_;
        std::string physicalEntityReference_;
    protected:
        std::string participant_metaid_;
    public:

        Participant(librdf_world *world, librdf_model *model, std::string subject, PredicatePtr predicate,
                    Resource resource, double multiplier,
                    std::string physicalEntityReference);

        Triples toTriples(std::string process_metaid) const;

        PredicatePtr getPredicatePtr();

        void setPredicatePtr(PredicatePtr predicate_ptr);

        librdf_world *getWorld() const;

        const std::string &getSubject() const;

        const Resource &getResource() const;

        double getMultiplier() const;

        const std::string &getPhysicalEntityReference() const;


    };


    typedef std::shared_ptr<Participant> ParticipantPtr;


    class SourceParticipant : public Participant {

    public:
        SourceParticipant(librdf_world *world, librdf_model *model, std::string subject, Resource resource,
                          double multiplier,
                          std::string physicalEntityReference);
    };


    class SinkParticipant : public Participant {
    private:

        double multiplier_;
        std::string physicalEntityReference_;
    public:

        SinkParticipant(
                librdf_world *world, librdf_model *model, std::string subject, Resource resource,
                double multiplier, std::string physicalEntityReference);

    };


    class MediatorParticipant : public Participant {
    private:
        double multiplier_ = 0.0;

    public:

        MediatorParticipant(
                librdf_world *world, librdf_model *model, std::string subject, Resource resource,
                std::string physicalEntityReference);

    };

    typedef std::vector<SourceParticipant> Sources;
    typedef std::vector<MediatorParticipant> Mediators;
    typedef std::vector<SinkParticipant> Sinks;

}


#endif //LIBSEMGEN_PARTICIPANT_H
