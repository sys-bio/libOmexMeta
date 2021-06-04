//
// Created by Ciaran on 20/04/2021.
//
#include <utility>

#include "MockRDF.h"
#include "SBMLFactory.h"
#include "omexmeta/Options.h"
#include "omexmeta/PurgeRDFBag.h"
#include "omexmeta/Query.h"
#include "omexmeta/RDF.h"
#include "gtest/gtest.h"

#include "redland/RedlandAPI.h"

using namespace omexmeta;
using namespace testing;
/**
 * @brief purging rdf:Bag depends heavily on correct sparql queries.
 * Therefore we need to include the Query as a dependency in this unit.
 */
class PurgeRDFBagTests2 : public ::testing::Test {
public:
    std::string biomd385FullString = "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                                     "         xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\"\n"
                                     "         xmlns:vCard=\"http://www.w3.org/2001/vcard-rdf/3.0#\" xmlns:dc=\"http://purl.org/dc/elements/1.1/\"\n"
                                     "         xmlns:dcterms=\"http://purl.org/dc/terms/\" xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\">\n"
                                     "    <rdf:Description rdf:about=\"#_272044\">\n"
                                     "        <dc:creator>\n"
                                     "            <rdf:Bag>\n"
                                     "                <rdf:li rdf:parseType=\"Resource\">\n"
                                     "                    <vCard:N rdf:parseType=\"Resource\">\n"
                                     "                        <vCard:Family>Chelliah</vCard:Family>\n"
                                     "                        <vCard:Given>Vijayalakshmi</vCard:Given>\n"
                                     "                    </vCard:N>\n"
                                     "                    <vCard:EMAIL>viji@ebi.ac.uk</vCard:EMAIL>\n"
                                     "                    <vCard:ORG rdf:parseType=\"Resource\">\n"
                                     "                        <vCard:Orgname>EMBL-EBI</vCard:Orgname>\n"
                                     "                    </vCard:ORG>\n"
                                     "                </rdf:li>\n"
                                     "                <rdf:li rdf:parseType=\"Resource\">\n"
                                     "                    <vCard:N rdf:parseType=\"Resource\">\n"
                                     "                        <vCard:Family>Nikoloski</vCard:Family>\n"
                                     "                        <vCard:Given>Zoran</vCard:Given>\n"
                                     "                    </vCard:N>\n"
                                     "                    <vCard:EMAIL>nikoloski@mpimp-golm.mpg.de</vCard:EMAIL>\n"
                                     "                    <vCard:ORG rdf:parseType=\"Resource\">\n"
                                     "                        <vCard:Orgname>Institute of Biochemistry and Biology, University of Potsdam, 14476\n"
                                     "                            Potsdam, Germany\n"
                                     "                        </vCard:Orgname>\n"
                                     "                    </vCard:ORG>\n"
                                     "                </rdf:li>\n"
                                     "                <rdf:li rdf:parseType=\"Resource\">\n"
                                     "                    <vCard:N rdf:parseType=\"Resource\">\n"
                                     "                        <vCard:Family>Arnold</vCard:Family>\n"
                                     "                        <vCard:Given>Anne</vCard:Given>\n"
                                     "                    </vCard:N>\n"
                                     "                    <vCard:EMAIL>arnold@mpimp-golm.mpg.de</vCard:EMAIL>\n"
                                     "                    <vCard:ORG rdf:parseType=\"Resource\">\n"
                                     "                        <vCard:Orgname>Max-Planck-Institute of Molecular Plant Physiology</vCard:Orgname>\n"
                                     "                    </vCard:ORG>\n"
                                     "                </rdf:li>\n"
                                     "            </rdf:Bag>\n"
                                     "        </dc:creator>\n"
                                     "        <dcterms:created rdf:parseType=\"Resource\">\n"
                                     "            <dcterms:W3CDTF>2011-10-19T14:51:13Z</dcterms:W3CDTF>\n"
                                     "        </dcterms:created>\n"
                                     "        <dcterms:modified rdf:parseType=\"Resource\">\n"
                                     "            <dcterms:W3CDTF>2012-04-20T19:52:45Z</dcterms:W3CDTF>\n"
                                     "        </dcterms:modified>\n"
                                     "        <bqmodel:is>\n"
                                     "            <rdf:Bag>\n"
                                     "                <rdf:li rdf:resource=\"http://identifiers.org/biomodels.db/MODEL1109270001\"/>\n"
                                     "            </rdf:Bag>\n"
                                     "        </bqmodel:is>\n"
                                     "        <bqmodel:is>\n"
                                     "            <rdf:Bag>\n"
                                     "                <rdf:li rdf:resource=\"http://identifiers.org/biomodels.db/BIOMD0000000385\"/>\n"
                                     "            </rdf:Bag>\n"
                                     "        </bqmodel:is>\n"
                                     "        <bqmodel:isDescribedBy>\n"
                                     "            <rdf:Bag>\n"
                                     "                <rdf:li rdf:resource=\"http://identifiers.org/pubmed/22001849\"/>\n"
                                     "            </rdf:Bag>\n"
                                     "        </bqmodel:isDescribedBy>\n"
                                     "        <bqmodel:is>\n"
                                     "            <rdf:Bag>\n"
                                     "                <rdf:li rdf:resource=\"http://identifiers.org/obo.go/GO:0019253\"/>\n"
                                     "            </rdf:Bag>\n"
                                     "        </bqmodel:is>\n"
                                     "        <bqbiol:hasTaxon>\n"
                                     "            <rdf:Bag>\n"
                                     "                <rdf:li rdf:resource=\"http://identifiers.org/taxonomy/33090\"/>\n"
                                     "            </rdf:Bag>\n"
                                     "        </bqbiol:hasTaxon>\n"
                                     "    </rdf:Description>\n"
                                     "</rdf:RDF>";


