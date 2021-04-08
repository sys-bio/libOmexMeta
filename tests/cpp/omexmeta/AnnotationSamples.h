//
// Created by Ciaran on 4/9/2020.
//

#ifndef LIBSEMGEN_ANNOTATIONSAMPLES_H
#define LIBSEMGEN_ANNOTATIONSAMPLES_H


#include <string>
#include "omexmeta/OmexMetaUtils.h"

class AnnotationSamples {
public:

    // urls and filepaths for some sbml samples
    std::string sbml_url1 = "https://www.ebi.ac.uk/biomodels/model/download/BIOMD0000000064.2?filename=BIOMD0000000064_url.xml";
    std::string sbml_filename1 = "./sbml_file1.sbml";

    std::string cellml_url1 = "http://models.cellml.org/workspace/267/download/824b8eefc8d7ad0f077b5466c06e8b4793882482/NBC.cellml";
    std::string cellml_filename1 = "./cellml_file1.cellml";

    // urls and filepaths for some cellml samples


    // urls and filepaths for the gold standard omex archives
    std::string gold_standard_url1 = "https://auckland.figshare.com/ndownloader/files/17432333";
    std::string gold_standard_url2 = "https://auckland.figshare.com/ndownloader/files/15425522";
    std::string gold_standard_url3 = "https://auckland.figshare.com/ndownloader/files/15425513";
    std::string gold_standard_url4 = "https://auckland.figshare.com/ndownloader/files/15425546";
    std::string gold_standard_url5 = "https://auckland.figshare.com/ndownloader/files/17432366";

    std::string gold_standard_filename1 = "./goldstandard1.omex";
    std::string gold_standard_filename2 = "./goldstandard2.omex";
    std::string gold_standard_filename3 = "./goldstandard3.omex";
    std::string gold_standard_filename4 = "./goldstandard4.omex";
    std::string gold_standard_filename5 = "./goldstandard5.omex";

    // collect all files into a iterable object for easy removal
    std::vector<std::string> all_files = {
            sbml_url1,
            sbml_filename1,
            gold_standard_url1,
            gold_standard_url2,
            gold_standard_url3,
            gold_standard_url4,
            gold_standard_url5,
            gold_standard_filename1,
            gold_standard_filename2,
            gold_standard_filename3,
            gold_standard_filename4,
            gold_standard_filename5,
    };

    std::string rdf_xml_example7 = "<?xml version=\"1.0\"?>\n"
                                   "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                                   "            xmlns:dc=\"http://purl.org/dc/elements/1.1/\"\n"
                                   "            xmlns:ex=\"http://example.org/stuff/1.0/\">\n"
                                   "  <rdf:Description rdf:about=\"http://www.w3.org/TR/rdf-syntax-grammar\"\n"
                                   "             dc:title=\"RDF1.1 XML Syntax\">\n"
                                   "    <ex:editor>\n"
                                   "      <rdf:Description ex:fullName=\"Dave Beckett\">\n"
                                   "        <ex:homePage rdf:resource=\"http://purl.org/net/dajobe/\" />\n"
                                   "      </rdf:Description>\n"
                                   "    </ex:editor>\n"
                                   "  </rdf:Description>\n"
                                   "</rdf:RDF>\n";

    std::string singular_annotation1 = "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                                       "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                                       "   xmlns:OMEXlib=\"http://omex-library.org/\"\n"
                                       "   xmlns:myOMEX=\"http://omex-library.org/NewModel.omex/\"\n"
                                       "   xmlns:local=\"http://omex-library.org/NewModel.rdf\"\n"
                                       "   xml:base=\"file://./NewModel.rdf\">\n"
                                       "    <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.xml#metaid_1\">\n"
                                       "        <bqbiol:is rdf:resource=\"https://identifiers.org/uniprot/P0DP23\"/>\n"
                                       "    </rdf:Description>\n"
                                       "</rdf:RDF>\n";


