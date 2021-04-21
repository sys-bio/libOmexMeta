//
// Created by Ciaran on 21/04/2021.
//

#include <omexmeta/PurgeRDFBag.h>


namespace omexmeta {

    omexmeta::PurgeRDFBag::PurgeRDFBag(RDF *rdf)
        : rdf_(rdf) {}

    void PurgeRDFBag::purge() {
        purgeListBagEntries();// always do first
        purgeNonListBagEntries();
    }


    void omexmeta::PurgeRDFBag::purgeListBagEntries() {
        std::string q = "PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>\n"
                        "PREFIX rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#>\n"
                        "SELECT  ?s ?rdf_li ?y ?p ?r ?x ?j     \n"
                        "WHERE {\n"
                        "   ?x ?j ?s . \n"
                        "   ?s rdf:type rdf:Bag .\n"
                        "   ?s ?rdf_li ?y .\n"
                        "   ?y ?p ?r\n"
                        "}\n";

        Query query(rdf_->getModel(), q);
        auto results = query.resultsAsMap();


        for (int i = 0; i < results["s"].size(); i++) {
            const std::string &x = results["x"][i];
            const std::string &j = results["j"][i];
            const std::string &s = results["s"][i];
            const std::string &rdf_li = results["rdf_li"][i];
            const std::string &y = results["y"][i];
            const std::string &p = results["p"][i];
            const std::string &r = results["r"][i];

            // std::cout << x << "; " << j << "; " << s << "; " << rdf_li << "; " << y << "; " << p << "; " << r << std::endl;

            // remove triples of form "r1r7268r10; http://www.w3.org/1999/02/22-rdf-syntax-ns#_1; r1r7268r3"
            Triple t1(
                    rdf_->getUriHandler(),
                    LibrdfNode::fromBlank(s),
                    LibrdfNode::fromUriString(rdf_li),
                    LibrdfNode::fromBlank(y));
            librdf_model_remove_statement(rdf_->getModel(), t1.getStatement());

            // remove other triples with form
            //      r1r8368r6; http://xmlns.com/foaf/0.1/mbox; nikoloski@mpimp-golm.mpg.de
            // Note, this removes all but 2 of the triples in the test example.
            Triple t2(
                    rdf_->getUriHandler(),
                    LibrdfNode::fromBlank(y),
                    LibrdfNode::fromUriString(p),
                    LibrdfNode::fromLiteral(r, "", ""));
            librdf_model_remove_statement(rdf_->getModel(), t2.getStatement());

            // And remove the bag
            Triple t3(
                    rdf_->getUriHandler(),
                    LibrdfNode::fromBlank(s),
                    LibrdfNode::fromUriString("http://www.w3.org/1999/02/22-rdf-syntax-ns#type"),
                    LibrdfNode::fromUriString("http://www.w3.org/1999/02/22-rdf-syntax-ns#Bag"));
            librdf_model_remove_statement(rdf_->getModel(), t3.getStatement());

            // we now construct a triple to add the information back in
            Triple t4(
                    rdf_->getUriHandler(),
                    LibrdfNode::fromBlank(s),
                    LibrdfNode::fromUriString(p),
                    LibrdfNode::fromLiteral(r, "", ""));
            librdf_model_add_statement(rdf_->getModel(), t4.getStatement());
        }
    }

    void omexmeta::PurgeRDFBag::purgeNonListBagEntries() {
        //        rdf:type rdf:Bag
        std::string q = "PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>\n"
                        "PREFIX rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#>\n"
                        "SELECT  ?s1 ?p ?b  ?p2 ?r    \n"
                        "WHERE {\n"
                        "   ?s1 ?p ?b . \n"
                        "   ?b rdf:type rdf:Bag .\n"
                        "   ?b ?p2 ?r\n"
                        "}\n";

        Query query(rdf_->getModel(), q);
        auto results = query.resultsAsMap();

        for (int i = 0; i < results["s1"].size(); i++) {
            const std::string &s1 = results["s1"][i];
            const std::string &p = results["p"][i];
            const std::string &p2 = results["p2"][i];
            const std::string &b = results["b"][i];
            //            const std::string &rdf_li = results["rdf_li"][i];
            const std::string &r = results["r"][i];

            // std::cout << s1 << "; " << p << "; " << b << "; " << p2 << "; " << r << std::endl;
            Triple t1(
                    rdf_->getUriHandler(),
                    LibrdfNode::fromUriString(s1),
                    LibrdfNode::fromUriString(p),
                    LibrdfNode::fromBlank(b));
            librdf_model_remove_statement(rdf_->getModel(), t1.getWithoutIncrement());
            Triple t2(
                    rdf_->getUriHandler(),
                    LibrdfNode::fromBlank(b),
                    LibrdfNode::fromUriString("http://www.w3.org/1999/02/22-rdf-syntax-ns#type"),
                    LibrdfNode::fromUriString("http://www.w3.org/1999/02/22-rdf-syntax-ns#Bag"));
            librdf_model_remove_statement(rdf_->getModel(), t2.getWithoutIncrement());

            Triple t3(
                    rdf_->getUriHandler(),
                    LibrdfNode::fromBlank(b),
                    LibrdfNode::fromUriString(p2),
                    LibrdfNode::fromUriString(r));
            librdf_model_remove_statement(rdf_->getModel(), t3.getWithoutIncrement());
            if (r != "http://www.w3.org/1999/02/22-rdf-syntax-ns#Bag") {
                Triple t4(
                        rdf_->getUriHandler(),
                        LibrdfNode::fromUriString(s1),
                        LibrdfNode::fromUriString(p),
                        LibrdfNode::fromUriString(r));
                librdf_model_add_statement(rdf_->getModel(), t4.getWithoutIncrement());
            }
        }
    }

}// namespace omexmeta