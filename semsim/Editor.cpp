//
// Created by Ciaran on 4/15/2020.
//

#include "Editor.h"

semsim::Editor::Editor(std::string xml, XmlAssistantType type) {
    semsim::XmlAssistantPtr xmlAssistantPtr = XmlAssistantFactory::generate(xml, type);
    std::pair<std::string, std::vector<std::string>> xml_and_metaids = xmlAssistantPtr->addMetaIds();
    xml_ = xml_and_metaids.first;
    //todo create a structure mapping metaids to more useful information for the user.
    metaids_ = xml_and_metaids.second;


}

const std::string &semsim::Editor::getXml() const {
    return xml_;
}

const std::vector<std::string> &semsim::Editor::getMetaids() const {
    return metaids_;
}

