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
    
    typedef std::unique_ptr<Predicate, Predicate::deleter> UniquePredicatePtrWithDeleter;

    /*
     * @brief Superclass of participant types allow us
     * to group participant types into vector.
     *
     * Predicate argument must either be `std::move`d into the Participant
     * or the caller must free the predicate manually, via predicate.free();
     * Prefer move. For developers, users do not need to know this.
     */
    class Participant {

        const LibrdfModel& model_;
        std::string subject_;
        SemSim semsim_predicate_term_;
        double multiplier_;
        std::string physicalEntityReference_;

    public:

//        Participant(const LibrdfModel& model, std::string subject, Predicate* predicate,
//                    double multiplier, std::string physicalEntityReference);
//
        ~Participant() = default;

        [[nodiscard]] Triples toTriples(const std::string& process_metaid) const;

        SemSim getPredicate();

        void setPredicate(std::string semsim_predicate_string);

        const std::string &getSubject() const;

        double getMultiplier() const;

        const std::string &getPhysicalEntityReference() const;

        void free();

        Participant(const LibrdfModel &model, std::string subject, SemSim *predicate, double multiplier,
                    std::string physicalEntityReference);

        Participant(const LibrdfModel &model, std::string subject, std::string semsim_predicate_term, double multiplier,
                    std::string physicalEntityReference);
    };


    typedef std::shared_ptr<Participant> ParticipantPtr;


    class SourceParticipant : public Participant {

    public:
        SourceParticipant(const LibrdfModel &model, std::string subject, double multiplier,
                          std::string physicalEntityReference);
    };


    class SinkParticipant : public Participant {
    private:

        double multiplier_{};
        std::string physicalEntityReference_;
    public:

        SinkParticipant(const LibrdfModel &model, std::string subject, double multiplier,
                        std::string physicalEntityReference);

    };


    class MediatorParticipant : public Participant {
    private:
        double multiplier_ = 0.0;

    public:

        MediatorParticipant(const LibrdfModel &model, std::string subject,
                            std::string physicalEntityReference);

    };

    typedef std::vector<SourceParticipant> Sources;
    typedef std::vector<MediatorParticipant> Mediators;
    typedef std::vector<SinkParticipant> Sinks;

}


#endif //LIBSEMSIM_PARTICIPANT_H
