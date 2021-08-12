//
// Created by Ciaran on 20/04/2021.
//

#include "redland/RedlandAPI.h"
#include <omexmeta/RDF.h>
#include <omexmeta/VCardTranslator.h>

using namespace redland;

namespace omexmeta {

    omexmeta::VCardTranslator::VCardTranslator(RDF *rdf)
        : rdf_(rdf) {}

    void VCardTranslator::translate() {
        // first we need to remove all the N constructs
        purgeNConstructs();

        // then we do an appropriate translation from vCard predicate to foaf prediate
        translateFamilyName();
        translateGivenName();
        translateOrganization();
        translateEmail();
    }

    void VCardTranslator::purgeNConstructs() {
        std::string q = "SELECT  ?subjectBlank ?resourceBlank ?vCardPred ?literal\n"
                        "WHERE {\n"
                        "?subjectBlank <http://www.w3.org/2001/vcard-rdf/3.0#N> ?resourceBlank .\n"
                        "?resourceBlank ?vCardPred ?literal\n"
                        "}\n";

        LibrdfQuery query(q, rdf_->getModel());
        LibrdfQueryResults queryResults = query.execute();
        auto results = queryResults.map();

        for (int i = 0; i < results["subjectBlank"].size(); i++) {
            std::string &subjectBlank = results["subjectBlank"][i];
            std::string &resourceBlank = results["resourceBlank"][i];
            std::string &vCardPred = results["vCardPred"][i];
            std::string &literal = results["literal"][i];

            // first make up the old N triple so we can remove them from the model
            UriHandler &uriHandler = rdf_->getUriHandler();
            Triple nTrip1(
                    uriHandler,
                    LibrdfNode::fromBlank(subjectBlank),
                    LibrdfNode::fromUriString("http://www.w3.org/2001/vcard-rdf/3.0#N"),
                    LibrdfNode::fromBlank(resourceBlank));

            Triple nTrip2(
                    uriHandler,
                    LibrdfNode::fromBlank(resourceBlank),
                    LibrdfNode::fromUriString(vCardPred),
                    LibrdfNode::fromLiteral(literal, "", ""));

            rdf_->getModel().removeStatement(nTrip1);
            rdf_->getModel().removeStatement(nTrip2);

            // now add the information that we took out, back into the model
            Triple nTrip3(
                    uriHandler,
                    LibrdfNode::fromBlank(subjectBlank),
                    LibrdfNode::fromUriString(vCardPred),
                    LibrdfNode::fromLiteral(literal, "", ""));
            rdf_->getModel().addStatement(nTrip3);
        }
    }

    void VCardTranslator::convertVCardToFoaf(const std::string &vcardUri, const std::string &foafReplacement) {
        std::string q = "SELECT  ?subjectBlank ?resourceLiteral\n"
                        "WHERE {\n"
                        "?subjectBlank <" +
                        vcardUri + "> ?resourceLiteral \n"
                                   "}\n";

        LibrdfQuery query(q, rdf_->getModel());
        LibrdfQueryResults queryResults = query.execute();
        auto results = queryResults.map();

        for (int i = 0; i < results["subjectBlank"].size(); i++) {
            std::string &subjectBlank = results["subjectBlank"][i];
            std::string &resourceLiteral = results["resourceLiteral"][i];

            Triple old(
                    rdf_->getUriHandler(),
                    LibrdfNode::fromBlank(subjectBlank),
                    LibrdfNode::fromUriString(vcardUri),
                    LibrdfNode::fromLiteral(resourceLiteral, "", ""));
            rdf_->getModel().removeStatement(old);
            Triple new_(
                    rdf_->getUriHandler(),
                    LibrdfNode::fromBlank(subjectBlank),
                    Foaf(foafReplacement).getNode(),
                    LibrdfNode::fromLiteral(resourceLiteral, "", ""));
            rdf_->getModel().addStatement(new_);
        }
    }

    void VCardTranslator::translateFamilyName() {
        convertVCardToFoaf("http://www.w3.org/2001/vcard-rdf/3.0#Family", "familyName");
    }

    void VCardTranslator::translateGivenName() {
        convertVCardToFoaf("http://www.w3.org/2001/vcard-rdf/3.0#Given", "givenName");
    }

    void VCardTranslator::translateEmail() {
        convertVCardToFoaf("http://www.w3.org/2001/vcard-rdf/3.0#EMAIL", "mbox");
    }

    void VCardTranslator::translateOrganization() {
        std::string q = "SELECT  ?subjectBlank ?resourceBlank ?literal\n"
                        "WHERE {\n"
                        "?subjectBlank <http://www.w3.org/2001/vcard-rdf/3.0#ORG> ?resourceBlank .\n"
                        "?resourceBlank <http://www.w3.org/2001/vcard-rdf/3.0#Orgname> ?literal\n"
                        "}\n";

        LibrdfQuery query(q, rdf_->getModel());
        LibrdfQueryResults queryResults = query.execute();
        auto results = queryResults.map();

        for (int i = 0; i < results["subjectBlank"].size(); i++) {
            std::string &subjectBlank = results["subjectBlank"][i];
            std::string &resourceBlank = results["resourceBlank"][i];
            std::string &literal = results["literal"][i];


            Triple old1(
                    rdf_->getUriHandler(),
                    LibrdfNode::fromBlank(subjectBlank),
                    LibrdfNode::fromUriString("http://www.w3.org/2001/vcard-rdf/3.0#ORG"),
                    LibrdfNode::fromBlank(resourceBlank));
            rdf_->getModel().removeStatement(old1);

            Triple old2(
                    rdf_->getUriHandler(),
                    LibrdfNode::fromBlank(resourceBlank),
                    LibrdfNode::fromUriString("http://www.w3.org/2001/vcard-rdf/3.0#Orgname"),
                    LibrdfNode::fromLiteral(literal, "", ""));
            rdf_->getModel().removeStatement(old2);

            Triple new_(
                    rdf_->getUriHandler(),
                    LibrdfNode::fromBlank(subjectBlank),
                    Foaf("Organization").getNode(),
                    LibrdfNode::fromLiteral(literal, "", ""));
            rdf_->getModel().addStatement(new_);
        }
    }


}// namespace omexmeta