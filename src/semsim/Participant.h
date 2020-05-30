//
// Created by Ciaran on 4/20/2020.
//

#ifndef LIBSEMSIM_PARTICIPANT_H
#define LIBSEMSIM_PARTICIPANT_H

#include "librdf.h"
#include <string>
#include "semsim/Resource.h"
#include "Subject.h"
#include "Triple.h"
#include "Triples.h"
#include "RedlandAPIWrapper.h"
#include <utility>

using namespace redland;

namespace semsim {

    /*
     * Superclass of participant types allow us
     * to group participant types into vector.
     */
    class Participant {
        LibrdfWorld world_;
        LibrdfModel model_;
        std::string subject_;
        PredicatePtr predicate_ptr_;
        double multiplier_;
        std::string physicalEntityReference_;
    public:

        Participant(LibrdfWorld world, LibrdfModel model, std::string subject, PredicatePtr predicate,
                    double multiplier, std::string physicalEntityReference);

        Triples toTriples(std::string process_metaid) const;

        PredicatePtr getPredicatePtr();

        void setPredicatePtr(PredicatePtr predicate_ptr);

        LibrdfWorld getWorld() const;

        const std::string &getSubject() const;

        double getMultiplier() const;

        const std::string &getPhysicalEntityReference() const;


    };


    typedef std::shared_ptr<Participant> ParticipantPtr;


    class SourceParticipant : public Participant {

    public:
        SourceParticipant(LibrdfWorld world, LibrdfModel model, std::string subject, double multiplier,
                          std::string physicalEntityReference);
    };


    class SinkParticipant : public Participant {
    private:

        double multiplier_;
        std::string physicalEntityReference_;
    public:

        SinkParticipant(LibrdfWorld world, LibrdfModel model, std::string subject, double multiplier,
                        std::string physicalEntityReference);

    };


    class MediatorParticipant : public Participant {
    private:
        double multiplier_ = 0.0;

    public:

        MediatorParticipant(LibrdfWorld world, LibrdfModel model, std::string subject,
                            std::string physicalEntityReference);

    };

    typedef std::vector<SourceParticipant> Sources;
    typedef std::vector<MediatorParticipant> Mediators;
    typedef std::vector<SinkParticipant> Sinks;

}


#endif //LIBSEMSIM_PARTICIPANT_H