    MockRDF mockRdf;
    std::string rdfBagQueryWithLists = "PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>\n"
                                       "PREFIX rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#>\n"
                                       "SELECT  ?s ?rdf_li ?y ?p ?r ?x ?j     \n"
                                       "WHERE {\n"
                                       "   ?x ?j ?s . \n"
                                       "   ?s rdf:type rdf:Bag .\n"
                                       "   ?s ?rdf_li ?y .\n"
                                       "   ?y ?p ?r\n"
                                       "}\n";
    std::string q = "SELECT ?x ?y ?z \n"
                    "WHERE {\n"
                    "    ?x ?y ?z \n"
                    "}\n";
    PurgeRDFBagTests2() {
        Options::translateVCard_ = false;// we'll do it manually during tests
    };


    ResultsMap runQuery(std::string input, std::string inputSyntax, std::string queryString) {
        LibrdfStorage storage;
        LibrdfModel model(storage);
        LibrdfParser parser(inputSyntax);
        parser.parseString(input, model, "https://baseUriNotNeeded.com");
        Query query(model.get(), std::move(queryString));
        return query.resultsAsMap();
    }

    void printResultsMap(ResultsMap &resultsMap) {
        for (auto [key, val] : resultsMap) {
            int count = 0;
            std::cout << "binding: " << key << "; value: " << std::endl;
            for (auto i : val) {
                std::cout << "\t" << count << ": " << i << std::endl;
                count += 1;
            }
        }
    }
    //
    //    void printResultsMap2(ResultsMap &resultsMap) {
    //        int numCols = resultsMap.size();
    //        int numRows = resultsMap.at(0).size();
    //        for (int irow = 0 ; irow <numRows; irow++){
    //            for (int icol = 0; icol<numCols; icol++){
    //                std::cout << resultsMap.at(icol)
    //
    //            }
    //        }
    //    }

    std::string toTurtle(std::string in, std::string inputSyntax, std::string outSyntax = "turtle") {
        LibrdfStorage storage;
        LibrdfModel model(storage);
        LibrdfParser parser(inputSyntax);
        parser.parseString(in, model, "https://baseUriNotNeeded.com");
        LibrdfSerializer serializer(outSyntax.c_str());
        std::string out = serializer.toString("s", model);
        return out;
    }
};


