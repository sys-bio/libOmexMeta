//
// Created by Ciaran on 4/14/2020.
//

#include "omexmeta/OmexMetaXml.h"
#include <libxml/parser.h>
#include <libxml/xmlwriter.h>

namespace omexmeta {
    OmexMetaXml::OmexMetaXml(std::string xml, std::string metaid_base, int metaid_num_digits, bool generate_new_metaids)
        : xml_(std::move(xml)),
          doc(parseDoc(xml_)),
          metaid_base_(std::move(metaid_base)),
          metaid_num_digits_(metaid_num_digits),
          generate_new_metaids_(generate_new_metaids) {
    }

    std::vector<std::string> OmexMetaXml::getValidElements() const {
        return std::vector<std::string>({"Any"});
    }

    void OmexMetaXml::generateMetaId(std::vector<std::string> &seen_metaids, long count,
                                     const MetaID &metaid_gen,
                                     std::string &id) {
        id = metaid_gen.generate(count);
        if (std::find(seen_metaids.begin(), seen_metaids.end(), id) != seen_metaids.end()) {
            count += 1;
            generateMetaId(seen_metaids, count, metaid_gen, id);// recursion
        }
    }

    void OmexMetaXml::addMetaIdsRecursion(xmlDocPtr doc, xmlNode *a_node, std::vector<std::string> &seen_metaids) {
        xmlNode *cur_node;
        cur_node = a_node;
        long count = 0;
        for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
            // isolate element nodes
            if (cur_node->type == XML_ELEMENT_NODE) {
                const std::vector<std::string> &valid_elements = getValidElements();
                // if the node name is in our list of valid elements or if valid_elements_ = ["All"]
                if (std::find(valid_elements.begin(), valid_elements.end(),
                              std::string((const char *) cur_node->name)) != valid_elements.end() ||
                    (valid_elements.size() == 1 && valid_elements[0] == "Any")) {

                    /*
                     * Test to see whether the element has the metaid attribute.
                     * In SBML there is a metaid attribute associated with sbml elements which are used
                     * for the metaid. In cellml however a "cmeta" namespace is used instead. We need
                     * to account for both so we can collect the ids from models that use both strategies.
                     */
                    const std::string &metaid_name = metaIdTagName();
                    const std::string metaid_namespace = metaIdNamespace();

                    // creates an indicator to check whether we need a namespace or not for the metaid that we generate
                    bool needs_namespace = true;
                    if (metaid_namespace.empty())
                        needs_namespace = false;

                    bool has_metaid = false;
                    if (needs_namespace) {
                        // use namespace strategy (cellml)
                        has_metaid = xmlHasNsProp(cur_node, (const xmlChar *) metaIdTagName().c_str(), (const xmlChar *) metaIdNamespace().c_str());
                    } else {
                        // use attribute/property strategy (sbml)
                        has_metaid = xmlHasProp(cur_node, (const xmlChar *) metaIdTagName().c_str());
                    }

                    if (!has_metaid) {
                        // next we check to see whether the user wants us to add a metaid for them to this element.
                        // Otherwise we just collect the metaids for later inspection.
                        if (generateNewMetaids()) {
                            // If we don't already have metaid and user wants us to add one, we generate a unique id
                            MetaID metaId((const char *) cur_node->name, 0, getMetaidNumDigits());
                            std::string id;
                            OmexMetaXml::generateMetaId(seen_metaids, count, metaId, id);
                            if (!needs_namespace) {
                                xmlNewProp(cur_node, (const xmlChar *) metaIdTagName().c_str(), (const xmlChar *) id.c_str());
                            } else {
                                // look through the existing list of xml namespaces.
                                // if its there we grab a pointer to it. if not we create it.
                                std::string cellml_metaid_namespace = "http://www.cellml.org/metadata/1.0#";
                                xmlNsPtr *ns_list_ptr = xmlGetNsList(doc, cur_node);
                                xmlNsPtr ns = ns_list_ptr[0];
                                while (ns) {
                                    // make copy
                                    std::string candidate = (const char *) ns->href;
                                    if (cellml_metaid_namespace == candidate)
                                        break;// ns will point to the namespace we want
                                    ns = ns->next;
                                    // xmlFree(ns);
                                }
                                // if ns is nullptr it means we traversed the previous
                                // while loop and reached the end. Therefore the ns we want
                                // doesn't exist and we want to create it
                                if (ns == nullptr) {
                                    ns = xmlNewGlobalNs(doc, (const xmlChar *) cellml_metaid_namespace.c_str(), (const xmlChar *) "cmeta");
                                }
                                // now create the NsProperty
                                xmlNewNsProp(cur_node, ns, (const xmlChar *) metaIdTagName().c_str(), (const xmlChar *) id.c_str());
                                // clear up //todo does this work?
                                xmlFree(ns_list_ptr);
                            }
                            seen_metaids.push_back(id);
                            count += 1;
                        }
                    } else {
                        // if namespace already exists, we take note by adding it to seen_metaids.
                        xmlChar *id = nullptr;
                        if (needs_namespace) {
                            id = xmlGetNsProp(cur_node, (const xmlChar *) metaIdTagName().c_str(), (const xmlChar *) metaIdNamespace().c_str());
                        } else {
                            id = xmlGetProp(cur_node, (const xmlChar *) metaIdTagName().c_str());
                        }
                        if (id == nullptr) {
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


    std::pair<std::string, std::vector<std::string>> OmexMetaXml::addMetaIds() {
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

    std::string OmexMetaXml::metaIdTagName() const {
        return std::string();
    }

    std::string OmexMetaXml::metaIdNamespace() const {
        return std::string();
    }
    bool OmexMetaXml::generateNewMetaids() const {
        return generate_new_metaids_;
    }

    const std::string &OmexMetaXml::getMetaidBase() const {
        return metaid_base_;
    }

    int OmexMetaXml::getMetaidNumDigits() const {
        return metaid_num_digits_;
    }

    void removeElementRecursion(xmlNodePtr a_node, const std::string &elementName) {
        xmlNodePtr cur_node = nullptr;
        xmlNodePtr del_node = nullptr;

        for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
            if (cur_node->type == XML_ELEMENT_NODE) {
                if (std::string((const char *) cur_node->name) == elementName) {
                    // transfer the node to a special node for deleting
                    del_node = cur_node;
                    // and ensure cur_node points to the next node
                    cur_node = cur_node->next;
                    // now we can delete the previous node
                    xmlUnlinkNode(del_node);
                }
            }
            removeElementRecursion(cur_node->children, elementName);
        }
        xmlFreeNode(cur_node);
    }

    std::string OmexMetaXml::removeElement(const std::string &elementName) {
        LIBXML_TEST_VERSION;

        // copy the xml

        xmlNodePtr root_element = xmlDocGetRootElement(doc);
        if (!root_element) {
            throw std::logic_error("Could not load xml document");
        }
        removeElementRecursion(root_element, elementName);
        return toString();
    }

    xmlDocPtr OmexMetaXml::parseDoc(const std::string &xml) {
        if (xml.empty()) {
            doc = xmlParseDoc((const xmlChar *) xml_.c_str());
        } else {
            doc = xmlParseDoc((const xmlChar *) xml.c_str());
        }
        if (doc == nullptr) {
            throw NullPointerException("NullPointerException:  OmexMetaXmlAssistant::addMetaIds(): doc");
        }
        return doc;
    }

    std::string OmexMetaXml::toString() {
        std::string out;
        xmlChar *s;
        int size;
        xmlDocDumpMemory(doc, &s, &size);
        if (s == nullptr)
            throw std::bad_alloc();
        try {
            out = (char *) s;
        } catch (...) {
            xmlFree(s);
            throw;
        }
        xmlFree(s);
        return out;
    }


    std::vector<std::string> OmexMetaSBML::getValidElements() const {
        std::vector<std::string> valid_elements_ = {
                "model",
                "unit",
                "compartment",
                "species",
                "reaction",
                "kineticLaw",
                "parameter",
        };
        return valid_elements_;
    }

    std::string OmexMetaSBML::metaIdTagName() const {
        return "metaid";
    }

    std::string OmexMetaSBML::metaIdNamespace() const {
        return std::string();
    }
    std::string OmexMetaSBML::getDefaultModelMetaid() {
        return std::string();
    }

    std::vector<std::string> OmexMetaCellML::getValidElements() const {
        std::vector<std::string> valid_elements_ = {"model", "component", "variable"};
        return valid_elements_;
    }

    std::string OmexMetaCellML::metaIdTagName() const {
        return "id";
    }

    std::string OmexMetaCellML::metaIdNamespace() const {
        return "http://www.cellml.org/metadata/1.0#";
    }
    std::string OmexMetaCellML::getDefaultModelMetaid() {
        return std::string();
    }

    OmexMetaXmlPtr
    OmexMetaXmlAssistantFactory::generate(const std::string &xml, OmexMetaXmlType type, bool generate_new_metaids,
                                          std::string metaid_base, int metaid_num_digits) {
        switch (type) {
            case OMEXMETA_TYPE_SBML: {
                OmexMetaSBML sbmlAssistant(xml, metaid_base, metaid_num_digits, generate_new_metaids);
                return std::make_unique<OmexMetaSBML>(sbmlAssistant);
            }
            case OMEXMETA_TYPE_CELLML: {
                OmexMetaCellML cellMlAssistant(xml, metaid_base, metaid_num_digits, generate_new_metaids);
                return std::make_unique<OmexMetaCellML>(cellMlAssistant);
            }
            case OMEXMETA_TYPE_UNKNOWN: {
                OmexMetaXml xmlAssistant(xml, metaid_base, metaid_num_digits, generate_new_metaids);
                return std::make_unique<OmexMetaXml>(xmlAssistant);
            }
            default:
                throw std::invalid_argument("Not a correct type");
        }
    }

}// namespace omexmeta