#include <combine/omexdescription.h>

#include <sbml/xml/XMLInputStream.h>
#include <sbml/xml/XMLOutputStream.h>
#include <sbml/xml/XMLNode.h>
#include <sbml/xml/XMLToken.h>
#include <sbml/xml/XMLErrorLog.h>

#include <fstream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <sstream>


LIBSBML_CPP_NAMESPACE_USE
LIBCOMBINE_CPP_NAMESPACE_USE

const std::string &
OmexDescription::getRdfNS()
{
  static std::string ns = "http://www.w3.org/1999/02/22-rdf-syntax-ns#";
  return ns;
}

const std::string &
OmexDescription::getDcNS()
{
  static std::string ns = "http://purl.org/dc/terms/";
  return ns;
}

bool
OmexDescription::isEmpty() const
{
  bool haveDescription = !mDescription.empty();
  if (haveDescription) return false;
  bool haveCreator = !mCreators.empty();
  if (!haveCreator) return true;
  bool firstCreatorEmpty = mCreators[0].isEmpty();
  if (firstCreatorEmpty) return true;
  return false;
}

std::vector<OmexDescription>
OmexDescription::parseFile(const std::string &fileName)
{
  XMLInputStream stream(fileName.c_str(), true );
  return readFrom(stream);

}

