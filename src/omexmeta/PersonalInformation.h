//
// Created by Ciaran on 10/07/2020.
//

#ifndef LIBOMEXMETA_PERSONALINFORMATION_H
#define LIBOMEXMETA_PERSONALINFORMATION_H

#include "Triples.h"
#include <memory>


namespace omexmeta {
    /*
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
    class PersonalInformation {

        librdf_model *model_;
        Triples triples_;
        std::string local_uri_;
        std::string metaid_;
        std::string model_name_;

    private:
        [[nodiscard]] std::string generateMetaId() const;

        void createSubject();

    public:
        PersonalInformation() = default;

        ~PersonalInformation() = default;

        PersonalInformation(librdf_model *model, std::string local_uri, std::string model_name);

        /*
         * @brief Copy constructor for PersonalInformation
         */
        PersonalInformation(const PersonalInformation &information) = delete;

        /*
         * @brief Move constructor for PersonalInformation
         */
        PersonalInformation(PersonalInformation &&information) noexcept;

        /*
         * @brief assignment operator for PersonalInformation
         */
        PersonalInformation &operator=(const PersonalInformation &information) = delete;

        /*
         * @brief move assignment operator for PersonalInformation
         */
        PersonalInformation &operator=(PersonalInformation &&information) noexcept;

        [[nodiscard]] const std::string &getLocalUri() const;

        void setLocalUri(const std::string &localUri);

        bool operator==(const PersonalInformation &rhs) const;

        bool operator!=(const PersonalInformation &rhs) const;

        PersonalInformation &addCreator(const std::string& value);

        PersonalInformation &addCurator(const std::string& value);

        PersonalInformation &addName(const std::string& value);

        PersonalInformation &addMbox(const std::string& value);

        PersonalInformation &addAccountName(const std::string& value);

        PersonalInformation &addAccountServiceHomepage(const std::string& value);

        PersonalInformation &addFoafBlank(const std::string &predicate, const std::string &blank_value);

        PersonalInformation &addFoafUri(const std::string &predicate, const std::string &uri_value);

        PersonalInformation &addFoafLiteral(const std::string &predicate, const std::string &literal_value);

        PersonalInformation &addFoaf(const std::string &predicate, const LibrdfNode& value_node);

        const std::string &getMetaid() const;

        void setMetaid(const std::string &metaid);

        const std::string &getModelName() const;

        void setModelName(const std::string &modelName);

        Triples getTriples();

        void freeTriples();
    };
}

#endif //LIBOMEXMETA_PERSONALINFORMATION_H
