//
// Created by Ciaran on 21/04/2021.
//

#include <omexmeta/PurgeRDFBag.h>


namespace omexmeta {

    omexmeta::PurgeRDFBag::PurgeRDFBag(IRDF *rdf)
        : rdf_(rdf) {}

    std::string PurgeRDFBag::rdfBagQueryString() {
        //        return "PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>\n"
        //               "PREFIX rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#>\n"
        //               "SELECT  ?s ?rdf_li ?y ?p ?r ?x ?j     \n"
        //               "WHERE {\n"
        //               "   ?x ?j ?s . \n"
        //               "   ?s rdf:type rdf:Bag .\n"
        //               "   ?s ?rdf_li ?y .\n"
        //               "   ?y ?p ?r\n"
        //               "}\n";
        // note: "a" is short for rdf:type
        return "PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>\n"
               "PREFIX rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#>\n"
               "SELECT  ?x ?y ?rdf_li ?z   \n"
               "WHERE {\n"
               "    ?x ?y rdf:Bag ;  \n"
               "       ?rdf_li ?z ."
               "    FILTER (isBlank(?x)) \n"
               "}\n";
    }

    void PurgeRDFBag::purge() {
        purgePattern1();// always do first
        purgePattern2();
        purgePattern3();
    }

    void omexmeta::PurgeRDFBag::purgePattern1() {

        /**
         * Note, we might be able to do another query that says
         * "if the query matches" do something with it.
         */
        std::string q = "PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>\n"
                        "PREFIX rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#>\n"
                        "SELECT  ?subject1 ?blank ?rdf_li ?blank2 ?p ?r      \n"
                        "WHERE {\n"
                        "{\n"
                        "   ?subject1 <" +
                        creatorType1 + "> ?blank  . \n"
                                       "    OPTIONAL {\n"
                                       "        ?subject1 <" +
                        creatorType2 + "> ?blank  ."
                                       "    }\n"
                                       "   ?blank rdf:type rdf:Bag .\n"
                                       "   ?blank ?rdf_li ?blank2 .\n"
                                       "   ?blank2 ?p ?r\n"
                                       "}\n"
                                       "UNION {\n"
                                       "   ?subject1 <" +
                        creatorType2 + "> ?blank  . \n"
                                       "    OPTIONAL {\n"
                                       "        ?subject1 <" +
                        creatorType1 + "> ?blank  ."
                                       "    }\n"
                                       "   ?blank rdf:type rdf:Bag .\n"
                                       "   ?blank ?rdf_li ?blank2 .\n"
                                       "   ?blank2 ?p ?r\n"
                                       "   }\n"
                                       "}\n";

        auto results = rdf_->queryResultsAsMap(q);

        for (int i = 0; i < results["blank"].size(); i++) {
            const std::string &subject1 = results["subject1"][i];
            //            const std::string &pred1 = results["pred1"][i];
            const std::string &blank = results["blank"][i];
            const std::string &blank2 = results["blank2"][i];
            const std::string &rdf_li = results["rdf_li"][i];
            //            const std::string &y = results["y"][i];
            const std::string &p = results["p"][i];
            const std::string &r = results["r"][i];

            //            std::cout << subject1 << "; " << /*pred1 << "; " <<*/ blank << "; " << rdf_li << "; " << blank2  << "; " << p << "; " << r << std::endl;

            // remove triples of form "r1r7268r10; http://www.w3.org/1999/02/22-rdf-syntax-ns#_1; r1r7268r3"
            Triple t1(
                    rdf_->getUriHandler(),
                    LibrdfNode::fromBlank(blank),
                    LibrdfNode::fromUriString(rdf_li),
                    LibrdfNode::fromBlank(blank2));
            rdf_->getModel().removeStatement(t1);

            // remove other triples with form
            //      r1r8368r6; http://xmlns.com/foaf/0.1/mbox; nikoloski@mpimp-golm.mpg.de
            // Note, this removes all but 2 of the triples in the test example.
            Triple t2(
                    rdf_->getUriHandler(),
                    LibrdfNode::fromBlank(blank2),
                    LibrdfNode::fromUriString(p),
                    LibrdfNode::fromLiteral(r, "", ""));
            rdf_->getModel().removeStatement(t2);

            // And remove the bag
            Triple t4(
                    rdf_->getUriHandler(),
                    LibrdfNode::fromBlank(blank),
                    LibrdfNode::fromUriString(rdf_type),
                    LibrdfNode::fromUriString(rdf_bag));
            rdf_->getModel().removeStatement(t4);

            Triple t5(
                    rdf_->getUriHandler(),
                    LibrdfNode::fromUriString(subject1),
                    LibrdfNode::fromUriString(creatorType1),
                    LibrdfNode::fromBlank(blank));
            rdf_->getModel().removeStatement(t5);

            Triple t5b(
                    rdf_->getUriHandler(),
                    LibrdfNode::fromUriString(subject1),
                    LibrdfNode::fromUriString(creatorType2),
                    LibrdfNode::fromBlank(blank));
            rdf_->getModel().removeStatement(t5b);

            Triple t6(
                    rdf_->getUriHandler(),
                    LibrdfNode::fromUriString(subject1),
                    LibrdfNode::fromUriString(creatorType1),
                    LibrdfNode::fromBlank(blank2));
            rdf_->getModel().addStatement(t6);

            Triple t7(
                    rdf_->getUriHandler(),
                    LibrdfNode::fromBlank(blank2),
                    LibrdfNode::fromUriString(p),
                    LibrdfNode::fromLiteral(r, "", ""));
            rdf_->getModel().addStatement(t7);
        }
    }

