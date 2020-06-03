//
// Created by Ciaran on 4/14/2020.
//

#include "SemsimXmlAssistant.h"
#include "HERE.h"

namespace semsim {
    SemsimXmlAssistant::SemsimXmlAssistant(std::string xml, std::string base, int metaid_num_digits) :
            xml_(std::move(xml)), metaid_base(std::move(base)), metaid_num_digits_(metaid_num_digits) {
    }

    std::vector<std::string> SemsimXmlAssistant::getValidElements() {
        return std::vector<std::string>({"Any"});
    }

    void SemsimXmlAssistant::generateMetaId(std::vector<std::string> &seen_metaids, long count,
                                            const MetaID &metaid_gen,
                                            std::string &id) {
        HERE();
        id = metaid_gen.generate(count);
        HERE();

        if (std::find(seen_metaids.begin(), seen_metaids.end(), id) != seen_metaids.end()) {
            HERE();
            count += 1;
            HERE();
            generateMetaId(seen_metaids, count, metaid_gen, id); // recursion
            HERE();
        }
    }

    void SemsimXmlAssistant::addMetaIdsRecursion(xmlNode *a_node, std::vector<std::string> &seen_metaids) {
        HERE();
        MetaID metaId("SemsimMetaid", 0, 4);
        HERE();
        xmlNode *cur_node = nullptr;
        HERE();
        long count = 0;
        HERE();
        for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
            HERE();
            // isolate element nodes
            if (cur_node->type == XML_ELEMENT_NODE) {
                HERE();
                // if the node name is in our list of valid elements or if valid_elements_ = ["All"]
                if (std::find(getValidElements().begin(), getValidElements().end(),
                              std::string((const char *) cur_node->name)) != getValidElements().end()
                    ||
                    (getValidElements().size() == 1 &&
                     strcmp(getValidElements()[0].c_str(), (const char *) "All") != 0)) {
                    // test to see whether the element has the metaid attribute
                    HERE();
                    bool has_meta_id = xmlHasProp(cur_node, (const xmlChar *) "metaid");
                    HERE();
                    if (!has_meta_id) {
                        // if not, we add one and give it a unique value
                        HERE();
                        std::string id;
                        HERE();
                        SemsimXmlAssistant::generateMetaId(seen_metaids, count, metaId, id);
                        HERE();
                        xmlNewProp(cur_node, (const xmlChar *) "metaid", (const xmlChar *) id.c_str());
                        HERE();
                        seen_metaids.push_back(id);
                        HERE();
                        count += 1;
                        HERE();
                    } else {
                        HERE();
                        // if so, we take note by adding it to seen_metaids.
                        xmlChar *id = xmlGetProp(cur_node, (const xmlChar *) "metaid");
                        HERE();
                        seen_metaids.emplace_back((const char *) id);
                        HERE();
                        xmlFree(id);
                        HERE();
                    }

                }
            }
            // recursion, we do this for every node
            HERE();
            addMetaIdsRecursion(cur_node->children, seen_metaids);
            HERE();
        }
    }


    std::pair<std::string, std::vector<std::string>> SemsimXmlAssistant::addMetaIds() {
        LIBXML_TEST_VERSION;
        HERE();
        xmlDocPtr doc; /* the resulting document tree */
        HERE();
        doc = xmlParseDoc((const xmlChar *) xml_.c_str());
        HERE();
        if (doc == nullptr) {
            throw std::bad_alloc();
        }
        HERE();

        xmlNodePtr root_element = xmlDocGetRootElement(doc);
        HERE();

        std::vector<std::string> seen_metaids = {};
        HERE();
        addMetaIdsRecursion(root_element, seen_metaids);
        HERE();

        xmlChar *s;
        HERE();
        int size;
        HERE();
        xmlDocDumpMemory(doc, &s, &size);
        HERE();
        if (s == nullptr)
            throw std::bad_alloc();
        HERE();
        std::string x = std::string((const char *) s);
        HERE();
        xmlFree(s);
        HERE();

        xmlFreeDoc(doc);
        HERE();
        xmlCleanupParser();
        HERE();
        std::pair<std::string, std::vector<std::string>> sbml_with_metaid(x, seen_metaids);
        HERE();
        return sbml_with_metaid;
    }


    std::vector<std::string> SBMLAssistant::getValidElements() {
        std::vector<std::string> valid_elements_ = {
                "model",
                "unit",
                "compartment",
                "species",
                "reaction",
                "kineticLaw",
                "localParameter",
        };
        return valid_elements_;
    }

    std::vector<std::string> CellMLAssistant::getValidElements() {
        std::vector<std::string> valid_elements_ = {
                "model",
                "unit",
                "compartment",
                "species",
                "reaction",
                "kineticLaw",
                "localParameter",
        };
        return valid_elements_;
    }

    XmlAssistantPtr SemsimXmlAssistantFactory::generate(const std::string &xml, SemsimXmlType type) {
        switch (type) {
            case SEMSIM_TYPE_SBML: {
                SBMLAssistant sbmlAssistant(xml);
                return std::make_unique<SBMLAssistant>(sbmlAssistant);
            }
            case SEMSIM_TYPE_CELLML: {
                CellMLAssistant cellMlAssistant(xml);
                return std::make_unique<CellMLAssistant>(cellMlAssistant);
            }
            case SEMSIM_TYPE_OTHER: {
                SemsimXmlAssistant xmlAssistant(xml);
                return std::make_unique<SemsimXmlAssistant>(xmlAssistant);
            }
            default:
                throw std::invalid_argument("Not a correct type");
        }
    }

}