    std::string singular_annotation2 = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                                       "    <rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                                       "             xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\"\n"
                                       "             xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                                       "             xmlns:OMEXlib=\"http://omex-library.org/\"\n"
                                       "             xmlns:myOMEX=\"http://omex-library.org/NewOmex.omex/\"\n"
                                       "             xmlns:local=\"http://omex-library.org/NewOmex.omex/myomex.rdf\"\n"
                                       "             xml:base=\"file://./NewModel.rdf\">\n"
                                       "    <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.xml#modelmeta1\">\n"
                                       "        <bqmodel:isDescribedBy rdf:resource=\"https://identifiers.org/pubmed/12991237\" />\n"
                                       "    </rdf:Description>\n"
                                       "</rdf:RDF>\n";

    std::string singular_annotation3 = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                                       "    <rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                                       "             xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                                       "             xmlns:OMEXlib=\"http://omex-library.org/\"\n"
                                       "             xmlns:myOMEX=\"http://omex-library.org/NewOmex.omex/\"\n"
                                       "             xmlns:local=\"http://omex-library.org/NewOmex.omex/myomex.rdf\"\n"
                                       "             xml:base=\"file://./NewModel.rdf\">\n"
                                       "    <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.xml#meta1\">\n"
                                       "        <bqbiol:is rdf:resource=\"https://identifiers.org/chebi/CHEBI:15422\" />\n"
                                       "    </rdf:Description>\n"
                                       "</rdf:RDF>\n";

    std::string singular_annotation4 = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                                       "    <rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\""
                                       "             xmlns:dcterms=\"https://dublincore.org/specifications/dublin-core/dcmi-terms/\"\n"
                                       "             xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                                       "             xmlns:OMEXlib=\"http://omex-library.org/\"\n"
                                       "             xmlns:myOMEX=\"http://omex-library.org/NewOmex.omex/\"\n"
                                       "             xmlns:local=\"http://omex-library.org/NewOmex.omex/myomex.rdf\"\n"
                                       "             xml:base=\"file://./NewModel.rdf\">\n"
                                       "    <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.xml#meta2\">\n"
                                       "    <dcterms:description>Cardiomyocyte cytosolic ATP concentration</dcterms:description>\n"
                                       "    </rdf:Description>\n"
                                       "</rdf:RDF>";

    std::string composite_annotation_pe = "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                                          "         xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                                          "             xmlns:OMEXlib=\"http://omex-library.org/\"\n"
                                          "             xmlns:myOMEX=\"http://omex-library.org/NewOmex.omex/\"\n"
                                          "             xmlns:local=\"http://omex-library.org/NewOmex.omex/myomex.rdf\"\n"
                                          "             xml:base=\"file://./NewModel.rdf\">\n"
                                          "    <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.xml#VLV\">\n"
                                          "        <bqbiol:isVersionOf rdf:resource=\"http://identifiers.org/opb/OPB_00154\"/>\n"
                                          "        <bqbiol:isPropertyOf rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.xml#entity_0\"/>\n"
                                          "    </rdf:Description>\n"
                                          "    <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.xml#entity_0\">\n"
                                          "        <bqbiol:is rdf:resource=\"http://identifiers.org/fma/FMA:9670\" />\n"
                                          "        <bqbiol:isPartOf rdf:resource=\"http://identifiers.org/fma/FMA:18228\"/>\n"
                                          "    </rdf:Description>\n"
                                          "</rdf:RDF>\n";

