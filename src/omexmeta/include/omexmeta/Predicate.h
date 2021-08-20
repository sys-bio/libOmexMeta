//
// Created by Ciaran on 4/17/2020.
//

#ifndef LIBOMEXMETA_PREDICATE_H
#define LIBOMEXMETA_PREDICATE_H

#include "redland/LibrdfWorld.h"
#include "redland/librdf.h"

#include "omexmeta/OmexMetaUtils.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace redland;

namespace omexmeta {

    typedef std::unordered_map<std::string, std::string> NamespaceMap;

    /**
     * The predicate class creates and stores a URI node.
     */
    class Predicate {

    public:
        Predicate() = default;

        /**
         * @brief get a map namespaces and prefixes
         * @returns a unordered_map with namespaces as keys and prefixes as values
         */
        static std::unordered_map<std::string, std::string> namespaceMap();

        /**
         * @brief construct a Predicate from a namespace, term and prefix portion of a predicate
         * @param namespace_ the namespace portion of a predicate. i.e. http://biomodels.net/biology-qualifiers/
         * @param term the last portion of the predicate, i.e. is
         * @param prefix the prefix that can be used instead of the full namespace, i.e. bqbiol
         *
         * http://biomodels.net/biology-qualifiers/is
         * ---------------------------------------|--
         *              |                           |
         *          namespace                      term
         *
         *  is equivalent to
         *
         * bqbiol:is
         * ------|--
         *    |    |
         * prefix  term
         *
         */
        Predicate(const std::string &namespace_,
                  std::string term, std::string prefix);

        explicit Predicate(LibrdfNode node);

        bool operator==(const Predicate &rhs) const;

        bool operator!=(const Predicate &rhs) const;

        /**
         * @brief get the predicate as a full string
         * @return a string representing the predicate
         */
        std::string str();

        /**
         * @brief Static method for checking validity of term against valid_terms
         * @param term the term to validate
         * @param valid_terms the set of terms to validate term against
         *
         * Throws an error when term is not in valid_terms. Used by subclasses
         * to verify user input.
         */
        static void verify(std::vector<std::string> valid_terms, const std::string &term);

        /**
         * @brief check if we have "know" a namespace. Known namespaces are
         * returned by Predicate::namespaceMap().
         * @param ns the namespace to check
         * @return True if we have seen the namespace ns before
         *
         */
        static bool namespaceKnown(const std::string &ns);

        /**
         * @brief stores the valid terms that are allowed in a particular predicate subclass
         * @return a vector of strings
         *
         * Subclasses override this method so they return a complete list of valid terms for their own class
         */
        [[nodiscard]] const std::vector<std::string> &getValidTerms() const;

        /**
         * @brief getter for the namespace portion of the Predicate
         * @return the string representing the namespace of the current Predicate
         *
         */
        [[nodiscard]] const std::string &getNamespace() const;

        /**
         * @brief getter for term portion of the Predicate
         * @return the string representing the term portion of the Predicate
         */
        [[nodiscard]] const std::string &getTerm() const;

        /**
         * @brief getter for the prefix portion of the Predicate
         * @return the string representing the prefix portion of the Predicate
         */
        [[nodiscard]] const std::string &getPrefix() const;

        /**
         * @brief getter for uri
         *
         * For developers. Consider removing since str() method does the same thing
         */
        [[maybe_unused]] [[nodiscard]] const std::string &getUri() const;

        /**
         * @brief release resources associated with this Predicate.
         *
         * Predicate objects contain a librdf_node pointer which
         * needs to be freed by the caller. If a Predicate is passed
         * to a Triple object (which most of the time is it),
         * responsibility for deleting the contained librdf_node
         * is transferred to the Triple object, which automatically
         * clears up resources. If not, then it is the callers
         * responsibility to call this method when they are done with
         * Predicate instances.
         */
        void freeNode();