    void omexmeta::PurgeRDFBag::purgePattern2() {

        /**
         * This query is not as specific as I would like it to be because
         * there is some "cross-reactivity" with triples that use rdf:_1, rdf:_2, ...
         * which is handled by a different sparql query.
         *
         * One "cheat" way around this is to only apply changes when
         * this sparql query locates more than one "row" (if you think of
         * the keys in ResultMap as columns and the values as cells).
         *
         * This is not guarenteed to work for every use case, but we'll see
         */
        std::string q = "PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>\n"
                        "PREFIX rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#>\n"
                        "SELECT  ?s1 ?p ?b  ?p2 ?uriResource     \n"
                        "WHERE {\n"
                        "   ?s1 ?p ?b . \n"
                        "   ?b rdf:type rdf:Bag .\n"
                        "   ?b ?p2 ?uriResource\n"
                        "   FILTER isUri(?s1)\n"
                        "   FILTER isUri(?p)\n"
                        "   FILTER isUri(?p2)\n"
                        "   FILTER (isUri(?uriResource))\n"// can be literal or uri
                        "   FILTER isBlank(?b)\n"
                        "   FILTER (?p2 != rdf:type) \n"// http://www.w3.org/1999/02/22-rdf-syntax-ns#_1; not rdf:type
                        "}\n";

        LibrdfQuery query(q, rdf_->getModel());
        LibrdfQueryResults queryResults = query.execute();
        auto results = queryResults.map();

        //        if (results["s1"].size() <= 1) {
        //            // return when we only have 1 or 0 search results
        //            // to prevent "cross reactivity" with PurgeRDFBag::purgeListBagEntries
        ////            return;
        //        }

        for (int i = 0; i < results["s1"].size(); i++) {
            const std::string &s1 = results["s1"][i];
            const std::string &p = results["p"][i];
            const std::string &p2 = results["p2"][i];
            const std::string &b = results["b"][i];
            const std::string &uriResource = results["uriResource"][i];

            // useful for debugging:
            //            std::cout << s1 << "; " << p << "; " << b << "; " << p2 << "; " << uriResource << std::endl;
            Triple t1(
                    rdf_->getUriHandler(),
                    LibrdfNode::fromUriString(s1),
                    LibrdfNode::fromUriString(p),
                    LibrdfNode::fromBlank(b));
            rdf_->getModel().removeStatement(t1);

            Triple t2(
                    rdf_->getUriHandler(),
                    LibrdfNode::fromBlank(b),
                    LibrdfNode::fromUriString("http://www.w3.org/1999/02/22-rdf-syntax-ns#type"),
                    LibrdfNode::fromUriString("http://www.w3.org/1999/02/22-rdf-syntax-ns#Bag"));
            rdf_->getModel().removeStatement(t2);

            Triple t3(
                    rdf_->getUriHandler(),
                    LibrdfNode::fromBlank(b),
                    LibrdfNode::fromUriString(p2),
                    LibrdfNode::fromUriString(uriResource));
            rdf_->getModel().removeStatement(t3);
            Triple t4(
                    rdf_->getUriHandler(),
                    LibrdfNode::fromUriString(s1),
                    LibrdfNode::fromUriString(p),
                    LibrdfNode::fromUriString(uriResource));
            rdf_->getModel().addStatement(t4);
        }
    }

