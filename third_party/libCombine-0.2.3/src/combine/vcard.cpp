#include <combine/vcard.h>
#include <combine/omexdescription.h>

#include <sbml/xml/XMLInputStream.h>

LIBCOMBINE_CPP_NAMESPACE_USE

bool VCard::isEmpty() const
{
  return mFamilyName.empty() && mGivenName.empty();
}

std::string VCard::toXML() const
{
  if (isEmpty()) return "";


  std::stringstream str;
  str << "    <dcterms:creator rdf:parseType='Resource'>" << std::endl;

  if (!mFamilyName.empty() || !mGivenName.empty())
  {
    str << "      <vCard:hasName rdf:parseType='Resource'>" << std::endl;

    if (!mFamilyName.empty())
      str << "        <vCard:family-name>" << mFamilyName << "</vCard:family-name>" << std::endl;
    if (!mGivenName.empty())
      str << "        <vCard:given-name>" << mGivenName << "</vCard:given-name>" << std::endl;

    str << "      </vCard:hasName>" << std::endl;
  }

  if (!mEmail.empty())
    str << "      <vCard:hasEmail rdf:resource='"<< mEmail << "' />" << std::endl;

  if (!mOrganization.empty())
    str << "      <vCard:organization-name>" << mOrganization << "</vCard:organization-name>" << std::endl;

  str << "    </dcterms:creator>";

  // <vCard:hasURL rdf:resource='http://orcid.org/0000-0002-6309-7327'/>

  return str.str();
}

std::string VCard::getFamilyName() const
{
  return mFamilyName;
}

void VCard::setFamilyName(const std::string &familyName)
{
  mFamilyName = familyName;
}
std::string VCard::getGivenName() const
{
  return mGivenName;
}

void VCard::setGivenName(const std::string &givenName)
{
  mGivenName = givenName;
}
std::string VCard::getEmail() const
{
  return mEmail;
}

void VCard::setEmail(const std::string &email)
{
  mEmail = email;
}
std::string VCard::getOrganization() const
{
  return mOrganization;
}

void VCard::setOrganization(const std::string &organization)
{
  mOrganization = organization;
}


VCard::VCard()
  : mFamilyName()
  , mGivenName()
  , mEmail()
  , mOrganization()
{
}

VCard::VCard(const VCard &other)
  : mFamilyName(other.mFamilyName)
  , mGivenName(other.mGivenName)
  , mEmail(other.mEmail)
  , mOrganization(other.mOrganization)
{

}

VCard::VCard(XMLInputStream &stream, const XMLToken& current)
  : mFamilyName()
  , mGivenName()
  , mEmail()
  , mOrganization()
{
 

  while (stream.isGood())
  {
    stream.skipText();
    XMLToken next = stream.next();

    if (next.isEndFor(current))
      return;

    if (!next.isStart()) 
      continue;

    if (next.getName() == "family-name")
    {
      mFamilyName = stream.next().getCharacters();
    }
    else if (next.getName() == "given-name")
    {
      mGivenName = stream.next().getCharacters();
    }
    else if (next.getName() == "organization-name")
    {
      mOrganization = stream.next().getCharacters();
    }
    else if (next.getName() == "email")
    {
      mEmail = stream.next().getCharacters();
    }
    else if (next.getName() == "hasEmail")
    {
      mEmail = next.getAttrValue("resource", OmexDescription::getRdfNS());
    }
  }
}