        /**
         * @brief utility for checking whether the uri in @parameter predicate
         * has a namespace that we already know. If found, the namespace is
         * added to @parameter serializer
         */
        static void
        addSeenNamespaceToSerializer(LibrdfSerializer serializer, LibrdfNode predicate);

        /**
         * @brief replace the current librdf_node assicated with
         * this Predicate with node
         * @param node the new librdf_node pointer to use in the Predicate
         */
        void setNode(LibrdfNode &node);

        LibrdfNode getNode();


        /**
         * @brief make a shared pointer from this Predicate
         *
         */
        //        std::shared_ptr<Predicate> makeShared();
    protected:
        std::string namespace_, term_, prefix_;
        std::string uri_;
        //        librdf_node *node_ = nullptr; //! predicates can only have type uri
        std::vector<std::string> valid_terms_{"All"};

        LibrdfNode node_;
    };

    /**
     * @class Subclass of Predicate specifically for predicates from the
     * BiomodelsBiologyQualifier set of predicates. All
     * BiomodelsBiologyQualifier predicates have the namespace
     * `http://biomodels.net/biology-qualifiers/` and a `bqbiol` prefix.
     *
     * @example
     * @code
     * BiomodelBiologyQualifier is("is");
     * std::cout << is.str() << std::endl;
     * @endcode
     * will output
     *   http://biomodels.net/biology-qualifiers/is
     * to console.
     */
    class BiomodelsBiologyQualifier : public Predicate {
    public:
        std::vector<std::string> valid_terms_{
                "is",
                "hasPart",
                "isPartOf",
                "isVersionOf",
                "hasVersion",
                "isHomologTo",
                "isDescribedBy",
                "isEncodedBy",
                "encodes",
                "occursIn",
                "isVersionOf",
                "isPropertyOf",
                "hasTaxon"};

        BiomodelsBiologyQualifier() = default;

        explicit BiomodelsBiologyQualifier(const std::string &term);

        void verify();

        //        std::shared_ptr<BiomodelsBiologyQualifier> makeShared();
    };

    /**
     * @class Subclass of Predicate specifically for predicates from the
     * BiomodelsModelQualifier set of predicates. All
     * BiomodelsModelQualifier predicates have the namespace
     * `http://biomodels.net/model-qualifiers/` and a `bqmodel` prefix.
     *
     * @example
     * @code
     * BiomodelModelQualifier isDerivedFrom("isDerivedFrom");
     * std::cout << isDerivedFrom.str() << std::endl;
     * @endcode
     * will output
     *   http://biomodels.net/model-qualifiers/isDerivedFrom
     * to console.
     */
    class BiomodelsModelQualifier : public Predicate {
    public:
        std::vector<std::string> valid_terms_{
                "isDerivedFrom",
                "isDescribedBy",
                "isInstanceOf",
                "hasInstance",
        };

        BiomodelsModelQualifier() = default;

        explicit BiomodelsModelQualifier(const std::string &term);

        void verify();

        //        std::shared_ptr<BiomodelsModelQualifier> makeShared();
    };

    /**
     * @class Subclass of Predicate specifically for predicates from the
     * DCTerm set of predicates. All
     * DCTerm predicates have the namespace
     * `http://purl.org/dc/terms/`
     *
     * @example
     * @code
     * DCTerm description("Description");
     * std::cout << description.str() << std::endl;
     * @endcode
     * will output
     *   "http://purl.org/dc/terms/Description"
     * to console.
     */
    class DCTerm : public Predicate {
    public:
        std::vector<std::string> valid_terms_{
                "abstract", "accessRights", "accrualMethod", "accrualPeriodicity", "accrualPolicy", "alternative",
                "audience", "available", "bibliographicCitation", "conformsTo", "contributor", "coverage", "created",
                "creator", "date", "dateAccepted", "dateCopyrighted", "dateSubmitted", "description", "educationLevel",
                "extent", "format", "hasFormat", "hasPart", "hasVersion", "identifier", "instructionalMethod",
                "isFormatOf", "isPartOf", "isReferencedBy", "isReplacedBy", "isRequiredBy", "issued", "isVersionOf",
                "language", "license", "mediator", "medium", "modified", "provenance", "publisher", "references",
                "relation", "replaces", "requires", "rights", "rightsHolder", "source", "spatial", "subject",
                "tableOfContents", "temporal", "title", "type", "valid", "W3CDTF"};

