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


    class Participant {

        librdf_model *model_ = nullptr;
        std::string subject_;
        std::string semsim_predicate_term_;
        double multiplier_;
        std::string physicalEntityReference_;

    public:

        void free();

        /*
         * @brief Superclass of participant types
         * @param model pointer to the librdf_model* in use. Passed down from RDF.
         * @param subject the content of the participant subject. A valid metaid.
         * @param semsim_predicate_term a string from the SemSim vocabulary.
         * @param multiplier Specifies the stoiciometry for the Participant in the process
         * @param physicalEntityReference the ID of the physicalEntity assicated with the Participant
         *
         * This class should not be used directly - the subclasses should be preferred.
         *
         * For developers - This superclass is implemented in order to substantially reduce
         * code duplication in the subclasses.
         *
         */
        Participant(librdf_model *model, std::string subject, std::string semsim_predicate_term, double multiplier,
                    std::string physicalEntityReference);

        ~Participant() = default;

        bool operator==(const Participant &rhs) const;

        bool operator!=(const Participant &rhs) const;

        /*
         * @brief create a Triples object from the Participant.
         * @param process_metaid the metaid for a process
         * @return A Triples container for the Triples associated with this Participant
         *
         * The same toTriples method is used for all participants.
         */
        [[nodiscard]] Triples toTriples(const std::string &process_metaid) const;

        /*
         * @brief get the predicate currently in use by the participant
         * @return a SemSim predicate
         */
        std::basic_string<char> getPredicate();

        /*
         * @brief set the predicate used in the participant
         * @param semsim_predicate_string The predicate portion of the SemSim predicate you want to use.
         *
         * i.e. "hasSourceParticipant" not "http://www.bhi.washington.edu/semsim#hasSourceParticipant"
         */
        void setPredicate(const std::string& semsim_predicate_string);

        /*
         * @brief get the subject portion of the Participant, which is the
         * @return the string of the subject value
         * metaid of the Participant
         */
        [[nodiscard]] const std::string &getSubject() const;

        /*
         * @brief get the multiplier representing the stoiciometry of the process being described
         * @return the multiplier
         */
        [[nodiscard]] double getMultiplier() const;

        /*
         * @brief get the physicalEntityReference
         * @return the physicalEntityReference string
         */
        [[nodiscard]] const std::string &getPhysicalEntityReference() const;

    };


    typedef std::shared_ptr<Participant> ParticipantPtr;

    /*
     * Subclass of Participant. See Participants for arguments.
     */
    class SourceParticipant : public Participant {

    public:
        /*
         * @brief A class representing process/force energetic source.
         */
        SourceParticipant(librdf_model *model, std::string subject, double multiplier,
                          std::string physicalEntityReference);
    };

    /*
     * Subclass of Participant. See Participants for arguments.
     */
    class SinkParticipant : public Participant {
    private:

        double multiplier_{};
        std::string physicalEntityReference_;
    public:

        /*
         * @brief A class representing process/force energetic sinks.
         */
        SinkParticipant(librdf_model *model, std::string subject, double multiplier,
                        std::string physicalEntityReference);

    };

    /*
     * Subclass of Participant. See Participants for arguments.
     */
    class MediatorParticipant : public Participant {
    private:
        double multiplier_ = 0.0;

    public:

        /*
         * @brief A class representing process mediators (such as a catalyst).
         */
        MediatorParticipant(librdf_model *model, std::string subject,
                            std::string physicalEntityReference);

    };

    typedef std::vector<SourceParticipant> Sources;
    typedef std::vector<MediatorParticipant> Mediators;
    typedef std::vector<SinkParticipant> Sinks;

}


#endif //LIBSEMSIM_PARTICIPANT_H
