//
// Created by Ciaran on 4/9/2020.
//

#ifndef LIBSEMGEN_ANNOTATIONSAMPLES_H
#define LIBSEMGEN_ANNOTATIONSAMPLES_H


#include <string>

class AnnoationSamples {
public:

    std::string sample_annotation1 = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                                     "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                                     "         xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\">\n"
                                     "    <rdf:Description rdf:about=\"#metaid_1\">\n"
                                     "        <bqbiol:is rdf:resource=\"https://identifiers.org/uniprot/P0DP23\"/>\n"
                                     "    </rdf:Description>\n"
                                     "</rdf:RDF>";

    std::string sample_annotation2 = "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                                     "         xmlns:dc=\"http://purl.org/dc/elements/1.1/\" xmlns:dcterms=\"http://purl.org/dc/terms/\"\n"
                                     "         xmlns:vCard=\"http://www.w3.org/2001/vcard-rdf/3.0#\"\n"
                                     "         xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                                     "         xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\">\n"
                                     "    <rdf:Description rdf:about=\"#metaid_1\">\n"
                                     "        <bqbiol:is>\n"
                                     "            <rdf:Bag>\n"
                                     "                <rdf:li rdf:resource=\"http://identifiers.org/chebi/CHEBI:15343\"/>\n"
                                     "            </rdf:Bag>\n"
                                     "        </bqbiol:is>\n"
                                     "    </rdf:Description>\n"
                                     "</rdf:RDF>\n";

    std::string sample_annotation3 = "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                                     "         xmlns:dc=\"http://purl.org/dc/elements/1.1/\" xmlns:dcterms=\"http://purl.org/dc/terms/\"\n"
                                     "         xmlns:vCard=\"http://www.w3.org/2001/vcard-rdf/3.0#\"\n"
                                     "         xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                                     "         xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\">\n"
                                     "    <rdf:Description rdf:about=\"#metaid_2\">\n"
                                     "        <bqbiol:is>\n"
                                     "            <rdf:Bag>\n"
                                     "                <rdf:li rdf:resource=\"http://identifiers.org/chebi/CHEBI:28907\"/>\n"
                                     "            </rdf:Bag>\n"
                                     "        </bqbiol:is>\n"
                                     "    </rdf:Description>\n"
                                     "</rdf:RDF>\n";

};












#endif //LIBSEMGEN_ANNOTATIONSAMPLES_H


