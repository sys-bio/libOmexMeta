//
// Created by Ciaran on 4/29/2020.
//

#ifndef LIBOMEXMETA_TRIPLES_H
#define LIBOMEXMETA_TRIPLES_H

#include "redland/RedlandAPI.h"

#include "omexmeta/Triple.h"
#include "omexmeta/Predicate.h"
#include "omexmeta/Subject.h"
#include "omexmeta/Resource.h"
#include "omexmeta/Error.h"

#include <vector>

#include "filesystem"
#include <utility>

using namespace redland;

namespace omexmeta {

//    class Triple;

    typedef std::vector<std::shared_ptr<Triple>> SharedTripleVector;
    typedef std::vector<Triple> TripleVector;

    /**
     * @brief A Triples object is a collection of Triple objects.
     * @details the implementation of Triples is hampered by the
     * inability to clone Triple objects. Instead triples must use
     * move semantics to get Triples in or out of a Triples object.
     * Under the hood, the Triples object is just a std::vector<Triple>.
     */
    class Triples {

    public:
        Triples();

        /**
         * @brief create an empty Triples object big enough
         * for @param size Triple objects
         */
        explicit Triples(int size);

        /**
         * @brief construct a Triples object from a single triple
         * @param triple The triple to put into triples
         * @details The triple is moved into element 0 of a new
         * Triples object. The Triple must be passed by reference
         * so that the triple is moved directly, instead of copied
         * and then moved into the Triples object (which is a memory leak).
         */
        explicit Triples(Triple &triple);

        /**
         * @brief construct a Triples object directly from a
         * std::vector<Triple>
         */
        explicit Triples(std::vector<Triple> triples);

        bool operator==(const Triples &rhs) const;

        bool operator!=(const Triples &rhs) const;

        /**
         * @brief move a Triple to the back of
         * the Triples object. Analogous to push
         * back but with move semantics.
         */
        void moveBack(Triple &triple);

        /**
         * @brief construct a Triple object from the necessary components and move it to the back of Triples
         * @details this method is heavily overloaded and has several signatures
         * all of which result in the construction and emplacement of a Triple at the back of Triples.
         */
        void emplace_back(UriHandler& uriHandler, Subject subject, const PredicatePtr &predicatePtr, const Resource &resource);


        /**
         * @brief construct a Triple object from the necessary components and move it to the back of Triples
         * @details this method is heavily overloaded and has several signatures
         * all of which result in the construction and emplacement of a Triple at the back of Triples.
         */
        void emplace_back(UriHandler& uriHandler, Subject subject, const Predicate &predicate, const Resource &resource);


        /**
         * @brief construct a Triple object from the necessary components and move it to the back of Triples
         * @details this method is heavily overloaded and has several signatures
         * all of which result in the construction and emplacement of a Triple at the back of Triples.
         */
        void emplace_back(UriHandler& uriHandler, Subject subject, BiomodelsBiologyQualifier predicate, const Resource &resource);


        /**
         * @brief construct a Triple object from the necessary components and move it to the back of Triples
         * @details this method is heavily overloaded and has several signatures
         * all of which result in the construction and emplacement of a Triple at the back of Triples.
         */
        void emplace_back(UriHandler& uriHandler, Subject subject, BiomodelsModelQualifier predicate, const Resource &resource);


        /**
         * @brief construct a Triple object from the necessary components and move it to the back of Triples
         * @details this method is heavily overloaded and has several signatures
         * all of which result in the construction and emplacement of a Triple at the back of Triples.
         */
        void emplace_back(UriHandler& uriHandler, Subject subject, DCTerm predicate, const Resource &resource);


        /**
         * @brief construct a Triple object from the necessary components and move it to the back of Triples
         * @details this method is heavily overloaded and has several signatures
         * all of which result in the construction and emplacement of a Triple at the back of Triples.
         */
        void emplace_back(UriHandler& uriHandler, Subject subject, SemSim predicate, const Resource &resource);

        /**
         * @brief construct a Triple object from the necessary components and move it to the back of Triples
         * @details this method is heavily overloaded and has several signatures
         * all of which result in the construction and emplacement of a Triple at the back of Triples.
         */
        void emplace_back(UriHandler& uriHandler, librdf_node *subject, librdf_node *predicate, librdf_node *resource);

        /**
         * @brief get all subjects as strings
         * @details we do not return the subject itself because subjects
         * cannot be copied, which complicates matters.
         * @returns All subject uri's as strings in a std::vector
         */
        std::vector<std::string> getSubjectsStr();

        /**
         * @brief get all predicates as strings
         * @details we do not return the predicate itself because Predicate objects
         * cannot be copied.
         * @returns All predicate uri's as strings in a std::vector
         */
        std::vector<std::string> getPredicates();

        /**
         * @brief get all resources as strings
         * @details we do not return the Resource itself because Resource objects
         * cannot be copied.
         * @returns All resource uri's as strings in a std::vector
         */
        std::vector<std::string> getResources();

        /**
         * @brief get the number of triples in the Triples object
         * @returns the integer number of triples in the Triples object
         */
        [[nodiscard]] int size() const;

        /**
         * @brief the begin iterator for a Triples object
         * @details this method is simply forwarded on to std::vector::begin()
         */
        TripleVector::iterator begin();

        /**
         * @brief the end iterator for a Triples object
         * @details this method is simply forwarded on to std::vector::end()
         */
        TripleVector::iterator end();

        /**
         * @brief Serialize the Triples object to @param format
         * @param format the format to serialize
         * @param base argument for RDF graph. This is hidden so basically irrelevant.
         * @param omex_name the omex portion of the current local uri. Default is NewOmex.omex
         * @param model_name the omex portion of the current local uri. Default is NewModel.xml
         * @details See RDF::str for more details regarding arguments. This method
         * is only for checking to see what Triples object looks like when serialized. The
         * annotations are not added to the main RDF graph. This is analogous to
         * Triple::str.
         */
        std::string str(
                const std::string &format = "turtle",
                std::string base = (std::filesystem::current_path() /= "annotations.rdf").string(),
                std::string omex_name = "NewOmex.omex/", std::string model_name = "NewModel.xml#"
                );

        void freeTriples();

        /**
         * @brief moves one triple of the end of triples
         * @returns the triple from the end of the triples vector
         * @details No copies are made. This is deliberate as it reduces
         * risk of memory issues. When you pop, you remove from the end of
         * the Triples object and return it. This means that responsibility
         * for freeing the returned Triple switches to the caller.
         */
        Triple pop();

        /**
         * @brief getter operator for Triples object
         * @return a reference to the Triple at index `index`
         * @details A copy is made of the Triple you want to return.
         * To get a reference without copying see Triples::pop(). Remember
         * that iterating over a Triples object and making copies
         * will cause complications with freeing the objects.
         */
        const Triple &operator[](int index) const;

        /**
         * @brief indicates whether Triples object is empty.
         * @return true if the Triples object doesn't contain any Triple objects
         * @details Useful for iterating over Triples in a while loop
         * without using the `[]` operator, which makes unwanted copies
         * that causes memory issues.
         */
        bool isEmpty();

        /**
         * @brief move the from Triple object out of the Triples object
         * @return a Triple from position 0 in Triples
         * @details caller is responsible for Triple resources
         */
//        [[deprecated("Slow algorithm so do not use")]] Triple popFront();

        /**
         * @brief forwarded on to std::vector::capacity
         * @return int the size of Triples currently allowed
         */
        int capacity();

    private:

        TripleVector triples_;
    };

}

#endif //LIBOMEXMETA_TRIPLES_H
