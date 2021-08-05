//
// Created by Ciaran on 10/07/2020.
//

#ifndef LIBOMEXMETA_PERSONALINFORMATION_H
#define LIBOMEXMETA_PERSONALINFORMATION_H

#include "omexmeta/Triples.h"
#include "omexmeta_export.h"

#include <memory>

namespace omexmeta {
    /**
     * @brief add personal information to the model as a
     * composite annotation.
     *
     * For developers: This composite annotation is fundamentally different
     * to the Physical* composites in that the structure
     * is more arbitrary. With the Physical* composites,
     * the structure is very well defined, so it was easier
     * to implement the toTriples() method to construct those triples
     * when called. This differs subtly in PersonalInformation in that
     * we have a class level Triples object to store generated triples
     * using a series of methods. The user can use as many or few of them
     * as they like. Once finished they can use the getTriples() method
     * to get a unique ptr to the triples.
     */
    class OMEXMETA_EXPORT PersonalInformation {


    public:
        const std::vector<std::string> &getNamespaces() const;

        ~PersonalInformation();

        PersonalInformation(librdf_model *model, UriHandler& uriHandler);

        /**
         * @brief Copy constructor for PersonalInformation
         */
        PersonalInformation(const PersonalInformation &information) = delete;

        /**
         * @brief Move constructor for PersonalInformation
         */
        PersonalInformation(PersonalInformation &&information) noexcept;

        /**
         * @brief assignment operator for PersonalInformation
         */
        PersonalInformation &operator=(const PersonalInformation &information) = delete;

        /**
         * @brief move assignment operator for PersonalInformation
         */
        PersonalInformation &operator=(PersonalInformation &&information) noexcept;

        [[nodiscard]] const std::string &getLocalUri() const;

        bool operator==(const PersonalInformation &rhs) const;

        bool operator!=(const PersonalInformation &rhs) const;

        PersonalInformation &addCreator(const std::string& value);

//        PersonalInformation &addContributor(const std::string &value);

        PersonalInformation &addName(const std::string &value);

        PersonalInformation &addMbox(const std::string &value);

        PersonalInformation &addAccountName(const std::string &value);

        PersonalInformation &addAccountServiceHomepage(const std::string &value);

        PersonalInformation &addFoafBlank(const std::string &predicate, const std::string &blank_value);

        PersonalInformation &addDC(const std::string &predicate, const LibrdfNode &value_node);

        PersonalInformation &addDCBlank(const std::string &predicate, const std::string &blank_value);

        PersonalInformation &addDCUri(const std::string &predicate, const std::string &uri_value);

        PersonalInformation &addDCLiteral(const std::string &predicate, const std::string &literal_value);

        PersonalInformation &addFoafUri(const std::string &predicate, const std::string &uri_value);

        PersonalInformation &addFoafLiteral(const std::string &predicate, const std::string &literal_value);

        PersonalInformation &addFoaf(const std::string &predicate, const LibrdfNode &value_node);

        const std::string &getMetaid() const;

        void setMetaid(const std::string &metaid);

        const std::string &getModelUri() const;

        Triples getTriples();

        void freeTriples();

        void setTriples(Triples triples);

    private:
        librdf_model *model_;
        Triples triples_;
        std::string metaid_;
        std::vector<std::string> namespaces_;
        [[nodiscard]] std::string generateMetaId() const;
        UriHandler& uriHandler_;

        void createSubject();

    };
}

#endif //LIBOMEXMETA_PERSONALINFORMATION_H