    std::string composite_annotation_pp = "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                                          "         xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                                          "         xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\"\n"
                                          "             xml:base=\"file://./NewModel.xml\">\n"
                                          "    <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.xml#property_metaid_0\">\n"
                                          "        <bqbiol:isPropertyOf rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.xml#process_metaid_0\"/>\n"
                                          "        <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/opb/OPB_00592\"/>\n"
                                          "    </rdf:Description>"
                                          "    <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.xml#process_metaid_0\">\n"
                                          "        <semsim:hasSourceParticipant rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.xml#source_0\"/>\n"
                                          "        <semsim:hasSinkParticipant rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.xml#sink_0\"/>\n"
                                          "        <semsim:hasMediatorParticipant rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.xml#mediator_0\"/>\n"
                                          "    </rdf:Description>\n"
                                          "    <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.xml#source_0\">\n"
                                          "        <semsim:hasMultiplier>1.0</semsim:hasMultiplier>\n"
                                          "        <semsim:hasPhysicalEntityReference rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.xml#special_metaid_0\"/>\n"
                                          "    </rdf:Description>\n"
                                          "    <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.xml#sink_0\">\n"
                                          "        <semsim:hasMultiplier>2.0</semsim:hasMultiplier>\n"
                                          "        <semsim:hasPhysicalEntityReference rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.xml#special_metaid_1\"/>\n"
                                          "    </rdf:Description>"
                                          "    <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.xml#mediator_0\">\n"
                                          "        <semsim:hasPhysicalEntityReference rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.xml#special_metaid_2\"/>\n"
                                          "    </rdf:Description>"
                                          "</rdf:RDF>\n";

    std::string composite_annotation_pf = "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                                          "         xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                                          "         xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\"\n"
                                          "         xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\"\n"
                                          "             xml:base=\"file://./NewModel.xml\">\n"
                                          "    <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.xml#parameter_metaid_0\">\n"
                                          "        <bqbiol:isPropertyOf rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.xml#force_0\"/>\n"
                                          "        <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/opb/OPB_01058\"/>\n"
                                          "    </rdf:Description>"
                                          "    <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.xml#force_0\">\n"
                                          "        <semsim:hasSourceParticipant rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.xml#source_0\"/>\n"
                                          "        <semsim:hasSinkParticipant rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.xml#sink_0\"/>\n"
                                          "    </rdf:Description>\n"
                                          "    <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.xml#source_0\">\n"
                                          "        <semsim:hasPhysicalEntityReference rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.xml#special_metaid_0\"/>\n"
                                          "    </rdf:Description>\n"
                                          "    <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.xml#sink_0\">\n"
                                          "        <semsim:hasPhysicalEntityReference rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.xml#special_metaid_1\"/>\n"
                                          "    </rdf:Description>"
                                          "</rdf:RDF>\n";

    std::string tabular_data1 = "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                                "         xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\"\n"
                                "         xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                                "         xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\"\n"
                                "             xml:base=\"file://./MyData.csv\">\n"
                                "    <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.xml#VleftCorArt\">\n"
                                "        <bqbiol:isVersionOf rdf:resource=\"http://identifiers.org/opb/OPB_00154\" />\n"
                                "        <bqbiol:isPropertyOf rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.xml#entity_0\"/>\n"
                                "    </rdf:Description>\n"
                                "    <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.xml#entity_0\">\n"
                                "        <bqbiol:is rdf:resource=\"http://identifiers.org/fma/FMA:9670\" />\n"
                                "        <bqbiol:isPartOf rdf:resource=\"http://identifiers.org/fma/FMA:18228\"/>\n"
                                "    </rdf:Description>"
                                "</rdf:RDF>\n";

    std::string rdf_turtle_bag_example = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#>.\n"
                                         "@prefix s:   <http://example.org/students/vocab#>.\n"
                                         "\n"
                                         "<http://example.org/courses/6.001>\n"
                                         "    s:students [\n"
                                         "        a rdf:Bag;\n"
                                         "        rdf:_1 <http://example.org/students/Amy>;\n"
                                         "        rdf:_2 <http://example.org/students/Mohamed>;\n"
                                         "        rdf:_3 <http://example.org/students/Johann>;\n"
                                         "        rdf:_4 <http://example.org/students/Maria>;\n"
                                         "        rdf:_5 <http://example.org/students/Phuong>;\n"
                                         "    ].";

    std::string rdf_xml_seq_example = "<?xml version=\"1.0\"?>\n"
                                      "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n"
                                      "  <rdf:Seq rdf:about=\"http://example.org/favourite-fruit\">\n"
                                      "    <rdf:_1 rdf:resource=\"http://example.org/banana\"/>\n"
                                      "    <rdf:_2 rdf:resource=\"http://example.org/apple\"/>\n"
                                      "    <rdf:_3 rdf:resource=\"http://example.org/pear\"/>\n"
                                      "  </rdf:Seq>\n"
                                      "</rdf:RDF>";