        DCTerm() = default;

        explicit DCTerm(const std::string &term);

        void verify();

        //        std::shared_ptr<DCTerm> makeShared() ;
    };

    /**
     * @class Subclass of Predicate specifically for predicates from the
     * SemSim set of predicates. All
     * SemSim predicates have the namespace
     * `http://www.bhi.washington.edu/semsim#` and a `bqmodel` prefix.
     *
     * @example
     * @code
     * SemSim hasSourceParticipant("hasSourceParticipant");
     * std::cout << hasSourceParticipant.str() << std::endl;
     * @endcode
     * will output
     *   "http://www.bhi.washington.edu/semsim#hasSourceParticipant"
     * to console.
     */
    class SemSim : public Predicate {
    public:
        std::vector<std::string> valid_terms_{
                "hasSourceParticipant",
                "hasSinkParticipant",
                "hasMediatorParticipant",
                "hasMultiplier",
                "hasPhysicalEntityReference",
        };

        SemSim() = default;

        explicit SemSim(const std::string &term);

        void verify();
    };

    /**
     * @class Subclass of Predicate specifically for predicates from the
     * Foaf set of predicates. All
     *  predicates have the namespace
     * `http://www.bhi.washington.edu/semsim#` and a `bqmodel` prefix.
     *
     * @example
     * @code
     * SemSim hasSourceParticipant("hasSourceParticipant");
     * std::cout << hasSourceParticipant.str() << std::endl;
     * @endcode
     * will output
     *   "http://www.bhi.washington.edu/semsim#hasSourceParticipant"
     * to console.
     */
    class Foaf : public Predicate {
    public:
        std::vector<std::string> valid_terms_{
                "Agent", "Person", "name", "title", "img", "depiction", "familyName", "givenName", "knows",
                "based_near", "age", "made", "primaryTopic", "Project", "Organization", "Group", "member",
                "Document", "Image", "nick", "mbox", "homepage", "weblog", "openid", "jabberID", "mbox_sha1sum",
                "interest", "topic_interest", "topic", "workplaceHomepage", "workInfoHomepage", "schoolHomepage",
                "publications", "currentProject", "pastProject", "account", "OnlineAccount", "accountName",
                "accountServiceHomepage", "PersonalProfileDocument", "tipjar", "sha1", "thumbnail", "logo"};

        Foaf() = default;

        explicit Foaf(const std::string &term);

        void verify();
    };

    typedef std::shared_ptr<Predicate> PredicatePtr;
    typedef std::vector<Predicate> Predicates;
    typedef std::vector<PredicatePtr> PredicatePtrs;

    /**
         * @brief Convenience function for creation of objects in the
     * predicate hierachy.
     * @param namespace_ one of 8 namespaces, a long and short form string for each Predicate subtype.
     * @param term the term portion of the predicate
     *
     * @details namespace_ argument is:
     *  - bqbiol or BiomodelsBiologyQualifier for BiomodelsBiologyQualifier
     *  - bqm or BiomodelsModelQualifier for BiomodelsModelQualifier
     *  - ss or SemSim for SemSim
     *  - dc or DCTerm for DCTerm
     *
     * @return a shared_ptr to a object from the predicate heirachy.
     */
    PredicatePtr PredicateFactory(std::string namespace_, const std::string &term);

}// namespace omexmeta


#endif//LIBOMEXMETA_PREDICATE_H