    void omexmeta::PurgeRDFBag::purgePattern3() {

        /**
         * This query is not as specific as I would like it to be because
         * there is some "cross-reactivity" with triples that use rdf:_1, rdf:_2, ...
         * which is handled by a different sparql query.
         *
         * One "cheat" way around this is to only apply changes when
         * this sparql query locates more than one "row" (if you think of
         * the keys in ResultMap as columns and the values as cells).
         *
         * This is not guarenteed to work for every use case, but we'll see
         */
        std::string q = "PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>\n"
                        "PREFIX rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#>\n"
                        "SELECT  ?s1 ?p ?b1 ?rdf_li ?b2 ?p2 ?r    \n"
                        "WHERE {\n"
                        "   ?s1 ?p ?b1 . \n"
                        "   ?b1 rdf:type rdf:Bag .\n"
                        "   ?b1 ?rdf_li ?b2 .\n"
                        "   ?b2 ?p2 ?r\n"
                        "   FILTER isUri(?s1)\n"
                        "   FILTER isUri(?p)\n"
                        "   FILTER isBlank(?b1)\n"
                        "   FILTER isUri(?p2)\n"
                        "   FILTER isBlank(?b2)\n"
                        "   FILTER isUri(?r)\n"
                        "}\n";

        LibrdfQuery query(q, rdf_->getModel());
        LibrdfQueryResults queryResults = query.execute();
        auto results = queryResults.map();

        //        if (results["s1"].size() <= 1) {
        //            // return when we only have 1 or 0 search results
        //            // to prevent "cross reactivity" with PurgeRDFBag::purgeListBagEntries
        //            return;
        //        }

        for (int i = 0; i < results["s1"].size(); i++) {
            const std::string &s1 = results["s1"][i];
            const std::string &p = results["p"][i];
            const std::string &b1 = results["b1"][i];
            const std::string &rdf_li = results["rdf_li"][i];
            const std::string &b2 = results["b2"][i];
            const std::string &p2 = results["p2"][i];
            const std::string &r = results["r"][i];

            // useful for debugging:
            //            std::cout << s1 << "; " << p << "; " << b1 << "; " << rdf_li << "; " << b2 << "; " << p2 << "; " << r << std::endl;

            Triple t1(rdf_->getUriHandler(),
                      LibrdfNode::fromBlank(b1), LibrdfNode::fromUriString(rdf_li), LibrdfNode::fromBlank(b2));
            rdf_->getModel().removeStatement(t1);

            Triple t2(
                    rdf_->getUriHandler(),
                    LibrdfNode::fromBlank(b1),
                    LibrdfNode::fromUriString("http://www.w3.org/1999/02/22-rdf-syntax-ns#type"),
                    LibrdfNode::fromUriString("http://www.w3.org/1999/02/22-rdf-syntax-ns#Bag"));
            rdf_->getModel().removeStatement(t2);

            Triple t3(
                    rdf_->getUriHandler(),
                    LibrdfNode::fromBlank(b2),
                    LibrdfNode::fromUriString(p2),
                    LibrdfNode::fromUriString(r));
            rdf_->getModel().removeStatement(t3);

            Triple t4(
                    rdf_->getUriHandler(),
                    LibrdfNode::fromBlank(b1),
                    LibrdfNode::fromUriString(p2),
                    LibrdfNode::fromUriString(r));
            rdf_->getModel().addStatement(t4);
        }
    }


}// namespace omexmeta