    std::string rdf_xml_bag_example = "<?xml version=\"1.0\"?>\n"
                                      "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n"
                                      "  <rdf:Bag rdf:about=\"http://example.org/favourite-fruit\">\n"
                                      "    <rdf:_1 rdf:resource=\"http://example.org/banana\"/>\n"
                                      "    <rdf:_2 rdf:resource=\"http://example.org/apple\"/>\n"
                                      "    <rdf:_3 rdf:resource=\"http://example.org/pear\"/>\n"
                                      "  </rdf:Bag>\n"
                                      "</rdf:RDF>";

    std::string rdf_turtle_basic_example = "@base <http://example.org/> .\n"
                                           "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                                           "@prefix rdfs: <http://www.w3.org/2000/01/rdf-schema#> .\n"
                                           "@prefix foaf: <http://xmlns.com/foaf/0.1/> .\n"
                                           "@prefix rel: <http://www.perceive.net/schemas/relationship/> .\n"
                                           "\n"
                                           "<#green-goblin>\n"
                                           "    rel:enemyOf <#spiderman> ;\n"
                                           "    a foaf:Person ;    # in the context of the Marvel universe\n"
                                           "    foaf:name \"Green Goblin\" .\n"
                                           "\n"
                                           "<#spiderman>\n"
                                           "    rel:enemyOf <#green-goblin> ;\n"
                                           "    a foaf:Person ;\n"
                                           "    foaf:name \"Spiderman\", \"Человек-паук\"@ru .";

    std::string rdf_xml_collection_type_example = "<?xml version=\"1.0\"?>\n"
                                                  "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                                                  "            xmlns:ex=\"http://example.org/stuff/1.0/\">\n"
                                                  "\n"
                                                  "  <rdf:Description rdf:about=\"http://example.org/basket\">\n"
                                                  "    <ex:hasFruit rdf:parseType=\"Collection\">\n"
                                                  "      <rdf:Description rdf:about=\"http://example.org/banana\"/>\n"
                                                  "      <rdf:Description rdf:about=\"http://example.org/apple\"/>\n"
                                                  "      <rdf:Description rdf:about=\"http://example.org/pear\"/>\n"
                                                  "    </ex:hasFruit>\n"
                                                  "  </rdf:Description>\n"
                                                  "\n"
                                                  "</rdf:RDF>";

    std::string simple_input_turtle_string = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                                             "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                                             "@prefix OMEXlib: <http://omex-library.org/> .\n"
                                             "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                                             "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                                             "\n"
                                             "<http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0000>\n"
                                             "     bqbiol:is <https://identifiers.org/uniprot/PD12345> .\n";

    std::string cellml_example = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                                 "<model xmlns=\"http://www.cellml.org/cellml/1.1#\" xmlns:cmeta=\"http://www.cellml.org/metadata/1.0#\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:bqs=\"http://www.cellml.org/bqs/1.0#\" xmlns:semsim=\"http://www.bhi.washington.edu/SemSim#\" xmlns:dc=\"https://dublincore.org/specifications/dublin-core/dcmi-terms/\" xmlns:vCard=\"http://www.w3.org/2001/vcard-rdf/3.0#\" name=\"annotation_examples\" cmeta:id=\"annExamples\">\n"
                                 "  <component name=\"main\">\n"
                                 "    <variable cmeta:id=\"main.Volume\" initial_value=\"100\" name=\"Volume\" units=\"dimensionless\" />\n"
                                 "    <variable cmeta:id=\"main.MembraneVoltage\" initial_value=\"-80\" name=\"MembraneVoltage\" units=\"dimensionless\" />\n"
                                 "    <variable cmeta:id=\"main.ReactionRate\" initial_value=\"1\" name=\"ReactionRate\" units=\"dimensionless\" />\n"
                                 "  </component>\n"
                                 "</model>";