TEST_F(PurgeRDFBagTests2, WithRDdFBagLists2) {

    std::string in = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#>.\n"
                     "@prefix s:   <http://example.org/students/vocab#>.\n"
                     "\n"
                     "<http://example.org/courses/6.001>\n"
                     "    s:students [\n"
                     "        a rdf:Bag;\n"
                     "        rdf:_1 <http://example.org/students/Amy>;\n"
                     "        rdf:_2 <http://example.org/students/Mohamed>;\n"
                     "    ].";

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#>.\n"
                           "@prefix s:   <http://example.org/students/vocab#>.\n"
                           "\n"
                           "<http://example.org/courses/6.001>\n"
                           "    s:students <http://example.org/students/Amy>, <http://example.org/students/Mohamed> .";

    checkRDFBagIsPurged(in, "turtle", expected);
    //    std::cout << expected <<std::endl;
    //    std::cout << toTurtle(in, "turtle", "rdfxml");
    //    auto results = runQuery(in, "turtle", PurgeRDFBag::rdfBagQueryString());
    //    printResultsMap(results);

    //    EXPECT_CALL(mockRdf, getModel)
    //        .WillRepeatedly(Return(model.get()));

    //    PurgeRDFBag purgeRdfBag(&mockRdf);
    //    purgeRdfBag.purgeListBagEntries();
}


