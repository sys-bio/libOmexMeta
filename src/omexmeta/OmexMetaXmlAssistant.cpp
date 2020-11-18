//
// Created by Ciaran on 4/14/2020.
//

#include "omexmeta/OmexMetaXmlAssistant.h"

namespace omexmeta {
    OmexMetaXmlAssistant::OmexMetaXmlAssistant(std::string xml, std::string metaid_base, int metaid_num_digits,
                                               bool generate_new_metaids) :
            xml_(std::move(xml)), metaid_base_(std::move(metaid_base)), metaid_num_digits_(metaid_num_digits),
            generate_new_metaids_(generate_new_metaids) {
    }

    std::vector<std::string> OmexMetaXmlAssistant::getValidElements() const {
        return std::vector<std::string>({"Any"});
    }

    void OmexMetaXmlAssistant::generateMetaId(std::vector<std::string> &seen_metaids, long count,
                                              const MetaID &metaid_gen,
                                              std::string &id) {
        id = metaid_gen.generate(count);
        if (std::find(seen_metaids.begin(), seen_metaids.end(), id) != seen_metaids.end()) {
            count += 1;
            generateMetaId(seen_metaids, count, metaid_gen, id); // recursion
        }
    }

    void OmexMetaXmlAssistant::addMetaIdsRecursion(xmlDocPtr doc, xmlNode *a_node, std::vector<std::string> &seen_metaids) {
        xmlNode *cur_node;
        cur_node = a_node;
        long count = 0;
        for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
            // isolate element nodes
            if (cur_node->type == XML_ELEMENT_NODE) {
                const std::vector<std::string> &valid_elements = getValidElements();
                // if the node name is in our list of valid elements or if valid_elements_ = ["All"]
                if (std::find(valid_elements.begin(), valid_elements.end(),
                              std::string((const char *) cur_node->name)) != valid_elements.end()
                    || (valid_elements.size() == 1 && valid_elements[0] == "Any")) {

                    /*
                     * Test to see whether the element has the metaid attribute.
                     * In SBML there is a metaid attribute associated with sbml elements which are used
                     * for the metaid. In cellml however a "cmeta" namespace is used instead. We need
                     * to account for both so we can collect the ids from models that use both strategies.
                     */
                    const std::string& metaid_name = metaIdTagName();
                    const std::string  metaid_namespace = metaIdNamespace();

                    // creates an indicator to check whether we need a namespace or not for the metaid that we generate
                    bool needs_namespace = true;
                    if (metaid_namespace.empty())
                        needs_namespace = false;

                    bool has_metaid = false;
                    if (needs_namespace){
                        // use namespace strategy (cellml)
                        has_metaid = xmlHasNsProp(cur_node, (const xmlChar *) metaIdTagName().c_str(),  (const xmlChar *) metaIdNamespace().c_str());
                    } else {
                        // use attribute/property strategy (sbml)
                        has_metaid = xmlHasProp(cur_node, (const xmlChar *) metaIdTagName().c_str());
                    }

                    if (!has_metaid) {
                        // next we check to see whether the user wants us to add a metaid for them to this element.
                        // Otherwise we just collect the metaids for later inspection.
                        if (generateNewMetaids()) {
                            // If we don't already have metaid and user wants us to add one, we generate a unique id
                            MetaID metaId((const char*)cur_node->name, 0, getMetaidNumDigits());
                            std::string id;
                            OmexMetaXmlAssistant::generateMetaId(seen_metaids, count, metaId, id);
                            if (!needs_namespace) {
                                xmlNewProp(cur_node, (const xmlChar *) metaIdTagName().c_str(), (const xmlChar *) id.c_str());
                            } else {
                                // look through the existing list of xml namespaces.
                                // if its there we grab a pointer to it. if not we create it.
                                std::string cellml_metaid_namespace = "http://www.cellml.org/metadata/1.0#";
                                xmlNsPtr* ns_list_ptr = xmlGetNsList(doc, cur_node);
                                xmlNsPtr ns = ns_list_ptr[0];
                                while(ns){
                                    // make copy
                                    std::string candidate = (const char*)ns->href;
                                    if (cellml_metaid_namespace == candidate)
                                        break; // ns will point to the namespace we want
                                    ns = ns->next;
//                                    xmlFree(ns);
                                }
                                // if ns is nullptr it means we traversed the previous
                                // while loop and reached the end. Therefore the ns we want
                                // doesn't exist and we want to create it
                                if (ns == nullptr){
                                    ns = xmlNewGlobalNs(doc, (const xmlChar*) cellml_metaid_namespace.c_str(), (const xmlChar*) "cmeta");
                                }
                                // now create the NsProperty
                                xmlNewNsProp(cur_node, ns, (const xmlChar*)metaIdTagName().c_str(), (const xmlChar *) id.c_str());
                                // clear up //todo does this work?
                                xmlFree(ns_list_ptr);
                            }
                            seen_metaids.push_back(id);
                            count += 1;
                        }
                    } else {
                        // if namespace already exists, we take note by adding it to seen_metaids.
                        xmlChar *id = nullptr;
                        if (needs_namespace){
                            id = xmlGetNsProp(cur_node, (const xmlChar *) metaIdTagName().c_str(), (const xmlChar *) metaIdNamespace().c_str());
                        } else{
                            id = xmlGetProp(cur_node, (const xmlChar *) metaIdTagName().c_str());
                        }
                        if (id == nullptr){
                            throw NullPointerException("OmexMetaXmlAssistant::addMetaIdsRecursion::id is null");
                        }
                        seen_metaids.emplace_back((const char *) id);
                        xmlFree(id);
                    }
                }
            }
            // recursion, we do this for every node
            addMetaIdsRecursion(doc, cur_node->children, seen_metaids);
        }
    }


    std::pair<std::string, std::vector<std::string>> OmexMetaXmlAssistant::addMetaIds() {
        LIBXML_TEST_VERSION;
        xmlDocPtr doc; /* the resulting document tree */
        doc = xmlParseDoc((const xmlChar *) xml_.c_str());
        if (doc == nullptr) {
            throw NullPointerException("NullPointerException:  OmexMetaXmlAssistant::addMetaIds(): doc");
        }
        xmlNodePtr root_element = xmlDocGetRootElement(doc);
        std::vector<std::string> seen_metaids = {};
        addMetaIdsRecursion(doc, root_element, seen_metaids);
        xmlChar *s;
        int size;
        xmlDocDumpMemory(doc, &s, &size);
        if (s == nullptr)
            throw std::bad_alloc();
        std::string x = std::string((const char *) s);
        xmlFree(s);
        xmlFreeDoc(doc);
        xmlCleanupParser();
        std::pair<std::string, std::vector<std::string>> sbml_with_metaid(x, seen_metaids);
        return sbml_with_metaid;
    }

    std::string OmexMetaXmlAssistant::metaIdTagName() const {
        return std::string();
    }

    std::string OmexMetaXmlAssistant::metaIdNamespace() const {
        return std::string();
    }
    bool OmexMetaXmlAssistant::generateNewMetaids() const {
        return generate_new_metaids_;
    }

    const std::string &OmexMetaXmlAssistant::getMetaidBase() const {
        return metaid_base_;
    }

    int OmexMetaXmlAssistant::getMetaidNumDigits() const {
        return metaid_num_digits_;
    }

    std::vector<std::string> SBMLAssistant::getValidElements() const {
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

    std::string SBMLAssistant::metaIdTagName() const {
        return "metaid";
    }

    std::string SBMLAssistant::metaIdNamespace() const {
        return std::string();
    }

    std::vector<std::string> CellMLAssistant::getValidElements() const {
        std::vector<std::string> valid_elements_ = { "model", "component", "variable"};
        return valid_elements_;
    }

    std::string CellMLAssistant::metaIdTagName() const {
        return "id";
    }

    std::string CellMLAssistant::metaIdNamespace() const {
        return "http://www.cellml.org/metadata/1.0#";
    }

    XmlAssistantPtr
    OmexMetaXmlAssistantFactory::generate(const std::string &xml, OmexMetaXmlType type, bool generate_new_metaids,
                                        std::string metaid_base, int metaid_num_digits) {
        switch (type) {
            case OMEXMETA_TYPE_SBML: {
                SBMLAssistant sbmlAssistant(xml, metaid_base, metaid_num_digits, generate_new_metaids);
                return std::make_unique<SBMLAssistant>(sbmlAssistant);
            }
            case OMEXMETA_TYPE_CELLML: {
                CellMLAssistant cellMlAssistant(xml, metaid_base, metaid_num_digits, generate_new_metaids);
                return std::make_unique<CellMLAssistant>(cellMlAssistant);
            }
            case OMEXMETA_TYPE_UNKNOWN: {
                OmexMetaXmlAssistant xmlAssistant(xml, metaid_base, metaid_num_digits, generate_new_metaids);
                return std::make_unique<OmexMetaXmlAssistant>(xmlAssistant);
            }
            default:
                throw std::invalid_argument("Not a correct type");
        }
    }

}