    std::string cellml_example_annotation = "<rdf:RDF\n"
                                            "    xmlns:semsim=\"http://www.bhi.washington.edu/SemSim#\"\n"
                                            "    xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                                            "    xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\"\n"
                                            "    xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                                            "    xmlns:dc=\"https://dublincore.org/specifications/dublin-core/dcmi-terms/\"\n"
                                            "    xmlns:myOMEX=\"http://omex-library.org/CellMLexamples.omex\"\n"
                                            "    xmlns:foaf=\"http://xmlns.com/foaf/0.1/\"\n"
                                            "    xmlns:local=\"http://omex-library.org/CellMLexamples.omex/examples.rdf\">\n"
                                            "  <rdf:Description rdf:about=\"http://omex-library.org/CellMLexamples.omex/examples.cellml#main.ReactionRate\">\n"
                                            "    <bqbiol:isPropertyOf>\n"
                                            "      <rdf:Description rdf:about=\"http://omex-library.org/CellMLexamples.omex/examples.rdf#process_0\">\n"
                                            "        <semsim:hasMediatorParticipant>\n"
                                            "          <rdf:Description rdf:about=\"http://omex-library.org/CellMLexamples.omex/examples.rdf#mediator_0\">\n"
                                            "            <semsim:hasPhysicalEntityReference>\n"
                                            "              <rdf:Description rdf:about=\"http://omex-library.org/CellMLexamples.omex/examples.rdf#entity_12\">\n"
                                            "                <bqbiol:isPartOf>\n"
                                            "                  <rdf:Description rdf:about=\"http://omex-library.org/CellMLexamples.omex/examples.rdf#entity_9\">\n"
                                            "                    <bqbiol:isPartOf>\n"
                                            "                      <rdf:Description rdf:about=\"http://omex-library.org/CellMLexamples.omex/examples.rdf#entity_10\">\n"
                                            "                        <bqbiol:is rdf:resource=\"http://identifiers.org/fma/FMA:14515\"/>\n"
                                            "                      </rdf:Description>\n"
                                            "                    </bqbiol:isPartOf>\n"
                                            "                    <bqbiol:is rdf:resource=\"http://identifiers.org/fma/FMA:66836\"/>\n"
                                            "                  </rdf:Description>\n"
                                            "                </bqbiol:isPartOf>\n"
                                            "                <bqbiol:is rdf:resource=\"http://purl.obolibrary.org/obo/PR_000003767\"/>\n"
                                            "              </rdf:Description>\n"
                                            "            </semsim:hasPhysicalEntityReference>\n"
                                            "          </rdf:Description>\n"
                                            "        </semsim:hasMediatorParticipant>\n"
                                            "        <semsim:hasSinkParticipant>\n"
                                            "          <rdf:Description rdf:about=\"http://omex-library.org/CellMLexamples.omex/examples.rdf#sink_1\"\n"
                                            "             semsim:hasMultiplier=\"1.0\">\n"
                                            "            <semsim:hasPhysicalEntityReference>\n"
                                            "              <rdf:Description rdf:about=\"http://omex-library.org/CellMLexamples.omex/examples.rdf#entity_11\">\n"
                                            "                <bqbiol:isPartOf rdf:resource=\"http://omex-library.org/CellMLexamples.omex/examples.rdf#entity_9\"/>\n"
                                            "                <bqbiol:is rdf:resource=\"https://identifiers.org/chebi/CHEBI:15343\"/>\n"
                                            "              </rdf:Description>\n"
                                            "            </semsim:hasPhysicalEntityReference>\n"
                                            "          </rdf:Description>\n"
                                            "        </semsim:hasSinkParticipant>\n"
                                            "        <semsim:hasSourceParticipant>\n"
                                            "          <rdf:Description rdf:about=\"http://omex-library.org/CellMLexamples.omex/examples.rdf#source_1\"\n"
                                            "             semsim:hasMultiplier=\"1.0\">\n"
                                            "            <semsim:hasPhysicalEntityReference>\n"
                                            "              <rdf:Description rdf:about=\"http://omex-library.org/CellMLexamples.omex/examples.rdf#entity_8\">\n"
                                            "                <bqbiol:isPartOf rdf:resource=\"http://omex-library.org/CellMLexamples.omex/examples.rdf#entity_9\"/>\n"
                                            "                <bqbiol:is rdf:resource=\"https://identifiers.org/chebi/CHEBI:16236\"/>\n"
                                            "              </rdf:Description>\n"
                                            "            </semsim:hasPhysicalEntityReference>\n"
                                            "          </rdf:Description>\n"
                                            "        </semsim:hasSourceParticipant>\n"
                                            "        <semsim:name>my process</semsim:name>\n"
                                            "        <bqbiol:isVersionOf rdf:resource=\"http://identifiers.org/go/GO:0004022\"/>\n"
                                            "      </rdf:Description>\n"
                                            "    </bqbiol:isPropertyOf>\n"
                                            "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/opb/OPB_00592\"/>\n"
                                            "  </rdf:Description>\n"
                                            "  <rdf:Description rdf:about=\"http://omex-library.org/CellMLexamples.omex/examples.cellml#main.Volume\">\n"
                                            "    <bqbiol:isPropertyOf>\n"
                                            "      <rdf:Description rdf:about=\"http://omex-library.org/CellMLexamples.omex/examples.rdf#entity_0\">\n"
                                            "        <bqbiol:isPartOf>\n"
                                            "          <rdf:Description rdf:about=\"http://omex-library.org/CellMLexamples.omex/examples.rdf#entity_1\">\n"
                                            "            <bqbiol:is rdf:resource=\"http://identifiers.org/fma/FMA:18228\"/>\n"
                                            "          </rdf:Description>\n"
                                            "        </bqbiol:isPartOf>\n"
                                            "        <bqbiol:is rdf:resource=\"http://identifiers.org/fma/FMA:9670\"/>\n"
                                            "      </rdf:Description>\n"
                                            "    </bqbiol:isPropertyOf>\n"
                                            "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/opb/OPB_00154\"/>\n"
                                            "  </rdf:Description>\n"
                                            "  <rdf:Description rdf:about=\"http://omex-library.org/CellMLexamples.omex/examples.cellml\"\n"
                                            "     semsim:modelName=\"annotation_examples\"/>\n"
                                            "  <rdf:Description rdf:about=\"http://omex-library.org/CellMLexamples.omex/examples.cellml#main.MembraneVoltage\">\n"
                                            "    <bqbiol:isPropertyOf>\n"
                                            "      <rdf:Description rdf:about=\"http://omex-library.org/CellMLexamples.omex/examples.rdf#force_0\">\n"
                                            "        <semsim:hasSinkParticipant>\n"
                                            "          <rdf:Description rdf:about=\"http://omex-library.org/CellMLexamples.omex/examples.rdf#sink_0\">\n"
                                            "            <semsim:hasPhysicalEntityReference>\n"
                                            "              <rdf:Description rdf:about=\"http://omex-library.org/CellMLexamples.omex/examples.rdf#entity_5\">\n"
                                            "                <bqbiol:isPartOf>\n"
                                            "                  <rdf:Description rdf:about=\"http://omex-library.org/CellMLexamples.omex/examples.rdf#entity_6\">\n"
                                            "                    <bqbiol:isPartOf>\n"
                                            "                      <rdf:Description rdf:about=\"http://omex-library.org/CellMLexamples.omex/examples.rdf#entity_7\">\n"
                                            "                        <bqbiol:is rdf:resource=\"http://identifiers.org/fma/FMA:16016\"/>\n"
                                            "                      </rdf:Description>\n"
                                            "                    </bqbiol:isPartOf>\n"
                                            "                    <bqbiol:is rdf:resource=\"http://identifiers.org/fma/FMA:9672\"/>\n"
                                            "                  </rdf:Description>\n"
                                            "                </bqbiol:isPartOf>\n"
                                            "                <bqbiol:is rdf:resource=\"https://identifiers.org/chebi/CHEBI:24870\"/>\n"
                                            "              </rdf:Description>\n"
                                            "            </semsim:hasPhysicalEntityReference>\n"
                                            "          </rdf:Description>\n"
                                            "        </semsim:hasSinkParticipant>\n"
                                            "        <semsim:hasSourceParticipant>\n"
                                            "          <rdf:Description rdf:about=\"http://omex-library.org/CellMLexamples.omex/examples.rdf#source_0\">\n"
                                            "            <semsim:hasPhysicalEntityReference>\n"
                                            "              <rdf:Description rdf:about=\"http://omex-library.org/CellMLexamples.omex/examples.rdf#entity_2\">\n"
                                            "                <bqbiol:isPartOf>\n"
                                            "                  <rdf:Description rdf:about=\"http://omex-library.org/CellMLexamples.omex/examples.rdf#entity_3\">\n"
                                            "                    <bqbiol:isPartOf>\n"
                                            "                      <rdf:Description rdf:about=\"http://omex-library.org/CellMLexamples.omex/examples.rdf#entity_4\">\n"
                                            "                        <bqbiol:is rdf:resource=\"http://identifiers.org/fma/FMA:70586\"/>\n"
                                            "                      </rdf:Description>\n"
                                            "                    </bqbiol:isPartOf>\n"
                                            "                    <bqbiol:is rdf:resource=\"http://identifiers.org/fma/FMA:66836\"/>\n"
                                            "                  </rdf:Description>\n"
                                            "                </bqbiol:isPartOf>\n"
                                            "                <bqbiol:is rdf:resource=\"https://identifiers.org/chebi/CHEBI:24870\"/>\n"
                                            "              </rdf:Description>\n"
                                            "            </semsim:hasPhysicalEntityReference>\n"
                                            "          </rdf:Description>\n"
                                            "        </semsim:hasSourceParticipant>\n"
                                            "      </rdf:Description>\n"
                                            "    </bqbiol:isPropertyOf>\n"
                                            "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/opb/OPB_00506\"/>\n"
                                            "  </rdf:Description>\n"
                                            "</rdf:RDF>";

