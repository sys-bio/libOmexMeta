//
// Created by Ciaran on 4/9/2020.
//

#ifndef LIBSEMGEN_ANNOTATIONSAMPLES_H
#define LIBSEMGEN_ANNOTATIONSAMPLES_H


#include <string>

class AnnoationSamples {
public:

    std::string singular_annotation1 = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                                       "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                                       "         xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\">\n"
                                       "    <rdf:Description rdf:about=\"#metaid_1\">\n"
                                       "        <bqbiol:is rdf:resource=\"https://identifiers.org/uniprot/P0DP23\"/>\n"
                                       "    </rdf:Description>\n"
                                       "</rdf:RDF>\n";

    std::string singular_annotation2 = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                                       "    <rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                                       "             xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\"\n"
                                       "             xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\">\n"
                                       "    <rdf:Description rdf:about=\"./MyModel.xml#modelmeta1\">\n"
                                       "        <bqmodel:isDescribedBy rdf:resource=\"https://identifiers.org/pubmed/12991237\" />\n"
                                       "    </rdf:Description>\n"
                                       "</rdf:RDF>\n";

    std::string singular_annotation3 = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                                       "    <rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                                       "             xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\">\n"
                                       "    <rdf:Description rdf:about=\"./MyModel.xml#meta1\">\n"
                                       "        <bqbiol:is rdf:resource=\"https://identifiers.org/chebi/CHEBI:15422\" />\n"
                                       "    </rdf:Description>\n"
                                       "</rdf:RDF>\n";

    std::string singular_annotation4 = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                                       "    <rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\""
                                       "             xmlns:dcterms=\"http://purl.org/dc/terms/\"\n"
                                       "             xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\">\n"
                                       "    <rdf:Description rdf:about=\"./MyModel.xml#meta2\">\n"
                                       "    <dcterms:description>Cardiomyocyte cytosolic ATP concentration</dcterms:description>\n"
                                       "    </rdf:Description>\n"
                                       "</rdf:RDF>";

    std::string composite_annotation_pe = "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                                          "         xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\">\n"
                                          "    <rdf:Description rdf:about=\"./MyModel.xml#VLV\">\n"
                                          "        <bqbiol:isVersionOf rdf:resource=\"http://identifiers.org/opb/OPB_00154\"/>\n"
                                          "        <bqbiol:isPropertyOf rdf:resource=\"#entity_0\"/>\n"
                                          "    </rdf:Description>\n"
                                          "    <rdf:Description rdf:about=\"#entity_0\">\n"
                                          "        <bqbiol:is rdf:resource=\"http://identifiers.org/fma/FMA:9670\" />\n"
                                          "        <bqbiol:isPartOf rdf:resource=\"http://identifiers.org/fma/FMA:18228\"/>\n"
                                          "    </rdf:Description>\n"
                                          "</rdf:RDF>\n";

    std::string composite_annotation_pp = "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                                          "         xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                                          "         xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\"\n"
                                          "         xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\">\n"
                                          "    <rdf:Description rdf:about=\"./MyModel.xml#property_metaid_0\">\n"
                                          "        <bqbiol:isPropertyOf rdf:resource=\"./MyModel.xml#process_metaid_0\"/>\n"
                                          "        <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/opb/OPB_00592\"/>\n"
                                          "    </rdf:Description>"
                                          "    <rdf:Description rdf:about=\"./MyModel.xml#process_metaid_0\">\n"
                                          "        <semsim:hasSourceParticipant rdf:resource=\"./MyModel.xml#source_0\"/>\n"
                                          "        <semsim:hasSinkParticipant rdf:resource=\"./MyModel.xml#sink_0\"/>\n"
                                          "        <semsim:hasMediatorParticipant rdf:resource=\"./MyModel.xml#mediator_0\"/>\n"
                                          "    </rdf:Description>\n"
                                          "    <rdf:Description rdf:about=\"./MyModel.xml#source_0\">\n"
                                          "        <semsim:hasMultiplier>1.0</semsim:hasMultiplier>\n"
                                          "        <semsim:hasPhysicalEntityReference rdf:resource=\"./MyModel.xml#species_metaid_0\"/>\n"
                                          "    </rdf:Description>\n"
                                          "    <rdf:Description rdf:about=\"./MyModel.xml#sink_0\">\n"
                                          "        <semsim:hasMultiplier>2.0</semsim:hasMultiplier>\n"
                                          "        <semsim:hasPhysicalEntityReference rdf:resource=\"./MyModel.xml#species_metaid_1\"/>\n"
                                          "    </rdf:Description>"
                                          "    <rdf:Description rdf:about=\"./MyModel.xml#mediator_0\">\n"
                                          "        <semsim:hasPhysicalEntityReference rdf:resource=\"./MyModel.xml#species_metaid_2\"/>\n"
                                          "    </rdf:Description>"
                                          "</rdf:RDF>\n";

    std::string composite_annotation_pf = "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                                          "         xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                                          "         xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\"\n"
                                          "         xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\">\n"
                                          "    <rdf:Description rdf:about=\"./MyModel.sbml#parameter_metaid_0\">\n"
                                          "        <bqbiol:isPropertyOf rdf:resource=\"./MyModel.sbml#force_0\"/>\n"
                                          "        <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/opb/OPB_01058\"/>\n"
                                          "    </rdf:Description>"
                                          "    <rdf:Description rdf:about=\"./MyModel.sbml#force_0\">\n"
                                          "        <semsim:hasSourceParticipant rdf:resource=\"./MyModel.sbml#source_0\"/>\n"
                                          "        <semsim:hasSinkParticipant rdf:resource=\"./MyModel.sbml#sink_0\"/>\n"
                                          "    </rdf:Description>\n"
                                          "    <rdf:Description rdf:about=\"./MyModel.sbml#source_0\">\n"
                                          "        <semsim:hasPhysicalEntityReference rdf:resource=\"./MyModel.sbml#species_metaid_0\"/>\n"
                                          "    </rdf:Description>\n"
                                          "    <rdf:Description rdf:about=\"./MyModel.sbml#sink_0\">\n"
                                          "        <semsim:hasPhysicalEntityReference rdf:resource=\"./MyModel.sbml#species_metaid_1\"/>\n"
                                          "    </rdf:Description>"
                                          "</rdf:RDF>\n";

    std::string tabular_data1 = "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                                "         xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\"\n"
                                "         xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                                "         xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\">\n"
                                "    <rdf:Description rdf:about=\"./MyData.csv#VleftCorArt\">\n"
                                "        <bqbiol:isVersionOf rdf:resource=\"http://identifiers.org/opb/OPB_00154\" />\n"
                                "        <bqbiol:isPropertyOf rdf:resource=\"#entity_0\"/>\n"
                                "    </rdf:Description>\n"
                                "    <rdf:Description rdf:about=\"#entity_0\">\n"
                                "        <bqbiol:is rdf:resource=\"http://identifiers.org/fma/FMA:9670\" />\n"
                                "        <bqbiol:isPartOf rdf:resource=\"http://identifiers.org/fma/FMA:18228\"/>\n"
                                "    </rdf:Description>"
                                "</rdf:RDF>\n";
};


#endif //LIBSEMGEN_ANNOTATIONSAMPLES_H