std::vector<OmexDescription>
OmexDescription::parseString(const std::string& xml)
{
  const static std::string xml_declaration("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
  if (xml.find("<?xml version=") == std::string::npos)
  {
    return parseString(xml_declaration + xml);
  }

  XMLInputStream stream(xml.c_str(), false );
  XMLErrorLog log;
  stream.setErrorLog(&log);
  return readFrom(stream);
}

std::vector<OmexDescription>
OmexDescription::readFrom(XMLInputStream &stream)
{
  std::vector<OmexDescription> result;
  const XMLToken& start = stream.peek();

  if (!start.isStart() || start.getName() != "RDF")
    return result;

  XMLToken next = stream.next();
  stream.skipText();

  next = stream.peek();
  while (next.isStart() && next.getName() == "Description")
  {
    result.push_back(OmexDescription(stream));
    stream.skipText();
    next = stream.peek();
  }

  return result;

}

OmexDescription::OmexDescription()
  : mAbout()
  , mDescription()
  , mCreators()
  , mCreated()
  , mModified()
{
}

std::string
OmexDescription::readString(XMLInputStream &stream)
{
  std::stringstream str;
  while (stream.peek().isText())
  {
    XMLToken current = stream.next();
    str << current.getCharacters();
  }

  return str.str();
}

Date
OmexDescription::readDate(XMLInputStream &stream)
{
  stream.skipText();
  XMLToken next = stream.next();
  if (next.isStart() && next.getName() == "W3CDTF" )
  {
    next = stream.next();
    return Date(next.getCharacters());
  }
  return Date();
}

OmexDescription::OmexDescription(XMLInputStream &stream)
  : mAbout()
  , mDescription()
  , mCreators()
  , mCreated()
  , mModified()
{
  XMLNode current = stream.next();

  if (!current.isStart() || current.getName() != "Description")
    return;

  mAbout = current.getAttrValue("about", getRdfNS());

  while(stream.isGood())
  {
    stream.skipText();
    XMLToken next = stream.next();

    if (next.isEndFor(current))
      return;

    if (!next.isStart()) 
      continue;

    if (next.getName() == "description")
    {
      mDescription = readString(stream);
      stream.skipPastEnd(next);
    }
    else if (next.getName() == "modified")
    {
      Date newDate = readDate(stream);
      mModified.push_back(newDate);
      stream.skipPastEnd(next);
    }
    else if (next.getName() == "created")
    {
      mCreated = readDate(stream);
      stream.skipPastEnd(next);
    }
    else if (next.getName() == "creator")
    {
      mCreators.push_back(VCard(stream, next));
    }
  }

  stream.skipPastEnd(current);
  
}

std::string
OmexDescription::toXML(bool omitDeclaration)
{
  if (mModified.empty())
  {
    mModified.push_back(getCurrentDateAndTime());
  }

  std::stringstream modifications;
  for (std::vector<Date>::iterator it = mModified.begin(); 
       it != mModified.end(); ++it)
  {
    modifications << "    <dcterms:modified rdf:parseType='Resource'>\n"
                  <<  "      <dcterms:W3CDTF>"
                   << (*it).getDateAsString()
                   << "</dcterms:W3CDTF>\n"
                   << "    </dcterms:modified>\n";
  }

  std::stringstream creators;
  for(std::vector<VCard>::iterator it = mCreators.begin(); 
      it != mCreators.end(); ++it)
    creators << (*it).toXML() <<  "\n";

  std::stringstream result;

  if (!omitDeclaration)
    result << "<?xml version='1.0' encoding='UTF-8'?>\n";

  result << "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#' "
         << "xmlns:dcterms='http://purl.org/dc/terms/' "
         << "xmlns:vCard='http://www.w3.org/2006/vcard/ns#'>\n"
         << "  <rdf:Description rdf:about='" << mAbout << "'>\n"
         << "    <dcterms:description>" << mDescription << "</dcterms:description>\n"
         << modifications.str()
         << "    <dcterms:created rdf:parseType='Resource'>\n"
         << "      <dcterms:W3CDTF>"<< mCreated.getDateAsString() << "</dcterms:W3CDTF>\n"
         << "    </dcterms:created>\n"
         << creators.str()
         <<"  </rdf:Description>\n"
        << "</rdf:RDF>\n";

  return result.str();
}

std::string
OmexDescription::getDescription() const
{
  return mDescription;
}

void
OmexDescription::setDescription(const std::string &description)
{
  mDescription = description;
}

std::string
OmexDescription::getAbout() const
{
  return mAbout;
}

void
OmexDescription::setAbout(const std::string &about)
{
  mAbout = about;
}

const std::vector<VCard>&
OmexDescription::getCreators() const
{
  return mCreators;
}

std::vector<VCard>&
OmexDescription::getCreators()
{
  return mCreators;
}

size_t
OmexDescription::getNumCreators() const
{
  return mCreators.size();
}

void
OmexDescription::setCreators(const std::vector<VCard> &creators)
{
  mCreators = creators;
}

void
OmexDescription::addCreator(const VCard &creator)
{
  mCreators.push_back(creator);
}

const Date &
OmexDescription::getCreated() const
{
  return mCreated;
}

Date &
OmexDescription::getCreated()
{
  return mCreated;
}

VCard
OmexDescription::getCreator(unsigned int index) const
{
  if (index >= mCreators.size())
    return VCard();

  return mCreators[index];
}

void
OmexDescription::setCreated(const Date &created)
{
  mCreated = created;
}

Date
OmexDescription::getCurrentDateAndTime()
{
  time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = gmtime ( &rawtime );
  char buffer[25];
  size_t length = strftime(buffer, 25, "%Y-%m-%dT%TZ",
    timeinfo);
  
  std::stringstream str;
  str <<     buffer;
  return str.str();
}

const std::vector<Date>&
OmexDescription::getModified() const
{
  return mModified;
}

std::vector<Date>&
OmexDescription::getModified()
{
  return mModified;
}

Date OmexDescription::getModified(int index) const
{
  if (index < 0 || index >= (int)mModified.size())
    return Date();

  return mModified[index];
}

size_t
OmexDescription::getNumModified() const
{
  return mModified.size();
}

void
OmexDescription::setModified(const std::vector<Date> &modified)
{
  mModified = modified;
}

void
OmexDescription::addModification(const Date &date)
{
  mModified.push_back(date);
}

void
OmexDescription::writeToFile(const std::string &fileName)
{
  std::ofstream stream(fileName.c_str());
  stream << toXML();
  stream.flush();
  stream.close();
}