    std::string annotationFromSBMLModelWithRDFBag = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                                                    "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                                                    "@prefix semsim: <http://bime.uw.edu/semsim/> .\n"
                                                    "@prefix OMEXlib: <http://omex-library.org/> .\n"
                                                    "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                                                    "\n"
                                                    "local:ProcessProperty0000\n"
                                                    "    bqbiol:isPropertyOf <http://omex-library.org/NewOmex.omex/NewModel.xml#reaction0000> ;\n"
                                                    "    bqbiol:isVersionOf <https://identifiers.org/opb:OPB_00592> .\n"
                                                    "\n"
                                                    "local:SinkParticipant0000\n"
                                                    "    semsim:hasMultiplier \"1\"^^rdf:double ;\n"
                                                    "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#species0000> .\n"
                                                    "\n"
                                                    "local:SourceParticipant0000\n"
                                                    "    semsim:hasMultiplier \"1\"^^rdf:double ;\n"
                                                    "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#S1> .\n"
                                                    "\n"
                                                    "<http://omex-library.org/NewOmex.omex/NewModel.xml#S1>\n"
                                                    "    bqbiol:isVersionOf [\n"
                                                    "        rdf:_1 <http://identifiers.org/obo.chebi/CHEBI:16526> ;\n"
                                                    "        a rdf:Bag\n"
                                                    "    ] .\n"
                                                    "\n"
                                                    "<http://omex-library.org/NewOmex.omex/NewModel.xml#reaction0000>\n"
                                                    "    semsim:hasSinkParticipant local:SinkParticipant0000 ;\n"
                                                    "    semsim:hasSourceParticipant local:SourceParticipant0000 .";

    void removeAllFilesIfTheyExist() {
        for (auto &file : this->all_files) {
            omexmeta::OmexMetaUtils::removeIfExists(file);
        }
    }

};


#endif //LIBSEMGEN_ANNOTATIONSAMPLES_H