TEST_F(PurgeRDFBagTests2, CreatorFromBIOMD385) {
    std::string in = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                     "\n"
                     "<https://baseUriNotNeeded.com#_272044>\n"
                     "    <http://purl.org/dc/elements/1.1/creator> [\n"
                     "        rdf:_1 [\n"
                     "            <http://www.w3.org/2001/vcard-rdf/3.0#EMAIL> \"viji@ebi.ac.uk\" ;\n"
                     "            <http://www.w3.org/2001/vcard-rdf/3.0#N> [\n"
                     "                <http://www.w3.org/2001/vcard-rdf/3.0#Family> \"Chelliah\" ;\n"
                     "                <http://www.w3.org/2001/vcard-rdf/3.0#Given> \"Vijayalakshmi\"\n"
                     "            ] ;\n"
                     "            <http://www.w3.org/2001/vcard-rdf/3.0#ORG> [\n"
                     "                <http://www.w3.org/2001/vcard-rdf/3.0#Orgname> \"EMBL-EBI\"\n"
                     "            ]\n"
                     "        ] ;\n"
                     "        rdf:_2 [\n"
                     "            <http://www.w3.org/2001/vcard-rdf/3.0#EMAIL> \"nikoloski@mpimp-golm.mpg.de\" ;\n"
                     "            <http://www.w3.org/2001/vcard-rdf/3.0#N> [\n"
                     "                <http://www.w3.org/2001/vcard-rdf/3.0#Family> \"Nikoloski\" ;\n"
                     "                <http://www.w3.org/2001/vcard-rdf/3.0#Given> \"Zoran\"\n"
                     "            ] ;\n"
                     "            <http://www.w3.org/2001/vcard-rdf/3.0#ORG> [\n"
                     "                <http://www.w3.org/2001/vcard-rdf/3.0#Orgname> \"\"\"Institute of Biochemistry and Biology, University of Potsdam, 14476\n"
                     "                            Potsdam, Germany\n"
                     "                        \"\"\"\n"
                     "            ]\n"
                     "        ] ;\n"
                     "        rdf:_3 [\n"
                     "            <http://www.w3.org/2001/vcard-rdf/3.0#EMAIL> \"arnold@mpimp-golm.mpg.de\" ;\n"
                     "            <http://www.w3.org/2001/vcard-rdf/3.0#N> [\n"
                     "                <http://www.w3.org/2001/vcard-rdf/3.0#Family> \"Arnold\" ;\n"
                     "                <http://www.w3.org/2001/vcard-rdf/3.0#Given> \"Anne\"\n"
                     "            ] ;\n"
                     "            <http://www.w3.org/2001/vcard-rdf/3.0#ORG> [\n"
                     "                <http://www.w3.org/2001/vcard-rdf/3.0#Orgname> \"Max-Planck-Institute of Molecular Plant Physiology\"\n"
                     "            ]\n"
                     "        ] ;\n"
                     "        a rdf:Bag\n"
                     "    ] .";

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "\n"
                           "<https://baseUriNotNeeded.com#_272044>\n"
                           "    <http://purl.org/dc/elements/1.1/creator> \n"
                           "        <http://www.w3.org/2001/vcard-rdf/3.0#EMAIL> \"viji@ebi.ac.uk\" ;\n"
                           "        <http://www.w3.org/2001/vcard-rdf/3.0#N> [\n"
                           "                <http://www.w3.org/2001/vcard-rdf/3.0#Family> \"Chelliah\" ;\n"
                           "                <http://www.w3.org/2001/vcard-rdf/3.0#Given> \"Vijayalakshmi\"\n"
                           "        ] ;\n"
                           "        <http://www.w3.org/2001/vcard-rdf/3.0#ORG> [\n"
                           "            <http://www.w3.org/2001/vcard-rdf/3.0#Orgname> \"EMBL-EBI\"\n"
                           "        ] ;\n"
                           "        <http://www.w3.org/2001/vcard-rdf/3.0#EMAIL> \"nikoloski@mpimp-golm.mpg.de\" ;\n"
                           "        <http://www.w3.org/2001/vcard-rdf/3.0#N> [\n"
                           "            <http://www.w3.org/2001/vcard-rdf/3.0#Family> \"Nikoloski\" ;\n"
                           "            <http://www.w3.org/2001/vcard-rdf/3.0#Given> \"Zoran\"\n"
                           "        ] ;\n"
                           "        <http://www.w3.org/2001/vcard-rdf/3.0#ORG> [\n"
                           "            <http://www.w3.org/2001/vcard-rdf/3.0#Orgname> \"\"\"Institute of Biochemistry and Biology, University of Potsdam, 14476\n"
                           "                        Potsdam, Germany\n"
                           "                    \"\"\"\n"
                           "        ]\n"
                           "        <http://www.w3.org/2001/vcard-rdf/3.0#EMAIL> \"arnold@mpimp-golm.mpg.de\" ;\n"
                           "        <http://www.w3.org/2001/vcard-rdf/3.0#N> [\n"
                           "            <http://www.w3.org/2001/vcard-rdf/3.0#Family> \"Arnold\" ;\n"
                           "            <http://www.w3.org/2001/vcard-rdf/3.0#Given> \"Anne\"\n"
                           "        ] ;\n"
                           "        <http://www.w3.org/2001/vcard-rdf/3.0#ORG> [\n"
                           "            <http://www.w3.org/2001/vcard-rdf/3.0#Orgname> \"Max-Planck-Institute of Molecular Plant Physiology\"\n"
                           "        ]\n"
                           "    ] .";

    std::cout << expected << std::endl;
    //    std::cout << toTurtle(in, "rdfxml")<< std::endl;
    checkRDFBagIsPurged(in, "turtle", expected);
}

