//
// Created by Ciaran on 4/20/2020.
//

#ifndef LIBOMEXMETA_PARTICIPANT_H
#define LIBOMEXMETA_PARTICIPANT_H

#include "redland/RedlandAPI.h"
#include "redland/librdf.h"

#include "UriHandler.h"
#include "omexmeta/Triple.h"
#include "omexmeta/Triples.h"

#include <string>
#include <utility>

using namespace redland;

namespace omexmeta {


    class Participant {

    public:
        /**
         * @brief Superclass of participant types
         * @param model pointer to the librdf_model* in use. Passed down from RDF.
         * @param base_metaid the content of the participant base_metaid. A valid metaid.
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
        Participant(LibrdfModel & model, std::string base_metaid, UriHandler &uriHandler,
                    std::string semsim_predicate_term, double multiplier,
                    std::string physicalEntityReference, eUriType type);

        /**
         * @brief setter for the multiplier field of Participant types
         */
        void setMultiplier(double multiplier);

        /**
         * @brief setter for physical entity reference field of Participant types
         * @details A physical entity reference must exist and point to a physical entity in the xml.
         */
        void setPhysicalEntityReference(const std::string &physicalEntityReference);

        /**
         * @brief return the local participant metaid.
         * @details When Participant types are created they are
         * done so with a metaid that is local to the annotation document
         * not to the model.
         */
        [[nodiscard]] const std::string &getLocalParticipantMetaid() const;

        /**
         * @brief set the local participant metaid.
         * @details When Participant types are created they are
         * done so with a metaid that is local to the annotation document
         * not to the model.
         */
        void setUniqueParticipantMetaid(const std::string &uniqueParticipantMetaid);

        /**
         * @brief getter for local uri attribute
         */
        [[nodiscard]] const std::string &getLocalUri() const;


        /**
         * @biref currently more of a placeholder so as to not break the tests.
         * todo remove this method, Triple objects deal with memory for Participants.
         */
        [[maybe_unused]] void free();

        ~Participant() = default;

        bool operator==(const Participant &rhs) const;

        bool operator!=(const Participant &rhs) const;

        /**
         * @brief create a Triples object from the Participant.
         * @param about the metaid for a process
         * @return A Triples container for the Triples associated with this Participant
         *
         * The same toTriples method is used for all participants.
         */
        [[nodiscard]] Triples toTriples(std::string about,
                                        std::vector<std::string> &metaid_exclusions);

        /**
         * @brief create a new metaid use base @param base
         */
        [[nodiscard]] std::string createMetaid(const std::string &base,
                                               std::vector<std::string> &metaid_exclusions) const;


        /**
         * @brief get the predicate currently in use by the participant
         * @return a SemSim predicate
         */
        std::basic_string<char> getPredicate();

        /**
         * @brief set the predicate used in the participant
         * @param semsim_predicate_string The predicate portion of the SemSim predicate you want to use.
         *
         * i.e. "hasSourceParticipant" not "http://www.bhi.washington.edu/semsim#hasSourceParticipant"
         */
        void setPredicate(const std::string &semsim_predicate_string);

        /**
         * @brief get the subject portion of the Participant, which is the
         * @return the string of the subject value
         * metaid of the Participant
         */
        [[nodiscard]] const std::string &getSubject() const;

        /**
         * @brief get the multiplier representing the stoiciometry of the process being described
         * @return the multiplier
         */
        [[nodiscard]] double getMultiplier() const;

        /**
         * @brief get the physicalEntityReference
         * @return the physicalEntityReference string
         */
        [[nodiscard]] const std::string &getPhysicalEntityReference() const;

        /**
         * @brief getter for model_uri_ attribute
         */
        [[nodiscard]] const std::string &getModelUri() const;

    private:
        LibrdfModel& model_ ;
        std::string metaid_template_str_;///like SourceParticipant in SourceParticipant0000
        std::string semsim_predicate_term_;
        double multiplier_ = 0;
        std::string physicalEntityReference_;
        // autogenerated id. This allows Participants to have memory,
        // so that you can call toTriples more than once and have the same
        // set of triples returned.
        std::string local_participant_metaid_;

        UriHandler &uriHandler_;

        eUriType type_;
    };


    typedef std::shared_ptr<Participant> ParticipantPtr;

    /**
     * Subclass of Participant. See Participants for arguments.
     */
    class SourceParticipant : public Participant {
    public:
        /**
         * @brief A class representing process/force energetic source.
         */
        SourceParticipant(LibrdfModel& model, double multiplier, std::string physicalEntityReference, eUriType type,
                          UriHandler &uriHandler);
    };

    /**
     * Subclass of Participant. See Participants for arguments.
     */
    class SinkParticipant : public Participant {
    public:
        /**
         * @brief A class representing process/force energetic sinks.
         */
        SinkParticipant(LibrdfModel& model, double multiplier, std::string physicalEntityReference, eUriType type,
                        UriHandler &uriHandler);
    };

    /**
     * Subclass of Participant. See Participants for arguments.
     */
    class MediatorParticipant : public Participant {
    public:
        /**
         * @brief A class representing process mediators (such as a catalyst).
         */
        MediatorParticipant(LibrdfModel& model, std::string physicalEntityReference, eUriType type, UriHandler &uriHandler);

    private:
        double multiplier_ = 0;
    };

    typedef std::vector<SourceParticipant> Sources;
    typedef std::vector<MediatorParticipant> Mediators;
    typedef std::vector<SinkParticipant> Sinks;


}// namespace omexmeta


#endif//LIBOMEXMETA_PARTICIPANT_H
