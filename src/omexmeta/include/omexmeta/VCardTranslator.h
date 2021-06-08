//
// Created by Ciaran on 20/04/2021.
//

#ifndef LIBOMEXMETA_VCARDTRANSLATOR_H
#define LIBOMEXMETA_VCARDTRANSLATOR_H

#include "redland/LibrdfModel.h"

using namespace redland;

namespace omexmeta {

    class RDF;

    class VCardTranslator {

    public:
        /**
         * @brief constructor
         * takes a non-owning RDF*
         */
        explicit VCardTranslator(RDF *rdf);

        void translate();

    private:

        /**
         * @brief convert a triple that has a vcard uri for predicate into a
         * corresponding foaf predicate. The subject is a blank node and the
         * resource a literal node.
         */
        void convertVCardToFoaf(const std::string& vcardUri, const std::string& foafReplacement);

        /**
         * @brief VCard N constructs are not necessary
         * So the first job of the translator is to remove them
         */
        void purgeNConstructs();

        /**
         * @brief converts vcard family name to foaf familyName
         */
        void translateFamilyName();

        /**
         * @brief converts vcard given name to foaf givenName
         */
        void translateGivenName();

        /**
         * @brief converts vcard org to foaf organization
         */
        void translateOrganization();

        /**
         * @brief converts vcard email to foaf email
         */
        void translateEmail();

        RDF *rdf_;

        unsigned int currentBlankId = 0;
    };


}// namespace omexmeta


#endif//LIBOMEXMETA_VCARDTRANSLATOR_H