TEST_F(PurgeRDFBagTests2, x) {
    std::string in = "            <rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                     "                     xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\"\n"
                     "                     xmlns:vCard=\"http://www.w3.org/2001/vcard-rdf/3.0#\" xmlns:dc=\"http://purl.org/dc/elements/1.1/\"\n"
                     "                     xmlns:dcterms=\"http://purl.org/dc/terms/\" xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\">\n"
                     "                <rdf:Description rdf:about=\"#_272044\">\n"
                     "                    <dc:creator>\n"
                     "                        <rdf:Bag>\n"
                     "                            <rdf:li rdf:parseType=\"Resource\">\n"
                     "                                <vCard:N rdf:parseType=\"Resource\">\n"
                     "                                    <vCard:Family>Chelliah</vCard:Family>\n"
                     "                                    <vCard:Given>Vijayalakshmi</vCard:Given>\n"
                     "                                </vCard:N>\n"
                     "                                <vCard:EMAIL>viji@ebi.ac.uk</vCard:EMAIL>\n"
                     "                                <vCard:ORG rdf:parseType=\"Resource\">\n"
                     "                                    <vCard:Orgname>EMBL-EBI</vCard:Orgname>\n"
                     "                                </vCard:ORG>\n"
                     "                            </rdf:li>\n"
                     "                            <rdf:li rdf:parseType=\"Resource\">\n"
                     "                                <vCard:N rdf:parseType=\"Resource\">\n"
                     "                                    <vCard:Family>Nikoloski</vCard:Family>\n"
                     "                                    <vCard:Given>Zoran</vCard:Given>\n"
                     "                                </vCard:N>\n"
                     "                                <vCard:EMAIL>nikoloski@mpimp-golm.mpg.de</vCard:EMAIL>\n"
                     "                                <vCard:ORG rdf:parseType=\"Resource\">\n"
                     "                                    <vCard:Orgname>Institute of Biochemistry and Biology, University of Potsdam, 14476\n"
                     "                                        Potsdam, Germany\n"
                     "                                    </vCard:Orgname>\n"
                     "                                </vCard:ORG>\n"
                     "                            </rdf:li>\n"
                     "                            <rdf:li rdf:parseType=\"Resource\">\n"
                     "                                <vCard:N rdf:parseType=\"Resource\">\n"
                     "                                    <vCard:Family>Arnold</vCard:Family>\n"
                     "                                    <vCard:Given>Anne</vCard:Given>\n"
                     "                                </vCard:N>\n"
                     "                                <vCard:EMAIL>arnold@mpimp-golm.mpg.de</vCard:EMAIL>\n"
                     "                                <vCard:ORG rdf:parseType=\"Resource\">\n"
                     "                                    <vCard:Orgname>Max-Planck-Institute of Molecular Plant Physiology</vCard:Orgname>\n"
                     "                                </vCard:ORG>\n"
                     "                            </rdf:li>\n"
                     "                        </rdf:Bag>\n"
                     "                    </dc:creator>\n"
                     "                    <dcterms:created rdf:parseType=\"Resource\">\n"
                     "                        <dcterms:W3CDTF>2011-10-19T14:51:13Z</dcterms:W3CDTF>\n"
                     "                    </dcterms:created>\n"
                     "                    <dcterms:modified rdf:parseType=\"Resource\">\n"
                     "                        <dcterms:W3CDTF>2012-04-20T19:52:45Z</dcterms:W3CDTF>\n"
                     "                    </dcterms:modified>\n"
                     "                    <bqmodel:is>\n"
                     "                        <rdf:Bag>\n"
                     "                            <rdf:li rdf:resource=\"http://identifiers.org/biomodels.db/MODEL1109270001\"/>\n"
                     "                        </rdf:Bag>\n"
                     "                    </bqmodel:is>\n"
                     "                    <bqmodel:is>\n"
                     "                        <rdf:Bag>\n"
                     "                            <rdf:li rdf:resource=\"http://identifiers.org/biomodels.db/BIOMD0000000385\"/>\n"
                     "                        </rdf:Bag>\n"
                     "                    </bqmodel:is>\n"
                     "                    <bqmodel:isDescribedBy>\n"
                     "                        <rdf:Bag>\n"
                     "                            <rdf:li rdf:resource=\"http://identifiers.org/pubmed/22001849\"/>\n"
                     "                        </rdf:Bag>\n"
                     "                    </bqmodel:isDescribedBy>\n"
                     "                    <bqmodel:is>\n"
                     "                        <rdf:Bag>\n"
                     "                            <rdf:li rdf:resource=\"http://identifiers.org/obo.go/GO:0019253\"/>\n"
                     "                        </rdf:Bag>\n"
                     "                    </bqmodel:is>\n"
                     "                    <bqbiol:hasTaxon>\n"
                     "                        <rdf:Bag>\n"
                     "                            <rdf:li rdf:resource=\"http://identifiers.org/taxonomy/33090\"/>\n"
                     "                        </rdf:Bag>\n"
                     "                    </bqbiol:hasTaxon>\n"
                     "                </rdf:Description>\n"
                     "            </rdf:RDF>";

    std::string expected;


    checkRDFBagIsPurged(in, "rdfxml", expected, "rdfxml");
}
